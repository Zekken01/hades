#ifndef __FORGE_FORGEWEATHER_HPP__
#define __FORGE_FORGEWEATHER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"

/* ---------- forward declarations */

namespace Forge
{
	class CForgeWeather;
	struct ForgeMapModifierProperties;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CForgeWeather
	{
	public:
		static void InitializeForNewMap();
		static void Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties);
		static bool UpdateWeatherEffects();
		static void HandleMapModifierDeleted();
	};
	static_assert(sizeof(Forge::CForgeWeather) == 1, "Invalid Forge::CForgeWeather size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGEWEATHER_HPP__
