/* ---------- headers */

#include "Server/Connect/ServerConnectStateHandler.hpp"
#include "hades/hades.h"

#include "Server/Connect/ServerConnectStateManager.hpp"

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

class CServerConnectStateHandler;
class CServerConnectStateManager;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern CServerConnectStateManager *_sub_10B0A9E0(CServerConnectStateHandler *const);
CServerConnectStateManager *CServerConnectStateHandler::GetManager() // 0x10B0A9E0
{
	mangled_x86(MANGLED_TODO, "?GetManager@CServerConnectStateHandler@@QAEPAVCServerConnectStateManager@@XZ");
	// CServerConnectStateHandler *const this;
	todo("implement");
	CServerConnectStateManager * __result = _sub_10B0A9E0(this);
	return __result;
}

_extern void _sub_10B0AA80(CServerConnectStateHandler *const, CServerConnectStateManager *);
void CServerConnectStateHandler::SetManager(CServerConnectStateManager *manager) // 0x10B0AA80
{
	mangled_x86(MANGLED_TODO, "?SetManager@CServerConnectStateHandler@@QAEXPAVCServerConnectStateManager@@@Z");
	// CServerConnectStateManager *manager;
	todo("implement");
	_sub_10B0AA80(this, manager);
}

_extern void _sub_10B0AA10(CServerConnectStateHandler *const, EServerConnectState);
void CServerConnectStateHandler::RequestStateChange(EServerConnectState state) // 0x10B0AA10
{
	mangled_x86(MANGLED_TODO, "?RequestStateChange@CServerConnectStateHandler@@IAEXW4EServerConnectState@@@Z");
	// EServerConnectState state;
	todo("implement");
	_sub_10B0AA10(this, state);
}

_extern void _sub_10B0A920(CServerConnectStateHandler *const, EServerConnectAbortReason);
void CServerConnectStateHandler::Abort(EServerConnectAbortReason reason) // 0x10B0A920
{
	mangled_x86(MANGLED_TODO, "?Abort@CServerConnectStateHandler@@IAEXW4EServerConnectAbortReason@@@Z");
	// EServerConnectAbortReason reason;
	todo("implement");
	_sub_10B0A920(this, reason);
}

_extern void _sub_10B0A990(CServerConnectStateHandler *const);
void CServerConnectStateHandler::Complete() // 0x10B0A990
{
	mangled_x86(MANGLED_TODO, "?Complete@CServerConnectStateHandler@@IAEXXZ");
	// CServerConnectStateHandler *const this;
	todo("implement");
	_sub_10B0A990(this);
}

/* ---------- private code */
