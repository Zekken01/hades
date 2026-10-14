#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_SAVED_FILM_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_SAVED_FILM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"
#include "mods/font_package.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_saved_film_game_options;
struct s_game_options;
struct s_network_session_parameter_saved_film_game_options;

/* ---------- constants */

/* ---------- definitions */

struct s_network_session_parameter_saved_film_game_options
{
	long playback_length_in_ticks; // 0x0
	long playback_start_tick; // 0x4
	s_game_options game_options; // 0x8
	s_network_session_parameter_saved_film_game_options(s_network_session_parameter_saved_film_game_options &); /* compiler_generated() */
	s_network_session_parameter_saved_film_game_options(s_network_session_parameter_saved_film_game_options const &); /* compiler_generated() */
	s_network_session_parameter_saved_film_game_options(); /* compiler_generated() */
	s_network_session_parameter_saved_film_game_options &operator=(s_network_session_parameter_saved_film_game_options &); /* compiler_generated() */
	s_network_session_parameter_saved_film_game_options &operator=(s_network_session_parameter_saved_film_game_options const &); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_parameter_saved_film_game_options) == 150352, "Invalid s_network_session_parameter_saved_film_game_options size");

class c_network_session_parameter_saved_film_game_options :
	public c_network_session_parameter_chunked<s_network_session_parameter_saved_film_game_options,34816>
{
public:
	c_network_session_parameter_saved_film_game_options(c_network_session_parameter_saved_film_game_options &); /* compiler_generated() */
	c_network_session_parameter_saved_film_game_options(c_network_session_parameter_saved_film_game_options const &); /* compiler_generated() */
	c_network_session_parameter_saved_film_game_options(); /* compiler_generated() */
	c_network_session_parameter_saved_film_game_options &operator=(c_network_session_parameter_saved_film_game_options &); /* compiler_generated() */
	c_network_session_parameter_saved_film_game_options &operator=(c_network_session_parameter_saved_film_game_options const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_saved_film_game_options) == 370496, "Invalid c_network_session_parameter_saved_film_game_options size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_SAVED_FILM_HPP__
