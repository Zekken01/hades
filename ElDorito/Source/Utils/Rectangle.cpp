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
	_extern bool _sub_10C5CF40(Utils::Rectangle const *const);
	bool Rectangle::IsEmpty() const // 0x10C5CF40
	{
		mangled_x86(MANGLED_TODO, "?IsEmpty@Rectangle@Utils@@QBE_NXZ");
		// Utils::Rectangle const *const this;
		todo("implement");
		bool __result = _sub_10C5CF40((Utils::Rectangle const *)this);
		return __result;
	}

	_extern bool _sub_10C5CE20(Utils::Rectangle const *const, Utils::Rectangle const &);
	bool Rectangle::Intersects(Utils::Rectangle const &other) const // 0x10C5CE20
	{
		mangled_x86(MANGLED_TODO, "?Intersects@Rectangle@Utils@@QBE_NABU12@@Z");
		// Utils::Rectangle const &other;
		// __int32 right;
		// __int32 otherBottom;
		// __int32 bottom;
		// __int32 otherRight;
		todo("implement");
		bool __result = _sub_10C5CE20((Utils::Rectangle const *)this, other);
		return __result;
	}

	extern Rectangle _sub_10C5CC20(Utils::Rectangle const *const, Utils::Rectangle const &);
	Utils::Rectangle Rectangle::Intersect(Utils::Rectangle const &other) const // 0x10C5CC20
	{
		mangled_x86(MANGLED_TODO, "?Intersect@Rectangle@Utils@@QBE?AU12@ABU12@@Z");
		// static ...; // 0x10C5CDA0
		// static ...; // 0x10C5CD98
		// Utils::Rectangle const *const this;
		// Utils::Rectangle const &other;
		// __int32 right;
		// Utils::Rectangle result;
		// __int32 bottom;
		todo("implement");
		Utils::Rectangle __result = _sub_10C5CC20((Utils::Rectangle const *)this, other);
		return __result;
	}

	extern Rectangle _sub_10C5CFA0(Utils::Rectangle const *const, __int32, __int32);
	Utils::Rectangle Rectangle::Translate(__int32 x, __int32 y) const // 0x10C5CFA0
	{
		mangled_x86(MANGLED_TODO, "?Translate@Rectangle@Utils@@QBE?AU12@HH@Z");
		// __int32 y;
		todo("implement");
		Utils::Rectangle __result = _sub_10C5CFA0((Utils::Rectangle const *)this, x, y);
		return __result;
	}

	extern Rectangle _sub_10C5CA70(Utils::Rectangle const *const, __int32, __int32, __int32, __int32);
	Utils::Rectangle Rectangle::Add(__int32 x, __int32 y, __int32 width, __int32 height) const // 0x10C5CA70
	{
		mangled_x86(MANGLED_TODO, "?Add@Rectangle@Utils@@QBE?AU12@HHHH@Z");
		// __int32 height;
		todo("implement");
		Utils::Rectangle __result = _sub_10C5CA70((Utils::Rectangle const *)this, x, y, width, height);
		return __result;
	}

	extern Rectangle _sub_10C5C850(Utils::Rectangle const *const, Utils::Rectangle const &);
	Utils::Rectangle Rectangle::Add(Utils::Rectangle const &other) const // 0x10C5C850
	{
		mangled_x86(MANGLED_TODO, "?Add@Rectangle@Utils@@QBE?AU12@ABU12@@Z");
		// static ...; // 0x10C5C9E8
		// static ...; // 0x10C5C9E0
		// Utils::Rectangle const *const this;
		// Utils::Rectangle const &other;
		// __int32 right;
		// Utils::Rectangle result;
		// __int32 bottom;
		todo("implement");
		Utils::Rectangle __result = _sub_10C5C850((Utils::Rectangle const *)this, other);
		return __result;
	}

	_extern void _sub_10C5CAF0(void *, __int32, __int32, unsigned __int32, void const *, Utils::Rectangle const &, unsigned __int32, unsigned __int32);
	void Rectangle::Copy(void *dest, __int32 destX, __int32 destY, unsigned __int32 destStride, void const *source, Utils::Rectangle const &sourceRect, unsigned __int32 sourceStride, unsigned __int32 elementSize) // 0x10C5CAF0
	{
		mangled_x86(MANGLED_TODO, "?Copy@Rectangle@Utils@@SAXPAXHHIPBXABU12@II@Z");
		// unsigned __int32 elementSize;
		// unsigned char const *srcBytes;
		// unsigned __int32 copyStride;
		// unsigned __int32 srcOffset;
		// unsigned __int32 destOffset;
		// unsigned char *destBytes;
		{
			// __int32 i;
		}
		todo("implement");
		_sub_10C5CAF0(dest, destX, destY, destStride, source, sourceRect, sourceStride, elementSize);
	}
}

/* ---------- private code */
