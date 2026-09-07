#ifndef __BLAM_ASYNC_ASYNC_HPP__
#define __BLAM_ASYNC_ASYNC_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/multithreading/synchronization/synchronized_int.hpp"

/* ---------- forward declarations */

class c_synchronized_int32;
struct c_async_completion_flag;

/* ---------- constants */

/* ---------- definitions */

struct c_async_completion_flag
{
	long peek() const;
	void set(long value);
	void set_internal_data(long value);
	long get_internal_data() const;
	bool is_done() const;
	c_async_completion_flag &operator=(c_async_completion_flag const &other);
	operator long() const;
private:
	c_synchronized_int32 m_status; // 0x0
	c_synchronized_int32 m_internal_data; // 0x4
public:
	_inline c_async_completion_flag(); /* compiler_generated() */
};
static_assert(sizeof(c_async_completion_flag) == 8, "Invalid c_async_completion_flag size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ASYNC_ASYNC_HPP__
