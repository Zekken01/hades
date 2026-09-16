#ifndef __JOB_JOBDEFINITIONS_HPP__
#define __JOB_JOBDEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Download/HttpFileDownload.hpp"

#include <atomic>

/* ---------- forward declarations */

struct SJobCounter;

/* ---------- constants */

/* ---------- definitions */

struct SJobCounter
{
	_inline __int32 GetValue() const;
	void SetValue(__int32);
	_inline __int32 Increment();
	_inline __int32 Decrement();
private:
	std::atomic<int> m_value; // 0x0
public:
	_inline SJobCounter() = default; /* compiler_generated() */
};
static_assert(sizeof(SJobCounter) == 4, "Invalid SJobCounter size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline __int32 SJobCounter::GetValue() const // 0x1086D250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetValue@SJobCounter@@QBEHXZ");
	// SJobCounter const *const this;

	return m_value.load();
}

_inline __int32 SJobCounter::Increment() // 0x1086A0D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Increment@SJobCounter@@QAEHXZ");
	// SJobCounter *const this;

	return m_value.fetch_add(1);
}

_inline __int32 SJobCounter::Decrement() // 0x10869F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Decrement@SJobCounter@@QAEHXZ");
	// SJobCounter *const this;

	return m_value.fetch_sub(1);
}

/* ---------- private code */

#endif // __JOB_JOBDEFINITIONS_HPP__
