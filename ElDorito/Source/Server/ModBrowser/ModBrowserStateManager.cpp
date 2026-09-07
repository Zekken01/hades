/* ---------- headers */

#include "Server/ModBrowser/ModBrowserStateManager.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/ModBrowser/ModBrowserStateHandler.hpp"
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

class CModBrowserStateHandler;
class CModBrowserStateManager;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10724970(CModBrowserStateManager *const, EModBrowserState, std::shared_ptr<CModBrowserStateHandler> const &);
void CModBrowserStateManager::RegisterStateHandler(EModBrowserState state, std::shared_ptr<CModBrowserStateHandler> const &handler) // 0x10724970
{
	mangled_x86(MANGLED_TODO, "?RegisterStateHandler@CModBrowserStateManager@@QAEXW4EModBrowserState@@ABV?$shared_ptr@VCModBrowserStateHandler@@@std@@@Z");
	// std::shared_ptr<CModBrowserStateHandler> const &handler;
	todo("implement");
	_sub_10724970(this, state, handler);
}

_extern void _sub_10724E30(CModBrowserStateManager *const);
void CModBrowserStateManager::Update() // 0x10724E30
{
	mangled_x86(MANGLED_TODO, "?Update@CModBrowserStateManager@@QAEXXZ");
	// CModBrowserStateManager *const this;
	{
		// bool it;
		{
			// EModBrowserState newState;
		}
	}
	// function call : void ()
	todo("implement");
	_sub_10724E30(this);
}

_extern void _sub_10724BF0(CModBrowserStateManager *const, EModBrowserState);
void CModBrowserStateManager::RequestStateChange(EModBrowserState state) // 0x10724BF0
{
	mangled_x86(MANGLED_TODO, "?RequestStateChange@CModBrowserStateManager@@QAEXW4EModBrowserState@@@Z");
	// EModBrowserState state;
	todo("implement");
	_sub_10724BF0(this, state);
}

_extern void _sub_10724830(CModBrowserStateManager *const, EModBrowserAbortReason);
void CModBrowserStateManager::Abort(EModBrowserAbortReason reason) // 0x10724830
{
	mangled_x86(MANGLED_TODO, "?Abort@CModBrowserStateManager@@QAEXW4EModBrowserAbortReason@@@Z");
	// EModBrowserAbortReason reason;
	todo("implement");
	_sub_10724830(this, reason);
}

_extern void _sub_10724860(CModBrowserStateManager *const);
void CModBrowserStateManager::Complete() // 0x10724860
{
	mangled_x86(MANGLED_TODO, "?Complete@CModBrowserStateManager@@QAEXXZ");
	// CModBrowserStateManager *const this;
	todo("implement");
	_sub_10724860(this);
}

_extern void _sub_10724C20(CModBrowserStateManager *const, EModBrowserState);
void CModBrowserStateManager::SetStateInternal(EModBrowserState state) // 0x10724C20
{
	mangled_x86(MANGLED_TODO, "?SetStateInternal@CModBrowserStateManager@@AAEXW4EModBrowserState@@@Z");
	// EModBrowserState state;
	// function call : void ()
	// function call : void ()
	todo("implement");
	_sub_10724C20(this, state);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void CEventSink<enum EModBrowserAbortReason>::PostEvent(EModBrowserAbortReason);
