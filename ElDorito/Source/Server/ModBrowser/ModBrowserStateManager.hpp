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

// CModBrowserStateManager is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline SModBrowserState &CModBrowserStateManager::GetStateMutable() // 0x1070C420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetStateMutable@CModBrowserStateManager@@QAEAAUSModBrowserState@@XZ");
	// CModBrowserStateManager *const this;

	return *(SModBrowserState *)m_state;
}

_inline SModBrowserState const &CModBrowserStateManager::GetState() const // 0x10717380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetState@CModBrowserStateManager@@QBEABUSModBrowserState@@XZ");
	// CModBrowserStateManager const *const this;

	return *(SModBrowserState const *)m_state;
}

_inline bool CModBrowserStateManager::InProgress() const // 0x1070C450
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InProgress@CModBrowserStateManager@@QBE_NXZ");
	// CModBrowserStateManager const *const this;

	return !(m_currentHandler == nullptr);
}

/* ---------- private code */

#endif // __SERVER_MODBROWSER_MODBROWSERSTATEMANAGER_HPP__
