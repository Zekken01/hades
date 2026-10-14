#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_MAP_VARIANT_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_MAP_VARIANT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_parameter_saved_film.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"
#include "mods/map_variant_loader.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_map_variant;
struct s_map_variant;
struct s_network_session_parameter_map_variant;

/* ---------- constants */

/* ---------- definitions */

struct s_network_session_parameter_map_variant
{
	unsigned char __pad0[8]; // 0x0
	s_map_variant map_variant; // 0x8
	s_network_session_parameter_map_variant(s_network_session_parameter_map_variant &); /* compiler_generated() */
	s_network_session_parameter_map_variant(s_network_session_parameter_map_variant const &); /* compiler_generated() */
	s_network_session_parameter_map_variant(); /* compiler_generated() */
	s_network_session_parameter_map_variant &operator=(s_network_session_parameter_map_variant &); /* compiler_generated() */
	s_network_session_parameter_map_variant &operator=(s_network_session_parameter_map_variant const &); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_parameter_map_variant) == 57496, "Invalid s_network_session_parameter_map_variant size");

class c_network_session_parameter_map_variant :
	public c_network_session_parameter_chunked<s_network_session_parameter_map_variant,28672>
{
public:
	c_network_session_parameter_map_variant(c_network_session_parameter_map_variant &); /* compiler_generated() */
	c_network_session_parameter_map_variant(c_network_session_parameter_map_variant const &); /* compiler_generated() */
	c_network_session_parameter_map_variant(); /* compiler_generated() */
	c_network_session_parameter_map_variant &operator=(c_network_session_parameter_map_variant &); /* compiler_generated() */
	c_network_session_parameter_map_variant &operator=(c_network_session_parameter_map_variant const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_map_variant) == 172496, "Invalid c_network_session_parameter_map_variant size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_MAP_VARIANT_HPP__
