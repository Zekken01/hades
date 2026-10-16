#ifndef __BLAM_GAME_GAME_ENGINE_CANDY_MONITOR_HPP__
#define __BLAM_GAME_GAME_ENGINE_CANDY_MONITOR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct c_candy_monitor;
struct c_candy_monitor_manager;
struct c_candy_spawner;

/* ---------- constants */

/* ---------- definitions */

struct c_candy_monitor
{
	long m_spawned_object_index; // 0x0
	unsigned short m_abandoned_timer; // 0x4
	bool m_disturbed_from_initial_placement; // 0x6
	short m_unknown_time; // 0x8
};
static_assert(sizeof(c_candy_monitor) == 12, "Invalid c_candy_monitor size");
static_assert(offsetof(c_candy_monitor, m_unknown_time) == 0x8, "c_candy_monitor::m_unknown_time moved when its reconstructed padding was removed");

struct c_candy_spawner
{
	unsigned char flags; // 0x0
	long m_map_variant_index; // 0x4
	long m_spawned_object_index; // 0x8
	short m_respawn_timer; // 0xC
	unsigned short m_candy_flags; // 0xE
	static void (*const spawn_object)(void *, bool);
};
static_assert(sizeof(c_candy_spawner) == 16, "Invalid c_candy_spawner size");
static_assert(offsetof(c_candy_spawner, m_map_variant_index) == 0x4, "c_candy_spawner::m_map_variant_index moved when its reconstructed padding was removed");

struct c_candy_monitor_manager
{
	c_candy_spawner m_candy_spawners[512]; // 0x0
	c_candy_monitor m_candy_monitors[512]; // 0x2000
	_inline void reset();
};
static_assert(sizeof(c_candy_monitor_manager) == 14336, "Invalid c_candy_monitor_manager size");

/* ---------- prototypes */

extern c_candy_monitor_manager *get_candy_monitor_manager();

/* ---------- globals */

/* ---------- public code */

inline void c_candy_monitor_manager::reset() // 0x106FA3C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reset@c_candy_monitor_manager@@QAEXXZ");

	((void(__thiscall *)(void *))0x58f790)(this);
}

/* ---------- private code */

#endif // __BLAM_GAME_GAME_ENGINE_CANDY_MONITOR_HPP__
