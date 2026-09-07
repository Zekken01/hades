#ifndef __BLAM_GAME_MULTIPLAYER_DEFINITIONS_HPP__
#define __BLAM_GAME_MULTIPLAYER_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/player_model_customization.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Patches/Events.hpp"

/* ---------- forward declarations */

struct real_rgb_color;
struct s_game_engine_status_response;
struct s_model_customization_selection;
struct s_multiplayer_consumable;
struct s_multiplayer_equipment;
struct s_multiplayer_event_response_definition;
struct s_multiplayer_globals_definition;
struct s_multiplayer_move_animations;
struct s_multiplayer_object_set;
struct s_multiplayer_object_substitution;
struct s_multiplayer_podium_animations;
struct s_multiplayer_runtime_globals_definition;
struct s_multiplayer_runtime_sound;
struct s_multiplayer_stance_animations;
struct s_multiplayer_team_color;
struct s_multiplayer_universal_globals_definition;
struct s_multiplayer_vehicle;
struct s_multiplayer_weapon;
struct s_tag_block;
struct s_tag_reference;
union tag_string;

/* ---------- constants */

/* ---------- definitions */

struct s_multiplayer_consumable
{
	unsigned long name; // 0x0
	s_tag_reference object; // 0x4
	short consumable_type; // 0x14
	unsigned char __pad0[2]; // 0x16
};
static_assert(sizeof(s_multiplayer_consumable) == 24, "Invalid s_multiplayer_consumable size");

struct s_multiplayer_weapon
{
	unsigned long name; // 0x0
	float random_chance; // 0x4
	s_tag_reference object; // 0x8
};
static_assert(sizeof(s_multiplayer_weapon) == 24, "Invalid s_multiplayer_weapon size");

#pragma pack(push, 4)
struct s_multiplayer_vehicle
{
	unsigned long name; // 0x0
	s_tag_reference object; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_multiplayer_vehicle) == 20, "Invalid s_multiplayer_vehicle size");

struct s_multiplayer_object_substitution
{
	unsigned long original_object_name; // 0x0
	unsigned long substituted_object_name; // 0x4
};
static_assert(sizeof(s_multiplayer_object_substitution) == 8, "Invalid s_multiplayer_object_substitution size");

struct s_multiplayer_object_set
{
	unsigned long name; // 0x0
	c_tag_block<s_multiplayer_object_substitution> substitutions; // 0x4
};
static_assert(sizeof(s_multiplayer_object_set) == 16, "Invalid s_multiplayer_object_set size");

#pragma pack(push, 4)
struct s_multiplayer_stance_animations
{
	tag_string name; // 0x0
	unsigned long base_animation; // 0x20
	unsigned long loop_animation; // 0x24
	unsigned long unarmed_transition; // 0x28
	unsigned long armed_transition; // 0x2C
	float biped_offset_distance; // 0x30
};
#pragma pack(pop)
static_assert(sizeof(s_multiplayer_stance_animations) == 52, "Invalid s_multiplayer_stance_animations size");

struct s_multiplayer_move_animations
{
	tag_string name; // 0x0
	unsigned long in_animation; // 0x20
	unsigned long loop_animation; // 0x24
	unsigned long out_animation; // 0x28
	float biped_offset_distance; // 0x2C
	s_tag_reference primary_weapon; // 0x30
	s_tag_reference secondary_weapon; // 0x40
};
static_assert(sizeof(s_multiplayer_move_animations) == 80, "Invalid s_multiplayer_move_animations size");

struct s_multiplayer_podium_animations
{
	s_tag_reference animation_graph; // 0x0
	unsigned long default_unarmed; // 0x10
	unsigned long default_armed; // 0x14
	c_tag_block<s_multiplayer_stance_animations> stance_animations; // 0x18
	c_tag_block<s_multiplayer_move_animations> move_animations; // 0x24
};
static_assert(sizeof(s_multiplayer_podium_animations) == 48, "Invalid s_multiplayer_podium_animations size");

#pragma pack(push, 4)
struct s_multiplayer_team_color
{
	real_rgb_color color; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_multiplayer_team_color) == 12, "Invalid s_multiplayer_team_color size");

struct s_multiplayer_universal_globals_definition
{
	s_tag_reference random_player_name_strings; // 0x0
	s_tag_reference team_names_strings; // 0x10
	c_tag_block<s_multiplayer_team_color> team_colors; // 0x20
	c_tag_block<s_model_customization_selection> player_model; // 0x2C
	c_tag_block<s_multiplayer_consumable> consumables; // 0x38
	s_tag_block energy_regeneration; // 0x44
	s_tag_reference multiplayer_strings; // 0x50
	s_tag_reference sandbox_strings; // 0x60
	s_tag_reference sandbox_text_value_pairs; // 0x70
	c_tag_block<s_multiplayer_weapon> weapons; // 0x80
	c_tag_block<s_multiplayer_vehicle> vehicles; // 0x8C
	c_tag_block<s_multiplayer_equipment> equipment; // 0x98
	c_tag_block<s_multiplayer_object_set> weapon_sets; // 0xA4
	c_tag_block<s_multiplayer_object_set> vehicle_sets; // 0xB0
	c_tag_block<s_multiplayer_podium_animations> podium_animations; // 0xBC
	s_tag_reference game_engine_settings; // 0xC8
};
static_assert(sizeof(s_multiplayer_universal_globals_definition) == 216, "Invalid s_multiplayer_universal_globals_definition size");

struct s_multiplayer_runtime_sound
{
	s_tag_reference sound; // 0x0
};
static_assert(sizeof(s_multiplayer_runtime_sound) == 16, "Invalid s_multiplayer_runtime_sound size");

struct s_multiplayer_runtime_globals_definition
{
	s_tag_reference sandbox_editor_unit; // 0x0
	s_tag_reference sandbox_editor_object; // 0x10
	s_tag_reference flag; // 0x20
	s_tag_reference ball; // 0x30
	s_tag_reference bomb; // 0x40
	s_tag_reference vip_zone; // 0x50
	s_tag_reference in_game_strings; // 0x60
	s_tag_reference unknown1; // 0x70
	s_tag_reference unknown2; // 0x80
	s_tag_reference unknown3; // 0x90
	s_tag_reference unknown4; // 0xA0
	s_tag_reference unknown5; // 0xB0
	c_tag_block<s_multiplayer_runtime_sound> sounds; // 0xC0
	c_tag_block<s_multiplayer_runtime_sound> looping_sounds; // 0xCC
	c_tag_block<s_multiplayer_event_response_definition> unknown_event_responses; // 0xD8
	c_tag_block<s_multiplayer_event_response_definition> general_event_responses; // 0xE4
	c_tag_block<s_multiplayer_event_response_definition> flavor_event_responses; // 0xF0
	c_tag_block<s_multiplayer_event_response_definition> slayer_event_responses; // 0xFC
	c_tag_block<s_multiplayer_event_response_definition> ctf_event_responses; // 0x108
	c_tag_block<s_multiplayer_event_response_definition> oddball_event_responses; // 0x114
	c_tag_block<s_multiplayer_event_response_definition> koth_event_responses; // 0x120
	c_tag_block<s_multiplayer_event_response_definition> vip_event_responses; // 0x12C
	c_tag_block<s_multiplayer_event_response_definition> juggernaut_event_responses; // 0x138
	c_tag_block<s_multiplayer_event_response_definition> territories_event_responses; // 0x144
	c_tag_block<s_multiplayer_event_response_definition> assault_event_responses; // 0x150
	c_tag_block<s_multiplayer_event_response_definition> infection_event_responses; // 0x15C
	long default_frag_grenade_count; // 0x168
	long default_plasma_grenade_count; // 0x16C
	s_tag_block multiplayer_constants; // 0x170
	c_tag_block<s_game_engine_status_response> state_responses; // 0x17C
	s_tag_reference scoreboard_emblem_bitmap; // 0x188
	s_tag_reference scoreboard_dead_emblem_bitmap; // 0x198
	s_tag_reference default_shape_shader; // 0x1A8
	s_tag_reference unknown6; // 0x1B8
	s_tag_reference ctf_intro_ui; // 0x1C8
	s_tag_reference slayer_intro_ui; // 0x1D8
	s_tag_reference oddball_intro_ui; // 0x1E8
	s_tag_reference king_of_the_hill_intro_ui; // 0x1F8
	s_tag_reference sandbox_intro_ui; // 0x208
	s_tag_reference vip_intro_ui; // 0x218
	s_tag_reference juggernaut_intro_ui; // 0x228
	s_tag_reference territories_intro_ui; // 0x238
	s_tag_reference assault_intro_ui; // 0x248
	s_tag_reference infection_intro_ui; // 0x258
	s_tag_reference menu_music_1; // 0x268
	s_tag_reference menu_music_2; // 0x278
	s_tag_reference menu_music_3; // 0x288
	s_tag_reference unknown7; // 0x298
};
static_assert(sizeof(s_multiplayer_runtime_globals_definition) == 680, "Invalid s_multiplayer_runtime_globals_definition size");

struct s_multiplayer_globals_definition
{
	c_tag_block<s_multiplayer_universal_globals_definition> universal; // 0x0
	c_tag_block<s_multiplayer_runtime_globals_definition> runtime; // 0xC
};
static_assert(sizeof(s_multiplayer_globals_definition) == 24, "Invalid s_multiplayer_globals_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_MULTIPLAYER_DEFINITIONS_HPP__
