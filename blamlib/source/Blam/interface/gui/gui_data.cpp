/* ---------- headers */

#include "Blam/interface/gui/gui_data.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_selected_items.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerCharacterSystem.hpp"

/* ---------- forward declarations */

class c_gui_data;
class c_gui_ordered_data;
class c_gui_selected_item;
struct s_player_appearance;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_gui_data* _sub_10F1DB30(c_gui_data *const);
_inline c_gui_data::c_gui_data() // 0x10F1DB30
{
	mangled_x86(MANGLED_TODO, "??0c_gui_data@@QAE@XZ");
	// c_gui_data *const this;
	todo("implement");
	_sub_10F1DB30(this);
}

_extern void _sub_10F1DC40(c_gui_data *const);
c_gui_data::~c_gui_data() // 0x10F1DC40
{
	mangled_x86(MANGLED_TODO, "??1c_gui_data@@UAE@XZ");
	// c_gui_data *const this;
	todo("implement");
	_sub_10F1DC40(this);
}

_extern bool _sub_10F1EA20(c_gui_data *const, unsigned long);
bool c_gui_data::initialize(unsigned long name) // 0x10F1EA20
{
	mangled_x86(MANGLED_TODO, "?initialize@c_gui_data@@UAE_NK@Z");
	// unsigned long name;
	todo("implement");
	bool __result = _sub_10F1EA20(this, name);
	return __result;
}

_extern void _sub_10F1E160(c_gui_data *const);
void c_gui_data::dispose() // 0x10F1E160
{
	mangled_x86(MANGLED_TODO, "?dispose@c_gui_data@@UAEXXZ");
	// c_gui_data *const this;
	todo("implement");
	_sub_10F1E160(this);
}

_extern void _sub_10F1EE20(c_gui_data *const);
void c_gui_data::update() // 0x10F1EE20
{
	mangled_x86(MANGLED_TODO, "?update@c_gui_data@@UAEXXZ");
	// c_gui_data *const this;
	todo("implement");
	_sub_10F1EE20(this);
}

_extern bool _sub_10F1EBD0(c_gui_data *const);
bool c_gui_data::nullsub1() // 0x10F1EBD0
{
	mangled_x86(MANGLED_TODO, "?nullsub1@c_gui_data@@UAE_NXZ");
	// c_gui_data *const this;
	todo("implement");
	bool __result = _sub_10F1EBD0(this);
	return __result;
}

_extern bool _sub_10F1E3F0(c_gui_data *const, long, void *, long);
bool c_gui_data::get_element(long element_handle, void *element, long element_size) // 0x10F1E3F0
{
	mangled_x86(MANGLED_TODO, "?get_element@c_gui_data@@UAE_NJPAXJ@Z");
	// long element_size;
	todo("implement");
	bool __result = _sub_10F1E3F0(this, element_handle, element, element_size);
	return __result;
}

_extern bool _sub_10F1E570(c_gui_data *const, long, unsigned long, long *);
bool c_gui_data::get_integer_value(long element_handle, unsigned long name, long *value) // 0x10F1E570
{
	mangled_x86(MANGLED_TODO, "?get_integer_value@c_gui_data@@UAE_NJKPAJ@Z");
	// long *value;
	todo("implement");
	bool __result = _sub_10F1E570(this, element_handle, name, value);
	return __result;
}

_extern bool _sub_10F1E9C0(c_gui_data *const, long, unsigned long, wchar_t (&)[1024]);
bool c_gui_data::get_text_value(long element_handle, unsigned long name, wchar_t (&value)[1024]) // 0x10F1E9C0
{
	mangled_x86(MANGLED_TODO, "?get_text_value@c_gui_data@@UAE_NJKAAY0EAA@_W@Z");
	// wchar_t (&value)[1024];
	todo("implement");
	bool __result = _sub_10F1E9C0(this, element_handle, name, value);
	return __result;
}

_extern bool _sub_10F1E960(c_gui_data *const, long, unsigned long, unsigned long *);
bool c_gui_data::get_string_id_value(long element_handle, unsigned long name, unsigned long *value) // 0x10F1E960
{
	mangled_x86(MANGLED_TODO, "?get_string_id_value@c_gui_data@@UAE_NJKPAK@Z");
	// unsigned long *value;
	todo("implement");
	bool __result = _sub_10F1E960(this, element_handle, name, value);
	return __result;
}

_extern bool _sub_10F1E8A0(c_gui_data *const, long, unsigned long, unsigned long long *);
bool c_gui_data::get_qword_value(long element_handle, unsigned long name, unsigned long long *value) // 0x10F1E8A0
{
	mangled_x86(MANGLED_TODO, "?get_qword_value@c_gui_data@@UAE_NJKPA_K@Z");
	// unsigned long long *value;
	todo("implement");
	bool __result = _sub_10F1E8A0(this, element_handle, name, value);
	return __result;
}

_extern bool _sub_10F1E900(c_gui_data *const, long, unsigned long, float *);
bool c_gui_data::get_real_value(long element_handle, unsigned long name, float *value) // 0x10F1E900
{
	mangled_x86(MANGLED_TODO, "?get_real_value@c_gui_data@@UAE_NJKPAM@Z");
	// float *value;
	todo("implement");
	bool __result = _sub_10F1E900(this, element_handle, name, value);
	return __result;
}

_extern bool _sub_10F1E770(c_gui_data *const, long, s_player_appearance *);
bool c_gui_data::get_player_appearance(long element_handle, s_player_appearance *__formal) // 0x10F1E770
{
	mangled_x86(MANGLED_TODO, "?get_player_appearance@c_gui_data@@UAE_NJPAUs_player_appearance@@@Z");
	// s_player_appearance *__formal;
	todo("implement");
	bool __result = _sub_10F1E770(this, element_handle, __formal);
	return __result;
}

extern c_gui_selected_item const *_sub_10F1E520(c_gui_data const *const);
c_gui_selected_item const *c_gui_data::get_gui_selected_item() const // 0x10F1E520
{
	mangled_x86(MANGLED_TODO, "?get_gui_selected_item@c_gui_data@@UBEPBVc_gui_selected_item@@XZ");
	// c_gui_data const *const this;
	todo("implement");
	c_gui_selected_item const * __result = _sub_10F1E520((c_gui_data const *)this);
	return __result;
}

_extern long _sub_10F1E630(c_gui_data *const);
long c_gui_data::get_maximum_item_count() // 0x10F1E630
{
	mangled_x86(MANGLED_TODO, "?get_maximum_item_count@c_gui_data@@UAEJXZ");
	// c_gui_data *const this;
	// function call : long ()
	todo("implement");
	long __result = _sub_10F1E630(this);
	return __result;
}

_extern long _sub_10F1DD80(c_gui_data *const);
long c_gui_data::add_element() // 0x10F1DD80
{
	mangled_x86(MANGLED_TODO, "?add_element@c_gui_data@@UAEJXZ");
	// c_gui_data *const this;
	todo("implement");
	long __result = _sub_10F1DD80(this);
	return __result;
}

_extern void _sub_10F1DEC0(c_gui_data *const, long);
void c_gui_data::delete_element(long element_handle) // 0x10F1DEC0
{
	mangled_x86(MANGLED_TODO, "?delete_element@c_gui_data@@UAEXJ@Z");
	// long element_handle;
	todo("implement");
	_sub_10F1DEC0(this, element_handle);
}

_extern void _sub_10F1ED40(c_gui_data *const, long, void const *, long);
void c_gui_data::set_element(long element_handle, void const *element, long element_size) // 0x10F1ED40
{
	mangled_x86(MANGLED_TODO, "?set_element@c_gui_data@@UAEXJPBXJ@Z");
	// long element_size;
	todo("implement");
	_sub_10F1ED40(this, element_handle, element, element_size);
}

_extern bool _sub_10F1E5D0(c_gui_data *const, long, long *);
bool c_gui_data::get_invoked_control(long __formal, long *name) // 0x10F1E5D0
{
	mangled_x86(MANGLED_TODO, "?get_invoked_control@c_gui_data@@UAE_NJPAJ@Z");
	// long *name;
	todo("implement");
	bool __result = _sub_10F1E5D0(this, __formal, name);
	return __result;
}

_extern void _sub_10F1DDE0(c_gui_data *const);
void c_gui_data::clear_disabled_elements() // 0x10F1DDE0
{
	mangled_x86(MANGLED_TODO, "?clear_disabled_elements@c_gui_data@@UAEXXZ");
	// c_gui_data *const this;
	todo("implement");
	_sub_10F1DDE0(this);
}

_extern void _sub_10F1EC20(c_gui_data *const, long, unsigned long);
void c_gui_data::set_disabled_element(long element_index, unsigned long name) // 0x10F1EC20
{
	mangled_x86(MANGLED_TODO, "?set_disabled_element@c_gui_data@@UAEXJK@Z");
	// unsigned long name;
	todo("implement");
	_sub_10F1EC20(this, element_index, name);
}

_extern void _sub_10F1DF40(c_gui_data *const, unsigned long);
void c_gui_data::disable_all_elements(unsigned long name) // 0x10F1DF40
{
	mangled_x86(MANGLED_TODO, "?disable_all_elements@c_gui_data@@UAEXK@Z");
	// unsigned long name;
	todo("implement");
	_sub_10F1DF40(this, name);
}

_extern void _sub_10F1E1B0(c_gui_data *const, long, unsigned long);
void c_gui_data::enable_element(long element_index, unsigned long name) // 0x10F1E1B0
{
	mangled_x86(MANGLED_TODO, "?enable_element@c_gui_data@@UAEXJK@Z");
	// unsigned long name;
	todo("implement");
	_sub_10F1E1B0(this, element_index, name);
}

_extern void _sub_10F1EDC0(c_gui_data *const, unsigned long);
void c_gui_data::set_name(unsigned long name) // 0x10F1EDC0
{
	mangled_x86(MANGLED_TODO, "?set_name@c_gui_data@@QAEXK@Z");
	// unsigned long name;
	todo("implement");
	_sub_10F1EDC0(this, name);
}

extern c_gui_ordered_data* _sub_10F1DBA0(c_gui_ordered_data *const);
c_gui_ordered_data::c_gui_ordered_data() // 0x10F1DBA0
{
	mangled_x86(MANGLED_TODO, "??0c_gui_ordered_data@@QAE@XZ");
	// c_gui_ordered_data *const this;
	todo("implement");
	_sub_10F1DBA0(this);
}

_extern long _sub_10F1E330(c_gui_ordered_data *const);
long c_gui_ordered_data::get_current_item_count() // 0x10F1E330
{
	mangled_x86(MANGLED_TODO, "?get_current_item_count@c_gui_ordered_data@@UAEJXZ");
	// c_gui_ordered_data *const this;
	// long item_count;
	{
		// long item_index;
	}
	// function call : long ()
	todo("implement");
	long __result = _sub_10F1E330(this);
	return __result;
}

_extern long _sub_10F1E450(c_gui_ordered_data *const);
long c_gui_ordered_data::get_first_element_handle() // 0x10F1E450
{
	mangled_x86(MANGLED_TODO, "?get_first_element_handle@c_gui_ordered_data@@UAEJXZ");
	// c_gui_ordered_data *const this;
	// long item_count;
	// long index;
	// function call : long ()
	todo("implement");
	long __result = _sub_10F1E450(this);
	return __result;
}

_extern long _sub_10F1E6A0(c_gui_ordered_data *const, long);
long c_gui_ordered_data::get_next_element_handle(long element_handle) // 0x10F1E6A0
{
	mangled_x86(MANGLED_TODO, "?get_next_element_handle@c_gui_ordered_data@@UAEJJ@Z");
	// long element_handle;
	// long item_count;
	// long index;
	// function call : long ()
	todo("implement");
	long __result = _sub_10F1E6A0(this, element_handle);
	return __result;
}

_extern long _sub_10F1E7D0(c_gui_ordered_data *const, long);
long c_gui_ordered_data::get_previous_element_handle(long element_handle) // 0x10F1E7D0
{
	mangled_x86(MANGLED_TODO, "?get_previous_element_handle@c_gui_ordered_data@@UAEJJ@Z");
	// long element_handle;
	// long item_count;
	// long index;
	// function call : long ()
	todo("implement");
	long __result = _sub_10F1E7D0(this, element_handle);
	return __result;
}

_extern void _sub_10F1DE60(c_gui_ordered_data *const);
void c_gui_ordered_data::clear_disabled_elements() // 0x10F1DE60
{
	mangled_x86(MANGLED_TODO, "?clear_disabled_elements@c_gui_ordered_data@@UAEXXZ");
	// c_gui_ordered_data *const this;
	todo("implement");
	_sub_10F1DE60(this);
}

_extern void _sub_10F1ECA0(c_gui_ordered_data *const, long, unsigned long);
void c_gui_ordered_data::set_disabled_element(long element_handle, unsigned long name) // 0x10F1ECA0
{
	mangled_x86(MANGLED_TODO, "?set_disabled_element@c_gui_ordered_data@@UAEXJK@Z");
	// unsigned long name;
	todo("implement");
	_sub_10F1ECA0(this, element_handle, name);
}

_extern void _sub_10F1DFC0(c_gui_ordered_data *const, unsigned long);
void c_gui_ordered_data::disable_all_elements(unsigned long name) // 0x10F1DFC0
{
	mangled_x86(MANGLED_TODO, "?disable_all_elements@c_gui_ordered_data@@UAEXK@Z");
	// static ...; // 0x10F1E0F4
	// static ...; // 0x10F1E0EC
	// c_gui_ordered_data *const this;
	// unsigned long name;
	{
		// long element_handle;
		{
			// unsigned long value;
		}
	}
	// function call : void ()
	// function call : long ()
	// function call : long (long)
	// function call : bool (long, unsigned long, unsigned long *)
	// function call : void (long, unsigned long)
	todo("implement");
	_sub_10F1DFC0(this, name);
}

_extern void _sub_10F1E230(c_gui_ordered_data *const, long, unsigned long);
void c_gui_ordered_data::enable_element(long element_handle, unsigned long name) // 0x10F1E230
{
	mangled_x86(MANGLED_TODO, "?enable_element@c_gui_ordered_data@@UAEXJK@Z");
	// unsigned long name;
	{
		// long i;
	}
	todo("implement");
	_sub_10F1E230(this, element_handle, name);
}

_extern bool _sub_10F1EA90(c_gui_ordered_data *const, long);
bool c_gui_ordered_data::is_enabled(long element_index) // 0x10F1EA90
{
	mangled_x86(MANGLED_TODO, "?is_enabled@c_gui_ordered_data@@AAE_NJ@Z");
	// static ...; // 0x10F1EB78
	// static ...; // 0x10F1EB70
	// c_gui_ordered_data *const this;
	// long element_index;
	{
		// long i;
		{
			// unsigned long value;
		}
	}
	// function call : bool (long, unsigned long, unsigned long *)
	todo("implement");
	bool __result = _sub_10F1EA90(this, element_index);
	return __result;
}

/* ---------- private code */
