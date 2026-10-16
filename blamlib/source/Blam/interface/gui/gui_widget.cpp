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

	((void(__thiscall *const)(c_gui_widget *, bool))0xaba7e0)(this, visible);
}

c_gui_widget *c_gui_widget::find_first_child(e_gui_widget type) const // 0x10F131E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_first_child@c_gui_widget@@QBEPAV1@W4e_gui_widget@@@Z");

	return ((c_gui_widget *(__thiscall *)(const c_gui_widget *, e_gui_widget))0xab8f80)(this, type);
}

c_gui_widget *c_gui_widget::find_next_sibling(e_gui_widget type) const // 0x10F13250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_next_sibling@c_gui_widget@@QBEPAV1@W4e_gui_widget@@@Z");

	return ((c_gui_widget *(__thiscall *)(c_gui_widget const *, e_gui_widget))0xab9290)(this, type);
}

void c_gui_widget::get_render_bounds(real_rectangle2d *bounds) const // 0x10F13490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_render_bounds@c_gui_widget@@QBEXPAUreal_rectangle2d@@@Z");

	get_current_bounds(bounds);
}

c_gui_widget *c_gui_widget::find_ancestor(bool (*predicate)(c_gui_widget const &)) // 0x10F13130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_ancestor@c_gui_widget@@QAEPAV1@P6A_NABV1@@Z@Z");

	for (c_gui_widget *ancestor = get_parent(); ancestor; ancestor = ancestor->get_parent())
	{
		if (predicate(*ancestor))
		{
			return ancestor;
		}
	}
	return nullptr;
}

c_gui_list_widget *c_gui_widget::get_child_list_widget(unsigned long name) // 0x10F13330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_child_list_widget@c_gui_widget@@QAEPAVc_gui_list_widget@@K@Z");

	return ((c_gui_list_widget *(__thiscall *)(c_gui_widget *, unsigned long))0xab8aa0)(this, name);
}

c_gui_widget *c_gui_widget::get_child_widget(e_gui_widget type, unsigned long name) const // 0x10F13410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_child_widget@c_gui_widget@@QBEPAV1@W4e_gui_widget@@K@Z");

	return ((c_gui_widget *(__thiscall *)(const c_gui_widget *, e_gui_widget, unsigned long))0xab8b00)(this, type, name);
}

c_gui_bitmap_widget *c_gui_widget::get_child_bitmap_widget(unsigned long name) // 0x10F132C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_child_bitmap_widget@c_gui_widget@@QAEPAVc_gui_bitmap_widget@@K@Z");

	return (c_gui_bitmap_widget *)get_child_widget(_gui_widget_bitmap, name);
}

c_gui_list_item_widget *c_gui_widget::get_child_text_widget(unsigned long name) // 0x10F133A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_child_text_widget@c_gui_widget@@QAEPAVc_gui_list_item_widget@@K@Z");

	return (c_gui_list_item_widget *)get_child_widget(_gui_widget_text, name);
}

void c_gui_widget::set_text_widget_text(unsigned long name, wchar_t const *text) // 0x10F13510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_text_widget_text@c_gui_widget@@QAEXKPB_W@Z");

	__int32 (__thiscall *const c_gui_screen_widget__set_text_widget_text)(void *, unsigned long, wchar_t const *) = (__int32(__thiscall *const)(void *, unsigned long, wchar_t const *))0xab23e0;

	c_gui_screen_widget__set_text_widget_text(this, name, text);
}

/* ---------- private code */
