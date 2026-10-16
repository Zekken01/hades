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

#include "mods/mod_system.hpp"  // hades: added for 0x1088AB10

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
	namespace hades_file_local_map_variant_loader { class ModListener; } using namespace hades_file_local_map_variant_loader;
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
	namespace hades_file_local_map_variant_loader { class ModListener :
		public IModListener
	{
	public:
		virtual void OnModChanged(EModIndex, IMod *);
		ModListener(ModListener &); /* compiler_generated() */
		ModListener(ModListener const &); /* compiler_generated() */
		ModListener() = default; /* compiler_generated() */ // 0x1088A2D0
		virtual ~ModListener() = default; /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	}; }  // hades_file_local_map_variant_loader: ModListener is a different class in each translation unit
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");
}
using namespace hades_file_local;
/* ---------- prototypes */

extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x1088A3F0

#include "Utils/Logger.hpp"  // hades: added for 0x1088B6C0
extern bool (*const file_get_size)(s_file_reference *, unsigned long *);  // hades: added for 0x1088B6C0

#include "mods/map_variant_tag_fixups.hpp"  // hades: added for 0x1088B4B0
extern bool (*const levels_try_and_get_multiplayer_map)(long, s_level_datum *);  // hades: added for 0x1088B4B0

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::string stored_blf; // 0x123B8A40
	extern e_map_variant_load_error last_error; // 0x123B8A5C
}
using namespace hades_file_local;
/* ---------- public code */

void c_map_variant_loader::initialzie() // 0x1088AB10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialzie@c_map_variant_loader@@SAXXZ");

	c_mod_system::GetModManager().AddListener(new ModListener());
}

void c_map_variant_loader::update() // 0x1088BB60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update@c_map_variant_loader@@SAXXZ");
}

bool c_map_variant_loader::load_from_buffer(long blf_size, unsigned char const *blf, s_map_variant *out_map_variant) // 0x1088B4B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_from_buffer@c_map_variant_loader@@SA_NJPBEPAUs_map_variant@@@Z");

	last_error = (e_map_variant_load_error)0;
	s_blf_chunk_header mapv_chunk;
	unsigned char const *mapv_data;
	unsigned long mapv_data_size;
	if (!blf_find_chunk_in_buffer(blf, blf_size, 0x6D617076, &mapv_chunk, &mapv_data, &mapv_data_size))
	{
		last_error = (e_map_variant_load_error)2;
		return false;
	}

	memcpy(out_map_variant, &mapv_data[4], 0xE090);
	s_level_datum level;
	if (!levels_try_and_get_multiplayer_map(out_map_variant->map_id, &level))
	{
		last_error = (e_map_variant_load_error)3;
		return false;
	}

	if (!c_map_variant_tag_fixups::fixup_map_variant_in_memory((unsigned char *)blf, blf_size, out_map_variant))
	{
		last_error = (e_map_variant_load_error)4;
		return false;
	}

	stored_blf.assign(blf, blf + blf_size);
	return true;
}

bool c_map_variant_loader::load_from_file(char const *filename, s_map_variant *out_map_variant) // 0x1088B6C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_from_file@c_map_variant_loader@@SA_NPBDPAUs_map_variant@@@Z");

	char logmessage[4096];
	sprintf_s(logmessage, "Loading map variant '%s'...", filename);
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Info, logmessage);
	std::string buffer;
	unsigned long file_size;
	c_file_reference file(filename);
	c_file_open_scope scope(file, 1);
	if (!file.is_open())
		return false;
	if (!file_get_size(&file, &file_size))
		return false;
	buffer.resize(file_size);
	if (!file.read(buffer.size(), false, buffer.data()))
		return false;
	return load_from_buffer(buffer.size(), (unsigned char const *)buffer.data(), out_map_variant);
}

bool c_map_variant_loader::load_default(long map_id, s_map_variant *out_map_variant) // 0x1088AC90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_default@c_map_variant_loader@@SA_NJPAUs_map_variant@@@Z");

	extern void (*const levels_get_map_name)(unsigned long, unsigned long, char *, int);
	char file_path[256];
	levels_get_map_name(0xFFFFFFFF, map_id, file_path, 256);
	std::string map_file_buffer;
	if (strstr(file_path, "mods\\") == file_path)
	{
		IMod *mod = c_mod_system::GetModManager().GetMod((EModIndex)0);
		if (!mod)
			return false;
		c_mod_package *mod_package = mod->GetPak(true);
		unsigned long map_file_size;
		long map_file_index = mod_package->find_map_file_by_map_id(map_id, &map_file_size);
		if (map_file_index == -1)
			return false;
		if (map_file_size <= 0x3390)
			return false;
		map_file_buffer.resize(map_file_size);
		c_file_reference file = mod_package->get_file();
		if (!mod_package->read_map_file_into_buffer(file, map_file_index, map_file_buffer.size(), &map_file_buffer[0]))
			return false;
	}
	else
	{
		s_static_string<256> file_path_with_ext;
		file_path_with_ext.set(file_path);
		file_path_with_ext.append(".map");
		unsigned long map_file_size;
		unsigned long err;
		c_file_reference file(file_path_with_ext.get_string());
		if (!file.open(1, &err))
			return false;
		if (!file_get_size(&file, &map_file_size))
			return false;
		map_file_buffer.resize(map_file_size);
		if (!file.read(map_file_buffer.size(), false, &map_file_buffer[0]))
			return false;
	}
	if (map_file_buffer.size() <= 0x3390)
		return false;
	unsigned long map_blf_offset = 0x3390;
	unsigned char *map_blf = (unsigned char *)&map_file_buffer[map_blf_offset];
	unsigned long map_blf_size = map_file_buffer.size() - map_blf_offset;
	s_blf_chunk_header mapv_chunk;
	unsigned char const *mapv_data;
	unsigned long mapv_data_size;
	if (!blf_find_chunk_in_buffer(map_blf, map_blf_size, 'mapv', &mapv_chunk, &mapv_data, &mapv_data_size))
	{
		void (__thiscall *const c_map_variant__initialize)(s_map_variant *, long) = reinterpret_cast<void (__thiscall *)(s_map_variant *, long)>(0x581F70);
		c_map_variant__initialize(out_map_variant, map_id);
		return true;
	}
	return load_from_buffer(map_blf_size, map_blf, out_map_variant);
}

e_map_variant_load_error c_map_variant_loader::get_last_error() // 0x1088AAF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_last_error@c_map_variant_loader@@SA?AW4e_map_variant_load_error@@XZ");

	return last_error;
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??0ModListener@hades_file_local@@QAE@XZ"); no body to assert in


void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x1088A3F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModChanged@ModListener@hades_file_local@@UAEXW4EModIndex@@PAVIMod@@@Z");

	if (stored_blf.size() < 1)
		return;
	void *(*const global_preferences_get_last_game_setup)() = reinterpret_cast<void *(*)()>(0x50B560);
	void (*const global_preferences_set_last_game_setup)(void *) = reinterpret_cast<void (*)(void *)>(0x50D8E0);
	static unsigned char game_setup[0x41B78];
	memcpy(game_setup, global_preferences_get_last_game_setup(), sizeof(game_setup));
	game_setup[0x338] = 0;
	game_setup[0xEA50] = 0;
	global_preferences_set_last_game_setup(game_setup);
	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session))
	{
		stored_blf.clear();
		return;
	}
	s_map_variant map_variant;
	if (!c_map_variant_loader::load_from_buffer(stored_blf.size(), (unsigned char const *)stored_blf.data(), &map_variant))
		c_map_variant_loader::load_default(0x140, &map_variant);
	reinterpret_cast<bool (*)(s_map_variant *)>(0xA83AB0)(&map_variant);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_flags<enum e_file_permission_flags,long>::c_flags(c_flags<enum e_file_permission_flags,long> const &);
template char const * s_static_string<256>::append(char const *);
template long s_static_string<256>::length();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { std::string stored_blf; }
namespace hades_file_local { e_map_variant_load_error last_error; }
