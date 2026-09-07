#ifndef __BLAM_INTERFACE_USER_INTERFACE_MULTIPLAYER_GAME_SETTINGS_HPP__
#define __BLAM_INTERFACE_USER_INTERFACE_MULTIPLAYER_GAME_SETTINGS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_text_value_pair_definition;

/* ---------- constants */

/* ---------- definitions */

// s_text_value_pair is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

struct s_text_value_pair_definition
{
	long parameter_type; // 0x0
	unsigned long parameter_name; // 0x4
	unsigned long parameter_description; // 0x8
	c_tag_block<s_text_value_pair> values; // 0xC
};
static_assert(sizeof(s_text_value_pair_definition) == 24, "Invalid s_text_value_pair_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_USER_INTERFACE_MULTIPLAYER_GAME_SETTINGS_HPP__
