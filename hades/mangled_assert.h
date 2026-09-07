#pragma once
#ifndef __HADES_MANGLED_ASSERT_H__
#define __HADES_MANGLED_ASSERT_H__

/* ---------- headers */

#include "hades/static_assert.h"

/* ---------- definitions */

// `mangled_x86` is the x86 analogue of Ares's `mangled_x64`: it pins a reconstructed
// function to the mangled name the original binary exported. If the signature, calling
// convention, const-ness, namespace or enclosing class drifts, `__FUNCDNAME__` stops
// matching and the translation unit fails to compile -- so the identity of every ported
// function is checked by the compiler rather than by eye.
//
// mtndew.dll is 32-bit, so the decorations are the x86 forms (`?Foo@@YAXH@Z`, a leading
// `_` on cdecl C functions, `@N` stack-size suffixes on __stdcall/__fastcall).

#ifndef mangled_x86

constexpr bool _mangled_names_equal(char const *a, char const *b)
{
	while (*a || *b)
	{
		if (*a++ != *b++)
		{
			return false;
		}
	}
	return true;
}

constexpr bool _mangled_prefix_matches(char const *prefix, char const *name)
{
	while (*prefix)
	{
		if (*prefix++ != *name++)
		{
			return false;
		}
	}
	return true;
}

#define MANGLED_DEFAULT 0
#define MANGLED_DEPRECATED 1
#define MANGLED_INLINED 2
#define MANGLED_INLINED_HEADER 4
#define MANGLED_TODO 16
// functions marked known good are believed correct but do not match for unknown reasons
#define MANGLED_KNOWN_GOOD 32

#ifdef __INTELLISENSE__
#define mangled_x86(FLAGS, mangled_name) static_assert32("mangled_x86 hidden")
#define mangled_prefix_assert(mangled_prefix) static_assert32("mangled_prefix_assert hidden")
#else
#define mangled_x86(FLAGS, mangled_name) \
	static_assert32(_mangled_names_equal(mangled_name, __FUNCDNAME__), "incorrect mangled : " __FUNCDNAME__ " != " mangled_name)
#define mangled_prefix_assert(mangled_prefix) \
	static_assert32(_mangled_prefix_matches(mangled_prefix, __FUNCDNAME__), "incorrect mangled prefix : " __FUNCDNAME__ " != " mangled_prefix)
#endif

#endif // mangled_x86

#endif // __HADES_MANGLED_ASSERT_H__
