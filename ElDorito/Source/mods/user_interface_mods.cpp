/* ---------- headers */

#include "mods/user_interface_mods.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/cache_file_interface.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

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
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
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
class c_file_reference;
class c_mod_package;
class c_user_interface_mods_player_character_data;
struct c_cache_file_interface;
struct s_cache_tag_instance;
struct s_game_globals;
struct s_mod_globals_definition;
struct s_mod_globals_player_character;
struct s_mod_globals_player_character_set;

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

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern bool _sub_108C2480(c_user_interface_mods_player_character_data *const, s_mod_globals_definition *);
bool c_user_interface_mods_player_character_data::build_from_mod_globals(s_mod_globals_definition *mod_globals) // 0x108C2480
{
	mangled_x86(MANGLED_TODO, "?build_from_mod_globals@c_user_interface_mods_player_character_data@@AAE_NPAUs_mod_globals_definition@@@Z");
	// s_mod_globals_definition *mod_globals;
	{
		// long i;
		{
			// s_mod_globals_player_character_set *character_set;
			{
				// long j;
				{
					// s_mod_globals_player_character *character;
				}
			}
		}
	}
	todo("implement");
	bool __result = _sub_108C2480(this, mod_globals);
	return __result;
}

_extern bool _sub_108C2420(c_user_interface_mods_player_character_data *const);
bool c_user_interface_mods_player_character_data::build_from_cache() // 0x108C2420
{
	mangled_x86(MANGLED_TODO, "?build_from_cache@c_user_interface_mods_player_character_data@@AAE_NXZ");
	// c_user_interface_mods_player_character_data *const this;
	// s_game_globals *game_globals;
	todo("implement");
	bool __result = _sub_108C2420(this);
	return __result;
}

_extern bool _sub_108C2730(c_user_interface_mods_player_character_data *const);
bool c_user_interface_mods_player_character_data::build_from_mod_package() // 0x108C2730
{
	mangled_x86(MANGLED_TODO, "?build_from_mod_package@c_user_interface_mods_player_character_data@@AAE_NXZ");
	// static ...; // 0x108C2D23
	// static ...; // 0x108C2D1C
	// static ...; // 0x108C2D12
	// static ...; // 0x108C2D08
	// static ...; // 0x108C2D03
	// static ...; // 0x108C2CF8
	// static ...; // 0x108C2CB0
	// static ...; // 0x108C2CA8
	// c_user_interface_mods_player_character_data *const this;
	// std::shared_ptr<c_cache_file_tag_cache> tag_cache;
	// long map_id;
	// long modg_tag_index;
	// std::unique_ptr<unsigned char,std::default_delete<unsigned char> > tag_memory;
	// std::shared_ptr<c_cache_file_interface> mod_cache;
	// c_file_reference file;
	// IMod *mod;
	// long campaign_id;
	// long cache_index;
	// c_mod_package *mod_package;
	// s_cache_tag_instance const *header;
	// s_mod_globals_definition *definition;
	// s_cache_tag_instance *tag_instance;
	// unsigned long *fixups;
	{
		// long i;
	}
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	// function call : bool (*const)(long *, long *)
	// function call : std::shared_ptr<c_cache_file_interface> (bool) const
	// function call : std::shared_ptr<c_cache_file_tag_cache> () const
	todo("implement");
	bool __result = _sub_108C2730(this);
	return __result;
}

_extern void _sub_108C2F60(c_user_interface_mods_player_character_data *const);
void c_user_interface_mods_player_character_data::update() // 0x108C2F60
{
	mangled_x86(MANGLED_TODO, "?update@c_user_interface_mods_player_character_data@@QAEXXZ");
	// c_user_interface_mods_player_character_data *const this;
	todo("implement");
	_sub_108C2F60(this);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<c_user_interface_mods_player_character_data::s_player_character,128>::valid(__int32);
template bool s_static_array<c_user_interface_mods_player_character_data::s_player_character_set,8>::valid(__int32);
template c_user_interface_mods_player_character_data::s_player_character & s_static_array<c_user_interface_mods_player_character_data::s_player_character,128>::operator[](long);
template c_user_interface_mods_player_character_data::s_player_character_set & s_static_array<c_user_interface_mods_player_character_data::s_player_character_set,8>::operator[](long);
template s_mod_globals_player_character & c_tag_block<s_mod_globals_player_character>::operator[](__int32);
