#ifndef __BLAM_MATH_COLOR_DEFINITIONS_HPP__
#define __BLAM_MATH_COLOR_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct real_argb_color;
struct real_rgb_color;

/* ---------- constants */

/* ---------- definitions */

struct real_rgb_color
{
	float red; // 0x0
	float green; // 0x4
	float blue; // 0x8
};
static_assert(sizeof(real_rgb_color) == 12, "Invalid real_rgb_color size");

struct real_argb_color
{
	float alpha; // 0x0
	float red; // 0x4
	float green; // 0x8
	float blue; // 0xC
};
static_assert(sizeof(real_argb_color) == 16, "Invalid real_argb_color size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MATH_COLOR_DEFINITIONS_HPP__
