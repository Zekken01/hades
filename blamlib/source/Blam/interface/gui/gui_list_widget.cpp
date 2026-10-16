/* ---------- headers */

#include "Blam/interface/gui/gui_list_widget.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_gui_list_widget;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void c_gui_list_widget::select_item(long index) // 0x10F13950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?select_item@c_gui_list_widget@@QAEXJ@Z");

	void (__thiscall *const select_item_internal)(c_gui_list_widget *, long, bool) = (void(__thiscall *const)(c_gui_list_widget *, long, bool))0xb162e0;

	select_item_internal(this, index, true);
}

long c_gui_list_widget::get_selected_data_item_index() const // 0x10F138D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_selected_data_item_index@c_gui_list_widget@@QBEJXZ");

	long (__thiscall *const F)(const c_gui_list_widget *, long) = (long(__thiscall *const)(const c_gui_list_widget *, long))0xb15060;

	return F(this, get_selected_index());
}

long c_gui_list_widget::get_item_count(bool count_hidden) const // 0x10F13860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_item_count@c_gui_list_widget@@QBEJ_N@Z");

	return ((long(__thiscall *)(const c_gui_list_widget *, bool))0xb15170)(this, count_hidden);
}

/* ---------- private code */
