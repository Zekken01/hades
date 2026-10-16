#ifndef __BLAM_STRUCTURES_STRUCTURE_SURFACES_HPP__
#define __BLAM_STRUCTURES_STRUCTURE_SURFACES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/physics/collision_bsp.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/visibility/visibility.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct c_collision_bsp_reference;
struct c_structure_surface;
struct collision_bsp;
struct s_scenario_structure_bsp;
struct s_structure_bsp_cache_file_resources;
struct s_structure_bsp_resources;
struct s_structure_instanced_geometry_definition;
struct s_structure_instanced_geometry_instance;
struct s_structure_plane;

/* ---------- constants */

/* ---------- definitions */

struct c_structure_surface
{
	_inline c_structure_surface(s_scenario_structure_bsp *structure_bsp, long instance_index, long surface_index);
	_inline bool sanity_check() const;
	_inline bool is_valid() const;
	_inline long get_surface_index() const;
	_inline long get_triangle_count() const;
	_inline long get_first_triangle_index() const;
	_inline long get_section_index(long index) const;
	_inline long get_mesh_index(long index) const;
	_inline long get_triangle_vertex_index(long index) const;
	_inline s_structure_plane const *get_triangle_mapping(long index) const;
	s_scenario_structure_bsp const *get_structure_bsp() const;
	_inline long get_compression_info_index() const;
	_inline s_structure_instanced_geometry_definition const *get_instance_definition() const;
	s_structure_instanced_geometry_instance const *get_instance() const;
	_inline void get_collision_bsp(c_collision_bsp_reference *bsp_reference) const;
private:
	bool m_valid; // 0x0
	unsigned char __pad0[3]; // 0x1
	s_structure_instanced_geometry_definition *m_instance_definition; // 0x4
	s_structure_bsp_cache_file_resources *m_cache_file_resources; // 0x8
	s_structure_bsp_resources *m_tag_resources; // 0xC
	s_scenario_structure_bsp *m_structure_bsp; // 0x10
	long m_instance_index; // 0x14
	long m_surface_index; // 0x18
};
static_assert(sizeof(c_structure_surface) == 28, "Invalid c_structure_surface size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline c_structure_surface::c_structure_surface(s_scenario_structure_bsp *structure_bsp, long instance_index, long surface_index) : m_valid(false), m_instance_definition(nullptr), m_cache_file_resources(nullptr), m_tag_resources(nullptr), m_structure_bsp(structure_bsp), m_instance_index(instance_index), m_surface_index(surface_index) /* hades-mem-init:  */ // 0x1091B9B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_structure_surface@@QAE@PAUs_scenario_structure_bsp@@JJ@Z");

	m_cache_file_resources = (s_structure_bsp_cache_file_resources *)((void *(*)(void *))0x563E10)(&structure_bsp->pathfinding_resource);
	m_tag_resources = (s_structure_bsp_resources *)((void *(*)(void *))0x563E10)(&structure_bsp->collision_bsp_resource);
	if (instance_index != -1)
	{
		m_instance_definition = &m_tag_resources->instanced_geometry[m_structure_bsp->instanced_geometry_instances[instance_index].mesh_index];
		if (!(surface_index >= 0 && surface_index < m_instance_definition->surface_planes.count))
			return;
	}
	else
	{
		m_instance_definition = nullptr;
		if (!(surface_index >= 0 && surface_index < m_cache_file_resources->surface_planes.count))
			return;
	}
	m_valid = sanity_check();
}

_inline bool c_structure_surface::sanity_check() const // 0x1091EF50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sanity_check@c_structure_surface@@QBE_NXZ");

	c_collision_bsp_reference collision_bsp;
	get_collision_bsp(&collision_bsp);

	long surface_index = get_surface_index();
	if (collision_bsp.large_bsp)
		return surface_index >= 0 && surface_index < collision_bsp.large_bsp->surfaces.count;
	else
		return surface_index >= 0 && surface_index < collision_bsp.bsp->surfaces.count;
}

_inline bool c_structure_surface::is_valid() const // 0x1091EEE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_valid@c_structure_surface@@QBE_NXZ");

	return m_valid;
}

_inline long c_structure_surface::get_surface_index() const // 0x1091EA40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_surface_index@c_structure_surface@@QBEJXZ");

	return m_surface_index;
}

_inline long c_structure_surface::get_triangle_count() const // 0x1091EC90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_triangle_count@c_structure_surface@@QBEJXZ");

	if (m_instance_definition)
	{
		return m_instance_definition->surface_planes[m_surface_index].plane_count;
	}
	else
	{
		return m_cache_file_resources->surface_planes[m_surface_index].plane_count;
	}
}

_inline long c_structure_surface::get_first_triangle_index() const // 0x1091E440
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_first_triangle_index@c_structure_surface@@QBEJXZ");

	if (m_instance_definition)
		return m_instance_definition->surface_planes[m_surface_index].plane_index;
	else
		return m_cache_file_resources->surface_planes[m_surface_index].plane_index;
}

_inline long c_structure_surface::get_section_index(long index) const // 0x1091E5D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_section_index@c_structure_surface@@QBEJJ@Z");

	return get_triangle_mapping(index)->cluster_index;
}

_inline long c_structure_surface::get_mesh_index(long index) const // 0x1091E520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_mesh_index@c_structure_surface@@QBEJJ@Z");

	if (m_instance_definition)
	{
		return m_instance_definition->mesh_index;
	}
	else
	{
		return m_structure_bsp->clusters[get_section_index(index)].mesh_index;
	}
}

_inline long c_structure_surface::get_triangle_vertex_index(long index) const // 0x1091EDF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_triangle_vertex_index@c_structure_surface@@QBEJJ@Z");

	return get_triangle_mapping(index)->index_offset;
}

_inline s_structure_plane const *c_structure_surface::get_triangle_mapping(long index) const // 0x1091ED40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_triangle_mapping@c_structure_surface@@QBEPBUs_structure_plane@@J@Z");

	if (m_instance_definition)
	{
		return &m_instance_definition->planes[index];
	}
	else
	{
		return &m_cache_file_resources->planes[index];
	}
}

_inline long c_structure_surface::get_compression_info_index() const // 0x1091DF30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_compression_info_index@c_structure_surface@@QBEJXZ");

	if (m_instance_definition)
	{
		return m_instance_definition->compression_info_index;
	}
	else
	{
		return -1;
	}
}

_inline s_structure_instanced_geometry_definition const *c_structure_surface::get_instance_definition() const // 0x1091E4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_instance_definition@c_structure_surface@@QBEPBUs_structure_instanced_geometry_definition@@XZ");

	return m_instance_definition;
}

_inline void c_structure_surface::get_collision_bsp(c_collision_bsp_reference *bsp_reference) const // 0x1091DE10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_collision_bsp@c_structure_surface@@QBEXPAUc_collision_bsp_reference@@@Z");

	bsp_reference->bsp = nullptr;
	bsp_reference->large_bsp = nullptr;
	if (m_instance_definition)
	{
		if (m_instance_definition->render_bsp.count > 0)
		{
			bsp_reference->bsp = &m_instance_definition->render_bsp[0];
		}
		else
		{
			bsp_reference->bsp = &m_instance_definition->collision_bsp;
		}
	}
	else if (m_tag_resources->large_collision_bsps.count == 1)
	{
		bsp_reference->large_bsp = &m_tag_resources->large_collision_bsps[0];
	}
	else
	{
		bsp_reference->bsp = &m_tag_resources->collision_bsps[0];
	}
}

/* ---------- private code */

#endif // __BLAM_STRUCTURES_STRUCTURE_SURFACES_HPP__
