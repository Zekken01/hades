#include "hades/hades.h"

// libdatachannel first: it pulls in winsock2.h, which must precede windows.h.
#include <rtc/rtc.hpp>
#include <opus/opus.h>

#include "Voip/VoipClient.hpp"
#include "Voip/AudioEngine.hpp"

#include "CommandMap.hpp"
#include "Modules/ModuleVoIP.hpp"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <deque>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

// Defined in Web/Bridge/Client/ClientFunctions.cpp.
namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				QueryError OnVoIPSpeakingChanged(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnVoIPConnectedChanged(rapidjson::Value const &p_Args, std::string *p_Result);
				QueryError OnVoIPPlayerVoipJoined(rapidjson::Value const &p_Args, std::string *p_Result);
			}
		}
	}
}

namespace
{
	using Clock = std::chrono::steady_clock;
	using Writer = rapidjson::Writer<rapidjson::StringBuffer>;

	constexpr int OpusPayloadType = 111;
	constexpr int VadWindowSamples = Voip::SampleRate / 10; // hark interval: 100 ms
	constexpr float SilenceDb = -100.0f;
	constexpr float SpeakingThresholdDb = -55.0f;
	const char *const Subprotocol = "dew-voip";
	const char *const NoSession = "No session available";

	void Log(Utils::LogLevel level, const std::string &text)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, level, "VoIP: %s", text.c_str());
	}

	double Seconds()
	{
		return std::chrono::duration<double>(Clock::now().time_since_epoch()).count();
	}

	std::string NameOf(const std::string &uid)
	{
		return uid.substr(0, uid.find('|'));
	}

	std::string Json(const std::function<void(Writer &)> &build)
	{
		rapidjson::StringBuffer buffer;
		Writer writer(buffer);
		build(writer);
		return buffer.GetString();
	}

	float ToDb(double sumSquares, int count)
	{
		if (count <= 0 || sumSquares <= 0.0)
			return SilenceDb;
		double db = 10.0 * std::log10(sumSquares / count);
		return (float)std::max<double>(db, SilenceDb);
	}

	// hark.js speaking detection: starts once 2 of the last 3 intervals were loud, stops
	// once all of the last 10 were quiet.
	struct SpeechDetector
	{
		int history[10] = {};
		bool speaking = false;

		// 1: started speaking, -1: stopped, 0: no change
		int Update(float db)
		{
			int result = 0;
			bool loud = db > SpeakingThresholdDb;
			if (loud && !speaking)
			{
				int sum = 0;
				for (int i = 7; i < 10; i++)
					sum += history[i];
				if (sum >= 2)
				{
					speaking = true;
					result = 1;
				}
			}
			else if (!loud && speaking)
			{
				int sum = 0;
				for (int v : history)
					sum += v;
				if (sum == 0)
				{
					speaking = false;
					result = -1;
				}
			}
			std::move(history + 1, history + 10, history);
			history[9] = loud ? 1 : 0;
			return result;
		}

		bool Active() const
		{
			if (speaking)
				return true;
			for (int v : history)
				if (v)
					return true;
			return false;
		}
	};

	struct Settings
	{
		bool enabled = true;
		bool pushToTalk = true;
		std::string microphone;
		bool echoCancellation = true;
		bool agc = true;
		bool noiseSuppression = true;
		float incomingVolume = 1.0f;
		float outgoingVolume = 1.0f;
		int maximumBitrate = 32000;

		bool Processing() const { return echoCancellation || agc || noiseSuppression; }

		static Settings Read()
		{
			auto &voip = Modules::ModuleVoIP::Instance();
			Settings s;
			s.enabled = voip.VarVoipEnabled->ValueInt != 0;
			s.pushToTalk = voip.VarPTTEnabled->ValueInt != 0;
			s.microphone = voip.VarMicrophone->ValueString;
			s.echoCancellation = voip.VarEchoCancellation->ValueInt != 0;
			s.agc = voip.VarAGC->ValueInt != 0;
			s.noiseSuppression = voip.VarNoiseSupress->ValueInt != 0;
			s.incomingVolume = voip.VarIncomingVolume->ValueFloat;
			s.outgoingVolume = voip.VarOutgoingVolume->ValueFloat;
			s.maximumBitrate = std::max(6000, (int)voip.VarMaximumBitrate->ValueInt);
			return s;
		}
	};

	struct ServerInfo
	{
		std::string server;
		std::string password;
		bool valid = false;

		static ServerInfo Parse(const std::string &json)
		{
			ServerInfo info;
			rapidjson::Document doc;
			doc.Parse(json.c_str());
			if (doc.HasParseError() || !doc.IsObject())
				return info;
			if (doc.HasMember("server") && doc["server"].IsString())
				info.server = doc["server"].GetString();
			if (doc.HasMember("password") && doc["password"].IsString())
				info.password = doc["password"].GetString();
			info.valid = !info.server.empty();
			return info;
		}

		// Server.WebsocketInfo (game thread)
		static ServerInfo Query()
		{
			std::string response = Modules::CommandMap::Instance().ExecuteCommand("Server.WebsocketInfo");
			if (response.find(NoSession) != std::string::npos)
				return ServerInfo();
			return Parse(response);
		}
	};

	struct Peer
	{
		std::string uid;
		std::string user;
		std::shared_ptr<rtc::PeerConnection> pc;
		std::shared_ptr<rtc::DataChannel> channel;
		std::shared_ptr<rtc::Track> track;
		std::shared_ptr<rtc::RtpPacketizationConfig> rtpConfig;
		bool makingOffer = false;
		bool ignoreOffer = false;
		bool joined = false;
		std::atomic<int> requestedBitrate{ 0 };

		// receive side, touched by the track's frame callback
		std::mutex audioMutex;
		OpusDecoder *decoder = nullptr;
		std::vector<float> pcm;
		double windowSquares = 0.0;
		int windowCount = 0;
		SpeechDetector detector;
		double lastAudio = 0.0;
		bool reportedSilence = true;

		std::atomic<uint64_t> packetsSent{ 0 };
		std::atomic<uint64_t> packetsReceived{ 0 };
		size_t lastBytesSent = 0;
		size_t lastBytesReceived = 0;
		double lastStatsTime = 0.0;

		~Peer()
		{
			if (decoder)
				opus_decoder_destroy(decoder);
		}
	};

	class Client
	{
	public:
		static Client &Instance()
		{
			static Client client;
			return client;
		}

		// ---- game thread entry points

		void OnSignalReady(const std::string &json)
		{
			ServerInfo info = ServerInfo::Parse(json);
			Settings settings = Settings::Read();
			Post([this, info, settings]() {
				m_settings = settings;
				ApplyGains();
				StartConnection(info);
			});
		}

		void ApplySettings()
		{
			Settings settings = Settings::Read();
			ServerInfo info = ServerInfo::Query();
			Post([this, settings, info]() {
				bool audioChanged = settings.microphone != m_settings.microphone || settings.Processing() != m_settings.Processing();
				m_settings = settings;
				m_pushToTalk = settings.pushToTalk;
				ApplyGains();
				UpdateBitrate();
				if (!settings.enabled)
				{
					ClearConnection();
					if (!m_listening)
						m_audio.Stop();
					return;
				}
				if (audioChanged && m_audio.Running())
					StartAudio();
				if (!m_socket && info.valid && info.password != "not-connected")
					StartConnection(info);
			});
		}

		void SetTalking(bool talking)
		{
			if (!m_listening)
				m_talking = talking;
		}

		void SetListenToMicrophone(bool listen)
		{
			Settings settings = Settings::Read();
			Post([this, listen, settings]() {
				m_listening = listen;
				m_audio.SetLoopback(listen);
				if (listen && !m_audio.Running())
				{
					m_settings = settings;
					ApplyGains();
					StartAudio();
				}
				else if (!listen && !m_socket)
				{
					m_audio.Stop();
				}
			});
		}

		void SetPeerVolume(const std::string &uid, float volume)
		{
			m_audio.SetPeerGain(uid, std::max(0.0f, volume));
		}

		void Reload()
		{
			Settings settings = Settings::Read();
			ServerInfo info = ServerInfo::Query();
			Post([this, settings, info]() {
				ClearConnection();
				m_audio.Stop();
				m_settings = settings;
				ApplyGains();
				if (m_listening)
					StartAudio();
				if (info.valid && settings.enabled && info.password != "not-connected")
					StartConnection(info);
			});
		}

		void Tick()
		{
			m_statsEnabled = Modules::ModuleVoIP::Instance().VarStatsEnabled->ValueInt == 1;
			std::vector<std::function<void()>> work;
			{
				std::lock_guard<std::mutex> lock(m_gameMutex);
				work.swap(m_gameQueue);
			}
			for (auto &fn : work)
				fn();
		}

		void Shutdown()
		{
			if (!m_worker.joinable())
				return;
			Post([this]() {
				ClearConnection();
				m_audio.Stop();
				m_stop = true;
			});
			m_worker.join();
			auto cleanup = rtc::Cleanup();
			cleanup.wait_for(std::chrono::seconds(2));
		}

	private:
		Client()
		{
			std::random_device random;
			m_ssrc = random();
			m_timestamp = random();
		}

		// ---- threads

		void Post(std::function<void()> fn, int delayMs = 0)
		{
			std::lock_guard<std::mutex> lock(m_workerMutex);
			if (!m_worker.joinable())
			{
				rtc::InitLogger(rtc::LogLevel::Warning, [](rtc::LogLevel level, std::string message) {
					Log(level <= rtc::LogLevel::Error ? Utils::LogLevel::Error : Utils::LogLevel::Warning, message);
				});
				m_worker = std::thread(&Client::WorkerLoop, this);
			}
			m_tasks.emplace(Clock::now() + std::chrono::milliseconds(delayMs), std::move(fn));
			m_workerCv.notify_one();
		}

		void RunOnGame(std::function<void()> fn)
		{
			std::lock_guard<std::mutex> lock(m_gameMutex);
			m_gameQueue.push_back(std::move(fn));
		}

		void Notify(const std::string &event, const std::string &json)
		{
			RunOnGame([event, json]() { Web::Ui::ScreenLayer::Notify(event, json, true); });
		}

		template <typename Fn>
		void CallBridge(Fn fn, const std::string &json)
		{
			RunOnGame([fn, json]() {
				rapidjson::Document args;
				args.Parse(json.c_str());
				std::string result;
				fn(args, &result);
			});
		}

		void WorkerLoop()
		{
			auto nextHousekeeping = Clock::now();
			while (true)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(m_workerMutex);
					auto wakeAt = nextHousekeeping;
					if (!m_tasks.empty() && m_tasks.begin()->first < wakeAt)
						wakeAt = m_tasks.begin()->first;
					m_workerCv.wait_until(lock, wakeAt, [&]() {
						return !m_tasks.empty() && m_tasks.begin()->first <= Clock::now();
					});
					if (!m_tasks.empty() && m_tasks.begin()->first <= Clock::now())
					{
						task = std::move(m_tasks.begin()->second);
						m_tasks.erase(m_tasks.begin());
					}
				}
				if (task)
				{
					try
					{
						task();
					}
					catch (const std::exception &e)
					{
						Log(Utils::LogLevel::Error, e.what());
					}
					if (m_stop)
						return;
				}
				if (Clock::now() >= nextHousekeeping)
				{
					Housekeeping();
					nextHousekeeping = Clock::now() + std::chrono::milliseconds(100);
				}
			}
		}

		// ---- audio

		void ApplyGains()
		{
			m_audio.SetMasterGain(m_settings.incomingVolume);
			m_audio.SetOutgoingGain(m_settings.outgoingVolume);
			m_pushToTalk = m_settings.pushToTalk;
		}

		void StartAudio()
		{
			if (!m_encoder)
			{
				int error = 0;
				m_encoder = opus_encoder_create(Voip::SampleRate, 1, OPUS_APPLICATION_VOIP, &error);
				if (m_encoder)
				{
					opus_encoder_ctl(m_encoder, OPUS_SET_INBAND_FEC(1));
					opus_encoder_ctl(m_encoder, OPUS_SET_PACKET_LOSS_PERC(5));
				}
			}
			UpdateBitrate();
			m_audio.Start(m_settings.microphone, m_settings.Processing(),
				[this](const float *samples, int count) { OnCapturedFrame(samples, count); });
		}

		void UpdateBitrate()
		{
			int bitrate = m_settings.maximumBitrate;
			{
				std::lock_guard<std::mutex> lock(m_sendMutex);
				for (auto &peer : m_sendPeers)
				{
					int requested = peer->requestedBitrate;
					if (requested > 0)
						bitrate = std::min(bitrate, requested);
				}
				if (m_encoder)
					opus_encoder_ctl(m_encoder, OPUS_SET_BITRATE(bitrate));
			}
		}

		// capture thread
		void OnCapturedFrame(const float *samples, int count)
		{
			bool transmit = m_connected && (!m_pushToTalk || m_talking);
			for (int i = 0; i < count; i++)
			{
				float s = transmit ? samples[i] : 0.0f;
				m_selfSquares += (double)s * s;
			}
			m_selfCount += count;
			if (m_selfCount >= VadWindowSamples)
			{
				float db = ToDb(m_selfSquares, m_selfCount);
				m_selfSquares = 0.0;
				m_selfCount = 0;
				if (m_connected)
				{
					Notify("voip-self-volume", Json([&](Writer &w) { w.StartObject(); w.Key("volume"); w.Double(db); w.EndObject(); }));
					int change = m_selfDetector.Update(db);
					if (change != 0)
					{
						bool value = change > 0;
						CallBridge(Web::Browser::Bridge::ClientFunctions::OnVoIPSpeakingChanged,
							Json([&](Writer &w) { w.StartObject(); w.Key("value"); w.Bool(value); w.EndObject(); }));
					}
				}
			}
			if (!transmit)
				return;

			unsigned char packet[1500];
			int size;
			std::vector<std::shared_ptr<Peer>> peers;
			{
				std::lock_guard<std::mutex> lock(m_sendMutex);
				if (!m_encoder)
					return;
				size = opus_encode_float(m_encoder, samples, count, packet, sizeof(packet));
				peers = m_sendPeers;
			}
			uint32_t timestamp = m_timestamp;
			m_timestamp += (uint32_t)count;
			if (size <= 0)
				return;
			for (auto &peer : peers)
			{
				auto track = std::atomic_load(&peer->track);
				if (!track || !track->isOpen())
					continue;
				try
				{
					track->sendFrame(reinterpret_cast<const std::byte *>(packet), (size_t)size, rtc::FrameInfo(timestamp));
					peer->packetsSent++;
				}
				catch (const std::exception &)
				{
				}
			}
		}

		// libdatachannel thread: one Opus packet from a peer
		void OnPeerFrame(const std::shared_ptr<Peer> &peer, const rtc::binary &data)
		{
			peer->packetsReceived++;
			std::lock_guard<std::mutex> lock(peer->audioMutex);
			if (!peer->decoder)
			{
				int error = 0;
				peer->decoder = opus_decoder_create(Voip::SampleRate, 1, &error);
				if (!peer->decoder)
					return;
			}
			peer->pcm.resize(5760);
			int samples = opus_decode_float(peer->decoder, reinterpret_cast<const unsigned char *>(data.data()), (opus_int32)data.size(),
				peer->pcm.data(), (int)peer->pcm.size(), 0);
			if (samples <= 0)
				return;
			m_audio.PushPeerAudio(peer->uid, peer->pcm.data(), samples);
			peer->lastAudio = Seconds();
			for (int i = 0; i < samples; i++)
				peer->windowSquares += (double)peer->pcm[i] * peer->pcm[i];
			peer->windowCount += samples;
			if (peer->windowCount >= VadWindowSamples)
			{
				float db = ToDb(peer->windowSquares, peer->windowCount);
				peer->windowSquares = 0.0;
				peer->windowCount = 0;
				PeerVolume(*peer, db);
			}
		}

		// hark volume_change / speaking / stopped_speaking for a peer (audioMutex held)
		void PeerVolume(Peer &peer, float db)
		{
			float gain = m_audio.GetPeerGain(peer.uid);
			peer.reportedSilence = db <= SilenceDb;
			std::string user = peer.user;
			Notify("voip-user-volume", Json([&](Writer &w) {
				w.StartObject();
				w.Key("user"); w.String(user.c_str());
				w.Key("volume"); w.Double(db);
				w.Key("peerLevel"); w.Double(gain);
				w.EndObject();
			}));
			int change = peer.detector.Update(db);
			if (change != 0)
				NotifySpeaking(user, change > 0, db, gain == 0.0f);
		}

		void NotifySpeaking(const std::string &user, bool speaking, float db, bool muted)
		{
			Notify("voip-peer-speaking", Json([&](Writer &w) {
				w.StartObject();
				w.Key("user"); w.String(user.c_str());
				w.Key("isSpeaking"); w.Bool(speaking);
				w.Key("volume"); w.Double(db);
				w.Key("muted"); w.Bool(muted);
				w.EndObject();
			}));
		}

		// ---- worker: periodic work

		void Housekeeping()
		{
			double now = Seconds();
			// peers that stopped sending (push-to-talk released) still need to stop speaking
			for (auto &entry : m_peers)
			{
				Peer &peer = *entry.second;
				std::lock_guard<std::mutex> lock(peer.audioMutex);
				if (now - peer.lastAudio > 0.3 && (peer.detector.Active() || !peer.reportedSilence))
					PeerVolume(peer, SilenceDb);
			}
			if (m_statsEnabled && now - m_lastStats >= 1.0)
			{
				m_lastStats = now;
				SendStats(now);
			}
		}

		static const char *StateName(rtc::PeerConnection::State state)
		{
			switch (state)
			{
			case rtc::PeerConnection::State::New: return "new";
			case rtc::PeerConnection::State::Connecting: return "connecting";
			case rtc::PeerConnection::State::Connected: return "connected";
			case rtc::PeerConnection::State::Disconnected: return "disconnected";
			case rtc::PeerConnection::State::Failed: return "failed";
			default: return "closed";
			}
		}

		static const char *IceStateName(rtc::PeerConnection::IceState state)
		{
			switch (state)
			{
			case rtc::PeerConnection::IceState::New: return "new";
			case rtc::PeerConnection::IceState::Checking: return "checking";
			case rtc::PeerConnection::IceState::Connected: return "connected";
			case rtc::PeerConnection::IceState::Completed: return "completed";
			case rtc::PeerConnection::IceState::Failed: return "failed";
			case rtc::PeerConnection::IceState::Disconnected: return "disconnected";
			default: return "closed";
			}
		}

		static const char *CandidateTypeName(rtc::Candidate::Type type)
		{
			switch (type)
			{
			case rtc::Candidate::Type::Host: return "host";
			case rtc::Candidate::Type::ServerReflexive: return "srflx";
			case rtc::Candidate::Type::PeerReflexive: return "prflx";
			case rtc::Candidate::Type::Relayed: return "relay";
			default: return "-";
			}
		}

		void SendStats(double now)
		{
			std::string json = Json([&](Writer &w) {
				w.StartObject();
				w.Key("peers");
				w.StartArray();
				for (auto &entry : m_peers)
				{
					Peer &peer = *entry.second;
					size_t sent = peer.pc->bytesSent();
					size_t received = peer.pc->bytesReceived();
					double dt = peer.lastStatsTime > 0 ? now - peer.lastStatsTime : 0.0;
					double outBitrate = dt > 0 ? (double)(sent - peer.lastBytesSent) * 8 / dt : 0.0;
					double inBitrate = dt > 0 ? (double)(received - peer.lastBytesReceived) * 8 / dt : 0.0;
					peer.lastBytesSent = sent;
					peer.lastBytesReceived = received;
					peer.lastStatsTime = now;

					std::string iceType = "-";
					rtc::Candidate local, remote;
					if (peer.pc->getSelectedCandidatePair(&local, &remote))
						iceType = std::string(CandidateTypeName(local.type())) + " / " + CandidateTypeName(remote.type());

					w.StartObject();
					w.Key("uid"); w.String(peer.uid.c_str());
					w.Key("connectionState"); w.String(StateName(peer.pc->state()));
					w.Key("iceConnectionState"); w.String(IceStateName(peer.pc->iceState()));
					w.Key("iceType"); w.String(iceType.c_str());
					w.Key("outgoingBitrate"); w.Double(std::round(outBitrate));
					w.Key("incomingBitrate"); w.Double(std::round(inBitrate));
					w.Key("packetsSent"); w.Uint64(peer.packetsSent);
					w.Key("packetsReceived"); w.Uint64(peer.packetsReceived);
					w.Key("packetsLost"); w.Uint64(0);
					w.EndObject();
				}
				w.EndArray();
				w.EndObject();
			});
			Notify("voip-stats", json);
		}

		// ---- worker: signaling (rtc.js startConnection / OnMessage)

		void StartConnection(const ServerInfo &info)
		{
			if (m_socket)
				ClearConnection();
			if (!info.valid || info.password.empty() || !m_settings.enabled)
				return;

			m_info = info;
			if (!m_audio.Running())
				StartAudio();

			rtc::WebSocket::Configuration config;
			config.protocols = { Subprotocol };
			auto socket = std::make_shared<rtc::WebSocket>(config);
			int generation = ++m_socketGeneration;
			socket->onOpen([this, generation]() {
				Post([this, generation]() {
					if (generation != m_socketGeneration || !m_socket)
						return;
					// rtc.js waited 500 ms before sending the password
					Post([this, generation]() {
						if (generation != m_socketGeneration || !m_socket)
							return;
						m_socket->send(m_info.password);
						m_connected = true;
						CallBridge(Web::Browser::Bridge::ClientFunctions::OnVoIPConnectedChanged, "{\"value\":true}");
					}, 500);
				});
			});
			socket->onMessage([this, generation](rtc::message_variant message) {
				if (!std::holds_alternative<std::string>(message))
					return;
				std::string text = std::get<std::string>(std::move(message));
				Post([this, generation, text]() {
					if (generation == m_socketGeneration)
						OnSignalMessage(text);
				});
			});
			socket->onClosed([this, generation]() {
				Post([this, generation]() {
					if (generation != m_socketGeneration)
						return; // replaced or closed on purpose
					Log(Utils::LogLevel::Info, "disconnected from signal server");
					ClearConnection();
					Post([this]() { Retry(); }, 3000);
				});
			});
			socket->onError([](std::string error) { Log(Utils::LogLevel::Warning, "signal server: " + error); });
			m_socket = socket;
			try
			{
				socket->open("ws://" + info.server);
			}
			catch (const std::exception &e)
			{
				Log(Utils::LogLevel::Error, e.what());
				m_socket.reset();
			}
		}

		void Retry()
		{
			RunOnGame([this]() {
				ServerInfo info = ServerInfo::Query();
				if (info.valid)
					Post([this, info]() { StartConnection(info); });
			});
		}

		void ClearConnection()
		{
			bool hadSocket = m_socket != nullptr;
			m_socketGeneration++;
			if (m_socket)
			{
				try { m_socket->close(); } catch (...) {}
				m_socket.reset();
			}
			std::vector<std::string> uids;
			for (auto &entry : m_peers)
				uids.push_back(entry.first);
			for (auto &uid : uids)
				RemovePeer(uid);
			if (m_connected || hadSocket)
				CallBridge(Web::Browser::Bridge::ClientFunctions::OnVoIPConnectedChanged, "{\"value\":false}");
			m_connected = false;
		}

		void SendSignal(const std::string &text)
		{
			if (!m_socket || !m_socket->isOpen())
				return;
			try
			{
				m_socket->send(text);
			}
			catch (const std::exception &e)
			{
				Log(Utils::LogLevel::Warning, e.what());
			}
		}

		void OnSignalMessage(const std::string &text)
		{
			if (text == "bad password")
			{
				Log(Utils::LogLevel::Warning, "bad password");
				return;
			}
			if (text == "try again later")
			{
				int generation = m_socketGeneration;
				Post([this, generation]() {
					RunOnGame([this, generation]() {
						ServerInfo info = ServerInfo::Query();
						if (!info.valid)
							return;
						Post([this, generation, info]() {
							if (generation == m_socketGeneration)
								SendSignal(info.password);
						});
					});
				}, 5000);
				return;
			}

			rapidjson::Document data;
			data.Parse(text.c_str());
			if (data.HasParseError() || !data.IsObject())
				return;

			if (data.HasMember("auth"))
			{
				if (data.HasMember("uid") && data["uid"].IsString())
					m_myUid = data["uid"].GetString();
				m_iceServers.clear();
				if (data.HasMember("iceServers") && data["iceServers"].IsArray())
					ParseIceServers(data["iceServers"]);
				SendSignal("{\"broadcast\":\"garbage\"}"); // let the other peers know we are ready
			}
			else if (data.HasMember("broadcast"))
			{
				if (data.HasMember("uid") && data["uid"].IsString())
					CreatePeer(data["uid"].GetString(), true);
			}
			else if (data.HasMember("sendTo"))
			{
				if (!data.HasMember("uid") || !data["uid"].IsString())
					return;
				std::string uid = data["uid"].GetString();
				auto peer = CreatePeer(uid, false);
				if (!peer)
					return;
				if (data.HasMember("sdp") && data["sdp"].IsObject())
					OnRemoteDescription(peer, data["sdp"]);
				else if (data.HasMember("ice") && data["ice"].IsObject())
					OnRemoteCandidate(peer, data["ice"]);
			}
			else if (data.HasMember("leave") && data["leave"].IsString())
			{
				RemovePeer(data["leave"].GetString());
			}
		}

		void ParseIceServers(const rapidjson::Value &servers)
		{
			for (auto &server : servers.GetArray())
			{
				if (!server.IsObject() || !server.HasMember("urls"))
					continue;
				std::vector<std::string> urls;
				const rapidjson::Value &value = server["urls"];
				if (value.IsString())
					urls.push_back(value.GetString());
				else if (value.IsArray())
					for (auto &url : value.GetArray())
						if (url.IsString())
							urls.push_back(url.GetString());
				for (auto &url : urls)
				{
					try
					{
						rtc::IceServer ice(url);
						if (server.HasMember("username") && server["username"].IsString())
							ice.username = server["username"].GetString();
						if (server.HasMember("credential") && server["credential"].IsString())
							ice.password = server["credential"].GetString();
						m_iceServers.push_back(ice);
					}
					catch (const std::exception &e)
					{
						Log(Utils::LogLevel::Warning, "bad ice server " + url + ": " + e.what());
					}
				}
			}
		}

		// ---- worker: peers (rtc.js createPeer / removePeer)

		std::shared_ptr<Peer> CreatePeer(const std::string &uid, bool offerer)
		{
			auto existing = m_peers.find(uid);
			if (existing != m_peers.end())
				return existing->second;

			rtc::Configuration config;
			config.iceServers = m_iceServers;
			config.disableAutoNegotiation = true;

			auto peer = std::make_shared<Peer>();
			peer->uid = uid;
			peer->user = NameOf(uid);
			peer->pc = std::make_shared<rtc::PeerConnection>(config);
			std::weak_ptr<Peer> weak = peer;

			peer->pc->onLocalDescription([this, weak](rtc::Description description) {
				std::string sdp = std::string(description);
				std::string type = description.typeString();
				Post([this, weak, sdp, type]() {
					auto peer = weak.lock();
					if (!peer)
						return;
					SendSignal(Json([&](Writer &w) {
						w.StartObject();
						w.Key("sdp");
						w.StartObject();
						w.Key("type"); w.String(type.c_str());
						w.Key("sdp"); w.String(sdp.c_str());
						w.EndObject();
						w.Key("sendTo"); w.String(peer->uid.c_str());
						w.EndObject();
					}));
				});
			});
			peer->pc->onLocalCandidate([this, weak](rtc::Candidate candidate) {
				std::string text = candidate.candidate();
				std::string mid = candidate.mid();
				Post([this, weak, text, mid]() {
					auto peer = weak.lock();
					if (!peer)
						return;
					SendSignal(Json([&](Writer &w) {
						w.StartObject();
						w.Key("ice");
						w.StartObject();
						w.Key("candidate"); w.String(text.c_str());
						w.Key("sdpMid"); w.String(mid.c_str());
						w.EndObject();
						w.Key("sendTo"); w.String(peer->uid.c_str());
						w.EndObject();
					}));
				});
			});
			peer->pc->onStateChange([this, weak](rtc::PeerConnection::State state) {
				Post([this, weak, state]() {
					auto peer = weak.lock();
					if (!peer || state != rtc::PeerConnection::State::Connected || peer->joined)
						return;
					peer->joined = true;
					std::string name = peer->user;
					std::string id = peer->uid.find('|') != std::string::npos ? peer->uid.substr(peer->uid.find('|') + 1) : "";
					CallBridge(Web::Browser::Bridge::ClientFunctions::OnVoIPPlayerVoipJoined, Json([&](Writer &w) {
						w.StartObject();
						w.Key("name"); w.String(name.c_str());
						w.Key("uid"); w.String(id.c_str());
						w.EndObject();
					}));
				});
			});
			peer->pc->onTrack([this, weak](std::shared_ptr<rtc::Track> track) {
				// the remote offered an audio track: send on it too
				auto peer = weak.lock();
				if (!peer || track->description().type() != "audio")
					return;
				int payloadType = OpusPayloadType;
				rtc::Description::Media media = track->description();
				for (int pt : media.payloadTypes())
				{
					auto *map = media.rtpMap(pt);
					if (map && (map->format == "opus" || map->format == "OPUS"))
					{
						payloadType = pt;
						break;
					}
				}
				media.addSSRC(m_ssrc, "dewvoip", "dewvoip", "dewvoip-audio");
				media.setDirection(rtc::Description::Direction::SendRecv);
				track->setDescription(media);
				ConfigureTrack(peer, track, payloadType);
			});

			if (offerer)
			{
				rtc::Description::Audio media("0", rtc::Description::Direction::SendRecv);
				media.addOpusCodec(OpusPayloadType);
				media.addSSRC(m_ssrc, "dewvoip", "dewvoip", "dewvoip-audio");
				ConfigureTrack(peer, peer->pc->addTrack(media), OpusPayloadType);
			}

			rtc::DataChannelInit init;
			init.negotiated = true;
			init.id = 0;
			peer->channel = peer->pc->createDataChannel("voip", init);
			peer->channel->onOpen([this, weak]() {
				Post([this, weak]() {
					auto peer = weak.lock();
					if (peer && peer->channel)
					{
						try
						{
							peer->channel->send("{\"request\":\"bitrate\",\"data\":" + std::to_string(m_settings.maximumBitrate) + "}");
						}
						catch (...)
						{
						}
					}
				});
			});
			peer->channel->onMessage([this, weak](rtc::message_variant message) {
				if (!std::holds_alternative<std::string>(message))
					return;
				std::string text = std::get<std::string>(std::move(message));
				Post([this, weak, text]() {
					auto peer = weak.lock();
					if (!peer)
						return;
					rapidjson::Document doc;
					doc.Parse(text.c_str());
					if (doc.HasParseError() || !doc.IsObject() || !doc.HasMember("request") || !doc["request"].IsString())
						return;
					if (std::string(doc["request"].GetString()) == "bitrate" && doc.HasMember("data") && doc["data"].IsNumber())
					{
						peer->requestedBitrate = std::min(doc["data"].GetInt(), m_settings.maximumBitrate);
						UpdateBitrate();
					}
				});
			});

			m_peers[uid] = peer;
			UpdateSendPeers();

			if (offerer)
			{
				peer->makingOffer = true;
				peer->ignoreOffer = false;
				try
				{
					peer->pc->setLocalDescription(rtc::Description::Type::Offer);
				}
				catch (const std::exception &e)
				{
					Log(Utils::LogLevel::Error, std::string("offer failed: ") + e.what());
				}
				peer->makingOffer = false;
			}
			return peer;
		}

		void ConfigureTrack(const std::shared_ptr<Peer> &peer, std::shared_ptr<rtc::Track> track, int payloadType)
		{
			auto config = std::make_shared<rtc::RtpPacketizationConfig>(m_ssrc, "dewvoip", (uint8_t)payloadType, rtc::OpusRtpPacketizer::DefaultClockRate);
			auto packetizer = std::make_shared<rtc::OpusRtpPacketizer>(config);
			packetizer->addToChain(std::make_shared<rtc::RtcpSrReporter>(config));
			packetizer->addToChain(std::make_shared<rtc::RtcpNackResponder>());
			packetizer->addToChain(std::make_shared<rtc::OpusRtpDepacketizer>());
			track->setMediaHandler(packetizer);
			std::weak_ptr<Peer> weak = peer;
			track->onFrame([this, weak](rtc::binary data, rtc::FrameInfo) {
				if (auto peer = weak.lock())
					OnPeerFrame(peer, data);
			});
			peer->rtpConfig = config;
			std::atomic_store(&peer->track, track);
		}

		void OnRemoteDescription(const std::shared_ptr<Peer> &peer, const rapidjson::Value &sdp)
		{
			if (!sdp.HasMember("sdp") || !sdp["sdp"].IsString() || !sdp.HasMember("type") || !sdp["type"].IsString())
				return;
			std::string type = sdp["type"].GetString();
			// perfect negotiation: the impolite side ignores a colliding offer
			bool offerCollision = type == "offer" &&
				(peer->makingOffer || peer->pc->signalingState() != rtc::PeerConnection::SignalingState::Stable);
			peer->ignoreOffer = peer->uid < m_myUid && offerCollision;
			if (peer->ignoreOffer)
				return;
			try
			{
				peer->pc->setRemoteDescription(rtc::Description(sdp["sdp"].GetString(), type));
				if (type == "offer")
					peer->pc->setLocalDescription(rtc::Description::Type::Answer);
			}
			catch (const std::exception &e)
			{
				Log(Utils::LogLevel::Error, std::string("remote description: ") + e.what());
			}
		}

		void OnRemoteCandidate(const std::shared_ptr<Peer> &peer, const rapidjson::Value &ice)
		{
			if (!ice.HasMember("candidate") || !ice["candidate"].IsString())
				return;
			std::string candidate = ice["candidate"].GetString();
			if (candidate.empty())
				return; // end of candidates
			std::string mid = ice.HasMember("sdpMid") && ice["sdpMid"].IsString() ? ice["sdpMid"].GetString() : "0";
			try
			{
				peer->pc->addRemoteCandidate(rtc::Candidate(candidate, mid));
			}
			catch (const std::exception &e)
			{
				if (!peer->ignoreOffer)
					Log(Utils::LogLevel::Warning, std::string("candidate: ") + e.what());
			}
		}

		void RemovePeer(const std::string &uid)
		{
			auto it = m_peers.find(uid);
			if (it == m_peers.end())
				return;
			auto peer = it->second;
			m_peers.erase(it);
			UpdateSendPeers();
			try
			{
				peer->pc->resetCallbacks();
				peer->pc->close();
			}
			catch (...)
			{
			}
			m_audio.RemovePeer(uid);
			Notify("voip-user-leave", Json([&](Writer &w) { w.StartObject(); w.Key("user"); w.String(uid.c_str()); w.EndObject(); }));
			NotifySpeaking(peer->user, false, 0.0f, false);
		}

		void UpdateSendPeers()
		{
			{
				std::lock_guard<std::mutex> lock(m_sendMutex);
				m_sendPeers.clear();
				for (auto &entry : m_peers)
					m_sendPeers.push_back(entry.second);
			}
			UpdateBitrate();
		}

		// ---- state

		std::thread m_worker;
		std::mutex m_workerMutex;
		std::condition_variable m_workerCv;
		std::multimap<Clock::time_point, std::function<void()>> m_tasks;
		bool m_stop = false;

		std::mutex m_gameMutex;
		std::vector<std::function<void()>> m_gameQueue;

		// worker-owned
		Settings m_settings;
		ServerInfo m_info;
		std::shared_ptr<rtc::WebSocket> m_socket;
		int m_socketGeneration = 0;
		std::string m_myUid;
		std::vector<rtc::IceServer> m_iceServers;
		std::map<std::string, std::shared_ptr<Peer>> m_peers;
		double m_lastStats = 0.0;

		// shared with the capture thread
		Voip::AudioEngine m_audio;
		std::mutex m_sendMutex; // guards m_sendPeers and m_encoder
		std::vector<std::shared_ptr<Peer>> m_sendPeers;
		OpusEncoder *m_encoder = nullptr;
		uint32_t m_ssrc = 0;
		std::atomic<uint32_t> m_timestamp{ 0 };
		std::atomic<bool> m_connected{ false };
		std::atomic<bool> m_pushToTalk{ true };
		std::atomic<bool> m_talking{ false };
		std::atomic<bool> m_listening{ false };
		std::atomic<bool> m_statsEnabled{ false };
		double m_selfSquares = 0.0; // capture thread only
		int m_selfCount = 0;
		SpeechDetector m_selfDetector;
	};
}

namespace Voip
{
	void OnSignalReady(const std::string &json) { Client::Instance().OnSignalReady(json); }
	void ApplySettings() { Client::Instance().ApplySettings(); }
	void SetTalking(bool talking) { Client::Instance().SetTalking(talking); }
	void SetListenToMicrophone(bool listen) { Client::Instance().SetListenToMicrophone(listen); }
	void SetPeerVolume(const std::string &uid, float volume) { Client::Instance().SetPeerVolume(uid, volume); }
	void Reload() { Client::Instance().Reload(); }
	void Tick() { Client::Instance().Tick(); }
	void Shutdown() { Client::Instance().Shutdown(); }
}
