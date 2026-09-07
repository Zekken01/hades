#ifndef __BLAM_MEMORY_LRUV_CACHE_HPP__
#define __BLAM_MEMORY_LRUV_CACHE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/memory/allocation_interface.hpp"
#include "Blam/memory/tls.hpp"

/* ---------- forward declarations */

struct c_allocation_interface;
struct s_lruv_cache;
struct s_lruv_cache_block;
union tag_string;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_lruv_cache
{
	tag_string name; // 0x0
	void *proc_context; // 0x20
	void *delete_block_proc; // 0x24
	void *locked_block_proc; // 0x28
	void *unknown_block_proc; // 0x2C
	void *compact_block_proc; // 0x30
	long hole_algorithm; // 0x34
	long maximum_page_count; // 0x38
	long page_size_bits; // 0x3C
	long fragmentation_threshold; // 0x40
	long frame_index; // 0x44
	long first_block_handle; // 0x48
	long last_block_handle; // 0x4C
	unsigned long failed_pages[8]; // 0x50
	c_data_array<s_lruv_cache_block> *blocks; // 0x70
	long signature; // 0x74
	c_allocation_interface *allocator; // 0x78
	long critical_section; // 0x7C
	unsigned char __pad0[4]; // 0x80
};
#pragma pack(pop)
static_assert(sizeof(s_lruv_cache) == 132, "Invalid s_lruv_cache size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MEMORY_LRUV_CACHE_HPP__
