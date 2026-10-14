#ifndef __SERVER_MODBROWSER_MODBROWSERSTATEMANAGER_HPP__
#define __SERVER_MODBROWSER_MODBROWSERSTATEMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Server/ModBrowser/ModBrowserDefinitions.hpp"

/* ---------- forward declarations */

struct SModBrowserState;

/* ---------- constants */

/* ---------- definitions */

// hades: moved from hades/recovered_types.h so m_state can be the real SModBrowserState
class CModBrowserStateManager
{
public: CEventSink<enum EModBrowserAbortReason> AbortEvent; private: // 0x0  // hades: was unsigned char[20]; public like CServerConnectStateManager's
	std::mutex m_mutex; // 0x14
	SModBrowserState m_state = {}; // 0x44  // hades: was unsigned char[424]; aggregate-initialized like the original
	EModBrowserState m_currentState = {}; // 0x1EC
	EModBrowserState m_requestedState = {}; // 0x1F0
	std::shared_ptr<CModBrowserStateHandler> m_currentHandler; // 0x1F4  // hades: was unsigned char[8]
	std::unordered_map<enum EModBrowserState,std::shared_ptr<CModBrowserStateHandler> > m_stateHandlers; // 0x1FC  // hades: was unsigned char[40]
	EModBrowserAbortReason m_abortReason = {}; // 0x224
public:
	void Update();
	void Complete();
	void Abort(EModBrowserAbortReason);
	SModBrowserState const & GetState() const;
	void RequestStateChange(EModBrowserState);
	void RegisterStateHandler(EModBrowserState, std::shared_ptr<CModBrowserStateHandler> const &);
private:
	void SetStateInternal(EModBrowserState);
public:
	SModBrowserState & GetStateMutable();
	bool InProgress() const;
	CModBrowserStateManager() = default;  // hades: not user-provided, so make_shared value-initializes
	~CModBrowserStateManager();
};
static_assert32(sizeof(CModBrowserStateManager) == 552, "Invalid CModBrowserStateManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline SModBrowserState &CModBrowserStateManager::GetStateMutable() // 0x1070C420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetStateMutable@CModBrowserStateManager@@QAEAAUSModBrowserState@@XZ");
	// CModBrowserStateManager *const this;

	return m_state;
}

_inline SModBrowserState const &CModBrowserStateManager::GetState() const // 0x10717380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetState@CModBrowserStateManager@@QBEABUSModBrowserState@@XZ");
	// CModBrowserStateManager const *const this;

	return m_state;
}

_inline bool CModBrowserStateManager::InProgress() const // 0x1070C450
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InProgress@CModBrowserStateManager@@QBE_NXZ");
	// CModBrowserStateManager const *const this;

	return !(m_currentHandler == nullptr);
}

/* ---------- private code */

#endif // __SERVER_MODBROWSER_MODBROWSERSTATEMANAGER_HPP__
