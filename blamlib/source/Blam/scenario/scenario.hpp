#ifndef __BLAM_SCENARIO_SCENARIO_HPP__
#define __BLAM_SCENARIO_SCENARIO_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/scenario/scenario_definitions.hpp"

/* ---------- forward declarations */

struct s_scenario;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_scenario **g_scenario_definition;  // hades: added for 0x1067F5D0

extern long scenario_pvs_bsp_pvs_index_get(unsigned long bsp_zone_flags, long bsp_index);

extern _inline s_scenario *global_scenario_get();

/* ---------- globals */

/* ---------- public code */

_inline s_scenario *global_scenario_get() // 0x1067F5D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?global_scenario_get@@YAPAUs_scenario@@XZ");
	// procedure flags: nofpo

	return *g_scenario_definition;
}

/* ---------- private code */

#endif // __BLAM_SCENARIO_SCENARIO_HPP__
