/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cache/cache_files.hpp"
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
#include "Blam/memory/static_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
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

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace FirstPerson {}
	using namespace Patches::FirstPerson;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace FirstPerson
	{
		extern void ApplyAll();
		extern void Tick();
	}
}

void first_person_weapon_offset_hook1_hook();
void first_person_weapon_offset_hook2_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern long g_first_weapon_offset_field_offset; // 0x113532DC
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace FirstPerson
	{
		_extern void _sub_10916590();
		void ApplyAll() // 0x10916590
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@FirstPerson@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10916590();
		}

		_extern void _sub_10916800();
		void Tick() // 0x10916800
		{
			mangled_x86(MANGLED_TODO, "?Tick@FirstPerson@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10916800();
		}
	}
}

/* ---------- private code */

__declspec(naked) void first_person_weapon_offset_hook1_hook() // 0x10916880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?first_person_weapon_offset_hook1_hook@@YAXXZ");
	// procedure flags: nofpo

	__asm
	{
		add eax, g_first_weapon_offset_field_offset
		push 0xA9B88F
		ret
	}
}

extern void _sub_10916890();
__declspec(naked) void first_person_weapon_offset_hook2_hook() // 0x10916890
{
	// `anonymous-namespace'::first_person_weapon_offset_hook2_hook
	// procedure flags: nofpo
	todo("implement");
	_sub_10916890();
}
