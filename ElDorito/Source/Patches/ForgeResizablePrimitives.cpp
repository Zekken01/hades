/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/breakable_surfaces.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/collision_model.hpp"
#include "Blam/physics/havok_component.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleForge.hpp"
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

/* ---------- forward declarations */

class c_havok_component;
struct collision_bsp;
struct collision_model_instance;
struct collision_model_test_vector_result;
struct hkMatrix3;
struct hkMatrix4;
struct hkVector4;
struct hkpBoxShape;
struct hkpEntity;
struct hkpShape;
struct real_matrix4x3;
struct real_vector3d;
struct s_breakable_surface_set;
struct s_collision_materials_extant_flags;
struct s_globals;
struct s_object_data;
struct s_object_definition;
namespace Modules
{
	class ModuleForge;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace ForgeResizablePrimitives {}
	using namespace Patches::ForgeResizablePrimitives;
}

/* ---------- constants */

/* ---------- definitions */

struct s_globals
{
	bool valid_bsp; // 0x0
	collision_bsp collision_bsp; // 0x4
};
// static_assert(sizeof(s_globals) == 100, "Invalid s_globals size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

namespace Patches
{
	namespace ForgeResizablePrimitives
	{
		extern void ApplyAll();
	}
}

bool object_is_resizable_box_primitive(long object_index);
real_vector3d get_test_dimensions();
bool collision_model_test_vector_hook(collision_model_instance *instance, unsigned long flags, real_vector3d *origin, real_vector3d *vector, collision_model_test_vector_result *out_result);
bool collision_bsp_test_surface_hook(struct collision_bsp *bsp, s_collision_materials_extant_flags *materials_extant_flags, short breakable_surface_set_count, s_breakable_surface_set *breakable_surface_sets, real_vector3d *origin, real_vector3d *vector, long bsp_leaf_index, long plane_index, float scale, bool flag);
real_matrix4x3 *object_compute_render_time_node_matrices_hook(long object_index, long render_model_definition_index, long unused, real_matrix4x3 *out_matrix);
bool fast_vector_intersects_sphere_hook(real_vector3d *origin, real_vector3d *vector, real_vector3d *p, float r);
bool object_compute_bounds_hook(long object_index);
hkpEntity *c_havok_component__build_rigid_body(c_havok_component *thisptr, void *unused, hkpShape *shape, float allowed_penetration_depth_scale, char is_static, hkVector4 *center_of_mass_local, float friction, float restitution, hkMatrix3 *inertia_tensor, float mass, long motion_type, hkMatrix4 *transform, unsigned long collision_filter, __int32 a13, bool only_collides_with_environment, float maximum_linear_velocity, float maximum_angular_velocity);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern real_vector3d global_zero3d; // 0x11197984
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace ForgeResizablePrimitives
	{
		_extern void _sub_10916FF0();
		void ApplyAll() // 0x10916FF0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@ForgeResizablePrimitives@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10916FF0();
		}
	}
}

/* ---------- private code */

bool object_is_resizable_box_primitive(long object_index) // 0x10918450
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_is_resizable_box_primitive@@YA_NJ@Z");
	// `anonymous-namespace'::object_is_resizable_box_primitive
	// long object_index;

	return false;
}

extern real_vector3d _sub_10917FF0();
real_vector3d get_test_dimensions() // 0x10917FF0
{
	// `anonymous-namespace'::get_test_dimensions
	// procedure flags: nofpo
	// Modules::ModuleForge const &mod;
	todo("implement");
	real_vector3d __result = _sub_10917FF0();
	return __result;
}

bool collision_model_test_vector_hook(collision_model_instance *instance, unsigned long flags, real_vector3d *origin, real_vector3d *vector, collision_model_test_vector_result *out_result) // 0x10917EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?collision_model_test_vector_hook@@YA_NPAUcollision_model_instance@@KPAUreal_vector3d@@1PAUcollision_model_test_vector_result@@@Z");
	// `anonymous-namespace'::collision_model_test_vector_hook
	// collision_model_test_vector_result *out_result;
	// constexpr bool (*const `collision_model_test_vector_hook'::`2'::collision_model_test_vector)(collision_model_instance *, unsigned long, real_vector3d *, real_vector3d *, collision_model_test_vector_result *); // constant == 9965856
	// bool result;
	// function call : bool (*const)(collision_model_instance *, unsigned long, real_vector3d *, real_vector3d *, collision_model_test_vector_result *)

	bool (__cdecl *const collision_model_test_vector)(collision_model_instance *, unsigned long, real_vector3d *, real_vector3d *, collision_model_test_vector_result *) = (bool(__cdecl *const)(collision_model_instance *, unsigned long, real_vector3d *, real_vector3d *, collision_model_test_vector_result *))0x981120;

	return collision_model_test_vector(instance, flags, origin, vector, out_result);
}

_extern bool _sub_10917E00(struct collision_bsp *, s_collision_materials_extant_flags *, short, s_breakable_surface_set *, real_vector3d *, real_vector3d *, long, long, float, bool);
bool collision_bsp_test_surface_hook(struct collision_bsp *bsp, s_collision_materials_extant_flags *materials_extant_flags, short breakable_surface_set_count, s_breakable_surface_set *breakable_surface_sets, real_vector3d *origin, real_vector3d *vector, long bsp_leaf_index, long plane_index, float scale, bool flag) // 0x10917E00
{
	// `anonymous-namespace'::collision_bsp_test_surface_hook
	// bool flag;
	// constexpr bool (*const `collision_bsp_test_surface_hook'::`2'::collision_bsp_test_surface)(struct collision_bsp *, s_collision_materials_extant_flags *, short, s_breakable_surface_set *, real_vector3d *, real_vector3d *, long, long, float, bool); // constant == 9927200
	// function call : bool (*const)(struct collision_bsp *, s_collision_materials_extant_flags *, short, s_breakable_surface_set *, real_vector3d *, real_vector3d *, long, long, float, bool)
	todo("implement");
	bool __result = _sub_10917E00(bsp, materials_extant_flags, breakable_surface_set_count, breakable_surface_sets, origin, vector, bsp_leaf_index, plane_index, scale, flag);
	return __result;
}

extern real_matrix4x3 *_sub_109181E0(long, long, long, real_matrix4x3 *);
real_matrix4x3 *object_compute_render_time_node_matrices_hook(long object_index, long render_model_definition_index, long unused, real_matrix4x3 *out_matrix) // 0x109181E0
{
	// `anonymous-namespace'::object_compute_render_time_node_matrices_hook
	// static ...; // 0x10918398
	// long object_index;
	// long render_model_definition_index;
	// long unused;
	// real_matrix4x3 *out_matrix;
	// __int32 (*object_compute_render_time_node_matrices)(long, long, long, real_matrix4x3 *);
	// real_matrix4x3 *(*object_get_world_matrix)(long, real_matrix4x3 *);
	{
		// real_matrix4x3 scale_matrix;
		// real_vector3d dimensions;
	}
	// function call : __int32 (*)(long, long, long, real_matrix4x3 *)
	// function call : real_matrix4x3 *(*)(long, real_matrix4x3 *)
	todo("implement");
	real_matrix4x3 * __result = _sub_109181E0(object_index, render_model_definition_index, unused, out_matrix);
	return __result;
}

_extern bool _sub_10917F30(real_vector3d *, real_vector3d *, real_vector3d *, float);
bool fast_vector_intersects_sphere_hook(real_vector3d *origin, real_vector3d *vector, real_vector3d *p, float r) // 0x10917F30
{
	mangled_x86(MANGLED_TODO, "?fast_vector_intersects_sphere_hook@@YA_NPAUreal_vector3d@@00M@Z");
	// `anonymous-namespace'::fast_vector_intersects_sphere_hook
	// float r;
	// constexpr bool (*const `fast_vector_intersects_sphere_hook'::`2'::fast_vector_intersects_sphere)(real_vector3d *, real_vector3d *, real_vector3d *, float); // constant == 5183792
	// float n;
	// function call : bool (*const)(real_vector3d *, real_vector3d *, real_vector3d *, float)
	todo("implement");
	bool __result = _sub_10917F30(origin, vector, p, r);
	return __result;
}

_extern bool _sub_10918060(long);
bool object_compute_bounds_hook(long object_index) // 0x10918060
{
	// `anonymous-namespace'::object_compute_bounds_hook
	// long object_index;
	// s_object_data *object;
	// bool (*const object_compute_bounds)(__int32);
	{
		// s_object_definition *object_definition;
		// float old_bounding_radius;
		// float old_dynamic_light_sphere_radius;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(__int32)
	// function call : bool (*const)(__int32)
	todo("implement");
	bool __result = _sub_10918060(object_index);
	return __result;
}

extern hkpEntity *_sub_10917B30(c_havok_component *, void *, hkpShape *, float, char, hkVector4 *, float, float, hkMatrix3 *, float, long, hkMatrix4 *, unsigned long, __int32, bool, float, float);
hkpEntity *c_havok_component__build_rigid_body(c_havok_component *thisptr, void *unused, hkpShape *shape, float allowed_penetration_depth_scale, char is_static, hkVector4 *center_of_mass_local, float friction, float restitution, hkMatrix3 *inertia_tensor, float mass, long motion_type, hkMatrix4 *transform, unsigned long collision_filter, __int32 a13, bool only_collides_with_environment, float maximum_linear_velocity, float maximum_angular_velocity) // 0x10917B30
{
	// `anonymous-namespace'::c_havok_component__build_rigid_body
	// __int32 a13;
	// bool only_collides_with_environment;
	// float maximum_linear_velocity;
	// float maximum_angular_velocity;
	// constexpr hkpEntity *(*const `c_havok_component__build_rigid_body'::`2'::c_havok_component__build_rigid_body)(c_havok_component *, hkpShape *, float, bool, hkVector4 *, float, float, hkMatrix3 *, float, long, hkMatrix4 *, unsigned long, __int32, bool, float, float); // constant == 6175824
	{
		// static hkpBoxShape `c_havok_component__build_rigid_body'::`5'::new_shape; // 0x12409510
		// real_vector3d dimensions;
	}
	// function call : hkpEntity *(*const)(c_havok_component *, hkpShape *, float, bool, hkVector4 *, float, float, hkMatrix3 *, float, long, hkMatrix4 *, unsigned long, __int32, bool, float, float)
	todo("implement");
	hkpEntity * __result = _sub_10917B30(thisptr, unused, shape, allowed_penetration_depth_scale, is_static, center_of_mass_local, friction, restitution, inertia_tensor, mass, motion_type, transform, collision_filter, a13, only_collides_with_environment, maximum_linear_velocity, maximum_angular_velocity);
	return __result;
}
