/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
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

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Mouse {}
	using namespace Patches::Mouse;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Mouse
	{
		extern void ApplyAll();
	}
}

void AimAssistHook();
unsigned __int32 DualAimAssistHook(unsigned __int32 unitObject, short weaponIndex);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Mouse
	{
		void ApplyAll() // 0x10A8BE00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Mouse@Patches@@YAXXZ");

			Hook(0x18AA17, AimAssistHook).Apply();
			Hook(0x18ABAB, DualAimAssistHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */

__declspec(naked) void AimAssistHook() // 0x10A8BDD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AimAssistHook@@YAXXZ");

	__asm
	{
		mov edx, 0244DE98h
		mov edx, [edx]
		test edx, edx
		jne Lcontroller
		xor edx, edx
		mov [edi + 14h], edx
		mov edx, 058AA23h
		jmp edx
		Lcontroller:
		movss xmm0, dword ptr [ebx + 388h]
		mov edx, 058AA1Fh
		jmp edx
	}
}

unsigned __int32 DualAimAssistHook(unsigned __int32 unitObject, short weaponIndex) // 0x10A8C040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DualAimAssistHook@@YAIIF@Z");

	// If using a mouse, report that there's no weapon being dual wielded
	if (!Pointer::Base(0x204DE98).Read<uint32_t>())
		return 0xFFFFFFFF;

	// Otherwise, get the weapon datum index normally
	typedef uint32_t(*UnitGetWeaponPtr)(uint32_t unitObject, short weaponIndex);
	auto UnitGetWeapon = reinterpret_cast<UnitGetWeaponPtr>(0xB454D0);
	return UnitGetWeapon(unitObject, weaponIndex);
}
