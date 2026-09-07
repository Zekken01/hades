#ifndef __MODS_TAG_RESOURCE_MEMORY_SIZE_HELPER_HPP__
#define __MODS_TAG_RESOURCE_MEMORY_SIZE_HELPER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"

/* ---------- forward declarations */

class c_tag_resource_memory_size_helper;
struct s_tag_resource_data;

/* ---------- constants */

/* ---------- definitions */

class c_tag_resource_memory_size_helper
{
public:
	public:
	class c_cache_file_tag_interop_bulk_sizer
	{
	public:
		static unsigned long (*const get_next_offset)(c_cache_file_tag_interop_bulk_sizer *, long);
		static void (*const add_type_with_type_index)(c_cache_file_tag_interop_bulk_sizer *, long);
		static unsigned long (*const get_size)(c_cache_file_tag_interop_bulk_sizer *);
		static unsigned long (*const get_unaligned_total_allocation_size)(c_cache_file_tag_interop_bulk_sizer *);
	private:
		long m_alignment_bits; // 0x0
		unsigned long m_size; // 0x4
	public:
		c_cache_file_tag_interop_bulk_sizer(); /* compiler_generated() */
	};
	static_assert(sizeof(c_cache_file_tag_interop_bulk_sizer) == 8, "Invalid c_cache_file_tag_interop_bulk_sizer size");
	struct c_wrapped_allocation_sizer
	{
		void add(unsigned long, long);
		void add_data_array(long, unsigned long, long);
		void add_flags(long);
		void add_array(long, long, long);
		unsigned long get_size() const;
	private:
		unsigned long m_size; // 0x0
	public:
		c_wrapped_allocation_sizer(); /* compiler_generated() */
	};
	static_assert(sizeof(c_wrapped_allocation_sizer) == 4, "Invalid c_wrapped_allocation_sizer size");
	public:
	static unsigned long calculate_required_memory_overhead(s_tag_resource_data const *);
private:
	static unsigned long align_up(unsigned long, long);
	static unsigned long calculate_required_interop_memory_size(s_tag_resource_data const *);
	static unsigned long calculate_tag_resource_cache_page_table_memory_size(long);
	static unsigned long calculate_tag_resource_inverse_page_table_memory_size(long);
	static unsigned long calculate_tag_resource_cache_controller_memory_size(long);
	static unsigned long calculate_tag_resource_access_cache_memory_size(long);
	static unsigned long calculate_tag_resource_address_cache_memory_size(long, long);
};
static_assert(sizeof(c_tag_resource_memory_size_helper) == 1, "Invalid c_tag_resource_memory_size_helper size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_TAG_RESOURCE_MEMORY_SIZE_HELPER_HPP__
