#ifndef __UTILS_URI_HPP__
#define __UTILS_URI_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <string>
#include <string_view>

/* ---------- forward declarations */

namespace Utils
{
	namespace Uri
	{
		struct UriComponents;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Utils
{
	namespace Uri
	{
		struct UriComponents
		{
			std::basic_string_view<char,std::char_traits<char> > scheme; // 0x0
			std::basic_string_view<char,std::char_traits<char> > authority; // 0x8
			std::basic_string_view<char,std::char_traits<char> > path; // 0x10
			std::basic_string_view<char,std::char_traits<char> > query; // 0x18
			std::basic_string_view<char,std::char_traits<char> > fragment; // 0x20
			_inline UriComponents(); /* compiler_generated() */
		};
		static_assert(sizeof(Utils::Uri::UriComponents) == 40, "Invalid Utils::Uri::UriComponents size");
	}
}

/* ---------- prototypes */

namespace Utils
{
	namespace Uri
	{
		extern bool ParseUriComponents(std::basic_string_view<char,std::char_traits<char> > uri, Utils::Uri::UriComponents &components);
		extern bool ResolveUrl(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &baseUri, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &relativeUri, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &result);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __UTILS_URI_HPP__
