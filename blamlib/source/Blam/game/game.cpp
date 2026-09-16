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
	// e_game_mode mode;

	if (mode < 0 || mode >= 6)
	{
		return "unknown";
	}

	return k_game_mode_names[mode];
}

/* ---------- private code */
