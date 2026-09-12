#ifndef __BLAM_UNITS_BIPED_DEFINITIONS_HPP__
#define __BLAM_UNITS_BIPED_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/unit_definitions.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct real_vector3d;
struct s_biped_camera_height_block;
struct s_biped_definition;
struct s_biped_ground_fitting_data;
struct s_biped_leaping_data;
struct s_biped_movement_gate_block;
struct s_biped_pivot_data;
struct s_character_physics_definition;
struct s_character_physics_flying_definition;
struct s_character_physics_ground_definition;
struct s_physics_model_havok_shape_base;
struct s_physics_model_havok_shape_reference;
struct s_physics_model_pill;
struct s_physics_model_shape;
struct s_physics_model_sphere;
struct s_tag_data;
struct s_tag_reference;
struct s_unit_definition;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_character_physics_flying_definition
{
	float bank_angle; // 0x0
	float bank_apply_time; // 0x4
	float bank_decay_time; // 0x8
	float pitch_ratio; // 0xC
	float maximum_velocity; // 0x10
	float maximum_sidestep_velocity; // 0x14
	float acceleration; // 0x18
	float deceleration; // 0x1C
	float angular_velocity_maximum; // 0x20
	float angular_acceleration_maximum; // 0x24
	float crouch_velocity_modifier; // 0x28
	c_tag_block<unsigned long> contact_points; // 0x2C
	unsigned char __pad0[4]; // 0x38
};
#pragma pack(pop)
static_assert(sizeof(s_character_physics_flying_definition) == 60, "Invalid s_character_physics_flying_definition size");

struct s_character_physics_ground_definition
{
	float maximum_slope_angle; // 0x0
	float downhill_falloff_angle; // 0x4
	float downhill_cutoff_angle; // 0x8
	float uphill_falloff_angle; // 0xC
	float uphill_cutoff_angle; // 0x10
	float downhill_velocity_scale; // 0x14
	float uphill_velocity_scale; // 0x18
	float runtime_minimum_normal_k; // 0x1C
	float runtime_downhill_k0; // 0x20
	float runtime_downhill_k1; // 0x24
	float runtime_uphill_k0; // 0x28
	float runtime_uphill_k1; // 0x2C
	float climb_inflection_angle; // 0x30
	float scale_airborne_reaction_time; // 0x34
	float scale_ground_adhesion_velocity; // 0x38
	float gravity_scale; // 0x3C
};
static_assert(sizeof(s_character_physics_ground_definition) == 64, "Invalid s_character_physics_ground_definition size");

struct s_physics_model_havok_shape_base
{
	long field_pointer_skip; // 0x0
	short size; // 0x4
	short count; // 0x6
	long offset; // 0x8
	long user_data; // 0xC
	float radius; // 0x10
};
static_assert(sizeof(s_physics_model_havok_shape_base) == 20, "Invalid s_physics_model_havok_shape_base size");

struct s_physics_model_shape
{
	unsigned long name; // 0x0
	short material_index; // 0x4
	short runtime_material_type; // 0x6
	float relative_mass_scale; // 0x8
	float friction; // 0xC
	float restitution; // 0x10
	float volume; // 0x14
	float mass; // 0x18
	short mass_distribution_index; // 0x1C
	char phantom_index; // 0x1E
	char proxy_collision_group; // 0x1F
	s_physics_model_havok_shape_base shape_base; // 0x20
	unsigned char pad[12]; // 0x34
};
static_assert(sizeof(s_physics_model_shape) == 64, "Invalid s_physics_model_shape size");

struct s_physics_model_pill :
	public s_physics_model_shape
{
	real_vector3d bottom; // 0x40
	float bottom_radius; // 0x4C
	real_vector3d top; // 0x50
	float top_radius; // 0x5C
};
static_assert(sizeof(s_physics_model_pill) == 96, "Invalid s_physics_model_pill size");

struct s_physics_model_havok_shape_reference
{
	c_enum<enum e_blam_shape_type,short> shapetype; // 0x0
	short shape_index; // 0x2
	unsigned long child_shape_size; // 0x4
	s_physics_model_havok_shape_reference(s_physics_model_havok_shape_reference &); /* compiler_generated() */
	s_physics_model_havok_shape_reference(s_physics_model_havok_shape_reference const &); /* compiler_generated() */
	s_physics_model_havok_shape_reference(); /* compiler_generated() */
	s_physics_model_havok_shape_reference &operator=(s_physics_model_havok_shape_reference &); /* compiler_generated() */
	s_physics_model_havok_shape_reference &operator=(s_physics_model_havok_shape_reference const &); /* compiler_generated() */
};
static_assert(sizeof(s_physics_model_havok_shape_reference) == 8, "Invalid s_physics_model_havok_shape_reference size");

struct s_physics_model_sphere :
	public s_physics_model_shape
{
	s_physics_model_havok_shape_base convex_base; // 0x40
	unsigned long field_pointer_skip; // 0x54
	s_physics_model_havok_shape_reference shape_reference; // 0x58
	real_vector3d translation; // 0x60
	float translation_radius; // 0x6C
	s_physics_model_sphere(s_physics_model_sphere &); /* compiler_generated() */
	s_physics_model_sphere(s_physics_model_sphere const &); /* compiler_generated() */
	s_physics_model_sphere(); /* compiler_generated() */
	s_physics_model_sphere &operator=(s_physics_model_sphere &); /* compiler_generated() */
	s_physics_model_sphere &operator=(s_physics_model_sphere const &); /* compiler_generated() */
};
static_assert(sizeof(s_physics_model_sphere) == 112, "Invalid s_physics_model_sphere size");

struct s_character_physics_definition
{
	c_flags<enum e_character_physics_definition_flags,long> physics_flags; // 0x0
	float height_standing; // 0x4
	float height_crouching; // 0x8
	float radius; // 0xC
	float mass; // 0x10
	unsigned long living_material_name; // 0x14
	unsigned long dead_material_name; // 0x18
	short living_material_global_index; // 0x1C
	short dead_material_global_index; // 0x1E
	c_tag_block<s_physics_model_sphere> dead_sphere_shapes; // 0x20
	c_tag_block<s_physics_model_pill> pill_shapes; // 0x2C
	c_tag_block<s_physics_model_sphere> sphere_shapes; // 0x38
	s_character_physics_ground_definition ground; // 0x44
	s_character_physics_flying_definition flying; // 0x84
	s_character_physics_definition(s_character_physics_definition &); /* compiler_generated() */
	s_character_physics_definition(s_character_physics_definition const &); /* compiler_generated() */
	s_character_physics_definition(); /* compiler_generated() */
	s_character_physics_definition &operator=(s_character_physics_definition &); /* compiler_generated() */
	s_character_physics_definition &operator=(s_character_physics_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_character_physics_definition) == 192, "Invalid s_character_physics_definition size");

struct s_biped_leaping_data
{
	long leap_flags; // 0x0
	float dampening_scale; // 0x4
	float roll_delay; // 0x8
	float cannonball_off_axis_scale; // 0xC
	float cannonball_off_track_scale; // 0x10
	angle_bounds cannonball_roll_bounds; // 0x14
	real_bounds anticipation_ratio_bounds; // 0x1C
	real_bounds reaction_force_bounds; // 0x24
	float lobbing_desire; // 0x2C
};
static_assert(sizeof(s_biped_leaping_data) == 48, "Invalid s_biped_leaping_data size");

struct s_biped_pivot_data
{
	float on_foot_scale; // 0x0
	float min_foot_delta; // 0x4
	float stride_length_scale; // 0x8
	float throttle_scale; // 0xC
	float offset_dampening; // 0x10
	float force_turn_rate; // 0x14
};
static_assert(sizeof(s_biped_pivot_data) == 24, "Invalid s_biped_pivot_data size");

#pragma pack(push, 4)
struct s_biped_ground_fitting_data
{
	float ground_normal_dampening; // 0x0
	float root_offset_scale; // 0x4
	float root_offset_dampening; // 0x8
	float following_camera_scale; // 0xC
	float root_leaning_scale; // 0x10
	real_bounds root_roll_bounds; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_biped_ground_fitting_data) == 28, "Invalid s_biped_ground_fitting_data size");

#pragma pack(push, 4)
struct s_biped_movement_gate_block
{
	float period; // 0x0
	float z_offset; // 0x4
	float constant_z_offset; // 0x8
	float y_offset; // 0xC
	s_tag_data default_function; // 0x10
	s_biped_movement_gate_block(s_biped_movement_gate_block &); /* compiler_generated() */
	s_biped_movement_gate_block(s_biped_movement_gate_block const &); /* compiler_generated() */
	s_biped_movement_gate_block(); /* compiler_generated() */
	s_biped_movement_gate_block &operator=(s_biped_movement_gate_block &); /* compiler_generated() */
	s_biped_movement_gate_block &operator=(s_biped_movement_gate_block const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_biped_movement_gate_block) == 36, "Invalid s_biped_movement_gate_block size");

struct s_biped_camera_height_block
{
	unsigned long class_name; // 0x0
	float standing_height_fraction; // 0x4
	float crouching_height_fraction; // 0x8
};
static_assert(sizeof(s_biped_camera_height_block) == 12, "Invalid s_biped_camera_height_block size");

struct s_biped_definition :
	public s_unit_definition
{
	float moving_turning_speed; // 0x3E8
	c_flags<enum e_biped_definition_flags,long> biped_flags; // 0x3EC
	float stationary_turning_speed; // 0x3F0
	float unknown1; // 0x3F4
	unsigned long ragdoll_region_name; // 0x3F8
	float jump_velocity; // 0x3FC
	float maximum_soft_landing_time; // 0x400
	float minimum_hard_landing_time; // 0x404
	float minimum_soft_landing_velocity; // 0x408
	float minimum_hard_landing_velocity; // 0x40C
	float maximum_hard_landing_velocity; // 0x410
	float death_hard_landing_velocity; // 0x414
	float stun_duration; // 0x418
	float stationary_standing_camera_height; // 0x41C
	float moving_standing_camera_height; // 0x420
	float stationary_crouching_camera_height; // 0x424
	float moving_crouching_camera_height; // 0x428
	float crouch_transition_time; // 0x42C
	s_tag_data crouching_camera_function; // 0x430
	c_tag_block<s_biped_camera_height_block> camera_heights; // 0x444
	float camera_interpolation_start; // 0x450
	float camera_interpolation_end; // 0x454
	real_vector3d camera_offset; // 0x458
	float root_offset_camera_scale; // 0x464
	float autoaim_width; // 0x468
	c_flags<enum e_biped_lock_on_flag_bits,long> lockon_flags; // 0x46C
	float lockon_distance; // 0x470
	short physics_control_node_index; // 0x474
	float runtime_cosine_stationary_turning_threshold; // 0x478
	float runtime_crouch_transition_velocity; // 0x47C
	float runtime_camera_height_velocity; // 0x480
	short pelvis_node_index; // 0x484
	short head_node_index; // 0x486
	float crouch_fp_weapon_overlay_playback_speed_scale; // 0x488
	float headshot_acceleration_scale; // 0x48C
	s_tag_reference area_damage_effect; // 0x490
	c_tag_block<s_biped_movement_gate_block> movement_gates; // 0x4A0
	c_tag_block<s_biped_movement_gate_block> movement_gates_crouching; // 0x4AC
	float jump_aim_offset_distance; // 0x4B8
	float jump_aim_offset_duration; // 0x4BC
	float land_aim_offset_distance; // 0x4C0
	float land_aim_offset_duration; // 0x4C4
	real_bounds aim_compensate_distance_bounds; // 0x4C8
	s_character_physics_definition physics; // 0x4D0
	s_tag_reference reanimation_character; // 0x590
	s_tag_reference transformation_muffin; // 0x5A0
	s_tag_reference death_spawn_character; // 0x5B0
	short death_spawn_count; // 0x5C0
	s_biped_leaping_data leaping_data; // 0x5C4
	s_biped_ground_fitting_data ground_fitting_data; // 0x5F4
	s_biped_pivot_data pivot_data; // 0x610
	s_biped_definition(s_biped_definition &); /* compiler_generated() */
	s_biped_definition(s_biped_definition const &); /* compiler_generated() */
	s_biped_definition(); /* compiler_generated() */
	s_biped_definition &operator=(s_biped_definition &); /* compiler_generated() */
	s_biped_definition &operator=(s_biped_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_biped_definition) == 1576, "Invalid s_biped_definition size");
static_assert(offsetof(s_biped_definition, runtime_cosine_stationary_turning_threshold) == 0x478, "s_biped_definition::runtime_cosine_stationary_turning_threshold moved when its reconstructed padding was removed");
static_assert(offsetof(s_biped_definition, leaping_data) == 0x5C4, "s_biped_definition::leaping_data moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_UNITS_BIPED_DEFINITIONS_HPP__
