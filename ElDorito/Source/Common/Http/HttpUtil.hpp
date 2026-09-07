#ifndef __COMMON_HTTP_HTTPUTIL_HPP__
#define __COMMON_HTTP_HTTPUTIL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <string>
#include <string_view>

/* ---------- forward declarations */

namespace Http
{
	struct SContentRangeHeader;
}

/* ---------- constants */

/* ---------- definitions */

namespace Http
{
	struct SContentRangeHeader
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > unit; // 0x0
		unsigned char __pad0[4]; // 0x1C
		long long rangeStart; // 0x20
		long long rangeEnd; // 0x28
		long long totalSize; // 0x30
		SContentRangeHeader(Http::SContentRangeHeader &); /* compiler_generated() */
		SContentRangeHeader(Http::SContentRangeHeader const &); /* compiler_generated() */
		_inline SContentRangeHeader(); /* compiler_generated() */
		_inline ~SContentRangeHeader(); /* compiler_generated() */
		Http::SContentRangeHeader &operator=(Http::SContentRangeHeader &); /* compiler_generated() */
		Http::SContentRangeHeader &operator=(Http::SContentRangeHeader const &); /* compiler_generated() */
	};
	static_assert(sizeof(Http::SContentRangeHeader) == 56, "Invalid Http::SContentRangeHeader size");
}

/* ---------- prototypes */

namespace Http
{
	extern bool ParseSize(std::basic_string_view<char,std::char_traits<char> > s, long long &value);
	extern bool ParseContentRangeHeader(std::basic_string_view<char,std::char_traits<char> > header, Http::SContentRangeHeader &parsedHeader);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __COMMON_HTTP_HTTPUTIL_HPP__
