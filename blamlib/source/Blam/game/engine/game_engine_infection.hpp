#ifndef __BLAM_GAME_ENGINE_GAME_ENGINE_INFECTION_HPP__
#define __BLAM_GAME_ENGINE_GAME_ENGINE_INFECTION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/tls.hpp"

#include "Blam/game/game_engine_area_set.hpp"
#include "Blam/game/game_engine_globals.hpp"

/* ---------- forward declarations */

struct c_area;
struct s_infection_globals;

/* ---------- constants */

/* ---------- definitions */

struct s_infection_globals
{
	unsigned short zombie_bit_vector; // 0x0
	unsigned short first_zombie_bit_vector; // 0x2
	long save_haven_timer; // 0x4
	unsigned short zombie_team_bit_vector; // 0x8
	unsigned short players_in_safe_haven_bit_vector; // 0xA
	c_area_set<c_area,12> save_heaven_zones; // 0xC
	long player_unknown_count[16]; // 0x4CC
	long player_zombie_kill_count[16]; // 0x50C
	bool last_man_standing; // 0x54C
};
static_assert(sizeof(s_infection_globals) == 1360, "Invalid s_infection_globals size");

/* ---------- prototypes */

extern _inline s_infection_globals *get_infection_globals();

/* ---------- globals */

/* ---------- public code */

_inline s_infection_globals *get_infection_globals() // 0x10C25580
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_infection_globals@@YAPAUs_infection_globals@@XZ");
	// procedure flags: nofpo

	return reinterpret_cast<s_infection_globals *>(tls_getd().game_engine_globals->engine_storage);
}

/* ---------- private code */

#endif // __BLAM_GAME_ENGINE_GAME_ENGINE_INFECTION_HPP__
