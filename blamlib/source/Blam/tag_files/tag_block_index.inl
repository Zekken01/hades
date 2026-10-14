#ifndef __BLAM_TAG_FILES_TAG_BLOCK_INDEX_INL__
#define __BLAM_TAG_FILES_TAG_BLOCK_INDEX_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/squads.hpp"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/chud/chud_globals.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

struct s_chud_per_character_globals;
struct s_forge_description_text_entry;
struct s_forge_palette_category;
struct s_game_globals_player_representation;
struct s_model_customization_selection;
struct s_scenario_object_name;
struct s_scenario_trigger_volume;
struct s_scenario_zone_set_pvs;
struct s_weapon_first_person_interface_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

template<> inline c_tag_block_index<s_scenario_object_name,short>::operator short() const // 0x1067D7C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_scenario_object_name@@F@@QBEFXZ");

	return m_index;
}

template<> inline c_tag_block_index<s_scenario_trigger_volume,short>::operator short() const // 0x108C7600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_scenario_trigger_volume@@F@@QBEFXZ");

	return m_index;
}

template<> inline c_tag_block_index<s_forge_description_text_entry,short>::operator short() const // 0x10CA68D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_forge_description_text_entry@@F@@QBEFXZ");

	return m_index;
}

template<> inline c_tag_block_index<s_forge_palette_category,short>::operator short() const // 0x10CA6900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_forge_palette_category@@F@@QBEFXZ");

	return m_index;
}

template<> inline c_tag_block_index<s_game_globals_player_representation,char>::operator char() const // 0x106BE220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_game_globals_player_representation@@D@@QBEDXZ");

	return m_index;
}

template<> inline c_tag_block_index<s_model_customization_selection,char>::operator char() const // 0x109012D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_model_customization_selection@@D@@QBEDXZ");

	return m_index;
}

template<> inline c_tag_block_index<s_chud_per_character_globals,char>::operator char() const // 0x10ABBEA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_chud_per_character_globals@@D@@QBEDXZ");

	return m_index;
}

template<> inline c_tag_block_index<s_weapon_first_person_interface_definition,char>::operator char() const // 0x10ABBED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_weapon_first_person_interface_definition@@D@@QBEDXZ");

	return m_index;
}

template<> inline c_tag_block_index<s_scenario_zone_set_pvs,long>::operator long() const // 0x10AC3F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_index@Us_scenario_zone_set_pvs@@J@@QBEJXZ");

	return m_index;
}

/* ---------- private code */

#endif // __BLAM_TAG_FILES_TAG_BLOCK_INDEX_INL__
