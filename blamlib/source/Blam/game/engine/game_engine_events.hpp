#ifndef __BLAM_GAME_ENGINE_GAME_ENGINE_EVENTS_HPP__
#define __BLAM_GAME_ENGINE_GAME_ENGINE_EVENTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_game_engine_event_data;
struct s_game_engine_queued_event;
struct s_multiplayer_event_sound_response_definition;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_multiplayer_event_sound_response_definition
{
	c_flags<enum e_multiplayer_event_sound_response_flags,unsigned short> sound_flags; // 0x0
	unsigned char agqd[2]; // 0x2
	s_tag_reference english_sound; // 0x4
	s_tag_reference japanese_sound; // 0x14
	s_tag_reference german_sound; // 0x24
	s_tag_reference french_sound; // 0x34
	s_tag_reference spanish_sound; // 0x44
	s_tag_reference mexican_sound; // 0x54
	s_tag_reference italian_sound; // 0x64
	s_tag_reference korean_sound; // 0x74
	s_tag_reference chinese_sound; // 0x84
	s_tag_reference chinese_sound_2; // 0x94
	s_tag_reference portuguese_sound; // 0xA4
	s_tag_reference polish_sound; // 0xB4
	float probability; // 0xC4
	s_multiplayer_event_sound_response_definition(s_multiplayer_event_sound_response_definition &); /* compiler_generated() */
	s_multiplayer_event_sound_response_definition(s_multiplayer_event_sound_response_definition const &); /* compiler_generated() */
	s_multiplayer_event_sound_response_definition(); /* compiler_generated() */
	s_multiplayer_event_sound_response_definition &operator=(s_multiplayer_event_sound_response_definition &); /* compiler_generated() */
	s_multiplayer_event_sound_response_definition &operator=(s_multiplayer_event_sound_response_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_multiplayer_event_sound_response_definition) == 200, "Invalid s_multiplayer_event_sound_response_definition size");

struct s_game_engine_event_data
{
	c_enum<enum e_game_engine_event_type,char> type; // 0x0
	unsigned long name; // 0x4
	long index; // 0x8
	long target_player_index; // 0xC
	long cause_player_index; // 0x10
	long cause_team_index; // 0x14
	long effect_player_index; // 0x18
	long effect_team_index; // 0x1C
	long points; // 0x20
	short territory_index; // 0x24
	s_game_engine_event_data(s_game_engine_event_data &); /* compiler_generated() */
	s_game_engine_event_data(s_game_engine_event_data const &); /* compiler_generated() */
	_inline s_game_engine_event_data() = default; /* compiler_generated() */
	s_game_engine_event_data &operator=(s_game_engine_event_data &); /* compiler_generated() */
	_inline s_game_engine_event_data &operator=(s_game_engine_event_data const &__that); /* compiler_generated() */
};
static_assert(sizeof(s_game_engine_event_data) == 40, "Invalid s_game_engine_event_data size");
static_assert(offsetof(s_game_engine_event_data, name) == 0x4, "s_game_engine_event_data::name moved when its reconstructed padding was removed");

struct s_game_engine_queued_event
{
	long equeued_game_time; // 0x0
	c_flags<enum e_game_engine_queued_event_flags,unsigned char> flags; // 0x4
	s_game_engine_event_data data; // 0x8
	s_game_engine_queued_event(s_game_engine_queued_event &); /* compiler_generated() */
	s_game_engine_queued_event(s_game_engine_queued_event const &); /* compiler_generated() */
	s_game_engine_queued_event(); /* compiler_generated() */
	s_game_engine_queued_event &operator=(s_game_engine_queued_event &); /* compiler_generated() */
	s_game_engine_queued_event &operator=(s_game_engine_queued_event const &); /* compiler_generated() */
};
static_assert(sizeof(s_game_engine_queued_event) == 48, "Invalid s_game_engine_queued_event size");
static_assert(offsetof(s_game_engine_queued_event, data) == 0x8, "s_game_engine_queued_event::data moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_ENGINE_GAME_ENGINE_EVENTS_HPP__
