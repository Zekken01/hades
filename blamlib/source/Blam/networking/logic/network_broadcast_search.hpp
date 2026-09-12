#ifndef __BLAM_NETWORKING_LOGIC_NETWORK_BROADCAST_SEARCH_HPP__
#define __BLAM_NETWORKING_LOGIC_NETWORK_BROADCAST_SEARCH_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_status.hpp"

/* ---------- forward declarations */

struct s_available_session;
struct s_network_session_status_data;

/* ---------- constants */

/* ---------- definitions */

struct s_available_session
{
	bool valid; // 0x0
	char unknown[52]; // 0x1
	s_network_session_status_data status; // 0x38
	s_available_session(); /* compiler_generated() */
};
static_assert(sizeof(s_available_session) == 91384, "Invalid s_available_session size");
static_assert(offsetof(s_available_session, status) == 0x38, "s_available_session::status moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_LOGIC_NETWORK_BROADCAST_SEARCH_HPP__
