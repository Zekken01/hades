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

_inline c_scaled_convex_vertices_shape *c_scaled_convex_vertices_shape_impl::fixup(c_scaled_convex_vertices_shape *shape, c_convex_vertices_shape_with_material *child, float scale) // 0x10F1B890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup@c_scaled_convex_vertices_shape_impl@@SAPAUc_scaled_convex_vertices_shape@@PAU2@PAUc_convex_vertices_shape_with_material@@M@Z");
	// float scale;

	shape->vftable = (void **)&g_vtable_for_hkpShape;
	shape->m_referenceObject.m_memSizeAndFlags = 0;
	shape->m_referenceObject.m_referenceCount = 128;
	shape->m_userData = 0xFFFF00AB;
	shape->m_type = 1;
	shape->m_radius = child->m_radius;
	shape->child = child;
	shape->scale = hkVector4{ scale, scale, scale, scale };
	return shape;
}

_inline void __fastcall c_scaled_convex_vertices_shape_impl::getAabbImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkTransform *transform, float tolerance, hkAabb &aabbOut) // 0x10F1B9B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getAabbImpl@c_scaled_convex_vertices_shape_impl@@CIXPAUc_scaled_convex_vertices_shape@@PAXPAUhkTransform@@MAAUhkAabb@@@Z");
	// c_scaled_convex_vertices_shape *this_;
	// void *__formal;
	// hkTransform *transform;
	// float tolerance;
	// hkAabb &aabbOut;
	// hkVector4 half_extents;
	// hkVector4 center;

	hkVector4 half_extents = this_->child->m_aabbHalfExtents;
	half_extents.x *= this_->scale.x;
	half_extents.y *= this_->scale.y;
	half_extents.z *= this_->scale.z;
	half_extents.w *= this_->scale.w;
	hkVector4 center = this_->child->m_aabbCenter;
	center.x *= this_->scale.x;
	center.y *= this_->scale.y;
	center.z *= this_->scale.z;
	center.w *= this_->scale.w;
	hkAabbUtil::calcAaab(*transform, half_extents, center, this_->m_radius + tolerance, aabbOut);
}

_inline bool *__fastcall c_scaled_convex_vertices_shape_impl::castRayImpl(c_scaled_convex_vertices_shape *this_, void *__formal, bool *resultOut, hkpShapeRayCastInput const &input, hkpShapeRayCastOutput &ouput) // 0x10F1B360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?castRayImpl@c_scaled_convex_vertices_shape_impl@@CIPA_NPAUc_scaled_convex_vertices_shape@@PAXPA_NABUhkpShapeRayCastInput@@AAUhkpShapeRayCastOutput@@@Z");
	// hkpShapeRayCastOutput &ouput;
	// function call : bool *(*)(hkpShape *, bool *, hkpShapeRayCastInput const &, hkpShapeRayCastOutput &)

	return (*(bool *(__thiscall **)(c_convex_vertices_shape_with_material *, bool *, hkpShapeRayCastInput const &, hkpShapeRayCastOutput &))(this_->child->vftable + 7))(this_->child, resultOut, input, ouput);
}

_inline __int32 __fastcall c_scaled_convex_vertices_shape_impl::getNumCollisionSpheresImpl(c_scaled_convex_vertices_shape *this_, void *__formal) // 0x10F1C0D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getNumCollisionSpheresImpl@c_scaled_convex_vertices_shape_impl@@CIHPAUc_scaled_convex_vertices_shape@@PAX@Z");
	// void *__formal;
	// function call : __int32 (*)(hkpShape *)

	return (*(__int32(__thiscall **)(c_convex_vertices_shape_with_material *))(this_->child->vftable + 8))(this_->child);
}

_inline hkVector4 *__fastcall c_scaled_convex_vertices_shape_impl::getCollisionSpheresImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 *buffer) // 0x10F1BD20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getCollisionSpheresImpl@c_scaled_convex_vertices_shape_impl@@CIPAUhkVector4@@PAUc_scaled_convex_vertices_shape@@PAXPAU2@@Z");
	// hkVector4 *buffer;
	// long num_spheres;
		// long i;
	// function call : __int32 (*)(hkpShape *)
	// function call : hkVector4 *(*)(hkpShape *, hkVector4 *)

	long num_spheres = (*(__int32(__thiscall **)(c_convex_vertices_shape_with_material *))(this_->child->vftable + 8))(this_->child);
	(*(hkVector4 *(__thiscall **)(c_convex_vertices_shape_with_material *, hkVector4 *))(this_->child->vftable + 9))(this_->child, buffer);

	for (long i = 0; i < num_spheres; i++)
	{
		buffer[i].x = buffer[i].x * this_->scale.x;
		buffer[i].y = buffer[i].y * this_->scale.y;
		buffer[i].z = buffer[i].z * this_->scale.z;
		buffer[i].w = buffer[i].w * this_->scale.w;
	}

	return buffer;
}

_inline void __fastcall c_scaled_convex_vertices_shape_impl::getFirstVertex(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 &vertexOut) // 0x10F1BF50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getFirstVertex@c_scaled_convex_vertices_shape_impl@@CIXPAUc_scaled_convex_vertices_shape@@PAXAAUhkVector4@@@Z");
	// hkVector4 &vertexOut;
	// function call : void (*)(hkpShape *, hkVector4 &)

	(*(void (__thiscall **)(c_convex_vertices_shape_with_material *, hkVector4 &))(this_->child->vftable + 10))(this_->child, vertexOut);

	vertexOut.x = vertexOut.x * this_->scale.x;
	vertexOut.y = vertexOut.y * this_->scale.y;
	vertexOut.z = vertexOut.z * this_->scale.z;
}

_inline void __fastcall c_scaled_convex_vertices_shape_impl::getSupportingVertexImpl(c_scaled_convex_vertices_shape *this_, void *__formal, hkVector4 const &dir, hkVector4 &supportingVertexOut) // 0x10F1C150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getSupportingVertexImpl@c_scaled_convex_vertices_shape_impl@@CIXPAUc_scaled_convex_vertices_shape@@PAXABUhkVector4@@AAU3@@Z");
	// hkVector4 &supportingVertexOut;
	// function call : void (*)(hkpShape *, hkVector4 const &, hkVector4 &)

	(*(void (__thiscall **)(c_convex_vertices_shape_with_material *, hkVector4 const &, hkVector4 &))(this_->child->vftable + 11))(this_->child, dir, supportingVertexOut);

	supportingVertexOut.x = supportingVertexOut.x * this_->scale.x;
	supportingVertexOut.y = supportingVertexOut.y * this_->scale.y;
	supportingVertexOut.z = supportingVertexOut.z * this_->scale.z;
}

_inline void __fastcall c_scaled_convex_vertices_shape_impl::convertVertexIdsToVerticesImpl(c_scaled_convex_vertices_shape *this_, void *__formal, unsigned short *ids, __int32 numIds, hkVector4 *vertixArrayOut) // 0x10F1B400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?convertVertexIdsToVerticesImpl@c_scaled_convex_vertices_shape_impl@@CIXPAUc_scaled_convex_vertices_shape@@PAXPAGHPAUhkVector4@@@Z");
	// hkVector4 *vertixArrayOut;
		// long i;
	// function call : void (*)(hkpShape *, unsigned short *, __int32, hkVector4 *)

	(*(void (__thiscall **)(c_convex_vertices_shape_with_material *, unsigned short *, __int32, hkVector4 *))(this_->child->vftable + 12))(this_->child, ids, numIds, vertixArrayOut);

	for (long i = 0; i < numIds; i++)
	{
		vertixArrayOut[i].x = vertixArrayOut[i].x * this_->scale.x;
		vertixArrayOut[i].y = vertixArrayOut[i].y * this_->scale.y;
		vertixArrayOut[i].z = vertixArrayOut[i].z * this_->scale.z;
	}
}

_inline c_convex_vertices_shape_with_material *c_convex_vertices_shape_with_material_impl::fixup(c_convex_vertices_shape_with_material *shape, s_structure_instanced_geometry_definition *instance_definition) // 0x10F1B5B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup@c_convex_vertices_shape_with_material_impl@@SAPAUc_convex_vertices_shape_with_material@@PAU2@PAUs_structure_instanced_geometry_definition@@@Z");
	// s_structure_instanced_geometry_definition *instance_definition;
	// long first_plane_index;
	// s_instanced_geometry_definition_extra_data *extra_data;
	// long first_vertex_index;
		// c_convex_vertices_shape_with_material const *p;

	shape->vftable = (void **)0x165D40C;
	shape->m_referenceObject.m_memSizeAndFlags = 0;
	shape->m_referenceObject.m_referenceCount = 128;
	shape->m_userData = 'poop';
	shape->m_type = 1;
	s_instanced_geometry_definition_extra_data *extra_data = &instance_definition->extra_data[0];
	long first_plane_index = 0;
	long first_vertex_index = 0;
	for (c_convex_vertices_shape_with_material const *p = extra_data->polyhedra.begin(); p != shape; p++)
	{
		first_plane_index += p->m_planeEquation.m_size;
		first_vertex_index += p->m_rotatedVertices.m_size;
	}
	shape->m_rotatedVertices.m_data = &extra_data->polyhedra_four_vectors[first_vertex_index];
	shape->m_planeEquation.m_data = &extra_data->polyhedra_plane_equations[first_plane_index];
	return shape;
}

_inline c_decomposed_poop_shape *c_decomposed_poop_shape_impl::fixup(c_decomposed_poop_shape *shape, s_structure_instanced_geometry_definition *instance_definition) // 0x10F1B770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup@c_decomposed_poop_shape_impl@@SAPAUc_decomposed_poop_shape@@PAU2@PAUs_structure_instanced_geometry_definition@@@Z");
	// s_structure_instanced_geometry_definition *instance_definition;

	shape->hkpShape::vftable = (void **)&g_vtable_for_hkpShape;
	shape->hkShapeContainer::vftable = (void **)&g_vtable_for_hkpShapeContainer;
	shape->m_referenceObject.m_memSizeAndFlags = 0;
	shape->m_referenceObject.m_referenceCount = 128;
	shape->m_userData = 0;
	shape->m_type = 2;
	shape->m_disableWelding = 0;
	shape->instance_definition = instance_definition;
	return shape;
}

_inline hkShapeContainer *__fastcall c_decomposed_poop_shape_impl::getContainer(c_decomposed_poop_shape *this_) // 0x10F1BED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getContainer@c_decomposed_poop_shape_impl@@CIPAUhkShapeContainer@@PAUc_decomposed_poop_shape@@@Z");
	// c_decomposed_poop_shape *this_;

	return this_ ? (hkShapeContainer *)((unsigned char *)this_ + 0x10) : nullptr;
}

_inline __int32 __fastcall c_decomposed_poop_shape_impl::getNumChildShapes(hkShapeContainer *this_) // 0x10F1C030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getNumChildShapes@c_decomposed_poop_shape_impl@@CIHPAUhkShapeContainer@@@Z");
	// hkShapeContainer *this_;
	// c_decomposed_poop_shape *decomposed_poop;
	// s_structure_instanced_geometry_definition *instance_def;
	// s_instanced_geometry_definition_extra_data *extra_data;

	c_decomposed_poop_shape *decomposed_poop = (c_decomposed_poop_shape *)havok_shape_from_container(this_);
	s_structure_instanced_geometry_definition *instance_def = (s_structure_instanced_geometry_definition *)decomposed_poop->instance_definition;
	s_instanced_geometry_definition_extra_data *extra_data = &instance_def->extra_data[0];
	return extra_data->polyhedra.count;
}

_inline hkpShape *__fastcall c_decomposed_poop_shape_impl::getChildShape(hkShapeContainer *this_, void *__formal, unsigned __int32 key, char (&buffer)[512]) // 0x10F1BBC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getChildShape@c_decomposed_poop_shape_impl@@CIPAUhkpShape@@PAUhkShapeContainer@@PAXIAAY0CAA@D@Z");
	// char (&buffer)[512];
	// s_structure_instanced_geometry_definition *instance_definition;
	// c_convex_vertices_shape_with_material *polyhedron;
	// c_decomposed_poop_shape *decomposed_poop_shape;
	// s_instanced_geometry_definition_extra_data *extra_data;

	typedef unsigned int hkUint32;
	c_decomposed_poop_shape *decomposed_poop_shape = (c_decomposed_poop_shape *)havok_shape_from_container(this_);
	s_structure_instanced_geometry_definition *instance_definition = (s_structure_instanced_geometry_definition *)decomposed_poop_shape->instance_definition;
	s_instanced_geometry_definition_extra_data *extra_data = &instance_definition->extra_data[0];
	if (!(key < (hkUint32)extra_data->polyhedra.count))
	{
		(void)((!!(key < (hkUint32)extra_data->polyhedra.count)) || (_wassert(L"key < (hkUint32)extra_data->polyhedra.count", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\physics\\physics_shapes.cpp", 220), 0));
		return nullptr;
	}
	c_convex_vertices_shape_with_material *polyhedron = &extra_data->polyhedra[key];
	if (!polyhedron->vftable)
		c_convex_vertices_shape_with_material_impl::fixup(polyhedron, instance_definition);
	if (decomposed_poop_shape->scale != 1.0f)
		return c_scaled_convex_vertices_shape_impl::fixup((c_scaled_convex_vertices_shape *)buffer, polyhedron, decomposed_poop_shape->scale);
	return polyhedron;
}

void c_scaled_convex_vertices_shape::fixup(c_scaled_convex_vertices_shape *definition, c_convex_vertices_shape_with_material *child, float scale) // 0x10F1B820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup@c_scaled_convex_vertices_shape@@SAXPAU1@PAUc_convex_vertices_shape_with_material@@M@Z");
	// float scale;

	c_scaled_convex_vertices_shape_impl::fixup(definition, child, scale);
}

void c_decomposed_poop_shape::fixup(c_decomposed_poop_shape *definition, s_structure_instanced_geometry_definition *instance_definition) // 0x10F1B710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup@c_decomposed_poop_shape@@SAXPAU1@PAUs_structure_instanced_geometry_definition@@@Z");
	// s_structure_instanced_geometry_definition *instance_definition;

	c_decomposed_poop_shape_impl::fixup(definition, instance_definition);
}

void c_convex_vertices_shape_with_material::fixup(c_convex_vertices_shape_with_material *definition, s_structure_instanced_geometry_definition *instance_definition) // 0x10F1B550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup@c_convex_vertices_shape_with_material@@SAXPAU1@PAUs_structure_instanced_geometry_definition@@@Z");
	// s_structure_instanced_geometry_definition *instance_definition;

	c_convex_vertices_shape_with_material_impl::fixup(definition, instance_definition);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<hkpConvexVerticesShape::FourVectors>::try_get_element(__int32, hkpConvexVerticesShape::FourVectors **) const;
template c_convex_vertices_shape_with_material * c_tag_block<c_convex_vertices_shape_with_material>::begin();
template hkpConvexVerticesShape::FourVectors & c_tag_block<hkpConvexVerticesShape::FourVectors>::operator[](__int32);
template hkpConvexVerticesShape::FourVectors * c_tag_block<hkpConvexVerticesShape::FourVectors>::get_element(__int32) const;
