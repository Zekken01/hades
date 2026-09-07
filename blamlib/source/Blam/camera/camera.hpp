#ifndef __BLAM_CAMERA_CAMERA_HPP__
#define __BLAM_CAMERA_CAMERA_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/camera/observer.hpp"
#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

class c_camera;
struct c_flying_camera;
struct real_euler_angles2d;
struct real_point3d;
struct real_vector3d;
struct s_camera_globals;
struct s_focus_and_distance;
struct s_observer_command;

/* ---------- constants */

enum e_camera_mode
{
	_camera_mode_none = -1,
	_camera_mode_following = 0,
	_camera_mode_orbiting,
	_camera_mode_flying,
	_camera_mode_first_person,
	_camera_mode_dead,
	_camera_mode_static,
	_camera_mode_scripted,
	_camera_mode_authored,
	k_number_of_camera_modes,
};

/* ---------- definitions */

class c_camera
{
public:
	virtual e_camera_mode get_type() = 0;
	virtual long get_perspective() = 0;
	virtual void update(long, float, s_observer_command *) = 0;
	virtual long get_target() = 0;
	virtual void set_target(long) = 0;
	virtual void set_position(real_point3d const *) = 0;
	virtual void set_forward(real_vector3d const *) = 0;
	virtual void set_roll(float) = 0;
	virtual void enable_orientation(bool) = 0;
	virtual void enable_movement(bool) = 0;
	virtual void enable_roll(bool) = 0;
	virtual void handle_deleted_player(long) = 0;
	virtual void handle_deleted_object(long) = 0;
	virtual void unknown_function() = 0;
	long target_object_index; // 0x4
	long base_camera_flags; // 0x8
	long field_C; // 0xC
	c_camera(c_camera &); /* compiler_generated() */
	c_camera(c_camera const &); /* compiler_generated() */
	c_camera(); /* compiler_generated() */
	c_camera &operator=(c_camera &); /* compiler_generated() */
	c_camera &operator=(c_camera const &); /* compiler_generated() */
};
static_assert(sizeof(c_camera) == 16, "Invalid c_camera size");

#pragma pack(push, 4)
struct c_flying_camera :
	public c_camera
{
	real_point3d position; // 0x10
	real_euler_angles2d angles; // 0x1C
	__int32 roll_angle; // 0x24
	float thrust_velocity; // 0x28
	float smoothing_time; // 0x2C
	__int32 field_30; // 0x30
	float unknown_scalar; // 0x34
	unsigned __int32 flags; // 0x38
	c_flying_camera(c_flying_camera &); /* compiler_generated() */
	c_flying_camera(c_flying_camera const &); /* compiler_generated() */
	c_flying_camera(); /* compiler_generated() */
	c_flying_camera &operator=(c_flying_camera &); /* compiler_generated() */
	c_flying_camera &operator=(c_flying_camera const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_flying_camera) == 60, "Invalid c_flying_camera size");

struct s_camera_globals
{
	float field_of_view; // 0x0
	float yaw_scale; // 0x4
	float pitch_scale; // 0x8
	float forward_scale; // 0xC
	float side_scale; // 0x10
	float up_scale; // 0x14
	float transition_time; // 0x18
	float falling_death_transition_time; // 0x1C
	float initial_distance; // 0x20
	float final_distance; // 0x24
	float dead_cam_z_offset; // 0x28
	float dead_cam_maximum_elevation; // 0x2C
	float dead_cam_movement_delay; // 0x30
	float time_to_auto_switch_to_orbiting; // 0x34
	float dead_camera_minimum_falling_velocity; // 0x38
	float maximum_boost_speed; // 0x3C
	float time_to_maximum_boost; // 0x40
	short boost_function; // 0x44
	unsigned char __pad0[2]; // 0x46
	float zoomed_field_of_view; // 0x48
	float zoomed_look_speed; // 0x4C
	float bounding_sphere_radius; // 0x50
	float flying_cam_movement_delay; // 0x54
	float zoom_transition_time; // 0x58
	float vertical_movement_time_to_max_speed; // 0x5C
	short vertical_movement_function; // 0x60
	unsigned char __pad1[2]; // 0x62
	float survival_switch_time; // 0x64
	float minimum_distance; // 0x68
	float maximum_distance; // 0x6C
	float orbit_cam_movement_delay; // 0x70
	float orbit_cam_z_offset; // 0x74
	float orbit_cam_minimum_elevation; // 0x78
	float orbit_cam_maximum_elevation; // 0x7C
	float max_playback_speed; // 0x80
	float fade_out_time; // 0x84
	float fade_in_time; // 0x88
	float enter_vehicle_transition_time; // 0x8C
	float exit_vehicle_transition_time; // 0x90
};
static_assert(sizeof(s_camera_globals) == 148, "Invalid s_camera_globals size");

struct s_focus_and_distance
{
	real_point3d position; // 0x0
	float distance; // 0xC
};
static_assert(sizeof(s_focus_and_distance) == 16, "Invalid s_focus_and_distance size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CAMERA_CAMERA_HPP__
