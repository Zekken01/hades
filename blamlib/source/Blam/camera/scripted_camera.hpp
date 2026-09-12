#ifndef __BLAM_CAMERA_SCRIPTED_CAMERA_HPP__
#define __BLAM_CAMERA_SCRIPTED_CAMERA_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct real_quaternion;
struct real_vector3d;
struct s_camera_pan_navigator;
struct s_scripted_camera_globals;

/* ---------- constants */

enum e_scripted_camera_mode
{
	_scripted_camera_none = 0,
	_scripted_camera_relative_to_object,
	_scripted_camera_pan_navigator,
	_scripted_camera_animated,
	_scripted_camera_fake_first_person,
	_scripted_camera_cinematic_flying,
	k_number_of_scripted_camera_modes,
};

/* ---------- definitions */

struct s_camera_pan_navigator
{
	__int32 ticks_elapsed; // 0x0
	float field_4; // 0x4
	short easing_type; // 0x8
	float end_time; // 0xC
	real_quaternion rotation; // 0x10
};
static_assert(sizeof(s_camera_pan_navigator) == 32, "Invalid s_camera_pan_navigator size");
static_assert(offsetof(s_camera_pan_navigator, end_time) == 0xC, "s_camera_pan_navigator::end_time moved when its reconstructed padding was removed");

struct s_scripted_camera_globals
{
	char field_0; // 0x0
	char update; // 0x1
	c_enum<enum e_scripted_camera_mode,short> mode; // 0x2
	float seconds_elapsed; // 0x4
	float field_of_view_change_duration; // 0x8
	float field_of_view; // 0xC
	float destination_field_of_view; // 0x10
	__int32 ticks_remaining; // 0x14
	real_vector3d pan_start_point; // 0x18
	real_vector3d forward; // 0x24
	real_vector3d up; // 0x30
	unsigned long relative_to_object_index; // 0x3C
	long cinematic_scene_tag_index; // 0x40
	__int32 scene_shot_index; // 0x44
	__int32 scene_frame_index; // 0x48
	__int32 frame_index_rounded; // 0x4C
	__int32 cutscene_flag_index; // 0x50
	bool cinematic_is_anchored; // 0x54
	unsigned long extra_camera_shot_name; // 0x58
	bool render_texture_camera_active; // 0x5C
	s_camera_pan_navigator pan_navigator; // 0x60
	real_quaternion unknown_rotation; // 0x80
	real_vector3d position_offset; // 0x90
	real_vector3d unknown_offset; // 0x9C
	float field_A8; // 0xA8
	real_vector3d field_AC; // 0xAC
	float horizontal_view_offset; // 0xB8
	float vertical_view_offset; // 0xBC
	__int32 field_C0; // 0xC0
	float field_C4; // 0xC4
	float field_C8; // 0xC8
	float field_CC; // 0xCC
	float field_D0; // 0xD0
	float field_D4; // 0xD4
	float field_D8; // 0xD8
	float field_DC; // 0xDC
	float field_E0; // 0xE0
	float field_E4; // 0xE4
	float field_E8; // 0xE8
	__int32 input_constraint_ticks_remaining; // 0xEC
	s_scripted_camera_globals(s_scripted_camera_globals &); /* compiler_generated() */
	s_scripted_camera_globals(s_scripted_camera_globals const &); /* compiler_generated() */
	s_scripted_camera_globals(); /* compiler_generated() */
	s_scripted_camera_globals &operator=(s_scripted_camera_globals &); /* compiler_generated() */
	s_scripted_camera_globals &operator=(s_scripted_camera_globals const &); /* compiler_generated() */
};
static_assert(sizeof(s_scripted_camera_globals) == 240, "Invalid s_scripted_camera_globals size");
static_assert(offsetof(s_scripted_camera_globals, extra_camera_shot_name) == 0x58, "s_scripted_camera_globals::extra_camera_shot_name moved when its reconstructed padding was removed");
static_assert(offsetof(s_scripted_camera_globals, pan_navigator) == 0x60, "s_scripted_camera_globals::pan_navigator moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CAMERA_SCRIPTED_CAMERA_HPP__
