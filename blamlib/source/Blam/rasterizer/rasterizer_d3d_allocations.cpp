/* ---------- headers */

#include "Blam/rasterizer/rasterizer_d3d_allocations.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

#include <Windows.h>

/* ---------- forward declarations */

class c_d3d_resource_allocator;
class c_d3d_resource_tracker;
struct _D3DVERTEXELEMENT9;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void d3d_resource_tracker_output_allocated_resource_counts();

/* ---------- globals */

long c_d3d_resource_allocator::m_released_index_buffers; // 0x12537C94
c_d3d_resource_tracker::s_allocation_info<IDirect3DIndexBuffer9 *> c_d3d_resource_tracker::m_allocated_d3d_index_buffers[6144]; // 0x12556C98
long c_d3d_resource_tracker::m_num_of_allocated_index_buffers; // 0x12562FA4
long c_d3d_resource_allocator::m_texture_selected_mip; // 0x12537C90
c_d3d_resource_tracker::s_allocation_info<IDirect3DPixelShader9 *> c_d3d_resource_tracker::m_allocated_d3d_pixel_shaders[12288]; // 0x12537C98
c_d3d_resource_tracker::s_allocation_info<IDirect3DVertexShader9 *> c_d3d_resource_tracker::m_allocated_d3d_vertex_shaders[3072]; // 0x12543C98
c_d3d_resource_tracker::s_allocation_info<IDirect3DVertexBuffer9 *> c_d3d_resource_tracker::m_allocated_d3d_vertex_buffers[16384]; // 0x12546C98
c_d3d_resource_tracker::s_allocation_info<IDirect3DSurface9 *> c_d3d_resource_tracker::m_allocated_surfaces[64]; // 0x1255CC98
c_d3d_resource_tracker::s_allocation_info<IDirect3DBaseTexture9 *> c_d3d_resource_tracker::m_allocated_textures[6144]; // 0x1255CD98
c_d3d_resource_tracker::s_allocation_info<IDirect3DVertexDeclaration9 *> c_d3d_resource_tracker::m_allocated_vertex_declarations[128]; // 0x12562D98
long c_d3d_resource_tracker::m_num_of_allocated_pixel_shaders; // 0x12562F98
long c_d3d_resource_tracker::m_num_of_allocated_vertex_shaders; // 0x12562F9C
long c_d3d_resource_tracker::m_num_of_allocated_vertex_buffers; // 0x12562FA0
long c_d3d_resource_tracker::m_num_of_allocated_surfaces; // 0x12562FA8
long c_d3d_resource_tracker::m_num_of_allocated_textures; // 0x12562FAC
long c_d3d_resource_tracker::m_num_of_allocated_vertex_declarations; // 0x12562FB0

/* ---------- private variables */

/* ---------- public code */

HRESULT c_d3d_resource_allocator::create_cube_texture(unsigned __int32 edge_length, unsigned __int32 levels, unsigned long usage, _D3DFORMAT hardware_format, unsigned long pool, IDirect3DCubeTexture9 **cube_texture, long debug_1, long debug_2, long debug_3, char const *debug_label) // 0x10F0EF20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_cube_texture@c_d3d_resource_allocator@@SAJIIKW4_D3DFORMAT@@KPAPAUIDirect3DCubeTexture9@@JJJPBD@Z");
	// char const *debug_label;
	// unsigned long d3d_usage;
	// _D3DPOOL d3d_pool;
	// HRESULT hr;
	// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DCubeTexture9 **, void **)

	if (!m_d3d_device_ptr)
	{
		return 0;
	}
	unsigned long d3d_pool = pool;
	unsigned long d3d_usage = usage;
	if (c_rasterizer::g_d3d9ex && pool == D3DPOOL_MANAGED)
	{
		d3d_pool = D3DPOOL_DEFAULT;
		d3d_usage |= 0x200;
	}
	HRESULT hr = m_d3d_device_ptr->CreateCubeTexture(edge_length, levels, d3d_usage, hardware_format, (D3DPOOL)d3d_pool, cube_texture, nullptr);
	c_d3d_resource_tracker::add_texture(*cube_texture);
	return hr;
}

HRESULT c_d3d_resource_allocator::create_d3d_index_buffer(unsigned __int32 length, unsigned long usage, _D3DFORMAT hardware_format, _D3DPOOL pool, IDirect3DIndexBuffer9 **index_buffer, void **shared_handle) // 0x10F0F040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_d3d_index_buffer@c_d3d_resource_allocator@@SAJIKW4_D3DFORMAT@@W4_D3DPOOL@@PAPAUIDirect3DIndexBuffer9@@PAPAX@Z");
	// void **shared_handle;
	// unsigned long d3d_usage;
	// _D3DPOOL d3d_pool;
	// HRESULT hr;
	// function call : HRESULT (unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DIndexBuffer9 **, void **)

	if (!m_d3d_device_ptr)
		return 0;

	_D3DPOOL d3d_pool = pool;
	unsigned long d3d_usage = usage;
	if (c_rasterizer::g_d3d9ex && pool == D3DPOOL_MANAGED)
	{
		d3d_pool = D3DPOOL_DEFAULT;
		d3d_usage = 8;
	}

	HRESULT hr = m_d3d_device_ptr->CreateIndexBuffer(length, d3d_usage, hardware_format, d3d_pool, index_buffer, shared_handle);
	c_d3d_resource_tracker::add_index_buffer(*index_buffer);
	return hr;
}

HRESULT c_d3d_resource_allocator::create_d3d_vertex_buffer(unsigned __int32 length, unsigned long usage, _D3DFORMAT hardware_format, unsigned long pool, IDirect3DVertexBuffer9 **vertex_buffer, void **shared_handle) // 0x10F0F150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_d3d_vertex_buffer@c_d3d_resource_allocator@@SAJIKW4_D3DFORMAT@@KPAPAUIDirect3DVertexBuffer9@@PAPAX@Z");
	// void **shared_handle;
	// unsigned long d3d_usage;
	// _D3DPOOL d3d_pool;
	// HRESULT hr;
	// function call : HRESULT (unsigned __int32, unsigned long, unsigned long, _D3DPOOL, IDirect3DVertexBuffer9 **, void **)

	if (!m_d3d_device_ptr)
		return 0;

	_D3DPOOL d3d_pool = (_D3DPOOL)pool;
	unsigned long d3d_usage = usage;
	if (c_rasterizer::g_d3d9ex && pool == D3DPOOL_MANAGED)
	{
		d3d_pool = D3DPOOL_DEFAULT;
		d3d_usage = 8;
	}

	HRESULT hr = m_d3d_device_ptr->CreateVertexBuffer(length, d3d_usage, hardware_format, d3d_pool, vertex_buffer, shared_handle);
	c_d3d_resource_tracker::add_vertex_buffer(*vertex_buffer);
	return hr;
}

HRESULT c_d3d_resource_allocator::create_depth_stencil_surface(unsigned __int32 width, unsigned __int32 height, _D3DFORMAT hardware_format, unsigned long multisample_type, unsigned long multisample_quality, __int32 discard, IDirect3DSurface9 **surface, long debug_1, char const *debug_label) // 0x10F0F260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_depth_stencil_surface@c_d3d_resource_allocator@@SAJIIW4_D3DFORMAT@@KKHPAPAUIDirect3DSurface9@@JPBD@Z");
	// char const *debug_label;
	// HRESULT hr;
	// _D3DMULTISAMPLE_TYPE d3d_multisample_type;
	// function call : HRESULT (unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DMULTISAMPLE_TYPE, unsigned long, __int32, IDirect3DSurface9 **, void **)

	if (!m_d3d_device_ptr)
		return 0;

	_D3DMULTISAMPLE_TYPE d3d_multisample_type = D3DMULTISAMPLE_NONE;
	HRESULT hr = m_d3d_device_ptr->CreateDepthStencilSurface(width, height, hardware_format, d3d_multisample_type, multisample_quality, discard, surface, nullptr);
	c_d3d_resource_tracker::add_surface(*surface);
	return hr;
}

HRESULT c_d3d_resource_allocator::create_off_screen_plain_surface(unsigned __int32 width, unsigned __int32 height, _D3DFORMAT hardware_format, IDirect3DSurface9 **surface, char const *debug_label) // 0x10F0F350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_off_screen_plain_surface@c_d3d_resource_allocator@@SAJIIW4_D3DFORMAT@@PAPAUIDirect3DSurface9@@PBD@Z");
	// char const *debug_label;
	// HRESULT hr;
	// function call : HRESULT (unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DSurface9 **, void **)

	if (!m_d3d_device_ptr)
		return 0;

	HRESULT hr = m_d3d_device_ptr->CreateOffscreenPlainSurface(width, height, hardware_format, D3DPOOL_SYSTEMMEM, surface, nullptr);
	c_d3d_resource_tracker::add_surface(*surface);
	return hr;
}

HRESULT c_d3d_resource_allocator::create_pixel_shader(unsigned long const *function, IDirect3DPixelShader9 **pixel_shader) // 0x10F0F430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_pixel_shader@c_d3d_resource_allocator@@SAJPBKPAPAUIDirect3DPixelShader9@@@Z");
	// IDirect3DPixelShader9 **pixel_shader;
	// HRESULT hr;
	// function call : HRESULT (unsigned long const *, IDirect3DPixelShader9 **)

	if (!m_d3d_device_ptr)
		return 0;

	HRESULT hr = m_d3d_device_ptr->CreatePixelShader(function, pixel_shader);
	c_d3d_resource_tracker::add_pixel_shader(*pixel_shader);
	return hr;
}

HRESULT c_d3d_resource_allocator::create_render_target(unsigned __int32 width, unsigned __int32 height, _D3DFORMAT hardware_format, unsigned long multisample_type, unsigned long multisample_quality, __int32 lockable, IDirect3DSurface9 **surface, char const *debug_label) // 0x10F0F500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_render_target@c_d3d_resource_allocator@@SAJIIW4_D3DFORMAT@@KKHPAPAUIDirect3DSurface9@@PBD@Z");
	// char const *debug_label;
	// HRESULT hr;
	// function call : HRESULT (unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DMULTISAMPLE_TYPE, unsigned long, __int32, IDirect3DSurface9 **, void **)

	if (!m_d3d_device_ptr)
	{
		return 0;
	}

	HRESULT hr = m_d3d_device_ptr->CreateRenderTarget(width, height, hardware_format, (_D3DMULTISAMPLE_TYPE)multisample_type, multisample_quality, lockable, surface, nullptr);
	c_d3d_resource_tracker::add_surface(*surface);
	return hr;
}

extern HRESULT _sub_10F0F5E0(unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, unsigned long, IDirect3DTexture9 **, long, long, long, char const *);
HRESULT c_d3d_resource_allocator::create_texture(unsigned __int32 width, unsigned __int32 height, unsigned __int32 levels, unsigned long usage, _D3DFORMAT hardware_format, unsigned long pool, IDirect3DTexture9 **texture, long debug_a7, long debug_a8, long debug_a9, char const *debug_label) // 0x10F0F5E0
{
	mangled_x86(MANGLED_TODO, "?create_texture@c_d3d_resource_allocator@@SAJIIIKW4_D3DFORMAT@@KPAPAUIDirect3DTexture9@@JJJPBD@Z");
	// char const *debug_label;
	// unsigned long d3d_usage;
	// unsigned __int32 tex_height;
	// _D3DPOOL d3d_pool;
	// HRESULT hr;
	// unsigned __int32 tex_width;
	// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
	todo("implement");
	HRESULT __result = _sub_10F0F5E0(width, height, levels, usage, hardware_format, pool, texture, debug_a7, debug_a8, debug_a9, debug_label);
	return __result;
}

HRESULT c_d3d_resource_allocator::create_vertex_declaration(_D3DVERTEXELEMENT9 const *elements, IDirect3DVertexDeclaration9 **vertex_declaration) // 0x10F0F780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_vertex_declaration@c_d3d_resource_allocator@@SAJPBU_D3DVERTEXELEMENT9@@PAPAUIDirect3DVertexDeclaration9@@@Z");
	// IDirect3DVertexDeclaration9 **vertex_declaration;
	// HRESULT hr;
	// function call : HRESULT (_D3DVERTEXELEMENT9 const *, IDirect3DVertexDeclaration9 **)

	if (!m_d3d_device_ptr)
		return 0;

	HRESULT hr = m_d3d_device_ptr->CreateVertexDeclaration(elements, vertex_declaration);
	c_d3d_resource_tracker::add_vertex_declaration(*vertex_declaration);
	return hr;
}

HRESULT c_d3d_resource_allocator::create_vertex_shader(unsigned long const *function, IDirect3DVertexShader9 **vertex_shader) // 0x10F0F850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_vertex_shader@c_d3d_resource_allocator@@SAJPBKPAPAUIDirect3DVertexShader9@@@Z");
	// IDirect3DVertexShader9 **vertex_shader;
	// HRESULT hr;
	// function call : HRESULT (unsigned long const *, IDirect3DVertexShader9 **)

	if (!m_d3d_device_ptr)
		return 0;

	HRESULT hr = m_d3d_device_ptr->CreateVertexShader(function, vertex_shader);
	c_d3d_resource_tracker::add_vertex_shader(*vertex_shader);
	return hr;
}

HRESULT c_d3d_resource_allocator::create_volume_texture(unsigned __int32 width, unsigned __int32 height, unsigned __int32 depth, unsigned __int32 levels, unsigned long usage, _D3DFORMAT hardware_format, unsigned long pool, IDirect3DVolumeTexture9 **volume_texture, long debug_1, long debug_2, long debug_3, char const *debug_label) // 0x10F0F920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_volume_texture@c_d3d_resource_allocator@@SAJIIIIKW4_D3DFORMAT@@KPAPAUIDirect3DVolumeTexture9@@JJJPBD@Z");
	// char const *debug_label;
	// unsigned long d3d_usage;
	// _D3DPOOL d3d_pool;
	// HRESULT hr;
	// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DVolumeTexture9 **, void **)

	if (!m_d3d_device_ptr)
	{
		return 0;
	}

	unsigned long d3d_pool = pool;
	unsigned long d3d_usage = usage;
	if (c_rasterizer::g_d3d9ex && pool == D3DPOOL_MANAGED)
	{
		d3d_pool = D3DPOOL_DEFAULT;
		d3d_usage |= 0x200;
	}

	HRESULT hr = m_d3d_device_ptr->CreateVolumeTexture(width, height, depth, levels, d3d_usage, hardware_format, (_D3DPOOL)d3d_pool, volume_texture, nullptr);
	c_d3d_resource_tracker::add_texture(*volume_texture);
	return hr;
}

HRESULT c_d3d_resource_allocator::release_all_d3d_resources() // 0x10F10330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_all_d3d_resources@c_d3d_resource_allocator@@SAJXZ");
	// procedure flags: nofpo

	return c_d3d_resource_tracker::release_all_allocated_pixel_shaders()
		| c_d3d_resource_tracker::release_all_allocated_vertex_shaders()
		| c_d3d_resource_tracker::release_all_allocated_vertex_buffers()
		| c_d3d_resource_tracker::release_all_allocated_index_buffers()
		| c_d3d_resource_tracker::release_all_allocated_surfaces()
		| c_d3d_resource_tracker::release_all_allocated_textures()
		| c_d3d_resource_tracker::release_all_allocated_vertex_declarations();
}

HRESULT c_d3d_resource_allocator::release_index_buffer(IDirect3DIndexBuffer9 *index_buffer) // 0x10F103B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_index_buffer@c_d3d_resource_allocator@@SAJPAUIDirect3DIndexBuffer9@@@Z");
	// IDirect3DIndexBuffer9 *index_buffer;
	// function call : unsigned long ()

	if (!index_buffer || *(bool *)0x2446530)
	{
		return 0;
	}

	c_d3d_resource_tracker::remove_index_buffer(index_buffer);
	m_released_index_buffers++;
	return index_buffer->Release();
}

HRESULT c_d3d_resource_allocator::release_vertex_buffer(IDirect3DVertexBuffer9 *vertex_buffer) // 0x10F10600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_vertex_buffer@c_d3d_resource_allocator@@SAJPAUIDirect3DVertexBuffer9@@@Z");
	// IDirect3DVertexBuffer9 *vertex_buffer;
	// function call : unsigned long ()

	if (!vertex_buffer || *(bool *)0x2446530)
	{
		return 0;
	}

	c_d3d_resource_tracker::remove_vertex_buffer(vertex_buffer);
	return vertex_buffer->Release();
}

HRESULT c_d3d_resource_allocator::release_pixel_shader(IDirect3DPixelShader9 *pixel_shader) // 0x10F10450
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_pixel_shader@c_d3d_resource_allocator@@SAJPAUIDirect3DPixelShader9@@@Z");
	// IDirect3DPixelShader9 *pixel_shader;
	// function call : unsigned long ()

	if (!pixel_shader || *(bool *)0x2446530)
	{
		return 0;
	}

	c_d3d_resource_tracker::remove_pixel_shader(pixel_shader);
	return pixel_shader->Release();
}

HRESULT c_d3d_resource_allocator::release_surface(IDirect3DSurface9 *surface) // 0x10F104E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_surface@c_d3d_resource_allocator@@SAJPAUIDirect3DSurface9@@@Z");
	// IDirect3DSurface9 *surface;
	// function call : unsigned long ()

	if (!surface || *(bool *)0x2446530)
	{
		return 0;
	}

	c_d3d_resource_tracker::remove_surface(surface);
	return surface->Release();
}

HRESULT c_d3d_resource_allocator::release_texture(IDirect3DBaseTexture9 *texture) // 0x10F10570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_texture@c_d3d_resource_allocator@@SAJPAUIDirect3DBaseTexture9@@@Z");
	// IDirect3DBaseTexture9 *texture;
	// function call : unsigned long ()

	if (!texture || *(bool *)0x2446530)
	{
		return 0;
	}

	c_d3d_resource_tracker::remove_texture(texture);
	return texture->Release();
}

HRESULT c_d3d_resource_allocator::release_vertex_declaration(IDirect3DVertexDeclaration9 *vertex_declaration) // 0x10F10690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_vertex_declaration@c_d3d_resource_allocator@@SAJPAUIDirect3DVertexDeclaration9@@@Z");
	// IDirect3DVertexDeclaration9 *vertex_declaration;
	// function call : unsigned long ()

	if (!vertex_declaration || *(bool *)0x2446530)
	{
		return 0;
	}

	c_d3d_resource_tracker::remove_vertex_declaration(vertex_declaration);
	return vertex_declaration->Release();
}

HRESULT c_d3d_resource_allocator::release_vertex_shader(IDirect3DVertexShader9 *vertex_shader) // 0x10F10720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_vertex_shader@c_d3d_resource_allocator@@SAJPAUIDirect3DVertexShader9@@@Z");
	// IDirect3DVertexShader9 *vertex_shader;
	// function call : unsigned long ()

	if (!vertex_shader || *(bool *)0x2446530)
	{
		return 0;
	}

	c_d3d_resource_tracker::remove_vertex_shader(vertex_shader);
	return vertex_shader->Release();
}

void c_d3d_resource_allocator::set_d3d_device(IDirect3DDevice9 *device) // 0x10F10A50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_d3d_device@c_d3d_resource_allocator@@SAXPAUIDirect3DDevice9@@@Z");
	// IDirect3DDevice9 *device;

	m_d3d_device_ptr = device;
}

HRESULT c_d3d_resource_allocator::update_texture(IDirect3DBaseTexture9 *source, IDirect3DBaseTexture9 *destination) // 0x10F10AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_texture@c_d3d_resource_allocator@@SAJPAUIDirect3DBaseTexture9@@0@Z");
	// IDirect3DBaseTexture9 *destination;
	// function call : HRESULT (IDirect3DBaseTexture9 *, IDirect3DBaseTexture9 *)

	return m_d3d_device_ptr->UpdateTexture(source, destination);
}

long c_d3d_resource_tracker::add_pixel_shader(IDirect3DPixelShader9 *resource) // 0x10F0EC90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_pixel_shader@c_d3d_resource_tracker@@SAJPAUIDirect3DPixelShader9@@@Z");
	// IDirect3DPixelShader9 *resource;

	return add_resource_helper(resource, m_allocated_d3d_pixel_shaders, 12288, &m_num_of_allocated_pixel_shaders);
}

long c_d3d_resource_tracker::add_vertex_shader(IDirect3DVertexShader9 *resource) // 0x10F0EEB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_vertex_shader@c_d3d_resource_tracker@@SAJPAUIDirect3DVertexShader9@@@Z");
	// IDirect3DVertexShader9 *resource;

	return add_resource_helper(resource, m_allocated_d3d_vertex_shaders, 3072, &m_num_of_allocated_vertex_shaders);
}

long c_d3d_resource_tracker::add_vertex_buffer(IDirect3DVertexBuffer9 *resource) // 0x10F0EDD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_vertex_buffer@c_d3d_resource_tracker@@SAJPAUIDirect3DVertexBuffer9@@@Z");
	// IDirect3DVertexBuffer9 *resource;

	return add_resource_helper(resource, m_allocated_d3d_vertex_buffers, 16384, &m_num_of_allocated_vertex_buffers);
}

long c_d3d_resource_tracker::add_index_buffer(IDirect3DIndexBuffer9 *resource) // 0x10F0EC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_index_buffer@c_d3d_resource_tracker@@SAJPAUIDirect3DIndexBuffer9@@@Z");
	// IDirect3DIndexBuffer9 *resource;

	return add_resource_helper(resource, m_allocated_d3d_index_buffers, 6144, &m_num_of_allocated_index_buffers);
}

long c_d3d_resource_tracker::add_texture(IDirect3DBaseTexture9 *resource) // 0x10F0ED60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_texture@c_d3d_resource_tracker@@SAJPAUIDirect3DBaseTexture9@@@Z");
	// IDirect3DBaseTexture9 *resource;

	return add_resource_helper(resource, m_allocated_textures, 6144, &m_num_of_allocated_textures);
}

long c_d3d_resource_tracker::add_surface(IDirect3DSurface9 *resource) // 0x10F0ED00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_surface@c_d3d_resource_tracker@@SAJPAUIDirect3DSurface9@@@Z");
	// IDirect3DSurface9 *resource;

	return add_resource_helper(resource, m_allocated_surfaces, 64, &m_num_of_allocated_surfaces);
}

long c_d3d_resource_tracker::add_vertex_declaration(IDirect3DVertexDeclaration9 *resource) // 0x10F0EE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_vertex_declaration@c_d3d_resource_tracker@@SAJPAUIDirect3DVertexDeclaration9@@@Z");
	// IDirect3DVertexDeclaration9 *resource;

	return add_resource_helper(resource, m_allocated_vertex_declarations, 128, &m_num_of_allocated_vertex_declarations);
}

long c_d3d_resource_tracker::remove_pixel_shader(IDirect3DPixelShader9 *resource) // 0x10F10810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?remove_pixel_shader@c_d3d_resource_tracker@@SAJPAUIDirect3DPixelShader9@@@Z");
	// IDirect3DPixelShader9 *resource;

	return remove_resource_helper(resource, m_allocated_d3d_pixel_shaders, &m_num_of_allocated_pixel_shaders);
}

long c_d3d_resource_tracker::remove_vertex_shader(IDirect3DVertexShader9 *resource) // 0x10F109F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?remove_vertex_shader@c_d3d_resource_tracker@@SAJPAUIDirect3DVertexShader9@@@Z");
	// IDirect3DVertexShader9 *resource;

	return remove_resource_helper(resource, m_allocated_d3d_vertex_shaders, &m_num_of_allocated_vertex_shaders);
}

long c_d3d_resource_tracker::remove_vertex_buffer(IDirect3DVertexBuffer9 *resource) // 0x10F10930
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?remove_vertex_buffer@c_d3d_resource_tracker@@SAJPAUIDirect3DVertexBuffer9@@@Z");
	// IDirect3DVertexBuffer9 *resource;

	return remove_resource_helper(resource, m_allocated_d3d_vertex_buffers, &m_num_of_allocated_vertex_buffers);
}

long c_d3d_resource_tracker::remove_index_buffer(IDirect3DIndexBuffer9 *resource) // 0x10F107B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?remove_index_buffer@c_d3d_resource_tracker@@SAJPAUIDirect3DIndexBuffer9@@@Z");
	// IDirect3DIndexBuffer9 *resource;

	return remove_resource_helper(resource, m_allocated_d3d_index_buffers, &m_num_of_allocated_index_buffers);
}

long c_d3d_resource_tracker::remove_texture(IDirect3DBaseTexture9 *resource) // 0x10F108D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?remove_texture@c_d3d_resource_tracker@@SAJPAUIDirect3DBaseTexture9@@@Z");
	// IDirect3DBaseTexture9 *resource;

	return remove_resource_helper(resource, m_allocated_textures, &m_num_of_allocated_textures);
}

long c_d3d_resource_tracker::remove_surface(IDirect3DSurface9 *resource) // 0x10F10870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?remove_surface@c_d3d_resource_tracker@@SAJPAUIDirect3DSurface9@@@Z");
	// IDirect3DSurface9 *resource;

	return remove_resource_helper(resource, m_allocated_surfaces, &m_num_of_allocated_surfaces);
}

long c_d3d_resource_tracker::remove_vertex_declaration(IDirect3DVertexDeclaration9 *resource) // 0x10F10990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?remove_vertex_declaration@c_d3d_resource_tracker@@SAJPAUIDirect3DVertexDeclaration9@@@Z");
	// IDirect3DVertexDeclaration9 *resource;

	return remove_resource_helper(resource, m_allocated_vertex_declarations, &m_num_of_allocated_vertex_declarations);
}

HRESULT c_d3d_resource_tracker::release_all_allocated_pixel_shaders() // 0x10F0FDF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_all_allocated_pixel_shaders@c_d3d_resource_tracker@@SAJXZ");
	// procedure flags: nofpo

	HRESULT hr = 0;

	for (long i = 0; i < m_num_of_allocated_pixel_shaders; i++)
		hr |= m_allocated_d3d_pixel_shaders[i].resource->Release();

	csmemset(m_allocated_d3d_pixel_shaders, 0, sizeof(m_allocated_d3d_pixel_shaders));
	m_num_of_allocated_pixel_shaders = 0;

	return hr;
}

HRESULT c_d3d_resource_tracker::release_all_allocated_vertex_shaders() // 0x10F10250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_all_allocated_vertex_shaders@c_d3d_resource_tracker@@SAJXZ");
	// procedure flags: nofpo

	HRESULT hr = 0;

	for (long i = 0; i < m_num_of_allocated_vertex_shaders; i++)
		hr |= m_allocated_d3d_vertex_shaders[i].resource->Release();

	csmemset(m_allocated_d3d_vertex_shaders, 0, sizeof(m_allocated_d3d_vertex_shaders));
	m_num_of_allocated_vertex_shaders = 0;

	return hr;
}

HRESULT c_d3d_resource_tracker::release_all_allocated_vertex_buffers() // 0x10F10090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_all_allocated_vertex_buffers@c_d3d_resource_tracker@@SAJXZ");
	// procedure flags: nofpo

	HRESULT hr = 0;

	for (long i = 0; i < m_num_of_allocated_vertex_buffers; i++)
		hr |= m_allocated_d3d_vertex_buffers[i].resource->Release();

	csmemset(m_allocated_d3d_vertex_buffers, 0, sizeof(m_allocated_d3d_vertex_buffers));
	m_num_of_allocated_vertex_buffers = 0;

	return hr;
}

HRESULT c_d3d_resource_tracker::release_all_allocated_index_buffers() // 0x10F0FD10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_all_allocated_index_buffers@c_d3d_resource_tracker@@SAJXZ");
	// procedure flags: nofpo

	HRESULT hr = 0;

	for (long i = 0; i < m_num_of_allocated_index_buffers; i++)
		hr |= m_allocated_d3d_index_buffers[i].resource->Release();

	csmemset(m_allocated_d3d_index_buffers, 0, sizeof(m_allocated_d3d_index_buffers));
	m_num_of_allocated_index_buffers = 0;

	return hr;
}

HRESULT c_d3d_resource_tracker::release_all_allocated_surfaces() // 0x10F0FED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_all_allocated_surfaces@c_d3d_resource_tracker@@SAJXZ");
	// procedure flags: nofpo

	HRESULT hr = 0;

	for (long i = 0; i < m_num_of_allocated_surfaces; i++)
		hr |= m_allocated_surfaces[i].resource->Release();

	csmemset(m_allocated_surfaces, 0, sizeof(m_allocated_surfaces));
	m_num_of_allocated_surfaces = 0;

	return hr;
}

HRESULT c_d3d_resource_tracker::release_all_allocated_textures() // 0x10F0FFB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_all_allocated_textures@c_d3d_resource_tracker@@SAJXZ");
	// procedure flags: nofpo

	HRESULT hr = 0;

	for (long i = 0; i < m_num_of_allocated_textures; i++)
		hr |= m_allocated_textures[i].resource->Release();

	csmemset(m_allocated_textures, 0, sizeof(m_allocated_textures));
	m_num_of_allocated_textures = 0;

	return hr;
}

HRESULT c_d3d_resource_tracker::release_all_allocated_vertex_declarations() // 0x10F10170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_all_allocated_vertex_declarations@c_d3d_resource_tracker@@SAJXZ");
	// procedure flags: nofpo

	HRESULT hr = 0;

	for (long i = 0; i < m_num_of_allocated_vertex_declarations; i++)
		hr |= m_allocated_vertex_declarations[i].resource->Release();

	csmemset(m_allocated_vertex_declarations, 0, sizeof(m_allocated_vertex_declarations));
	m_num_of_allocated_vertex_declarations = 0;

	return hr;
}

void c_d3d_resource_tracker::get_allocated_resource_counts(long *num_allocated_pixel_shaders, long *num_allocated_vertex_shaders, long *num_allocated_vertex_buffers, long *num_allocated_index_buffers, long *num_allocated_surfaces, long *num_allocated_textures, long *num_allocated_vertex_declarations) // 0x10F0FC30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_allocated_resource_counts@c_d3d_resource_tracker@@SAXPAJ000000@Z");
	// long *num_allocated_vertex_declarations;

	if (num_allocated_pixel_shaders)
		*num_allocated_pixel_shaders = m_num_of_allocated_pixel_shaders;

	if (num_allocated_vertex_shaders)
		*num_allocated_vertex_shaders = m_num_of_allocated_vertex_shaders;

	if (num_allocated_vertex_buffers)
		*num_allocated_vertex_buffers = m_num_of_allocated_vertex_buffers;

	if (num_allocated_index_buffers)
		*num_allocated_index_buffers = m_num_of_allocated_index_buffers;

	if (num_allocated_surfaces)
		*num_allocated_surfaces = m_num_of_allocated_surfaces;

	if (num_allocated_textures)
		*num_allocated_textures = m_num_of_allocated_textures;

	if (num_allocated_vertex_declarations)
		*num_allocated_vertex_declarations = m_num_of_allocated_vertex_declarations;
}

template<typename t_arg0>
long c_d3d_resource_tracker::add_resource_helper(t_arg0 resource, s_allocation_info<t_arg0> *tracked_allocations, long max_resources, long *count)
{
	mangled_prefix_assert("??$add_resource_helper@");

	for (long i = 0; i < *count; i++)
	{
		if (tracked_allocations[i].resource == resource)
			return *count;
	}

	if (*count < max_resources)
	{
		tracked_allocations[*count].resource = resource;
		*count = *count + 1;
	}

	return *count;
}

template<typename t_arg0>
long c_d3d_resource_tracker::remove_resource_helper(t_arg0 const resource, s_allocation_info<t_arg0> *tracked_allocations, long *count)
{
	mangled_prefix_assert("??$remove_resource_helper@");

	long result = -1;

	for (long i = 0; i < *count; i++)
	{
		if (tracked_allocations[i].resource == resource)
		{
			csmemmove(&tracked_allocations[i], &tracked_allocations[i + 1], (*count - i) * sizeof(s_allocation_info<t_arg0>) - sizeof(s_allocation_info<t_arg0>));
			*count = *count - 1;
			result = *count;
		}
	}

	return result;
}

_extern void _sub_10F0FA40();
void d3d_resource_tracker_output_allocated_resource_counts() // 0x10F0FA40
{
	mangled_x86(MANGLED_TODO, "?d3d_resource_tracker_output_allocated_resource_counts@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10F0FBAE
	// static ...; // 0x10F0FB95
	// static ...; // 0x10F0FB7C
	// static ...; // 0x10F0FB64
	// static ...; // 0x10F0FB51
	// static ...; // 0x10F0FB3E
	// static ...; // 0x10F0FB20
	// static ...; // 0x10F0FACC
	// static ...; // 0x10F0FAC4
	// long allocated_surfaces;
	// long allocated_pixel_shaders;
	// long allocated_textures;
	// long allocated_vertex_declarations;
	// long allocated_index_buffers;
	// long allocated_vertex_buffers;
	// long allocated_vertex_shaders;
	todo("implement");
	_sub_10F0FA40();
}

/* ---------- private code */
