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
			std::string_view scheme; // 0x0
			std::string_view authority; // 0x8
			std::string_view path; // 0x10
			std::string_view query; // 0x18
			std::string_view fragment; // 0x20
			_inline UriComponents() = default; /* compiler_generated() */
		};
		static_assert(sizeof(Utils::Uri::UriComponents) == 40, "Invalid Utils::Uri::UriComponents size");
	}
}

/* ---------- prototypes */

namespace Utils
{
	namespace Uri
	{
		extern bool ParseUriComponents(std::string_view uri, Utils::Uri::UriComponents &components);
		extern bool ResolveUrl(std::string const &baseUri, std::string const &relativeUri, std::string &result);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __UTILS_URI_HPP__
