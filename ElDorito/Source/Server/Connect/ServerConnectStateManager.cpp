/* ---------- headers */

#include "Server/Connect/ServerConnectStateManager.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Connect/ServerConnectStateHandler.hpp"
#include "Utils/EventSink.hpp"

#include <Windows.h>
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
#include <list>
#include <memory>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

/* ---------- forward declarations */

class CServerConnectStateHandler;
class CServerConnectStateManager;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10B0D750(CServerConnectStateManager *const, EServerConnectState, std::shared_ptr<CServerConnectStateHandler> const &);
void CServerConnectStateManager::RegisterStateHandler(EServerConnectState state, std::shared_ptr<CServerConnectStateHandler> const &handler) // 0x10B0D750
{
	mangled_x86(MANGLED_TODO, "?RegisterStateHandler@CServerConnectStateManager@@QAEXW4EServerConnectState@@ABV?$shared_ptr@VCServerConnectStateHandler@@@std@@@Z");
	// std::shared_ptr<CServerConnectStateHandler> const &handler;
	todo("implement");
	_sub_10B0D750(this, state, handler);
}

_extern void _sub_10B0DC10(CServerConnectStateManager *const);
void CServerConnectStateManager::Update() // 0x10B0DC10
{
	mangled_x86(MANGLED_TODO, "?Update@CServerConnectStateManager@@QAEXXZ");
	// CServerConnectStateManager *const this;
	{
		// bool it;
		{
			// EServerConnectState newState;
		}
	}
	// function call : void ()
	todo("implement");
	_sub_10B0DC10(this);
}

void CServerConnectStateManager::RequestStateChange(EServerConnectState state) // 0x10B0D9D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RequestStateChange@CServerConnectStateManager@@QAEXW4EServerConnectState@@@Z");
	// EServerConnectState state;

	m_requestedState = state;
}

void CServerConnectStateManager::Abort(EServerConnectAbortReason reason) // 0x10B0D610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Abort@CServerConnectStateManager@@QAEXW4EServerConnectAbortReason@@@Z");
	// EServerConnectAbortReason reason;

	m_abortReason = reason;
}

void CServerConnectStateManager::Complete() // 0x10B0D640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Complete@CServerConnectStateManager@@QAEXXZ");
	// CServerConnectStateManager *const this;

	SetStateInternal((EServerConnectState)0);
}

_extern void _sub_10B0DA00(CServerConnectStateManager *const, EServerConnectState);
void CServerConnectStateManager::SetStateInternal(EServerConnectState state) // 0x10B0DA00
{
	mangled_x86(MANGLED_TODO, "?SetStateInternal@CServerConnectStateManager@@AAEXW4EServerConnectState@@@Z");
	// EServerConnectState state;
	// function call : void ()
	// function call : void ()
	todo("implement");
	_sub_10B0DA00(this, state);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void CEventSink<enum EServerConnectAbortReason>::PostEvent(EServerConnectAbortReason);
