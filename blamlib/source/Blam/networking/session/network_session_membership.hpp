#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_MEMBERSHIP_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_MEMBERSHIP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/player_configuration.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct s_network_session_peer;
struct s_network_session_peer_channel;
struct s_network_session_peer_properties;
struct s_network_session_player;
struct s_network_session_shared_membership;
struct s_player_add_queue_entry;
struct s_player_configuration;
struct s_player_configuration_from_client;
struct s_player_identifier;

/* ---------- constants */

/* ---------- definitions */

struct s_network_session_peer_channel
{
	unsigned long flags; // 0x0
	long channel_index; // 0x4
	unsigned long expected_update_number; // 0x8
};
static_assert(sizeof(s_network_session_peer_channel) == 12, "Invalid s_network_session_peer_channel size");

struct s_network_session_peer_properties
{
	wchar_t machine_name[16]; // 0x0
	wchar_t session_name[32]; // 0x20
	unsigned long available_map_mask; // 0x60
	long map_id; // 0x64
	long map_status; // 0x68
	long map_progress_percentage; // 0x6C
	unsigned long long game_instance; // 0x70
	long ready_hopper_identifier; // 0x78
	long game_start_error; // 0x7C
	bool has_hard_drive; // 0x80
	unsigned char __pad0[3]; // 0x81
	unsigned char channel_identifier[8]; // 0x84
	bool field_8C; // 0x8C
	unsigned char __pad1[3]; // 0x8D
	long nat_type; // 0x90
	long connectivity_badness_rating; // 0x94
	long host_badness_rating; // 0x98
	long client_badness_rating; // 0x9C
	unsigned short peer_probe_mask; // 0xA0
	unsigned char __pad2[2]; // 0xA2
	long peer_latency_min; // 0xA4
	long peer_latency_est; // 0xA8
	long peer_latency_max; // 0xAC
	long language; // 0xB0
	long determinism_version; // 0xB4
	long determinism_compatible_version; // 0xB8
	unsigned long status_flags; // 0xBC
};
static_assert(sizeof(s_network_session_peer_properties) == 192, "Invalid s_network_session_peer_properties size");

struct s_network_session_peer
{
	s_transport_secure_address secure_address; // 0x0
	c_enum<enum e_network_session_peer_state,long> connection_state; // 0x10
	long network_version; // 0x14
	unsigned long creation_timestamp; // 0x18
	s_network_session_peer_properties properties; // 0x20
	unsigned long long party_nonce; // 0xE0
	unsigned long long join_nonce; // 0xE8
	unsigned long player_mask; // 0xF0
	s_network_session_peer(s_network_session_peer &); /* compiler_generated() */
	s_network_session_peer(s_network_session_peer const &); /* compiler_generated() */
	s_network_session_peer(); /* compiler_generated() */
	s_network_session_peer &operator=(s_network_session_peer &); /* compiler_generated() */
	s_network_session_peer &operator=(s_network_session_peer const &); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_peer) == 248, "Invalid s_network_session_peer size");
static_assert(offsetof(s_network_session_peer, properties) == 0x20, "s_network_session_peer::properties moved when its reconstructed padding was removed");

struct s_network_session_player
{
	long player_update_number; // 0x0
	s_player_identifier player_identifier; // 0x4
	long peer_index; // 0xC
	long player_sequence_number; // 0x10
	char peer_user_index; // 0x14
	unsigned char __pad0[3]; // 0x15
	long controller_index; // 0x18
	unsigned char __pad1[4]; // 0x1C
	s_player_configuration configuration; // 0x20
	unsigned long voice_settings; // 0x1640
	s_network_session_player(); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_player) == 5704, "Invalid s_network_session_player size");

struct s_player_add_queue_entry
{
	s_player_identifier player_identifier; // 0x0
	long player_index; // 0x8
	long output_user_index; // 0xC
	long controller_index; // 0x10
	s_player_configuration_from_client client_configuration; // 0x14
	unsigned long voice_settings; // 0x44
};
static_assert(sizeof(s_player_add_queue_entry) == 72, "Invalid s_player_add_queue_entry size");

struct s_network_session_shared_membership
{
	long update_number; // 0x0
	long leader_peer_index; // 0x4
	long host_peer_index; // 0x8
	long private_slot_count; // 0xC
	long public_slot_count; // 0x10
	bool friends_only; // 0x14
	bool are_slots_locked; // 0x15
	unsigned char __pad0[2]; // 0x16
	long peer_count; // 0x18
	unsigned long peer_valid_mask; // 0x1C
	s_network_session_peer peers[17]; // 0x20
	long player_count; // 0x1098
	unsigned long player_valid_mask; // 0x109C
	s_network_session_player players[16]; // 0x10A0
	long player_addition_number; // 0x17520
	s_network_session_shared_membership(s_network_session_shared_membership &); /* compiler_generated() */
	s_network_session_shared_membership(s_network_session_shared_membership const &); /* compiler_generated() */
	s_network_session_shared_membership(); /* compiler_generated() */
	s_network_session_shared_membership &operator=(s_network_session_shared_membership &); /* compiler_generated() */
	s_network_session_shared_membership &operator=(s_network_session_shared_membership const &); /* compiler_generated() */
};
static_assert(sizeof(s_network_session_shared_membership) == 95528, "Invalid s_network_session_shared_membership size");

// c_network_session_membership is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// c_network_session_membership is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline bool c_network_session_membership::has_membership() const // 0x10A9E1F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?has_membership@c_network_session_membership@@QBE_NXZ");

	return update_number() != -1;
}

inline long c_network_session_membership::update_number() const // 0x10A9E850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_number@c_network_session_membership@@QBEJXZ");

	return ((s_network_session_shared_membership const *)m_shared_network_membership)->update_number;
}

inline long c_network_session_membership::local_peer_index() const // 0x10EF8720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?local_peer_index@c_network_session_membership@@QBEJXZ");

	return m_local_peer_index;
}

inline long c_network_session_membership::host_peer_index() const // 0x10A9E270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?host_peer_index@c_network_session_membership@@QBEJXZ");

	return ((s_network_session_shared_membership const *)m_shared_network_membership)->host_peer_index;
}

inline long c_network_session_membership::get_player_count() const // 0x10693C50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_count@c_network_session_membership@@QBEJXZ");

	return ((s_network_session_shared_membership const *)m_shared_network_membership)->player_count;
}

inline s_network_session_shared_membership const *c_network_session_membership::get_current_membership() const // 0x10A9E1C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_membership@c_network_session_membership@@QBEPBUs_network_session_shared_membership@@XZ");

	return (s_network_session_shared_membership const *)m_shared_network_membership;
}

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_MEMBERSHIP_HPP__
