#ifndef __FORGE_FORGECAMERAFX_HPP__
#define __FORGE_FORGECAMERAFX_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/render/views/render_player_view.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"

/* ---------- forward declarations */

struct c_player_view;
namespace Forge
{
	class CForgeCameraFx;
	struct ForgeMapModifierProperties;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CForgeCameraFx
	{
	public:
		static void InitializeForNewMap();
		static void Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties);
		static void HandleMapModifierDeleted();
		static void OverrideCameraFxSettings(c_player_view *player_view, float exposure_boost);
		static bool IsActive();
		static float GetBloomIntensity();
	};
	static_assert(sizeof(Forge::CForgeCameraFx) == 1, "Invalid Forge::CForgeCameraFx size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGECAMERAFX_HPP__
