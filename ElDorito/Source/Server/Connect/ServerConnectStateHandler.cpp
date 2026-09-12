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

CServerConnectStateManager *CServerConnectStateHandler::GetManager() // 0x10B0A9E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetManager@CServerConnectStateHandler@@QAEPAVCServerConnectStateManager@@XZ");
	// CServerConnectStateHandler *const this;

	return static_cast<CServerConnectStateManager *>(m_manager);
}

void CServerConnectStateHandler::SetManager(CServerConnectStateManager *manager) // 0x10B0AA80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetManager@CServerConnectStateHandler@@QAEXPAVCServerConnectStateManager@@@Z");
	// CServerConnectStateManager *manager;

	m_manager = manager;
}

void CServerConnectStateHandler::RequestStateChange(EServerConnectState state) // 0x10B0AA10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RequestStateChange@CServerConnectStateHandler@@IAEXW4EServerConnectState@@@Z");
	// EServerConnectState state;

	static_cast<CServerConnectStateManager *>(m_manager)->RequestStateChange(state);
}

void CServerConnectStateHandler::Abort(EServerConnectAbortReason reason) // 0x10B0A920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Abort@CServerConnectStateHandler@@IAEXW4EServerConnectAbortReason@@@Z");
	// EServerConnectAbortReason reason;

	static_cast<CServerConnectStateManager *>(m_manager)->Abort(reason);
}

void CServerConnectStateHandler::Complete() // 0x10B0A990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Complete@CServerConnectStateHandler@@IAEXXZ");
	// CServerConnectStateHandler *const this;

	static_cast<CServerConnectStateManager *>(m_manager)->Complete();
}

/* ---------- private code */
