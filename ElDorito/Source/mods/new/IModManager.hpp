#ifndef __MODS_NEW_IMODMANAGER_HPP__
#define __MODS_NEW_IMODMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/cache_file_interface.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>

/* ---------- forward declarations */

class IMod;
class IModListener;
class IModManager;
struct c_cache_file_interface;

/* ---------- constants */

enum EModResult
{
	kSuccess = 0,
	kNotLoaded,
	kPakLoadFailed,
	kCacheLoadFailed,
	kPending,
	kNoModSet,
	kUnknownError,
};

/* ---------- definitions */

// c_mod_package is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

class IMod
{
public:
	virtual _inline ~IMod() = default; // 0x1078BD40
	virtual void AddRef() = 0;
	virtual void Release() = 0;
	virtual char const *GetFilename() const = 0;
	virtual bool GetPakIsLoading() const = 0;
	virtual bool GetCacheIsLoading() const = 0;
	virtual EModResult GetError() const = 0;
	virtual c_mod_package *GetPak(bool) const = 0;
	virtual std::shared_ptr<c_cache_file_interface> GetCache(bool) const = 0;
	IMod(IMod const &); /* compiler_generated() */
	_inline IMod(); /* compiler_generated() */
	IMod &operator=(IMod const &); /* compiler_generated() */
};
static_assert(sizeof(IMod) == 4, "Invalid IMod size");

class IModListener
{
public:
	virtual _inline ~IModListener() = default; // 0x10793DE0
	virtual _inline void OnModChanged(EModIndex index, IMod *mod);
	virtual _inline void OnModCacheChanged(EModIndex index, IMod *mod);
	virtual _inline void OnModLoadStateChangedAsync(EModIndex index, IMod *mod);
	IModListener(IModListener const &); /* compiler_generated() */
	_inline IModListener(); /* compiler_generated() */
	IModListener &operator=(IModListener const &); /* compiler_generated() */
};
static_assert(sizeof(IModListener) == 4, "Invalid IModListener size");

class IModManager
{
public:
	virtual _inline ~IModManager() = default; // 0x10791400
	virtual EModResult SetMod(EModIndex, char const *, bool) = 0;
	virtual EModResult SetModCache(EModIndex, __int32, bool) = 0;
	virtual IMod *GetMod(EModIndex) const = 0;
	virtual Ref<IMod> GetModShared(EModIndex) const = 0;
	virtual void AddListener(IModListener *) = 0;
	virtual void RemoveListener(IModListener *) = 0;
	virtual void Tick() = 0;
	char const *GetErrorName(EModResult);
	IModManager(IModManager const &); /* compiler_generated() */
	_inline IModManager(); /* compiler_generated() */
	IModManager &operator=(IModManager const &); /* compiler_generated() */
};
static_assert(sizeof(IModManager) == 4, "Invalid IModManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline void IModListener::OnModChanged(EModIndex index, IMod *mod) // 0x10794400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModChanged@IModListener@@UAEXW4EModIndex@@PAVIMod@@@Z");
	// IMod *mod;
}

_inline void IModListener::OnModCacheChanged(EModIndex index, IMod *mod) // 0x107943E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModCacheChanged@IModListener@@UAEXW4EModIndex@@PAVIMod@@@Z");
	// IMod *mod;
}

_inline void IModListener::OnModLoadStateChangedAsync(EModIndex index, IMod *mod) // 0x10794610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModLoadStateChangedAsync@IModListener@@UAEXW4EModIndex@@PAVIMod@@@Z");
	// IMod *mod;
}

/* ---------- private code */

#endif // __MODS_NEW_IMODMANAGER_HPP__
