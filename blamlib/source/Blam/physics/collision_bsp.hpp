#ifndef __BLAM_PHYSICS_COLLISION_BSP_HPP__
#define __BLAM_PHYSICS_COLLISION_BSP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct bsp2d_node;
struct bsp2d_reference;
struct bsp3d_node;
struct c_collision_bsp_reference;
struct c_collision_surface_reference;
struct collision_bsp;
struct collision_edge;
struct collision_leaf;
struct collision_surface;
struct collision_vertex;
struct real_plane2d;
struct real_plane3d;
struct s_large_bsp2d_node;
struct s_large_bsp2d_reference;
struct s_large_bsp3d_node;
struct s_large_collision_bsp;
struct s_large_collision_edge;
struct s_large_collision_surface;
struct s_large_collision_vertex;
struct s_scenario_structure_bsp;

/* ---------- constants */

/* ---------- definitions */

struct bsp2d_reference
{
	short plane_index; // 0x0
	short node_index; // 0x2
};
static_assert(sizeof(bsp2d_reference) == 4, "Invalid bsp2d_reference size");

struct bsp2d_node
{
	real_plane2d plane; // 0x0
	short left_child; // 0xC
	short right_child; // 0xE
};
static_assert(sizeof(bsp2d_node) == 16, "Invalid bsp2d_node size");

struct collision_leaf
{
	c_flags<enum e_collision_leaf_flags,unsigned char> flags; // 0x0
	unsigned short bsp2d_reference_count; // 0x2
	unsigned long first_bsp2d_reference; // 0x4
	collision_leaf(collision_leaf &); /* compiler_generated() */
	collision_leaf(collision_leaf const &); /* compiler_generated() */
	collision_leaf(); /* compiler_generated() */
	collision_leaf &operator=(collision_leaf &); /* compiler_generated() */
	collision_leaf &operator=(collision_leaf const &); /* compiler_generated() */
};
static_assert(sizeof(collision_leaf) == 8, "Invalid collision_leaf size");
static_assert(offsetof(collision_leaf, bsp2d_reference_count) == 0x2, "collision_leaf::bsp2d_reference_count moved when its reconstructed padding was removed");

struct collision_surface
{
	unsigned short plane_index; // 0x0
	unsigned short first_edge_index; // 0x2
	short material_index; // 0x4
	short breakable_surface_index; // 0x6
	short breakable_surface_set_index; // 0x8
	c_flags<enum e_collision_surface_flags,unsigned char> surface_flags; // 0xA
	unsigned char best_plane_calculation_vertex_index; // 0xB
	collision_surface(collision_surface &); /* compiler_generated() */
	collision_surface(collision_surface const &); /* compiler_generated() */
	collision_surface(); /* compiler_generated() */
	collision_surface &operator=(collision_surface &); /* compiler_generated() */
	collision_surface &operator=(collision_surface const &); /* compiler_generated() */
};
static_assert(sizeof(collision_surface) == 12, "Invalid collision_surface size");

struct collision_edge
{
	unsigned short start_vertex; // 0x0
	unsigned short end_vertex; // 0x2
	unsigned short forward_edge; // 0x4
	unsigned short reverse_edge; // 0x6
	unsigned short left_surface; // 0x8
	unsigned short right_surface; // 0xA
};
static_assert(sizeof(collision_edge) == 12, "Invalid collision_edge size");

struct collision_vertex
{
	real_point3d position; // 0x0
	unsigned short first_edge; // 0xC
	short sink; // 0xE
};
static_assert(sizeof(collision_vertex) == 16, "Invalid collision_vertex size");

struct bsp3d_node
{
	unsigned long long value; // 0x0
};
static_assert(sizeof(bsp3d_node) == 8, "Invalid bsp3d_node size");

struct collision_bsp
{
	c_tag_block<bsp3d_node> bsp3d_nodes; // 0x0
	c_tag_block<real_plane3d> planes; // 0xC
	c_tag_block<collision_leaf> leaves; // 0x18
	c_tag_block<bsp2d_reference> bsp2d_references; // 0x24
	c_tag_block<bsp2d_node> bsp2d_nodes; // 0x30
	c_tag_block<collision_surface> surfaces; // 0x3C
	c_tag_block<collision_edge> edges; // 0x48
	c_tag_block<collision_vertex> vertices; // 0x54
};
static_assert(sizeof(collision_bsp) == 96, "Invalid collision_bsp size");

struct s_large_collision_surface
{
	long plane_index; // 0x0
	long first_edge_index; // 0x4
	short material_index; // 0x8
	short breakable_surface_index; // 0xA
	short breakable_surface_set_index; // 0xC
	unsigned char flags; // 0xE
	unsigned char best_plane_calculation_vertex_index; // 0xF
};
static_assert(sizeof(s_large_collision_surface) == 16, "Invalid s_large_collision_surface size");

struct s_large_bsp3d_node
{
	long plane; // 0x0
	long back_child; // 0x4
	long front_child; // 0x8
};
static_assert(sizeof(s_large_bsp3d_node) == 12, "Invalid s_large_bsp3d_node size");

struct s_large_bsp2d_reference
{
	long plane_index; // 0x0
	long node_index; // 0x4
};
static_assert(sizeof(s_large_bsp2d_reference) == 8, "Invalid s_large_bsp2d_reference size");

#pragma pack(push, 4)
struct s_large_bsp2d_node
{
	real_plane2d plane; // 0x0
	long left_child; // 0xC
	long right_child; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_large_bsp2d_node) == 20, "Invalid s_large_bsp2d_node size");

struct s_large_collision_edge
{
	long start_vertex; // 0x0
	long end_vertex; // 0x4
	long forward_edge; // 0x8
	long reverse_edge; // 0xC
	long left_surface; // 0x10
	long right_surface; // 0x14
};
static_assert(sizeof(s_large_collision_edge) == 24, "Invalid s_large_collision_edge size");

#pragma pack(push, 4)
struct s_large_collision_vertex
{
	real_point3d position; // 0x0
	long first_edge; // 0xC
	long sink; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_large_collision_vertex) == 20, "Invalid s_large_collision_vertex size");

struct s_large_collision_bsp
{
	c_tag_block<s_large_bsp3d_node> bsp3d_nodes; // 0x0
	c_tag_block<real_plane3d> planes; // 0xC
	c_tag_block<collision_leaf> leaves; // 0x18
	c_tag_block<s_large_bsp2d_reference> bsp2d_references; // 0x24
	c_tag_block<s_large_bsp2d_node> bsp2d_nodes; // 0x30
	c_tag_block<s_large_collision_surface> surfaces; // 0x3C
	c_tag_block<s_large_collision_edge> edges; // 0x48
	c_tag_block<s_large_collision_vertex> vertices; // 0x54
};
static_assert(sizeof(s_large_collision_bsp) == 96, "Invalid s_large_collision_bsp size");

struct c_collision_bsp_reference
{
	collision_bsp *bsp; // 0x0
	s_large_collision_bsp *large_bsp; // 0x4
	static void (*const initialize)(c_collision_bsp_reference *, s_scenario_structure_bsp const *);
	static void (*const initialize_instanced)(c_collision_bsp_reference *, s_scenario_structure_bsp const *, long, bool);
};
static_assert(sizeof(c_collision_bsp_reference) == 8, "Invalid c_collision_bsp_reference size");

#pragma pack(push, 4)
struct c_collision_surface_reference
{
	c_collision_bsp_reference m_bsp_reference; // 0x0
	long m_surface_index; // 0x8
	static void (*const initialize)(c_collision_surface_reference *, c_collision_bsp_reference, long);
	static long (*const get_breakable_surface_index)(c_collision_surface_reference *);
	static long (*const get_breakable_surface_set_index)(c_collision_surface_reference *);
	static unsigned char (*const get_flags)(c_collision_surface_reference *);
};
#pragma pack(pop)
static_assert(sizeof(c_collision_surface_reference) == 12, "Invalid c_collision_surface_reference size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_PHYSICS_COLLISION_BSP_HPP__
