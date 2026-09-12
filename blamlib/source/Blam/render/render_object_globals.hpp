#ifndef __BLAM_RENDER_RENDER_OBJECT_GLOBALS_HPP__
#define __BLAM_RENDER_RENDER_OBJECT_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/visibility/visibility_object_render_info.hpp"

/* ---------- forward declarations */

struct s_lod_alphas;
struct s_render_lighting;
struct s_render_object;
struct s_render_object_globals;
struct s_render_object_info;
struct s_render_object_mesh_part;
struct s_shader_extern_info;
struct s_visible_object;

/* ---------- constants */

/* ---------- definitions */

struct s_visible_object
{
	s_render_object_info info; // 0x0
	long object_index; // 0x6C
	unsigned long *subpart_visibility; // 0x70
	unsigned char flags; // 0x74
};
static_assert(sizeof(s_visible_object) == 120, "Invalid s_visible_object size");

struct s_render_object
{
	unsigned long handle; // 0x0
	s_lod_alphas lod_alphas; // 0x4
	s_render_lighting *lighting; // 0x8
	s_shader_extern_info *cached_render_state; // 0xC
};
static_assert(sizeof(s_render_object) == 16, "Invalid s_render_object size");

struct s_render_object_mesh_part
{
	unsigned long flags; // 0x0
	s_visible_object *info; // 0x4
	unsigned long *subpart_visibility; // 0x8
	short part_index; // 0xC
	short mesh_index; // 0xE
	short skinning_node_index; // 0x10
	long material_index; // 0x14
	void *shield_definition; // 0x18
};
static_assert(sizeof(s_render_object_mesh_part) == 28, "Invalid s_render_object_mesh_part size");
static_assert(offsetof(s_render_object_mesh_part, material_index) == 0x14, "s_render_object_mesh_part::material_index moved when its reconstructed padding was removed");

struct s_render_object_globals
{
	s_render_object objects[2048]; // 0x0
	long object_count; // 0x8000
	s_render_object_mesh_part parts[8192]; // 0x8004
	long part_count; // 0x40004
	bool unknown; // 0x40008
	long marker_stack_top; // 0x4000C
	long object_marker_stack[6]; // 0x40010
	long part_marker_stack[6]; // 0x40028
};
static_assert(sizeof(s_render_object_globals) == 262208, "Invalid s_render_object_globals size");
static_assert(offsetof(s_render_object_globals, marker_stack_top) == 0x4000C, "s_render_object_globals::marker_stack_top moved when its reconstructed padding was removed");

/* ---------- prototypes */

extern s_render_object_globals *render_object_globals_get();

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_RENDER_OBJECT_GLOBALS_HPP__
