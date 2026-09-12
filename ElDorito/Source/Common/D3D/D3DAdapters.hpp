#ifndef __COMMON_D3D_D3DADAPTERS_HPP__
#define __COMMON_D3D_D3DADAPTERS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"

#include <memory>
#include <vector>

/* ---------- forward declarations */

namespace Common
{
	namespace D3DAdapters
	{
		struct DisplayMode;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Common
{
	namespace D3DAdapters
	{
		struct DisplayMode
		{
			__int32 width; // 0x0
			__int32 height; // 0x4
			__int32 adapterIndex; // 0x8
		};
		static_assert(sizeof(Common::D3DAdapters::DisplayMode) == 12, "Invalid Common::D3DAdapters::DisplayMode size");
	}
}

/* ---------- prototypes */

namespace Common
{
	namespace D3DAdapters
	{
		extern void EnumerateDisplayModes();
		extern std::vector<Common::D3DAdapters::DisplayMode> const &GetAdapterDisplayModes(__int32 adapterIndex);
		extern Common::D3DAdapters::DisplayMode GetClosestSupportedDisplayMode(__int32 preferredWidth, __int32 preferredHeight);
		extern __int32 GetCurrentAdapterIndex();

		extern _inline bool operator<(Common::D3DAdapters::DisplayMode const &lhs, Common::D3DAdapters::DisplayMode const &rhs);
		extern _inline bool operator==(Common::D3DAdapters::DisplayMode const &lhs, Common::D3DAdapters::DisplayMode const &rhs);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Common
{
	namespace D3DAdapters
	{
		_inline bool operator<(Common::D3DAdapters::DisplayMode const &lhs, Common::D3DAdapters::DisplayMode const &rhs) // 0x10687350
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??MD3DAdapters@Common@@YA_NABUDisplayMode@01@0@Z");
			// Common::D3DAdapters::DisplayMode const &rhs;

			if (lhs.adapterIndex != rhs.adapterIndex)
				return lhs.adapterIndex < rhs.adapterIndex;

			if (lhs.width != rhs.width)
				return lhs.width < rhs.width;

			return lhs.height < rhs.height;
		}

		_inline bool operator==(Common::D3DAdapters::DisplayMode const &lhs, Common::D3DAdapters::DisplayMode const &rhs) // 0x10687070
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??8D3DAdapters@Common@@YA_NABUDisplayMode@01@0@Z");
			// Common::D3DAdapters::DisplayMode const &rhs;

			return lhs.adapterIndex == rhs.adapterIndex && lhs.width == rhs.width && lhs.height == rhs.height;
		}
	}
}

/* ---------- private code */

#endif // __COMMON_D3D_D3DADAPTERS_HPP__
