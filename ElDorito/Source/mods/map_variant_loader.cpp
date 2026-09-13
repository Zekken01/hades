/* ---------- headers */

#include "mods/map_variant_loader.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/blf_reader.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Utils/Singleton.hpp"

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
class c_network_session;
struct c_map_variant_loader;
struct s_blf_chunk_header;
struct s_file_reference;
struct s_level_datum;
struct s_map_variant;
namespace hades_file_local
{
	class ModListener;
}
using namespace hades_file_local;

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
		virtual ~ModListener() = default; /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	};
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");
}
using namespace hades_file_local;
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::string stored_blf; // 0x123B8A40
	extern e_map_variant_load_error last_error; // 0x123B8A5C
}
using namespace hades_file_local;
/* ---------- public code */

_extern void _sub_1088AB10();
void c_map_variant_loader::initialzie() // 0x1088AB10
{
	mangled_x86(MANGLED_TODO, "?initialzie@c_map_variant_loader@@SAXXZ");
	// procedure flags: nofpo
	// function call : void (IModListener *)
	todo("implement");
	_sub_1088AB10();
}

void c_map_variant_loader::update() // 0x1088BB60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update@c_map_variant_loader@@SAXXZ");
	// procedure flags: nofpo
}

_extern bool _sub_1088B4B0(long, unsigned char const *, s_map_variant *);
bool c_map_variant_loader::load_from_buffer(long blf_size, unsigned char const *blf, s_map_variant *out_map_variant) // 0x1088B4B0
{
	mangled_x86(MANGLED_TODO, "?load_from_buffer@c_map_variant_loader@@SA_NJPBEPAUs_map_variant@@@Z");
	// static ...; // 0x1088B62A
	// static ...; // 0x1088B624
	// static ...; // 0x1088B5F4
	// static ...; // 0x1088B5EC
	// long blf_size;
	// unsigned char const *blf;
	// s_map_variant *out_map_variant;
	// unsigned char const *mapv_data;
	// s_blf_chunk_header mapv_chunk;
	// s_level_datum level;
	// unsigned long mapv_data_size;
	// function call : bool (*const)(long, s_level_datum *)
	todo("implement");
	bool __result = _sub_1088B4B0(blf_size, blf, out_map_variant);
	return __result;
}

_extern bool _sub_1088B6C0(char const *, s_map_variant *);
bool c_map_variant_loader::load_from_file(char const *filename, s_map_variant *out_map_variant) // 0x1088B6C0
{
	mangled_x86(MANGLED_TODO, "?load_from_file@c_map_variant_loader@@SA_NPBDPAUs_map_variant@@@Z");
	// static ...; // 0x1088B9F9
	// static ...; // 0x1088B9EF
	// static ...; // 0x1088B9EA
	// static ...; // 0x1088B9E4
	// static ...; // 0x1088B9A8
	// static ...; // 0x1088B9A0
	// char const *filename;
	// s_map_variant *out_map_variant;
	// char logmessage[4096];
	// std::string buffer;
	// c_file_reference file;
	// unsigned long file_size;
	// c_file_open_scope scope;
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	todo("implement");
	bool __result = _sub_1088B6C0(filename, out_map_variant);
	return __result;
}

_extern bool _sub_1088AC90(long, s_map_variant *);
bool c_map_variant_loader::load_default(long map_id, s_map_variant *out_map_variant) // 0x1088AC90
{
	mangled_x86(MANGLED_TODO, "?load_default@c_map_variant_loader@@SA_NJPAUs_map_variant@@@Z");
	// static ...; // 0x1088B2F5
	// static ...; // 0x1088B2E7
	// static ...; // 0x1088B2E2
	// static ...; // 0x1088B2CF
	// static ...; // 0x1088B2C1
	// static ...; // 0x1088B2BD
	// static ...; // 0x1088B2B8
	// static ...; // 0x1088B2AD
	// static ...; // 0x1088B2A3
	// static ...; // 0x1088B294
	// static ...; // 0x1088B210
	// static ...; // 0x1088B208
	// long map_id;
	// s_map_variant *out_map_variant;
	// std::string map_file_buffer;
	// unsigned long map_blf_offset;
	// unsigned char *map_blf;
	// unsigned long map_blf_size;
	// unsigned char const *mapv_data;
	// char file_path[256];
	// s_blf_chunk_header mapv_chunk;
	// unsigned long mapv_data_size;
	{
		// unsigned long map_file_size;
		// long map_file_index;
		// c_file_reference file;
		// IMod *mod;
		// c_mod_package *mod_package;
	}
	{
		// unsigned long err;
		// s_static_string<256> file_path_with_ext;
	}
	{
		// void (*const c_map_variant__initialize)(s_map_variant *, long);
	}
	// function call : void (*const)(unsigned long, unsigned long, char *, __int32)
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	// function call : bool (*const)(s_file_reference *, unsigned long *)
	// function call : void (*const)(s_map_variant *, long)
	todo("implement");
	bool __result = _sub_1088AC90(map_id, out_map_variant);
	return __result;
}

e_map_variant_load_error c_map_variant_loader::get_last_error() // 0x1088AAF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_last_error@c_map_variant_loader@@SA?AW4e_map_variant_load_error@@XZ");
	// procedure flags: nofpo

	return last_error;
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??0ModListener@hades_file_local@@QAE@XZ"); no body to assert in
_inline ModListener::ModListener() = default; // 0x1088A2D0


_extern void _sub_1088A3F0(ModListener *const, EModIndex, IMod *);
void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x1088A3F0
{
	// `anonymous-namespace'::ModListener::OnModChanged
	// static ...; // 0x1088A5CC
	// static ...; // 0x1088A5C4
	// ModListener *const this;
	// EModIndex index;
	// IMod *mod;
	// void (*const global_preferences_set_last_game_setup)(void *);
	// s_map_variant map_variant;
	// void *(*const global_preferences_get_last_game_setup)();
	// c_network_session *session;
	// static unsigned char `ModListener::OnModChanged'::`2'::game_setup[269176]; // 0x123B8A60
	// function call : void *(*const)()
	// function call : void (*const)(void *)
	// function call : bool (*const)(c_network_session **)
	// function call : bool (*const)(s_map_variant *)
	todo("implement");
	_sub_1088A3F0(this, index, mod);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_flags<enum e_file_permission_flags,long>::c_flags(c_flags<enum e_file_permission_flags,long> const &);
template char const * s_static_string<256>::append(char const *);
template long s_static_string<256>::length();
