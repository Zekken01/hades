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

inline c_file_reference::c_file_reference() // 0x106CD8A0
{
	initialize_header(_file_reference_location_none);
}

inline c_file_reference::c_file_reference(char const *path) : c_file_reference() /* hades-mem-init:  */ // 0x108715F0
{
	set_name(path);
}

inline c_file_reference::~c_file_reference() // 0x106CDDC0
{
	file_close(this);
}

inline c_file_reference &c_file_reference::initialize_header(c_enum<enum e_file_reference_location,short> location) // 0x106D0FD0
{
	return *(c_file_reference *)file_reference_initialize_header(this, location);
}

inline c_file_reference &c_file_reference::set_name(char const *name) // 0x10875490
{
	return *(c_file_reference *)file_reference_set_name(this, name);
}

inline bool c_file_reference::exists() const // 0x1089D950
{
	return file_exists((c_file_reference const *)this);
}

inline bool c_file_reference::is_open() const // 0x1088ABE0
{
	return file_is_open(this);
}

inline bool c_file_reference::open(c_flags<enum e_file_permission_flags,long> flags, unsigned long *out_error) // 0x1088BAE0
{
	return file_open(this, flags, out_error);
}

inline bool c_file_reference::close() // 0x1089D360
{
	return file_close(this);
}

inline bool c_file_reference::set_position(unsigned long position, bool flag) // 0x10875510
{
	return file_set_position(this, position, flag);
}

inline bool c_file_reference::read(unsigned long size_in_bytes, bool flag, void *buffer) // 0x10874CE0
{
	return file_read(this, size_in_bytes, flag, buffer);
}

inline bool c_file_reference::read_from_position(unsigned long position, unsigned long size_in_bytes, void *buffer) // 0x1089EE50
{
	if (!file_set_position(this, position, false))
	{
		return false;
	}

	return file_read(this, size_in_bytes, false, buffer);
}

template<typename t_arg0>
_inline bool c_file_reference::read(t_arg0 *address)
{
	return read(sizeof(*address), false, address);
}

template<typename t_arg0>
_inline bool c_file_reference::read_from_position(unsigned long position, t_arg0 *address)
{
	return read_from_position(position, sizeof(*address), address);
}

inline c_file_open_scope::c_file_open_scope(s_file_reference &file, long permission_flags) : m_file(file), m_is_owner(!file_is_open(&m_file)) /* hades-mem-init: : m_file(file) */ // 0x1074C680
{
	if (m_is_owner)
	{
		unsigned long err;
		file_open(&m_file, permission_flags, &err);
	}
}

inline c_file_open_scope::~c_file_open_scope() // 0x1074CF30
{
	if (m_is_owner && file_is_open(&m_file))
	{
		file_close(&m_file);
	}

	release_ownership();
}

inline void c_file_open_scope::release_ownership() // 0x10752490
{
	m_is_owner = false;
}

/* ---------- private code */

#endif // __BLAM_TAG_FILES_FILE_REFERENCE_INL__
