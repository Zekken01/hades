#ifndef __BLAM_RASTERIZER_RASTERIZER_VERTEX_TYPES_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_VERTEX_TYPES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_point2d;
struct real_vector2d;
struct s_debug_vertex;
struct s_screen_vertex;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_screen_vertex
{
	real_point2d position; // 0x0
	real_vector2d texcoord; // 0x8
	unsigned __int32 color; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_screen_vertex) == 20, "Invalid s_screen_vertex size");

struct s_debug_vertex
{
	real_point3d position; // 0x0
	unsigned long color; // 0xC
};
static_assert(sizeof(s_debug_vertex) == 16, "Invalid s_debug_vertex size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_VERTEX_TYPES_HPP__
