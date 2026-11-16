/* ---------- headers */

#include "Blam/multithreading/synchronization/synchronized_int.hpp"
#include "hades/hades.h"

#include <Windows.h>

/* ---------- forward declarations */

class c_synchronized_int32;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_synchronized_int32::c_synchronized_int32(long value) // 0x10F0D360
{
	m_value = value;
}

c_synchronized_int32::c_synchronized_int32() : c_synchronized_int32(0) /* hades-mem-init:  */ // 0x10F0D3C0
{
}

long c_synchronized_int32::set(long value) // 0x10F0D5B0
{
	return _InterlockedExchange(&m_value, value);
}

long c_synchronized_int32::peek() const // 0x10F0D550
{
	return m_value;
}

long c_synchronized_int32::increment() // 0x10F0D4F0
{
	return _InterlockedIncrement(&m_value);
}

long c_synchronized_int32::decrement() // 0x10F0D490
{
	return _InterlockedDecrement(&m_value);
}

long c_synchronized_int32::add(long value) // 0x10F0D420
{
	return InterlockedAdd(&m_value, value);
}

/* ---------- private code */
