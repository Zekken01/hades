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

#include "Modules/ModuleCamera.hpp"  // hades: added for 0x10916800

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
		void ApplyAll() // 0x10916590
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@FirstPerson@Patches@@YAXXZ");

			Patch::NopFill(0xA9E564, 5);
			Hook(0x69B88A, first_person_weapon_offset_hook1_hook).Apply();
			Hook(0x69B92B, first_person_weapon_offset_hook2_hook).Apply();
		}

		void Tick() // 0x10916800
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@FirstPerson@Patches@@YAXXZ");

			g_first_weapon_offset_field_offset = !Utils::Singleton<Modules::ModuleCamera>::Instance().VarCameraCenteredCrosshairFirst->ValueInt ? 1324 : 1368;
		}
	}
}

/* ---------- private code */

__declspec(naked) void first_person_weapon_offset_hook1_hook() // 0x10916880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?first_person_weapon_offset_hook1_hook@@YAXXZ");

	__asm
	{
		add eax, g_first_weapon_offset_field_offset
		push 0xA9B88F
		ret
	}
}

__declspec(naked) void first_person_weapon_offset_hook2_hook() // 0x10916890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?first_person_weapon_offset_hook2_hook@@YAXXZ");

	__asm
	{
		add eax, g_first_weapon_offset_field_offset
		movss xmm0, [edi+0x2784]
		subss xmm0, [eax]
		movss [edi+0x2784], xmm0
		movss xmm0, [edi+0x2788]
		subss xmm0, [eax+0x4]
		movss [edi+0x2788], xmm0
		movss xmm0, [edi+0x278C]
		subss xmm0, [eax+0x8]
		or dword ptr [edi], 0x10
		movss [edi+0x278C], xmm0
		push 0xA9B97B
		ret
	}
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { long g_first_weapon_offset_field_offset = 1324; }
