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
#include "Forge/ForgeUndo.hpp"
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

/* ---------- forward declarations */

namespace
{
	struct SslWStringHeader;
	struct PlayerNameString;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Scoreboard {}
	using namespace Patches::Scoreboard;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct SslWStringHeader
	{
		__int32 refCount; // 0x0
		__int32 length1; // 0x4
		__int32 length2; // 0x8
	};
	static_assert(sizeof(SslWStringHeader) == 12, "Invalid SslWStringHeader size");

	struct PlayerNameString
	{
		SslWStringHeader header; // 0x0
		char16_t name[16]; // 0xC
	};
}
// static_assert(sizeof(PlayerNameString) == 44, "Invalid PlayerNameString size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

/* ---------- prototypes */

namespace Patches
{
	namespace Scoreboard
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Scoreboard
	{
		_extern void _sub_10ACA2A0();
		void ApplyAll() // 0x10ACA2A0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Scoreboard@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10ACA2A0();
		}
	}
}

/* ---------- private code */
