#ifndef __BLAM_SIMULATION_SIMULATION_GAME_OBJECTS_HPP__
#define __BLAM_SIMULATION_SIMULATION_GAME_OBJECTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/units/units.hpp"
#include "Player/PlayerCharacterSystem.hpp"

/* ---------- forward declarations */

class c_bitstream;
struct c_simulation_object_index_state_data;
struct real_vector3d;
struct s_player_model_customization;
struct s_simulation_generic_creation_data;
struct s_simulation_object_creation_data;
struct s_simulation_object_state_data;
struct s_simulation_player_appearance;
struct s_simulation_unit_creation_data;
struct s_simulation_unit_state_data;
struct s_unit_weapon_set;

/* ---------- constants */

enum e_simulation_object_update_flags
{
	_simulation_object_update_dead_bit = 0,
	_simulation_object_update_position_bit,
	_simulation_object_update_forward_and_up_bit,
	_simulation_object_update_scale_bit,
	_simulation_object_update_translational_velocity_bit,
	_simulation_object_update_angular_velocity_bit,
	_simulation_object_update_body_vitality_bit,
	_simulation_object_update_shield_vitality_bit,
	_simulation_object_update_region_state_bit,
	_simulation_object_update_constraint_state_bit,
	_simulation_object_update_owner_team_index_bit,
	_simulation_object_update_parent_state_bit,
	_simulation_object_update_multiplayer_properties_bit,
	_simulation_object_update_map_variant_index_bit,
	k_simulation_object_update_flag_count,
};

enum e_simulation_unit_update_flags
{
	_simulation_unit_update_control_bit = 14, // 0x000E
	_simulation_unit_update_parent_vehicle_bit = 15, // 0x000F
	_simulation_unit_update_desired_aiming_vector_bit = 16, // 0x0010
	_simulation_unit_update_desired_weapon_set_bit = 17, // 0x0011
	_simulation_unit_update_weapon1_type_bit = 18, // 0x0012
	_simulation_unit_update_weapon2_type_bit = 19, // 0x0013
	_simulation_unit_update_weapon3_type_bit = 20, // 0x0014
	_simulation_unit_update_weapon4_type_bit = 21, // 0x0015
	_simulation_unit_update_weapon1_state_bit = 22, // 0x0016
	_simulation_unit_update_weapon2_state_bit = 23, // 0x0017
	_simulation_unit_update_weapon3_state_bit = 24, // 0x0018
	_simulation_unit_update_weapon4_state_bit = 25, // 0x0019
	_simulation_unit_update_grenade_counts_bit = 26, // 0x001A
	_simulation_unit_update_active_camo_bit = 27, // 0x001B
	_simulation_unit_update_equipment_bit = 28, // 0x001C
	_simulation_unit_update_equipment_charges_bit = 29, // 0x001D
	_simulation_unit_update_consumable_energy_bit = 30, // 0x001E
	_simulation_unit_update_control_context_bit = 31, // 0x001F
	_simulation_unit_update_assassination_data_bit = 32, // 0x0020 ' '
	_simulation_unit_update_hud_info_bit = 33, // 0x0021 '!'
	_simulation_unit_update_map_editor_flags_bit = 34, // 0x0022 '"'
	k_simulation_unit_update_flag_count = 35, // 0x0023 '#'
};

/* ---------- definitions */

struct c_simulation_object_index_state_data
{
	long object_index_state_data; // 0x0
	long simulation_object_glue_index; // 0x4
	static char (*const apply_update)(c_simulation_object_index_state_data const *, long *);
	static bool (*const build_update)(c_simulation_object_index_state_data *, long);
	static bool (*const decode)(c_simulation_object_index_state_data *, c_bitstream *, bool);
	static void (*const encode)(c_simulation_object_index_state_data const *, c_bitstream *, bool);
};
static_assert(sizeof(c_simulation_object_index_state_data) == 8, "Invalid c_simulation_object_index_state_data size");

struct s_simulation_object_state_data
{
	real_point3d position; // 0x0
	real_vector3d forward; // 0xC
	real_vector3d up; // 0x18
	float scale; // 0x24
	real_vector3d translational_velocity; // 0x28
	real_vector3d angular_velocity; // 0x34
	float body_vitality; // 0x40
	bool body_stun_ticks_is_zero; // 0x44
	unsigned char __pad0[3]; // 0x45
	float shield_vitality; // 0x48
	bool shield_stun_ticks_is_zero; // 0x4C
	bool shield_charging; // 0x4D
	bool shield_depleted; // 0x4E
	bool is_dead; // 0x4F
	short owner_team_index; // 0x50
	char region_count; // 0x52
	unsigned char region_state[16]; // 0x53
	char damage_section_count; // 0x63
	unsigned short destroyed_constraints; // 0x64
	unsigned short loosened_constraints; // 0x66
	long parent_entity_index; // 0x68
	long parent_object_glue_index; // 0x6C
	long node; // 0x70
	bool initial_attachment; // 0x74
	unsigned char __pad1[3]; // 0x75
	real_point3d attachment_relative_position; // 0x78
	real_vector3d attachment_up; // 0x84
	real_vector3d attachment_forward; // 0x90
	unsigned short multiplayer_properties_data_flags; // 0x9C
	short map_variant_index; // 0x9E
};
static_assert(sizeof(s_simulation_object_state_data) == 160, "Invalid s_simulation_object_state_data size");

struct s_simulation_object_creation_data
{
	long scenario_datum_index; // 0x0
	short map_variant_index; // 0x4
	bool should_override_placement; // 0x6
	unsigned char __pad0[1]; // 0x7
	long object_definition_index; // 0x8
	long variant_attachment_override_index; // 0xC
};
static_assert(sizeof(s_simulation_object_creation_data) == 16, "Invalid s_simulation_object_creation_data size");

#pragma pack(push, 4)
struct s_simulation_generic_creation_data :
	public s_simulation_object_creation_data
{
	unsigned long variant_name; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_simulation_generic_creation_data) == 20, "Invalid s_simulation_generic_creation_data size");

struct s_simulation_player_appearance
{
	unsigned long change_colors[5]; // 0x0
	unsigned char region_permutation_indices[10]; // 0x14
	char field_1E; // 0x1E
	char field_1F; // 0x1F
};
static_assert(sizeof(s_simulation_player_appearance) == 32, "Invalid s_simulation_player_appearance size");

struct s_simulation_unit_creation_data :
	public s_simulation_object_creation_data
{
	s_player_model_customization player_appearance; // 0x10
	unsigned long variant_name; // 0x34
	long team; // 0x38
	long hologram_definition_index; // 0x3C
	real_point3d hologram_position; // 0x40
	long controlling_player_index; // 0x4C
};
static_assert(sizeof(s_simulation_unit_creation_data) == 80, "Invalid s_simulation_unit_creation_data size");

#pragma pack(push, 4)
struct s_simulation_unit_state_data :
	public s_simulation_object_state_data
{
	public:
	struct s_weapon_state_data
	{
		long definition_index; // 0x0
		short multiplayer_weapon_identifier; // 0x4
		short simulation_weapon_identifier; // 0x6
		short rounds_loaded; // 0x8
		short rounds_total; // 0xA
		float age; // 0xC
	};
	static_assert(sizeof(s_weapon_state_data) == 16, "Invalid s_weapon_state_data size");
	public:
	short controlling_player_index; // 0xA0
	short controlling_actor_index; // 0xA2
	short controlling_actor_squad_index; // 0xA4
	short controlling_actor_cell_index; // 0xA6
	short controlling_actor_spawn_point_index; // 0xA8
	unsigned char __pad0[2]; // 0xAA
	long parent_vehicle_entity_index; // 0xAC
	short parent_seat_index; // 0xB0
	unsigned char __pad1[2]; // 0xB2
	real_vector3d desired_aiming_vector; // 0xB4
	s_unit_weapon_set desired_weapon_set; // 0xC0
	s_weapon_state_data weapons[4]; // 0xC4
	char grenade_counts[4]; // 0x104
	bool active_camo_active; // 0x108
	unsigned char __pad2[3]; // 0x109
	float active_camo_maximum; // 0x10C
	float active_camo; // 0x110
	float active_camo_regrowth; // 0x114
	long parent_gamestate_index; // 0x118
	long equipment[4]; // 0x11C
	char equipment_charges[4]; // 0x12C
	long consumable_energy_level; // 0x130
	long consumable_energy_ticks; // 0x134
	unsigned char map_editor_flags; // 0x138
	char control_context_identifier; // 0x139
	bool tracked_target; // 0x13A
	bool locked_target; // 0x13B
	c_simulation_object_index_state_data object_index_state_data; // 0x13C
	unsigned long assassination_sync_action_name; // 0x144
	real_point3d assassination_authoritative_position; // 0x148
	real_vector3d assassination_authoritative_forward; // 0x154
	bool assassination_is_victim; // 0x160
	unsigned char __pad3[3]; // 0x161
};
#pragma pack(pop)
static_assert(sizeof(s_simulation_unit_state_data) == 356, "Invalid s_simulation_unit_state_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SIMULATION_SIMULATION_GAME_OBJECTS_HPP__
