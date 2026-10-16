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

void CServerConnectStateManager::RegisterStateHandler(EServerConnectState state, std::shared_ptr<CServerConnectStateHandler> const &handler) // 0x10B0D750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterStateHandler@CServerConnectStateManager@@QAEXW4EServerConnectState@@ABV?$shared_ptr@VCServerConnectStateHandler@@@std@@@Z");
#line 61

	#line 59 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateManager.cpp"
		assert(m_stateHandlers.find(state) == m_stateHandlers.end());
		#line 65 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateManager.cpp"
	m_stateHandlers.insert(std::make_pair(state, handler));
	handler->SetManager(this);
}

void CServerConnectStateManager::Update() // 0x10B0DC10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CServerConnectStateManager@@QAEXXZ");
#line 76

	if (m_abortReason)
	{
		AbortEvent.PostEvent(m_abortReason);
		m_abortReason = (EServerConnectAbortReason)0;
		Complete();
	}
	if (m_requestedState)
	{
		if (bool it = m_stateHandlers.find(m_requestedState) != std::end(m_stateHandlers))
		{
			EServerConnectState newState = m_requestedState;
			m_requestedState = (EServerConnectState)0;
			SetStateInternal(newState);
		}
		else
		{
			#line 91 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateManager.cpp"
				assert(!"CServerConnectStateManager :: transitioned to unknown state");
				#line 96 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateManager.cpp"
		}
	}
	if (m_currentHandler)
		m_currentHandler->OnUpdate();
}

void CServerConnectStateManager::RequestStateChange(EServerConnectState state) // 0x10B0D9D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RequestStateChange@CServerConnectStateManager@@QAEXW4EServerConnectState@@@Z");

	m_requestedState = state;
}

void CServerConnectStateManager::Abort(EServerConnectAbortReason reason) // 0x10B0D610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Abort@CServerConnectStateManager@@QAEXW4EServerConnectAbortReason@@@Z");

	m_abortReason = reason;
}

void CServerConnectStateManager::Complete() // 0x10B0D640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Complete@CServerConnectStateManager@@QAEXXZ");

	SetStateInternal((EServerConnectState)0);
}

void CServerConnectStateManager::SetStateInternal(EServerConnectState state) // 0x10B0DA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetStateInternal@CServerConnectStateManager@@AAEXW4EServerConnectState@@@Z");

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

template void CEventSink<enum EServerConnectAbortReason>::PostEvent(EServerConnectAbortReason);
