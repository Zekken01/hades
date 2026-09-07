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

extern c_bitstream* _sub_10F00F80(c_bitstream *const);
c_bitstream::c_bitstream() // 0x10F00F80
{
	mangled_x86(MANGLED_TODO, "??0c_bitstream@@QAE@XZ");
	// c_bitstream *const this;
	todo("implement");
	_sub_10F00F80(this);
}

extern c_bitstream* _sub_10F00EF0(c_bitstream *const, unsigned char *, long);
c_bitstream::c_bitstream(unsigned char *data, long data_length) // 0x10F00EF0
{
	mangled_x86(MANGLED_TODO, "??0c_bitstream@@QAE@PAEJ@Z");
	// long data_length;
	todo("implement");
	_sub_10F00EF0(this, data, data_length);
}

_extern void _sub_10F01010(c_bitstream *const);
c_bitstream::~c_bitstream() // 0x10F01010
{
	mangled_x86(MANGLED_TODO, "??1c_bitstream@@QAE@XZ");
	// c_bitstream *const this;
	todo("implement");
	_sub_10F01010(this);
}

_extern bool _sub_10F02910(c_bitstream const *const);
bool c_bitstream::writing() const // 0x10F02910
{
	mangled_x86(MANGLED_TODO, "?writing@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;
	todo("implement");
	bool __result = _sub_10F02910((c_bitstream const *)this);
	return __result;
}

_extern bool _sub_10F01F90(c_bitstream const *const);
bool c_bitstream::reading() const // 0x10F01F90
{
	mangled_x86(MANGLED_TODO, "?reading@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;
	todo("implement");
	bool __result = _sub_10F01F90((c_bitstream const *)this);
	return __result;
}

_extern bool _sub_10F019F0(c_bitstream const *const);
bool c_bitstream::read_only_for_consistency() const // 0x10F019F0
{
	mangled_x86(MANGLED_TODO, "?read_only_for_consistency@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;
	todo("implement");
	bool __result = _sub_10F019F0((c_bitstream const *)this);
	return __result;
}

_extern bool _sub_10F016B0(c_bitstream const *const);
bool c_bitstream::overflowed() const // 0x10F016B0
{
	mangled_x86(MANGLED_TODO, "?overflowed@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;
	todo("implement");
	bool __result = _sub_10F016B0((c_bitstream const *)this);
	return __result;
}

_extern bool _sub_10F02100(c_bitstream const *const, long);
bool c_bitstream::would_overflow(long size_bits) const // 0x10F02100
{
	mangled_x86(MANGLED_TODO, "?would_overflow@c_bitstream@@QBE_NJ@Z");
	// long size_bits;
	todo("implement");
	bool __result = _sub_10F02100((c_bitstream const *)this, size_bits);
	return __result;
}

_extern bool _sub_10F012B0(c_bitstream const *const);
bool c_bitstream::error_occured() const // 0x10F012B0
{
	mangled_x86(MANGLED_TODO, "?error_occured@c_bitstream@@QBE_NXZ");
	// c_bitstream const *const this;
	todo("implement");
	bool __result = _sub_10F012B0((c_bitstream const *)this);
	return __result;
}

_extern long _sub_10F015E0(c_bitstream const *const);
long c_bitstream::get_space_used_in_bits() const // 0x10F015E0
{
	mangled_x86(MANGLED_TODO, "?get_space_used_in_bits@c_bitstream@@QBEJXZ");
	// c_bitstream const *const this;
	todo("implement");
	long __result = _sub_10F015E0((c_bitstream const *)this);
	return __result;
}

_extern long _sub_10F01640(c_bitstream const *const);
long c_bitstream::get_space_used_in_bytes() const // 0x10F01640
{
	mangled_x86(MANGLED_TODO, "?get_space_used_in_bytes@c_bitstream@@QBEJXZ");
	// c_bitstream const *const this;
	todo("implement");
	long __result = _sub_10F01640((c_bitstream const *)this);
	return __result;
}

_extern long _sub_10F01570(c_bitstream const *const);
long c_bitstream::get_space_left_in_bits() const // 0x10F01570
{
	mangled_x86(MANGLED_TODO, "?get_space_left_in_bits@c_bitstream@@QBEJXZ");
	// c_bitstream const *const this;
	todo("implement");
	long __result = _sub_10F01570((c_bitstream const *)this);
	return __result;
}

_extern long _sub_10F014A0(c_bitstream const *const);
long c_bitstream::get_current_stream_bit_position() const // 0x10F014A0
{
	mangled_x86(MANGLED_TODO, "?get_current_stream_bit_position@c_bitstream@@QBEJXZ");
	// c_bitstream const *const this;
	todo("implement");
	long __result = _sub_10F014A0((c_bitstream const *)this);
	return __result;
}

extern unsigned char const *_sub_10F01500(c_bitstream const *const, long *);
unsigned char const *c_bitstream::get_data(long *data_length) const // 0x10F01500
{
	mangled_x86(MANGLED_TODO, "?get_data@c_bitstream@@QBEPBEPAJ@Z");
	// long *data_length;
	todo("implement");
	unsigned char const * __result = _sub_10F01500((c_bitstream const *)this, data_length);
	return __result;
}

_extern void _sub_10F02080(c_bitstream *const, unsigned char *, long);
void c_bitstream::set_data(unsigned char *data, long data_length) // 0x10F02080
{
	mangled_x86(MANGLED_TODO, "?set_data@c_bitstream@@QAEXPAEJ@Z");
	// long data_length;
	todo("implement");
	_sub_10F02080(this, data, data_length);
}

_extern void _sub_10F01160(c_bitstream *const);
void c_bitstream::begin_reading() // 0x10F01160
{
	mangled_x86(MANGLED_TODO, "?begin_reading@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : void (*const)(c_bitstream *)
	todo("implement");
	_sub_10F01160(this);
}

_extern void _sub_10F010F0(c_bitstream *const);
void c_bitstream::begin_consistency_check() // 0x10F010F0
{
	mangled_x86(MANGLED_TODO, "?begin_consistency_check@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : bool (*const)(c_bitstream *)
	todo("implement");
	_sub_10F010F0(this);
}

_extern void _sub_10F011D0(c_bitstream *const, long);
void c_bitstream::begin_writing(long data_size_alignment) // 0x10F011D0
{
	mangled_x86(MANGLED_TODO, "?begin_writing@c_bitstream@@QAEXJ@Z");
	// long data_size_alignment;
	// function call : void (*const)(c_bitstream *, long)
	todo("implement");
	_sub_10F011D0(this, data_size_alignment);
}

_extern void _sub_10F013C0(c_bitstream *const);
void c_bitstream::finish_reading() // 0x10F013C0
{
	mangled_x86(MANGLED_TODO, "?finish_reading@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : void (*const)(c_bitstream *)
	todo("implement");
	_sub_10F013C0(this);
}

_extern void _sub_10F01350(c_bitstream *const);
void c_bitstream::finish_consistency_check() // 0x10F01350
{
	mangled_x86(MANGLED_TODO, "?finish_consistency_check@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : void (*const)(c_bitstream *)
	todo("implement");
	_sub_10F01350(this);
}

_extern void _sub_10F01430(c_bitstream *const, long *);
void c_bitstream::finish_writing(long *out_size) // 0x10F01430
{
	mangled_x86(MANGLED_TODO, "?finish_writing@c_bitstream@@QAEXPAJ@Z");
	// long *out_size;
	// function call : void (*const)(c_bitstream *, long *)
	todo("implement");
	_sub_10F01430(this, out_size);
}

_extern void _sub_10F01240(c_bitstream *const);
void c_bitstream::discard_remaining_data() // 0x10F01240
{
	mangled_x86(MANGLED_TODO, "?discard_remaining_data@c_bitstream@@QAEXXZ");
	// c_bitstream *const this;
	// function call : void (*const)(c_bitstream *)
	todo("implement");
	_sub_10F01240(this);
}

_extern void _sub_10F02010(c_bitstream *const, c_bitstream::e_state);
void c_bitstream::reset(c_bitstream::e_state state) // 0x10F02010
{
	mangled_x86(MANGLED_TODO, "?reset@c_bitstream@@QAEXW4e_state@1@@Z");
	// c_bitstream::e_state state;
	// function call : void (*const)(c_bitstream *, long)
	todo("implement");
	_sub_10F02010(this, state);
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

_extern void _sub_10F02190(c_bitstream *const, char const *, bool);
void c_bitstream::write_bool(char const *name, bool value) // 0x10F02190
{
	mangled_x86(MANGLED_TODO, "?write_bool@c_bitstream@@QAEXPBD_N@Z");
	// bool value;
	// function call : void (*const)(c_bitstream *, char const *, bool)
	todo("implement");
	_sub_10F02190(this, name, value);
}

_extern void _sub_10F024F0(c_bitstream *const, char const *, void const *, long);
void c_bitstream::write_raw_data(char const *name, void const *data, long data_length) // 0x10F024F0
{
	mangled_x86(MANGLED_TODO, "?write_raw_data@c_bitstream@@QAEXPBDPBXJ@Z");
	// long data_length;
	// function call : void (*const)(c_bitstream *, unsigned char const *, long, bool)
	todo("implement");
	_sub_10F024F0(this, name, data, data_length);
}

_extern void _sub_10F02670(c_bitstream *const, char const *, char const *, long);
void c_bitstream::write_string(char const *name, char const *str, long max_string_size) // 0x10F02670
{
	mangled_x86(MANGLED_TODO, "?write_string@c_bitstream@@QAEXPBD0J@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, char const *, long)
	todo("implement");
	_sub_10F02670(this, name, str, max_string_size);
}

_extern void _sub_10F026F0(c_bitstream *const, char const *, utf8 const *, long);
void c_bitstream::write_string_utf8(char const *name, utf8 const *str, long max_string_size) // 0x10F026F0
{
	mangled_x86(MANGLED_TODO, "?write_string_utf8@c_bitstream@@QAEXPBDPBUutf8@@J@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, utf8 const *, long)
	todo("implement");
	_sub_10F026F0(this, name, str, max_string_size);
}

_extern void _sub_10F02770(c_bitstream *const, char const *, wchar_t const *, long);
void c_bitstream::write_string_wchar(char const *name, wchar_t const *str, long max_string_size) // 0x10F02770
{
	mangled_x86(MANGLED_TODO, "?write_string_wchar@c_bitstream@@QAEXPBDPB_WJ@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, wchar_t const *, long)
	todo("implement");
	_sub_10F02770(this, name, str, max_string_size);
}

_extern void _sub_10F02870(c_bitstream *const, char const *, real_vector3d const *, float, float, __int32, __int32);
void c_bitstream::write_vector(char const *name, real_vector3d const *vector, float magnitude_min, float magnitude_max, __int32 size_in_bits_min, __int32 size_in_bits_max) // 0x10F02870
{
	mangled_x86(MANGLED_TODO, "?write_vector@c_bitstream@@QAEXPBDPBUreal_vector3d@@MMHH@Z");
	// __int32 size_in_bits_max;
	// function call : void (*const)(c_bitstream *, char const *, real_vector3d const *, float, float, __int32, __int32)
	todo("implement");
	_sub_10F02870(this, name, vector, magnitude_min, magnitude_max, size_in_bits_min, size_in_bits_max);
}

_extern void _sub_10F027F0(c_bitstream *const, char const *, real_vector3d const *, __int32);
void c_bitstream::write_unit_vector(char const *name, real_vector3d const *vector, __int32 size_in_bits) // 0x10F027F0
{
	mangled_x86(MANGLED_TODO, "?write_unit_vector@c_bitstream@@QAEXPBDPBUreal_vector3d@@H@Z");
	// __int32 size_in_bits;
	// function call : void (*const)(c_bitstream *, char const *, real_vector3d const *, long)
	todo("implement");
	_sub_10F027F0(this, name, vector, size_in_bits);
}

_extern void _sub_10F022D0(c_bitstream *const, char const *, real_point3d const *, long);
void c_bitstream::write_point3d(char const *name, real_point3d const *point, long axis_encoding_size_in_bits) // 0x10F022D0
{
	mangled_x86(MANGLED_TODO, "?write_point3d@c_bitstream@@QAEXPBDPBUreal_point3d@@J@Z");
	// long axis_encoding_size_in_bits;
	// function call : void (*const)(c_bitstream *, char const *, real_point3d const *, long)
	todo("implement");
	_sub_10F022D0(this, name, point, axis_encoding_size_in_bits);
}

_extern void _sub_10F02350(c_bitstream *const, char const *, float, float, float, __int32, bool, bool);
void c_bitstream::write_quantized_real(char const *name, float value, float min_value, float max_value, __int32 size_in_bits, bool exact_midpoint, bool unknown) // 0x10F02350
{
	mangled_x86(MANGLED_TODO, "?write_quantized_real@c_bitstream@@QAEXPBDMMMH_N1@Z");
	// bool unknown;
	// function call : void (*const)(c_bitstream *, char const *, float, float, float, __int32, bool, bool)
	todo("implement");
	_sub_10F02350(this, name, value, min_value, max_value, size_in_bits, exact_midpoint, unknown);
}

_extern unsigned long _sub_10F01980(c_bitstream *const, char const *, long);
unsigned long c_bitstream::read_integer(char const *name, long size_in_bits) // 0x10F01980
{
	mangled_x86(MANGLED_TODO, "?read_integer@c_bitstream@@QAEKPBDJ@Z");
	// long size_in_bits;
	// function call : unsigned long (*const)(c_bitstream *, long)
	todo("implement");
	unsigned long __result = _sub_10F01980(this, name, size_in_bits);
	return __result;
}

_extern long _sub_10F01C80(c_bitstream *const, char const *, long);
long c_bitstream::read_signed_integer(char const *name, long size_in_bits) // 0x10F01C80
{
	mangled_x86(MANGLED_TODO, "?read_signed_integer@c_bitstream@@QAEJPBDJ@Z");
	// long size_in_bits;
	// function call : unsigned long (*const)(c_bitstream *, long)
	todo("implement");
	long __result = _sub_10F01C80(this, name, size_in_bits);
	return __result;
}

_extern unsigned long long _sub_10F01B90(c_bitstream *const, char const *, long);
unsigned long long c_bitstream::read_qword(char const *name, long size_in_bits) // 0x10F01B90
{
	mangled_x86(MANGLED_TODO, "?read_qword@c_bitstream@@QAE_KPBDJ@Z");
	// long size_in_bits;
	// function call : unsigned long long (*const)(c_bitstream *, long)
	todo("implement");
	unsigned long long __result = _sub_10F01B90(this, name, size_in_bits);
	return __result;
}

_extern bool _sub_10F01910(c_bitstream *const, char const *);
bool c_bitstream::read_bool(char const *name) // 0x10F01910
{
	mangled_x86(MANGLED_TODO, "?read_bool@c_bitstream@@QAE_NPBD@Z");
	// char const *name;
	// function call : bool (*const)(c_bitstream *)
	todo("implement");
	bool __result = _sub_10F01910(this, name);
	return __result;
}

_extern void _sub_10F01C00(c_bitstream *const, char const *, void *, long);
void c_bitstream::read_raw_data(char const *name, void *buffer, long size_in_bits) // 0x10F01C00
{
	mangled_x86(MANGLED_TODO, "?read_raw_data@c_bitstream@@QAEXPBDPAXJ@Z");
	// long size_in_bits;
	// function call : void (*const)(c_bitstream *, void *, long)
	todo("implement");
	_sub_10F01C00(this, name, buffer, size_in_bits);
}

_extern void _sub_10F01CF0(c_bitstream *const, char const *, char *, long);
void c_bitstream::read_string(char const *name, char *buffer, long max_string_size) // 0x10F01CF0
{
	mangled_x86(MANGLED_TODO, "?read_string@c_bitstream@@QAEXPBDPADJ@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, char *, long)
	todo("implement");
	_sub_10F01CF0(this, name, buffer, max_string_size);
}

_extern void _sub_10F01D70(c_bitstream *const, char const *, utf8 *, long);
void c_bitstream::read_string_utf8(char const *name, utf8 *buffer, long max_string_size) // 0x10F01D70
{
	mangled_x86(MANGLED_TODO, "?read_string_utf8@c_bitstream@@QAEXPBDPAUutf8@@J@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, utf8 *, long)
	todo("implement");
	_sub_10F01D70(this, name, buffer, max_string_size);
}

_extern void _sub_10F01DF0(c_bitstream *const, char const *, wchar_t *, long);
void c_bitstream::read_string_wchar(char const *name, wchar_t *buffer, long max_string_size) // 0x10F01DF0
{
	mangled_x86(MANGLED_TODO, "?read_string_wchar@c_bitstream@@QAEXPBDPA_WJ@Z");
	// long max_string_size;
	// function call : void (*const)(c_bitstream *, char const *, wchar_t *, long)
	todo("implement");
	_sub_10F01DF0(this, name, buffer, max_string_size);
}

_extern void _sub_10F01EF0(c_bitstream *const, char const *, real_vector3d *, float, float, long, long);
void c_bitstream::read_vector(char const *name, real_vector3d *vector, float magnitude_min, float magnitude_max, long size_in_bits_min, long size_in_bits_max) // 0x10F01EF0
{
	mangled_x86(MANGLED_TODO, "?read_vector@c_bitstream@@QAEXPBDPAUreal_vector3d@@MMJJ@Z");
	// long size_in_bits_max;
	// function call : void (*const)(c_bitstream *, char const *, real_vector3d *, float, float, long, long)
	todo("implement");
	_sub_10F01EF0(this, name, vector, magnitude_min, magnitude_max, size_in_bits_min, size_in_bits_max);
}

_extern float _sub_10F01AF0(c_bitstream *const, char const *, float, float, __int32, bool, bool);
float c_bitstream::read_quantized_real(char const *name, float min_value, float max_value, __int32 size_in_bits, bool exact_midpoint, bool unknown) // 0x10F01AF0
{
	mangled_x86(MANGLED_TODO, "?read_quantized_real@c_bitstream@@QAEMPBDMMH_N1@Z");
	// bool unknown;
	// function call : float (*const)(c_bitstream *, char const *, float, float, __int32, bool, bool)
	todo("implement");
	float __result = _sub_10F01AF0(this, name, min_value, max_value, size_in_bits, exact_midpoint, unknown);
	return __result;
}

_extern void _sub_10F01E70(c_bitstream *const, char const *, real_vector3d *, long);
void c_bitstream::read_unit_vector(char const *name, real_vector3d *vector, long size_in_bits) // 0x10F01E70
{
	mangled_x86(MANGLED_TODO, "?read_unit_vector@c_bitstream@@QAEXPBDPAUreal_vector3d@@J@Z");
	// long size_in_bits;
	// function call : void (*const)(c_bitstream *, char const *, real_vector3d *, long)
	todo("implement");
	_sub_10F01E70(this, name, vector, size_in_bits);
}

_extern void _sub_10F01A70(c_bitstream *const, char const *, real_point3d *, long);
void c_bitstream::read_point3d(char const *name, real_point3d *point, long axis_encoding_size_in_bits) // 0x10F01A70
{
	mangled_x86(MANGLED_TODO, "?read_point3d@c_bitstream@@QAEXPBDPAUreal_point3d@@J@Z");
	// long axis_encoding_size_in_bits;
	// function call : long (*const)(c_bitstream *, char const *, real_point3d *, long)
	todo("implement");
	_sub_10F01A70(this, name, point, axis_encoding_size_in_bits);
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
