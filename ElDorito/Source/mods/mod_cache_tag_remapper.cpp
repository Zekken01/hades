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

_extern bool _sub_1089B630(c_mod_cache_tag_remapper const *const);
bool c_mod_cache_tag_remapper::is_valid() const // 0x1089B630
{
	mangled_x86(MANGLED_TODO, "?is_valid@c_mod_cache_tag_remapper@@QBE_NXZ");
	// c_mod_cache_tag_remapper const *const this;
	todo("implement");
	bool __result = _sub_1089B630((c_mod_cache_tag_remapper const *)this);
	return __result;
}

_extern long _sub_1089B280(c_mod_cache_tag_remapper const *const);
long c_mod_cache_tag_remapper::get_runtime_tag_count() const // 0x1089B280
{
	mangled_x86(MANGLED_TODO, "?get_runtime_tag_count@c_mod_cache_tag_remapper@@QBEJXZ");
	// c_mod_cache_tag_remapper const *const this;
	todo("implement");
	long __result = _sub_1089B280((c_mod_cache_tag_remapper const *)this);
	return __result;
}

_extern long _sub_1089B0E0(c_mod_cache_tag_remapper const *const, long);
long c_mod_cache_tag_remapper::get_mod_tag_index(long runtime_index) const // 0x1089B0E0
{
	mangled_x86(MANGLED_TODO, "?get_mod_tag_index@c_mod_cache_tag_remapper@@QBEJJ@Z");
	// static ...; // 0x1089B21C
	// static ...; // 0x1089B214
	// c_mod_cache_tag_remapper const *const this;
	// long runtime_index;
	// std::unordered_map<long,long,std::hash<long>,std::equal_to<long>,std::allocator<std::pair<long const ,long> > > const &map;
	{
		// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<long const ,long> > > > it;
	}
	todo("implement");
	long __result = _sub_1089B0E0((c_mod_cache_tag_remapper const *)this, runtime_index);
	return __result;
}

_extern long _sub_1089B2B0(c_mod_cache_tag_remapper const *const, long);
long c_mod_cache_tag_remapper::get_runtime_tag_index(long mod_index) const // 0x1089B2B0
{
	mangled_x86(MANGLED_TODO, "?get_runtime_tag_index@c_mod_cache_tag_remapper@@QBEJJ@Z");
	// static ...; // 0x1089B3EC
	// static ...; // 0x1089B3E4
	// c_mod_cache_tag_remapper const *const this;
	// long mod_index;
	// std::unordered_map<long,long,std::hash<long>,std::equal_to<long>,std::allocator<std::pair<long const ,long> > > const &map;
	{
		// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<long const ,long> > > > it;
	}
	todo("implement");
	long __result = _sub_1089B2B0((c_mod_cache_tag_remapper const *)this, mod_index);
	return __result;
}

_extern bool _sub_1089B450(c_mod_cache_tag_remapper *const, c_cache_file_tag_cache *);
bool c_mod_cache_tag_remapper::initialize(c_cache_file_tag_cache *base_cache) // 0x1089B450
{
	mangled_x86(MANGLED_TODO, "?initialize@c_mod_cache_tag_remapper@@QAE_NPAVc_cache_file_tag_cache@@@Z");
	// static ...; // 0x1089B5B0
	// static ...; // 0x1089B5A8
	// c_mod_cache_tag_remapper *const this;
	// c_cache_file_tag_cache *base_cache;
	// c_cache_file_tag_cache::c_instance_iterator base_it;
	{
		// char const *base_tag_name;
	}
	todo("implement");
	bool __result = _sub_1089B450(this, base_cache);
	return __result;
}

_extern bool _sub_1089A150(c_mod_cache_tag_remapper *const, c_cache_file_tag_cache const *);
bool c_mod_cache_tag_remapper::add_mod(c_cache_file_tag_cache const *mod_cache) // 0x1089A150
{
	mangled_x86(MANGLED_TODO, "?add_mod@c_mod_cache_tag_remapper@@QAE_NPBVc_cache_file_tag_cache@@@Z");
	// static ...; // 0x1089A4E9
	// static ...; // 0x1089A4E6
	// static ...; // 0x1089A4D4
	// static ...; // 0x1089A4A4
	// static ...; // 0x1089A49C
	// c_mod_cache_tag_remapper *const this;
	// c_cache_file_tag_cache const *mod_cache;
	// long used_mod_tag_count;
	// c_cache_file_tag_cache::c_instance_iterator mod_it;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<c_mod_cache_tag_remapper::s_name_lookup_key const ,long> > > > it;
		// char const *mod_tag_name;
		// s_cache_tag_instance const *base_tag;
		// long base_tag_index;
		// long runtime_tag_index;
	}
	todo("implement");
	bool __result = _sub_1089A150(this, mod_cache);
	return __result;
}

_extern void _sub_1089BA60(c_mod_cache_tag_remapper *const);
void c_mod_cache_tag_remapper::reset() // 0x1089BA60
{
	mangled_x86(MANGLED_TODO, "?reset@c_mod_cache_tag_remapper@@QAEXXZ");
	// c_mod_cache_tag_remapper *const this;
	todo("implement");
	_sub_1089BA60(this);
}

/* ---------- private code */
