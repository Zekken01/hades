/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"

#include <sys/stat.h>
#include <wchar.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern __int32 ustrnicmp(wchar_t const *string1, wchar_t const *string2, long count);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

__int32 ustrnicmp(wchar_t const *string1, wchar_t const *string2, long count) // 0x10F1AAC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ustrnicmp@@YAHPB_W0J@Z");
#line 28

	#line 26 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\text\\unicode.cpp"
		assert(string1 != NULL);
		assert(string2 != NULL);
		#line 33 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\text\\unicode.cpp"
	return _wcsnicmp(string1, string2, count);
}

/* ---------- private code */
