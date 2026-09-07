#ifndef __BLAM_GAME_GAME_ENGINE_AREA_SET_HPP__
#define __BLAM_GAME_GAME_ENGINE_AREA_SET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"

/* ---------- forward declarations */

struct c_area;
struct real_argb_color;
struct s_multiplayer_object_boundary_geometry_data;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_area
{
	s_multiplayer_object_boundary_geometry_data boundary_geometry; // 0x0
	real_argb_color color; // 0x50
	long object_index; // 0x60
};
#pragma pack(pop)
static_assert(sizeof(c_area) == 100, "Invalid c_area size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_GAME_ENGINE_AREA_SET_HPP__
