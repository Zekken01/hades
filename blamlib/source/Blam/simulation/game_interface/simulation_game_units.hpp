#ifndef __BLAM_SIMULATION_GAME_INTERFACE_SIMULATION_GAME_UNITS_HPP__
#define __BLAM_SIMULATION_GAME_INTERFACE_SIMULATION_GAME_UNITS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_simulation_unit_pickup_event_data;

/* ---------- constants */

/* ---------- definitions */

struct s_simulation_unit_pickup_event_data
{
	short type; // 0x0
	unsigned char __pad0[2]; // 0x2
	long definition_index; // 0x4
	long unknown; // 0x8
};
static_assert(sizeof(s_simulation_unit_pickup_event_data) == 12, "Invalid s_simulation_unit_pickup_event_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SIMULATION_GAME_INTERFACE_SIMULATION_GAME_UNITS_HPP__
