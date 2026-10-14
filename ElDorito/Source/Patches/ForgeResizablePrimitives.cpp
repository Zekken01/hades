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

void matrix4x3_identity(real_matrix4x3 *matrix);  // hades: added for 0x109181E0
void matrix4x3_multiply(real_matrix4x3 const *a, real_matrix4x3 const *b, real_matrix4x3 *result);  // hades: added for 0x109181E0

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10918060
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10918060

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
hkpEntity *__fastcall c_havok_component__build_rigid_body(c_havok_component *thisptr, void *unused, hkpShape *shape, float allowed_penetration_depth_scale, char is_static, hkVector4 *center_of_mass_local, float friction, float restitution, hkMatrix3 *inertia_tensor, float mass, long motion_type, hkMatrix4 *transform, unsigned long collision_filter, __int32 a13, bool only_collides_with_environment, float maximum_linear_velocity, float maximum_angular_velocity);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern real_vector3d global_zero3d; // 0x11197984
	extern s_globals globals; // 0x124094A0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace ForgeResizablePrimitives
	{
		void ApplyAll() // 0x10916FF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@ForgeResizablePrimitives@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x2D8FA6, collision_model_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2D7E1D, collision_model_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x577727, collision_bsp_test_surface_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x61F17E, object_compute_render_time_node_matrices_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2D8F6D, fast_vector_intersects_sphere_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x72A6EA, object_compute_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x72B911, object_compute_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x72D39C, object_compute_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x72D4D4, object_compute_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x72FBA9, object_compute_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x72FF9C, object_compute_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1E2EBC, c_havok_component__build_rigid_body, static_cast<__int32>(HookFlags::IsCall)).Apply();
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

real_vector3d get_test_dimensions() // 0x10917FF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_test_dimensions@@YA?AUreal_vector3d@@XZ");
	// `anonymous-namespace'::get_test_dimensions
	// procedure flags: nofpo
	// Modules::ModuleForge const &mod;

	Modules::ModuleForge &forgeModule = Modules::ModuleForge::Instance();
	return global_zero3d;
}

bool collision_model_test_vector_hook(collision_model_instance *instance, unsigned long flags, real_vector3d *origin, real_vector3d *vector, collision_model_test_vector_result *out_result) // 0x10917EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?collision_model_test_vector_hook@@YA_NPAUcollision_model_instance@@KPAUreal_vector3d@@1PAUcollision_model_test_vector_result@@@Z");
	// `anonymous-namespace'::collision_model_test_vector_hook
	// collision_model_test_vector_result *out_result;
	// constexpr bool (*const `collision_model_test_vector_hook'::`2'::collision_model_test_vector)(collision_model_instance *, unsigned long, real_vector3d *, real_vector3d *, collision_model_test_vector_result *); // constant == 9965856
	// bool result;
	// function call : bool (*const)(collision_model_instance *, unsigned long, real_vector3d *, real_vector3d *, collision_model_test_vector_result *)

	bool result = ((bool(__cdecl *)(collision_model_instance *, unsigned long, real_vector3d *, real_vector3d *, collision_model_test_vector_result *))0x981120)(instance, flags, origin, vector, out_result);

	globals.valid_bsp = false;
	return result;
}

bool collision_bsp_test_surface_hook(struct collision_bsp *bsp, s_collision_materials_extant_flags *materials_extant_flags, short breakable_surface_set_count, s_breakable_surface_set *breakable_surface_sets, real_vector3d *origin, real_vector3d *vector, long bsp_leaf_index, long plane_index, float scale, bool flag) // 0x10917E00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?collision_bsp_test_surface_hook@@YA_NPAUcollision_bsp@@PAUs_collision_materials_extant_flags@@FPAUs_breakable_surface_set@@PAUreal_vector3d@@3JJM_N@Z");
	// `anonymous-namespace'::collision_bsp_test_surface_hook
	// bool flag;
	// constexpr bool (*const `collision_bsp_test_surface_hook'::`2'::collision_bsp_test_surface)(struct collision_bsp *, s_collision_materials_extant_flags *, short, s_breakable_surface_set *, real_vector3d *, real_vector3d *, long, long, float, bool); // constant == 9927200
	// function call : bool (*const)(struct collision_bsp *, s_collision_materials_extant_flags *, short, s_breakable_surface_set *, real_vector3d *, real_vector3d *, long, long, float, bool)

	if (globals.valid_bsp)
		bsp = &globals.collision_bsp;
	return ((bool(__cdecl *)(collision_bsp *, s_collision_materials_extant_flags *, unsigned short, s_breakable_surface_set *, real_vector3d *, real_vector3d *, long, long, float, bool))0x977a20)(bsp, materials_extant_flags, breakable_surface_set_count, breakable_surface_sets, origin, vector, bsp_leaf_index, plane_index, scale, flag);
}

real_matrix4x3 *object_compute_render_time_node_matrices_hook(long object_index, long render_model_definition_index, long unused, real_matrix4x3 *out_matrix) // 0x109181E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_compute_render_time_node_matrices_hook@@YAPAUreal_matrix4x3@@JJJPAU1@@Z");
	// `anonymous-namespace'::object_compute_render_time_node_matrices_hook
	// static ...; // 0x10918398
	// long object_index;
	// long render_model_definition_index;
	// long unused;
	// real_matrix4x3 *out_matrix;
	// __int32 (*object_compute_render_time_node_matrices)(long, long, long, real_matrix4x3 *);
	// real_matrix4x3 *(*object_get_world_matrix)(long, real_matrix4x3 *);
		// real_matrix4x3 scale_matrix;
		// real_vector3d dimensions;
	// function call : __int32 (*)(long, long, long, real_matrix4x3 *)
	// function call : real_matrix4x3 *(*)(long, real_matrix4x3 *)

	real_matrix4x3 *(*object_get_world_matrix)(long, real_matrix4x3 *) = reinterpret_cast<real_matrix4x3 *(*)(long, real_matrix4x3 *)>(0xB2EC60);
	__int32 (*object_compute_render_time_node_matrices)(long, long, long, real_matrix4x3 *) = reinterpret_cast<__int32 (*)(long, long, long, real_matrix4x3 *)>(0xB2C3D0);
	object_compute_render_time_node_matrices(object_index, render_model_definition_index, unused, out_matrix);
	if (object_is_resizable_box_primitive(object_index))
	{
		real_vector3d dimensions = get_test_dimensions();
		real_matrix4x3 scale_matrix;
		matrix4x3_identity(&scale_matrix);
		scale_matrix.forward.i = dimensions.i * 1.10108399f;
		scale_matrix.left.j = dimensions.j * 1.10108399f;
		scale_matrix.up.k = dimensions.k * 1.10108399f;
		scale_matrix.position = real_point3d{ 0.0f, 0.0f, 0.0f };
		matrix4x3_multiply(out_matrix, &scale_matrix, out_matrix);
		object_get_world_matrix(object_index, out_matrix);
		matrix4x3_multiply(out_matrix, &scale_matrix, out_matrix);
	}
	return out_matrix;
}

bool fast_vector_intersects_sphere_hook(real_vector3d *origin, real_vector3d *vector, real_vector3d *p, float r) // 0x10917F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fast_vector_intersects_sphere_hook@@YA_NPAUreal_vector3d@@00M@Z");
	// `anonymous-namespace'::fast_vector_intersects_sphere_hook
	// float r;
	// constexpr bool (*const `fast_vector_intersects_sphere_hook'::`2'::fast_vector_intersects_sphere)(real_vector3d *, real_vector3d *, real_vector3d *, float); // constant == 5183792
	// float n;
	// function call : bool (*const)(real_vector3d *, real_vector3d *, real_vector3d *, float)

	float scale = 10.0f;

	return ((bool(*)(real_vector3d *, real_vector3d *, real_vector3d *, float))0x4F1930)(origin, vector, p, r * scale);
}

bool object_compute_bounds_hook(long object_index) // 0x10918060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_compute_bounds_hook@@YA_NJ@Z");
	// `anonymous-namespace'::object_compute_bounds_hook
	// long object_index;
	// s_object_data *object;
	// bool (*const object_compute_bounds)(__int32);
		// s_object_definition *object_definition;
		// float old_bounding_radius;
		// float old_dynamic_light_sphere_radius;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(__int32)
	// function call : bool (*const)(__int32)

	bool (*const object_compute_bounds)(__int32) = reinterpret_cast<bool (*)(__int32)>(0xB2AB10);
	s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
	if (object_is_resizable_box_primitive(object_index))
	{
		s_object_definition *object_definition = (s_object_definition *)tag_get('obje', object->definition_index);
		float old_bounding_radius = object_definition->bounding_radius;
		float old_dynamic_light_sphere_radius = object_definition->dynamic_light_sphere_radius;
		object_definition->bounding_radius = 10.0f;
		object_definition->dynamic_light_sphere_radius = 10.0f;
		object_compute_bounds(object_index);
		object_definition->bounding_radius = old_bounding_radius;
		object_definition->dynamic_light_sphere_radius = old_dynamic_light_sphere_radius;
	}
	else
		object_compute_bounds(object_index);
	return true;
}

hkpEntity *__fastcall c_havok_component__build_rigid_body(c_havok_component *thisptr, void *unused, hkpShape *shape, float allowed_penetration_depth_scale, char is_static, hkVector4 *center_of_mass_local, float friction, float restitution, hkMatrix3 *inertia_tensor, float mass, long motion_type, hkMatrix4 *transform, unsigned long collision_filter, __int32 a13, bool only_collides_with_environment, float maximum_linear_velocity, float maximum_angular_velocity) // 0x10917B30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_havok_component__build_rigid_body@@YIPAUhkpEntity@@PAVc_havok_component@@PAXPAUhkpShape@@MDPAUhkVector4@@MMPAUhkMatrix3@@MJPAUhkMatrix4@@KH_NMM@Z");
	// `anonymous-namespace'::c_havok_component__build_rigid_body
	// __int32 a13;
	// bool only_collides_with_environment;
	// float maximum_linear_velocity;
	// float maximum_angular_velocity;
	// constexpr hkpEntity *(*const `c_havok_component__build_rigid_body'::`2'::c_havok_component__build_rigid_body)(c_havok_component *, hkpShape *, float, bool, hkVector4 *, float, float, hkMatrix3 *, float, long, hkMatrix4 *, unsigned long, __int32, bool, float, float); // constant == 6175824
		// static hkpBoxShape `c_havok_component__build_rigid_body'::`5'::new_shape; // 0x12409510
		// real_vector3d dimensions;
	// function call : hkpEntity *(*const)(c_havok_component *, hkpShape *, float, bool, hkVector4 *, float, float, hkMatrix3 *, float, long, hkMatrix4 *, unsigned long, __int32, bool, float, float)

	if (object_is_resizable_box_primitive(thisptr->get_object_index()))
	{
		static hkpBoxShape new_shape;
		real_vector3d dimensions = get_test_dimensions();
		new_shape.vftable = reinterpret_cast<void **>(0x165D38C);
		new_shape.m_referenceObject.m_referenceCount = 1;
		new_shape.m_type = 6;
		new_shape.m_halfExtents = { dimensions.i * 0.5f, dimensions.j * 0.5f, dimensions.k * 0.5f, 0.0f };
		new_shape.m_radius = 0.0f;
		new_shape.m_userData = reinterpret_cast<unsigned long>(shape);
		shape = &new_shape;
	}
	return ((hkpEntity *(__thiscall *)(c_havok_component *, hkpShape *, float, bool, hkVector4 *, float, float, hkMatrix3 *, float, long, hkMatrix4 *, unsigned long, __int32, bool, float, float))0x5E3C50)(thisptr, shape, allowed_penetration_depth_scale, is_static, center_of_mass_local, friction, restitution, inertia_tensor, mass, motion_type, transform, collision_filter, a13, only_collides_with_environment, maximum_linear_velocity, maximum_angular_velocity);
}
