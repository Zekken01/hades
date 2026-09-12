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

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_gui_screen_manager *c_gui_screen_manager::get() // 0x10F12E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@c_gui_screen_manager@@SAPAV1@XZ");
	// procedure flags: nofpo
	// function call : c_gui_screen_manager *(*)()

	return ((c_gui_screen_manager *(__cdecl *const)())0xaad930)();
}

bool c_gui_screen_manager::any_active_screens(long controller_index) const // 0x10F12D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?any_active_screens@c_gui_screen_manager@@QBE_NJ@Z");
	// long controller_index;
	// function call : bool (*)(c_gui_screen_manager const *, long)

	return ((bool(__thiscall *const)(const c_gui_screen_manager *, long))0xaaa970)(this, controller_index);
}

c_gui_screen_widget *c_gui_screen_manager::find_screen(long controller_index, unsigned long name) const // 0x10F12DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_screen@c_gui_screen_manager@@QBEPAVc_gui_screen_widget@@JK@Z");
	// unsigned long name;
	// function call : c_gui_screen_widget *(*)(c_gui_screen_manager const *, long, unsigned long)

	return ((c_gui_screen_widget *(__thiscall *const)(const c_gui_screen_manager *, long, unsigned long))0xaab550)(this, controller_index, name);
}

c_gui_screen_widget *c_gui_screen_manager::get_current_screen(long controller_index, long *out_output_user_index) const // 0x10F12ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_screen@c_gui_screen_manager@@QBEPAVc_gui_screen_widget@@JPAJ@Z");
	// long *out_output_user_index;
	// function call : c_gui_screen_widget *(*)(c_gui_screen_manager const *, long, long *)

	return ((c_gui_screen_widget *(__thiscall *const)(const c_gui_screen_manager *, long, long *))0xaab320)(this, controller_index, out_output_user_index);
}

c_gui_screen_widget *c_gui_screen_manager::get_screen_below(c_gui_screen_widget *screen_widget) const // 0x10F12F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_screen_below@c_gui_screen_manager@@QBEPAVc_gui_screen_widget@@PAV2@@Z");
	// c_gui_screen_widget *screen_widget;
	// function call : c_gui_screen_widget *(*)(c_gui_screen_manager const *, long, c_gui_screen_widget *)

	return ((c_gui_screen_widget *(__thiscall *const)(const c_gui_screen_manager *, int, c_gui_screen_widget *))0xaab4e0)(this, 4, screen_widget);
}

c_gui_screen_widget *c_gui_screen_manager::get_topmost_screen() const // 0x10F12FC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_topmost_screen@c_gui_screen_manager@@QBEPAVc_gui_screen_widget@@XZ");
	// c_gui_screen_manager const *const this;
	// function call : c_gui_screen_widget *(*)(c_gui_screen_manager const *, long)

	return ((c_gui_screen_widget *(__thiscall *const)(const c_gui_screen_manager *, int))0xaab630)(this, 4);
}

void c_gui_screen_manager::post_message(void *message) // 0x10F130C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?post_message@c_gui_screen_manager@@QAEXPAX@Z");
	// void *message;
	// function call : void (*)(c_gui_screen_manager *, void *)

	((void(__thiscall *const)(c_gui_screen_manager *, void *))0xaab7d0)(this, message);
}

_extern bool _sub_10F13030(c_gui_screen_manager *const, long);
bool c_gui_screen_manager::input_should_be_suppressed(long controller_index) // 0x10F13030
{
	mangled_x86(MANGLED_TODO, "?input_should_be_suppressed@c_gui_screen_manager@@QAE_NJ@Z");
	// long controller_index;
	// function call : char (*)(c_gui_screen_manager *, long)
	todo("implement");
	bool __result = _sub_10F13030(this, controller_index);
	return __result;
}

/* ---------- private code */
