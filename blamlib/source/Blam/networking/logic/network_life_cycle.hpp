#ifndef __BLAM_NETWORKING_LOGIC_NETWORK_LIFE_CYCLE_HPP__
#define __BLAM_NETWORKING_LOGIC_NETWORK_LIFE_CYCLE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_network_session;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern _inline bool network_life_cycle_in_squad_session(c_network_session **out_session);

/* ---------- globals */

/* ---------- public code */

_inline bool network_life_cycle_in_squad_session(c_network_session **out_session) // 0x10903ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?network_life_cycle_in_squad_session@@YA_NPAPAVc_network_session@@@Z");

	return ((bool(__cdecl *const)(c_network_session **))0x454ea0)(out_session);
}

/* ---------- private code */

#endif // __BLAM_NETWORKING_LOGIC_NETWORK_LIFE_CYCLE_HPP__
