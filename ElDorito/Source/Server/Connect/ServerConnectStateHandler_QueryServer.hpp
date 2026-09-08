#ifndef __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_QUERYSERVER_HPP__
#define __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_QUERYSERVER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Job/JobDefinitions.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectStateHandler.hpp"

#include <memory>
#include <mutex>
#include <string>
#include <vector>

/* ---------- forward declarations */

class CServerConnectStateHandler;
class CServerConnectStateHandler_QueryServer;
struct SJobCounter;
struct SQueryInfoServerArgs;
struct SQueryInfoServerData;
struct SServerConnectState;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct SQueryInfoServerArgs
{
	std::string hostname; // 0x0
	std::string password; // 0x1C
	__int32 port; // 0x38
	_inline SQueryInfoServerArgs(SQueryInfoServerArgs &&__that); /* compiler_generated() */
	_inline SQueryInfoServerArgs(SQueryInfoServerArgs const &__that); /* compiler_generated() */
	_inline SQueryInfoServerArgs(); /* compiler_generated() */
	_inline ~SQueryInfoServerArgs(); /* compiler_generated() */
	SQueryInfoServerArgs &operator=(SQueryInfoServerArgs &); /* compiler_generated() */
	SQueryInfoServerArgs &operator=(SQueryInfoServerArgs const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(SQueryInfoServerArgs) == 60, "Invalid SQueryInfoServerArgs size");

#pragma pack(push, 4)
struct SQueryInfoServerData
{
	bool success; // 0x0
	unsigned char __pad0[3]; // 0x1
	std::string serverName; // 0x4
	std::string serverHost; // 0x20
	std::string message; // 0x3C
	unsigned short gamePort; // 0x58
	unsigned short fileServerPort; // 0x5A
	unsigned char xnkid[16]; // 0x5C
	unsigned char xnaddr[16]; // 0x6C
	SQueryInfoServerData(SQueryInfoServerData &); /* compiler_generated() */
	SQueryInfoServerData(SQueryInfoServerData const &); /* compiler_generated() */
	_inline SQueryInfoServerData(); /* compiler_generated() */
	_inline ~SQueryInfoServerData(); /* compiler_generated() */
	_inline SQueryInfoServerData &operator=(SQueryInfoServerData &&__that); /* compiler_generated() */
	SQueryInfoServerData &operator=(SQueryInfoServerData const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(SQueryInfoServerData) == 124, "Invalid SQueryInfoServerData size");

class CServerConnectStateHandler_QueryServer :
	public CServerConnectStateHandler
{
private:
	virtual void OnEnter();
	virtual void OnExit();
	virtual void OnUpdate();
	EJobResult QueryInfoServerJobCallback(SQueryInfoServerArgs const &args);
	EJobResult QueryModsJobCallback(SQueryInfoServerArgs const &args);
	EJobResult ResolveAddressJobCallback(std::string const &hostname);
	std::mutex m_mutex; // 0x8
	SJobCounter m_jobCounter; // 0x38
	SQueryInfoServerData m_infoServerData; // 0x3C
	__int32 m_queryInfoServerResult; // 0xB8
	__int32 m_queryModsResult; // 0xBC
	__int32 m_addressLookupResult; // 0xC0
	unsigned __int32 m_addressLookupAddress; // 0xC4
	std::vector<SServerConnectState::SRequiredMod> m_requiredMods; // 0xC8
public:
	_inline CServerConnectStateHandler_QueryServer(); /* compiler_generated() */
	_inline ~CServerConnectStateHandler_QueryServer(); /* compiler_generated() */
};
static_assert(sizeof(CServerConnectStateHandler_QueryServer) == 216, "Invalid CServerConnectStateHandler_QueryServer size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_QUERYSERVER_HPP__
