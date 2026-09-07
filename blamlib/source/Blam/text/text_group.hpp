#ifndef __BLAM_TEXT_TEXT_GROUP_HPP__
#define __BLAM_TEXT_TEXT_GROUP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_language_pack_offsets;
struct s_multilingual_unicode_string_list_group_header;
struct s_multilingual_unicode_string_reference;
struct s_tag_data;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_multilingual_unicode_string_reference
{
	unsigned long string_id; // 0x0
	char string_id_str[32]; // 0x4
	long offsets[12]; // 0x24
};
#pragma pack(pop)
static_assert(sizeof(s_multilingual_unicode_string_reference) == 84, "Invalid s_multilingual_unicode_string_reference size");

struct s_language_pack_offsets
{
	unsigned short start_index; // 0x0
	unsigned short string_count; // 0x2
};
static_assert(sizeof(s_language_pack_offsets) == 4, "Invalid s_language_pack_offsets size");

struct s_multilingual_unicode_string_list_group_header
{
	c_tag_block<s_multilingual_unicode_string_reference> string_references; // 0x0
	s_tag_data string_data_utf8; // 0xC
	s_language_pack_offsets language_pack_offsets[12]; // 0x20
	s_multilingual_unicode_string_list_group_header(s_multilingual_unicode_string_list_group_header &); /* compiler_generated() */
	s_multilingual_unicode_string_list_group_header(s_multilingual_unicode_string_list_group_header const &); /* compiler_generated() */
	s_multilingual_unicode_string_list_group_header(); /* compiler_generated() */
	s_multilingual_unicode_string_list_group_header &operator=(s_multilingual_unicode_string_list_group_header &); /* compiler_generated() */
	s_multilingual_unicode_string_list_group_header &operator=(s_multilingual_unicode_string_list_group_header const &); /* compiler_generated() */
};
static_assert(sizeof(s_multilingual_unicode_string_list_group_header) == 80, "Invalid s_multilingual_unicode_string_list_group_header size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_TEXT_TEXT_GROUP_HPP__
