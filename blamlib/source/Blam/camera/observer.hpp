#ifndef __BLAM_CAMERA_OBSERVER_HPP__
#define __BLAM_CAMERA_OBSERVER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

struct real_matrix4x3;
struct real_vector2d;
struct real_vector3d;
struct s_camera_definition;
struct s_cluster_reference;
struct s_observer;
struct s_observer_command;
struct s_observer_depth_of_field;
struct s_observer_globals;
struct s_observer_result;

/* ---------- constants */

/* ---------- definitions */

struct s_observer_depth_of_field
{
	unsigned long flags; // 0x0
	float focus_distance; // 0x4
	float focus_half_width; // 0x8
	float near_plane; // 0xC
	float far_plane; // 0x10
};
static_assert(sizeof(s_observer_depth_of_field) == 20, "Invalid s_observer_depth_of_field size");

struct s_observer_result
{
	real_point3d position; // 0x0
	s_cluster_reference cluster_reference; // 0xC
	real_vector3d translational_velocity; // 0x10
	real_vector3d angular_velocity; // 0x1C
	real_vector3d forward; // 0x28
	real_vector3d up; // 0x34
	float horizontal_field_of_view; // 0x40
	s_observer_depth_of_field depth_of_field; // 0x44
	float aspect_ratio; // 0x58
	real_vector2d focus_offset; // 0x5C
	float focus_distance; // 0x64
	float vertical_field_of_view; // 0x68
	float fov_scale; // 0x6C
};
static_assert(sizeof(s_observer_result) == 112, "Invalid s_observer_result size");
static_assert(offsetof(s_observer_result, translational_velocity) == 0x10, "s_observer_result::translational_velocity moved when its reconstructed padding was removed");

struct s_camera_definition
{
	real_point3d position; // 0x0
	real_vector3d position_shift; // 0xC
	real_vector2d focus_offset; // 0x18
	float focus_distance; // 0x20
	float horizontal_field_of_view; // 0x24
	real_vector3d forward; // 0x28
	real_vector3d up; // 0x34
};
static_assert(sizeof(s_camera_definition) == 64, "Invalid s_camera_definition size");

#pragma pack(push, 4)
struct s_observer_command
{
	long flags; // 0x0
	s_camera_definition camera; // 0x4
	real_vector3d velocity; // 0x44
	real_matrix4x3 relative_object_matrix; // 0x50
	long relative_to_object_index; // 0x84
	real_vector3d target_center; // 0x88
	float smoothing_factor; // 0x94
	long target_object_index; // 0x98
	long ignore_object_index2; // 0x9C
	long collision_mode; // 0xA0
	real_point3d target_origin; // 0xA4
	float target_height; // 0xB0
	float target_bounding_radius; // 0xB4
	unsigned char __pad0[4]; // 0xB8
	char zoom_flags; // 0xBC
	unsigned char __pad1[19]; // 0xBD
	float zoom_change_time; // 0xD0
	unsigned char __pad2[4]; // 0xD4
	s_observer_depth_of_field depth_of_field; // 0xD8
};
#pragma pack(pop)
static_assert(sizeof(s_observer_command) == 236, "Invalid s_observer_command size");

struct s_observer
{
	long head_signature; // 0x0
	s_observer_command *pending_command; // 0x4
	s_observer_command current_command; // 0x8
	char active; // 0xF4
	char field_F5; // 0xF5
	char use_focus_space; // 0xF6
	char field_F7; // 0xF7
	float field_F8; // 0xF8
	long field_FC; // 0xFC
	long field_100; // 0x100
	long field_104; // 0x104
	char result_valid; // 0x108
	s_observer_result result; // 0x10C
	s_camera_definition values; // 0x17C
	real_matrix4x3 focus_space; // 0x1BC
	real_vector3d translational_velocity; // 0x1F0
	float field_1FC[7]; // 0x1FC
	real_vector3d angular_velocity; // 0x218
	real_vector3d field_224; // 0x224
	float field_230[7]; // 0x230
	real_vector3d field_24C; // 0x24C
	float field_258[78]; // 0x258
	real_vector3d field_390; // 0x390
	float field_23C[7]; // 0x39C
	real_vector3d field_3B8; // 0x3B8
	long footer_signature; // 0x3C4
};
static_assert(sizeof(s_observer) == 968, "Invalid s_observer size");
static_assert(offsetof(s_observer, result) == 0x10C, "s_observer::result moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_observer_globals
{
	float current_time; // 0x0
	s_observer observers[4]; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_observer_globals) == 3876, "Invalid s_observer_globals size");

/* ---------- prototypes */

extern s_observer *observer_get(long output_user_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CAMERA_OBSERVER_HPP__
