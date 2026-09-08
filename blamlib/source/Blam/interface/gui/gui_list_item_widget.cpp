/* ---------- headers */

#include "Blam/interface/gui/gui_list_item_widget.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_gui_list_item_widget;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

long c_gui_list_item_widget::get_data_item_index() const // 0x10F139D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_data_item_index@c_gui_list_item_widget@@QBEJXZ");
	// c_gui_list_item_widget const *const this;
	// long (*const get_selected_item_data_index)(c_gui_list_item_widget const *);
	// function call : long (*const)(c_gui_list_item_widget const *)

	long (__thiscall *const get_selected_item_data_index)(c_gui_list_item_widget const *) = (long(__thiscall *const)(c_gui_list_item_widget const *))0xb184a0;

	return get_selected_item_data_index(this);
}

/* ---------- private code */
