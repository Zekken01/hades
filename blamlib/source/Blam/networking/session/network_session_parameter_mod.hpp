#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_MOD_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_MOD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Utils/StlUtil.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_mod;
struct s_session_mod_options;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 1)
struct s_session_mod_options
{
	bool valid; // 0x0
	unsigned char hash[20]; // 0x1
};
#pragma pack(pop)
static_assert(sizeof(s_session_mod_options) == 21, "Invalid s_session_mod_options size");

#pragma pack(push, 4)
class c_network_session_parameter_mod :
	public c_custom_network_session_parameter<s_session_mod_options>
{
public:
	s_session_mod_options const *get() const;
	bool set(s_session_mod_options const *options);
	bool request_change(s_session_mod_options const *options);
	c_network_session_parameter_mod(c_network_session_parameter_mod &); /* compiler_generated() */
	c_network_session_parameter_mod(c_network_session_parameter_mod const &); /* compiler_generated() */
	_inline c_network_session_parameter_mod(); /* compiler_generated() */
	c_network_session_parameter_mod &operator=(c_network_session_parameter_mod &); /* compiler_generated() */
	c_network_session_parameter_mod &operator=(c_network_session_parameter_mod const &); /* compiler_generated() */
	void __autoclassinit2(unsigned __int32); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_network_session_parameter_mod) == 92, "Invalid c_network_session_parameter_mod size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_MOD_HPP__
