#ifndef __UTILS_COMMANDLINEUTILS_HPP__
#define __UTILS_COMMANDLINEUTILS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	extern _inline std::string FormatCommandLine(std::vector<std::string> args);
}

/* ---------- globals */

/* ---------- public code */


namespace Utils
{
	_inline std::string FormatCommandLine(std::vector<std::string> args) // 0x10981810
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FormatCommandLine@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@3@@Z");

		std::stringstream ss;
		bool first = true;
		for (std::string const &arg : args)
		{
			bool hasNonSpace = false;
			bool hasSpace = false;
			for (char c : arg)
			{
				if (isspace(c))
					hasSpace = true;
				else
					hasNonSpace = true;
			}
			if (!hasNonSpace)
				continue;
			if (!first)
				ss << ' ';
			first = false;
			if (hasSpace)
				ss << '"';
			ss << arg;
			if (hasSpace)
				ss << '"';
		}
		return ss.str();
	}
}

/* ---------- private code */

#endif // __UTILS_COMMANDLINEUTILS_HPP__
