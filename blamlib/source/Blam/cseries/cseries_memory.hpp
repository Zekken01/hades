#ifndef __BLAM_CSERIES_CSERIES_MEMORY_HPP__
#define __BLAM_CSERIES_CSERIES_MEMORY_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern _inline unsigned long address_from_pointer(void const *pointer);
extern _inline void const *pointer_from_address(unsigned long address);
extern _inline void *offset_pointer(void *pointer, long offset);
extern _inline void const *offset_pointer(void const *pointer, long offset);

/* ---------- globals */

/* ---------- public code */

_extern unsigned long _sub_1069C260(void const *);
_inline unsigned long address_from_pointer(void const *pointer) // 0x1069C260
{
	mangled_x86(MANGLED_TODO, "?address_from_pointer@@YAKPBX@Z");
	// void const *pointer;
	todo("implement");
	unsigned long __result = _sub_1069C260(pointer);
	return __result;
}

extern void const *_sub_1069D890(unsigned long);
_inline void const *pointer_from_address(unsigned long address) // 0x1069D890
{
	mangled_x86(MANGLED_TODO, "?pointer_from_address@@YAPBXK@Z");
	// unsigned long address;
	todo("implement");
	void const * __result = _sub_1069D890(address);
	return __result;
}

_extern void *_sub_1069D830(void *, long);
_inline void *offset_pointer(void *pointer, long offset) // 0x1069D830
{
	mangled_x86(MANGLED_TODO, "?offset_pointer@@YAPAXPAXJ@Z");
	// long offset;
	todo("implement");
	void * __result = _sub_1069D830(pointer, offset);
	return __result;
}

extern void const *_sub_107A7D90(void const *, long);
_inline void const *offset_pointer(void const *pointer, long offset) // 0x107A7D90
{
	mangled_x86(MANGLED_TODO, "?offset_pointer@@YAPBXPBXJ@Z");
	// long offset;
	todo("implement");
	void const * __result = _sub_107A7D90(pointer, offset);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_CSERIES_CSERIES_MEMORY_HPP__
