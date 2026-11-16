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
	m_value = initialValue;
}

void WaitEvent::Set() // 0x106D16D0
{
	if (!_InterlockedExchange(&m_value, 1))
		WakeByAddressAll(this);
}

void WaitEvent::Reset() // 0x106D1670
{
	if (InterlockedExchange(&m_value, 0) == 1)
		WakeByAddressAll(this);
}

bool WaitEvent::Wait(__int32 timeout) const // 0x106D1730
{
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
