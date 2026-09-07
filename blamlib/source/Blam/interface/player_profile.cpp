/* ---------- headers */

#include "Blam/interface/player_profile.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_player_profile_interface;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F18C10(c_player_profile_interface *const, long, unsigned long long, bool);
void c_player_profile_interface::set_last_campaign_played_time(long campaign_game_mode, unsigned long long time, bool unused) // 0x10F18C10
{
	mangled_x86(MANGLED_TODO, "?set_last_campaign_played_time@c_player_profile_interface@@QAEXJ_K_N@Z");
	// bool unused;
	// function call : void (*)(c_player_profile_interface *, long, unsigned long long, bool)
	todo("implement");
	_sub_10F18C10(this, campaign_game_mode, time, unused);
}

/* ---------- private code */
