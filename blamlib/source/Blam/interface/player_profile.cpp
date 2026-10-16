/* ---------- headers */

#include "Blam/interface/player_profile.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_player_profile_interface;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const c_player_profile_interface_set_last_campaign_played_time = reinterpret_cast<void(__thiscall *)(c_player_profile_interface *, long, unsigned long long, bool)>(0xAA31F0);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void c_player_profile_interface::set_last_campaign_played_time(long campaign_game_mode, unsigned long long time, bool unused) // 0x10F18C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_last_campaign_played_time@c_player_profile_interface@@QAEXJ_K_N@Z");

	eldorado::c_player_profile_interface_set_last_campaign_played_time(this, campaign_game_mode, time, unused);
}

/* ---------- private code */
