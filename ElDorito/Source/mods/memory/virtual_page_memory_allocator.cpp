/* ---------- headers */

#include "mods/memory/virtual_page_memory_allocator.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>

/* ---------- forward declarations */

struct c_virtual_page_memory_allocator;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool c_virtual_page_memory_allocator::reserve_memory(unsigned long total_size) // 0x10892330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reserve_memory@c_virtual_page_memory_allocator@@QAE_NK@Z");

	unsigned long aligned_size = (total_size + 4095) & 0xFFFFF000;
	m_memory = (unsigned char *)VirtualAlloc(nullptr, aligned_size, 0x2000, 1);
	if (!m_memory)
	{
		return false;
	}
	m_total_size = aligned_size;
	m_current_size = 0;
	return true;
}

unsigned long c_virtual_page_memory_allocator::get_marker() const // 0x10892300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_marker@c_virtual_page_memory_allocator@@QBEKXZ");

	return m_current_size;
}

void *c_virtual_page_memory_allocator::allocate(unsigned long size, long alignment_bits, unsigned long *out_allocated_size) // 0x108920D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?allocate@c_virtual_page_memory_allocator@@QAEPAXKJPAK@Z");

	unsigned long alignment_mask = (1 << alignment_bits) - 1;
	unsigned long aligned_size = (size + alignment_mask) & ~alignment_mask;
	unsigned long padding = aligned_size - size;
	unsigned long page_mask = 0xFFF;
	if (m_current_size + aligned_size > m_next_uncommitted_page_offset)
	{
		if (m_next_uncommitted_page_offset >= m_total_size)
			return nullptr;
		unsigned long page_range_size = (aligned_size + page_mask) & ~page_mask;
		if (!VirtualAlloc(m_memory + m_next_uncommitted_page_offset, page_range_size, MEM_COMMIT, PAGE_READWRITE))
			return nullptr;
		m_next_uncommitted_page_offset += page_range_size;
	}
	void *memory = &m_memory[m_current_size + padding];
	m_current_size += aligned_size;
	if (out_allocated_size)
		*out_allocated_size = aligned_size;
	return memory;
}

#line 85
void c_virtual_page_memory_allocator::free_to_marker(unsigned long marker) // 0x10892220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?free_to_marker@c_virtual_page_memory_allocator@@QAEXK@Z");
#line 91

	#line 87 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\memory\\virtual_page_memory_allocator.cpp"
		assert(marker <= m_current_size);
		#line 95 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\memory\\virtual_page_memory_allocator.cpp"
	if (marker == m_current_size)
	{
		return;
	}

	unsigned long next_page_offset = (marker + 0xFFF) & 0xFFFFF000;
	VirtualFree(m_memory + next_page_offset, m_current_size - marker, MEM_DECOMMIT);
	m_current_size = marker;
	m_next_uncommitted_page_offset = next_page_offset;
}

/* ---------- private code */
