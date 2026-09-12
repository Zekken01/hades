#ifndef __BLAM_UNITS_UNIT_DEFINITIONS_HPP__
#define __BLAM_UNITS_UNIT_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Player/PlayerEmotes.hpp"

/* ---------- forward declarations */

struct real_vector3d;
struct s_object_definition;
struct s_tag_reference;
struct s_target_tracking_type_definition;
struct s_unit_assassination_definition;
struct s_unit_camera_axis_acceleration_definition;
struct s_unit_camera_definition;
struct s_unit_definition;
struct s_unit_dialogue_variant_definition;
struct s_unit_hud_interface_definition;
struct s_unit_metagame_property_definition;
struct s_unit_posture_definition;
struct s_unit_powered_seat_definition;
struct s_unit_seat_acceleration_definition;
struct s_unit_seat_definition;
struct s_unit_target_tracking_definition;
struct s_unit_weapon_definition;

/* ---------- constants */

/* ---------- definitions */

struct s_unit_metagame_property_definition
{
	char flags; // 0x0
	c_enum<enum e_metagame_unit_type,char> metagame_unit_type; // 0x1
	c_enum<enum e_metagame_unit_type,char> metagame_unit_classification; // 0x2
	short points_awarded; // 0x4
	s_unit_metagame_property_definition(s_unit_metagame_property_definition &); /* compiler_generated() */
	s_unit_metagame_property_definition(s_unit_metagame_property_definition const &); /* compiler_generated() */
	s_unit_metagame_property_definition(); /* compiler_generated() */
	s_unit_metagame_property_definition &operator=(s_unit_metagame_property_definition &); /* compiler_generated() */
	s_unit_metagame_property_definition &operator=(s_unit_metagame_property_definition const &); /* compiler_generated() */
	unsigned char __pad1[2]; // 0x6
};
static_assert(sizeof(s_unit_metagame_property_definition) == 8, "Invalid s_unit_metagame_property_definition size");
static_assert(offsetof(s_unit_metagame_property_definition, points_awarded) == 0x4, "s_unit_metagame_property_definition::points_awarded moved when its reconstructed padding was removed");

// s_unit_camera_track_definition is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

struct s_unit_camera_axis_acceleration_definition
{
	float unknown_00; // 0x0
	float unknown_04; // 0x4
	float unknown_08; // 0x8
	float unknown_0C; // 0xC
	float unknown_10; // 0x10
	float unknown_14; // 0x14
};
static_assert(sizeof(s_unit_camera_axis_acceleration_definition) == 24, "Invalid s_unit_camera_axis_acceleration_definition size");

// s_unit_camera_acceleration_definition is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

#pragma pack(push, 4)
struct s_unit_assassination_definition
{
	s_tag_reference response; // 0x0
	s_tag_reference weapon; // 0x10
	unsigned long tool_stow_anchor; // 0x20
	unsigned long tool_hand_marker; // 0x24
	unsigned long tool_marker; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_unit_assassination_definition) == 44, "Invalid s_unit_assassination_definition size");

#pragma pack(push, 4)
struct s_unit_seat_acceleration_definition
{
	real_vector3d range; // 0x0
	float action_scale; // 0xC
	float attach_scale; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_unit_seat_acceleration_definition) == 20, "Invalid s_unit_seat_acceleration_definition size");

struct s_unit_posture_definition
{
	unsigned long name; // 0x0
	real_vector3d pill_fffset; // 0x4
};
static_assert(sizeof(s_unit_posture_definition) == 16, "Invalid s_unit_posture_definition size");

struct s_unit_hud_interface_definition
{
	s_tag_reference unit_hud_interface; // 0x0
};
static_assert(sizeof(s_unit_hud_interface_definition) == 16, "Invalid s_unit_hud_interface_definition size");

#pragma pack(push, 4)
struct s_unit_dialogue_variant_definition
{
	short variant_number; // 0x0
	unsigned char __pad0[2]; // 0x2
	s_tag_reference dialogue; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_unit_dialogue_variant_definition) == 20, "Invalid s_unit_dialogue_variant_definition size");

struct s_unit_powered_seat_definition
{
	float driver_powerup_time; // 0x0
	float driver_powerdown_time; // 0x4
};
static_assert(sizeof(s_unit_powered_seat_definition) == 8, "Invalid s_unit_powered_seat_definition size");

struct s_unit_weapon_definition
{
	s_tag_reference weapon; // 0x0
};
static_assert(sizeof(s_unit_weapon_definition) == 16, "Invalid s_unit_weapon_definition size");

struct s_target_tracking_type_definition
{
	unsigned long tracking_type; // 0x0
};
static_assert(sizeof(s_target_tracking_type_definition) == 4, "Invalid s_target_tracking_type_definition size");

struct s_unit_target_tracking_definition
{
	c_tag_block<s_target_tracking_type_definition> target_tracking_types; // 0x0
	float acquire_time; // 0xC
	float grace_time; // 0x10
	float decay_time; // 0x14
	s_tag_reference tracking_sound; // 0x18
	s_tag_reference locked_sound; // 0x28
};
static_assert(sizeof(s_unit_target_tracking_definition) == 56, "Invalid s_unit_target_tracking_definition size");

#pragma pack(push, 4)
struct s_unit_seat_definition
{
	c_flags<enum e_unit_seat_flags,long> flags; // 0x0
	unsigned long seat_animation; // 0x4
	unsigned long seat_marker_name; // 0x8
	unsigned long entry_marker_name; // 0xC
	unsigned long boarding_grenade_marker; // 0x10
	unsigned long boarding_grenade_string; // 0x14
	unsigned long boarding_melee_string; // 0x18
	unsigned long detach_weapon_string; // 0x1C
	float ping_scale; // 0x20
	float turnover_time; // 0x24
	s_unit_seat_acceleration_definition seat_acceleration; // 0x28
	float ai_scariness; // 0x3C
	c_enum<enum e_unit_seat_type,short> ai_seat_type; // 0x40
	short boarding_seat; // 0x42
	float listener_interpolation_factor; // 0x44
	float yaw_rate_bounds[2]; // 0x48
	float pitch_rate_bounds[2]; // 0x50
	float pitch_interpolation_time; // 0x58
	float speed_reference_bounds[2]; // 0x5C
	float speed_exponent; // 0x64
	s_unit_camera_definition camera; // 0x68
	c_tag_block<s_unit_hud_interface_definition> unit_hud_interface; // 0xA4
	unsigned long enter_seat_string; // 0xB0
	float yaw_range[2]; // 0xB4
	s_tag_reference built_in_gunner; // 0xBC
	float entry_radius; // 0xCC
	float entry_marker_cone_angle; // 0xD0
	float entry_marker_facing_angle; // 0xD4
	float maximum_relative_velocity; // 0xD8
	unsigned long invisible_seat_region; // 0xDC
	long runtime_invisible_seat_region_index; // 0xE0
	s_unit_seat_definition(s_unit_seat_definition &); /* compiler_generated() */
	s_unit_seat_definition(s_unit_seat_definition const &); /* compiler_generated() */
	s_unit_seat_definition(); /* compiler_generated() */
	s_unit_seat_definition &operator=(s_unit_seat_definition &); /* compiler_generated() */
	s_unit_seat_definition &operator=(s_unit_seat_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_unit_seat_definition) == 228, "Invalid s_unit_seat_definition size");

struct s_unit_definition :
	public s_object_definition
{
	c_flags<enum e_unit_object_flags,long> flags; // 0x120
	c_enum<enum e_unit_default_team,short> default_team; // 0x124
	c_enum<enum e_unit_constant_sound_volume,short> constant_sound_volume; // 0x126
	s_tag_reference hologram_unit; // 0x128
	c_tag_block<s_unit_metagame_property_definition> metagame_properties; // 0x138
	s_tag_reference integrated_light_toggle; // 0x144
	float camera_field_of_view; // 0x154
	float camera_stiffness; // 0x158
	s_unit_camera_definition camera; // 0x15C
	s_unit_camera_definition sync_action_camera; // 0x198
	s_unit_assassination_definition assassination; // 0x1D4
	s_unit_seat_acceleration_definition seat_acceleration; // 0x200
	float soft_ping_threshold; // 0x214
	float soft_ping_interrupt_time; // 0x218
	float hard_ping_threshold; // 0x21C
	float hard_ping_interrupt_time; // 0x220
	float feign_death_threshold; // 0x224
	float feign_death_time; // 0x228
	float distance_of_evade_animation; // 0x22C
	float distance_of_dive_animation; // 0x230
	float stunned_movement_threshold; // 0x234
	float feign_death_chance; // 0x238
	float feign_repeat_chance; // 0x23C
	s_tag_reference spawned_turret_character; // 0x240
	short spawned_actor_count_min; // 0x250
	short spawned_actor_count_max; // 0x252
	unsigned long target_aiming_pivot_marker_name; // 0x254
	float aiming_velocity_maximum; // 0x258
	float aiming_acceleration_maximum; // 0x25C
	float casual_aiming_modifier; // 0x260
	float looking_velocity_maximum; // 0x264
	float looking_acceleration_maximum; // 0x268
	unsigned long right_hand_node; // 0x26C
	unsigned long left_hand_node; // 0x270
	unsigned long preferred_gun_node; // 0x274
	s_tag_reference melee_damage; // 0x278
	s_tag_reference boarding_melee_damage; // 0x288
	s_tag_reference boarding_melee_response; // 0x298
	s_tag_reference ejection_melee_damage; // 0x2A8
	s_tag_reference ejection_melee_response; // 0x2B8
	s_tag_reference landing_melee_damage; // 0x2C8
	s_tag_reference flurry_melee_damage; // 0x2D8
	s_tag_reference obstacle_smash_melee_damage; // 0x2E8
	s_tag_reference shield_pop_damage; // 0x2F8
	s_tag_reference assassination_damage; // 0x308
	c_enum<enum e_unit_motion_sensor_blip_size,short> motion_sensor_blip_size; // 0x318
	c_enum<enum e_unit_item_scale,short> item_scale; // 0x31A
	c_tag_block<s_unit_posture_definition> postures; // 0x31C
	c_tag_block<s_unit_hud_interface_definition> hud_interfaces; // 0x328
	c_tag_block<s_unit_dialogue_variant_definition> dialogue_variants; // 0x334
	float motion_tracker_range_modifier; // 0x340
	float grenade_angle; // 0x344
	float grenade_angle_max_elevation; // 0x348
	float grenade_angle_min_elevation; // 0x34C
	float grenade_velocity; // 0x350
	c_enum<enum e_unit_grenade_type,short> grenade_type; // 0x354
	unsigned short grenade_count; // 0x356
	c_tag_block<s_unit_powered_seat_definition> powered_seats; // 0x358
	c_tag_block<s_unit_weapon_definition> weapons; // 0x364
	c_tag_block<s_unit_target_tracking_definition> target_tracking; // 0x370
	c_tag_block<s_unit_seat_definition> seats; // 0x37C
	float emp_radius; // 0x388
	s_tag_reference emp_effect; // 0x38C
	s_tag_reference boost_collision_damage; // 0x39C
	float boost_peak_power; // 0x3AC
	float boost_rise_power; // 0x3B0
	float boost_peak_time; // 0x3B4
	float boost_fall_power; // 0x3B8
	float boost_dead_time; // 0x3BC
	float lipsync_attack_weight; // 0x3C0
	float lipsync_decay_weight; // 0x3C4
	s_tag_reference detach_damage; // 0x3C8
	s_tag_reference detached_weapon; // 0x3D8
	s_unit_definition(s_unit_definition &); /* compiler_generated() */
	s_unit_definition(s_unit_definition const &); /* compiler_generated() */
	s_unit_definition(); /* compiler_generated() */
	s_unit_definition &operator=(s_unit_definition &); /* compiler_generated() */
	s_unit_definition &operator=(s_unit_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_unit_definition) == 1000, "Invalid s_unit_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_UNITS_UNIT_DEFINITIONS_HPP__
