#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_TYPES_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_TYPES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/bitstream.hpp"
#include "Blam/networking/session/network_session_membership.hpp"

/* ---------- forward declarations */

class c_bitstream;
class c_network_session_parameter_type_collection;

/* ---------- constants */

// e_network_session_parameter_type is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- definitions */

class c_network_session_parameter_type_collection
{
public:
	public:
	struct s_type
	{
		bool initialized; // 0x0
		unsigned char __pad0[3]; // 0x1
		char const *parameter_name; // 0x4
		bool (*update_encode)(c_bitstream *, void *); // 0x8
		bool (*update_decode)(c_bitstream *, void *); // 0xC
		long update_size; // 0x10
		bool (*change_request_encode)(c_bitstream *, void *); // 0x14
		bool (*change_request_decode)(c_bitstream *, void *); // 0x18
		long change_request_size; // 0x1C
	};
	static_assert(sizeof(s_type) == 32, "Invalid s_type size");
	public:
	typedef bool (*t_encode_function)(c_bitstream *, void *);
	typedef bool (*t_decode_function)(c_bitstream *, void *);
	void register_session_parameter_type(e_network_session_parameter_type session_parameter_type, char const *session_parameter_name, bool (*update_encode)(c_bitstream *, void *), bool (*update_decode)(c_bitstream *, void *), long update_size, bool (*change_request_encode)(c_bitstream *, void *), bool (*change_request_decode)(c_bitstream *, void *), long change_request_size);
private:
	s_static_array<s_type,49> m_types; // 0x0
};
static_assert(sizeof(c_network_session_parameter_type_collection) == 1568, "Invalid c_network_session_parameter_type_collection size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETER_TYPES_HPP__
