#ifndef __BLAM_RENDER_CUBEMAP_SAMPLE_HPP__
#define __BLAM_RENDER_CUBEMAP_SAMPLE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

struct c_dynamic_cubemap_sample;
struct s_cluster_reference;

/* ---------- constants */

/* ---------- definitions */

struct c_dynamic_cubemap_sample
{
	s_cluster_reference cubemap0_location; // 0x0
	char cubemap0_index; // 0x2
	char cubemap0_reference_index; // 0x3
	short cubemap0_bitmap_index; // 0x4
	s_cluster_reference cubemap1_location; // 0x6
	char cubemap1_index; // 0x8
	char cubemap1_reference_index; // 0x9
	short cubemap1_bitmap_index; // 0xA
	float blend; // 0xC
};
static_assert(sizeof(c_dynamic_cubemap_sample) == 16, "Invalid c_dynamic_cubemap_sample size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_CUBEMAP_SAMPLE_HPP__
