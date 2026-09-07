#ifndef __BLAM_RASTERIZER_RASTERIZER_LUT_CONTROL_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_LUT_CONTROL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"

/* ---------- forward declarations */

class c_rasterizer_LUT_control;
struct _D3DGAMMARAMP;
struct real_rgb_color;

/* ---------- constants */

/* ---------- definitions */

class c_rasterizer_LUT_control
{
public:
	long m_buffer_type; // 0x0
	float m_buffer_curve; // 0x4
	float m_target_curve; // 0x8
	long m_gamma_mode; // 0xC
	real_rgb_color m_white_level; // 0x10
	real_rgb_color m_black_level; // 0x1C
	bool same_curve_as(c_rasterizer_LUT_control *x) const;
	void compute_LUT(_D3DGAMMARAMP *ramp);
	static bool initialized();
	static bool initialize_LUT_textures();
	static void set_LUT_texture(long sampler);
	static void release_textures();
	static float sample_ramp(unsigned short *ramp_channel, float coord);
	static void update_LUT_gpu();
};
static_assert(sizeof(c_rasterizer_LUT_control) == 40, "Invalid c_rasterizer_LUT_control size");

/* ---------- prototypes */

extern float get_linear_buffer_value(long a1, long max_pixel_value, float a3);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_LUT_CONTROL_HPP__
