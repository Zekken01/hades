#ifndef __BLAM_CUTSCENE_CINEMATIC_DEFINITIONS_HPP__
#define __BLAM_CUTSCENE_CINEMATIC_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_vector3d;
struct s_camera_frame;
struct s_cinematic_extra_camera_frame;
struct s_cinematic_extra_camera_shot;
struct s_cinematic_scene_definition;
struct s_cinematic_scene_object;
struct s_cinematic_scene_puppet_attachment;
struct s_cinematic_scene_shot;
struct s_cinematic_shot_background_sound;
struct s_cinematic_shot_clip;
struct s_cinematic_shot_cortana_effect;
struct s_cinematic_shot_custom_script;
struct s_cinematic_shot_effect;
struct s_cinematic_shot_extra_camera;
struct s_cinematic_shot_function;
struct s_cinematic_shot_function_keyframe;
struct s_cinematic_shot_lighting;
struct s_cinematic_shot_screen_effect;
struct s_cinematic_shot_sound;
struct s_cinematic_shot_user_input_constraints;
struct s_tag_data;
struct s_tag_reference;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

struct s_cinematic_scene_puppet_attachment
{
	long unknown_01; // 0x0
	long unknown_02; // 0x4
	long unknown_03; // 0x8
	long unknown_04; // 0xC
	long unknown_05; // 0x10
	long unknown_06; // 0x14
	long unknown_07; // 0x18
	long unknown_08; // 0x1C
	long unknown_09; // 0x20
	long unknown_10; // 0x24
	s_tag_reference unknown_11; // 0x28
};
static_assert(sizeof(s_cinematic_scene_puppet_attachment) == 56, "Invalid s_cinematic_scene_puppet_attachment size");

#pragma pack(push, 4)
struct s_cinematic_scene_object
{
	char import_name[32]; // 0x0
	unsigned long name; // 0x20
	unsigned long variant; // 0x24
	s_tag_reference animation; // 0x28
	s_tag_reference puppet_object; // 0x38
	c_flags<enum e_cinematic_object_flags,long> flags; // 0x48
	long unknown_02; // 0x4C
	long unknown_03; // 0x50
	s_tag_data import_script; // 0x54
	c_tag_block<s_cinematic_scene_puppet_attachment> attachments; // 0x68
	s_cinematic_scene_object(s_cinematic_scene_object &); /* compiler_generated() */
	s_cinematic_scene_object(s_cinematic_scene_object const &); /* compiler_generated() */
	s_cinematic_scene_object(); /* compiler_generated() */
	s_cinematic_scene_object &operator=(s_cinematic_scene_object &); /* compiler_generated() */
	s_cinematic_scene_object &operator=(s_cinematic_scene_object const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_scene_object) == 116, "Invalid s_cinematic_scene_object size");

#pragma pack(push, 4)
struct s_cinematic_shot_lighting
{
	long unknown_00; // 0x0
	s_tag_reference cinematic_light; // 0x4
	long owner_puppet_index; // 0x14
	unsigned long marker; // 0x18
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_shot_lighting) == 28, "Invalid s_cinematic_shot_lighting size");

#pragma pack(push, 4)
struct s_cinematic_shot_clip
{
	real_point3d plane_center; // 0x0
	real_vector3d plane_direction; // 0xC
	long frame_start; // 0x18
	long frame_end; // 0x1C
	c_tag_block<long> puppet_indices; // 0x20
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_shot_clip) == 44, "Invalid s_cinematic_shot_clip size");

#pragma pack(push, 4)
struct s_cinematic_shot_sound
{
	s_tag_reference sound; // 0x0
	long frame; // 0x10
	float unknown_01; // 0x14
	unsigned long unknown_02; // 0x18
	long unknown_03; // 0x1C
	unsigned long unknown_04; // 0x20
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_shot_sound) == 36, "Invalid s_cinematic_shot_sound size");

struct s_cinematic_shot_background_sound
{
	long unknown_00; // 0x0
	s_tag_reference sound; // 0x4
	long frame; // 0x14
};
static_assert(sizeof(s_cinematic_shot_background_sound) == 24, "Invalid s_cinematic_shot_background_sound size");

#pragma pack(push, 4)
struct s_cinematic_shot_effect
{
	s_tag_reference effect; // 0x0
	long frame; // 0x10
	unsigned long marker; // 0x14
	long owner_puppet_index; // 0x18
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_shot_effect) == 28, "Invalid s_cinematic_shot_effect size");

struct s_cinematic_shot_function_keyframe
{
	long flags; // 0x0
	long frame_index; // 0x4
	float value; // 0x8
	float interpolation_time; // 0xC
};
static_assert(sizeof(s_cinematic_shot_function_keyframe) == 16, "Invalid s_cinematic_shot_function_keyframe size");

#pragma pack(push, 4)
struct s_cinematic_shot_function
{
	long owner_puppet_index; // 0x0
	unsigned long target_function_name; // 0x4
	c_tag_block<s_cinematic_shot_function_keyframe> keyframes; // 0x8
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_shot_function) == 20, "Invalid s_cinematic_shot_function size");

struct s_cinematic_shot_screen_effect
{
	s_tag_reference effect; // 0x0
	long start_frame; // 0x10
	long end_frame; // 0x14
};
static_assert(sizeof(s_cinematic_shot_screen_effect) == 24, "Invalid s_cinematic_shot_screen_effect size");

#pragma pack(push, 4)
struct s_cinematic_shot_cortana_effect
{
	s_tag_reference effect; // 0x0
	long unknown; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_shot_cortana_effect) == 20, "Invalid s_cinematic_shot_cortana_effect size");

struct s_cinematic_shot_custom_script
{
	long frame; // 0x0
	s_tag_data import_script; // 0x4
	s_cinematic_shot_custom_script(s_cinematic_shot_custom_script &); /* compiler_generated() */
	s_cinematic_shot_custom_script(s_cinematic_shot_custom_script const &); /* compiler_generated() */
	s_cinematic_shot_custom_script(); /* compiler_generated() */
	s_cinematic_shot_custom_script &operator=(s_cinematic_shot_custom_script &); /* compiler_generated() */
	s_cinematic_shot_custom_script &operator=(s_cinematic_shot_custom_script const &); /* compiler_generated() */
};
static_assert(sizeof(s_cinematic_shot_custom_script) == 24, "Invalid s_cinematic_shot_custom_script size");

#pragma pack(push, 4)
struct s_cinematic_shot_user_input_constraints
{
	short unknown_01; // 0x0
	short unknown_02; // 0x2
	long ticks; // 0x4
	short_rectangle2d constraint_boundaries; // 0x8
	float unknown_03; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_shot_user_input_constraints) == 20, "Invalid s_cinematic_shot_user_input_constraints size");

#pragma pack(push, 4)
struct s_camera_frame
{
	real_point3d position; // 0x0
	real_vector3d forward; // 0xC
	real_vector3d up; // 0x18
	float unknown_00; // 0x24
	float unknown_01; // 0x28
	float field_of_view; // 0x2C
	long depth_of_field; // 0x30
	float near_focal_plane_distance; // 0x34
	float far_focal_plane_distance; // 0x38
	float focal_depth; // 0x3C
	float blur_amount; // 0x40
};
#pragma pack(pop)
static_assert(sizeof(s_camera_frame) == 68, "Invalid s_camera_frame size");

#pragma pack(push, 4)
struct s_cinematic_scene_shot
{
	s_tag_data opening_import_script; // 0x0
	long unknown_01; // 0x14
	long unknown_02; // 0x18
	float unknown_03; // 0x1C
	c_tag_block<s_cinematic_shot_lighting> lighting; // 0x20
	c_tag_block<s_cinematic_shot_clip> clips; // 0x2C
	c_tag_block<s_cinematic_shot_sound> sounds; // 0x38
	c_tag_block<s_cinematic_shot_background_sound> background_sounds; // 0x44
	c_tag_block<s_cinematic_shot_effect> effects; // 0x50
	c_tag_block<s_cinematic_shot_function> functions; // 0x5C
	c_tag_block<s_cinematic_shot_screen_effect> screen_effects; // 0x68
	c_tag_block<s_cinematic_shot_cortana_effect> cortana_effects; // 0x74
	c_tag_block<s_cinematic_shot_custom_script> custom_scripts; // 0x80
	c_tag_block<s_cinematic_shot_user_input_constraints> user_input_constraints; // 0x8C
	s_tag_data import_script1; // 0x98
	long frame_count; // 0xAC
	c_tag_block<s_camera_frame> camera_frames; // 0xB0
	s_cinematic_scene_shot(s_cinematic_scene_shot &); /* compiler_generated() */
	s_cinematic_scene_shot(s_cinematic_scene_shot const &); /* compiler_generated() */
	s_cinematic_scene_shot(); /* compiler_generated() */
	s_cinematic_scene_shot &operator=(s_cinematic_scene_shot &); /* compiler_generated() */
	s_cinematic_scene_shot &operator=(s_cinematic_scene_shot const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_scene_shot) == 188, "Invalid s_cinematic_scene_shot size");

struct s_cinematic_extra_camera_frame
{
	long flags; // 0x0
	s_camera_frame frame_data; // 0x4
};
static_assert(sizeof(s_cinematic_extra_camera_frame) == 72, "Invalid s_cinematic_extra_camera_frame size");

#pragma pack(push, 4)
struct s_cinematic_extra_camera_shot
{
	c_tag_block<s_cinematic_extra_camera_frame> camera_frames; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_extra_camera_shot) == 12, "Invalid s_cinematic_extra_camera_shot size");

#pragma pack(push, 4)
struct s_cinematic_shot_extra_camera
{
	unsigned long name; // 0x0
	unsigned long type; // 0x4
	c_tag_block<s_cinematic_extra_camera_shot> shots; // 0x8
};
#pragma pack(pop)
static_assert(sizeof(s_cinematic_shot_extra_camera) == 20, "Invalid s_cinematic_shot_extra_camera size");

struct s_cinematic_scene_definition
{
	unsigned long name; // 0x0
	char anchor_name[32]; // 0x4
	long unknown_01; // 0x24
	s_tag_data import_script; // 0x28
	c_tag_block<s_cinematic_scene_object> objects; // 0x3C
	c_tag_block<s_cinematic_scene_shot> shots; // 0x48
	c_tag_block<s_cinematic_shot_extra_camera> extra_camera_frame_data; // 0x54
	s_tag_data import_script2; // 0x60
	long unknown_02; // 0x74
	s_cinematic_scene_definition(s_cinematic_scene_definition &); /* compiler_generated() */
	s_cinematic_scene_definition(s_cinematic_scene_definition const &); /* compiler_generated() */
	s_cinematic_scene_definition(); /* compiler_generated() */
	s_cinematic_scene_definition &operator=(s_cinematic_scene_definition &); /* compiler_generated() */
	s_cinematic_scene_definition &operator=(s_cinematic_scene_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_cinematic_scene_definition) == 120, "Invalid s_cinematic_scene_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CUTSCENE_CINEMATIC_DEFINITIONS_HPP__
