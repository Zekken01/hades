#ifndef __BLAM_ITEMS_EQUIPMENT_HPP__
#define __BLAM_ITEMS_EQUIPMENT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/items.hpp"
#include "Blam/objects/damage.hpp"

/* ---------- forward declarations */

struct s_damage_owner;
struct s_equipment_data;
struct s_item_data;

/* ---------- constants */

/* ---------- definitions */

struct s_equipment_data :
	public s_item_data
{
	unsigned short equipment_flags; // 0x18C
	long creation_time; // 0x190
	long last_use_time; // 0x194
	char number_of_charges; // 0x198
	long owner_unit_index; // 0x19C
	s_damage_owner equipment_damage_owner; // 0x1A0
	unsigned long effect_index; // 0x1AC
	long field_1B0; // 0x1B0
	long field_1B4; // 0x1B4
	long tracked_effects[16]; // 0x1B8
	s_equipment_data(s_equipment_data &); /* compiler_generated() */
	s_equipment_data(s_equipment_data const &); /* compiler_generated() */
	s_equipment_data(); /* compiler_generated() */
	s_equipment_data &operator=(s_equipment_data &); /* compiler_generated() */
	s_equipment_data &operator=(s_equipment_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_equipment_data) == 504, "Invalid s_equipment_data size");
static_assert(offsetof(s_equipment_data, creation_time) == 0x190, "s_equipment_data::creation_time moved when its reconstructed padding was removed");
static_assert(offsetof(s_equipment_data, owner_unit_index) == 0x19C, "s_equipment_data::owner_unit_index moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ITEMS_EQUIPMENT_HPP__
