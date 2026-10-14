#ifndef __MODS_MAP_LOAD_CRASH_RECOVERY_HELPER_HPP__
#define __MODS_MAP_LOAD_CRASH_RECOVERY_HELPER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <string>

/* ---------- forward declarations */

class c_map_load_crash_recovery_helper;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class c_map_load_crash_recovery_helper
{
public:
	void map_load_start();
	void map_load_end();
	void tick();
	void shutdown();
	void dirty_disk();
private:
	unsigned __int32 m_map_load_end_time = 0xFFFFFFFF; // 0x0
	bool m_dirty_disked = false; // 0x4
	std::string kMapLoadTempFileName = ""; // 0x8
public:
	c_map_load_crash_recovery_helper(c_map_load_crash_recovery_helper &); /* compiler_generated() */
	c_map_load_crash_recovery_helper(c_map_load_crash_recovery_helper const &); /* compiler_generated() */
	_inline c_map_load_crash_recovery_helper() = default; /* compiler_generated() */
	_inline ~c_map_load_crash_recovery_helper(); /* compiler_generated() */
	c_map_load_crash_recovery_helper &operator=(c_map_load_crash_recovery_helper &); /* compiler_generated() */
	c_map_load_crash_recovery_helper &operator=(c_map_load_crash_recovery_helper const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_map_load_crash_recovery_helper) == 36, "Invalid c_map_load_crash_recovery_helper size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_MAP_LOAD_CRASH_RECOVERY_HELPER_HPP__
