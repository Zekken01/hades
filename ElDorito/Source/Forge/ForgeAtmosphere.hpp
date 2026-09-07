#ifndef __FORGE_FORGEATMOSPHERE_HPP__
#define __FORGE_FORGEATMOSPHERE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/sky_atm/atmosphere.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"

/* ---------- forward declarations */

struct s_cluster_reference;
struct s_weighted_atmosphere_parameters;
namespace Forge
{
	class CForgeAtmosphere;
	struct ForgeMapModifierProperties;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CForgeAtmosphere
	{
	public:
		static void InitializeForNewMap();
		static void Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties);
		static void HandleMapModifierDeleted();
		static bool OverrideSkyAtmosphereSettings(s_cluster_reference cluster_reference, s_weighted_atmosphere_parameters *parameters);
	};
	static_assert(sizeof(Forge::CForgeAtmosphere) == 1, "Invalid Forge::CForgeAtmosphere size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGEATMOSPHERE_HPP__
