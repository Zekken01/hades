/* ---------- headers */

#include "Common/Threading/WaitEvent.hpp"
#include "hades/hades.h"

#include <Windows.h>

/* ---------- forward declarations */

class WaitEvent;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern WaitEvent* _sub_106D1640(WaitEvent *const, bool);
WaitEvent::WaitEvent(bool initialValue) // 0x106D1640
{
	mangled_x86(MANGLED_TODO, "??0WaitEvent@@QAE@_N@Z");
	// bool initialValue;
	todo("implement");
	_sub_106D1640(this, initialValue);
}

_extern void _sub_106D16D0(WaitEvent *const);
void WaitEvent::Set() // 0x106D16D0
{
	mangled_x86(MANGLED_TODO, "?Set@WaitEvent@@QAEXXZ");
	// WaitEvent *const this;
	todo("implement");
	_sub_106D16D0(this);
}

_extern void _sub_106D1670(WaitEvent *const);
void WaitEvent::Reset() // 0x106D1670
{
	mangled_x86(MANGLED_TODO, "?Reset@WaitEvent@@QAEXXZ");
	// WaitEvent *const this;
	todo("implement");
	_sub_106D1670(this);
}

_extern bool _sub_106D1730(WaitEvent const *const, __int32);
bool WaitEvent::Wait(__int32 timeout) const // 0x106D1730
{
	mangled_x86(MANGLED_TODO, "?Wait@WaitEvent@@QBE_NH@Z");
	// static ...; // 0x106D17C0
	// static ...; // 0x106D17B8
	// WaitEvent const *const this;
	// __int32 timeout;
	// long undesiredValue;
	// long capturedValue;
	todo("implement");
	bool __result = _sub_106D1730((WaitEvent const *)this, timeout);
	return __result;
}

/* ---------- private code */
