#ifndef __PATCH_HPP__
#define __PATCH_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Pointer.hpp"

#include <initializer_list>
#include <memory>
#include <vector>

/* ---------- forward declarations */

class Hook;
class Patch;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class Patch
{
public:
	typedef std::initializer_list<unsigned char> InitializerListType;
	Patch(Patch &); /* compiler_generated() */
	Patch(Patch const &); /* compiler_generated() */
	Patch(unsigned __int32 Offset, unsigned __int32 byteValue, unsigned __int32 numBytes, Pointer base = Pointer::Base());  /* hades: default from 0.6.1 */
	Patch(unsigned __int32 Offset, std::initializer_list<unsigned char> const &Data, Pointer base = Pointer::Base());  /* hades: default from 0.6.1 */
	Patch(unsigned __int32 Offset, std::initializer_list<unsigned char> const &Data, std::initializer_list<unsigned char> const &Reset);
	Patch();
	_inline void Apply(bool revert = false, Pointer offset = Pointer::Base()) const;  /* hades: default from 0.6.1 */
	_inline void Reset(Pointer offset = Pointer::Base()) const;  /* hades: default from 0.6.1 */
	static _inline void NopFill(Pointer offset, unsigned __int32 length);
private:
	unsigned __int32 Offset; // 0x0
	std::vector<unsigned char> Data; // 0x4
	std::vector<unsigned char> Orig; // 0x14
public:
	_inline ~Patch(); /* compiler_generated() */
	Patch &operator=(Patch &); /* compiler_generated() */
	Patch &operator=(Patch const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(Patch) == 36, "Invalid Patch size");

#pragma pack(push, 4)
class Hook
{
public:
	Hook(Hook &); /* compiler_generated() */
	Hook(Hook const &); /* compiler_generated() */
	Hook(unsigned __int32 Offset, void *destFunc, __int32 flags = 0, std::initializer_list<unsigned char> Reset = {});  /* hades: default from 0.6.1 */
	Hook();
	_inline void Apply(bool revert = false, Pointer offset = Pointer::Base()) const;  /* hades: default from 0.6.1 */
	_inline void Reset(Pointer offset = Pointer::Base()) const;  /* hades: default from 0.6.1 */
private:
	unsigned __int32 Offset; // 0x0
	void *DestFunc; // 0x4
	__int32 const Flags; // 0x8
	std::vector<unsigned char> Orig; // 0xC
public:
	_inline ~Hook(); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(Hook) == 28, "Invalid Hook size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline void Patch::Apply(bool revert, Pointer offset) const // 0x107A9530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Apply@Patch@@QBEX_NVPointer@@@Z");
	// Pointer offset;

	if (revert)
	{
		Reset(offset);
		return;
	}

	if (Data.size())
		offset(Offset, 1).Write(&Data[0], Data.size());
}

inline void Patch::Reset(Pointer offset) const // 0x107AB3C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@Patch@@QBEXVPointer@@@Z");
	// Pointer offset;

	if (Orig.size())
		offset(Offset, 1).Write(&Orig[0], Orig.size());
}

inline void Patch::NopFill(Pointer offset, unsigned __int32 length) // 0x108E4200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NopFill@Patch@@SAXVPointer@@I@Z");
	// unsigned __int32 length;

	memset(offset, 0x90, length);
}

inline void Hook::Apply(bool revert, Pointer offset) const // 0x10699840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Apply@Hook@@QBEX_NVPointer@@@Z");
	// Pointer offset;

	if (revert)
	{
		Reset(offset);
		return;
	}

	if (Flags & 1 || Flags & 2)
		offset(Offset, 1).WriteCall(DestFunc, Flags & 2 ? true : false);
	else
		offset(Offset, 1).WriteJump(DestFunc, Flags);
}

inline void Hook::Reset(Pointer offset) const // 0x10699DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@Hook@@QBEXVPointer@@@Z");
	// Pointer offset;

	if (Orig.size())
		offset(Offset, 1).Write(&Orig[0], Orig.size());
}

/* ---------- private code */

#endif // __PATCH_HPP__
