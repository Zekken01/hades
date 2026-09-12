/* ---------- headers */

#include "Blam/interface/gui/gui_widget.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/interface/gui/gui_bitmap_widget.hpp"
#include "Blam/interface/gui/gui_list_item_widget.hpp"
#include "Blam/interface/gui/gui_list_widget.hpp"
#include "Blam/interface/gui/gui_widget_types.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_gui_bitmap_widget;
class c_gui_list_item_widget;
class c_gui_list_widget;
class c_gui_widget;
struct real_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void c_gui_widget::set_visible(bool visible) // 0x10F13590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_visible@c_gui_widget@@QAEX_N@Z");
	// bool visible;
	// function call : void (*)(c_gui_widget *, bool)

	((void(__thiscall *const)(c_gui_widget *, bool))0xaba7e0)(this, visible);
}

c_gui_widget *c_gui_widget::find_first_child(e_gui_widget type) const // 0x10F131E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_first_child@c_gui_widget@@QBEPAV1@W4e_gui_widget@@@Z");
	// e_gui_widget type;
	// function call : c_gui_widget *(*)(c_gui_widget const *, e_gui_widget)

	return ((c_gui_widget *(__thiscall *)(const c_gui_widget *, e_gui_widget))0xab8f80)(this, type);
}

extern c_gui_widget *_sub_10F13250(c_gui_widget const *const, e_gui_widget);
c_gui_widget *c_gui_widget::find_next_sibling(e_gui_widget type) const // 0x10F13250
{
	mangled_x86(MANGLED_TODO, "?find_next_sibling@c_gui_widget@@QBEPAV1@W4e_gui_widget@@@Z");
	// e_gui_widget type;
	// function call : c_gui_widget *(*)(c_gui_widget const *, e_gui_widget)
	todo("implement");
	c_gui_widget * __result = _sub_10F13250((c_gui_widget const *)this, type);
	return __result;
}

void c_gui_widget::get_render_bounds(real_rectangle2d *bounds) const // 0x10F13490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_render_bounds@c_gui_widget@@QBEXPAUreal_rectangle2d@@@Z");
	// real_rectangle2d *bounds;
	// function call : real_rectangle2d *(real_rectangle2d *) const

	get_current_bounds(bounds);
}

extern c_gui_widget *_sub_10F13130(c_gui_widget *const, bool (*)(c_gui_widget const &));
c_gui_widget *c_gui_widget::find_ancestor(bool (*predicate)(c_gui_widget const &)) // 0x10F13130
{
	mangled_x86(MANGLED_TODO, "?find_ancestor@c_gui_widget@@QAEPAV1@P6A_NABV1@@Z@Z");
	// bool (*predicate)(c_gui_widget const &);
	{
		// c_gui_widget *widget;
	}
	// function call : bool (*)(c_gui_widget const &)
	todo("implement");
	c_gui_widget * __result = _sub_10F13130(this, predicate);
	return __result;
}

extern c_gui_list_widget *_sub_10F13330(c_gui_widget *const, unsigned long);
c_gui_list_widget *c_gui_widget::get_child_list_widget(unsigned long name) // 0x10F13330
{
	mangled_x86(MANGLED_TODO, "?get_child_list_widget@c_gui_widget@@QAEPAVc_gui_list_widget@@K@Z");
	// unsigned long name;
	// function call : c_gui_list_widget *(*)(c_gui_widget *, unsigned long)
	todo("implement");
	c_gui_list_widget * __result = _sub_10F13330(this, name);
	return __result;
}

c_gui_widget *c_gui_widget::get_child_widget(e_gui_widget type, unsigned long name) const // 0x10F13410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_child_widget@c_gui_widget@@QBEPAV1@W4e_gui_widget@@K@Z");
	// unsigned long name;
	// function call : c_gui_widget *(*)(c_gui_widget const *, e_gui_widget, unsigned long)

	return ((c_gui_widget *(__thiscall *)(const c_gui_widget *, e_gui_widget, unsigned long))0xab8b00)(this, type, name);
}

c_gui_bitmap_widget *c_gui_widget::get_child_bitmap_widget(unsigned long name) // 0x10F132C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_child_bitmap_widget@c_gui_widget@@QAEPAVc_gui_bitmap_widget@@K@Z");
	// unsigned long name;

	return (c_gui_bitmap_widget *)get_child_widget(_gui_widget_bitmap, name);
}

c_gui_list_item_widget *c_gui_widget::get_child_text_widget(unsigned long name) // 0x10F133A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_child_text_widget@c_gui_widget@@QAEPAVc_gui_list_item_widget@@K@Z");
	// unsigned long name;

	return (c_gui_list_item_widget *)get_child_widget(_gui_widget_text, name);
}

void c_gui_widget::set_text_widget_text(unsigned long name, wchar_t const *text) // 0x10F13510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_text_widget_text@c_gui_widget@@QAEXKPB_W@Z");
	// wchar_t const *text;
	// __int32 (*const c_gui_screen_widget__set_text_widget_text)(void *, unsigned long, wchar_t const *);
	// function call : __int32 (*const)(void *, unsigned long, wchar_t const *)

	__int32 (__thiscall *const c_gui_screen_widget__set_text_widget_text)(void *, unsigned long, wchar_t const *) = (__int32(__thiscall *const)(void *, unsigned long, wchar_t const *))0xab23e0;

	c_gui_screen_widget__set_text_widget_text(this, name, text);
}

/* ---------- private code */
