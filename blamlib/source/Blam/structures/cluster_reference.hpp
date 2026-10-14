#ifndef __BLAM_STRUCTURES_CLUSTER_REFERENCE_HPP__
#define __BLAM_STRUCTURES_CLUSTER_REFERENCE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_cluster_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_cluster_reference
{
	char bsp_index; // 0x0
	unsigned char cluster_index; // 0x1
};
static_assert(sizeof(s_cluster_reference) == 2, "Invalid s_cluster_reference size");

/* ---------- prototypes */

extern _inline bool const operator==(s_cluster_reference a, s_cluster_reference b);

/* ---------- globals */

/* ---------- public code */

inline bool const operator==(s_cluster_reference a, s_cluster_reference b) // 0x108E3430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??8@YA?B_NUs_cluster_reference@@0@Z");
	// s_cluster_reference b;

	return a.bsp_index == b.bsp_index && a.cluster_index == b.cluster_index;
}

/* ---------- private code */

#endif // __BLAM_STRUCTURES_CLUSTER_REFERENCE_HPP__
