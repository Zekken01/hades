#ifndef __BLAM_BITMAPS_BITMAP_DEFINITION_HPP__
#define __BLAM_BITMAPS_BITMAP_DEFINITION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct c_rasterizer_texture_ref;
struct real_point2d;
struct s_bitmap_definition;
struct s_bitmap_image;
struct s_bitmap_resource;
struct s_bitmap_sequence;
struct s_bitmap_sprite;
struct s_bitmap_tight_binding;
struct s_bitmap_usage_override;
struct s_tag_data;
struct short_point_2d;

/* ---------- constants */

/* ---------- definitions */

struct s_bitmap_tight_binding
{
	real_point2d uv; // 0x0
};
static_assert(sizeof(s_bitmap_tight_binding) == 8, "Invalid s_bitmap_tight_binding size");

struct s_bitmap_usage_override
{
	float source_gamma; // 0x0
	long bitmap_curve; // 0x4
	long unknown_8; // 0x8
	long unknown_C; // 0xC
	long unknown_10; // 0x10
	long unknown_14; // 0x14
	long unknown_18; // 0x18
	long unknown_1C; // 0x1C
	long unknown_20; // 0x20
	long unknown_24; // 0x24
};
static_assert(sizeof(s_bitmap_usage_override) == 40, "Invalid s_bitmap_usage_override size");

struct s_bitmap_sprite
{
	short bitmap_index; // 0x0
	short unknown; // 0x2
	short unknown2; // 0x4
	float left; // 0x8
	float right; // 0xC
	float top; // 0x10
	float bottom; // 0x14
	real_point2d registration_point; // 0x18
};
static_assert(sizeof(s_bitmap_sprite) == 32, "Invalid s_bitmap_sprite size");
static_assert(offsetof(s_bitmap_sprite, left) == 0x8, "s_bitmap_sprite::left moved when its reconstructed padding was removed");

struct s_bitmap_sequence
{
	char name[32]; // 0x0
	short first_bitmap_index; // 0x20
	short bitmap_count; // 0x22
	long unknown; // 0x24
	long unknown2; // 0x28
	long unknown3; // 0x2C
	long unknown4; // 0x30
	c_tag_block<s_bitmap_sprite> sprites; // 0x34
};
static_assert(sizeof(s_bitmap_sequence) == 64, "Invalid s_bitmap_sequence size");

struct s_bitmap_image
{
	unsigned long signature; // 0x0
	short width; // 0x4
	short height; // 0x6
	unsigned char depth; // 0x8
	unsigned char more_flags; // 0x9
	short bitmap_type; // 0xA
	c_enum<enum e_bitmap_format,unsigned char> format; // 0xC
	short flags; // 0xE
	short_point_2d registration_point; // 0x10
	unsigned char mipmap_count; // 0x14
	unsigned char curve_mode; // 0x15
	unsigned char interleaved_interop; // 0x16
	unsigned char interleaved_texture_index; // 0x17
	long pixels_offset; // 0x18
	long pixels_size; // 0x1C
	long high_res_pixels_offset; // 0x20
	long high_res_pixels_size; // 0x24
	c_rasterizer_texture_ref hardware_format; // 0x28
	void *runtime_tag_base_address; // 0x2C
	s_bitmap_image(s_bitmap_image &); /* compiler_generated() */
	s_bitmap_image(s_bitmap_image const &); /* compiler_generated() */
	s_bitmap_image(); /* compiler_generated() */
	s_bitmap_image &operator=(s_bitmap_image &); /* compiler_generated() */
	s_bitmap_image &operator=(s_bitmap_image const &); /* compiler_generated() */
};
static_assert(sizeof(s_bitmap_image) == 48, "Invalid s_bitmap_image size");
static_assert(offsetof(s_bitmap_image, flags) == 0xE, "s_bitmap_image::flags moved when its reconstructed padding was removed");

struct s_bitmap_resource
{
	unsigned long pageable_resource; // 0x0
	long unknown; // 0x4
};
static_assert(sizeof(s_bitmap_resource) == 8, "Invalid s_bitmap_resource size");

struct s_bitmap_definition
{
	long usage; // 0x0
	c_flags<enum e_bitmap_runtime_flags,short> runtime_flags; // 0x4
	short sprite_spacing; // 0x6
	float bump_map_height; // 0x8
	float fade_factor; // 0xC
	unsigned char bitmap_curve_mode; // 0x10
	unsigned char max_mipmap_level; // 0x11
	short max_resolution; // 0x12
	short atlas_index; // 0x14
	short force_bitmap_format; // 0x16
	c_tag_block<s_bitmap_tight_binding> tight_bounds; // 0x18
	c_tag_block<s_bitmap_usage_override> usage_overrides; // 0x24
	c_tag_block<s_bitmap_sequence> manual_sequences; // 0x30
	s_tag_data source_data; // 0x3C
	s_tag_data processed_pixel_data; // 0x50
	c_tag_block<s_bitmap_sequence> sequences; // 0x64
	c_tag_block<s_bitmap_image> images; // 0x70
	s_tag_data xenon_processed_pixel_data; // 0x7C
	c_tag_block<s_bitmap_image> xenon_images; // 0x90
	c_tag_block<s_bitmap_resource> resources; // 0x9C
	c_tag_block<s_bitmap_resource> interleaved_resources; // 0xA8
	long unknown_B4; // 0xB4
	s_bitmap_definition(s_bitmap_definition &); /* compiler_generated() */
	s_bitmap_definition(s_bitmap_definition const &); /* compiler_generated() */
	s_bitmap_definition(); /* compiler_generated() */
	s_bitmap_definition &operator=(s_bitmap_definition &); /* compiler_generated() */
	s_bitmap_definition &operator=(s_bitmap_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_bitmap_definition) == 184, "Invalid s_bitmap_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_BITMAPS_BITMAP_DEFINITION_HPP__
