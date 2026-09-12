#ifndef __BLAM_RENDER_DEPTH_OF_FIELD_HPP__
#define __BLAM_RENDER_DEPTH_OF_FIELD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_depth_of_field;

/* ---------- constants */

/* ---------- definitions */

struct s_depth_of_field
{
	bool enabled; // 0x0
	char field_01; // 0x1
	float field_04; // 0x4
	float focus_near; // 0x8
	float focus_far; // 0xC
	float focus_depth; // 0x10
	float field_14; // 0x14
	float field_18; // 0x18
	long game_time; // 0x1C
	float field_20; // 0x20
	long animation_start_tick; // 0x24
	long animation_end_tick; // 0x28
	float field_2C; // 0x2C
	float field_30; // 0x30
	float field_34; // 0x34
	float field_38; // 0x38
	float field_3C; // 0x3C
	static s_depth_of_field *(*get)();
	static bool (*get_enabled)();
	static float (*get_depth_of_field_blur_sigma)(s_depth_of_field *);
};
static_assert(sizeof(s_depth_of_field) == 64, "Invalid s_depth_of_field size");
static_assert(offsetof(s_depth_of_field, field_04) == 0x4, "s_depth_of_field::field_04 moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_DEPTH_OF_FIELD_HPP__
