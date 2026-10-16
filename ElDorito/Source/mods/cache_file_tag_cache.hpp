#ifndef __MODS_CACHE_FILE_TAG_CACHE_HPP__
#define __MODS_CACHE_FILE_TAG_CACHE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/tag_name_dictionary.hpp"

#include "Blam/cseries/cseries.hpp"  // hades: added for 0x10875680

#include <memory>
#include <vector>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
class c_file_reference;
class c_tag_name_dictionary;
struct s_cache_tag_instance;
struct s_tag_group;

/* ---------- constants */

/* ---------- definitions */

class c_cache_file_tag_cache
{
public:
	public:
#pragma pack(push, 4)
	struct c_instance_iterator
	{
		c_cache_file_tag_cache const *cache; // 0x0
		long tag_index; // 0x4
		long absolute_index; // 0x8
		unsigned long group_tag_filter; // 0xC
		s_cache_tag_instance const *instance; // 0x10
		s_tag_group group; // 0x14
		_inline c_instance_iterator(c_cache_file_tag_cache const *in_cache, unsigned long in_group_filter);
		bool next();
	};
#pragma pack(pop)
	static_assert(sizeof(c_instance_iterator) == 36, "Invalid c_instance_iterator size");
	public:
	c_cache_file_tag_cache(c_cache_file_tag_cache &);
	c_cache_file_tag_cache(c_cache_file_tag_cache const &);
	c_cache_file_tag_cache(c_file_reference const *file, unsigned long base_offset, c_tag_name_dictionary &&tag_names);
	_inline ~c_cache_file_tag_cache();
	c_cache_file_tag_cache &operator=(c_cache_file_tag_cache &);
	c_cache_file_tag_cache &operator=(c_cache_file_tag_cache const);
	bool is_initialized() const;
	bool initialize();
	bool read_tag_data(c_file_reference *file, long index, unsigned long offset, unsigned long size, void *buffer);
	bool read_and_fixup_tag(c_file_reference *file, long index, unsigned long buffer_size, void *buffer);
	long find_by_name(unsigned long group, char const *name) const;
	_inline bool valid_index(long index) const;
	_inline bool valid_tag(long index) const;
	bool empty_tag(long index) const;
	_inline long get_tag_count() const;
	long get_non_null_tag_count() const;
	_inline s_cache_tag_instance const *get_instance(long index) const;
	_inline char const *get_tag_name(long index) const;
	_inline c_instance_iterator create_iterator(unsigned long group_filter) const;
	_inline c_file_reference get_file() const;
private:
	bool read_data_internal(c_file_reference *file, unsigned long offset, unsigned long size, void *buffer);
	bool read_tag_offsets();
	bool load_tags();
	bool load_internal();
	bool m_initialized; // 0x0
	// 0x1: 3 bytes of implicit padding (hades: no array member, it would add a /GS cookie to stack instances)
	c_file_reference m_file; // 0x4
	unsigned long const m_base_offset; // 0x114
	std::vector<unsigned long> m_tag_offsets; // 0x118
	std::vector<s_cache_tag_instance> m_tags; // 0x128
	std::vector<long> m_index_to_absolute_index; // 0x138
	std::vector<long> m_absolute_index_to_index; // 0x148
	c_tag_name_dictionary const m_tag_names; // 0x158
};
static_assert(sizeof(c_cache_file_tag_cache) == 384, "Invalid c_cache_file_tag_cache size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline c_cache_file_tag_cache::c_instance_iterator::c_instance_iterator(c_cache_file_tag_cache const *in_cache, unsigned long in_group_filter) : cache(in_cache), tag_index(-1), absolute_index(-1), group_tag_filter(in_group_filter), instance(nullptr), group(s_tag_group::invalid()) /* hades-mem-init:  */ // 0x108716A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_instance_iterator@c_cache_file_tag_cache@@QAE@PBV1@K@Z");
}

inline c_cache_file_tag_cache::~c_cache_file_tag_cache() // 0x10877EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_cache_file_tag_cache@@QAE@XZ");
}

inline bool c_cache_file_tag_cache::valid_index(long index) const // 0x10875680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?valid_index@c_cache_file_tag_cache@@QBE_NJ@Z");

	if (!(m_initialized)) { display_assert("m_initialized", "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\cache_file_tag_cache.hpp", 65, true); system_exit(-1); }
	return index >= 0 && index < (long)m_tag_offsets.size();
}

inline bool c_cache_file_tag_cache::valid_tag(long index) const // 0x10892020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?valid_tag@c_cache_file_tag_cache@@QBE_NJ@Z");

	return valid_index(index) && ((std::vector<unsigned long> &)m_tag_offsets)[index];
}

inline long c_cache_file_tag_cache::get_tag_count() const // 0x10891AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_tag_count@c_cache_file_tag_cache@@QBEJXZ");

	return m_tag_offsets.size();
}

inline s_cache_tag_instance const *c_cache_file_tag_cache::get_instance(long index) const // 0x10874160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_instance@c_cache_file_tag_cache@@QBEPBUs_cache_tag_instance@@J@Z");

	if (index < 0 || index >= (long)m_index_to_absolute_index.size())
		return nullptr;

	long absolute_index = const_cast<std::vector<long> &>(m_index_to_absolute_index)[index];
	if (absolute_index == -1)
		return nullptr;

	return &const_cast<std::vector<s_cache_tag_instance> &>(m_tags)[absolute_index];
}

inline char const *c_cache_file_tag_cache::get_tag_name(long index) const // 0x10891B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_tag_name@c_cache_file_tag_cache@@QBEPBDJ@Z");

	return m_tag_names.get_name(index);
}

inline c_cache_file_tag_cache::c_instance_iterator c_cache_file_tag_cache::create_iterator(unsigned long group_filter) const // 0x10873C60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create_iterator@c_cache_file_tag_cache@@QBE?AUc_instance_iterator@1@K@Z");

	return c_instance_iterator(this, group_filter);
}

inline c_file_reference c_cache_file_tag_cache::get_file() const // 0x108C2EE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_file@c_cache_file_tag_cache@@QBE?AVc_file_reference@@XZ");

	return c_file_reference(m_file.filename);
}

/* ---------- private code */

#endif // __MODS_CACHE_FILE_TAG_CACHE_HPP__
