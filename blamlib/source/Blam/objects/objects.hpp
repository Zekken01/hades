#ifndef __BLAM_OBJECTS_OBJECTS_HPP__
#define __BLAM_OBJECTS_OBJECTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct c_object_identifier;
struct real_matrix4x3;
struct real_rgb_color;
struct real_vector3d;
struct s_damage_owner;
struct s_datum;
struct s_multiplayer_object_properties_definition;
struct s_object_data;
struct s_object_header;
struct s_object_header_block_reference;
struct s_object_marker;
struct s_object_ordnance_drop_point;
struct s_object_placement_data;
struct s_object_region_information;
struct s_scenario_location;

/* ---------- constants */

/* ---------- definitions */

struct s_object_header_block_reference
{
	short size; // 0x0
	short offset; // 0x2
};
static_assert(sizeof(s_object_header_block_reference) == 4, "Invalid s_object_header_block_reference size");

#pragma pack(push, 4)
struct s_object_placement_data
{
	long definition_index; // 0x0
	c_object_identifier object_identifier; // 0x4
	unsigned long variant_name; // 0xC
	long scenario_datum_index; // 0x10
	unsigned char bsp_placement_policy; // 0x14
	unsigned char __pad0[3]; // 0x15
	unsigned long placement_flags; // 0x18
	real_point3d relative_position; // 0x1C
	real_vector3d forward; // 0x28
	real_vector3d up; // 0x34
	real_vector3d translational_velocity; // 0x40
	real_vector3d angular_velocity; // 0x4C
	float scale; // 0x58
	s_damage_owner damage_owner1; // 0x5C
	s_damage_owner damage_owner2; // 0x68
	unsigned long valid_change_colors; // 0x74
	s_static_array<real_rgb_color,5> change_colors; // 0x78
	long ordnance_drop_point_count; // 0xB4
	s_static_array<s_object_ordnance_drop_point,16> ordnance_drop_points; // 0xB8
	long field_138; // 0x138
	unsigned short valid_damage_constraints1; // 0x13C
	unsigned short valid_damage_constraints2; // 0x13E
	short field_140; // 0x140
	short field_142; // 0x142
	unsigned char __pad1[4]; // 0x144
	s_scenario_location location; // 0x148
	unsigned char __pad2[2]; // 0x14A
	unsigned long parent_object_index; // 0x14C
	unsigned long child_name; // 0x150
	unsigned long child_marker_name; // 0x154
	s_multiplayer_object_properties_definition multiplayer_properties; // 0x158
	s_object_placement_data(s_object_placement_data &); /* compiler_generated() */
	s_object_placement_data(s_object_placement_data const &); /* compiler_generated() */
	_inline s_object_placement_data(); /* compiler_generated() */
	s_object_placement_data &operator=(s_object_placement_data &); /* compiler_generated() */
	s_object_placement_data &operator=(s_object_placement_data const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_object_placement_data) == 396, "Invalid s_object_placement_data size");

struct s_object_data
{
	long definition_index; // 0x0
	c_flags<enum e_object_flags,long> object_flags; // 0x4
	unsigned long extra_object_state; // 0x8
	long next_object_index; // 0xC
	long first_child_object_index; // 0x10
	long parent_object_index; // 0x14
	unsigned char parent_node_index; // 0x18
	unsigned char inhibited_flags; // 0x19
	short scenario_datum_index; // 0x1A
	short map_variant_index; // 0x1C
	s_scenario_location location; // 0x1E
	real_point3d bounding_sphere_center; // 0x20
	float bounding_sphere_radius; // 0x2C
	real_point3d collision_sphere_center; // 0x30
	float collision_sphere_radius; // 0x3C
	real_point3d attached_bounds_sphere_center; // 0x40
	float attached_bounds_sphere_radius; // 0x4C
	long first_cluster_reference_index; // 0x50
	real_point3d relative_position; // 0x54
	real_vector3d forward; // 0x60
	real_vector3d up; // 0x6C
	real_vector3d transitional_velocity; // 0x78
	real_vector3d angular_velocity; // 0x84
	float scale; // 0x90
	c_object_identifier object_identifier; // 0x94
	short name_index; // 0x9C
	char bsp_placement_policy; // 0x9E
	char keyframed_object_collision_damage_ticks; // 0x9F
	long havok_component_index; // 0xA0
	long local_physics_space_object_index; // 0xA4
	long last_motion_time; // 0xA8
	unsigned long physics_flags; // 0xAC
	unsigned char physics_deactivation_count; // 0xB0
	unsigned char physically_attached_node; // 0xB1
	unsigned char phantom_power_scale; // 0xB2
	unsigned char phantom_speed_scale; // 0xB3
	short in_water_ticks; // 0xB4
	char environment_interpenetration_ticks; // 0xB6
	unsigned char brittle_collision_damage_timer; // 0xB7
	short scale_interpolation_ticks; // 0xB8
	char variant_index; // 0xBA
	unsigned char ai_flags; // 0xBB
	unsigned long melee_damage_unique_identifier; // 0xBC
	s_damage_owner damage_owner; // 0xC0
	short bsp2E4_datum_index; // 0xCC
	char created_at_rest; // 0xCE
	unsigned char clusters_touched_on_connection; // 0xCF
	long simulation_object_glue_index; // 0xD0
	short simulation_unknown_team_index; // 0xD4
	unsigned char simulation_flags; // 0xD6
	char child_variant_index; // 0xD7
	long unknown_simulation_ticks; // 0xD8
	real_vector3d unknown_simulation_position; // 0xDC
	long first_widget_index; // 0xE8
	short destroyed_constraints; // 0xEC
	short loosened_constraints; // 0xEE
	float maximum_body_vitality; // 0xF0
	float maximum_shield_vitality; // 0xF4
	float shield_charge_delay; // 0xF8
	float body_vitality; // 0xFC
	float shield_vitality; // 0x100
	float current_body_damage; // 0x104
	float current_shield_damage; // 0x108
	float recent_body_damage; // 0x10C
	float recent_shield_damage; // 0x110
	float shield_impact_current_body_damage; // 0x114
	float shield_impact_current_shield_damage; // 0x118
	short shield_stun_ticks; // 0x11C
	short body_stun_ticks; // 0x11E
	unsigned long damage_flags; // 0x120
	char damaged_explosion_timer; // 0x124
	char body_damage_delay_ticks; // 0x125
	char shield_impact_decay_timer; // 0x126
	unsigned char recycling_flags; // 0x127
	long next_recycling_object_index; // 0x128
	long recycling_time; // 0x12C
	long parent_recycling_group; // 0x130
	long next_recycling_group_member; // 0x134
	long next_sync_action_participant_index; // 0x138
	long sync_action_name; // 0x13C
	long sync_animation_id; // 0x140
	long ai_sync_action_arranger_index; // 0x144
	short render_flags; // 0x148
	s_object_header_block_reference original_node_orientations; // 0x14A
	s_object_header_block_reference node_orientations; // 0x14E
	s_object_header_block_reference node_matrices; // 0x152
	s_object_header_block_reference region_information; // 0x156
	s_object_header_block_reference attachments; // 0x15A
	s_object_header_block_reference damage_sections; // 0x15E
	s_object_header_block_reference change_colors; // 0x162
	s_object_header_block_reference animation; // 0x166
	s_object_header_block_reference multiplayer; // 0x16A
	short first_extension_offset; // 0x16E
	long air_probe_index; // 0x170
	long air_probe_index2; // 0x174
	s_object_data(s_object_data &); /* compiler_generated() */
	s_object_data(s_object_data const &); /* compiler_generated() */
	s_object_data(); /* compiler_generated() */
	s_object_data &operator=(s_object_data &); /* compiler_generated() */
	s_object_data &operator=(s_object_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_object_data) == 376, "Invalid s_object_data size");

struct s_object_header :
	public s_datum
{
	c_flags<enum e_object_datum_flags,unsigned char> flags; // 0x2
	c_enum<enum e_object_type,char> type; // 0x3
	short cluster; // 0x4
	short data_size; // 0x6
	long pool_handle; // 0x8
	s_object_data *data; // 0xC
	s_object_header(s_object_header &); /* compiler_generated() */
	s_object_header(s_object_header const &); /* compiler_generated() */
	s_object_header(); /* compiler_generated() */
	s_object_header &operator=(s_object_header &); /* compiler_generated() */
	s_object_header &operator=(s_object_header const &); /* compiler_generated() */
};
static_assert(sizeof(s_object_header) == 16, "Invalid s_object_header size");

struct s_object_region_information
{
	char variant_permutation_index; // 0x0
	char state; // 0x1
	unsigned char property_flags; // 0x2
	long unknown_index; // 0x4
};
static_assert(sizeof(s_object_region_information) == 8, "Invalid s_object_region_information size");
static_assert(offsetof(s_object_region_information, unknown_index) == 0x4, "s_object_region_information::unknown_index moved when its reconstructed padding was removed");

struct s_object_marker
{
	short node_index; // 0x0
	real_matrix4x3 local_to_world; // 0x4
	real_matrix4x3 world_matrix; // 0x38
	float scale; // 0x6C
};
static_assert(sizeof(s_object_marker) == 112, "Invalid s_object_marker size");
static_assert(offsetof(s_object_marker, local_to_world) == 0x4, "s_object_marker::local_to_world moved when its reconstructed padding was removed");

/* ---------- prototypes */

extern c_data_array<s_object_header> *object_headers_get();
extern s_object_header *object_header_get(unsigned long object_index);
extern s_object_data *object_get(unsigned long object_index);
extern __int32 object_choose_variant(unsigned long object_index, unsigned long variant_name);
extern __int32 object_lookup_variant_index_from_name(__int32 tag_index, unsigned long variant_name);
extern unsigned long object_get_variant_name(long object_index);

extern "C" _inline e_object_type object_get_type(long object_index);
extern "C" _inline e_object_type object_get_type(long object_index);
extern "C" _inline e_object_type object_get_type(long object_index);
extern "C" _inline e_object_type object_get_type(long object_index);
extern "C" _inline e_object_type object_get_type(long object_index);
extern "C" _inline e_object_type object_get_type(long object_index);
extern "C" _inline e_object_type object_get_type(long object_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

// The same function, inlined into 12 other translation units: 0x10AB5D10, 0x10A770C0, 0x10A52F20, 0x10A442D0, 0x10954540, 0x107EB220, 0x107A9130, 0x107954E0, 0x106D6E40, 0x106A0F90, 0x1069EA40, 0x10F0C610

// The same function, inlined into 1 other translation unit: 0x1069EA90

extern e_object_type _sub_10CA98A0(long);
// The same function, inlined into 6 other translation units: 0x10A6F570, 0x10A556F0, 0x107C2080, 0x107B07B0, 0x106D7DD0, 0x1069FDC0
extern "C" _inline e_object_type object_get_type(long object_index) // 0x10CA98A0
{
	// object_get_type
	// long object_index;
	todo("implement");
	e_object_type __result = _sub_10CA98A0(object_index);
	return __result;
}

#endif // __BLAM_OBJECTS_OBJECTS_HPP__
