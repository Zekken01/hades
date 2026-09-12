#ifndef __BLAM_RENDER_VIEWS_RENDER_CAMERA_HPP__
#define __BLAM_RENDER_VIEWS_RENDER_CAMERA_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_matrix4x3;
struct real_plane3d;
struct real_point2d;
struct real_point3d;
struct real_rectangle2d;
struct real_vector3d;
struct s_render_camera;
struct s_render_projection;
struct short_point_2d;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

struct s_render_projection
{
	real_matrix4x3 world_to_view; // 0x0
	real_matrix4x3 view_to_world; // 0x34
	real_rectangle2d projection_bounds; // 0x68
	float projection_matrix[4][4]; // 0x78
	float scale_width; // 0xB8
	float scale_height; // 0xBC
};
static_assert(sizeof(s_render_projection) == 192, "Invalid s_render_projection size");

struct s_render_camera
{
	real_point3d position; // 0x0
	real_vector3d forward; // 0xC
	real_vector3d up; // 0x18
	char field_24; // 0x24
	float vertical_field_of_view; // 0x28
	float horizontal_field_of_view; // 0x2C
	short_rectangle2d window_pixel_bounds; // 0x30
	short_rectangle2d fullscreen_pixel_bounds; // 0x38
	short_point_2d unknown_chud_offset; // 0x40
	short_rectangle2d render_pixel_bounds; // 0x44
	short_rectangle2d render_title_safe_pixel_bounds; // 0x4C
	short_rectangle2d display_pixel_bounds; // 0x54
	float z_near; // 0x5C
	float z_far; // 0x60
	real_plane3d plane; // 0x64
	bool far_flag; // 0x74
	float field_78; // 0x78
	float field_7C; // 0x7C
	float x_scale; // 0x80
	float y_scale; // 0x84
};
static_assert(sizeof(s_render_camera) == 136, "Invalid s_render_camera size");
static_assert(offsetof(s_render_camera, vertical_field_of_view) == 0x28, "s_render_camera::vertical_field_of_view moved when its reconstructed padding was removed");
static_assert(offsetof(s_render_camera, field_78) == 0x78, "s_render_camera::field_78 moved when its reconstructed padding was removed");

/* ---------- prototypes */

extern bool render_camera_view_to_screen(s_render_camera const *camera, s_render_projection const *projection, short_rectangle2d const *window_display_bounds, real_point3d const *view_point, real_point2d *screen_point);
extern bool render_camera_world_to_window(s_render_camera const *camera, s_render_projection const *projection, short_rectangle2d const *window_display_bounds, real_point3d const *world_point, real_point2d *screen_point);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_VIEWS_RENDER_CAMERA_HPP__
