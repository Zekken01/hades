#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_VOICE_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_VOICE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"
#include "Blam/networking/session/network_session_parameters_matchmaking.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_voice_repeater;
struct s_network_session_parameter_voice_repeater;

/* ---------- constants */

/* ---------- definitions */

class c_network_session_parameter_voice_repeater :
	public c_generic_network_session_parameter<s_network_session_parameter_voice_repeater>
{
public:
	c_network_session_parameter_voice_repeater(c_network_session_parameter_voice_repeater &); /* compiler_generated() */
	c_network_session_parameter_voice_repeater(c_network_session_parameter_voice_repeater const &); /* compiler_generated() */
	c_network_session_parameter_voice_repeater(); /* compiler_generated() */
	c_network_session_parameter_voice_repeater &operator=(c_network_session_parameter_voice_repeater &); /* compiler_generated() */
	c_network_session_parameter_voice_repeater &operator=(c_network_session_parameter_voice_repeater const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_voice_repeater) == 56, "Invalid c_network_session_parameter_voice_repeater size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_VOICE_HPP__
