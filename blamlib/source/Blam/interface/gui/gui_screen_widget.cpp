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

extern c_gui_widget *_sub_10F136D0(c_gui_screen_widget const *const);
c_gui_widget *c_gui_screen_widget::get_focused_widget() const // 0x10F136D0
{
	mangled_x86(MANGLED_TODO, "?get_focused_widget@c_gui_screen_widget@@QBEPAVc_gui_widget@@XZ");
	// c_gui_screen_widget const *const this;
	// function call : c_gui_widget *(*)(c_gui_screen_widget const *)
	todo("implement");
	c_gui_widget * __result = _sub_10F136D0((c_gui_screen_widget const *)this);
	return __result;
}

_extern void _sub_10F13740(c_gui_screen_widget *const, c_gui_list_widget *, long, bool, bool);
void c_gui_screen_widget::select_list_item(c_gui_list_widget *list_widget, long item_index, bool flag1, bool flag2) // 0x10F13740
{
	mangled_x86(MANGLED_TODO, "?select_list_item@c_gui_screen_widget@@QAEXPAVc_gui_list_widget@@J_N1@Z");
	// bool flag2;
	// void (*const select_list_item)(c_gui_screen_widget *, c_gui_list_widget *, long, bool, bool);
	// function call : void (*const)(c_gui_screen_widget *, c_gui_list_widget *, long, bool, bool)
	todo("implement");
	_sub_10F13740(this, list_widget, item_index, flag1, flag2);
}

extern c_gui_data *_sub_10F13600(c_gui_screen_widget const *const, unsigned long);
c_gui_data *c_gui_screen_widget::get_datasource(unsigned long name) const // 0x10F13600
{
	mangled_x86(MANGLED_TODO, "?get_datasource@c_gui_screen_widget@@QBEPAVc_gui_data@@K@Z");
	// static ...; // 0x10F13698
	// static ...; // 0x10F13690
	// c_gui_screen_widget const *const this;
	// unsigned long name;
	// long a1;
	// c_gui_data *(*const get_datasource)(c_gui_screen_widget const *, unsigned long, long *);
	// function call : c_gui_data *(*const)(c_gui_screen_widget const *, unsigned long, long *)
	todo("implement");
	c_gui_data * __result = _sub_10F13600((c_gui_screen_widget const *)this, name);
	return __result;
}

_extern void _sub_10F137D0(c_gui_screen_widget *const, __int32);
void c_gui_screen_widget::transition_out(__int32 type) // 0x10F137D0
{
	mangled_x86(MANGLED_TODO, "?transition_out@c_gui_screen_widget@@QAEXH@Z");
	// __int32 type;
	// function call : void (long, long)
	todo("implement");
	_sub_10F137D0(this, type);
}

/* ---------- private code */
