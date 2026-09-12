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

void c_player_profile_interface::set_last_campaign_played_time(long campaign_game_mode, unsigned long long time, bool unused) // 0x10F18C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_last_campaign_played_time@c_player_profile_interface@@QAEXJ_K_N@Z");
	// bool unused;
	// function call : void (*)(c_player_profile_interface *, long, unsigned long long, bool)

	((void(__thiscall *const)(c_player_profile_interface *, long, unsigned long long, bool))0xaa31f0)(this, campaign_game_mode, time, unused);
}

/* ---------- private code */
