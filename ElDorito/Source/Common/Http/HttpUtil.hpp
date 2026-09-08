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
		std::string unit; // 0x0
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
	extern bool ParseSize(std::string_view s, long long &value);
	extern bool ParseContentRangeHeader(std::string_view header, Http::SContentRangeHeader &parsedHeader);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __COMMON_HTTP_HTTPUTIL_HPP__
