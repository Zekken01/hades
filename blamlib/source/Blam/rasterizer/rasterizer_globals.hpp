#ifndef __BLAM_RASTERIZER_RASTERIZER_GLOBALS_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/game/game_globals.hpp"  // hades: added for 0x108D32B0
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_rasterizer_globals;
struct c_rasterizer_texture_ref;
struct s_default_bitmap;
struct s_explicit_shader_ref;
struct s_motion_blur_parameters;
struct s_rasterizer_globals;
struct s_tag_reference;

/* ---------- constants */

enum e_rasterizer_default_bitmap
{
	_default_bitmap_default_white = 0,
	_default_bitmap_default_normal,
	_default_bitmap_default_cubemap,
	_default_bitmap_default_environment_map,
	_default_bitmap_color_bars,
	_default_bitmap_color_black,
	_default_bitmap_color_black_transparent,
	_default_bitmap_color_gray,
	_default_bitmap_auto_exposure_weight,
	_default_bitmap_auto_exposure_weight_4x3,
	_default_bitmap_stencil_dither_pattern,
	_default_bitmap_noise_warp,
	_default_bitmap_ripple_pattern,
	_default_bitmap_noise,
	_default_bitmap_material_diffuse_power,
	_default_bitmap_smaa_area,
	_default_bitmap_smaa_search,
	k_number_of_rasterizer_default_bitmaps,
};

enum e_rasterizer_default_shader
{
	_default_shader_debug = 0,
	_default_shader_debug2d,
	_default_shader_copy_surface,
	_default_shader_spike_blur_vertical,
	_default_shader_spike_blur_horizontal,
	_default_shader_downsize_2x_to_bloom,
	_default_shader_downsize_2x_target,
	_default_shader_copy_rgbe_to_rgb,
	_default_shader_update_persistence,
	_default_shader_add_downsampled,
	_default_shader_add,
	_default_shader_blur_11_horizontal,
	_default_shader_blur_11_vertical,
	_default_shader_cubemap_phi_blur,
	_default_shader_cubemap_theta_blur,
	_default_shader_cubemap_clamp,
	_default_shader_cubemap_divide,
	_default_shader_write_depth,
	_default_shader_final_composite,
	_default_shader_sky_dome_simple,
	_default_shader_transparent,
	_default_shader_shield_meter,
	_default_shader_legacy_meter,
	_default_shader_overhead_map_geometry,
	_default_shader_legacy_hud_bitmap,
	_default_shader_blend3,
	_default_shader_particle_update,
	_default_shader_particle_spawn,
	_default_shader_screenshot_combine,
	_default_shader_downsample_2x2,
	_default_shader_rotate_2d,
	_default_shader_bspline_resample,
	_default_shader_downsample_4x4_bloom_dof,
	_default_shader_final_composite_dof,
	_default_shader_kernel_5,
	_default_shader_exposure_downsample,
	_default_shader_yuv_to_rgb,
	_default_shader_displacement,
	_default_shader_screenshot_display,
	_default_shader_downsample_4x4_block,
	_default_shader_crop,
	_default_shader_screenshot_combine_dof,
	_default_shader_gamma_correct,
	_default_shader_contrail_spawn,
	_default_shader_contrail_update,
	_default_shader_stencil_stipple,
	_default_shader_lens_flare,
	_default_shader_decorator_default,
	_default_shader_downsample_4x4_block_bloom,
	_default_shader_downsample_4x4_gaussian,
	_default_shader_apply_color_matrix,
	_default_shader_copy,
	_default_shader_shadow_geometry,
	_default_shader_shadow_apply,
	_default_shader_gradient,
	_default_shader_alpha_test_explicit,
	_default_shader_patchy_fog,
	_default_shader_light_volume_update,
	_default_shader_water_ripple,
	_default_shader_double_gradient,
	_default_shader_sniper_scope,
	_default_shader_shield_impact,
	_default_shader_player_emblem_world,
	_default_shader_player_emblem_screen,
	_default_shader_implicit_hill,
	_default_shader_chud_overlay_blend,
	_default_shader_bloom_add_alpha1,
	_default_shader_downsample_4x4_block_bloom_ldr,
	_default_shader_restore_ldr_hdr_depth,
	_default_shader_beam_update,
	_default_shader_decorator_no_wind,
	_default_shader_decorator_static,
	_default_shader_decorator_sun,
	_default_shader_decorator_wavy,
	_default_shader_final_composite_zoom,
	_default_shader_final_composite_debug,
	_default_shader_shadow_apply_point,
	_default_shader_shadow_apply_bilinear,
	_default_shader_shadow_apply_fancy,
	_default_shader_shadow_apply_faster,
	_default_shader_shadow_apply2,
	_default_shader_displacement_motion_blur,
	_default_shader_decorator_shaded,
	_default_shader_screenshot_memexport,
	_default_shader_downsample_4x4_gaussian_bloom_ldr,
	_default_shader_downsample_4x4_gaussian_bloom,
	_default_shader_downsample_4x4_block_bloom_new,
	_default_shader_bloom_curve,
	_default_shader_custom_gamma_correct,
	_default_shader_pixel_copy,
	_default_shader_unknown90,
	_default_shader_hdr_retrieve,
	_default_shader_unknown92,
	_default_shader_unknown93,
	_default_shader_unknown94,
	_default_shader_unknown95,
	_default_shader_unknown96,
	_default_shader_unknown97,
	_default_shader_unknown98,
	_default_shader_unknown99,
	_default_shader_unknown100,
	_default_shader_unknown101,
	_default_shader_unknown102,
	_default_shader_unknown103,
	_default_shader_unknown104,
	_default_shader_unknown105,
	_default_shader_unknown106,
	_default_shader_unknown107,
	_default_shader_unknown108,
	_default_shader_unknown109,
	k_number_of_rasterizer_default_shaders,
};

/* ---------- definitions */

#pragma pack(push, 4)
struct s_default_bitmap
{
	long flags; // 0x0
	s_tag_reference bitmap; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_default_bitmap) == 20, "Invalid s_default_bitmap size");

struct s_motion_blur_parameters
{
	float max_blur; // 0x0
	float field_04; // 0x4
	float blur_scale; // 0x8
	float center_falloff[2]; // 0xC
	float expected_time_per_tick; // 0x14
};
static_assert(sizeof(s_motion_blur_parameters) == 24, "Invalid s_motion_blur_parameters size");

#pragma pack(push, 4)
struct s_rasterizer_globals
{
	c_tag_block<s_default_bitmap> default_bitmaps; // 0x0
	c_tag_block<s_tag_reference> material_textures; // 0xC
	s_tag_reference default_vertex_shader; // 0x18
	s_tag_reference default_pixel_shader; // 0x28
	c_tag_block<s_explicit_shader_ref> explicit_shaders; // 0x38
	long field_44; // 0x44
	long field_48; // 0x48
	long field_4C; // 0x4C
	long field_50; // 0x50
	long field_54; // 0x54
	s_tag_reference active_camo_texture; // 0x58
	s_tag_reference default_performance_throttles; // 0x68
	s_tag_reference default_shield_impact; // 0x78
	s_tag_reference default_vision_mode; // 0x88
	long field_98; // 0x98
	s_motion_blur_parameters motion_blur_parameters; // 0x9C
};
#pragma pack(pop)
static_assert(sizeof(s_rasterizer_globals) == 180, "Invalid s_rasterizer_globals size");

class c_rasterizer_globals
{
public:
	static char &g_motion_blur_parameters_set;
	static bool g_motion_blur_cinematic_set;
	static s_motion_blur_parameters *g_motion_blur_parameters;
	static __int32 &g_motion_blur_max_local_players;
	static __int32 &g_motion_blur_min_width;
	static __int32 &g_motion_blur_max_width;
	static __int32 &g_motion_blur_min_taps;
	static __int32 &g_motion_blur_max_taps;
	static _inline s_rasterizer_globals *get();
	static void (__thiscall *get_default_texture_rasterizer_texture_ref)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>);
};
static_assert(sizeof(c_rasterizer_globals) == 1, "Invalid c_rasterizer_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline s_rasterizer_globals *c_rasterizer_globals::get() // 0x108D32B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@c_rasterizer_globals@@SAPAUs_rasterizer_globals@@XZ");
	// procedure flags: nofpo
	// function call : void *(*const)(unsigned long, long)

	return (s_rasterizer_globals *)tag_get('rasg', game_globals_get()->RasterizerGlobals.index);
}

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_GLOBALS_HPP__
