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

_extern void *_sub_10EF90A0(unsigned long const);
void *tls_get(unsigned long const offset) // 0x10EF90A0
{
	mangled_x86(MANGLED_TODO, "?tls_get@@YAPAXK@Z");
	// unsigned long const offset;
	// void *address;
	todo("implement");
	void * __result = _sub_10EF90A0(offset);
	return __result;
}

/* ---------- private code */
