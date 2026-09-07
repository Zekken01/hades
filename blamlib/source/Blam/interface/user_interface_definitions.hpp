#ifndef __BLAM_INTERFACE_USER_INTERFACE_DEFINITIONS_HPP__
#define __BLAM_INTERFACE_USER_INTERFACE_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_argb_color;
struct real_vector2d;
struct s_gui_alert_description;
struct s_tag_block;
struct s_tag_data;
struct s_tag_reference;
struct s_user_interface_shared_globals;

/* ---------- constants */

/* ---------- definitions */

struct s_gui_alert_description
{
	unsigned long error_name; // 0x0
	c_flags<enum e_gui_alert_flags,unsigned char> flags; // 0x4
	c_enum<enum e_gui_error_category,char> error_category; // 0x5
	c_enum<enum e_gui_error_icon,char> error_icon; // 0x6
	unsigned char pad0[1]; // 0x7
	unsigned long title; // 0x8
	unsigned long message; // 0xC
	s_gui_alert_description(s_gui_alert_description &); /* compiler_generated() */
	s_gui_alert_description(s_gui_alert_description const &); /* compiler_generated() */
	s_gui_alert_description(); /* compiler_generated() */
	s_gui_alert_description &operator=(s_gui_alert_description &); /* compiler_generated() */
	s_gui_alert_description &operator=(s_gui_alert_description const &); /* compiler_generated() */
};
static_assert(sizeof(s_gui_alert_description) == 16, "Invalid s_gui_alert_description size");

struct s_user_interface_shared_globals
{
	short inc_text_update_period; // 0x0
	short inc_text_block_character; // 0x2
	float near_clip_plane_distance; // 0x4
	float projection_plane_distance; // 0x8
	float far_clip_plane_distance; // 0xC
	s_tag_reference global_strings; // 0x10
	s_tag_reference damage_reporting_strings; // 0x20
	s_tag_reference hf2p_ui_strings; // 0x30
	s_tag_reference main_menu_music; // 0x40
	float music_fade_time; // 0x50
	real_argb_color text_color; // 0x54
	real_argb_color text_shadow_color; // 0x64
	s_tag_block color_presets; // 0x74
	s_tag_block tint_colors; // 0x80
	s_tag_reference default_sounds; // 0x8C
	c_tag_block<s_gui_alert_description> alerts; // 0x9C
	s_tag_block dialogs; // 0xA8
	s_tag_block global_data_sources; // 0xB4
	real_vector2d widescreen_bitmap_scale; // 0xC0
	real_vector2d standard_bitmap_scale; // 0xC8
	float menu_blur_x; // 0xD0
	float menu_blur_y; // 0xD4
	s_tag_block widget_bipeds; // 0xD8
	unsigned long mc_biped_name; // 0xE4
	unsigned long mc_ai_squad_name; // 0xE8
	unsigned long mc_ai_start_pos; // 0xEC
	unsigned long elite_biped_name; // 0xF0
	unsigned long elite_ai_squad_name; // 0xF4
	unsigned long elite_ai_squad_start_pos; // 0xF8
	unsigned long odst1_biped_name; // 0xFC
	unsigned long odst1_ai_squad_name; // 0x100
	unsigned long odst1_ai_squad_start_pos; // 0x104
	unsigned long mickey_biped_name; // 0x108
	unsigned long mickey_ai_squad_name; // 0x10C
	unsigned long mickey_ai_squad_start_pos; // 0x110
	unsigned long romeo_biped_name; // 0x114
	unsigned long romeo_ai_squad_name; // 0x118
	unsigned long romeo_ai_squad_start_pos; // 0x11C
	unsigned long dutch_biped_name; // 0x120
	unsigned long dutch_ai_squad_name; // 0x124
	unsigned long dutch_ai_squad_start_pos; // 0x128
	unsigned long johnson_biped_name; // 0x12C
	unsigned long johnson_ai_squad_name; // 0x130
	unsigned long johnson_ai_squad_start_pos; // 0x134
	unsigned long odst2_biped_name; // 0x138
	unsigned long odst2_ai_squad_name; // 0x13C
	unsigned long odst2_ai_squad_start_pos; // 0x140
	unsigned long odst3_biped_name; // 0x144
	unsigned long odst3_ai_squad_name; // 0x148
	unsigned long odst3_ai_squad_start_pos; // 0x14C
	unsigned long odst4_biped_name; // 0x150
	unsigned long odst4_ai_squad_name; // 0x154
	unsigned long odst4_ai_squad_start_pos; // 0x158
	unsigned long spartan_portrait_biped_name; // 0x15C
	unsigned long elite_portrait_biped_name; // 0x160
	long navigation_tab_delay; // 0x164
	long navigation_tab_fast_wait; // 0x168
	long navigation_tab_fast_delay; // 0x16C
	s_tag_data spinner_tab_speed_function; // 0x170
	long max_input_time; // 0x184
	s_tag_block motion_tracker_distance_function; // 0x188
	long attract_mode_delay; // 0x194
	s_user_interface_shared_globals(s_user_interface_shared_globals &); /* compiler_generated() */
	s_user_interface_shared_globals(s_user_interface_shared_globals const &); /* compiler_generated() */
	s_user_interface_shared_globals(); /* compiler_generated() */
	s_user_interface_shared_globals &operator=(s_user_interface_shared_globals &); /* compiler_generated() */
	s_user_interface_shared_globals &operator=(s_user_interface_shared_globals const &); /* compiler_generated() */
	unsigned char __pad0[16]; // 0x198
};
static_assert(sizeof(s_user_interface_shared_globals) == 424, "Invalid s_user_interface_shared_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_USER_INTERFACE_DEFINITIONS_HPP__
