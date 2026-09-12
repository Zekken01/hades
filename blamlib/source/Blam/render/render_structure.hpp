#ifndef __BLAM_RENDER_RENDER_STRUCTURE_HPP__
#define __BLAM_RENDER_RENDER_STRUCTURE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/function_definitions.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"

/* ---------- forward declarations */

class c_function_definition;
struct real_point3d;
struct real_rgb_color;
struct s_cluster_reference;
struct s_compression_info;
struct s_decorator_set;
struct s_mesh;
struct s_per_mesh_node_map;
struct s_render_cluster_part;
struct s_render_geometry;
struct s_render_geometry_pvs_data;
struct s_render_instance_part;
struct s_render_structure_globals;
struct s_scenario_lightmap_bsp_data;
struct s_sorting_position;
struct s_tag_block;
struct s_tag_reference;
struct s_tag_resource;
struct s_wind_definition;
struct s_wind_values;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_render_geometry
{
	c_flags<enum e_render_geometry_flags,long> runtime_flags; // 0x0
	c_tag_block<s_mesh> meshes; // 0x4
	c_tag_block<s_compression_info> compression; // 0x10
	c_tag_block<s_sorting_position> sorting; // 0x1C
	s_tag_block unknown1; // 0x28
	s_tag_block unknown2; // 0x34
	s_tag_block unknown3; // 0x40
	c_tag_block<s_per_mesh_node_map> per_mesh_node_maps; // 0x4C
	s_render_geometry_pvs_data pvs_data; // 0x58
	s_tag_resource *resource; // 0x7C
	s_render_geometry(s_render_geometry &); /* compiler_generated() */
	s_render_geometry(s_render_geometry const &); /* compiler_generated() */
	s_render_geometry(); /* compiler_generated() */
	s_render_geometry &operator=(s_render_geometry &); /* compiler_generated() */
	s_render_geometry &operator=(s_render_geometry const &); /* compiler_generated() */
	unsigned char __pad0[4]; // 0x80
};
#pragma pack(pop)
static_assert(sizeof(s_render_geometry) == 132, "Invalid s_render_geometry size");

struct s_render_cluster_part
{
	unsigned long flags; // 0x0
	s_cluster_reference cluster_reference; // 0x4
	unsigned short mesh_index; // 0x6
	unsigned short part_index; // 0x8
};
static_assert(sizeof(s_render_cluster_part) == 12, "Invalid s_render_cluster_part size");

struct s_render_instance_part
{
	unsigned long flags; // 0x0
	short structure_bsp_index; // 0x4
	short instance_index; // 0x6
	short mesh_index; // 0x8
	short mesh_part_index; // 0xA
	unsigned char lod; // 0xC
};
static_assert(sizeof(s_render_instance_part) == 16, "Invalid s_render_instance_part size");

#pragma pack(push, 4)
struct s_render_structure_globals
{
	unsigned char valid_bsp_mask; // 0x0
	unsigned char __pad0[3]; // 0x1
	long bsp_lightmap_bsp_types[16]; // 0x4
	s_scenario_lightmap_bsp_data *bsp_lightmap_bsps[16]; // 0x44
	s_render_geometry *bsp_render_geometry[16]; // 0x84
	s_render_cluster_part cluster_parts[2048]; // 0xC4
	long cluster_part_count; // 0x60C4
	s_render_instance_part instance_parts[3072]; // 0x60C8
	long instance_part_count; // 0x120C8
	long marker_index; // 0x120CC
	long cluster_markers[6]; // 0x120D0
	long instance_markers[6]; // 0x120E8
	long current_bsp_index; // 0x12100
	long current_instance_definition_index; // 0x12104
	long current_instance_index; // 0x12108
};
#pragma pack(pop)
static_assert(sizeof(s_render_structure_globals) == 73996, "Invalid s_render_structure_globals size");

struct s_wind_values
{
	long field_00; // 0x0
	long field_04; // 0x4
	float field_08; // 0x8
	float field_0C; // 0xC
	float field_10; // 0x10
	float field_14; // 0x14
	float field_18; // 0x18
	float field_1C; // 0x1C
	float field_20; // 0x20
	float field_24; // 0x24
	float field_28; // 0x28
	float field_2C; // 0x2C
};
static_assert(sizeof(s_wind_values) == 48, "Invalid s_wind_values size");

struct s_wind_definition
{
	c_function_definition direction_mapping; // 0x0
	c_function_definition speed_mapping; // 0x14
	c_function_definition bend_mapping; // 0x28
	c_function_definition oscillation_mapping; // 0x3C
	c_function_definition frequency_mapping; // 0x50
	float gust_size; // 0x64
	s_tag_reference gust_noise_bitmap; // 0x68
	static void (*update)(s_wind_definition *, s_wind_values *);
	static s_wind_definition *(*get)();
	static s_wind_definition *(*get_wind_definition)(real_point3d *);
	s_wind_definition(s_wind_definition &); /* compiler_generated() */
	s_wind_definition(s_wind_definition const &); /* compiler_generated() */
	s_wind_definition(); /* compiler_generated() */
	s_wind_definition &operator=(s_wind_definition &); /* compiler_generated() */
	s_wind_definition &operator=(s_wind_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_wind_definition) == 120, "Invalid s_wind_definition size");

struct s_decorator_set
{
	s_tag_reference model; // 0x0
	c_tag_block<unsigned long> valid_render_model_instance_names; // 0x10
	long valid_render_model_instances; // 0x1C
	s_tag_reference texture; // 0x20
	char render_flags; // 0x30
	char render_shader; // 0x31
	char light_sampling_pattern; // 0x32
	unsigned char __pad0[1]; // 0x33
	real_rgb_color translucency_abc; // 0x34
	float material_translucency; // 0x40
	float wavelength_xy[2]; // 0x44
	float wave_speed; // 0x4C
	float wave_frequency; // 0x50
	float darkness; // 0x54
	float brightness; // 0x58
	unsigned char __pad1[8]; // 0x5C
	float cull_start; // 0x64
	float cull_end; // 0x68
	float scale; // 0x6C
	float offset; // 0x70
	static s_decorator_set *(*get)(long);
	static long (*get_explicit_shader_index)(s_decorator_set *);
	unsigned char __pad2[12]; // 0x74
};
static_assert(sizeof(s_decorator_set) == 128, "Invalid s_decorator_set size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_RENDER_STRUCTURE_HPP__
