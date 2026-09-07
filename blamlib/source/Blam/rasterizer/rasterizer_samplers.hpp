#ifndef __BLAM_RASTERIZER_RASTERIZER_SAMPLERS_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_SAMPLERS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/damage_definitions.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"

/* ---------- forward declarations */

struct c_rasterizer_samplers;
struct c_rasterizer_texture_ref;

/* ---------- constants */

enum e_sampler_filter_mode
{
	_filter_trilinear = 0,
	_filter_point,
	_filter_bilinear,
	_filter_unused_00,
	_filter_anisotropic_2x,
	_filter_unused_01,
	_filter_anisotropic_4x,
	_filter_lightprobe_texture_array,
	_filter_texture_array_quadlinear,
	_filter_texture_array_quadanisotropic_2x,
};

enum e_sampler_address_mode
{
	_address_mode_wrap = 0,
	_address_mode_clamp,
	_address_mode_mirror,
	_address_mode_black_border,
	_address_mode_mirror_once,
	_address_mode_mirror_once_border,
};

/* ---------- definitions */

struct c_rasterizer_samplers
{
	static void (*const clear_sampler_texture_cache)(long);
	static void (*const clear_sampler_textures)();
	static long (*const get_stage)(long);
	static void (*const set_sampler_address_mode)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>);
	static void (*const set_sampler_address_mode_custom_device_no_cache)(void *, long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>);
	static void (*const set_sampler_filter_mode)(long, c_enum<enum e_sampler_filter_mode,long>);
	static void (*const set_vertex_sampler_filter_mode)(long, c_enum<enum e_sampler_filter_mode,long>);
	static void (*const set_sampler_filter_mode_custom_device_no_cache)(void *, long, c_enum<enum e_sampler_filter_mode,long>);
	static void (*const set_sampler_texture)(long, c_rasterizer_texture_ref);
	static void (*const set_sampler_texture_direct)(long, IDirect3DBaseTexture9 *);
	static void (*const set_srgb)(long, long);
	static char *sampler_srgb_states;
	static long get_forced_aniso_filter();
};
static_assert(sizeof(c_rasterizer_samplers) == 1, "Invalid c_rasterizer_samplers size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_SAMPLERS_HPP__
