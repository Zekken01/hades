#ifndef __BLAM_SIMULATION_SIMULATION_QUEUE_GLOBAL_EVENTS_HPP__
#define __BLAM_SIMULATION_SIMULATION_QUEUE_GLOBAL_EVENTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/saved_games/scenario_map_variant.hpp"

/* ---------- forward declarations */

struct s_map_variant_placement_properties;
struct s_simulation_queue_sandbox_event_data;

/* ---------- constants */

/* ---------- definitions */

struct s_simulation_queue_sandbox_event_data
{
	public:
	enum e_event_type
	{
		_event_type_place_object = 0,
		_event_type_delete_object,
		_event_type_toggle_player_mode,
		_event_type_start_editing_object,
		_event_type_stop_editing_object,
		_event_type_update_variant_object_properties,
		_event_type_edit_object_quota,
		_event_type_switch_game_engine,
	};
	public:
	e_event_type type; // 0x0
	long object_definition_index; // 0x4
	long map_variant_index; // 0x8
	long player_index; // 0xC
	float object_throw_force; // 0x10
	unsigned char quota_min; // 0x14
	unsigned char quota_max; // 0x15
	unsigned char __pad0[2]; // 0x16
	real_point3d position; // 0x18
	long game_engine_type; // 0x24
	s_map_variant_placement_properties object_properties; // 0x28
	s_simulation_queue_sandbox_event_data(s_simulation_queue_sandbox_event_data &); /* compiler_generated() */
	s_simulation_queue_sandbox_event_data(s_simulation_queue_sandbox_event_data const &); /* compiler_generated() */
	_inline s_simulation_queue_sandbox_event_data(); /* compiler_generated() */
	s_simulation_queue_sandbox_event_data &operator=(s_simulation_queue_sandbox_event_data &); /* compiler_generated() */
	s_simulation_queue_sandbox_event_data &operator=(s_simulation_queue_sandbox_event_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_simulation_queue_sandbox_event_data) == 64, "Invalid s_simulation_queue_sandbox_event_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SIMULATION_SIMULATION_QUEUE_GLOBAL_EVENTS_HPP__
