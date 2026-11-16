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

inline unsigned long address_from_pointer(void const *pointer) // 0x1069C260
{
	return (unsigned long)pointer;
}

inline void const *pointer_from_address(unsigned long address) // 0x1069D890
{
	return (void const *)address;
}

inline void *offset_pointer(void *pointer, long offset) // 0x1069D830
{
	return (void *)pointer_from_address(address_from_pointer(pointer) + offset);
}

inline void const *offset_pointer(void const *pointer, long offset) // 0x107A7D90
{
	return pointer_from_address(address_from_pointer(pointer) + offset);
}

/* ---------- private code */

#endif // __BLAM_CSERIES_CSERIES_MEMORY_HPP__
