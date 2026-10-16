/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

#include "mods/font_package.hpp"  // hades: added for 0x109168F0
extern void font_package_set_defaults();  // hades: added for 0x109168F0

extern void font_patches_apply();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void font_patches_apply() // 0x109168F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?font_patches_apply@@YAXXZ");

	font_package_set_defaults();
	Hook(0x25C5D0, font_package_do_work).Apply();
	Hook(0x25C200, font_package_cache_flush).Apply();
	Hook(0x25C370, font_package_idle).Apply();
	Hook(0x1099A0, fonts_begin_loading_internal).Apply();
	Hook(0x109550, font_load_callback).Apply();
	Hook(0x109480, font_load).Apply();
	Patch(0x1093F9, 0x90, 5).Apply();
}

/* ---------- private code */
