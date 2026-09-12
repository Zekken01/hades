#ifndef __SERVER_CONNECT_SERVERCONNECT_HPP__
#define __SERVER_CONNECT_SERVERCONNECT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectStateManager.hpp"

#include <memory>

/* ---------- forward declarations */

class CServerConnectStateManager;
struct CServerConnectManager;
struct SServerConnectOptions;

/* ---------- constants */

/* ---------- definitions */

struct CServerConnectManager :
	public Utils::Singleton<CServerConnectManager>
{
	void Initialize();
	void Update();
	bool ConnectToServer(SServerConnectOptions const &options);
private:
	void OnConnectionAborted(EServerConnectAbortReason reason);
	std::shared_ptr<CServerConnectStateManager> m_stateManager; // 0x0
public:
	_inline CServerConnectManager() = default; /* compiler_generated() */
	~CServerConnectManager(); /* compiler_generated() */
};
static_assert(sizeof(CServerConnectManager) == 8, "Invalid CServerConnectManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_CONNECT_SERVERCONNECT_HPP__
