#ifndef __BLAM_TAG_FILES_TAG_GROUPS_HPP__
#define __BLAM_TAG_FILES_TAG_GROUPS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"


/* ---------- forward declarations */

struct s_tag_block_definition;
struct s_tag_data;
struct s_tag_enum_definition;
struct s_tag_enum_option;
struct s_tag_field_definition;
struct s_tag_group;
struct s_tag_group_definition;
struct s_tag_padding_definition;
struct s_tag_reference;
struct s_tag_reference_short;

/* ---------- constants */

/* ---------- definitions */

struct s_tag_reference
{
	unsigned long group_tag; // 0x0
	char const *name; // 0x4
	long name_length; // 0x8
	unsigned long index; // 0xC
};
static_assert(sizeof(s_tag_reference) == 16, "Invalid s_tag_reference size");

struct s_tag_reference_short
{
	unsigned long index; // 0x0
};
static_assert(sizeof(s_tag_reference_short) == 4, "Invalid s_tag_reference_short size");

struct s_tag_field_definition
{
	c_enum<enum e_tag_field_type,long> type; // 0x0
	char const *name; // 0x4
	void *definition; // 0x8
	// s_tag_field_definition(s_tag_field_definition &); /* compiler_generated(): left implicit so the field tables stay aggregates */
	// s_tag_field_definition(s_tag_field_definition const &); /* compiler_generated(): left implicit so the field tables stay aggregates */
	// s_tag_field_definition(); /* compiler_generated(): left implicit so the field tables stay aggregates */
	// s_tag_field_definition &operator=(s_tag_field_definition &); /* compiler_generated(): left implicit so the field tables stay aggregates */
	// s_tag_field_definition &operator=(s_tag_field_definition const &); /* compiler_generated(): left implicit so the field tables stay aggregates */
};
static_assert(sizeof(s_tag_field_definition) == 12, "Invalid s_tag_field_definition size");

struct s_tag_enum_option
{
	char const *name; // 0x0
	long value; // 0x4
};
static_assert(sizeof(s_tag_enum_option) == 8, "Invalid s_tag_enum_option size");

struct s_tag_enum_definition
{
	char const *name; // 0x0
	long option_count; // 0x4
	s_tag_enum_option *options; // 0x8
};
static_assert(sizeof(s_tag_enum_definition) == 12, "Invalid s_tag_enum_definition size");

struct s_tag_block_definition
{
	char const *name; // 0x0
	long element_size; // 0x4
	long maximum_element_count; // 0x8
	s_tag_field_definition *fields; // 0xC
};
static_assert(sizeof(s_tag_block_definition) == 16, "Invalid s_tag_block_definition size");

// s_tag_block is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

struct s_tag_data
{
	long size; // 0x0
	c_flags<enum e_tag_data_flags,long> flags; // 0x4
	long stream_position; // 0x8
	void *address; // 0xC
	s_tag_block_definition *definition; // 0x10
	s_tag_data(s_tag_data &); /* compiler_generated() */
	s_tag_data(s_tag_data const &); /* compiler_generated() */
	_inline s_tag_data() = default; /* compiler_generated() */
	s_tag_data &operator=(s_tag_data &); /* compiler_generated() */
	s_tag_data &operator=(s_tag_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_tag_data) == 20, "Invalid s_tag_data size");

struct s_tag_padding_definition
{
	char const *name; // 0x0
	long length; // 0x4
};
static_assert(sizeof(s_tag_padding_definition) == 8, "Invalid s_tag_padding_definition size");

struct s_tag_group_definition
{
	char const *name; // 0x0
	unsigned long group_tag; // 0x4
	long size; // 0x8
	s_tag_group_definition *parent; // 0xC
	s_tag_field_definition *fields; // 0x10
	s_tag_group_definition(char const *, unsigned long, long, s_tag_group_definition *, s_tag_field_definition *);
	s_tag_group_definition(char const *, unsigned long, long, s_tag_field_definition *);
};
static_assert(sizeof(s_tag_group_definition) == 20, "Invalid s_tag_group_definition size");

struct s_tag_group
{
	unsigned long tags[3]; // 0x0
	unsigned long name; // 0xC
	static _inline s_tag_group invalid();
};
static_assert(sizeof(s_tag_group) == 16, "Invalid s_tag_group size");

/* ---------- prototypes */

extern void *tag_try_and_get_and_verify_group(unsigned long group_tag, long tag_index);
extern unsigned long tag_try_and_get_group_tag(long tag_index);
extern unsigned long tag_get_group_tag(long tag_index);
extern bool tag_loaded(long tag_index);
extern bool tags_loaded();

/* ---------- globals */

/* ---------- public code */

inline s_tag_group s_tag_group::invalid() // 0x10874460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?invalid@s_tag_group@@SA?AU1@XZ");
	// procedure flags: nofpo

	return { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF }, 0 };
}

/* ---------- private code */

#endif // __BLAM_TAG_FILES_TAG_GROUPS_HPP__
