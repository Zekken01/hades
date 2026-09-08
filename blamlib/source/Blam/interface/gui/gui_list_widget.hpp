#ifndef __BLAM_INTERFACE_GUI_GUI_LIST_WIDGET_HPP__
#define __BLAM_INTERFACE_GUI_GUI_LIST_WIDGET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

class c_gui_list_widget;
class c_gui_widget;
struct s_tag_block;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class c_gui_list_widget :
	public c_gui_widget
{
public:
	_inline long get_selected_index() const;
	long get_scroll_position() const;
	long get_selected_data_item_index() const;
	_inline unsigned long const get_item_datasource_name() const;
	void select_item(long index);
	long get_item_count(bool count_hidden) const;
private:
	unsigned char __pad0[60]; // 0xDC
	long skin_index; // 0x118
	unsigned char __pad1[4]; // 0x11C
	s_tag_block items_definitions; // 0x120
	long up_arrow_bitmap_index; // 0x12C
	long down_arrow_bitmap_index; // 0x130
	unsigned long data_source_name; // 0x134
	c_gui_widget *up_arrow_bitmap_widget; // 0x138
	c_gui_widget *down_arrow_bitmap_widget; // 0x13C
	long selected_index; // 0x140
	unsigned char __pad2[4]; // 0x144
	long scroll_position; // 0x148
public:
	c_gui_list_widget(c_gui_list_widget &); /* compiler_generated() */
	c_gui_list_widget(c_gui_list_widget const &); /* compiler_generated() */
	c_gui_list_widget(); /* compiler_generated() */
	virtual ~c_gui_list_widget(); /* compiler_generated() */
	c_gui_list_widget &operator=(c_gui_list_widget &); /* compiler_generated() */
	c_gui_list_widget &operator=(c_gui_list_widget const &); /* compiler_generated() */
	void __autoclassinit2(unsigned __int32); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_gui_list_widget) == 332, "Invalid c_gui_list_widget size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline long c_gui_list_widget::get_selected_index() const // 0x108D5F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_selected_index@c_gui_list_widget@@QBEJXZ");
	// c_gui_list_widget const *const this;

	return selected_index;
}

_inline unsigned long const c_gui_list_widget::get_item_datasource_name() const // 0x108D5E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_item_datasource_name@c_gui_list_widget@@QBE?BKXZ");
	// c_gui_list_widget const *const this;

	return data_source_name;
}

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_LIST_WIDGET_HPP__
