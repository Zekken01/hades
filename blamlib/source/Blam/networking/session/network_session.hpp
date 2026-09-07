#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct c_network_channel_owner;

/* ---------- constants */

/* ---------- definitions */

struct c_network_channel_owner
{
	void *vftable; // 0x0
};
static_assert(sizeof(c_network_channel_owner) == 4, "Invalid c_network_channel_owner size");

// c_network_session is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// c_network_session is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern long _sub_10903E10(c_network_session const *const);
_inline long c_network_session::get_index() const // 0x10903E10
{
	mangled_x86(MANGLED_TODO, "?get_index@c_network_session@@QBEJXZ");
	// c_network_session const *const this;
	todo("implement");
	long __result = _sub_10903E10((c_network_session const *)this);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_HPP__
