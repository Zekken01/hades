#ifndef __BLAM_PHYSICS_HAVOK_COMPONENT_HPP__
#define __BLAM_PHYSICS_HAVOK_COMPONENT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"

/* ---------- forward declarations */

struct c_havok_contact_point;
struct real_vector3d;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_havok_contact_point
{
	unsigned long shape_key; // 0x0
	long impact_handle; // 0x4
	long contact_surface_index; // 0x8
	short mateiral_type_a; // 0xC
	short material_type_b; // 0xE
	__int32 offending_component_index; // 0x10
	__int32 object_index; // 0x14
	real_point3d position; // 0x18
	real_vector3d separating_normal; // 0x24
	float distance; // 0x30
	float friction; // 0x34
	float restitution; // 0x38
	short contact_point_id; // 0x3C
	short lifecycle_flag; // 0x3E
	char surface_flags; // 0x40
	char rigid_body_index_a; // 0x41
	char rigid_body_index_b; // 0x42
	char structure_bsp_index; // 0x43
};
#pragma pack(pop)
static_assert(sizeof(c_havok_contact_point) == 68, "Invalid c_havok_contact_point size");

// c_havok_component is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// c_havok_component is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

extern c_data_array<c_havok_component> *havok_components_get();
extern c_havok_component *havok_component_get(unsigned long havok_component_index);

/* ---------- globals */

/* ---------- public code */

_extern long _sub_10917FC0(c_havok_component const *const);
_inline long c_havok_component::get_object_index() const // 0x10917FC0
{
	mangled_x86(MANGLED_TODO, "?get_object_index@c_havok_component@@QBEJXZ");
	// c_havok_component const *const this;
	todo("implement");
	long __result = _sub_10917FC0((c_havok_component const *)this);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_PHYSICS_HAVOK_COMPONENT_HPP__
