#ifndef __BLAM_INTERFACE_GUI_GUI_LIST_ITEM_WIDGET_HPP__
#define __BLAM_INTERFACE_GUI_GUI_LIST_ITEM_WIDGET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

class c_gui_list_item_widget;
class c_gui_widget;
struct real_point2d;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class c_gui_list_item_widget :
	public c_gui_widget
{
public:
	_inline long get_item_index() const;
	long get_data_item_index() const;
	_inline c_gui_list_item_widget *find_next_item();
	_inline real_point2d get_anchor_position();
private:
	unsigned char __pad0[56]; // 0xDC
	long target; // 0x114
	long item_index; // 0x118
public:
	c_gui_list_item_widget(c_gui_list_item_widget &); /* compiler_generated() */
	c_gui_list_item_widget(c_gui_list_item_widget const &); /* compiler_generated() */
	c_gui_list_item_widget(); /* compiler_generated() */
	virtual ~c_gui_list_item_widget(); /* compiler_generated() */
	c_gui_list_item_widget &operator=(c_gui_list_item_widget &); /* compiler_generated() */
	c_gui_list_item_widget &operator=(c_gui_list_item_widget const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_gui_list_item_widget) == 284, "Invalid c_gui_list_item_widget size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern long _sub_108D5E90(c_gui_list_item_widget const *const);
_inline long c_gui_list_item_widget::get_item_index() const // 0x108D5E90
{
	mangled_x86(MANGLED_TODO, "?get_item_index@c_gui_list_item_widget@@QBEJXZ");
	// c_gui_list_item_widget const *const this;
	todo("implement");
	long __result = _sub_108D5E90((c_gui_list_item_widget const *)this);
	return __result;
}

extern c_gui_list_item_widget *_sub_108D5D70(c_gui_list_item_widget *const);
_inline c_gui_list_item_widget *c_gui_list_item_widget::find_next_item() // 0x108D5D70
{
	mangled_x86(MANGLED_TODO, "?find_next_item@c_gui_list_item_widget@@QAEPAV1@XZ");
	// c_gui_list_item_widget *const this;
	todo("implement");
	c_gui_list_item_widget * __result = _sub_108D5D70(this);
	return __result;
}

extern real_point2d _sub_108D5DC0(c_gui_list_item_widget *const);
_inline real_point2d c_gui_list_item_widget::get_anchor_position() // 0x108D5DC0
{
	mangled_x86(MANGLED_TODO, "?get_anchor_position@c_gui_list_item_widget@@QAE?AUreal_point2d@@XZ");
	// c_gui_list_item_widget *const this;
	todo("implement");
	real_point2d __result = _sub_108D5DC0(this);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_LIST_ITEM_WIDGET_HPP__
