#ifndef __BLAM_GAME_PLAYER_CONFIGURATION_HPP__
#define __BLAM_GAME_PLAYER_CONFIGURATION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Player/PlayerCharacterSystem.hpp"

/* ---------- forward declarations */

struct s_player_appearance;
struct s_player_configuration;
struct s_player_configuration_from_client;
struct s_player_configuration_from_host;
struct s_player_identifier;

/* ---------- constants */

enum e_player_configuration_encoding_type
{
	_player_configuration_encoding_type_full = 0,
	_player_configuration_encoding_type_compact,
};

/* ---------- definitions */

struct s_player_identifier
{
	long value1; // 0x0
	long value2; // 0x4
};
static_assert(sizeof(s_player_identifier) == 8, "Invalid s_player_identifier size");

struct s_player_configuration_from_client
{
	wchar_t player_name[16]; // 0x0
	unsigned char multiplayer_team; // 0x20
	unsigned long hopper_access_flags; // 0x24
	unsigned long cheating_flags; // 0x28
	unsigned long user_experience_flags; // 0x2C
};
static_assert(sizeof(s_player_configuration_from_client) == 48, "Invalid s_player_configuration_from_client size");
static_assert(offsetof(s_player_configuration_from_client, hopper_access_flags) == 0x24, "s_player_configuration_from_client::hopper_access_flags moved when its reconstructed padding was removed");

struct s_player_configuration_from_host
{
	unsigned long long player_uid; // 0x0
	wchar_t player_name[16]; // 0x8
	long team; // 0x28
	long player_assigned_team; // 0x2C
	s_player_appearance appearance; // 0x30
private:
	unsigned char unused[3216]; // 0x960
public:
	_inline s_player_configuration_from_host() = default; /* compiler_generated() */
};
static_assert(sizeof(s_player_configuration_from_host) == 5616, "Invalid s_player_configuration_from_host size");

struct s_player_configuration
{
	s_player_configuration_from_client client; // 0x0
	s_player_configuration_from_host host; // 0x30
	_inline s_player_configuration() = default; /* compiler_generated() */
};
static_assert(sizeof(s_player_configuration) == 5664, "Invalid s_player_configuration size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_PLAYER_CONFIGURATION_HPP__
