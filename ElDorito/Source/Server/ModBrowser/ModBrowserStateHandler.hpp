#ifndef __SERVER_MODBROWSER_MODBROWSERSTATEHANDLER_HPP__
#define __SERVER_MODBROWSER_MODBROWSERSTATEHANDLER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Server/ModBrowser/ModBrowserStateManager.hpp"

/* ---------- forward declarations */

class CModBrowserStateHandler;
class CModBrowserStateManager;

/* ---------- constants */

/* ---------- definitions */

class CModBrowserStateHandler
{
public:
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void OnUpdate() = 0;
	CModBrowserStateManager *GetManager();
	void SetManager(CModBrowserStateManager *manager);
protected:
	void RequestStateChange(EModBrowserState state);
	void Abort(EModBrowserAbortReason reason);
	void Complete();
private:
	CModBrowserStateManager *m_manager; // 0x4
public:
	CModBrowserStateHandler(CModBrowserStateHandler &); /* compiler_generated() */
	CModBrowserStateHandler(CModBrowserStateHandler const &); /* compiler_generated() */
	_inline CModBrowserStateHandler() = default; /* compiler_generated() */
	CModBrowserStateHandler &operator=(CModBrowserStateHandler &); /* compiler_generated() */
	CModBrowserStateHandler &operator=(CModBrowserStateHandler const &); /* compiler_generated() */
};
static_assert(sizeof(CModBrowserStateHandler) == 8, "Invalid CModBrowserStateHandler size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_MODBROWSER_MODBROWSERSTATEHANDLER_HPP__
