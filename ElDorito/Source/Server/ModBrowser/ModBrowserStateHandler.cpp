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

	return m_manager;
}

void CModBrowserStateHandler::SetManager(CModBrowserStateManager *manager) // 0x10721CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetManager@CModBrowserStateHandler@@QAEXPAVCModBrowserStateManager@@@Z");

	m_manager = manager;
}

void CModBrowserStateHandler::RequestStateChange(EModBrowserState state) // 0x10721C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RequestStateChange@CModBrowserStateHandler@@IAEXW4EModBrowserState@@@Z");

	m_manager->RequestStateChange(state);
}

void CModBrowserStateHandler::Abort(EModBrowserAbortReason reason) // 0x10721B40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Abort@CModBrowserStateHandler@@IAEXW4EModBrowserAbortReason@@@Z");

	m_manager->Abort(reason);
}

void CModBrowserStateHandler::Complete() // 0x10721BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Complete@CModBrowserStateHandler@@IAEXXZ");

	m_manager->Complete();
}

/* ---------- private code */
