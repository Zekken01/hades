/* ---------- headers */

#include "mods/map_variant_tag_fixups.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/saved_games/scenario_map_variant_blf.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/blf_reader.hpp"
#include "mods/cache_file_interface.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/map_variant_loader.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "ThirdParty/rapidjson/document.h"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class IMod;
class c_cache_file_tag_cache;
class c_map_variant_tag_fixups;
class c_mod_package;
struct c_cache_file_interface;
struct s_blf_chunk_header;
struct s_blf_chunk_mapv_tag_names;
struct s_file_reference;
struct s_map_variant;
struct s_mod_loading_state;
struct s_name_lookup_key;
struct s_tag_group;
struct s_variant_quota;

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

// s_mod_loading_state is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

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
	std::basic_string_view<char,std::char_traits<char> > name; // 0x4
	s_name_lookup_key(); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_name_lookup_key) == 12, "Invalid s_name_lookup_key size");

/* ---------- prototypes */

extern _inline bool operator==(s_name_lookup_key const &lhs, s_name_lookup_key const &rhs);

extern "C" bool in_tag_group(s_tag_group const &group, long needle);
extern "C" void log_error(char const *message);
extern "C" void log_errorf(char const *format, ...);
extern "C" bool fixup_map_variant_internal(s_blf_chunk_mapv_tag_names const *fixup_data, s_map_variant *map_variant);

/* ---------- globals */

extern s_mod_loading_state g_mod_loading_state; // 0x12407830

/* ---------- private variables */

/* ---------- public code */

_extern bool _sub_1088EA80(s_name_lookup_key const &, s_name_lookup_key const &);
_inline bool operator==(s_name_lookup_key const &lhs, s_name_lookup_key const &rhs) // 0x1088EA80
{
	mangled_x86(MANGLED_TODO, "??8@YA_NABUs_name_lookup_key@@0@Z");
	// s_name_lookup_key const &rhs;
	todo("implement");
	bool __result = _sub_1088EA80(lhs, rhs);
	return __result;
}

_extern unsigned __int32 _sub_1088EF80(s_name_lookup_key::s_hasher const *const, s_name_lookup_key const &);
_inline unsigned __int32 s_name_lookup_key::s_hasher::operator()(s_name_lookup_key const &k) const // 0x1088EF80
{
	mangled_x86(MANGLED_TODO, "??Rs_hasher@s_name_lookup_key@@QBEIABU1@@Z");
	// s_name_lookup_key const &k;
	todo("implement");
	unsigned __int32 __result = _sub_1088EF80((s_name_lookup_key::s_hasher const *)this, k);
	return __result;
}

extern s_mod_loading_state* _sub_1088E290(s_mod_loading_state *const);
_inline s_mod_loading_state::s_mod_loading_state() // 0x1088E290
{
	mangled_x86(MANGLED_TODO, "??0s_mod_loading_state@@QAE@XZ");
	// s_mod_loading_state *const this;
	compiler_generated();
	todo("implement");
	_sub_1088E290(this);
}

_extern void _sub_1088E8D0(s_mod_loading_state *const);
_inline s_mod_loading_state::~s_mod_loading_state() // 0x1088E8D0
{
	mangled_x86(MANGLED_TODO, "??1s_mod_loading_state@@QAE@XZ");
	// s_mod_loading_state *const this;
	compiler_generated();
	todo("implement");
	_sub_1088E8D0(this);
}

_extern bool _sub_10890DD0(unsigned char *, unsigned long, s_map_variant *);
bool c_map_variant_tag_fixups::fixup_map_variant_in_memory(unsigned char *buffer, unsigned long buffer_size, s_map_variant *map_variant) // 0x10890DD0
{
	mangled_x86(MANGLED_TODO, "?fixup_map_variant_in_memory@c_map_variant_tag_fixups@@SA_NPAEKPAUs_map_variant@@@Z");
	// static ...; // 0x10890E94
	// static ...; // 0x10890E70
	// static ...; // 0x10890E68
	// unsigned char *buffer;
	// unsigned long buffer_size;
	// s_map_variant *map_variant;
	// s_blf_chunk_header chunk_header;
	// unsigned char const *data;
	// unsigned long data_size;
	todo("implement");
	bool __result = _sub_10890DD0(buffer, buffer_size, map_variant);
	return __result;
}

_extern bool _sub_10890AD0(s_file_reference *, s_map_variant *);
bool c_map_variant_tag_fixups::fixup_map_variant_from_file(s_file_reference *file, s_map_variant *map_variant) // 0x10890AD0
{
	mangled_x86(MANGLED_TODO, "?fixup_map_variant_from_file@c_map_variant_tag_fixups@@SA_NPAUs_file_reference@@PAUs_map_variant@@@Z");
	// static ...; // 0x10890D1C
	// static ...; // 0x10890D18
	// static ...; // 0x10890CF4
	// static ...; // 0x10890CEC
	// s_file_reference *file;
	// s_map_variant *map_variant;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > file_buff;
	// unsigned long err;
	// bool result;
	// unsigned long file_size;
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)
	// function call : bool (*const)(s_file_reference *)
	todo("implement");
	bool __result = _sub_10890AD0(file, map_variant);
	return __result;
}

void c_map_variant_tag_fixups::initialize() // 0x10891BF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_map_variant_tag_fixups@@SAXXZ");
	// procedure flags: nofpo
}

/* ---------- private code */

_extern bool _sub_10891B70(s_tag_group const &, long);
extern "C" bool in_tag_group(s_tag_group const &group, long needle) // 0x10891B70
{
	// in_tag_group
	// long needle;
	todo("implement");
	bool __result = _sub_10891B70(group, needle);
	return __result;
}

_extern void _sub_10891C10(char const *);
extern "C" void log_error(char const *message) // 0x10891C10
{
	// log_error
	// static ...; // 0x10891CCC
	// static ...; // 0x10891CC0
	// static ...; // 0x10891CB8
	// char const *message;
	// char buff[8192];
	todo("implement");
	_sub_10891C10(message);
}

_extern void _sub_10891D10(char const *, ...);
extern "C" void log_errorf(char const *format, ...) // 0x10891D10
{
	// log_errorf
	// static ...; // 0x10891DB0
	// static ...; // 0x10891DA8
	// char const *format;
	// char buff[8192];
	// char *va;
	todo("implement");
	_sub_10891D10(format);
}

_extern bool _sub_10890EF0(s_blf_chunk_mapv_tag_names const *, s_map_variant *);
extern "C" bool fixup_map_variant_internal(s_blf_chunk_mapv_tag_names const *fixup_data, s_map_variant *map_variant) // 0x10890EF0
{
	// fixup_map_variant_internal
	// static ...; // 0x10891800
	// static ...; // 0x108917FD
	// static ...; // 0x108917F3
	// static ...; // 0x108917ED
	// static ...; // 0x108917E3
	// static ...; // 0x108917DA
	// static ...; // 0x108917C8
	// static ...; // 0x108917BC
	// static ...; // 0x108917AF
	// static ...; // 0x108917AC
	// static ...; // 0x10891728
	// static ...; // 0x10891720
	// s_blf_chunk_mapv_tag_names const *fixup_data;
	// s_map_variant *map_variant;
	// std::unordered_map<s_name_lookup_key,long,s_name_lookup_key::s_hasher,std::equal_to<s_name_lookup_key>,std::allocator<std::pair<s_name_lookup_key const ,long> > > runtime_tags_by_name;
	// std::shared_ptr<c_cache_file_tag_cache> base_cache;
	// IMod *mod;
	// bool succeeded;
	{
		// c_cache_file_tag_cache::c_instance_iterator it;
		{
			// long tag_index;
			// char const *name;
		}
	}
	{
		// long used_mod_tag_count;
		// std::shared_ptr<c_cache_file_tag_cache> mod_cache;
		// c_cache_file_tag_cache::c_instance_iterator iterator;
		// long cache_index;
		// std::shared_ptr<c_cache_file_interface> cache;
		// long tag_count;
		// c_mod_package *mod_package;
		// long counter;
		{
			// char const *mod_tag_name;
			// unsigned long mod_tag_group;
			// long runtime_tag_index;
			// long mod_tag_index;
		}
	}
	{
		// long i;
		{
			// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<s_name_lookup_key const ,long> > > > it;
			// char pe_tag_name[256];
			// char const *const pe_tag_path;
			// unsigned long pe_group_tag;
			// s_variant_quota &palette_entry;
		}
	}
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	// function call : bool () const
	// function call : __int32 ()
	// function call : void (*const)()
	// function call : std::shared_ptr<c_cache_file_interface> (bool) const
	// function call : std::shared_ptr<c_cache_file_tag_cache> () const
	todo("implement");
	bool __result = _sub_10890EF0(fixup_data, map_variant);
	return __result;
}
