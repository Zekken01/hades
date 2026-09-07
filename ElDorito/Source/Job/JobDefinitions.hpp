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
	_inline SJobCounter(); /* compiler_generated() */
};
static_assert(sizeof(SJobCounter) == 4, "Invalid SJobCounter size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern __int32 _sub_1086D250(SJobCounter const *const);
_inline __int32 SJobCounter::GetValue() const // 0x1086D250
{
	mangled_x86(MANGLED_TODO, "?GetValue@SJobCounter@@QBEHXZ");
	// SJobCounter const *const this;
	todo("implement");
	__int32 __result = _sub_1086D250((SJobCounter const *)this);
	return __result;
}

_extern __int32 _sub_1086A0D0(SJobCounter *const);
_inline __int32 SJobCounter::Increment() // 0x1086A0D0
{
	mangled_x86(MANGLED_TODO, "?Increment@SJobCounter@@QAEHXZ");
	// SJobCounter *const this;
	todo("implement");
	__int32 __result = _sub_1086A0D0(this);
	return __result;
}

_extern __int32 _sub_10869F20(SJobCounter *const);
_inline __int32 SJobCounter::Decrement() // 0x10869F20
{
	mangled_x86(MANGLED_TODO, "?Decrement@SJobCounter@@QAEHXZ");
	// SJobCounter *const this;
	todo("implement");
	__int32 __result = _sub_10869F20(this);
	return __result;
}

/* ---------- private code */

#endif // __JOB_JOBDEFINITIONS_HPP__
