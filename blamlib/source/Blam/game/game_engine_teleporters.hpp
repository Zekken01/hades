#ifndef __BLAM_GAME_GAME_ENGINE_TELEPORTERS_HPP__
#define __BLAM_GAME_GAME_ENGINE_TELEPORTERS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/game_engine_area_set.hpp"

/* ---------- forward declarations */

struct c_area;
struct c_teleporter_area;

/* ---------- constants */

/* ---------- definitions */

struct c_teleporter_area :
	public c_area
{
	unsigned char __pad0[12]; // 0x64
};
static_assert(sizeof(c_teleporter_area) == 112, "Invalid c_teleporter_area size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_GAME_ENGINE_TELEPORTERS_HPP__
