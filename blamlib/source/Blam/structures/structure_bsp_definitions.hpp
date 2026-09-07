#ifndef __BLAM_STRUCTURES_STRUCTURE_BSP_DEFINITIONS_HPP__
#define __BLAM_STRUCTURES_STRUCTURE_BSP_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/physics/physics_shapes.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"
#include "Blam/visibility/visibility.hpp"

/* ---------- forward declarations */

struct c_convex_vertices_shape_with_material;
struct collision_bsp;
struct hkShapeContainer;
struct hkpConvexVerticesShape;
struct real_plane3d;
struct real_rectangle3d;
struct s_cubemap_reference_point;
struct s_decorator_grid;
struct s_geometry_material;
struct s_instanced_geometry_definition_extra_data;
struct s_large_collision_bsp;
struct s_render_geometry;
struct s_scenario_structure_bsp;
struct s_structure_breakable_surface;
struct s_structure_bsp_cache_file_resources;
struct s_structure_bsp_resources;
struct s_structure_cluster;
struct s_structure_cluster_cubemap_info;
struct s_structure_collision_material;
struct s_structure_instanced_geometry_definition;
struct s_structure_instanced_geometry_instance;
struct s_structure_physics;
struct s_structure_plane;
struct s_structure_surface_plane;
struct s_tag_block;
struct s_tag_reference;
struct s_tag_resource;

/* ---------- constants */

/* ---------- definitions */

struct s_structure_breakable_surface
{
	short instanced_geometry_index; // 0x0
	unsigned char breakable_surface_set_index; // 0x2
	unsigned char breakable_surface_index; // 0x3
	long seed_surface_index; // 0x4
	real_rectangle3d bounds; // 0x8
};
static_assert(sizeof(s_structure_breakable_surface) == 32, "Invalid s_structure_breakable_surface size");

#pragma pack(push, 4)
struct s_decorator_grid
{
	short amount; // 0x0
	short palette_index; // 0x2
	short variant; // 0x4
	short vertex_buffer_index; // 0x6
	__int32 vertex_buffer_offset; // 0x8
	real_point3d position; // 0xC
	float radius; // 0x18
	real_point3d grid_size; // 0x1C
	real_point3d bounding_sphere_offset; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_decorator_grid) == 52, "Invalid s_decorator_grid size");

struct s_cubemap_reference_point
{
	real_point3d point; // 0x0
	long point_index; // 0xC
};
static_assert(sizeof(s_cubemap_reference_point) == 16, "Invalid s_cubemap_reference_point size");

struct s_structure_cluster_cubemap_info
{
	short cubemap_index; // 0x0
	short cubemap_bitmap_index; // 0x2
	c_tag_block<s_cubemap_reference_point> reference_points; // 0x4
};
static_assert(sizeof(s_structure_cluster_cubemap_info) == 16, "Invalid s_structure_cluster_cubemap_info size");

#pragma pack(push, 4)
struct s_structure_physics
{
	__int32 field_0; // 0x0
	short Size; // 0x4
	short Offset; // 0x6
	__int32 field_8; // 0x8
	__int32 field_C; // 0xC
	hkShapeContainer ShapeContainer; // 0x10
	__int32 field_14; // 0x14
	s_tag_reference Bsp; // 0x18
	__int32 ClusterIndex; // 0x28
	__int32 BspTreeShape; // 0x2C
	__int32 field_30; // 0x30
	__int32 field_34; // 0x34
	__int32 field_38; // 0x38
	__int32 field_3C; // 0x3C
	__int32 field_40; // 0x40
	__int32 field_44; // 0x44
	s_tag_block mopp_codes; // 0x48
};
#pragma pack(pop)
static_assert(sizeof(s_structure_physics) == 84, "Invalid s_structure_physics size");

#pragma pack(push, 4)
struct s_structure_cluster
{
	real_rectangle3d bounds; // 0x0
	char unknown_sky_index; // 0x18
	char scenario_sky_index; // 0x19
	char camera_effect_index; // 0x1A
	char field_1B; // 0x1B
	short background_sound_environment_index; // 0x1C
	short SoundClustersIndex; // 0x1E
	short field_20; // 0x20
	short field_22; // 0x22
	short field_24; // 0x24
	short field_26; // 0x26
	short field_28; // 0x28
	short runtime_decal_start_index; // 0x2A
	short runtime_decal_entry_count; // 0x2C
	unsigned short flags; // 0x2E
	__int32 field_30; // 0x30
	__int32 field_34; // 0x34
	__int32 field_38; // 0x38
	s_tag_block portal_mapping; // 0x3C
	s_structure_physics structure_physics; // 0x48
	short mesh_index; // 0x9C
	short field_9E; // 0x9E
	c_tag_block<char> seam_indices; // 0xA0
	c_tag_block<s_decorator_grid> decorator_grids; // 0xAC
	__int32 field_B8; // 0xB8
	__int32 field_BC; // 0xBC
	__int32 field_C0; // 0xC0
	s_tag_block SceneryEffectObjects; // 0xC4
	c_tag_block<s_structure_cluster_cubemap_info> cubemaps; // 0xD0
};
#pragma pack(pop)
static_assert(sizeof(s_structure_cluster) == 220, "Invalid s_structure_cluster size");

struct s_structure_collision_material
{
	s_tag_reference render_method; // 0x0
	short global_materal_type; // 0x10
	short conveyor_surface_index; // 0x12
	short seam_index; // 0x14
	short field_16; // 0x16
};
static_assert(sizeof(s_structure_collision_material) == 24, "Invalid s_structure_collision_material size");

// s_instanced_geometry_physics_definition is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

#pragma pack(push, 4)
struct s_scenario_structure_bsp
{
	long bsp_checksum; // 0x0
	c_flags<enum e_scenario_structure_bsp_flags,unsigned short> flags; // 0x4
	c_flags<enum e_scenario_structure_bsp_content_policy_flags,unsigned short> content_policy_flags; // 0x6
	c_flags<enum e_scenario_structure_bsp_content_policy_flags,unsigned short> failed_content_policy_flags; // 0x8
	c_flags<enum e_scenario_structure_bsp_compatibility_flags,unsigned short> compatibility_flags; // 0xA
	unsigned long unknown1; // 0xC
	s_tag_block seam_identifiers; // 0x10
	s_tag_block unknown_raw7ths; // 0x1C
	c_tag_block<s_structure_collision_material> collision_materials; // 0x28
	s_tag_block leaves; // 0x34
	real_rectangle3d world_bounds; // 0x40
	s_tag_block surface_planes; // 0x58
	s_tag_block planes; // 0x64
	s_tag_block unknown2; // 0x70
	s_tag_block cluster_portals; // 0x7C
	s_tag_block unknown3; // 0x88
	s_tag_block fog; // 0x94
	s_tag_block camera_effects; // 0xA0
	s_tag_block unknown4; // 0xAC
	s_tag_block detail_objects; // 0xB8
	c_tag_block<s_structure_cluster> clusters; // 0xC4
	c_tag_block<s_geometry_material> materials; // 0xD0
	s_tag_block sky_owner_cluster; // 0xDC
	s_tag_block conveyor_surfaces; // 0xE8
	s_tag_block breakable_surfaces; // 0xF4
	s_tag_block pathfinding_data; // 0x100
	s_tag_block unknown5; // 0x10C
	s_tag_block background_sound_environment_palette; // 0x118
	unsigned long unknown33; // 0x124
	unsigned long unknown34; // 0x128
	unsigned long unknown35; // 0x12C
	unsigned long unknown36; // 0x130
	unsigned long unknown37; // 0x134
	unsigned long unknown38; // 0x138
	unsigned long unknown39; // 0x13C
	unsigned long unknown40; // 0x140
	unsigned long unknown41; // 0x144
	unsigned long unknown42; // 0x148
	unsigned long unknown43; // 0x14C
	s_tag_block markers; // 0x150
	s_tag_block lights; // 0x15C
	s_tag_block runtime_lights; // 0x168
	s_tag_block runtime_decals; // 0x174
	s_tag_block environment_object_palette; // 0x180
	s_tag_block environment_objects; // 0x18C
	unsigned long unknown45; // 0x198
	unsigned long unknown46; // 0x19C
	unsigned long unknown47; // 0x1A0
	unsigned long unknown48; // 0x1A4
	unsigned long unknown49; // 0x1A8
	unsigned long unknown50; // 0x1AC
	unsigned long unknown51; // 0x1B0
	unsigned long unknown52; // 0x1B4
	unsigned long unknown53; // 0x1B8
	unsigned long unknown54; // 0x1BC
	c_tag_block<s_structure_instanced_geometry_instance> instanced_geometry_instances; // 0x1C0
	c_tag_block<s_tag_reference> decorators; // 0x1CC
	s_render_geometry decorator_geometry; // 0x1D8
	s_tag_block unknown_sound_clusters_a; // 0x25C
	s_tag_block unknown_sound_clusters_b; // 0x268
	s_tag_block unknown_sound_clusters_c; // 0x274
	s_tag_block transparent_planes; // 0x280
	s_tag_block unknown55; // 0x28C
	s_tag_block collision_mopp_codes; // 0x298
	unsigned long unknown67; // 0x2A4
	real_point3d collision_world_bounds_lower; // 0x2A8
	real_point3d collision_world_bounds_upper; // 0x2B4
	s_tag_block breakable_surface_mopp_codes; // 0x2C0
	c_tag_block<s_structure_breakable_surface> breakable_surface_key_table; // 0x2CC
	s_tag_block unknown68; // 0x2D8
	s_tag_block unknown69; // 0x2E4
	s_render_geometry geometry; // 0x2F0
	s_tag_block leaf_systems; // 0x374
	s_tag_block unknown70; // 0x380
	s_tag_resource *collision_bsp_resource; // 0x38C
	long useless_padding3; // 0x390
	s_tag_resource *pathfinding_resource; // 0x394
	long useless_padding4; // 0x398
	long unknown86; // 0x39C
	s_tag_block unknown87; // 0x3A0
	s_scenario_structure_bsp(s_scenario_structure_bsp &); /* compiler_generated() */
	s_scenario_structure_bsp(s_scenario_structure_bsp const &); /* compiler_generated() */
	s_scenario_structure_bsp(); /* compiler_generated() */
	s_scenario_structure_bsp &operator=(s_scenario_structure_bsp &); /* compiler_generated() */
	s_scenario_structure_bsp &operator=(s_scenario_structure_bsp const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_structure_bsp) == 940, "Invalid s_scenario_structure_bsp size");

struct s_structure_plane
{
	long cluster_index : 12; // 0x0
	long index_offset : 20; // 0x0
};
static_assert(sizeof(s_structure_plane) == 4, "Invalid s_structure_plane size");

struct s_structure_surface_plane
{
	long plane_index; // 0x0
	long plane_count; // 0x4
};
static_assert(sizeof(s_structure_surface_plane) == 8, "Invalid s_structure_surface_plane size");

struct s_structure_bsp_cache_file_resources
{
	c_tag_block<s_structure_surface_plane> surface_planes; // 0x0
	c_tag_block<s_structure_plane> planes; // 0xC
};
static_assert(sizeof(s_structure_bsp_cache_file_resources) == 24, "Invalid s_structure_bsp_cache_file_resources size");

#pragma pack(push, 4)
struct s_instanced_geometry_definition_extra_data
{
	c_tag_block<c_convex_vertices_shape_with_material> polyhedra; // 0x0
	c_tag_block<hkpConvexVerticesShape::FourVectors> polyhedra_four_vectors; // 0xC
	c_tag_block<real_plane3d> polyhedra_plane_equations; // 0x18
};
#pragma pack(pop)
static_assert(sizeof(s_instanced_geometry_definition_extra_data) == 36, "Invalid s_instanced_geometry_definition_extra_data size");

struct s_structure_instanced_geometry_definition
{
	unsigned long checksum; // 0x0
	real_point3d bounding_sphere_offset; // 0x4
	float bounding_sphere_radius; // 0x10
	collision_bsp collision_bsp; // 0x14
	c_tag_block<struct collision_bsp> render_bsp; // 0x74
	s_tag_block physics_mopp_codes; // 0x80
	s_tag_block breakable_surfaces; // 0x8C
	c_tag_block<s_structure_surface_plane> surface_planes; // 0x98
	c_tag_block<s_structure_plane> planes; // 0xA4
	unsigned short mesh_index; // 0xB0
	short compression_info_index; // 0xB2
	float global_lightmap_resolution_scale; // 0xB4
	c_tag_block<s_instanced_geometry_definition_extra_data> extra_data; // 0xB8
	unsigned char __pad0[4]; // 0xC4
};
static_assert(sizeof(s_structure_instanced_geometry_definition) == 200, "Invalid s_structure_instanced_geometry_definition size");

struct s_structure_bsp_resources
{
	c_tag_block<struct collision_bsp> collision_bsps; // 0x0
	c_tag_block<s_large_collision_bsp> large_collision_bsps; // 0xC
	c_tag_block<s_structure_instanced_geometry_definition> instanced_geometry; // 0x18
	s_tag_block havok_data; // 0x24
};
static_assert(sizeof(s_structure_bsp_resources) == 48, "Invalid s_structure_bsp_resources size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_STRUCTURES_STRUCTURE_BSP_DEFINITIONS_HPP__
