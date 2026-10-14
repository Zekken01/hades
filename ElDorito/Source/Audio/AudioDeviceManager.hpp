#ifndef __AUDIO_AUDIODEVICEMANAGER_HPP__
#define __AUDIO_AUDIODEVICEMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/SelectionRenderer.hpp"

/* ---------- forward declarations */

namespace Audio
{
	class CAudioDeviceManager;
	struct IAudioDeviceListener;
	struct SAudioDeviceEvent;
}

/* ---------- constants */

/* ---------- definitions */

namespace Audio
{
	struct SAudioDeviceEvent
	{
		public:
		enum EEventType
		{
			DeviceAdded = 0,
			DeviceRemoved,
			DefaultDeviceChanged,
		};
		public:
		EEventType eventType; // 0x0
	};
	static_assert(sizeof(Audio::SAudioDeviceEvent) == 4, "Invalid Audio::SAudioDeviceEvent size");

	struct IAudioDeviceListener
	{
		Audio::IAudioDeviceListener *next; // 0x4
		virtual _inline ~IAudioDeviceListener() = default; // 0x107F1780
		virtual void OnEvent(Audio::SAudioDeviceEvent const &) = 0;
		IAudioDeviceListener(Audio::IAudioDeviceListener const &); /* compiler_generated() */
		_inline IAudioDeviceListener() = default; /* compiler_generated() */
		Audio::IAudioDeviceListener &operator=(Audio::IAudioDeviceListener const &); /* compiler_generated() */
	};
	static_assert(sizeof(Audio::IAudioDeviceListener) == 8, "Invalid Audio::IAudioDeviceListener size");

	class CAudioDeviceManager :
		public Utils::Singleton<Audio::CAudioDeviceManager>,
		private Audio::IAudioDeviceListener
	{
	public:
		public:
		class CAudioDeviceManagerImpl :
			public IMMNotificationClient
		{
		public:
			_inline ~CAudioDeviceManagerImpl();
			_inline bool Initialize(Audio::IAudioDeviceListener *deviceListener);
			_inline void Dispose();
			_inline void Update();
		private:
			virtual _inline HRESULT __stdcall QueryInterface(_GUID const &riid, void **ppvObject);
			virtual _inline unsigned long __stdcall AddRef();
			virtual _inline unsigned long __stdcall Release();
			virtual _inline HRESULT __stdcall OnDeviceStateChanged(wchar_t const *pwstrDeviceId, unsigned long dwNewState);
			virtual _inline HRESULT __stdcall OnDeviceAdded(wchar_t const *pwstrDeviceId);
			virtual _inline HRESULT __stdcall OnDeviceRemoved(wchar_t const *pwstrDeviceId);
			virtual _inline HRESULT __stdcall OnDefaultDeviceChanged(__MIDL___MIDL_itf_mmdeviceapi_0000_0000_0001 flow, __MIDL___MIDL_itf_mmdeviceapi_0000_0000_0002 role, wchar_t const *pwstrDefaultDeviceId);
			virtual _inline HRESULT __stdcall OnPropertyValueChanged(wchar_t const *pwstrDeviceId, _tagpropertykey const key);
			long volatile m_referenceCount; // 0x4
			IMMDeviceEnumerator *m_pDeviceEnumerator; // 0x8
			Audio::IAudioDeviceListener *m_pDeviceListener; // 0xC
			CSimpleMessageQueue<Audio::SAudioDeviceEvent,16> m_eventQueue; // 0x10
		public:
			_inline CAudioDeviceManagerImpl() = default; /* compiler_generated() */
		};
		static_assert(sizeof(CAudioDeviceManagerImpl) == 168, "Invalid CAudioDeviceManagerImpl size");
		public:
		CEventSink<Audio::SAudioDeviceEvent const &> deviceEvents; // 0x8
	private:
		CAudioDeviceManagerImpl *m_impl = nullptr; // 0x1C
	public:
		CAudioDeviceManager() = default;  // hades: implicit, so `new T()` zero-fills first as the original's Instance() does
		virtual ~CAudioDeviceManager();
		void Initialize();
		void Update();
	private:
		virtual void OnEvent(Audio::SAudioDeviceEvent const &e);
	};
	static_assert(sizeof(Audio::CAudioDeviceManager) == 32, "Invalid Audio::CAudioDeviceManager size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Audio
{
	// hades: CAudioDeviceManager::CAudioDeviceManager() is defaulted in the class (0x109637D0)
}

/* ---------- private code */

#endif // __AUDIO_AUDIODEVICEMANAGER_HPP__
