#ifndef __BLAM_PHYSICS_COLLISION_TEST_HPP__
#define __BLAM_PHYSICS_COLLISION_TEST_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

struct c_collision_bsp_reference;
struct real_plane3d;
struct s_cluster_reference;
struct s_collision_result;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_collision_result
{
	long type; // 0x0
	float t; // 0x4
	real_point3d intersection_point; // 0x8
	s_cluster_reference cluster_reference2; // 0x14
	s_cluster_reference cluster_reference; // 0x16
	c_collision_bsp_reference collision_bsp_reference; // 0x18
	short global_material_type; // 0x20
	unsigned char __pad0[2]; // 0x22
	real_plane3d plane; // 0x24
	long instance_geometry_index; // 0x34
	long object_index; // 0x38
	short region_index; // 0x3C
	short node_index; // 0x3E
	long bsp_reference; // 0x40
	long bsp_index; // 0x44
	long leaf_index; // 0x48
	long surface_index; // 0x4C
	long plane_index; // 0x50
	bool plane_negated; // 0x54
	unsigned char surface_flags; // 0x55
	unsigned char breakable_surface_index; // 0x56
	unsigned char __pad1[1]; // 0x57
	short material_index; // 0x58
	unsigned char breakable_surface_set_index; // 0x5A
};
#pragma pack(pop)
static_assert(sizeof(s_collision_result) == 92, "Invalid s_collision_result size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_PHYSICS_COLLISION_TEST_HPP__
