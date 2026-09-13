#ifndef __BLAM_SHADERS_RENDER_METHOD_SUBMIT_HPP__
#define __BLAM_SHADERS_RENDER_METHOD_SUBMIT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"


/* ---------- forward declarations */

class c_render_method;
class s_tag_block_index;
struct c_render_method_data;
struct s_destination_info;
struct s_render_submit_cache;

/* ---------- constants */

enum e_entry_point
{
	_entry_default = 0,
	_entry_albedo,
	_entry_static_default,
	_entry_static_per_pixel,
	_entry_static_per_vertex,
	_entry_static_sh,
	_entry_static_prt_ambient,
	_entry_static_prt_linear,
	_entry_static_prt_quadratic,
	_entry_dynamic_light,
	_entry_shadow_generate,
	_entry_shadow_apply,
	_entry_active_camo,
	_entry_lightmap_debug_mode,
	_entry_static_per_vertex_color,
	_entry_water_tessellation,
	_entry_water_shading,
	_entry_dynamic_light_cinematic,
	_entry_z_only,
	_entry_sfx_distort,
	k_number_of_entry_points,
};

/* ---------- definitions */

struct s_destination_info
{
	short source_index; // 0x0
	short destination_index; // 0x2
};
static_assert(sizeof(s_destination_info) == 4, "Invalid s_destination_info size");

struct s_render_submit_cache
{
	bool m_unknown; // 0x0
	c_render_method *m_render_method; // 0x4
	long m_vertex_type; // 0x8
	long m_entry_point; // 0xC
};
static_assert(sizeof(s_render_submit_cache) == 16, "Invalid s_render_submit_cache size");
static_assert(offsetof(s_render_submit_cache, m_vertex_type) == 0x8, "s_render_submit_cache::m_vertex_type moved when its reconstructed padding was removed");

class s_tag_block_index
{
public:
	unsigned short integer; // 0x0
	_inline unsigned short get_offset() const;
	_inline unsigned short get_count() const;
};
static_assert(sizeof(s_tag_block_index) == 2, "Invalid s_tag_block_index size");

struct c_render_method_data
{
	static bool *lighting_debug;
	static unsigned long *m_change_colors;
	static long &m_context;
	static float (*m_context_interface)(long, long, long);
	static s_render_submit_cache *render_submit_cache;
};
static_assert(sizeof(c_render_method_data) == 1, "Invalid c_render_method_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline unsigned short s_tag_block_index::get_offset() const // 0x108EFE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_offset@s_tag_block_index@@QBEGXZ");
	// s_tag_block_index const *const this;

	return integer & 0x3FF;
}

_inline unsigned short s_tag_block_index::get_count() const // 0x108EEFE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_count@s_tag_block_index@@QBEGXZ");
	// s_tag_block_index const *const this;

	return integer >> 10;
}

/* ---------- private code */

#endif // __BLAM_SHADERS_RENDER_METHOD_SUBMIT_HPP__
