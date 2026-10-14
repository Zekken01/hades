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
#include "mods/cache_file_tags.hpp"  // hades: added for 0x10890EF0
#include "mods/mod_system.hpp"  // hades: added for 0x10890EF0
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

// hades: moved from hades/recovered_types.h, where its member types were not visible
struct s_mod_loading_state
{
	s_file_reference file; // 0x0
	std::shared_ptr<c_cache_file_tag_cache> mod_tag_cache; // 0x110  // hades: was unsigned char[8]
public:
	s_mod_loading_state();
	~s_mod_loading_state();
};
static_assert32(sizeof(s_mod_loading_state) == 280, "Invalid s_mod_loading_state size");

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
	std::string_view name; // 0x4
	// s_name_lookup_key(); /* compiler_generated() */  // hades: implicit, so the key is an aggregate (0x10890EF0)
};
#pragma pack(pop)
static_assert(sizeof(s_name_lookup_key) == 12, "Invalid s_name_lookup_key size");

/* ---------- prototypes */

extern bool (*const file_get_size)(s_file_reference *, unsigned long *);  // hades: added for 0x10890AD0
extern bool (*const file_open)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *);  // hades: added for 0x10890AD0
extern bool (*const file_read)(s_file_reference *, unsigned long, bool, void *);  // hades: added for 0x10890AD0
extern bool (*const file_close)(s_file_reference *);  // hades: added for 0x10890AD0

namespace Utils { namespace stl { namespace detail { template<typename t_arg0> void hash_combine(unsigned __int32 &seed, t_arg0 val) { seed ^= std::hash<t_arg0>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2); } } template<typename... t_args> unsigned __int32 hash_combine(t_args... args) { unsigned __int32 seed = 0; (detail::hash_combine(seed, args), ...); return seed; } } }  // hades: added for 0x1088EF80; 0x1088D740

extern _inline bool operator==(s_name_lookup_key const &lhs, s_name_lookup_key const &rhs);

static bool in_tag_group(s_tag_group const &group, long needle);
static void log_error(char const *message);
static void log_errorf(char const *format, ...); extern bool parse_tag_file_name(char const *path, char *out_tag_name, unsigned long *out_group_tag);  // hades: added for 0x10890EF0
static bool fixup_map_variant_internal(s_blf_chunk_mapv_tag_names const *fixup_data, s_map_variant *map_variant);

/* ---------- globals */

extern s_mod_loading_state g_mod_loading_state; // 0x12407830

/* ---------- private variables */

/* ---------- public code */

_inline bool operator==(s_name_lookup_key const &lhs, s_name_lookup_key const &rhs) // 0x1088EA80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??8@YA_NABUs_name_lookup_key@@0@Z");
	// s_name_lookup_key const &rhs;

	return lhs.group_tag == rhs.group_tag && lhs.name == rhs.name;
}

_inline unsigned __int32 s_name_lookup_key::s_hasher::operator()(s_name_lookup_key const &k) const // 0x1088EF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??Rs_hasher@s_name_lookup_key@@QBEIABU1@@Z");
	// s_name_lookup_key const &k;

	return Utils::stl::hash_combine<unsigned int, std::string_view>(k.group_tag, k.name);
}

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_loading_state@@QAE@XZ"); no body to assert in
_inline s_mod_loading_state::s_mod_loading_state() = default; // 0x1088E290

// mangled_x86(MANGLED_DEFAULT, "??1s_mod_loading_state@@QAE@XZ"); no body to assert in
_inline s_mod_loading_state::~s_mod_loading_state() = default; // 0x1088E8D0

bool c_map_variant_tag_fixups::fixup_map_variant_in_memory(unsigned char *buffer, unsigned long buffer_size, s_map_variant *map_variant) // 0x10890DD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup_map_variant_in_memory@c_map_variant_tag_fixups@@SA_NPAEKPAUs_map_variant@@@Z");
	// static ...; // 0x10890E94
	// static ...; // 0x10890E70
	// static ...; // 0x10890E68
	// unsigned char *buffer;
	// unsigned long buffer_size;
	// s_map_variant *map_variant;
	// s_blf_chunk_header chunk_header;
	// unsigned char const *data;
	// unsigned long data_size;

	s_blf_chunk_header chunk_header;
	unsigned char const *data;
	unsigned long data_size;
	if (!blf_find_chunk_in_buffer(buffer, buffer_size, 0x7461676E, &chunk_header, &data, &data_size))
	{
		return false;
	}
	return fixup_map_variant_internal((s_blf_chunk_mapv_tag_names const *)&data[-(long)sizeof(s_blf_chunk_header)], map_variant);
}

bool c_map_variant_tag_fixups::fixup_map_variant_from_file(s_file_reference *file, s_map_variant *map_variant) // 0x10890AD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup_map_variant_from_file@c_map_variant_tag_fixups@@SA_NPAUs_file_reference@@PAUs_map_variant@@@Z");
	// static ...; // 0x10890D1C
	// static ...; // 0x10890D18
	// static ...; // 0x10890CF4
	// static ...; // 0x10890CEC
	// s_file_reference *file;
	// s_map_variant *map_variant;
	// std::string file_buff;
	// unsigned long err;
	// bool result;
	// unsigned long file_size;
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)
	// function call : bool (*const)(s_file_reference *)

	std::string file_buff;
	unsigned long file_size;
	if (!file_get_size(file, &file_size))
		return false;

	file_buff.resize(file_size);
	unsigned long err;
	if (!file_open(file, 1, &err))
		return false;

	bool result = false;
	if (file_read(file, file_buff.size(), false, &file_buff[0]))
		result = fixup_map_variant_in_memory((unsigned char *)&file_buff[0], file_buff.size(), map_variant);
	file_close(file);
	return result;
}

void c_map_variant_tag_fixups::initialize() // 0x10891BF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_map_variant_tag_fixups@@SAXXZ");
	// procedure flags: nofpo
}

/* ---------- private code */

static bool in_tag_group(s_tag_group const &group, long needle) // 0x10891B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?in_tag_group@@YA_NABUs_tag_group@@J@Z");
	// in_tag_group
	// long needle;

	return group.tags[0] == needle || group.tags[1] == needle || group.tags[2] == needle;
}

static void log_error(char const *message) // 0x10891C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?log_error@@YAXPBD@Z");
	// log_error
	// static ...; // 0x10891CCC
	// static ...; // 0x10891CC0
	// static ...; // 0x10891CB8
	// char const *message;
	// char buff[8192];

	char buff[0x2000];
	sprintf_s(buff, "[ERROR]: c_map_variant_loader :: %s", message);
	Utils::Singleton<Utils::Logger>::Instance().Log((Utils::LogTypes)1, (Utils::LogLevel)4, buff);
}

static void log_errorf(char const *format, ...) // 0x10891D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?log_errorf@@YAXPBDZZ");
	// log_errorf
	// static ...; // 0x10891DB0
	// static ...; // 0x10891DA8
	// char const *format;
	// char buff[8192];
	// char *va;

	char buff[8192];
	va_list va;
	va_start(va, format);
	vsprintf_s(buff, format, va);
	va_end(va);
	log_error(buff);
}

bool fixup_map_variant_internal(s_blf_chunk_mapv_tag_names const *fixup_data, s_map_variant *map_variant) // 0x10890EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup_map_variant_internal@@YA_NPBUs_blf_chunk_mapv_tag_names@@PAUs_map_variant@@@Z");
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
	// std::unordered_map<s_name_lookup_key,long,s_name_lookup_key::s_hasher> runtime_tags_by_name;
	// std::shared_ptr<c_cache_file_tag_cache> base_cache;
	// IMod *mod;
	// bool succeeded;
		// c_cache_file_tag_cache::c_instance_iterator it;
			// long tag_index;
			// char const *name;
		// long used_mod_tag_count;
		// std::shared_ptr<c_cache_file_tag_cache> mod_cache;
		// c_cache_file_tag_cache::c_instance_iterator iterator;
		// long cache_index;
		// std::shared_ptr<c_cache_file_interface> cache;
		// long tag_count;
		// c_mod_package *mod_package;
		// long counter;
			// char const *mod_tag_name;
			// unsigned long mod_tag_group;
			// long runtime_tag_index;
			// long mod_tag_index;
		// long i;
			// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<s_name_lookup_key const ,long> > > > it;
			// char pe_tag_name[256];
			// char const *const pe_tag_path;
			// unsigned long pe_group_tag;
			// s_variant_quota &palette_entry;
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	// function call : bool () const
	// function call : __int32 ()
	// function call : void (*const)()
	// function call : std::shared_ptr<c_cache_file_interface> (bool) const
	// function call : std::shared_ptr<c_cache_file_tag_cache> () const

	std::shared_ptr<c_cache_file_tag_cache> base_cache = c_cache_file_tags::get_open_cache();
	if (base_cache == nullptr)
		return false;
	std::unordered_map<s_name_lookup_key, long, s_name_lookup_key::s_hasher> runtime_tags_by_name;
	for (c_cache_file_tag_cache::c_instance_iterator it = base_cache->create_iterator('obje'); it.next();)
	{
		long tag_index = it.tag_index;
		if (!base_cache->valid_tag(tag_index))
			continue;
		char const *name = base_cache->get_tag_name(tag_index);
		if (!name)
			continue;
		runtime_tags_by_name.emplace(s_name_lookup_key{ it.group.tags[0], name }, tag_index);
	}
	IMod *mod = c_mod_system::GetModManager().GetMod(kGame);
	if (mod)
	{
		c_mod_package *mod_package = mod->GetPak(true);
		if (!mod_package)
			return false;
		long cache_index = mod_package->get_tag_cache_index_for_map_id(map_variant->map_id);
		if (cache_index == -1)
		{
			log_errorf("Mod package tag cache not found for map id: %d", map_variant->map_id);
			return false;
		}
		while (mod->GetCacheIsLoading())
		{
			SwitchToThread();
			((void (*const)())0x5063A0)();
		}
		std::shared_ptr<c_cache_file_interface> cache = mod->GetCache(true);
		if (!cache)
		{
			log_errorf("Failed to open mod package tag cache");
			return false;
		}
		std::shared_ptr<c_cache_file_tag_cache> mod_cache = cache->get_tag_cache();
		long tag_count = base_cache->get_tag_count();
		long counter = base_cache->get_tag_count();
		c_cache_file_tag_cache::c_instance_iterator iterator = mod_cache->create_iterator(0xFFFFFFFF);
		long used_mod_tag_count = 0;
		while (iterator.next())
		{
			if (iterator.instance->definition_offset == iterator.instance->size)
				continue;
			if (in_tag_group(iterator.group, 'obje'))
			{
				long mod_tag_index = iterator.tag_index;
				unsigned long mod_tag_group = iterator.instance->group.tags[0];
				char const *mod_tag_name = mod_cache->get_tag_name(mod_tag_index);
	#line 370 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\map_variant_tag_fixups.cpp"
					assert(mod_tag_name);
	#line 405 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\map_variant_tag_fixups.cpp"
				long runtime_tag_index = -1;
				if (runtime_tag_index == -1)
				{
				runtime_tag_index = 0xFFFF - used_mod_tag_count - 1;
				if (runtime_tag_index <= base_cache->get_tag_count())
					return false;
				runtime_tags_by_name.emplace(s_name_lookup_key{ mod_tag_group, mod_tag_name }, runtime_tag_index);
				}
			}
			used_mod_tag_count++;
		}
	}
	bool succeeded = true;
	for (long i = 0; i < 256; i++)
	{
		s_variant_quota &palette_entry = map_variant->object_quotas[i];
		if (palette_entry.definition_index == -1)
			continue;
		char const *const pe_tag_path = fixup_data->names[i];
		if (!pe_tag_path[0])
			continue;
		char pe_tag_name[256];
		unsigned long pe_group_tag;
		if (!parse_tag_file_name(pe_tag_path, pe_tag_name, &pe_group_tag))
		{
			log_errorf("Invalid tag name: '%s'", pe_tag_path);
			succeeded = false;
			continue;
		}
		long runtime_tag_index = -1;
		auto it = runtime_tags_by_name.find(s_name_lookup_key{ pe_group_tag, pe_tag_name });
		if (it != runtime_tags_by_name.end())
			runtime_tag_index = it->second;
		if (runtime_tag_index == -1)
		{
			log_errorf("Missing tag '%s'", pe_tag_path);
			succeeded = false;
			continue;
		}
		if (runtime_tag_index != palette_entry.definition_index)
			palette_entry.definition_index = runtime_tag_index;
	}
	return succeeded;
}
