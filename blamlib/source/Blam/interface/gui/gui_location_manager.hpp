#ifndef __BLAM_INTERFACE_GUI_GUI_LOCATION_MANAGER_HPP__
#define __BLAM_INTERFACE_GUI_GUI_LOCATION_MANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/gui/gui_screen_widget.hpp"

/* ---------- forward declarations */

class c_gui_screen_widget;
struct c_gui_location_manager;

/* ---------- constants */

/* ---------- definitions */

struct c_gui_location_manager
{
	bool initialized; // 0x0
	unsigned char __pad0[3]; // 0x1
	long state; // 0x4
	char launching_main_menu; // 0x8
	unsigned char __pad1[3]; // 0x9
	long last_update_milliseconds; // 0xC
	long last_change_location_milliseconds; // 0x10
	static c_gui_screen_widget *(*get_location_gui_screen)();
};
static_assert(sizeof(c_gui_location_manager) == 20, "Invalid c_gui_location_manager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_LOCATION_MANAGER_HPP__
