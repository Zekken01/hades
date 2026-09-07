#ifndef __BLAM_SIMULATION_GAME_INTERFACE_SIMULATION_GAME_ENGINE_PLAYER_HPP__
#define __BLAM_SIMULATION_GAME_INTERFACE_SIMULATION_GAME_ENGINE_PLAYER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/engine/game_engine_player_traits.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"

/* ---------- forward declarations */

struct c_player_traits;
struct real_vector3d;
struct s_damage_reporting_info;
struct s_simulation_game_engine_player_state_data;
struct s_simulation_player_netdebug_data;

/* ---------- constants */

enum e_simulation_game_engine_player_components
{
	_simulation_game_engine_player_respawn_timer = 0,
	_simulation_game_engine_player_early_respawn,
	_simulation_game_engine_player_shield_traits,
	_simulation_game_engine_player_weapon_traits,
	_simulation_game_engine_player_movement_traits,
	_simulation_game_engine_player_appearance_traits,
	_simulation_game_engine_player_sensor_traits,
	_simulation_game_engine_player_waypoint_action,
	_simulation_game_engine_player_blocking_teleporter,
	_simulation_game_engine_player_netdebug,
	_simulation_game_engine_player_lives_remaining,
	_simulation_game_engine_player_last_betrayer,
	_simulation_game_engine_player_vehicle_entrance_ban,
	_simulation_game_engine_player_active_in_game,
	_simulation_game_engine_player_sitting_out,
	_simulation_game_engine_player_desired_respawn_player,
	_simulation_game_engine_player_control_aiming,
	_simulation_game_engine_player_character_type,
	_simulation_game_engine_player_consumable_supression,
	_simulation_game_engine_player_last_killer,
	_simulation_game_engine_player_extended_traits,
	k_number_of_simulation_game_engine_player_components,
};

/* ---------- definitions */

struct s_simulation_player_netdebug_data
{
	bool is_host; // 0x0
	unsigned char __pad0[1]; // 0x1
	short host_estimated_bps; // 0x2
	short host_transmission_rate; // 0x4
	short host_transmission_bps; // 0x6
	short rtt_average; // 0x8
	short packet_rate_average; // 0xA
	short bandwidth_average; // 0xC
	short packet_loss_average; // 0xE
};
static_assert(sizeof(s_simulation_player_netdebug_data) == 16, "Invalid s_simulation_player_netdebug_data size");

#pragma pack(push, 4)
struct s_simulation_game_engine_player_state_data
{
	char waypoint_action; // 0x0
	bool initial_spawn; // 0x1
	unsigned char __pad0[6]; // 0x2
	short respawn_timer; // 0x8
	unsigned char __pad1[2]; // 0xA
	real_point3d unused_dead_location; // 0xC
	bool early_respawn_requested; // 0x18
	unsigned char __pad2[1]; // 0x19
	c_player_traits player_traits; // 0x1A
	bool blocking_teleporter; // 0x36
	unsigned char __pad3[1]; // 0x37
	short lives_remaining; // 0x38
	unsigned char __pad4[2]; // 0x3A
	long last_betrayer_player_index; // 0x3C
	bool vehicle_entrance_ban; // 0x40
	bool active_in_game; // 0x41
	bool sitting_out; // 0x42
	char consumable_suppression1; // 0x43
	char consumable_supression2; // 0x44
	char consumable_supression3; // 0x45
	short desired_respawn_player_index; // 0x46
	real_vector3d player_control_aiming; // 0x48
	long player_character_type_index; // 0x54
	long loadout_consumable_index; // 0x58
	long revenge_last_killer_player_index; // 0x5C
	s_damage_reporting_info revenge_damage_report; // 0x60
	s_simulation_player_netdebug_data netdebug_data; // 0x64
	s_simulation_game_engine_player_state_data(s_simulation_game_engine_player_state_data &); /* compiler_generated() */
	s_simulation_game_engine_player_state_data(s_simulation_game_engine_player_state_data const &); /* compiler_generated() */
	s_simulation_game_engine_player_state_data(); /* compiler_generated() */
	s_simulation_game_engine_player_state_data &operator=(s_simulation_game_engine_player_state_data &); /* compiler_generated() */
	s_simulation_game_engine_player_state_data &operator=(s_simulation_game_engine_player_state_data const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_simulation_game_engine_player_state_data) == 116, "Invalid s_simulation_game_engine_player_state_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SIMULATION_GAME_INTERFACE_SIMULATION_GAME_ENGINE_PLAYER_HPP__
