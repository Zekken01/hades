// Smoke test for the native VoIP peer setup (mirrors Voip/VoipClient.cpp CreatePeer and
// ConfigureTrack): an offerer with its own Opus track and an answerer that adopts the
// offered track in onTrack, both with a negotiated "voip" data channel (id 0) and
// auto-negotiation off.  Signaling is a direct in-process hand-off.  Passes when Opus
// frames arrive both ways and the data channel carries the bitrate request.
//
// build: cmake --build --preset default --target peer_test (build/voip-test/peer_test.exe)

#include <rtc/rtc.hpp>
#include <opus/opus.h>

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

struct Side
{
	const char *name;
	std::shared_ptr<rtc::PeerConnection> pc;
	std::shared_ptr<rtc::Track> track;
	std::shared_ptr<rtc::DataChannel> channel;
	std::atomic<int> framesReceived{ 0 };
	std::atomic<int> samplesDecoded{ 0 };
	std::atomic<bool> gotBitrate{ false };
	OpusDecoder *decoder = nullptr;
	uint32_t ssrc;
};

static void Configure(Side &side, std::shared_ptr<rtc::Track> track, int payloadType)
{
	auto config = std::make_shared<rtc::RtpPacketizationConfig>(side.ssrc, "dewvoip", (uint8_t)payloadType, rtc::OpusRtpPacketizer::DefaultClockRate);
	auto packetizer = std::make_shared<rtc::OpusRtpPacketizer>(config);
	packetizer->addToChain(std::make_shared<rtc::RtcpSrReporter>(config));
	packetizer->addToChain(std::make_shared<rtc::RtcpNackResponder>());
	packetizer->addToChain(std::make_shared<rtc::OpusRtpDepacketizer>());
	track->setMediaHandler(packetizer);
	track->onFrame([&side](rtc::binary data, rtc::FrameInfo) {
		side.framesReceived++;
		float pcm[5760];
		int n = opus_decode_float(side.decoder, reinterpret_cast<const unsigned char *>(data.data()), (opus_int32)data.size(), pcm, 5760, 0);
		if (n > 0)
			side.samplesDecoded += n;
	});
	std::atomic_store(&side.track, track);
}

int main()
{
	rtc::InitLogger(rtc::LogLevel::Warning);
	Side a{ "offerer" }, b{ "answerer" };
	a.ssrc = 1111;
	b.ssrc = 2222;
	int error = 0;
	a.decoder = opus_decoder_create(48000, 1, &error);
	b.decoder = opus_decoder_create(48000, 1, &error);

	rtc::Configuration config;
	config.disableAutoNegotiation = true;
	a.pc = std::make_shared<rtc::PeerConnection>(config);
	b.pc = std::make_shared<rtc::PeerConnection>(config);

	// signaling: descriptions and candidates go straight to the other side
	auto wire = [](Side &from, Side &to) {
		from.pc->onLocalDescription([&to](rtc::Description d) {
			std::string sdp = std::string(d), type = d.typeString();
			std::thread([&to, sdp, type]() {
				to.pc->setRemoteDescription(rtc::Description(sdp, type));
				if (type == "offer")
					to.pc->setLocalDescription(rtc::Description::Type::Answer);
			}).detach();
		});
		from.pc->onLocalCandidate([&to](rtc::Candidate c) {
			std::string cand = c.candidate(), mid = c.mid();
			std::thread([&to, cand, mid]() { to.pc->addRemoteCandidate(rtc::Candidate(cand, mid)); }).detach();
		});
	};
	wire(a, b);
	wire(b, a);

	b.pc->onTrack([&b](std::shared_ptr<rtc::Track> track) {
		int payloadType = 111;
		rtc::Description::Media media = track->description();
		for (int pt : media.payloadTypes())
			if (auto *map = media.rtpMap(pt); map && map->format == "opus")
				payloadType = pt;
		media.addSSRC(b.ssrc, "dewvoip", "dewvoip", "dewvoip-audio");
		media.setDirection(rtc::Description::Direction::SendRecv);
		track->setDescription(media);
		Configure(b, track, payloadType);
		printf("answerer: adopted offered track mid=%s pt=%d\n", track->mid().c_str(), payloadType);
	});

	rtc::Description::Audio media("0", rtc::Description::Direction::SendRecv);
	media.addOpusCodec(111);
	media.addSSRC(a.ssrc, "dewvoip", "dewvoip", "dewvoip-audio");
	Configure(a, a.pc->addTrack(media), 111);

	rtc::DataChannelInit init;
	init.negotiated = true;
	init.id = 0;
	for (Side *s : { &a, &b })
	{
		s->channel = s->pc->createDataChannel("voip", init);
		s->channel->onOpen([s]() { s->channel->send("{\"request\":\"bitrate\",\"data\":32000}"); });
		s->channel->onMessage([s](rtc::message_variant m) {
			if (std::holds_alternative<std::string>(m) && std::get<std::string>(m).find("bitrate") != std::string::npos)
				s->gotBitrate = true;
		});
	}

	a.pc->setLocalDescription(rtc::Description::Type::Offer);

	// 2 s of a 440 Hz tone each way in 20 ms Opus frames
	OpusEncoder *encoder = opus_encoder_create(48000, 1, OPUS_APPLICATION_VOIP, &error);
	opus_encoder_ctl(encoder, OPUS_SET_BITRATE(32000));
	std::vector<float> frame(960);
	uint32_t timestamp = 1000;
	int sent = 0;
	for (int i = 0; i < 300; i++)
	{
		for (int j = 0; j < 960; j++)
			frame[j] = 0.3f * std::sin(2 * 3.14159265f * 440.0f * (i * 960 + j) / 48000.0f);
		unsigned char packet[1500];
		int size = opus_encode_float(encoder, frame.data(), 960, packet, sizeof(packet));
		for (Side *s : { &a, &b })
		{
			auto track = std::atomic_load(&s->track);
			if (track && track->isOpen())
			{
				track->sendFrame(reinterpret_cast<const std::byte *>(packet), (size_t)size, rtc::FrameInfo(timestamp));
				sent++;
			}
		}
		timestamp += 960;
		std::this_thread::sleep_for(20ms);
	}

	printf("state a=%d b=%d sent=%d\n", (int)a.pc->state(), (int)b.pc->state(), sent);
	printf("offerer received %d frames (%d samples), answerer received %d frames (%d samples)\n",
		a.framesReceived.load(), a.samplesDecoded.load(), b.framesReceived.load(), b.samplesDecoded.load());
	printf("bitrate request: offerer %s, answerer %s\n", a.gotBitrate ? "yes" : "no", b.gotBitrate ? "yes" : "no");
	bool ok = a.framesReceived > 50 && b.framesReceived > 50 && a.gotBitrate && b.gotBitrate;
	printf(ok ? "PASS\n" : "FAIL\n");
	a.pc->close();
	b.pc->close();
	rtc::Cleanup().wait_for(2s);
	return ok ? 0 : 1;
}
