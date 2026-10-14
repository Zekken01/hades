#ifndef __UTILS_MACROS_HPP__
#define __UTILS_MACROS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	template<typename T>
	T Clamp(T n, T low, T high)
	{
		return n >= high ? high : n <= low ? low : n;
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __UTILS_MACROS_HPP__
