#ifndef __BLAM_DEVICES_DEVICE_DEFINITIONS_HPP__
#define __BLAM_DEVICES_DEVICE_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_control_definition;
struct s_device_definition;
struct s_machine_definition;
struct s_object_definition;
struct s_tag_reference;

/* ---------- constants */

enum e_machine_type
{
	_machine_type_door = 0,
	_machine_type_platform,
	_machine_type_gear,
};

/* ---------- definitions */

struct s_device_definition :
	public s_object_definition
{
	unsigned long device_flags; // 0x120
	float power_transition_time; // 0x124
	float power_acceleration_time; // 0x128
	float position_time; // 0x12C
	float position_acceleration_time; // 0x130
	float depowered_position_transition_time; // 0x134
	float depowered_position_acceleration_time; // 0x138
	unsigned long lightmap_flags; // 0x13C
	s_tag_reference open_effect; // 0x140
	s_tag_reference close_effect; // 0x150
	s_tag_reference opened_effect; // 0x160
	s_tag_reference closed_effect; // 0x170
	s_tag_reference depowered_effect; // 0x180
	s_tag_reference repowered_effect; // 0x190
	float delay_time; // 0x1A0
	s_tag_reference delay_effect; // 0x1A4
	float proximity_radius; // 0x1B4
	s_device_definition(s_device_definition &); /* compiler_generated() */
	s_device_definition(s_device_definition const &); /* compiler_generated() */
	s_device_definition(); /* compiler_generated() */
	s_device_definition &operator=(s_device_definition &); /* compiler_generated() */
	s_device_definition &operator=(s_device_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_device_definition) == 440, "Invalid s_device_definition size");

struct s_machine_definition :
	public s_device_definition
{
	c_enum<enum e_machine_type,short> machine_type; // 0x1B8
	unsigned short machine_flags; // 0x1BA
	float door_open_time; // 0x1BC
	float occlusion_bounds_minimum; // 0x1C0
	float occlusion_bounds_maximum; // 0x1C4
	short collision_response; // 0x1C8
	short elevator_node; // 0x1CA
	short pathfinding_policy; // 0x1CC
	s_machine_definition(s_machine_definition &); /* compiler_generated() */
	s_machine_definition(s_machine_definition const &); /* compiler_generated() */
	s_machine_definition(); /* compiler_generated() */
	s_machine_definition &operator=(s_machine_definition &); /* compiler_generated() */
	s_machine_definition &operator=(s_machine_definition const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x1CE
};
static_assert(sizeof(s_machine_definition) == 464, "Invalid s_machine_definition size");

#pragma pack(push, 4)
struct s_control_definition :
	public s_device_definition
{
	short control_type; // 0x1B8
	short triggers_when; // 0x1BA
	float call_value; // 0x1BC
	unsigned long action_string; // 0x1C0
	s_tag_reference on; // 0x1C4
	s_tag_reference off; // 0x1D4
	s_tag_reference deny; // 0x1E4
	s_control_definition(s_control_definition &); /* compiler_generated() */
	s_control_definition(s_control_definition const &); /* compiler_generated() */
	s_control_definition(); /* compiler_generated() */
	s_control_definition &operator=(s_control_definition &); /* compiler_generated() */
	s_control_definition &operator=(s_control_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_control_definition) == 500, "Invalid s_control_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_DEVICES_DEVICE_DEFINITIONS_HPP__
