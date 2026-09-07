/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_component.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/physics/havok_utilities.hpp"
#include "Blam/physics/physics_model.hpp"
#include "Blam/physics/physics_shapes.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "Blam/visibility/visibility.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
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
struct c_character_physics_mode_ground_datum;
struct c_convex_vertices_shape_with_material;
struct c_decomposed_poop_shape;
struct c_environment_surface_shape;
struct c_havok_contact_point;
struct hkShapeContainer;
struct hkTransform;
struct hkpCdBody;
struct hkpCollidable;
struct hkpConvexTransformShape;
struct hkpEntity;
struct hkpShape;
struct hkpWorldCinfo;
struct hkpkWorld;
struct real_matrix4x3;
struct real_point3d;
struct real_vector3d;
struct s_character_physics_move_input_datum;
struct s_global_material_definition;
struct s_havok_contact_point_reference;
struct s_instanced_geometry_definition_extra_data;
struct s_instanced_geometry_physics_definition;
struct s_object_data;
struct s_physics_model_primitive;
struct s_scenario_structure_bsp;
struct s_structure_bsp_resources;
struct s_structure_instanced_geometry_definition;
struct s_structure_instanced_geometry_instance;
struct s_unit_data;

namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Reforge {}
	using namespace Forge::Reforge;
}

/* ---------- constants */

/* ---------- definitions */

typedef unsigned char hkUint8;
typedef char hkint8;

/* ---------- prototypes */

extern void physics_patches_apply();

bool havok_broadphase_reforge_barrier_object_test(long havok_component_index_a, long havok_component_index_b);
bool havok_broadphase_collidables_test(hkpCollidable *collidable_a, hkpCollidable *collidable_b);
hkpEntity *havok_collidable_get_entity(hkpCollidable *collidable);
bool *hkCollidableCollidableFilte__isCollisionEnabled(void *thisptr, void *unused, bool *a2, hkpCollidable *collidable_a, hkpCollidable *collidable_b);
bool c_environment_surface_shape__is_key_alive_hook(long structure_bsp_index, long a2, bool a3, unsigned __int32 key);
hkpShape const *c_environment_surface_shape__getChildShape_hook(hkShapeContainer *thisptr, void *__formal, unsigned __int32 key, char (&buffer)[512]);
short get_structure_global_material_type(s_scenario_structure_bsp const *structure, long material_index);
void calculate_havok_shape_properties_hook(hkpShape *shape, hkpEntity *body, real_vector3d *position, long shape_key, float *out_friction, float *out_restitution, unsigned short *out_global_material_type);
s_physics_model_primitive *physics_model_primitive_get(hkpShape *shape);
_inline hkpCdBody *havok_get_root_cdbody(hkpCdBody *body);
bool c_group_filter__collidable_b_evalulate_primitive_collision_group_hook(void *this_, void *__formal, hkpCollidable *body_a, hkpCollidable *body_b, hkpShape *shape_b, bool *out_is_enabled);
short *c_havok_contact_point__calculate_global_material_type_b_hook(c_havok_contact_point *this_, void *__formal, short *global_material_type);
void c_havok_contact_point__get_surface_normal_hook(c_havok_contact_point *this_, void *__formal, real_vector3d *out_normal);
void c_character_physics_mode_ground_datum__update_internal_hook(void *thisptr, void *__formal, char *output, char *input, bool a4, real_vector3d *a5);
void hkpWorld_ctor_hook(hkpkWorld *thisptr, void *__formal, hkpWorldCinfo *info, unsigned __int32 sdkVersion);
bool c_character_physics_mode_ground_datum__calculate_ground_contact_hook(c_character_physics_mode_ground_datum *thisptr, void *__formal, s_character_physics_move_input_datum *physics_input, bool a3, real_vector3d *linear_velocity_input, real_vector3d *out_ground_plane, s_havok_contact_point_reference *out_contact_point, float *out_landing_velocity, long *out_contact_object_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10AAB7B0();
void physics_patches_apply() // 0x10AAB7B0
{
	mangled_x86(MANGLED_TODO, "?physics_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10AAB7B0();
}

/* ---------- private code */

_extern bool _sub_10AAB080(long, long);
bool havok_broadphase_reforge_barrier_object_test(long havok_component_index_a, long havok_component_index_b) // 0x10AAB080
{
	// `anonymous-namespace'::havok_broadphase_reforge_barrier_object_test
	// long havok_component_index_b;
	// long object_index_b;
	// s_object_data *object_a;
	// long unit_index;
	// long object_index_a;
	// long barrier_object_index;
	// c_havok_component *havok_component_a;
	// s_object_data *object_b;
	// c_havok_component *havok_component_b;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	bool __result = _sub_10AAB080(havok_component_index_a, havok_component_index_b);
	return __result;
}

_extern bool _sub_10AAAEB0(hkpCollidable *, hkpCollidable *);
bool havok_broadphase_collidables_test(hkpCollidable *collidable_a, hkpCollidable *collidable_b) // 0x10AAAEB0
{
	// `anonymous-namespace'::havok_broadphase_collidables_test
	// hkpCollidable *collidable_b;
	// constexpr bool (*const `havok_broadphase_collidables_test'::`2'::sub_5E9980)(c_havok_component *, long); // constant == 6199680
	// hkpEntity *entity_a;
	// hkpEntity *entity_b;
	{
		// long havok_component_index_a;
		// long havok_component_index_b;
	}
	// function call : long (*const)(hkpEntity const *)
	// function call : long (*const)(hkpEntity const *)
	// function call : long (*const)(hkpEntity const *)
	// function call : bool (*const)(c_havok_component *, long)
	todo("implement");
	bool __result = _sub_10AAAEB0(collidable_a, collidable_b);
	return __result;
}

extern hkpEntity *_sub_10AAB250(hkpCollidable *);
hkpEntity *havok_collidable_get_entity(hkpCollidable *collidable) // 0x10AAB250
{
	// `anonymous-namespace'::havok_collidable_get_entity
	// hkpCollidable *collidable;
	// hkpEntity *entity;
	todo("implement");
	hkpEntity * __result = _sub_10AAB250(collidable);
	return __result;
}

_extern bool *_sub_10AAB3F0(void *, void *, bool *, hkpCollidable *, hkpCollidable *);
bool *hkCollidableCollidableFilte__isCollisionEnabled(void *thisptr, void *unused, bool *a2, hkpCollidable *collidable_a, hkpCollidable *collidable_b) // 0x10AAB3F0
{
	// `anonymous-namespace'::hkCollidableCollidableFilte__isCollisionEnabled
	// hkpCollidable *collidable_b;
	// bool *(*const isCollisionEnabled)(void *, bool *, hkpCollidable *, hkpCollidable *);
	// hkpEntity *entity_a;
	// hkpEntity *entity_b;
	{
		// long havok_component_index_a;
		// long havok_component_index_b;
	}
	// function call : bool *(*const)(void *, bool *, hkpCollidable *, hkpCollidable *)
	// function call : long (*const)(hkpEntity const *)
	// function call : long (*const)(hkpEntity const *)
	todo("implement");
	bool * __result = _sub_10AAB3F0(thisptr, unused, a2, collidable_a, collidable_b);
	return __result;
}

_extern bool _sub_10AAA1E0(long, long, bool, unsigned __int32);
bool c_environment_surface_shape__is_key_alive_hook(long structure_bsp_index, long a2, bool a3, unsigned __int32 key) // 0x10AAA1E0
{
	// `anonymous-namespace'::c_environment_surface_shape__is_key_alive_hook
	// unsigned __int32 key;
	// bool (*const c_environment_surface_shape__is_key_alive)(long, long, bool, unsigned __int32);
	{
		// s_structure_instanced_geometry_instance *instance;
		// s_scenario_structure_bsp *structure_bsp;
		// long instance_index;
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : bool (*const)(long, long, bool, unsigned __int32)
	todo("implement");
	bool __result = _sub_10AAA1E0(structure_bsp_index, a2, a3, key);
	return __result;
}

extern hkpShape const *_sub_10AA9E80(hkShapeContainer *, void *, unsigned __int32, char (&)[512]);
hkpShape const *c_environment_surface_shape__getChildShape_hook(hkShapeContainer *thisptr, void *__formal, unsigned __int32 key, char (&buffer)[512]) // 0x10AA9E80
{
	// `anonymous-namespace'::c_environment_surface_shape__getChildShape_hook
	// hkShapeContainer *thisptr;
	// void *__formal;
	// unsigned __int32 key;
	// char (&buffer)[512];
	// hkpShape *(*const c_environment_surface_shape__getChildShape)(hkShapeContainer *, unsigned __int32, char (&)[512]);
	// hkpConvexTransformShape *(*const hkpConvexTransformShape__ctor)(hkpConvexTransformShape *, hkpShape const *, hkTransform const *);
	// void (*const hkReferencedObject__removeReference)(hkpShape *);
	// void (*const hkTransform_from_matrix4x3)(hkTransform *, real_matrix4x3 *);
	// c_environment_surface_shape *environemnt_surface_shape;
	{
		// s_structure_instanced_geometry_instance *instance;
		// s_scenario_structure_bsp *structure_bsp;
		// long instance_index;
		{
			// s_instanced_geometry_physics_definition *instance_physics;
			{
				// c_decomposed_poop_shape *polyhedra_list_shape;
				// hkpShape *sub_shape;
				// hkpConvexTransformShape *transform_shape;
				// hkTransform transform;
				// long polyhedron_index;
				{
					// s_structure_instanced_geometry_definition *instance_definition;
					// s_structure_bsp_resources *tag_resources;
				}
			}
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : void *(*const)(void *)
	// function call : void (*const)(hkpShape *)
	// function call : void (*const)(hkTransform *, real_matrix4x3 *)
	// function call : hkpConvexTransformShape *(*const)(hkpConvexTransformShape *, hkpShape const *, hkTransform const *)
	// function call : hkpShape *(*const)(hkShapeContainer *, unsigned __int32, char (&)[512])
	todo("implement");
	hkpShape const * __result = _sub_10AA9E80(thisptr, __formal, key, buffer);
	return __result;
}

_extern short _sub_10AAAE30(s_scenario_structure_bsp const *, long);
short get_structure_global_material_type(s_scenario_structure_bsp const *structure, long material_index) // 0x10AAAE30
{
	// `anonymous-namespace'::get_structure_global_material_type
	// long material_index;
	todo("implement");
	short __result = _sub_10AAAE30(structure, material_index);
	return __result;
}

_extern void _sub_10AAA960(hkpShape *, hkpEntity *, real_vector3d *, long, float *, float *, unsigned short *);
void calculate_havok_shape_properties_hook(hkpShape *shape, hkpEntity *body, real_vector3d *position, long shape_key, float *out_friction, float *out_restitution, unsigned short *out_global_material_type) // 0x10AAA960
{
	// `anonymous-namespace'::calculate_havok_shape_properties_hook
	// unsigned short *out_global_material_type;
	// void (*const calculate_havok_shape_properties)(hkpShape *, hkpEntity *, real_vector3d *, long, float *, float *, unsigned short *);
	// c_convex_vertices_shape_with_material *unwrapped_shape;
	// long (*const havok_entity_get_structure_bsp_index)(hkpEntity *);
	{
		// long structure_bsp_index;
		{
			// s_scenario_structure_bsp *structure_bsp;
			// s_global_material_definition *global_material;
		}
	}
	// function call : long (*const)(hkpEntity *)
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_global_material_definition *(*const)(short)
	// function call : void (*const)(hkpShape *, hkpEntity *, real_vector3d *, long, float *, float *, unsigned short *)
	todo("implement");
	_sub_10AAA960(shape, body, position, shape_key, out_friction, out_restitution, out_global_material_type);
}

extern s_physics_model_primitive *_sub_10AAB6F0(hkpShape *);
s_physics_model_primitive *physics_model_primitive_get(hkpShape *shape) // 0x10AAB6F0
{
	// `anonymous-namespace'::physics_model_primitive_get
	// hkpShape *shape;
	// hkpShape *unwrapped_shape;
	// unsigned long result;
	todo("implement");
	s_physics_model_primitive * __result = _sub_10AAB6F0(shape);
	return __result;
}

extern hkpCdBody *_sub_10AAB2F0(hkpCdBody *);
_inline hkpCdBody *havok_get_root_cdbody(hkpCdBody *body) // 0x10AAB2F0
{
	// `anonymous-namespace'::havok_get_root_cdbody
	// hkpCdBody *body;
	todo("implement");
	hkpCdBody * __result = _sub_10AAB2F0(body);
	return __result;
}

_extern bool _sub_10AAA300(void *, void *, hkpCollidable *, hkpCollidable *, hkpShape *, bool *);
bool c_group_filter__collidable_b_evalulate_primitive_collision_group_hook(void *this_, void *__formal, hkpCollidable *body_a, hkpCollidable *body_b, hkpShape *shape_b, bool *out_is_enabled) // 0x10AAA300
{
	// `anonymous-namespace'::c_group_filter__collidable_b_evalulate_primitive_collision_group_hook
	// bool *out_is_enabled;
	// bool *(*const hkpGroupFilter__isCollisionEnabled)(void *, bool *, unsigned __int32, unsigned __int32);
	// hkpCollidable *collidable_b;
	// bool primitive_b_has_collision_group;
	// unsigned long collision_filter_a;
	// unsigned long collision_filter_b;
	// s_physics_model_primitive *primitive_a;
	// s_physics_model_primitive *primitive_b;
	// bool primitive_a_has_collision_group;
	// hkpCollidable *collidable_a;
	// function call : bool *(*const)(void *, bool *, unsigned __int32, unsigned __int32)
	todo("implement");
	bool __result = _sub_10AAA300(this_, __formal, body_a, body_b, shape_b, out_is_enabled);
	return __result;
}

_extern short *_sub_10AAA4C0(c_havok_contact_point *, void *, short *);
short *c_havok_contact_point__calculate_global_material_type_b_hook(c_havok_contact_point *this_, void *__formal, short *global_material_type) // 0x10AAA4C0
{
	// `anonymous-namespace'::c_havok_contact_point__calculate_global_material_type_b_hook
	// short *global_material_type;
	// short *(*const global_material_resolve_underwater_material_proxy)(short *, short, real_point3d const *);
	// short *(*const collision_calculate_structure_global_material_type)(short *, long, real_point3d const *, long, long);
	{
		// long identifier_value;
		{
			// long surface_index;
		}
		{
			// s_structure_instanced_geometry_instance *instance;
			// long sub_index;
			// s_scenario_structure_bsp *structure_bsp;
			// long instance_index;
			{
				// s_instanced_geometry_physics_definition *instance_physics;
				{
					// s_structure_instanced_geometry_definition *instance_definition;
					// s_structure_bsp_resources *bsp_resources;
					// s_instanced_geometry_definition_extra_data *extra_data;
				}
			}
		}
	}
	// function call : short *(*const)(short *, long, real_point3d const *, long, long)
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : void *(*const)(void *)
	// function call : short *(*const)(short *, long, real_point3d const *, long, long)
	// function call : short *(*const)(short *, short, real_point3d const *)
	todo("implement");
	short * __result = _sub_10AAA4C0(this_, __formal, global_material_type);
	return __result;
}

_extern void _sub_10AAA7F0(c_havok_contact_point *, void *, real_vector3d *);
void c_havok_contact_point__get_surface_normal_hook(c_havok_contact_point *this_, void *__formal, real_vector3d *out_normal) // 0x10AAA7F0
{
	// `anonymous-namespace'::c_havok_contact_point__get_surface_normal_hook
	// real_vector3d *out_normal;
	// void (*const c_havok_contact_point__get_surface_normal)(c_havok_contact_point *, real_vector3d *);
	{
		// s_structure_instanced_geometry_instance *instance;
		// long sub_index;
		// s_scenario_structure_bsp *structure_bsp;
		// long instance_index;
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : void (*const)(c_havok_contact_point *, real_vector3d *)
	todo("implement");
	_sub_10AAA7F0(this_, __formal, out_normal);
}

_extern void _sub_10AA9D50(void *, void *, char *, char *, bool, real_vector3d *);
void c_character_physics_mode_ground_datum__update_internal_hook(void *thisptr, void *__formal, char *output, char *input, bool a4, real_vector3d *a5) // 0x10AA9D50
{
	// `anonymous-namespace'::c_character_physics_mode_ground_datum__update_internal_hook
	// real_vector3d *a5;
	// float const old_velocity_scale;
	// void (*const c_character_physics_mode_ground_datum__update_internal)(void *, char *, char *, bool, real_vector3d *);
	// float &velocity_scale;
	// function call : long (*const)()
	// function call : void (*const)(void *, char *, char *, bool, real_vector3d *)
	todo("implement");
	_sub_10AA9D50(thisptr, __formal, output, input, a4, a5);
}

_extern void _sub_10AAB570(hkpkWorld *, void *, hkpWorldCinfo *, unsigned __int32);
void hkpWorld_ctor_hook(hkpkWorld *thisptr, void *__formal, hkpWorldCinfo *info, unsigned __int32 sdkVersion) // 0x10AAB570
{
	// `anonymous-namespace'::hkpWorld_ctor_hook
	// unsigned __int32 sdkVersion;
	// void (*const hkpWorld_ctor)(hkpkWorld *, hkpWorldCinfo *, unsigned __int32);
	// float const tick_rate_scale;
	// function call : long (*const)()
	// function call : void (*const)(hkpkWorld *, hkpWorldCinfo *, unsigned __int32)
	todo("implement");
	_sub_10AAB570(thisptr, __formal, info, sdkVersion);
}

_extern bool _sub_10AA9BF0(c_character_physics_mode_ground_datum *, void *, s_character_physics_move_input_datum *, bool, real_vector3d *, real_vector3d *, s_havok_contact_point_reference *, float *, long *);
bool c_character_physics_mode_ground_datum__calculate_ground_contact_hook(c_character_physics_mode_ground_datum *thisptr, void *__formal, s_character_physics_move_input_datum *physics_input, bool a3, real_vector3d *linear_velocity_input, real_vector3d *out_ground_plane, s_havok_contact_point_reference *out_contact_point, float *out_landing_velocity, long *out_contact_object_index) // 0x10AA9BF0
{
	// `anonymous-namespace'::c_character_physics_mode_ground_datum__calculate_ground_contact_hook
	// long *out_contact_object_index;
	// c_havok_component const *havok_component;
	// s_unit_data const *unit;
	// bool (*const c_character_physics_mode_ground_datum__calculate_ground_contact)(c_character_physics_mode_ground_datum *, s_character_physics_move_input_datum *, bool, real_vector3d const *, real_vector3d *, s_havok_contact_point_reference *, float *, long *);
	{
		// long jump_start_time;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)()
	// function call : bool (*const)(c_character_physics_mode_ground_datum *, s_character_physics_move_input_datum *, bool, real_vector3d const *, real_vector3d *, s_havok_contact_point_reference *, float *, long *)
	todo("implement");
	bool __result = _sub_10AA9BF0(thisptr, __formal, physics_input, a3, linear_velocity_input, out_ground_plane, out_contact_point, out_landing_velocity, out_contact_object_index);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<c_convex_vertices_shape_with_material>::try_get_element(__int32, c_convex_vertices_shape_with_material **) const;
template bool c_tag_block<c_decomposed_poop_shape>::try_get_element(__int32, c_decomposed_poop_shape **) const;
template bool c_tag_block<s_instanced_geometry_definition_extra_data>::try_get_element(__int32, s_instanced_geometry_definition_extra_data **) const;
template bool c_tag_block<s_instanced_geometry_physics_definition>::try_get_element(__int32, s_instanced_geometry_physics_definition **) const;
template c_convex_vertices_shape_with_material & c_tag_block<c_convex_vertices_shape_with_material>::operator[](__int32);
template c_convex_vertices_shape_with_material * c_tag_block<c_convex_vertices_shape_with_material>::get_element(__int32) const;
template c_decomposed_poop_shape & c_tag_block<c_decomposed_poop_shape>::operator[](__int32);
template c_decomposed_poop_shape * c_tag_block<c_decomposed_poop_shape>::get_element(__int32) const;
template s_instanced_geometry_definition_extra_data & c_tag_block<s_instanced_geometry_definition_extra_data>::operator[](__int32);
template s_instanced_geometry_definition_extra_data * c_tag_block<s_instanced_geometry_definition_extra_data>::get_element(__int32) const;
template s_instanced_geometry_physics_definition & c_tag_block<s_instanced_geometry_physics_definition>::operator[](__int32);
template s_instanced_geometry_physics_definition * c_tag_block<s_instanced_geometry_physics_definition>::get_element(__int32) const;
template s_structure_collision_material const & c_tag_block<s_structure_collision_material>::operator[](__int32) const;
