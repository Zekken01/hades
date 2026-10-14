/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/vehicles.hpp"
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

/* ---------- forward declarations */

struct c_vehicle_auto_turret;
struct c_vehicle_type_component;

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Vehicle {}
	using namespace Patches::Vehicle;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Vehicle
	{
		extern void ApplyAll();
	}
}

void __fastcall c_vehicle_type_component__handle_deleted_object_hook(c_vehicle_type_component *thisptr, void *__formal, long vehicle_index, long object_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Vehicle
	{
		void ApplyAll() // 0x106A3DF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Vehicle@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x78A820, c_vehicle_type_component__handle_deleted_object_hook).Apply();
		}
	}
}

/* ---------- private code */

void __fastcall c_vehicle_type_component__handle_deleted_object_hook(c_vehicle_type_component *thisptr, void *__formal, long vehicle_index, long object_index) // 0x106A3F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_vehicle_type_component__handle_deleted_object_hook@@YIXPAUc_vehicle_type_component@@PAXJJ@Z");
	// `anonymous-namespace'::c_vehicle_type_component__handle_deleted_object_hook
	// long object_index;
	// e_vehicle_type vehicle_type;
	// function call : e_vehicle_type (*const)(long)
	// function call : void (*const)(c_vehicle_auto_turret *, long, long)
	// function call : void (*const)(c_vehicle_auto_turret *, long, long)

	e_vehicle_type vehicle_type = ((e_vehicle_type (*)(long))0xB75EE0)(vehicle_index);
	if (vehicle_type == _vehicle_type_turret)
		((void (__thiscall *)(c_vehicle_auto_turret *, long, long))0xBBFFC0)(&thisptr->get<c_vehicle_type_turret>()->auto_turret, vehicle_index, object_index);
	else if (vehicle_type == _vehicle_type_guardian)
		((void (__thiscall *)(c_vehicle_auto_turret *, long, long))0xBBFFC0)(&thisptr->get<c_vehicle_type_guardian>()->auto_turret, vehicle_index, object_index);
}
