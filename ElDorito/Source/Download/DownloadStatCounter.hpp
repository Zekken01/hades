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
		_inline CDownloadStatCounter() noexcept; /* compiler_generated() */  // hades: noexcept - SSegment() has no EH frame
	};
	static_assert(sizeof(Download::CDownloadStatCounter) == 16, "Invalid Download::CDownloadStatCounter size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Download
{
	_inline __int32 CDownloadStatCounter::GetRate() const // 0x108301E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetRate@CDownloadStatCounter@Download@@QBEHXZ");
		// Download::CDownloadStatCounter const *const this;

		return m_average;
	}

	_inline void CDownloadStatCounter::SecondTick(__int32 deltaMs) // 0x10831BC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SecondTick@CDownloadStatCounter@Download@@QAEXH@Z");
		// __int32 deltaMs;
		// long long sample;

		long long sample = m_counter * 1000LL / deltaMs;
		(void)((!!(sample >= 0)) || (_wassert(L"sample >= 0", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Download\\DownloadStatCounter.hpp", 22), 0));
		m_average = m_average * 3LL / 4 + sample / 4;
		m_counter = 0;
	}

	_inline void CDownloadStatCounter::Clear() // 0x1082EB10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Clear@CDownloadStatCounter@Download@@QAEXXZ");
		// Download::CDownloadStatCounter *const this;

		m_counter = 0;
		m_average = 0;
		m_totalCounter = 0;
	}

	_inline void CDownloadStatCounter::Add(__int32 count) // 0x1082DEC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Add@CDownloadStatCounter@Download@@QAEXH@Z");
		// __int32 count;

		(void)((!!(m_counter < (std::numeric_limits<std::int32_t>::max)() - count)) || (_wassert(L"m_counter < (std::numeric_limits<std::int32_t>::max)() - count", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Download\\DownloadStatCounter.hpp", 36), 0));
		m_counter += count;
		(void)((!!(m_totalCounter < (std::numeric_limits<std::int64_t>::max)() - count)) || (_wassert(L"m_totalCounter < (std::numeric_limits<std::int64_t>::max)() - count", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Download\\DownloadStatCounter.hpp", 38), 0));
		m_totalCounter += count;
	}
}

/* ---------- private code */

#endif // __DOWNLOAD_DOWNLOADSTATCOUNTER_HPP__
