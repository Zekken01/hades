#ifndef __BLAM_GAME_PLAYER_CONFIGURATION_INL__
#define __BLAM_GAME_PLAYER_CONFIGURATION_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/player_configuration.hpp"

/* ---------- forward declarations */

struct s_player_identifier;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern _inline bool operator==(s_player_identifier const &a, s_player_identifier const &b);

/* ---------- globals */

/* ---------- public code */

_extern bool _sub_106CE000(s_player_identifier const &, s_player_identifier const &);
_inline bool operator==(s_player_identifier const &a, s_player_identifier const &b) // 0x106CE000
{
	mangled_x86(MANGLED_TODO, "??8@YA_NABUs_player_identifier@@0@Z");
	// s_player_identifier const &b;
	todo("implement");
	bool __result = _sub_106CE000(a, b);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_GAME_PLAYER_CONFIGURATION_INL__
