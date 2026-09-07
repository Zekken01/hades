#ifndef __BLAM_INTERFACE_GUI_GUI_PREGAME_SETUP_MANAGER_HPP__
#define __BLAM_INTERFACE_GUI_GUI_PREGAME_SETUP_MANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_gui_pregame_setup_manager;

/* ---------- constants */

/* ---------- definitions */

struct c_gui_pregame_setup_manager
{
	bool selected_recent_item[8]; // 0x0
	long mxbox_live_private_prviacy_setting; // 0x8
	char storage[151172]; // 0xC
	long ui_game_mode; // 0x24E90
	bool restore_requested; // 0x24E94
	static void (*const restore_from_last)(c_gui_pregame_setup_manager *, e_gui_game_mode);
	static c_gui_pregame_setup_manager *(*const get)();
	unsigned char __pad0[3]; // 0x24E95
};
static_assert(sizeof(c_gui_pregame_setup_manager) == 151192, "Invalid c_gui_pregame_setup_manager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_PREGAME_SETUP_MANAGER_HPP__
