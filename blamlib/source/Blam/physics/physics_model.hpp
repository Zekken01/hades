#ifndef __BLAM_PHYSICS_PHYSICS_MODEL_HPP__
#define __BLAM_PHYSICS_PHYSICS_MODEL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/biped_definitions.hpp"

/* ---------- forward declarations */

struct hkMatrix3;
struct hkVector4;
struct hkpShape;
struct real_matrix4x3;
struct real_rectangle3d;
struct real_vector3d;
struct s_c_mopp_bv_tree_shape;
struct s_model_definition;
struct s_physics_model_box;
struct s_physics_model_damped_spring_motor;
struct s_physics_model_definition;
struct s_physics_model_hinge_constraint;
struct s_physics_model_instance;
struct s_physics_model_limited_hinge_constraint;
struct s_physics_model_list;
struct s_physics_model_list_shape;
struct s_physics_model_material;
struct s_physics_model_node;
struct s_physics_model_node_edge;
struct s_physics_model_permutation;
struct s_physics_model_phantom;
struct s_physics_model_phantom_type;
struct s_physics_model_pill;
struct s_physics_model_polyhedron;
struct s_physics_model_polyhedron_four_vector;
struct s_physics_model_polyhedron_plane_equation;
struct s_physics_model_position_motor;
struct s_physics_model_powered_chain;
struct s_physics_model_primitive;
struct s_physics_model_ragdoll_constraint;
struct s_physics_model_region;
struct s_physics_model_rigid_body;
struct s_physics_model_sphere;
struct s_physics_model_triangle;
struct s_tag_block;
struct s_tag_data;
struct u_havok_shape_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_physics_model_permutation
{
	unsigned long name; // 0x0
	c_tag_block<short> rigid_body_indices; // 0x4
};
static_assert(sizeof(s_physics_model_permutation) == 16, "Invalid s_physics_model_permutation size");

struct s_physics_model_region
{
	unsigned long name; // 0x0
	c_tag_block<s_physics_model_permutation> permutations; // 0x4
};
static_assert(sizeof(s_physics_model_region) == 16, "Invalid s_physics_model_region size");

struct u_havok_shape_reference
{
	union
	{
		struct
		{
			short shape_type; // 0x0
			short shape_index; // 0x2
		} design_time; // 0x0
		hkpShape *runtime_shape; // 0x0
	};
};
static_assert(sizeof(u_havok_shape_reference) == 4, "Invalid u_havok_shape_reference size");

struct s_physics_model_rigid_body
{
	short node; // 0x0
	short region; // 0x2
	short permutation; // 0x4
	short serialized_shapes; // 0x6
	real_point3d bounding_sphere_offset; // 0x8
	float bounding_sphere_radius; // 0x14
	unsigned short flags; // 0x18
	short motion_type; // 0x1A
	unsigned char __pad0[2]; // 0x1C
	short size; // 0x1E
	float inertia_tensor_scale; // 0x20
	float linear_dampening; // 0x24
	float angular_dampening; // 0x28
	real_vector3d center_of_mass_offset; // 0x2C
	real_rectangle3d water_physics_aabb; // 0x38
	unsigned char __pad1[8]; // 0x50
	u_havok_shape_reference shape; // 0x58
	float mass; // 0x5C
	hkVector4 center_of_mass; // 0x60
	hkMatrix3 intertia_tensor; // 0x70
	unsigned char __pad2[16]; // 0xA0
};
static_assert(sizeof(s_physics_model_rigid_body) == 176, "Invalid s_physics_model_rigid_body size");

struct s_physics_model_definition
{
	long flags; // 0x0
	float mass; // 0x4
	float low_frequency_deactivation_scale; // 0x8
	float high_frequency_deactivation_scale; // 0xC
	float custom_shape_radius; // 0x10
	float maximum_penetration_depth_scale; // 0x14
	char import_version; // 0x18
	c_tag_block<s_physics_model_damped_spring_motor> damped_spring_motors; // 0x1C
	c_tag_block<s_physics_model_position_motor> position_motors; // 0x28
	c_tag_block<s_physics_model_phantom_type> phantom_types; // 0x34
	c_tag_block<s_physics_model_powered_chain> powered_chains; // 0x40
	c_tag_block<s_physics_model_node_edge> node_edges; // 0x4C
	c_tag_block<s_physics_model_rigid_body> rigid_bodies; // 0x58
	c_tag_block<s_physics_model_material> materials; // 0x64
	c_tag_block<s_physics_model_sphere> spheres; // 0x70
	s_tag_block multi_spheres; // 0x7C
	c_tag_block<s_physics_model_pill> pills; // 0x88
	c_tag_block<s_physics_model_box> boxes; // 0x94
	c_tag_block<s_physics_model_triangle> triangles; // 0xA0
	c_tag_block<s_physics_model_polyhedron> polyhedra; // 0xAC
	c_tag_block<s_physics_model_polyhedron_four_vector> polyhedron_four_vectors; // 0xB8
	c_tag_block<s_physics_model_polyhedron_plane_equation> polyhedron_plane_equations; // 0xC4
	s_tag_block mass_distributions; // 0xD0
	c_tag_block<s_physics_model_list> lists; // 0xDC
	c_tag_block<s_physics_model_list_shape> list_shapes; // 0xE8
	c_tag_block<s_c_mopp_bv_tree_shape> mopps; // 0xF4
	s_tag_data mopp_data; // 0x100
	c_tag_block<s_physics_model_hinge_constraint> hinge_constraints; // 0x114
	c_tag_block<s_physics_model_ragdoll_constraint> ragdoll_constraints; // 0x120
	c_tag_block<s_physics_model_region> regions; // 0x12C
	c_tag_block<s_physics_model_node> nodes; // 0x138
	s_tag_block errors; // 0x144
	s_tag_block point_to_path_curves; // 0x150
	c_tag_block<s_physics_model_limited_hinge_constraint> limited_hinge_constraints; // 0x15C
	s_tag_block unused_ball_and_socket_constraints; // 0x168
	s_tag_block stiff_spring_constraints; // 0x174
	s_tag_block prismatic_constraints; // 0x180
	c_tag_block<s_physics_model_phantom> phantoms; // 0x18C
	s_physics_model_definition(s_physics_model_definition &); /* compiler_generated() */
	s_physics_model_definition(s_physics_model_definition const &); /* compiler_generated() */
	s_physics_model_definition(); /* compiler_generated() */
	s_physics_model_definition &operator=(s_physics_model_definition &); /* compiler_generated() */
	s_physics_model_definition &operator=(s_physics_model_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_physics_model_definition) == 408, "Invalid s_physics_model_definition size");
static_assert(offsetof(s_physics_model_definition, damped_spring_motors) == 0x1C, "s_physics_model_definition::damped_spring_motors moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_physics_model_instance
{
	long object_index; // 0x0
	long havok_component_index; // 0x4
	real_matrix4x3 matrix; // 0x8
	long model_definition_index; // 0x3C
	long physics_model_definition_index; // 0x40
	s_model_definition *model; // 0x44
	s_physics_model_definition *physics_model; // 0x48
	char *region_permutation_indices; // 0x4C
	real_matrix4x3 *node_matrices; // 0x50
};
#pragma pack(pop)
static_assert(sizeof(s_physics_model_instance) == 84, "Invalid s_physics_model_instance size");

struct s_physics_model_primitive
{
	unsigned long name; // 0x0
	char material; // 0x4
	unsigned char material_flags; // 0x5
	short runtime_material_type; // 0x6
	float relative_mass_scale; // 0x8
	float friction; // 0xC
	float restitution; // 0x10
	float volume; // 0x14
	float mass; // 0x18
	short mass_distribution_index; // 0x1C
	char phantom; // 0x1E
	char runtime_collision_group; // 0x1F
};
static_assert(sizeof(s_physics_model_primitive) == 32, "Invalid s_physics_model_primitive size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_PHYSICS_PHYSICS_MODEL_HPP__
