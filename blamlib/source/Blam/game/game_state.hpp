#ifndef __BLAM_GAME_GAME_STATE_HPP__
#define __BLAM_GAME_GAME_STATE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/player_configuration.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct s_game_machine_options;
struct s_game_player_options;
struct s_machine_identifier;
struct s_player_configuration;
struct s_player_identifier;

/* ---------- constants */

/* ---------- definitions */

struct s_game_machine_options
{
	unsigned long valid_machine_mask; // 0x0
	s_static_array<s_machine_identifier,17> machine_identifiers; // 0x4
	unsigned char __pad0[20]; // 0x114
};
static_assert(sizeof(s_game_machine_options) == 296, "Invalid s_game_machine_options size");

struct s_game_player_options
{
	bool valid; // 0x0
	bool player_left_game; // 0x1
	short input_user_index; // 0x2
	short controller_index; // 0x4
	unsigned char __pad0[2]; // 0x6
	s_machine_identifier player_uid; // 0x8
	s_player_identifier player_identifier; // 0x18
	s_player_configuration configuration_data; // 0x20
	_inline s_game_player_options() = default; /* compiler_generated() */
};
static_assert(sizeof(s_game_player_options) == 5696, "Invalid s_game_player_options size");

/* ---------- prototypes */

extern void player_format_uid(char *string, unsigned long long id);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_GAME_STATE_HPP__
