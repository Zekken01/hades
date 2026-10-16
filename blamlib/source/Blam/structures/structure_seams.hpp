#ifndef __BLAM_STRUCTURES_STRUCTURE_SEAMS_HPP__
#define __BLAM_STRUCTURES_STRUCTURE_SEAMS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

struct c_seam_connected_cluster_references;
struct s_cluster_reference;
struct s_seam_mapping;
struct s_structure_seam_globals;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_seam_connected_cluster_references
{
	long reference_count; // 0x0
	s_static_array<s_cluster_reference,64> references; // 0x4
	_inline long find(s_cluster_reference cluster_reference);
	_inline bool insert(s_cluster_reference reference);
};
#pragma pack(pop)
static_assert(sizeof(c_seam_connected_cluster_references) == 132, "Invalid c_seam_connected_cluster_references size");

#pragma pack(push, 4)
struct s_seam_mapping
{
	public:
#pragma pack(push, 4)
	struct s_seam_cluster_mapping
	{
		real_point3d cluster_center; // 0x0
		short cluster_indices[2]; // 0xC
		short cluster_mapping_indices[2]; // 0x10
	};
#pragma pack(pop)
	static_assert(sizeof(s_seam_cluster_mapping) == 20, "Invalid s_seam_cluster_mapping size");
	public:
	char bsp_indices[2]; // 0x0
	short clusters_count; // 0x2
	s_seam_cluster_mapping clusters[32]; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_seam_mapping) == 644, "Invalid s_seam_mapping size");

#pragma pack(push, 4)
struct s_structure_seam_globals
{
	unsigned long material_extant_flags[16][16]; // 0x0
	s_static_array<s_seam_mapping,128> mappings; // 0x400
	unsigned long active_seams_mask[4]; // 0x14600
	unsigned long connected_bsps_mask; // 0x14610
};
#pragma pack(pop)
static_assert(sizeof(s_structure_seam_globals) == 83476, "Invalid s_structure_seam_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline long c_seam_connected_cluster_references::find(s_cluster_reference cluster_reference) // 0x10AC4C40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find@c_seam_connected_cluster_references@@QAEJUs_cluster_reference@@@Z");

	for (long i = 0; i < reference_count; i++)
	{
		if (references[i] == cluster_reference)
		{
			return i;
		}
	}
	return -1;
}

inline bool c_seam_connected_cluster_references::insert(s_cluster_reference reference) // 0x10AC5140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?insert@c_seam_connected_cluster_references@@QAE_NUs_cluster_reference@@@Z");

	if (reference_count >= references.get_count())
	{
		return false;
	}
	if (find(reference) == -1)
	{
		references[reference_count++] = reference;
	}
	return true;
}

/* ---------- private code */

#endif // __BLAM_STRUCTURES_STRUCTURE_SEAMS_HPP__
