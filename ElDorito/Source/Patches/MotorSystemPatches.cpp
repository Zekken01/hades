/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/motor/action_system.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Player/PlayerEmotes.hpp"
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

struct s_action_definition;
struct s_action_usage;

namespace Player {}
using namespace ::Player;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace MotorSystem {}
	using namespace Patches::MotorSystem;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace MotorSystem
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern s_action_usage g_action_usage_definitions[88]; // 0x11351E28
	extern s_action_definition *g_action_definitions[88]; // 0x113520E8
}
/* ---------- public code */

namespace Patches
{
	namespace MotorSystem
	{
		_extern void _sub_107BA430();
		void ApplyAll() // 0x107BA430
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@MotorSystem@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107BA430();
		}
	}
}

/* ---------- private code */
