#ifndef __BLAM_RENDER_VIEWS_RENDER_TEXTURE_CAMERA_VIEW_HPP__
#define __BLAM_RENDER_VIEWS_RENDER_TEXTURE_CAMERA_VIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/damage_definitions.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/views/render_player_view.hpp"

/* ---------- forward declarations */

struct c_player_view;
struct c_rasterizer_texture_ref;
struct c_texture_camera_view;

/* ---------- constants */

/* ---------- definitions */

struct c_texture_camera_view :
	public c_player_view
{
	c_rasterizer_texture_ref accum_texture; // 0x26B8
	c_rasterizer_texture_ref albedo_texture; // 0x26BC
	c_rasterizer_texture_ref normal_texture; // 0x26C0
	c_rasterizer_texture_ref unknown_texture1; // 0x26C4
	c_rasterizer_texture_ref unknown_texture2; // 0x26C8
	long cubemap_face; // 0x26CC
	c_enum<enum e_surface,long> depth_stencil_surface; // 0x26D0
	unsigned long flags; // 0x26D4
	long unknown_object_index; // 0x26D8
	long field_26DC; // 0x26DC
	void (*unknown_callback)(void *); // 0x26E0
	void *unknown_callback_context; // 0x26E4
	c_texture_camera_view(c_texture_camera_view &); /* compiler_generated() */
	c_texture_camera_view(c_texture_camera_view const &); /* compiler_generated() */
	c_texture_camera_view(); /* compiler_generated() */
	c_texture_camera_view &operator=(c_texture_camera_view &); /* compiler_generated() */
	c_texture_camera_view &operator=(c_texture_camera_view const &); /* compiler_generated() */
};
static_assert(sizeof(c_texture_camera_view) == 9960, "Invalid c_texture_camera_view size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_VIEWS_RENDER_TEXTURE_CAMERA_VIEW_HPP__
