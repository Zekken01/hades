/* ---------- headers */

#include "Blam/render/views/render_player_view.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/main/main_render.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_game_states.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizer_vertex_types.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/render_globals.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>
#include <directxmath.h>
#include <DirectXMathConvert.inl>
#include <DirectXMathMatrix.inl>
#include <DirectXMathMisc.inl>
#include <DirectXMathVector.inl>

/* ---------- forward declarations */

struct c_player_render_camera_iterator;
struct c_player_view;
struct c_render_surface;
struct c_surface_group;
struct real_matrix4x3;
struct real_vector3d;
struct real_vector4d;
struct s_rasterizer_globals;
struct s_screen_vertex;
struct short_rectangle2d;

namespace DirectX {}
using namespace ::DirectX;
namespace DirectX
{
	namespace Internal {}
	using namespace DirectX::Internal;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void draw_fullscreen_displacement(short_rectangle2d *bounds, DirectX::XMMATRIX *view_projection, DirectX::XMMATRIX *previous_view_projection, DirectX::XMMATRIX *view_to_world, DirectX::XMMATRIX *screen_to_world, bool render_motion_blur);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F174C0(short_rectangle2d *, DirectX::XMMATRIX *, DirectX::XMMATRIX *, DirectX::XMMATRIX *, DirectX::XMMATRIX *, bool);
void draw_fullscreen_displacement(short_rectangle2d *bounds, DirectX::XMMATRIX *view_projection, DirectX::XMMATRIX *previous_view_projection, DirectX::XMMATRIX *view_to_world, DirectX::XMMATRIX *screen_to_world, bool render_motion_blur) // 0x10F174C0
{
	mangled_x86(MANGLED_TODO, "?draw_fullscreen_displacement@@YAXPAUshort_rectangle2d@@PAUXMMATRIX@DirectX@@111_N@Z");
	// static ...; // 0x10F17E30
	// static ...; // 0x10F17E28
	// short_rectangle2d *bounds;
	// DirectX::XMMATRIX *view_projection;
	// DirectX::XMMATRIX *previous_view_projection;
	// DirectX::XMMATRIX *view_to_world;
	// DirectX::XMMATRIX *screen_to_world;
	// bool render_motion_blur;
	// void (*const screenshot_get_scales)(float *, float *);
	// long *g_game_resolution;
	// void (*const set_motion_blur_parameters)();
	// bool distortion_surface_valid;
	// long *g_client_resolution;
	{
		// short_rectangle2d viewport_bounds;
		// real_vector4d zbuffer_xform;
		// float texcoord_x_scale;
		// s_screen_vertex vertices[4];
		// __int32 displacement_shader_index;
		// s_rasterizer_globals *const rasg;
		// float texcoord_y_scale;
		// real_vector4d screen_constants;
		// void *const vtsh;
		// real_vector4d window_bounds;
		// void *const pixl;
	}
	// function call : bool (*const)(e_surface)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)()
	// function call : void (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)(bool)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(void *, long, long, long)
	// function call : bool (*const)(void *, long)
	// function call : void (*const)(short_rectangle2d *, float, float)
	// function call : void (*const)(float *, float *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long)
	// function call : bool (*const)(IDirect3DIndexBuffer9 *)
	// function call : void (*const)(long, long, void *, long)
	// function call : void (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)()
	// function call : void (*const)()
	todo("implement");
	_sub_10F174C0(bounds, view_projection, previous_view_projection, view_to_world, screen_to_world, render_motion_blur);
}

_extern void _sub_10F16B80(c_player_view *, real_vector3d *, bool);
void __fastcall c_player_view::apply_distortions_new(c_player_view *_this, real_vector3d *motion_suck_dir, bool force_motion_blur) // 0x10F16B80
{
	mangled_x86(MANGLED_TODO, "?apply_distortions_new@c_player_view@@SIXPAU1@PAUreal_vector3d@@_N@Z");
	// static ...; // 0x10F172BF
	// static ...; // 0x10F172B1
	// static ...; // 0x10F17299
	// static ...; // 0x10F17290
	// static ...; // 0x10F1727D
	// static ...; // 0x10F17265
	// static ...; // 0x10F1724C
	// static ...; // 0x10F1723C
	// static ...; // 0x10F171C4
	// static ...; // 0x10F171BC
	// c_player_view *_this;
	// real_vector3d *motion_suck_dir;
	// bool force_motion_blur;
	// bool (*const preferences_get_motion_blur)();
	// long (*const preferences_get_effects_quality)();
	// bool (*const sub_610190)();
	// c_player_render_camera_iterator render_camera_it;
	// void (*const unpack_distortion_matrices)(real_matrix4x3 *, DirectX::XMMATRIX *, DirectX::XMMATRIX *, DirectX::XMMATRIX *);
	// bool render_motion_blur;
	// long window_count;
	{
		// float up_vector_velocity;
		// float forward_vector_velocity;
		// float distortion_magnitude;
		// real_vector3d velocity_vector;
	}
	{
		// DirectX::XMMATRIX wtv;
		// DirectX::XMMATRIX current_view_projection;
		// IDirect3DDevice9Ex *const device;
		// DirectX::XMMATRIX motion_suck_translation;
		// DirectX::XMMATRIX prev_view_to_world;
		// DirectX::XMMATRIX prev_wtv;
		// DirectX::XMMATRIX previous_view_projection;
		// DirectX::XMMATRIX screen_to_world;
		// DirectX::XMMATRIX view_to_world;
	}
	// function call : long (*const)(c_player_render_camera_iterator *)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : void (*const)(real_matrix4x3 *, DirectX::XMMATRIX *, DirectX::XMMATRIX *, DirectX::XMMATRIX *)
	// function call : void (*const)(real_matrix4x3 *, DirectX::XMMATRIX *, DirectX::XMMATRIX *, DirectX::XMMATRIX *)
	// function call : c_render_surface *(*const)(c_surface_group *, e_surface)
	// function call : c_render_surface *(*const)(c_surface_group *, e_surface)
	// function call : HRESULT (IDirect3DSurface9 *, tagRECT const *, IDirect3DSurface9 *, tagRECT const *, _D3DTEXTUREFILTERTYPE)
	// function call : e_surface (*const)(e_surface)
	// function call : void (*const)()
	// function call : void (*const)(bool)
	todo("implement");
	_sub_10F16B80(_this, motion_suck_dir, force_motion_blur);
}

/* ---------- private code */
