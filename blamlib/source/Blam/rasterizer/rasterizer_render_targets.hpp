#ifndef __BLAM_RASTERIZER_RASTERIZER_RENDER_TARGETS_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_RENDER_TARGETS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

/* ---------- forward declarations */

struct c_render_surface;
struct c_surface_group;
struct s_surface_description;
struct s_surface_group_description;

/* ---------- constants */

enum e_surface
{
	_surface_none = 0,
	_surface_disable,
	_surface_display,
	_surface_shadow_1,
	_surface_depth_stencil,
	_surface_depth_stencil_multisample,
	_surface_screenshot_composite_16f,
	_surface_accum_LDR,
	_surface_accum_HDR,
	_surface_albedo,
	_surface_albedo_debug,
	_surface_gbuf,
	_surface_normal,
	_surface_post_LDR,
	_surface_post_HDR,
	_surface_post_half_LDR,
	_surface_post_half_HDR,
	_surface_normal_half,
	_surface_depth_half_fp32,
	_surface_color_half_fp16_0,
	_surface_color_half_fp16_1,
	_surface_fullscreen_blur,
	_surface_shadow_color,
	_surface_depth_fp32,
	_surface_aux_reflection,
	_surface_aux_refraction,
	_surface_hdr_retrieve,
	_surface_ssao_noise,
	_surface_screenshot_composite_8bit,
	_surface_screenshot_display,
	_surface_screenshot_composite_16i,
	_surface_aux_bloom,
	_surface_aux_chud,
	_surface_aux_star,
	_surface_aux_small,
	_surface_aux_tiny,
	_surface_aux_mini,
	_surface_aux_exposure_0,
	_surface_aux_exposure_1,
	_surface_aux_exposure_2,
	_surface_aux_exposure_3,
	_surface_aux_exposure_4,
	_surface_aux_exposure_5,
	_surface_aux_exposure_6,
	_surface_aux_exposure_7,
	_surface_aux_small2,
	_surface_aux_tiny2,
	_surface_aux_mini2,
	_surface_aux_depth_of_field2,
	_surface_aux_depth_of_field,
	_surface_distortion,
	_surface_depth_camera_depth,
	_surface_depth_camera,
	_surface_aux_water_interaction_height,
	_surface_aux_water_interaction_slope,
	_surface_chud_turbulence,
	_surface_cortana_effect_mua_haha,
	_surface_surface_depth_camera_texture,
	_surface_surface_weather_occlusion,
	_surface_surface_depth_visr,
};

/* ---------- definitions */

#pragma pack(push, 4)
struct s_surface_group_description
{
	c_flags<enum e_surface_variant_flags,long> m_variant_flags; // 0x0
	bool valid; // 0x4
	unsigned char __pad0[3]; // 0x5
	float depth_stencil_width; // 0x8
	float depth_stencil_height; // 0xC
	unsigned long depth_stencil_format; // 0x10
	unsigned char __pad1[4]; // 0x14
	bool srgb; // 0x18
	unsigned char __pad2[3]; // 0x19
	unsigned long multisample_type; // 0x1C
	float surface_width; // 0x20
	float surface_height; // 0x24
	unsigned long surface_format; // 0x28
	unsigned char __pad3[20]; // 0x2C
	long texture_alias_surface; // 0x40
	unsigned char __pad4[4]; // 0x44
	e_surface unknown_surface; // 0x48
	s_surface_group_description(s_surface_group_description &); /* compiler_generated() */
	s_surface_group_description(s_surface_group_description const &); /* compiler_generated() */
	s_surface_group_description(); /* compiler_generated() */
	s_surface_group_description &operator=(s_surface_group_description &); /* compiler_generated() */
	s_surface_group_description &operator=(s_surface_group_description const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_surface_group_description) == 76, "Invalid s_surface_group_description size");

struct s_surface_description
{
	bool vald; // 0x0
	unsigned char __pad0[3]; // 0x1
	float surface_width; // 0x4
	float surface_height; // 0x8
	_D3DFORMAT surface_format; // 0xC
	unsigned char __pad1[8]; // 0x10
	float depth_stencil_width; // 0x18
	float depth_stencil_height; // 0x1C
	_D3DFORMAT depth_stencil_format; // 0x20
	bool srgb; // 0x24
	unsigned char __pad2[11]; // 0x25
	unsigned long multi_sample_type; // 0x30
	long texture_alias_surface; // 0x34
	unsigned char __pad3[12]; // 0x38
	e_surface unknown_surface; // 0x44
};
static_assert(sizeof(s_surface_description) == 72, "Invalid s_surface_description size");

struct c_render_surface
{
	IDirect3DSurface9 *m_surface; // 0x0
	IDirect3DTexture9 *m_texture; // 0x4
	s_surface_description m_desc; // 0x8
	__int32 m_buffer_index; // 0x50
	__int32 field_54; // 0x54
	__int32 field_58; // 0x58
	__int32 field_5C; // 0x5C
	__int32 field_60; // 0x60
	__int32 field_64; // 0x64
	__int32 field_68; // 0x68
	__int32 field_6C; // 0x6C
	__int32 field_70; // 0x70
	__int32 field_74; // 0x74
};
static_assert(sizeof(c_render_surface) == 120, "Invalid c_render_surface size");

#pragma pack(push, 4)
struct c_surface_group
{
	s_surface_group_description description; // 0x0
	long surface_count; // 0x4C
	c_render_surface *surfaces; // 0x50
	static c_render_surface *(*const get_specialized_surface)(c_surface_group *, e_surface);
	c_surface_group(c_surface_group &); /* compiler_generated() */
	c_surface_group(c_surface_group const &); /* compiler_generated() */
	c_surface_group(); /* compiler_generated() */
	c_surface_group &operator=(c_surface_group &); /* compiler_generated() */
	c_surface_group &operator=(c_surface_group const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_surface_group) == 84, "Invalid c_surface_group size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_RENDER_TARGETS_HPP__
