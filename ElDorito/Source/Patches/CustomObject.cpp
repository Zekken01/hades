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
	s_object_type_definition const *g_first_object_type_definition = g_object_type_definitions[0]; // 0x12409464
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace CustomObjects
	{
		void ApplyAll() // 0x10914A40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@CustomObjects@Patches@@YAXXZ");
			// procedure flags: nofpo

			g_custom_object_data_definition.name = nullptr;
			g_custom_object_data_definition.group_tag = 'cobj';
			g_custom_object_data_definition.datum_size = 0x178;
			g_custom_object_data_definition.placement_tag_block_offset = -1;
			g_custom_object_data_definition.palette_tag_block_offset = -1;
			g_custom_object_data_definition.placement_tag_block_element_size = -1;
			g_custom_object_data_definition.maximum_placement_count = 0;
			g_custom_object_data_definition.mixing_board_index = -1;
			g_custom_object_data_definition.child_types[0] = reinterpret_cast<s_object_type_definition *>(0x1947F10);
			g_custom_object_data_definition.child_types[1] = nullptr;
			g_object_type_definitions[14]->next_type = &g_custom_object_data_definition;
			Pointer(0x5287BDC).Write<s_object_type_definition const *>(g_first_object_type_definition);
			Pointer(0xB73885).Write(g_object_type_definitions);
			Pointer(0xB742BF).Write(g_object_type_definitions);
			Pointer(0xB74345).Write(g_object_type_definitions);
			Pointer(0xB743F3).Write(g_object_type_definitions);
			Pointer(0xB73BC6).Write(g_object_type_definitions);
			Pointer(0xB736B6).Write(g_object_type_definitions);
			Pointer(0xB731E6).Write(g_object_type_definitions);
			Pointer(0xB73C9C).Write(g_object_type_definitions);
			Pointer(0xB73DF5).Write(g_object_type_definitions);
			Pointer(0xB740B6).Write(g_object_type_definitions);
			Pointer(0xB734B6).Write(g_object_type_definitions);
			Pointer(0xB7353A).Write(g_object_type_definitions);
			Pointer(0xB74127).Write(g_object_type_definitions);
			Pointer(0xB73C32).Write(g_object_type_definitions);
			Pointer(0xB733AA).Write(g_object_type_definitions);
			Pointer(0xB73417).Write(g_object_type_definitions);
			Pointer(0xB73276).Write(g_object_type_definitions);
			Pointer(0xB73646).Write(g_object_type_definitions);
			Pointer(0xB732E1).Write(g_object_type_definitions);
			Pointer(0xB73341).Write(g_object_type_definitions);
			Pointer(0xB735D4).Write(g_object_type_definitions);
			Pointer(0xB739B5).Write(g_object_type_definitions);
			Pointer(0xB73A35).Write(g_object_type_definitions);
			Pointer(0xB73B35).Write(g_object_type_definitions);
			Pointer(0xB73AB4).Write(g_object_type_definitions);
			Pointer(0xB73721).Write(g_object_type_definitions);
			Pointer(0xB737A2).Write(g_object_type_definitions);
			Pointer(0xB73F05).Write(g_object_type_definitions);
			Pointer(0xB73F95).Write(g_object_type_definitions);
			Pointer(0xB73E75).Write(g_object_type_definitions);
			Pointer(0xB74026).Write(g_object_type_definitions);
			Pointer(0xB73D65).Write(g_object_type_definitions);
			Pointer(0xB73D65).Write(g_object_type_definitions);
			Pointer(0xB73939).Write(g_object_type_definitions);
			Pointer(0xB73959).Write(g_object_type_definitions);
			Pointer(0xB73969).Write(g_object_type_definitions);
			Pointer(0xB73919).Write(g_object_type_definitions);
			Pointer(0xB738F9).Write(g_object_type_definitions);
			Pointer(0xB738D9).Write(g_object_type_definitions);
			Pointer(0xB738B3).Write(g_object_type_definitions);
			Pointer(0xB73885).Write(g_object_type_definitions);
			Pointer(0xB734F9).Write(g_object_type_definitions);
			Pointer(0xB968BA).Write<int>(0xFFFF);
			Hook(0x2D717C, object_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2D360E, object_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2D67CF, object_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x73C7B3, object_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7700DB, object_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x77C0E9, object_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2D6831, object_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x5C8278).Write<unsigned long>(*reinterpret_cast<unsigned long *>(0x5C8277) | 0x8000);
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { s_custom_object_data_definition g_custom_object_data_definition; }
