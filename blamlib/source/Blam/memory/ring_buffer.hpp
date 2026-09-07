#ifndef __BLAM_MEMORY_RING_BUFFER_HPP__
#define __BLAM_MEMORY_RING_BUFFER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_ring_buffer;

/* ---------- constants */

/* ---------- definitions */

struct c_ring_buffer
{
	long ring_size; // 0x0
	long first_element; // 0x4
	long element_count; // 0x8
};
static_assert(sizeof(c_ring_buffer) == 12, "Invalid c_ring_buffer size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MEMORY_RING_BUFFER_HPP__
