#ifndef __COMMON_THREADING_WAITEVENT_HPP__
#define __COMMON_THREADING_WAITEVENT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

class WaitEvent;

/* ---------- constants */

/* ---------- definitions */

class WaitEvent
{
public:
	WaitEvent(bool initialValue);
	void Set();
	void Reset();
	bool Wait(__int32 timeout) const;
private:
	long volatile m_value; // 0x0
public:
	void __dflt_ctor_closure(); /* compiler_generated() */
};
static_assert(sizeof(WaitEvent) == 4, "Invalid WaitEvent size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __COMMON_THREADING_WAITEVENT_HPP__
