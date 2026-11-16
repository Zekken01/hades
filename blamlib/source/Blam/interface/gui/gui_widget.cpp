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

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const c_gui_widget_set_visible = reinterpret_cast<void(__thiscall *)(c_gui_widget *, bool)>(0xABA7E0);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void c_gui_widget::set_visible(bool visible) // 0x10F13590
{
	eldorado::c_gui_widget_set_visible(this, visible);
}

c_gui_widget *c_gui_widget::find_first_child(e_gui_widget type) const // 0x10F131E0
{
	return ((c_gui_widget *(__thiscall *)(const c_gui_widget *, e_gui_widget))0xab8f80)(this, type);
}

c_gui_widget *c_gui_widget::find_next_sibling(e_gui_widget type) const // 0x10F13250
{
	return ((c_gui_widget *(__thiscall *)(c_gui_widget const *, e_gui_widget))0xab9290)(this, type);
}

void c_gui_widget::get_render_bounds(real_rectangle2d *bounds) const // 0x10F13490
{
	get_current_bounds(bounds);
}

c_gui_widget *c_gui_widget::find_ancestor(bool (*predicate)(c_gui_widget const &)) // 0x10F13130
{
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
	return ((c_gui_list_widget *(__thiscall *)(c_gui_widget *, unsigned long))0xab8aa0)(this, name);
}

c_gui_widget *c_gui_widget::get_child_widget(e_gui_widget type, unsigned long name) const // 0x10F13410
{
	return ((c_gui_widget *(__thiscall *)(const c_gui_widget *, e_gui_widget, unsigned long))0xab8b00)(this, type, name);
}

c_gui_bitmap_widget *c_gui_widget::get_child_bitmap_widget(unsigned long name) // 0x10F132C0
{
	return (c_gui_bitmap_widget *)get_child_widget(_gui_widget_bitmap, name);
}

c_gui_list_item_widget *c_gui_widget::get_child_text_widget(unsigned long name) // 0x10F133A0
{
	return (c_gui_list_item_widget *)get_child_widget(_gui_widget_text, name);
}

void c_gui_widget::set_text_widget_text(unsigned long name, wchar_t const *text) // 0x10F13510
{
	__int32 (__thiscall *const c_gui_screen_widget__set_text_widget_text)(void *, unsigned long, wchar_t const *) = (__int32(__thiscall *const)(void *, unsigned long, wchar_t const *))0xab23e0;

	c_gui_screen_widget__set_text_widget_text(this, name, text);
}

/* ---------- private code */
