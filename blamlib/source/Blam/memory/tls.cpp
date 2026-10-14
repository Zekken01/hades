/* ---------- headers */

#include "Blam/memory/tls.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void *tls_get(unsigned long const offset);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void *tls_get(unsigned long const offset) // 0x10EF90A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tls_get@@YAPAXK@Z");
	// unsigned long const offset;
	// void *address;

	void *address = nullptr;
	__asm
	{
		mov eax, fs:[0x2c]
		mov eax, ds:[eax]
		mov address, eax
	}
	return (char *)address + offset;
}

/* ---------- private code */
