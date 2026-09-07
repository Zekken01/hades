/* ---------- headers */

#include "Blam/scenario/scenario.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>

/* ---------- forward declarations */

struct s_scenario;
struct s_scenario_structure_bsp;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern long scenario_pvs_bsp_pvs_index_get(unsigned long bsp_zone_flags, long bsp_index);

/* ---------- globals */

extern s_scenario **g_scenario_definition; // 0x11359564
extern s_scenario_structure_bsp *(*const global_structure_bsp_get)(long); // 0x11248AD4
extern long (*const global_structure_bsp_first_active_index_get)(); // 0x11248ACC
extern long (*const global_structure_bsp_next_active_index_get)(long); // 0x11248AD0

/* ---------- private variables */

/* ---------- public code */

_extern long _sub_10EFC310(unsigned long, long);
long scenario_pvs_bsp_pvs_index_get(unsigned long bsp_zone_flags, long bsp_index) // 0x10EFC310
{
	mangled_x86(MANGLED_TODO, "?scenario_pvs_bsp_pvs_index_get@@YAJKJ@Z");
	// long bsp_index;
	// unsigned long mask;
	todo("implement");
	long __result = _sub_10EFC310(bsp_zone_flags, bsp_index);
	return __result;
}

/* ---------- private code */
