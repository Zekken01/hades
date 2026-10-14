#ifndef __BLAM_ITEMS_WEAPONS_HPP__
#define __BLAM_ITEMS_WEAPONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/animations/mixing_board/channels/animation_channel.hpp"
#include "Blam/items/items.hpp"
#include "Blam/objects/target_tracking.hpp"

/* ---------- forward declarations */

class c_animation_id;
struct c_target_tracking_system;
struct s_item_data;
struct s_weapon_barrel;
struct s_weapon_data;
struct s_weapon_first_person_emulation;
struct s_weapon_magazine;
struct s_weapon_trigger;

/* ---------- constants */

enum e_multiplayer_weapon
{
	_multiplayer_weapon_none = 0,
	_multiplayer_weapon_flag,
	_multiplayer_weapon_oddball,
	_multiplayer_weapon_headhunter_head,
	_multiplayer_weapon_juggernaut_powerup,
	k_number_of_multiplayer_weapons,
};

enum e_weapon_barrel_state
{
	_weapon_barrel_state_idle = 0,
	_weapon_barrel_state_firing,
};

/* ---------- definitions */

struct s_weapon_barrel
{
	unsigned char unknown; // 0x0
	char state; // 0x1
	unsigned short field_2; // 0x2
	unsigned short firing_flags; // 0x4
	short field_6; // 0x6
	unsigned short firing_effect_flags; // 0x8
	short firing_effect_block_index; // 0xA
	short firing_effect_uses_remaining; // 0xC
	char fieldE; // 0xE
	char fieldF; // 0xF
	float firing_rate; // 0x10
	float ejection; // 0x14
	float illumination; // 0x18
	float error; // 0x1C
	float recoil; // 0x20
	float field_24; // 0x24
	long field_28; // 0x28
	short bonus_rounds_fired; // 0x2C
	unsigned char shots_fired; // 0x2E
	char field_2F; // 0x2F
	long effect_index; // 0x30
};
static_assert(sizeof(s_weapon_barrel) == 52, "Invalid s_weapon_barrel size");

struct s_weapon_trigger
{
	char field_0; // 0x0
	char field_1; // 0x1
	char field_2; // 0x2
	char field_3; // 0x3
	short charge_up_timer; // 0x4
	unsigned short flags; // 0x6
	__int32 charing_effect_index; // 0x8
};
static_assert(sizeof(s_weapon_trigger) == 12, "Invalid s_weapon_trigger size");

struct s_weapon_magazine
{
	short state; // 0x0
	short reload_cooldown; // 0x2
	short field_4; // 0x4
	short rounds_unloaded; // 0x6
	short field_8; // 0x8
	short rounds_loaded; // 0xA
	short field_C; // 0xC
	short field_E; // 0xE
	short field_10; // 0x10
	short firing_cooldown; // 0x12
	short field_14; // 0x14
	short field_16; // 0x16
	short field_18; // 0x18
};
static_assert(sizeof(s_weapon_magazine) == 26, "Invalid s_weapon_magazine size");

struct s_weapon_first_person_emulation
{
	long animation_graph_definition_index; // 0x0
	c_animation_id animation_id; // 0x4
	long authored_time; // 0x8
	long animation_name; // 0xC
	long field_10; // 0x10
	long sound_impulse_tracker_index; // 0x14
	long unknown_animation_name; // 0x18
};
static_assert(sizeof(s_weapon_first_person_emulation) == 28, "Invalid s_weapon_first_person_emulation size");

#pragma pack(push, 4)
struct s_weapon_data :
	public s_item_data
{
	unsigned short weapon_flags; // 0x18C
	char weapon_control_flags; // 0x18E
	char primary_trigger; // 0x18F
	char last_primary_trigger; // 0x190
	char last_hill_or_valley; // 0x191
	char primary_trigger_diration; // 0x192
	char primary_trigger_down_ticks; // 0x193
	char primary_trigger_firing_ticks; // 0x194
	char barrel_spin; // 0x195
	char delay_authorative_state_timer; // 0x196
	char field_197; // 0x197
	short state; // 0x198
	short state_timer; // 0x19A
	short weapon_disabled_by_reload_timer; // 0x19C
	short multiplayer_weapon_identifier; // 0x19E
	short simulation_weapon_identifier; // 0x1A0
	float heat; // 0x1A4
	float age; // 0x1A8
	float overcharged; // 0x1AC
	float illumination_scale; // 0x1B0
	float current_power; // 0x1B4
	float desired_power; // 0x1B8
	c_target_tracking_system target_tracking; // 0x1BC
	short recoil_angular_velocity; // 0x1FC
	short recoil_recovery_time; // 0x1FE
	short shorts_until_dometion; // 0x200
	short alternate_shots_loaded; // 0x202
	s_weapon_barrel barrels[2]; // 0x204
	s_weapon_trigger triggers[2]; // 0x26C
	s_weapon_magazine magazines[2]; // 0x284
	__int32 overheated_effect_index; // 0x2B8
	__int32 game_time_last_fired; // 0x2BC
	s_weapon_first_person_emulation first_person_emulation; // 0x2C0
	s_weapon_data(s_weapon_data &); /* compiler_generated() */
	s_weapon_data(s_weapon_data const &); /* compiler_generated() */
	s_weapon_data(); /* compiler_generated() */
	s_weapon_data &operator=(s_weapon_data &); /* compiler_generated() */
	s_weapon_data &operator=(s_weapon_data const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_weapon_data) == 732, "Invalid s_weapon_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ITEMS_WEAPONS_HPP__
