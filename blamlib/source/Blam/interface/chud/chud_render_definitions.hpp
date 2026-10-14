#ifndef __BLAM_INTERFACE_CHUD_CHUD_RENDER_DEFINITIONS_HPP__
#define __BLAM_INTERFACE_CHUD_CHUD_RENDER_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_vector4d;
struct s_hud_shader_info;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_hud_shader_info
{
	long vertex_shader; // 0x0
	long pixel_shader; // 0x4
	short blend_mode; // 0x8
	real_vector4d chud_color_output_a; // 0xC
	real_vector4d chud_color_output_b; // 0x1C
	real_vector4d chud_color_output_c; // 0x2C
	real_vector4d chud_color_output_d; // 0x3C
	real_vector4d chud_color_output_e; // 0x4C
	real_vector4d chud_color_output_f; // 0x5C
	real_vector4d chud_scalar_output_abcd; // 0x6C
	real_vector4d chud_scalar_output_ef; // 0x7C
	real_vector4d chud_texture_transform; // 0x8C
	short_rectangle2d rect; // 0x9C
};
#pragma pack(pop)
static_assert(sizeof(s_hud_shader_info) == 164, "Invalid s_hud_shader_info size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_CHUD_CHUD_RENDER_DEFINITIONS_HPP__
