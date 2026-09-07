#ifndef __BLAM_MATH_INTEGER_MATH_DEFINITIONS_HPP__
#define __BLAM_MATH_INTEGER_MATH_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct short_bounds;
struct short_point_2d;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

struct short_bounds
{
	short lower; // 0x0
	short upper; // 0x2
};
static_assert(sizeof(short_bounds) == 4, "Invalid short_bounds size");

struct short_point_2d
{
	short x; // 0x0
	short y; // 0x2
};
static_assert(sizeof(short_point_2d) == 4, "Invalid short_point_2d size");

struct short_rectangle2d
{
	short y0; // 0x0
	short x0; // 0x2
	short y1; // 0x4
	short x1; // 0x6
};
static_assert(sizeof(short_rectangle2d) == 8, "Invalid short_rectangle2d size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MATH_INTEGER_MATH_DEFINITIONS_HPP__
