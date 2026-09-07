/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
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
	namespace Events {}
	using namespace Patches::Events;
	namespace Medals {}
	using namespace Patches::Medals;
}

/* ---------- constants */

/* ---------- definitions */

//struct chud_update_h3_medal_animation_hook::__l2::s_chud_h3_medal_state
//{
//	char Active; // 0x0
//	__int32 field_4; // 0x4
//	__int32 StartTime; // 0x8
//	__int32 InEndTime; // 0xC
//	__int32 Duration; // 0x10
//	char InAnimationFinished; // 0x14
//	__int32 OutPercent; // 0x18
//	__int32 field_1C; // 0x1C
//	__int32 field_20; // 0x20
//	float Opacity; // 0x24
//};
//static_assert(sizeof(chud_update_h3_medal_animation_hook::__l2::s_chud_h3_medal_state) == 40, "Invalid chud_update_h3_medal_animation_hook::__l2::s_chud_h3_medal_state size");

/* ---------- prototypes */

namespace Patches
{
	namespace Medals
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Medals
	{
		_extern void _sub_10A89990();
		void ApplyAll() // 0x10A89990
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Medals@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A89990();
		}
	}
}

/* ---------- private code */
