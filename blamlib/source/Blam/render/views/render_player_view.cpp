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
extern float dot_product3d(real_vector3d const *v1, real_vector3d const *v2);  // hades: added for 0x10F16B80
extern real_vector3d *vector_from_points3d(real_point3d const *p1, real_point3d const *p2, real_vector3d *result);  // hades: added for 0x10F16B80
extern float magnitude3d(real_vector3d const *v);  // hades: added for 0x10F16B80
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10F174C0

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void draw_fullscreen_displacement(short_rectangle2d *bounds, DirectX::XMMATRIX *view_projection, DirectX::XMMATRIX *previous_view_projection, DirectX::XMMATRIX *view_to_world, DirectX::XMMATRIX *screen_to_world, bool render_motion_blur) // 0x10F174C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?draw_fullscreen_displacement@@YAXPAUshort_rectangle2d@@PAUXMMATRIX@DirectX@@111_N@Z");
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

	long *g_client_resolution = (long *)0x19106E4;
	long *g_game_resolution = (long *)0x19106C0;
	void (*const set_motion_blur_parameters)() = (void (*)())0xA47060;
	void (*const screenshot_get_scales)(float *, float *) = (void (*)(float *, float *))0x6102C0;
	bool distortion_surface_valid = ((bool (*const)(e_surface))0xA490E0)((e_surface)50);
	if (distortion_surface_valid || render_motion_blur)
	{
		if (distortion_surface_valid)
			((void (*const)(long, e_surface))0xA48F20)(0, (e_surface)50);
		else
			((void (*const)(long, e_surface))0xA48D40)(0, (e_surface)50);
		((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(0, _address_mode_mirror, _address_mode_mirror, _address_mode_mirror);
		((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(0, _filter_point);
		((void (*const)(long, e_surface))0xA48F20)(1, (e_surface)13);
		((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(1, _address_mode_mirror, _address_mode_mirror, _address_mode_mirror);
		((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(1, _filter_bilinear);
		if (render_motion_blur)
		{
			((void (*const)(long, e_surface))0xA48F20)(3, (e_surface)23);
			((void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>))0xA23570)(3, _address_mode_mirror, _address_mode_mirror, _address_mode_mirror);
			((void (*const)(long, c_enum<enum e_sampler_filter_mode,long>))0xA23660)(3, _filter_point);
			set_motion_blur_parameters();
		}
		((void (*const)(long))0xA22D10)(0);
		((long (*const)(long))0xA247E0)(2);
		((void (*const)(bool))0xA25400)(true);
		__int32 displacement_shader_index = render_motion_blur ? 81 : 37;
		s_rasterizer_globals *const rasg = c_rasterizer_globals::get();
		void *const vtsh = tag_get('vtsh', ((s_tag_reference *)rasg->explicit_shaders[displacement_shader_index].vertex_shader)->index);
		void *const pixl = tag_get('pixl', ((s_tag_reference *)rasg->explicit_shaders[displacement_shader_index].pixel_shader)->index);
		((bool (*const)(void *, long, long, long))0xA246E0)(vtsh, 7, 0, 0);
		((bool (*const)(void *, long))0xA23460)(pixl, 0);
		short_rectangle2d viewport_bounds;
		viewport_bounds.y0 = 0;
		viewport_bounds.x0 = 0;
		viewport_bounds.y1 = (short)g_game_resolution[1];
		viewport_bounds.x1 = (short)g_game_resolution[0];
		((void (*const)(short_rectangle2d *, float, float))0xA49010)(&viewport_bounds, 0.0f, 1.0f);
		real_vector4d screen_constants;
		screen_constants.i = 1.0f / g_game_resolution[0];
		screen_constants.j = 1.0f / g_game_resolution[1];
		screen_constants.k = 0.0f;
		screen_constants.w = 0.0f;
		screenshot_get_scales(&screen_constants.k, &screen_constants.w);
		((void (*const)(long, long, real_vector4d const *))0xA66270)(203, 1, &screen_constants);
		real_vector4d window_bounds;
		window_bounds.i = (bounds->x0 + 0.5f) / g_game_resolution[0];
		window_bounds.j = (bounds->y0 + 0.5f) / g_game_resolution[1];
		window_bounds.k = (bounds->x1 - 0.5f) / g_game_resolution[0];
		window_bounds.w = (bounds->y1 - 0.5f) / g_game_resolution[1];
		((void (*const)(long, long, real_vector4d const *))0xA66270)(204, 1, &window_bounds);
		real_vector4d zbuffer_xform;
		zbuffer_xform.i = view_to_world->r[3].m128_f32[2];
		zbuffer_xform.j = -view_to_world->r[2].m128_f32[2];
		zbuffer_xform.k = 0.0f;
		zbuffer_xform.w = 0.0f;
		((void (*const)(long, long, real_vector4d const *))0xA66270)(175, 1, &zbuffer_xform);
		if (render_motion_blur)
		{
			((void (*const)(long, long, real_vector4d const *))0xA66270)(160, 4, (real_vector4d const *)view_projection);
			((void (*const)(long, long, real_vector4d const *))0xA66270)(164, 4, (real_vector4d const *)previous_view_projection);
			((void (*const)(long, long, real_vector4d const *))0xA66270)(168, 4, (real_vector4d const *)screen_to_world);
		}
		float texcoord_x_scale = (float)g_client_resolution[0] / g_game_resolution[0];
		float texcoord_y_scale = (float)g_client_resolution[1] / g_game_resolution[1];
		s_screen_vertex vertices[4] = {};
		vertices[0].position.x = -1.0f;
		vertices[0].position.y = 1.0f;
		vertices[0].texcoord.i = 0.0f;
		vertices[0].texcoord.j = 0.0f;
		vertices[0].color = 0xFFFFFFFF;
		vertices[1].position.x = 1.0f;
		vertices[1].position.y = 1.0f;
		vertices[1].texcoord.i = 1.0f / texcoord_x_scale;
		vertices[1].texcoord.j = 0.0f;
		vertices[1].color = 0xFFFFFFFF;
		vertices[2].position.x = -1.0f;
		vertices[2].position.y = -1.0f;
		vertices[2].texcoord.i = 0.0f;
		vertices[2].texcoord.j = 1.0f / texcoord_y_scale;
		vertices[2].color = 0xFFFFFFFF;
		vertices[3].position.x = 1.0f;
		vertices[3].position.y = -1.0f;
		vertices[3].texcoord.i = 1.0f / texcoord_x_scale;
		vertices[3].texcoord.j = 1.0f / texcoord_y_scale;
		vertices[3].color = 0xFFFFFFFF;
		((void (*const)(long))0xA232D0)(1);
		((bool (*const)(IDirect3DIndexBuffer9 *))0xA233C0)(nullptr);
		((void (*const)(long, long, void *, long))0xA28330)(5, 2, vertices, sizeof(s_screen_vertex));
		((void (*const)(long))0xA232D0)(2);
		((long (*const)(long))0xA247E0)(1);
		((void (*const)())0xA202F0)();
		((void (*const)())0xA202E0)();
	}
}

void __fastcall c_player_view::apply_distortions_new(c_player_view *_this, real_vector3d *motion_suck_dir, bool force_motion_blur) // 0x10F16B80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_distortions_new@c_player_view@@SIXPAU1@PAUreal_vector3d@@_N@Z");
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
		// float up_vector_velocity;
		// float forward_vector_velocity;
		// float distortion_magnitude;
		// real_vector3d velocity_vector;
		// DirectX::XMMATRIX wtv;
		// DirectX::XMMATRIX current_view_projection;
		// IDirect3DDevice9Ex *const device;
		// DirectX::XMMATRIX motion_suck_translation;
		// DirectX::XMMATRIX prev_view_to_world;
		// DirectX::XMMATRIX prev_wtv;
		// DirectX::XMMATRIX previous_view_projection;
		// DirectX::XMMATRIX screen_to_world;
		// DirectX::XMMATRIX view_to_world;
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

	long (*const preferences_get_effects_quality)() = (long (*)())0x50B150;
	bool (*const preferences_get_motion_blur)() = (bool (*)())0x50B990;
	bool (*const sub_610190)() = (bool (*)())0x610190;
	void (*const unpack_distortion_matrices)(real_matrix4x3 *, DirectX::XMMATRIX *, DirectX::XMMATRIX *, DirectX::XMMATRIX *) = (void (*)(real_matrix4x3 *, DirectX::XMMATRIX *, DirectX::XMMATRIX *, DirectX::XMMATRIX *))0xA397E0;
	c_player_render_camera_iterator render_camera_it;
	long window_count = ((long (__thiscall *)(c_player_render_camera_iterator *))0x6042B0)(&render_camera_it);
	bool render_motion_blur = false;
	if (!preferences_get_motion_blur() || !c_rasterizer_states::initialized || (((bool (*)())0x67D270)() && !tls_getd().rasterizer_game_states->render_cinematic_motion_blur_enabled) || !sub_610190() || window_count > c_rasterizer_globals::g_motion_blur_max_local_players)
	{
		render_motion_blur = false;
	}
	else
	{
		render_motion_blur = true;
		if (motion_suck_dir->i == 0.0f && motion_suck_dir->j == 0.0f && motion_suck_dir->k == 0.0f)
		{
			float forward_vector_velocity = dot_product3d(&_this->distortion_forward, &_this->rasterizer_camera.forward);
			float up_vector_velocity = dot_product3d(&_this->distortion_up, &_this->rasterizer_camera.up);
			real_vector3d velocity_vector;
			vector_from_points3d(&_this->rasterizer_camera.position, &_this->distortion_position, &velocity_vector);
			float distortion_magnitude = magnitude3d(&velocity_vector);
			if (!force_motion_blur && forward_vector_velocity > 0.99f && up_vector_velocity > 0.99f && distortion_magnitude < 1.0f || forward_vector_velocity < c_render_globals::motion_blur_velocity_threshold || up_vector_velocity < c_render_globals::motion_blur_velocity_threshold || distortion_magnitude > 5.0f)
				render_motion_blur = false;
		}
	}
	if ((((bool (*)())0xA29580)() || render_motion_blur) && preferences_get_effects_quality() > 0)
	{
		DirectX::XMMATRIX wtv;
		DirectX::XMMATRIX view_to_world;
		unpack_distortion_matrices(&_this->rasterizer_projection.world_to_view, (DirectX::XMMATRIX *)&_this->rasterizer_projection.projection_matrix[0][0], &wtv, &view_to_world);
		DirectX::XMMATRIX current_view_projection = wtv * view_to_world;
		DirectX::XMMATRIX prev_wtv;
		DirectX::XMMATRIX prev_view_to_world;
		unpack_distortion_matrices(&_this->distortion_projection_matrix, (DirectX::XMMATRIX *)&_this->distortion_view_parameters, &prev_wtv, &prev_view_to_world);
		DirectX::XMMATRIX motion_suck_translation = DirectX::XMMatrixTranslation(motion_suck_dir->i, motion_suck_dir->j, motion_suck_dir->k);
		DirectX::XMMATRIX previous_view_projection = motion_suck_translation * prev_wtv * prev_view_to_world;
		DirectX::XMMATRIX screen_to_world = DirectX::XMMatrixInverse(nullptr, current_view_projection);
		IDirect3DDevice9Ex *const device = c_rasterizer::get_device();
		device->StretchRect(((c_render_surface *(__thiscall *)(c_surface_group *, e_surface))0xA48740)((c_surface_group *)0x510DB1C, (e_surface)7)->m_surface, nullptr, ((c_render_surface *(__thiscall *)(c_surface_group *, e_surface))0xA48740)((c_surface_group *)0x510DD14, (e_surface)0xD)->m_surface, nullptr, D3DTEXF_POINT);
		((e_surface (*const)(e_surface))0xA48CB0)((e_surface)0);
		draw_fullscreen_displacement(&_this->rasterizer_camera.window_pixel_bounds, &current_view_projection, &previous_view_projection, &view_to_world, &screen_to_world, render_motion_blur);
		((void (*const)())0xA202F0)();
		((void (*const)(bool))0xA2A320)(false);
	}
	memcpy(&_this->distortion_view_parameters, &_this->rasterizer_projection.projection_matrix, sizeof(_this->distortion_view_parameters));
	memcpy(&_this->distortion_projection_matrix, &_this->rasterizer_projection.world_to_view, sizeof(_this->distortion_projection_matrix));
	_this->distortion_forward = _this->rasterizer_camera.forward;
	_this->distortion_up = _this->rasterizer_camera.up;
	_this->distortion_position = _this->rasterizer_camera.position;
}

/* ---------- private code */
