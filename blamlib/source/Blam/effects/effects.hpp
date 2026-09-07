#ifndef __BLAM_EFFECTS_EFFECTS_HPP__
#define __BLAM_EFFECTS_EFFECTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/scenario/scenario_definitions.hpp"

/* ---------- forward declarations */

struct real_matrix4x3;
struct real_vector3d;
struct s_damage_owner;
struct s_damage_reporting_info;
struct s_datum;
struct s_effect_datum;
struct s_effect_event_datum;
struct s_effect_location_datum;
struct s_effect_message;
struct s_scenario_location;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_effect_message
{
	c_flags<enum e_effect_message_type,unsigned char> type; // 0x0
	unsigned char __pad0[3]; // 0x1
	long effect_index; // 0x4
	long definition_index; // 0x8
	long event_index; // 0xC
	unsigned char __pad1[2]; // 0x10
	short particle_system_count; // 0x12
	long field_14; // 0x14
	real_matrix4x3 transform; // 0x18
	real_vector3d velocity; // 0x4C
	s_effect_message(s_effect_message &); /* compiler_generated() */
	s_effect_message(s_effect_message const &); /* compiler_generated() */
	s_effect_message(); /* compiler_generated() */
	s_effect_message &operator=(s_effect_message &); /* compiler_generated() */
	s_effect_message &operator=(s_effect_message const &); /* compiler_generated() */
	unsigned char __pad2[4]; // 0x58
};
#pragma pack(pop)
static_assert(sizeof(s_effect_message) == 92, "Invalid s_effect_message size");

struct s_effect_datum :
	public s_datum
{
	unsigned char __pad0[2]; // 0x2
	char Flags; // 0x4
	unsigned char __pad1[1]; // 0x5
	unsigned char environment_flags; // 0x6
	unsigned char __pad2[1]; // 0x7
	long definition_index; // 0x8
	long looping_sound_index; // 0xC
	long node_index; // 0x10
	unsigned char __pad3[2]; // 0x14
	short field_16; // 0x16
	long field_18; // 0x18
	long field_1C; // 0x1C
	s_scenario_location location; // 0x20
	unsigned char __pad4[2]; // 0x22
	real_vector3d linear_velocity; // 0x24
	long object_index; // 0x30
	s_damage_owner damage_owner; // 0x34
	s_damage_reporting_info damage_reporting_info; // 0x40
	char field_44; // 0x44
	char field_45; // 0x45
	char field_46; // 0x46
	char field_47; // 0x47
	long particle_index; // 0x48
	long event_index; // 0x4C
	float primary_scale; // 0x50
	float secondary_scale; // 0x54
	unsigned char __pad5[8]; // 0x58
	long locations[8]; // 0x60
	long lightprobe_index; // 0x80
	unsigned char __pad6[4]; // 0x84
	unsigned long random_seed; // 0x88
	s_effect_datum(s_effect_datum &); /* compiler_generated() */
	s_effect_datum(s_effect_datum const &); /* compiler_generated() */
	s_effect_datum(); /* compiler_generated() */
	s_effect_datum &operator=(s_effect_datum &); /* compiler_generated() */
	s_effect_datum &operator=(s_effect_datum const &); /* compiler_generated() */
	unsigned char __pad7[20]; // 0x8C
};
static_assert(sizeof(s_effect_datum) == 160, "Invalid s_effect_datum size");

struct s_effect_location_datum :
	public s_datum
{
	unsigned short node_index; // 0x2
	__int32 field_04; // 0x4
	__int32 next_location_index; // 0x8
	real_matrix4x3 world_location; // 0xC
};
static_assert(sizeof(s_effect_location_datum) == 64, "Invalid s_effect_location_datum size");

struct s_effect_event_datum :
	public s_datum
{
	char flags; // 0x2
	char event_index; // 0x3
	short field_04; // 0x4
	short field_06; // 0x6
	__int32 next_event; // 0x8
	float time; // 0xC
	float duration; // 0x10
};
static_assert(sizeof(s_effect_event_datum) == 20, "Invalid s_effect_event_datum size");

/* ---------- prototypes */

extern c_data_array<s_effect_datum> *effects_get();

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_EFFECTS_EFFECTS_HPP__
