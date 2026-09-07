#ifndef __BLAM_GAME_ENGINE_GAME_ENGINE_CTF_HPP__
#define __BLAM_GAME_ENGINE_GAME_ENGINE_CTF_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/game_engine_area_set.hpp"
#include "Blam/game/game_engine_globals.hpp"
#include "Blam/networking/session/network_session_membership.hpp"

/* ---------- forward declarations */

struct c_area;
struct s_ctf_engine_globals;

/* ---------- constants */

/* ---------- definitions */

struct s_ctf_engine_globals
{
	s_static_array<c_area_set<c_area,3>,9> defender_goal_zones; // 0x0
	s_static_array<c_area_set<c_area,3>,9> attacker_goal_zones; // 0xB1C
	bool field_1638; // 0x1638
	bool field_1639; // 0x1639
	unsigned char __pad0[2]; // 0x163A
	long defensive_team; // 0x163C
	long flag_swap_timer; // 0x1640
	long field_1644; // 0x1644
	unsigned short helper_flags; // 0x1648
	unsigned short unknown_flags; // 0x164A
	long touch_return_timers[9]; // 0x164C
	short flag_reset_timers[9]; // 0x1670
	char field_1682[9]; // 0x1682
	unsigned char __pad1[1]; // 0x168B
	long field_168C[7]; // 0x168C
	unsigned char flag_weapon_flags[9]; // 0x16A8
	unsigned char __pad2[1]; // 0x16B1
	short unknown_timers1[9]; // 0x16B2
	short unknown_timers2[9]; // 0x16C4
	short field_16D6; // 0x16D6
};
static_assert(sizeof(s_ctf_engine_globals) == 5848, "Invalid s_ctf_engine_globals size");

/* ---------- prototypes */

extern _inline s_ctf_engine_globals *get_ctf_globals();

/* ---------- globals */

/* ---------- public code */

extern s_ctf_engine_globals *_sub_109562B0();
_inline s_ctf_engine_globals *get_ctf_globals() // 0x109562B0
{
	mangled_x86(MANGLED_TODO, "?get_ctf_globals@@YAPAUs_ctf_engine_globals@@XZ");
	// procedure flags: nofpo
	todo("implement");
	s_ctf_engine_globals * __result = _sub_109562B0();
	return __result;
}

/* ---------- private code */

#endif // __BLAM_GAME_ENGINE_GAME_ENGINE_CTF_HPP__
