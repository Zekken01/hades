#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_MATCHMAKING_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_MATCHMAKING_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_matchmaking_game_list;
class c_network_session_parameter_matchmaking_hopper;
class c_network_session_parameter_matchmaking_hopper_list;
class c_network_session_parameter_matchmaking_hopper_statistics;
class c_network_session_parameter_matchmaking_messaging;
class c_network_session_parameter_matchmaking_progress;
class c_network_session_parameter_matchmaking_progress_search_criteria;
class c_network_session_parameter_matchmaking_rematch_data;
struct s_network_session_parameter_matchmaking_game_list;
struct s_network_session_parameter_matchmaking_hopper;
struct s_network_session_parameter_matchmaking_hopper_list;
struct s_network_session_parameter_matchmaking_hopper_statistics;
struct s_network_session_parameter_matchmaking_messaging;
struct s_network_session_parameter_matchmaking_progress;
struct s_network_session_parameter_matchmaking_progress_search_criteria;
struct s_network_session_parameter_matchmaking_rematch_data;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_network_session_parameter_matchmaking_hopper_list
{
	unsigned char field_0[1700]; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_network_session_parameter_matchmaking_hopper_list) == 1700, "Invalid s_network_session_parameter_matchmaking_hopper_list size");

class c_network_session_parameter_matchmaking_hopper_list :
	private c_generic_network_session_parameter<s_network_session_parameter_matchmaking_hopper_list>
{
public:
	c_network_session_parameter_matchmaking_hopper_list(c_network_session_parameter_matchmaking_hopper_list &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper_list(c_network_session_parameter_matchmaking_hopper_list const &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper_list(); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper_list &operator=(c_network_session_parameter_matchmaking_hopper_list &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper_list &operator=(c_network_session_parameter_matchmaking_hopper_list const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_matchmaking_hopper_list) == 3448, "Invalid c_network_session_parameter_matchmaking_hopper_list size");

struct s_network_session_parameter_matchmaking_game_list
{
	unsigned char field_0[432]; // 0x0
};
static_assert(sizeof(s_network_session_parameter_matchmaking_game_list) == 432, "Invalid s_network_session_parameter_matchmaking_game_list size");

class c_network_session_parameter_matchmaking_game_list :
	private c_generic_network_session_parameter<s_network_session_parameter_matchmaking_game_list>
{
public:
	c_network_session_parameter_matchmaking_game_list(c_network_session_parameter_matchmaking_game_list &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_game_list(c_network_session_parameter_matchmaking_game_list const &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_game_list(); /* compiler_generated() */
	c_network_session_parameter_matchmaking_game_list &operator=(c_network_session_parameter_matchmaking_game_list &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_game_list &operator=(c_network_session_parameter_matchmaking_game_list const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_matchmaking_game_list) == 912, "Invalid c_network_session_parameter_matchmaking_game_list size");

#pragma pack(push, 4)
struct s_network_session_parameter_matchmaking_hopper
{
	unsigned char field_0[76]; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_network_session_parameter_matchmaking_hopper) == 76, "Invalid s_network_session_parameter_matchmaking_hopper size");

class c_network_session_parameter_matchmaking_hopper :
	private c_generic_network_session_parameter<s_network_session_parameter_matchmaking_hopper>
{
public:
	c_network_session_parameter_matchmaking_hopper(c_network_session_parameter_matchmaking_hopper &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper(c_network_session_parameter_matchmaking_hopper const &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper(); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper &operator=(c_network_session_parameter_matchmaking_hopper &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper &operator=(c_network_session_parameter_matchmaking_hopper const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_matchmaking_hopper) == 200, "Invalid c_network_session_parameter_matchmaking_hopper size");

struct s_network_session_parameter_matchmaking_progress
{
	char field_0[32]; // 0x0
};
static_assert(sizeof(s_network_session_parameter_matchmaking_progress) == 32, "Invalid s_network_session_parameter_matchmaking_progress size");

class c_network_session_parameter_matchmaking_progress :
	private c_generic_network_session_parameter<s_network_session_parameter_matchmaking_progress>
{
public:
	c_network_session_parameter_matchmaking_progress(c_network_session_parameter_matchmaking_progress &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_progress(c_network_session_parameter_matchmaking_progress const &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_progress(); /* compiler_generated() */
	c_network_session_parameter_matchmaking_progress &operator=(c_network_session_parameter_matchmaking_progress &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_progress &operator=(c_network_session_parameter_matchmaking_progress const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_matchmaking_progress) == 112, "Invalid c_network_session_parameter_matchmaking_progress size");

#pragma pack(push, 4)
struct s_network_session_parameter_matchmaking_progress_search_criteria
{
	char field_0[36]; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_network_session_parameter_matchmaking_progress_search_criteria) == 36, "Invalid s_network_session_parameter_matchmaking_progress_search_criteria size");

class c_network_session_parameter_matchmaking_progress_search_criteria :
	private c_generic_network_session_parameter<s_network_session_parameter_matchmaking_progress_search_criteria>
{
public:
	c_network_session_parameter_matchmaking_progress_search_criteria(c_network_session_parameter_matchmaking_progress_search_criteria &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_progress_search_criteria(c_network_session_parameter_matchmaking_progress_search_criteria const &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_progress_search_criteria(); /* compiler_generated() */
	c_network_session_parameter_matchmaking_progress_search_criteria &operator=(c_network_session_parameter_matchmaking_progress_search_criteria &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_progress_search_criteria &operator=(c_network_session_parameter_matchmaking_progress_search_criteria const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_matchmaking_progress_search_criteria) == 120, "Invalid c_network_session_parameter_matchmaking_progress_search_criteria size");

#pragma pack(push, 4)
struct s_network_session_parameter_matchmaking_rematch_data
{
	char field_0[964]; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_network_session_parameter_matchmaking_rematch_data) == 964, "Invalid s_network_session_parameter_matchmaking_rematch_data size");

class c_network_session_parameter_matchmaking_rematch_data :
	private c_generic_network_session_parameter<s_network_session_parameter_matchmaking_rematch_data>
{
public:
	c_network_session_parameter_matchmaking_rematch_data(c_network_session_parameter_matchmaking_rematch_data &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_rematch_data(c_network_session_parameter_matchmaking_rematch_data const &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_rematch_data(); /* compiler_generated() */
	c_network_session_parameter_matchmaking_rematch_data &operator=(c_network_session_parameter_matchmaking_rematch_data &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_rematch_data &operator=(c_network_session_parameter_matchmaking_rematch_data const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_matchmaking_rematch_data) == 1976, "Invalid c_network_session_parameter_matchmaking_rematch_data size");

class c_network_session_parameter_matchmaking_hopper_statistics :
	private c_generic_network_session_parameter<s_network_session_parameter_matchmaking_hopper_statistics>
{
public:
	c_network_session_parameter_matchmaking_hopper_statistics(c_network_session_parameter_matchmaking_hopper_statistics &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper_statistics(c_network_session_parameter_matchmaking_hopper_statistics const &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper_statistics(); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper_statistics &operator=(c_network_session_parameter_matchmaking_hopper_statistics &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_hopper_statistics &operator=(c_network_session_parameter_matchmaking_hopper_statistics const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_matchmaking_hopper_statistics) == 64, "Invalid c_network_session_parameter_matchmaking_hopper_statistics size");

struct s_network_session_parameter_matchmaking_messaging
{
	long field_0; // 0x0
	long field_4; // 0x4
	long field_8; // 0x8
};
static_assert(sizeof(s_network_session_parameter_matchmaking_messaging) == 12, "Invalid s_network_session_parameter_matchmaking_messaging size");

class c_network_session_parameter_matchmaking_messaging :
	public c_generic_network_session_parameter<s_network_session_parameter_matchmaking_messaging>
{
public:
	c_network_session_parameter_matchmaking_messaging(c_network_session_parameter_matchmaking_messaging &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_messaging(c_network_session_parameter_matchmaking_messaging const &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_messaging(); /* compiler_generated() */
	c_network_session_parameter_matchmaking_messaging &operator=(c_network_session_parameter_matchmaking_messaging &); /* compiler_generated() */
	c_network_session_parameter_matchmaking_messaging &operator=(c_network_session_parameter_matchmaking_messaging const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_matchmaking_messaging) == 72, "Invalid c_network_session_parameter_matchmaking_messaging size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_MATCHMAKING_HPP__
