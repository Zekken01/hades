/* ---------- headers */

#include "Blam/render/screen_postprocess.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>

/* ---------- forward declarations */

struct c_player_view;
struct c_rasterizer_texture_ref;
struct c_screen_postprocess;
struct real_matrix4x3;
struct real_rectangle2d;
struct real_vector4d;
struct s_rasterizer_globals;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void *offset_pointer(void *pointer, long offset);  // hades: added for 0x10F10B40

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

e_surface c_screen_postprocess::blur_display(float blur_x, float blur_y) // 0x10F10B40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?blur_display@c_screen_postprocess@@SA?AW4e_surface@@MM@Z");
	// float blur_y;
		// e_surface blur_surface;
		// void *player_view;
	// function call : e_surface (*const)(long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(long, __int32, float, unsigned char)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(e_surface, e_surface, float, float)

	if (((e_surface (*)(long))0xA48720)(0) == 29)
	{
		e_surface blur_surface = (e_surface)29;
		void *player_view = *(void **)0x50DEDF0;
		if (player_view)
			blur_surface = *(e_surface *)offset_pointer(player_view, 0x26B0);
		((e_surface (*)(long, e_surface, long))0xA48E40)(0, (e_surface)34, -1);
		((void (*)(long, __int32, float, unsigned char))0xA213F0)(1, 0xFF000000, 0.0f, 0);
		((void (*)(long, long))0xA231E0)(0, 7);
		((void (*)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *))0xA60460)(39, blur_surface, (e_surface)34, 2, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
		((void (*)(long, long))0xA231E0)(0, 15);
		((void (*)(e_surface, e_surface, float, float))0xA60D60)((e_surface)34, (e_surface)45, blur_x, blur_y);
	}
	return (e_surface)34;
}

e_surface c_screen_postprocess::blur_display(float blur_x, float blur_y, e_surface blur_surface) // 0x10F10D20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?blur_display@c_screen_postprocess@@SA?AW4e_surface@@MMW42@@Z");
	// e_surface blur_surface;
	// function call : e_surface (*const)(long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(long, __int32, float, unsigned char)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(e_surface, e_surface, float, float)

	if (((e_surface (*)(long))0xA48720)(0) == 29)
	{
		((e_surface (*)(long, e_surface, long))0xA48E40)(0, (e_surface)34, -1);
		((void (*)(long, __int32, float, unsigned char))0xA213F0)(1, 0xFF000000, 0.0f, 0);
		((void (*)(long, long))0xA231E0)(0, 7);
		((void (*)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *))0xA60460)(39, blur_surface, (e_surface)34, 2, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
		((void (*)(long, long))0xA231E0)(0, 15);
		((void (*)(e_surface, e_surface, float, float))0xA60D60)((e_surface)34, (e_surface)45, blur_x, blur_y);
	}
	return (e_surface)34;
}

void c_screen_postprocess::render_screen_effect_blur(float x_blur, float y_blur) // 0x10F113D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_screen_effect_blur@c_screen_postprocess@@SAXMM@Z");
	// float y_blur;
		// float blur_x;
		// e_surface blurred_surface;
		// float blur_y;
		// float blur_blend;
		// __int32 blur_blendi;
	// function call : void (*const)(bool)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : void (*const)(long)

	if (x_blur > 0.0f || y_blur > 0.0f)
	{
		float blur_x = fmaxf(x_blur - 0.5f, 0.35f);
		float blur_y = fmaxf(y_blur - 0.5f, 0.35f);
		((void (*)(long))0xA63510)(0);
		e_surface blurred_surface = c_screen_postprocess::blur_display(blur_x, blur_y, (e_surface)29);
		((void (*)(long))0xA22D10)(13);
		float blur_blend = fminf(fmaxf(x_blur, y_blur) * 300.0f, 255.0f);
		__int32 blur_blendi = *(__int32 *)&blur_blend;
		((void (*)(unsigned long))0xA231A0)((((blur_blendi << 8) | blur_blendi) << 8 | blur_blendi) << 8 | blur_blendi);
		((void (*)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *))0xA60460)(51, blurred_surface, (e_surface)29, 2, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
		((void (*)(long))0xA22D10)(0);
	}
}

bool c_screen_postprocess::smaa_initialize(long resolution_x, long resolution_y) // 0x10F116D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?smaa_initialize@c_screen_postprocess@@SA_NJJ@Z");
	// long resolution_y;

	if (smaa_globals.valid && !smaa_globals.reinit_next_frame)
	{
		return true;
	}
	else if (!smaa_globals.valid && smaa_globals.reinit_next_frame)
	{
		smaa_globals.destroy_surfaces();
		smaa_globals.reinit_next_frame = false;
		return false;
	}
	else
	{
		smaa_globals.valid = false;
		smaa_globals.reinit_next_frame = false;
		smaa_globals.temporal_valid = false;
		smaa_globals.temporal_enabled = true;
		smaa_globals.set_resolution(resolution_x, resolution_y);
		smaa_globals.depth_threshold = 0.005f;
		if (smaa_globals.init_surfaces(c_rasterizer::get_device()))
		{
			smaa_globals.valid = true;
		}
		return smaa_globals.valid;
	}
}

void c_screen_postprocess::smaa_render_velocity(IDirect3DDevice9 *device, e_surface dst_surface, long debug_mode) // 0x10F12980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?smaa_render_velocity@c_screen_postprocess@@SAXPAUIDirect3DDevice9@@W4e_surface@@J@Z");
	// static ...; // 0x10F12C8C
	// IDirect3DDevice9 *device;
	// e_surface dst_surface;
	// long debug_mode;
	// void (*const combine_projection_and_view_matrix)(real_matrix4x3 *, float *, float *);
	// float view_proj[4][4];
	// c_player_view *const player_view;
	// function call : void (*const)(real_matrix4x3 *, float *, float *)
	// function call : bool (*const)(long, long, long, long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : HRESULT (unsigned long, IDirect3DSurface9 *)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long)

	void (*const combine_projection_and_view_matrix)(real_matrix4x3 *, float *, float *) = reinterpret_cast<void (*)(real_matrix4x3 *, float *, float *)>(0xA29440);
	c_player_view *const player_view = c_player_view::get_current();
	float view_proj[4][4];
	memset(view_proj, 0, sizeof(view_proj));
	combine_projection_and_view_matrix(&player_view->render_projection.world_to_view, &player_view->render_projection.projection_matrix[0][0], &view_proj[0][0]);
	if (smaa_globals.temporal_valid)
	{
		if (((bool (*)(long, long, long, long))0xA23300)(110, 7, 0, 9))
		{
			if (debug_mode == s_smaa_globals::_smaa_debug_mode_velocity_postprocessed)
				((e_surface (*)(long, e_surface, long))0xA48E40)(0, dst_surface, -1);
			else
				device->SetRenderTarget(0, smaa_globals.velocity_srf);
			device->SetTexture(7, smaa_globals.prev_depth);
			((void (*)(long, long))0xA23530)(7, 0);
			((void (*)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(7, (e_sampler_address_mode)1, (e_sampler_address_mode)1, (e_sampler_address_mode)1);
			((void (*)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(7, (e_sampler_filter_mode)2);
			((void (*)(long, long, real_vector4d const *))0xA66270)(4, 4, (real_vector4d const *)&view_proj[0][0]);
			((void (*)(long, long, real_vector4d const *))0xA66410)(4, 4, (real_vector4d const *)&view_proj[0][0]);
			((void (*)(long, long, real_vector4d const *))0xA66270)(8, 4, (real_vector4d const *)&smaa_globals.last_view_proj[0][0]);
			((void (*)(long, long, real_vector4d const *))0xA66410)(8, 4, (real_vector4d const *)&smaa_globals.last_view_proj[0][0]);
			((void (*)(long, long))0xA45EE0)(smaa_globals.res_x, smaa_globals.res_y);
		}
		else
			smaa_globals.temporal_valid = false;
	}
	memcpy(smaa_globals.last_view_proj, view_proj, sizeof(view_proj));
}

bool c_screen_postprocess::smaa_render(e_surface src_surface, e_surface dst_surface, long debug_mode) // 0x10F117F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?smaa_render@c_screen_postprocess@@SA_NW4e_surface@@0J@Z");
	// static ...; // 0x10F125D7
	// static ...; // 0x10F125CC
	// static ...; // 0x10F125BC
	// static ...; // 0x10F125B3
	// static ...; // 0x10F125A8
	// static ...; // 0x10F12554
	// static ...; // 0x10F1254C
	// e_surface src_surface;
	// e_surface dst_surface;
	// long debug_mode;
	// IDirect3DDevice9Ex *const device;
	// IDirect3DSurface9 *src;
	// IDirect3DSurface9 *dst;
		// real_vector4d depth_constants;
		// void (*const rasterizer_get_z_planes)(float *, float *);
		// float z_near;
		// float z_far;
		// bool result;
			// real_vector4d depth_threshold;
			// real_vector4d pixel_size;
				// c_rasterizer_texture_ref area_tex;
				// s_rasterizer_globals *rasg;
				// c_rasterizer_texture_ref search_tex;
			// IDirect3DSurface9 *dpth_fp32;
			// IDirect3DSurface9 *dst;
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(float *, float *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : bool (*const)(long, long, long, long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : HRESULT (unsigned long, IDirect3DSurface9 *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, long)
	// function call : void (*const)()
	// function call : bool (*const)(long, long, long, long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : HRESULT (unsigned long, IDirect3DSurface9 *)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, long)
	// function call : void (*const)()
	// function call : bool (*const)(long, long, long, long)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : HRESULT (unsigned long, IDirect3DSurface9 *)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(long, long)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, long)
	// function call : bool (*const)(long, long, long, long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, long)
	// function call : void (*const)()
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : HRESULT (IDirect3DSurface9 *, tagRECT const *, IDirect3DSurface9 *, tagRECT const *, _D3DTEXTUREFILTERTYPE)
	// function call : HRESULT (IDirect3DSurface9 *, tagRECT const *, IDirect3DSurface9 *, tagRECT const *, _D3DTEXTUREFILTERTYPE)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : HRESULT (IDirect3DSurface9 *, tagRECT const *, IDirect3DSurface9 *, tagRECT const *, _D3DTEXTUREFILTERTYPE)
	// function call : e_surface (*const)(long, e_surface, long)

	IDirect3DDevice9Ex *const device = c_rasterizer::get_device();
	if (smaa_initialize(((long (*const)(long))0xA48810)(dst_surface), ((long (*const)(long))0xA487A0)(dst_surface)))
	{
		bool result = debug_mode == s_smaa_globals::_smaa_debug_mode_velocity_postprocessed;
		float z_near;
		float z_far;
		((e_surface (*const)(long, e_surface, long))0xA48E40)(1, (e_surface)0, -1);
		((e_surface (*const)(long, e_surface, long))0xA48E40)(2, (e_surface)0, -1);
		((e_surface (*const)(long, e_surface, long))0xA48E40)(3, (e_surface)0, -1);
		((void (*const)(long, e_surface))0xA48F20)(1, (e_surface)23);
		((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(1, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
		((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(1, _filter_bilinear);
		void (*const rasterizer_get_z_planes)(float *, float *) = (void (*)(float *, float *))0xA25AA0;
		rasterizer_get_z_planes(&z_near, &z_far);
		real_vector4d depth_constants;
		depth_constants.i = -(z_far / (z_far - z_near) * z_near);
		depth_constants.j = z_far / (z_far - z_near);
		depth_constants.k = 0.0f;
		depth_constants.w = 0.0f;
		((void (*const)(long, long, real_vector4d const *))0xA66270)(3, 1, &depth_constants);
		if (smaa_globals.temporal_enabled)
			smaa_render_velocity(device, dst_surface, debug_mode);
		else
			smaa_globals.temporal_valid = false;
		if (debug_mode != s_smaa_globals::_smaa_debug_mode_velocity_postprocessed && ((bool (*const)(long, long, long, long))0xA23300)(110, 7, 0, 0))
		{
			if (debug_mode == s_smaa_globals::_smaa_debug_mode_edges)
				((e_surface (*const)(long, e_surface, long))0xA48E40)(0, dst_surface, -1);
			else
				device->SetRenderTarget(0, smaa_globals.edge_srf);
			real_vector4d pixel_size;
			pixel_size.i = 1.0f / smaa_globals.res_x;
			pixel_size.j = 1.0f / smaa_globals.res_y;
			pixel_size.k = (float)smaa_globals.res_x;
			pixel_size.w = (float)smaa_globals.res_y;
			((void (*const)(long, long, real_vector4d const *))0xA66270)(1, 1, &pixel_size);
			((void (*const)(long, long, real_vector4d const *))0xA66410)(1, 1, &pixel_size);
			real_vector4d depth_threshold;
			depth_threshold.i = smaa_globals.depth_threshold;
			depth_threshold.j = 0.0f;
			depth_threshold.k = 0.0f;
			depth_threshold.w = 0.0f;
			((void (*const)(long, long, real_vector4d const *))0xA66270)(2, 1, &depth_threshold);
			((void (*const)(long, e_surface))0xA48F20)(0, src_surface);
			((void (*const)(long, long))0xA23530)(0, 0);
			((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(0, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
			((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(0, _filter_bilinear);
			((void (*const)(long, long))0xA45EE0)(smaa_globals.res_x, smaa_globals.res_y);
			if (debug_mode == s_smaa_globals::_smaa_debug_mode_edges)
			{
				((void (*const)())0xA22AB0)();
				return true;
			}
			if (((bool (*const)(long, long, long, long))0xA23300)(110, 7, 0, 1))
			{
				if (debug_mode == s_smaa_globals::_smaa_debug_mode_blend_weights)
					((e_surface (*const)(long, e_surface, long))0xA48E40)(0, dst_surface, -1);
				else
					device->SetRenderTarget(0, smaa_globals.blend_srf);
				device->SetTexture(2, smaa_globals.edge_buffer);
				((void (*const)(long, long))0xA23530)(2, 0);
				((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(2, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
				((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(2, _filter_bilinear);
				{
					s_rasterizer_globals *rasg = c_rasterizer_globals::get();
					c_rasterizer_texture_ref area_tex(-1);
					c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &area_tex, (e_rasterizer_default_bitmap)15);
					((void (*const)(long, c_rasterizer_texture_ref))0xA23810)(3, area_tex);
					((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(3, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
					((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(3, _filter_bilinear);
					c_rasterizer_texture_ref search_tex(-1);
					c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &search_tex, (e_rasterizer_default_bitmap)16);
					((void (*const)(long, c_rasterizer_texture_ref))0xA23810)(4, search_tex);
					((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(4, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
					((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(4, _filter_bilinear);
				}
				((void (*const)(long, long))0xA45EE0)(smaa_globals.res_x, smaa_globals.res_y);
				if (debug_mode == s_smaa_globals::_smaa_debug_mode_blend_weights)
				{
					((void (*const)())0xA22AB0)();
					return true;
				}
				if (((bool (*const)(long, long, long, long))0xA23300)(110, 7, 0, 2))
				{
					if (smaa_globals.temporal_valid)
					{
						device->SetTexture(2, nullptr);
						device->SetRenderTarget(0, smaa_globals.edge_srf);
					}
					else
					{
						((e_surface (*const)(long, e_surface, long))0xA48E40)(0, dst_surface, -1);
					}
					((void (*const)(long, long))0xA23530)(0, 1);
					device->SetTexture(5, smaa_globals.blend_buffer);
					((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(5, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
					((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(5, _filter_bilinear);
					device->SetTexture(6, smaa_globals.velocity_buffer);
					((void (*const)(long, long))0xA23530)(6, 0);
					((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(6, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
					((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(6, _filter_bilinear);
					((void (*const)(long, long))0xA45EE0)(smaa_globals.res_x, smaa_globals.res_y);
					if (smaa_globals.temporal_valid)
					{
						if (((bool (*const)(long, long, long, long))0xA23300)(110, 7, 0, 10))
						{
							((e_surface (*const)(long, e_surface, long))0xA48E40)(0, dst_surface, -1);
							device->SetTexture(2, smaa_globals.edge_buffer);
							((void (*const)(long, long))0xA23530)(2, 1);
							device->SetTexture(8, smaa_globals.prev_rt);
							((void (*const)(long, long))0xA23530)(8, 1);
							((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(8, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
							((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(8, _filter_bilinear);
							((void (*const)(long, long))0xA45EE0)(smaa_globals.res_x, smaa_globals.res_y);
							result = true;
						}
					}
					else
					{
						result = true;
					}
				}
			}
		}
		if (result)
		{
			((void (*const)())0xA22AB0)();
			((e_surface (*const)(long, e_surface, long))0xA48E40)(0, (e_surface)0, -1);
			if (smaa_globals.temporal_enabled)
			{
				if (!smaa_globals.temporal_valid)
					smaa_globals.temporal_valid = true;
				IDirect3DSurface9 *dst = ((c_surface_group *)0x510D8D0)[dst_surface].surfaces[0].m_surface;
				device->StretchRect(dst, nullptr, smaa_globals.prev_rt_srf, nullptr, D3DTEXF_NONE);
				IDirect3DSurface9 *dpth_fp32 = ((c_surface_group *)0x510D8D0)[23].surfaces[0].m_surface;
				device->StretchRect(dpth_fp32, nullptr, smaa_globals.prev_depth_srf, nullptr, D3DTEXF_NONE);
			}
			((e_surface (*const)(long, e_surface, long))0xA48E40)(0, dst_surface, -1);
			return true;
		}
	}
	((e_surface (*const)(long, e_surface, long))0xA48E40)(0, (e_surface)0, -1);
	IDirect3DSurface9 *src = ((c_surface_group *)0x510D8D0)[src_surface].surfaces[0].m_surface;
	IDirect3DSurface9 *dst = ((c_surface_group *)0x510D8D0)[dst_surface].surfaces[0].m_surface;
	device->StretchRect(src, nullptr, dst, nullptr, D3DTEXF_NONE);
	((e_surface (*const)(long, e_surface, long))0xA48E40)(0, dst_surface, -1);
	return false;
}

/* ---------- private code */
