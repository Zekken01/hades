#ifndef __BLAM_PHYSICS_BREAKABLE_SURFACES_HPP__
#define __BLAM_PHYSICS_BREAKABLE_SURFACES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_breakable_surface_globals;
struct s_breakable_surface_impact_decal;
struct s_breakable_surface_set;

/* ---------- constants */

/* ---------- definitions */

struct s_breakable_surface_set
{
	long first_broken_event_index; // 0x0
	bool is_broken; // 0x4
	unsigned long subpart_visibility[8]; // 0x8
	unsigned char impct_decal_indices[16]; // 0x28
};
static_assert(sizeof(s_breakable_surface_set) == 56, "Invalid s_breakable_surface_set size");
static_assert(offsetof(s_breakable_surface_set, subpart_visibility) == 0x8, "s_breakable_surface_set::subpart_visibility moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_breakable_surface_impact_decal
{
	long timestamp; // 0x0
	short breakable_surface_index; // 0x4
	short breakable_surface_set_index; // 0x6
	short structure_bsp_index; // 0x8
	short instance_index; // 0xA
	long surface_index; // 0xC
	real_point3d position; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_breakable_surface_impact_decal) == 28, "Invalid s_breakable_surface_impact_decal size");

struct s_breakable_surface_globals
{
	bool enabled; // 0x0
	bool unknown_flag; // 0x1
	bool havok_geometry_dirty; // 0x2
	long next_breakable_surface_set_index; // 0x4
	unsigned long active_bsp_mask; // 0x8
	long impact_decal_next_index; // 0xC
	__int32 field_10; // 0x10
	s_breakable_surface_impact_decal impact_decals[127]; // 0x14
	s_breakable_surface_set breakable_surface_sets[2048]; // 0xDF8
	short structure_bsp_mapping_table[16]; // 0x1CDF8
	short instanced_geometry_mapping_table[16][4096]; // 0x1CE18
};
static_assert(sizeof(s_breakable_surface_globals) == 249368, "Invalid s_breakable_surface_globals size");
static_assert(offsetof(s_breakable_surface_globals, next_breakable_surface_set_index) == 0x4, "s_breakable_surface_globals::next_breakable_surface_set_index moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_PHYSICS_BREAKABLE_SURFACES_HPP__
