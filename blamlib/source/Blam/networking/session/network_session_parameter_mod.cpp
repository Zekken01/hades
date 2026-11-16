/* ---------- headers */

#include "Blam/networking/session/network_session_parameter_mod.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_mod;
struct s_session_mod_options;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool c_network_session_parameter_mod::request_change(s_session_mod_options const *options) // 0x10F1D510
{
	return set_allowed() && set(options);
}

s_session_mod_options const *c_network_session_parameter_mod::get() const // 0x10F1D4A0
{
	if (!get_allowed())
		return nullptr;
	else
		return &m_data;
}

bool c_network_session_parameter_mod::set(s_session_mod_options const *options) // 0x10F1D5B0
{
	if (!set_allowed())
		return false;

	csmemcpy((unsigned char *)this + 0x30, options, sizeof(s_session_mod_options));
	set_update_required();
	return true;
}

/* ---------- private code */
