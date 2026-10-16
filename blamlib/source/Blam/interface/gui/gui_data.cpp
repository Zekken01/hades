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
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_gui_data@@QAE@XZ");

	m_name = 0;
}

c_gui_data::~c_gui_data() // 0x10F1DC40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_gui_data@@UAE@XZ");
}

bool c_gui_data::initialize(unsigned long name) // 0x10F1EA20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_gui_data@@UAE_NK@Z");

	set_name(name);
	return true;
}

void c_gui_data::dispose() // 0x10F1E160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?dispose@c_gui_data@@UAEXXZ");
}

void c_gui_data::update() // 0x10F1EE20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update@c_gui_data@@UAEXXZ");
}

bool c_gui_data::nullsub1() // 0x10F1EBD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?nullsub1@c_gui_data@@UAE_NXZ");

	return false;
}

bool c_gui_data::get_element(long element_handle, void *element, long element_size) // 0x10F1E3F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_element@c_gui_data@@UAE_NJPAXJ@Z");

	return false;
}

bool c_gui_data::get_integer_value(long element_handle, unsigned long name, long *value) // 0x10F1E570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_integer_value@c_gui_data@@UAE_NJKPAJ@Z");

	return false;
}

bool c_gui_data::get_text_value(long element_handle, unsigned long name, wchar_t (&value)[1024]) // 0x10F1E9C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_text_value@c_gui_data@@UAE_NJKAAY0EAA@_W@Z");

	return false;
}

bool c_gui_data::get_string_id_value(long element_handle, unsigned long name, unsigned long *value) // 0x10F1E960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_string_id_value@c_gui_data@@UAE_NJKPAK@Z");

	return false;
}

bool c_gui_data::get_qword_value(long element_handle, unsigned long name, unsigned long long *value) // 0x10F1E8A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_qword_value@c_gui_data@@UAE_NJKPA_K@Z");

	return false;
}

bool c_gui_data::get_real_value(long element_handle, unsigned long name, float *value) // 0x10F1E900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_real_value@c_gui_data@@UAE_NJKPAM@Z");

	return false;
}

bool c_gui_data::get_player_appearance(long element_handle, s_player_appearance *__formal) // 0x10F1E770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_appearance@c_gui_data@@UAE_NJPAUs_player_appearance@@@Z");

	return false;
}

c_gui_selected_item const *c_gui_data::get_gui_selected_item() const // 0x10F1E520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_gui_selected_item@c_gui_data@@UBEPBVc_gui_selected_item@@XZ");

	return nullptr;
}

long c_gui_data::get_maximum_item_count() // 0x10F1E630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_maximum_item_count@c_gui_data@@UAEJXZ");

	return get_current_item_count();
}

long c_gui_data::add_element() // 0x10F1DD80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_element@c_gui_data@@UAEJXZ");

	return -1;
}

#line 155
void c_gui_data::delete_element(long element_handle) // 0x10F1DEC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?delete_element@c_gui_data@@UAEXJ@Z");
	// long element_handle;

	#line 157 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"not implemented");
		#line 163 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::set_element(long element_handle, void const *element, long element_size) // 0x10F1ED40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_element@c_gui_data@@UAEXJPBXJ@Z");
	// long element_size;

	#line 167 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"not implemented");
		#line 173 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

bool c_gui_data::get_invoked_control(long __formal, long *name) // 0x10F1E5D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_invoked_control@c_gui_data@@UAE_NJPAJ@Z");

	return false;
}

#line 183
void c_gui_data::clear_disabled_elements() // 0x10F1DDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?clear_disabled_elements@c_gui_data@@UAEXXZ");
	// c_gui_data *const this;

	#line 185 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"datasource doesn't support enabling and disabling");
		#line 191 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::set_disabled_element(long element_index, unsigned long name) // 0x10F1EC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_disabled_element@c_gui_data@@UAEXJK@Z");
	// unsigned long name;

	#line 195 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"datasource doesn't support enabling and disabling");
		#line 201 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::disable_all_elements(unsigned long name) // 0x10F1DF40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?disable_all_elements@c_gui_data@@UAEXK@Z");
	// unsigned long name;

	#line 205 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"datasource doesn't support enabling and disabling");
		#line 211 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::enable_element(long element_index, unsigned long name) // 0x10F1E1B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?enable_element@c_gui_data@@UAEXJK@Z");
	// unsigned long name;

	#line 215 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\interface\\gui\\gui_data.cpp"
		assert(!"datasource doesn't support enabling and disabling");
		#line 221 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\interface\\gui\\gui_data.cpp"
}

void c_gui_data::set_name(unsigned long name) // 0x10F1EDC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_name@c_gui_data@@QAEXK@Z");

	m_name = name;
}

c_gui_ordered_data::c_gui_ordered_data() // 0x10F1DBA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_gui_ordered_data@@QAE@XZ");

	memset(m_disabled_elements, 0, sizeof(m_disabled_elements));
	m_disabled_element_count = 0;
}

long c_gui_ordered_data::get_current_item_count() // 0x10F1E330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_item_count@c_gui_ordered_data@@UAEJXZ");

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
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_first_element_handle@c_gui_ordered_data@@UAEJXZ");

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
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_next_element_handle@c_gui_ordered_data@@UAEJJ@Z");

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
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_previous_element_handle@c_gui_ordered_data@@UAEJJ@Z");

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
	mangled_x86(MANGLED_KNOWN_GOOD, "?clear_disabled_elements@c_gui_ordered_data@@UAEXXZ");

	m_disabled_element_count = 0;
}

void c_gui_ordered_data::set_disabled_element(long element_handle, unsigned long name) // 0x10F1ECA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_disabled_element@c_gui_ordered_data@@UAEXJK@Z");

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
	mangled_x86(MANGLED_KNOWN_GOOD, "?disable_all_elements@c_gui_ordered_data@@UAEXK@Z");

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
	mangled_x86(MANGLED_KNOWN_GOOD, "?enable_element@c_gui_ordered_data@@UAEXJK@Z");

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
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_enabled@c_gui_ordered_data@@AAE_NJ@Z");

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
