#ifndef __DOWNLOAD_DOWNLOADSTATCOUNTER_HPP__
#define __DOWNLOAD_DOWNLOADSTATCOUNTER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

namespace Download
{
	struct CDownloadStatCounter;
}

/* ---------- constants */

/* ---------- definitions */

namespace Download
{
	struct CDownloadStatCounter
	{
		_inline __int32 GetRate() const;
		long long GetTotal() const;
		__int32 GetCounter();
		_inline void SecondTick(__int32 deltaMs);
		_inline void Clear();
		_inline void Add(__int32 count);
	private:
		long long m_totalCounter; // 0x0
		__int32 m_counter; // 0x8
		__int32 m_average; // 0xC
	public:
		_inline CDownloadStatCounter(); /* compiler_generated() */
	};
	static_assert(sizeof(Download::CDownloadStatCounter) == 16, "Invalid Download::CDownloadStatCounter size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Download
{
	_extern __int32 _sub_108301E0(Download::CDownloadStatCounter const *const);
	_inline __int32 CDownloadStatCounter::GetRate() const // 0x108301E0
	{
		mangled_x86(MANGLED_TODO, "?GetRate@CDownloadStatCounter@Download@@QBEHXZ");
		// Download::CDownloadStatCounter const *const this;
		todo("implement");
		__int32 __result = _sub_108301E0((Download::CDownloadStatCounter const *)this);
		return __result;
	}

	_extern void _sub_10831BC0(Download::CDownloadStatCounter *const, __int32);
	_inline void CDownloadStatCounter::SecondTick(__int32 deltaMs) // 0x10831BC0
	{
		mangled_x86(MANGLED_TODO, "?SecondTick@CDownloadStatCounter@Download@@QAEXH@Z");
		// __int32 deltaMs;
		// long long sample;
		todo("implement");
		_sub_10831BC0(this, deltaMs);
	}

	_extern void _sub_1082EB10(Download::CDownloadStatCounter *const);
	_inline void CDownloadStatCounter::Clear() // 0x1082EB10
	{
		mangled_x86(MANGLED_TODO, "?Clear@CDownloadStatCounter@Download@@QAEXXZ");
		// Download::CDownloadStatCounter *const this;
		todo("implement");
		_sub_1082EB10(this);
	}

	_extern void _sub_1082DEC0(Download::CDownloadStatCounter *const, __int32);
	_inline void CDownloadStatCounter::Add(__int32 count) // 0x1082DEC0
	{
		mangled_x86(MANGLED_TODO, "?Add@CDownloadStatCounter@Download@@QAEXH@Z");
		// __int32 count;
		todo("implement");
		_sub_1082DEC0(this, count);
	}
}

/* ---------- private code */

#endif // __DOWNLOAD_DOWNLOADSTATCOUNTER_HPP__
