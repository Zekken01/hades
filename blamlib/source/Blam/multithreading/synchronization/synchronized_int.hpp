#ifndef __BLAM_MULTITHREADING_SYNCHRONIZATION_SYNCHRONIZED_INT_HPP__
#define __BLAM_MULTITHREADING_SYNCHRONIZATION_SYNCHRONIZED_INT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

class c_synchronized_int32;

/* ---------- constants */

/* ---------- definitions */

class c_synchronized_int32
{
private:
	long volatile m_value; // 0x0
public:
	c_synchronized_int32(long value);
	c_synchronized_int32();
	long peek() const;
	long set(long value);
	long increment();
	long decrement();
	long add(long value);
};
static_assert(sizeof(c_synchronized_int32) == 4, "Invalid c_synchronized_int32 size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MULTITHREADING_SYNCHRONIZATION_SYNCHRONIZED_INT_HPP__
