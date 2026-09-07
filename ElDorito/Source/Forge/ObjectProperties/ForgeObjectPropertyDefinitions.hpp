#ifndef __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYDEFINITIONS_HPP__
#define __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYDEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"

/* ---------- forward declarations */

namespace Forge
{
	struct SPropertyDefinition;
}

/* ---------- constants */

namespace Forge
{
	enum EPropertyValueType
	{
		Invalid = -1,
		Integer = 0,
		Real,
		ColorRGB,
	};
}

/* ---------- definitions */

namespace Forge
{
	struct SPropertyDefinition
	{
		char const *name; // 0x0
		Forge::EObjectProperty property; // 0x4
		Forge::EPropertyValueType valueType; // 0x8
	};
	static_assert(sizeof(Forge::SPropertyDefinition) == 12, "Invalid Forge::SPropertyDefinition size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_OBJECTPROPERTIES_FORGEOBJECTPROPERTYDEFINITIONS_HPP__
