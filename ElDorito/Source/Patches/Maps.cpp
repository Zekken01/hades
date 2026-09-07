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
		ModListener(); /* compiler_generated() */
		virtual ~ModListener(); /* compiler_generated() */
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

namespace Patches
{
	namespace Maps
	{
		extern void ApplyAll();
	}
}

bool verify_against_multiplayer_levels_hook(wchar_t const *name);
unsigned long levels_get_available_map_mask_hook();
void c_map_variant_initialize_default_hook(s_map_variant *thisptr, void *unused, long mapId);
bool levels_add_map_impl(s_file_reference *file_reference, char const *maps_path);
bool load_mod_package_campaigns(char const *virtual_path, c_mod_package *mod_package);
bool load_mod_package_maps(char const *virtual_path, c_mod_package *mod_package, __int32 type_mask);
long levels_enumerate_hook(s_levels_enumerate_async_data *data);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *const k_mods_mainmenu_virtual_path; // 0x111B0700
	extern char const *const k_mods_game_virtual_path; // 0x111B0704
	extern std::vector<unsigned char,std::allocator<unsigned char> > map_file_buffer; // 0x12458E90
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Maps
	{
		_extern void _sub_10A87700();
		void ApplyAll() // 0x10A87700
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Maps@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : void (IModListener *)
			todo("implement");
			_sub_10A87700();
		}
	}
}

/* ---------- private code */

_extern void _sub_10A88240(ModListener *const, EModIndex, IMod *);
_inline void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x10A88240
{
	// `anonymous-namespace'::ModListener::OnModChanged
	// IMod *mod;
	todo("implement");
	_sub_10A88240(this, index, mod);
}

_extern bool _sub_10A893B0(wchar_t const *);
bool verify_against_multiplayer_levels_hook(wchar_t const *name) // 0x10A893B0
{
	// `anonymous-namespace'::verify_against_multiplayer_levels_hook
	// static ...; // 0x10A894EC
	// static ...; // 0x10A894E4
	// static ...; // 0x10A894D8
	// static ...; // 0x10A894B4
	// static ...; // 0x10A894AC
	// wchar_t const *name;
	// long map_ids[100];
	// long map_id_count;
	{
		// long i;
		{
			// s_level_datum level_datum;
		}
	}
	// function call : long *(*const)(long *, long *)
	// function call : bool (*const)(long, s_level_datum *)
	todo("implement");
	bool __result = _sub_10A893B0(name);
	return __result;
}

_extern unsigned long _sub_10A88E40();
unsigned long levels_get_available_map_mask_hook() // 0x10A88E40
{
	// `anonymous-namespace'::levels_get_available_map_mask_hook
	// procedure flags: nofpo
	todo("implement");
	unsigned long __result = _sub_10A88E40();
	return __result;
}

_extern void _sub_10A88290(s_map_variant *, void *, long);
void c_map_variant_initialize_default_hook(s_map_variant *thisptr, void *unused, long mapId) // 0x10A88290
{
	// `anonymous-namespace'::c_map_variant_initialize_default_hook
	// long mapId;
	todo("implement");
	_sub_10A88290(thisptr, unused, mapId);
}

_extern bool _sub_10A882F0(s_file_reference *, char const *);
bool levels_add_map_impl(s_file_reference *file_reference, char const *maps_path) // 0x10A882F0
{
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
	{
		// s_blf_map_information *map_info;
	}
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)
	// function call : bool (*const)(s_file_reference *)
	// function call : bool (*const)(s_cache_file_header *, char const *, bool)
	// function call : bool (*const)(s_file_reference *)
	// function call : void (*const)(s_blf_map_information *, bool, char const *, bool)
	// function call : bool (*const)(s_file_reference *)
	todo("implement");
	bool __result = _sub_10A882F0(file_reference, maps_path);
	return __result;
}

extern ModListener* _sub_10A875E0(ModListener *const);
_inline ModListener::ModListener() // 0x10A875E0
{
	// `anonymous-namespace'::ModListener::ModListener
	// ModListener *const this;
	compiler_generated();
	todo("implement");
	_sub_10A875E0(this);
}

_extern void _sub_10A87640(ModListener *const);
_inline ModListener::~ModListener() // 0x10A87640
{
	// `anonymous-namespace'::ModListener::~ModListener
	// ModListener *const this;
	compiler_generated();
	todo("implement");
	_sub_10A87640(this);
}

_extern bool _sub_10A88E60(char const *, c_mod_package *);
bool load_mod_package_campaigns(char const *virtual_path, c_mod_package *mod_package) // 0x10A88E60
{
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
	todo("implement");
	bool __result = _sub_10A88E60(virtual_path, mod_package);
	return __result;
}

_extern bool _sub_10A89060(char const *, c_mod_package *, __int32);
bool load_mod_package_maps(char const *virtual_path, c_mod_package *mod_package, __int32 type_mask) // 0x10A89060
{
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
	{
		// __int32 i;
		{
			// short map_type;
			// s_mod_package_map_file_entry const *entry;
			// static s_blf_map_information `load_mod_package_maps'::`4'::blf_map_information; // 0x12458EA0
			// static __int32 `load_mod_package_maps'::`4'::$TSS0; // 0x12462760
		}
	}
	// function call : void (*const)(s_blf_map_information *, bool, char const *, bool)
	todo("implement");
	bool __result = _sub_10A89060(virtual_path, mod_package, type_mask);
	return __result;
}

_extern long _sub_10A886A0(s_levels_enumerate_async_data *);
long levels_enumerate_hook(s_levels_enumerate_async_data *data) // 0x10A886A0
{
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
	{
		// Ref<IMod> mod;
		{
			// c_mod_package *pak;
		}
	}
	{
		{
		}
	}
	{
		// s_file_reference *maps_directory_file_reference;
	}
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
	todo("implement");
	long __result = _sub_10A886A0(data);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_flags<enum e_file_reference_flags,long>::c_flags(long const &);
