#ifndef __BLAM_RENDER_RENDER_OBJECT_HPP__
#define __BLAM_RENDER_RENDER_OBJECT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/render/render_object_globals.hpp"
#include "Blam/render/render_structure.hpp"

/* ---------- forward declarations */

struct real_matrix4x3;
struct s_datum;
struct s_dynamic_cubemap_sample;
struct s_geometry_material;
struct s_mesh;
struct s_object_cached_render_state_datum;
struct s_part;
struct s_render_first_person_model;
struct s_render_geometry;
struct s_render_model;
struct s_render_object_first_person_globals;
struct s_render_shield_parts;
struct s_visible_object;

/* ---------- constants */

/* ---------- definitions */

struct s_dynamic_cubemap_sample
{
	unsigned char __pad0[4]; // 0x0
	short environment_map0_bitmap_index; // 0x4
	unsigned short cluster_reference; // 0x6
	unsigned char __pad1[2]; // 0x8
	short environment_map1_bitmap_index; // 0xA
	float dynamic_environment_blend; // 0xC
};
static_assert(sizeof(s_dynamic_cubemap_sample) == 16, "Invalid s_dynamic_cubemap_sample size");

// s_render_lighting is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_shader_extern_info is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

struct s_object_cached_render_state_datum :
	public s_datum
{
	bool valid; // 0x2
	bool flag1; // 0x3
	bool flag2; // 0x4
	long object_index; // 0x8
	long last_update_frame_index; // 0xC
	long last_frame_index; // 0x10
	real_point3d object_origin; // 0x14
	s_render_lighting render_lighting; // 0x20
	s_shader_extern_info shader_extern_info; // 0x238
	unsigned char __pad1[68]; // 0x494
};
static_assert(sizeof(s_object_cached_render_state_datum) == 1240, "Invalid s_object_cached_render_state_datum size");
static_assert(offsetof(s_object_cached_render_state_datum, object_index) == 0x8, "s_object_cached_render_state_datum::object_index moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_render_first_person_model
{
	long render_model_index; // 0x0
	long object_index; // 0x4
	unsigned long flags; // 0x8
	real_matrix4x3 node_matrices[150]; // 0xC
};
#pragma pack(pop)
static_assert(sizeof(s_render_first_person_model) == 7812, "Invalid s_render_first_person_model size");

struct s_render_object_first_person_globals
{
	__int32 object_index; // 0x0
	__int32 first_person_model_count; // 0x4
	s_render_first_person_model first_person_models[6]; // 0x8
};
static_assert(sizeof(s_render_object_first_person_globals) == 46880, "Invalid s_render_object_first_person_globals size");

struct s_render_shield_parts
{
	s_visible_object *visible_object; // 0x0
	s_render_model *render_model; // 0x4
	s_render_geometry *geometry; // 0x8
	s_geometry_material *materials; // 0xC
	__int32 current_region_index; // 0x10
	__int32 current_mesh_index; // 0x14
	s_mesh *current_mesh; // 0x18
	__int32 current_part_index; // 0x1C
	s_part *current_part; // 0x20
};
static_assert(sizeof(s_render_shield_parts) == 36, "Invalid s_render_shield_parts size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_RENDER_OBJECT_HPP__
