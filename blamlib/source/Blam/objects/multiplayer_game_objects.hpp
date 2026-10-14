#ifndef __BLAM_OBJECTS_MULTIPLAYER_GAME_OBJECTS_HPP__
#define __BLAM_OBJECTS_MULTIPLAYER_GAME_OBJECTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_matrix4x3;
struct s_multiplayer_object_boundary_geometry_data;
struct s_multiplayer_object_boundary_shader_definition;
struct s_multiplayer_object_definition;
struct s_multiplayer_object_properties;
struct s_multiplayer_object_properties_definition;
struct s_tag_reference;

/* ---------- constants */

enum e_multiplayer_object_type
{
	_object_multiplayer_type_ordinary = 0,
	_object_multiplayer_type_weapon,
	_object_multiplayer_type_grenade,
	_object_multiplayer_type_projectile,
	_object_multiplayer_type_powerup,
	_object_multiplayer_type_equipment,
	_object_multiplayer_type_light_land_vehicle,
	_object_multiplayer_type_heavy_land_vehicle,
	_object_multiplayer_type_flying_vehicle,
	_object_multiplayer_type_teleporter_2way,
	_object_multiplayer_type_teleporter_sender,
	_object_multiplayer_type_teleporter_receiver,
	_object_multiplayer_type_player_spawn_location,
	_object_multiplayer_type_player_respawn_zone,
	_object_multiplayer_type_hold_spawn_objective,
	_object_multiplayer_type_capture_spawn_objective,
	_object_multiplayer_type_hold_destination_objective,
	_object_multiplayer_type_capture_destination_objective,
	_object_multiplayer_type_hill_objective,
	_object_multiplayer_type_infection_haven_objective,
	_object_multiplayer_type_territory_objective,
	_object_multiplayer_type_vip_boundary_objective,
	_object_multiplayer_type_vip_destination_objective,
	_object_multiplayer_type_juggernaut_destination_objective,
	k_number_of_multiplayer_object_types,
};

enum e_multiplayer_object_boundary_shape
{
	_multiplayer_object_boundary_shape_none = 0,
	_multiplayer_object_boundary_shape_sphere,
	_multiplayer_object_boundary_shape_cylinder,
	_multiplayer_object_boundary_shape_box,
	k_number_of_multiplayer_object_boundary_shapes,
};

/* ---------- definitions */

#pragma pack(push, 4)
struct s_multiplayer_object_properties_definition
{
	c_enum<enum e_game_engine_symmetric_placement,long> symmetry; // 0x0
	c_flags<enum e_game_engine_flags,unsigned short> engine_flags; // 0x4
	c_enum<enum e_multiplayer_team_designator,short> team_designator; // 0x6
	unsigned char spawn_sequence; // 0x8
	unsigned char runtime_minimum; // 0x9
	unsigned char runtime_maximum; // 0xA
	c_enum<enum e_multiplayer_object_placement_spawn_flags,unsigned char> spawn_flags; // 0xB
	short spawn_time; // 0xC
	short abandon_time; // 0xE
	c_flags<enum e_multiplayer_object_teleporter_flags,unsigned char> teleporter_passability; // 0x10
	c_enum<enum e_multiplayer_object_boundary_shape,char> boundary_shape; // 0x11
	c_enum<enum e_multiplayer_teleporter_channel,char> teleporter_channel; // 0x12
	unsigned char : 8; // 0x13  // hades: unnamed bit-fields, not padding members - the original leaves 0x13-0x15 alone when it zero-initializes this
	unsigned short : 16; // 0x14
	short attached_name; // 0x16
	long field_18; // 0x18  // hades: scalars, not a padding array - an array would start its own zeroing run
	long field_1C; // 0x1C
	float boundary_width; // 0x20
	float boundary_length; // 0x24
	float boundary_top; // 0x28
	float boundary_bottom; // 0x2C
	// hades: special members left implicit (s_object_placement_data is aggregate-initialized member by member)
	long field_30; // 0x30
};
#pragma pack(pop)
static_assert(sizeof(s_multiplayer_object_properties_definition) == 52, "Invalid s_multiplayer_object_properties_definition size");

struct s_multiplayer_object_boundary_geometry_data
{
	e_multiplayer_object_boundary_shape shape; // 0x0
	long render_method_definition_index; // 0x4
	float radius_width; // 0x8
	float length; // 0xC
	float top; // 0x10
	float bottom; // 0x14
	real_matrix4x3 matrix; // 0x18
	float bounding_radius; // 0x4C
};
static_assert(sizeof(s_multiplayer_object_boundary_geometry_data) == 80, "Invalid s_multiplayer_object_boundary_geometry_data size");

struct s_multiplayer_object_boundary_shader_definition
{
	s_tag_reference standard_shader; // 0x0
	s_tag_reference opaque_shader; // 0x10
};
static_assert(sizeof(s_multiplayer_object_boundary_shader_definition) == 32, "Invalid s_multiplayer_object_boundary_shader_definition size");

#pragma pack(push, 4)
struct s_multiplayer_object_definition
{
	c_flags<enum e_game_engine_flags,unsigned short> engine_flags; // 0x0
	c_enum<enum e_multiplayer_object_type,char> type; // 0x2
	c_flags<enum e_multiplayer_object_teleporter_flags,unsigned char> teleporter_passability; // 0x3
	c_flags<enum e_multiplayer_object_flags,unsigned short> flags; // 0x4
	c_enum<enum e_multiplayer_object_boundary_shape,char> boundary_shape; // 0x6
	c_enum<enum e_multiplayer_object_spawn_timer_type,char> spawn_timer_type; // 0x7
	short default_spawn_time; // 0x8
	short default_abandon_time; // 0xA
	float boundary_width; // 0xC
	float boundary_length; // 0x10
	float boundary_top; // 0x14
	float boundary_bottom; // 0x18
	float unknown1; // 0x1C
	float unknown2; // 0x20
	float unknown3; // 0x24
	unsigned long boundary_center_marker; // 0x28
	unsigned long spawned_object_marker_name; // 0x2C
	s_tag_reference spawned_object; // 0x30
	unsigned long nyi_boundary_material; // 0x40
	s_multiplayer_object_boundary_shader_definition boundary_shaders[4]; // 0x44
	s_multiplayer_object_definition(s_multiplayer_object_definition &); /* compiler_generated() */
	s_multiplayer_object_definition(s_multiplayer_object_definition const &); /* compiler_generated() */
	s_multiplayer_object_definition(); /* compiler_generated() */
	s_multiplayer_object_definition &operator=(s_multiplayer_object_definition &); /* compiler_generated() */
	s_multiplayer_object_definition &operator=(s_multiplayer_object_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_multiplayer_object_definition) == 196, "Invalid s_multiplayer_object_definition size");

#pragma pack(push, 4)
struct s_multiplayer_object_properties
{
	c_flags<enum e_multiplayer_object_flags,unsigned char> definition_flags; // 0x0
	c_flags<enum e_multiplayer_object_flags,unsigned char> placement_flags; // 0x1
	c_enum<enum e_multiplayer_object_type,char> multiplayer_object_type; // 0x2
	c_enum<enum e_multiplayer_object_boundary_shape,char> boundary_shape; // 0x3
	c_enum<enum e_multiplayer_object_remapping_policy,char> remapping_policy; // 0x4
	c_enum<enum e_multiplayer_teleporter_channel,unsigned char> teleporter_channel; // 0x5
	c_enum<enum e_multiplayer_object_teleporter_flags,unsigned char> teleporter_flags; // 0x6
	c_enum<enum e_game_engine_symmetric_placement,char> symmetry; // 0x7
	c_flags<enum e_game_engine_flags,unsigned short> engine_flags; // 0x8
	c_flags<enum e_multiplayer_team_designator,short> team_designator; // 0xA
	char spare_clips; // 0xC
	char runtime_minimum; // 0xD
	char runtime_maximum; // 0xE
	char spawn_timer_mode; // 0xF
	short spawn_time; // 0x10
	short abandon_time; // 0x12
	float boundry_width; // 0x14
	float boundry_length; // 0x18
	float boundry_top; // 0x1C
	float boundry_bottom; // 0x20
	float spawn_weight_base; // 0x24
	float spawn_bias; // 0x28
	float spawn_weight_alt1; // 0x2C
	float spawn_weight_alt2; // 0x30
	unsigned char __pad0[4]; // 0x34
	long teleporter_marker; // 0x38
	unsigned char __pad1[8]; // 0x3C
	long primary_render_method_index; // 0x44
	long secondary_render_method_index; // 0x48
	s_multiplayer_object_properties(s_multiplayer_object_properties &); /* compiler_generated() */
	s_multiplayer_object_properties(s_multiplayer_object_properties const &); /* compiler_generated() */
	s_multiplayer_object_properties(); /* compiler_generated() */
	s_multiplayer_object_properties &operator=(s_multiplayer_object_properties &); /* compiler_generated() */
	s_multiplayer_object_properties &operator=(s_multiplayer_object_properties const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_multiplayer_object_properties) == 76, "Invalid s_multiplayer_object_properties size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_OBJECTS_MULTIPLAYER_GAME_OBJECTS_HPP__
