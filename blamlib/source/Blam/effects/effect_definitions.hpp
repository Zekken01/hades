#ifndef __BLAM_EFFECTS_EFFECT_DEFINITIONS_HPP__
#define __BLAM_EFFECTS_EFFECT_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/particle_emitter_definitions.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct real_euler_angles2d;
struct s_effect;
struct s_effect_conical_distribution;
struct s_effect_event;
struct s_effect_event_acceleration;
struct s_effect_event_part;
struct s_effect_location;
struct s_particle_system_definition;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_effect_location
{
	unsigned long marker_name; // 0x0
	long unknown1; // 0x4
	char unknown2; // 0x8
	char unknown3; // 0x9
	char unknown4; // 0xA
	char unknown5; // 0xB
};
static_assert(sizeof(s_effect_location) == 12, "Invalid s_effect_location size");

struct s_effect_event_part
{
	c_enum<enum e_effect_environment,short> create_in_environment; // 0x0
	c_enum<enum e_effect_violence_mode,short> create_in_disposition; // 0x2
	short primary_location; // 0x4
	short secondary_location; // 0x6
	c_flags<enum e_effect_event_part_flags,unsigned short> flags; // 0x8
	c_enum<enum e_effect_priority,char> priority; // 0xA
	c_enum<enum e_effect_camera_mode,char> camera_mode; // 0xB
	unsigned long runtime_base_group_tag; // 0xC
	s_tag_reference type; // 0x10
	real_bounds velocity_bounds; // 0x20
	real_euler_angles2d velocity_orientation; // 0x28
	float velocity_cone_angle; // 0x30
	real_bounds angular_velocity_bounds; // 0x34
	real_bounds radius_modifier_bounds; // 0x3C
	real_point3d relative_offset; // 0x44
	real_euler_angles2d relative_orientation; // 0x50
	c_enum<enum e_effect_event_part_scales,long> a_scales_values; // 0x58
	c_enum<enum e_effect_event_part_scales,long> b_scales_values; // 0x5C
	s_effect_event_part(s_effect_event_part &); /* compiler_generated() */
	s_effect_event_part(s_effect_event_part const &); /* compiler_generated() */
	s_effect_event_part(); /* compiler_generated() */
	s_effect_event_part &operator=(s_effect_event_part &); /* compiler_generated() */
	s_effect_event_part &operator=(s_effect_event_part const &); /* compiler_generated() */
};
static_assert(sizeof(s_effect_event_part) == 96, "Invalid s_effect_event_part size");

struct s_effect_event_acceleration
{
	c_enum<enum e_effect_event_acceleration_create_in_environment,short> create_in_environment; // 0x0
	c_enum<enum e_effect_event_acceleration_create_in_disposition,short> create_in_disposition; // 0x2
	short location_index; // 0x4
	unsigned char unused[2]; // 0x6
	float acceleration_amount; // 0x8
	float inner_cone_angle; // 0xC
	float outer_cone_angle; // 0x10
	s_effect_event_acceleration(s_effect_event_acceleration &); /* compiler_generated() */
	s_effect_event_acceleration(s_effect_event_acceleration const &); /* compiler_generated() */
	s_effect_event_acceleration(); /* compiler_generated() */
	s_effect_event_acceleration &operator=(s_effect_event_acceleration &); /* compiler_generated() */
	s_effect_event_acceleration &operator=(s_effect_event_acceleration const &); /* compiler_generated() */
};
static_assert(sizeof(s_effect_event_acceleration) == 20, "Invalid s_effect_event_acceleration size");

#pragma pack(push, 4)
struct s_effect_event
{
	unsigned long name; // 0x0
	long unknown; // 0x4
	char unknown2; // 0x8
	char unknown3; // 0x9
	char unknown4; // 0xA
	char unknown5; // 0xB
	float skip_fraction; // 0xC
	float delay_bounds_min; // 0x10
	float delay_bounds_max; // 0x14
	float duration_bounds_min; // 0x18
	float duration_bounds_max; // 0x1C
	c_tag_block<s_effect_event_part> parts; // 0x20
	c_tag_block<s_effect_event_acceleration> accelerations; // 0x2C
	c_tag_block<s_particle_system_definition> particle_systems; // 0x38
};
#pragma pack(pop)
static_assert(sizeof(s_effect_event) == 68, "Invalid s_effect_event size");

struct s_effect_conical_distribution
{
	short projection_yaw_count; // 0x0
	short projection_pitch_count; // 0x2
	float distribution_exponent; // 0x4
	float spread; // 0x8
};
static_assert(sizeof(s_effect_conical_distribution) == 12, "Invalid s_effect_conical_distribution size");

struct s_effect
{
	c_flags<enum e_effect_flags,long> flags; // 0x0
	unsigned long fixed_random_seed; // 0x4
	float overlap_threshold; // 0x8
	float continue_if_within; // 0xC
	float death_delay; // 0x10
	char unknown1; // 0x14
	char unknown2; // 0x15
	char unknown3; // 0x16
	char unknown4; // 0x17
	short loop_start_event; // 0x18
	c_enum<enum e_effect_priority,short> priority; // 0x1A
	unsigned long unknown5; // 0x1C
	c_tag_block<s_effect_location> locations; // 0x20
	c_tag_block<s_effect_event> events; // 0x2C
	s_tag_reference looping_sound; // 0x38
	char location_index; // 0x48
	char event_index; // 0x49
	short unknown11; // 0x4A
	float always_play_distance; // 0x4C
	float never_play_distance; // 0x50
	float runtime_lightprobe_death_delay; // 0x54
	float runtime_local_space_death_delay; // 0x58
	c_tag_block<s_effect_conical_distribution> conical_distributions; // 0x5C
	s_effect(s_effect &); /* compiler_generated() */
	s_effect(s_effect const &); /* compiler_generated() */
	s_effect(); /* compiler_generated() */
	s_effect &operator=(s_effect &); /* compiler_generated() */
	s_effect &operator=(s_effect const &); /* compiler_generated() */
};
static_assert(sizeof(s_effect) == 104, "Invalid s_effect size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_EFFECTS_EFFECT_DEFINITIONS_HPP__
