#ifndef __BLAM_RASTERIZER_RASTERIZER_STATES_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_STATES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"

/* ---------- forward declarations */

class c_rasterizer_states;
struct c_rasterizer_compiled_pixel_shader;
struct c_rasterizer_pixel_shader;
struct c_rasterizer_texture_ref;
struct c_rasterizer_vertex_shader;
struct short_rectangle2d;

/* ---------- constants */

enum e_z_buffer_mode
{
	_z_buffer_mode_default = 0,
	_z_buffer_mode_no_write,
	_z_buffer_mode_disabled,
	_z_buffer_mode_shadow_generate,
	_z_buffer_mode_dynamic_light_shadow,
	_z_buffer_mode_shadow_apply,
	_z_buffer_mode_decal,
	_z_buffer_mode_unknown_no_write,
	_z_buffer_mode_unknown_always,
};

enum e_alpha_blend_mode
{
	_blend_mode_opaque = 0,
	_blend_mode_additive,
	_blend_mode_multiply,
	_blend_mode_alpha_blend,
	_blend_mode_double_multiply,
	_blend_mode_pre_multiplied_alpha,
	_blend_mode_maximum,
	_blend_mode_multiply_add,
	_blend_mode_add_src_times_dstalpha,
	_blend_mode_add_src_times_srcalpha,
	_blend_mode_inv_alpha_blend,
	_blend_mode_separate_alpha_blend,
	_blend_mode_separate_alpha_blend_additive,
};

/* ---------- definitions */

class c_rasterizer_states
{
public:
	static void (*const restore_last_scissor_rect)();
	static void (*const restore_last_viewport)();
	static long (*const enable_clip_planes)(long);
	static void (*const invalidate_render_state_cache)();
	static void (*const set_alpha_blend_mode)(long);
	static long (*const set_clip_plane)(long, float const *);
	static void (*const set_color_write_enable)(long, long);
	static bool (*const set_compiled_pixel_shader)(c_rasterizer_compiled_pixel_shader *);
	static bool (*const set_compiled_vertex_shader)(c_rasterizer_vertex_shader *, long, long, long);
	static void (*const set_cull_mode)(long);
	static long (*const get_cull_mode)();
	static bool (*const set_explicit_shaders)(long, long, long, long);
	static void (*const set_fill_mode)(long);
	static bool (*const set_pixel_shader)(c_rasterizer_pixel_shader *, long);
	static long (*const set_sampler_address_mode)(long, long, long, long);
	static void (*const set_sampler_filter_mode)(long, long);
	static void (*const set_sampler_texture)(long, c_rasterizer_texture_ref);
	static void (*const set_scissor_rect)(short_rectangle2d *);
	static long (*const set_alpha_blend_mode2)(long);
	static long (*const set_stencil_mode)(long);
	static void (*const set_stencil_mode_with_value)(long, unsigned char);
	static char (*const set_vertex_shader)(c_rasterizer_vertex_shader *, long, long, long);
	static long (*const set_z_buffer_mode)(long);
	static void (*const set_alpha_test_enabled)(bool);
	static void (*const set_srgb)(bool);
	static void (*const set_actually_calc_albedo)(bool);
	static unsigned long (*const setup_occlusion_state)();
	static void (*const setup_render_target_globals_with_exposure)(float, float, float);
	static void (*const setup_targets_static_lighting)(float, float, bool, float, bool, char, bool);
	static void (*const setup_targets_static_lighting_alpha_blend)(bool);
	static void (*const set_viewport)(short_rectangle2d *, float, float);
	static void (*const set_blend_factor)(long);
	static void (*const begin_high_quality_blend)();
	static void (*const end_high_quality_blend)();
	static void (*const reset)(bool);
	static bool &initialized;
	static _inline void set_separate_alpha_blend_enabled(bool b);
};
static_assert(sizeof(c_rasterizer_states) == 1, "Invalid c_rasterizer_states size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern void _sub_108F6990(bool);
_inline void c_rasterizer_states::set_separate_alpha_blend_enabled(bool b) // 0x108F6990
{
	mangled_x86(MANGLED_TODO, "?set_separate_alpha_blend_enabled@c_rasterizer_states@@SAX_N@Z");
	// bool b;
	todo("implement");
	_sub_108F6990(b);
}

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_STATES_HPP__
