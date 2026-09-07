/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
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
#include <functional>
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

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Projectiles {}
	using namespace Patches::Projectiles;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Projectiles
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern float g_projectile_translate_tick_delta; // 0x1138600C
}
/* ---------- public code */

namespace Patches
{
	namespace Projectiles
	{
		_extern void _sub_1069E000();
		void ApplyAll() // 0x1069E000
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Projectiles@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1069E000();
		}
	}
}

/* ---------- private code */
