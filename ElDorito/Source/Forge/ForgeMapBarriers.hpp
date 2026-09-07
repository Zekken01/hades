#ifndef __FORGE_FORGEMAPBARRIERS_HPP__
#define __FORGE_FORGEMAPBARRIERS_HPP__
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
	class CForgeMapBarriers;
	struct ForgeMapModifierProperties;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CForgeMapBarriers
	{
	public:
		static void InitializeForNewMap();
		static void Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties);
		static void HandleMapModifierDeleted();
		static bool KillBarrierDisabled();
		static bool PushBarrierDisabled();
	};
	static_assert(sizeof(Forge::CForgeMapBarriers) == 1, "Invalid Forge::CForgeMapBarriers size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGEMAPBARRIERS_HPP__
