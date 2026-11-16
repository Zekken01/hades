#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_BASE_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_BASE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameter_types.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- constants */

/* ---------- definitions */

// c_network_session_parameter_base is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// c_network_session_parameter_base is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline void c_network_session_parameter_base::notify_set_update_required() // 0x10AA9420
{
}

inline void c_network_session_parameter_base::notify_set_change_request() // 0x10AA9400
{
}

inline void c_network_session_parameter_base::notify_update_payload_sent_to_peer(long peer_index) // 0x10AA94C0
{
}

inline void c_network_session_parameter_base::notify_change_request_payload_sent() // 0x10AA9310
{
}

inline bool c_network_session_parameter_base::can_set_peer_no_longer_requires_update(long peer_index) // 0x10AA8B60
{
	return true;
}

inline bool c_network_session_parameter_base::can_clear_change_request_desired() // 0x10AA8B40
{
	return true;
}

inline bool c_network_session_parameter_base::parameter_data_ready_for_consumption() // 0x10AA94E0
{
	return true;
}

inline void c_network_session_parameter_base::get_update_payload(long __formal, void *__formal1) // 0x10AA8D00
{
}

inline long c_network_session_parameter_base::get_update_payload_size() // 0x10AA8D50
{
	return 0;
}

inline bool c_network_session_parameter_base::handle_update_payload(void const *__formal) // 0x10AA8E70
{
	return true;
}

inline void c_network_session_parameter_base::get_change_request_payload(long __formal, long __formal1, void *__formal2) // 0x10AA8BE0
{
}

inline long c_network_session_parameter_base::get_change_request_payload_size() // 0x10AA8C80
{
	return 0;
}

inline bool c_network_session_parameter_base::handle_change_request_payload(void const *__formal) // 0x10AA8DF0
{
	return true;
}

inline void c_network_session_parameter_base::notify_reset_peer_state(long __formal) // 0x10AA93E0
{
}

inline void c_network_session_parameter_base::notify_clear() // 0x10AA93A0
{
}

inline void c_network_session_parameter_base::notify_transition_state_to_become_host() // 0x10AA94A0
{
}

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_BASE_HPP__
