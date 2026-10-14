#ifndef __BLAM_RASTERIZER_RASTERIZER_SCREEN_GEOMETRY_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_SCREEN_GEOMETRY_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_rasterizer_screen_geometry_parameters;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_rasterizer_screen_geometry_parameters
{
	unsigned char __pad0[8]; // 0x0
	long texture_datum_index; // 0x8
	long texture_datum_index_2; // 0xC
	unsigned char __pad1[4]; // 0x10
	char texture_address_mode1; // 0x14
	char texture_address_mode2; // 0x15
	char field_16; // 0x16
	unsigned char __pad2[41]; // 0x17
	float field_40; // 0x40
	float field_44; // 0x44
	float field_48; // 0x48
	float field_4C; // 0x4C
	unsigned char __pad3[64]; // 0x50
	short alpha_blend_mode; // 0x90
	char texture_filter_mode; // 0x92
	long explicit_shader_index; // 0x94
	long surface_index; // 0x98
};
#pragma pack(pop)
static_assert(sizeof(s_rasterizer_screen_geometry_parameters) == 156, "Invalid s_rasterizer_screen_geometry_parameters size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_SCREEN_GEOMETRY_HPP__
