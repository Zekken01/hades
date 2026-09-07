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

_extern void _sub_10F13950(c_gui_list_widget *const, long);
void c_gui_list_widget::select_item(long index) // 0x10F13950
{
	mangled_x86(MANGLED_TODO, "?select_item@c_gui_list_widget@@QAEXJ@Z");
	// long index;
	// void (*const select_item)(c_gui_list_widget *, long, bool);
	// function call : void (*const)(c_gui_list_widget *, long, bool)
	todo("implement");
	_sub_10F13950(this, index);
}

_extern long _sub_10F138D0(c_gui_list_widget const *const);
long c_gui_list_widget::get_selected_data_item_index() const // 0x10F138D0
{
	mangled_x86(MANGLED_TODO, "?get_selected_data_item_index@c_gui_list_widget@@QBEJXZ");
	// c_gui_list_widget const *const this;
	// long (*const get_scrolled_index)(c_gui_list_widget const *, long);
	// function call : long (*const)(c_gui_list_widget const *, long)
	todo("implement");
	long __result = _sub_10F138D0((c_gui_list_widget const *)this);
	return __result;
}

_extern long _sub_10F13860(c_gui_list_widget const *const, bool);
long c_gui_list_widget::get_item_count(bool count_hidden) const // 0x10F13860
{
	mangled_x86(MANGLED_TODO, "?get_item_count@c_gui_list_widget@@QBEJ_N@Z");
	// bool count_hidden;
	// function call : long (*)(c_gui_list_widget const *, bool)
	todo("implement");
	long __result = _sub_10F13860((c_gui_list_widget const *)this, count_hidden);
	return __result;
}

/* ---------- private code */
