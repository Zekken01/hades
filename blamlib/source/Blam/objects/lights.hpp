#ifndef __BLAM_OBJECTS_LIGHTS_HPP__
#define __BLAM_OBJECTS_LIGHTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/scenario/scenario_definitions.hpp"

/* ---------- forward declarations */

struct real_point2d;
struct real_rgb_color;
struct real_vector3d;
struct s_datum;
struct s_light_datum;
struct s_scenario_location;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_light_datum :
	public s_datum
{
	unsigned short flags; // 0x2
	long definition_index; // 0x4
	long scenario_light_index; // 0x8
	long first_cluster_reference_index; // 0xC
	long creation_time; // 0x10
	real_point3d bounding_center; // 0x14
	float bounding_radius; // 0x20
	real_vector3d lod_bounding_center; // 0x24
	float lod_bounding_radius; // 0x30
	real_vector3d origin; // 0x34
	s_scenario_location location; // 0x40
	unsigned char __pad0[2]; // 0x42
	long object_index; // 0x44
	unsigned long object_function_reference; // 0x48
	short object_attachment_index; // 0x4C
	short object_change_color_reference; // 0x4E
	long unattached_object_index; // 0x50
	short object_node_index; // 0x54
	unsigned char __pad1[2]; // 0x56
	real_point3d node_relative_position; // 0x58
	real_vector3d node_relative_forward; // 0x64
	real_vector3d node_relative_up; // 0x70
	real_point3d position; // 0x7C
	real_point3d target_position; // 0x88
	float offset_distance; // 0x94
	real_point3d valid_position; // 0x98
	real_vector3d forward; // 0xA4
	real_vector3d up; // 0xB0
	float maximum_distance_scale; // 0xBC
	long field_C0; // 0xC0
	float intensity2; // 0xC4
	float intensity; // 0xC8
	real_rgb_color color; // 0xCC
	real_point2d gel_xform; // 0xD8
	long precomputed_structure_visibility_block_index; // 0xE0
};
#pragma pack(pop)
static_assert(sizeof(s_light_datum) == 228, "Invalid s_light_datum size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_OBJECTS_LIGHTS_HPP__
