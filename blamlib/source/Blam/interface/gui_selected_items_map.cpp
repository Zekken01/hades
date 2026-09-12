/* ---------- headers */

#include "Blam/interface/gui_selected_items_map.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/interface/gui/gui_data.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class c_gui_map_category_datasource;
class c_gui_ordered_data;
struct s_level_datum;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_gui_map_category_datasource* _sub_10F1C5C0(c_gui_map_category_datasource *const, wchar_t const *, wchar_t const *, wchar_t const *, wchar_t const *);
c_gui_map_category_datasource::c_gui_map_category_datasource(wchar_t const *recent_maps_item_name, wchar_t const *recent_maps_item_description, wchar_t const *file_share_item_name, wchar_t const *file_share_item_description) // 0x10F1C5C0
{
	mangled_x86(MANGLED_TODO, "??0c_gui_map_category_datasource@@QAE@PB_W000@Z");
	// wchar_t const *file_share_item_description;
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	todo("implement");
	_sub_10F1C5C0(this, recent_maps_item_name, recent_maps_item_description, file_share_item_name, file_share_item_description);
}

_inline c_gui_map_category_datasource::~c_gui_map_category_datasource() // 0x10F1C760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_gui_map_category_datasource@@UAE@XZ");
	// c_gui_map_category_datasource *const this;

	compiler_generated();
}

_inline c_gui_ordered_data::~c_gui_ordered_data() // 0x10F1C7B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_gui_ordered_data@@UAE@XZ");
	// c_gui_ordered_data *const this;

	compiler_generated();
}

_extern bool _sub_10F1CEF0(c_gui_map_category_datasource *const, unsigned long);
bool c_gui_map_category_datasource::initialize(unsigned long name) // 0x10F1CEF0
{
	mangled_x86(MANGLED_TODO, "?initialize@c_gui_map_category_datasource@@UAE_NK@Z");
	// static ...; // 0x10F1D16C
	// static ...; // 0x10F1D160
	// static ...; // 0x10F1D13C
	// static ...; // 0x10F1D134
	// c_gui_map_category_datasource *const this;
	// unsigned long name;
	// __int32 (*const map_selected_item_sort_proc)(void const *, void const *);
	// long map_ids[100];
	// long map_id_count;
	{
		// long i;
		{
			// s_level_datum level_datum;
			{
				// c_gui_map_category_datasource::s_map_category_item &new_item;
			}
		}
	}
	// function call : long *(*const)(long *, long *)
	// function call : bool (*const)(long, s_level_datum *)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	todo("implement");
	bool __result = _sub_10F1CEF0(this, name);
	return __result;
}

_extern void _sub_10F1C900(c_gui_map_category_datasource *const, unsigned long *, long *);
void c_gui_map_category_datasource::get_column_names(unsigned long *names, long *out_name_count) // 0x10F1C900
{
	mangled_x86(MANGLED_TODO, "?get_column_names@c_gui_map_category_datasource@@UAEXPAKPAJ@Z");
	// long *out_name_count;
	todo("implement");
	_sub_10F1C900(this, names, out_name_count);
}

_extern bool _sub_10F1CAD0(c_gui_map_category_datasource *const, long, unsigned long, long *);
bool c_gui_map_category_datasource::get_integer_value(long element_handle, unsigned long name, long *value) // 0x10F1CAD0
{
	mangled_x86(MANGLED_TODO, "?get_integer_value@c_gui_map_category_datasource@@UAE_NJKPAJ@Z");
	// long *value;
	todo("implement");
	bool __result = _sub_10F1CAD0(this, element_handle, name, value);
	return __result;
}

_extern bool _sub_10F1CD80(c_gui_map_category_datasource *const, long, unsigned long, wchar_t (&)[1024]);
bool c_gui_map_category_datasource::get_text_value(long element_handle, unsigned long name, wchar_t (&value)[1024]) // 0x10F1CD80
{
	mangled_x86(MANGLED_TODO, "?get_text_value@c_gui_map_category_datasource@@UAE_NJKAAY0EAA@_W@Z");
	// wchar_t (&value)[1024];
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	todo("implement");
	bool __result = _sub_10F1CD80(this, element_handle, name, value);
	return __result;
}

_extern bool _sub_10F1CCE0(c_gui_map_category_datasource *const, long, unsigned long, unsigned long *);
_inline bool c_gui_map_category_datasource::get_string_id_value(long element_handle, unsigned long name, unsigned long *value) // 0x10F1CCE0
{
	mangled_x86(MANGLED_TODO, "?get_string_id_value@c_gui_map_category_datasource@@UAE_NJKPAK@Z");
	// unsigned long *value;
	todo("implement");
	bool __result = _sub_10F1CCE0(this, element_handle, name, value);
	return __result;
}

_inline long c_gui_map_category_datasource::get_current_item_count_internal() // 0x10F1CA10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_item_count_internal@c_gui_map_category_datasource@@MAEJXZ");
	// c_gui_map_category_datasource *const this;

	return m_item_count;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<c_gui_map_category_datasource::s_map_category_item,100>::valid(__int32);
template c_gui_map_category_datasource::s_map_category_item & s_static_array<c_gui_map_category_datasource::s_map_category_item,100>::operator[](long);
template c_gui_map_category_datasource::s_map_category_item * s_static_array<c_gui_map_category_datasource::s_map_category_item,100>::get_elements();
