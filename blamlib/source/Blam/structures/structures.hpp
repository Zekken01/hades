#ifndef __BLAM_STRUCTURES_STRUCTURES_HPP__
#define __BLAM_STRUCTURES_STRUCTURES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_structure_globals;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_structure_globals
{
	bool unused; // 0x0
	bool cluster_marker_initialized; // 0x1
	unsigned char __pad0[2]; // 0x2
	long cluster_marker_salt; // 0x4
	long cluster_marker_table[16][256]; // 0x8
	bool instanced_geometry_marker_initialized; // 0x4008
	unsigned char __pad1[3]; // 0x4009
	unsigned long instanced_geometry_marker_bit_vectors[16][256]; // 0x400C
	char padding[17416]; // 0x800C
};
#pragma pack(pop)
static_assert(sizeof(s_structure_globals) == 50196, "Invalid s_structure_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_STRUCTURES_STRUCTURES_HPP__
