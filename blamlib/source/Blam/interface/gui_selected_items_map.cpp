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

extern bool (*const levels_try_and_get_multiplayer_map)(long, s_level_datum *);  // hades: added for 0x10F1CEF0

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_gui_map_category_datasource::c_gui_map_category_datasource(wchar_t const *recent_maps_item_name, wchar_t const *recent_maps_item_description, wchar_t const *file_share_item_name, wchar_t const *file_share_item_description) // 0x10F1C5C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_gui_map_category_datasource@@QAE@PB_W000@Z");

	memset(&m_items, 0, sizeof(m_items));
	((wchar_t *(*)(wchar_t *, wchar_t const *, long))0x4ECCD0)(m_recent_item_name, recent_maps_item_name, 48);
	((wchar_t *(*)(wchar_t *, wchar_t const *, long))0x4ECCD0)(m_recent_item_description, recent_maps_item_description, 256);
	((wchar_t *(*)(wchar_t *, wchar_t const *, long))0x4ECCD0)(m_file_share_item_name, file_share_item_name, 48);
	((wchar_t *(*)(wchar_t *, wchar_t const *, long))0x4ECCD0)(m_file_share_item_description, file_share_item_description, 256);
	m_item_count = 0;
}


bool c_gui_map_category_datasource::initialize(unsigned long name) // 0x10F1CEF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_gui_map_category_datasource@@UAE_NK@Z");

	if (!c_gui_data::initialize(name))
		return false;
	long map_ids[100];
	long map_id_count = 100;
	((void (*)(long *, long *))0x54BEE0)(map_ids, &map_id_count);
	m_item_count = 0;
	for (long i = 0; i < map_id_count; i++)
	{
		s_level_datum level_datum;
		if (levels_try_and_get_multiplayer_map(map_ids[i], &level_datum))
		{
			c_gui_map_category_datasource::s_map_category_item &new_item = m_items[m_item_count++];
			new_item.special_status = 2;
			new_item.map_id = map_ids[i];
			new_item.type = 2;
			((wchar_t *(*)(wchar_t *, wchar_t const *, long))0x4ECCD0)(new_item.name, level_datum.name, 48);
			((wchar_t *(*)(wchar_t *, wchar_t const *, long))0x4ECCD0)(new_item.description, level_datum.description, 256);
		}
	}
	__int32 (*const map_selected_item_sort_proc)(void const *, void const *) = reinterpret_cast<__int32 (*)(void const *, void const *)>(0xADA1D0);
	qsort(m_items.get_elements(), m_item_count, sizeof(c_gui_map_category_datasource::s_map_category_item), map_selected_item_sort_proc);
	return true;
}

#line 115
void c_gui_map_category_datasource::get_column_names(unsigned long *names, long *out_name_count) // 0x10F1C900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_column_names@c_gui_map_category_datasource@@UAEXPAKPAJ@Z");
	// long *out_name_count;

	#line 117 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui_selected_items_map.cpp"
		assert(names);
		assert(out_name_count);
		#line 124 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui_selected_items_map.cpp"
	*out_name_count = 0;
	names[*out_name_count++] = 0x105;
	names[*out_name_count++] = 0x2AB;
	names[*out_name_count++] = 0x2AC;
}

bool c_gui_map_category_datasource::get_integer_value(long element_handle, unsigned long name, long *value) // 0x10F1CAD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_integer_value@c_gui_map_category_datasource@@UAE_NJKPAJ@Z");
	// long *value;

	#line 132 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui_selected_items_map.cpp"
		assert(value);
		#line 138 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui_selected_items_map.cpp"
	*value = -1;
	if (element_handle >= 0 || element_handle < m_item_count)
	{
		switch (name)
		{
		case 0x10400:
			*value = m_items[element_handle].special_status;
			return true;
		case 0x10346:
			if (m_items[element_handle].special_status >= 0 && m_items[element_handle].special_status <= 1)
			{
				*value = m_items[element_handle].special_status;
				return true;
			}
			break;
		case 0x105:
		case 0x10029:
			*value = m_items[element_handle].map_id;
			return true;
		}
	}
	return false;
}

bool c_gui_map_category_datasource::get_text_value(long element_handle, unsigned long name, wchar_t (&value)[1024]) // 0x10F1CD80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_text_value@c_gui_map_category_datasource@@UAE_NJKAAY0EAA@_W@Z");
	// wchar_t (&value)[1024];
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)

	#line 164 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui_selected_items_map.cpp"
		assert(value);
		#line 172 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui_selected_items_map.cpp"
	if (element_handle >= 0 && element_handle < m_item_count)
	{
		switch (name)
		{
		case 0x2AB:
			((wchar_t *(__cdecl *)(wchar_t *, wchar_t const *, long))0x4ECCD0)(value, m_items[element_handle].name, 1024);
			return true;
		case 0x2AC:
			((wchar_t *(__cdecl *)(wchar_t *, wchar_t const *, long))0x4ECCD0)(value, m_items[element_handle].description, 1024);
			return true;
		}
	}

	return false;
}

_inline bool c_gui_map_category_datasource::get_string_id_value(long element_handle, unsigned long name, unsigned long *value) // 0x10F1CCE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_string_id_value@c_gui_map_category_datasource@@UAE_NJKPAK@Z");
	// unsigned long *value;

	#line 190 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui_selected_items_map.cpp"
		assert(value);
		#line 196 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui_selected_items_map.cpp"
	if (name == 0x10345)
	{
		*value = 0x10349;
		return true;
	}

	return false;
}

_inline long c_gui_map_category_datasource::get_current_item_count_internal() // 0x10F1CA10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_item_count_internal@c_gui_map_category_datasource@@MAEJXZ");

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
