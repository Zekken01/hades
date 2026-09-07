#ifndef __FORGE_FORGESKIES_HPP__
#define __FORGE_FORGESKIES_HPP__
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
	class CForgeSkies;
	struct ForgeMapModifierProperties;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CForgeSkies
	{
	public:
		static bool IsActive();
		static void InitializeForNewMap();
		static void Update(long modifierObjectIndex, Forge::ForgeMapModifierProperties &mapModifierProperties);
		static void HandleMapModifierDeleted();
	};
	static_assert(sizeof(Forge::CForgeSkies) == 1, "Invalid Forge::CForgeSkies size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGESKIES_HPP__
