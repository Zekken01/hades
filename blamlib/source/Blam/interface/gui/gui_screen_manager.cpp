/* ---------- headers */

#include "Blam/interface/gui/gui_screen_manager.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_gui_screen_manager;
class c_gui_screen_widget;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const c_window_manager_controller_input_should_be_suppressed = reinterpret_cast<bool(__thiscall *)(const c_gui_screen_manager *, long)>(0xAAA970);
	static auto const c_window_manager_get_responding_screen = reinterpret_cast<c_gui_screen_widget *(__thiscall *)(const c_gui_screen_manager *, long, long *)>(0xAAB320);
	static auto const c_window_manager_get_screen_below = reinterpret_cast<c_gui_screen_widget *(__thiscall *)(const c_gui_screen_manager *, int, c_gui_screen_widget *)>(0xAAB4E0);
	static auto const c_window_manager_get_screen_by_name = reinterpret_cast<c_gui_screen_widget *(__thiscall *)(const c_gui_screen_manager *, long, unsigned long)>(0xAAB550);
	static auto const c_window_manager_get_topmost_screen = reinterpret_cast<c_gui_screen_widget *(__thiscall *)(const c_gui_screen_manager *, int)>(0xAAB630);
	static auto const c_window_manager_handle_global_controller_event = reinterpret_cast<void(__thiscall *)(c_gui_screen_manager *, void *)>(0xAAB7D0);
	static auto const window_manager_get = reinterpret_cast<c_gui_screen_manager *(__cdecl *)()>(0xAAD930);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_gui_screen_manager *c_gui_screen_manager::get() // 0x10F12E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@c_gui_screen_manager@@SAPAV1@XZ");

	return eldorado::window_manager_get();
}

bool c_gui_screen_manager::any_active_screens(long controller_index) const // 0x10F12D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?any_active_screens@c_gui_screen_manager@@QBE_NJ@Z");

	return eldorado::c_window_manager_controller_input_should_be_suppressed(this, controller_index);
}

c_gui_screen_widget *c_gui_screen_manager::find_screen(long controller_index, unsigned long name) const // 0x10F12DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_screen@c_gui_screen_manager@@QBEPAVc_gui_screen_widget@@JK@Z");

	return eldorado::c_window_manager_get_screen_by_name(this, controller_index, name);
}

c_gui_screen_widget *c_gui_screen_manager::get_current_screen(long controller_index, long *out_output_user_index) const // 0x10F12ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_screen@c_gui_screen_manager@@QBEPAVc_gui_screen_widget@@JPAJ@Z");

	return eldorado::c_window_manager_get_responding_screen(this, controller_index, out_output_user_index);
}

c_gui_screen_widget *c_gui_screen_manager::get_screen_below(c_gui_screen_widget *screen_widget) const // 0x10F12F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_screen_below@c_gui_screen_manager@@QBEPAVc_gui_screen_widget@@PAV2@@Z");

	return eldorado::c_window_manager_get_screen_below(this, 4, screen_widget);
}

c_gui_screen_widget *c_gui_screen_manager::get_topmost_screen() const // 0x10F12FC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_topmost_screen@c_gui_screen_manager@@QBEPAVc_gui_screen_widget@@XZ");

	return eldorado::c_window_manager_get_topmost_screen(this, 4);
}

void c_gui_screen_manager::post_message(void *message) // 0x10F130C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?post_message@c_gui_screen_manager@@QAEXPAX@Z");

	eldorado::c_window_manager_handle_global_controller_event(this, message);
}

bool c_gui_screen_manager::input_should_be_suppressed(long controller_index) // 0x10F13030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_should_be_suppressed@c_gui_screen_manager@@QAE_NJ@Z");

	return (bool)((char(__thiscall *)(c_gui_screen_manager *, long))0xAAA970)(this, controller_index);
}

/* ---------- private code */
