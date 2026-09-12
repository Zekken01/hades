#ifndef __BLAM_CSERIES_STATIC_STRING_INL__
#define __BLAM_CSERIES_STATIC_STRING_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline s_static_string<256>::operator char const *() const // 0x108AE460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$s_static_string@$0BAA@@@QBEPBDXZ");
	// s_static_string<256> const *const this;

	return get_string();
}

_inline s_static_string<32>::operator char const *() const // 0x108AE4B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$s_static_string@$0CA@@@QBEPBDXZ");
	// s_static_string<32> const *const this;

	return get_string();
}

_inline s_static_string<4096>::operator char const *() const // 0x1068DFF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$s_static_string@$0BAAA@@@QBEPBDXZ");
	// s_static_string<4096> const *const this;

	return get_string();
}

/* ---------- private code */

#endif // __BLAM_CSERIES_STATIC_STRING_INL__
