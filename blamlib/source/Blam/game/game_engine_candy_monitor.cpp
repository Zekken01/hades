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

void *tls_get(unsigned long index);  // hades: added for 0X10F03560

extern c_candy_monitor_manager *get_candy_monitor_manager();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_candy_monitor_manager *get_candy_monitor_manager() // 0x10F03560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_candy_monitor_manager@@YAPAUc_candy_monitor_manager@@XZ");

	return (c_candy_monitor_manager *)offset_pointer(*(void **)tls_get(72), 66972);
}

/* ---------- private code */
