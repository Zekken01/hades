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

extern bool const _sub_108E3430(s_cluster_reference, s_cluster_reference);
_inline bool const operator==(s_cluster_reference a, s_cluster_reference b) // 0x108E3430
{
	mangled_x86(MANGLED_TODO, "??8@YA?B_NUs_cluster_reference@@0@Z");
	// s_cluster_reference b;
	todo("implement");
	bool const __result = _sub_108E3430(a, b);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_STRUCTURES_CLUSTER_REFERENCE_HPP__
