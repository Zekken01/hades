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
		float NormalizeAngle(float a) // 0x10AB72A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?NormalizeAngle@Math@Utils@@YAMM@Z");

			a = fmodf(a, 360.0f);
			a = fmodf(a + 360.0f, 360.0f);
			if (a > 180.0f)
				a -= 360.0f;
			return a;
		}

		float DeltaAngle(float a, float b) // 0x10AB6B50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?DeltaAngle@Math@Utils@@YAMMM@Z");

			float d = Utils::Math::NormalizeAngle(a - b);
			if (180.0f >= d)
				return d;
			else
				return d - 360.0f;
		}

		float EaseOutCubic(float x) // 0x10AB6BF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?EaseOutCubic@Math@Utils@@YAMM@Z");

			return (float)(1.0 - pow(1.0f - x, 3));
		}
	}
}

/* ---------- private code */

#endif // __UTILS_MATHUTILS_HPP__
