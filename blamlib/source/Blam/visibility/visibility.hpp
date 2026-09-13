#ifndef __BLAM_VISIBILITY_VISIBILITY_HPP__
#define __BLAM_VISIBILITY_VISIBILITY_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

struct c_visibility_collection;
struct real_matrix4x3;
struct real_plane3d;
struct real_point3d;
struct real_rectangle2d;
struct real_rectangle3d;
struct real_vector2d;
struct real_vector3d;
struct s_cluster_reference;
struct s_instanced_geometry_physics_definition;
struct s_structure_instanced_geometry_instance;
struct s_visibility_cluster;
struct s_visibility_projection;
struct s_visibility_region;
struct s_visibility_volume;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_visibility_volume
{
	real_plane3d field_0[6]; // 0x0
	short type; // 0x60
	short region_cluster_count; // 0x62
	long plane_index; // 0x64
	short structure_bsp_index; // 0x68
	unsigned char __pad0[2]; // 0x6A
	real_rectangle2d frustum_bounds; // 0x6C
	unsigned char __pad1[4]; // 0x7C
	real_point3d points[4]; // 0x80
	real_point3d world_position; // 0xB0
	real_rectangle3d enclosed_points; // 0xBC
	real_plane3d projction_planes[6]; // 0xD4
	real_vector3d field_134; // 0x134
	real_vector3d field_140; // 0x140
	real_vector3d field_14C; // 0x14C
	unsigned char __pad2[12]; // 0x158
};
#pragma pack(pop)
static_assert(sizeof(s_visibility_volume) == 356, "Invalid s_visibility_volume size");

struct s_visibility_projection
{
	char field_0; // 0x0
	real_matrix4x3 world_to_basis; // 0x4
	real_matrix4x3 basis_to_world; // 0x38
	char negated_flag; // 0x6C
	float z_near; // 0x70
	real_plane3d near_plane; // 0x74
	char far_bounded_flag; // 0x84
	float z_far; // 0x88
	char visibility_volume_valid; // 0x8C
	s_visibility_volume visibility_volume; // 0x90
	__int32 convex_hull_point_count; // 0x1F4
	real_vector2d convex_hull_points[4]; // 0x1F8
};
static_assert(sizeof(s_visibility_projection) == 536, "Invalid s_visibility_projection size");
static_assert(offsetof(s_visibility_projection, world_to_basis) == 0x4, "s_visibility_projection::world_to_basis moved when its reconstructed padding was removed");
static_assert(offsetof(s_visibility_projection, z_near) == 0x70, "s_visibility_projection::z_near moved when its reconstructed padding was removed");
static_assert(offsetof(s_visibility_projection, z_far) == 0x88, "s_visibility_projection::z_far moved when its reconstructed padding was removed");
static_assert(offsetof(s_visibility_projection, visibility_volume) == 0x90, "s_visibility_projection::visibility_volume moved when its reconstructed padding was removed");

#pragma pack(push, 2)
struct s_visibility_cluster
{
	s_cluster_reference cluster_reference; // 0x0
	short volume_counts[6]; // 0x2
	short first_volume_indices[6]; // 0xE
};
#pragma pack(pop)
static_assert(sizeof(s_visibility_cluster) == 26, "Invalid s_visibility_cluster size");

#pragma pack(push, 4)
struct s_visibility_region
{
	short projection_count; // 0x0
	unsigned char __pad0[2]; // 0x2
	s_visibility_projection projections[6]; // 0x4
	short cluster_count; // 0xC94
	s_visibility_cluster clusters[128]; // 0xC96
	unsigned char __pad1[2]; // 0x1996
	long sorted_clusters[128]; // 0x1998
	short volume_count; // 0x1B98
	unsigned char __pad2[2]; // 0x1B9A
	s_visibility_volume volumes[512]; // 0x1B9C
	s_cluster_reference cluster_reference; // 0x2E39C
	unsigned char __pad3[2]; // 0x2E39E
	long output_user_index; // 0x2E3A0
	long window_index; // 0x2E3A4
	long flags; // 0x2E3A8
	short unknown; // 0x2E3AC
	unsigned char __pad4[2]; // 0x2E3AE
	real_point3d bounding_sphere_center; // 0x2E3B0
	float bounding_sphere_radius; // 0x2E3BC
	__int32 collection_type; // 0x2E3C0
	long collection_shape; // 0x2E3C4
	long stack_marker; // 0x2E3C8
	unsigned long active_clusters_bit_vector[128]; // 0x2E3CC
	char region_cluster_mapping[16][256]; // 0x2E5CC
};
#pragma pack(pop)
static_assert(sizeof(s_visibility_region) == 193996, "Invalid s_visibility_region size");

#pragma pack(push, 4)
struct s_structure_instanced_geometry_instance
{
	real_matrix4x3 rigid_matrix; // 0x0
	short mesh_index; // 0x34
	c_flags<enum e_instanced_geometry_flags,unsigned short> flags; // 0x36
	short lod_data_index; // 0x38
	unsigned char __pad0[6]; // 0x3A
	real_point3d bounding_sphere_offset; // 0x40
	float bounding_sphere_radius_minimum; // 0x4C
	float bounding_sphere_radius_maximum; // 0x50
	unsigned long name; // 0x54
	short pathfinding_policy; // 0x58
	short lightmapping_policy; // 0x5A
	unsigned char __pad1[4]; // 0x5C
	c_tag_block<s_instanced_geometry_physics_definition> physics; // 0x60
	unsigned char __pad2[4]; // 0x6C
	short cubemap_index; // 0x70
	s_structure_instanced_geometry_instance(s_structure_instanced_geometry_instance &); /* compiler_generated() */
	s_structure_instanced_geometry_instance(s_structure_instanced_geometry_instance const &); /* compiler_generated() */
	s_structure_instanced_geometry_instance(); /* compiler_generated() */
	s_structure_instanced_geometry_instance &operator=(s_structure_instanced_geometry_instance &); /* compiler_generated() */
	s_structure_instanced_geometry_instance &operator=(s_structure_instanced_geometry_instance const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_structure_instanced_geometry_instance) == 116, "Invalid s_structure_instanced_geometry_instance size");

struct c_visibility_collection
{
	s_visibility_region *visbility_region; // 0x0
	short *visible_objects; // 0x4
	static void (*const generate_structure_visible_subparts)(c_visibility_collection *);
	static long (*const region_cluster_bitvector_new)(c_visibility_collection *, short);
	static char (*const sphere_visible_no_portals)(c_visibility_collection *, real_point3d const *, float, short, bool, bool *, bool *, bool *);
	static long (*const region_cluster_bitvector_add_index)(short, short);
	static float (*const compute_instance_alpha)(s_structure_instanced_geometry_instance const *, long);
};
static_assert(sizeof(c_visibility_collection) == 8, "Invalid c_visibility_collection size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_VISIBILITY_VISIBILITY_HPP__
