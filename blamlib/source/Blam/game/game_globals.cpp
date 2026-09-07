/* ---------- headers */

#include "Blam/game/game_globals.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_game_globals;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_game_globals *game_globals_get();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

s_game_globals *game_globals_get() // 0x10F005C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_globals_get@@YAPAUs_game_globals@@XZ");
	// procedure flags: nofpo

	return *reinterpret_cast<s_game_globals **>(0x22AAEB8);
}

/* ---------- private code */
