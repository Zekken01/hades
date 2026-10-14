#ifndef __BLAM_PHYSICS_COLLISION_MODEL_HPP__
#define __BLAM_PHYSICS_COLLISION_MODEL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct c_collision_bsp_reference;
struct c_collision_bsp_test_vector_result;
struct collision_bsp;
struct collision_model_bsp;
struct collision_model_definition;
struct collision_model_instance;
struct collision_model_node;
struct collision_model_pathfinding_sphere;
struct collision_model_permutation;
struct collision_model_region;
struct collision_model_test_vector_result;
struct model_definition;
struct real_matrix4x3;
struct real_plane3d;
struct real_vector3d;
struct s_collision_model_bsp_iterator;
struct s_tag_block;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct collision_model_bsp
{
	short node_index; // 0x0
	unsigned char __pad0[2]; // 0x2
	collision_bsp bsp; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(collision_model_bsp) == 100, "Invalid collision_model_bsp size");

struct collision_model_permutation
{
	unsigned long name; // 0x0
	c_tag_block<collision_model_bsp> bsps; // 0x4
	s_tag_block bsp_physics; // 0x10
	s_tag_block mopp_codes; // 0x1C
};
static_assert(sizeof(collision_model_permutation) == 40, "Invalid collision_model_permutation size");

struct collision_model_region
{
	unsigned long name; // 0x0
	c_tag_block<collision_model_permutation> permutations; // 0x4
};
static_assert(sizeof(collision_model_region) == 16, "Invalid collision_model_region size");

#pragma pack(push, 4)
struct collision_model_pathfinding_sphere
{
	short node_index; // 0x0
	unsigned short flags; // 0x2
	real_vector3d center; // 0x4
	float radius; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(collision_model_pathfinding_sphere) == 20, "Invalid collision_model_pathfinding_sphere size");

struct collision_model_node
{
	unsigned long name; // 0x0
	unsigned short flags; // 0x4
	short parent_node; // 0x6
	short next_sibling_node; // 0x8
	short first_child_node; // 0xA
};
static_assert(sizeof(collision_model_node) == 12, "Invalid collision_model_node size");

#pragma pack(push, 4)
struct collision_model_definition
{
	unsigned long checksum; // 0x0
	unsigned char __pad0[12]; // 0x4
	unsigned long flags; // 0x10
	c_tag_block<unsigned long> materials; // 0x14
	c_tag_block<collision_model_region> regions; // 0x20
	c_tag_block<collision_model_pathfinding_sphere> path_finding_spheres; // 0x2C
	c_tag_block<collision_model_node> nodes; // 0x38
};
#pragma pack(pop)
static_assert(sizeof(collision_model_definition) == 68, "Invalid collision_model_definition size");

struct collision_model_instance
{
	long object_index; // 0x0
	model_definition *model; // 0x4
	collision_model_definition *collision_model; // 0x8
	unsigned char *permutations; // 0xC
	real_matrix4x3 *nodes; // 0x10
	long root_node_index; // 0x14
};
static_assert(sizeof(collision_model_instance) == 24, "Invalid collision_model_instance size");

#pragma pack(push, 4)
struct c_collision_bsp_test_vector_result
{
	float t; // 0x0
	real_plane3d *plane; // 0x4
	long leaf_index; // 0x8
	long surface_index; // 0xC
	long plane_index; // 0x10
	bool field_14; // 0x14
	c_flags<enum e_collision_surface_flags,unsigned char> surface_flags; // 0x15
	char breakable_surface_index; // 0x16
	char field_17; // 0x17
	short material_index; // 0x18
	long leaves_count; // 0x1C
	long leaves[256]; // 0x20
	char breakable_surface_set_index; // 0x420
	c_collision_bsp_test_vector_result(c_collision_bsp_test_vector_result &); /* compiler_generated() */
	c_collision_bsp_test_vector_result(c_collision_bsp_test_vector_result const &); /* compiler_generated() */
	c_collision_bsp_test_vector_result(); /* compiler_generated() */
	c_collision_bsp_test_vector_result &operator=(c_collision_bsp_test_vector_result &); /* compiler_generated() */
	c_collision_bsp_test_vector_result &operator=(c_collision_bsp_test_vector_result const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_collision_bsp_test_vector_result) == 1060, "Invalid c_collision_bsp_test_vector_result size");

#pragma pack(push, 4)
struct collision_model_test_vector_result
{
	unsigned long bsp_reference; // 0x0
	short node_index; // 0x4
	short region_index; // 0x6
	c_collision_bsp_test_vector_result bsp_test_result; // 0x8
	collision_model_test_vector_result(collision_model_test_vector_result &); /* compiler_generated() */
	collision_model_test_vector_result(collision_model_test_vector_result const &); /* compiler_generated() */
	collision_model_test_vector_result(); /* compiler_generated() */
	collision_model_test_vector_result &operator=(collision_model_test_vector_result &); /* compiler_generated() */
	collision_model_test_vector_result &operator=(collision_model_test_vector_result const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(collision_model_test_vector_result) == 1068, "Invalid collision_model_test_vector_result size");

struct s_collision_model_bsp_iterator
{
	collision_model_definition *m_definition; // 0x0
	unsigned char m_region_permutation_indices[16]; // 0x4
	unsigned long m_bsp3d_reference; // 0x14
	c_collision_bsp_reference m_bsp; // 0x18
};
static_assert(sizeof(s_collision_model_bsp_iterator) == 32, "Invalid s_collision_model_bsp_iterator size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_PHYSICS_COLLISION_MODEL_HPP__
