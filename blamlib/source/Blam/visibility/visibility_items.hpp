#ifndef __BLAM_VISIBILITY_VISIBILITY_ITEMS_HPP__
#define __BLAM_VISIBILITY_VISIBILITY_ITEMS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/render/render_object_globals.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/visibility/visibility_object_render_info.hpp"

/* ---------- forward declarations */

class c_visible_items;
struct s_cluster_reference;
struct s_lod_alphas;
struct s_visible_cluster;
struct s_visible_instance;
struct s_visible_instance_group;
struct s_visible_items;
struct s_visible_items_stack_marker;
struct s_visible_object;
struct s_visible_object_hierarchy;

/* ---------- constants */

enum
{
	k_number_of_visible_object_hierarchies = 1536, // 0x0600
	k_number_of_visible_objects = 1792, // 0x0700
	k_number_of_visible_instance_groups = 4096, // 0x1000
	k_number_of_visible_instances = 4608, // 0x1200
	k_number_of_visible_clusters = 1392, // 0x0570
	k_number_of_visible_lights = 50, // 0x0032 '2'
	k_number_of_visible_skies = 6, // 0x0006
	k_number_of_visible_cluster_mesh_parts = 16384, // 0x4000
	k_number_of_visible_cluster_groups = 512, // 0x0200
};

/* ---------- definitions */

struct s_visible_object_hierarchy
{
	unsigned short flags; // 0x0
	short group_index; // 0x2
	long first_index; // 0x4
	short count; // 0x8
	s_lod_alphas lod_alphas; // 0xA
	unsigned char __pad0[2]; // 0xE
};
static_assert(sizeof(s_visible_object_hierarchy) == 16, "Invalid s_visible_object_hierarchy size");

struct s_visible_instance_group
{
	s_cluster_reference cluster_reference; // 0x0
	short unknown; // 0x2
	short instance_bucket_index; // 0x4
	short first_index; // 0x6
	short count; // 0x8
	short mesh_index; // 0xA
};
static_assert(sizeof(s_visible_instance_group) == 12, "Invalid s_visible_instance_group size");

struct s_visible_instance
{
	unsigned short flags; // 0x0
	short instance_index; // 0x2
	short structure_bsp_index; // 0x4
	short group_index; // 0x6
	unsigned short alpha; // 0x8
	unsigned char __pad0[2]; // 0xA
	unsigned long *mesh_part_visibility; // 0xC
};
static_assert(sizeof(s_visible_instance) == 16, "Invalid s_visible_instance size");

struct s_visible_cluster
{
	unsigned short flags; // 0x0
	s_cluster_reference cluster_reference; // 0x2
	short unknown; // 0x4
	short region_cluster_index; // 0x6
	short mesh_index; // 0x8
	unsigned char __pad0[2]; // 0xA
	unsigned long *mesh_part_visibility; // 0xC
};
static_assert(sizeof(s_visible_cluster) == 16, "Invalid s_visible_cluster size");

struct s_visible_items_stack_marker
{
	short object_hierarchy_marker; // 0x0
	short objects_marker; // 0x2
	short instance_groups_marker; // 0x4
	short instances_marker; // 0x6
	short clusters_marker; // 0x8
	short lights_marker; // 0xA
	short parts_count_marker; // 0xC
	short cluster_count_marker; // 0xE
	short skies_marker; // 0x10
};
static_assert(sizeof(s_visible_items_stack_marker) == 18, "Invalid s_visible_items_stack_marker size");

struct s_visible_items
{
	s_simple_list<s_visible_object_hierarchy,1536> object_hierarchies; // 0x0
	s_simple_list<s_visible_object,1792> objects; // 0x6004
	s_simple_list<s_visible_instance_group,4096> instance_groups; // 0x3A808
	s_simple_list<s_visible_instance,4608> instances; // 0x4680C
	s_simple_list<s_visible_cluster,1392> clusters; // 0x58810
	s_simple_list<long,50> lights; // 0x5DF14
	s_simple_list<long,6> skies; // 0x5DFE0
	unsigned long cluster_mesh_part_visibility[512]; // 0x5DFFC
	short cluster_mesh_part_visibility_size; // 0x5E7FC
	short cluster_group_count; // 0x5E7FE
	unsigned long cluster_group_visibility[2048]; // 0x5E800
	unsigned short object_mapping[2048]; // 0x60800
	_inline s_visible_items(); /* compiler_generated() */
};
static_assert(sizeof(s_visible_items) == 399360, "Invalid s_visible_items size");

class c_visible_items
{
public:
	static _inline s_visible_items &get_global_items();
	static void push_marker();
	static void pop_marker();
	static void clear_all();
	static s_visible_items_stack_marker &get_current_markers();
	typedef s_static_array<s_visible_items_stack_marker,3> t_marker_stack;
private:
	static s_visible_items m_items;
	static s_static_array<s_visible_items_stack_marker,3> &m_marker_stack;
	static long &m_marker_stack_top;
};
static_assert(sizeof(c_visible_items) == 1, "Invalid c_visible_items size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

extern s_visible_items &_sub_108CAC20();
_inline s_visible_items &c_visible_items::get_global_items() // 0x108CAC20
{
	mangled_x86(MANGLED_TODO, "?get_global_items@c_visible_items@@SAAAUs_visible_items@@XZ");
	// procedure flags: nofpo
	todo("implement");
	s_visible_items & __result = _sub_108CAC20();
	return __result;
}

/* ---------- private code */

#endif // __BLAM_VISIBILITY_VISIBILITY_ITEMS_HPP__
