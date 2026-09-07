#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_UI_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_UI_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"
#include "Blam/networking/session/network_session_parameters_matchmaking.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_lobby_vote_set;
struct s_network_session_parameter_lobby_vote_set;

/* ---------- constants */

/* ---------- definitions */

class c_network_session_parameter_lobby_vote_set :
	public c_generic_network_session_parameter<s_network_session_parameter_lobby_vote_set>
{
public:
	c_network_session_parameter_lobby_vote_set(c_network_session_parameter_lobby_vote_set &); /* compiler_generated() */
	c_network_session_parameter_lobby_vote_set(c_network_session_parameter_lobby_vote_set const &); /* compiler_generated() */
	c_network_session_parameter_lobby_vote_set(); /* compiler_generated() */
	c_network_session_parameter_lobby_vote_set &operator=(c_network_session_parameter_lobby_vote_set &); /* compiler_generated() */
	c_network_session_parameter_lobby_vote_set &operator=(c_network_session_parameter_lobby_vote_set const &); /* compiler_generated() */
	void __autoclassinit2(unsigned __int32); /* compiler_generated() */
};
static_assert(sizeof(c_network_session_parameter_lobby_vote_set) == 64, "Invalid c_network_session_parameter_lobby_vote_set size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_UI_HPP__
