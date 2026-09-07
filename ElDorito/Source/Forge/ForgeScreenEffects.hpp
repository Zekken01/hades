#ifndef __FORGE_FORGESCREENEFFECTS_HPP__
#define __FORGE_FORGESCREENEFFECTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Forge/Geoemetry.hpp"

/* ---------- forward declarations */

struct s_single_screen_effect_definition;
namespace Forge
{
	struct CForgeScreenEffects;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	struct CForgeScreenEffects
	{
		static void ApplyScreenEffectOverride(long output_user_index, long datum_index, s_single_screen_effect_definition *definition);
	};
	static_assert(sizeof(Forge::CForgeScreenEffects) == 1, "Invalid Forge::CForgeScreenEffects size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGESCREENEFFECTS_HPP__
