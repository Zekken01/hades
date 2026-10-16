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

void CModBrowserStateManager::RegisterStateHandler(EModBrowserState state, std::shared_ptr<CModBrowserStateHandler> const &handler) // 0x10724970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterStateHandler@CModBrowserStateManager@@QAEXW4EModBrowserState@@ABV?$shared_ptr@VCModBrowserStateHandler@@@std@@@Z");
#line 61

	#line 59 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateManager.cpp"
		assert(m_stateHandlers.find(state) == m_stateHandlers.end());
		#line 65 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateManager.cpp"
	m_stateHandlers.insert(std::make_pair(state, handler));
	handler->SetManager(this);
}

void CModBrowserStateManager::Update() // 0x10724E30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CModBrowserStateManager@@QAEXXZ");
#line 76

	if (m_abortReason)
	{
		AbortEvent.PostEvent(m_abortReason);
		m_abortReason = (EModBrowserAbortReason)0;
		Complete();
	}
	if (m_requestedState)
	{
		if (bool it = m_stateHandlers.find(m_requestedState) != std::end(m_stateHandlers))
		{
			EModBrowserState newState = m_requestedState;
			m_requestedState = (EModBrowserState)0;
			SetStateInternal(newState);
		}
		else
		{
			#line 91 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateManager.cpp"
				assert(!"CModBrowserStateManager :: transitioned to unknown state");
				#line 96 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateManager.cpp"
		}
	}
	if (m_currentHandler)
		m_currentHandler->OnUpdate();
}

void CModBrowserStateManager::RequestStateChange(EModBrowserState state) // 0x10724BF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RequestStateChange@CModBrowserStateManager@@QAEXW4EModBrowserState@@@Z");

	m_requestedState = state;
}

void CModBrowserStateManager::Abort(EModBrowserAbortReason reason) // 0x10724830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Abort@CModBrowserStateManager@@QAEXW4EModBrowserAbortReason@@@Z");

	m_abortReason = reason;
}

void CModBrowserStateManager::Complete() // 0x10724860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Complete@CModBrowserStateManager@@QAEXXZ");

	SetStateInternal((EModBrowserState)0);
}

void CModBrowserStateManager::SetStateInternal(EModBrowserState state) // 0x10724C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetStateInternal@CModBrowserStateManager@@AAEXW4EModBrowserState@@@Z");

	if (m_currentHandler)
		m_currentHandler->OnExit();

	m_currentHandler = state ? m_stateHandlers[state] : nullptr;

	if (m_currentHandler)
		m_currentHandler->OnEnter();
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void CEventSink<enum EModBrowserAbortReason>::PostEvent(EModBrowserAbortReason);
