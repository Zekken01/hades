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

_extern void _sub_10F06750(c_simulation_type_collection *const, e_simulation_event_type, c_simulation_event_definition *);
void c_simulation_type_collection::register_event_definition(e_simulation_event_type type, c_simulation_event_definition *definition) // 0x10F06750
{
	mangled_x86(MANGLED_TODO, "?register_event_definition@c_simulation_type_collection@@QAEXW4e_simulation_event_type@@PAVc_simulation_event_definition@@@Z");
	// c_simulation_event_definition *definition;
	todo("implement");
	_sub_10F06750(this, type, definition);
}

/* ---------- private code */
