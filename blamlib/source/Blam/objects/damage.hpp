#ifndef __BLAM_OBJECTS_DAMAGE_HPP__
#define __BLAM_OBJECTS_DAMAGE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

struct real_vector3d;
struct s_cluster_reference;
struct s_damage_data;
struct s_damage_owner;
struct s_damage_reporting_info;

/* ---------- constants */

enum e_damage_reporting_type
{
	_damage_reporting_type_guardians_unknown = 0,
	_damage_reporting_type_guardians,
	_damage_reporting_type_falling_damage,
	_damage_reporting_type_generic_collision,
	_damage_reporting_type_armor_lock_crush,
	_damage_reporting_type_generic_melee,
	_damage_reporting_type_generic_explosion,
	_damage_reporting_type_magnum,
	_damage_reporting_type_plasma_pistol,
	_damage_reporting_type_needler,
	_damage_reporting_type_mauler,
	_damage_reporting_type_smg,
	_damage_reporting_type_plasma_rifle,
	_damage_reporting_type_battle_rifle,
	_damage_reporting_type_carbine,
	_damage_reporting_type_shotgun,
	_damage_reporting_type_sniper_rifle,
	_damage_reporting_type_beam_rifle,
	_damage_reporting_type_assault_rifle,
	_damage_reporting_type_spiker,
	_damage_reporting_type_fuel_rod_cannon,
	_damage_reporting_type_missile_pod,
	_damage_reporting_type_rocket_launcher,
	_damage_reporting_type_spartan_laser,
	_damage_reporting_type_brute_shot,
	_damage_reporting_type_flamethrower,
	_damage_reporting_type_sentinel_gun,
	_damage_reporting_type_energy_sword,
	_damage_reporting_type_gravity_hammer,
	_damage_reporting_type_frag_grenade,
	_damage_reporting_type_plasma_grenade,
	_damage_reporting_type_spike_grenade,
	_damage_reporting_type_firebomb_grenade,
	_damage_reporting_type_flag,
	_damage_reporting_type_bomb,
	_damage_reporting_type_bomb_explosion,
	_damage_reporting_type_ball,
	_damage_reporting_type_machinegun_turret,
	_damage_reporting_type_plasma_cannon,
	_damage_reporting_type_plasma_mortar,
	_damage_reporting_type_plasma_turret,
	_damage_reporting_type_shade_turret,
	_damage_reporting_type_banshee,
	_damage_reporting_type_ghost,
	_damage_reporting_type_mongoose,
	_damage_reporting_type_scorpion,
	_damage_reporting_type_scorpion_gunner,
	_damage_reporting_type_spectre,
	_damage_reporting_type_spectre_gunner,
	_damage_reporting_type_warthog,
	_damage_reporting_type_warthog_gunner,
	_damage_reporting_type_warthog_gauss_turret,
	_damage_reporting_type_wraith,
	_damage_reporting_type_wraith_gunner,
	_damage_reporting_type_tank,
	_damage_reporting_type_chopper,
	_damage_reporting_type_hornet,
	_damage_reporting_type_mantis,
	_damage_reporting_type_prowler,
	_damage_reporting_type_sentinel_beam,
	_damage_reporting_type_sentinel_rpg,
	_damage_reporting_type_teleporter,
	_damage_reporting_type_tripmine,
	_damage_reporting_type_dmr,
	k_number_of_damage_reporting_types,
};

/* ---------- definitions */

struct s_damage_owner
{
	long player_index; // 0x0
	long object_index; // 0x4
	unsigned char team; // 0x8
	unsigned char __pad0[3]; // 0x9
};
static_assert(sizeof(s_damage_owner) == 12, "Invalid s_damage_owner size");

struct s_damage_reporting_info
{
	c_enum<enum e_damage_reporting_type,short> type; // 0x0
	char variant; // 0x2
	char modifier; // 0x3
	s_damage_reporting_info(s_damage_reporting_info &); /* compiler_generated() */
	s_damage_reporting_info(s_damage_reporting_info const &); /* compiler_generated() */
	_inline s_damage_reporting_info(); /* compiler_generated() */
	s_damage_reporting_info &operator=(s_damage_reporting_info &); /* compiler_generated() */
	_inline s_damage_reporting_info &operator=(s_damage_reporting_info const &__that); /* compiler_generated() */
};
static_assert(sizeof(s_damage_reporting_info) == 4, "Invalid s_damage_reporting_info size");

struct s_damage_data
{
	long damage_effect_index; // 0x0
	long flags; // 0x4
	s_damage_owner damage_owner; // 0x8
	long unknown_object_index1; // 0x14
	long unknown_object_index2; // 0x18
	unsigned char __pad0[4]; // 0x1C
	s_cluster_reference location; // 0x20
	unsigned char __pad1[2]; // 0x22
	real_point3d position; // 0x24
	real_point3d epicenter; // 0x30
	real_vector3d direction; // 0x3C
	unsigned char __pad2[4]; // 0x48
	float material_effect_scale; // 0x4C
	float material_effect_error; // 0x50
	float acceleration_scale; // 0x54
	float shake_scale; // 0x58
	float damage_scale; // 0x5C
	float unknown_scale; // 0x60
	unsigned char __pad3[12]; // 0x64
	real_vector3d unknown_vector; // 0x70
	long unknown_object_index3; // 0x7C
	float unknown_vitality; // 0x80
	short material_type; // 0x84
	short projectile_shot_id; // 0x86
	long material_response_index; // 0x88
	s_damage_reporting_info reporting_info; // 0x8C
	long damage_batchifer; // 0x90
	long material_index; // 0x94
	s_damage_data(s_damage_data &); /* compiler_generated() */
	s_damage_data(s_damage_data const &); /* compiler_generated() */
	_inline s_damage_data(); /* compiler_generated() */
	s_damage_data &operator=(s_damage_data &); /* compiler_generated() */
	s_damage_data &operator=(s_damage_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_damage_data) == 152, "Invalid s_damage_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_OBJECTS_DAMAGE_HPP__
