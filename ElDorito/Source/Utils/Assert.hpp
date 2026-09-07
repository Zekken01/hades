#ifndef __UTILS_ASSERT_HPP__
#define __UTILS_ASSERT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

namespace Utils
{
	enum FailBehavior
	{
		Halt = 0,
		Continue,
	};
}

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	extern Utils::FailBehavior ReportFailure(char const *condition, char const *msg, char const *file, char const *fnc, long line);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __UTILS_ASSERT_HPP__
