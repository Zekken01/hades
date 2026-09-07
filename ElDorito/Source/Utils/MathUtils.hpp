#ifndef __UTILS_MATHUTILS_HPP__
#define __UTILS_MATHUTILS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	namespace Math
	{
		extern float NormalizeAngle(float a);
		extern float DeltaAngle(float a, float b);
		extern float EaseOutCubic(float x);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Utils
{
	namespace Math
	{
		_extern float _sub_10AB72A0(float);
		float NormalizeAngle(float a) // 0x10AB72A0
		{
			mangled_x86(MANGLED_TODO, "?NormalizeAngle@Math@Utils@@YAMM@Z");
			// float a;
			todo("implement");
			float __result = _sub_10AB72A0(a);
			return __result;
		}

		_extern float _sub_10AB6B50(float, float);
		float DeltaAngle(float a, float b) // 0x10AB6B50
		{
			mangled_x86(MANGLED_TODO, "?DeltaAngle@Math@Utils@@YAMMM@Z");
			// float b;
			// float d;
			todo("implement");
			float __result = _sub_10AB6B50(a, b);
			return __result;
		}

		_extern float _sub_10AB6BF0(float);
		float EaseOutCubic(float x) // 0x10AB6BF0
		{
			mangled_x86(MANGLED_TODO, "?EaseOutCubic@Math@Utils@@YAMM@Z");
			// float x;
			todo("implement");
			float __result = _sub_10AB6BF0(x);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __UTILS_MATHUTILS_HPP__
