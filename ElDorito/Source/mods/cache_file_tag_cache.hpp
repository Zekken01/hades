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
	unsigned char __pad0[3]; // 0x1
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

extern c_cache_file_tag_cache::c_instance_iterator* _sub_108716A0(c_cache_file_tag_cache::c_instance_iterator *const, c_cache_file_tag_cache const *, unsigned long);
_inline c_cache_file_tag_cache::c_instance_iterator::c_instance_iterator(c_cache_file_tag_cache const *in_cache, unsigned long in_group_filter) // 0x108716A0
{
	mangled_x86(MANGLED_TODO, "??0c_instance_iterator@c_cache_file_tag_cache@@QAE@PBV1@K@Z");
	// unsigned long in_group_filter;
	todo("implement");
	_sub_108716A0(this, in_cache, in_group_filter);
}

_extern void _sub_10877EB0(c_cache_file_tag_cache *const);
_inline c_cache_file_tag_cache::~c_cache_file_tag_cache() // 0x10877EB0
{
	mangled_x86(MANGLED_TODO, "??1c_cache_file_tag_cache@@QAE@XZ");
	// c_cache_file_tag_cache *const this;
	todo("implement");
	_sub_10877EB0(this);
}

_extern bool _sub_10875680(c_cache_file_tag_cache const *const, long);
_inline bool c_cache_file_tag_cache::valid_index(long index) const // 0x10875680
{
	mangled_x86(MANGLED_TODO, "?valid_index@c_cache_file_tag_cache@@QBE_NJ@Z");
	// long index;
	todo("implement");
	bool __result = _sub_10875680((c_cache_file_tag_cache const *)this, index);
	return __result;
}

_extern bool _sub_10892020(c_cache_file_tag_cache const *const, long);
_inline bool c_cache_file_tag_cache::valid_tag(long index) const // 0x10892020
{
	mangled_x86(MANGLED_TODO, "?valid_tag@c_cache_file_tag_cache@@QBE_NJ@Z");
	// long index;
	todo("implement");
	bool __result = _sub_10892020((c_cache_file_tag_cache const *)this, index);
	return __result;
}

_extern long _sub_10891AA0(c_cache_file_tag_cache const *const);
_inline long c_cache_file_tag_cache::get_tag_count() const // 0x10891AA0
{
	mangled_x86(MANGLED_TODO, "?get_tag_count@c_cache_file_tag_cache@@QBEJXZ");
	// c_cache_file_tag_cache const *const this;
	todo("implement");
	long __result = _sub_10891AA0((c_cache_file_tag_cache const *)this);
	return __result;
}

extern s_cache_tag_instance const *_sub_10874160(c_cache_file_tag_cache const *const, long);
_inline s_cache_tag_instance const *c_cache_file_tag_cache::get_instance(long index) const // 0x10874160
{
	mangled_x86(MANGLED_TODO, "?get_instance@c_cache_file_tag_cache@@QBEPBUs_cache_tag_instance@@J@Z");
	// long index;
	// long const absolute_index;
	todo("implement");
	s_cache_tag_instance const * __result = _sub_10874160((c_cache_file_tag_cache const *)this, index);
	return __result;
}

extern char const *_sub_10891B00(c_cache_file_tag_cache const *const, long);
_inline char const *c_cache_file_tag_cache::get_tag_name(long index) const // 0x10891B00
{
	mangled_x86(MANGLED_TODO, "?get_tag_name@c_cache_file_tag_cache@@QBEPBDJ@Z");
	// long index;
	todo("implement");
	char const * __result = _sub_10891B00((c_cache_file_tag_cache const *)this, index);
	return __result;
}

extern c_cache_file_tag_cache::c_instance_iterator _sub_10873C60(c_cache_file_tag_cache const *const, unsigned long);
_inline c_cache_file_tag_cache::c_instance_iterator c_cache_file_tag_cache::create_iterator(unsigned long group_filter) const // 0x10873C60
{
	mangled_x86(MANGLED_TODO, "?create_iterator@c_cache_file_tag_cache@@QBE?AUc_instance_iterator@1@K@Z");
	// unsigned long group_filter;
	todo("implement");
	c_cache_file_tag_cache::c_instance_iterator __result = _sub_10873C60((c_cache_file_tag_cache const *)this, group_filter);
	return __result;
}

extern c_file_reference _sub_108C2EE0(c_cache_file_tag_cache const *const);
_inline c_file_reference c_cache_file_tag_cache::get_file() const // 0x108C2EE0
{
	mangled_x86(MANGLED_TODO, "?get_file@c_cache_file_tag_cache@@QBE?AVc_file_reference@@XZ");
	// c_cache_file_tag_cache const *const this;
	todo("implement");
	c_file_reference __result = _sub_108C2EE0((c_cache_file_tag_cache const *)this);
	return __result;
}

/* ---------- private code */

#endif // __MODS_CACHE_FILE_TAG_CACHE_HPP__
