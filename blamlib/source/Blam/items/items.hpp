#ifndef __BLAM_ITEMS_ITEMS_HPP__
#define __BLAM_ITEMS_ITEMS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/objects.hpp"

/* ---------- forward declarations */

struct s_item_data;
struct s_object_data;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_item_data :
	public s_object_data
{
	char item_flags; // 0x178
	char inventory_state; // 0x179
	unsigned long ignore_object_index; // 0x17C
	long last_relevant_time; // 0x180
	unsigned long owner_unit_index; // 0x184
	s_item_data(s_item_data &); /* compiler_generated() */
	s_item_data(s_item_data const &); /* compiler_generated() */
	s_item_data(); /* compiler_generated() */
	s_item_data &operator=(s_item_data &); /* compiler_generated() */
	s_item_data &operator=(s_item_data const &); /* compiler_generated() */
	unsigned char __pad1[4]; // 0x188
};
#pragma pack(pop)
static_assert(sizeof(s_item_data) == 396, "Invalid s_item_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ITEMS_ITEMS_HPP__
