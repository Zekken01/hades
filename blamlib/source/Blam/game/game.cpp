/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern char const *game_mode_get_string(e_game_mode mode);

/* ---------- globals */

extern bool (*const game_is_multiplayer)(); // 0x11248DCC
extern bool (*const game_is_server)(); // 0x11248DD0
extern bool (*const game_is_distributed)(); // 0x11248DD4
extern char const *k_game_mode_names[6]; // 0x11359720

/* ---------- private variables */

/* ---------- public code */

char const *game_mode_get_string(e_game_mode mode) // 0x10F00470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_mode_get_string@@YAPBDW4e_game_mode@@@Z");

	if (mode < 0 || mode >= 6)
	{
		return "unknown";
	}

	return k_game_mode_names[mode];
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
bool (*const game_is_multiplayer)() = reinterpret_cast<decltype(game_is_multiplayer)>(0x531C00);
bool (*const game_is_server)() = reinterpret_cast<decltype(game_is_server)>(0x531DA0);
bool (*const game_is_distributed)() = reinterpret_cast<decltype(game_is_distributed)>(0x531AF0);

char const *k_game_mode_names[6] = { "none", "campaign", "multiplayer", "mainmenu", "theater", "shared" };
