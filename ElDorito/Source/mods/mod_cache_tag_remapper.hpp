#ifndef __MODS_MOD_CACHE_TAG_REMAPPER_HPP__
#define __MODS_MOD_CACHE_TAG_REMAPPER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "mods/cache_file_tag_cache.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
class c_mod_cache_tag_remapper;
class c_tag_name_dictionary;
struct s_name_lookup_key;

/* ---------- constants */

/* ---------- definitions */

class c_mod_cache_tag_remapper
{
public:
	public:
#pragma pack(push, 4)
	struct s_name_lookup_key
	{
		public:
		struct s_hasher
		{
			unsigned __int32 operator()(s_name_lookup_key const &) const;
		};
		static_assert(sizeof(s_hasher) == 1, "Invalid s_hasher size");
		public:
		unsigned __int32 group_tag; // 0x0
		std::string_view name; // 0x4
		// s_name_lookup_key(); compiler_generated (hades: left implicit so the key stays an aggregate for initialize)
	};
#pragma pack(pop)
	static_assert(sizeof(s_name_lookup_key) == 12, "Invalid s_name_lookup_key size");
	public:
	bool is_valid() const;
	long get_mod_tag_index(long runtime_index) const;
	long get_runtime_tag_index(long mod_index) const;
	long get_runtime_tag_count() const;
	bool initialize(c_cache_file_tag_cache *base_cache);
	bool add_mod(c_cache_file_tag_cache const *mod_cache);
	void reset();
	c_tag_name_dictionary &steal_tag_names();
private:
	bool m_valid = false; // 0x0
	// 0x1: 3 bytes of implicit padding (hades: no array member, it would add a /GS cookie to stack instances)
	unsigned long m_runtime_memory_size = 0; // 0x4
	long m_runtime_tag_count = 0; // 0x8
	std::unordered_map<long,long> m_runtime_tag_index_to_mod_tag_index; // 0xC
	std::unordered_map<long,long> m_mod_tag_index_to_runtime_index; // 0x34
	c_cache_file_tag_cache *m_base_cache = nullptr; // 0x5C
	std::unordered_map<s_name_lookup_key,long,c_mod_cache_tag_remapper::s_name_lookup_key::s_hasher> m_base_tags_by_name; // 0x60
public:
	c_mod_cache_tag_remapper(c_mod_cache_tag_remapper &); /* compiler_generated() */
	c_mod_cache_tag_remapper(c_mod_cache_tag_remapper const &); /* compiler_generated() */
	_inline c_mod_cache_tag_remapper() = default; /* compiler_generated() */
	_inline ~c_mod_cache_tag_remapper(); /* compiler_generated() */
	c_mod_cache_tag_remapper &operator=(c_mod_cache_tag_remapper &); /* compiler_generated() */
	c_mod_cache_tag_remapper &operator=(c_mod_cache_tag_remapper const &); /* compiler_generated() */
};
static_assert(sizeof(c_mod_cache_tag_remapper) == 136, "Invalid c_mod_cache_tag_remapper size");

/* ---------- prototypes */

namespace Utils { namespace stl { template<typename t_arg0, typename t_arg1> unsigned __int32 hash_combine(t_arg0, t_arg1); } }  // hades: added for 0x10897780

extern _inline bool operator==(c_mod_cache_tag_remapper::s_name_lookup_key const &lhs, c_mod_cache_tag_remapper::s_name_lookup_key const &rhs);

/* ---------- globals */

/* ---------- public code */

inline bool operator==(c_mod_cache_tag_remapper::s_name_lookup_key const &lhs, c_mod_cache_tag_remapper::s_name_lookup_key const &rhs) // 0x10896F70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??8@YA_NABUs_name_lookup_key@c_mod_cache_tag_remapper@@0@Z");
	// c_mod_cache_tag_remapper::s_name_lookup_key const &rhs;

	return lhs.group_tag == rhs.group_tag && lhs.name == rhs.name;
}

inline unsigned __int32 c_mod_cache_tag_remapper::s_name_lookup_key::s_hasher::operator()(c_mod_cache_tag_remapper::s_name_lookup_key const &k) const // 0x10897780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??Rs_hasher@s_name_lookup_key@c_mod_cache_tag_remapper@@QBEIABU12@@Z");
	// c_mod_cache_tag_remapper::s_name_lookup_key const &k;

	return Utils::stl::hash_combine<unsigned int, std::string_view>(k.group_tag, k.name);
}

/* ---------- private code */

#endif // __MODS_MOD_CACHE_TAG_REMAPPER_HPP__
