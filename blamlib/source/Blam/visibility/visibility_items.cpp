/* ---------- headers */

#include "Blam/visibility/visibility_items.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

class c_visible_items;
struct s_visible_items;
struct s_visible_items_stack_marker;

/* ---------- constants */

/* ---------- definitions */

typedef void vorbis_info_residue;
typedef void vorbis_info_floor;
typedef void vorbis_look_transform;
typedef void vorbis_info_mapping;
typedef short vorbis_fpu_control;
typedef void vorbis_look_floor;
typedef void vorbis_look_residue;

/* ---------- prototypes */

/* ---------- globals */

s_visible_items c_visible_items::m_items; // 0x124C2C90

/* ---------- private variables */

/* ---------- public code */

void c_visible_items::push_marker() // 0x10F0DF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?push_marker@c_visible_items@@SAXXZ");
	// procedure flags: nofpo
	// s_visible_items_stack_marker &top;

	s_visible_items_stack_marker &top = m_marker_stack[++m_marker_stack_top];
	top.object_hierarchy_marker = m_items.object_hierarchies.count;
	top.objects_marker = m_items.objects.count;
	top.instance_groups_marker = m_items.instance_groups.count;
	top.instances_marker = m_items.instances.count;
	top.clusters_marker = m_items.clusters.count;
	top.lights_marker = m_items.lights.count;
	top.skies_marker = m_items.skies.count;
	top.parts_count_marker = m_items.cluster_mesh_part_visibility_size;
	top.cluster_count_marker = m_items.cluster_group_count;
}

void c_visible_items::pop_marker() // 0x10F0DDB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?pop_marker@c_visible_items@@SAXXZ");
	// procedure flags: nofpo
	// s_visible_items_stack_marker &top;

	#line 59 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\visibility\\visibility_items.cpp"
		assert(m_marker_stack_top >= 0);
		#line 66 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\visibility\\visibility_items.cpp"
	s_visible_items_stack_marker &top = m_marker_stack[m_marker_stack_top--];
	m_items.object_hierarchies.count = top.object_hierarchy_marker;
	m_items.objects.count = top.objects_marker;
	m_items.instance_groups.count = top.instance_groups_marker;
	m_items.instances.count = top.instances_marker;
	m_items.clusters.count = top.clusters_marker;
	m_items.lights.count = top.lights_marker;
	m_items.skies.count = top.skies_marker;
	m_items.cluster_mesh_part_visibility_size = top.parts_count_marker;
	m_items.cluster_group_count = top.cluster_count_marker;
}

// mangled_x86(MANGLED_DEFAULT, "??0s_visible_items@@QAE@XZ"); no body to assert in

void c_visible_items::clear_all() // 0x10F0DC80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?clear_all@c_visible_items@@SAXXZ");
	// procedure flags: nofpo

	csmemset((unsigned char *)&m_items + 0x5dffc, 0, *(short *)((unsigned char *)&m_items + 0x5e7fc) * sizeof(long));
	*(short *)((unsigned char *)&m_items + 0x2) = 0;
	*(short *)((unsigned char *)&m_items + 0x6006) = 0;
	*(short *)((unsigned char *)&m_items + 0x3a80a) = 0;
	*(short *)((unsigned char *)&m_items + 0x4680e) = 0;
	*(short *)((unsigned char *)&m_items + 0x58812) = 0;
	*(short *)((unsigned char *)&m_items + 0x5df16) = 0;
	*(short *)((unsigned char *)&m_items + 0x5dfe2) = 0;
	*(short *)((unsigned char *)&m_items + 0x5e7fc) = 0;
	*(short *)((unsigned char *)&m_items + 0x5e7fe) = 0;
	m_marker_stack_top = NONE;
}

s_visible_items_stack_marker &c_visible_items::get_current_markers() // 0x10F0DD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_markers@c_visible_items@@SAAAUs_visible_items_stack_marker@@XZ");
	// procedure flags: nofpo

	return m_marker_stack[m_marker_stack_top];
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<s_visible_items_stack_marker,3>::valid(__int32);
template s_visible_items_stack_marker & s_static_array<s_visible_items_stack_marker,3>::operator[](long);

/* ---------- explicit instantiations */
// template s_simple_list<long,6>::s_simple_list();
// template s_simple_list<long,50>::s_simple_list();
// template s_simple_list<s_visible_cluster,1392>::s_simple_list();
// template s_simple_list<s_visible_instance,4608>::s_simple_list();
// template s_simple_list<s_visible_instance_group,4096>::s_simple_list();
// template s_simple_list<s_visible_object,1792>::s_simple_list();
// template s_simple_list<s_visible_object_hierarchy,1536>::s_simple_list();
// template s_simple_list<long,6>::s_simple_list();
// template s_simple_list<long,50>::s_simple_list();
// template s_simple_list<s_visible_cluster,1392>::s_simple_list();
// template s_simple_list<s_visible_instance,4608>::s_simple_list();
// template s_simple_list<s_visible_instance_group,4096>::s_simple_list();
// template s_simple_list<s_visible_object,1792>::s_simple_list();
// template s_simple_list<s_visible_object_hierarchy,1536>::s_simple_list();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
s_static_array<s_visible_items_stack_marker,3> &c_visible_items::m_marker_stack = *reinterpret_cast<s_static_array<s_visible_items_stack_marker,3> *>(0x24B0A58);
long &c_visible_items::m_marker_stack_top = *reinterpret_cast<long *>(0x18BF6B0);
