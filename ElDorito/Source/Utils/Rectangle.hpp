#ifndef __UTILS_RECTANGLE_HPP__
#define __UTILS_RECTANGLE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

namespace Utils
{
	struct Rectangle;
}

/* ---------- constants */

/* ---------- definitions */

namespace Utils
{
	struct Rectangle
	{
		_inline Rectangle(__int32 x, __int32 y, __int32 width, __int32 height);
		_inline Rectangle();
		__int32 X; // 0x0
		__int32 Y; // 0x4
		__int32 Width; // 0x8
		__int32 Height; // 0xC
		bool IsEmpty() const;
		bool Intersects(Utils::Rectangle const &other) const;
		Utils::Rectangle Intersect(Utils::Rectangle const &other) const;
		Utils::Rectangle Translate(__int32 x, __int32 y) const;
		Utils::Rectangle Add(Utils::Rectangle const &other) const;
		Utils::Rectangle Add(__int32 x, __int32 y, __int32 width, __int32 height) const;
		static void Copy(void *dest, __int32 destX, __int32 destY, unsigned __int32 destStride, void const *source, Utils::Rectangle const &sourceRect, unsigned __int32 sourceStride, unsigned __int32 elementSize);
		_inline bool operator==(Utils::Rectangle const &other) const;
	};
	static_assert(sizeof(Utils::Rectangle) == 16, "Invalid Utils::Rectangle size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Utils
{
	extern Rectangle* _sub_10C5C800(Utils::Rectangle *const);
	_inline Rectangle::Rectangle() // 0x10C5C800
	{
		mangled_x86(MANGLED_TODO, "??0Rectangle@Utils@@QAE@XZ");
		// Utils::Rectangle *const this;
		todo("implement");
		_sub_10C5C800(this);
	}

	extern Rectangle* _sub_10C5C7B0(Utils::Rectangle *const, __int32, __int32, __int32, __int32);
	_inline Rectangle::Rectangle(__int32 x, __int32 y, __int32 width, __int32 height) // 0x10C5C7B0
	{
		mangled_x86(MANGLED_TODO, "??0Rectangle@Utils@@QAE@HHHH@Z");
		// __int32 height;
		todo("implement");
		_sub_10C5C7B0(this, x, y, width, height);
	}

	_extern bool _sub_10CEB160(Utils::Rectangle const *const, Utils::Rectangle const &);
	_inline bool Rectangle::operator==(Utils::Rectangle const &other) const // 0x10CEB160
	{
		mangled_x86(MANGLED_TODO, "??8Rectangle@Utils@@QBE_NABU01@@Z");
		// Utils::Rectangle const &other;
		todo("implement");
		bool __result = _sub_10CEB160((Utils::Rectangle const *)this, other);
		return __result;
	}
}

/* ---------- private code */

#endif // __UTILS_RECTANGLE_HPP__
