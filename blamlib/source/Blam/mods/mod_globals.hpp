#ifndef __BLAM_MODS_MOD_GLOBALS_HPP__
#define __BLAM_MODS_MOD_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "mods/ModGlobals.hpp"

/* ---------- forward declarations */

struct s_mod_globals_definition;
struct s_mod_globals_player_character;
struct s_mod_globals_player_character_customization;
struct s_mod_globals_player_character_set;
union tag_string;

/* ---------- constants */

enum
{
	_mod_globals_tag = 'modg', // 0x6D6F6467
};

/* ---------- definitions */

struct s_mod_globals_player_character
{
	tag_string display_name; // 0x0
	unsigned long name; // 0x20
	float random_chance; // 0x24
};
static_assert(sizeof(s_mod_globals_player_character) == 40, "Invalid s_mod_globals_player_character size");

#pragma pack(push, 4)
struct s_mod_globals_player_character_set
{
	tag_string display_name; // 0x0
	unsigned long name; // 0x20
	float random_chance; // 0x24
	c_tag_block<s_mod_globals_player_character> characters; // 0x28
	unsigned char unused[80]; // 0x34
};
#pragma pack(pop)
static_assert(sizeof(s_mod_globals_player_character_set) == 132, "Invalid s_mod_globals_player_character_set size");

// s_mod_globals_player_character_colors is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_mod_globals_character_region_script is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_mod_globals_character_position_info is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

#pragma pack(push, 4)
struct s_mod_globals_definition
{
	__int32 version; // 0x0
	c_tag_block<s_mod_globals_player_character_set> player_character_sets; // 0x4
	c_tag_block<s_mod_globals_player_character_customization> player_character_customizations; // 0x10
	unsigned char unused[256]; // 0x1C
};
#pragma pack(pop)
static_assert(sizeof(s_mod_globals_definition) == 284, "Invalid s_mod_globals_definition size");

/* ---------- prototypes */

extern s_mod_globals_definition *mod_globals_get_definition();

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MODS_MOD_GLOBALS_HPP__
