#ifndef __BLAM_DEVICES_DEVICES_HPP__
#define __BLAM_DEVICES_DEVICES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/data.hpp"
#include "Blam/objects/objects.hpp"

/* ---------- forward declarations */

struct s_datum;
struct s_device_animation_control;
struct s_device_data;
struct s_device_group_datum;
struct s_object_data;

/* ---------- constants */

/* ---------- definitions */

struct s_device_animation_control
{
	float field_0; // 0x0
	float field_4; // 0x4
	__int32 field_8; // 0x8
	__int32 field_C; // 0xC
	__int32 field_10; // 0x10
	float field_14; // 0x14
	float field_18; // 0x18
	float field_1C; // 0x1C
};
static_assert(sizeof(s_device_animation_control) == 32, "Invalid s_device_animation_control size");

struct s_device_data :
	public s_object_data
{
	unsigned long device_flags; // 0x178
	long power_group_index; // 0x17C
	float power; // 0x180
	float power_velocity; // 0x184
	long position_group_index; // 0x188
	float position; // 0x18C
	float position_velocity; // 0x190
	short delay_ticks; // 0x194
	short field_196; // 0x196
	s_device_animation_control position_track; // 0x198
	s_device_animation_control overlay_track; // 0x1B8
	char position_animation_channel[60]; // 0x1D8
	char power_animation_channel[60]; // 0x214
	s_device_data(s_device_data &); /* compiler_generated() */
	s_device_data(s_device_data const &); /* compiler_generated() */
	s_device_data(); /* compiler_generated() */
	s_device_data &operator=(s_device_data &); /* compiler_generated() */
	s_device_data &operator=(s_device_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_device_data) == 592, "Invalid s_device_data size");

struct s_device_group_datum :
	public s_datum
{
	unsigned short flags; // 0x2
	float value; // 0x4
	float initial_value; // 0x8
	long object_index; // 0xC
};
static_assert(sizeof(s_device_group_datum) == 16, "Invalid s_device_group_datum size");

/* ---------- prototypes */

extern c_data_array<s_device_group_datum> *device_groups_get();
extern long device_group_new(long device_index, float initial_value, unsigned long flags);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_DEVICES_DEVICES_HPP__
