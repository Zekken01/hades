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

c_cache_file_tag_cache::c_cache_file_tag_cache(c_file_reference const *file, unsigned long base_offset, c_tag_name_dictionary &&tag_names) : m_initialized(false), m_file(file->filename), m_base_offset(base_offset), m_tag_names(std::move(tag_names)) /* hades-mem-init: : m_base_offset(todo_result<unsigned long>()), m_tag_names(todo_result<c_tag_name_dictionary>()) */ // 0x108714F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_cache_file_tag_cache@@QAE@PBVc_file_reference@@K$$QAVc_tag_name_dictionary@@@Z");
}

bool c_cache_file_tag_cache::initialize() // 0x108743F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_cache_file_tag_cache@@QAE_NXZ");

	if (m_initialized)
		return true;
	m_initialized = load_internal();
	return m_initialized;
}

bool c_cache_file_tag_cache::load_internal() // 0x10874500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_internal@c_cache_file_tag_cache@@AAE_NXZ");

	c_file_open_scope scope(m_file, 1);

	if (!read_tag_offsets())
		return false;

	if (!load_tags())
		return false;

	return true;
}

#line 90
bool c_cache_file_tag_cache::read_tag_data(c_file_reference *file, long index, unsigned long offset, unsigned long size, void *buffer) // 0x108750D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_tag_data@c_cache_file_tag_cache@@QAE_NPAVc_file_reference@@JKKPAX@Z");
#line 94

	#line 92 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\cache_file_tag_cache.cpp"
		if (!(valid_index(index))) { display_assert("valid_index(index)", __FILE__, __LINE__, true); system_exit(-1); }
		if (!(buffer)) { display_assert("buffer", __FILE__, __LINE__, true); system_exit(-1); }
		#line 99 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\cache_file_tag_cache.cpp"
	if (!m_tag_offsets[index])
		return false;
	return read_data_internal(file, m_tag_offsets[index] + offset, size, buffer);
}

bool c_cache_file_tag_cache::read_and_fixup_tag(c_file_reference *file, long index, unsigned long buffer_size, void *buffer) // 0x10874D60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_and_fixup_tag@c_cache_file_tag_cache@@QAE_NPAVc_file_reference@@JKPAX@Z");
#line 112

	#line 106 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\cache_file_tag_cache.cpp"
		if (!(valid_index(index))) { display_assert("valid_index(index)", __FILE__, __LINE__, true); system_exit(-1); }
		#line 107 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\cache_file_tag_cache.cpp"
		if (!(buffer)) { display_assert("buffer", __FILE__, __LINE__, true); system_exit(-1); }
		#line 118 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\cache_file_tag_cache.cpp"
	s_cache_tag_instance const *header = get_instance(index);
	if (!header)
		return false;
	if (header->size > buffer_size)
	{
		#line 115 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\cache_file_tag_cache.cpp"
			if (!(!"insufficent buffer")) { display_assert("!\"insufficent buffer\"", __FILE__, __LINE__, true); system_exit(-1); }
			#line 126 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\cache_file_tag_cache.cpp"
		return false;
	}
	if (!read_tag_data(file, index, 0, header->size, buffer))
		return false;
	s_cache_tag_instance *instance = (s_cache_tag_instance *)buffer;
	unsigned __int32 *fixups = (unsigned __int32 *)&instance[1] + instance->dependency_count;
	for (long i = 0; i < instance->fixup_count; i++)
		*(unsigned long *)((char *)instance + fixups[i] - 0x40000000) = (unsigned long)((char *)instance + *(unsigned long *)((char *)instance + fixups[i] - 0x40000000) - 0x40000000);
	return true;
}

bool c_cache_file_tag_cache::read_data_internal(c_file_reference *file, unsigned long offset, unsigned long size, void *buffer) // 0x10874F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_data_internal@c_cache_file_tag_cache@@AAE_NPAVc_file_reference@@KKPAX@Z");

	c_file_open_scope scope(*file, 1);
	if (!file->set_position(m_base_offset + offset, false))
		return false;
	if (!file->read(size, false, buffer))
		return false;
	return true;
}

bool c_cache_file_tag_cache::read_tag_offsets() // 0x10875210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_tag_offsets@c_cache_file_tag_cache@@AAE_NXZ");

	s_cache_file_segment_header tags_header;

	if (!read_data_internal(&m_file, 0, sizeof(tags_header), &tags_header))
		return false;

	m_tag_offsets.resize(tags_header.table_count);

	if (!read_data_internal(&m_file, tags_header.table_offset, m_tag_offsets.size() * sizeof(unsigned long), m_tag_offsets.data()))
		return false;

	return true;
}

bool c_cache_file_tag_cache::load_tags() // 0x10874660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_tags@c_cache_file_tag_cache@@AAE_NXZ");

	long absolute_index = 0;
	long actual_count = 0;
	for (unsigned __int32 tag_index = 0; tag_index < m_tag_offsets.size(); tag_index++)
	{
		if (m_tag_offsets[tag_index])
			actual_count++;
	}
	m_tags.resize(actual_count);
	m_index_to_absolute_index.resize(m_tag_offsets.size(), -1);
	m_absolute_index_to_index.resize(actual_count, -1);
	for (long tag_index = 0; tag_index < (long)m_tag_offsets.size(); tag_index++)
	{
		unsigned long const offset = m_tag_offsets[tag_index];
		if (!offset)
			continue;
		if (!read_data_internal(&m_file, offset, sizeof(s_cache_tag_instance), &m_tags[absolute_index]))
			return false;
		m_absolute_index_to_index[absolute_index] = tag_index;
		m_index_to_absolute_index[tag_index] = absolute_index;
		absolute_index++;
	}
	return true;
}

long c_cache_file_tag_cache::find_by_name(unsigned long group, char const *name) const // 0x10874040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_by_name@c_cache_file_tag_cache@@QBEJKPBD@Z");

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

	const s_cache_tag_instance *instance = get_instance(index);

	if (!instance)
		return false;

	return instance->definition_offset == instance->size;
}

bool c_cache_file_tag_cache::c_instance_iterator::next() // 0x10874AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?next@c_instance_iterator@c_cache_file_tag_cache@@QAE_NXZ");

	while (true)
	{
		if (++absolute_index >= (long)cache->m_tags.size())
			return false;

		tag_index = const_cast<c_cache_file_tag_cache *>(cache)->m_absolute_index_to_index.at(absolute_index);
		instance = &const_cast<c_cache_file_tag_cache *>(cache)->m_tags.at(absolute_index);
		group = instance->group;
		if (group_tag_filter == -1 || group_tag_filter == group.tags[0] || group_tag_filter == group.tags[1] || group_tag_filter == group.tags[2])
			break;
	}
	return true;
}

/* ---------- private code */
