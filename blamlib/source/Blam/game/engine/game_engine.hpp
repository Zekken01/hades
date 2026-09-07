#ifndef __BLAM_GAME_ENGINE_GAME_ENGINE_HPP__
#define __BLAM_GAME_ENGINE_GAME_ENGINE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct c_game_engine;
struct real_rgb_color;
struct s_game_engine_status_response;
struct s_local_game_engine_globals;
struct s_tag_reference;

/* ---------- constants */

enum e_game_engine_type
{
	_game_engine_type_none = 0,
	_game_engine_type_ctf,
	_game_engine_type_slayer,
	_game_engine_type_oddball,
	_game_engine_type_koth,
	_game_engine_type_sandbox,
	_game_engine_type_vip,
	_game_engine_type_juggernaut,
	_game_engine_type_territories,
	_game_engine_type_assault,
	_game_engine_type_infection,
	k_number_of_game_engine_types,
};

/* ---------- definitions */

#pragma pack(push, 4)
struct s_game_engine_status_response
{
	unsigned short flags; // 0x0
	unsigned char __pad0[2]; // 0x2
	c_enum<enum e_game_engine_status,short> state; // 0x4
	unsigned char __pad1[2]; // 0x6
	unsigned long ffa_message; // 0x8
	unsigned long team_message; // 0xC
	s_tag_reference unused; // 0x10
	s_game_engine_status_response(s_game_engine_status_response &); /* compiler_generated() */
	s_game_engine_status_response(s_game_engine_status_response const &); /* compiler_generated() */
	s_game_engine_status_response(); /* compiler_generated() */
	s_game_engine_status_response &operator=(s_game_engine_status_response &); /* compiler_generated() */
	s_game_engine_status_response &operator=(s_game_engine_status_response const &); /* compiler_generated() */
	unsigned char __pad2[4]; // 0x20
};
#pragma pack(pop)
static_assert(sizeof(s_game_engine_status_response) == 36, "Invalid s_game_engine_status_response size");

#pragma pack(push, 4)
struct s_local_game_engine_globals
{
	public:
	struct s_player_state
	{
		long state; // 0x0
		long field_4; // 0x4
		long field_8; // 0x8
	};
	static_assert(sizeof(s_player_state) == 12, "Invalid s_player_state size");
	public:
	unsigned char __pad0[20]; // 0x0
	s_player_state player_states[4]; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_local_game_engine_globals) == 68, "Invalid s_local_game_engine_globals size");

struct c_game_engine
{
	virtual e_game_engine_type get_type() = 0;
	c_game_engine(c_game_engine &); /* compiler_generated() */
	c_game_engine(c_game_engine const &); /* compiler_generated() */
	c_game_engine(); /* compiler_generated() */
	c_game_engine &operator=(c_game_engine &); /* compiler_generated() */
	c_game_engine &operator=(c_game_engine const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine) == 4, "Invalid c_game_engine size");

/* ---------- prototypes */

extern __int32 game_engine_get_player_assists(unsigned long player_index);
extern __int32 game_engine_get_player_deaths(unsigned long player_index);
extern __int32 game_engine_get_player_kills(unsigned long player_index);
extern __int32 game_engine_get_player_score(unsigned long player_index);
extern long game_engine_get_team_designator(long player_index);
extern void game_engine_get_team_color(real_rgb_color *color, long team);
extern char const *game_engine_type_get_string(e_game_engine_type type);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_ENGINE_GAME_ENGINE_HPP__
