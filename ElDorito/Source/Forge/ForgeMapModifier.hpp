#ifndef __FORGE_FORGEMAPMODIFIER_HPP__
#define __FORGE_FORGEMAPMODIFIER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"

/* ---------- forward declarations */

namespace Forge
{
	class CForgeMapModifier;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CForgeMapModifier
	{
	public:
		static void InitializeForNewMap();
		static void Update();
		static void OnUndoRedoCompleted();
		static long GetOrCreateMapModifierObject();
	};
	static_assert(sizeof(Forge::CForgeMapModifier) == 1, "Invalid Forge::CForgeMapModifier size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGEMAPMODIFIER_HPP__
