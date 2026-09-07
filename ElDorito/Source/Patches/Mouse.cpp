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
		_extern void _sub_10A8BE00();
		void ApplyAll() // 0x10A8BE00
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Mouse@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A8BE00();
		}
	}
}

/* ---------- private code */

extern void _sub_10A8BDD0();
__declspec(naked) void AimAssistHook() // 0x10A8BDD0
{
	// `anonymous-namespace'::AimAssistHook
	// procedure flags: nofpo
// controller:
	todo("implement");
	_sub_10A8BDD0();
}

_extern unsigned __int32 _sub_10A8C040(unsigned __int32, short);
unsigned __int32 DualAimAssistHook(unsigned __int32 unitObject, short weaponIndex) // 0x10A8C040
{
	// `anonymous-namespace'::DualAimAssistHook
	// short weaponIndex;
	// unsigned __int32 (*UnitGetWeapon)(unsigned __int32, short);
	// function call : unsigned __int32 (*)(unsigned __int32, short)
	todo("implement");
	unsigned __int32 __result = _sub_10A8C040(unitObject, weaponIndex);
	return __result;
}
