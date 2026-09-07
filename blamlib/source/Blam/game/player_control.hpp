#ifndef __BLAM_GAME_PLAYER_CONTROL_HPP__
#define __BLAM_GAME_PLAYER_CONTROL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/aim_target.hpp"
#include "Blam/game/players.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/units/units.hpp"

/* ---------- forward declarations */

struct real_euler_angles2d;
struct s_aim_assist_targeting_result;
struct s_player_action_context;
struct s_player_control_globals;
struct s_player_control_input;
struct s_player_control_input_state;
struct s_player_control_state;
struct s_unit_weapon_set;

/* ---------- constants */

/* ---------- definitions */

struct s_player_control_input
{
	float forward_velocity; // 0x0
	float strafe_velocity; // 0x4
	float primary_trigger; // 0x8
	float secondary_trigger; // 0xC
	real_euler_angles2d aiming; // 0x10
	unsigned long unit_control_flags; // 0x18
	unsigned long player_control_flags; // 0x1C
	unsigned short player_action_flags; // 0x20
	unsigned char __pad0[2]; // 0x22
	float field_24; // 0x24
	s_aim_assist_targeting_result aim_assist; // 0x28
};
static_assert(sizeof(s_player_control_input) == 80, "Invalid s_player_control_input size");

#pragma pack(push, 4)
struct s_player_control_state
{
	unsigned long unit_control_flags; // 0x0
	unsigned short player_action_flags; // 0x4
	unsigned char __pad0[2]; // 0x6
	real_euler_angles2d desired_angles; // 0x8
	float forward_velocity; // 0x10
	float strafe_velocity; // 0x14
	float primary_trigger; // 0x18
	float secondary_trigger; // 0x1C
	s_unit_weapon_set desired_weapon_set; // 0x20
	short grenade_index; // 0x24
	char magnification_level; // 0x26
	unsigned char __pad1[1]; // 0x27
	s_player_action_context action_context; // 0x28
	s_aim_assist_targeting_result aim_assist; // 0x34
	bool map_editor_rotation_valid; // 0x5C
	unsigned char __pad2[3]; // 0x5D
	float map_editor_rotation_yaw; // 0x60
	float map_editor_rotation_pitch; // 0x64
	unsigned short map_editor_flags; // 0x68
	unsigned char __pad3[2]; // 0x6A
};
#pragma pack(pop)
static_assert(sizeof(s_player_control_state) == 108, "Invalid s_player_control_state size");

struct s_player_control_input_state
{
	long unit_index; // 0x0
	s_player_control_state state; // 0x4
	unsigned char unknown1[105]; // 0x70
	bool weapon_lowered; // 0xD9
	unsigned char unknown2[30]; // 0xDA
};
static_assert(sizeof(s_player_control_input_state) == 248, "Invalid s_player_control_input_state size");

struct s_player_control_globals
{
	public:
	struct s_player_control_player_unknown
	{
		char unknown[48]; // 0x0
	};
	static_assert(sizeof(s_player_control_player_unknown) == 48, "Invalid s_player_control_player_unknown size");
	public:
	s_static_array<s_player_control_player_unknown,16> player_unknown; // 0x0
	s_static_array<s_player_control_input_state,4> player_input; // 0x300
};
static_assert(sizeof(s_player_control_globals) == 1760, "Invalid s_player_control_globals size");

/* ---------- prototypes */

extern s_player_control_input_state *player_control_input_get(long user_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_PLAYER_CONTROL_HPP__
