/* ---------- headers */

#include "Blam/physics/physics_shapes.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/physics/havok_utilities.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>

/* ---------- forward declarations */

struct c_convex_vertices_shape_with_material;
struct c_convex_vertices_shape_with_material_impl;
struct c_decomposed_poop_shape;
struct c_decomposed_poop_shape_impl;
struct c_scaled_convex_vertices_shape;
struct c_scaled_convex_vertices_shape_impl;
struct hkAabb;
struct hkShapeContainer;
struct hkTransform;
struct hkVector4;
struct hkpShape;
struct hkpShapeRayCastInput;
struct hkpShapeRayCastOutput;
struct s_havok_convex_shape_vtable;
struct s_havok_shape_container_vtable;
struct s_havok_shape_vtable;
struct s_instanced_geometry_definition_extra_data;
struct s_structure_instanced_geometry_definition;

/* ---------- constants */

/* ---------- definitions */

// s_havok_shape_vtable is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_havok_convex_shape_vtable is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_havok_shape_container_vtable is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

struct c_scaled_convex_vertices_shape_impl
{
	static _inline c_scaled_convex_vertices_shape *fixup(c_scaled_convex_vertices_shape *shape, c_convex_vertices_shape_with_material *child, float scale);
private:
	static _inline void __fastcall getAabbImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkTransform *transform, float tolerance, hkAabb &aabbOut);
	static _inline bool *__fastcall castRayImpl(c_scaled_convex_vertices_shape *this_, void *__formal, bool *resultOut, hkpShapeRayCastInput const &input, hkpShapeRayCastOutput &ouput);
	static _inline __int32 __fastcall getNumCollisionSpheresImpl(c_scaled_convex_vertices_shape *this_, void *__formal);
	static _inline hkVector4 *__fastcall getCollisionSpheresImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 *buffer);
	static _inline void __fastcall getFirstVertex(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 &vertexOut);
	static _inline void __fastcall getSupportingVertexImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 const &dir, hkVector4 &supportingVertexOut);
	static _inline void __fastcall convertVertexIdsToVerticesImpl(c_scaled_convex_vertices_shape *this_, void *__formal, unsigned short *ids, __int32 numIds, hkVector4 *vertixArrayOut);
	static s_havok_convex_shape_vtable g_vtable_for_hkpShape;
};
static_assert(sizeof(c_scaled_convex_vertices_shape_impl) == 1, "Invalid c_scaled_convex_vertices_shape_impl size");

typedef hkVector4 hkSphere;

struct c_convex_vertices_shape_with_material_impl
{
	static _inline c_convex_vertices_shape_with_material *fixup(c_convex_vertices_shape_with_material *shape, s_structure_instanced_geometry_definition *instance_definition);
};
static_assert(sizeof(c_convex_vertices_shape_with_material_impl) == 1, "Invalid c_convex_vertices_shape_with_material_impl size");

struct c_decomposed_poop_shape_impl
{
	static _inline c_decomposed_poop_shape *fixup(c_decomposed_poop_shape *shape, s_structure_instanced_geometry_definition *instance_definition);
private:
	static _inline hkShapeContainer *__fastcall getContainer(c_decomposed_poop_shape *this_);
	static _inline __int32 __fastcall getNumChildShapes(hkShapeContainer *this_);
	static _inline hkpShape *__fastcall getChildShape(hkShapeContainer *this_, void *__formal, unsigned __int32 key, char (&buffer)[512]);
	static s_havok_shape_vtable g_vtable_for_hkpShape;
	static s_havok_shape_container_vtable g_vtable_for_hkpShapeContainer;
};
static_assert(sizeof(c_decomposed_poop_shape_impl) == 1, "Invalid c_decomposed_poop_shape_impl size");

/* ---------- prototypes */

/* ---------- globals */

s_havok_convex_shape_vtable c_scaled_convex_vertices_shape_impl::g_vtable_for_hkpShape; // 0x1135A338
s_havok_shape_vtable c_decomposed_poop_shape_impl::g_vtable_for_hkpShape; // 0x1135A380
s_havok_shape_container_vtable c_decomposed_poop_shape_impl::g_vtable_for_hkpShapeContainer; // 0x1135A3A8

/* ---------- private variables */

/* ---------- public code */

extern c_scaled_convex_vertices_shape *_sub_10F1B890(c_scaled_convex_vertices_shape *, c_convex_vertices_shape_with_material *, float);
_inline c_scaled_convex_vertices_shape *c_scaled_convex_vertices_shape_impl::fixup(c_scaled_convex_vertices_shape *shape, c_convex_vertices_shape_with_material *child, float scale) // 0x10F1B890
{
	mangled_x86(MANGLED_TODO, "?fixup@c_scaled_convex_vertices_shape_impl@@SAPAUc_scaled_convex_vertices_shape@@PAU2@PAUc_convex_vertices_shape_with_material@@M@Z");
	// float scale;
	todo("implement");
	c_scaled_convex_vertices_shape * __result = _sub_10F1B890(shape, child, scale);
	return __result;
}

_extern void _sub_10F1B9B0(c_scaled_convex_vertices_shape *, void *, hkTransform *, float, hkAabb &);
_inline void __fastcall c_scaled_convex_vertices_shape_impl::getAabbImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkTransform *transform, float tolerance, hkAabb &aabbOut) // 0x10F1B9B0
{
	mangled_x86(MANGLED_TODO, "?getAabbImpl@c_scaled_convex_vertices_shape_impl@@CIXPAUc_scaled_convex_vertices_shape@@PAXPAUhkTransform@@MAAUhkAabb@@@Z");
	// c_scaled_convex_vertices_shape *this_;
	// void *__formal;
	// hkTransform *transform;
	// float tolerance;
	// hkAabb &aabbOut;
	// hkVector4 half_extents;
	// hkVector4 center;
	todo("implement");
	_sub_10F1B9B0(this_, __formal, transform, tolerance, aabbOut);
}

_extern bool *_sub_10F1B360(c_scaled_convex_vertices_shape *, void *, bool *, hkpShapeRayCastInput const &, hkpShapeRayCastOutput &);
_inline bool *__fastcall c_scaled_convex_vertices_shape_impl::castRayImpl(c_scaled_convex_vertices_shape *this_, void *__formal, bool *resultOut, hkpShapeRayCastInput const &input, hkpShapeRayCastOutput &ouput) // 0x10F1B360
{
	mangled_x86(MANGLED_TODO, "?castRayImpl@c_scaled_convex_vertices_shape_impl@@CIPA_NPAUc_scaled_convex_vertices_shape@@PAXPA_NABUhkpShapeRayCastInput@@AAUhkpShapeRayCastOutput@@@Z");
	// hkpShapeRayCastOutput &ouput;
	// function call : bool *(*)(hkpShape *, bool *, hkpShapeRayCastInput const &, hkpShapeRayCastOutput &)
	todo("implement");
	bool * __result = _sub_10F1B360(this_, __formal, resultOut, input, ouput);
	return __result;
}

_extern __int32 _sub_10F1C0D0(c_scaled_convex_vertices_shape *, void *);
_inline __int32 __fastcall c_scaled_convex_vertices_shape_impl::getNumCollisionSpheresImpl(c_scaled_convex_vertices_shape *this_, void *__formal) // 0x10F1C0D0
{
	mangled_x86(MANGLED_TODO, "?getNumCollisionSpheresImpl@c_scaled_convex_vertices_shape_impl@@CIHPAUc_scaled_convex_vertices_shape@@PAX@Z");
	// void *__formal;
	// function call : __int32 (*)(hkpShape *)
	todo("implement");
	__int32 __result = _sub_10F1C0D0(this_, __formal);
	return __result;
}

extern hkVector4 *_sub_10F1BD20(c_scaled_convex_vertices_shape *, void *, hkVector4 *);
_inline hkVector4 *__fastcall c_scaled_convex_vertices_shape_impl::getCollisionSpheresImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 *buffer) // 0x10F1BD20
{
	mangled_x86(MANGLED_TODO, "?getCollisionSpheresImpl@c_scaled_convex_vertices_shape_impl@@CIPAUhkVector4@@PAUc_scaled_convex_vertices_shape@@PAXPAU2@@Z");
	// hkVector4 *buffer;
	// long num_spheres;
	{
		// long i;
	}
	// function call : __int32 (*)(hkpShape *)
	// function call : hkVector4 *(*)(hkpShape *, hkVector4 *)
	todo("implement");
	hkVector4 * __result = _sub_10F1BD20(this_, __formal, buffer);
	return __result;
}

_extern void _sub_10F1BF50(c_scaled_convex_vertices_shape *, void *, hkVector4 &);
_inline void __fastcall c_scaled_convex_vertices_shape_impl::getFirstVertex(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 &vertexOut) // 0x10F1BF50
{
	mangled_x86(MANGLED_TODO, "?getFirstVertex@c_scaled_convex_vertices_shape_impl@@CIXPAUc_scaled_convex_vertices_shape@@PAXAAUhkVector4@@@Z");
	// hkVector4 &vertexOut;
	// function call : void (*)(hkpShape *, hkVector4 &)
	todo("implement");
	_sub_10F1BF50(this_, __formal, vertexOut);
}

_extern void _sub_10F1C150(c_scaled_convex_vertices_shape *, void *, hkVector4 const &, hkVector4 &);
_inline void __fastcall c_scaled_convex_vertices_shape_impl::getSupportingVertexImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 const &dir, hkVector4 &supportingVertexOut) // 0x10F1C150
{
	mangled_x86(MANGLED_TODO, "?getSupportingVertexImpl@c_scaled_convex_vertices_shape_impl@@CIXPAUc_scaled_convex_vertices_shape@@PAXABUhkVector4@@AAU3@@Z");
	// hkVector4 &supportingVertexOut;
	// function call : void (*)(hkpShape *, hkVector4 const &, hkVector4 &)
	todo("implement");
	_sub_10F1C150(this_, __formal, dir, supportingVertexOut);
}

_extern void _sub_10F1B400(c_scaled_convex_vertices_shape *, void *, unsigned short *, __int32, hkVector4 *);
_inline void __fastcall c_scaled_convex_vertices_shape_impl::convertVertexIdsToVerticesImpl(c_scaled_convex_vertices_shape *this_, void *__formal, unsigned short *ids, __int32 numIds, hkVector4 *vertixArrayOut) // 0x10F1B400
{
	mangled_x86(MANGLED_TODO, "?convertVertexIdsToVerticesImpl@c_scaled_convex_vertices_shape_impl@@CIXPAUc_scaled_convex_vertices_shape@@PAXPAGHPAUhkVector4@@@Z");
	// hkVector4 *vertixArrayOut;
	{
		// long i;
	}
	// function call : void (*)(hkpShape *, unsigned short *, __int32, hkVector4 *)
	todo("implement");
	_sub_10F1B400(this_, __formal, ids, numIds, vertixArrayOut);
}

extern c_convex_vertices_shape_with_material *_sub_10F1B5B0(c_convex_vertices_shape_with_material *, s_structure_instanced_geometry_definition *);
_inline c_convex_vertices_shape_with_material *c_convex_vertices_shape_with_material_impl::fixup(c_convex_vertices_shape_with_material *shape, s_structure_instanced_geometry_definition *instance_definition) // 0x10F1B5B0
{
	mangled_x86(MANGLED_TODO, "?fixup@c_convex_vertices_shape_with_material_impl@@SAPAUc_convex_vertices_shape_with_material@@PAU2@PAUs_structure_instanced_geometry_definition@@@Z");
	// s_structure_instanced_geometry_definition *instance_definition;
	// long first_plane_index;
	// s_instanced_geometry_definition_extra_data *extra_data;
	// long first_vertex_index;
	{
		// c_convex_vertices_shape_with_material const *p;
	}
	todo("implement");
	c_convex_vertices_shape_with_material * __result = _sub_10F1B5B0(shape, instance_definition);
	return __result;
}

extern c_decomposed_poop_shape *_sub_10F1B770(c_decomposed_poop_shape *, s_structure_instanced_geometry_definition *);
_inline c_decomposed_poop_shape *c_decomposed_poop_shape_impl::fixup(c_decomposed_poop_shape *shape, s_structure_instanced_geometry_definition *instance_definition) // 0x10F1B770
{
	mangled_x86(MANGLED_TODO, "?fixup@c_decomposed_poop_shape_impl@@SAPAUc_decomposed_poop_shape@@PAU2@PAUs_structure_instanced_geometry_definition@@@Z");
	// s_structure_instanced_geometry_definition *instance_definition;
	todo("implement");
	c_decomposed_poop_shape * __result = _sub_10F1B770(shape, instance_definition);
	return __result;
}

extern hkShapeContainer *_sub_10F1BED0(c_decomposed_poop_shape *);
_inline hkShapeContainer *__fastcall c_decomposed_poop_shape_impl::getContainer(c_decomposed_poop_shape *this_) // 0x10F1BED0
{
	mangled_x86(MANGLED_TODO, "?getContainer@c_decomposed_poop_shape_impl@@CIPAUhkShapeContainer@@PAUc_decomposed_poop_shape@@@Z");
	// c_decomposed_poop_shape *this_;
	todo("implement");
	hkShapeContainer * __result = _sub_10F1BED0(this_);
	return __result;
}

_extern __int32 _sub_10F1C030(hkShapeContainer *);
_inline __int32 __fastcall c_decomposed_poop_shape_impl::getNumChildShapes(hkShapeContainer *this_) // 0x10F1C030
{
	mangled_x86(MANGLED_TODO, "?getNumChildShapes@c_decomposed_poop_shape_impl@@CIHPAUhkShapeContainer@@@Z");
	// hkShapeContainer *this_;
	// c_decomposed_poop_shape *decomposed_poop;
	// s_structure_instanced_geometry_definition *instance_def;
	// s_instanced_geometry_definition_extra_data *extra_data;
	todo("implement");
	__int32 __result = _sub_10F1C030(this_);
	return __result;
}

extern hkpShape *_sub_10F1BBC0(hkShapeContainer *, void *, unsigned __int32, char (&)[512]);
_inline hkpShape *__fastcall c_decomposed_poop_shape_impl::getChildShape(hkShapeContainer *this_, void *__formal, unsigned __int32 key, char (&buffer)[512]) // 0x10F1BBC0
{
	mangled_x86(MANGLED_TODO, "?getChildShape@c_decomposed_poop_shape_impl@@CIPAUhkpShape@@PAUhkShapeContainer@@PAXIAAY0CAA@D@Z");
	// char (&buffer)[512];
	// s_structure_instanced_geometry_definition *instance_definition;
	// c_convex_vertices_shape_with_material *polyhedron;
	// c_decomposed_poop_shape *decomposed_poop_shape;
	// s_instanced_geometry_definition_extra_data *extra_data;
	todo("implement");
	hkpShape * __result = _sub_10F1BBC0(this_, __formal, key, buffer);
	return __result;
}

_extern void _sub_10F1B820(c_scaled_convex_vertices_shape *, c_convex_vertices_shape_with_material *, float);
void c_scaled_convex_vertices_shape::fixup(c_scaled_convex_vertices_shape *definition, c_convex_vertices_shape_with_material *child, float scale) // 0x10F1B820
{
	mangled_x86(MANGLED_TODO, "?fixup@c_scaled_convex_vertices_shape@@SAXPAU1@PAUc_convex_vertices_shape_with_material@@M@Z");
	// float scale;
	todo("implement");
	_sub_10F1B820(definition, child, scale);
}

_extern void _sub_10F1B710(c_decomposed_poop_shape *, s_structure_instanced_geometry_definition *);
void c_decomposed_poop_shape::fixup(c_decomposed_poop_shape *definition, s_structure_instanced_geometry_definition *instance_definition) // 0x10F1B710
{
	mangled_x86(MANGLED_TODO, "?fixup@c_decomposed_poop_shape@@SAXPAU1@PAUs_structure_instanced_geometry_definition@@@Z");
	// s_structure_instanced_geometry_definition *instance_definition;
	todo("implement");
	_sub_10F1B710(definition, instance_definition);
}

_extern void _sub_10F1B550(c_convex_vertices_shape_with_material *, s_structure_instanced_geometry_definition *);
void c_convex_vertices_shape_with_material::fixup(c_convex_vertices_shape_with_material *definition, s_structure_instanced_geometry_definition *instance_definition) // 0x10F1B550
{
	mangled_x86(MANGLED_TODO, "?fixup@c_convex_vertices_shape_with_material@@SAXPAU1@PAUs_structure_instanced_geometry_definition@@@Z");
	// s_structure_instanced_geometry_definition *instance_definition;
	todo("implement");
	_sub_10F1B550(definition, instance_definition);
}

/* ---------- private code */
