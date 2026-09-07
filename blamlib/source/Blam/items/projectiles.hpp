#ifndef __BLAM_ITEMS_PROJECTILES_HPP__
#define __BLAM_ITEMS_PROJECTILES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/aim_target.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct c_aim_target_object;
struct real_bounds;
struct real_vector3d;
struct s_object_data;
struct s_object_definition;
struct s_projectile_brute_grenade_property;
struct s_projectile_data;
struct s_projectile_definition;
struct s_projectile_fire_bomb_grenade_property;
struct s_projectile_material_response;
struct s_projectile_shotgun_property;
struct s_tag_reference;

/* ---------- constants */

enum e_projectile_definition_flags
{
	_projectile_oriented_along_velocity_bit = 0,
	_projectile_ai_must_use_ballistic_aiming_bit,
	_projectile_detonation_max_time_if_attached_bit,
	_projectile_has_super_combining_explosion_bit,
	_projectile_damage_scales_based_on_distance_bit,
	_projectile_travels_instantaneously_bit,
	_projectile_steering_adjusts_orientation_bit,
	_projectile_do_not_noise_up_steering_bit,
	_projectile_can_track_behind_itself_bit,
	_projectile_robotron_steering_bit,
	_projectile_faster_when_owned_by_player_bit,
};

/* ---------- definitions */

struct s_projectile_brute_grenade_property
{
	real_bounds angular_velocity_range; // 0x0
	float spin_angular_velocity; // 0x8
	float angular_damping; // 0xC
	float drag_angle_k; // 0x10
	float drag_speed_k; // 0x14
	float drag_exponent; // 0x18
	float attach_sample_radius; // 0x1C
	float attach_acc_k; // 0x20
	float attach_acc_s; // 0x24
	float attach_acc_e; // 0x28
	float attach_acc_damping; // 0x2C
};
static_assert(sizeof(s_projectile_brute_grenade_property) == 48, "Invalid s_projectile_brute_grenade_property size");

struct s_projectile_fire_bomb_grenade_property
{
	float projection_offset; // 0x0
};
static_assert(sizeof(s_projectile_fire_bomb_grenade_property) == 4, "Invalid s_projectile_fire_bomb_grenade_property size");

struct s_projectile_material_response
{
	c_flags<enum e_projectile_material_response_flag_bits,unsigned short> flags; // 0x0
	c_enum<enum e_projectile_material_response_response,short> default_response; // 0x2
	unsigned long material_name; // 0x4
	short global_material_index; // 0x8
	unsigned char unused1[2]; // 0xA
	c_enum<enum e_projectile_material_response_response,short> potential_response; // 0xC
	c_flags<enum e_projectile_material_response_response_flag_bits,unsigned short> response_flags; // 0xE
	float chance_fraction; // 0x10
	real_bounds between_angle; // 0x14
	real_bounds and_velocity; // 0x1C
	c_enum<enum e_projectile_material_response_scale_effects_by,short> scale_effects_by; // 0x24
	unsigned char unused2[2]; // 0x26
	float angular_noise; // 0x28
	float velocity_noise; // 0x2C
	float initial_friction; // 0x30
	float maximum_distance; // 0x34
	float parallel_friction; // 0x38
	float perpendicular_friction; // 0x3C
	s_projectile_material_response(s_projectile_material_response &); /* compiler_generated() */
	s_projectile_material_response(s_projectile_material_response const &); /* compiler_generated() */
	s_projectile_material_response(); /* compiler_generated() */
	s_projectile_material_response &operator=(s_projectile_material_response &); /* compiler_generated() */
	s_projectile_material_response &operator=(s_projectile_material_response const &); /* compiler_generated() */
};
static_assert(sizeof(s_projectile_material_response) == 64, "Invalid s_projectile_material_response size");

struct s_projectile_shotgun_property
{
	short amount; // 0x0
	short distance; // 0x2
	float accuracy; // 0x4
	float spread_cone_angle; // 0x8
};
static_assert(sizeof(s_projectile_shotgun_property) == 12, "Invalid s_projectile_shotgun_property size");

#pragma pack(push, 4)
struct s_projectile_definition :
	public s_object_definition
{
	c_flags<enum e_projectile_definition_flags,long> projectile_flags; // 0x120
	c_enum<enum e_projectile_detonation_timer_starts,short> detonation_timer_starts; // 0x124
	c_enum<enum e_projectile_noise_level,short> impact_noise; // 0x126
	float collision_radius; // 0x128
	float arming_time; // 0x12C
	float danger_radius; // 0x130
	real_bounds timer; // 0x134
	float minimum_velocity; // 0x13C
	float maximum_range; // 0x140
	float detonation_charge_time; // 0x144
	c_enum<enum e_projectile_noise_level,short> detonation_noise; // 0x148
	short super_detonation_projectile_count; // 0x14A
	float super_detonation_delay; // 0x14C
	s_tag_reference detonation_started; // 0x150
	s_tag_reference airborne_detonation_effect; // 0x160
	s_tag_reference ground_detonation_effect; // 0x170
	s_tag_reference detonation_damage; // 0x180
	s_tag_reference attached_detonation_damage; // 0x190
	s_tag_reference super_detonation; // 0x1A0
	s_tag_reference super_detonation_damage; // 0x1B0
	s_tag_reference detonation_sound; // 0x1C0
	c_enum<enum e_damage_reporting_type,char> damage_reporting_type; // 0x1D0
	unsigned char unknown3; // 0x1D1
	unsigned char unknown4; // 0x1D2
	unsigned char unknown5; // 0x1D3
	s_tag_reference attached_super_detonation_damage; // 0x1D4
	float material_effect_radius; // 0x1E4
	s_tag_reference flyby_sound; // 0x1E8
	s_tag_reference flyby_response; // 0x1F8
	s_tag_reference impact_effect; // 0x208
	s_tag_reference impact_damage; // 0x218
	float boarding_detonation_time; // 0x228
	s_tag_reference boarding_detonation_damage; // 0x22C
	s_tag_reference boarding_attached_detonation_damage; // 0x23C
	float air_gravity_scale; // 0x24C
	real_bounds air_damage_range; // 0x250
	float water_gravity_scale; // 0x258
	real_bounds water_damage_range; // 0x25C
	float initial_velocity; // 0x264
	float final_velocity; // 0x268
	float indirect_fire_velocity; // 0x26C
	float ai_velocity_scale; // 0x270
	float ai_guided_angular_velocity_scale; // 0x274
	real_bounds guided_angular_velocity; // 0x278
	float guided_angular_velocity_at_rest; // 0x280
	real_bounds acceleration_range; // 0x284
	float ai_target_leading_scale; // 0x28C
	float targeted_leading_fraction; // 0x290
	float guided_projectile_outer_range_error_radius; // 0x294
	float autoaim_leading_max_lead_time; // 0x298
	c_tag_block<s_projectile_material_response> material_responses; // 0x29C
	c_tag_block<s_projectile_brute_grenade_property> brute_grenade_properties; // 0x2A8
	c_tag_block<s_projectile_fire_bomb_grenade_property> fire_bomb_grenade_properties; // 0x2B4
	c_tag_block<s_projectile_shotgun_property> shotgun_properties; // 0x2C0
	s_projectile_definition(s_projectile_definition &); /* compiler_generated() */
	s_projectile_definition(s_projectile_definition const &); /* compiler_generated() */
	s_projectile_definition(); /* compiler_generated() */
	s_projectile_definition &operator=(s_projectile_definition &); /* compiler_generated() */
	s_projectile_definition &operator=(s_projectile_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_projectile_definition) == 716, "Invalid s_projectile_definition size");

struct s_projectile_data :
	public s_object_data
{
	long projectile_flags; // 0x178
	char action; // 0x17C
	unsigned char __pad0[1]; // 0x17D
	unsigned short hit_global_material_type; // 0x17E
	real_vector3d hit_normal; // 0x180
	long ignore_object_index_a; // 0x18C
	long ignore_object_index_b; // 0x190
	c_aim_target_object targeting_data; // 0x194
	long weapon_index; // 0x1A0
	long simulation_collision_object_index; // 0x1A4
	long simulation_collision_object_node_index; // 0x1A8
	real_point3d simulation_collision_object_position; // 0x1AC
	float detonation_timer; // 0x1B8
	float detonation_timer_delta; // 0x1BC
	float super_detonation_check_timer; // 0x1C0
	float super_detonation_check_timer_delta; // 0x1C4
	float arming_timer; // 0x1C8
	float arming_timer_delta; // 0x1CC
	float odometer; // 0x1D0
	float bounce_odometer; // 0x1D4
	float velocity_scale; // 0x1D8
	float maximum_damage_distance; // 0x1DC
	real_vector3d rotation_axis; // 0x1E0
	float rotation_sine; // 0x1EC
	float rotation_cosine; // 0x1F0
	float damage_scale; // 0x1F4
	float guided_angular_velocity; // 0x1F8
	float last_thrust_speed; // 0x1FC
	float thrust_odometer; // 0x200
	real_point3d start_point; // 0x204
	unsigned short shot_id; // 0x210
	unsigned short time_of_flight_ticks; // 0x212
	long creation_game_time; // 0x214
	s_projectile_data(s_projectile_data &); /* compiler_generated() */
	s_projectile_data(s_projectile_data const &); /* compiler_generated() */
	s_projectile_data(); /* compiler_generated() */
	s_projectile_data &operator=(s_projectile_data &); /* compiler_generated() */
	s_projectile_data &operator=(s_projectile_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_projectile_data) == 536, "Invalid s_projectile_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ITEMS_PROJECTILES_HPP__
