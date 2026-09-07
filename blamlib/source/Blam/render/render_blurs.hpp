#ifndef __BLAM_RENDER_RENDER_BLURS_HPP__
#define __BLAM_RENDER_RENDER_BLURS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/rasterizer/rasterizer_globals.hpp"

/* ---------- forward declarations */

struct s_rasterizer_globals;

/* ---------- constants */

enum e_ps_displacement_vector_registers
{
	_ps_displacement_pixel_blur_constants = 158, // 0x009E
	_ps_displacement_view_projection = 160, // 0x00A0
	_ps_displacement_previous_view_projection = 164, // 0x00A4
	_ps_displacement_screen_to_world = 168, // 0x00A8
	_ps_displacement_misc_values = 172, // 0x00AC
	_ps_displacement_blur_max_and_scale = 173, // 0x00AD
	_ps_displacement_crosshair_center = 174, // 0x00AE
	_ps_displacement_zbuffer_xform = 175, // 0x00AF
	_ps_displacement_combined3 = 188, // 0x00BC
	_ps_displacement_screen_constants = 203, // 0x00CB
	_ps_displacement_window_bounds = 204, // 0x00CC
	_ps_displacement_distort_constants = 205, // 0x00CD
	_ps_displacement_resolution_constants = 207, // 0x00CF
	_ps_displacement_crosshair_constants = 209, // 0x00D1
};

enum e_ps_displacement_int_registers
{
	_ps_displacement_num_taps = 2, // 0x0002
};

enum e_ps_displacement_bool_registers
{
	_ps_displacement_do_distortion = 2, // 0x0002
};

/* ---------- definitions */

/* ---------- prototypes */

extern void update_motion_blur_globals(s_rasterizer_globals const *rasg, float motion_blur_strength);

/* ---------- globals */

/* ---------- public code */

_extern void _sub_10AC38D0(s_rasterizer_globals const *, float);
void update_motion_blur_globals(s_rasterizer_globals const *rasg, float motion_blur_strength) // 0x10AC38D0
{
	mangled_x86(MANGLED_TODO, "?update_motion_blur_globals@@YAXPBUs_rasterizer_globals@@M@Z");
	// float motion_blur_strength;
	{
		// float strength_max;
		// float strength_min;
	}
	todo("implement");
	_sub_10AC38D0(rasg, motion_blur_strength);
}

/* ---------- private code */

#endif // __BLAM_RENDER_RENDER_BLURS_HPP__
