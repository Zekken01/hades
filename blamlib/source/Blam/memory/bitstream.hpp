#ifndef __BLAM_MEMORY_BITSTREAM_HPP__
#define __BLAM_MEMORY_BITSTREAM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Common/Http/HttpHeaders.hpp"

/* ---------- forward declarations */

class c_bitstream;
struct real_point3d;
struct real_vector3d;
struct utf8;

/* ---------- constants */

/* ---------- definitions */

class c_bitstream
{
public:
	public:
	enum e_state
	{
		_state_none = 0,
		_state_writing,
		_state_finished_writing,
		_state_reading,
		_state_consistency_check,
		_state_finished_reading,
	};
	struct s_bitstream_data
	{
		long memory_bit_position; // 0x0
		long stream_bit_position; // 0x4
		unsigned long long accumulator; // 0x8
		long accumulator_bits_used; // 0x10
		unsigned char *m_next_data; // 0x14
	};
	static_assert(sizeof(s_bitstream_data) == 24, "Invalid s_bitstream_data size");
	public:
	static long const k_maximum_position_stack_size;
	c_bitstream(c_bitstream const &); /* compiler_generated() */
	c_bitstream(unsigned char *data, long data_length);
	c_bitstream();
	~c_bitstream();
	bool writing() const;
	bool reading() const;
	bool read_only_for_consistency() const;
	bool overflowed() const;
	bool would_overflow(long size_bits) const;
	bool error_occured() const;
	long get_space_used_in_bits() const;
	long get_space_used_in_bytes() const;
	long get_space_left_in_bits() const;
	long get_current_stream_bit_position() const;
	unsigned char const *get_data(long *data_length) const;
	void set_data(unsigned char *data, long data_length);
	void begin_reading();
	void begin_consistency_check();
	void begin_writing(long data_size_alignment);
	void finish_reading();
	void finish_consistency_check();
	void finish_writing(long *out_size);
	void discard_remaining_data();
	void reset(e_state state);
	void write_integer(char const *name, unsigned long value, long size_in_bits);
	void write_signed_integer(char const *name, long value, long size_in_bits);
	void write_qword(unsigned long long value, long size_in_bits);
	void write_bool(char const *name, bool value);
	void write_raw_data(char const *name, void const *data, long data_length);
	void write_string(char const *name, char const *str, long max_string_size);
	void write_string_utf8(char const *name, utf8 const *str, long max_string_size);
	void write_string_wchar(char const *name, wchar_t const *str, long max_string_size);
	void write_quantized_real(char const *name, float value, float min_value, float max_value, __int32 size_in_bits, bool exact_midpoint, bool unknown);
	void write_vector(char const *name, real_vector3d const *vector, float magnitude_min, float magnitude_max, __int32 size_in_bits_min, __int32 size_in_bits_max);
	void write_unit_vector(char const *name, real_vector3d const *vector, __int32 size_in_bits);
	void write_point3d(char const *name, real_point3d const *point, long axis_encoding_size_in_bits);
	unsigned long read_integer(char const *name, long size_in_bits);
	long read_signed_integer(char const *name, long size_in_bits);
	unsigned long long read_qword(char const *name, long size_in_bits);
	bool read_bool(char const *name);
	void read_raw_data(char const *name, void *buffer, long size_in_bits);
	void read_string(char const *name, char *buffer, long max_string_size);
	void read_string_utf8(char const *name, utf8 *buffer, long max_string_size);
	void read_string_wchar(char const *name, wchar_t *buffer, long max_string_size);
	float read_quantized_real(char const *name, float min_value, float max_value, __int32 size_in_bits, bool exact_midpoint, bool unknown);
	void read_vector(char const *name, real_vector3d *vector, float magnitude_min, float magnitude_max, long size_in_bits_min, long size_in_bits_max);
	void read_unit_vector(char const *name, real_vector3d *vector, long size_in_bits);
	void read_point3d(char const *name, real_point3d *point, long axis_encoding_size_in_bits);
	void push_position();
	void pop_position(bool restore);
private:
	unsigned char *m_data; // 0x0
	unsigned char *m_data_max; // 0x4
	long m_data_size_bytes; // 0x8
	long m_data_size_alignment_bits; // 0xC
	c_enum<enum e_state,long> m_state; // 0x10
	bool m_error_occured; // 0x14
	bool m_data_is_untrusted; // 0x15
	unsigned char __pad0[2]; // 0x16
	s_bitstream_data m_bitstream_data; // 0x18
	long m_position_stack_depth; // 0x30
	unsigned char __pad1[4]; // 0x34
	s_bitstream_data m_position_stack[4]; // 0x38
public:
	c_bitstream &operator=(c_bitstream const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
unsigned char __pad2[8]; // 0x98
};
static_assert(sizeof(c_bitstream) == 160, "Invalid c_bitstream size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MEMORY_BITSTREAM_HPP__
