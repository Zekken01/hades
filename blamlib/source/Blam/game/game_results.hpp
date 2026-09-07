#ifndef __BLAM_GAME_GAME_RESULTS_HPP__
#define __BLAM_GAME_GAME_RESULTS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct c_game_results;
struct c_game_variant;
struct s_game_results_events;
struct s_game_results_hopper;
struct s_game_results_machine_data;
struct s_game_results_player_data;
struct s_game_results_player_kill_statistics;
struct s_game_results_player_medal_statistics;
struct s_game_results_player_statistics;
struct s_game_results_player_vs_player_statistics;
struct s_game_results_player_weapon_statistics;
struct s_game_results_statistics;
struct s_game_results_team_data;
struct s_game_results_team_statistics;
struct s_kill;
struct s_player_configuration;

/* ---------- constants */

/* ---------- definitions */

struct s_game_results_player_kill_statistics
{
	unsigned short kills; // 0x0
	unsigned short killed_by; // 0x2
};
static_assert(sizeof(s_game_results_player_kill_statistics) == 4, "Invalid s_game_results_player_kill_statistics size");

struct s_game_results_player_vs_player_statistics
{
	s_game_results_player_kill_statistics stats_against_each_player[16]; // 0x0
};
static_assert(sizeof(s_game_results_player_vs_player_statistics) == 64, "Invalid s_game_results_player_vs_player_statistics size");

struct s_game_results_player_medal_statistics
{
	unsigned short earned; // 0x0
};
static_assert(sizeof(s_game_results_player_medal_statistics) == 2, "Invalid s_game_results_player_medal_statistics size");

struct s_game_results_player_weapon_statistics
{
	unsigned short initialized; // 0x0
	unsigned short kills; // 0x2
	unsigned short killed_by; // 0x4
	unsigned short betrayals_with; // 0x6
	unsigned short suicides_with; // 0x8
	unsigned short headshots_with; // 0xA
};
static_assert(sizeof(s_game_results_player_weapon_statistics) == 12, "Invalid s_game_results_player_weapon_statistics size");

struct s_game_results_player_statistics
{
	unsigned short games_played; // 0x0
	unsigned short games_completed; // 0x2
	unsigned short games_won; // 0x4
	unsigned short games_tied; // 0x6
	unsigned short rounds_completed; // 0x8
	unsigned short rounds_won; // 0xA
	unsigned short in_round_score; // 0xC
	unsigned short in_game_total_score; // 0xE
	unsigned short kills; // 0x10
	unsigned short assists; // 0x12
	unsigned short deaths; // 0x14
	unsigned short betrayals; // 0x16
	unsigned short suicides; // 0x18
	unsigned short best_streak; // 0x1A
	unsigned short seconds_alive; // 0x1C
	unsigned short ctf_flag_scores; // 0x1E
	unsigned short ctf_flag_grabs; // 0x20
	unsigned short carriers_killed; // 0x22
	unsigned short ctf_flag_returns; // 0x24
	unsigned short assault_bomb_arms; // 0x26
	unsigned short assault_bomb_grabs; // 0x28
	unsigned short assault_bomb_disarms; // 0x2A
	unsigned short assault_bomb_detonations; // 0x2C
	unsigned short oddball_time_with_ball; // 0x2E
	unsigned short oddball_unused; // 0x30
	unsigned short oddball_kills_as_carrier; // 0x32
	unsigned short oddball_ball_carrier_kills; // 0x34
	unsigned short unknown23; // 0x36
	unsigned short kings_killed; // 0x38
	unsigned short time_in_hill; // 0x3A
	unsigned short time_controlling_hill; // 0x3C
	unsigned short unused1; // 0x3E
	unsigned short unused2; // 0x40
	unsigned short unused3; // 0x42
	unsigned short vip_takedowns; // 0x44
	unsigned short vip_kills_as_vip; // 0x46
	unsigned short vip_guard_time; // 0x48
	unsigned short vip_time_as_vip; // 0x4A
	unsigned short vip_lives_as_vip; // 0x4C
	unsigned short juggernaut_kills; // 0x4E
	unsigned short kills_as_juggernaut; // 0x50
	unsigned short time_as_juggernaut; // 0x52
	unsigned short total_wp; // 0x54
	unsigned short juggernaut_unused; // 0x56
	unsigned short territories_owned; // 0x58
	unsigned short territories_captured; // 0x5A
	unsigned short territories_ousts; // 0x5C
	unsigned short time_in_territory; // 0x5E
	unsigned short infection_zombie_kills; // 0x60
	unsigned short infection_infections; // 0x62
	unsigned short infection_time_as_human; // 0x64
	s_game_results_player_medal_statistics medals[58]; // 0x66
	unsigned short achievements[47]; // 0xDA
	s_game_results_player_weapon_statistics weapon_stats[64]; // 0x138
};
static_assert(sizeof(s_game_results_player_statistics) == 1080, "Invalid s_game_results_player_statistics size");

struct s_game_results_team_statistics
{
	unsigned short games_played; // 0x0
	unsigned short games_completed; // 0x2
	unsigned short games_won; // 0x4
	unsigned short games_tied; // 0x6
	unsigned short rounds_completed; // 0x8
	unsigned short rounds_won; // 0xA
	unsigned short in_round_score; // 0xC
	unsigned short in_game_total_score; // 0xE
	unsigned short kills; // 0x10
	unsigned short assists; // 0x12
	unsigned short deaths; // 0x14
	unsigned short betrayals; // 0x16
	unsigned short suicides; // 0x18
	unsigned short best_streak; // 0x1A
	unsigned short seconds_alive; // 0x1C
	unsigned short ctf_flag_scores; // 0x1E
	unsigned short ctf_flag_grabs; // 0x20
	unsigned short carriers_killed; // 0x22
	unsigned short ctf_flag_returns; // 0x24
	unsigned short assault_bomb_arms; // 0x26
	unsigned short assault_bomb_grabs; // 0x28
	unsigned short assault_bomb_disarms; // 0x2A
	unsigned short assault_bomb_detonations; // 0x2C
	unsigned short oddball_time_with_ball; // 0x2E
	unsigned short oddball_unused; // 0x30
	unsigned short oddball_kills_as_carrier; // 0x32
	unsigned short oddball_ball_carrier_kills; // 0x34
	unsigned short unknown23; // 0x36
	unsigned short kings_killed; // 0x38
	unsigned short time_in_hill; // 0x3A
	unsigned short time_controlling_hill; // 0x3C
	unsigned short unused1; // 0x3E
	unsigned short unused2; // 0x40
	unsigned short unused3; // 0x42
	unsigned short vip_takedowns; // 0x44
	unsigned short vip_kills_as_vip; // 0x46
	unsigned short vip_guard_time; // 0x48
	unsigned short vip_time_as_vip; // 0x4A
	unsigned short vip_lives_as_vip; // 0x4C
	unsigned short juggernaut_kills; // 0x4E
	unsigned short kills_as_juggernaut; // 0x50
	unsigned short time_as_juggernaut; // 0x52
	unsigned short total_wp; // 0x54
	unsigned short juggernaut_unused; // 0x56
	unsigned short territories_owned; // 0x58
	unsigned short territories_captured; // 0x5A
	unsigned short territories_ousts; // 0x5C
	unsigned short time_in_territory; // 0x5E
	unsigned short infection_zombie_kills; // 0x60
	unsigned short infection_infections; // 0x62
	unsigned short infection_time_as_human; // 0x64
};
static_assert(sizeof(s_game_results_team_statistics) == 102, "Invalid s_game_results_team_statistics size");

#pragma pack(push, 1)
struct s_game_results_events
{
	c_enum<enum e_game_results_event_type,char> type; // 0x0
	union
	{
		struct s_kill
		{
			unsigned char killing_player_index; // 0x0
			unsigned char dead_player_index; // 0x1
			unsigned char padding; // 0x2
			real_point3d killing_player_position; // 0x3
			real_point3d dead_player_position; // 0xF
			c_enum<enum e_damage_reporting_type,long> tracked_damage_type; // 0x1B
			s_kill(s_kill &); /* compiler_generated() */
			s_kill(s_kill const &); /* compiler_generated() */
			s_kill(); /* compiler_generated() */
			s_kill &operator=(s_kill &); /* compiler_generated() */
			s_kill &operator=(s_kill const &); /* compiler_generated() */
		} kill; // 0x1
		struct
		{
			unsigned char player_index; // 0x0
			unsigned char unknown2; // 0x1
			unsigned char padding; // 0x2
			real_point3d player_position; // 0x3
			long carry; // 0xF
			long carry_type; // 0x13
		} carry; // 0x1
		struct
		{
			unsigned char player_index; // 0x0
			unsigned char unknown2; // 0x1
			unsigned char padding; // 0x2
			real_point3d player_position; // 0x3
			long score; // 0xF
			long score_type; // 0x13
		} score; // 0x1
		unsigned char event_type_storage[31]; // 0x1
	};
	unsigned long time; // 0x20
};
#pragma pack(pop)
static_assert(sizeof(s_game_results_events) == 36, "Invalid s_game_results_events size");

struct s_game_results_player_data
{
	bool exists; // 0x0
	unsigned char __pad0[3]; // 0x1
	long field_4; // 0x4
	long field_8; // 0x8
	long field_C; // 0xC
	s_player_configuration configuration; // 0x10
	char standing; // 0x1630
	unsigned char __pad1[3]; // 0x1631
	long field_1634; // 0x1634
	long field_1638; // 0x1638
	short score; // 0x163C
	short field_163E; // 0x163E
	s_game_results_player_data(); /* compiler_generated() */
};
static_assert(sizeof(s_game_results_player_data) == 5696, "Invalid s_game_results_player_data size");

struct s_game_results_team_data
{
	bool exists; // 0x0
	char standing; // 0x1
	short score; // 0x2
};
static_assert(sizeof(s_game_results_team_data) == 4, "Invalid s_game_results_team_data size");

struct s_game_results_machine_data
{
	s_machine_identifier machine_identifier; // 0x0
	bool field_10; // 0x10
	bool host; // 0x11
	char field_12; // 0x12
	char field_13; // 0x13
	char field_14; // 0x14
	char field_15; // 0x15
	char field_16; // 0x16
	char field_17; // 0x17
	char field_18; // 0x18
	unsigned char __pad0[3]; // 0x19
	long field_1C; // 0x1C
};
static_assert(sizeof(s_game_results_machine_data) == 32, "Invalid s_game_results_machine_data size");

struct s_game_results_statistics
{
	s_game_results_player_statistics player[16]; // 0x0
	s_game_results_player_vs_player_statistics player_vs_player[16]; // 0x4380
	s_game_results_team_statistics team[16]; // 0x4780
};
static_assert(sizeof(s_game_results_statistics) == 19936, "Invalid s_game_results_statistics size");

#pragma pack(push, 4)
struct s_game_results_hopper
{
	unsigned short hopper_id; // 0x0
	wchar_t hopper_name[32]; // 0x2
	short field_42; // 0x42
	bool ranked; // 0x44
	bool team_based; // 0x45
	unsigned char __pad0[2]; // 0x46
	long field_48; // 0x48
	long field_4C; // 0x4C
	long field_50; // 0x50
	long field_54; // 0x54
	long field_58; // 0x58
};
#pragma pack(pop)
static_assert(sizeof(s_game_results_hopper) == 92, "Invalid s_game_results_hopper size");

struct c_game_results
{
	bool initialized; // 0x0
	bool finalized; // 0x1
	bool unreliable; // 0x2
	unsigned char __pad0[1]; // 0x3
	s_game_results_hopper hopper; // 0x4
	bool team_based; // 0x60
	unsigned char __pad1[7]; // 0x61
	unsigned long long game_id; // 0x68
	c_game_variant game_variant; // 0x70
	wchar_t map_variant_name[32]; // 0x2D4
	long map_id; // 0x314
	char scenario_path[260]; // 0x318
	bool started; // 0x41C
	unsigned char __pad2[3]; // 0x41D
	unsigned long start_time; // 0x420
	bool finished; // 0x424
	unsigned char __pad3[3]; // 0x425
	unsigned long finished_time; // 0x428
	unsigned char __pad4[4]; // 0x42C
	s_game_results_player_data players[16]; // 0x430
	s_game_results_team_data teams[16]; // 0x16830
	s_game_results_statistics statistics; // 0x16870
	s_game_results_events events[1000]; // 0x1B650
	s_game_results_machine_data machines[17]; // 0x242F0
};
static_assert(sizeof(c_game_results) == 148752, "Invalid c_game_results size");

/* ---------- prototypes */

extern s_game_results_player_statistics *game_results_get_player_stats(__int32 player_index);
extern s_game_results_player_vs_player_statistics *game_results_get_player_vs_player_stats(__int32 player_index);
extern s_game_results_events *game_results_get_event(__int32 event_index);

extern _inline c_game_results *game_results_get_current_results();

/* ---------- globals */

/* ---------- public code */

extern c_game_results *_sub_10B2D590();
_inline c_game_results *game_results_get_current_results() // 0x10B2D590
{
	mangled_x86(MANGLED_TODO, "?game_results_get_current_results@@YAPAUc_game_results@@XZ");
	// procedure flags: nofpo
	todo("implement");
	c_game_results * __result = _sub_10B2D590();
	return __result;
}

/* ---------- private code */

#endif // __BLAM_GAME_GAME_RESULTS_HPP__
