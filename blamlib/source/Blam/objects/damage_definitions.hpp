#ifndef __BLAM_OBJECTS_DAMAGE_DEFINITIONS_HPP__
#define __BLAM_OBJECTS_DAMAGE_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/function_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

class c_function_definition;
struct real_argb_color;
struct real_bounds;
struct s_damage_effect_definition;
struct s_damage_effect_player_response_block;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_damage_effect_player_response_block
{
	c_enum<enum e_damage_effect_player_response_block_response_type,short> response_type; // 0x0
	short unknown; // 0x2
	c_enum<enum e_damage_effect_player_response_block_type,short> type; // 0x4
	c_enum<enum e_damage_effect_player_response_block_priority,short> priority; // 0x6
	float duration; // 0x8
	c_enum<enum e_damage_fade_effect_function,short> fade_function; // 0xC
	short unknown2; // 0xE
	float maximum_intensity; // 0x10
	real_argb_color color; // 0x14
	float low_frequency_vibration_duration; // 0x24
	c_function_definition low_frequency_vibration_function; // 0x28
	float high_frequency_vibration_duration; // 0x3C
	c_function_definition high_frequency_vibration_function; // 0x40
	unsigned long effect_name; // 0x54
	float duration2; // 0x58
	c_function_definition effect_scale_function; // 0x5C
	s_damage_effect_player_response_block(s_damage_effect_player_response_block &); /* compiler_generated() */
	s_damage_effect_player_response_block(s_damage_effect_player_response_block const &); /* compiler_generated() */
	s_damage_effect_player_response_block(); /* compiler_generated() */
	s_damage_effect_player_response_block &operator=(s_damage_effect_player_response_block &); /* compiler_generated() */
	s_damage_effect_player_response_block &operator=(s_damage_effect_player_response_block const &); /* compiler_generated() */
};
static_assert(sizeof(s_damage_effect_player_response_block) == 112, "Invalid s_damage_effect_player_response_block size");

#pragma pack(push, 4)
struct s_damage_effect_definition
{
	real_bounds radius; // 0x0
	float cutoff_scale; // 0x8
	c_flags<enum e_damage_effect_flags,unsigned long> flags; // 0xC
	c_enum<enum e_damage_effect_side_effect,short> side_effect; // 0x10
	c_enum<enum e_damage_effect_category,short> category; // 0x12
	c_flags<enum e_damage_effect_flags2,unsigned long> flags2; // 0x14
	float area_of_effect_core_radius; // 0x18
	float damage_lower_bound; // 0x1C
	real_bounds damage_upper_bound; // 0x20
	float damage_inner_cone_angle; // 0x28
	float damage_outer_cone_angle; // 0x2C
	float active_camoflage_damage; // 0x30
	float stun; // 0x34
	float max_stun; // 0x38
	float stun_time; // 0x3C
	float instantaneous_acceleration; // 0x40
	float rider_direct_damage_scale; // 0x44
	float rider_max_transfer_damage_scale; // 0x48
	float rider_min_transfer_damage_scale; // 0x4C
	unsigned long general_damage; // 0x50
	unsigned long specific_damage; // 0x54
	unsigned long special_damage; // 0x58
	float ai_stun_radius; // 0x5C
	real_bounds ai_stun_bounds; // 0x60
	float shake_radius; // 0x68
	float emp_radius; // 0x6C
	float aoe_spike_radius; // 0x70
	float aoe_spike_damage_bump; // 0x74
	float unknown_ho; // 0x78
	c_tag_block<s_damage_effect_player_response_block> player_responses; // 0x7C
	s_tag_reference damage_response; // 0x88
	float camera_impulse_duration; // 0x98
	c_enum<enum e_damage_effect_wobble_function,short> camera_impulse_fade_function; // 0x9C
	short unknown; // 0x9E
	float camera_impulse_rotation; // 0xA0
	float camera_impulse_pushback; // 0xA4
	real_bounds camera_impulse_jitter; // 0xA8
	float camera_shake_duration; // 0xB0
	c_enum<enum e_damage_effect_wobble_function,short> camera_shake_falloff_function; // 0xB4
	short unknown2; // 0xB6
	float camera_shake_random_translation; // 0xB8
	float camera_shake_random_rotation; // 0xBC
	c_enum<enum e_damage_effect_wobble_function,short> camera_shake_wobble_function; // 0xC0
	short unknown3; // 0xC2
	float camera_shake_wobble_function_period; // 0xC4
	float camera_shake_wobble_weight; // 0xC8
	s_tag_reference sound; // 0xCC
	float breaking_effect_forward_velocity; // 0xDC
	float breaking_effect_forward_radius; // 0xE0
	float breaking_effect_forward_exponent; // 0xE4
	float breaking_effect_outward_velocity; // 0xE8
	float breaking_effect_outward_radius; // 0xEC
	float breaking_effect_outward_exponent; // 0xF0
	s_damage_effect_definition(s_damage_effect_definition &); /* compiler_generated() */
	s_damage_effect_definition(s_damage_effect_definition const &); /* compiler_generated() */
	s_damage_effect_definition(); /* compiler_generated() */
	s_damage_effect_definition &operator=(s_damage_effect_definition &); /* compiler_generated() */
	s_damage_effect_definition &operator=(s_damage_effect_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_damage_effect_definition) == 244, "Invalid s_damage_effect_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_OBJECTS_DAMAGE_DEFINITIONS_HPP__
