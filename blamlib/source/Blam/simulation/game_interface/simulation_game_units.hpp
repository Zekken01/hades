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
	long definition_index; // 0x4
	long unknown; // 0x8
};
static_assert(sizeof(s_simulation_unit_pickup_event_data) == 12, "Invalid s_simulation_unit_pickup_event_data size");
static_assert(offsetof(s_simulation_unit_pickup_event_data, definition_index) == 0x4, "s_simulation_unit_pickup_event_data::definition_index moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SIMULATION_GAME_INTERFACE_SIMULATION_GAME_UNITS_HPP__
