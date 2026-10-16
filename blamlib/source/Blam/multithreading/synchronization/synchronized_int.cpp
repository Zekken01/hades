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
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_synchronized_int32@@QAE@J@Z");

	m_value = value;
}

c_synchronized_int32::c_synchronized_int32() : c_synchronized_int32(0) /* hades-mem-init:  */ // 0x10F0D3C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_synchronized_int32@@QAE@XZ");
}

long c_synchronized_int32::set(long value) // 0x10F0D5B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_synchronized_int32@@QAEJJ@Z");

	return _InterlockedExchange(&m_value, value);
}

long c_synchronized_int32::peek() const // 0x10F0D550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?peek@c_synchronized_int32@@QBEJXZ");

	return m_value;
}

long c_synchronized_int32::increment() // 0x10F0D4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?increment@c_synchronized_int32@@QAEJXZ");

	return _InterlockedIncrement(&m_value);
}

long c_synchronized_int32::decrement() // 0x10F0D490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?decrement@c_synchronized_int32@@QAEJXZ");

	return _InterlockedDecrement(&m_value);
}

long c_synchronized_int32::add(long value) // 0x10F0D420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add@c_synchronized_int32@@QAEJJ@Z");

	return InterlockedAdd(&m_value, value);
}

/* ---------- private code */
