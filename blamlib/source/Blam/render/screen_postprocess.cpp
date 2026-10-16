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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const c_rasterizer_clear_sampler_textures = reinterpret_cast<void (*)()>(0xA22AB0);
	static auto const c_rasterizer_draw_fullscreen_quad = reinterpret_cast<void (*)(long, long)>(0xA45EE0);
	static auto const c_rasterizer_get_surface_height = reinterpret_cast<long (*)(long)>(0xA487A0);
	static auto const c_rasterizer_get_surface_width = reinterpret_cast<long (*)(long)>(0xA48810);
	static auto const c_rasterizer_set_explicit_shaders = reinterpret_cast<bool (*)(long, long, long, long)>(0xA23300);
	static auto const c_rasterizer_set_pixel_shader_constant = reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270);
	static auto const c_rasterizer_set_render_target = reinterpret_cast<e_surface (*)(long, e_surface, long)>(0xA48E40);
	static auto const c_rasterizer_set_sampler_address_mode = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)>(0xA23570);
	static auto const c_rasterizer_set_sampler_filter_mode = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_filter_mode,long>)>(0xA23660);
	static auto const c_rasterizer_set_sampler_texture = reinterpret_cast<void (*)(long, c_rasterizer_texture_ref)>(0xA23810);
	static auto const c_rasterizer_set_sampler_texture_direct = reinterpret_cast<void (*)(long, long)>(0xA23530);
	static auto const c_rasterizer_set_surface_as_texture = reinterpret_cast<void (*)(long, e_surface)>(0xA48F20);
	static auto const c_rasterizer_set_vertex_shader_constant = reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66410);
}

void *offset_pointer(void *pointer, long offset);  // hades: added for 0x10F10B40

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

e_surface c_screen_postprocess::blur_display(float blur_x, float blur_y) // 0x10F10B40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?blur_display@c_screen_postprocess@@SA?AW4e_surface@@MM@Z");

	if (((e_surface (*)(long))0xA48720)(0) == 29)
	{
		e_surface blur_surface = _surface_screenshot_display;
		void *player_view = *(void **)0x50DEDF0;
		if (player_view)
			blur_surface = *(e_surface *)offset_pointer(player_view, 0x26B0);
		((e_surface (*)(long, e_surface, long))0xA48E40)(0, _surface_aux_small, -1);
		((void (*)(long, __int32, float, unsigned char))0xA213F0)(1, 0xFF000000, 0.0f, 0);
		((void (*)(long, long))0xA231E0)(0, 7);
		((void (*)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *))0xA60460)(39, blur_surface, _surface_aux_small, 2, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
		((void (*)(long, long))0xA231E0)(0, 15);
		((void (*)(e_surface, e_surface, float, float))0xA60D60)(_surface_aux_small, _surface_aux_small2, blur_x, blur_y);
	}
	return _surface_aux_small;
}

e_surface c_screen_postprocess::blur_display(float blur_x, float blur_y, e_surface blur_surface) // 0x10F10D20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?blur_display@c_screen_postprocess@@SA?AW4e_surface@@MMW42@@Z");

	if (((e_surface (*)(long))0xA48720)(0) == 29)
	{
		((e_surface (*)(long, e_surface, long))0xA48E40)(0, _surface_aux_small, -1);
		((void (*)(long, __int32, float, unsigned char))0xA213F0)(1, 0xFF000000, 0.0f, 0);
		((void (*)(long, long))0xA231E0)(0, 7);
		((void (*)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *))0xA60460)(39, blur_surface, _surface_aux_small, 2, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
		((void (*)(long, long))0xA231E0)(0, 15);
		((void (*)(e_surface, e_surface, float, float))0xA60D60)(_surface_aux_small, _surface_aux_small2, blur_x, blur_y);
	}
	return _surface_aux_small;
}

void c_screen_postprocess::render_screen_effect_blur(float x_blur, float y_blur) // 0x10F113D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_screen_effect_blur@c_screen_postprocess@@SAXMM@Z");

	if (x_blur > 0.0f || y_blur > 0.0f)
	{
		float blur_x = fmaxf(x_blur - 0.5f, 0.35f);
		float blur_y = fmaxf(y_blur - 0.5f, 0.35f);
		((void (*)(long))0xA63510)(0);
		e_surface blurred_surface = c_screen_postprocess::blur_display(blur_x, blur_y, _surface_screenshot_display);
		((void (*)(long))0xA22D10)(13);
		float blur_blend = fminf(fmaxf(x_blur, y_blur) * 300.0f, 255.0f);
		__int32 blur_blendi = *(__int32 *)&blur_blend;
		((void (*)(unsigned long))0xA231A0)((((blur_blendi << 8) | blur_blendi) << 8 | blur_blendi) << 8 | blur_blendi);
		((void (*)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *))0xA60460)(51, blurred_surface, _surface_screenshot_display, 2, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
		((void (*)(long))0xA22D10)(0);
	}
}

bool c_screen_postprocess::smaa_initialize(long resolution_x, long resolution_y) // 0x10F116D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?smaa_initialize@c_screen_postprocess@@SA_NJJ@Z");

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
			((void (*)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(7, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
			((void (*)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(7, _filter_bilinear);
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

	IDirect3DDevice9Ex *const device = c_rasterizer::get_device();
	if (smaa_initialize(eldorado::c_rasterizer_get_surface_width(dst_surface), eldorado::c_rasterizer_get_surface_height(dst_surface)))
	{
		bool result = debug_mode == s_smaa_globals::_smaa_debug_mode_velocity_postprocessed;
		float z_near;
		float z_far;
		eldorado::c_rasterizer_set_render_target(1, _surface_none, -1);
		eldorado::c_rasterizer_set_render_target(2, _surface_none, -1);
		eldorado::c_rasterizer_set_render_target(3, _surface_none, -1);
		eldorado::c_rasterizer_set_surface_as_texture(1, _surface_depth_fp32);
		eldorado::c_rasterizer_set_sampler_address_mode(1, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
		eldorado::c_rasterizer_set_sampler_filter_mode(1, _filter_bilinear);
		void (*const rasterizer_get_z_planes)(float *, float *) = (void (*)(float *, float *))0xA25AA0;
		rasterizer_get_z_planes(&z_near, &z_far);
		real_vector4d depth_constants;
		depth_constants.i = -(z_far / (z_far - z_near) * z_near);
		depth_constants.j = z_far / (z_far - z_near);
		depth_constants.k = 0.0f;
		depth_constants.w = 0.0f;
		eldorado::c_rasterizer_set_pixel_shader_constant(3, 1, &depth_constants);
		if (smaa_globals.temporal_enabled)
			smaa_render_velocity(device, dst_surface, debug_mode);
		else
			smaa_globals.temporal_valid = false;
		if (debug_mode != s_smaa_globals::_smaa_debug_mode_velocity_postprocessed && eldorado::c_rasterizer_set_explicit_shaders(110, 7, 0, 0))
		{
			if (debug_mode == s_smaa_globals::_smaa_debug_mode_edges)
				eldorado::c_rasterizer_set_render_target(0, dst_surface, -1);
			else
				device->SetRenderTarget(0, smaa_globals.edge_srf);
			real_vector4d pixel_size;
			pixel_size.i = 1.0f / smaa_globals.res_x;
			pixel_size.j = 1.0f / smaa_globals.res_y;
			pixel_size.k = (float)smaa_globals.res_x;
			pixel_size.w = (float)smaa_globals.res_y;
			eldorado::c_rasterizer_set_pixel_shader_constant(1, 1, &pixel_size);
			eldorado::c_rasterizer_set_vertex_shader_constant(1, 1, &pixel_size);
			real_vector4d depth_threshold;
			depth_threshold.i = smaa_globals.depth_threshold;
			depth_threshold.j = 0.0f;
			depth_threshold.k = 0.0f;
			depth_threshold.w = 0.0f;
			eldorado::c_rasterizer_set_pixel_shader_constant(2, 1, &depth_threshold);
			eldorado::c_rasterizer_set_surface_as_texture(0, src_surface);
			eldorado::c_rasterizer_set_sampler_texture_direct(0, 0);
			eldorado::c_rasterizer_set_sampler_address_mode(0, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
			eldorado::c_rasterizer_set_sampler_filter_mode(0, _filter_bilinear);
			eldorado::c_rasterizer_draw_fullscreen_quad(smaa_globals.res_x, smaa_globals.res_y);
			if (debug_mode == s_smaa_globals::_smaa_debug_mode_edges)
			{
				eldorado::c_rasterizer_clear_sampler_textures();
				return true;
			}
			if (eldorado::c_rasterizer_set_explicit_shaders(110, 7, 0, 1))
			{
				if (debug_mode == s_smaa_globals::_smaa_debug_mode_blend_weights)
					eldorado::c_rasterizer_set_render_target(0, dst_surface, -1);
				else
					device->SetRenderTarget(0, smaa_globals.blend_srf);
				device->SetTexture(2, smaa_globals.edge_buffer);
				eldorado::c_rasterizer_set_sampler_texture_direct(2, 0);
				eldorado::c_rasterizer_set_sampler_address_mode(2, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
				eldorado::c_rasterizer_set_sampler_filter_mode(2, _filter_bilinear);
				{
					s_rasterizer_globals *rasg = c_rasterizer_globals::get();
					c_rasterizer_texture_ref area_tex(-1);
					c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &area_tex, _default_bitmap_smaa_area);
					eldorado::c_rasterizer_set_sampler_texture(3, area_tex);
					eldorado::c_rasterizer_set_sampler_address_mode(3, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
					eldorado::c_rasterizer_set_sampler_filter_mode(3, _filter_bilinear);
					c_rasterizer_texture_ref search_tex(-1);
					c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &search_tex, _default_bitmap_smaa_search);
					eldorado::c_rasterizer_set_sampler_texture(4, search_tex);
					eldorado::c_rasterizer_set_sampler_address_mode(4, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
					eldorado::c_rasterizer_set_sampler_filter_mode(4, _filter_bilinear);
				}
				eldorado::c_rasterizer_draw_fullscreen_quad(smaa_globals.res_x, smaa_globals.res_y);
				if (debug_mode == s_smaa_globals::_smaa_debug_mode_blend_weights)
				{
					eldorado::c_rasterizer_clear_sampler_textures();
					return true;
				}
				if (eldorado::c_rasterizer_set_explicit_shaders(110, 7, 0, 2))
				{
					if (smaa_globals.temporal_valid)
					{
						device->SetTexture(2, nullptr);
						device->SetRenderTarget(0, smaa_globals.edge_srf);
					}
					else
					{
						eldorado::c_rasterizer_set_render_target(0, dst_surface, -1);
					}
					eldorado::c_rasterizer_set_sampler_texture_direct(0, 1);
					device->SetTexture(5, smaa_globals.blend_buffer);
					eldorado::c_rasterizer_set_sampler_address_mode(5, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
					eldorado::c_rasterizer_set_sampler_filter_mode(5, _filter_bilinear);
					device->SetTexture(6, smaa_globals.velocity_buffer);
					eldorado::c_rasterizer_set_sampler_texture_direct(6, 0);
					eldorado::c_rasterizer_set_sampler_address_mode(6, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
					eldorado::c_rasterizer_set_sampler_filter_mode(6, _filter_bilinear);
					eldorado::c_rasterizer_draw_fullscreen_quad(smaa_globals.res_x, smaa_globals.res_y);
					if (smaa_globals.temporal_valid)
					{
						if (eldorado::c_rasterizer_set_explicit_shaders(110, 7, 0, 10))
						{
							eldorado::c_rasterizer_set_render_target(0, dst_surface, -1);
							device->SetTexture(2, smaa_globals.edge_buffer);
							eldorado::c_rasterizer_set_sampler_texture_direct(2, 1);
							device->SetTexture(8, smaa_globals.prev_rt);
							eldorado::c_rasterizer_set_sampler_texture_direct(8, 1);
							eldorado::c_rasterizer_set_sampler_address_mode(8, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
							eldorado::c_rasterizer_set_sampler_filter_mode(8, _filter_bilinear);
							eldorado::c_rasterizer_draw_fullscreen_quad(smaa_globals.res_x, smaa_globals.res_y);
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
			eldorado::c_rasterizer_clear_sampler_textures();
			eldorado::c_rasterizer_set_render_target(0, _surface_none, -1);
			if (smaa_globals.temporal_enabled)
			{
				if (!smaa_globals.temporal_valid)
					smaa_globals.temporal_valid = true;
				IDirect3DSurface9 *dst = ((c_surface_group *)0x510D8D0)[dst_surface].surfaces[0].m_surface;
				device->StretchRect(dst, nullptr, smaa_globals.prev_rt_srf, nullptr, D3DTEXF_NONE);
				IDirect3DSurface9 *dpth_fp32 = ((c_surface_group *)0x510D8D0)[23].surfaces[0].m_surface;
				device->StretchRect(dpth_fp32, nullptr, smaa_globals.prev_depth_srf, nullptr, D3DTEXF_NONE);
			}
			eldorado::c_rasterizer_set_render_target(0, dst_surface, -1);
			return true;
		}
	}
	eldorado::c_rasterizer_set_render_target(0, _surface_none, -1);
	IDirect3DSurface9 *src = ((c_surface_group *)0x510D8D0)[src_surface].surfaces[0].m_surface;
	IDirect3DSurface9 *dst = ((c_surface_group *)0x510D8D0)[dst_surface].surfaces[0].m_surface;
	device->StretchRect(src, nullptr, dst, nullptr, D3DTEXF_NONE);
	eldorado::c_rasterizer_set_render_target(0, dst_surface, -1);
	return false;
}

/* ---------- private code */
