#ifndef __BLAM_GAME_PLAYER_MODEL_CUSTOMIZATION_HPP__
#define __BLAM_GAME_PLAYER_MODEL_CUSTOMIZATION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_model_customization_player_region;
struct s_model_customization_player_region_permutation;
struct s_model_customization_region_permutation;
struct s_model_customization_selection;

/* ---------- constants */

/* ---------- definitions */

struct s_model_customization_region_permutation
{
	unsigned long region_name; // 0x0
	unsigned long permutation_name; // 0x4
};
static_assert(sizeof(s_model_customization_region_permutation) == 8, "Invalid s_model_customization_region_permutation size");

#pragma pack(push, 4)
struct s_model_customization_player_region_permutation
{
	public:
	enum region_permutation_flags
	{
		_permutationHasRequirement = 0,
		_permutationHasSpecialRequirement,
		_permutationBit2,
		_permutationBit3,
		_permutationBit4,
		_permutationBit5,
		_permutationBit6,
		_permutationBit7,
		_permutationBit8,
		_permutationBit9,
		_permutationBit10,
		_permutationBit11,
		_permutationBit12,
		_permutationBit13,
		_permutationBit14,
		_permutationHidden,
	};
	public:
	unsigned long name; // 0x0
	unsigned long description; // 0x4
	unsigned short flags; // 0x8
	unsigned char __pad0[2]; // 0xA
	unsigned long achievement_requirement; // 0xC
	c_tag_block<s_model_customization_region_permutation> variants; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_model_customization_player_region_permutation) == 28, "Invalid s_model_customization_player_region_permutation size");

struct s_model_customization_player_region
{
	unsigned long name; // 0x0
	c_tag_block<s_model_customization_player_region_permutation> permutations; // 0x4
};
static_assert(sizeof(s_model_customization_player_region) == 16, "Invalid s_model_customization_player_region size");

struct s_model_customization_selection
{
	unsigned long character_name; // 0x0
	c_tag_block<s_model_customization_player_region> regions; // 0x4
};
static_assert(sizeof(s_model_customization_selection) == 16, "Invalid s_model_customization_selection size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_PLAYER_MODEL_CUSTOMIZATION_HPP__
