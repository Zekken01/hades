#ifndef __MODS_MEMORY_PHYSICAL_MEMORY_MANAGER_HPP__
#define __MODS_MEMORY_PHYSICAL_MEMORY_MANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_physical_memory_manager;

/* ---------- constants */

enum e_physical_memory_stage
{
	_physical_memory_stage_shared = 0,
	_physical_memory_stage_tags,
	_physical_memory_stage_resources,
	k_physical_memory_stage_count,
};

/* ---------- definitions */

struct c_physical_memory_manager
{
	static bool initialize(unsigned long total_memory_size);
	static void push(e_physical_memory_stage stage);
	static void pop(e_physical_memory_stage stage);
	static void *allocate(e_physical_memory_stage stage, char const *name, unsigned long size, long alignment_bits, unsigned long *out_allocated_size);
	static void prepare_for_new_map();
	static void *get_base_address();
	static void *get_current_address();
	static unsigned long get_stage_used_size(e_physical_memory_stage stage);
	static unsigned long get_used_size();
	static unsigned long get_total_size();
};
static_assert(sizeof(c_physical_memory_manager) == 1, "Invalid c_physical_memory_manager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_MEMORY_PHYSICAL_MEMORY_MANAGER_HPP__
