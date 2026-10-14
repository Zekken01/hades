#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_GAME_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_GAME_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/game_state.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"
#include "Blam/networking/session/network_session_parameters_matchmaking.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_countdown_timer;
class c_network_session_parameter_game_start_status;
class c_network_session_parameter_initial_participants;
class c_network_session_parameter_map;
class c_network_session_parameter_request_campaign_quit;
class c_network_session_parameter_synchronous_out_of_sync;
class c_network_session_parameter_ui_game_mode;
struct s_game_machine_options;
struct s_game_player_options;
struct s_network_session_parameter_countdown_timer;
struct s_network_session_parameter_game_start_status;
struct s_network_session_parameter_initial_participants;
struct s_network_session_parameter_map;
struct s_network_session_parameter_request_campaign_quit;
struct s_network_session_parameter_synchronous_out_of_sync;
struct s_network_session_privacy_mode;
struct s_saved_film_description;

/* ---------- constants */

/* ---------- definitions */

struct s_network_session_privacy_mode
{
	long privacy_mode; // 0x0
	unsigned char __pad0[12]; // 0x4
};
static_assert(sizeof(s_network_session_privacy_mode) == 16, "Invalid s_network_session_privacy_mode size");

class c_network_session_parameter_ui_game_mode :
	private c_generic_network_session_parameter<enum e_gui_game_mode>
{
public:
	c_network_session_parameter_ui_game_mode(c_network_session_parameter_ui_game_mode &); /* compiler_generated() */
	c_network_session_parameter_ui_game_mode(c_network_session_parameter_ui_game_mode const &); /* compiler_generated() */
	c_network_session_parameter_ui_game_mode(); /* compiler_generated() */
	c_network_session_parameter_ui_game_mode &operator=(c_network_session_parameter_ui_game_mode &); /* compiler_generated() */
	c_network_session_parameter_ui_game_mode &operator=(c_network_session_parameter_ui_game_mode const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_ui_game_mode) == 56, "Invalid c_network_session_parameter_ui_game_mode size");

struct s_network_session_parameter_map
{
	long campaign_id; // 0x0
	long map_id; // 0x4
	char map_name[128]; // 0x8
	unsigned char campagin_arguments[120]; // 0x88
	unsigned long game_progression_bit_vector[64]; // 0x100
};
static_assert(sizeof(s_network_session_parameter_map) == 512, "Invalid s_network_session_parameter_map size");

class c_network_session_parameter_map :
	private c_generic_network_session_parameter<s_network_session_parameter_map>
{
public:
	c_network_session_parameter_map(c_network_session_parameter_map &); /* compiler_generated() */
	c_network_session_parameter_map(c_network_session_parameter_map const &); /* compiler_generated() */
	c_network_session_parameter_map(); /* compiler_generated() */
	c_network_session_parameter_map &operator=(c_network_session_parameter_map &); /* compiler_generated() */
	c_network_session_parameter_map &operator=(c_network_session_parameter_map const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_map) == 1072, "Invalid c_network_session_parameter_map size");

struct s_network_session_parameter_initial_participants
{
	bool machine_options_exists; // 0x0
	s_game_machine_options machine_options; // 0x4
	bool player_options_exists; // 0x12C
	s_game_player_options player_options[16]; // 0x130
	s_network_session_parameter_initial_participants(); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_parameter_initial_participants) == 91440, "Invalid s_network_session_parameter_initial_participants size");
static_assert(offsetof(s_network_session_parameter_initial_participants, machine_options) == 0x4, "s_network_session_parameter_initial_participants::machine_options moved when its reconstructed padding was removed");
static_assert(offsetof(s_network_session_parameter_initial_participants, player_options) == 0x130, "s_network_session_parameter_initial_participants::player_options moved when its reconstructed padding was removed");

class c_network_session_parameter_initial_participants :
	public c_generic_network_session_parameter<s_network_session_parameter_initial_participants>
{
public:
	c_network_session_parameter_initial_participants(c_network_session_parameter_initial_participants &); /* compiler_generated() */
	c_network_session_parameter_initial_participants(c_network_session_parameter_initial_participants const &); /* compiler_generated() */
	c_network_session_parameter_initial_participants(); /* compiler_generated() */
	c_network_session_parameter_initial_participants &operator=(c_network_session_parameter_initial_participants &); /* compiler_generated() */
	c_network_session_parameter_initial_participants &operator=(c_network_session_parameter_initial_participants const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_initial_participants) == 182928, "Invalid c_network_session_parameter_initial_participants size");

#pragma pack(push, 4)
struct s_saved_film_description
{
	unsigned char field_0[796]; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_saved_film_description) == 796, "Invalid s_saved_film_description size");

class c_network_session_parameter_game_start_status :
	public c_generic_network_session_parameter<s_network_session_parameter_game_start_status>
{
public:
	c_network_session_parameter_game_start_status(c_network_session_parameter_game_start_status &); /* compiler_generated() */
	c_network_session_parameter_game_start_status(c_network_session_parameter_game_start_status const &); /* compiler_generated() */
	c_network_session_parameter_game_start_status(); /* compiler_generated() */
	c_network_session_parameter_game_start_status &operator=(c_network_session_parameter_game_start_status &); /* compiler_generated() */
	c_network_session_parameter_game_start_status &operator=(c_network_session_parameter_game_start_status const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_game_start_status) == 72, "Invalid c_network_session_parameter_game_start_status size");

class c_network_session_parameter_countdown_timer :
	public c_generic_network_session_parameter<s_network_session_parameter_countdown_timer>
{
public:
	c_network_session_parameter_countdown_timer(c_network_session_parameter_countdown_timer &); /* compiler_generated() */
	c_network_session_parameter_countdown_timer(c_network_session_parameter_countdown_timer const &); /* compiler_generated() */
	c_network_session_parameter_countdown_timer(); /* compiler_generated() */
	c_network_session_parameter_countdown_timer &operator=(c_network_session_parameter_countdown_timer &); /* compiler_generated() */
	c_network_session_parameter_countdown_timer &operator=(c_network_session_parameter_countdown_timer const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_countdown_timer) == 64, "Invalid c_network_session_parameter_countdown_timer size");

#pragma pack(push, 4)
class c_network_session_parameter_synchronous_out_of_sync :
	public c_generic_network_session_parameter<s_network_session_parameter_synchronous_out_of_sync>
{
public:
	c_network_session_parameter_synchronous_out_of_sync(c_network_session_parameter_synchronous_out_of_sync &); /* compiler_generated() */
	c_network_session_parameter_synchronous_out_of_sync(c_network_session_parameter_synchronous_out_of_sync const &); /* compiler_generated() */
	c_network_session_parameter_synchronous_out_of_sync(); /* compiler_generated() */
	c_network_session_parameter_synchronous_out_of_sync &operator=(c_network_session_parameter_synchronous_out_of_sync &); /* compiler_generated() */
	c_network_session_parameter_synchronous_out_of_sync &operator=(c_network_session_parameter_synchronous_out_of_sync const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
#pragma pack(pop)
static_assert(sizeof(c_network_session_parameter_synchronous_out_of_sync) == 52, "Invalid c_network_session_parameter_synchronous_out_of_sync size");

struct s_network_session_parameter_request_campaign_quit
{
	long field_0; // 0x0
	long field_4; // 0x4
};
static_assert(sizeof(s_network_session_parameter_request_campaign_quit) == 8, "Invalid s_network_session_parameter_request_campaign_quit size");

class c_network_session_parameter_request_campaign_quit :
	public c_generic_network_session_parameter<s_network_session_parameter_request_campaign_quit>
{
public:
	c_network_session_parameter_request_campaign_quit(c_network_session_parameter_request_campaign_quit &); /* compiler_generated() */
	c_network_session_parameter_request_campaign_quit(c_network_session_parameter_request_campaign_quit const &); /* compiler_generated() */
	c_network_session_parameter_request_campaign_quit(); /* compiler_generated() */
	c_network_session_parameter_request_campaign_quit &operator=(c_network_session_parameter_request_campaign_quit &); /* compiler_generated() */
	c_network_session_parameter_request_campaign_quit &operator=(c_network_session_parameter_request_campaign_quit const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_request_campaign_quit) == 64, "Invalid c_network_session_parameter_request_campaign_quit size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_GAME_HPP__
