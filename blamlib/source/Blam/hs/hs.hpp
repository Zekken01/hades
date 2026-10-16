#ifndef __BLAM_HS_HS_HPP__
#define __BLAM_HS_HS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct $s_hs_script_op$_extraBytes_0;
struct $s_hs_script_op$_extraBytes_10;
struct $s_hs_script_op$_extraBytes_12;
struct $s_hs_script_op$_extraBytes_14;
struct $s_hs_script_op$_extraBytes_2;
struct $s_hs_script_op$_extraBytes_4;
struct $s_hs_script_op$_extraBytes_6;
struct $s_hs_script_op$_extraBytes_8;
struct hs_stack_frame;
struct hs_value;
struct s_datum;
struct s_hs_global;
struct s_hs_global_external;
struct s_hs_global_runtime;
struct s_hs_script;
struct s_hs_script_op;
struct s_hs_script_parameter;
struct s_hs_syntax_node;
struct s_hs_thread;
union tag_string;

/* ---------- constants */

enum
{
	k_hs_thread_deterministic_data_tls_offset = 104, // 0x0068 'h'
	k_hs_external_global_count = 1315, // 0x0523
};

/* ---------- definitions */

struct s_hs_global
{
	tag_string name; // 0x0
	c_enum<enum e_hs_type,short> type; // 0x20
	unsigned long root_expression_index; // 0x24
	s_hs_global(s_hs_global &); /* compiler_generated() */
	s_hs_global(s_hs_global const &); /* compiler_generated() */
	s_hs_global(); /* compiler_generated() */
	s_hs_global &operator=(s_hs_global &); /* compiler_generated() */
	s_hs_global &operator=(s_hs_global const &); /* compiler_generated() */
};
static_assert(sizeof(s_hs_global) == 40, "Invalid s_hs_global size");
static_assert(offsetof(s_hs_global, root_expression_index) == 0x24, "s_hs_global::root_expression_index moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_hs_script_parameter
{
	tag_string name; // 0x0
	c_enum<enum e_hs_type,short> type; // 0x20
	s_hs_script_parameter(s_hs_script_parameter &); /* compiler_generated() */
	s_hs_script_parameter(s_hs_script_parameter const &); /* compiler_generated() */
	s_hs_script_parameter(); /* compiler_generated() */
	s_hs_script_parameter &operator=(s_hs_script_parameter &); /* compiler_generated() */
	s_hs_script_parameter &operator=(s_hs_script_parameter const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x22
};
#pragma pack(pop)
static_assert(sizeof(s_hs_script_parameter) == 36, "Invalid s_hs_script_parameter size");

#pragma pack(push, 4)
struct s_hs_script
{
	tag_string name; // 0x0
	c_enum<enum e_hs_script_type,short> type; // 0x20
	c_enum<enum e_hs_type,short> return_type; // 0x22
	union
	{
		unsigned long root_expression_index; // 0x24
		void *extern_method; // 0x24
	};
	c_tag_block<s_hs_script_parameter> parameters; // 0x28
	s_hs_script(s_hs_script &); /* compiler_generated() */
	s_hs_script(s_hs_script const &); /* compiler_generated() */
	s_hs_script(); /* compiler_generated() */
	s_hs_script &operator=(s_hs_script &); /* compiler_generated() */
	s_hs_script &operator=(s_hs_script const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_hs_script) == 52, "Invalid s_hs_script size");

struct s_hs_syntax_node :
	public s_datum
{
	unsigned short opcode; // 0x2
	c_enum<enum e_hs_type,short> type; // 0x4
	c_flags<enum e_hs_syntax_node_flags,unsigned short> flags; // 0x6
	unsigned long next_expression_index; // 0x8
	long string_address; // 0xC
	unsigned char data[4]; // 0x10
	short line_number; // 0x14
	s_hs_syntax_node(s_hs_syntax_node &); /* compiler_generated() */
	s_hs_syntax_node(s_hs_syntax_node const &); /* compiler_generated() */
	s_hs_syntax_node(); /* compiler_generated() */
	s_hs_syntax_node &operator=(s_hs_syntax_node &); /* compiler_generated() */
	s_hs_syntax_node &operator=(s_hs_syntax_node const &); /* compiler_generated() */
};
static_assert(sizeof(s_hs_syntax_node) == 24, "Invalid s_hs_syntax_node size");

#pragma pack(push, 2)
struct $s_hs_script_op$_extraBytes_6
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	c_enum<enum e_hs_type,short> args[3]; // 0xE
	unsigned char __pad1[2]; // 0x14
};
#pragma pack(pop)
static_assert(sizeof($s_hs_script_op$_extraBytes_6) == 22, "Invalid $s_hs_script_op$_extraBytes_6 size");

#pragma pack(push, 2)
struct $s_hs_script_op$_extraBytes_2
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	c_enum<enum e_hs_type,short> args[1]; // 0xE
	unsigned char __pad1[2]; // 0x10
};
#pragma pack(pop)
static_assert(sizeof($s_hs_script_op$_extraBytes_2) == 18, "Invalid $s_hs_script_op$_extraBytes_2 size");

#pragma pack(push, 2)
struct $s_hs_script_op$_extraBytes_10
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	c_enum<enum e_hs_type,short> args[5]; // 0xE
	unsigned char __pad1[2]; // 0x18
};
#pragma pack(pop)
static_assert(sizeof($s_hs_script_op$_extraBytes_10) == 26, "Invalid $s_hs_script_op$_extraBytes_10 size");

struct $s_hs_script_op$_extraBytes_8
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	c_enum<enum e_hs_type,short> args[4]; // 0xE
};
static_assert(sizeof($s_hs_script_op$_extraBytes_8) == 24, "Invalid $s_hs_script_op$_extraBytes_8 size");

#pragma pack(push, 2)
struct $s_hs_script_op$_extraBytes_14
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	c_enum<enum e_hs_type,short> args[7]; // 0xE
	unsigned char __pad1[2]; // 0x1C
};
#pragma pack(pop)
static_assert(sizeof($s_hs_script_op$_extraBytes_14) == 30, "Invalid $s_hs_script_op$_extraBytes_14 size");

#pragma pack(push, 4)
struct $s_hs_script_op$_extraBytes_12
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	c_enum<enum e_hs_type,short> args[6]; // 0xE
};
#pragma pack(pop)
static_assert(sizeof($s_hs_script_op$_extraBytes_12) == 28, "Invalid $s_hs_script_op$_extraBytes_12 size");

struct $s_hs_script_op$_extraBytes_4
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	c_enum<enum e_hs_type,short> args[2]; // 0xE
};
static_assert(sizeof($s_hs_script_op$_extraBytes_4) == 20, "Invalid $s_hs_script_op$_extraBytes_4 size");

struct $s_hs_script_op$_extraBytes_0
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	unsigned char __pad1[2]; // 0xE
	c_enum<enum e_hs_type,short> args[0]; // 0xE
};
static_assert(sizeof($s_hs_script_op$_extraBytes_0) == 16, "Invalid $s_hs_script_op$_extraBytes_0 size");

struct s_hs_script_op
{
	c_enum<enum e_hs_type,short> return_type; // 0x0
	void (*callback)(short, __int32, char); // 0x4
	char const *special_syntax; // 0x8
	short argument_count; // 0xC
	s_hs_script_op(s_hs_script_op &); /* compiler_generated() */
	s_hs_script_op(s_hs_script_op const &); /* compiler_generated() */
	s_hs_script_op(); /* compiler_generated() */
	s_hs_script_op &operator=(s_hs_script_op &); /* compiler_generated() */
	s_hs_script_op &operator=(s_hs_script_op const &); /* compiler_generated() */
	c_enum<enum e_hs_type,short> args[0]; // 0xE
};
static_assert(sizeof(s_hs_script_op) == 16, "Invalid s_hs_script_op size");
static_assert(offsetof(s_hs_script_op, argument_count) == 0xC, "s_hs_script_op::argument_count moved when its reconstructed padding was removed");
static_assert(offsetof(s_hs_script_op, args) == 0xE, "s_hs_script_op::args moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_hs_thread :
	public s_datum
{
	short script_index; // 0x2
	short previous_script_index; // 0x4
	long delay_until_time; // 0x8
	long sleep_time; // 0xC
	unsigned short stack_offset; // 0x10
	long return_value; // 0x14
	long tracking_index; // 0x18
	char type; // 0x1C
	unsigned char flags1; // 0x1D
	unsigned char flags2; // 0x1E
	unsigned char __pad2[5]; // 0x1F
	char stack[1280]; // 0x24
};
#pragma pack(pop)
static_assert(sizeof(s_hs_thread) == 1316, "Invalid s_hs_thread size");

struct s_hs_global_runtime :
	public s_datum
{
	long value; // 0x4
};
static_assert(sizeof(s_hs_global_runtime) == 8, "Invalid s_hs_global_runtime size");
static_assert(offsetof(s_hs_global_runtime, value) == 0x4, "s_hs_global_runtime::value moved when its reconstructed padding was removed");

struct s_hs_global_external
{
	c_enum<unsigned short,enum e_hs_type> type; // 0x0
	long value; // 0x4
	s_hs_global_external(s_hs_global_external &); /* compiler_generated() */
	s_hs_global_external(s_hs_global_external const &); /* compiler_generated() */
	s_hs_global_external(); /* compiler_generated() */
	s_hs_global_external &operator=(s_hs_global_external &); /* compiler_generated() */
	s_hs_global_external &operator=(s_hs_global_external const &); /* compiler_generated() */
};
static_assert(sizeof(s_hs_global_external) == 8, "Invalid s_hs_global_external size");

struct hs_stack_frame
{
	long expression_index; // 0x0
	long script_index; // 0x4
	long result_destination; // 0x8
	short parameters; // 0xC
	short parent_stack_frame; // 0xE
	short frame_size; // 0x10
};
static_assert(sizeof(hs_stack_frame) == 20, "Invalid hs_stack_frame size");

struct hs_value
{
	union
	{
		long long_value; // 0x0
		short short_value; // 0x0
		float real_value; // 0x0
		bool bool_value; // 0x0
		char const *string_value; // 0x0
	};
	static _inline hs_value from_long(long value);
	static _inline hs_value from_short(short value);
	static _inline hs_value from_real(float value);
	static _inline hs_value from_bool(bool value);
	static _inline hs_value from_string(char const *value);
	static hs_value get_default(e_hs_type type);
};
static_assert(sizeof(hs_value) == 4, "Invalid hs_value size");

/* ---------- prototypes */

extern void *hs_get_node_data(unsigned long script_index);
extern s_hs_thread *hs_thread_get(unsigned long index);
extern void hs_find_dormant_script(char const *script_name, long *out_script_index);
extern hs_stack_frame *hs_thread_stack(long thread_index);
extern s_hs_global_external *hs_global_external_get(short index);
extern e_hs_type hs_global_get_type(short global_index);
extern char const *hs_global_get_name(short global_index);
extern short hs_global_get_runtime_index(short global_index);
extern s_hs_global_runtime *hs_global_runtime_get(short global_index);
extern hs_value const *hs_evaluate_arguments2(short op, long thread_index, bool initial);
extern void hs_return2(long thread_index, hs_value value);
extern char const *hs_get_type_name(e_hs_type type);

/* ---------- globals */

/* ---------- public code */

inline hs_value hs_value::from_long(long value) // 0x10681220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?from_long@hs_value@@SA?AU1@J@Z");

	return hs_value{ .long_value = value };
}

inline hs_value hs_value::from_short(short value) // 0x106F7950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?from_short@hs_value@@SA?AU1@F@Z");

	return hs_value{ .short_value = value };
}

inline hs_value hs_value::from_real(float value) // 0x10681250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?from_real@hs_value@@SA?AU1@M@Z");

	return hs_value{ .real_value = value };
}

inline hs_value hs_value::from_bool(bool value) // 0x107059A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?from_bool@hs_value@@SA?AU1@_N@Z");

	return hs_value{ .bool_value = value };
}

inline hs_value hs_value::from_string(char const *value) // 0x106EC650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?from_string@hs_value@@SA?AU1@PBD@Z");

	return hs_value{ .string_value = value };
}

/* ---------- private code */

#endif // __BLAM_HS_HS_HPP__
