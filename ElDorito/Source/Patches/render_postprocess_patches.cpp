/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/depth_of_field.hpp"
#include "Blam/render/render_blurs.hpp"
#include "Blam/render/render_globals.hpp"
#include "Blam/render/screen_postprocess.hpp"
#include "Blam/render/views/render_camera.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

#include "Modules/ModuleSettings.hpp"  // hades: added for 0x10AC21B0
#include "Modules/ModuleDebug.hpp"  // hades: added for 0x10AC04E0

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_rasterizer_globals;
struct _D3DLOCKED_RECT;
struct c_camera_fx_values;
struct c_exposure;
struct c_player_view;
struct c_rasterizer_texture_ref;
struct real_point2d;
struct real_rectangle2d;
struct real_rgb_color;
struct real_vector3d;
struct real_vector4d;
struct s_camera_fx_exposure_struct;
struct s_camera_fx_lightshafts_struct;
struct s_depth_of_field;
struct s_hue_saturation_control;
struct s_motion_blur_parameters;
struct s_observer_depth_of_field;
struct s_rasterizer_globals;
struct s_render_camera;
struct s_render_projection;
struct s_screen_effect_settings;
struct s_surface_group_description;
struct tls_data;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

typedef IDirect3DQuery9 *LPDIRECT3DQUERY9;
typedef IDirect3DSurface9 *LPDIRECT3DSURFACE9;

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const c_rasterizer_get_display_surface = reinterpret_cast<e_surface (*)()>(0xA48770);
	static auto const c_rasterizer_get_surface_height = reinterpret_cast<long (*)(long)>(0xA487A0);
	static auto const c_rasterizer_get_surface_width = reinterpret_cast<long (*)(long)>(0xA48810);
	static auto const c_rasterizer_set_pixel_shader_constant = reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270);
	static auto const c_rasterizer_set_pixel_shader_constant_bool = reinterpret_cast<void (*)(long, long, __int32 const *)>(0xA66370);
	static auto const c_rasterizer_set_pixel_shader_constant_int = reinterpret_cast<void (*)(long, long, __int32 const *)>(0xA663A0);
	static auto const c_rasterizer_set_render_target = reinterpret_cast<e_surface (*)(long, e_surface, long)>(0xA48E40);
	static auto const c_rasterizer_set_sampler_address_mode = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)>(0xA23570);
	static auto const c_rasterizer_set_sampler_filter_mode = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_filter_mode,long>)>(0xA23660);
	static auto const c_rasterizer_set_sampler_texture = reinterpret_cast<void (*)(long, c_rasterizer_texture_ref)>(0xA23810);
	static auto const c_rasterizer_set_vertex_shader_constant = reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66410);
	static auto const c_screen_postprocess_apply_binary_op_ex = reinterpret_cast<void (*)(e_rasterizer_default_shader, e_surface, e_surface, e_surface, long, e_sampler_address_mode, float, float, float, float)>(0xA60060);
	static auto const c_screen_postprocess_copy = reinterpret_cast<void (*)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)>(0xA60460);
	static auto const c_screen_postprocess_gaussian_blur = reinterpret_cast<void (*)(e_surface, e_surface, float, float)>(0xA60D60);
	static auto const c_screen_postprocess_postprocess_bloom_buffer = reinterpret_cast<e_surface (*)(e_surface, c_camera_fx_values *, long)>(0xA60F90);
	static auto const c_screen_postprocess_render_lightshafts = reinterpret_cast<void (*)(s_camera_fx_lightshafts_struct *, s_render_projection *, s_render_camera *, e_surface, e_surface)>(0xA62720);
	static auto const c_screen_postprocess_setup_rasterizer_for_postprocess = reinterpret_cast<void (*)(bool)>(0xA63510);
	static auto const copy_accumulation_target = reinterpret_cast<void (*)(e_surface, e_surface, float, float, float, float, bool, s_observer_depth_of_field *)>(0xA605B0);
	static auto const get_distortion_visible = reinterpret_cast<bool (*)()>(0xA29580);
}

#include "Modules/ModuleGraphics.hpp"  // hades: added for 0x10AC2F20

extern unsigned long *(*get_local_random_seed_address)();  // hades: added for 0x10AC04E0
extern void render_postprocess_patches_tick();
extern long detect_driver_forced_msaa();
extern void render_postprocess_patches_apply_after_init();
extern void render_postprocess_patches_apply();

void render_objects_shadow_generate_hook(long pass, unsigned long flags);
void render_post_process_reflections_enabled_hook();
void force_sampler_filter_mode_hook(long sampler, long e_sampler_filter_mode);
void set_postprocess_gamma_hook(long index, long count, real_vector4d const *constant);
void set_motion_blur_parameters_hook();
void c_screen_postprocess__postprocess_player_view_hook(c_camera_fx_values *camera_fx_values, s_render_projection *projection, s_render_camera *camera, s_screen_effect_settings *screen_effect_settings, long splitscreen_res, s_observer_depth_of_field *depth_of_field, long output_user_index);
void __fastcall c_camera_fx_settings__s_real_exposure_parameter__calculate_new_value_hook(s_camera_fx_exposure_struct *_this, void *_, c_camera_fx_values *camera_fx, __int32 flags, float forced_exposure, float forced_auto_exposure, float min, float max);
long c_screen_postprocess__downsample_generate_call_hook(e_surface source_surface, c_camera_fx_values *camera_fx, e_surface a3, e_surface a4);

/* ---------- globals */

s_motion_blur_parameters *c_rasterizer_globals::g_motion_blur_parameters = reinterpret_cast<decltype(c_rasterizer_globals::g_motion_blur_parameters)>(0x1914B90); // 0x11354A3C
bool (*s_depth_of_field::get_enabled)() = reinterpret_cast<decltype(s_depth_of_field::get_enabled)>(0xA3ECB0); // 0x11354A50
float (*s_depth_of_field::get_depth_of_field_blur_sigma)(s_depth_of_field *) = reinterpret_cast<decltype(s_depth_of_field::get_depth_of_field_blur_sigma)>(0xA3EC30); // 0x11354A54

/* ---------- private variables */

namespace hades_file_local
{
	extern long driver_forced_msaa_value; // 0x11354A2C
	extern long g_exposure_occlusion_pixels_passed; // 0x1246736C
	extern IDirect3DSurface9 *g_exposure_dup_surface; // 0x12467370
	extern bool reflections_enabled; // 0x12467374
}
using namespace hades_file_local;
/* ---------- public code */

void render_postprocess_patches_tick() // 0x10AC2F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_postprocess_patches_tick@@YAXXZ");

	reflections_enabled = (bool)Utils::Singleton<Modules::ModuleGraphics>::Instance().VarReflectionsEnabled->ValueInt;
}

long detect_driver_forced_msaa() // 0x10AC1880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?detect_driver_forced_msaa@@YAJXZ");

	IDirect3DDevice9Ex *const device = c_rasterizer::get_device();
	device->BeginScene();
	struct s_test_vertex
	{
		float x;
		float y;
		float z;
	};
	s_test_vertex test_verts[4] = { { -1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { -1.0f, -1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f } };
	long msaa_level = 0;
	IDirect3DVertexBuffer9 *test_buffer = nullptr;
	if (SUCCEEDED(device->CreateVertexBuffer(sizeof(test_verts), 0, D3DFVF_XYZ, D3DPOOL_DEFAULT, &test_buffer, NULL)))
	{
		void *test_vertices;
		if (SUCCEEDED(test_buffer->Lock(0, sizeof(test_verts), &test_vertices, 0)))
		{
			memcpy(test_vertices, test_verts, sizeof(test_verts));
			test_buffer->Unlock();
			IDirect3DSurface9 *test_surface;
			_D3DFORMAT test_format = (_D3DFORMAT)MAKEFOURCC('N', 'U', 'L', 'L');
			long test_rt_res = 256;
			if (SUCCEEDED(device->CreateRenderTarget(test_rt_res, test_rt_res, test_format, D3DMULTISAMPLE_NONE, 0, FALSE, &test_surface, NULL)))
			{
				IDirect3DQuery9 *test_query;
				if (SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_OCCLUSION, &test_query)))
				{
					device->SetRenderTarget(0, test_surface);
					device->SetStreamSource(0, test_buffer, 0, sizeof(s_test_vertex));
					device->SetFVF(D3DFVF_XYZ);
					device->SetRenderState(D3DRS_LIGHTING, FALSE);
					device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
					test_query->Issue(D3DISSUE_BEGIN);
					device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
					test_query->Issue(D3DISSUE_END);
					__int32 non_occluded_pixels;
					long cycles = 0;
					unsigned long start_time = system_milliseconds();
					if (test_query->GetData(&non_occluded_pixels, sizeof(non_occluded_pixels), 0) == S_FALSE)
					{
						while (test_query->GetData(&non_occluded_pixels, sizeof(non_occluded_pixels), D3DGETDATA_FLUSH) == S_FALSE)
						{
							if ((cycles++ >= 10000) != false)
							{
								cycles = 0;
								if (system_milliseconds() - start_time >= 100)
									break;
							}
						}
					}
					msaa_level = (long)((float)non_occluded_pixels / (test_rt_res * test_rt_res) + 0.5f);
					device->SetRenderTarget(0, NULL);
					test_query->Release();
				}
				test_surface->Release();
			}
		}
		test_buffer->Release();
	}
	device->EndScene();
	return msaa_level == 0 ? 1 : msaa_level;
}

void render_postprocess_patches_apply_after_init() // 0x10AC2E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_postprocess_patches_apply_after_init@@YAXXZ");

	driver_forced_msaa_value = detect_driver_forced_msaa();
	IDirect3DDevice9Ex *device = c_rasterizer::get_device();
	IDirect3DTexture9 *dup_exposure_tex;
	device->CreateTexture(1, 1, 1, 512, D3DFMT_R32F, D3DPOOL_SYSTEMMEM, &dup_exposure_tex, nullptr);
	dup_exposure_tex->GetSurfaceLevel(0, &g_exposure_dup_surface);
}

void render_postprocess_patches_apply() // 0x10AC21B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_postprocess_patches_apply@@YAXXZ");

	Hook(0x661770, c_screen_postprocess__postprocess_player_view_hook).Apply();
	Hook(0x678F20, render_objects_shadow_generate_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x662411, render_post_process_reflections_enabled_hook).Apply();
	Hook(0x66D3E0, force_sampler_filter_mode_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63DEA8, force_sampler_filter_mode_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	s_surface_group_description *cortana_effect_surface = &reinterpret_cast<s_surface_group_description *>(0x1914E50)[56];
	cortana_effect_surface->unknown_surface = static_cast<e_surface>(0);
	Hook(0x660A4F, set_postprocess_gamma_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x671231, set_postprocess_gamma_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x647060, set_motion_blur_parameters_hook).Apply();
	Hook(0x62A420, c_camera_fx_settings__s_real_exposure_parameter__calculate_new_value_hook).Apply();
	Hook(0x660FC7, c_screen_postprocess__downsample_generate_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	reinterpret_cast<s_surface_group_description *>(0x1914E50)[37].surface_format = 0x72;
	reinterpret_cast<s_surface_group_description *>(0x1914E50)[38].surface_format = 0x72;
	reinterpret_cast<s_surface_group_description *>(0x1914E50)[39].surface_format = 0x72;
	reinterpret_cast<s_surface_group_description *>(0x1914E50)[40].surface_format = 0x72;
	reinterpret_cast<s_surface_group_description *>(0x1914E50)[41].surface_format = 0x72;
	reinterpret_cast<s_surface_group_description *>(0x1914E50)[42].surface_format = 0x72;
	reinterpret_cast<s_surface_group_description *>(0x1914E50)[43].surface_format = 0x72;
	reinterpret_cast<s_surface_group_description *>(0x1914E50)[44].surface_format = 0x72;
	long const shadow_texture_resolution = Modules::ModuleSettings::Instance().VarShadowResolution->ValueInt;
	s_surface_group_description *shadow_surface = &reinterpret_cast<s_surface_group_description *>(0x1914E50)[3];
	shadow_surface->depth_stencil_width = shadow_texture_resolution;
	shadow_surface->depth_stencil_height = shadow_texture_resolution;
	shadow_surface->surface_width = shadow_texture_resolution;
	shadow_surface->surface_height = shadow_texture_resolution;
	s_surface_group_description *shadow_color_surface = &reinterpret_cast<s_surface_group_description *>(0x1914E50)[22];
	shadow_color_surface->depth_stencil_width = shadow_texture_resolution;
	shadow_color_surface->depth_stencil_height = shadow_texture_resolution;
	shadow_color_surface->surface_width = shadow_texture_resolution;
	shadow_color_surface->surface_height = shadow_texture_resolution;
	*(long *)0x19106E0 = shadow_texture_resolution;
	*(long *)0xA68F58 = shadow_texture_resolution;
	*(long *)0xA6B521 = shadow_texture_resolution;
	Pointer(0x16950F8).Write<int>(0x0);
	Pointer(0x16950FC).Write<int>(0x19);
	Pointer(0x1695100).Write<int>(0x32);
}

/* ---------- private code */

void render_objects_shadow_generate_hook(long pass, unsigned long flags) // 0x10AC2120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_objects_shadow_generate_hook@@YAXJK@Z");

	((void(__cdecl *)(int))0xa233c0)(0);
	((void(__cdecl *)(long, unsigned long))0xa78a50)(pass, flags);
}

__declspec(naked) void render_post_process_reflections_enabled_hook() // 0x10AC21A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_post_process_reflections_enabled_hook@@YAXXZ");

	__asm
	{
		mov al, reflections_enabled
		test al, al
		push 0xA62418
		ret
	}
}

void force_sampler_filter_mode_hook(long sampler, long e_sampler_filter_mode) // 0x10AC1FE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?force_sampler_filter_mode_hook@@YAXJJ@Z");

	void *device = *(void **)0x50daddc;
	long *sampler_filter_modes = (long *)0x1910630;
	long device_state = *(long *)0x191055c;

	if (device_state != -1)
	{
		if (sampler >= 0 && sampler < 20)
			sampler_filter_modes[sampler] = e_sampler_filter_mode;

		((void (*)(void *, long, long))0xa23700)(device, sampler, e_sampler_filter_mode);
		(*(void (__stdcall **)(void *, long, long, long))((unsigned char *)*(void **)device + 0x114))(device, sampler, 10, 1);
	}
	else if (sampler_filter_modes[sampler] != e_sampler_filter_mode)
	{
		if (sampler >= 0 && sampler < 20)
			sampler_filter_modes[sampler] = e_sampler_filter_mode;

		((void (*)(void *, long, long))0xa23700)(device, sampler, e_sampler_filter_mode);
	}
}

void set_postprocess_gamma_hook(long index, long count, real_vector4d const *constant) // 0x10AC3780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_postprocess_gamma_hook@@YAXJJPBUreal_vector4d@@@Z");

	((void(__cdecl *)(long, long, real_vector4d const *))0xA66270)(index, count, constant);

	long gamma_power_register = 8;
	real_vector4d gamma_power_constant = { Modules::ModuleGraphics::Instance().VarGammaPower->ValueFloatMax - Modules::ModuleGraphics::Instance().VarGammaPower->ValueFloat + 1.0f, 0.0f, 0.0f, 0.0f };
	((void(__cdecl *)(long, long, real_vector4d const *))0xA66270)(gamma_power_register, 1, &gamma_power_constant);
}

void set_motion_blur_parameters_hook() // 0x10AC2F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_motion_blur_parameters_hook@@YAXXZ");

	long (*const global_preferences_get_effects_quality)() = (long (*)())0x50B150;
	void (*const chud_get_crosshair_screen_position)(__int32, real_point2d *) = (void (*)(__int32, real_point2d *))0xAC9C70;
	void (*const sub_684700)(__int32, real_vector3d *) = (void (*)(__int32, real_vector3d *))0x684700;
	void (*const screenshot_get_scales)(float *, float *) = (void (*)(float *, float *))0x6102C0;
	if (!c_rasterizer_globals::g_motion_blur_parameters_set)
	{
		s_rasterizer_globals const *rasg = c_rasterizer_globals::get();
		c_rasterizer_globals::g_motion_blur_parameters->max_blur = rasg->motion_blur_parameters.max_blur;
		c_rasterizer_globals::g_motion_blur_parameters->field_04 = rasg->motion_blur_parameters.field_04;
		c_rasterizer_globals::g_motion_blur_parameters->center_falloff[0] = rasg->motion_blur_parameters.center_falloff[0];
		c_rasterizer_globals::g_motion_blur_parameters->center_falloff[1] = rasg->motion_blur_parameters.center_falloff[1];
		c_rasterizer_globals::g_motion_blur_parameters->expected_time_per_tick = rasg->motion_blur_parameters.expected_time_per_tick;
		float strength_min = 0.0f;
		float strength_max = 0.4f;
		float motion_blur_strength = Modules::ModuleSettings::Instance().VarMotionBlurStrength->ValueFloat;
		c_rasterizer_globals::g_motion_blur_parameters->blur_scale = (strength_max - strength_min) * motion_blur_strength + strength_min;
		if (global_preferences_get_effects_quality() == 2)
		{
			c_rasterizer_globals::g_motion_blur_max_taps = 24;
			c_rasterizer_globals::g_motion_blur_min_taps = 12;
		}
		else
		{
			c_rasterizer_globals::g_motion_blur_max_taps = 16;
			c_rasterizer_globals::g_motion_blur_min_taps = 6;
		}
		c_rasterizer_globals::g_motion_blur_parameters_set = 1;
	}
	__int32 width;
	__int32 height;
	Modules::ModuleSettings::Instance().GetScreenResolution(&width, &height);
	float width_scale = (float)(width - c_rasterizer_globals::g_motion_blur_min_width) / (float)(c_rasterizer_globals::g_motion_blur_max_width - c_rasterizer_globals::g_motion_blur_min_width);
	width_scale = fmax(width_scale, 0.0f);
	width_scale = (float)c_rasterizer_globals::g_motion_blur_min_taps + (float)(c_rasterizer_globals::g_motion_blur_max_taps - c_rasterizer_globals::g_motion_blur_min_taps) * width_scale;
	__int32 num_taps = (__int32)width_scale;
	if (global_preferences_get_effects_quality() != 2)
		num_taps = (__int32)fmin(width_scale, c_rasterizer_globals::g_motion_blur_max_taps);
	tls_data *tls = (tls_data *)tls_get(0);
	float timing_unknown = *(float *)((char *)tls->main_render_timing + 8);
	if (timing_unknown <= 0.000099999997)
		timing_unknown = 1.0f;
	else
		timing_unknown = c_rasterizer_globals::g_motion_blur_parameters->expected_time_per_tick / timing_unknown;
	c_player_view *current_player_view = c_player_view::get_current();
	real_vector3d unknown_effect;
	sub_684700(current_player_view->out_user_index, &unknown_effect);
	real_point2d crosshair_screen_position;
	chud_get_crosshair_screen_position(current_player_view->out_user_index, &crosshair_screen_position);
	__int32 dis_num_taps[4] = { num_taps, 0, 1, 0 };
	eldorado::c_rasterizer_set_pixel_shader_constant_int(2, 1, dis_num_taps);
	real_vector4d misc_values = { (float)num_taps, timing_unknown, c_rasterizer_globals::g_motion_blur_parameters->expected_time_per_tick, unknown_effect.k * c_rasterizer_globals::g_motion_blur_parameters->center_falloff[1] };
	eldorado::c_rasterizer_set_pixel_shader_constant(0xAC, 1, &misc_values);
	real_vector4d blur_max_and_scale = { unknown_effect.i * c_rasterizer_globals::g_motion_blur_parameters->max_blur, unknown_effect.i * c_rasterizer_globals::g_motion_blur_parameters->field_04, unknown_effect.j * c_rasterizer_globals::g_motion_blur_parameters->blur_scale * timing_unknown, -c_rasterizer_globals::g_motion_blur_parameters->center_falloff[0] * unknown_effect.j * timing_unknown };
	eldorado::c_rasterizer_set_pixel_shader_constant(0xAD, 1, &blur_max_and_scale);
	real_vector4d crosshair_center = { crosshair_screen_position.x * 2.0f - 1.0f, 1.0f - crosshair_screen_position.y * 2.0f, 0.0f, 0.0f };
	eldorado::c_rasterizer_set_pixel_shader_constant(0xAE, 1, &crosshair_center);
	__int32 const do_distortion = eldorado::get_distortion_visible();
	eldorado::c_rasterizer_set_pixel_shader_constant_bool(2, 1, &do_distortion);
}

void c_screen_postprocess__postprocess_player_view_hook(c_camera_fx_values *camera_fx_values, s_render_projection *projection, s_render_camera *camera, s_screen_effect_settings *screen_effect_settings, long splitscreen_res, s_observer_depth_of_field *depth_of_field, long output_user_index) // 0x10AC04E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_screen_postprocess__postprocess_player_view_hook@@YAXPAUc_camera_fx_values@@PAUs_render_projection@@PAUs_render_camera@@PAUs_screen_effect_settings@@JPAUs_observer_depth_of_field@@J@Z");

	char (*const global_preferences_get_anti_aliasing)() = reinterpret_cast<char (*)()>(0x50A830);
	long (*const global_preferenced_get_effects_quality)() = reinterpret_cast<long (*)()>(0x50B150);
	bool const g_render_anti_aliasing_enabled = *(bool *)0x1917D60;
	bool const g_render_light_shafts_enabled = *(bool *)0x1917D61;
	float contrast_enhance = screen_effect_settings->contrast_enhance;
	((void (__thiscall *)(s_hue_saturation_control *, float, float, float, real_rgb_color const *, real_rgb_color const *))0xA411A0)(tls_getd().hue_saturation_control, screen_effect_settings->hue_right - screen_effect_settings->hue_left, screen_effect_settings->saturation - screen_effect_settings->desaturation, contrast_enhance, &screen_effect_settings->color_filter, &screen_effect_settings->color_floor);
	float contrast = fminf(fmaxf(screen_effect_settings->gamma_enhance + 1.0 - screen_effect_settings->gamma_reduce, 0.01f), 10.0f);
	real_vector4d p_postprocess_contrast;
	p_postprocess_contrast[3] = contrast;
	p_postprocess_contrast[2] = contrast;
	p_postprocess_contrast[1] = contrast;
	p_postprocess_contrast[0] = contrast;
	eldorado::c_rasterizer_set_pixel_shader_constant(222, 1, &p_postprocess_contrast);
	eldorado::c_screen_postprocess_setup_rasterizer_for_postprocess(true);
	bool dof_enabled = s_depth_of_field::get_enabled() || depth_of_field && (depth_of_field->flags & 1);
	if (!c_screen_postprocess::x_settings.field_0)
	{
		float v20 = c_screen_postprocess::x_settings.field_24;
		float a8 = c_screen_postprocess::x_settings.field_24;
		float a7 = c_screen_postprocess::x_settings.field_24;
		e_surface v14 = eldorado::c_rasterizer_get_display_surface();
		eldorado::c_screen_postprocess_copy(7, (e_surface)7, v14, 1, 1, a7, a8, v20, 1.0f, nullptr);
		return;
	}
	if (dof_enabled)
		eldorado::c_screen_postprocess_copy(51, (e_surface)7, (e_surface)49, 2, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
	float exposure = c_exposure::set_exposure(&tls_getd().scripted_exposure_globals->exposure, camera_fx_values->exposure);
	float exposure_power = fmaxf(powf(2.0f, (exposure + c_camera_fx_values::g_exposure_stops + camera_fx_values->exposure_boost) * camera_fx_values->exposure_scale), 1.0f);
	float final_exposure = c_screen_postprocess::x_settings.field_2C / 1.4938016f * exposure_power;
	real_vector4d bloom_intensity_vector;
	bloom_intensity_vector[0] = 0.299f;
	bloom_intensity_vector[1] = 0.587f;
	bloom_intensity_vector[2] = 0.114f;
	bloom_intensity_vector[3] = 0.0f;
	eldorado::c_rasterizer_set_pixel_shader_constant(3, 1, &bloom_intensity_vector);
	eldorado::c_screen_postprocess_apply_binary_op_ex((e_rasterizer_default_shader)48, (e_surface)8, (e_surface)0, (e_surface)34, 2, (e_sampler_address_mode)1, camera_fx_values->highlight_bloom * final_exposure, camera_fx_values->inherent_bloom, 1.0f, 1.0f);
	eldorado::c_screen_postprocess_apply_binary_op_ex((e_rasterizer_default_shader)67, (e_surface)34, (e_surface)7, (e_surface)45, 2, (e_sampler_address_mode)1, camera_fx_values->highlight_bloom * final_exposure, camera_fx_values->inherent_bloom, 1.0f, 1.0f);
	e_surface bloom_buffer_surface = eldorado::c_screen_postprocess_postprocess_bloom_buffer((e_surface)45, camera_fx_values, 0);
	if (bloom_buffer_surface)
	{
		float s = c_screen_postprocess::x_settings.field_24;
		e_surface dest_surface = eldorado::c_rasterizer_get_display_surface();
		eldorado::c_screen_postprocess_copy(7, bloom_buffer_surface, dest_surface, 1, 1, s, s, s, 1.0f, nullptr);
		return;
	}
	if (dof_enabled)
	{
		float blur_sigma = s_depth_of_field::get_depth_of_field_blur_sigma(s_depth_of_field::get());
		eldorado::c_screen_postprocess_gaussian_blur((e_surface)49, (e_surface)48, blur_sigma * 0.25f, blur_sigma * 0.25f);
	}
	bool render_light_shafts = (camera_fx_values->light_shafts.flags & 2) && g_render_light_shafts_enabled && global_preferenced_get_effects_quality();
	bool anti_aliasing = global_preferences_get_anti_aliasing() && g_render_anti_aliasing_enabled;
	e_surface composite_surface;
	if (render_light_shafts || anti_aliasing)
		composite_surface = (e_surface)9;
	else
		composite_surface = eldorado::c_rasterizer_get_display_surface();
	real_vector4d pixel_space_xform;
	pixel_space_xform[0] = 1.0f;
	pixel_space_xform[1] = 1.0f;
	pixel_space_xform[2] = 0.0f;
	pixel_space_xform[3] = 0.0f;
	eldorado::c_rasterizer_set_vertex_shader_constant(9, 1, &pixel_space_xform);
	s_rasterizer_globals *const rasg = c_rasterizer_globals::get();
	c_rasterizer_texture_ref default_noise_texture_ref(-1);
	c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &default_noise_texture_ref, _default_bitmap_noise);
	eldorado::c_rasterizer_set_sampler_texture(9, default_noise_texture_ref);
	eldorado::c_rasterizer_set_sampler_address_mode(9, 0, 0, 0);
	eldorado::c_rasterizer_set_sampler_filter_mode(9, 1);
	long noise_width;
	long noise_height;
	((bool (__thiscall *)(c_rasterizer_texture_ref *, long, long *, long *))0xA6E950)(&default_noise_texture_ref, 0, &noise_width, &noise_height);
	__int32 cs_width = eldorado::c_rasterizer_get_surface_width(composite_surface);
	__int32 cs_height = eldorado::c_rasterizer_get_surface_height(composite_surface);
	unsigned long *random_seed_address = get_local_random_seed_address();
	unsigned long random_seed = 1664525 * *random_seed_address + 1013904223;
	*random_seed_address = random_seed;
	float noise_random1 = HIWORD(random_seed) / 65535.0f;
	random_seed_address = get_local_random_seed_address();
	random_seed = 1664525 * *random_seed_address + 1013904223;
	*random_seed_address = random_seed;
	float noise_random2 = HIWORD(random_seed) / 65535.0f;
	long frame_index = c_render_globals::get_frame_index();
	real_vector4d noise_space_xform;
	noise_space_xform[0] = (float)cs_width / (float)noise_width;
	noise_space_xform[1] = (float)cs_height / (float)noise_height;
	noise_space_xform[2] = ((frame_index & 2) * 0.5f + noise_random1) * 0.5f;
	noise_space_xform[3] = (((frame_index + 1) & 2) * 0.5f + noise_random2) * 0.5f;
	eldorado::c_rasterizer_set_vertex_shader_constant(10, 1, &noise_space_xform);
	real_vector4d noise_params;
	noise_params[0] = screen_effect_settings->dark_noise + screen_effect_settings->dark_noise;
	noise_params[1] = screen_effect_settings->bright_noise;
	noise_params[2] = 1.0 - screen_effect_settings->dark_noise;
	noise_params[3] = 0.0f;
	eldorado::c_rasterizer_set_pixel_shader_constant(11, 1, &noise_params);
	eldorado::c_rasterizer_set_render_target(0, composite_surface, -1);
	eldorado::copy_accumulation_target(composite_surface, *(e_surface *)0x5115AF8, 1.0f, camera_fx_values->bloom_intensity, camera_fx_values->bling_intensity, 0.5f, dof_enabled, depth_of_field);
	if (render_light_shafts)
	{
		eldorado::c_screen_postprocess_render_lightshafts(&camera_fx_values->light_shafts, projection, camera, (e_surface)9, (e_surface)9);
		if (!anti_aliasing)
		{
			eldorado::c_screen_postprocess_copy(51, (e_surface)9, eldorado::c_rasterizer_get_display_surface(), 1, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
			return;
		}
	}
	if (!anti_aliasing)
		return;
	real_vector4d texcoord_scale;
	texcoord_scale[0] = 1.0f / eldorado::c_rasterizer_get_surface_width(9);
	texcoord_scale[1] = 1.0f / eldorado::c_rasterizer_get_surface_height(9);
	texcoord_scale[2] = 0.0f;
	texcoord_scale[3] = 0.0f;
	eldorado::c_rasterizer_set_vertex_shader_constant(240, 1, &texcoord_scale);
	unsigned long debug = Utils::Singleton<Modules::ModuleDebug>::Instance().VarSmaaDebugMode->ValueInt;
	if (Modules::ModuleSettings::Instance().VarAntialiasing->ValueInt == 2)
	{
		c_screen_postprocess::smaa_render((e_surface)9, eldorado::c_rasterizer_get_display_surface(), debug);
		return;
	}
	eldorado::c_screen_postprocess_copy(93, (e_surface)9, eldorado::c_rasterizer_get_display_surface(), 2, 1, 1.0f, 1.0f, 1.0f, 1.0f, nullptr);
}

void __fastcall c_camera_fx_settings__s_real_exposure_parameter__calculate_new_value_hook(s_camera_fx_exposure_struct *_this, void *_, c_camera_fx_values *camera_fx, __int32 flags, float forced_exposure, float forced_auto_exposure, float min, float max) // 0x10ABFC70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_camera_fx_settings__s_real_exposure_parameter__calculate_new_value_hook@@YIXPAUs_camera_fx_exposure_struct@@PAXPAUc_camera_fx_values@@HMMMM@Z");

	float (__thiscall *const sub_A2A970)(c_camera_fx_values *, float) = (float (__thiscall *)(c_camera_fx_values *, float))0xA2A970;
	float (__thiscall *const sub_A2A850)(c_camera_fx_values *, float) = (float (__thiscall *)(c_camera_fx_values *, float))0xA2A850;
	IDirect3DQuery9 **g_exposure_occlusion_buffers = (IDirect3DQuery9 **)0x524B68C;
	float occluded_exposure = 0.0f;
	unsigned long non_occluded_pixels = 0;
	float exposure = forced_exposure;
	if (flags & 4)
	{
		if (Utils::Singleton<Modules::ModuleSettings>::Instance().VarExposureCpu->ValueInt)
		{
			occluded_exposure = g_exposure_occlusion_pixels_passed * 0.00036621094f - 8.0f;
		}
		else if (camera_fx->occlusion_query_index != -1)
		{
			__int32 retrieve_count = 0;
			if (g_exposure_occlusion_buffers[camera_fx->occlusion_query_index]->GetData(&non_occluded_pixels, 4, 0) == 1)
			{
				while (g_exposure_occlusion_buffers[camera_fx->occlusion_query_index]->GetData(&non_occluded_pixels, 4, 1) == 1)
				{
					retrieve_count++;
					if (retrieve_count >= 3000)
						break;
				}
			}
			if (retrieve_count < 3000)
				occluded_exposure = (float)non_occluded_pixels / driver_forced_msaa_value * 0.00036621094f - 8.0f;
		}
		exposure = camera_fx->brightness + forced_auto_exposure + occluded_exposure;
		camera_fx->field_C = occluded_exposure;
	}
	camera_fx->brightness = camera_fx->exposure;
	exposure = fminf(max, fmaxf(exposure, min));
	tls_data const &tls = tls_getd();
	if (!(tls.scripted_exposure_globals->exposure.flags & 2))
	{
		camera_fx->exposure_samples[camera_fx->exposure_sample_count] = exposure;
		camera_fx->exposure_sample_count++;
		if (camera_fx->exposure_sample_count >= 60)
			camera_fx->exposure_sample_count = 0;
	}
	if ((tls.scripted_exposure_globals->exposure.flags & 2) || !(tls.scripted_exposure_globals->exposure.flags & 1))
	{
		if ((camera_fx->exposure >= exposure || camera_fx->exposure >= sub_A2A970(camera_fx, _this->autoexposure_delay)) && (exposure >= camera_fx->exposure || sub_A2A850(camera_fx, _this->autoexposure_delay) >= camera_fx->exposure))
		{
			camera_fx->field_14 = 0.0f;
		}
		else
		{
			float blend_speed = fminf(_this->blend_speed, fabsf(camera_fx->exposure - exposure) * 0.05f);
			if (!(unsigned char)(c_screen_postprocess::x_settings.field_30 & 0xFF) && !(tls.scripted_exposure_globals->exposure.flags & 2))
				camera_fx->exposure = (1.0 - blend_speed) * camera_fx->exposure + blend_speed * exposure;
		}
	}
	else
	{
		float const old_exposure_weight = 0.1f;
		camera_fx->exposure = camera_fx->exposure * old_exposure_weight + exposure * (1.0f - old_exposure_weight);
	}
}

long c_screen_postprocess__downsample_generate_call_hook(e_surface source_surface, c_camera_fx_values *camera_fx, e_surface a3, e_surface a4) // 0x10AC0230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_screen_postprocess__downsample_generate_call_hook@@YAJW4e_surface@@PAUc_camera_fx_values@@00@Z");

	__int32 (*const c_screen_postprocess__downsample_generate)(e_surface, c_camera_fx_values *, e_surface, e_surface) = reinterpret_cast<__int32 (*)(e_surface, c_camera_fx_values *, e_surface, e_surface)>(0xA60B00);
	IDirect3DQuery9 **g_exposure_occlusion_buffers = reinterpret_cast<IDirect3DQuery9 **>(0x524B68C);
	__int32 result = c_screen_postprocess__downsample_generate(source_surface, camera_fx, a3, a4);
	if (Modules::ModuleSettings::Instance().VarExposureCpu->ValueInt == 1)
	{
		g_exposure_occlusion_pixels_passed = 0;
		IDirect3DDevice9Ex *const device = c_rasterizer::get_device();
		IDirect3DSurface9 *exposure_sfc = ((c_surface_group *)0x510D8D0)[camera_fx->occlusion_type + _surface_aux_exposure_0].surfaces[0].m_surface;
		device->GetRenderTargetData(exposure_sfc, g_exposure_dup_surface);
		_D3DLOCKED_RECT exposure_rect;
		if (SUCCEEDED(g_exposure_dup_surface->LockRect(&exposure_rect, nullptr, D3DLOCK_READONLY)))
		{
			float sample = *reinterpret_cast<float *>(exposure_rect.pBits);
			float index = (-sample + 8.0f) / 24.0f * 256.0f * 256.0f;
			g_exposure_dup_surface->UnlockRect();
			for (float y = 0; y < 256.0f; y++)
			{
				for (float x = 0; x < 256.0f; x++)
				{
					if (index - (y * 256.0f + x) >= 0.0f)
						g_exposure_occlusion_pixels_passed++;
				}
			}
		}
	}
	return result;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { long driver_forced_msaa_value = 1; }
namespace hades_file_local { long g_exposure_occlusion_pixels_passed; }
namespace hades_file_local { IDirect3DSurface9 *g_exposure_dup_surface; }
namespace hades_file_local { bool reflections_enabled; }
float const &c_camera_fx_values::g_exposure_stops = *reinterpret_cast<float const *>(0x50E8920);
int &c_rasterizer_globals::g_motion_blur_min_width = *reinterpret_cast<int *>(0x1914BAC);
int &c_rasterizer_globals::g_motion_blur_max_width = *reinterpret_cast<int *>(0x1914BB0);
int &c_rasterizer_globals::g_motion_blur_min_taps = *reinterpret_cast<int *>(0x1914BB4);
int &c_rasterizer_globals::g_motion_blur_max_taps = *reinterpret_cast<int *>(0x1914BB8);
c_screen_postprocess::s_settings const &c_screen_postprocess::x_settings = *reinterpret_cast<c_screen_postprocess::s_settings const *>(0x1917D18);
