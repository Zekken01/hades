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
	mangled_x86(MANGLED_KNOWN_GOOD, "?request_change@c_network_session_parameter_mod@@QAE_NPBUs_session_mod_options@@@Z");
	// s_session_mod_options const *options;

	return set_allowed() && set(options);
}

extern s_session_mod_options const *_sub_10F1D4A0(c_network_session_parameter_mod const *const);
s_session_mod_options const *c_network_session_parameter_mod::get() const // 0x10F1D4A0
{
	mangled_x86(MANGLED_TODO, "?get@c_network_session_parameter_mod@@QBEPBUs_session_mod_options@@XZ");
	// c_network_session_parameter_mod const *const this;
	todo("implement");
	s_session_mod_options const * __result = _sub_10F1D4A0((c_network_session_parameter_mod const *)this);
	return __result;
}

_extern bool _sub_10F1D5B0(c_network_session_parameter_mod *const, s_session_mod_options const *);
bool c_network_session_parameter_mod::set(s_session_mod_options const *options) // 0x10F1D5B0
{
	mangled_x86(MANGLED_TODO, "?set@c_network_session_parameter_mod@@QAE_NPBUs_session_mod_options@@@Z");
	// s_session_mod_options const *options;
	todo("implement");
	bool __result = _sub_10F1D5B0(this, options);
	return __result;
}

/* ---------- private code */
