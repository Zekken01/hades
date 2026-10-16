#ifndef __MODS_MEMORY_VIRTUAL_PAGE_MEMORY_ALLOCATOR_HPP__
#define __MODS_MEMORY_VIRTUAL_PAGE_MEMORY_ALLOCATOR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_virtual_page_memory_allocator;

/* ---------- constants */

/* ---------- definitions */

struct c_virtual_page_memory_allocator
{
	bool reserve_memory(unsigned long total_size);
	void *allocate(unsigned long size, long alignment_bits, unsigned long *out_allocated_size);
	unsigned long get_marker() const;
	void free_to_marker(unsigned long marker);
	_inline void *get_base_address();
	_inline unsigned long get_used_size() const;
	_inline unsigned long get_total_size() const;
private:
	unsigned char *m_memory; // 0x0
	unsigned long m_total_size; // 0x4
	unsigned long m_current_size; // 0x8
	unsigned long m_next_uncommitted_page_offset; // 0xC
public:
	_inline c_virtual_page_memory_allocator(); /* compiler_generated() */
};
static_assert(sizeof(c_virtual_page_memory_allocator) == 16, "Invalid c_virtual_page_memory_allocator size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline void *c_virtual_page_memory_allocator::get_base_address() // 0x108BDD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_base_address@c_virtual_page_memory_allocator@@QAEPAXXZ");

	return m_memory;
}

inline unsigned long c_virtual_page_memory_allocator::get_used_size() const // 0x108BE060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_used_size@c_virtual_page_memory_allocator@@QBEKXZ");

	return m_current_size;
}

inline unsigned long c_virtual_page_memory_allocator::get_total_size() const // 0x108BDF90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_total_size@c_virtual_page_memory_allocator@@QBEKXZ");

	return m_total_size;
}

/* ---------- private code */

#endif // __MODS_MEMORY_VIRTUAL_PAGE_MEMORY_ALLOCATOR_HPP__
