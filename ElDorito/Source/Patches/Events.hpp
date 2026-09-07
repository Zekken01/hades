#ifndef __PATCHES_EVENTS_HPP__
#define __PATCHES_EVENTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/Audio.hpp"

#include <functional>

/* ---------- forward declarations */

struct s_game_engine_event_data;
struct s_multiplayer_event_response_definition;
struct s_multiplayer_event_sound_response_definition;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_multiplayer_event_response_definition
{
	c_flags<enum e_game_engine_event_response_flags,unsigned short> flags; // 0x0
	c_enum<enum e_game_engine_event_type,short> type; // 0x2
	unsigned long event; // 0x4
	c_enum<enum e_game_engine_event_audience,short> audience; // 0x8
	short display_priority; // 0xA
	short sub_priority; // 0xC
	c_enum<enum e_game_engine_event_team,short> display_context; // 0xE
	unsigned long display_string; // 0x10
	unsigned long medal_award; // 0x14
	long earned_wp; // 0x18
	float display_time; // 0x1C
	c_enum<enum e_game_engine_event_audience,short> required_field; // 0x20
	c_enum<enum e_game_engine_event_audience,short> excluded_audience; // 0x22
	c_enum<enum e_game_engine_event_audience,short> splitscreen_suppression; // 0x24
	unsigned char __pad0[2]; // 0x26
	unsigned long primary_string; // 0x28
	long primary_string_duration; // 0x2C
	unsigned long secondary_string; // 0x30
	long secondary_string_duration; // 0x34
	c_flags<enum e_game_engine_event_response_sound_flags,unsigned short> sound_flags; // 0x38
	unsigned char __pad1[2]; // 0x3A
	s_tag_reference sounds[12]; // 0x3C
	float probability; // 0xFC
	c_tag_block<s_multiplayer_event_sound_response_definition> sound_permutations; // 0x100
	s_multiplayer_event_response_definition(s_multiplayer_event_response_definition &); /* compiler_generated() */
	s_multiplayer_event_response_definition(s_multiplayer_event_response_definition const &); /* compiler_generated() */
	s_multiplayer_event_response_definition(); /* compiler_generated() */
	s_multiplayer_event_response_definition &operator=(s_multiplayer_event_response_definition &); /* compiler_generated() */
	s_multiplayer_event_response_definition &operator=(s_multiplayer_event_response_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_multiplayer_event_response_definition) == 268, "Invalid s_multiplayer_event_response_definition size");

/* ---------- prototypes */

namespace Patches
{
	namespace Events
	{
		extern void ApplyAll();
		extern void OnEvent(std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> callback);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PATCHES_EVENTS_HPP__
