#ifndef __MODS_USER_INTERFACE_MODS_HPP__
#define __MODS_USER_INTERFACE_MODS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/networking/session/network_session_membership.hpp"

/* ---------- forward declarations */

class c_user_interface_mods_player_character_data;
struct s_mod_globals_definition;
union tag_string;

/* ---------- constants */

/* ---------- definitions */

class c_user_interface_mods_player_character_data
{
public:
	public:
#pragma pack(push, 4)
	struct s_player_character_set
	{
		tag_string display_name; // 0x0
		unsigned long name; // 0x20
	};
#pragma pack(pop)
	static_assert(sizeof(s_player_character_set) == 36, "Invalid s_player_character_set size");
	struct s_player_character
	{
		tag_string display_name; // 0x0
		unsigned long name; // 0x20
		long character_set_index; // 0x24
	};
	static_assert(sizeof(s_player_character) == 40, "Invalid s_player_character size");
	public:
    enum
	{
		k_maximum_set_count = 8, // 0x0008
		k_maximum_character_count = 128, // 0x0080
	};
	long player_character_set_count; // 0x0
	s_static_array<s_player_character_set,8> player_character_sets; // 0x4
	long player_characters_count; // 0x124
	s_static_array<s_player_character,128> player_characters; // 0x128
	void update();
private:
	bool build_from_cache();
	bool build_from_mod_package();
	bool build_from_mod_globals(s_mod_globals_definition *mod_globals);
};
static_assert(sizeof(c_user_interface_mods_player_character_data) == 5416, "Invalid c_user_interface_mods_player_character_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_USER_INTERFACE_MODS_HPP__
