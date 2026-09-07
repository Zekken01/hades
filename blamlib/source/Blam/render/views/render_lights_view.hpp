#ifndef __BLAM_RENDER_VIEWS_RENDER_LIGHTS_VIEW_HPP__
#define __BLAM_RENDER_VIEWS_RENDER_LIGHTS_VIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/render/views/render_world_view.hpp"

#include <d3d9.h>

/* ---------- forward declarations */

struct c_lights_view;
struct c_world_view;
struct real_rgb_color;
struct real_vector3d;
struct s_simple_light;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

struct s_simple_light
{
	real_point3d position; // 0x0
	float size; // 0xC
	real_vector3d direction; // 0x10
	float sphere; // 0x1C
	real_rgb_color color; // 0x20
	float smooth; // 0x2C
	float falloff_scale_x; // 0x30
	float falloff_scale_y; // 0x34
	float falloff_offset_x; // 0x38
	float falloff_offset_y; // 0x3C
	float bounding_radius; // 0x40
	unsigned char __pad0[12]; // 0x44
};
static_assert(sizeof(s_simple_light) == 80, "Invalid s_simple_light size");

struct c_lights_view :
	public c_world_view
{
	char data[3316]; // 0x298
	short_rectangle2d bounds; // 0xF8C
	long m_local_user_index; // 0xF94
	long m_simple_light_count; // 0xF98
	char data2[80]; // 0xF9C
	s_simple_light m_simple_lights[8]; // 0xFEC
	float global_light_intensity; // 0x126C
	static void (*const submit_simple_light_draw_list_to_vertex_shader)(c_lights_view *, long, long);
	static void (*const submit_simple_light_draw_list_to_shader)(s_simple_light *, long);
	static void (*const build_simple_light_draw_list)(c_lights_view *, long);
	static long (*const clear_simple_light_draw_list)(c_lights_view *, long);
	static void (*const render)(c_lights_view *, long, long, IDirect3DSurface9 *, IDirect3DSurface9 *, IDirect3DSurface9 *);
	static void (*const submit_attachments)(long);
	static void (*const submit_light_draw_list_to_shader)(s_simple_light *, long);
	static float const &g_render_light_intensity;
};
static_assert(sizeof(c_lights_view) == 4720, "Invalid c_lights_view size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_VIEWS_RENDER_LIGHTS_VIEW_HPP__
