#ifndef __MODS_NEW_MODSESSIONMANAGER_HPP__
#define __MODS_NEW_MODSESSIONMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_parameter_mod.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/new/IModManager.hpp"

/* ---------- forward declarations */

class IMod;
class IModListener;
class IModManager;
class ModSessionManager;
struct s_session_mod_options;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class ModSessionManager :
	public IModListener
{
public:
	ModSessionManager(ModSessionManager const &); /* compiler_generated() */
	ModSessionManager(IModManager &modManager);
	virtual ~ModSessionManager();
	void Tick();
private:
	void CheckSession();
	bool HandleSessionModChanged(s_session_mod_options const &options);
	virtual void OnModChanged(EModIndex index, IMod *mod);
	IModManager &m_modManager; // 0x4
	unsigned char m_currentPakHash[20]; // 0x8
	bool m_valid; // 0x1C
	unsigned char __pad0[3]; // 0x1D
	unsigned __int32 m_lastCheckTime; // 0x20
};
#pragma pack(pop)
static_assert(sizeof(ModSessionManager) == 36, "Invalid ModSessionManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_NEW_MODSESSIONMANAGER_HPP__
