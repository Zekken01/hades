#ifndef __BLAM_AI_SQUADS_HPP__
#define __BLAM_AI_SQUADS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/ai.hpp"
#include "Blam/ai/ai_reference_frame.hpp"
#include "Blam/ai/cl_engine.hpp"
#include "Blam/ai/zone.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

class c_ai_point3d;
struct real_euler_angles2d;
struct real_euler_angles3d;
struct s_ai_conditions;
struct s_cell_character_type;
struct s_cell_definition;
struct s_cell_item_type;
struct s_cs_point;
struct s_cs_point_set;
struct s_follow_firing_point_query;
struct s_hs_script;
struct s_objective;
struct s_opposing_objective;
struct s_scenario_character_palette_entry;
struct s_scenario_editor_folder;
struct s_scenario_object_palette_entry;
struct s_scenario_structure_bsp_reference;
struct s_spawn_point_definition;
struct s_squad_character;
struct s_squad_definition;
struct s_squad_equipment;
struct s_squad_group_definition;
struct s_squad_patrol_definition;
struct s_squad_patrol_waypoint_definition;
struct s_squad_vehicle;
struct s_squad_weapon;
struct s_tag_reference_short;
struct s_task;
struct s_task_activation_script;
struct s_task_area;
struct s_task_direction;
struct s_task_direction_point;
struct s_task_pureform_distribution;
struct s_zone_area_definition;
struct s_zone_definition;
struct short_bounds;
union long_string;
union tag_string;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_follow_firing_point_query
{
	c_enum<enum e_firing_point_shape,char> shape; // 0x0
	c_enum<enum e_firing_point_anchor_relationship,char> anchor_relationship; // 0x1
	unsigned char __pad0[2]; // 0x2
	float relationship_offset; // 0x4
	float scale; // 0x8
	float z_threshold; // 0xC
	real_euler_angles3d angles; // 0x10
	s_follow_firing_point_query(s_follow_firing_point_query &); /* compiler_generated() */
	s_follow_firing_point_query(s_follow_firing_point_query const &); /* compiler_generated() */
	s_follow_firing_point_query(); /* compiler_generated() */
	s_follow_firing_point_query &operator=(s_follow_firing_point_query &); /* compiler_generated() */
	s_follow_firing_point_query &operator=(s_follow_firing_point_query const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_follow_firing_point_query) == 28, "Invalid s_follow_firing_point_query size");

struct s_task_pureform_distribution
{
	short unknown1; // 0x0
	short unknown2; // 0x2
	short unknown3; // 0x4
	unsigned char __pad0[2]; // 0x6
};
static_assert(sizeof(s_task_pureform_distribution) == 8, "Invalid s_task_pureform_distribution size");

#pragma pack(push, 4)
struct s_task_activation_script
{
	tag_string script_name; // 0x0
	long_string script_source; // 0x20
	c_enum<enum e_hs_compile_state,short> compile_state; // 0x120
	s_task_activation_script(s_task_activation_script &); /* compiler_generated() */
	s_task_activation_script(s_task_activation_script const &); /* compiler_generated() */
	s_task_activation_script(); /* compiler_generated() */
	s_task_activation_script &operator=(s_task_activation_script &); /* compiler_generated() */
	s_task_activation_script &operator=(s_task_activation_script const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x122
};
#pragma pack(pop)
static_assert(sizeof(s_task_activation_script) == 292, "Invalid s_task_activation_script size");

struct s_task_area
{
	c_enum<enum e_task_area_type,short> type; // 0x0
	c_flags<enum e_task_area_flags,unsigned char> flags; // 0x2
	c_flags<enum e_task_area_character_flags,unsigned char> character_flags; // 0x3
	c_tag_block_index<s_zone_definition,short> zone; // 0x4
	c_tag_block_index<s_zone_area_definition,short> area; // 0x6
	float yaw; // 0x8
	long connectivity_bit_vector; // 0xC
	s_task_area(s_task_area &); /* compiler_generated() */
	s_task_area(s_task_area const &); /* compiler_generated() */
	s_task_area(); /* compiler_generated() */
	s_task_area &operator=(s_task_area &); /* compiler_generated() */
	s_task_area &operator=(s_task_area const &); /* compiler_generated() */
};
static_assert(sizeof(s_task_area) == 16, "Invalid s_task_area size");

struct s_task_direction_point
{
	real_point3d position; // 0x0
	short manual_reference_frame; // 0xC
	c_tag_block_index<s_scenario_structure_bsp_reference,short> bsp; // 0xE
	s_task_direction_point(s_task_direction_point &); /* compiler_generated() */
	s_task_direction_point(s_task_direction_point const &); /* compiler_generated() */
	s_task_direction_point(); /* compiler_generated() */
};
static_assert(sizeof(s_task_direction_point) == 16, "Invalid s_task_direction_point size");

#pragma pack(push, 4)
struct s_task_direction
{
	c_tag_block<s_task_direction_point> points; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_task_direction) == 12, "Invalid s_task_direction size");

struct s_cell_character_type
{
	s_ai_conditions place_on; // 0x0
	c_tag_block_index<s_scenario_character_palette_entry,short> character; // 0xC
	short chance; // 0xE
	s_cell_character_type(s_cell_character_type &); /* compiler_generated() */
	s_cell_character_type(s_cell_character_type const &); /* compiler_generated() */
	s_cell_character_type(); /* compiler_generated() */
	s_cell_character_type &operator=(s_cell_character_type &); /* compiler_generated() */
	s_cell_character_type &operator=(s_cell_character_type const &); /* compiler_generated() */
};
static_assert(sizeof(s_cell_character_type) == 16, "Invalid s_cell_character_type size");

struct s_cell_item_type
{
	s_ai_conditions place_on; // 0x0
	c_tag_block_index<s_scenario_object_palette_entry,short> item; // 0xC
	short chance; // 0xE
	s_cell_item_type(s_cell_item_type &); /* compiler_generated() */
	s_cell_item_type(s_cell_item_type const &); /* compiler_generated() */
	s_cell_item_type(); /* compiler_generated() */
	s_cell_item_type &operator=(s_cell_item_type &); /* compiler_generated() */
	s_cell_item_type &operator=(s_cell_item_type const &); /* compiler_generated() */
};
static_assert(sizeof(s_cell_item_type) == 16, "Invalid s_cell_item_type size");

struct s_squad_patrol_waypoint_definition
{
	c_tag_block_index<s_cs_point,short> point; // 0x0
	c_flags<enum e_squad_patrol_waypoint_flags,unsigned short> flags; // 0x2
	float delay; // 0x4
	float angle; // 0x8
	unsigned long activity_name; // 0xC
	c_enum<enum e_ai_activity,short> activity; // 0x10
	short activity_variant; // 0x12
	tag_string command_script_name; // 0x14
	c_tag_block_index<s_hs_script,short> command_script; // 0x34
	s_squad_patrol_waypoint_definition(s_squad_patrol_waypoint_definition &); /* compiler_generated() */
	s_squad_patrol_waypoint_definition(s_squad_patrol_waypoint_definition const &); /* compiler_generated() */
	s_squad_patrol_waypoint_definition(); /* compiler_generated() */
	s_squad_patrol_waypoint_definition &operator=(s_squad_patrol_waypoint_definition &); /* compiler_generated() */
	s_squad_patrol_waypoint_definition &operator=(s_squad_patrol_waypoint_definition const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x36
};
static_assert(sizeof(s_squad_patrol_waypoint_definition) == 56, "Invalid s_squad_patrol_waypoint_definition size");

#pragma pack(push, 4)
struct s_cell_definition
{
	unsigned long name; // 0x0
	s_ai_conditions place_on; // 0x4
	short spawn_count; // 0x10
	short major_upgrade; // 0x12
	c_tag_block<s_cell_character_type> character_types; // 0x14
	c_tag_block<s_cell_item_type> primary_weapon_types; // 0x20
	c_tag_block<s_cell_item_type> secondary_weapon_types; // 0x2C
	c_tag_block<s_cell_item_type> equipment; // 0x38
	c_enum<enum e_squad_grenade_type,short> grenade_type; // 0x44
	c_tag_block_index<s_scenario_object_palette_entry,short> vehicle_type; // 0x46
	unsigned long vehicle_variant; // 0x48
	tag_string command_script_name; // 0x4C
	c_tag_block_index<s_hs_script,short> command_script_index; // 0x6C
	unsigned char __pad0[2]; // 0x6E
	unsigned long activity_name; // 0x70
	c_tag_block_index<s_cs_point_set,short> point_set; // 0x74
	c_enum<enum e_squad_patrol_mode,short> patrol_mode; // 0x76
	c_tag_block<s_squad_patrol_waypoint_definition> patrol_points; // 0x78
	s_cell_definition(s_cell_definition &); /* compiler_generated() */
	s_cell_definition(s_cell_definition const &); /* compiler_generated() */
	s_cell_definition(); /* compiler_generated() */
	s_cell_definition &operator=(s_cell_definition &); /* compiler_generated() */
	s_cell_definition &operator=(s_cell_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_cell_definition) == 132, "Invalid s_cell_definition size");

struct s_opposing_objective
{
	c_tag_block_index<s_objective,short> objective; // 0x0
	s_opposing_objective(s_opposing_objective &); /* compiler_generated() */
	s_opposing_objective(s_opposing_objective const &); /* compiler_generated() */
	s_opposing_objective(); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x2
};
static_assert(sizeof(s_opposing_objective) == 4, "Invalid s_opposing_objective size");

#pragma pack(push, 4)
struct s_objective
{
	unsigned long name; // 0x0
	c_tag_block<s_opposing_objective> opposing_objectives; // 0x4
	c_flags<enum e_objective_flags,unsigned short> flags; // 0x10
	c_tag_block_index<s_zone_definition,short> zone; // 0x12
	c_tag_block_index<s_task,short> initial_task; // 0x14
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x16
	c_tag_block<s_task> tasks; // 0x18
	s_objective(s_objective &); /* compiler_generated() */
	s_objective(s_objective const &); /* compiler_generated() */
	s_objective(); /* compiler_generated() */
	s_objective &operator=(s_objective &); /* compiler_generated() */
	s_objective &operator=(s_objective const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_objective) == 36, "Invalid s_objective size");

struct s_spawn_point_definition
{
	s_ai_conditions place_on; // 0x0
	unsigned long name; // 0xC
	c_tag_block_index<s_cell_definition,short> cell; // 0x10
	unsigned char __pad0[2]; // 0x12
	c_ai_point3d point; // 0x14
	real_euler_angles2d facing; // 0x24
	float roll; // 0x2C
	c_flags<enum e_squad_spawn_point_flags,unsigned short> flags; // 0x30
	c_tag_block_index<s_squad_character,short> character_type; // 0x32
	c_tag_block_index<s_squad_weapon,short> initial_primary_weapon; // 0x34
	c_tag_block_index<s_squad_weapon,short> initial_secondary_weapon; // 0x36
	c_tag_block_index<s_squad_equipment,short> initial_equipment; // 0x38
	c_tag_block_index<s_squad_vehicle,short> vehicle_type; // 0x3A
	c_enum<enum e_squad_seat_type,short> seat_type; // 0x3C
	c_enum<enum e_squad_grenade_type,short> initial_grenade_type; // 0x3E
	short swarm_count; // 0x40
	unsigned char __pad1[2]; // 0x42
	unsigned long actor_variant; // 0x44
	unsigned long vehicle_variant; // 0x48
	float initial_movement_distance; // 0x4C
	c_enum<enum e_squad_movement_mode,short> movement_mode; // 0x50
	short emitter_vehicle; // 0x52
	short emitter_giant; // 0x54
	short emitter_biped; // 0x56
	tag_string placement_script_name; // 0x58
	c_tag_block_index<s_hs_script,short> placement_script; // 0x78
	unsigned char __pad2[2]; // 0x7A
	unsigned long activity_name; // 0x7C
	c_tag_block_index<s_cs_point_set,short> point_set; // 0x80
	c_enum<enum e_squad_patrol_mode,short> patrol_mode; // 0x82
	c_tag_block<s_squad_patrol_waypoint_definition> patrol_points; // 0x84
	s_spawn_point_definition(s_spawn_point_definition &); /* compiler_generated() */
	s_spawn_point_definition(s_spawn_point_definition const &); /* compiler_generated() */
	s_spawn_point_definition(); /* compiler_generated() */
	s_spawn_point_definition &operator=(s_spawn_point_definition &); /* compiler_generated() */
	s_spawn_point_definition &operator=(s_spawn_point_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_spawn_point_definition) == 144, "Invalid s_spawn_point_definition size");

struct s_squad_group_definition
{
	tag_string name; // 0x0
	c_tag_block_index<s_squad_group_definition,short> parent; // 0x20
	c_tag_block_index<s_objective,short> initial_objective; // 0x22
	unsigned char __pad0[2]; // 0x24
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x26
	s_squad_group_definition(s_squad_group_definition &); /* compiler_generated() */
	s_squad_group_definition(s_squad_group_definition const &); /* compiler_generated() */
	s_squad_group_definition(); /* compiler_generated() */
};
static_assert(sizeof(s_squad_group_definition) == 40, "Invalid s_squad_group_definition size");

#pragma pack(push, 4)
struct s_squad_patrol_definition
{
	s_ai_conditions place_on; // 0x0
	unsigned long name; // 0xC
	c_ai_point3d point; // 0x10
	real_euler_angles2d facing; // 0x20
	float roll; // 0x28
	unsigned long formation_type; // 0x2C
	float initial_movement_distance; // 0x30
	c_enum<enum e_squad_movement_mode,short> initial_movement_mode; // 0x34
	c_tag_block_index<s_hs_script,short> placement_script; // 0x36
	tag_string placement_script_name; // 0x38
	unsigned long initial_state; // 0x58
	c_tag_block_index<s_cs_point_set,short> point_set; // 0x5C
	c_enum<enum e_squad_patrol_mode,short> patrol_mode; // 0x5E
	c_tag_block<s_squad_patrol_waypoint_definition> patrol_points; // 0x60
	s_squad_patrol_definition(s_squad_patrol_definition &); /* compiler_generated() */
	s_squad_patrol_definition(s_squad_patrol_definition const &); /* compiler_generated() */
	s_squad_patrol_definition(); /* compiler_generated() */
	s_squad_patrol_definition &operator=(s_squad_patrol_definition &); /* compiler_generated() */
	s_squad_patrol_definition &operator=(s_squad_patrol_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_squad_patrol_definition) == 108, "Invalid s_squad_patrol_definition size");

struct s_squad_definition
{
	tag_string name; // 0x0
	c_flags<enum e_squad_flags,long> flags; // 0x20
	c_enum<enum e_squad_team,short> team; // 0x24
	c_tag_block_index<s_squad_group_definition,short> parent; // 0x26
	c_tag_block_index<s_zone_definition,short> initial_zone; // 0x28
	c_tag_block_index<s_objective,short> initial_objective; // 0x2A
	c_tag_block_index<s_task,short> initial_task; // 0x2C
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x2E
	c_tag_block<s_squad_patrol_definition> spawn_formations; // 0x30
	c_tag_block<s_spawn_point_definition> spawn_points; // 0x3C
	unsigned long module_id; // 0x48
	s_tag_reference_short squad_template; // 0x4C
	c_tag_block<s_cell_definition> designer_cells; // 0x50
	c_tag_block<s_cell_definition> template_cells; // 0x5C
	s_squad_definition(s_squad_definition &); /* compiler_generated() */
	s_squad_definition(s_squad_definition const &); /* compiler_generated() */
	s_squad_definition(); /* compiler_generated() */
	s_squad_definition &operator=(s_squad_definition &); /* compiler_generated() */
	s_squad_definition &operator=(s_squad_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_squad_definition) == 104, "Invalid s_squad_definition size");

struct s_task
{
	c_flags<enum e_task_flags,unsigned short> flags; // 0x0
	s_ai_conditions place_on; // 0x2
	c_enum<enum e_squad_movement_mode,short> movement; // 0xE
	c_enum<enum e_squad_follow_mode,short> follow; // 0x10
	c_tag_block_index<s_squad_definition,short> follow_squad; // 0x12
	float follow_radius; // 0x14
	c_flags<enum e_squad_follow_player_flags,unsigned short> follow_players; // 0x18
	unsigned char __pad0[2]; // 0x1A
	c_tag_block<s_follow_firing_point_query> follow_firing_point_query; // 0x1C
	tag_string entry_script_name; // 0x28
	tag_string command_script_name; // 0x48
	tag_string exhaustion_script_name; // 0x68
	c_tag_block_index<s_hs_script,short> entry_script_index; // 0x88
	c_tag_block_index<s_hs_script,short> command_script_index; // 0x8A
	c_tag_block_index<s_hs_script,short> exhaustion_script_index; // 0x8C
	c_tag_block_flags<s_squad_group_definition,unsigned short> squad_group_filter; // 0x8E
	c_enum<enum e_task_dialogue_type,short> dialogue_type; // 0x90
	c_flags<enum e_task_runtime_flags,unsigned short> runtime_flags; // 0x92
	c_tag_block<s_task_pureform_distribution> pureform_distribution; // 0x94
	unsigned char __pad1[4]; // 0xA0
	unsigned long name; // 0xA4
	short heirarchy; // 0xA8
	c_tag_block_index<s_task,short> previous_task; // 0xAA
	c_tag_block_index<s_task,short> next_task; // 0xAC
	c_tag_block_index<s_task,short> parent_task; // 0xAE
	c_tag_block<s_task_activation_script> activation_script; // 0xB0
	c_tag_block_index<s_hs_script,short> script_index; // 0xBC
	short lifetime_count; // 0xBE
	c_flags<enum e_task_filter_flags,unsigned short> filter_flags; // 0xC0
	c_enum<enum e_task_filter,short> filter; // 0xC2
	short_bounds capacity; // 0xC4
	short max_body_count; // 0xC8
	c_enum<enum e_squad_attitude,short> attitude; // 0xCA
	float min_strength; // 0xCC
	c_tag_block<s_task_area> areas; // 0xD0
	c_tag_block<s_task_direction> direction; // 0xDC
	s_task(s_task &); /* compiler_generated() */
	s_task(s_task const &); /* compiler_generated() */
	s_task(); /* compiler_generated() */
	s_task &operator=(s_task &); /* compiler_generated() */
	s_task &operator=(s_task const &); /* compiler_generated() */
};
static_assert(sizeof(s_task) == 232, "Invalid s_task size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_AI_SQUADS_HPP__
