#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_SESSION_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_SESSION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"
#include "Blam/networking/session/network_session_parameters_matchmaking.hpp"
#include "Blam/networking/transport/transport.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_base;
class c_network_session_parameter_leader_properties;
class c_network_session_parameter_remote_join_data;
class c_network_session_parameter_requested_remote_join_data;
class c_network_session_parameter_session_mode;
class c_network_session_parameter_session_size;
struct s_network_session_parameter_leader_properties;
struct s_network_session_parameter_session_mode;
struct s_network_session_parameter_session_size;
struct s_network_session_remote_session_join_data;
struct s_transport_secure_key;

/* ---------- constants */

/* ---------- definitions */

struct s_network_session_parameter_session_mode
{
	long set_counter; // 0x0
	long mode; // 0x4
	long last_set_time; // 0x8
};
static_assert(sizeof(s_network_session_parameter_session_mode) == 12, "Invalid s_network_session_parameter_session_mode size");

class c_network_session_parameter_session_mode :
	public c_network_session_parameter_base,
	private c_generic_network_session_parameter_data<s_network_session_parameter_session_mode>
{
public:
	c_network_session_parameter_session_mode(c_network_session_parameter_session_mode &); /* compiler_generated() */
	c_network_session_parameter_session_mode(c_network_session_parameter_session_mode const &); /* compiler_generated() */
	c_network_session_parameter_session_mode(); /* compiler_generated() */
	c_network_session_parameter_session_mode &operator=(c_network_session_parameter_session_mode &); /* compiler_generated() */
	c_network_session_parameter_session_mode &operator=(c_network_session_parameter_session_mode const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_session_mode) == 72, "Invalid c_network_session_parameter_session_mode size");

struct s_network_session_parameter_session_size
{
	long max_peer_count; // 0x0
	long max_player_count; // 0x4
};
static_assert(sizeof(s_network_session_parameter_session_size) == 8, "Invalid s_network_session_parameter_session_size size");

class c_network_session_parameter_session_size :
	public c_network_session_parameter_base,
	private c_generic_network_session_parameter_data<s_network_session_parameter_session_size>
{
public:
	long get_max_player_count() const;
	c_network_session_parameter_session_size(c_network_session_parameter_session_size &); /* compiler_generated() */
	c_network_session_parameter_session_size(c_network_session_parameter_session_size const &); /* compiler_generated() */
	c_network_session_parameter_session_size(); /* compiler_generated() */
	c_network_session_parameter_session_size &operator=(c_network_session_parameter_session_size &); /* compiler_generated() */
	c_network_session_parameter_session_size &operator=(c_network_session_parameter_session_size const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_session_size) == 64, "Invalid c_network_session_parameter_session_size size");

struct s_network_session_remote_session_join_data
{
	unsigned char __pad0[16]; // 0x0
	unsigned long long join_nonce; // 0x10
	long transport_platform; // 0x18
	s_transport_secure_identifier session_id; // 0x1C
	s_transport_secure_key key; // 0x2C
	s_transport_secure_address host_address; // 0x3C
	long session_class; // 0x4C
	long status; // 0x50
};
static_assert(sizeof(s_network_session_remote_session_join_data) == 88, "Invalid s_network_session_remote_session_join_data size");

class c_network_session_parameter_requested_remote_join_data :
	public c_generic_network_session_parameter<s_network_session_remote_session_join_data>
{
public:
	c_network_session_parameter_requested_remote_join_data(c_network_session_parameter_requested_remote_join_data &); /* compiler_generated() */
	c_network_session_parameter_requested_remote_join_data(c_network_session_parameter_requested_remote_join_data const &); /* compiler_generated() */
	c_network_session_parameter_requested_remote_join_data(); /* compiler_generated() */
	c_network_session_parameter_requested_remote_join_data &operator=(c_network_session_parameter_requested_remote_join_data &); /* compiler_generated() */
	c_network_session_parameter_requested_remote_join_data &operator=(c_network_session_parameter_requested_remote_join_data const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_requested_remote_join_data) == 224, "Invalid c_network_session_parameter_requested_remote_join_data size");

class c_network_session_parameter_remote_join_data :
	public c_generic_network_session_parameter<s_network_session_remote_session_join_data>
{
public:
	c_network_session_parameter_remote_join_data(c_network_session_parameter_remote_join_data &); /* compiler_generated() */
	c_network_session_parameter_remote_join_data(c_network_session_parameter_remote_join_data const &); /* compiler_generated() */
	c_network_session_parameter_remote_join_data(); /* compiler_generated() */
	c_network_session_parameter_remote_join_data &operator=(c_network_session_parameter_remote_join_data &); /* compiler_generated() */
	c_network_session_parameter_remote_join_data &operator=(c_network_session_parameter_remote_join_data const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_remote_join_data) == 224, "Invalid c_network_session_parameter_remote_join_data size");

struct s_network_session_parameter_leader_properties
{
	char field_0[64]; // 0x0
};
static_assert(sizeof(s_network_session_parameter_leader_properties) == 64, "Invalid s_network_session_parameter_leader_properties size");

class c_network_session_parameter_leader_properties :
	public c_generic_network_session_parameter<s_network_session_parameter_leader_properties>
{
public:
	c_network_session_parameter_leader_properties(c_network_session_parameter_leader_properties &); /* compiler_generated() */
	c_network_session_parameter_leader_properties(c_network_session_parameter_leader_properties const &); /* compiler_generated() */
	c_network_session_parameter_leader_properties(); /* compiler_generated() */
	c_network_session_parameter_leader_properties &operator=(c_network_session_parameter_leader_properties &); /* compiler_generated() */
	c_network_session_parameter_leader_properties &operator=(c_network_session_parameter_leader_properties const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameter_leader_properties) == 176, "Invalid c_network_session_parameter_leader_properties size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_SESSION_HPP__
