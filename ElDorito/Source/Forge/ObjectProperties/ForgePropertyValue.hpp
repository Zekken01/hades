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
	extern SPropertyValue* _sub_1083AE40(Forge::SPropertyValue *const);
	_inline SPropertyValue::SPropertyValue() // 0x1083AE40
	{
		mangled_x86(MANGLED_TODO, "??0SPropertyValue@Forge@@QAE@XZ");
		// Forge::SPropertyValue *const this;
		todo("implement");
		_sub_1083AE40(this);
	}

	extern SPropertyValue* _sub_1083ADC0(Forge::SPropertyValue *const, __int32);
	_inline SPropertyValue::SPropertyValue(__int32 val) // 0x1083ADC0
	{
		mangled_x86(MANGLED_TODO, "??0SPropertyValue@Forge@@QAE@H@Z");
		// __int32 val;
		todo("implement");
		_sub_1083ADC0(this, val);
	}

	extern SPropertyValue* _sub_1083AE00(Forge::SPropertyValue *const, float);
	_inline SPropertyValue::SPropertyValue(float val) // 0x1083AE00
	{
		mangled_x86(MANGLED_TODO, "??0SPropertyValue@Forge@@QAE@M@Z");
		// float val;
		todo("implement");
		_sub_1083AE00(this, val);
	}

	extern SPropertyValue _sub_1083E830(__int32);
	_inline Forge::SPropertyValue SPropertyValue::Integer(__int32 val) // 0x1083E830
	{
		mangled_x86(MANGLED_TODO, "?Integer@SPropertyValue@Forge@@SA?AU12@H@Z");
		// __int32 val;
		todo("implement");
		Forge::SPropertyValue __result = _sub_1083E830(val);
		return __result;
	}

	extern SPropertyValue _sub_1083E880(float);
	_inline Forge::SPropertyValue SPropertyValue::Real(float val) // 0x1083E880
	{
		mangled_x86(MANGLED_TODO, "?Real@SPropertyValue@Forge@@SA?AU12@M@Z");
		// float val;
		todo("implement");
		Forge::SPropertyValue __result = _sub_1083E880(val);
		return __result;
	}
}

/* ---------- private code */

#endif // __FORGE_OBJECTPROPERTIES_FORGEPROPERTYVALUE_HPP__
