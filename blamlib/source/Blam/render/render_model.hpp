#ifndef __BLAM_RENDER_RENDER_MODEL_HPP__
#define __BLAM_RENDER_RENDER_MODEL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_matrix4x3;
struct real_quaternion;
struct real_rgb_color;
struct real_vector3d;
struct s_geometry_material;
struct s_render_geometry;
struct s_render_model;
struct s_render_model_instance_placement;
struct s_render_model_marker;
struct s_render_model_marker_group;
struct s_render_model_permutation;
struct s_render_model_region;
struct s_sky_gen_light;
struct s_tag_block;

/* ---------- constants */

/* ---------- definitions */

struct s_render_model_permutation
{
	unsigned long name; // 0x0
	short mesh_index; // 0x4
	short mesh_count; // 0x6
	unsigned char __pad0[16]; // 0x8
};
static_assert(sizeof(s_render_model_permutation) == 24, "Invalid s_render_model_permutation size");

struct s_render_model_region
{
	unsigned long name; // 0x0
	c_tag_block<s_render_model_permutation> permutations; // 0x4
};
static_assert(sizeof(s_render_model_region) == 16, "Invalid s_render_model_region size");

#pragma pack(push, 4)
struct s_render_model_marker
{
	char region_index; // 0x0
	char permutation_index; // 0x1
	char node_index; // 0x2
	real_point3d position; // 0x4
	real_quaternion rotation; // 0x10
	float scale; // 0x20
};
#pragma pack(pop)
static_assert(sizeof(s_render_model_marker) == 36, "Invalid s_render_model_marker size");

struct s_render_model_marker_group
{
	unsigned long name; // 0x0
	c_tag_block<s_render_model_marker> markers; // 0x4
};
static_assert(sizeof(s_render_model_marker_group) == 16, "Invalid s_render_model_marker_group size");

#pragma pack(push, 4)
struct s_sky_gen_light
{
	real_vector3d direction; // 0x0
	real_rgb_color color; // 0xC
	float magnitude; // 0x18
};
#pragma pack(pop)
static_assert(sizeof(s_sky_gen_light) == 28, "Invalid s_sky_gen_light size");

#pragma pack(push, 4)
struct s_render_model_instance_placement
{
	unsigned long name; // 0x0
	__int32 node_index; // 0x4
	real_matrix4x3 matrix; // 0x8
};
#pragma pack(pop)
static_assert(sizeof(s_render_model_instance_placement) == 60, "Invalid s_render_model_instance_placement size");

#pragma pack(push, 4)
struct s_render_model
{
	unsigned long name; // 0x0
	short flags; // 0x4
	short import_version; // 0x6
	unsigned long import_checksum; // 0x8
	c_tag_block<s_render_model_region> regions; // 0xC
	unsigned char __pad0[4]; // 0x18
	long instance_mesh_index; // 0x1C
	c_tag_block<s_render_model_instance_placement> instance_placements; // 0x20
	long node_list_checksum; // 0x2C
	s_tag_block nodes; // 0x30
	c_tag_block<s_render_model_marker_group> marker_groups; // 0x3C
	c_tag_block<s_geometry_material> materials; // 0x48
	s_tag_block errors; // 0x54
	float overdraw_camera_angle; // 0x60
	s_render_geometry render_geometry; // 0x64
	c_tag_block<s_sky_gen_light> lightgen_lights; // 0xE8
	s_render_model(s_render_model &); /* compiler_generated() */
	s_render_model(s_render_model const &); /* compiler_generated() */
	s_render_model(); /* compiler_generated() */
	s_render_model &operator=(s_render_model &); /* compiler_generated() */
	s_render_model &operator=(s_render_model const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_render_model) == 244, "Invalid s_render_model size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_RENDER_MODEL_HPP__
