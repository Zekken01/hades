#ifndef __MODS_MODGLOBALS_HPP__
#define __MODS_MODGLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct real_rgb_color;
struct s_mod_globals_character_position_info;
struct s_mod_globals_character_region_script;
struct s_mod_globals_player_character_colors;
struct s_mod_globals_player_character_customization;
struct s_tag_reference;
namespace Mods
{
	struct CModGlobals;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_mod_globals_player_character_customization
{
	__int32 global_player_character_type_index; // 0x0
	unsigned long character_name; // 0x4
	unsigned long character_description; // 0x8
	s_tag_reference hud_globals; // 0xC
	s_tag_reference vision_mode; // 0x1C
	s_tag_reference action_set; // 0x2C
	c_tag_block<s_mod_globals_character_region_script> region_camera_scripts; // 0x3C
	s_mod_globals_character_position_info character_position_data; // 0x48
	s_mod_globals_player_character_colors character_colors; // 0xD4
	unsigned char unused[80]; // 0x114
};
#pragma pack(pop)
static_assert(sizeof(s_mod_globals_player_character_customization) == 356, "Invalid s_mod_globals_player_character_customization size");

namespace Mods
{
	struct CModGlobals
	{
		static __int32 FindCharacterSet(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name);
		static __int32 FindCharacterInSet(__int32 characterSetIndex, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name);
		static __int32 GetCharacterVisionModeGlobals(__int32 characterTypeIndex);
		static __int32 GetCharacterHudGlobals(__int32 characterTypeIndex);
		static bool GetCharacterDefaultColors(__int32 characterTypeIndex, unsigned long *colors);
		static bool GetCharacterDefaultColors(__int32 characterTypeIndex, real_rgb_color *colors);
		static s_mod_globals_player_character_customization *GetCustomizationCharacter(__int32 characterTypeIndex);
	};
	static_assert(sizeof(Mods::CModGlobals) == 1, "Invalid Mods::CModGlobals size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_MODGLOBALS_HPP__
