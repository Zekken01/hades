/* ---------- headers */

#include "Blam/memory/bitstream.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"

/* ---------- forward declarations */

class c_bitstream;
struct real_point3d;
struct real_vector3d;
struct utf8;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_bitstream::c_bitstream() // 0x10F00F80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_bitstream@@QAE@XZ");
	// c_bitstream *const this;

	m_data = nullptr;
	m_data_max = nullptr;
	m_data_size_bytes = 0;
	reset((e_state)0);
}

c_bitstream::c_bitstream(unsigned char *data, long data_length) // 0x10F00EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_bitstream@@QAE@PAEJ@Z");
	// long data_length;

	m_data_size_alignment_bits = 1;
	set_data(data, data_length);
}

c_bitstream::~c_bitstream() // 0x10F01010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_bitstream@@QAE@XZ");
	// c_bitstream *const this;
}

bool c_bitstream::writing() const // 0x10F02910
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?writing@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;

	return m_state == _state_writing;
}

bool c_bitstream::reading() const // 0x10F01F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reading@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;

	return m_state == _state_reading;
}

bool c_bitstream::read_only_for_consistency() const // 0x10F019F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_only_for_consistency@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;

	return m_state == _state_consistency_check;
}

bool c_bitstream::overflowed() const // 0x10F016B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?overflowed@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;

	return m_bitstream_data.stream_bit_position > 8 * m_data_size_bytes;
}

bool c_bitstream::would_overflow(long size_bits) const // 0x10F02100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?would_overflow@c_bitstream@@QBE_NJ@Z");
	// long size_bits;

	return m_bitstream_data.memory_bit_position + size_bits > 8 * m_data_size_bytes;
}

bool c_bitstream::error_occured() const // 0x10F012B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?error_occured@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;

	return m_error_occured || overflowed();
}

long c_bitstream::get_space_used_in_bits() const // 0x10F015E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_space_used_in_bits@c_bitstream@@QBEJXZ");
	// c_bitstream const *const this;

	return m_bitstream_data.accumulator_bits_used + m_bitstream_data.memory_bit_position;
}

long c_bitstream::get_space_used_in_bytes() const // 0x10F01640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_space_used_in_bytes@c_bitstream@@QBEJXZ");
	// c_bitstream const *const this;

	return (get_space_used_in_bits() + 7) / 8;
}

long c_bitstream::get_space_left_in_bits() const // 0x10F01570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_space_left_in_bits@c_bitstream@@QBEJXZ");
	// c_bitstream const *const this;

	return 8 * m_data_size_bytes - get_space_used_in_bits();
}

long c_bitstream::get_current_stream_bit_position() const // 0x10F014A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_stream_bit_position@c_bitstream@@QBEJXZ");
	// c_bitstream const *const this;

	return m_bitstream_data.stream_bit_position;
}

unsigned char const *c_bitstream::get_data(long *data_length) const // 0x10F01500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_data@c_bitstream@@QBEPBEPAJ@Z");
	// long *data_length;

	*data_length = m_data_size_bytes;
	return m_data;
}

void c_bitstream::set_data(unsigned char *data, long data_length) // 0x10F02080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_data@c_bitstream@@QAEXPAEJ@Z");
	// long data_length;

	m_data = data;
	m_data_max = &data[data_length];
	m_data_size_bytes = data_length;
	reset(_state_none);
}

void c_bitstream::begin_reading() // 0x10F01160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?begin_reading@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : void (*const)(c_bitstream *)

	((void(__thiscall *const)(c_bitstream *const))0x5574a0)(this);
}

void c_bitstream::begin_consistency_check() // 0x10F010F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?begin_consistency_check@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : bool (*const)(c_bitstream *)

	((void(__thiscall *const)(c_bitstream *const))0x557490)(this);
}

void c_bitstream::begin_writing(long data_size_alignment) // 0x10F011D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?begin_writing@c_bitstream@@QAEXJ@Z");
	// long data_size_alignment;
	// function call : void (*const)(c_bitstream *, long)

	((void(__thiscall *const)(c_bitstream *, long))0x5574b0)(this, data_size_alignment);
}

void c_bitstream::finish_reading() // 0x10F013C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?finish_reading@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : void (*const)(c_bitstream *)

	((void(__thiscall *const)(c_bitstream *const))0x5580c0)(this);
}

void c_bitstream::finish_consistency_check() // 0x10F01350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?finish_consistency_check@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : void (*const)(c_bitstream *)

	((void(__thiscall *const)(c_bitstream *const))0x5580c0)(this);
}

void c_bitstream::finish_writing(long *out_size) // 0x10F01430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?finish_writing@c_bitstream@@QAEXPAJ@Z");
	// long *out_size;
	// function call : void (*const)(c_bitstream *, long *)

	((void(__thiscall *const)(c_bitstream *, long *))0x5580d0)(this, out_size);
}

void c_bitstream::discard_remaining_data() // 0x10F01240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?discard_remaining_data@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : void (*const)(c_bitstream *)

	((void(__thiscall *const)(c_bitstream *const))0x557f60)(this);
}

void c_bitstream::reset(c_bitstream::e_state state) // 0x10F02010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reset@c_bitstream@@QAEXW4e_state@1@@Z");
	// c_bitstream::e_state state;
	// function call : void (*const)(c_bitstream *, long)

	((void(__thiscall *const)(c_bitstream *, long))0x559be0)(this, state);
}

_extern void _sub_10F02210(c_bitstream *const, char const *, unsigned long, long);
void c_bitstream::write_integer(char const *name, unsigned long value, long size_in_bits) // 0x10F02210
{
	mangled_x86(MANGLED_TODO, "?write_integer@c_bitstream@@QAEXPBDKJ@Z");
	// long size_in_bits;
	// function call : void (*const)(c_bitstream *, char const *, unsigned long, long)
	todo("implement");
	_sub_10F02210(this, name, value, size_in_bits);
}

_extern void _sub_10F02570(c_bitstream *const, char const *, long, long);
void c_bitstream::write_signed_integer(char const *name, long value, long size_in_bits) // 0x10F02570
{
	mangled_x86(MANGLED_TODO, "?write_signed_integer@c_bitstream@@QAEXPBDJJ@Z");
	// long size_in_bits;
	// long const maximum;
	// long const minimum;
	// function call : void (*const)(c_bitstream *, char const *, long, long)
	todo("implement");
	_sub_10F02570(this, name, value, size_in_bits);
}

_extern void _sub_10F02400(c_bitstream *const, unsigned long long, long);
void c_bitstream::write_qword(unsigned long long value, long size_in_bits) // 0x10F02400
{
	mangled_x86(MANGLED_TODO, "?write_qword@c_bitstream@@QAEX_KJ@Z");
	// long size_in_bits;
	// function call : void (*const)(c_bitstream *, unsigned long long, long)
	todo("implement");
	_sub_10F02400(this, value, size_in_bits);
}

void c_bitstream::write_bool(char const *name, bool value) // 0x10F02190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_bool@c_bitstream@@QAEXPBD_N@Z");
	// bool value;
	// function call : void (*const)(c_bitstream *, char const *, bool)

	((void(__thiscall *const)(c_bitstream *const, char const *, bool))0x444b30)(this, name, value);
}

void c_bitstream::write_raw_data(char const *name, void const *data, long data_length) // 0x10F024F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_raw_data@c_bitstream@@QAEXPBDPBXJ@Z");
	// long data_length;
	// function call : void (*const)(c_bitstream *, unsigned char const *, long, bool)

	((void(__thiscall *const)(c_bitstream *, unsigned char const *, long, bool))0x55a000)(this, (unsigned char const *)data, data_length, false);
}

void c_bitstream::write_string(char const *name, char const *str, long max_string_size) // 0x10F02670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_string@c_bitstream@@QAEXPBD0J@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, char const *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, char const *, long))0x55a430)(this, name, str, max_string_size);
}

void c_bitstream::write_string_utf8(char const *name, utf8 const *str, long max_string_size) // 0x10F026F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_string_utf8@c_bitstream@@QAEXPBDPBUutf8@@J@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, utf8 const *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, utf8 const *, long))0x55a650)(this, name, str, max_string_size);
}

void c_bitstream::write_string_wchar(char const *name, wchar_t const *str, long max_string_size) // 0x10F02770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_string_wchar@c_bitstream@@QAEXPBDPB_WJ@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, wchar_t const *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, wchar_t const *, long))0x55a6d0)(this, name, str, max_string_size);
}

void c_bitstream::write_vector(char const *name, real_vector3d const *vector, float magnitude_min, float magnitude_max, __int32 size_in_bits_min, __int32 size_in_bits_max) // 0x10F02870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_vector@c_bitstream@@QAEXPBDPBUreal_vector3d@@MMHH@Z");
	// __int32 size_in_bits_max;
	// function call : void (*const)(c_bitstream *, char const *, real_vector3d const *, float, float, __int32, __int32)

	((void(__thiscall *)(c_bitstream *, char const *, real_vector3d const *, float, float, __int32, __int32))0x55a7b0)(this, name, vector, magnitude_min, magnitude_max, size_in_bits_min, size_in_bits_max);
}

void c_bitstream::write_unit_vector(char const *name, real_vector3d const *vector, __int32 size_in_bits) // 0x10F027F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_unit_vector@c_bitstream@@QAEXPBDPBUreal_vector3d@@H@Z");
	// __int32 size_in_bits;
	// function call : void (*const)(c_bitstream *, char const *, real_vector3d const *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, real_vector3d const *, long))0x55a750)(this, name, vector, size_in_bits);
}

void c_bitstream::write_point3d(char const *name, real_point3d const *point, long axis_encoding_size_in_bits) // 0x10F022D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_point3d@c_bitstream@@QAEXPBDPBUreal_point3d@@J@Z");
	// long axis_encoding_size_in_bits;
	// function call : void (*const)(c_bitstream *, char const *, real_point3d const *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, real_point3d const *, long))0x55a1e0)(this, name, point, axis_encoding_size_in_bits);
}

void c_bitstream::write_quantized_real(char const *name, float value, float min_value, float max_value, __int32 size_in_bits, bool exact_midpoint, bool unknown) // 0x10F02350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_quantized_real@c_bitstream@@QAEXPBDMMMH_N1@Z");
	// bool unknown;
	// function call : void (*const)(c_bitstream *, char const *, float, float, float, __int32, bool, bool)

	((void(__thiscall *const)(c_bitstream *, char const *, float, float, float, __int32, bool, bool))0x55a2b0)(this, name, value, min_value, max_value, size_in_bits, exact_midpoint, unknown);
}

unsigned long c_bitstream::read_integer(char const *name, long size_in_bits) // 0x10F01980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_integer@c_bitstream@@QAEKPBDJ@Z");
	// long size_in_bits;
	// function call : unsigned long (*const)(c_bitstream *, long)

	return ((unsigned long(__thiscall *const)(c_bitstream *, long))0x5589a0)(this, size_in_bits);
}

long c_bitstream::read_signed_integer(char const *name, long size_in_bits) // 0x10F01C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_signed_integer@c_bitstream@@QAEJPBDJ@Z");
	// long size_in_bits;
	// function call : unsigned long (*const)(c_bitstream *, long)

	return ((unsigned long(__thiscall *const)(c_bitstream *, long))0x5589a0)(this, size_in_bits);
}

unsigned long long c_bitstream::read_qword(char const *name, long size_in_bits) // 0x10F01B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_qword@c_bitstream@@QAE_KPBDJ@Z");
	// long size_in_bits;
	// function call : unsigned long long (*const)(c_bitstream *, long)

	return ((unsigned long long(__thiscall *const)(c_bitstream *, long))0x559160)(this, size_in_bits);
}

bool c_bitstream::read_bool(char const *name) // 0x10F01910
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_bool@c_bitstream@@QAE_NPBD@Z");
	// char const *name;
	// function call : bool (*const)(c_bitstream *)

	return ((bool(__thiscall *const)(c_bitstream *))0x558570)(this);
}

void c_bitstream::read_raw_data(char const *name, void *buffer, long size_in_bits) // 0x10F01C00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_raw_data@c_bitstream@@QAEXPBDPAXJ@Z");
	// long size_in_bits;
	// function call : void (*const)(c_bitstream *, void *, long)

	((void(__thiscall *const)(c_bitstream *, void *, long))0x558740)(this, buffer, size_in_bits);
}

void c_bitstream::read_string(char const *name, char *buffer, long max_string_size) // 0x10F01CF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_string@c_bitstream@@QAEXPBDPADJ@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, char *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, char *, long))0x559380)(this, name, buffer, max_string_size);
}

void c_bitstream::read_string_utf8(char const *name, utf8 *buffer, long max_string_size) // 0x10F01D70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_string_utf8@c_bitstream@@QAEXPBDPAUutf8@@J@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, utf8 *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, utf8 *, long))0x559670)(this, name, buffer, max_string_size);
}

void c_bitstream::read_string_wchar(char const *name, wchar_t *buffer, long max_string_size) // 0x10F01DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_string_wchar@c_bitstream@@QAEXPBDPA_WJ@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, wchar_t *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, wchar_t *, long))0x559880)(this, name, buffer, max_string_size);
}

void c_bitstream::read_vector(char const *name, real_vector3d *vector, float magnitude_min, float magnitude_max, long size_in_bits_min, long size_in_bits_max) // 0x10F01EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_vector@c_bitstream@@QAEXPBDPAUreal_vector3d@@MMJJ@Z");
	// long size_in_bits_max;
	// function call : void (*const)(c_bitstream *, char const *, real_vector3d *, float, float, long, long)

	((void(__thiscall *const)(c_bitstream *, char const *, real_vector3d *, float, float, long, long))0x559ab0)(this, name, vector, magnitude_min, magnitude_max, size_in_bits_min, size_in_bits_max);
}

float c_bitstream::read_quantized_real(char const *name, float min_value, float max_value, __int32 size_in_bits, bool exact_midpoint, bool unknown) // 0x10F01AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_quantized_real@c_bitstream@@QAEMPBDMMH_N1@Z");
	// bool unknown;
	// function call : float (*const)(c_bitstream *, char const *, float, float, __int32, bool, bool)

	return ((float(__thiscall *const)(c_bitstream *, char const *, float, float, __int32, bool, bool))0x559080)(this, name, min_value, max_value, size_in_bits, exact_midpoint, unknown);
}

void c_bitstream::read_unit_vector(char const *name, real_vector3d *vector, long size_in_bits) // 0x10F01E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_unit_vector@c_bitstream@@QAEXPBDPAUreal_vector3d@@J@Z");
	// long size_in_bits;
	// function call : void (*const)(c_bitstream *, char const *, real_vector3d *, long)

	((void(__thiscall *const)(c_bitstream *, char const *, real_vector3d *, long))0x559a90)(this, name, vector, size_in_bits);
}

void c_bitstream::read_point3d(char const *name, real_point3d *point, long axis_encoding_size_in_bits) // 0x10F01A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_point3d@c_bitstream@@QAEXPBDPAUreal_point3d@@J@Z");
	// long axis_encoding_size_in_bits;
	// function call : long (*const)(c_bitstream *, char const *, real_point3d *, long)

	((long(__thiscall *const)(c_bitstream *, char const *, real_point3d *, long))0x558c50)(this, name, point, axis_encoding_size_in_bits);
}

_extern void _sub_10F01810(c_bitstream *const);
void c_bitstream::push_position() // 0x10F01810
{
	mangled_x86(MANGLED_TODO, "?push_position@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	todo("implement");
	_sub_10F01810(this);
}

_extern void _sub_10F01740(c_bitstream *const, bool);
void c_bitstream::pop_position(bool restore) // 0x10F01740
{
	mangled_x86(MANGLED_TODO, "?pop_position@c_bitstream@@QAEX_N@Z");
	// bool restore;
	todo("implement");
	_sub_10F01740(this, restore);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum c_bitstream::e_state,long>::operator==(c_bitstream::e_state const &) const;
template c_enum<enum c_bitstream::e_state,long>::c_enum();
