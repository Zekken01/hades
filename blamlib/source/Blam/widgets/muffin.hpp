#ifndef __BLAM_WIDGETS_MUFFIN_HPP__
#define __BLAM_WIDGETS_MUFFIN_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_matrix4x3;
struct real_vector3d;
struct s_muffin;
struct s_muffin_datum;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_muffin
{
	char flags; // 0x0
	char muffin_type; // 0x1
	char field_02; // 0x2
	char mesh_index; // 0x3
	long field_04; // 0x4
	long field_08; // 0x8
	long start_tick; // 0xC
	real_point3d position; // 0x10
	real_vector3d velocity; // 0x1C
	real_matrix4x3 node_matrix; // 0x28
	real_matrix4x3 render_matrix; // 0x5C
	real_matrix4x3 field_90; // 0x90
};
#pragma pack(pop)
static_assert(sizeof(s_muffin) == 196, "Invalid s_muffin size");

struct s_muffin_datum
{
	short datum; // 0x0
	char field_02; // 0x2
	unsigned char muffin_count; // 0x3
	s_muffin muffins[32]; // 0x4
	long tag_index; // 0x1884
	long object_index; // 0x1888
	float seconds_since_last_update; // 0x188C
};
static_assert(sizeof(s_muffin_datum) == 6288, "Invalid s_muffin_datum size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_WIDGETS_MUFFIN_HPP__
