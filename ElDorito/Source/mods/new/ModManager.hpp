#ifndef __MODS_NEW_MODMANAGER_HPP__
#define __MODS_NEW_MODMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/new/Mod.hpp"
#include "mods/new/ModListenerSet.hpp"
#include "mods/new/ModSessionManager.hpp"

#include <thread>

/* ---------- forward declarations */

class IMod;
class IModListener;
class IModManager;
class Mod;
class ModListenerSet;
class ModManager;
class ModSessionManager;

/* ---------- constants */

/* ---------- definitions */

class ModManager :
	public IModManager,
	private Mod::IClient
{
public:
	static bool const kDebugForceBlocking;
	ModManager();
	virtual ~ModManager();
	virtual Ref<IMod> GetModShared(EModIndex index) const;
	virtual IMod *GetMod(EModIndex index) const;
	virtual EModResult SetMod(EModIndex index, char const *filename, bool async);
	virtual EModResult SetModCache(EModIndex index, __int32 cacheIndex, bool async);
	virtual void AddListener(IModListener *listener);
	virtual void RemoveListener(IModListener *listener);
	void SetMainThread();
	bool IsMainThread() const;
	virtual void Tick();
private:
	virtual void OnModLoadStateChanged(Mod *mod);
	std::thread::id m_mainThreadId; // 0x8
	Ref<Mod> m_mods[2]; // 0xC
	ModListenerSet m_listeners; // 0x14
	ModSessionManager m_sessionManager; // 0x3C
};
static_assert(sizeof(ModManager) == 96, "Invalid ModManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_NEW_MODMANAGER_HPP__
