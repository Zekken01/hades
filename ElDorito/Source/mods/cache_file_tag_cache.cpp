/* ---------- headers */

#include "mods/cache_file_tag_cache.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "ThirdParty/rapidjson/document.h"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <list>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
class c_file_open_scope;
class c_file_reference;
class c_tag_name_dictionary;
struct s_cache_file_segment_header;
struct s_cache_tag_instance;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_cache_file_tag_cache* _sub_108714F0(c_cache_file_tag_cache *const, c_file_reference const *, unsigned long, c_tag_name_dictionary &);
c_cache_file_tag_cache::c_cache_file_tag_cache(c_file_reference const *file, unsigned long base_offset, c_tag_name_dictionary &&tag_names) : m_base_offset(todo_result<unsigned long>()), m_tag_names(todo_result<c_tag_name_dictionary>()) // 0x108714F0
{
	mangled_x86(MANGLED_TODO, "??0c_cache_file_tag_cache@@QAE@PBVc_file_reference@@K$$QAVc_tag_name_dictionary@@@Z");
	// c_tag_name_dictionary &tag_names;
	todo("implement");
	_sub_108714F0(this, file, base_offset, tag_names);
}

bool c_cache_file_tag_cache::initialize() // 0x108743F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_cache_file_tag_cache@@QAE_NXZ");
	// c_cache_file_tag_cache *const this;

	if (m_initialized)
		return true;
	m_initialized = load_internal();
	return m_initialized;
}

bool c_cache_file_tag_cache::load_internal() // 0x10874500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_internal@c_cache_file_tag_cache@@AAE_NXZ");
	// static ...; // 0x10874614
	// static ...; // 0x10874608
	// static ...; // 0x10874600
	// c_cache_file_tag_cache *const this;
	// c_file_open_scope scope;

	c_file_open_scope scope(m_file, 1);

	if (!read_tag_offsets())
		return false;

	if (!load_tags())
		return false;

	return true;
}

_extern bool _sub_108750D0(c_cache_file_tag_cache *const, c_file_reference *, long, unsigned long, unsigned long, void *);
bool c_cache_file_tag_cache::read_tag_data(c_file_reference *file, long index, unsigned long offset, unsigned long size, void *buffer) // 0x108750D0
{
	mangled_x86(MANGLED_TODO, "?read_tag_data@c_cache_file_tag_cache@@QAE_NPAVc_file_reference@@JKKPAX@Z");
	// void *buffer;
	todo("implement");
	bool __result = _sub_108750D0(this, file, index, offset, size, buffer);
	return __result;
}

_extern bool _sub_10874D60(c_cache_file_tag_cache *const, c_file_reference *, long, unsigned long, void *);
bool c_cache_file_tag_cache::read_and_fixup_tag(c_file_reference *file, long index, unsigned long buffer_size, void *buffer) // 0x10874D60
{
	mangled_x86(MANGLED_TODO, "?read_and_fixup_tag@c_cache_file_tag_cache@@QAE_NPAVc_file_reference@@JKPAX@Z");
	// void *buffer;
	// s_cache_tag_instance *instance;
	// s_cache_tag_instance const *header;
	// unsigned __int32 *fixups;
	{
		// long i;
	}
	todo("implement");
	bool __result = _sub_10874D60(this, file, index, buffer_size, buffer);
	return __result;
}

_extern bool _sub_10874F50(c_cache_file_tag_cache *const, c_file_reference *, unsigned long, unsigned long, void *);
bool c_cache_file_tag_cache::read_data_internal(c_file_reference *file, unsigned long offset, unsigned long size, void *buffer) // 0x10874F50
{
	mangled_x86(MANGLED_TODO, "?read_data_internal@c_cache_file_tag_cache@@AAE_NPAVc_file_reference@@KKPAX@Z");
	// c_file_reference *file;
	// unsigned long offset;
	// unsigned long size;
	// void *buffer;
	// c_file_open_scope scope;
	todo("implement");
	bool __result = _sub_10874F50(this, file, offset, size, buffer);
	return __result;
}

bool c_cache_file_tag_cache::read_tag_offsets() // 0x10875210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_tag_offsets@c_cache_file_tag_cache@@AAE_NXZ");
	// static ...; // 0x10875318
	// static ...; // 0x1087530C
	// static ...; // 0x10875304
	// c_cache_file_tag_cache *const this;
	// s_cache_file_segment_header tags_header;

	s_cache_file_segment_header tags_header;

	if (!read_data_internal(&m_file, 0, sizeof(tags_header), &tags_header))
		return false;

	m_tag_offsets.resize(tags_header.table_count);

	if (!read_data_internal(&m_file, tags_header.table_offset, m_tag_offsets.size() * sizeof(unsigned long), m_tag_offsets.data()))
		return false;

	return true;
}

_extern bool _sub_10874660(c_cache_file_tag_cache *const);
bool c_cache_file_tag_cache::load_tags() // 0x10874660
{
	mangled_x86(MANGLED_TODO, "?load_tags@c_cache_file_tag_cache@@AAE_NXZ");
	// c_cache_file_tag_cache *const this;
	// long actual_count;
	// long absolute_index;
	{
		// unsigned __int32 tag_index;
	}
	{
		// long tag_index;
		{
			// unsigned long const offset;
		}
	}
	todo("implement");
	bool __result = _sub_10874660(this);
	return __result;
}

long c_cache_file_tag_cache::find_by_name(unsigned long group, char const *name) const // 0x10874040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_by_name@c_cache_file_tag_cache@@QBEJKPBD@Z");
	// static ...; // 0x10874108
	// c_cache_file_tag_cache const *const this;
	// unsigned long group;
	// char const *name;
	// c_cache_file_tag_cache::c_instance_iterator iterator;
		// char const *instance_name;

	c_instance_iterator iterator = create_iterator(group);

	while (iterator.next())
	{
		char const *instance_name = m_tag_names.get_name(iterator.tag_index);

		if (!instance_name)
			continue;

		if (strncmp(instance_name, name, k_maximum_long_string_length) == 0)
			return iterator.tag_index;
	}

	return NONE;
}

bool c_cache_file_tag_cache::empty_tag(long index) const // 0x10873EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?empty_tag@c_cache_file_tag_cache@@QBE_NJ@Z");
	// long index;
	// s_cache_tag_instance const *instance;

	const s_cache_tag_instance *instance = get_instance(index);

	if (!instance)
		return false;

	return instance->definition_offset == instance->size;
}

_extern bool _sub_10874AF0(c_cache_file_tag_cache::c_instance_iterator *const);
bool c_cache_file_tag_cache::c_instance_iterator::next() // 0x10874AF0
{
	mangled_x86(MANGLED_TODO, "?next@c_instance_iterator@c_cache_file_tag_cache@@QAE_NXZ");
	// c_cache_file_tag_cache::c_instance_iterator *const this;
	todo("implement");
	bool __result = _sub_10874AF0(this);
	return __result;
}

/* ---------- private code */
