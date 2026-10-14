#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_GAME_VARIANT_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_GAME_VARIANT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/game_variant.hpp"
#include "Blam/networking/session/network_session_parameter_saved_film.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_game_variant;
struct c_game_variant;
struct s_network_session_parameter_game_variant;

/* ---------- constants */

/* ---------- definitions */

struct s_network_session_parameter_game_variant
{
	unsigned char __pad0[4]; // 0x0
	c_game_variant game_variant; // 0x4
	s_network_session_parameter_game_variant(s_network_session_parameter_game_variant &); /* compiler_generated() */
	s_network_session_parameter_game_variant(s_network_session_parameter_game_variant const &); /* compiler_generated() */
	s_network_session_parameter_game_variant(); /* compiler_generated() */
	s_network_session_parameter_game_variant &operator=(s_network_session_parameter_game_variant &); /* compiler_generated() */
	s_network_session_parameter_game_variant &operator=(s_network_session_parameter_game_variant const &); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_parameter_game_variant) == 616, "Invalid s_network_session_parameter_game_variant size");

class c_network_session_parameter_game_variant :
	public c_network_session_parameter_chunked<s_network_session_parameter_game_variant,6144>
{
public:
	c_network_session_parameter_game_variant(c_network_session_parameter_game_variant &); /* compiler_generated() */
	c_network_session_parameter_game_variant(c_network_session_parameter_game_variant const &); /* compiler_generated() */
	c_network_session_parameter_game_variant(); /* compiler_generated() */
	c_network_session_parameter_game_variant &operator=(c_network_session_parameter_game_variant &); /* compiler_generated() */
	c_network_session_parameter_game_variant &operator=(c_network_session_parameter_game_variant const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_game_variant) == 13680, "Invalid c_network_session_parameter_game_variant size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_GAME_VARIANT_HPP__
