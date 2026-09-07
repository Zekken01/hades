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
	extern _inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > FormatCommandLine(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > args);
}

/* ---------- globals */

/* ---------- public code */

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10981810(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > >);
namespace Utils
{
	_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > FormatCommandLine(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > args) // 0x10981810
	{
		mangled_x86(MANGLED_TODO, "?FormatCommandLine@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@3@@Z");
		// static ...; // 0x10981A68
		// static ...; // 0x10981A5C
		// static ...; // 0x10981A54
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > args;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		// bool first;
		{
			// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &arg;
				{
					// bool hasNonSpace;
					// bool hasSpace;
					{
						// char const *<end>$L1;
						// char const *<begin>$L1;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &<range>$L1;
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
