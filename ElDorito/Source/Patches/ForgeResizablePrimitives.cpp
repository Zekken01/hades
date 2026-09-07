/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/havok_component.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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

/* ---------- forward declarations */

struct collision_bsp;
struct real_vector3d;
struct s_globals;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace ForgeResizablePrimitives {}
	using namespace Patches::ForgeResizablePrimitives;
}

/* ---------- constants */

/* ---------- definitions */

struct s_globals
{
	bool valid_bsp; // 0x0
	collision_bsp collision_bsp; // 0x4
};
// static_assert(sizeof(s_globals) == 100, "Invalid s_globals size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

namespace Patches
{
	namespace ForgeResizablePrimitives
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern real_vector3d global_zero3d; // 0x11197984
}
/* ---------- public code */

namespace Patches
{
	namespace ForgeResizablePrimitives
	{
		_extern void _sub_10916FF0();
		void ApplyAll() // 0x10916FF0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@ForgeResizablePrimitives@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10916FF0();
		}
	}
}

/* ---------- private code */
