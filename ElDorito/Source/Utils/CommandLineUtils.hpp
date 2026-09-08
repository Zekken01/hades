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

extern std::string _sub_10981810(std::vector<std::string>);
namespace Utils
{
	_inline std::string FormatCommandLine(std::vector<std::string> args) // 0x10981810
	{
		mangled_x86(MANGLED_TODO, "?FormatCommandLine@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@3@@Z");
		// static ...; // 0x10981A68
		// static ...; // 0x10981A5C
		// static ...; // 0x10981A54
		// std::vector<std::string> args;
		// std::stringstream ss;
		// bool first;
		{
			// std::vector<std::string> &<range>$L0;
			// std::string *<begin>$L0;
			// std::string *<end>$L0;
			{
				// std::string const &arg;
				{
					// bool hasNonSpace;
					// bool hasSpace;
					{
						// char const *<end>$L1;
						// char const *<begin>$L1;
						// std::string const &<range>$L1;
						{
							// char c;
						}
					}
				}
			}
		}
		todo("implement");
		std::string __result = _sub_10981810(args);
		return __result;
	}
}

/* ---------- private code */

#endif // __UTILS_COMMANDLINEUTILS_HPP__
