#ifndef __BLAM_RENDER_SCREEN_POSTPROCESS_HPP__
#define __BLAM_RENDER_SCREEN_POSTPROCESS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/camera/observer.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_camera.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

/* ---------- forward declarations */

struct c_camera_fx_values;
struct c_screen_postprocess;
struct real_rectangle2d;
struct s_camera_fx_lightshafts_struct;
struct s_observer_depth_of_field;
struct s_render_camera;
struct s_render_projection;

/* ---------- constants */

/* ---------- definitions */

struct c_screen_postprocess
{
	public:
	struct s_settings
	{
		char field_0; // 0x0
		__int32 field_4; // 0x4
		__int32 flags; // 0x8
		__int32 field_C; // 0xC
		__int32 field_10; // 0x10
		__int32 field_14; // 0x14
		__int32 field_18; // 0x18
		char field_1C; // 0x1C
		__int32 field_20; // 0x20
		float field_24; // 0x24
		char field_28; // 0x28
		bool field_29; // 0x29
		float field_2C; // 0x2C
		__int32 field_30; // 0x30
		char field_34; // 0x34
		char field_35; // 0x35
		char field_36; // 0x36
		char field_37; // 0x37
	};
	static_assert(sizeof(s_settings) == 56, "Invalid s_settings size");
	static_assert(offsetof(s_settings, field_4) == 0x4, "s_settings::field_4 moved when its reconstructed padding was removed");
	static_assert(offsetof(s_settings, field_20) == 0x20, "s_settings::field_20 moved when its reconstructed padding was removed");
	static_assert(offsetof(s_settings, field_2C) == 0x2C, "s_settings::field_2C moved when its reconstructed padding was removed");
	struct s_smaa_globals
	{
		public:
		enum e_smaa_debug_mode
		{
			_smaa_debug_mode_none = 0,
			_smaa_debug_mode_edges,
			_smaa_debug_mode_blend_weights,
			_smaa_debug_mode_velocity_postprocessed,
		};
		public:
		IDirect3DTexture9 *edge_buffer; // 0x0
		IDirect3DTexture9 *blend_buffer; // 0x4
		IDirect3DTexture9 *velocity_buffer; // 0x8
		IDirect3DTexture9 *prev_rt; // 0xC
		IDirect3DTexture9 *prev_depth; // 0x10
		IDirect3DSurface9 *edge_srf; // 0x14
		IDirect3DSurface9 *blend_srf; // 0x18
		IDirect3DSurface9 *velocity_srf; // 0x1C
		IDirect3DSurface9 *prev_rt_srf; // 0x20
		IDirect3DSurface9 *prev_depth_srf; // 0x24
		long res_x; // 0x28
		long res_y; // 0x2C
		float depth_threshold; // 0x30
		bool valid; // 0x34
		bool temporal_valid; // 0x35
		bool temporal_enabled; // 0x36
		bool reinit_next_frame; // 0x37
		float last_view_proj[4][4]; // 0x38
	private:
		_inline bool init_surface(IDirect3DDevice9 *device, IDirect3DTexture9 **tex, IDirect3DSurface9 **srf, _D3DFORMAT format);
	public:
		_inline void set_reinit();
		_inline void set_resolution(long res_x, long res_y);
		_inline bool init_surfaces(IDirect3DDevice9 *device);
		_inline void destroy_surfaces();
	};
	static_assert(sizeof(s_smaa_globals) == 120, "Invalid s_smaa_globals size");
	public:
	static s_settings const &x_settings;
	static s_smaa_globals smaa_globals;
	static void (*const copy)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *);
	static void (*const gaussian_blur)(e_surface, e_surface, float, float);
	static void (*const gaussian_blur_fixed)(e_surface, e_surface, float, float, float, float);
	static void (*const setup_rasterizer_for_postprocess)(bool);
	static void (*const postprocess_final_composite)(e_surface, e_surface, float, float, float, float, bool, s_observer_depth_of_field *);
	static e_surface (*const postprocess_bloom_buffer)(e_surface, c_camera_fx_values *, long);
	static void (*const render_lightshafts)(s_camera_fx_lightshafts_struct *, s_render_projection *, s_render_camera *, e_surface, e_surface);
	static void (*const apply_binary_op_ex)(e_rasterizer_default_shader, e_surface, e_surface, e_surface, long, e_sampler_address_mode, float, float, float, float);
	static e_surface blur_display(float blur_x, float blur_y, e_surface blur_surface);
	static e_surface blur_display(float blur_x, float blur_y);
	static void render_screen_effect_blur(float x_blur, float y_blur);
	static bool smaa_initialize(long resolution_x, long resolution_y);
	static bool smaa_render(e_surface src_surface, e_surface dst_surface, long debug_mode);
	static void smaa_render_velocity(IDirect3DDevice9 *device, e_surface dst_surface, long debug_mode);
};
static_assert(sizeof(c_screen_postprocess) == 1, "Invalid c_screen_postprocess size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline bool c_screen_postprocess::s_smaa_globals::init_surface(IDirect3DDevice9 *device, IDirect3DTexture9 **tex, IDirect3DSurface9 **srf, _D3DFORMAT format) // 0x10F11160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?init_surface@s_smaa_globals@c_screen_postprocess@@AAE_NPAUIDirect3DDevice9@@PAPAUIDirect3DTexture9@@PAPAUIDirect3DSurface9@@W4_D3DFORMAT@@@Z");
	// _D3DFORMAT format;
	// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
	// function call : HRESULT (unsigned __int32, IDirect3DSurface9 **)
	// function call : unsigned long ()

	if (FAILED(device->CreateTexture(res_x, res_y, 1, D3DUSAGE_RENDERTARGET, format, D3DPOOL_DEFAULT, tex, nullptr)))
		return false;

	if (FAILED((*tex)->GetSurfaceLevel(0, srf)))
	{
		(*tex)->Release();
		*tex = nullptr;
		return false;
	}

	return true;
}

_inline void c_screen_postprocess::s_smaa_globals::set_reinit() // 0x10A22100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_reinit@s_smaa_globals@c_screen_postprocess@@QAEXXZ");
	// c_screen_postprocess::s_smaa_globals *const this;

	valid = false;
	reinit_next_frame = true;
}

_inline void c_screen_postprocess::s_smaa_globals::set_resolution(long res_x, long res_y) // 0x10F11660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_resolution@s_smaa_globals@c_screen_postprocess@@QAEXJJ@Z");
	// long res_y;

	this->res_x = res_x;
	this->res_y = res_y;
}

_extern bool _sub_10F11290(c_screen_postprocess::s_smaa_globals *const, IDirect3DDevice9 *);
_inline bool c_screen_postprocess::s_smaa_globals::init_surfaces(IDirect3DDevice9 *device) // 0x10F11290
{
	mangled_x86(MANGLED_TODO, "?init_surfaces@s_smaa_globals@c_screen_postprocess@@QAE_NPAUIDirect3DDevice9@@@Z");
	// IDirect3DDevice9 *device;
	todo("implement");
	bool __result = _sub_10F11290(this, device);
	return __result;
}

_extern void _sub_10F10EC0(c_screen_postprocess::s_smaa_globals *const);
_inline void c_screen_postprocess::s_smaa_globals::destroy_surfaces() // 0x10F10EC0
{
	mangled_x86(MANGLED_TODO, "?destroy_surfaces@s_smaa_globals@c_screen_postprocess@@QAEXXZ");
	// c_screen_postprocess::s_smaa_globals *const this;
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	todo("implement");
	_sub_10F10EC0(this);
}

/* ---------- private code */

#endif // __BLAM_RENDER_SCREEN_POSTPROCESS_HPP__
