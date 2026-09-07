#ifndef __BLAM_GEOMETRY_GEOMETRY_DEFINITIONS_HPP__
#define __BLAM_GEOMETRY_GEOMETRY_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_plane3d;
struct s_geometry_material;
struct s_instance_part;
struct s_instance_part_contents;
struct s_instance_water;
struct s_mesh;
struct s_node_map;
struct s_part;
struct s_per_mesh_lod_data;
struct s_per_mesh_lod_index;
struct s_per_mesh_node_map;
struct s_per_mesh_subpart_visibility;
struct s_render_geometry_pvs_data;
struct s_sorting_position;
struct s_subpart;
struct s_tag_block;
struct s_tag_reference;

/* ---------- constants */

enum
{
	k_number_of_mesh_vertex_buffers = 8, // 0x0008
	k_number_of_mesh_index_buffers = 2, // 0x0002
	k_number_of_visibility_geometry_node_indices = 4, // 0x0004
	k_number_of_visibility_geometry_node_weights = 3, // 0x0003
};

/* ---------- definitions */

struct s_part
{
	short material_index; // 0x0
	short transparent_sorting_index; // 0x2
	__int32 first_index; // 0x4
	__int32 index_count; // 0x8
	short first_subpart_index; // 0xC
	short subpart_count; // 0xE
	c_enum<enum e_part_type,char> type; // 0x10
	c_flags<enum e_part_flags,unsigned char> flags; // 0x11
	unsigned short vertex_count; // 0x12
	s_part(s_part &); /* compiler_generated() */
	s_part(s_part const &); /* compiler_generated() */
	s_part(); /* compiler_generated() */
	s_part &operator=(s_part &); /* compiler_generated() */
	s_part &operator=(s_part const &); /* compiler_generated() */
};
static_assert(sizeof(s_part) == 20, "Invalid s_part size");

struct s_subpart
{
	__int32 first_index; // 0x0
	__int32 index_count; // 0x4
	short part_index; // 0x8
	unsigned short vertex_count; // 0xA
};
static_assert(sizeof(s_subpart) == 12, "Invalid s_subpart size");

struct s_instance_part_contents
{
	short value; // 0x0
};
static_assert(sizeof(s_instance_part_contents) == 2, "Invalid s_instance_part_contents size");

struct s_instance_part
{
	short section1; // 0x0
	short section2; // 0x2
	c_tag_block<s_instance_part_contents> contents; // 0x4
};
static_assert(sizeof(s_instance_part) == 16, "Invalid s_instance_part size");

#pragma pack(push, 4)
struct s_mesh
{
	c_tag_block<s_part> parts; // 0x0
	c_tag_block<s_subpart> subparts; // 0xC
	short vertex_buffer_indices[8]; // 0x18
	short index_buffer_indices[2]; // 0x28
	c_flags<enum e_mesh_flags,unsigned char> flags; // 0x2C
	char rigid_node; // 0x2D
	c_enum<enum e_vertex_type,char> vertex_type; // 0x2E
	c_enum<enum e_prt_vertex_type,char> prt_vertex_type; // 0x2F
	c_enum<enum e_index_buffer_type,char> index_buffer_type; // 0x30
	unsigned char __pad0[3]; // 0x31
	c_tag_block<s_instance_part> instance_parts; // 0x34
	c_tag_block<s_instance_water> instance_water; // 0x40
	s_mesh(s_mesh &); /* compiler_generated() */
	s_mesh(s_mesh const &); /* compiler_generated() */
	s_mesh(); /* compiler_generated() */
	s_mesh &operator=(s_mesh &); /* compiler_generated() */
	s_mesh &operator=(s_mesh const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_mesh) == 76, "Invalid s_mesh size");

struct s_sorting_position
{
	real_plane3d plane; // 0x0
	real_point3d position; // 0x10
	float radius; // 0x1C
	char node_indices[4]; // 0x20
	float node_weights[3]; // 0x24
};
static_assert(sizeof(s_sorting_position) == 48, "Invalid s_sorting_position size");

struct s_node_map
{
	char node; // 0x0
};
static_assert(sizeof(s_node_map) == 1, "Invalid s_node_map size");

#pragma pack(push, 4)
struct s_per_mesh_node_map
{
	c_tag_block<s_node_map> nodes; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_per_mesh_node_map) == 12, "Invalid s_per_mesh_node_map size");

#pragma pack(push, 4)
struct s_per_mesh_subpart_visibility
{
	c_tag_block<s_sorting_position> sorting_position; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_per_mesh_subpart_visibility) == 12, "Invalid s_per_mesh_subpart_visibility size");

struct s_per_mesh_lod_index
{
	long value; // 0x0
};
static_assert(sizeof(s_per_mesh_lod_index) == 4, "Invalid s_per_mesh_lod_index size");

struct s_per_mesh_lod_data
{
	c_tag_block<s_per_mesh_lod_index> indices; // 0x0
	short vertex_buffer; // 0xC
	unsigned char __pad0[2]; // 0xE
};
static_assert(sizeof(s_per_mesh_lod_data) == 16, "Invalid s_per_mesh_lod_data size");

#pragma pack(push, 4)
struct s_render_geometry_pvs_data
{
	c_tag_block<s_per_mesh_subpart_visibility> per_mesh_subpart_visibility; // 0x0
	s_tag_block unknown4; // 0xC
	c_tag_block<s_per_mesh_lod_data> per_mesh_lod_data; // 0x18
};
#pragma pack(pop)
static_assert(sizeof(s_render_geometry_pvs_data) == 36, "Invalid s_render_geometry_pvs_data size");

#pragma pack(push, 4)
struct s_geometry_material
{
	s_tag_reference render_method; // 0x0
	s_tag_block properties; // 0x10
	unsigned char __pad0[4]; // 0x1C
	char breakable_surface_set_index; // 0x20
	unsigned char __pad1[3]; // 0x21
};
#pragma pack(pop)
static_assert(sizeof(s_geometry_material) == 36, "Invalid s_geometry_material size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GEOMETRY_GEOMETRY_DEFINITIONS_HPP__
