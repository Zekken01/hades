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

WaitEvent::WaitEvent(bool initialValue) // 0x106D1640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0WaitEvent@@QAE@_N@Z");
	// bool initialValue;

	m_value = initialValue;
}

void WaitEvent::Set() // 0x106D16D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Set@WaitEvent@@QAEXXZ");
	// WaitEvent *const this;

	if (!_InterlockedExchange(&m_value, 1))
		WakeByAddressAll(this);
}

void WaitEvent::Reset() // 0x106D1670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@WaitEvent@@QAEXXZ");
	// WaitEvent *const this;

	if (InterlockedExchange(&m_value, 0) == 1)
		WakeByAddressAll(this);
}

bool WaitEvent::Wait(__int32 timeout) const // 0x106D1730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Wait@WaitEvent@@QBE_NH@Z");
	// static ...; // 0x106D17C0
	// static ...; // 0x106D17B8
	// WaitEvent const *const this;
	// __int32 timeout;
	// long undesiredValue;
	// long capturedValue;

	long current;
	long undesiredValue = 0;

	current = m_value;

	while (current == undesiredValue)
	{
		if (!WaitOnAddress((void *)&m_value, &undesiredValue, sizeof(undesiredValue), timeout))
		{
			return false;
		}

		current = m_value;
	}

	return true;
}

/* ---------- private code */
