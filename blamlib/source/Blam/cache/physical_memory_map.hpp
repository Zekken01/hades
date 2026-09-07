#ifndef __BLAM_CACHE_PHYSICAL_MEMORY_MAP_HPP__
#define __BLAM_CACHE_PHYSICAL_MEMORY_MAP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_physical_memory_listener;
struct s_physical_memory_globals;
struct s_physical_memory_stage;

/* ---------- constants */

/* ---------- definitions */

struct s_physical_memory_stage
{
	void *start_address; // 0x0
	void *end_address; // 0x4
	unsigned char __pad0[4]; // 0x8
	__int32 num_allocations; // 0xC
	long field_10; // 0x10
};
static_assert(sizeof(s_physical_memory_stage) == 20, "Invalid s_physical_memory_stage size");

#pragma pack(push, 4)
struct s_physical_memory_globals
{
	c_physical_memory_listener *listener; // 0x0
	__int32 current_stage; // 0x4
	void *start_address; // 0x8
	void *current_address; // 0xC
	__int32 field_10; // 0x10
	s_physical_memory_stage stages[8]; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_physical_memory_globals) == 180, "Invalid s_physical_memory_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CACHE_PHYSICAL_MEMORY_MAP_HPP__
