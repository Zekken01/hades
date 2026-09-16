#ifndef __MODS_MAP_VARIANT_LOADER_HPP__
#define __MODS_MAP_VARIANT_LOADER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/saved_games/content.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"

/* ---------- forward declarations */

struct c_map_variant_loader;
struct real_point3d;
struct real_rectangle3d;
struct real_vector3d;
struct s_content_item_metadata;
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_variant_datum;
struct s_variant_quota;

/* ---------- constants */

/* ---------- definitions */

struct s_map_variant
{
	s_content_item_metadata metadata; // 0x0
	short version; // 0xF8
	unsigned short scenario_object_count; // 0xFA
	unsigned short variant_object_count; // 0xFC
	unsigned short placeable_object_quota_count; // 0xFE
	long map_id; // 0x100
	real_rectangle3d world_bounds; // 0x104
	long content_type; // 0x11C
	float maximum_budget; // 0x120
	float spent_budget; // 0x124
	bool showing_helpers; // 0x128
	bool built_in; // 0x129
	long cache_checksum; // 0x12C
	s_variant_datum objects[640]; // 0x130
	short object_type_start_index[15]; // 0xD330
	s_variant_quota object_quotas[256]; // 0xD350
	char simulation_state[320]; // 0xDF50
	static long (*const create_object)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short);
	static void (*const initialize)(s_map_variant *, long);
	s_map_variant(s_map_variant &); /* compiler_generated() */
	_inline s_map_variant(s_map_variant const &__that); /* compiler_generated() */
	_inline s_map_variant() = default; /* compiler_generated() */
	s_map_variant &operator=(s_map_variant &); /* compiler_generated() */
	s_map_variant &operator=(s_map_variant const &); /* compiler_generated() */
};
static_assert(sizeof(s_map_variant) == 57488, "Invalid s_map_variant size");
static_assert(offsetof(s_map_variant, cache_checksum) == 0x12C, "s_map_variant::cache_checksum moved when its reconstructed padding was removed");
static_assert(offsetof(s_map_variant, object_quotas) == 0xD350, "s_map_variant::object_quotas moved when its reconstructed padding was removed");

struct c_map_variant_loader
{
	static void initialzie();
	static void update();
	static bool load_from_buffer(long blf_size, unsigned char const *blf, s_map_variant *out_map_variant);
	static bool load_from_file(char const *filename, s_map_variant *out_map_variant);
	static bool load_default(long map_id, s_map_variant *out_map_variant);
	static e_map_variant_load_error get_last_error();
};
static_assert(sizeof(c_map_variant_loader) == 1, "Invalid c_map_variant_loader size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_MAP_VARIANT_LOADER_HPP__
