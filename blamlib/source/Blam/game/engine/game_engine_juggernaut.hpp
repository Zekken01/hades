#ifndef __BLAM_GAME_ENGINE_GAME_ENGINE_JUGGERNAUT_HPP__
#define __BLAM_GAME_ENGINE_GAME_ENGINE_JUGGERNAUT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/tls.hpp"

#include "Blam/game/game_engine_area_set.hpp"
#include "Blam/game/game_engine_globals.hpp"

/* ---------- forward declarations */

struct c_area;
struct s_juggernaut_globals;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_juggernaut_globals
{
	unsigned long juggernaut_player_index; // 0x0
	short next_juggernaut_delay_seconds; // 0x4
	bool juggernaut_visited_zone; // 0x6
	long next_juggernaut_timer; // 0x8
	c_area_set<c_area,12> goal_zones; // 0xC
};
#pragma pack(pop)
static_assert(sizeof(s_juggernaut_globals) == 1228, "Invalid s_juggernaut_globals size");

/* ---------- prototypes */

extern _inline s_juggernaut_globals *get_juggernaut_globals();

/* ---------- globals */

/* ---------- public code */

_inline s_juggernaut_globals *get_juggernaut_globals() // 0x10CB3A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_juggernaut_globals@@YAPAUs_juggernaut_globals@@XZ");

	return reinterpret_cast<s_juggernaut_globals *>(tls_getd().game_engine_globals->engine_storage);
}

/* ---------- private code */

#endif // __BLAM_GAME_ENGINE_GAME_ENGINE_JUGGERNAUT_HPP__
