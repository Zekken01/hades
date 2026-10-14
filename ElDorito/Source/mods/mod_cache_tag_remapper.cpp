/* ---------- headers */

#include "mods/mod_cache_tag_remapper.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <list>
#include <memory>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
class c_mod_cache_tag_remapper;
struct s_cache_tag_instance;
struct s_name_lookup_key;

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool c_mod_cache_tag_remapper::is_valid() const // 0x1089B630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_valid@c_mod_cache_tag_remapper@@QBE_NXZ");
	// c_mod_cache_tag_remapper const *const this;

	return m_valid;
}

long c_mod_cache_tag_remapper::get_runtime_tag_count() const // 0x1089B280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_runtime_tag_count@c_mod_cache_tag_remapper@@QBEJXZ");
	// c_mod_cache_tag_remapper const *const this;

	return m_runtime_tag_count;
}

long c_mod_cache_tag_remapper::get_mod_tag_index(long runtime_index) const // 0x1089B0E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_mod_tag_index@c_mod_cache_tag_remapper@@QBEJJ@Z");
	// static ...; // 0x1089B21C
	// static ...; // 0x1089B214
	// c_mod_cache_tag_remapper const *const this;
	// long runtime_index;
	// std::unordered_map<long,long> const &map;
		// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<long const ,long> > > > it;

	std::unordered_map<long,long> const &map = m_runtime_tag_index_to_mod_tag_index;
	if (std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<long const ,long> > > > it = map.find(runtime_index); it != std::end(map))
		return it->second;
	return -1;
}

long c_mod_cache_tag_remapper::get_runtime_tag_index(long mod_index) const // 0x1089B2B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_runtime_tag_index@c_mod_cache_tag_remapper@@QBEJJ@Z");
	// static ...; // 0x1089B3EC
	// static ...; // 0x1089B3E4
	// c_mod_cache_tag_remapper const *const this;
	// long mod_index;
	// std::unordered_map<long,long> const &map;
		// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<long const ,long> > > > it;

	std::unordered_map<long,long> const &map = m_mod_tag_index_to_runtime_index;
	if (std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<long const ,long> > > > it = map.find(mod_index); it != std::end(map))
		return it->second;
	return -1;
}

bool c_mod_cache_tag_remapper::initialize(c_cache_file_tag_cache *base_cache) // 0x1089B450
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_mod_cache_tag_remapper@@QAE_NPAVc_cache_file_tag_cache@@@Z");
	// static ...; // 0x1089B5B0
	// static ...; // 0x1089B5A8
	// c_mod_cache_tag_remapper *const this;
	// c_cache_file_tag_cache *base_cache;
	// c_cache_file_tag_cache::c_instance_iterator base_it;
		// char const *base_tag_name;

	reset();
	m_base_cache = base_cache;
	m_runtime_memory_size = 0;
	c_cache_file_tag_cache::c_instance_iterator base_it = base_cache->create_iterator(0xFFFFFFFF);
	while (base_it.next())
	{
		char const *base_tag_name = base_cache->get_tag_name(base_it.tag_index);
		#line 119 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_cache_tag_remapper.cpp"
			assert(base_tag_name);
			#line 128 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_cache_tag_remapper.cpp"
		if (!base_tag_name)
			return false;
		m_base_tags_by_name.emplace(s_name_lookup_key{ base_it.group.tags[0], base_tag_name }, base_it.tag_index);
		m_runtime_memory_size += base_it.instance->size;
		m_runtime_tag_count++;
	}
	m_valid = true;
	return true;
}

bool c_mod_cache_tag_remapper::add_mod(c_cache_file_tag_cache const *mod_cache) // 0x1089A150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_mod@c_mod_cache_tag_remapper@@QAE_NPBVc_cache_file_tag_cache@@@Z");
	// static ...; // 0x1089A4E9
	// static ...; // 0x1089A4E6
	// static ...; // 0x1089A4D4
	// static ...; // 0x1089A4A4
	// static ...; // 0x1089A49C
	// c_mod_cache_tag_remapper *const this;
	// c_cache_file_tag_cache const *mod_cache;
	// long used_mod_tag_count;
	// c_cache_file_tag_cache::c_instance_iterator mod_it;
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<c_mod_cache_tag_remapper::s_name_lookup_key const ,long> > > > it;
		// char const *mod_tag_name;
		// s_cache_tag_instance const *base_tag;
		// long base_tag_index;
		// long runtime_tag_index;

	if (!m_valid)
		return false;
	c_cache_file_tag_cache::c_instance_iterator mod_it = mod_cache->create_iterator(0xFFFFFFFF);
	long used_mod_tag_count = 0;
	while (mod_it.next())
	{
		char const *mod_tag_name = mod_cache->get_tag_name(mod_it.tag_index);
		#line 149 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\mod_cache_tag_remapper.cpp"
			assert(mod_tag_name);
			#line 166 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\mod_cache_tag_remapper.cpp"
		long base_tag_index = -1;
		s_cache_tag_instance const *base_tag = nullptr;
		auto it = m_base_tags_by_name.find(s_name_lookup_key{ mod_it.group.tags[0], mod_tag_name });
		if (it != m_base_tags_by_name.end())
		{
			base_tag_index = it->second;
			base_tag = m_base_cache->get_instance(it->second);
		}
		if (mod_it.instance->definition_offset == mod_it.instance->size)
		{
			m_mod_tag_index_to_runtime_index.insert(std::make_pair(mod_it.tag_index, base_tag_index));
			continue;
		}
		long runtime_tag_index = -1;
		if (base_tag_index == -1)
		{
			runtime_tag_index = 0xFFFF - used_mod_tag_count - 1;
			m_runtime_tag_count++;
			m_runtime_memory_size += mod_it.instance->size;
		}
		else
		{
			runtime_tag_index = base_tag_index;
			m_runtime_memory_size += mod_it.instance->size;
			m_runtime_memory_size -= base_tag->size;
		}
		m_mod_tag_index_to_runtime_index[mod_it.tag_index] = runtime_tag_index;
		m_runtime_tag_index_to_mod_tag_index[runtime_tag_index] = mod_it.tag_index;
		used_mod_tag_count++;
	}
	return true;
}

void c_mod_cache_tag_remapper::reset() // 0x1089BA60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reset@c_mod_cache_tag_remapper@@QAEXXZ");
	// c_mod_cache_tag_remapper *const this;

	m_valid = false;
	m_runtime_tag_count = 0;
	m_mod_tag_index_to_runtime_index.clear();
	m_runtime_tag_index_to_mod_tag_index.clear();
	m_base_tags_by_name.clear();
	m_base_cache = nullptr;
}

/* ---------- private code */
