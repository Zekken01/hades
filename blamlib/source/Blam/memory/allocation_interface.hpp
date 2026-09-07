#ifndef __BLAM_MEMORY_ALLOCATION_INTERFACE_HPP__
#define __BLAM_MEMORY_ALLOCATION_INTERFACE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_allocation_interface;

/* ---------- constants */

/* ---------- definitions */

struct c_allocation_interface
{
	virtual void *allocate(unsigned long, char const *) = 0;
	virtual void daallocate(void *) = 0;
	c_allocation_interface(c_allocation_interface &); /* compiler_generated() */
	c_allocation_interface(c_allocation_interface const &); /* compiler_generated() */
	c_allocation_interface(); /* compiler_generated() */
	c_allocation_interface &operator=(c_allocation_interface &); /* compiler_generated() */
	c_allocation_interface &operator=(c_allocation_interface const &); /* compiler_generated() */
};
static_assert(sizeof(c_allocation_interface) == 4, "Invalid c_allocation_interface size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MEMORY_ALLOCATION_INTERFACE_HPP__
