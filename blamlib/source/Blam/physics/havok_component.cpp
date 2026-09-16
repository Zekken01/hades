/* ---------- headers */

#include "Blam/physics/havok_component.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/physics/havok_types.hpp"

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

class c_havok_component;
struct hkpEntity;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern c_data_array<c_havok_component> *havok_components_get();
extern c_havok_component *havok_component_get(unsigned long havok_component_index);

/* ---------- globals */

extern long (*const havok_entity_get_havok_component_index)(hkpEntity const *); // 0x1124B6A8
extern long (*const havok_entity_get_havok_component_rigid_body_index)(hkpEntity const *); // 0x1124B6AC

/* ---------- private variables */

/* ---------- public code */

c_data_array<c_havok_component> *havok_components_get() // 0x10F18A60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_components_get@@YAPAV?$c_data_array@Vc_havok_component@@@@XZ");
	// procedure flags: nofpo

	return *(c_data_array<c_havok_component> * *)0x2446080;
}

c_havok_component *havok_component_get(unsigned long havok_component_index) // 0x10F189F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_component_get@@YAPAVc_havok_component@@K@Z");
	// unsigned long havok_component_index;

	return havok_components_get()->try_and_get(havok_component_index);
}

unsigned long c_havok_component::get_rigid_body_collision_filter_info(long rigid_body_index) // 0x10F18970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_rigid_body_collision_filter_info@c_havok_component@@QAEKJ@Z");
	// long rigid_body_index;

	return ((hkpRigidBody *)m_rigid_bodies[rigid_body_index].rigid_body)->m_collisionFilterInfo;
}

void c_havok_component::set_rigid_body_collision_filter_info(long rigid_body_index, unsigned long info) // 0x10F18AB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_rigid_body_collision_filter_info@c_havok_component@@QAEXJK@Z");
	// unsigned long info;

	*(unsigned long *)(*(unsigned char **)((unsigned char *)&(*(hkArray<c_rigid_body> *)((unsigned char *)this + 0x14))[rigid_body_index] + 0x40) + 0x2c) = info;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_havok_component * c_data_array<c_havok_component>::try_and_get(unsigned long);
template c_havok_component::c_rigid_body & hkArray<c_havok_component::c_rigid_body>::operator[](__int32);
