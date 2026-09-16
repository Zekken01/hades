/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

/* ---------- forward declarations */

class Hook;

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Bitmaps {}
	using namespace Patches::Bitmaps;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Bitmaps
	{
		extern void ApplyAll();
	}
}

bool bitmap_format_is_default_srgb_hook(short format);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Bitmaps
	{
		_extern void _sub_10699A70();
		void ApplyAll() // 0x10699A70
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Bitmaps@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10699A70();
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??1Hook@@QAE@XZ"); no body to assert in
_inline Hook::~Hook() = default; // 0x10698FB0

/* ---------- private code */

bool bitmap_format_is_default_srgb_hook(short format) // 0x1069A9E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?bitmap_format_is_default_srgb_hook@@YA_NF@Z");
	// `anonymous-namespace'::bitmap_format_is_default_srgb_hook
	// static ...; // 0x1069AA38
	// static ...; // 0x1069AA30
// $LN14:
// $LN2:
	// short format;

	switch (format)
	{
	case 13:
	case 20:
	case 22:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 33:
	case 34:
		return false;
	}

	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::Write<unsigned long>(unsigned long const) const;
template void Pointer::Write<unsigned short>(unsigned short const) const;
