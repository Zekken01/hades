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

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern e_surface _sub_10F10B40(float, float);
e_surface c_screen_postprocess::blur_display(float blur_x, float blur_y) // 0x10F10B40
{
	mangled_x86(MANGLED_TODO, "?blur_display@c_screen_postprocess@@SA?AW4e_surface@@MM@Z");
	// float blur_y;
	{
		// e_surface blur_surface;
		// void *player_view;
	}
	// function call : e_surface (*const)(long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(long, __int32, float, unsigned char)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(e_surface, e_surface, float, float)
	todo("implement");
	e_surface __result = _sub_10F10B40(blur_x, blur_y);
	return __result;
}

extern e_surface _sub_10F10D20(float, float, e_surface);
e_surface c_screen_postprocess::blur_display(float blur_x, float blur_y, e_surface blur_surface) // 0x10F10D20
{
	mangled_x86(MANGLED_TODO, "?blur_display@c_screen_postprocess@@SA?AW4e_surface@@MMW42@@Z");
	// e_surface blur_surface;
	// function call : e_surface (*const)(long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(long, __int32, float, unsigned char)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(e_surface, e_surface, float, float)
	todo("implement");
	e_surface __result = _sub_10F10D20(blur_x, blur_y, blur_surface);
	return __result;
}

_extern void _sub_10F113D0(float, float);
void c_screen_postprocess::render_screen_effect_blur(float x_blur, float y_blur) // 0x10F113D0
{
	mangled_x86(MANGLED_TODO, "?render_screen_effect_blur@c_screen_postprocess@@SAXMM@Z");
	// float y_blur;
	{
		// float blur_x;
		// e_surface blurred_surface;
		// float blur_y;
		// float blur_blend;
		// __int32 blur_blendi;
	}
	// function call : void (*const)(bool)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(long, e_surface, e_surface, long, long, float, float, float, float, real_rectangle2d *)
	// function call : void (*const)(long)
	todo("implement");
	_sub_10F113D0(x_blur, y_blur);
}

_extern bool _sub_10F116D0(long, long);
bool c_screen_postprocess::smaa_initialize(long resolution_x, long resolution_y) // 0x10F116D0
{
	mangled_x86(MANGLED_TODO, "?smaa_initialize@c_screen_postprocess@@SA_NJJ@Z");
	// long resolution_y;
	todo("implement");
	bool __result = _sub_10F116D0(resolution_x, resolution_y);
	return __result;
}

_extern void _sub_10F12980(IDirect3DDevice9 *, e_surface, long);
void c_screen_postprocess::smaa_render_velocity(IDirect3DDevice9 *device, e_surface dst_surface, long debug_mode) // 0x10F12980
{
	mangled_x86(MANGLED_TODO, "?smaa_render_velocity@c_screen_postprocess@@SAXPAUIDirect3DDevice9@@W4e_surface@@J@Z");
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
	todo("implement");
	_sub_10F12980(device, dst_surface, debug_mode);
}

_extern bool _sub_10F117F0(e_surface, e_surface, long);
bool c_screen_postprocess::smaa_render(e_surface src_surface, e_surface dst_surface, long debug_mode) // 0x10F117F0
{
	mangled_x86(MANGLED_TODO, "?smaa_render@c_screen_postprocess@@SA_NW4e_surface@@0J@Z");
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
	{
		// real_vector4d depth_constants;
		// void (*const rasterizer_get_z_planes)(float *, float *);
		// float z_near;
		// float z_far;
		// bool result;
		{
			// real_vector4d depth_threshold;
			// real_vector4d pixel_size;
			{
				// c_rasterizer_texture_ref area_tex;
				// s_rasterizer_globals *rasg;
				// c_rasterizer_texture_ref search_tex;
			}
		}
		{
			// IDirect3DSurface9 *dpth_fp32;
			// IDirect3DSurface9 *dst;
		}
	}
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
	todo("implement");
	bool __result = _sub_10F117F0(src_surface, dst_surface, debug_mode);
	return __result;
}

/* ---------- private code */
