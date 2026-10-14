/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/RefCounting.hpp"
#include "mods/blf_reader.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/map_variant_loader.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x10A87700

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
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
class IModListener;
class c_file_open_scope;
class c_file_reference;
class c_mod_package;
struct s_blf_campaign;
struct s_blf_chunk_header;
struct s_blf_map_information;
struct s_cache_file_header;
struct s_file_reference;
struct s_file_time;
struct s_find_file_data;
struct s_level_datum;
struct s_map_variant;
struct s_mod_package_map_file_entry;
namespace hades_file_local
{
	class ModListener;
	struct s_levels_enumerate_async_data;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Maps {}
	using namespace Patches::Maps;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class ModListener :
		public IModListener
	{
	public:
		virtual void OnModChanged(EModIndex, IMod *);
		ModListener(ModListener &); /* compiler_generated() */
		ModListener(ModListener const &); /* compiler_generated() */
		ModListener() = default; /* compiler_generated() */ // 0x10A875E0
		virtual ~ModListener() = default; /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	};
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");

	struct s_levels_enumerate_async_data
	{
		unsigned long state; // 0x0
		s_find_file_data *find_data; // 0x4
	};
	static_assert(sizeof(s_levels_enumerate_async_data) == 8, "Invalid s_levels_enumerate_async_data size");
}
using namespace hades_file_local;
/* ---------- prototypes */

extern bool (*const file_get_size)(s_file_reference *, unsigned long *);  // hades: added for 0x10A882F0
extern bool (*const file_open)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *);  // hades: added for 0x10A882F0
extern bool (*const file_read)(s_file_reference *, unsigned long, bool, void *);  // hades: added for 0x10A882F0
extern bool (*const file_close)(s_file_reference *);  // hades: added for 0x10A882F0
extern bool (*const cache_file_header_verify)(s_cache_file_header *, char const *, bool);  // hades: added for 0x10A882F0
bool blf_find_chunk_in_buffer(unsigned char const *buffer, unsigned long buffer_size, unsigned long chunk_type, s_blf_chunk_header *out_chunk_header, unsigned char const **out_chunk_data, unsigned long *out_chunk_size);  // hades: added for 0x10A882F0

extern void levels_close_multiplayer_map(long map_id);  // hades: added for 0x10A89060
extern void levels_close_campaign_map(long map_id);  // hades: added for 0x10A89060
extern void (*const levels_add_map_internal)(s_blf_map_information *, bool, char const *, bool);  // hades: added for 0x10A89060

extern bool (*const levels_add_campaign_internal)(s_blf_campaign *, bool, char const *, bool);  // hades: added for 0x10A88E60
void levels_close_all_campaigns();  // hades: added for 0x10A88E60

extern bool (*const levels_try_and_get_multiplayer_map)(long, s_level_datum *);  // hades: added for 0x10A893B0
__int32 ustrnicmp(wchar_t const *string1, wchar_t const *string2, long count);  // hades: added for 0x10A893B0

namespace Patches
{
	namespace Maps
	{
		extern void ApplyAll();
	}
}

bool verify_against_multiplayer_levels_hook(wchar_t const *name);
unsigned long levels_get_available_map_mask_hook();
void __fastcall c_map_variant_initialize_default_hook(s_map_variant *thisptr, void *unused, long mapId);
bool levels_add_map_impl(s_file_reference *file_reference, char const *maps_path);
bool load_mod_package_campaigns(char const *virtual_path, c_mod_package *mod_package);
bool load_mod_package_maps(char const *virtual_path, c_mod_package *mod_package, __int32 type_mask);
extern bool (*const find_files_next)(s_find_file_data *, s_file_reference *, s_file_time *);  // hades: added for 0x10A886A0
extern void (*const find_files_end)(s_find_file_data *);  // hades: added for 0x10A886A0
extern void (*const find_files_start)(s_find_file_data *, unsigned long, s_file_reference *);  // hades: added for 0x10A886A0
extern s_file_reference *(*const file_reference_create_from_path)(s_file_reference *, char const *, bool);  // hades: added for 0x10A886A0
extern char *(*const file_reference_get_name)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, char *, long);  // hades: added for 0x10A886A0
extern wchar_t *(*const file_reference_get_name_wide)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, wchar_t *, long);  // hades: added for 0x10A886A0
extern void (*const levels_add_map)(s_file_reference *, char *);  // hades: added for 0x10A886A0
extern bool (*const levels_add_campaign)(s_file_reference *, wchar_t *, bool);  // hades: added for 0x10A886A0
extern char const *(*const cache_files_map_directory)();  // hades: added for 0x10A886A0
long levels_enumerate_hook(s_levels_enumerate_async_data *data);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *const k_mods_mainmenu_virtual_path; // 0x111B0700
	extern char const *const k_mods_game_virtual_path; // 0x111B0704
	std::vector<unsigned char> map_file_buffer; // 0x12458E90
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Maps
	{
		void ApplyAll() // 0x10A87700
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Maps@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : void (IModListener *)

			Pointer(0x54AD9C).Write<unsigned int>(reinterpret_cast<unsigned int>(levels_enumerate_hook));
			Hook(0x6A81CF, c_map_variant_initialize_default_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6A7954, c_map_variant_initialize_default_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6A77CA, c_map_variant_initialize_default_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6A78A3, c_map_variant_initialize_default_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6A79D9, c_map_variant_initialize_default_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x14BCA0, { 0xB8, 0x40, 0x01, 0x00, 0x00, 0xC3 }).Apply();
			Patch(0x7004DF, { 0xEB }).Apply();
			c_mod_system::GetModManager().AddListener(new ModListener());
			Hook(0x1A8100, verify_against_multiplayer_levels_hook).Apply();
			Hook(0x14B610, levels_get_available_map_mask_hook).Apply();
			Pointer(0x54C19B).Write<unsigned char>(0x64);
		}
	}
}

/* ---------- private code */

_inline void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x10A88240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModChanged@ModListener@hades_file_local@@UAEXW4EModIndex@@PAVIMod@@@Z");
	// `anonymous-namespace'::ModListener::OnModChanged
	// IMod *mod;

	levels_clear_and_enumerate_async();
}

bool verify_against_multiplayer_levels_hook(wchar_t const *name) // 0x10A893B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?verify_against_multiplayer_levels_hook@@YA_NPB_W@Z");
	// `anonymous-namespace'::verify_against_multiplayer_levels_hook
	// static ...; // 0x10A894EC
	// static ...; // 0x10A894E4
	// static ...; // 0x10A894D8
	// static ...; // 0x10A894B4
	// static ...; // 0x10A894AC
	// wchar_t const *name;
	// long map_ids[100];
	// long map_id_count;
		// long i;
			// s_level_datum level_datum;
	// function call : long *(*const)(long *, long *)
	// function call : bool (*const)(long, s_level_datum *)

	static long *(*const levels_get_multiplayer_map_ids)(long *, long *) = reinterpret_cast<long *(*)(long *, long *)>(0x54BEE0);
	long map_id_count = 100;
	long map_ids[100];
	levels_get_multiplayer_map_ids(map_ids, &map_id_count);
	for (long i = 0; i < map_id_count; i++)
	{
		s_level_datum level_datum;
		if (levels_try_and_get_multiplayer_map(map_ids[i], &level_datum) && !ustrnicmp(level_datum.name, name, 32))
			return true;
	}
	return false;
}

unsigned long levels_get_available_map_mask_hook() // 0x10A88E40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_get_available_map_mask_hook@@YAKXZ");
	// `anonymous-namespace'::levels_get_available_map_mask_hook
	// procedure flags: nofpo

	return 0;
}

void __fastcall c_map_variant_initialize_default_hook(s_map_variant *thisptr, void *unused, long mapId) // 0x10A88290
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant_initialize_default_hook@@YIXPAUs_map_variant@@PAXJ@Z");
	// `anonymous-namespace'::c_map_variant_initialize_default_hook
	// long mapId;

	c_map_variant_loader::load_default(mapId, thisptr);
}

bool levels_add_map_impl(s_file_reference *file_reference, char const *maps_path) // 0x10A882F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_add_map_impl@@YA_NPAUs_file_reference@@PBD@Z");
	// `anonymous-namespace'::levels_add_map_impl
	// static ...; // 0x10A885C8
	// static ...; // 0x10A885BD
	// static ...; // 0x10A885B3
	// static ...; // 0x10A885A4
	// static ...; // 0x10A88568
	// static ...; // 0x10A88560
	// s_file_reference *file_reference;
	// char const *maps_path;
	// unsigned long last_error;
	// unsigned long map_blf_offset;
	// unsigned char *map_blf;
	// unsigned long map_blf_size;
	// bool success;
	// unsigned char const *levl_data;
	// s_blf_chunk_header mapv_chunk;
	// unsigned long levl_data_size;
	// unsigned long file_size;
		// s_blf_map_information *map_info;
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)
	// function call : bool (*const)(s_file_reference *)
	// function call : bool (*const)(s_cache_file_header *, char const *, bool)
	// function call : bool (*const)(s_file_reference *)
	// function call : void (*const)(s_blf_map_information *, bool, char const *, bool)
	// function call : bool (*const)(s_file_reference *)

	bool success = false;
	unsigned long last_error;
	unsigned long file_size;
	if (!file_get_size(file_reference, &file_size) || file_size < 0x3390)
		return false;
	if (!file_open(file_reference, 1, &last_error))
		return false;
	map_file_buffer.resize(file_size);
	if (!file_read(file_reference, map_file_buffer.size(), false, map_file_buffer.data()))
	{
		file_close(file_reference);
		return false;
	}
	if (!cache_file_header_verify((s_cache_file_header *)map_file_buffer.data(), maps_path, false))
	{
		file_close(file_reference);
		return false;
	}
	unsigned long map_blf_offset = 0x3390;
	unsigned char *map_blf = map_file_buffer.data() + map_blf_offset;
	unsigned long map_blf_size = map_file_buffer.size() - map_blf_offset;
	s_blf_chunk_header mapv_chunk;
	unsigned char const *levl_data;
	unsigned long levl_data_size;
	if (blf_find_chunk_in_buffer(map_blf, map_blf_size, 'levl', &mapv_chunk, &levl_data, &levl_data_size))
	{
		s_blf_map_information *map_info = (s_blf_map_information *)(levl_data - 12);
		levels_add_map_internal(map_info, false, maps_path, true);
		success = true;
	}
	file_close(file_reference);
	return success;
}

// mangled_x86(MANGLED_DEFAULT, "??0ModListener@hades_file_local@@QAE@XZ"); no body to assert in


bool load_mod_package_campaigns(char const *virtual_path, c_mod_package *mod_package) // 0x10A88E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_mod_package_campaigns@@YA_NPBDPAVc_mod_package@@@Z");
	// `anonymous-namespace'::load_mod_package_campaigns
	// static ...; // 0x10A88FEF
	// static ...; // 0x10A88FE6
	// static ...; // 0x10A88FDC
	// static ...; // 0x10A88FAC
	// static ...; // 0x10A88FA4
	// char const *virtual_path;
	// c_mod_package *mod_package;
	// bool byte_swap;
	// s_blf_campaign campaign;
	// c_mod_package *game_mod;
	// c_file_reference file;
	// c_file_open_scope scope;
	// function call : bool (*const)(s_blf_campaign *, bool, char const *, bool)

	c_mod_package *game_mod = mod_package;
	c_file_reference file = game_mod->get_file();
	c_file_open_scope scope(file, 1);
	s_blf_campaign campaign;
	bool byte_swap = false;
	if (game_mod->read_campaign(file, &campaign, &byte_swap))
	{
		levels_close_all_campaigns();
		levels_add_campaign_internal(&campaign, byte_swap, virtual_path, false);
	}
	return true;
}

bool load_mod_package_maps(char const *virtual_path, c_mod_package *mod_package, __int32 type_mask) // 0x10A89060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_mod_package_maps@@YA_NPBDPAVc_mod_package@@H@Z");
	// `anonymous-namespace'::load_mod_package_maps
	// static ...; // 0x10A892EC
	// static ...; // 0x10A892C8
	// static ...; // 0x10A892C0
	// char const *virtual_path;
	// c_mod_package *mod_package;
	// __int32 type_mask;
	// bool byte_swap;
	// long map_count;
	// c_mod_package *game_mod;
	// c_file_reference file;
	// c_file_open_scope scope;
		// __int32 i;
			// short map_type;
			// s_mod_package_map_file_entry const *entry;
			// static s_blf_map_information `load_mod_package_maps'::`4'::blf_map_information; // 0x12458EA0
			// static __int32 `load_mod_package_maps'::`4'::$TSS0; // 0x12462760
	// function call : void (*const)(s_blf_map_information *, bool, char const *, bool)

	c_mod_package *game_mod = mod_package;
	c_file_reference file = game_mod->get_file();
	c_file_open_scope scope(file, 1);
	bool byte_swap = false;
	long map_count = game_mod->get_map_count();
	for (__int32 i = 0; i < map_count; i++)
	{
		s_mod_package_map_file_entry const *entry = game_mod->get_map_file_entry(i);
		short map_type;
		if (!game_mod->read_section_data(file, (e_mod_package_sections)4, entry->offset + 0x13C, 2, &map_type))
			continue;
		if (!(type_mask & (1 << map_type)))
			continue;
		if (map_type == 1)
			levels_close_multiplayer_map(entry->map_id);
		if (map_type == 0)
			levels_close_campaign_map(entry->map_id);
		static s_blf_map_information blf_map_information;
		if (!game_mod->read_map_blf_map_information(file, i, &blf_map_information))
			continue;
		levels_add_map_internal(&blf_map_information, false, virtual_path, true);
	}
	return true;
}

long levels_enumerate_hook(s_levels_enumerate_async_data *data) // 0x10A886A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_enumerate_hook@@YAJPAUs_levels_enumerate_async_data@hades_file_local@@@Z");
	// `anonymous-namespace'::levels_enumerate_hook
	// static ...; // 0x10A88CA7
	// static ...; // 0x10A88C9D
	// static ...; // 0x10A88C93
	// static ...; // 0x10A88C84
	// static ...; // 0x10A88C80
	// static ...; // 0x10A88C7C
	// static ...; // 0x10A88C34
	// static ...; // 0x10A88C2C
	// s_levels_enumerate_async_data *data;
	// wchar_t extension[256];
	// char directory_ascii[256];
	// s_file_reference file_reference;
	// wchar_t directory[256];
		// Ref<IMod> mod;
			// c_mod_package *pak;
		// s_file_reference *maps_directory_file_reference;
	// function call : bool (*const)(s_find_file_data *, s_file_reference *, s_file_time *)
	// function call : void (*const)(s_find_file_data *)
	// function call : char *(*const)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, char *, long)
	// function call : wchar_t *(*const)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, wchar_t *, long)
	// function call : wchar_t *(*const)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, wchar_t *, long)
	// function call : void (*const)(s_file_reference *, char *)
	// function call : bool (*const)(s_file_reference *, wchar_t *, bool)
	// function call : Ref<IMod> (EModIndex) const
	// function call : bool () const
	// function call : c_mod_package *(bool) const
	// function call : Ref<IMod> (EModIndex) const
	// function call : bool () const
	// function call : c_mod_package *(bool) const
	// function call : char const *(*const)()
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : void (*const)(s_find_file_data *, unsigned long, s_file_reference *)

	char directory_ascii[256];
	wchar_t directory[256];
	wchar_t extension[256];
	s_file_reference file_reference;
	if (data->state)
	{
		if (data->state == 1)
		{
			if (!find_files_next(data->find_data, &file_reference, nullptr))
			{
				find_files_end(data->find_data);
				data->state++;
			}
			file_reference_get_name(&file_reference, 1, directory_ascii, 256);
			file_reference_get_name_wide(&file_reference, 1, directory, 256);
			file_reference_get_name_wide(&file_reference, 8, extension, 256);
			if (!wcscmp(extension, L"map"))
			{
				if (!levels_add_map_impl(&file_reference, directory_ascii))
					levels_add_map(&file_reference, directory_ascii);
			}
			else if (!wcscmp(extension, L"campaign"))
			{
				levels_add_campaign(&file_reference, directory, true);
			}
		}
		else if (data->state == 2)
		{
			{
				Ref<IMod> mod = c_mod_system::GetModManager().GetModShared(kGame);
				if (mod)
				{
					if (mod->GetPakIsLoading())
						return 0;
					c_mod_package *pak = mod->GetPak(false);
					if (pak)
					{
						load_mod_package_campaigns(k_mods_game_virtual_path, pak);
						load_mod_package_maps(k_mods_game_virtual_path, pak, 3);
					}
				}
			}
			{
				Ref<IMod> mod = c_mod_system::GetModManager().GetModShared(kMainMenu);
				if (mod)
				{
					if (mod->GetPakIsLoading())
						return 0;
					c_mod_package *pak = mod->GetPak(false);
					if (pak)
					{
						load_mod_package_maps(k_mods_mainmenu_virtual_path, pak, 4);
					}
				}
			}
			data->state = 3;
		}
	}
	else
	{
		s_file_reference *maps_directory_file_reference = file_reference_create_from_path(&file_reference, cache_files_map_directory(), true);
		find_files_start(data->find_data, 0, maps_directory_file_reference);
		data->state++;
	}
	return data->state == 3;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_flags<enum e_file_reference_flags,long>::c_flags(long const &);
