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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const tag_resource_get = reinterpret_cast<void *(*)(void *)>(0x563E10);
}

namespace Forge { namespace Reforge { extern bool TeamBarrierTestUnit(long barrierObjectIndex, long unitIndex); } }  // hades: added for 0x10AAB080

extern long (*const havok_entity_get_havok_component_index)(hkpEntity const *);  // hades: added for 0x10AAAEB0
extern long (*const havok_entity_get_havok_component_rigid_body_index)(hkpEntity const *);  // hades: added for 0x10AAAEB0

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10AA9BF0
extern long (*const game_time_get)();  // hades: added for 0x10AA9BF0

extern s_scenario_structure_bsp *(*const global_structure_bsp_get)(long);  // hades: added for 0x10AAA1E0

extern long (*const game_tick_rate)();  // hades: added for 0X10AAB570

extern void physics_patches_apply();

bool havok_broadphase_reforge_barrier_object_test(long havok_component_index_a, long havok_component_index_b);
bool havok_broadphase_collidables_test(hkpCollidable *collidable_a, hkpCollidable *collidable_b);
hkpEntity *havok_collidable_get_entity(hkpCollidable *collidable);
bool *__fastcall hkCollidableCollidableFilte__isCollisionEnabled(void *thisptr, void *unused, bool *a2, hkpCollidable *collidable_a, hkpCollidable *collidable_b);
bool c_environment_surface_shape__is_key_alive_hook(long structure_bsp_index, long a2, bool a3, unsigned __int32 key);
hkpShape const *__fastcall c_environment_surface_shape__getChildShape_hook(hkShapeContainer *thisptr, void *__formal, unsigned __int32 key, char (&buffer)[512]);
short get_structure_global_material_type(s_scenario_structure_bsp const *structure, long material_index);
void calculate_havok_shape_properties_hook(hkpShape *shape, hkpEntity *body, real_vector3d *position, long shape_key, float *out_friction, float *out_restitution, unsigned short *out_global_material_type);
s_physics_model_primitive *physics_model_primitive_get(hkpShape *shape);
_inline hkpCdBody *havok_get_root_cdbody(hkpCdBody *body);
bool __fastcall c_group_filter__collidable_b_evalulate_primitive_collision_group_hook(void *this_, void *__formal, hkpCollidable *body_a, hkpCollidable *body_b, hkpShape *shape_b, bool *out_is_enabled);
short *__fastcall c_havok_contact_point__calculate_global_material_type_b_hook(c_havok_contact_point *this_, void *__formal, short *global_material_type);
void __fastcall c_havok_contact_point__get_surface_normal_hook(c_havok_contact_point *this_, void *__formal, real_vector3d *out_normal);
void __fastcall c_character_physics_mode_ground_datum__update_internal_hook(void *thisptr, void *__formal, char *output, char *input, bool a4, real_vector3d *a5);
void __fastcall hkpWorld_ctor_hook(hkpkWorld *thisptr, void *__formal, hkpWorldCinfo *info, unsigned __int32 sdkVersion);
bool __fastcall c_character_physics_mode_ground_datum__calculate_ground_contact_hook(c_character_physics_mode_ground_datum *thisptr, void *__formal, s_character_physics_move_input_datum *physics_input, bool a3, real_vector3d *linear_velocity_input, real_vector3d *out_ground_plane, s_havok_contact_point_reference *out_contact_point, float *out_landing_velocity, long *out_contact_object_index);

/* ---------- globals */


/* ---------- private variables */

/* ---------- public code */

void physics_patches_apply() // 0x10AAB7B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?physics_patches_apply@@YAXXZ");

	Hook(0x365300, havok_broadphase_collidables_test).Apply();
	Pointer(0x167C474).Write(hkCollidableCollidableFilte__isCollisionEnabled);
	Pointer(0x14EA9F5).Write<int>(0x1000);
	Pointer(0x14EAA28).Write<int>(0x1000);
	Pointer(0x167C040).Write(c_environment_surface_shape__getChildShape_hook);
	Hook(0x35F12A, c_environment_surface_shape__is_key_alive_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x35F1F2, c_environment_surface_shape__is_key_alive_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x35FC3E, c_environment_surface_shape__is_key_alive_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x361832, calculate_havok_shape_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x3151AB, calculate_havok_shape_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x314D2A, calculate_havok_shape_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x36472E, c_group_filter__collidable_b_evalulate_primitive_collision_group_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x364F8E, c_group_filter__collidable_b_evalulate_primitive_collision_group_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1E50C0, c_havok_contact_point__calculate_global_material_type_b_hook).Apply();
	Hook(0x322470, c_havok_contact_point__get_surface_normal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x323932, c_havok_contact_point__get_surface_normal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x7C202E, c_havok_contact_point__get_surface_normal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	*(uint8_t *)0x471A33E = 0x1;
	Patch::NopFill(0x5F3C0C, 5);
	Hook(0x324701, c_character_physics_mode_ground_datum__update_internal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1C60A1, hkpWorld_ctor_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x323C5D, c_character_physics_mode_ground_datum__calculate_ground_contact_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Patch::NopFill(0x5F4B8F, 6);
}

/* ---------- private code */

bool havok_broadphase_reforge_barrier_object_test(long havok_component_index_a, long havok_component_index_b) // 0x10AAB080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_broadphase_reforge_barrier_object_test@@YA_NJJ@Z");

	long unit_index = -1;
	long barrier_object_index = -1;
	c_havok_component *havok_component_a = havok_component_get(havok_component_index_a);
	c_havok_component *havok_component_b = havok_component_get(havok_component_index_b);
	if (!havok_component_a || !havok_component_b)
		return false;
	long object_index_a = havok_component_a->get_object_index();
	long object_index_b = havok_component_b->get_object_index();
	s_object_data *object_a = object_try_and_get_and_verify_type(object_index_a, -1);
	s_object_data *object_b = object_try_and_get_and_verify_type(object_index_b, -1);
	if (!object_a || !object_b)
		return false;
	if ((1 << static_cast<char>(object_a->object_identifier.type)) & 0x2003)
	{
		unit_index = object_index_a;
		barrier_object_index = object_index_b;
	}
	else if ((1 << static_cast<char>(object_b->object_identifier.type)) & 0x2003)
	{
		unit_index = object_index_b;
		barrier_object_index = object_index_a;
	}
	else
	{
		return false;
	}
	return Forge::Reforge::TeamBarrierTestUnit(barrier_object_index, unit_index);
}

bool havok_broadphase_collidables_test(hkpCollidable *collidable_a, hkpCollidable *collidable_b) // 0x10AAAEB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_broadphase_collidables_test@@YA_NPAUhkpCollidable@@0@Z");

	hkpEntity *entity_a = nullptr;
	hkpEntity *entity_b = nullptr;
	if (collidable_a->m_broadPhaseHandle.m_type == 1)
		entity_a = (hkpEntity *)((char *)collidable_a + collidable_a->m_ownerOffset);
	if (collidable_b->m_broadPhaseHandle.m_type == 1)
		entity_b = (hkpEntity *)((char *)collidable_b + collidable_b->m_ownerOffset);
	if (entity_a && entity_b && (entity_b->m_motion.m_type == 7 || entity_b->m_motion.m_type == 6))
	{
		long havok_component_index_b = havok_entity_get_havok_component_index(entity_b);
		long havok_component_index_a = havok_entity_get_havok_component_index(entity_a);
		if (havok_broadphase_reforge_barrier_object_test(havok_component_index_a, havok_component_index_b))
			return true;
		if (havok_component_index_a != -1)
			return ((bool (__thiscall *)(c_havok_component *, long))0x5E9980)(havok_component_get(havok_component_index_a), havok_entity_get_havok_component_rigid_body_index(entity_a));
	}
	return false;
}

hkpEntity *havok_collidable_get_entity(hkpCollidable *collidable) // 0x10AAB250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_collidable_get_entity@@YAPAUhkpEntity@@PAUhkpCollidable@@@Z");

	hkpEntity *entity = nullptr;
	if (collidable->m_broadPhaseHandle.m_type == 1)
		entity = (hkpEntity *)offset_pointer(collidable, collidable->m_ownerOffset);
	else if (collidable->m_broadPhaseHandle.m_type == 2)
		entity = (hkpEntity *)offset_pointer(collidable, -16);
	return entity;
}

bool *__fastcall hkCollidableCollidableFilte__isCollisionEnabled(void *thisptr, void *unused, bool *a2, hkpCollidable *collidable_a, hkpCollidable *collidable_b) // 0x10AAB3F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hkCollidableCollidableFilte__isCollisionEnabled@@YIPA_NPAX0PA_NPAUhkpCollidable@@2@Z");

	bool *(__thiscall *const isCollisionEnabled)(void *, bool *, hkpCollidable *, hkpCollidable *) = reinterpret_cast<bool *(__thiscall *)(void *, bool *, hkpCollidable *, hkpCollidable *)>(0x764F10);
	a2 = isCollisionEnabled(thisptr, a2, collidable_a, collidable_b);
	hkpEntity *entity_a = havok_collidable_get_entity(collidable_a);
	hkpEntity *entity_b = havok_collidable_get_entity(collidable_b);
	if (*a2 && entity_a && entity_b && (entity_b->m_motion.m_type == 7 || entity_b->m_motion.m_type == 6))
	{
		long havok_component_index_a = havok_entity_get_havok_component_index(entity_a);
		long havok_component_index_b = havok_entity_get_havok_component_index(entity_b);
		if (havok_broadphase_reforge_barrier_object_test(havok_component_index_a, havok_component_index_b))
			*a2 = false;
	}
	return a2;
}

bool c_environment_surface_shape__is_key_alive_hook(long structure_bsp_index, long a2, bool a3, unsigned __int32 key) // 0x10AAA1E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_environment_surface_shape__is_key_alive_hook@@YA_NJJ_NI@Z");

	bool (*const c_environment_surface_shape__is_key_alive)(long, long, bool, unsigned __int32) = reinterpret_cast<bool (*)(long, long, bool, unsigned __int32)>(0x75FC50);
	if (key >> 29 == 3)
	{
		long instance_index = key & 0xFFFF;
		s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(structure_bsp_index);
		s_structure_instanced_geometry_instance *instance = &structure_bsp->instanced_geometry_instances[instance_index];
		if (!instance->physics.count || *(long *)instance->physics[0].polyhedra_list_shape > 0)
			return true;
	}
	return c_environment_surface_shape__is_key_alive(structure_bsp_index, a2, a3, key);
}

hkpShape const *__fastcall c_environment_surface_shape__getChildShape_hook(hkShapeContainer *thisptr, void *__formal, unsigned __int32 key, char (&buffer)[512]) // 0x10AA9E80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_environment_surface_shape__getChildShape_hook@@YIPBUhkpShape@@PAUhkShapeContainer@@PAXIAAY0CAA@D@Z");

	hkpShape *(__thiscall *const c_environment_surface_shape__getChildShape)(hkShapeContainer *, unsigned __int32, char (&)[512]) = (hkpShape *(__thiscall *)(hkShapeContainer *, unsigned __int32, char (&)[512]))0x75F1B0;
	hkpConvexTransformShape *(__thiscall *const hkpConvexTransformShape__ctor)(hkpConvexTransformShape *, hkpShape const *, hkTransform const *) = (hkpConvexTransformShape *(__thiscall *)(hkpConvexTransformShape *, hkpShape const *, hkTransform const *))0xC4E7B0;
	void (__thiscall *const hkReferencedObject__removeReference)(hkpShape *) = (void (__thiscall *)(hkpShape *))0x5C2E00;
	void (*const hkTransform_from_matrix4x3)(hkTransform *, real_matrix4x3 *) = (void (*)(hkTransform *, real_matrix4x3 *))0x717850;
	c_environment_surface_shape *environemnt_surface_shape = (c_environment_surface_shape *)havok_shape_from_container(thisptr);
	if ((key >> 29) == 3)
	{
		long instance_index = key & 0xFFFF;
		s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(environemnt_surface_shape->structure_bsp_index);
		s_structure_instanced_geometry_instance *instance = &structure_bsp->instanced_geometry_instances[instance_index];
		if (instance->physics.count > 0)
		{
			s_instanced_geometry_physics_definition *instance_physics = &instance->physics[0];
			if (reinterpret_cast<c_tag_block<c_decomposed_poop_shape> *>(instance_physics->polyhedra_list_shape)->count > 0)
			{
				long polyhedron_index = (key >> 16) & 0x1FFF;
				c_decomposed_poop_shape *polyhedra_list_shape = &(*reinterpret_cast<c_tag_block<c_decomposed_poop_shape> *>(instance_physics->polyhedra_list_shape))[0];
				if (!*reinterpret_cast<void **>(polyhedra_list_shape))
				{
					s_structure_bsp_resources *tag_resources = (s_structure_bsp_resources *)eldorado::tag_resource_get(&structure_bsp->collision_bsp_resource);
					s_structure_instanced_geometry_definition *instance_definition = &tag_resources->instanced_geometry[instance->mesh_index];
					c_decomposed_poop_shape::fixup(polyhedra_list_shape, instance_definition);
				}
				hkpShape *sub_shape = polyhedra_list_shape->getChildShape(polyhedron_index, &buffer[sizeof(hkpConvexTransformShape) * 1]);
				hkReferencedObject__removeReference(sub_shape);
				hkpConvexTransformShape *transform_shape = reinterpret_cast<hkpConvexTransformShape *>(buffer);
				hkTransform transform;
				hkTransform_from_matrix4x3(&transform, &instance->rigid_matrix);
				hkpConvexTransformShape__ctor(transform_shape, sub_shape, &transform);
				return transform_shape;
			}
		}
	}
	return c_environment_surface_shape__getChildShape(thisptr, key, buffer);
}

short get_structure_global_material_type(s_scenario_structure_bsp const *structure, long material_index) // 0x10AAAE30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_structure_global_material_type@@YAFPBUs_scenario_structure_bsp@@J@Z");

	if (material_index < 0 || material_index >= structure->collision_materials.count)
	{
		return 0;
	}

	return structure->collision_materials[material_index].global_materal_type;
}

void calculate_havok_shape_properties_hook(hkpShape *shape, hkpEntity *body, real_vector3d *position, long shape_key, float *out_friction, float *out_restitution, unsigned short *out_global_material_type) // 0x10AAA960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?calculate_havok_shape_properties_hook@@YAXPAUhkpShape@@PAUhkpEntity@@PAUreal_vector3d@@JPAM3PAG@Z");

	long (*const havok_entity_get_structure_bsp_index)(hkpEntity *) = reinterpret_cast<long (*)(hkpEntity *)>(0x5EA980);
	void (*const calculate_havok_shape_properties)(hkpShape *, hkpEntity *, real_vector3d *, long, float *, float *, unsigned short *) = reinterpret_cast<void (*)(hkpShape *, hkpEntity *, real_vector3d *, long, float *, float *, unsigned short *)>(0x714A20);
	c_convex_vertices_shape_with_material *unwrapped_shape = (c_convex_vertices_shape_with_material *)havok_transform_wrapper_shape_get_child_shape(shape);
	if (unwrapped_shape->m_userData == 'poop')
	{
		long structure_bsp_index = havok_entity_get_structure_bsp_index(body);
		if (structure_bsp_index != -1)
		{
			s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(structure_bsp_index);
			if (unwrapped_shape->material_index != -1)
				*out_global_material_type = get_structure_global_material_type(structure_bsp, unwrapped_shape->material_index);
			else
				*out_global_material_type = 0;
			s_global_material_definition *global_material = ((s_global_material_definition *(*)(short))0x5CA640)(*out_global_material_type);
			if (global_material)
			{
				*out_friction = global_material->physics.friction;
				*out_restitution = global_material->physics.restitution;
			}
		}
	}
	else
	{
		calculate_havok_shape_properties(shape, body, position, shape_key, out_friction, out_restitution, out_global_material_type);
	}
}

s_physics_model_primitive *physics_model_primitive_get(hkpShape *shape) // 0x10AAB6F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?physics_model_primitive_get@@YAPAUs_physics_model_primitive@@PAUhkpShape@@@Z");

	if (shape == nullptr)
	{
		return nullptr;
	}
	hkpShape *unwrapped_shape = havok_transform_wrapper_shape_get_child_shape(shape);
	if (unwrapped_shape->m_type == 30)
	{
		return nullptr;
	}
	if (unwrapped_shape->m_userData == 0x706F6F70)
	{
		return nullptr;
	}
	if (!is_havok_convex_shape(unwrapped_shape))
	{
		return nullptr;
	}
	s_physics_model_primitive *primitive = (s_physics_model_primitive *)unwrapped_shape->m_userData;
	if (primitive == nullptr || (unsigned long)primitive <= 0x10)
	{
		return nullptr;
	}
	return primitive;
}

_inline hkpCdBody *havok_get_root_cdbody(hkpCdBody *body) // 0x10AAB2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_get_root_cdbody@@YAPAUhkpCdBody@@PAU1@@Z");

	while (body->m_parent)
	{
		body = body->m_parent;
	}

	return body;
}

bool __fastcall c_group_filter__collidable_b_evalulate_primitive_collision_group_hook(void *this_, void *__formal, hkpCollidable *body_a, hkpCollidable *body_b, hkpShape *shape_b, bool *out_is_enabled) // 0x10AAA300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_group_filter__collidable_b_evalulate_primitive_collision_group_hook@@YI_NPAX0PAUhkpCollidable@@1PAUhkpShape@@PA_N@Z");

	bool *(__thiscall *const hkpGroupFilter__isCollisionEnabled)(void *, bool *, unsigned __int32, unsigned __int32) = reinterpret_cast<bool *(__thiscall *)(void *, bool *, unsigned __int32, unsigned __int32)>(0xC57120);
	s_physics_model_primitive *primitive_a = physics_model_primitive_get(body_a->m_shape);
	s_physics_model_primitive *primitive_b = physics_model_primitive_get(shape_b);
	bool primitive_a_has_collision_group = primitive_a && primitive_a->runtime_collision_group != -1;
	bool primitive_b_has_collision_group = primitive_b && primitive_b->runtime_collision_group != -1;
	if (!primitive_a_has_collision_group && !primitive_b_has_collision_group)
		return false;
	hkpCollidable *collidable_a = (hkpCollidable *)havok_get_root_cdbody(body_a);
	hkpCollidable *collidable_b = (hkpCollidable *)havok_get_root_cdbody(body_b);
	unsigned long collision_filter_a = collidable_a->m_broadPhaseHandle.m_collisionFilterInfo;
	unsigned long collision_filter_b = collidable_b->m_broadPhaseHandle.m_collisionFilterInfo;
	if (primitive_a_has_collision_group)
		collision_filter_a = (collision_filter_a & 0xFFFF0000) | primitive_a->runtime_collision_group;
	if (primitive_b_has_collision_group)
		collision_filter_b = (collision_filter_b & 0xFFFF0000) | primitive_b->runtime_collision_group;
	hkpGroupFilter__isCollisionEnabled(this_, out_is_enabled, collision_filter_b, collision_filter_a);
	return true;
}

short *__fastcall c_havok_contact_point__calculate_global_material_type_b_hook(c_havok_contact_point *this_, void *__formal, short *global_material_type) // 0x10AAA4C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_havok_contact_point__calculate_global_material_type_b_hook@@YIPAFPAUc_havok_contact_point@@PAXPAF@Z");

	short *(*const collision_calculate_structure_global_material_type)(short *, long, real_point3d const *, long, long) = reinterpret_cast<short *(*)(short *, long, real_point3d const *, long, long)>(0x6D3110);
	short *(*const global_material_resolve_underwater_material_proxy)(short *, short, real_point3d const *) = reinterpret_cast<short *(*)(short *, short, real_point3d const *)>(0x5CA820);
	*global_material_type = this_->material_type_b;
	if (this_->shape_key != -1)
	{
		long identifier_value = this_->shape_key >> 29;
		if (identifier_value == 1)
		{
			long surface_index = this_->shape_key & 0x3FFFFFF;
			*global_material_type = *collision_calculate_structure_global_material_type(global_material_type, this_->structure_bsp_index, &this_->position, surface_index, -1);
		}
		else if (identifier_value == 3)
		{
			long instance_index = this_->shape_key & 0xFFFF;
			long sub_index = (this_->shape_key >> 16) & 0x1FFF;
			s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(this_->structure_bsp_index);
			s_structure_instanced_geometry_instance *instance = &structure_bsp->instanced_geometry_instances[instance_index];
			if (instance->physics.count > 0)
			{
				s_instanced_geometry_physics_definition *instance_physics = &instance->physics[0];
				if (((s_tag_block *)instance_physics->polyhedra_list_shape)->count > 0)
				{
					s_structure_bsp_resources *bsp_resources = ((s_structure_bsp_resources *(*)(void *))0x563E10)(&structure_bsp->collision_bsp_resource);
					s_structure_instanced_geometry_definition *instance_definition = &bsp_resources->instanced_geometry[instance->mesh_index];
					s_instanced_geometry_definition_extra_data *extra_data = &instance_definition->extra_data[0];
					if (sub_index >= 0 && sub_index < extra_data->polyhedra.count)
						*global_material_type = get_structure_global_material_type(structure_bsp, extra_data->polyhedra[sub_index].material_index);
				}
				else
				{
					*global_material_type = *collision_calculate_structure_global_material_type(global_material_type, this_->structure_bsp_index, &this_->position, sub_index, instance_index);
				}
			}
		}
	}
	*global_material_type = *global_material_resolve_underwater_material_proxy(global_material_type, *global_material_type, &this_->position);
	return global_material_type;
}

void __fastcall c_havok_contact_point__get_surface_normal_hook(c_havok_contact_point *this_, void *__formal, real_vector3d *out_normal) // 0x10AAA7F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_havok_contact_point__get_surface_normal_hook@@YIXPAUc_havok_contact_point@@PAXPAUreal_vector3d@@@Z");

	void (__thiscall *const c_havok_contact_point__get_surface_normal)(c_havok_contact_point *, real_vector3d *) = reinterpret_cast<void (__thiscall *)(c_havok_contact_point *, real_vector3d *)>(0x5EA160);
	*out_normal = this_->separating_normal;
	if (this_->shape_key == -1)
		return;
	if (this_->shape_key >> 29 == 3)
	{
		long instance_index = this_->shape_key & 0xFFFF;
		long sub_index = (this_->shape_key >> 16) & 0x1FFF;
		s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(this_->structure_bsp_index);
		s_structure_instanced_geometry_instance *instance = &structure_bsp->instanced_geometry_instances[instance_index];
		if (instance->physics.count > 0 && *(long *)instance->physics[0].polyhedra_list_shape > 0)
			return;
	}
	c_havok_contact_point__get_surface_normal(this_, out_normal);
}

void __fastcall c_character_physics_mode_ground_datum__update_internal_hook(void *thisptr, void *__formal, char *output, char *input, bool a4, real_vector3d *a5) // 0x10AA9D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_character_physics_mode_ground_datum__update_internal_hook@@YIXPAX0PAD1_NPAUreal_vector3d@@@Z");

	void (__thiscall *const c_character_physics_mode_ground_datum__update_internal)(void *, char *, char *, bool, real_vector3d *) = (void (__thiscall *const)(void *, char *, char *, bool, real_vector3d *))0x724BB0;

	float *value = (float *)(input + 0xAC);
	float saved = *value;
	if (*value <= 0.0f)
	{
		*value = 1.0f;
	}

	*value *= 30.0f / game_tick_rate();

	c_character_physics_mode_ground_datum__update_internal(thisptr, output, input, a4, a5);

	*value = saved;
}

void __fastcall hkpWorld_ctor_hook(hkpkWorld *thisptr, void *__formal, hkpWorldCinfo *info, unsigned __int32 sdkVersion) // 0x10AAB570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hkpWorld_ctor_hook@@YIXPAUhkpkWorld@@PAXPAUhkpWorldCinfo@@I@Z");

	void (__thiscall *const hkpWorld_ctor)(hkpkWorld *, hkpWorldCinfo *, unsigned __int32) = (void (__thiscall *)(hkpkWorld *, hkpWorldCinfo *, unsigned __int32))0xC7C0E0;
	float scale = 30.0f / game_tick_rate();

	info->m_collisionTolerance = *(float *)0x18A2324 * scale;
	info->m_deactivationReferenceDistance = *(float *)0x18A233C * scale;

	hkpWorld_ctor(thisptr, info, sdkVersion);
}

bool __fastcall c_character_physics_mode_ground_datum__calculate_ground_contact_hook(c_character_physics_mode_ground_datum *thisptr, void *__formal, s_character_physics_move_input_datum *physics_input, bool a3, real_vector3d *linear_velocity_input, real_vector3d *out_ground_plane, s_havok_contact_point_reference *out_contact_point, float *out_landing_velocity, long *out_contact_object_index) // 0x10AA9BF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_character_physics_mode_ground_datum__calculate_ground_contact_hook@@YI_NPAUc_character_physics_mode_ground_datum@@PAXPAUs_character_physics_move_input_datum@@_NPAUreal_vector3d@@4PAUs_havok_contact_point_reference@@PAMPAJ@Z");

	bool (__thiscall *const c_character_physics_mode_ground_datum__calculate_ground_contact)(c_character_physics_mode_ground_datum *, s_character_physics_move_input_datum *, bool, real_vector3d const *, real_vector3d *, s_havok_contact_point_reference *, float *, long *) = reinterpret_cast<bool (__thiscall *)(c_character_physics_mode_ground_datum *, s_character_physics_move_input_datum *, bool, real_vector3d const *, real_vector3d *, s_havok_contact_point_reference *, float *, long *)>(0x7221F0);
	c_havok_component const *havok_component = havok_component_get(*(unsigned long *)offset_pointer(physics_input, 0x58));
	s_unit_data const *unit = (s_unit_data const *)object_try_and_get_and_verify_type(havok_component->get_object_index(), 1);
	if (unit && unit->player_index != -1)
	{
		long jump_start_time = *(long const *)offset_pointer(unit, 0x5EC);
		if (game_time_get() - jump_start_time < 2)
			return false;
	}
	return c_character_physics_mode_ground_datum__calculate_ground_contact(thisptr, physics_input, a3, linear_velocity_input, out_ground_plane, out_contact_point, out_landing_velocity, out_contact_object_index);
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
