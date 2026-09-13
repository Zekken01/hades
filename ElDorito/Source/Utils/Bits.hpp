#ifndef __UTILS_BITS_HPP__
#define __UTILS_BITS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

/* ---------- definitions */

namespace Utils
{
	namespace Bits
{
		template<typename t_arg0>
		__int32 CountBits(t_arg0 val);
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

template<typename t_arg0>
__int32 Utils::Bits::CountBits(t_arg0 val)
{
	mangled_prefix_assert("??$CountBits@");

	__int32 count = 0;

	while (val)
	{
		val >>= 1;
		count++;
	}

	return count;
}

/* ---------- private code */

#endif // __UTILS_BITS_HPP__
