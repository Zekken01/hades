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

_inline c_gui_data::c_gui_data() // 0x10F1DB30
{
	m_name = 0;
}

c_gui_data::~c_gui_data() // 0x10F1DC40
{
}

bool c_gui_data::initialize(unsigned long name) // 0x10F1EA20
{
	set_name(name);
	return true;
}

void c_gui_data::dispose() // 0x10F1E160
{
}

void c_gui_data::update() // 0x10F1EE20
{
}

bool c_gui_data::nullsub1() // 0x10F1EBD0
{
	return false;
}

bool c_gui_data::get_element(long element_handle, void *element, long element_size) // 0x10F1E3F0
{
	return false;
}

bool c_gui_data::get_integer_value(long element_handle, unsigned long name, long *value) // 0x10F1E570
{
	return false;
}

bool c_gui_data::get_text_value(long element_handle, unsigned long name, wchar_t (&value)[1024]) // 0x10F1E9C0
{
	return false;
}

bool c_gui_data::get_string_id_value(long element_handle, unsigned long name, unsigned long *value) // 0x10F1E960
{
	return false;
}

bool c_gui_data::get_qword_value(long element_handle, unsigned long name, unsigned long long *value) // 0x10F1E8A0
{
	return false;
}

bool c_gui_data::get_real_value(long element_handle, unsigned long name, float *value) // 0x10F1E900
{
	return false;
}

bool c_gui_data::get_player_appearance(long element_handle, s_player_appearance *__formal) // 0x10F1E770
{
	return false;
}

c_gui_selected_item const *c_gui_data::get_gui_selected_item() const // 0x10F1E520
{
	return nullptr;
}

long c_gui_data::get_maximum_item_count() // 0x10F1E630
{
	return get_current_item_count();
}

long c_gui_data::add_element() // 0x10F1DD80
{
	return -1;
}

#line 155
void c_gui_data::delete_element(long element_handle) // 0x10F1DEC0
{
#line 159

	#line 157 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"not implemented");
		#line 163 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::set_element(long element_handle, void const *element, long element_size) // 0x10F1ED40
{
#line 169

	#line 167 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"not implemented");
		#line 173 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

bool c_gui_data::get_invoked_control(long __formal, long *name) // 0x10F1E5D0
{
	return false;
}

#line 183
void c_gui_data::clear_disabled_elements() // 0x10F1DDE0
{
#line 187

	#line 185 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"datasource doesn't support enabling and disabling");
		#line 191 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::set_disabled_element(long element_index, unsigned long name) // 0x10F1EC20
{
#line 197

	#line 195 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"datasource doesn't support enabling and disabling");
		#line 201 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::disable_all_elements(unsigned long name) // 0x10F1DF40
{
#line 207

	#line 205 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"datasource doesn't support enabling and disabling");
		#line 211 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::enable_element(long element_index, unsigned long name) // 0x10F1E1B0
{
#line 217

	#line 215 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"datasource doesn't support enabling and disabling");
		#line 221 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::set_name(unsigned long name) // 0x10F1EDC0
{
	m_name = name;
}

c_gui_ordered_data::c_gui_ordered_data() // 0x10F1DBA0
{
	memset(m_disabled_elements, 0, sizeof(m_disabled_elements));
	m_disabled_element_count = 0;
}

long c_gui_ordered_data::get_current_item_count() // 0x10F1E330
{
	long item_count = 0;

	for (long item_index = 0; item_index < get_current_item_count_internal(); item_index++)
	{
		if (is_enabled(item_index))
		{
			item_count++;
		}
	}

	return item_count;
}

long c_gui_ordered_data::get_first_element_handle() // 0x10F1E450
{
	long item_count = get_current_item_count_internal();
	long index = 0;

	while (index >= 0 && index < item_count && !is_enabled(index))
	{
		index++;
	}

	if (index < 0 || index >= item_count)
	{
		return -1;
	}

	return index;
}

long c_gui_ordered_data::get_next_element_handle(long element_handle) // 0x10F1E6A0
{
	long item_count = get_current_item_count_internal();
	long index = element_handle + 1;

	while (index >= 0 && index < item_count && !is_enabled(index))
	{
		index++;
	}

	if (index < 0 || index >= item_count)
	{
		return -1;
	}

	return index;
}

long c_gui_ordered_data::get_previous_element_handle(long element_handle) // 0x10F1E7D0
{
	long item_count = get_current_item_count_internal();
	long index = element_handle - 1;

	while (index >= 0 && index < item_count && !is_enabled(index))
	{
		index--;
	}

	if (index < 0 || index >= item_count)
	{
		return -1;
	}

	return index;
}

void c_gui_ordered_data::clear_disabled_elements() // 0x10F1DE60
{
	m_disabled_element_count = 0;
}

void c_gui_ordered_data::set_disabled_element(long element_handle, unsigned long name) // 0x10F1ECA0
{
	if (m_disabled_element_count + 1 < 32)
	{
		m_disabled_elements[m_disabled_element_count].element_handle = element_handle;
		m_disabled_elements[m_disabled_element_count].name = name;
	}
}

// The original carries a /GS cookie here that our flags do not produce for a plain
// scalar whose address escapes; `strict_gs_check` forces it. Cause of the difference
// is unestablished -- see hades-gs-cookie.
#pragma strict_gs_check(push, on)
void c_gui_ordered_data::disable_all_elements(unsigned long name) // 0x10F1DFC0
{
	clear_disabled_elements();

	for (long element_handle = get_first_element_handle(); element_handle != -1; element_handle = get_next_element_handle(element_handle))
	{
		unsigned long value;

		if (get_string_id_value(element_handle, name, &value) && value != -1)
		{
			set_disabled_element(element_handle, name);
		}
	}
}
#pragma strict_gs_check(pop)

void c_gui_ordered_data::enable_element(long element_handle, unsigned long name) // 0x10F1E230
{
	for (long i = 0; i < m_disabled_element_count; i++)
	{
		if (m_disabled_elements[i].element_handle == element_handle && m_disabled_elements[i].name == name)
		{
			m_disabled_element_count--;
			csmemmove(&m_disabled_elements[i], &m_disabled_elements[i + 1], 8 * (m_disabled_element_count - i));
			return;
		}
	}
}

// The original carries a /GS cookie here that our flags do not produce for a plain
// scalar whose address escapes; `strict_gs_check` forces it. Cause of the difference
// is unestablished -- see hades-gs-cookie.
#pragma strict_gs_check(push, on)
bool c_gui_ordered_data::is_enabled(long element_index) // 0x10F1EA90
{
	for (long i = 0; i < m_disabled_element_count; i++)
	{
		unsigned long value = -1;

		if (get_string_id_value(element_index, m_disabled_elements[i].name, &value)
			&& value == m_disabled_elements[i].name)
		{
			return false;
		}
	}

	return true;
}
#pragma strict_gs_check(pop)

/* ---------- private code */
