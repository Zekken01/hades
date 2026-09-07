#ifndef __FORGE_OBJECTSET_HPP__
#define __FORGE_OBJECTSET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"

#include <bitset>

/* ---------- forward declarations */

namespace Forge
{
	class ObjectSet;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class ObjectSet
	{
	public:
		_inline bool Contains(long objectIndex) const;
		__int32 Count() const;
		_inline bool Any() const;
		_inline void Add(long objectIndex);
		_inline void Remove(long objectIndex);
		_inline void Clear();
	private:
		std::bitset<2048> m_Bits; // 0x0
	public:
		_inline ObjectSet(); /* compiler_generated() */
	};
	static_assert(sizeof(Forge::ObjectSet) == 256, "Invalid Forge::ObjectSet size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Forge
{
	_extern bool _sub_10838010(Forge::ObjectSet const *const, long);
	_inline bool ObjectSet::Contains(long objectIndex) const // 0x10838010
	{
		mangled_x86(MANGLED_TODO, "?Contains@ObjectSet@Forge@@QBE_NJ@Z");
		// long objectIndex;
		todo("implement");
		bool __result = _sub_10838010((Forge::ObjectSet const *)this, objectIndex);
		return __result;
	}

	_extern bool _sub_10973B60(Forge::ObjectSet const *const);
	_inline bool ObjectSet::Any() const // 0x10973B60
	{
		mangled_x86(MANGLED_TODO, "?Any@ObjectSet@Forge@@QBE_NXZ");
		// Forge::ObjectSet const *const this;
		todo("implement");
		bool __result = _sub_10973B60((Forge::ObjectSet const *)this);
		return __result;
	}

	_extern void _sub_1096F9F0(Forge::ObjectSet *const, long);
	_inline void ObjectSet::Add(long objectIndex) // 0x1096F9F0
	{
		mangled_x86(MANGLED_TODO, "?Add@ObjectSet@Forge@@QAEXJ@Z");
		// long objectIndex;
		todo("implement");
		_sub_1096F9F0(this, objectIndex);
	}

	_extern void _sub_10974BD0(Forge::ObjectSet *const, long);
	_inline void ObjectSet::Remove(long objectIndex) // 0x10974BD0
	{
		mangled_x86(MANGLED_TODO, "?Remove@ObjectSet@Forge@@QAEXJ@Z");
		// long objectIndex;
		todo("implement");
		_sub_10974BD0(this, objectIndex);
	}

	_extern void _sub_1096FA60(Forge::ObjectSet *const);
	_inline void ObjectSet::Clear() // 0x1096FA60
	{
		mangled_x86(MANGLED_TODO, "?Clear@ObjectSet@Forge@@QAEXXZ");
		// Forge::ObjectSet *const this;
		todo("implement");
		_sub_1096FA60(this);
	}
}

/* ---------- private code */

#endif // __FORGE_OBJECTSET_HPP__
