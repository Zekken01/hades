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

_extern float _sub_1081D1B0();
_inline float c_render_globals::get_frame_time() // 0x1081D1B0
{
	mangled_x86(MANGLED_TODO, "?get_frame_time@c_render_globals@@SAMXZ");
	// procedure flags: nofpo
	todo("implement");
	float __result = _sub_1081D1B0();
	return __result;
}

_extern long _sub_108EFCB0();
_inline long c_render_globals::get_frame_index() // 0x108EFCB0
{
	mangled_x86(MANGLED_TODO, "?get_frame_index@c_render_globals@@SAJXZ");
	// procedure flags: nofpo
	todo("implement");
	long __result = _sub_108EFCB0();
	return __result;
}

/* ---------- private code */

#endif // __BLAM_RENDER_RENDER_GLOBALS_HPP__
