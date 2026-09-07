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

_extern void _sub_10698FB0(Hook *const);
_inline Hook::~Hook() // 0x10698FB0
{
	mangled_x86(MANGLED_TODO, "??1Hook@@QAE@XZ");
	// Hook *const this;
	compiler_generated();
	todo("implement");
	_sub_10698FB0(this);
}

/* ---------- private code */
