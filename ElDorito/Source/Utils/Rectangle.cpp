/* ---------- headers */

#include "Utils/Rectangle.hpp"
#include "hades/hades.h"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

namespace Utils
{
	struct Rectangle;
}

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	bool Rectangle::IsEmpty() const // 0x10C5CF40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsEmpty@Rectangle@Utils@@QBE_NXZ");

		return Width == 0 || Height == 0;
	}

	bool Rectangle::Intersects(Utils::Rectangle const &other) const // 0x10C5CE20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Intersects@Rectangle@Utils@@QBE_NABU12@@Z");

		if (IsEmpty() || other.IsEmpty())
		{
			return false;
		}

		int right = X + Width;
		int bottom = Y + Height;
		int otherRight = other.X + other.Width;
		int otherBottom = other.Y + other.Height;

		return X < otherRight && right > other.X && Y < otherBottom && bottom > other.Y;
	}

	Utils::Rectangle Rectangle::Intersect(Utils::Rectangle const &other) const // 0x10C5CC20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Intersect@Rectangle@Utils@@QBE?AU12@ABU12@@Z");

		if (IsEmpty() || other.IsEmpty())
			return Utils::Rectangle();

		Utils::Rectangle result;
		result.X = std::max(X, other.X);
		result.Y = std::max(Y, other.Y);
		__int32 right = std::min(X + Width, other.X + other.Width);
		__int32 bottom = std::min(Y + Height, other.Y + other.Height);
		if (right <= result.X || bottom <= result.Y)
			return Utils::Rectangle();

		result.Width = right - result.X;
		result.Height = bottom - result.Y;
		return result;
	}

	Utils::Rectangle Rectangle::Translate(__int32 x, __int32 y) const // 0x10C5CFA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Translate@Rectangle@Utils@@QBE?AU12@HH@Z");

		return Rectangle(X + x, Y + y, Width, Height);
	}

	Utils::Rectangle Rectangle::Add(__int32 x, __int32 y, __int32 width, __int32 height) const // 0x10C5CA70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Add@Rectangle@Utils@@QBE?AU12@HHHH@Z");

		return Add(Utils::Rectangle(x, y, width, height));
	}

	Utils::Rectangle Rectangle::Add(Utils::Rectangle const &other) const // 0x10C5C850
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Add@Rectangle@Utils@@QBE?AU12@ABU12@@Z");

		if (IsEmpty())
			return other;
		if (other.IsEmpty())
			return *this;

		Utils::Rectangle result;
		result.X = std::min(X, other.X);
		result.Y = std::min(Y, other.Y);
		__int32 right = std::max(X + Width, other.X + other.Width);
		__int32 bottom = std::max(Y + Height, other.Y + other.Height);
		result.Width = right - result.X;
		result.Height = bottom - result.Y;
		return result;
	}

	void Rectangle::Copy(void *dest, __int32 destX, __int32 destY, unsigned __int32 destStride, void const *source, Utils::Rectangle const &sourceRect, unsigned __int32 sourceStride, unsigned __int32 elementSize) // 0x10C5CAF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Copy@Rectangle@Utils@@SAXPAXHHIPBXABU12@II@Z");

		unsigned __int32 srcOffset = sourceStride * sourceRect.Y + sourceRect.X * elementSize;
		unsigned __int32 destOffset = destStride * destY + destX * elementSize;
		unsigned char const *srcBytes = (unsigned char const *)source + srcOffset;
		unsigned char *destBytes = (unsigned char *)dest + destOffset;
		unsigned __int32 copyStride = sourceRect.Width * elementSize;
		if (destStride == sourceStride && destStride == copyStride)
		{
			memcpy(destBytes, srcBytes, copyStride * sourceRect.Height);
		}
		else
		{
			for (__int32 i = 0; i < sourceRect.Height; i++)
			{
				memcpy(destBytes, srcBytes, copyStride);
				srcBytes += sourceStride;
				destBytes += destStride;
			}
		}
	}
}

/* ---------- private code */
