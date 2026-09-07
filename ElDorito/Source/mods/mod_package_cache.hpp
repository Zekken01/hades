#ifndef __MODS_MOD_PACKAGE_CACHE_HPP__
#define __MODS_MOD_PACKAGE_CACHE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/tag_files/files.hpp"

/* ---------- forward declarations */

struct s_file_time;
struct s_mod_package_file_entry;
struct s_mod_package_header;
struct s_mod_package_map_file_entry;
struct s_mod_package_metadata;
struct s_mod_package_section_header;
struct s_mod_package_section_table;
struct s_mod_package_tag_cache_entry;
struct s_mod_package_tag_name_entry;

/* ---------- constants */

enum
{
	k_mod_package_map_count = 64, // 0x0040 '@'
	k_number_of_mod_package_tag_cache_entries = 32, // 0x0020 ' '
};

enum e_mod_package_major_versions
{
	_mod_package_current_major_version = 4, // 0x0004
	k_number_of_mod_package_version = 5, // 0x0005
};

enum e_mod_package_sections
{
	_mod_package_section_metadata = 0,
	_mod_package_section_tags,
	_mod_package_section_tag_names,
	_mod_package_section_resources,
	_mod_package_section_map_files,
	_mod_package_section_campaign_files,
	_mod_package_section_fonts,
	_mod_package_section_string_ids,
	_mod_package_section_locales,
	_mod_package_section_files,
	k_number_of_mod_package_sections,
};

/* ---------- definitions */

struct s_mod_package_section_table
{
	long count; // 0x0
	unsigned long offset; // 0x4
};
static_assert(sizeof(s_mod_package_section_table) == 8, "Invalid s_mod_package_section_table size");

struct s_mod_package_section_header
{
	unsigned long size; // 0x0
	unsigned long offset; // 0x4
};
static_assert(sizeof(s_mod_package_section_header) == 8, "Invalid s_mod_package_section_header size");

#pragma pack(push, 4)
struct s_mod_package_tag_name_entry
{
	long tag_index; // 0x0
	char name[256]; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_mod_package_tag_name_entry) == 260, "Invalid s_mod_package_tag_name_entry size");

struct s_mod_package_map_file_entry
{
	unsigned long size; // 0x0
	unsigned long offset; // 0x4
	long tag_cache_index; // 0x8
	long map_id; // 0xC
};
static_assert(sizeof(s_mod_package_map_file_entry) == 16, "Invalid s_mod_package_map_file_entry size");

struct s_mod_package_header
{
	unsigned long signature; // 0x0
	short version_major; // 0x4
	short version_minor; // 0x6
	long file_size; // 0x8
	unsigned char sha1[20]; // 0xC
	c_flags<enum e_mod_package_map_flags,long> map_flags; // 0x20
	c_flags<enum e_mod_package_modifier_flags,long> modifier_flags; // 0x24
	s_mod_package_section_table section_table; // 0x28
	unsigned char rsa_public_key[550]; // 0x30
	unsigned char rsa_signature[512]; // 0x256
	s_mod_package_header(s_mod_package_header &); /* compiler_generated() */
	s_mod_package_header(s_mod_package_header const &); /* compiler_generated() */
	_inline s_mod_package_header(); /* compiler_generated() */
	s_mod_package_header &operator=(s_mod_package_header &); /* compiler_generated() */
	s_mod_package_header &operator=(s_mod_package_header const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x456
};
static_assert(sizeof(s_mod_package_header) == 1112, "Invalid s_mod_package_header size");

struct s_mod_package_metadata
{
	unsigned long signature; // 0x0
	wchar_t name[32]; // 0x4
	char author[32]; // 0x44
	char description[512]; // 0x64
	s_file_time build_date; // 0x264
	short version_major; // 0x26C
	short version_minor; // 0x26E
	char url[512]; // 0x270
};
static_assert(sizeof(s_mod_package_metadata) == 1136, "Invalid s_mod_package_metadata size");

struct s_mod_package_tag_cache_entry
{
	unsigned long size; // 0x0
	unsigned long offset; // 0x4
	char name[32]; // 0x8
};
static_assert(sizeof(s_mod_package_tag_cache_entry) == 40, "Invalid s_mod_package_tag_cache_entry size");

struct s_mod_package_file_entry
{
	unsigned long size; // 0x0
	unsigned long offset; // 0x4
	char path[256]; // 0x8
};
static_assert(sizeof(s_mod_package_file_entry) == 264, "Invalid s_mod_package_file_entry size");

/* ---------- prototypes */

extern bool mod_package_header_valid(s_mod_package_header const *header);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_MOD_PACKAGE_CACHE_HPP__
