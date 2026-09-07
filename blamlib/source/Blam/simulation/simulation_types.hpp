#ifndef __BLAM_SIMULATION_SIMULATION_TYPES_HPP__
#define __BLAM_SIMULATION_SIMULATION_TYPES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

enum e_simulation_entity_type
{
	_simulation_entity_type_game_engine_player = 10, // 0x000A
	_simulation_entity_type_game_statbrg = 11, // 0x000B
	_simulation_entity_type_breakable_surface_group = 12, // 0x000C
	_simulation_entity_type_map_variant = 13, // 0x000D
	_simulation_entity_type_unit = 14, // 0x000E
	_simulation_entity_type_item = 15, // 0x000F
	_simulation_entity_type_generic = 16, // 0x0010
	_simulation_entity_type_generic_garbage = 17, // 0x0011
	_simulation_entity_type_vehicle = 18, // 0x0012
	_simulation_entity_type_projectile = 19, // 0x0013
	_simulation_entity_type_weapon = 20, // 0x0014
	_simulation_entity_type_device = 21, // 0x0015
	k_simulation_entity_type_maximum_count = 32, // 0x0020 ' '
};

enum e_simulation_event_type
{
	_simulation_event_type_aftermath = 0, // 0x0000
	_simulation_event_type_damage_section_response = 1, // 0x0001
	_simulation_event_type_damage_breakable_surface_damage = 2, // 0x0002
	_simulation_event_type_projectile_attached = 3, // 0x0003
	_simulation_event_type_projectile_detonate = 4, // 0x0004
	_simulation_event_type_projectile_impact_effect = 5, // 0x0005
	_simulation_event_type_projectile_object_impact_effect = 6, // 0x0006
	_simulation_event_type_effect_on_pos = 7, // 0x0007
	_simulation_event_type_game_engine = 8, // 0x0008
	_simulation_event_type_unit_board_vehicle = 9, // 0x0009
	_simulation_event_type_unit_pickup = 10, // 0x000A
	_simulation_event_type_weapon_effect = 11, // 0x000B
	_simulation_event_type_weapon_empty_click = 12, // 0x000C
	_simulation_event_type_hit_marker = 13, // 0x000D
	_simulation_event_type_unit_exit_vehicle = 14, // 0x000E
	_simulation_event_type_unit_assassinate = 15, // 0x000F
	_simulation_event_type_player_taunt_request = 16, // 0x0010
	_simulation_event_type_weapon_fire = 17, // 0x0011
	_simulation_event_type_unit_equipment_use = 18, // 0x0012
	_simulation_event_type_weapon_reload = 19, // 0x0013
	_simulation_event_type_unit_throw_initiate = 20, // 0x0014
	_simulation_event_type_melee_initiate = 21, // 0x0015
	_simulation_event_type_weapon_pickup = 22, // 0x0016
	_simulation_event_type_weapon_put_away = 23, // 0x0017
	_simulation_event_type_weapon_drop = 24, // 0x0018
	_simulation_event_type_vehicle_flip = 25, // 0x0019
	_simulation_event_type_vehicle_trick = 26, // 0x001A
	_simulation_event_type_device_touch = 27, // 0x001B
	_simulation_event_type_unit_throw_release = 28, // 0x001C
	_simulation_event_type_unit_melee_damage = 29, // 0x001D
	_simulation_event_type_unit_melee_clang = 30, // 0x001E
	_simulation_event_type_unit_enter_vehicle = 31, // 0x001F
	_simulation_event_type_game_engine_request_boot_player = 32, // 0x0020 ' '
	_simulation_event_type_player_respawn_request = 33, // 0x0021 '!'
	_simulation_event_type_player_force_base_respawn = 34, // 0x0022 '"'
	_simulation_event_type_unit_equipment_pickup = 35, // 0x0023 '#'
	_simulation_event_type_projectile_supercombine_request = 36, // 0x0024 '$'
	_simulation_event_type_object_refresh = 37, // 0x0025 '%'
	_simulation_event_type_player_editor_request = 38, // 0x0026 '&'
	_simulation_event_type_hs_wake_script = 39, // 0x0027 '''
	_simulation_event_type_hs_sync_global = 40, // 0x0028 '('
	k_simulation_event_type_maximum_count = 64, // 0x0040 '@'
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SIMULATION_SIMULATION_TYPES_HPP__
