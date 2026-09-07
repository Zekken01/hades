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
void c_camera_fx_settings__s_real_exposure_parameter__calculate_new_value_hook(s_camera_fx_exposure_struct *_this, void *_, c_camera_fx_values *camera_fx, __int32 flags, float forced_exposure, float forced_auto_exposure, float min, float max);
long c_screen_postprocess__downsample_generate_call_hook(e_surface source_surface, c_camera_fx_values *camera_fx, e_surface a3, e_surface a4);

/* ---------- globals */

s_motion_blur_parameters *c_rasterizer_globals::g_motion_blur_parameters; // 0x11354A3C
bool (*s_depth_of_field::get_enabled)(); // 0x11354A50
float (*s_depth_of_field::get_depth_of_field_blur_sigma)(s_depth_of_field *); // 0x11354A54

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

_extern void _sub_10AC2F20();
void render_postprocess_patches_tick() // 0x10AC2F20
{
	mangled_x86(MANGLED_TODO, "?render_postprocess_patches_tick@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10AC2F20();
}

_extern long _sub_10AC1880();
long detect_driver_forced_msaa() // 0x10AC1880
{
	mangled_x86(MANGLED_TODO, "?detect_driver_forced_msaa@@YAJXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AC1E5A
	// static ...; // 0x10AC1E4E
	// static ...; // 0x10AC1E40
	// static ...; // 0x10AC1E33
	// static ...; // 0x10AC1E28
	// static ...; // 0x10AC1E14
	// static ...; // 0x10AC1DCC
	// static ...; // 0x10AC1DC4
	// long msaa_level;
	// IDirect3DDevice9Ex *const device;
	// IDirect3DVertexBuffer9 *test_buffer;
	// detect_driver_forced_msaa::__l2::s_test_vertex test_verts[4];
	{
		// void *test_vertices;
		{
			// IDirect3DSurface9 *test_surface;
			// long test_rt_res;
			// _D3DFORMAT test_format;
			{
				// IDirect3DQuery9 *test_query;
				{
					// __int32 non_occluded_pixels;
					// unsigned long start_time;
					// long cycles;
				}
			}
		}
	}
	// function call : HRESULT ()
	// function call : HRESULT (unsigned __int32, unsigned long, unsigned long, _D3DPOOL, IDirect3DVertexBuffer9 **, void **)
	// function call : HRESULT (unsigned __int32, unsigned __int32, void **, unsigned long)
	// function call : HRESULT ()
	// function call : HRESULT (unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DMULTISAMPLE_TYPE, unsigned long, __int32, IDirect3DSurface9 **, void **)
	// function call : HRESULT (_D3DQUERYTYPE, IDirect3DQuery9 **)
	// function call : HRESULT (unsigned long, IDirect3DSurface9 *)
	// function call : HRESULT (unsigned __int32, IDirect3DVertexBuffer9 *, unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned long)
	// function call : HRESULT (_D3DRENDERSTATETYPE, unsigned long)
	// function call : HRESULT (_D3DRENDERSTATETYPE, unsigned long)
	// function call : HRESULT (unsigned long)
	// function call : HRESULT (_D3DPRIMITIVETYPE, unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned long)
	// function call : HRESULT (void *, unsigned long, unsigned long)
	// function call : HRESULT (void *, unsigned long, unsigned long)
	// function call : HRESULT (unsigned long, IDirect3DSurface9 *)
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : HRESULT ()
	todo("implement");
	long __result = _sub_10AC1880();
	return __result;
}

_extern void _sub_10AC2E10();
void render_postprocess_patches_apply_after_init() // 0x10AC2E10
{
	mangled_x86(MANGLED_TODO, "?render_postprocess_patches_apply_after_init@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AC2ED4
	// static ...; // 0x10AC2EC8
	// static ...; // 0x10AC2EC0
	// IDirect3DDevice9Ex *const device;
	// IDirect3DTexture9 *dup_exposure_tex;
	// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
	// function call : HRESULT (unsigned __int32, IDirect3DSurface9 **)
	todo("implement");
	_sub_10AC2E10();
}

_extern void _sub_10AC21B0();
void render_postprocess_patches_apply() // 0x10AC21B0
{
	mangled_x86(MANGLED_TODO, "?render_postprocess_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	// long const shadow_texture_resolution;
	// s_surface_group_description *shadow_surface;
	// s_surface_group_description *shadow_color_surface;
	// s_surface_group_description *cortana_effect_surface;
	todo("implement");
	_sub_10AC21B0();
}

/* ---------- private code */

_extern void _sub_10AC2120(long, unsigned long);
void render_objects_shadow_generate_hook(long pass, unsigned long flags) // 0x10AC2120
{
	// `anonymous-namespace'::render_objects_shadow_generate_hook
	// unsigned long flags;
	// function call : bool (*const)(IDirect3DIndexBuffer9 *)
	// function call : void (*)(long, long)
	todo("implement");
	_sub_10AC2120(pass, flags);
}

extern void _sub_10AC21A0();
__declspec(naked) void render_post_process_reflections_enabled_hook() // 0x10AC21A0
{
	// `anonymous-namespace'::render_post_process_reflections_enabled_hook
	// procedure flags: nofpo
	todo("implement");
	_sub_10AC21A0();
}

_extern void _sub_10AC1FE0(long, long);
void force_sampler_filter_mode_hook(long sampler, long e_sampler_filter_mode) // 0x10AC1FE0
{
	// `anonymous-namespace'::force_sampler_filter_mode_hook
	// long e_sampler_filter_mode;
	// IDirect3DDevice9 *device;
	// constexpr void (*const `force_sampler_filter_mode_hook'::`2'::c_rasterizer_samplers__set_filter)(void *, long, long); // constant == 10630912
	// long anisotropic_filtering_override;
	// long *g_sampler_filter_modes;
	// function call : void (*const)(void *, long, long)
	// function call : HRESULT (unsigned long, _D3DSAMPLERSTATETYPE, unsigned long)
	// function call : void (*const)(void *, long, long)
	todo("implement");
	_sub_10AC1FE0(sampler, e_sampler_filter_mode);
}

_extern void _sub_10AC3780(long, long, real_vector4d const *);
void set_postprocess_gamma_hook(long index, long count, real_vector4d const *constant) // 0x10AC3780
{
	// `anonymous-namespace'::set_postprocess_gamma_hook
	// static ...; // 0x10AC385C
	// long index;
	// long count;
	// real_vector4d const *constant;
	// real_vector4d gamma_power_constant;
	// long gamma_power_register;
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	todo("implement");
	_sub_10AC3780(index, count, constant);
}

_extern void _sub_10AC2F90();
void set_motion_blur_parameters_hook() // 0x10AC2F90
{
	// `anonymous-namespace'::set_motion_blur_parameters_hook
	// procedure flags: nofpo
	// static ...; // 0x10AC35E3
	// static ...; // 0x10AC35DC
	// static ...; // 0x10AC35CD
	// static ...; // 0x10AC35B3
	// static ...; // 0x10AC35A6
	// static ...; // 0x10AC359A
	// static ...; // 0x10AC3587
	// static ...; // 0x10AC3576
	// static ...; // 0x10AC3568
	// static ...; // 0x10AC34FC
	// static ...; // 0x10AC34F4
	// real_vector4d misc_values;
	// __int32 const do_distortion;
	// real_vector4d blur_max_and_scale;
	// void (*const screenshot_get_scales)(float *, float *);
	// real_vector3d unknown_effect;
	// real_vector4d crosshair_center;
	// void (*const sub_684700)(__int32, real_vector3d *);
	// tls_data *tls;
	// __int32 dis_num_taps[4];
	// void (*const chud_get_crosshair_screen_position)(__int32, real_point2d *);
	// float timing_unknown;
	// float width_scale;
	// __int32 num_taps;
	// __int32 width;
	// c_player_view *current_player_view;
	// real_point2d crosshair_screen_position;
	// long (*const global_preferences_get_effects_quality)();
	// __int32 height;
	{
		// float strength_max;
		// float motion_blur_strength;
		// s_rasterizer_globals const *rasg;
		// float strength_min;
	}
	// function call : long (*const)()
	// function call : long (*const)()
	// function call : void (*const)(__int32, real_vector3d *)
	// function call : void (*const)(__int32, real_point2d *)
	// function call : void (*const)(long, long, __int32 const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : bool (*const)()
	// function call : void (*const)(long, long, __int32 const *)
	todo("implement");
	_sub_10AC2F90();
}

_extern void _sub_10AC04E0(c_camera_fx_values *, s_render_projection *, s_render_camera *, s_screen_effect_settings *, long, s_observer_depth_of_field *, long);
void c_screen_postprocess__postprocess_player_view_hook(c_camera_fx_values *camera_fx_values, s_render_projection *projection, s_render_camera *camera, s_screen_effect_settings *screen_effect_settings, long splitscreen_res, s_observer_depth_of_field *depth_of_field, long output_user_index) // 0x10AC04E0
{
	// `anonymous-namespace'::c_screen_postprocess__postprocess_player_view_hook
	// static ...; // 0x10AC1404
	// static ...; // 0x10AC13F7
	// static ...; // 0x10AC13E8
	// static ...; // 0x10AC137C
	// static ...; // 0x10AC1374
	// c_camera_fx_values *camera_fx_values;
	// s_render_projection *projection;
	// s_render_camera *camera;
	// s_screen_effect_settings *screen_effect_settings;
	// long splitscreen_res;
	// s_observer_depth_of_field *depth_of_field;
	// long output_user_index;
	// float contrast_enhance;
	// unsigned long *random_seed_address;
	// real_vector4d pixel_space_xform;
	// long noise_height;
	// float noise_random2;
	// bool anti_aliasing;
	// c_rasterizer_texture_ref default_noise_texture_ref;
	// unsigned long debug;
	// float contrast;
	// float final_exposure;
	// unsigned long random_seed;
	// bool const g_render_light_shafts_enabled;
	// bool dof_enabled;
	// __int32 cs_height;
	// char (*const global_preferences_get_anti_aliasing)();
	// s_rasterizer_globals *const rasg;
	// real_vector4d bloom_intensity_vector;
	// float noise_random1;
	// __int32 cs_width;
	// real_vector4d texcoord_scale;
	// long frame_index;
	// bool render_light_shafts;
	// real_vector4d noise_params;
	// real_vector4d p_postprocess_contrast;
	// float exposure_power;
	// e_surface bloom_buffer_surface;
	// long (*const global_preferenced_get_effects_quality)();
	// float exposure;
	// e_surface composite_surface;
	// long noise_width;
	// bool const g_render_anti_aliasing_enabled;
	// real_vector4d noise_space_xform;
	{
		// e_surface v14;
		// float a7;
		// float a8;
		// float v20;
	}
	{
		// float s;
		// e_surface dest_surface;
	}
	{
		// float blur_sigma;
	}
	// function call : void (*const)(s_hue_saturation_control *, float, float, float, real_rgb_color const *, real_rgb_color const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(bool)
	// function call : bool (*)()
	// function call : e_surface (*const)()
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : float (*const)(c_exposure *, float)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(e_rasterizer_default_shader, e_surface, e_surface, e_surface, long, e_sampler_address_mode, float, float, float, float)
	// function call : void (*const)(e_rasterizer_default_shader, e_surface, e_surface, e_surface, long, e_sampler_address_mode, float, float, float, float)
	// function call : e_surface (*const)(e_surface, c_camera_fx_values *, long)
	// function call : e_surface (*const)()
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : s_depth_of_field *(*)()
	// function call : float (*)(s_depth_of_field *)
	// function call : void (*const)(e_surface, e_surface, float, float)
	// function call : long (*const)()
	// function call : char (*const)()
	// function call : e_surface (*const)()
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : bool (*const)(c_rasterizer_texture_ref *, long, long *, long *)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : unsigned long *(*)()
	// function call : unsigned long *(*)()
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(e_surface, e_surface, float, float, float, float, bool, s_observer_depth_of_field *)
	// function call : void (*const)(s_camera_fx_lightshafts_struct *, s_render_projection *, s_render_camera *, e_surface, e_surface)
	// function call : e_surface (*const)()
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : e_surface (*const)()
	// function call : e_surface (*const)()
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	todo("implement");
	_sub_10AC04E0(camera_fx_values, projection, camera, screen_effect_settings, splitscreen_res, depth_of_field, output_user_index);
}

_extern void _sub_10ABFC70(s_camera_fx_exposure_struct *, void *, c_camera_fx_values *, __int32, float, float, float, float);
void c_camera_fx_settings__s_real_exposure_parameter__calculate_new_value_hook(s_camera_fx_exposure_struct *_this, void *_, c_camera_fx_values *camera_fx, __int32 flags, float forced_exposure, float forced_auto_exposure, float min, float max) // 0x10ABFC70
{
	// `anonymous-namespace'::c_camera_fx_settings__s_real_exposure_parameter__calculate_new_value_hook
	// float forced_exposure;
	// float forced_auto_exposure;
	// float min;
	// float max;
	// float (*const sub_A2A970)(c_camera_fx_values *, float);
	// unsigned long non_occluded_pixels;
	// tls_data const &tls;
	// float (*const sub_A2A850)(c_camera_fx_values *, float);
	// IDirect3DQuery9 **g_exposure_occlusion_buffers;
	// float occluded_exposure;
	// float exposure;
	{
		// __int32 retrieve_count;
	}
	{
		// float blend_speed;
	}
	{
		// float const old_exposure_weight;
	}
	// function call : HRESULT (void *, unsigned long, unsigned long)
	// function call : HRESULT (void *, unsigned long, unsigned long)
	// function call : float (*const)(c_camera_fx_values *, float)
	// function call : float (*const)(c_camera_fx_values *, float)
	todo("implement");
	_sub_10ABFC70(_this, _, camera_fx, flags, forced_exposure, forced_auto_exposure, min, max);
}

_extern long _sub_10AC0230(e_surface, c_camera_fx_values *, e_surface, e_surface);
long c_screen_postprocess__downsample_generate_call_hook(e_surface source_surface, c_camera_fx_values *camera_fx, e_surface a3, e_surface a4) // 0x10AC0230
{
	// `anonymous-namespace'::c_screen_postprocess__downsample_generate_call_hook
	// e_surface source_surface;
	// c_camera_fx_values *camera_fx;
	// e_surface a3;
	// e_surface a4;
	// __int32 (*const c_screen_postprocess__downsample_generate)(e_surface, c_camera_fx_values *, e_surface, e_surface);
	// __int32 result;
	// IDirect3DQuery9 **g_exposure_occlusion_buffers;
	{
		// _D3DLOCKED_RECT exposure_rect;
		// IDirect3DDevice9Ex *const device;
		// IDirect3DSurface9 *exposure_sfc;
		{
			// float sample;
			// float index;
			{
				// float y;
				{
					// float x;
				}
			}
		}
	}
	// function call : __int32 (*const)(e_surface, c_camera_fx_values *, e_surface, e_surface)
	// function call : HRESULT (IDirect3DSurface9 *, IDirect3DSurface9 *)
	// function call : HRESULT (_D3DLOCKED_RECT *, tagRECT const *, unsigned long)
	// function call : HRESULT ()
	todo("implement");
	long __result = _sub_10AC0230(source_surface, camera_fx, a3, a4);
	return __result;
}
