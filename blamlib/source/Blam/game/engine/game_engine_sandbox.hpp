#ifndef __BLAM_GAME_ENGINE_GAME_ENGINE_SANDBOX_HPP__
#define __BLAM_GAME_ENGINE_GAME_ENGINE_SANDBOX_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/tls.hpp"

#include "Blam/game/game_engine_globals.hpp"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"

/* ---------- forward declarations */

struct real_vector3d;
struct s_map_variant_placement_properties;
struct s_sandbox_globals;

/* ---------- constants */

/* ---------- definitions */

struct s_sandbox_globals
{
	__int32 field_0; // 0x0
	__int32 field_4; // 0x4
	unsigned short player_role; // 0x8
	long player_edited_object_index[16]; // 0xC
	float player_cursor_distance[16]; // 0x4C
	real_point3d player_cursor_position[16]; // 0x8C
	real_vector3d player_cursor_normal[16]; // 0x14C
	real_vector3d player_cursor_direction[16]; // 0x20C
	long player_cursor_object_index[16]; // 0x2CC
	bool player_rotating[16]; // 0x30C
	long tracked_objects_indices[64]; // 0x31C
	real_point3d tracked_object_positions[64]; // 0x41C
	long tracked_object_count; // 0x71C
	long field_720; // 0x720
	long last_create_object_variant_index; // 0x724
	bool map_variant_dirty; // 0x728
	long cursor_boundary_object_index; // 0x72C
	s_map_variant_placement_properties unknown_variant_properties; // 0x730
	s_sandbox_globals(s_sandbox_globals &); /* compiler_generated() */
	s_sandbox_globals(s_sandbox_globals const &); /* compiler_generated() */
	s_sandbox_globals(); /* compiler_generated() */
	s_sandbox_globals &operator=(s_sandbox_globals &); /* compiler_generated() */
	s_sandbox_globals &operator=(s_sandbox_globals const &); /* compiler_generated() */
};
static_assert(sizeof(s_sandbox_globals) == 1864, "Invalid s_sandbox_globals size");
static_assert(offsetof(s_sandbox_globals, player_edited_object_index) == 0xC, "s_sandbox_globals::player_edited_object_index moved when its reconstructed padding was removed");
static_assert(offsetof(s_sandbox_globals, cursor_boundary_object_index) == 0x72C, "s_sandbox_globals::cursor_boundary_object_index moved when its reconstructed padding was removed");

/* ---------- prototypes */

extern _inline s_sandbox_globals *get_sandbox_globals();

/* ---------- globals */

/* ---------- public code */

inline s_sandbox_globals *get_sandbox_globals() // 0x1067CD80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_sandbox_globals@@YAPAUs_sandbox_globals@@XZ");

	return reinterpret_cast<s_sandbox_globals *>(tls_getd().game_engine_globals->engine_storage);
}

/* ---------- private code */

#endif // __BLAM_GAME_ENGINE_GAME_ENGINE_SANDBOX_HPP__
