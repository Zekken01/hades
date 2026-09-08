#ifndef __MODS_NEW_MODLISTENERSET_HPP__
#define __MODS_NEW_MODLISTENERSET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "mods/new/IModManager.hpp"

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <vector>

/* ---------- forward declarations */

class IModListener;
class ModListenerSet;

/* ---------- constants */

/* ---------- definitions */

class ModListenerSet
{
public:
	_inline void Add(IModListener *listener);
	_inline void Remove(IModListener *listener);
private:
	std::vector<IModListener *> m_listeners; // 0x0
	std::vector<IModListener *> m_dirtyListeners; // 0x10
	bool m_dirty; // 0x20
	unsigned char __pad0[3]; // 0x21
	std::shared_mutex m_lock; // 0x24
public:
	_inline ModListenerSet(); /* compiler_generated() */
	_inline ~ModListenerSet(); /* compiler_generated() */
};
static_assert(sizeof(ModListenerSet) == 40, "Invalid ModListenerSet size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern void _sub_107919F0(ModListenerSet *const, IModListener *);
_inline void ModListenerSet::Add(IModListener *listener) // 0x107919F0
{
	mangled_x86(MANGLED_TODO, "?Add@ModListenerSet@@QAEXPAVIModListener@@@Z");
	// static ...; // 0x10791BC0
	// static ...; // 0x10791BB8
	// ModListenerSet *const this;
	// IModListener *listener;
	// std::scoped_lock<std::shared_mutex> lock;
	todo("implement");
	_sub_107919F0(this, listener);
}

_extern void _sub_10791F40(ModListenerSet *const, IModListener *);
_inline void ModListenerSet::Remove(IModListener *listener) // 0x10791F40
{
	mangled_x86(MANGLED_TODO, "?Remove@ModListenerSet@@QAEXPAVIModListener@@@Z");
	// static ...; // 0x10791FF8
	// static ...; // 0x10791FF0
	// ModListenerSet *const this;
	// IModListener *listener;
	// std::scoped_lock<std::shared_mutex> lock;
	todo("implement");
	_sub_10791F40(this, listener);
}

/* ---------- private code */

#endif // __MODS_NEW_MODLISTENERSET_HPP__
