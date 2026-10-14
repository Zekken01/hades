#ifndef __BLAM_RENDER_RENDER_LENS_FLARES_HPP__
#define __BLAM_RENDER_RENDER_LENS_FLARES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/function_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

class c_function_definition;
struct real_rgb_color;
struct real_vector2d;
struct s_lens_flare_definition;
struct s_tag_block;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_lens_flare_definition
{
	public:
	enum e_flags
	{
		_occlusion_testing_box_with_lens_flare_bit = 0,
		_no_occlusion_test_bit,
		_only_render_in_first_person_bit,
		_only_render_in_third_person_bit,
		_use_simple_occlusion_box_test_bit,
		_no_reflection_opacity_feedback_bit,
		_scale_by_marker_bit,
		_dont_autofade_bit,
		_dont_render_while_zoomed_bit,
	};
#pragma pack(push, 4)
	struct s_reflection
	{
		unsigned short flags; // 0x0
		short bitmap_group_index; // 0x2
		char bitmap_index; // 0x4
		s_tag_reference bitmap_override; // 0x8
		float rotation_offset; // 0x18
		float axis_offset; // 0x1C
		real_vector2d offset_bounds; // 0x20
		c_function_definition radius_curve_function; // 0x28
		c_function_definition scale_curve_x_function; // 0x3C
		c_function_definition scale_curve_y_function; // 0x50
		c_function_definition brightness_curve_function; // 0x64
		real_rgb_color tint_color; // 0x78
		float tint_modulation_factor; // 0x84
		float tint_power; // 0x88
		s_reflection(s_reflection &); /* compiler_generated() */
		s_reflection(s_reflection const &); /* compiler_generated() */
		s_reflection(); /* compiler_generated() */
		s_reflection &operator=(s_reflection &); /* compiler_generated() */
		s_reflection &operator=(s_reflection const &); /* compiler_generated() */
	};
#pragma pack(pop)
	static_assert(sizeof(s_reflection) == 140, "Invalid s_reflection size");
	public:
	float falloff_angle; // 0x0
	float cutoff_angle; // 0x4
	float occlusion_reflection_index; // 0x8
	float occlusion_offset_distance; // 0xC
	short occlusion_offset_direction; // 0x10
	short occlusion_inner_radius_scale; // 0x12
	float near_fade_begin_distance; // 0x14
	float near_fade_end_distance; // 0x18
	float near_fade_distance; // 0x1C
	float far_fade_distance; // 0x20
	s_tag_reference bitmap; // 0x24
	c_flags<enum e_flags,unsigned short> flags; // 0x34
	unsigned short runtime_flags; // 0x36
	short rotation_function; // 0x38
	float rotation_function_scale; // 0x3C
	short falloff_function; // 0x40
	c_tag_block<s_reflection> reflections; // 0x44
	unsigned long animation_flags; // 0x50
	s_tag_block time_brightness; // 0x54
	s_tag_block age_brightness; // 0x60
	s_tag_block time_color; // 0x6C
	s_tag_block age_color; // 0x78
	s_tag_block time_rotation; // 0x84
	s_tag_block age_rotation; // 0x90
	s_lens_flare_definition(s_lens_flare_definition &); /* compiler_generated() */
	s_lens_flare_definition(s_lens_flare_definition const &); /* compiler_generated() */
	s_lens_flare_definition(); /* compiler_generated() */
	s_lens_flare_definition &operator=(s_lens_flare_definition &); /* compiler_generated() */
	s_lens_flare_definition &operator=(s_lens_flare_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_lens_flare_definition) == 156, "Invalid s_lens_flare_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_RENDER_LENS_FLARES_HPP__
