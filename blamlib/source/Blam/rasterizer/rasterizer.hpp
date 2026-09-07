#ifndef __BLAM_RASTERIZER_RASTERIZER_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_vertex_types.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"

#include <d3d9.h>

/* ---------- forward declarations */

class c_rasterizer_index_buffer;
class c_rasterizer_vertex_buffer;
struct c_rasterizer;
struct c_rasterizer_texture_ref;
struct s_screen_vertex;

/* ---------- constants */

/* ---------- definitions */

struct c_rasterizer
{
	static _inline IDirect3DDevice9Ex *get_device();
	static _inline IDirect3D9Ex *get_direct3d();
	static bool (*const set_indices)(IDirect3DIndexBuffer9 *);
	static void (*const clear)(long, __int32, float, unsigned char);
	static bool (*const thread_owns_device)();
	static bool (*const set_vertex_shader)(void *, long, long, long);
	static void (*const set_using_albedo_sampler)(bool);
	static bool (*const set_pixel_shader)(void *, long);
	static void (*const normalize_screenspace_vertices)(float, float, float, float, s_screen_vertex *, long);
	static long *(*const get_device_caps)();
	static bool (*const set_vertex_declaration)(IDirect3DVertexDeclaration9 *);
	static bool (*const get_is_widescreen)();
	static bool (*const set_vertex_stream)(c_rasterizer_vertex_buffer const *);
	static void (*const draw_indexed_primitive)(c_rasterizer_index_buffer const *, long, long, long, long);
	static void (*const draw_primitive)(long, long, long);
	static void (*const draw_primitive_up)(long, long, void *, long);
	static void (*const draw_fullscreen_quad)(long, long);
	static void (*const draw_fullscreen_quad_custom_coords)(long, long, float *);
	static void (*const draw_textured_screen_quad)(void *, char);
	static bool &m_use_floating_point_z_buffer;
	static long &g_depth_stencil_surface;
	static long *g_color_surfaces;
	static bool &g_d3d9ex;
	static bool &g_reset_device;
	static long g_buffer_count;
	static long g_backbuffer_format;
	static c_rasterizer_texture_ref &m_albedo_texture;
	static c_rasterizer_texture_ref &m_normal_texture;
	static void set_DAC_LUT_curve();
};
static_assert(sizeof(c_rasterizer) == 1, "Invalid c_rasterizer size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

extern IDirect3DDevice9Ex *_sub_10786340();
_inline IDirect3DDevice9Ex *c_rasterizer::get_device() // 0x10786340
{
	mangled_x86(MANGLED_TODO, "?get_device@c_rasterizer@@SAPAUIDirect3DDevice9Ex@@XZ");
	// procedure flags: nofpo
	todo("implement");
	IDirect3DDevice9Ex * __result = _sub_10786340();
	return __result;
}

extern IDirect3D9Ex *_sub_108EF070();
_inline IDirect3D9Ex *c_rasterizer::get_direct3d() // 0x108EF070
{
	mangled_x86(MANGLED_TODO, "?get_direct3d@c_rasterizer@@SAPAUIDirect3D9Ex@@XZ");
	// procedure flags: nofpo
	todo("implement");
	IDirect3D9Ex * __result = _sub_108EF070();
	return __result;
}

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_HPP__
