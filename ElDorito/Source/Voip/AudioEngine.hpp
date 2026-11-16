#pragma once

// WASAPI capture and playback for native VoIP (replaces the getUserMedia/WebAudio graph of
// the old CEF voip screen).  Both directions run at 48 kHz float through the shared-mode
// engine's format conversion; capture is mono, cut into 20 ms frames for Opus; playback
// mixes one jitter buffer per peer (plus the microphone test loopback) into the default
// output device.

#include <atomic>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace Voip
{
	constexpr int SampleRate = 48000;
	constexpr int FrameSamples = SampleRate / 50; // 20 ms

	class AudioEngine
	{
	public:
		// Called on the capture thread with one 20 ms mono frame (outgoing gain applied).
		using FrameCallback = std::function<void(const float *samples, int count)>;

		AudioEngine() = default;
		~AudioEngine();
		AudioEngine(const AudioEngine &) = delete;
		AudioEngine &operator=(const AudioEngine &) = delete;

		// microphoneName: endpoint friendly name, "" or "default" for the default device.
		// communications: ask the endpoint for its voice-processing mode (echo cancellation,
		// noise suppression and gain control where the driver provides them).
		void Start(const std::string &microphoneName, bool communications, FrameCallback onFrame);
		void Stop();
		bool Running() const { return m_running; }
		bool HasMicrophone() const { return m_hasMicrophone; }

		void SetOutgoingGain(float gain) { m_outgoingGain = gain; }
		void SetMasterGain(float gain) { m_masterGain = gain; }
		void SetLoopback(bool enabled);

		void PushPeerAudio(const std::string &peer, const float *samples, int count);
		void SetPeerGain(const std::string &peer, float gain);
		float GetPeerGain(const std::string &peer);
		void RemovePeer(const std::string &peer);

	private:
		struct Stream
		{
			std::vector<float> ring; // FIFO of mono samples
			size_t read = 0;
			bool buffering = true;
			float gain = 1.0f;
			size_t Available() const { return ring.size() - read; }
		};

		void CaptureThread(std::string microphoneName, bool communications);
		void RenderThread();
		void Push(Stream &stream, const float *samples, int count);
		int Pull(Stream &stream, float *out, int count);

		std::atomic<bool> m_running{ false };
		std::atomic<bool> m_hasMicrophone{ false };
		std::atomic<float> m_outgoingGain{ 1.0f };
		std::atomic<float> m_masterGain{ 1.0f };
		std::atomic<bool> m_loopback{ false };
		FrameCallback m_onFrame;
		std::thread m_capture;
		std::thread m_render;
		std::mutex m_mutex; // guards m_streams, m_loopbackStream and m_gains
		std::map<std::string, Stream> m_streams;
		std::map<std::string, float> m_gains;
		Stream m_loopbackStream;
	};
}
