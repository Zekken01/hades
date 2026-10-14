#ifndef __BLAM_RENDER_VIEWS_RENDER_PLAYER_VIEW_HPP__
#define __BLAM_RENDER_VIEWS_RENDER_PLAYER_VIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/camera/observer.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_first_person_view.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Blam/render/views/render_ui_view.hpp"
#include "Blam/render/views/render_world_view.hpp"

/* ---------- forward declarations */

struct c_camera_fx_settings;
struct c_camera_fx_values;
struct c_first_person_view;
struct c_lights_view;
struct c_patchy_fog;
struct c_player_view;
struct c_ui_view;
struct c_world_view;
struct real_matrix4x3;
struct real_rectangle2d;
struct real_vector3d;
struct s_observer_depth_of_field;
struct s_render_game_state_player_window;
struct s_render_view_parameters;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_patchy_fog
{
	real_vector3d camera_position; // 0x0
	real_vector3d camera_forward; // 0xC
	real_vector3d camera_up; // 0x18
	float rotation; // 0x24
	float near_clip_unknown; // 0x28
	__int32 field_2C; // 0x2C
	__int32 field_30; // 0x30
	unsigned char field_34[400]; // 0x34
	unsigned char field_1C4[400]; // 0x1C4
};
#pragma pack(pop)
static_assert(sizeof(c_patchy_fog) == 852, "Invalid c_patchy_fog size");

struct s_render_view_parameters
{
	real_rectangle2d frustum_bounds; // 0x0
	float window_width; // 0x10
	float window_height; // 0x14
	float frustum_half_width; // 0x18
	float frustum_half_height; // 0x1C
	float scale_x; // 0x20
	float scale_y; // 0x24
	float width_scale; // 0x28
	float height_scale; // 0x2C
	real_rectangle2d projection_bounds; // 0x30
};
static_assert(sizeof(s_render_view_parameters) == 64, "Invalid s_render_view_parameters size");

struct s_render_game_state_player_window
{
	c_camera_fx_settings camera_fx_settings; // 0x0
	c_camera_fx_values camera_fx_values; // 0x170
};
static_assert(sizeof(s_render_game_state_player_window) == 864, "Invalid s_render_game_state_player_window size");

struct c_player_view :
	public c_world_view
{
	s_render_game_state_player_window *player_window_game_state; // 0x298
	float exposure; // 0x29C
	float bloom_intensity; // 0x2A0
	s_observer_depth_of_field observer_depth_of_field; // 0x2A4
	c_patchy_fog patchy_fog; // 0x2B8
	real_point3d distortion_position; // 0x60C
	real_vector3d distortion_forward; // 0x618
	real_vector3d distortion_up; // 0x624
	__int32 field_630; // 0x630
	real_matrix4x3 distortion_projection_matrix; // 0x634
	s_render_view_parameters distortion_view_parameters; // 0x668
	c_first_person_view first_person_view; // 0x6A8
	c_ui_view ui_view; // 0x940
	c_lights_view lights_view; // 0xBDC
	char lightmap_shadows_view[728]; // 0x1E4C
	char reflections_view[660]; // 0x2124
	char occlusion_view[720]; // 0x23B8
	char field_2688; // 0x2688
	unsigned char __pad0[7]; // 0x2689
	short_rectangle2d unknown_bounds; // 0x2690
	long window_index; // 0x2698
	long window_count; // 0x269C
	long display_type; // 0x26A0
	long out_user_index; // 0x26A4
	long controller_index; // 0x26A8
	long splitscreen_res; // 0x26AC
	long blur_surface; // 0x26B0
	bool flush_device_queries; // 0x26B4
	static float &render_debug_depth_render_scale_r;
	static float &render_debug_depth_render_scale_g;
	static float &render_debug_depth_render_scale_b;
	static float render_debug_depth_render_alpha;
	static _inline c_player_view *get_current();
	static void __fastcall apply_distortions_new(c_player_view *_this, real_vector3d *motion_suck_dir, bool force_motion_blur);
	static void (*const distortion_generate)(c_player_view *);
	static void (*const queue_patchy_fog)(c_player_view *);
	static bool (*const render_albedo)(c_player_view *);
	static void (*const render_albedo_decals)(long, long);
	static void (*const render_distortion)(c_player_view *);
	static void (*const render_first_person_static_lighting)(c_player_view *, char);
	static void (*const render_lens_flares)(c_player_view *);
	static char (*const render_lightmap_shadows)(c_player_view *);
	static void (*const render_static_lighting)(c_player_view *);
	static void (*const render_transparents)(c_player_view *);
	static void (*const render_water)();
	static void (*const render_weather_occlusion)(c_player_view *);
	static void (*const setup_camera_fx_parameters)(c_player_view *, float);
	static void (*const setup_cinematic_clip_planes)();
	static void (*const static_lighting_setup_internals)(c_player_view *);
	static void (*const render_effects)(long, long);
};
static_assert(sizeof(c_player_view) == 9912, "Invalid c_player_view size");

/* ---------- prototypes */

extern void draw_fullscreen_displacement(short_rectangle2d *bounds, DirectX::XMMATRIX *view_projection, DirectX::XMMATRIX *previous_view_projection, DirectX::XMMATRIX *view_to_world, DirectX::XMMATRIX *screen_to_world, bool render_motion_blur);

/* ---------- globals */

/* ---------- public code */

inline c_player_view *c_player_view::get_current() // 0x1085DBD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current@c_player_view@@SAPAU1@XZ");
	// procedure flags: nofpo

	return *(c_player_view * *)0x50dedf0;
}

/* ---------- private code */

#endif // __BLAM_RENDER_VIEWS_RENDER_PLAYER_VIEW_HPP__
