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

_extern __int32 _sub_108572B0(CEventSink<> *const, std::function<void __cdecl(void)> const &);
_inline __int32 CEventSink<>::Subscribe(std::function<void __cdecl(void)> const &callable) // 0x108572B0
{
	mangled_x86(MANGLED_TODO, "?Subscribe@?$CEventSink@$$V@@QAEHABV?$function@$$A6AXXZ@std@@@Z");
	// std::function<void __cdecl(void)> const &callable;
	// __int32 id;
	todo("implement");
	__int32 __result = _sub_108572B0((CEventSink<> *)this, callable);
	return __result;
}

_extern void _sub_108315F0(CEventSink<> *const);
_inline void CEventSink<>::PostEvent() // 0x108315F0
{
	mangled_x86(MANGLED_TODO, "?PostEvent@?$CEventSink@$$V@@QAEXXZ");
	// CEventSink<> *const this;
	{
		// std::vector<CEventSink<>::SCallbackEntry> &<range>$L0;
		// CEventSink<>::SCallbackEntry *<begin>$L0;
		// CEventSink<>::SCallbackEntry *<end>$L0;
		{
			// CEventSink<>::SCallbackEntry const &c;
		}
	}
	todo("implement");
	_sub_108315F0((CEventSink<> *)this);
}

_extern void _sub_10831B70(CEventSink<> *const);
_inline void CEventSink<>::Reset() // 0x10831B70
{
	mangled_x86(MANGLED_TODO, "?Reset@?$CEventSink@$$V@@QAEXXZ");
	// CEventSink<> *const this;
	todo("implement");
	_sub_10831B70((CEventSink<> *)this);
}

/* ---------- private code */

#endif // __UTILS_EVENTSINK_HPP__
