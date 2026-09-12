#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_STATUS_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_STATUS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/player_configuration.hpp"

/* ---------- forward declarations */

struct s_network_session_status_data;
struct s_network_session_status_data_header;
struct s_network_session_status_data_player;
struct s_player_configuration;

/* ---------- constants */

/* ---------- definitions */

struct s_network_session_status_data_header
{
	short protocol; // 0x0
	short platform; // 0x2
	long executable_type; // 0x4
	long executable_version; // 0x8
	long compatible_version; // 0xC
};
static_assert(sizeof(s_network_session_status_data_header) == 16, "Invalid s_network_session_status_data_header size");

struct s_network_session_status_data_player
{
	unsigned long long id; // 0x0
	s_player_configuration configuration; // 0x8
	s_network_session_status_data_player(); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_status_data_player) == 5672, "Invalid s_network_session_status_data_player size");

struct s_network_session_status_data
{
	s_network_session_status_data_header header; // 0x0
	long session_mode; // 0x10
	long field_14; // 0x14
	long session_class; // 0x18
	long session_type; // 0x1C
	long privacy_mode; // 0x20
	wchar_t session_name[32]; // 0x24
	short life_cycle_state; // 0x64
	unsigned char session_id[16]; // 0x66
	unsigned char host_secure_address[16]; // 0x76
	unsigned char session_key[16]; // 0x86
	short capacity; // 0x96
	short public_slots; // 0x98
	short private_slots; // 0x9A
	short public_players; // 0x9C
	short private_players; // 0x9E
	short game_mode; // 0xA0
	short game_state; // 0xA2
	short network_game_type; // 0xA4
	char playlist_name[16]; // 0xA6
	long game_engine_type; // 0xB8
	wchar_t game_engine_variant_name[16]; // 0xBC
	long campaign_id; // 0xDC
	long campaign_difficulty; // 0xE0
	long map_id; // 0xE4
	short campaign_insertion_point; // 0xE8
	wchar_t map_variant_name[16]; // 0xEA
	wchar_t saved_film_name[16]; // 0x10A
	char game_has_teams; // 0x12A
	short game_team_count; // 0x12C
	short target_score; // 0x12E
	short current_score; // 0x130
	short player_count; // 0x132
	__int32 field_134; // 0x134
	s_network_session_status_data_player players[16]; // 0x138
	long player_encoded_count; // 0x163B8
	long game_timer_type; // 0x163BC
	long game_timer_seconds; // 0x163C0
	long valid_game_team_scores; // 0x163C4
	long game_team_scores[8]; // 0x163C8
	long gather_party_properties; // 0x163E8
	unsigned char unknown[208]; // 0x163EC
	s_network_session_status_data(); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_status_data) == 91328, "Invalid s_network_session_status_data size");
static_assert(offsetof(s_network_session_status_data, game_engine_type) == 0xB8, "s_network_session_status_data::game_engine_type moved when its reconstructed padding was removed");
static_assert(offsetof(s_network_session_status_data, game_team_count) == 0x12C, "s_network_session_status_data::game_team_count moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_STATUS_HPP__
