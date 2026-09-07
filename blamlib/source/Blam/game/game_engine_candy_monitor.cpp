/* ---------- headers */

#include "Blam/game/game_engine_candy_monitor.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/memory/tls.hpp"

/* ---------- forward declarations */

struct c_candy_monitor_manager;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern c_candy_monitor_manager *get_candy_monitor_manager();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_candy_monitor_manager *_sub_10F03560();
c_candy_monitor_manager *get_candy_monitor_manager() // 0x10F03560
{
	mangled_x86(MANGLED_TODO, "?get_candy_monitor_manager@@YAPAUc_candy_monitor_manager@@XZ");
	// procedure flags: nofpo
	todo("implement");
	c_candy_monitor_manager * __result = _sub_10F03560();
	return __result;
}

/* ---------- private code */
