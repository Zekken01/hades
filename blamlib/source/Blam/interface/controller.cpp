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

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_player_profile_interface *_sub_10F18BB0(c_controller_interface *const);
c_player_profile_interface *c_controller_interface::get_player_profile_interface() // 0x10F18BB0
{
	mangled_x86(MANGLED_TODO, "?get_player_profile_interface@c_controller_interface@@QAEPAVc_player_profile_interface@@XZ");
	// c_controller_interface *const this;
	todo("implement");
	c_player_profile_interface * __result = _sub_10F18BB0(this);
	return __result;
}

/* ---------- private code */
