#ifndef __BLAM_INTERFACE_GUI_GUI_SCREEN_MANAGER_HPP__
#define __BLAM_INTERFACE_GUI_GUI_SCREEN_MANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/gui/gui_screen_widget.hpp"

/* ---------- forward declarations */

class c_gui_screen_manager;
class c_gui_screen_widget;

/* ---------- constants */

/* ---------- definitions */

class c_gui_screen_manager
{
public:
	static c_gui_screen_manager *get();
	c_gui_screen_manager();
	bool any_active_screens(long controller_index) const;
	c_gui_screen_widget *find_screen(long controller_index, unsigned long name) const;
	c_gui_screen_widget *get_current_screen(long controller_index, long *out_output_user_index) const;
	c_gui_screen_widget *get_screen_below(c_gui_screen_widget *screen_widget) const;
	c_gui_screen_widget *get_topmost_screen() const;
	void post_message(void *message);
	bool input_should_be_suppressed(long controller_index);
};
static_assert(sizeof(c_gui_screen_manager) == 1, "Invalid c_gui_screen_manager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_SCREEN_MANAGER_HPP__
