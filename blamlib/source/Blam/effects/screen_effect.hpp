#ifndef __BLAM_EFFECTS_SCREEN_EFFECT_HPP__
#define __BLAM_EFFECTS_SCREEN_EFFECT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/function_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_function_definition;
struct real_rectangle2d;
struct real_rgb_color;
struct real_vector3d;
struct s_area_screen_effect_definition;
struct s_cinematic_screen_effect;
struct s_datum;
struct s_screen_effect_camera_settings;
struct s_screen_effect_datum;
struct s_screen_effect_settings;
struct s_screen_effect_shader_sample;
struct s_screen_effect_shader_sample_result;
struct s_single_screen_effect_definition;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_screen_effect_settings
{
	float exposure_boost; // 0x0
	float exposure_deboost; // 0x4
	float hue_left; // 0x8
	float hue_right; // 0xC
	float saturation; // 0x10
	float desaturation; // 0x14
	float contrast_enhance; // 0x18
	float gamma_enhance; // 0x1C
	float gamma_reduce; // 0x20
	float bright_noise; // 0x24
	float dark_noise; // 0x28
	real_rgb_color color_filter; // 0x2C
	real_rgb_color color_floor; // 0x38
	float tron; // 0x44
	float motion_suck; // 0x48
	real_vector3d motion_suck_direction; // 0x4C
	float horizontal_blur; // 0x58
	float vertical_blur; // 0x5C
	float vision_mode; // 0x60
	float vision_noise; // 0x64
	float hud_fade; // 0x68
	void set_defaults();
	void accumulate_settings(s_screen_effect_settings const *settings, real_vector3d const *camera_to_effect, float falloff);
};
#pragma pack(pop)
static_assert(sizeof(s_screen_effect_settings) == 108, "Invalid s_screen_effect_settings size");

#pragma pack(push, 4)
struct s_single_screen_effect_definition
{
	public:
	enum e_flags
	{
		_debug_disable_bit = 0,
		_allow_effect_outside_radius_bit,
		_unattached_bit,
		_first_person_only_bit,
		_third_person_only_bit,
		_disable_cinematic_camera_falloffs_bit,
		_only_affects_attached_object_bit,
	};
	enum e_hidden_flags
	{
		_update_thread_bit = 0,
		_render_thread_bit,
	};
#pragma pack(push, 4)
	struct s_object_falloff
	{
		unsigned long input_variable; // 0x0
		unsigned long range_variable; // 0x4
		c_function_definition function; // 0x8
		s_object_falloff(s_object_falloff &); /* compiler_generated() */
		s_object_falloff(s_object_falloff const &); /* compiler_generated() */
		s_object_falloff(); /* compiler_generated() */
		s_object_falloff &operator=(s_object_falloff &); /* compiler_generated() */
		s_object_falloff &operator=(s_object_falloff const &); /* compiler_generated() */
	};
#pragma pack(pop)
	static_assert(sizeof(s_object_falloff) == 28, "Invalid s_object_falloff size");
	public:
	unsigned long name; // 0x0
	c_flags<enum e_flags,unsigned short> flags; // 0x4
	c_flags<enum e_hidden_flags,unsigned short> hidden_flags; // 0x6
	float maximum_distance; // 0x8
	c_function_definition distance_falloff_function; // 0xC
	float delay; // 0x20
	float lifetime; // 0x24
	c_function_definition time_evoluation_function; // 0x28
	c_function_definition angle_falloff_function; // 0x3C
	s_object_falloff object_falloff; // 0x50
	s_screen_effect_settings settings; // 0x6C
	float fov_in; // 0xD8
	float fov_out; // 0xDC
	float screen_shake; // 0xE0
	s_tag_reference screen_shader; // 0xE4
	bool is_visible(float time_alive_seconds, long attach_object_index, long output_user_index);
	float evaluate_falloff(float distance, float angle, float time_alive, long attach_object_index, long output_user_index, float *out_t);
	s_single_screen_effect_definition(s_single_screen_effect_definition &); /* compiler_generated() */
	s_single_screen_effect_definition(s_single_screen_effect_definition const &); /* compiler_generated() */
	s_single_screen_effect_definition(); /* compiler_generated() */
	s_single_screen_effect_definition &operator=(s_single_screen_effect_definition &); /* compiler_generated() */
	s_single_screen_effect_definition &operator=(s_single_screen_effect_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_single_screen_effect_definition) == 244, "Invalid s_single_screen_effect_definition size");

#pragma pack(push, 4)
struct s_area_screen_effect_definition
{
	public:
	enum e_global_flags
	{
		_play_sequentially_bit = 0,
		_debug_this_screen_effect_bit,
		_force_delete_when_attached_to_dead_object_bit,
		_force_max_one_per_object_bit,
	};
	enum e_global_hidden_flags
	{
		_hidden_flags_update_thread_bit = 0,
		_hidden_flags_render_thread_bit,
	};
	public:
	__int32 version; // 0x0
	c_flags<enum e_global_flags,unsigned short> global_flags; // 0x4
	c_flags<enum e_global_hidden_flags,unsigned short> global_hidden_flags; // 0x6
	c_tag_block<s_single_screen_effect_definition> screen_effects; // 0x8
	static _inline s_area_screen_effect_definition *get(long definition_index);
	s_area_screen_effect_definition(s_area_screen_effect_definition &); /* compiler_generated() */
	s_area_screen_effect_definition(s_area_screen_effect_definition const &); /* compiler_generated() */
	s_area_screen_effect_definition(); /* compiler_generated() */
	s_area_screen_effect_definition &operator=(s_area_screen_effect_definition &); /* compiler_generated() */
	s_area_screen_effect_definition &operator=(s_area_screen_effect_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_area_screen_effect_definition) == 20, "Invalid s_area_screen_effect_definition size");

#pragma pack(push, 4)
struct s_screen_effect_datum :
	public s_datum
{
	public:
	enum e_flags
	{
		_cannot_die_bit = 0,
		_unknown1_bit,
		_destroyed_with_object_bit,
	};
	enum e_type
	{
		_type_unattached = 0,
		_type_attached,
	};
	public:
	c_enum<enum e_type,char> type; // 0x2
	c_flags<enum e_flags,unsigned char> flags; // 0x3
	long definition_index; // 0x4
	float alive_time_in_seconds; // 0x8
	real_point3d position; // 0xC
	long attach_object_index; // 0x18
	short attach_node_index; // 0x1C
	real_point3d attach_relative_position; // 0x20
	real_rectangle2d bounds; // 0x2C
	bool update_position();
	s_screen_effect_datum(s_screen_effect_datum &); /* compiler_generated() */
	s_screen_effect_datum(s_screen_effect_datum const &); /* compiler_generated() */
	s_screen_effect_datum(); /* compiler_generated() */
	s_screen_effect_datum &operator=(s_screen_effect_datum &); /* compiler_generated() */
	s_screen_effect_datum &operator=(s_screen_effect_datum const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_screen_effect_datum) == 60, "Invalid s_screen_effect_datum size");

#pragma pack(push, 4)
struct s_screen_effect_shader_sample
{
	long render_method_index; // 0x0
	float falloff; // 0x4
	float falloff_t; // 0x8
	long layer; // 0xC
	unsigned char __pad0[4]; // 0x10
	real_rectangle2d bounds; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_screen_effect_shader_sample) == 36, "Invalid s_screen_effect_shader_sample size");

#pragma pack(push, 4)
struct s_screen_effect_shader_sample_result
{
	s_screen_effect_shader_sample samples[8]; // 0x0
	long sample_count; // 0x120
	void accumulate_settings(s_tag_reference const *shader, float falloff, float t, long attach_object_index, real_rectangle2d const *bounds);
};
#pragma pack(pop)
static_assert(sizeof(s_screen_effect_shader_sample_result) == 292, "Invalid s_screen_effect_shader_sample_result size");

struct s_cinematic_screen_effect
{
	long shot_screen_effect_index; // 0x0
	unsigned long screen_effect_index; // 0x4
};
static_assert(sizeof(s_cinematic_screen_effect) == 8, "Invalid s_cinematic_screen_effect size");

struct s_screen_effect_camera_settings
{
	float fov_in; // 0x0
	float fov_out; // 0x4
	float screen_shake; // 0x8
};
static_assert(sizeof(s_screen_effect_camera_settings) == 12, "Invalid s_screen_effect_camera_settings size");

/* ---------- prototypes */

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x107C1D40

/* ---------- globals */

/* ---------- public code */

_inline s_area_screen_effect_definition *s_area_screen_effect_definition::get(long definition_index) // 0x107C1D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@s_area_screen_effect_definition@@SAPAU1@J@Z");
	// long definition_index;
	// function call : void *(*const)(unsigned long, long)

	return (s_area_screen_effect_definition *)tag_get(0x73656663, definition_index);
}

/* ---------- private code */

#endif // __BLAM_EFFECTS_SCREEN_EFFECT_HPP__
