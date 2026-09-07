#ifndef __BLAM_MODS_PLAYER_ACTION_SET_HPP__
#define __BLAM_MODS_PLAYER_ACTION_SET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Player/PlayerEmotes.hpp"

/* ---------- forward declarations */

struct s_mod_player_action;
struct s_mod_player_actions_set_definition;
struct s_player_action_widget_data;
struct s_unit_camera_definition;
union tag_string;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_mod_player_action
{
	public:
	enum e_mod_action_flags
	{
		_hide_weapon = 0,
		_force_third_person_camera,
		_inhibit_movement,
		_inhibit_camera_movement,
		_inhibit_cancel,
		_dont_play_exit_animation_on_cancel,
		_hold_on_last_frame,
	};
	public:
	tag_string title; // 0x0
	tag_string icon_name; // 0x20
	unsigned long animation_enter; // 0x40
	unsigned long animation_idle; // 0x44
	unsigned long animation_exit; // 0x48
	__int32 flags; // 0x4C
	c_tag_block<s_unit_camera_definition> override_camera; // 0x50
	unsigned char unused[256]; // 0x5C
};
#pragma pack(pop)
static_assert(sizeof(s_mod_player_action) == 348, "Invalid s_mod_player_action size");

#pragma pack(push, 4)
struct s_player_action_widget_data
{
	public:
	enum e_action_widget_type
	{
		_wheel = 0,
		_grid,
	};
	public:
	tag_string title; // 0x0
	short type; // 0x20
	unsigned short flags; // 0x22
	unsigned long background_color; // 0x24
	unsigned long border_color; // 0x28
	unsigned long highlight_color; // 0x2C
	unsigned long text_color; // 0x30
	unsigned char unused[240]; // 0x34
};
#pragma pack(pop)
static_assert(sizeof(s_player_action_widget_data) == 292, "Invalid s_player_action_widget_data size");

#pragma pack(push, 4)
struct s_mod_player_actions_set_definition
{
	__int32 version; // 0x0
	c_tag_block<s_player_action_widget_data> widget; // 0x4
	c_tag_block<s_mod_player_action> actions; // 0x10
	unsigned char unused[256]; // 0x1C
	static s_mod_player_actions_set_definition *get(long definition_index);
};
#pragma pack(pop)
static_assert(sizeof(s_mod_player_actions_set_definition) == 284, "Invalid s_mod_player_actions_set_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MODS_PLAYER_ACTION_SET_HPP__
