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

_extern __int32 _sub_10F1AAC0(wchar_t const *, wchar_t const *, long);
__int32 ustrnicmp(wchar_t const *string1, wchar_t const *string2, long count) // 0x10F1AAC0
{
	mangled_x86(MANGLED_TODO, "?ustrnicmp@@YAHPB_W0J@Z");
	// long count;
	todo("implement");
	__int32 __result = _sub_10F1AAC0(string1, string2, count);
	return __result;
}

/* ---------- private code */
