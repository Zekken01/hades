#ifndef __UTILS_EVENTSINK_HPP__
#define __UTILS_EVENTSINK_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"

#include <functional>
#include <memory>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

template<> inline __int32 CEventSink<>::Subscribe(std::function<void __cdecl(void)> const &callable) // 0x108572B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Subscribe@?$CEventSink@$$V@@QAEHABV?$function@$$A6AXXZ@std@@@Z");

	__int32 id = m_nextId.fetch_add(1);
	m_callbacks.push_back({ callable, id });
	return id;
}

template<> inline void CEventSink<>::PostEvent() // 0x108315F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PostEvent@?$CEventSink@$$V@@QAEXXZ");

	for (auto &entry : m_callbacks)
		entry.callback();
}

template<> inline void CEventSink<>::Reset() // 0x10831B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@?$CEventSink@$$V@@QAEXXZ");

	m_callbacks.clear();
}

/* ---------- private code */

#endif // __UTILS_EVENTSINK_HPP__
