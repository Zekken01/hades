#ifndef __BLAM_SIMULATION_SIMULATION_ENTITY_DEFINITION_HPP__
#define __BLAM_SIMULATION_SIMULATION_ENTITY_DEFINITION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/bitstream.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_bitstream;
struct c_entity_update_encode_helper;

/* ---------- constants */

/* ---------- definitions */

struct c_entity_update_encode_helper
{
	public:
	struct s_internal_methods
	{
		static bool (*const start_encoding_update)(c_entity_update_encode_helper *, c_bitstream *, long, long, long, unsigned long long *);
		static bool (*const start_component)(c_entity_update_encode_helper *, long, char const *);
		static void (*const finish_component)(c_entity_update_encode_helper *);
		static void (*const cancel_component)(c_entity_update_encode_helper *);
		static void (*const finish_encoding_update)(c_entity_update_encode_helper *, unsigned long long *);
	};
	static_assert(sizeof(s_internal_methods) == 1, "Invalid s_internal_methods size");
	public:
	_inline bool start_encoding_update(c_bitstream *stream, long parent_update_component_count, long update_component_first_index, long update_component_count, unsigned long long *mask);
	_inline bool start_component(long update_component_index, char const *update_component_name);
	_inline void finish_component();
	_inline void finish_encoding_update(unsigned long long *update_mask_written);
	void cancel_component();
private:
	c_bitstream *m_bitstream; // 0x0
	long m_update_component_first_index; // 0x4
	long m_update_component_count; // 0x8
	unsigned char __pad0[4]; // 0xC
	unsigned long long m_update_component_mask2; // 0x10
	unsigned long long m_update_component_mask3; // 0x18
	unsigned long long m_update_component_mask_written; // 0x20
	unsigned long long m_update_component_mask4; // 0x28
	unsigned long long m_update_component_mask5; // 0x30
	bool m_has_space_left; // 0x38
	unsigned char __pad1[3]; // 0x39
	long m_update_component_index; // 0x3C
	char const *m_update_component_name; // 0x40
	long m_required_leave_space_bits; // 0x44
	long m_current_required_leave_space_bits; // 0x48
	long m_current_leave_space_bits; // 0x4C
};
static_assert(sizeof(c_entity_update_encode_helper) == 80, "Invalid c_entity_update_encode_helper size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern bool _sub_107B0880(c_entity_update_encode_helper *const, c_bitstream *, long, long, long, unsigned long long *);
_inline bool c_entity_update_encode_helper::start_encoding_update(c_bitstream *stream, long parent_update_component_count, long update_component_first_index, long update_component_count, unsigned long long *mask) // 0x107B0880
{
	mangled_x86(MANGLED_TODO, "?start_encoding_update@c_entity_update_encode_helper@@QAE_NPAVc_bitstream@@JJJPA_K@Z");
	// unsigned long long *mask;
	// function call : bool (*const)(c_entity_update_encode_helper *, c_bitstream *, long, long, long, unsigned long long *)
	todo("implement");
	bool __result = _sub_107B0880(this, stream, parent_update_component_count, update_component_first_index, update_component_count, mask);
	return __result;
}

_extern bool _sub_107B0810(c_entity_update_encode_helper *const, long, char const *);
_inline bool c_entity_update_encode_helper::start_component(long update_component_index, char const *update_component_name) // 0x107B0810
{
	mangled_x86(MANGLED_TODO, "?start_component@c_entity_update_encode_helper@@QAE_NJPBD@Z");
	// char const *update_component_name;
	// function call : bool (*const)(c_entity_update_encode_helper *, long, char const *)
	todo("implement");
	bool __result = _sub_107B0810(this, update_component_index, update_component_name);
	return __result;
}

_extern void _sub_107AE7A0(c_entity_update_encode_helper *const);
_inline void c_entity_update_encode_helper::finish_component() // 0x107AE7A0
{
	mangled_x86(MANGLED_TODO, "?finish_component@c_entity_update_encode_helper@@QAEXXZ");
	// c_entity_update_encode_helper *const this;
	// function call : void (*const)(c_entity_update_encode_helper *)
	todo("implement");
	_sub_107AE7A0(this);
}

_extern void _sub_107AE800(c_entity_update_encode_helper *const, unsigned long long *);
_inline void c_entity_update_encode_helper::finish_encoding_update(unsigned long long *update_mask_written) // 0x107AE800
{
	mangled_x86(MANGLED_TODO, "?finish_encoding_update@c_entity_update_encode_helper@@QAEXPA_K@Z");
	// unsigned long long *update_mask_written;
	// function call : void (*const)(c_entity_update_encode_helper *, unsigned long long *)
	todo("implement");
	_sub_107AE800(this, update_mask_written);
}

/* ---------- private code */

#endif // __BLAM_SIMULATION_SIMULATION_ENTITY_DEFINITION_HPP__
