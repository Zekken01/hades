#ifndef __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_CONNECT_HPP__
#define __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_CONNECT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Server/Connect/ServerConnectStateHandler.hpp"

/* ---------- forward declarations */

class CServerConnectStateHandler;
class CServerConnectStateHandler_Connect;

/* ---------- constants */

/* ---------- definitions */

class CServerConnectStateHandler_Connect :
	public CServerConnectStateHandler
{
private:
	virtual void OnEnter();
	virtual void OnExit();
	virtual void OnUpdate();
public:
	CServerConnectStateHandler_Connect(CServerConnectStateHandler_Connect &); /* compiler_generated() */
	CServerConnectStateHandler_Connect(CServerConnectStateHandler_Connect const &); /* compiler_generated() */
	_inline CServerConnectStateHandler_Connect(); /* compiler_generated() */
	CServerConnectStateHandler_Connect &operator=(CServerConnectStateHandler_Connect &); /* compiler_generated() */
	CServerConnectStateHandler_Connect &operator=(CServerConnectStateHandler_Connect const &); /* compiler_generated() */
};
static_assert(sizeof(CServerConnectStateHandler_Connect) == 8, "Invalid CServerConnectStateHandler_Connect size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_CONNECT_HPP__
