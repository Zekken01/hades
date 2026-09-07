#ifndef __BLAM_SCENARIO_SCENARIO_DEFINITIONS_HPP__
#define __BLAM_SCENARIO_SCENARIO_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/squads.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct c_object_identifier;
struct real_bounds;
struct real_euler_angles2d;
struct real_euler_angles3d;
struct real_plane3d;
struct real_point2d;
struct real_quaternion;
struct real_vector3d;
struct s_cluster_reference;
struct s_hs_global;
struct s_hs_script;
struct s_hs_syntax_node;
struct s_multiplayer_object_properties_definition;
struct s_scenario;
struct s_scenario_acoustics_ambience;
struct s_scenario_acoustics_environment;
struct s_scenario_acoustics_palette_entry;
struct s_scenario_ai_deafening_encoded_pas;
struct s_scenario_arg_device;
struct s_scenario_background_textures;
struct s_scenario_biped;
struct s_scenario_bsp_cluster_to_room_bounds_mapping;
struct s_scenario_bsp_cluster_to_room_index_mapping;
struct s_scenario_campaign_player;
struct s_scenario_control;
struct s_scenario_crate;
struct s_scenario_cutscene_camera_point;
struct s_scenario_decal;
struct s_scenario_decal_palette_entry;
struct s_scenario_detail_object_palette_entry;
struct s_scenario_device;
struct s_scenario_device_group;
struct s_scenario_door_encoded_pas;
struct s_scenario_editor_folder;
struct s_scenario_effect_scenery;
struct s_scenario_encoded_room_distances;
struct s_scenario_equipment;
struct s_scenario_game_portal_to_door_occluder_mapping;
struct s_scenario_game_portal_to_portal_mapping;
struct s_scenario_giant;
struct s_scenario_kill_trigger_volume;
struct s_scenario_light_volume;
struct s_scenario_location;
struct s_scenario_machine;
struct s_scenario_object;
struct s_scenario_object_arg_device_data;
struct s_scenario_object_control_data;
struct s_scenario_object_crate_data;
struct s_scenario_object_data;
struct s_scenario_object_device_data;
struct s_scenario_object_equipment_data;
struct s_scenario_object_giant_data;
struct s_scenario_object_light_volume_data;
struct s_scenario_object_machine_data;
struct s_scenario_object_name;
struct s_scenario_object_node_orientations;
struct s_scenario_object_node_orientations_bit_vector;
struct s_scenario_object_node_orientations_orientations;
struct s_scenario_object_parent_identifier;
struct s_scenario_object_pathfinding_reference;
struct s_scenario_object_permutation_data;
struct s_scenario_object_scenery_data;
struct s_scenario_object_sound_scenery_data;
struct s_scenario_object_unit_data;
struct s_scenario_object_weapon_data;
struct s_scenario_placement;
struct s_scenario_player;
struct s_scenario_profile;
struct s_scenario_recorded_animation;
struct s_scenario_room_door_portal_encoded_pas;
struct s_scenario_sandbox_object;
struct s_scenario_scenery;
struct s_scenario_sky_reference;
struct s_scenario_soft_ceiling;
struct s_scenario_sound_scenery;
struct s_scenario_structure_bsp_atlas;
struct s_scenario_structure_device_portal_association;
struct s_scenario_structure_portal_device_mapping;
struct s_scenario_style_palette_entry;
struct s_scenario_terminal;
struct s_scenario_trigger_volume;
struct s_scenario_trigger_volume_point;
struct s_scenario_trigger_volume_triangle;
struct s_scenario_unit;
struct s_scenario_vehicle;
struct s_scenario_weapon;
struct s_scenario_zone_set;
struct s_scenario_zone_set_audibility;
struct s_scenario_zone_set_bsp_bits;
struct s_scenario_zone_set_bsp_checksum;
struct s_scenario_zone_set_bsp_pvs;
struct s_scenario_zone_set_bsp_pvs_unknown;
struct s_scenario_zone_set_bsp_seam_cluster_mapping;
struct s_scenario_zone_set_cluster_pvs;
struct s_scenario_zone_set_cluster_pvs_bit_vector;
struct s_scenario_zone_set_cluster_sky_reference;
struct s_scenario_zone_set_pvs;
struct s_scenario_zone_set_switch_trigger_volume;
struct s_squad_definition;
struct s_squad_group_definition;
struct s_starting_weapon_info;
struct s_tag_block;
struct s_tag_data;
struct s_tag_reference;
union tag_string;

/* ---------- constants */

enum e_scenario_type
{
	_scenario_type_campaign = 0,
	_scenario_type_multiplayer,
	_scenario_type_main_menu,
	k_number_of_scenario_types,
};

/* ---------- definitions */

struct c_object_identifier
{
	unsigned long unique_id; // 0x0
	c_tag_block_index<s_scenario_structure_bsp_reference,short> origin_bsp_index; // 0x4
	c_enum<enum e_object_type,char> type; // 0x6
	c_enum<enum e_scenario_object_source,char> source; // 0x7
	c_object_identifier(c_object_identifier &); /* compiler_generated() */
	_inline c_object_identifier(c_object_identifier const &__that); /* compiler_generated() */
	_inline c_object_identifier(); /* compiler_generated() */
	c_object_identifier &operator=(c_object_identifier &); /* compiler_generated() */
	c_object_identifier &operator=(c_object_identifier const &); /* compiler_generated() */
};
static_assert(sizeof(c_object_identifier) == 8, "Invalid c_object_identifier size");

#pragma pack(push, 4)
struct s_scenario_object_name
{
	tag_string name; // 0x0
	c_enum<enum e_object_type,short> object_type; // 0x20
	short scenario_datum_index; // 0x22
	s_scenario_object_name(s_scenario_object_name &); /* compiler_generated() */
	s_scenario_object_name(s_scenario_object_name const &); /* compiler_generated() */
	s_scenario_object_name(); /* compiler_generated() */
	s_scenario_object_name &operator=(s_scenario_object_name &); /* compiler_generated() */
	s_scenario_object_name &operator=(s_scenario_object_name const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_object_name) == 36, "Invalid s_scenario_object_name size");

struct s_scenario_location
{
	s_cluster_reference cluster_reference; // 0x0
};
static_assert(sizeof(s_scenario_location) == 2, "Invalid s_scenario_location size");

// s_scenario_structure_bsp_reference is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

#pragma pack(push, 4)
struct s_scenario_sky_reference
{
	s_tag_reference sky_object; // 0x0
	c_tag_block_index<s_scenario_object_name,short> name; // 0x10
	c_flags<enum e_scenario_structure_bsp_reference,unsigned short> active_bsps; // 0x12
	s_scenario_sky_reference(s_scenario_sky_reference &); /* compiler_generated() */
	s_scenario_sky_reference(s_scenario_sky_reference const &); /* compiler_generated() */
	s_scenario_sky_reference(); /* compiler_generated() */
	s_scenario_sky_reference &operator=(s_scenario_sky_reference &); /* compiler_generated() */
	s_scenario_sky_reference &operator=(s_scenario_sky_reference const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_sky_reference) == 20, "Invalid s_scenario_sky_reference size");

struct s_scenario_zone_set_bsp_checksum
{
	unsigned long bsp_checksum; // 0x0
};
static_assert(sizeof(s_scenario_zone_set_bsp_checksum) == 4, "Invalid s_scenario_zone_set_bsp_checksum size");

struct s_scenario_zone_set_cluster_pvs_bit_vector
{
	unsigned long value; // 0x0
};
static_assert(sizeof(s_scenario_zone_set_cluster_pvs_bit_vector) == 4, "Invalid s_scenario_zone_set_cluster_pvs_bit_vector size");

#pragma pack(push, 4)
struct s_scenario_zone_set_bsp_bits
{
	c_tag_block<s_scenario_zone_set_cluster_pvs_bit_vector> bits; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_zone_set_bsp_bits) == 12, "Invalid s_scenario_zone_set_bsp_bits size");

#pragma pack(push, 4)
struct s_scenario_zone_set_cluster_pvs
{
	c_tag_block<s_scenario_zone_set_bsp_bits> cluster_pvs_bit_vectors; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_zone_set_cluster_pvs) == 12, "Invalid s_scenario_zone_set_cluster_pvs size");

struct s_scenario_zone_set_cluster_sky_reference
{
	c_tag_block_index<s_scenario_sky_reference,char> sky; // 0x0
	s_scenario_zone_set_cluster_sky_reference(s_scenario_zone_set_cluster_sky_reference &); /* compiler_generated() */
	s_scenario_zone_set_cluster_sky_reference(s_scenario_zone_set_cluster_sky_reference const &); /* compiler_generated() */
	s_scenario_zone_set_cluster_sky_reference(); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_zone_set_cluster_sky_reference) == 1, "Invalid s_scenario_zone_set_cluster_sky_reference size");

struct s_scenario_zone_set_bsp_seam_cluster_mapping
{
	c_tag_block<unsigned char> clusters; // 0x0
	c_tag_block<s_cluster_reference> root_clusters; // 0xC
	c_tag_block<s_cluster_reference> attached_clusters; // 0x18
	c_tag_block<s_cluster_reference> connected_clusters; // 0x24
};
static_assert(sizeof(s_scenario_zone_set_bsp_seam_cluster_mapping) == 48, "Invalid s_scenario_zone_set_bsp_seam_cluster_mapping size");

#pragma pack(push, 4)
struct s_scenario_zone_set_bsp_pvs
{
	c_tag_block<s_scenario_zone_set_cluster_pvs> cluster_pvs; // 0x0
	c_tag_block<s_scenario_zone_set_cluster_pvs> cluster_pvs_doors_closed; // 0xC
	c_tag_block<s_scenario_zone_set_cluster_sky_reference> cluster_skies; // 0x18
	c_tag_block<s_scenario_zone_set_cluster_sky_reference> cluster_visible_skies; // 0x24
	c_tag_block<s_scenario_zone_set_bsp_pvs_unknown> unknown1; // 0x30
	c_tag_block<s_scenario_zone_set_bsp_pvs_unknown> unknown2; // 0x3C
	c_tag_block<s_scenario_zone_set_bsp_seam_cluster_mapping> cluster_mapping; // 0x48
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_zone_set_bsp_pvs) == 84, "Invalid s_scenario_zone_set_bsp_pvs size");

#pragma pack(push, 4)
struct s_scenario_structure_device_portal_association
{
	c_object_identifier device_id; // 0x0
	short first_game_portal_index; // 0x8
	unsigned short game_portal_count; // 0xA
	s_scenario_structure_device_portal_association(s_scenario_structure_device_portal_association &); /* compiler_generated() */
	s_scenario_structure_device_portal_association(s_scenario_structure_device_portal_association const &); /* compiler_generated() */
	s_scenario_structure_device_portal_association(); /* compiler_generated() */
	s_scenario_structure_device_portal_association &operator=(s_scenario_structure_device_portal_association &); /* compiler_generated() */
	s_scenario_structure_device_portal_association &operator=(s_scenario_structure_device_portal_association const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_structure_device_portal_association) == 12, "Invalid s_scenario_structure_device_portal_association size");

struct s_scenario_game_portal_to_portal_mapping
{
	short portal_index; // 0x0
};
static_assert(sizeof(s_scenario_game_portal_to_portal_mapping) == 2, "Invalid s_scenario_game_portal_to_portal_mapping size");

struct s_scenario_structure_portal_device_mapping
{
	c_tag_block<s_scenario_structure_device_portal_association> device_portal_associations; // 0x0
	c_tag_block<s_scenario_game_portal_to_portal_mapping> game_portal_to_portal_map; // 0xC
};
static_assert(sizeof(s_scenario_structure_portal_device_mapping) == 24, "Invalid s_scenario_structure_portal_device_mapping size");

#pragma pack(push, 4)
struct s_scenario_zone_set_pvs
{
	unsigned long structure_bsp_mask; // 0x0
	short version; // 0x4
	c_flags<enum e_scenario_zone_set_pvs_flags,unsigned short> flags; // 0x6
	c_tag_block<s_scenario_zone_set_bsp_checksum> bsp_checksums; // 0x8
	c_tag_block<s_scenario_zone_set_bsp_pvs> structure_bsp_pvs; // 0x14
	c_tag_block<s_scenario_structure_portal_device_mapping> portal_to_device_mappings; // 0x20
	s_scenario_zone_set_pvs(s_scenario_zone_set_pvs &); /* compiler_generated() */
	s_scenario_zone_set_pvs(s_scenario_zone_set_pvs const &); /* compiler_generated() */
	s_scenario_zone_set_pvs(); /* compiler_generated() */
	s_scenario_zone_set_pvs &operator=(s_scenario_zone_set_pvs &); /* compiler_generated() */
	s_scenario_zone_set_pvs &operator=(s_scenario_zone_set_pvs const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_zone_set_pvs) == 44, "Invalid s_scenario_zone_set_pvs size");

struct s_scenario_ai_deafening_encoded_pas
{
	long encoded_data; // 0x0
};
static_assert(sizeof(s_scenario_ai_deafening_encoded_pas) == 4, "Invalid s_scenario_ai_deafening_encoded_pas size");

struct s_scenario_encoded_room_distances
{
	char encoded_data; // 0x0
};
static_assert(sizeof(s_scenario_encoded_room_distances) == 1, "Invalid s_scenario_encoded_room_distances size");

struct s_scenario_game_portal_to_door_occluder_mapping
{
	long first_door_occluder_index; // 0x0
	long door_occluder_count; // 0x4
};
static_assert(sizeof(s_scenario_game_portal_to_door_occluder_mapping) == 8, "Invalid s_scenario_game_portal_to_door_occluder_mapping size");

struct s_scenario_bsp_cluster_to_room_bounds_mapping
{
	long first_room_index; // 0x0
	long room_index_count; // 0x4
};
static_assert(sizeof(s_scenario_bsp_cluster_to_room_bounds_mapping) == 8, "Invalid s_scenario_bsp_cluster_to_room_bounds_mapping size");

struct s_scenario_bsp_cluster_to_room_index_mapping
{
	short room_index; // 0x0
};
static_assert(sizeof(s_scenario_bsp_cluster_to_room_index_mapping) == 2, "Invalid s_scenario_bsp_cluster_to_room_index_mapping size");

#pragma pack(push, 4)
struct s_scenario_zone_set_audibility
{
	long door_portal_count; // 0x0
	long room_count; // 0x4
	real_bounds room_distance_bounds; // 0x8
	c_tag_block<s_scenario_door_encoded_pas> encoded_door_pas; // 0x10
	c_tag_block<s_scenario_room_door_portal_encoded_pas> room_door_portal_encoded_pas; // 0x1C
	c_tag_block<s_scenario_ai_deafening_encoded_pas> ai_deafening_pas; // 0x28
	c_tag_block<s_scenario_encoded_room_distances> room_distances; // 0x34
	c_tag_block<s_scenario_game_portal_to_door_occluder_mapping> game_portal_to_door_occluder_mapping; // 0x40
	c_tag_block<s_scenario_bsp_cluster_to_room_bounds_mapping> bsp_cluster_to_room_bounds; // 0x4C
	c_tag_block<s_scenario_bsp_cluster_to_room_index_mapping> bsp_cluster_to_room_indices; // 0x58
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_zone_set_audibility) == 100, "Invalid s_scenario_zone_set_audibility size");

struct s_scenario_zone_set
{
	unsigned long name; // 0x0
	c_tag_block_index<s_scenario_zone_set_pvs,long> pvs_index; // 0x4
	c_flags<enum e_scenario_zone_set_flags,long> flags; // 0x8
	c_tag_block_flags<s_scenario_structure_bsp_reference,long> bsp_zone_flags; // 0xC
	c_tag_block_flags<s_scenario_structure_bsp_reference,long> design_zone_flags; // 0x10
	c_tag_block_flags<s_scenario_structure_bsp_reference,long> runtime_bsp_zone_flags; // 0x14
	c_tag_block_flags<s_scenario_structure_bsp_reference,long> runtime_design_zone_flags; // 0x18
	c_tag_block_index<s_scenario_zone_set,long> hint_previous_zone_index; // 0x1C
	c_tag_block_index<s_scenario_zone_set_audibility,long> audibility_index; // 0x20
	s_scenario_zone_set(s_scenario_zone_set &); /* compiler_generated() */
	s_scenario_zone_set(s_scenario_zone_set const &); /* compiler_generated() */
	s_scenario_zone_set(); /* compiler_generated() */
	s_scenario_zone_set &operator=(s_scenario_zone_set &); /* compiler_generated() */
	s_scenario_zone_set &operator=(s_scenario_zone_set const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_zone_set) == 36, "Invalid s_scenario_zone_set size");

struct s_scenario_structure_bsp_atlas
{
	unsigned long name; // 0x0
	c_tag_block_flags<s_scenario_structure_bsp_reference,long> bsp_reference; // 0x4
	c_tag_block_flags<s_scenario_structure_bsp_reference,long> connected_bsps; // 0x8
	s_scenario_structure_bsp_atlas(s_scenario_structure_bsp_atlas &); /* compiler_generated() */
	s_scenario_structure_bsp_atlas(s_scenario_structure_bsp_atlas const &); /* compiler_generated() */
	s_scenario_structure_bsp_atlas(); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_structure_bsp_atlas) == 12, "Invalid s_scenario_structure_bsp_atlas size");

struct s_scenario_campaign_player
{
	unsigned long player_representation; // 0x0
};
static_assert(sizeof(s_scenario_campaign_player) == 4, "Invalid s_scenario_campaign_player size");

// s_scenario_object_palette_entry is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

struct s_scenario_object_node_orientations_bit_vector
{
	unsigned char data; // 0x0
};
static_assert(sizeof(s_scenario_object_node_orientations_bit_vector) == 1, "Invalid s_scenario_object_node_orientations_bit_vector size");

struct s_scenario_object_node_orientations_orientations
{
	short number; // 0x0
};
static_assert(sizeof(s_scenario_object_node_orientations_orientations) == 2, "Invalid s_scenario_object_node_orientations_orientations size");

#pragma pack(push, 4)
struct s_scenario_object_node_orientations
{
	short node_count; // 0x0
	unsigned char __pad0[2]; // 0x2
	c_tag_block<s_scenario_object_node_orientations_bit_vector> bit_vector; // 0x4
	c_tag_block<s_scenario_object_node_orientations_orientations> orientations; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_object_node_orientations) == 28, "Invalid s_scenario_object_node_orientations size");

struct s_scenario_object_parent_identifier
{
	unsigned char __pad0[2]; // 0x0
	c_tag_block_index<s_scenario_object_name,short> parent_object_name; // 0x2
	unsigned long parent_name; // 0x4
	unsigned long parent_marker; // 0x8
	s_scenario_object_parent_identifier(s_scenario_object_parent_identifier &); /* compiler_generated() */
	s_scenario_object_parent_identifier(s_scenario_object_parent_identifier const &); /* compiler_generated() */
	s_scenario_object_parent_identifier(); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_parent_identifier) == 12, "Invalid s_scenario_object_parent_identifier size");

#pragma pack(push, 4)
struct s_scenario_device_group
{
	tag_string name; // 0x0
	float initial_value; // 0x20
	c_flags<enum e_scenario_device_group_flags,long> flags; // 0x24
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x28
	s_scenario_device_group(s_scenario_device_group &); /* compiler_generated() */
	s_scenario_device_group(s_scenario_device_group const &); /* compiler_generated() */
	s_scenario_device_group(); /* compiler_generated() */
	s_scenario_device_group &operator=(s_scenario_device_group &); /* compiler_generated() */
	s_scenario_device_group &operator=(s_scenario_device_group const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x2A
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_device_group) == 44, "Invalid s_scenario_device_group size");

struct s_scenario_object_data
{
	c_flags<enum e_scenario_object_placement_flags,long> placement_flags; // 0x0
	real_point3d position; // 0x4
	real_euler_angles3d rotation; // 0x10
	float scale; // 0x1C
	c_tag_block<s_scenario_object_node_orientations> node_orientations; // 0x20
	unsigned char __pad0[2]; // 0x2C
	c_flags<enum e_scenario_structure_bsp_reference,unsigned short> manual_bsp_flags; // 0x2E
	unsigned char __pad1[4]; // 0x30
	c_object_identifier object_id; // 0x34
	c_enum<enum e_scenario_object_bsp_policy,char> bsp_policy; // 0x3C
	unsigned char __pad2[1]; // 0x3D
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x3E
	s_scenario_object_parent_identifier parent_id; // 0x40
	c_flags<enum e_scenario_structure_bsp_reference,unsigned short> bsp_flags; // 0x4C
	s_scenario_object_data(s_scenario_object_data &); /* compiler_generated() */
	s_scenario_object_data(s_scenario_object_data const &); /* compiler_generated() */
	s_scenario_object_data(); /* compiler_generated() */
	s_scenario_object_data &operator=(s_scenario_object_data &); /* compiler_generated() */
	s_scenario_object_data &operator=(s_scenario_object_data const &); /* compiler_generated() */
	unsigned char __pad3[2]; // 0x4E
};
static_assert(sizeof(s_scenario_object_data) == 80, "Invalid s_scenario_object_data size");

#pragma pack(push, 4)
struct s_scenario_object_permutation_data
{
	unsigned long variant; // 0x0
	c_flags<enum e_object_change_color,unsigned char> active_change_colors; // 0x4
	unsigned char __pad0[3]; // 0x5
	unsigned long change_colors[5]; // 0x8
	s_scenario_object_permutation_data(s_scenario_object_permutation_data &); /* compiler_generated() */
	s_scenario_object_permutation_data(s_scenario_object_permutation_data const &); /* compiler_generated() */
	s_scenario_object_permutation_data(); /* compiler_generated() */
	s_scenario_object_permutation_data &operator=(s_scenario_object_permutation_data &); /* compiler_generated() */
	s_scenario_object_permutation_data &operator=(s_scenario_object_permutation_data const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_object_permutation_data) == 28, "Invalid s_scenario_object_permutation_data size");

struct s_scenario_object_pathfinding_reference
{
	c_tag_block_index<s_scenario_structure_bsp_reference,short> bsp; // 0x0
	short pathfinding_object_index; // 0x2
	s_scenario_object_pathfinding_reference(s_scenario_object_pathfinding_reference &); /* compiler_generated() */
	s_scenario_object_pathfinding_reference(s_scenario_object_pathfinding_reference const &); /* compiler_generated() */
	s_scenario_object_pathfinding_reference(); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_pathfinding_reference) == 4, "Invalid s_scenario_object_pathfinding_reference size");

#pragma pack(push, 4)
struct s_scenario_object_scenery_data
{
	c_enum<enum e_scenario_object_pathfinding_policy,short> pathfinding_policy; // 0x0
	c_enum<enum e_scenario_object_lightmapping_policy,short> lightmaping_policy; // 0x2
	c_tag_block<s_scenario_object_pathfinding_reference> pathfinding_references; // 0x4
	s_scenario_object_scenery_data(s_scenario_object_scenery_data &); /* compiler_generated() */
	s_scenario_object_scenery_data(s_scenario_object_scenery_data const &); /* compiler_generated() */
	s_scenario_object_scenery_data(); /* compiler_generated() */
	s_scenario_object_scenery_data &operator=(s_scenario_object_scenery_data &); /* compiler_generated() */
	s_scenario_object_scenery_data &operator=(s_scenario_object_scenery_data const &); /* compiler_generated() */
	unsigned char __pad0[4]; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_object_scenery_data) == 20, "Invalid s_scenario_object_scenery_data size");

struct s_scenario_object_crate_data
{
	c_enum<enum e_scenario_object_pathfinding_policy,short> pathfinding_policy; // 0x0
	c_enum<enum e_scenario_object_lightmapping_policy,short> lightmaping_policy; // 0x2
	c_tag_block<s_scenario_object_pathfinding_reference> pathfinding_references; // 0x4
	s_scenario_object_crate_data(s_scenario_object_crate_data &); /* compiler_generated() */
	s_scenario_object_crate_data(s_scenario_object_crate_data const &); /* compiler_generated() */
	s_scenario_object_crate_data(); /* compiler_generated() */
	s_scenario_object_crate_data &operator=(s_scenario_object_crate_data &); /* compiler_generated() */
	s_scenario_object_crate_data &operator=(s_scenario_object_crate_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_crate_data) == 16, "Invalid s_scenario_object_crate_data size");

struct s_scenario_object_unit_data
{
	float body_vitality_percentage; // 0x0
	c_flags<enum e_scenario_object_unit_flags,long> unit_flags; // 0x4
	s_scenario_object_unit_data(s_scenario_object_unit_data &); /* compiler_generated() */
	s_scenario_object_unit_data(s_scenario_object_unit_data const &); /* compiler_generated() */
	s_scenario_object_unit_data(); /* compiler_generated() */
	s_scenario_object_unit_data &operator=(s_scenario_object_unit_data &); /* compiler_generated() */
	s_scenario_object_unit_data &operator=(s_scenario_object_unit_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_unit_data) == 8, "Invalid s_scenario_object_unit_data size");

struct s_scenario_object_equipment_data
{
	c_flags<enum e_scenario_object_item_flags,long> item_flags; // 0x0
	s_scenario_object_equipment_data(s_scenario_object_equipment_data &); /* compiler_generated() */
	s_scenario_object_equipment_data(s_scenario_object_equipment_data const &); /* compiler_generated() */
	s_scenario_object_equipment_data(); /* compiler_generated() */
	s_scenario_object_equipment_data &operator=(s_scenario_object_equipment_data &); /* compiler_generated() */
	s_scenario_object_equipment_data &operator=(s_scenario_object_equipment_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_equipment_data) == 4, "Invalid s_scenario_object_equipment_data size");

struct s_scenario_object_weapon_data
{
	short rounds_left; // 0x0
	short rounds_loaded; // 0x2
	c_flags<enum e_scenario_object_item_flags,long> item_flags; // 0x4
	s_scenario_object_weapon_data(s_scenario_object_weapon_data &); /* compiler_generated() */
	s_scenario_object_weapon_data(s_scenario_object_weapon_data const &); /* compiler_generated() */
	s_scenario_object_weapon_data(); /* compiler_generated() */
	s_scenario_object_weapon_data &operator=(s_scenario_object_weapon_data &); /* compiler_generated() */
	s_scenario_object_weapon_data &operator=(s_scenario_object_weapon_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_weapon_data) == 8, "Invalid s_scenario_object_weapon_data size");

struct s_scenario_object_device_data
{
	c_tag_block_index<s_scenario_device_group,short> power_group; // 0x0
	c_tag_block_index<s_scenario_device_group,short> position_group; // 0x2
	c_flags<enum e_scenario_object_device_flags,long> device_flags; // 0x4
	s_scenario_object_device_data(s_scenario_object_device_data &); /* compiler_generated() */
	s_scenario_object_device_data(s_scenario_object_device_data const &); /* compiler_generated() */
	s_scenario_object_device_data(); /* compiler_generated() */
	s_scenario_object_device_data &operator=(s_scenario_object_device_data &); /* compiler_generated() */
	s_scenario_object_device_data &operator=(s_scenario_object_device_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_device_data) == 8, "Invalid s_scenario_object_device_data size");

#pragma pack(push, 4)
struct s_scenario_object_machine_data
{
	c_flags<enum e_scenario_object_machine_flags,long> machine_flags; // 0x0
	c_tag_block<s_scenario_object_pathfinding_reference> pathfinding_references; // 0x4
	c_enum<enum e_scenario_object_pathfinding_policy,short> pathfinding_policy; // 0x10
	s_scenario_object_machine_data(s_scenario_object_machine_data &); /* compiler_generated() */
	s_scenario_object_machine_data(s_scenario_object_machine_data const &); /* compiler_generated() */
	s_scenario_object_machine_data(); /* compiler_generated() */
	s_scenario_object_machine_data &operator=(s_scenario_object_machine_data &); /* compiler_generated() */
	s_scenario_object_machine_data &operator=(s_scenario_object_machine_data const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x12
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_object_machine_data) == 20, "Invalid s_scenario_object_machine_data size");

#pragma pack(push, 4)
struct s_scenario_object_arg_device_data
{
	tag_string tap_script_name; // 0x0
	tag_string hold_script_name; // 0x20
	c_tag_block_index<s_hs_script,short> tap_script_index; // 0x40
	c_tag_block_index<s_hs_script,short> hold_script_index; // 0x42
	s_scenario_object_arg_device_data(s_scenario_object_arg_device_data &); /* compiler_generated() */
	s_scenario_object_arg_device_data(s_scenario_object_arg_device_data const &); /* compiler_generated() */
	s_scenario_object_arg_device_data(); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_object_arg_device_data) == 68, "Invalid s_scenario_object_arg_device_data size");

struct s_scenario_object_control_data
{
	c_flags<enum e_scenario_object_control_flags,long> control_flags; // 0x0
	s_scenario_object_control_data(s_scenario_object_control_data &); /* compiler_generated() */
	s_scenario_object_control_data(s_scenario_object_control_data const &); /* compiler_generated() */
	s_scenario_object_control_data(); /* compiler_generated() */
	s_scenario_object_control_data &operator=(s_scenario_object_control_data &); /* compiler_generated() */
	s_scenario_object_control_data &operator=(s_scenario_object_control_data const &); /* compiler_generated() */
	unsigned char __pad0[4]; // 0x4
};
static_assert(sizeof(s_scenario_object_control_data) == 8, "Invalid s_scenario_object_control_data size");

#pragma pack(push, 4)
struct s_scenario_object_sound_scenery_data
{
	c_enum<enum e_scenario_sound_volume_type,long> volume_type; // 0x0
	float height; // 0x4
	real_bounds override_distance_bounds; // 0x8
	angle_bounds override_cone_angle_bounds; // 0x10
	float override_outer_cone_gain; // 0x18
	s_scenario_object_sound_scenery_data(s_scenario_object_sound_scenery_data &); /* compiler_generated() */
	s_scenario_object_sound_scenery_data(s_scenario_object_sound_scenery_data const &); /* compiler_generated() */
	s_scenario_object_sound_scenery_data(); /* compiler_generated() */
	s_scenario_object_sound_scenery_data &operator=(s_scenario_object_sound_scenery_data &); /* compiler_generated() */
	s_scenario_object_sound_scenery_data &operator=(s_scenario_object_sound_scenery_data const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_object_sound_scenery_data) == 28, "Invalid s_scenario_object_sound_scenery_data size");

struct s_scenario_object_giant_data
{
	c_enum<enum e_scenario_object_pathfinding_policy,short> pathfinding_policy; // 0x0
	unsigned char __pad0[2]; // 0x2
	c_tag_block<s_scenario_object_pathfinding_reference> pathfinding_references; // 0x4
	s_scenario_object_giant_data(s_scenario_object_giant_data &); /* compiler_generated() */
	s_scenario_object_giant_data(s_scenario_object_giant_data const &); /* compiler_generated() */
	s_scenario_object_giant_data(); /* compiler_generated() */
	s_scenario_object_giant_data &operator=(s_scenario_object_giant_data &); /* compiler_generated() */
	s_scenario_object_giant_data &operator=(s_scenario_object_giant_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_giant_data) == 16, "Invalid s_scenario_object_giant_data size");

struct s_scenario_object_light_volume_data
{
	c_enum<enum e_scenario_light_volume_type,short> volume_type; // 0x0
	c_flags<enum e_scenario_object_light_volume_flags,unsigned short> volume_flags; // 0x2
	c_enum<enum e_scenario_object_lightmap_type,short> lightmap_type; // 0x4
	c_flags<enum e_scenario_object_lightmap_flags,unsigned short> lightmap_flags; // 0x6
	float lightmap_half_life; // 0x8
	float lightmap_light_scale; // 0xC
	real_point3d target_point; // 0x10
	float width; // 0x1C
	float height; // 0x20
	float field_of_view; // 0x24
	float falloff_distance; // 0x28
	float cutoff_distance; // 0x2C
	s_scenario_object_light_volume_data(s_scenario_object_light_volume_data &); /* compiler_generated() */
	s_scenario_object_light_volume_data(s_scenario_object_light_volume_data const &); /* compiler_generated() */
	s_scenario_object_light_volume_data(); /* compiler_generated() */
	s_scenario_object_light_volume_data &operator=(s_scenario_object_light_volume_data &); /* compiler_generated() */
	s_scenario_object_light_volume_data &operator=(s_scenario_object_light_volume_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_object_light_volume_data) == 48, "Invalid s_scenario_object_light_volume_data size");

struct s_scenario_placement
{
	short palette_index; // 0x0
	c_tag_block_index<s_scenario_object_name,short> name; // 0x2
	s_scenario_placement(s_scenario_placement &); /* compiler_generated() */
	s_scenario_placement(s_scenario_placement const &); /* compiler_generated() */
	s_scenario_placement(); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_placement) == 4, "Invalid s_scenario_placement size");

#pragma pack(push, 4)
struct s_scenario_object :
	public s_scenario_placement,
	public s_scenario_object_data
{
	s_scenario_object(s_scenario_object &); /* compiler_generated() */
	s_scenario_object(s_scenario_object const &); /* compiler_generated() */
	s_scenario_object(); /* compiler_generated() */
	s_scenario_object &operator=(s_scenario_object &); /* compiler_generated() */
	s_scenario_object &operator=(s_scenario_object const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_object) == 84, "Invalid s_scenario_object size");

struct s_scenario_scenery :
	public s_scenario_object,
	public s_scenario_object_permutation_data,
	public s_scenario_object_scenery_data,
	public s_multiplayer_object_properties_definition
{
	s_scenario_scenery(s_scenario_scenery &); /* compiler_generated() */
	s_scenario_scenery(s_scenario_scenery const &); /* compiler_generated() */
	s_scenario_scenery(); /* compiler_generated() */
	s_scenario_scenery &operator=(s_scenario_scenery &); /* compiler_generated() */
	s_scenario_scenery &operator=(s_scenario_scenery const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_scenery) == 184, "Invalid s_scenario_scenery size");

#pragma pack(push, 4)
struct s_scenario_crate :
	public s_scenario_object,
	public s_scenario_object_permutation_data,
	public s_scenario_object_crate_data,
	public s_multiplayer_object_properties_definition
{
	s_scenario_crate(s_scenario_crate &); /* compiler_generated() */
	s_scenario_crate(s_scenario_crate const &); /* compiler_generated() */
	s_scenario_crate(); /* compiler_generated() */
	s_scenario_crate &operator=(s_scenario_crate &); /* compiler_generated() */
	s_scenario_crate &operator=(s_scenario_crate const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_crate) == 180, "Invalid s_scenario_crate size");

struct s_scenario_unit :
	public s_scenario_object,
	public s_scenario_object_permutation_data,
	public s_scenario_object_unit_data
{
	s_scenario_unit(s_scenario_unit &); /* compiler_generated() */
	s_scenario_unit(s_scenario_unit const &); /* compiler_generated() */
	s_scenario_unit(); /* compiler_generated() */
	s_scenario_unit &operator=(s_scenario_unit &); /* compiler_generated() */
	s_scenario_unit &operator=(s_scenario_unit const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_unit) == 120, "Invalid s_scenario_unit size");

struct s_scenario_biped :
	public s_scenario_unit
{
	s_scenario_biped(s_scenario_biped &); /* compiler_generated() */
	s_scenario_biped(s_scenario_biped const &); /* compiler_generated() */
	s_scenario_biped(); /* compiler_generated() */
	s_scenario_biped &operator=(s_scenario_biped &); /* compiler_generated() */
	s_scenario_biped &operator=(s_scenario_biped const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_biped) == 120, "Invalid s_scenario_biped size");

#pragma pack(push, 4)
struct s_scenario_vehicle :
	public s_scenario_unit,
	public s_multiplayer_object_properties_definition
{
	s_scenario_vehicle(s_scenario_vehicle &); /* compiler_generated() */
	s_scenario_vehicle(s_scenario_vehicle const &); /* compiler_generated() */
	s_scenario_vehicle(); /* compiler_generated() */
	s_scenario_vehicle &operator=(s_scenario_vehicle &); /* compiler_generated() */
	s_scenario_vehicle &operator=(s_scenario_vehicle const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_vehicle) == 172, "Invalid s_scenario_vehicle size");

#pragma pack(push, 4)
struct s_scenario_equipment :
	public s_scenario_object,
	public s_scenario_object_equipment_data,
	public s_multiplayer_object_properties_definition
{
	s_scenario_equipment(s_scenario_equipment &); /* compiler_generated() */
	s_scenario_equipment(s_scenario_equipment const &); /* compiler_generated() */
	s_scenario_equipment(); /* compiler_generated() */
	s_scenario_equipment &operator=(s_scenario_equipment &); /* compiler_generated() */
	s_scenario_equipment &operator=(s_scenario_equipment const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_equipment) == 140, "Invalid s_scenario_equipment size");

#pragma pack(push, 4)
struct s_scenario_weapon :
	public s_scenario_object,
	public s_scenario_object_permutation_data,
	public s_scenario_object_weapon_data,
	public s_multiplayer_object_properties_definition
{
	s_scenario_weapon(s_scenario_weapon &); /* compiler_generated() */
	s_scenario_weapon(s_scenario_weapon const &); /* compiler_generated() */
	s_scenario_weapon(); /* compiler_generated() */
	s_scenario_weapon &operator=(s_scenario_weapon &); /* compiler_generated() */
	s_scenario_weapon &operator=(s_scenario_weapon const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_weapon) == 172, "Invalid s_scenario_weapon size");

struct s_scenario_device :
	public s_scenario_object,
	public s_scenario_object_permutation_data,
	public s_scenario_object_device_data
{
	s_scenario_device(s_scenario_device &); /* compiler_generated() */
	s_scenario_device(s_scenario_device const &); /* compiler_generated() */
	s_scenario_device(); /* compiler_generated() */
	s_scenario_device &operator=(s_scenario_device &); /* compiler_generated() */
	s_scenario_device &operator=(s_scenario_device const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_device) == 120, "Invalid s_scenario_device size");

#pragma pack(push, 4)
struct s_scenario_machine :
	public s_scenario_device,
	public s_scenario_object_machine_data
{
	s_scenario_machine(s_scenario_machine &); /* compiler_generated() */
	s_scenario_machine(s_scenario_machine const &); /* compiler_generated() */
	s_scenario_machine(); /* compiler_generated() */
	s_scenario_machine &operator=(s_scenario_machine &); /* compiler_generated() */
	s_scenario_machine &operator=(s_scenario_machine const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_machine) == 140, "Invalid s_scenario_machine size");

#pragma pack(push, 4)
struct s_scenario_terminal :
	public s_scenario_device,
	public s_scenario_object_terminal_data
{
	s_scenario_terminal(s_scenario_terminal &); /* compiler_generated() */
	s_scenario_terminal(s_scenario_terminal const &); /* compiler_generated() */
	s_scenario_terminal(); /* compiler_generated() */
	s_scenario_terminal &operator=(s_scenario_terminal &); /* compiler_generated() */
	s_scenario_terminal &operator=(s_scenario_terminal const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_terminal) == 124, "Invalid s_scenario_terminal size");

#pragma pack(push, 4)
struct s_scenario_arg_device :
	public s_scenario_device,
	public s_scenario_object_arg_device_data
{
	s_scenario_arg_device(s_scenario_arg_device &); /* compiler_generated() */
	s_scenario_arg_device(s_scenario_arg_device const &); /* compiler_generated() */
	s_scenario_arg_device(); /* compiler_generated() */
	s_scenario_arg_device &operator=(s_scenario_arg_device &); /* compiler_generated() */
	s_scenario_arg_device &operator=(s_scenario_arg_device const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_arg_device) == 188, "Invalid s_scenario_arg_device size");

struct s_scenario_control :
	public s_scenario_device,
	public s_scenario_object_control_data
{
	s_scenario_control(s_scenario_control &); /* compiler_generated() */
	s_scenario_control(s_scenario_control const &); /* compiler_generated() */
	s_scenario_control(); /* compiler_generated() */
	s_scenario_control &operator=(s_scenario_control &); /* compiler_generated() */
	s_scenario_control &operator=(s_scenario_control const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_control) == 128, "Invalid s_scenario_control size");

struct s_scenario_sound_scenery :
	public s_scenario_object,
	public s_scenario_object_sound_scenery_data
{
	s_scenario_sound_scenery(s_scenario_sound_scenery &); /* compiler_generated() */
	s_scenario_sound_scenery(s_scenario_sound_scenery const &); /* compiler_generated() */
	s_scenario_sound_scenery(); /* compiler_generated() */
	s_scenario_sound_scenery &operator=(s_scenario_sound_scenery &); /* compiler_generated() */
	s_scenario_sound_scenery &operator=(s_scenario_sound_scenery const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_sound_scenery) == 112, "Invalid s_scenario_sound_scenery size");

struct s_scenario_giant :
	public s_scenario_unit,
	public s_scenario_object_giant_data
{
	s_scenario_giant(s_scenario_giant &); /* compiler_generated() */
	s_scenario_giant(s_scenario_giant const &); /* compiler_generated() */
	s_scenario_giant(); /* compiler_generated() */
	s_scenario_giant &operator=(s_scenario_giant &); /* compiler_generated() */
	s_scenario_giant &operator=(s_scenario_giant const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_giant) == 136, "Invalid s_scenario_giant size");

#pragma pack(push, 4)
struct s_scenario_effect_scenery :
	public s_scenario_object
{
	s_scenario_effect_scenery(s_scenario_effect_scenery &); /* compiler_generated() */
	s_scenario_effect_scenery(s_scenario_effect_scenery const &); /* compiler_generated() */
	s_scenario_effect_scenery(); /* compiler_generated() */
	s_scenario_effect_scenery &operator=(s_scenario_effect_scenery &); /* compiler_generated() */
	s_scenario_effect_scenery &operator=(s_scenario_effect_scenery const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_effect_scenery) == 84, "Invalid s_scenario_effect_scenery size");

#pragma pack(push, 4)
struct s_scenario_light_volume :
	public s_scenario_object,
	public s_scenario_object_device_data,
	public s_scenario_object_light_volume_data
{
	s_scenario_light_volume(s_scenario_light_volume &); /* compiler_generated() */
	s_scenario_light_volume(s_scenario_light_volume const &); /* compiler_generated() */
	s_scenario_light_volume(); /* compiler_generated() */
	s_scenario_light_volume &operator=(s_scenario_light_volume &); /* compiler_generated() */
	s_scenario_light_volume &operator=(s_scenario_light_volume const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_light_volume) == 140, "Invalid s_scenario_light_volume size");

struct s_scenario_sandbox_object
{
	s_tag_reference object; // 0x0
	unsigned long name; // 0x10
	long max_allowed; // 0x14
	float cost; // 0x18
	unsigned char __pad0[20]; // 0x1C
};
static_assert(sizeof(s_scenario_sandbox_object) == 48, "Invalid s_scenario_sandbox_object size");

struct s_scenario_soft_ceiling
{
	c_enum<enum e_scenario_soft_ceiling_flags,unsigned short> flags; // 0x0
	c_enum<enum e_scenario_soft_ceiling_flags,unsigned short> runtime_flags; // 0x2
	unsigned long name; // 0x4
	c_enum<enum e_scenario_soft_ceiling_type,short> type; // 0x8
	s_scenario_soft_ceiling(s_scenario_soft_ceiling &); /* compiler_generated() */
	s_scenario_soft_ceiling(s_scenario_soft_ceiling const &); /* compiler_generated() */
	s_scenario_soft_ceiling(); /* compiler_generated() */
	s_scenario_soft_ceiling &operator=(s_scenario_soft_ceiling &); /* compiler_generated() */
	s_scenario_soft_ceiling &operator=(s_scenario_soft_ceiling const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0xA
};
static_assert(sizeof(s_scenario_soft_ceiling) == 12, "Invalid s_scenario_soft_ceiling size");

#pragma pack(push, 4)
struct s_starting_weapon_info
{
	s_tag_reference weapon; // 0x0
	short rounds_loaded; // 0x10
	short rounds_total; // 0x12
};
#pragma pack(pop)
static_assert(sizeof(s_starting_weapon_info) == 20, "Invalid s_starting_weapon_info size");

struct s_scenario_profile
{
	tag_string name; // 0x0
	float starting_health_damage; // 0x20
	float starting_shield_damage; // 0x24
	s_starting_weapon_info starting_weapons[2]; // 0x28
	short starting_consumables[4]; // 0x50
	char starting_grenades[4]; // 0x58
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x5C
	s_scenario_profile(s_scenario_profile &); /* compiler_generated() */
	s_scenario_profile(s_scenario_profile const &); /* compiler_generated() */
	s_scenario_profile(); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x5E
};
static_assert(sizeof(s_scenario_profile) == 96, "Invalid s_scenario_profile size");

#pragma pack(push, 4)
struct s_scenario_player
{
	real_point3d position; // 0x0
	real_euler_angles2d facing; // 0xC
	short insertion_point_index; // 0x14
	c_flags<enum e_scenario_player_spawn_flags,unsigned short> flags; // 0x16
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x18
	s_scenario_player(s_scenario_player &); /* compiler_generated() */
	s_scenario_player(s_scenario_player const &); /* compiler_generated() */
	s_scenario_player(); /* compiler_generated() */
	s_scenario_player &operator=(s_scenario_player &); /* compiler_generated() */
	s_scenario_player &operator=(s_scenario_player const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x1A
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_player) == 28, "Invalid s_scenario_player size");

#pragma pack(push, 4)
struct s_scenario_trigger_volume_point
{
	real_point3d position; // 0x0
	real_euler_angles2d normal; // 0xC
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_trigger_volume_point) == 20, "Invalid s_scenario_trigger_volume_point size");

struct s_scenario_trigger_volume_triangle
{
	real_plane3d planes[3]; // 0x0
	real_point2d points[3]; // 0x30
	unsigned char __pad0[8]; // 0x48
};
static_assert(sizeof(s_scenario_trigger_volume_triangle) == 80, "Invalid s_scenario_trigger_volume_triangle size");

#pragma pack(push, 4)
struct s_scenario_trigger_volume
{
	unsigned long name; // 0x0
	c_tag_block_index<s_scenario_object_name,short> object_name; // 0x4
	short runtime_node_index; // 0x6
	unsigned long node_name; // 0x8
	c_enum<enum e_scenario_trigger_volume_type,short> type; // 0xC
	unsigned char __pad0[2]; // 0xE
	real_vector3d forward; // 0x10
	real_vector3d up; // 0x1C
	real_point3d position; // 0x28
	real_point3d extents; // 0x34
	float z_sink; // 0x40
	c_tag_block<s_scenario_trigger_volume_point> sector_points; // 0x44
	c_tag_block<s_scenario_trigger_volume_triangle> runtime_triangles; // 0x50
	real_bounds runtime_sector_x_bounds; // 0x5C
	real_bounds runtime_sector_y_bounds; // 0x64
	real_bounds runtime_sector_z_bounds; // 0x6C
	float c; // 0x74
	c_tag_block_index<s_scenario_kill_trigger_volume,short> kill_volume; // 0x78
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x7A
	s_scenario_trigger_volume(s_scenario_trigger_volume &); /* compiler_generated() */
	s_scenario_trigger_volume(s_scenario_trigger_volume const &); /* compiler_generated() */
	s_scenario_trigger_volume(); /* compiler_generated() */
	s_scenario_trigger_volume &operator=(s_scenario_trigger_volume &); /* compiler_generated() */
	s_scenario_trigger_volume &operator=(s_scenario_trigger_volume const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_trigger_volume) == 124, "Invalid s_scenario_trigger_volume size");

struct s_scenario_recorded_animation
{
	tag_string name; // 0x0
	char version; // 0x20
	char raw_animation_data; // 0x21
	char unit_control_data_version; // 0x22
	unsigned char __pad0[1]; // 0x23
	short length_of_animation; // 0x24
	unsigned char __pad1[6]; // 0x26
	s_tag_data recorded_animation_event_stream; // 0x2C
	s_scenario_recorded_animation(s_scenario_recorded_animation &); /* compiler_generated() */
	s_scenario_recorded_animation(s_scenario_recorded_animation const &); /* compiler_generated() */
	s_scenario_recorded_animation(); /* compiler_generated() */
	s_scenario_recorded_animation &operator=(s_scenario_recorded_animation &); /* compiler_generated() */
	s_scenario_recorded_animation &operator=(s_scenario_recorded_animation const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_recorded_animation) == 64, "Invalid s_scenario_recorded_animation size");

struct s_scenario_zone_set_switch_trigger_volume
{
	c_flags<enum e_scenario_zone_set_switch_trigger_volume_flags,unsigned short> flags; // 0x0
	c_tag_block_index<s_scenario_zone_set,short> begin_zone_set; // 0x2
	c_tag_block_index<s_scenario_trigger_volume,short> trigger_volume; // 0x4
	c_tag_block_index<s_scenario_zone_set,short> commit_zone_set; // 0x6
	s_scenario_zone_set_switch_trigger_volume(s_scenario_zone_set_switch_trigger_volume &); /* compiler_generated() */
	s_scenario_zone_set_switch_trigger_volume(s_scenario_zone_set_switch_trigger_volume const &); /* compiler_generated() */
	s_scenario_zone_set_switch_trigger_volume(); /* compiler_generated() */
	s_scenario_zone_set_switch_trigger_volume &operator=(s_scenario_zone_set_switch_trigger_volume &); /* compiler_generated() */
	s_scenario_zone_set_switch_trigger_volume &operator=(s_scenario_zone_set_switch_trigger_volume const &); /* compiler_generated() */
	unsigned char __pad0[4]; // 0x8
};
static_assert(sizeof(s_scenario_zone_set_switch_trigger_volume) == 12, "Invalid s_scenario_zone_set_switch_trigger_volume size");

#pragma pack(push, 4)
struct s_scenario_decal
{
	c_tag_block_index<s_scenario_decal_palette_entry,short> decal_palette_index; // 0x0
	c_flags<enum e_scenario_decal_flags,unsigned char> flags; // 0x2
	unsigned char __pad0[1]; // 0x3
	real_quaternion rotation; // 0x4
	real_point3d position; // 0x14
	float scale; // 0x20
	s_scenario_decal(s_scenario_decal &); /* compiler_generated() */
	s_scenario_decal(s_scenario_decal const &); /* compiler_generated() */
	s_scenario_decal(); /* compiler_generated() */
	s_scenario_decal &operator=(s_scenario_decal &); /* compiler_generated() */
	s_scenario_decal &operator=(s_scenario_decal const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_decal) == 36, "Invalid s_scenario_decal size");

struct s_scenario_detail_object_palette_entry
{
	s_tag_reference reference; // 0x0
};
static_assert(sizeof(s_scenario_detail_object_palette_entry) == 16, "Invalid s_scenario_detail_object_palette_entry size");

// s_scenario_character_palette_entry is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

struct s_scenario_cutscene_camera_point
{
	unsigned short flags; // 0x0
	c_enum<enum e_scenario_cutscene_camera_point_type,unsigned short> camera_type; // 0x2
	char name[32]; // 0x4
	unsigned char __pad0[4]; // 0x24
	real_point3d position; // 0x28
	real_euler_angles3d orientation; // 0x34
	s_scenario_cutscene_camera_point(s_scenario_cutscene_camera_point &); /* compiler_generated() */
	_inline s_scenario_cutscene_camera_point(s_scenario_cutscene_camera_point const &__that); /* compiler_generated() */
	s_scenario_cutscene_camera_point(); /* compiler_generated() */
	s_scenario_cutscene_camera_point &operator=(s_scenario_cutscene_camera_point &); /* compiler_generated() */
	s_scenario_cutscene_camera_point &operator=(s_scenario_cutscene_camera_point const &); /* compiler_generated() */
};
static_assert(sizeof(s_scenario_cutscene_camera_point) == 64, "Invalid s_scenario_cutscene_camera_point size");

#pragma pack(push, 4)
struct s_scenario_acoustics_environment
{
	s_tag_reference sound_environment; // 0x0
	long type; // 0x10
	float cutoff_distance; // 0x14
	float interpolation_time; // 0x18
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_acoustics_environment) == 28, "Invalid s_scenario_acoustics_environment size");

struct s_scenario_acoustics_ambience
{
	s_tag_reference background_sound; // 0x0
	s_tag_reference inside_cluster_sound; // 0x10
	float cutoff_distance; // 0x20
	unsigned long scale_flags; // 0x24
	float interior_scale; // 0x28
	float portal_scale; // 0x2C
	float exterior_scale; // 0x30
	float interpolation_time; // 0x34
};
static_assert(sizeof(s_scenario_acoustics_ambience) == 56, "Invalid s_scenario_acoustics_ambience size");

struct s_scenario_acoustics_palette_entry
{
	unsigned long name; // 0x0
	s_scenario_acoustics_environment reverb; // 0x4
	s_scenario_acoustics_ambience ambience; // 0x20
};
static_assert(sizeof(s_scenario_acoustics_palette_entry) == 88, "Invalid s_scenario_acoustics_palette_entry size");

#pragma pack(push, 4)
struct s_scenario
{
	c_enum<enum e_scenario_type,char> type; // 0x0
	c_enum<enum e_scenario_subtype,char> subtype; // 0x1
	c_flags<enum e_scenario_flags,unsigned short> flags; // 0x2
	long campaign_id; // 0x4
	long map_id; // 0x8
	float local_north; // 0xC
	float sandbox_budget; // 0x10
	c_tag_block<s_scenario_structure_bsp_reference> structure_bsps; // 0x14
	s_tag_reference do_not_use; // 0x20
	c_tag_block<s_scenario_sky_reference> skies; // 0x30
	c_tag_block<s_scenario_zone_set_pvs> zone_set_pvs; // 0x3C
	c_tag_block<s_scenario_zone_set_audibility> zone_set_audibility; // 0x48
	c_tag_block<s_scenario_zone_set> zone_sets; // 0x54
	c_tag_block<s_scenario_structure_bsp_atlas> bsp_atlas; // 0x60
	c_tag_block<s_scenario_campaign_player> campaign_players; // 0x6C
	s_tag_block unknown1; // 0x78
	s_tag_block unknown2; // 0x84
	s_tag_block unknown3; // 0x90
	s_tag_data editor_scenario_data; // 0x9C
	s_tag_block comments; // 0xB0
	c_tag_block<s_scenario_object_name> object_names; // 0xBC
	c_tag_block<s_scenario_scenery> scenery; // 0xC8
	c_tag_block<s_scenario_object_palette_entry> scenery_palette; // 0xD4
	c_tag_block<s_scenario_biped> bipeds; // 0xE0
	c_tag_block<s_scenario_object_palette_entry> biped_palette; // 0xEC
	c_tag_block<s_scenario_vehicle> vehicles; // 0xF8
	c_tag_block<s_scenario_object_palette_entry> vehicle_palette; // 0x104
	c_tag_block<s_scenario_equipment> equipment; // 0x110
	c_tag_block<s_scenario_object_palette_entry> equipment_palette; // 0x11C
	c_tag_block<s_scenario_weapon> weapons; // 0x128
	c_tag_block<s_scenario_object_palette_entry> weapon_palette; // 0x134
	c_tag_block<s_scenario_device_group> device_groups; // 0x140
	c_tag_block<s_scenario_machine> machines; // 0x14C
	c_tag_block<s_scenario_object_palette_entry> machine_palette; // 0x158
	c_tag_block<s_scenario_terminal> terminals; // 0x164
	c_tag_block<s_scenario_object_palette_entry> terminal_palette; // 0x170
	c_tag_block<s_scenario_arg_device> arg_devices; // 0x17C
	c_tag_block<s_scenario_object_palette_entry> arg_device_palette; // 0x188
	c_tag_block<s_scenario_control> controls; // 0x194
	c_tag_block<s_scenario_object_palette_entry> control_palette; // 0x1A0
	c_tag_block<s_scenario_sound_scenery> sound_scenery; // 0x1AC
	c_tag_block<s_scenario_object_palette_entry> sound_scenery_palette; // 0x1B8
	c_tag_block<s_scenario_giant> giants; // 0x1C4
	c_tag_block<s_scenario_object_palette_entry> giant_palette; // 0x1D0
	c_tag_block<s_scenario_effect_scenery> effect_scenery; // 0x1DC
	c_tag_block<s_scenario_object_palette_entry> effect_scenery_palette; // 0x1E8
	c_tag_block<s_scenario_light_volume> light_volumes; // 0x1F4
	c_tag_block<s_scenario_object_palette_entry> light_volume_palette; // 0x200
	c_tag_block<s_scenario_sandbox_object> sandbox_vehicles; // 0x20C
	c_tag_block<s_scenario_sandbox_object> sandbox_weapons; // 0x218
	c_tag_block<s_scenario_sandbox_object> sandbox_equipment; // 0x224
	c_tag_block<s_scenario_sandbox_object> sandbox_scenery; // 0x230
	c_tag_block<s_scenario_sandbox_object> sandbox_teleporters; // 0x23C
	c_tag_block<s_scenario_sandbox_object> sandbox_goal_objects; // 0x248
	c_tag_block<s_scenario_sandbox_object> sandbox_spawning; // 0x254
	c_tag_block<s_scenario_soft_ceiling> soft_ceilings; // 0x260
	c_tag_block<s_scenario_profile> player_starting_profile; // 0x26C
	c_tag_block<s_scenario_player> player_starting_locations; // 0x278
	c_tag_block<s_scenario_trigger_volume> trigger_volumes; // 0x284
	c_tag_block<s_scenario_recorded_animation> recorded_animations; // 0x290
	c_tag_block<s_scenario_zone_set_switch_trigger_volume> zone_set_switch_trigger_volumes; // 0x29C
	s_tag_block unknown4; // 0x2A8
	s_tag_block unknown5; // 0x2B4
	s_tag_block unknown6; // 0x2C0
	s_tag_block unknown7; // 0x2CC
	s_tag_block unknown8; // 0x2D8
	s_tag_block unknown9; // 0x2E4
	s_tag_block unknown10; // 0x2F0
	s_tag_block unknown11; // 0x2FC
	s_tag_block unknown12; // 0x308
	s_tag_block unknown13; // 0x314
	s_tag_block unknown14; // 0x320
	s_tag_block unknown15; // 0x32C
	s_tag_block unknown16; // 0x338
	s_tag_block unknown17; // 0x344
	s_tag_block unknown18; // 0x350
	s_tag_block unknown19; // 0x35C
	s_tag_block unknown20; // 0x368
	c_tag_block<s_scenario_decal> decals; // 0x374
	c_tag_block<s_scenario_decal_palette_entry> decal_palette; // 0x380
	c_tag_block<s_scenario_detail_object_palette_entry> detail_object_palette; // 0x38C
	c_tag_block<s_scenario_style_palette_entry> style_palette; // 0x398
	c_tag_block<s_squad_group_definition> squad_groups; // 0x3A4
	c_tag_block<s_squad_definition> squads; // 0x3B0
	s_tag_block zones; // 0x3BC
	s_tag_block squad_patrols; // 0x3C8
	s_tag_block mission_scenes; // 0x3D4
	s_tag_block character_palette; // 0x3E0
	s_tag_block block3EC; // 0x3EC
	s_tag_block ai_pathfinding; // 0x3F8
	s_tag_block block404; // 0x404
	s_tag_data script_strings; // 0x410
	c_tag_block<s_hs_script> scripts; // 0x424
	c_tag_block<s_hs_global> script_globals; // 0x430
	s_tag_block script_src_references; // 0x43C
	s_tag_block script_extern_references; // 0x448
	s_tag_block scripting_data; // 0x454
	s_tag_block cutscene_flags; // 0x460
	c_tag_block<s_scenario_cutscene_camera_point> cutscene_camera_points; // 0x46C
	s_tag_block cutscene_titles; // 0x478
	s_tag_reference custom_object_name_strings; // 0x484
	s_tag_reference chapter_title_strings; // 0x494
	s_tag_block scenario_resources; // 0x4A4
	s_tag_block unit_seats_mapping; // 0x4B0
	c_tag_block<short> scenario_kill_triggers; // 0x4BC
	c_tag_block<short> scenario_safe_triggers; // 0x4C8
	c_tag_block<s_hs_syntax_node> script_expressions; // 0x4D4
	s_tag_block orders; // 0x4E0
	s_tag_block triggers; // 0x4EC
	c_tag_block<s_scenario_acoustics_palette_entry> background_sound_environment_palette; // 0x4F8
	s_tag_block block504; // 0x504
	s_tag_block block510; // 0x510
	s_tag_block block51C; // 0x51C
	s_tag_block fog; // 0x528
	s_tag_block camera_fx; // 0x534
	s_tag_block block540; // 0x540
	s_tag_block block54C; // 0x54C
	s_tag_block block558; // 0x558
	s_tag_block scenario_cluster_data; // 0x564
	s_tag_block block570; // 0x570
	__int32 object_salts[32]; // 0x57C
	s_tag_block spawn_data; // 0x5FC
	s_tag_reference sound_effects_collection; // 0x608
	c_tag_block<s_scenario_crate> crates; // 0x618
	c_tag_block<s_scenario_object_palette_entry> crate_palette; // 0x624
	s_tag_block flock_palette; // 0x630
	s_tag_block flocks; // 0x63C
	s_tag_reference subtitle_strings; // 0x648
	s_tag_block creatures; // 0x658
	s_tag_block creature_palette; // 0x664
	s_tag_block editor_folders; // 0x670
	s_tag_reference territory_location_name_strings; // 0x67C
	__int32 unknown21; // 0x68C
	__int32 unknown22; // 0x690
	s_tag_block mission_dialogue; // 0x694
	s_tag_reference objective_strings; // 0x6A0
	s_tag_block interpolators; // 0x6B0
	s_tag_block block6BC; // 0x6BC
	s_tag_block block6C8; // 0x6C8
	s_tag_block simulation_definition_table; // 0x6D4
	s_tag_reference default_camera_fx; // 0x6E0
	s_tag_reference default_screen_fx; // 0x6F0
	s_tag_reference ref700; // 0x700
	s_tag_reference sky_parameters; // 0x710
	s_tag_reference global_lighting; // 0x720
	s_tag_reference lightmap; // 0x730
	s_tag_reference performance_throttles; // 0x740
	s_tag_block reference_frames; // 0x750
	s_tag_block ai_objectives; // 0x75C
	s_tag_block designer_zonesets; // 0x768
	s_tag_block block774; // 0x774
	s_tag_block block780; // 0x780
	s_tag_block cinematics; // 0x78C
	s_tag_block cinematic_lighting; // 0x798
	s_tag_block block7A4; // 0x7A4
	s_tag_block scenario_metagame; // 0x7B0
	s_tag_block collision_unknown; // 0x7BC
	s_tag_block block7C8; // 0x7C8
	s_tag_block cortana_effects; // 0x7D4
	s_tag_block lightmap_airprobes; // 0x7E0
	s_tag_block block7EC; // 0x7EC
	s_tag_reference mission_vision_effects; // 0x7F8
	s_tag_reference mission_vision_mode_theater_effect; // 0x808
	c_tag_block<s_scenario_background_textures> background_textures; // 0x818
	s_scenario(s_scenario &); /* compiler_generated() */
	s_scenario(s_scenario const &); /* compiler_generated() */
	s_scenario(); /* compiler_generated() */
	s_scenario &operator=(s_scenario &); /* compiler_generated() */
	s_scenario &operator=(s_scenario const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_scenario) == 2084, "Invalid s_scenario size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SCENARIO_SCENARIO_DEFINITIONS_HPP__
