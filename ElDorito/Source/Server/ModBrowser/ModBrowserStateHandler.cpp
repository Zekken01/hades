/* ---------- headers */

#include "Server/ModBrowser/ModBrowserStateHandler.hpp"
#include "hades/hades.h"

#include "Server/ModBrowser/ModBrowserStateManager.hpp"

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
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>

/* ---------- forward declarations */

class CModBrowserStateHandler;
class CModBrowserStateManager;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

CModBrowserStateManager *CModBrowserStateHandler::GetManager() // 0x10721C00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetManager@CModBrowserStateHandler@@QAEPAVCModBrowserStateManager@@XZ");
	// CModBrowserStateHandler *const this;

	return m_manager;
}

_extern void _sub_10721CA0(CModBrowserStateHandler *const, CModBrowserStateManager *);
void CModBrowserStateHandler::SetManager(CModBrowserStateManager *manager) // 0x10721CA0
{
	mangled_x86(MANGLED_TODO, "?SetManager@CModBrowserStateHandler@@QAEXPAVCModBrowserStateManager@@@Z");
	// CModBrowserStateManager *manager;
	todo("implement");
	_sub_10721CA0(this, manager);
}

_extern void _sub_10721C30(CModBrowserStateHandler *const, EModBrowserState);
void CModBrowserStateHandler::RequestStateChange(EModBrowserState state) // 0x10721C30
{
	mangled_x86(MANGLED_TODO, "?RequestStateChange@CModBrowserStateHandler@@IAEXW4EModBrowserState@@@Z");
	// EModBrowserState state;
	todo("implement");
	_sub_10721C30(this, state);
}

_extern void _sub_10721B40(CModBrowserStateHandler *const, EModBrowserAbortReason);
void CModBrowserStateHandler::Abort(EModBrowserAbortReason reason) // 0x10721B40
{
	mangled_x86(MANGLED_TODO, "?Abort@CModBrowserStateHandler@@IAEXW4EModBrowserAbortReason@@@Z");
	// EModBrowserAbortReason reason;
	todo("implement");
	_sub_10721B40(this, reason);
}

_extern void _sub_10721BB0(CModBrowserStateHandler *const);
void CModBrowserStateHandler::Complete() // 0x10721BB0
{
	mangled_x86(MANGLED_TODO, "?Complete@CModBrowserStateHandler@@IAEXXZ");
	// CModBrowserStateHandler *const this;
	todo("implement");
	_sub_10721BB0(this);
}

/* ---------- private code */
