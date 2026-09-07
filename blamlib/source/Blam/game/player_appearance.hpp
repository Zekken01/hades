#ifndef __BLAM_GAME_PLAYER_APPEARANCE_HPP__
#define __BLAM_GAME_PLAYER_APPEARANCE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

/* ---------- definitions */

// s_player_character_customiztion is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_player_emblem_configuration is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern bool _sub_108FC620(s_player_emblem_configuration const *const, s_player_emblem_configuration const &);
_inline bool s_player_emblem_configuration::operator==(s_player_emblem_configuration const &val) const // 0x108FC620
{
	mangled_x86(MANGLED_TODO, "??8s_player_emblem_configuration@@QBE_NABU0@@Z");
	// s_player_emblem_configuration const &val;
	todo("implement");
	bool __result = _sub_108FC620((s_player_emblem_configuration const *)this, val);
	return __result;
}

_extern bool _sub_108FF880(s_player_emblem_configuration *const);
_inline bool s_player_emblem_configuration::isUninitialized() // 0x108FF880
{
	mangled_x86(MANGLED_TODO, "?isUninitialized@s_player_emblem_configuration@@QAE_NXZ");
	// s_player_emblem_configuration *const this;
	todo("implement");
	bool __result = _sub_108FF880(this);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_GAME_PLAYER_APPEARANCE_HPP__
