#ifndef __FORGE_OBJECTPROPERTIES_FORGEPROPERTYVALUE_HPP__
#define __FORGE_OBJECTPROPERTIES_FORGEPROPERTYVALUE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyDefinitions.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Forge
{
	struct SPropertyValue;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	struct SPropertyValue
	{
		Forge::EPropertyValueType type; // 0x0
		union
		{
			float realValue; // 0x4
			__int32 intValue; // 0x4
		};
		_inline SPropertyValue(float val);
		_inline SPropertyValue(__int32 val);
		_inline SPropertyValue();
		static _inline Forge::SPropertyValue Integer(__int32 val);
		static _inline Forge::SPropertyValue Real(float val);
		std::string ToString();
	};
	static_assert(sizeof(Forge::SPropertyValue) == 8, "Invalid Forge::SPropertyValue size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Forge
{
	_inline SPropertyValue::SPropertyValue() // 0x1083AE40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SPropertyValue@Forge@@QAE@XZ");
		// Forge::SPropertyValue *const this;

		type = (Forge::EPropertyValueType)0xFFFFFFFF;
	}

	_inline SPropertyValue::SPropertyValue(__int32 val) // 0x1083ADC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SPropertyValue@Forge@@QAE@H@Z");
		// __int32 val;

		type = Forge::Integer;
		intValue = val;
	}

	_inline SPropertyValue::SPropertyValue(float val) // 0x1083AE00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SPropertyValue@Forge@@QAE@M@Z");
		// float val;

		type = Forge::Real;
		realValue = val;
	}

	_inline Forge::SPropertyValue SPropertyValue::Integer(__int32 val) // 0x1083E830
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Integer@SPropertyValue@Forge@@SA?AU12@H@Z");
		// __int32 val;

		return SPropertyValue(val);
	}

	_inline Forge::SPropertyValue SPropertyValue::Real(float val) // 0x1083E880
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Real@SPropertyValue@Forge@@SA?AU12@M@Z");
		// float val;

		return SPropertyValue(val);
	}
}

/* ---------- private code */

#endif // __FORGE_OBJECTPROPERTIES_FORGEPROPERTYVALUE_HPP__
