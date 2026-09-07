#ifndef __DEBUG_DEBUGTRACE_HPP__
#define __DEBUG_DEBUGTRACE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"

/* ---------- forward declarations */

class CDebugTrace;

/* ---------- constants */

/* ---------- definitions */

class CDebugTrace
{
public:
	static void Trace(__int32 color, char const *format, ...);
	static void Render();
};
static_assert(sizeof(CDebugTrace) == 1, "Invalid CDebugTrace size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __DEBUG_DEBUGTRACE_HPP__
