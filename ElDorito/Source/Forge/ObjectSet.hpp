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
		_inline ObjectSet() = default; /* compiler_generated() */
	};
	static_assert(sizeof(Forge::ObjectSet) == 256, "Invalid Forge::ObjectSet size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Forge
{
	inline bool ObjectSet::Contains(long objectIndex) const // 0x10838010
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Contains@ObjectSet@Forge@@QBE_NJ@Z");

		return objectIndex != -1 && m_Bits.test(objectIndex & 0xFFFF);
	}

	inline bool ObjectSet::Any() const // 0x10973B60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Any@ObjectSet@Forge@@QBE_NXZ");

		return m_Bits.any();
	}

	inline void ObjectSet::Add(long objectIndex) // 0x1096F9F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Add@ObjectSet@Forge@@QAEXJ@Z");

		m_Bits.set(objectIndex & 0xFFFF, true);
	}

	inline void ObjectSet::Remove(long objectIndex) // 0x10974BD0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Remove@ObjectSet@Forge@@QAEXJ@Z");

		m_Bits.set(objectIndex & 0xFFFF, false);
	}

	inline void ObjectSet::Clear() // 0x1096FA60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Clear@ObjectSet@Forge@@QAEXXZ");

		m_Bits.reset();
	}
}

/* ---------- private code */

#endif // __FORGE_OBJECTSET_HPP__
