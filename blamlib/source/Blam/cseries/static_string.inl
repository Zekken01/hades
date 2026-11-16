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

template<> inline s_static_string<256>::operator char const *() const // 0x108AE460
{
	return get_string();
}

template<> inline s_static_string<32>::operator char const *() const // 0x108AE4B0
{
	return get_string();
}

template<> inline s_static_string<4096>::operator char const *() const // 0x1068DFF0
{
	return get_string();
}

/* ---------- private code */

#endif // __BLAM_CSERIES_STATIC_STRING_INL__
