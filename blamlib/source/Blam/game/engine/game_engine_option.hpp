#ifndef __BLAM_GAME_ENGINE_GAME_ENGINE_OPTION_HPP__
#define __BLAM_GAME_ENGINE_GAME_ENGINE_OPTION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_player_traits.hpp"

/* ---------- forward declarations */

struct c_game_engine_map_override_options;
struct c_game_engine_miscellaneous_options;
struct c_game_engine_respawn_options;
struct c_game_engine_team_options;
struct c_player_traits;

/* ---------- constants */

/* ---------- definitions */

struct c_game_engine_miscellaneous_options
{
	public:
	enum e_flags
	{
		_teams_enabled_bit = 0,
	};
	public:
	_inline bool teams_enabled() const;
	c_flags<enum e_flags,unsigned char> flags; // 0x0
	unsigned char time_limit_in_minutes; // 0x1
	unsigned char round_count; // 0x2
	unsigned char early_victory_win_count; // 0x3
	c_game_engine_miscellaneous_options(c_game_engine_miscellaneous_options &); /* compiler_generated() */
	c_game_engine_miscellaneous_options(c_game_engine_miscellaneous_options const &); /* compiler_generated() */
	c_game_engine_miscellaneous_options(); /* compiler_generated() */
	c_game_engine_miscellaneous_options &operator=(c_game_engine_miscellaneous_options &); /* compiler_generated() */
	c_game_engine_miscellaneous_options &operator=(c_game_engine_miscellaneous_options const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine_miscellaneous_options) == 4, "Invalid c_game_engine_miscellaneous_options size");

struct c_game_engine_team_options
{
	unsigned short team_flags; // 0x0
};
static_assert(sizeof(c_game_engine_team_options) == 2, "Invalid c_game_engine_team_options size");

struct c_game_engine_respawn_options
{
	unsigned char flags; // 0x0
	unsigned char lives_per_round; // 0x1
	unsigned char team_lives_per_round; // 0x2
	unsigned char respawn_time; // 0x3
	unsigned char suicide_penalty; // 0x4
	unsigned char betrayal_penalty; // 0x5
	unsigned char unknown_penalty; // 0x6
	unsigned char respawn_growth; // 0x7
	unsigned char respawn_traits_duration; // 0x8
	unsigned char __pad0[3]; // 0x9
	c_player_traits player_traits; // 0xC
};
static_assert(sizeof(c_game_engine_respawn_options) == 40, "Invalid c_game_engine_respawn_options size");

#pragma pack(push, 4)
struct c_game_engine_map_override_options
{
	unsigned long flags; // 0x0
	c_player_traits base_player_traits; // 0x4
	unsigned short weapon_set_identifier; // 0x20
	unsigned short vehicle_set_identifier; // 0x22
	c_player_traits red_traits; // 0x24
	c_player_traits blue_traits; // 0x40
	c_player_traits yellow_traits; // 0x5C
	unsigned char red_traits_duration; // 0x78
	unsigned char blue_traits_duration; // 0x79
	unsigned char yellow_traits_duration; // 0x7A
	unsigned char __pad0[1]; // 0x7B
};
#pragma pack(pop)
static_assert(sizeof(c_game_engine_map_override_options) == 124, "Invalid c_game_engine_map_override_options size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline bool c_game_engine_miscellaneous_options::teams_enabled() const // 0x1092D000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?teams_enabled@c_game_engine_miscellaneous_options@@QBE_NXZ");
	// c_game_engine_miscellaneous_options const *const this;

	return flags.test(_teams_enabled_bit);
}

/* ---------- private code */

#endif // __BLAM_GAME_ENGINE_GAME_ENGINE_OPTION_HPP__
