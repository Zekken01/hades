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
		// Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const this;

		Dispose();
	}

	_inline bool CAudioDeviceManager::CAudioDeviceManagerImpl::Initialize(Audio::IAudioDeviceListener *deviceListener) // 0x107F1DB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@QAE_NPAUIAudioDeviceListener@3@@Z");
		// Audio::IAudioDeviceListener *deviceListener;
		// HRESULT hr;
		// function call : HRESULT (_GUID const &, IUnknown *, unsigned long, _GUID const &, void **)
		// function call : HRESULT (IMMNotificationClient *)

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
		// Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const this;
		// __int32 count;
		// function call : HRESULT (IMMNotificationClient *)
		// function call : unsigned long ()

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

	_extern void _sub_107F2440(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const);
	_inline void CAudioDeviceManager::CAudioDeviceManagerImpl::Update() // 0x107F2440
	{
		mangled_x86(MANGLED_TODO, "?Update@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@QAEXXZ");
		// Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const this;
		todo("implement");
		_sub_107F2440(this);
	}
}

extern HRESULT _sub_107F21E0(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const, _GUID const &, void **);
namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::QueryInterface(_GUID const &riid, void **ppvObject) // 0x107F21E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?QueryInterface@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJABU_GUID@@PAPAX@Z");
		// void **ppvObject;
		// function call : unsigned long ()
		// function call : unsigned long ()

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
		// Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const this;

		return _InterlockedIncrement(&m_referenceCount);
	}

	_inline unsigned long __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::Release() // 0x107F22C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Release@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGKXZ");
		// Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const this;

		return InterlockedDecrement(&m_referenceCount);
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@QAE@XZ"); no body to assert in
}

extern HRESULT _sub_107F2070(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const, wchar_t const *, unsigned long);
namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnDeviceStateChanged(wchar_t const *pwstrDeviceId, unsigned long dwNewState) // 0x107F2070
	{
		mangled_x86(MANGLED_TODO, "?OnDeviceStateChanged@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJPB_WK@Z");
		// unsigned long dwNewState;
		todo("implement");
		HRESULT __result = _sub_107F2070(this, pwstrDeviceId, dwNewState);
		return __result;
	}
}

extern HRESULT _sub_107F1F50(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const, wchar_t const *);
namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnDeviceAdded(wchar_t const *pwstrDeviceId) // 0x107F1F50
	{
		mangled_x86(MANGLED_TODO, "?OnDeviceAdded@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJPB_W@Z");
		// wchar_t const *pwstrDeviceId;
		// Audio::SAudioDeviceEvent *e;
		todo("implement");
		HRESULT __result = _sub_107F1F50(this, pwstrDeviceId);
		return __result;
	}
}

extern HRESULT _sub_107F1FE0(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const, wchar_t const *);
namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnDeviceRemoved(wchar_t const *pwstrDeviceId) // 0x107F1FE0
	{
		mangled_x86(MANGLED_TODO, "?OnDeviceRemoved@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJPB_W@Z");
		// wchar_t const *pwstrDeviceId;
		// Audio::SAudioDeviceEvent *e;
		todo("implement");
		HRESULT __result = _sub_107F1FE0(this, pwstrDeviceId);
		return __result;
	}
}

extern HRESULT _sub_107F1EC0(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const, __MIDL___MIDL_itf_mmdeviceapi_0000_0000_0001, __MIDL___MIDL_itf_mmdeviceapi_0000_0000_0002, wchar_t const *);
namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnDefaultDeviceChanged(__MIDL___MIDL_itf_mmdeviceapi_0000_0000_0001 flow, __MIDL___MIDL_itf_mmdeviceapi_0000_0000_0002 role, wchar_t const *pwstrDefaultDeviceId) // 0x107F1EC0
	{
		mangled_x86(MANGLED_TODO, "?OnDefaultDeviceChanged@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJW4__MIDL___MIDL_itf_mmdeviceapi_0000_0000_0001@@W4__MIDL___MIDL_itf_mmdeviceapi_0000_0000_0002@@PB_W@Z");
		// wchar_t const *pwstrDefaultDeviceId;
		// Audio::SAudioDeviceEvent *e;
		todo("implement");
		HRESULT __result = _sub_107F1EC0(this, flow, role, pwstrDefaultDeviceId);
		return __result;
	}
}

extern HRESULT _sub_107F2100(Audio::CAudioDeviceManager::CAudioDeviceManagerImpl *const, wchar_t const *, _tagpropertykey const);
namespace Audio
{
	_inline HRESULT __stdcall CAudioDeviceManager::CAudioDeviceManagerImpl::OnPropertyValueChanged(wchar_t const *pwstrDeviceId, _tagpropertykey const key) // 0x107F2100
	{
		mangled_x86(MANGLED_TODO, "?OnPropertyValueChanged@CAudioDeviceManagerImpl@CAudioDeviceManager@Audio@@EAGJPB_WU_tagpropertykey@@@Z");
		// _tagpropertykey key;
		todo("implement");
		HRESULT __result = _sub_107F2100(this, pwstrDeviceId, key);
		return __result;
	}

	CAudioDeviceManager::~CAudioDeviceManager() // 0x107F1630
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CAudioDeviceManager@Audio@@UAE@XZ");
		// Audio::CAudioDeviceManager *const this;

		if (m_impl)
		{
			delete m_impl;
		}
	}

	void CAudioDeviceManager::Initialize() // 0x107F1C80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CAudioDeviceManager@Audio@@QAEXXZ");
		// Audio::CAudioDeviceManager *const this;

		m_impl = new CAudioDeviceManagerImpl();
		m_impl->Initialize(this);
	}

	void CAudioDeviceManager::Update() // 0x107F23F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CAudioDeviceManager@Audio@@QAEXXZ");
		// Audio::CAudioDeviceManager *const this;

		m_impl->Update();
	}

	void CAudioDeviceManager::OnEvent(Audio::SAudioDeviceEvent const &e) // 0x107F2090
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnEvent@CAudioDeviceManager@Audio@@EAEXABUSAudioDeviceEvent@2@@Z");
		// Audio::SAudioDeviceEvent const &e;

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
