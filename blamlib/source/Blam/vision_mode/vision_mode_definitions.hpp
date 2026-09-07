#ifndef __BLAM_VISION_MODE_VISION_MODE_DEFINITIONS_HPP__
#define __BLAM_VISION_MODE_VISION_MODE_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_ping_parameters;

/* ---------- constants */

enum e_ping_mode
{
	_ping_default = 0,
	_ping_vehicle,
	_ping_observer,
	k_number_of_ping_modes,
};

enum e_vision_mode_pass
{
	_vision_mode_pass_equipment = 0,
	_vision_mode_pass_allies,
	_vision_mode_pass_enemies,
	_vision_mode_pass_objectives,
	_vision_mode_pass_environment,
	k_number_of_vision_mode_passes,
};

/* ---------- definitions */

struct s_ping_parameters
{
	float distance; // 0x0
	float through_walls_distance; // 0x4
	float ping_interval; // 0x8
	float ping_pulse_duration; // 0xC
	float unknown_10; // 0x10
	float ping_delay_by_seconds; // 0x14
};
static_assert(sizeof(s_ping_parameters) == 24, "Invalid s_ping_parameters size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_VISION_MODE_VISION_MODE_DEFINITIONS_HPP__
