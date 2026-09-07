#ifndef __WEB_WEBRENDERERSHADER_HPP__
#define __WEB_WEBRENDERERSHADER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

namespace Web
{
	namespace Browser
	{
		struct SCefScreenVertex;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		struct SCefScreenVertex
		{
			D3DXVECTOR2 position; // 0x0
			D3DXVECTOR2 texcoord; // 0x8
			SCefScreenVertex(); /* compiler_generated() */
		};
		static_assert(sizeof(Web::Browser::SCefScreenVertex) == 16, "Invalid Web::Browser::SCefScreenVertex size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_WEBRENDERERSHADER_HPP__
