#ifndef __BLAM_INTERFACE_USER_INTERFACE_HPP__
#define __BLAM_INTERFACE_USER_INTERFACE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_user_interface_main_menu_music;

/* ---------- constants */

enum e_user_interface_main_menu_state
{
	_user_interface_main_music_none = 0,
	_user_interface_main_music_playing,
};

/* ---------- definitions */

struct c_user_interface_main_menu_music
{
	long m_previous_state; // 0x0
	long m_current_state; // 0x4
	long m_desired_state; // 0x8
	long m_fade_start_time; // 0xC
	long m_looping_sound_index; // 0x10
	long m_fade_out_start_time; // 0x14
};
static_assert(sizeof(c_user_interface_main_menu_music) == 24, "Invalid c_user_interface_main_menu_music size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_USER_INTERFACE_HPP__
