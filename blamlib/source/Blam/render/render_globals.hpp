#ifndef __BLAM_RENDER_RENDER_GLOBALS_HPP__
#define __BLAM_RENDER_RENDER_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_render_globals;

/* ---------- constants */

/* ---------- definitions */

struct c_render_globals
{
	static bool (*const get_distortion_active)();
	static bool (*const get_distortion_visible)();
	static void (*const set_distortion_active)(bool);
	static void (*const set_distortion_visible)(bool);
	static char (*const set_distortion_history)(char);
	static _inline float get_frame_time();
	static _inline long get_frame_index();
	static float &motion_blur_velocity_threshold;
};
static_assert(sizeof(c_render_globals) == 1, "Invalid c_render_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline float c_render_globals::get_frame_time() // 0x1081D1B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_frame_time@c_render_globals@@SAMXZ");

	return *(float *)0x50e88f0;
}

inline long c_render_globals::get_frame_index() // 0x108EFCB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_frame_index@c_render_globals@@SAJXZ");

	return *(long *)0x1913474;
}

/* ---------- private code */

#endif // __BLAM_RENDER_RENDER_GLOBALS_HPP__
