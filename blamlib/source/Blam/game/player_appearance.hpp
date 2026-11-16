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

inline bool s_player_emblem_configuration::operator==(s_player_emblem_configuration const &val) const // 0x108FC620
{
	return foregroundIndex == val.foregroundIndex && backgroundIndex == val.backgroundIndex && backgroundColor == val.backgroundColor && secondaryColor == val.secondaryColor && primaryColor == val.primaryColor && iconEnabled == val.iconEnabled && backgroundHex == val.backgroundHex && secondaryHex == val.secondaryHex && primaryHex == val.primaryHex;
}

inline bool s_player_emblem_configuration::isUninitialized() // 0x108FF880
{
	return !foregroundIndex && !backgroundIndex && !backgroundColor && !secondaryColor && !primaryColor && !iconEnabled && !backgroundHex && !secondaryHex && !primaryHex;
}

/* ---------- private code */

#endif // __BLAM_GAME_PLAYER_APPEARANCE_HPP__
