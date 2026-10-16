/* ---------- headers */

#include "Blam/simulation/simulation_type_collection.hpp"
#include "hades/hades.h"

#include "Blam/simulation/simulation_types.hpp"

/* ---------- forward declarations */

class c_simulation_event_definition;
class c_simulation_type_collection;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void c_simulation_type_collection::register_event_definition(e_simulation_event_type type, c_simulation_event_definition *definition) // 0x10F06750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?register_event_definition@c_simulation_type_collection@@QAEXW4e_simulation_event_type@@PAVc_simulation_event_definition@@@Z");
#line 29

	#line 27 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\simulation\\simulation_type_collection.cpp"
		(void)((!!(type >= 0 && type < 64)) || (_wassert(L"type >= 0 && type < k_simulation_event_type_maximum_count", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
		#line 33 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\simulation\\simulation_type_collection.cpp"
	if (type < 0 || type >= 64)
	{
		return;
	}

	m_event_types[type] = definition;
}

/* ---------- private code */
