#include "hades/hades.h"

#include "Voip/AudioEngine.hpp"

#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <Audioclient.h>
#include <mmreg.h>
#include <functiondiscoverykeys_devpkey.h>
#include <mmdeviceapi.h>

#include <algorithm>
#include <cmath>

namespace
{
	constexpr size_t MaxBufferedSamples = Voip::SampleRate * 3 / 10; // 300 ms per peer
	constexpr size_t PrebufferSamples = Voip::SampleRate * 6 / 100;  // 60 ms before playback starts
	constexpr REFERENCE_TIME BufferDuration = 400000;                  // 40 ms, in 100 ns units

	// KSDATAFORMAT_SUBTYPE_IEEE_FLOAT, spelled out so ksuser.lib is not needed
	const GUID FloatSubFormat = { 0x00000003, 0x0000, 0x0010, { 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71 } };

	template <typename T>
	struct ComPtr
	{
		T *p = nullptr;
		~ComPtr() { if (p) p->Release(); }
		T **operator&() { return &p; }
		T *operator->() const { return p; }
		explicit operator bool() const { return p != nullptr; }
	};

	void LogError(const char *what, HRESULT hr)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Sound, Utils::LogLevel::Error, "VoIP audio: %s failed (0x%08X)", what, (unsigned)hr);
	}

	WAVEFORMATEXTENSIBLE FloatFormat(int channels)
	{
		WAVEFORMATEXTENSIBLE format = {};
		format.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
		format.Format.nChannels = (WORD)channels;
		format.Format.nSamplesPerSec = Voip::SampleRate;
		format.Format.wBitsPerSample = 32;
		format.Format.nBlockAlign = (WORD)(channels * 4);
		format.Format.nAvgBytesPerSec = Voip::SampleRate * format.Format.nBlockAlign;
		format.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
		format.Samples.wValidBitsPerSample = 32;
		format.dwChannelMask = channels == 1 ? SPEAKER_FRONT_CENTER : (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT);
		format.SubFormat = FloatSubFormat;
		return format;
	}

	// The capture endpoint whose friendly name matches, or the default one.
	HRESULT FindCaptureDevice(IMMDeviceEnumerator *enumerator, const std::string &name, IMMDevice **device)
	{
		if (!name.empty() && name != "default")
		{
			ComPtr<IMMDeviceCollection> devices;
			if (SUCCEEDED(enumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &devices)))
			{
				UINT count = 0;
				devices->GetCount(&count);
				for (UINT i = 0; i < count; i++)
				{
					ComPtr<IMMDevice> candidate;
					ComPtr<IPropertyStore> store;
					if (FAILED(devices->Item(i, &candidate)) || FAILED(candidate->OpenPropertyStore(STGM_READ, &store)))
						continue;
					PROPVARIANT value;
					PropVariantInit(&value);
					bool match = false;
					if (SUCCEEDED(store->GetValue(PKEY_Device_FriendlyName, &value)) && value.vt == VT_LPWSTR)
						match = Utils::String::ThinString(value.pwszVal) == name;
					PropVariantClear(&value);
					if (match)
					{
						*device = candidate.p;
						candidate.p = nullptr;
						return S_OK;
					}
				}
			}
		}
		return enumerator->GetDefaultAudioEndpoint(eCapture, eConsole, device);
	}

	HRESULT InitializeClient(IAudioClient *client, int channels, bool communications)
	{
		if (communications)
		{
			ComPtr<IAudioClient2> client2;
			if (SUCCEEDED(client->QueryInterface(__uuidof(IAudioClient2), (void **)&client2)))
			{
				AudioClientProperties properties = {};
				properties.cbSize = sizeof(properties);
				properties.eCategory = AudioCategory_Communications;
				client2->SetClientProperties(&properties);
			}
		}
		WAVEFORMATEXTENSIBLE format = FloatFormat(channels);
		DWORD flags = AUDCLNT_STREAMFLAGS_EVENTCALLBACK | AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM | AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY;
		return client->Initialize(AUDCLNT_SHAREMODE_SHARED, flags, BufferDuration, 0, &format.Format, nullptr);
	}
}

namespace Voip
{
	AudioEngine::~AudioEngine()
	{
		Stop();
	}

	void AudioEngine::Start(const std::string &microphoneName, bool communications, FrameCallback onFrame)
	{
		Stop();
		m_onFrame = std::move(onFrame);
		m_running = true;
		m_capture = std::thread(&AudioEngine::CaptureThread, this, microphoneName, communications);
		m_render = std::thread(&AudioEngine::RenderThread, this);
	}

	void AudioEngine::Stop()
	{
		m_running = false;
		if (m_capture.joinable())
			m_capture.join();
		if (m_render.joinable())
			m_render.join();
		std::lock_guard<std::mutex> lock(m_mutex);
		m_streams.clear();
		m_loopbackStream = Stream();
		m_hasMicrophone = false;
	}

	void AudioEngine::SetLoopback(bool enabled)
	{
		m_loopback = enabled;
		if (!enabled)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_loopbackStream = Stream();
		}
	}

	void AudioEngine::Push(Stream &stream, const float *samples, int count)
	{
		if (stream.read > 0 && stream.read >= stream.ring.size() / 2)
		{
			stream.ring.erase(stream.ring.begin(), stream.ring.begin() + stream.read);
			stream.read = 0;
		}
		stream.ring.insert(stream.ring.end(), samples, samples + count);
		if (stream.Available() > MaxBufferedSamples)
			stream.read = stream.ring.size() - MaxBufferedSamples; // drop the oldest: keep latency bounded
	}

	int AudioEngine::Pull(Stream &stream, float *out, int count)
	{
		if (stream.buffering)
		{
			if (stream.Available() < PrebufferSamples)
				return 0;
			stream.buffering = false;
		}
		int n = (int)std::min<size_t>(count, stream.Available());
		std::copy_n(stream.ring.begin() + stream.read, n, out);
		stream.read += n;
		if (stream.Available() == 0)
			stream.buffering = true; // ran dry: rebuild the cushion before playing again
		return n;
	}

	void AudioEngine::PushPeerAudio(const std::string &peer, const float *samples, int count)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		Stream &stream = m_streams[peer];
		auto gain = m_gains.find(peer);
		stream.gain = gain != m_gains.end() ? gain->second : 1.0f;
		Push(stream, samples, count);
	}

	void AudioEngine::SetPeerGain(const std::string &peer, float gain)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_gains[peer] = gain;
		auto it = m_streams.find(peer);
		if (it != m_streams.end())
			it->second.gain = gain;
	}

	float AudioEngine::GetPeerGain(const std::string &peer)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		auto gain = m_gains.find(peer);
		return gain != m_gains.end() ? gain->second : 1.0f;
	}

	void AudioEngine::RemovePeer(const std::string &peer)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_streams.erase(peer);
	}

	void AudioEngine::CaptureThread(std::string microphoneName, bool communications)
	{
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		{
			ComPtr<IMMDeviceEnumerator> enumerator;
			ComPtr<IMMDevice> device;
			ComPtr<IAudioClient> client;
			ComPtr<IAudioCaptureClient> capture;
			HANDLE event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
			HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void **)&enumerator);
			if (SUCCEEDED(hr)) hr = FindCaptureDevice(enumerator.p, microphoneName, &device);
			if (SUCCEEDED(hr)) hr = device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void **)&client);
			if (SUCCEEDED(hr)) hr = InitializeClient(client.p, 1, communications);
			if (SUCCEEDED(hr)) hr = client->SetEventHandle(event);
			if (SUCCEEDED(hr)) hr = client->GetService(__uuidof(IAudioCaptureClient), (void **)&capture);
			if (SUCCEEDED(hr)) hr = client->Start();

			if (FAILED(hr))
			{
				// no microphone: stay connected and listen only (the web version sent silence)
				LogError("capture setup", hr);
			}
			else
			{
				m_hasMicrophone = true;
				std::vector<float> frame;
				frame.reserve(FrameSamples);
				while (m_running)
				{
					if (WaitForSingleObject(event, 100) != WAIT_OBJECT_0)
						continue;
					UINT32 packet = 0;
					while (SUCCEEDED(capture->GetNextPacketSize(&packet)) && packet > 0)
					{
						BYTE *data = nullptr;
						UINT32 frames = 0;
						DWORD flags = 0;
						if (FAILED(capture->GetBuffer(&data, &frames, &flags, nullptr, nullptr)))
							break;
						const float *samples = reinterpret_cast<const float *>(data);
						bool silent = (flags & AUDCLNT_BUFFERFLAGS_SILENT) != 0;
						float gain = m_outgoingGain;
						for (UINT32 i = 0; i < frames; i++)
						{
							frame.push_back(silent ? 0.0f : samples[i] * gain);
							if ((int)frame.size() == FrameSamples)
							{
								if (m_loopback)
								{
									std::lock_guard<std::mutex> lock(m_mutex);
									Push(m_loopbackStream, frame.data(), FrameSamples);
								}
								if (m_onFrame)
									m_onFrame(frame.data(), FrameSamples);
								frame.clear();
							}
						}
						capture->ReleaseBuffer(frames);
					}
				}
				client->Stop();
			}
			CloseHandle(event);
		}
		CoUninitialize();
	}

	void AudioEngine::RenderThread()
	{
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		{
			ComPtr<IMMDeviceEnumerator> enumerator;
			ComPtr<IMMDevice> device;
			ComPtr<IAudioClient> client;
			ComPtr<IAudioRenderClient> render;
			HANDLE event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
			UINT32 bufferFrames = 0;
			HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void **)&enumerator);
			if (SUCCEEDED(hr)) hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device);
			if (SUCCEEDED(hr)) hr = device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void **)&client);
			if (SUCCEEDED(hr)) hr = InitializeClient(client.p, 2, false);
			if (SUCCEEDED(hr)) hr = client->SetEventHandle(event);
			if (SUCCEEDED(hr)) hr = client->GetBufferSize(&bufferFrames);
			if (SUCCEEDED(hr)) hr = client->GetService(__uuidof(IAudioRenderClient), (void **)&render);
			if (SUCCEEDED(hr)) hr = client->Start();

			if (FAILED(hr))
			{
				LogError("playback setup", hr);
			}
			else
			{
				std::vector<float> mix, scratch;
				while (m_running)
				{
					if (WaitForSingleObject(event, 100) != WAIT_OBJECT_0)
						continue;
					UINT32 padding = 0;
					if (FAILED(client->GetCurrentPadding(&padding)))
						continue;
					UINT32 frames = bufferFrames - padding;
					if (frames == 0)
						continue;
					mix.assign(frames, 0.0f);
					scratch.resize(frames);
					{
						std::lock_guard<std::mutex> lock(m_mutex);
						for (auto &entry : m_streams)
						{
							int n = Pull(entry.second, scratch.data(), (int)frames);
							for (int i = 0; i < n; i++)
								mix[i] += scratch[i] * entry.second.gain;
						}
						if (m_loopback)
						{
							int n = Pull(m_loopbackStream, scratch.data(), (int)frames);
							for (int i = 0; i < n; i++)
								mix[i] += scratch[i];
						}
					}
					BYTE *data = nullptr;
					if (FAILED(render->GetBuffer(frames, &data)))
						continue;
					float *out = reinterpret_cast<float *>(data);
					float master = m_masterGain;
					for (UINT32 i = 0; i < frames; i++)
					{
						float v = std::clamp(mix[i] * master, -1.0f, 1.0f);
						out[i * 2] = v;
						out[i * 2 + 1] = v;
					}
					render->ReleaseBuffer(frames, 0);
				}
				client->Stop();
			}
			CloseHandle(event);
		}
		CoUninitialize();
	}
}
