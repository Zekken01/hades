#ifndef __BLAM_VISION_MODE_VISION_MODE_GLOBALS_HPP__
#define __BLAM_VISION_MODE_VISION_MODE_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/vision_mode/vision_mode_definitions.hpp"

/* ---------- forward declarations */

struct s_ping_parameters;
struct s_player_vision_mode;
struct s_vision_mode_globals;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_player_vision_mode
{
	float vision_time; // 0x0
	s_ping_parameters last_ping_parameters; // 0x4
	s_ping_parameters ping_parameters; // 0x1C
	float ping_time; // 0x34
	float field_38; // 0x38
};
#pragma pack(pop)
static_assert(sizeof(s_player_vision_mode) == 60, "Invalid s_player_vision_mode size");

struct s_vision_mode_globals
{
	s_player_vision_mode player_vision_mode[4]; // 0x0
};
static_assert(sizeof(s_vision_mode_globals) == 240, "Invalid s_vision_mode_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_VISION_MODE_VISION_MODE_GLOBALS_HPP__
