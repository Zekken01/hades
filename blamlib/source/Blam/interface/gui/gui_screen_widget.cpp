/* ---------- headers */

#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/interface/gui/gui_list_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_gui_data;
class c_gui_list_widget;
class c_gui_screen_widget;
class c_gui_widget;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_gui_widget *c_gui_screen_widget::get_focused_widget() const // 0x10F136D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_focused_widget@c_gui_screen_widget@@QBEPAVc_gui_widget@@XZ");

	return ((c_gui_widget *(__thiscall *const)(const c_gui_screen_widget *))0xab0f40)(this);
}

void c_gui_screen_widget::select_list_item(c_gui_list_widget *list_widget, long item_index, bool flag1, bool flag2) // 0x10F13740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?select_list_item@c_gui_screen_widget@@QAEXPAVc_gui_list_widget@@J_N1@Z");

	void (__thiscall *const select_list_item)(c_gui_screen_widget *, c_gui_list_widget *, long, bool, bool) = (void(__thiscall *const)(c_gui_screen_widget *, c_gui_list_widget *, long, bool, bool))0xab2640;

	select_list_item(this, list_widget, item_index, flag1, flag2);
}

c_gui_data *c_gui_screen_widget::get_datasource(unsigned long name) const // 0x10F13600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_datasource@c_gui_screen_widget@@QBEPAVc_gui_data@@K@Z");

	c_gui_data *(__thiscall *const get_datasource)(c_gui_screen_widget const *, unsigned long, long *) = reinterpret_cast<c_gui_data *(__thiscall *)(c_gui_screen_widget const *, unsigned long, long *)>(0xAB0DB0);
	long a1 = -1;
	return get_datasource(this, name, &a1);
}

void c_gui_screen_widget::transition_out(__int32 type) // 0x10F137D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?transition_out@c_gui_screen_widget@@QAEXH@Z");

	transition_out_internal(type, 0);
}

/* ---------- private code */
