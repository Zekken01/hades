#ifndef __BLAM_GAME_GAME_ENGINE_GLOBALS_HPP__
#define __BLAM_GAME_GAME_ENGINE_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_engine_teleporters.hpp"
#include "Blam/game/game_statborg.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/simulation/game_interface/simulation_game_engine_player.hpp"
#include "mods/map_variant_loader.hpp"

/* ---------- forward declarations */

struct c_candy_monitor_manager;
struct c_game_statborg;
struct c_teleporter_area;
struct real_vector3d;
struct s_game_engine_globals;
struct s_game_engine_queued_event;
struct s_map_variant;
struct s_multiplayer_weapon_tracker;
struct s_simulation_player_netdebug_data;

/* ---------- constants */

/* ---------- definitions */

struct s_multiplayer_weapon_tracker
{
	long weapon_index; // 0x0
	short multiplayer_weapon_identifier; // 0x4
	unsigned char __pad0[2]; // 0x6
	long owner_unit_index; // 0x8
	long owner_player_index; // 0xC
};
static_assert(sizeof(s_multiplayer_weapon_tracker) == 16, "Invalid s_multiplayer_weapon_tracker size");

struct s_game_engine_globals
{
	public:
#pragma pack(push, 4)
	struct s_game_engine_score_list
	{
		long player_indices[16]; // 0x0
		long team_indices[8]; // 0x40
		unsigned char player_compound_ranks[16]; // 0x60
		unsigned char team_compound_ranks[8]; // 0x70
		short player_count; // 0x78
		short team_count; // 0x7A
	};
#pragma pack(pop)
	static_assert(sizeof(s_game_engine_score_list) == 124, "Invalid s_game_engine_score_list size");
	struct s_dead_player_info
	{
		long player_index; // 0x0
		long death_game_time; // 0x4
		real_vector3d position; // 0x8
		unsigned char __pad0[60]; // 0x14
	};
	static_assert(sizeof(s_dead_player_info) == 80, "Invalid s_dead_player_info size");
#pragma pack(push, 4)
	struct s_unknown_waypoint
	{
		bool death_acknowledged; // 0x0
		unsigned char __pad0[3]; // 0x1
		real_point3d death_position; // 0x4
		short respawn_timer1; // 0x10
		short respawn_timer2; // 0x12
		long dead_unit_index; // 0x14
		char waypoint_action; // 0x18
		unsigned char __pad1[3]; // 0x19
	};
#pragma pack(pop)
	static_assert(sizeof(s_unknown_waypoint) == 28, "Invalid s_unknown_waypoint size");
	public:
	unsigned long flags; // 0x0
	unsigned short allowed_teams_mask; // 0x4
	unsigned short field_6; // 0x6
	unsigned short unknown_team_mask; // 0x8
	unsigned short valid_team_mask; // 0xA
	unsigned short active_team_mask; // 0xC
	unsigned short ever_active_team_mask; // 0xE
	unsigned short team_designator_to_team_index[8]; // 0x10
	unsigned short field_20; // 0x20
	unsigned char team_lives[8]; // 0x22
	unsigned char __pad0[2]; // 0x2A
	long gamestate_index; // 0x2C
	long statborg_gamestate_index; // 0x30
	long players[16]; // 0x34
	long unused1; // 0x74
	s_map_variant map_variant; // 0x78
	short round_state; // 0xE108
	short round_index; // 0xE10A
	long round_start_time; // 0xE10C
	char round_condition_flags; // 0xE110
	unsigned char __pad1[3]; // 0xE111
	s_game_engine_score_list score_list; // 0xE114
	unsigned char engine_storage[6144]; // 0xE190
	unsigned short seconds_remaining; // 0xF990
	unsigned char __pad2[2]; // 0xF992
	long round_time_remaining_ticks; // 0xF994
	float fade_to_black_amount[4]; // 0xF998
	unsigned char fade_to_black_active_user_mask; // 0xF9A8
	unsigned char __pad3[1]; // 0xF9A9
	unsigned short game_over_timer; // 0xF9AA
	unsigned short next_shot_id; // 0xF9AC
	unsigned char __pad4[2]; // 0xF9AE
	s_dead_player_info player_deaths[16]; // 0xF9B0
	c_game_statborg statborg; // 0xFEB0
	long unused2; // 0x102D4
	s_unknown_waypoint unknown_waypoints[16]; // 0x102D8
	long player_netdebug_last_update_time; // 0x10498
	s_simulation_player_netdebug_data player_netdebug[16]; // 0x1049C
	c_candy_monitor_manager candy_monitor_manager; // 0x1059C
	long round_end_time; // 0x13D9C
	long desired_round_state; // 0x13DA0
	bool game_ended; // 0x13DA4
	unsigned char __pad5[3]; // 0x13DA5
	long garbage_collection_level; // 0x13DA8
	long unused3; // 0x13DAC
	long current_game_engine_type; // 0x13DB0
	long multiplayer_weapon_count; // 0x13DB4
	s_multiplayer_weapon_tracker multiplayer_weapon[8]; // 0x13DB8
	c_area_set<c_teleporter_area,32> telporters; // 0x13E38
	long queued_event_count; // 0x14C48
	s_game_engine_queued_event queued_events[64]; // 0x14C4C
	long respawn_stagger_game_time; // 0x1584C
	long respawn_stagger_seconds; // 0x15850
	long unused4; // 0x15854
	s_game_engine_globals(s_game_engine_globals &); /* compiler_generated() */
	s_game_engine_globals(s_game_engine_globals const &); /* compiler_generated() */
	s_game_engine_globals(); /* compiler_generated() */
	s_game_engine_globals &operator=(s_game_engine_globals &); /* compiler_generated() */
	s_game_engine_globals &operator=(s_game_engine_globals const &); /* compiler_generated() */
};
static_assert(sizeof(s_game_engine_globals) == 88152, "Invalid s_game_engine_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_GAME_ENGINE_GLOBALS_HPP__
