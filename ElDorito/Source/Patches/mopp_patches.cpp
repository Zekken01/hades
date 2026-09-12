/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Reforge.hpp"
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

struct s_scenario;
struct s_scenario_structure_bsp;

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Mopp {}
	using namespace Patches::Mopp;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Mopp
	{
		extern void InitializeForNewMap();
		extern void ApplyAll();
		extern void Tick();
	}
}

void fixMoppAddress();
void loc_D0E9E3_hook();
void loc_D0D919_hook();
void loc_D0F505_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool ApplyRuntimeMoppFix; // 0x12464608
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Mopp
	{
		_extern void _sub_10A8BC10();
		void InitializeForNewMap() // 0x10A8BC10
		{
			mangled_x86(MANGLED_TODO, "?InitializeForNewMap@Mopp@Patches@@YAXXZ");
			// procedure flags: nofpo
			// s_scenario *scenario;
			{
				// long i;
				{
					// s_scenario_structure_bsp *sbsp;
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			_sub_10A8BC10();
		}

		_extern void _sub_10A8B8E0();
		void ApplyAll() // 0x10A8B8E0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Mopp@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A8B8E0();
		}

		void Tick() // 0x10A8BD10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Mopp@Patches@@YAXXZ");
			// procedure flags: nofpo
		}
	}
}

/* ---------- private code */

__declspec(naked) void fixMoppAddress() // 0x10A8BD30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixMoppAddress@@YAXXZ");
	// `anonymous-namespace'::fixMoppAddress
	// procedure flags: nofpo
// skip_fixup:

	__asm
	{
		push eax
		mov eax, esi
		and eax, 10000h
		shr eax, 10h
		cmp eax, 1
		jne Lskip_fixup
		mov al, ApplyRuntimeMoppFix
		test al, al
		je Lskip_fixup
		and esi, 0FF00FFFFh
		add esi, 4000000h
		Lskip_fixup:
		pop eax
		ret
	}
}

__declspec(naked) void loc_D0E9E3_hook() // 0x10A8BD90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?loc_D0E9E3_hook@@YAXXZ");
	// `anonymous-namespace'::loc_D0E9E3_hook
	// procedure flags: nofpo

	__asm
	{
		mov esi, [esi + 2Ch]
		add esi, ecx
		call fixMoppAddress
		mov eax, [ebp + 10h]
		push 0D0E9EBh
		ret
	}
}

__declspec(naked) void loc_D0D919_hook() // 0x10A8BD60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?loc_D0D919_hook@@YAXXZ");
	// `anonymous-namespace'::loc_D0D919_hook
	// procedure flags: nofpo

	__asm
	{
		mov ecx, [ebp + 8]
		mov esi, [ecx + 18h]
		mov ecx, [ebx + 64h]
		mov edx, [ecx]
		mov edx, [edx + 14h]
		add esi, eax
		call fixMoppAddress
		push 0D0D929h
		ret
	}
}

__declspec(naked) void loc_D0F505_hook() // 0x10A8BDB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?loc_D0F505_hook@@YAXXZ");
	// `anonymous-namespace'::loc_D0F505_hook
	// procedure flags: nofpo

	__asm
	{
		mov esi, [esi + 1Ch]
		mov ebp, [ebp]
		add esi, eax
		call fixMoppAddress
		push 0D0F50Dh
		ret
	}
}
