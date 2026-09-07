#ifndef __BLAM_PHYSICS_PHYSICS_SHAPES_HPP__
#define __BLAM_PHYSICS_PHYSICS_SHAPES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/havok_types.hpp"

/* ---------- forward declarations */

struct c_collision_Geometry_shape;
struct c_collision_bsp_reference;
struct c_convex_vertices_shape_with_material;
struct c_decomposed_poop_shape;
struct c_environment_surface_shape;
struct c_mopp_bv_tree_shape;
struct c_scaled_convex_vertices_shape;
struct collision_bsp;
struct hkVector4;
struct hkpConvexShape;
struct hkpConvexVerticesShape;
struct hkpMoppBvTreeShape;
struct hkpShapeCollection;
struct s_structure_instanced_geometry_definition;

/* ---------- constants */

/* ---------- definitions */

struct c_mopp_bv_tree_shape :
	public hkpMoppBvTreeShape
{
	float mopp_scale; // 0x1C
};
static_assert(sizeof(c_mopp_bv_tree_shape) == 32, "Invalid c_mopp_bv_tree_shape size");

struct c_collision_Geometry_shape :
	public hkpShapeCollection
{
	unsigned char __pad0[8]; // 0x18
	hkVector4 aabb_center; // 0x20
	hkVector4 aabb_half_extents; // 0x30
	__int32 model_definition_index; // 0x40
	c_collision_bsp_reference collision_bsp; // 0x44
	char bsp_index; // 0x4C
	char collision_geometry_shape_type; // 0x4D
	short instance_index; // 0x4E
	float scale; // 0x50
	unsigned char __pad1[12]; // 0x54
};
static_assert(sizeof(c_collision_Geometry_shape) == 96, "Invalid c_collision_Geometry_shape size");

struct c_decomposed_poop_shape :
	public hkpShapeCollection
{
	unsigned char __pad0[8]; // 0x18
	hkVector4 aabb_half_extents; // 0x20
	hkVector4 aabb_center; // 0x30
	float scale; // 0x40
	void *instance_definition; // 0x44
	static void fixup(c_decomposed_poop_shape *definition, s_structure_instanced_geometry_definition *instance_definition);
	unsigned char __pad1[8]; // 0x48
};
static_assert(sizeof(c_decomposed_poop_shape) == 80, "Invalid c_decomposed_poop_shape size");

struct c_convex_vertices_shape_with_material :
	public hkpConvexVerticesShape
{
	static unsigned long const k_tag;
	long material_index; // 0x60
	static void fixup(c_convex_vertices_shape_with_material *definition, s_structure_instanced_geometry_definition *instance_definition);
	unsigned char __pad0[12]; // 0x64
};
static_assert(sizeof(c_convex_vertices_shape_with_material) == 112, "Invalid c_convex_vertices_shape_with_material size");

struct c_scaled_convex_vertices_shape :
	public hkpConvexShape
{
	static unsigned long const k_tag;
	c_convex_vertices_shape_with_material *child; // 0x14
	unsigned char __pad0[8]; // 0x18
	hkVector4 scale; // 0x20
	static void fixup(c_scaled_convex_vertices_shape *definition, c_convex_vertices_shape_with_material *child, float scale);
};
static_assert(sizeof(c_scaled_convex_vertices_shape) == 48, "Invalid c_scaled_convex_vertices_shape size");

struct c_environment_surface_shape :
	public hkpShapeCollection
{
	static unsigned long const k_tag;
	unsigned char __pad0[8]; // 0x18
	hkVector4 aabb_min; // 0x20
	hkVector4 aabb_max; // 0x30
	long structure_bsp_index; // 0x40
	unsigned char __pad1[12]; // 0x44
};
static_assert(sizeof(c_environment_surface_shape) == 80, "Invalid c_environment_surface_shape size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_PHYSICS_PHYSICS_SHAPES_HPP__
