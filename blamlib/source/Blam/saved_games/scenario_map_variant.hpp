#ifndef __BLAM_SAVED_GAMES_SCENARIO_MAP_VARIANT_HPP__
#define __BLAM_SAVED_GAMES_SCENARIO_MAP_VARIANT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"

/* ---------- forward declarations */

struct c_object_identifier;
struct real_vector3d;
struct s_map_variant_placement_properties;
struct s_variant_datum;
struct s_variant_quota;

/* ---------- constants */

/* ---------- definitions */

struct s_map_variant_placement_properties
{
	c_flags<enum e_game_engine_type,unsigned short> game_engine_flags; // 0x0
	c_flags<enum e_variant_placement_flags,unsigned char> placement_flags; // 0x2
	char team_affiliation; // 0x3
	unsigned char shared_storage; // 0x4
	unsigned char respawn_time; // 0x5
	char multiplayer_object_type; // 0x6
	c_enum<enum e_multiplayer_object_boundary_shape,char> boundry_shape; // 0x7
	float boundry_width; // 0x8
	float boundry_length; // 0xC
	float boundry_top; // 0x10
	float boundry_bottom; // 0x14
	// s_map_variant_placement_properties(s_map_variant_placement_properties &); /* compiler_generated() */ // hades: implicit, so the struct is an aggregate
	// _inline s_map_variant_placement_properties(s_map_variant_placement_properties const &__that); /* compiler_generated() */
	// _inline s_map_variant_placement_properties() = default; /* compiler_generated() */
	s_map_variant_placement_properties &operator=(s_map_variant_placement_properties &); /* compiler_generated() */
	_inline s_map_variant_placement_properties &operator=(s_map_variant_placement_properties const &__that); /* compiler_generated() */
};
static_assert(sizeof(s_map_variant_placement_properties) == 24, "Invalid s_map_variant_placement_properties size");

#pragma pack(push, 4)
struct s_variant_datum
{
	c_flags<enum e_variant_object_placement_flags,unsigned short> flags; // 0x0
	long object_index; // 0x4
	long editor_object_index; // 0x8
	long quota_index; // 0xC
	real_point3d position; // 0x10
	real_vector3d forward; // 0x1C
	real_vector3d up; // 0x28
	c_object_identifier parent_object; // 0x34
	s_map_variant_placement_properties properties; // 0x3C
	s_variant_datum(s_variant_datum &); /* compiler_generated() */
	_inline s_variant_datum(s_variant_datum const &__that); /* compiler_generated() */
	_inline s_variant_datum() = default; /* compiler_generated() */
	s_variant_datum &operator=(s_variant_datum &); /* compiler_generated() */
	s_variant_datum &operator=(s_variant_datum const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_variant_datum) == 84, "Invalid s_variant_datum size");

struct s_variant_quota
{
	long definition_index; // 0x0
	unsigned char minimum_count; // 0x4
	unsigned char maximum_count; // 0x5
	unsigned char placed_on_map; // 0x6
	unsigned char maximum_allowed; // 0x7
	float cost; // 0x8
};
static_assert(sizeof(s_variant_quota) == 12, "Invalid s_variant_quota size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SAVED_GAMES_SCENARIO_MAP_VARIANT_HPP__
