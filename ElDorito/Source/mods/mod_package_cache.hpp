#ifndef __MODS_MOD_PACKAGE_CACHE_HPP__
#define __MODS_MOD_PACKAGE_CACHE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/tag_files/files.hpp"
#include "Blam/cache/cache_files.hpp"

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
	// hades: special members left implicit (CModPackageFileSystemView::ReadFileTable aggregate-initializes the header)
	//
	//
	//
	//
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

// hades: moved from hades/recovered_types.h, where its member types were not visible
class c_mod_package
{
public:
	enum e_error
	{
		_error_none = 0,
		_error_not_found = 1,
		_error_access_denied = 2,
		_error_bad_format = 3,
	};
	static_assert32(sizeof(e_error) == 4, "Invalid e_error size");
public:
	bool m_valid; // 0x0
	// 0x1: 3 bytes of implicit padding (hades: no array member, it would add a /GS cookie to stack instances)
	int m_campaign_file_count; // 0x4
	unsigned int m_tags_section_offset; // 0x8
	unsigned int m_resource_cache_offset; // 0xC
	c_file_reference m_file; // 0x10
	s_mod_package_header m_header; // 0x120
	s_mod_package_metadata m_metadata; // 0x578
	s_cache_file_segment_header m_resource_cache_header; // 0x9E8
	s_mod_package_section_header m_sections[10]; // 0xA08
	int m_tag_cache_count; // 0xA58
	s_mod_package_tag_cache_entry m_tag_cache_entries[32]; // 0xA5C
	int m_map_file_count; // 0xF5C
	s_mod_package_map_file_entry m_map_files[64]; // 0xF60
public:
	bool valid() const;
	void dispose();
	std::shared_ptr<c_cache_file_tag_cache> open_tag_cache(c_file_reference &, long);
	c_file_reference get_file() const;
	c_mod_package(char const *);
	~c_mod_package();
	char const * get_file_name() const;
	s_mod_package_header const * get_header() const;
	s_mod_package_metadata const * get_metadata() const;
	long get_map_count() const;
	s_mod_package_map_file_entry const * get_map_file_entry(long) const;
	bool valid_map_file_index(long) const;
	long find_map_file_by_map_id(long, unsigned long *);
	long get_tag_cache_index_for_map_id(long);
	bool read_campaign(c_file_reference &, s_blf_campaign *, bool *);
	bool read_map_cache_file_header(c_file_reference &, long, s_cache_file_header *);
	bool read_map_blf_map_information(c_file_reference &, long, s_blf_map_information *);
	bool verify_signature();
	bool compute_hash(unsigned char (&)[20]);
	bool verify_hash(unsigned char const (&)[20]) const;
	bool initialize(e_error *);
	static _inline char const *get_error_string(e_error err); // hades: was missing, inline (emitted where used)
	bool get_section_header(e_mod_package_sections, s_mod_package_section_header *);
	bool read_section_data(c_file_reference &, e_mod_package_sections, unsigned long, unsigned long, void *);
	bool valid_section(e_mod_package_sections) const;
	bool valid_section_offset(e_mod_package_sections, unsigned long) const;
private:
	e_error initialize_internal();
	bool read_metadata_section(s_mod_package_metadata *);
	bool read_tags_section();
	bool read_resources_section(s_cache_file_segment_header *);
public:
	unsigned long get_tag_cache_offset(int) const;
	unsigned long get_resource_cache_offset() const;
	std::shared_ptr<Blam::Cache::StringIDCache> open_string_id_cache(c_file_reference &);
private:
	bool read_section_headers();
	bool read_map_files_section();
public:
	bool read_map_file_into_buffer(c_file_reference &, long, unsigned long, void *);
	bool read_font_package_blocking(c_file_reference &, unsigned long, unsigned long, void *);
	std::unordered_map<int,std::string> read_tag_names(c_file_reference &, int);
public:
	c_mod_package();
};
static_assert32(sizeof(c_mod_package) == 4960, "Invalid c_mod_package size");

/* ---------- prototypes */

extern bool mod_package_header_valid(s_mod_package_header const *header);

/* ---------- globals */

/* ---------- public code */

inline char const *c_mod_package::get_error_string(c_mod_package::e_error err) // 0x1071D070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_error_string@c_mod_package@@SAPBDW4e_error@1@@Z");
	// c_mod_package::e_error err;

	switch (err)
	{
	case _error_none:
		return "none";
	case _error_not_found:
		return "not found";
	case _error_access_denied:
		return "access denied";
	case _error_bad_format:
		return "bad format";
	}

	return "unknown error";
}

/* ---------- private code */

#endif // __MODS_MOD_PACKAGE_CACHE_HPP__
