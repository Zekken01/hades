#ifndef __BLAM_GEOMETRY_GEOMETRY_SAMPLER_HPP__
#define __BLAM_GEOMETRY_GEOMETRY_SAMPLER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_point2d;
struct real_rgb_color;
struct real_vector2d;
struct real_vector3d;
struct s_geometry_sample;
struct s_geometry_test_result;
struct s_uncompressed_triangle;

/* ---------- constants */

/* ---------- definitions */

struct s_geometry_sample
{
	real_point3d origin; // 0x0
	float sh_red[36]; // 0xC
	float sh_green[36]; // 0x9C
	float sh_blue[36]; // 0x12C
	real_rgb_color tint; // 0x1BC
	real_vector3d normal; // 0x1C8
	real_vector3d dominant_light_direction; // 0x1D4
	real_rgb_color dominant_light_intensity; // 0x1E0
	float field_1EC; // 0x1EC
	bool is_valid; // 0x1F0
	char field_1F1; // 0x1F1
	short field_1F2; // 0x1F2
	float illumination_scale; // 0x1F4
};
static_assert(sizeof(s_geometry_sample) == 504, "Invalid s_geometry_sample size");

#pragma pack(push, 4)
struct s_geometry_test_result
{
	real_vector3d intersection_point; // 0x0
	real_vector3d nearest_vertex_position; // 0xC
	real_vector2d nearest_vertex_texture_coords; // 0x18
	real_point2d lightmap_coordinate; // 0x20
	real_vector3d normal; // 0x28
	long bsp_index; // 0x34
	long cluster_index; // 0x38
	long instanced_geometry_index; // 0x3C
	long object_index; // 0x40
	bool use_per_vertex_lighting; // 0x44
	bool use_per_pixel_lighting; // 0x45
	bool use_lightprobe; // 0x46
	char field_47; // 0x47
	float sh_red_2[9]; // 0x48
	float sh_green_2[9]; // 0x6C
	float sh_blue_2[9]; // 0x90
	float sh_red_1[4]; // 0xB4
	float sh_green_1[4]; // 0xC4
	float sh_blue_1[4]; // 0xD4
	real_vector3d light_intensity; // 0xE4
	float triangle_distances[2]; // 0xF0
	long field_F8; // 0xF8
	real_vector3d triangle_points[3]; // 0xFC
	real_vector3d triangle_tex_coords[3]; // 0x120
	long field_144; // 0x144
	long field_148; // 0x148
	long field_14C; // 0x14C
	long material_index; // 0x150
	short global_material_type; // 0x154
	short field_156; // 0x156
	char field_158; // 0x158
	char field_159; // 0x159
	char field_15A; // 0x15A
	char field_15B; // 0x15B
};
#pragma pack(pop)
static_assert(sizeof(s_geometry_test_result) == 348, "Invalid s_geometry_test_result size");

#pragma pack(push, 4)
struct s_uncompressed_triangle
{
	real_point3d positions[3]; // 0x0
	real_vector2d texture_coords[3]; // 0x24
	real_vector3d normals[3]; // 0x3C
	long indices[3]; // 0x60
};
#pragma pack(pop)
static_assert(sizeof(s_uncompressed_triangle) == 108, "Invalid s_uncompressed_triangle size");

// s_compression_info is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_scenario_lightmap_bsp_data is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GEOMETRY_GEOMETRY_SAMPLER_HPP__
