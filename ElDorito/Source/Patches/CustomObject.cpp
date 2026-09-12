/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/physics/collision_test.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
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

struct real_vector3d;
struct s_collision_result;
struct s_object_type_definition;
namespace hades_file_local
{
	struct s_custom_object_data_definition;
}
using namespace hades_file_local;

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace CustomObjects {}
	using namespace Patches::CustomObjects;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct s_custom_object_data_definition :
		public s_object_type_definition
	{
	};
	#pragma pack(pop)
	static_assert(sizeof(s_custom_object_data_definition) == 244, "Invalid s_custom_object_data_definition size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace CustomObjects
	{
		extern void ApplyAll();
	}
}

bool object_test_vector_hook(unsigned long flags, unsigned long collision_flags, bool a3, real_vector3d *origin, real_vector3d *vector, long ignore_object_index1, long ignore_object_index2, long ignore_object_index3, s_collision_result *results);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern s_object_type_definition *g_object_type_definitions[16]; // 0x11353250
	extern s_custom_object_data_definition g_custom_object_data_definition; // 0x12409370
	extern s_object_type_definition const *g_first_object_type_definition; // 0x12409464
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace CustomObjects
	{
		_extern void _sub_10914A40();
		void ApplyAll() // 0x10914A40
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@CustomObjects@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10914A40();
		}
	}
}

/* ---------- private code */

bool object_test_vector_hook(unsigned long flags, unsigned long collision_flags, bool a3, real_vector3d *origin, real_vector3d *vector, long ignore_object_index1, long ignore_object_index2, long ignore_object_index3, s_collision_result *results) // 0x10916500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_test_vector_hook@@YA_NKK_NPAUreal_vector3d@@1JJJPAUs_collision_result@@@Z");
	// `anonymous-namespace'::object_test_vector_hook
	// s_collision_result *results;
	// constexpr bool (*const `object_test_vector_hook'::`2'::object_test_vector)(unsigned long, unsigned long, bool, real_vector3d *, real_vector3d *, long, long, long, s_collision_result *); // constant == 7172496
	// function call : bool (*const)(unsigned long, unsigned long, bool, real_vector3d *, real_vector3d *, long, long, long, s_collision_result *)

	if ((collision_flags & 1) != 0)
	{
		collision_flags |= 0x10000;
	}
	return ((bool(__cdecl *)(unsigned long, unsigned long, bool, real_vector3d *, real_vector3d *, long, long, long, s_collision_result *))0x6d7190)(flags, collision_flags, false, origin, vector, ignore_object_index1, ignore_object_index2, -1, results);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::Write<int>(__int32 const) const;
template void Pointer::Write<s_object_type_definition * *>(s_object_type_definition **const) const;
template void Pointer::Write<s_object_type_definition const *>(s_object_type_definition const *const) const;
