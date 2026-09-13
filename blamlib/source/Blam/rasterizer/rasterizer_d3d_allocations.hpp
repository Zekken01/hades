#ifndef __BLAM_RASTERIZER_RASTERIZER_D3D_ALLOCATIONS_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_D3D_ALLOCATIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

/* ---------- forward declarations */

class c_d3d_resource_allocator;
class c_d3d_resource_tracker;
struct _D3DVERTEXELEMENT9;

/* ---------- constants */

/* ---------- definitions */

class c_d3d_resource_allocator
{
public:
	static long m_texture_selected_mip;
	static long m_released_index_buffers;
	static HRESULT create_cube_texture(unsigned __int32 edge_length, unsigned __int32 levels, unsigned long usage, _D3DFORMAT hardware_format, unsigned long pool, IDirect3DCubeTexture9 **cube_texture, long debug_1, long debug_2, long debug_3, char const *debug_label);
	static HRESULT create_d3d_index_buffer(unsigned __int32 length, unsigned long usage, _D3DFORMAT hardware_format, _D3DPOOL pool, IDirect3DIndexBuffer9 **index_buffer, void **shared_handle);
	static HRESULT create_d3d_vertex_buffer(unsigned __int32 length, unsigned long usage, _D3DFORMAT hardware_format, unsigned long pool, IDirect3DVertexBuffer9 **vertex_buffer, void **shared_handle);
	static HRESULT create_depth_stencil_surface(unsigned __int32 width, unsigned __int32 height, _D3DFORMAT hardware_format, unsigned long multisample_type, unsigned long multisample_quality, __int32 discard, IDirect3DSurface9 **surface, long debug_1, char const *debug_label);
	static HRESULT create_off_screen_plain_surface(unsigned __int32 width, unsigned __int32 height, _D3DFORMAT hardware_format, IDirect3DSurface9 **surface, char const *debug_label);
	static HRESULT create_pixel_shader(unsigned long const *function, IDirect3DPixelShader9 **pixel_shader);
	static HRESULT create_render_target(unsigned __int32 width, unsigned __int32 height, _D3DFORMAT hardware_format, unsigned long multisample_type, unsigned long multisample_quality, __int32 lockable, IDirect3DSurface9 **surface, char const *debug_label);
	static HRESULT create_texture(unsigned __int32 width, unsigned __int32 height, unsigned __int32 levels, unsigned long usage, _D3DFORMAT hardware_format, unsigned long pool, IDirect3DTexture9 **texture, long debug_a7, long debug_a8, long debug_a9, char const *debug_label);
	static HRESULT create_vertex_declaration(_D3DVERTEXELEMENT9 const *elements, IDirect3DVertexDeclaration9 **vertex_declaration);
	static HRESULT create_vertex_shader(unsigned long const *function, IDirect3DVertexShader9 **vertex_shader);
	static HRESULT create_volume_texture(unsigned __int32 width, unsigned __int32 height, unsigned __int32 depth, unsigned __int32 levels, unsigned long usage, _D3DFORMAT hardware_format, unsigned long pool, IDirect3DVolumeTexture9 **volume_texture, long debug_1, long debug_2, long debug_3, char const *debug_label);
	static HRESULT release_all_d3d_resources();
	static HRESULT release_index_buffer(IDirect3DIndexBuffer9 *index_buffer);
	static HRESULT release_vertex_buffer(IDirect3DVertexBuffer9 *vertex_buffer);
	static HRESULT release_pixel_shader(IDirect3DPixelShader9 *pixel_shader);
	static HRESULT release_surface(IDirect3DSurface9 *surface);
	static HRESULT release_texture(IDirect3DBaseTexture9 *texture);
	static HRESULT release_vertex_declaration(IDirect3DVertexDeclaration9 *vertex_declaration);
	static HRESULT release_vertex_shader(IDirect3DVertexShader9 *vertex_shader);
	static void set_d3d_device(IDirect3DDevice9 *device);
	static HRESULT update_texture(IDirect3DBaseTexture9 *source, IDirect3DBaseTexture9 *destination);
private:
	static IDirect3DDevice9 *&m_d3d_device_ptr;
};
static_assert(sizeof(c_d3d_resource_allocator) == 1, "Invalid c_d3d_resource_allocator size");

class c_d3d_resource_tracker
{
public:
	static long add_pixel_shader(IDirect3DPixelShader9 *resource);
	static long add_vertex_shader(IDirect3DVertexShader9 *resource);
	static long add_vertex_buffer(IDirect3DVertexBuffer9 *resource);
	static long add_index_buffer(IDirect3DIndexBuffer9 *resource);
	static long add_texture(IDirect3DBaseTexture9 *resource);
	static long add_surface(IDirect3DSurface9 *resource);
	static long add_vertex_declaration(IDirect3DVertexDeclaration9 *resource);
	static long remove_pixel_shader(IDirect3DPixelShader9 *resource);
	static long remove_vertex_shader(IDirect3DVertexShader9 *resource);
	static long remove_vertex_buffer(IDirect3DVertexBuffer9 *resource);
	static long remove_index_buffer(IDirect3DIndexBuffer9 *resource);
	static long remove_texture(IDirect3DBaseTexture9 *resource);
	static long remove_surface(IDirect3DSurface9 *resource);
	static long remove_vertex_declaration(IDirect3DVertexDeclaration9 *resource);
	static HRESULT release_all_allocated_pixel_shaders();
	static HRESULT release_all_allocated_vertex_shaders();
	static HRESULT release_all_allocated_vertex_buffers();
	static HRESULT release_all_allocated_index_buffers();
	static HRESULT release_all_allocated_surfaces();
	static HRESULT release_all_allocated_textures();
	static HRESULT release_all_allocated_vertex_declarations();
	static void get_allocated_resource_counts(long *num_allocated_pixel_shaders, long *num_allocated_vertex_shaders, long *num_allocated_vertex_buffers, long *num_allocated_index_buffers, long *num_allocated_surfaces, long *num_allocated_textures, long *num_allocated_vertex_declarations);
	static _inline long get_index_buffer_ptr();
	template<typename t_type> struct s_allocation_info
	{
		t_type resource; // 0x0
	};
private:
	static s_allocation_info<IDirect3DPixelShader9 *> m_allocated_d3d_pixel_shaders[12288];
	static s_allocation_info<IDirect3DVertexShader9 *> m_allocated_d3d_vertex_shaders[3072];
	static s_allocation_info<IDirect3DVertexBuffer9 *> m_allocated_d3d_vertex_buffers[16384];
	static s_allocation_info<IDirect3DIndexBuffer9 *> m_allocated_d3d_index_buffers[6144];
	static s_allocation_info<IDirect3DSurface9 *> m_allocated_surfaces[64];
	static s_allocation_info<IDirect3DBaseTexture9 *> m_allocated_textures[6144];
	static s_allocation_info<IDirect3DVertexDeclaration9 *> m_allocated_vertex_declarations[128];
	static long m_num_of_allocated_pixel_shaders;
	static long m_num_of_allocated_vertex_shaders;
	static long m_num_of_allocated_vertex_buffers;
	static long m_num_of_allocated_index_buffers;
	static long m_num_of_allocated_surfaces;
	static long m_num_of_allocated_textures;
	static long m_num_of_allocated_vertex_declarations;
	// Both are `CA` in the decorated name - private, __cdecl - so
	// static, and the allocation table is `s_allocation_info<t_arg0> *`
	// rather than a second `t_arg0`.
	template<typename t_arg0>
	static long add_resource_helper(t_arg0 resource, s_allocation_info<t_arg0> *tracked_allocations, long max_resources, long *count);
	template<typename t_arg0>
	static long remove_resource_helper(t_arg0 const resource, s_allocation_info<t_arg0> *tracked_allocations, long *count);
};
static_assert(sizeof(c_d3d_resource_tracker) == 1, "Invalid c_d3d_resource_tracker size");

/* ---------- prototypes */

extern void d3d_resource_tracker_output_allocated_resource_counts();

/* ---------- globals */

/* ---------- public code */

_extern long _sub_108CAC40();
_inline long c_d3d_resource_tracker::get_index_buffer_ptr() // 0x108CAC40
{
	mangled_x86(MANGLED_TODO, "?get_index_buffer_ptr@c_d3d_resource_tracker@@SAJXZ");
	// procedure flags: nofpo
	todo("implement");
	long __result = _sub_108CAC40();
	return __result;
}

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_D3D_ALLOCATIONS_HPP__
