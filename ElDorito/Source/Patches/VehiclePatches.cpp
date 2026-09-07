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

void c_vehicle_type_component__handle_deleted_object_hook(c_vehicle_type_component *thisptr, void *__formal, long vehicle_index, long object_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Vehicle
	{
		_extern void _sub_106A3DF0();
		void ApplyAll() // 0x106A3DF0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Vehicle@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_106A3DF0();
		}
	}
}

/* ---------- private code */

_extern void _sub_106A3F50(c_vehicle_type_component *, void *, long, long);
void c_vehicle_type_component__handle_deleted_object_hook(c_vehicle_type_component *thisptr, void *__formal, long vehicle_index, long object_index) // 0x106A3F50
{
	// `anonymous-namespace'::c_vehicle_type_component__handle_deleted_object_hook
	// long object_index;
	// e_vehicle_type vehicle_type;
	// function call : e_vehicle_type (*const)(long)
	// function call : void (*const)(c_vehicle_auto_turret *, long, long)
	// function call : void (*const)(c_vehicle_auto_turret *, long, long)
	todo("implement");
	_sub_106A3F50(thisptr, __formal, vehicle_index, object_index);
}
