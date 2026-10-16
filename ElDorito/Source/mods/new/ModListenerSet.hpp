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
	_inline void Remove(IModListener *listener); template<typename t_method, typename... t_arguments> void Notify(t_method &&method, t_arguments &&...arguments) { std::shared_lock<std::shared_mutex> lock(m_lock); if (m_dirty) { m_listeners = m_dirtyListeners; m_dirty = false; } lock.unlock(); for (auto listener : m_listeners) (listener->*method)(std::forward<t_arguments &&>(arguments)...); }  // hades: added for ModManager notifications
private:
	std::vector<IModListener *> m_listeners; // 0x0
	std::vector<IModListener *> m_dirtyListeners; // 0x10
	bool m_dirty = false; // 0x20
	unsigned char __pad0[3]; // 0x21
	std::shared_mutex m_lock; // 0x24
public:
	_inline ModListenerSet() = default; /* compiler_generated() */
	_inline ~ModListenerSet(); /* compiler_generated() */
};
static_assert(sizeof(ModListenerSet) == 40, "Invalid ModListenerSet size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline void ModListenerSet::Add(IModListener *listener) // 0x107919F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Add@ModListenerSet@@QAEXPAVIModListener@@@Z");

	std::scoped_lock<std::shared_mutex> lock(m_lock);
	if (std::find(m_listeners.begin(), m_listeners.end(), listener) != m_listeners.end())
		return;
	m_dirtyListeners.push_back(listener);
	m_dirty = true;
}

inline void ModListenerSet::Remove(IModListener *listener) // 0x10791F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Remove@ModListenerSet@@QAEXPAVIModListener@@@Z");

	std::scoped_lock<std::shared_mutex> lock(m_lock);
	std::erase(m_dirtyListeners, listener);
	m_dirty = true;
}

/* ---------- private code */

#endif // __MODS_NEW_MODLISTENERSET_HPP__
