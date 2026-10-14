#ifndef __BLAM_VISIBILITY_VISIBILITY_OBJECT_RENDER_INFO_HPP__
#define __BLAM_VISIBILITY_VISIBILITY_OBJECT_RENDER_INFO_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"


/* ---------- forward declarations */

struct s_lod_alphas;
struct s_render_object_info;
struct s_shader_extern_info;

/* ---------- constants */

/* ---------- definitions */

struct s_lod_alphas
{
	unsigned char lod_fade; // 0x0
	unsigned char field_1; // 0x1
	unsigned char shadow_alpha; // 0x2
	unsigned char field_3; // 0x3
};
static_assert(sizeof(s_lod_alphas) == 4, "Invalid s_lod_alphas size");

#pragma pack(push, 4)
struct s_render_object_info
{
	long region_count; // 0x0
	long render_model_index; // 0x4
	long skinning_memory_designator; // 0x8
	unsigned char skinning_matrix_count; // 0xC
	unsigned char region_mesh_indices[16]; // 0xD
	unsigned char __pad0[1]; // 0x1D
	short sorted_regions[16]; // 0x1E
	short region_transparent_sort_indices[16]; // 0x3E
	short lod_type; // 0x5E
	short lightmap_object_index; // 0x60
	long clipping_mask; // 0x64
	s_shader_extern_info *render_info; // 0x68
};
#pragma pack(pop)
static_assert(sizeof(s_render_object_info) == 108, "Invalid s_render_object_info size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_VISIBILITY_VISIBILITY_OBJECT_RENDER_INFO_HPP__
