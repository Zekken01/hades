#ifndef __SERVER_MODBROWSER_MODBROWSER_HPP__
#define __SERVER_MODBROWSER_MODBROWSER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Server/ModBrowser/ModBrowserDefinitions.hpp"
#include "Server/ModBrowser/ModBrowserStateManager.hpp"

#include <memory>

/* ---------- forward declarations */

class CModBrowserStateManager;
struct CModBrowserManager;
struct SModBrowserState;

/* ---------- constants */

/* ---------- definitions */

struct CModBrowserManager :
	public Utils::Singleton<CModBrowserManager>
{
	void Initialize();
	void Update();
	bool DownloadMod(SModBrowserState const &options);
private:
	void OnDownloadAborted(EModBrowserAbortReason reason);
	bool ShouldDownloadPackage(SModBrowserState::SRequestedMod const &package);
	std::shared_ptr<CModBrowserStateManager> m_stateManager; // 0x0
public:
	_inline CModBrowserManager() = default; /* compiler_generated() */
	~CModBrowserManager() = default; /* compiler_generated() */
};
static_assert(sizeof(CModBrowserManager) == 8, "Invalid CModBrowserManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_MODBROWSER_MODBROWSER_HPP__
