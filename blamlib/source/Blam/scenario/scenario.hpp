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

extern long scenario_pvs_bsp_pvs_index_get(unsigned long bsp_zone_flags, long bsp_index);

extern _inline s_scenario *global_scenario_get();

/* ---------- globals */

/* ---------- public code */

extern s_scenario *_sub_1067F5D0();
_inline s_scenario *global_scenario_get() // 0x1067F5D0
{
	mangled_x86(MANGLED_TODO, "?global_scenario_get@@YAPAUs_scenario@@XZ");
	// procedure flags: nofpo
	todo("implement");
	s_scenario * __result = _sub_1067F5D0();
	return __result;
}

/* ---------- private code */

#endif // __BLAM_SCENARIO_SCENARIO_HPP__
