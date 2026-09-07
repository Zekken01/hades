#ifndef __BLAM_NETWORKING_LOGIC_NETWORK_JOIN_HPP__
#define __BLAM_NETWORKING_LOGIC_NETWORK_JOIN_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/transport/transport.hpp"

/* ---------- forward declarations */

struct s_network_session_remote_join_data;
struct s_transport_secure_key;

/* ---------- constants */

/* ---------- definitions */

struct s_network_session_remote_join_data
{
	long join_state; // 0x0
	long joing_from; // 0x4
	long joing_to; // 0x8
	long join_target; // 0xC
	unsigned long long join_nonce; // 0x10
	long platform; // 0x18
	s_transport_secure_identifier session_id; // 0x1C
	s_transport_secure_key session_key; // 0x2C
	s_transport_secure_address host_secure_address; // 0x3C
	long session_class; // 0x4C
	long join_result; // 0x50
	bool join_to_public_slots; // 0x54
	unsigned char __pad0[3]; // 0x55
};
static_assert(sizeof(s_network_session_remote_join_data) == 88, "Invalid s_network_session_remote_join_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_LOGIC_NETWORK_JOIN_HPP__
