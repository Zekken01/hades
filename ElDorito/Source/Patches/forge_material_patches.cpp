/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_component.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
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

class c_havok_component;
struct hkpEntity;
struct hkpShape;
struct real_vector3d;
struct s_forge_globals_definition;
struct s_forge_material_type;
struct s_multiplayer_object_properties;
struct s_object_data;
namespace Forge
{
	struct ReforgeObjectProperties;
}
namespace hades_file_local
{
	struct c_global_material_type;
}
using namespace hades_file_local;

namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Reforge {}
	using namespace Forge::Reforge;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct c_global_material_type
	{
		short material_index; // 0x0
	};
	static_assert(sizeof(c_global_material_type) == 2, "Invalid c_global_material_type size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Forge { namespace Reforge { extern bool IsReforgeObject(long objectIndex); } }  // hades: added for 0x10918AD0

extern void forge_material_patches_apply();

bool object_is_reforge_object(long object_index);
bool reforge_get_object_global_material_override(long object_index, s_forge_material_type **out_type);
long __fastcall sub_5E0EA0_hook(void *thisptr, void *unused, short a2, char a3, char a4, __int32 a5, __int32 a6, long object_index, bool a8, long a9, long a10, float a11, float a12, c_global_material_type global_material_type_a, c_global_material_type global_material_type_b);
c_global_material_type *collision_get_global_material_index(c_global_material_type *global_material_type, long object_index, long material_index);
void calculate_havok_shape_properties_hook2(hkpShape *shape, hkpEntity *rigidbody, real_vector3d *position, __int32 a4, float *out_friction, float *out_restitution, c_global_material_type *out_global_material_type);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_109186F0();
void forge_material_patches_apply() // 0x109186F0
{
	mangled_x86(MANGLED_TODO, "?forge_material_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_109186F0();
}

/* ---------- private code */

bool object_is_reforge_object(long object_index) // 0x10918AD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_is_reforge_object@@YA_NJ@Z");
	// `anonymous-namespace'::object_is_reforge_object
	// long object_index;

	return Forge::Reforge::IsReforgeObject(object_index);
}

_extern bool _sub_10918B20(long, s_forge_material_type **);
bool reforge_get_object_global_material_override(long object_index, s_forge_material_type **out_type) // 0x10918B20
{
	// `anonymous-namespace'::reforge_get_object_global_material_override
	// s_forge_material_type **out_type;
	// s_multiplayer_object_properties *multiplayer_properties;
	// Forge::ReforgeObjectProperties *const reforge_properties;
	// s_forge_globals_definition *forge_globals;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	todo("implement");
	bool __result = _sub_10918B20(object_index, out_type);
	return __result;
}

long __fastcall sub_5E0EA0_hook(void *thisptr, void *unused, short a2, char a3, char a4, __int32 a5, __int32 a6, long object_index, bool a8, long a9, long a10, float a11, float a12, c_global_material_type global_material_type_a, c_global_material_type global_material_type_b) // 0x10918C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sub_5E0EA0_hook@@YIJPAX0FDDHHJ_NJJMMUc_global_material_type@hades_file_local@@2@Z");
	// `anonymous-namespace'::sub_5E0EA0_hook
	// float a11;
	// float a12;
	// c_global_material_type global_material_type_a;
	// c_global_material_type global_material_type_b;
	// s_forge_material_type *material_override;
	// constexpr long (*const `sub_5E0EA0_hook'::`2'::sub_5E0EA0)(void *, short, char, char, __int32, __int32, long, bool, long, long, float, float, c_global_material_type, c_global_material_type); // constant == 6164128
	// function call : long (*const)(void *, short, char, char, __int32, __int32, long, bool, long, long, float, float, c_global_material_type, c_global_material_type)

	s_forge_material_type *material_type;
	if (reforge_get_object_global_material_override(object_index, &material_type))
	{
		global_material_type_b.material_index = material_type->physics_global_material_type;
	}

	return ((long (__thiscall *)(void *, short, char, char, __int32, __int32, long, bool, long, long, float, float, c_global_material_type, c_global_material_type))0x5E0EA0)(thisptr, a2, a3, a4, a5, a6, object_index, a8, a9, a10, a11, a12, global_material_type_a, global_material_type_b);
}

c_global_material_type *collision_get_global_material_index(c_global_material_type *global_material_type, long object_index, long material_index) // 0x10918610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?collision_get_global_material_index@@YAPAUc_global_material_type@hades_file_local@@PAU12@JJ@Z");
	// `anonymous-namespace'::collision_get_global_material_index
	// static ...; // 0x10918698
	// c_global_material_type *global_material_type;
	// long object_index;
	// long material_index;
	// constexpr c_global_material_type *(*const `collision_get_global_material_index'::`2'::object_get_material)(c_global_material_type *, __int32, __int32); // constant == 11893056
	// s_forge_material_type *material_override;
	// function call : c_global_material_type *(*const)(c_global_material_type *, __int32, __int32)

	s_forge_material_type *material_override;

	if (!reforge_get_object_global_material_override(object_index, &material_override))
	{
		return ((c_global_material_type *(*)(c_global_material_type *, long, long))0xB57940)(global_material_type, object_index, material_index);
	}

	global_material_type->material_index = material_override->collision_global_material_type;
	return global_material_type;
}

_extern void _sub_109184D0(hkpShape *, hkpEntity *, real_vector3d *, __int32, float *, float *, c_global_material_type *);
void calculate_havok_shape_properties_hook2(hkpShape *shape, hkpEntity *rigidbody, real_vector3d *position, __int32 a4, float *out_friction, float *out_restitution, c_global_material_type *out_global_material_type) // 0x109184D0
{
	// `anonymous-namespace'::calculate_havok_shape_properties_hook2
	// __int32 a4;
	// float *out_friction;
	// float *out_restitution;
	// c_global_material_type *out_global_material_type;
	// constexpr void (*const `calculate_havok_shape_properties_hook2'::`2'::calculate_havok_shape_properties)(hkpShape *, hkpEntity *, real_vector3d *, __int32, float *, float *, c_global_material_type *); // constant == 7424544
	// c_havok_component *havok_component;
	// long havok_component_index;
	{
		// s_forge_material_type *material_override;
	}
	// function call : void (*const)(hkpShape *, hkpEntity *, real_vector3d *, __int32, float *, float *, c_global_material_type *)
	// function call : long (*const)(hkpEntity const *)
	todo("implement");
	_sub_109184D0(shape, rigidbody, position, a4, out_friction, out_restitution, out_global_material_type);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_forge_material_type>::try_get_element(__int32, s_forge_material_type **) const;
template s_forge_material_type & c_tag_block<s_forge_material_type>::operator[](__int32);
template s_forge_material_type * c_tag_block<s_forge_material_type>::get_element(__int32) const;
