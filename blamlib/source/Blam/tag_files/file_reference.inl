#ifndef __BLAM_TAG_FILES_FILE_REFERENCE_INL__
#define __BLAM_TAG_FILES_FILE_REFERENCE_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/files.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_file_open_scope;
class c_file_reference;
struct s_file_reference;

/* ---------- constants */

/* ---------- definitions */

class c_file_reference :
	public s_file_reference
{
public:
	_inline c_file_reference(c_file_reference const &__that); /* compiler_generated() */
	c_file_reference(wchar_t const *);
	_inline c_file_reference(char const *path);
	_inline c_file_reference();
	_inline ~c_file_reference();
	_inline c_file_reference &initialize_header(c_enum<enum e_file_reference_location,short> location);
	char *get_name(c_flags<enum e_file_reference_flags,long>, char *, long);
	wchar_t *get_name_wide(c_flags<enum e_file_reference_flags,long>, wchar_t *, long);
	_inline c_file_reference &set_name(char const *name);
	c_file_reference &set_name_wide(wchar_t const *);
	c_file_reference &add_name(char const *);
	c_file_reference &add_name_wide(wchar_t const *);
	_inline bool exists() const;
	_inline bool is_open() const;
	_inline bool open(c_flags<enum e_file_permission_flags,long> flags, unsigned long *out_error);
	_inline bool close();
	_inline bool set_position(unsigned long position, bool flag);
	_inline bool read(unsigned long size_in_bytes, bool flag, void *buffer);
	_inline bool read_from_position(unsigned long position, unsigned long size_in_bytes, void *buffer);
	bool write(unsigned long, void *);
	_inline c_file_reference &operator=(c_file_reference const &__that); /* compiler_generated() */
public:
	template<typename t_arg0>
	bool read(t_arg0 *address);
	template<typename t_arg0>
	bool read_from_position(unsigned long position, t_arg0 *address);
};
static_assert(sizeof(c_file_reference) == 272, "Invalid c_file_reference size");

class c_file_open_scope
{
public:
	c_file_open_scope(c_file_open_scope const &);
	_inline c_file_open_scope(s_file_reference &file, long permission_flags);
	_inline ~c_file_open_scope();
	c_file_open_scope &operator=(c_file_open_scope &);
	c_file_open_scope &operator=(c_file_open_scope const &);
	_inline void release_ownership();
private:
	s_file_reference &m_file; // 0x0
	bool m_is_owner; // 0x4
};
static_assert(sizeof(c_file_open_scope) == 8, "Invalid c_file_open_scope size");

/* ---------- prototypes */

extern bool (*const file_read)(s_file_reference *, unsigned long, bool, void *);  // hades: added for 0x1089EE50

extern bool (__cdecl *const file_close)(struct s_file_reference *);  // hades: added for 0x1074CF30

extern s_file_reference *(*const file_reference_initialize_header)(s_file_reference *, c_enum<enum e_file_reference_location,short>);  // hades: added for 0x106D0FD0

extern s_file_reference *(*const file_reference_set_name)(s_file_reference *, char const *);  // hades: added for 0x10875490

extern bool (*const file_exists)(s_file_reference const *);  // hades: added for 0x1089D950

extern bool (*const file_open)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *);  // hades: added for 0x1088BAE0

extern bool (*const file_close)(s_file_reference *);  // hades: added for 0x1089D360

extern bool (*const file_set_position)(s_file_reference *, unsigned long, bool);  // hades: added for 0x10875510

/* ---------- globals */

/* ---------- public code */

_inline c_file_reference::c_file_reference() // 0x106CD8A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_file_reference@@QAE@XZ");
	// c_file_reference *const this;

	initialize_header(_file_reference_location_none);
}

_inline c_file_reference::c_file_reference(char const *path) : c_file_reference() /* hades-mem-init:  */ // 0x108715F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_file_reference@@QAE@PBD@Z");
	// char const *path;

	set_name(path);
}

_inline c_file_reference::~c_file_reference() // 0x106CDDC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_file_reference@@QAE@XZ");
	// c_file_reference *const this;
	// function call : bool (*const)(s_file_reference *)

	file_close(this);
}

_inline c_file_reference &c_file_reference::initialize_header(c_enum<enum e_file_reference_location,short> location) // 0x106D0FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_header@c_file_reference@@QAEAAV1@V?$c_enum@W4e_file_reference_location@@F@@@Z");
	// c_enum<enum e_file_reference_location,short> location;
	// function call : s_file_reference *(*const)(s_file_reference *, c_enum<enum e_file_reference_location,short>)

	return *(c_file_reference *)file_reference_initialize_header(this, location);
}

_inline c_file_reference &c_file_reference::set_name(char const *name) // 0x10875490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_name@c_file_reference@@QAEAAV1@PBD@Z");
	// char const *name;
	// function call : s_file_reference *(*const)(s_file_reference *, char const *)

	return *(c_file_reference *)file_reference_set_name(this, name);
}

_inline bool c_file_reference::exists() const // 0x1089D950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?exists@c_file_reference@@QBE_NXZ");
	// c_file_reference const *const this;
	// function call : bool (*const)(s_file_reference const *)

	return file_exists((c_file_reference const *)this);
}

_inline bool c_file_reference::is_open() const // 0x1088ABE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_open@c_file_reference@@QBE_NXZ");
	// c_file_reference const *const this;

	return file_is_open(this);
}

_inline bool c_file_reference::open(c_flags<enum e_file_permission_flags,long> flags, unsigned long *out_error) // 0x1088BAE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?open@c_file_reference@@QAE_NV?$c_flags@W4e_file_permission_flags@@J@@PAK@Z");
	// unsigned long *out_error;
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)

	return file_open(this, flags, out_error);
}

_inline bool c_file_reference::close() // 0x1089D360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?close@c_file_reference@@QAE_NXZ");
	// c_file_reference *const this;
	// function call : bool (*const)(s_file_reference *)

	return file_close(this);
}

_inline bool c_file_reference::set_position(unsigned long position, bool flag) // 0x10875510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_position@c_file_reference@@QAE_NK_N@Z");
	// bool flag;
	// function call : bool (*const)(s_file_reference *, unsigned long, bool)

	return file_set_position(this, position, flag);
}

_inline bool c_file_reference::read(unsigned long size_in_bytes, bool flag, void *buffer) // 0x10874CE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read@c_file_reference@@QAE_NK_NPAX@Z");
	// void *buffer;
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)

	return file_read(this, size_in_bytes, flag, buffer);
}

_inline bool c_file_reference::read_from_position(unsigned long position, unsigned long size_in_bytes, void *buffer) // 0x1089EE50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_from_position@c_file_reference@@QAE_NKKPAX@Z");
	// void *buffer;
	// function call : bool (*const)(s_file_reference *, unsigned long, bool)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)

	if (!file_set_position(this, position, false))
	{
		return false;
	}

	return file_read(this, size_in_bytes, false, buffer);
}

template<typename t_arg0>
_inline bool c_file_reference::read(t_arg0 *address)
{
	mangled_prefix_assert("??$read@");

	return read(sizeof(*address), false, address);
}

template<typename t_arg0>
_inline bool c_file_reference::read_from_position(unsigned long position, t_arg0 *address)
{
	mangled_prefix_assert("??$read_from_position@");

	return read_from_position(position, sizeof(*address), address);
}

_inline c_file_open_scope::c_file_open_scope(s_file_reference &file, long permission_flags) : m_file(file), m_is_owner(!file_is_open(&m_file)) /* hades-mem-init: : m_file(file) */ // 0x1074C680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_file_open_scope@@QAE@AAUs_file_reference@@J@Z");
	// static ...; // 0x1074C74C
	// c_file_open_scope *const this;
	// s_file_reference &file;
	// long permission_flags;
	// unsigned long err;
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)

	if (m_is_owner)
	{
		unsigned long err;
		file_open(&m_file, permission_flags, &err);
	}
}

_inline c_file_open_scope::~c_file_open_scope() // 0x1074CF30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_file_open_scope@@QAE@XZ");
	// c_file_open_scope *const this;
	// function call : bool (*const)(s_file_reference *)

	if (m_is_owner && file_is_open(&m_file))
	{
		file_close(&m_file);
	}

	release_ownership();
}

_inline void c_file_open_scope::release_ownership() // 0x10752490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_ownership@c_file_open_scope@@QAEXXZ");
	// c_file_open_scope *const this;

	m_is_owner = false;
}

/* ---------- private code */

#endif // __BLAM_TAG_FILES_FILE_REFERENCE_INL__
