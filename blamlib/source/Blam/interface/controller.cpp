/* ---------- headers */

#include "Blam/interface/controller.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/interface/player_profile.hpp"

/* ---------- forward declarations */

class c_controller_interface;
class c_player_profile_interface;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void *offset_pointer(void *pointer, long offset);  // hades: added for 0x10F18BB0

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_player_profile_interface *c_controller_interface::get_player_profile_interface() // 0x10F18BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_profile_interface@c_controller_interface@@QAEPAVc_player_profile_interface@@XZ");
	// c_controller_interface *const this;

	return (c_player_profile_interface *)offset_pointer(this, 8);
}

/* ---------- private code */
