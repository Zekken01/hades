#ifndef __BLAM_ITEMS_ITEM_DEFINITIONS_HPP__
#define __BLAM_ITEMS_ITEM_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct s_item_definition;
struct s_item_predicted_bitmap_definition;
struct s_object_definition;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_item_predicted_bitmap_definition
{
	s_tag_reference bitmap; // 0x0
};
static_assert(sizeof(s_item_predicted_bitmap_definition) == 16, "Invalid s_item_predicted_bitmap_definition size");

#pragma pack(push, 4)
struct s_item_definition :
	public s_object_definition
{
	c_flags<enum e_item_definition_flags,long> item_flags; // 0x120
	short old_message_index; // 0x124
	short sort_order; // 0x126
	float old_multiplayer_on_ground_scale; // 0x128
	float old_campaign_on_ground_scale; // 0x12C
	unsigned long pickup_message; // 0x130
	unsigned long swap_message; // 0x134
	unsigned long pickup_or_dual_wield_message; // 0x138
	unsigned long swap_or_dual_wield_message; // 0x13C
	unsigned long picked_up_message; // 0x140
	unsigned long switch_to_message; // 0x144
	unsigned long switch_to_from_ai_message; // 0x148
	unsigned long all_weapons_empty_message; // 0x14C
	s_tag_reference collision_sound; // 0x150
	c_tag_block<s_item_predicted_bitmap_definition> predicted_bitmaps; // 0x160
	s_tag_reference detonation_damage_effect; // 0x16C
	real_bounds detonation_delay; // 0x17C
	s_tag_reference detonating_effect; // 0x184
	s_tag_reference detonation_effect; // 0x194
	float campaign_ground_scale; // 0x1A4
	float multiplayer_ground_scale; // 0x1A8
	float small_hold_scale; // 0x1AC
	float small_holster_scale; // 0x1B0
	float medium_hold_scale; // 0x1B4
	float medium_holster_scale; // 0x1B8
	float large_hold_scale; // 0x1BC
	float large_holster_scale; // 0x1C0
	float huge_hold_scale; // 0x1C4
	float huge_holster_scale; // 0x1C8
	float grounded_friction_length; // 0x1CC
	float grounded_friction_unknown; // 0x1D0
	s_item_definition(s_item_definition &); /* compiler_generated() */
	s_item_definition(s_item_definition const &); /* compiler_generated() */
	s_item_definition(); /* compiler_generated() */
	s_item_definition &operator=(s_item_definition &); /* compiler_generated() */
	s_item_definition &operator=(s_item_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_item_definition) == 468, "Invalid s_item_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ITEMS_ITEM_DEFINITIONS_HPP__
