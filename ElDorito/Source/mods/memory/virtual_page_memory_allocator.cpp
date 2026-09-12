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
	// unsigned long total_size;
	// unsigned long aligned_total_size;
	// function call : void *(void *, unsigned long, unsigned long, unsigned long)

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
	// c_virtual_page_memory_allocator const *const this;

	return m_current_size;
}

_extern void *_sub_108920D0(c_virtual_page_memory_allocator *const, unsigned long, long, unsigned long *);
void *c_virtual_page_memory_allocator::allocate(unsigned long size, long alignment_bits, unsigned long *out_allocated_size) // 0x108920D0
{
	mangled_x86(MANGLED_TODO, "?allocate@c_virtual_page_memory_allocator@@QAEPAXKJPAK@Z");
	// unsigned long *out_allocated_size;
	// unsigned long aligned_size;
	// unsigned long page_mask;
	// unsigned long padding;
	// unsigned long alignment_mask;
	// void *memory;
	{
		// unsigned long page_range_size;
	}
	// function call : void *(void *, unsigned long, unsigned long, unsigned long)
	todo("implement");
	void * __result = _sub_108920D0(this, size, alignment_bits, out_allocated_size);
	return __result;
}

_extern void _sub_10892220(c_virtual_page_memory_allocator *const, unsigned long);
void c_virtual_page_memory_allocator::free_to_marker(unsigned long marker) // 0x10892220
{
	mangled_x86(MANGLED_TODO, "?free_to_marker@c_virtual_page_memory_allocator@@QAEXK@Z");
	// unsigned long marker;
	// unsigned long next_page_offset;
	// function call : __int32 (void *, unsigned long, unsigned long)
	todo("implement");
	_sub_10892220(this, marker);
}

/* ---------- private code */
