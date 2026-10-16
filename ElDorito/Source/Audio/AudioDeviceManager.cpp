/* ---------- headers */

#include "Audio/AudioDeviceManager.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Threading/SimpleMessageQueue.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/SelectionRenderer.hpp"
#include "Patches/Events.hpp"
#include "Server/Connect/ServerConnectStateHandler_AcquireMods.hpp"
#include "Utils/EventSink.hpp"

#include <Windows.h>
#include <mmdeviceapi.h>
#include <propkeydef.h>
#include <propsys.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct lambda_1;
namespace Audio
{
	class CAudioDeviceManager;
	struct IAudioDeviceListener;
	struct SAudioDeviceEvent;
}

namespace Utils {}
using namespace ::Utils;
namespace Audio {}
using namespace ::Audio;

/* ---------- constants */

/* ---------- definitions */

//class Audio::CAudioDeviceManager::CAudioDeviceManagerImpl::Update::__l2::<lambda_1>
//{
//public:
//	<lambda_1>(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl::Update::__l2::<lambda_1> &);
//	<lambda_1>(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *);
//private:
//	Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *__this; // 0x0
//public:
//	Audio::CAudioDeviceManager::CAudioDeviceManagerImpl::Update::__l2::<lambda_1> &operator=(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl::Update::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl::Update::__l2::<lambda_1>) == 4, "Invalid Audio::CAudioDeviceManager::CAudioDeviceManagerImpl::Update::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

template<typename t_arg2> _inline void Add(t_arg2 *message);
template<typename t_arg2> _inline void ConsumeAll(t_arg2 f);

/* ---------- private variables */

/* ---------- public code */

namespace Audio
{
	_inline CAudioDeviceManager::CAudioDeviceManagerImpl::~CAudioDeviceManagerImpl() // 0x107F16E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@QAE@XZ");

		Dispose();
	}

	_inline bool CAudioDeviceManager::CAudioDeviceManagerImpl::Initialize(Audio::IAudioDeviceListener *deviceListener) // 0x107F1DB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@QAE_NPAUIAudioDeviceListener@3@@Z");

		HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&m_pDeviceEnumerator);
		if (hr < 0)
		{
			return false;
		}

		++m_referenceCount;
		m_pDeviceListener = deviceListener;
		m_eventQueue.Initialize();

		hr = m_pDeviceEnumerator->RegisterEndpointNotificationCallback(this);
		if (hr < 0)
		{
			return false;
		}

		return true;
	}

	_inline void CAudioDeviceManager::CAudioDeviceManagerImpl::Dispose() // 0x107F1A30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Dispose@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@QAEXXZ");

		m_pDeviceListener = nullptr;

		if (m_pDeviceEnumerator)
		{
			m_pDeviceEnumerator->UnregisterEndpointNotificationCallback(this);
		}

		__int32 count = Release();
		if (count == 0)
		{
			return;
		}

		while (m_referenceCount > 0)
		{
			_mm_pause();
		}
	}

	_inline void CAudioDeviceManager::CAudioDeviceManagerImpl::Update() // 0x107F2440
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@QAEXXZ");

		m_eventQueue.ConsumeAll([this](auto e) {
			if (m_pDeviceListener)
				m_pDeviceListener->OnEvent(*e);
		});
	}
}


namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::QueryInterface(_GUID const &riid, void **ppvObject) // 0x107F21E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?QueryInterface@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJABU_GUID@@PAPAX@Z");

		if (riid == IID_IUnknown)
		{
			*ppvObject = this;
			AddRef();
		}
		else if (riid == __uuidof(IMMNotificationClient))
		{
			*ppvObject = this;
			AddRef();
		}
		else
		{
			return E_NOINTERFACE;
		}
		return S_OK;
	}

	_inline unsigned long __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::AddRef() // 0x107F1A00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGKXZ");

		return _InterlockedIncrement(&m_referenceCount);
	}

	_inline unsigned long __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::Release() // 0x107F22C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Release@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGKXZ");

		return InterlockedDecrement(&m_referenceCount);
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@QAE@XZ"); no body to assert in
}


namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnDeviceStateChanged(wchar_t const *pwstrDeviceId, unsigned long dwNewState) // 0x107F2070
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnDeviceStateChanged@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJPB_WK@Z");

		return E_NOTIMPL;
	}
}


namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnDeviceAdded(wchar_t const *pwstrDeviceId) // 0x107F1F50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnDeviceAdded@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJPB_W@Z");

		SAudioDeviceEvent *e = m_eventQueue.TryToAllocate();
		if (e)
		{
			e->eventType = SAudioDeviceEvent::DeviceAdded;
			m_eventQueue.Add(e);
		}
		return S_OK;
	}
}


namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnDeviceRemoved(wchar_t const *pwstrDeviceId) // 0x107F1FE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnDeviceRemoved@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJPB_W@Z");

		SAudioDeviceEvent *e = m_eventQueue.TryToAllocate();
		if (e)
		{
			e->eventType = SAudioDeviceEvent::DeviceRemoved;
			m_eventQueue.Add(e);
		}
		return S_OK;
	}
}


namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnDefaultDeviceChanged(__MIDL___MIDL_itf_mmdeviceapi_0000_0000_0001 flow, __MIDL___MIDL_itf_mmdeviceapi_0000_0000_0002 role, wchar_t const *pwstrDefaultDeviceId) // 0x107F1EC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnDefaultDeviceChanged@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJW4__MIDL___MIDL_itf_mmdeviceapi_0000_0000_0001@@W4__MIDL___MIDL_itf_mmdeviceapi_0000_0000_0002@@PB_W@Z");

		SAudioDeviceEvent *e = m_eventQueue.TryToAllocate();
		if (e)
		{
			e->eventType = SAudioDeviceEvent::DefaultDeviceChanged;
			m_eventQueue.Add(e);
		}
		return S_OK;
	}
}


namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnPropertyValueChanged(wchar_t const *pwstrDeviceId, _tagpropertykey const key) // 0x107F2100
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnPropertyValueChanged@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJPB_WU_tagpropertykey@@@Z");

		return E_NOTIMPL;
	}

	CAudioDeviceManager::~CAudioDeviceManager() // 0x107F1630
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CAudioDeviceManager@Audio@@UAE@XZ");

		if (m_impl)
		{
			delete m_impl;
		}
	}

	void CAudioDeviceManager::Initialize() // 0x107F1C80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CAudioDeviceManager@Audio@@QAEXXZ");

		m_impl = new CAudioDeviceManagerImpl();
		m_impl->Initialize(this);
	}

	void CAudioDeviceManager::Update() // 0x107F23F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CAudioDeviceManager@Audio@@QAEXXZ");

		m_impl->Update();
	}

	void CAudioDeviceManager::OnEvent(Audio::SAudioDeviceEvent const &e) // 0x107F2090
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnEvent@CAudioDeviceManager@Audio@@EAEXABUSAudioDeviceEvent@2@@Z");

		deviceEvents.PostEvent(e);
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Audio::SAudioDeviceEvent * CSimpleMessageQueue<Audio::SAudioDeviceEvent,16>::TryToAllocate();
template CSimpleMessageQueue<Audio::SAudioDeviceEvent,16>::CSimpleMessageQueue();
template CSimpleMessageQueue<Audio::SAudioDeviceEvent,16>::~CSimpleMessageQueue();
template _SINGLE_LIST_ENTRY * CSimpleMessageQueue<Audio::SAudioDeviceEvent,16>::Reversed(_SINGLE_LIST_ENTRY *);
template void CEventSink<Audio::SAudioDeviceEvent const &>::PostEvent(Audio::SAudioDeviceEvent const &);
template void CSimpleMessageQueue<Audio::SAudioDeviceEvent,16>::FreeElement(CSimpleMessageQueue<Audio::SAudioDeviceEvent,16>::SQueueEntry *);
template void CSimpleMessageQueue<Audio::SAudioDeviceEvent,16>::Initialize();
