#ifndef __BLAM_INTERFACE_GUI_GUI_DATA_HPP__
#define __BLAM_INTERFACE_GUI_GUI_DATA_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/gui/gui_screen_widget.hpp"

/* ---------- forward declarations */

class c_gui_data;
class c_gui_ordered_data;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class c_gui_ordered_data :
	public c_gui_data
{
public:
	public:
	struct s_disabled_element
	{
		unsigned long name; // 0x0
		long element_handle; // 0x4
	};
	static_assert(sizeof(s_disabled_element) == 8, "Invalid s_disabled_element size");
	public:
	c_gui_ordered_data(c_gui_ordered_data &); /* compiler_generated() */
	c_gui_ordered_data(c_gui_ordered_data const &); /* compiler_generated() */
	c_gui_ordered_data();
	virtual long get_current_item_count();
	virtual long get_first_element_handle();
	virtual long get_next_element_handle(long element_handle);
	virtual long get_previous_element_handle(long element_handle);
	virtual void clear_disabled_elements();
	virtual void set_disabled_element(long element_handle, unsigned long name);
	virtual void disable_all_elements(unsigned long name);
	virtual void enable_element(long element_handle, unsigned long name);
protected:
	virtual long get_current_item_count_internal() = 0;
private:
	static long const k_maximum_disabled_element_count;
	bool is_enabled(long element_index);
	s_disabled_element m_disabled_elements[32]; // 0x8
	long m_disabled_element_count; // 0x108
public:
	// mangled_x86(MANGLED_KNOWN_GOOD, "??1c_gui_ordered_data@@UAE@XZ"); defaulted on its declaration
	// virtual _inline ~c_gui_ordered_data() = default; // 0x10f1c7b0 // hades: implicit
	c_gui_ordered_data &operator=(c_gui_ordered_data &); /* compiler_generated() */
	c_gui_ordered_data &operator=(c_gui_ordered_data const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_gui_ordered_data) == 268, "Invalid c_gui_ordered_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_DATA_HPP__
