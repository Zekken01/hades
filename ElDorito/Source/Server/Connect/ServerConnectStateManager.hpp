#ifndef __SERVER_CONNECT_SERVERCONNECTSTATEMANAGER_HPP__
#define __SERVER_CONNECT_SERVERCONNECTSTATEMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectStateHandler.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

class CServerConnectStateHandler;
class CServerConnectStateManager;
struct SServerConnectState;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class CServerConnectStateManager
{
public:
	CEventSink<enum EServerConnectAbortReason> AbortEvent; // 0x0
private:
	std::mutex m_mutex; // 0x14
	SServerConnectState m_state; // 0x44
	EServerConnectState m_currentState; // 0xF8
	EServerConnectState m_requestedState; // 0xFC
	std::shared_ptr<CServerConnectStateHandler> m_currentHandler; // 0x100
	std::unordered_map<enum EServerConnectState,std::shared_ptr<CServerConnectStateHandler> > m_stateHandlers; // 0x108
	EServerConnectAbortReason m_abortReason; // 0x130
public:
	void RegisterStateHandler(EServerConnectState state, std::shared_ptr<CServerConnectStateHandler> const &handler);
	void RequestStateChange(EServerConnectState state);
	void Update();
	void Abort(EServerConnectAbortReason reason);
	void Complete();
	_inline SServerConnectState &GetStateMutable();
	_inline SServerConnectState const &GetState() const;
	_inline bool InProgress() const;
private:
	void SetStateInternal(EServerConnectState state);
public:
	_inline CServerConnectStateManager(); /* compiler_generated() */
	_inline ~CServerConnectStateManager(); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(CServerConnectStateManager) == 308, "Invalid CServerConnectStateManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline SServerConnectState &CServerConnectStateManager::GetStateMutable() // 0x10907590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetStateMutable@CServerConnectStateManager@@QAEAAUSServerConnectState@@XZ");
	// CServerConnectStateManager *const this;

	return m_state;
}

_inline SServerConnectState const &CServerConnectStateManager::GetState() const // 0x10907560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetState@CServerConnectStateManager@@QBEABUSServerConnectState@@XZ");
	// CServerConnectStateManager const *const this;

	return m_state;
}

_inline bool CServerConnectStateManager::InProgress() const // 0x10B07950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InProgress@CServerConnectStateManager@@QBE_NXZ");
	// CServerConnectStateManager const *const this;

	return !(m_currentHandler == nullptr);
}

/* ---------- private code */

#endif // __SERVER_CONNECT_SERVERCONNECTSTATEMANAGER_HPP__
