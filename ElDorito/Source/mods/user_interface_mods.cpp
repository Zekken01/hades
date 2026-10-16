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
#include "mods/mod_system.hpp"  // hades: added for 0x108C2730
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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const user_interface_session_get_map = reinterpret_cast<bool (*)(long *, long *)>(0xA817B0);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool c_user_interface_mods_player_character_data::build_from_mod_globals(s_mod_globals_definition *mod_globals) // 0x108C2480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_from_mod_globals@c_user_interface_mods_player_character_data@@AAE_NPAUs_mod_globals_definition@@@Z");
	// s_mod_globals_definition *mod_globals;
		// long i;
			// s_mod_globals_player_character_set *character_set;
				// long j;
					// s_mod_globals_player_character *character;

	if (!mod_globals)
		return false;
	player_character_set_count = 0;
	player_characters_count = 0;
	for (long i = 0; i < mod_globals->player_character_sets.count && i < k_maximum_set_count; i++)
	{
		s_mod_globals_player_character_set *character_set = &mod_globals->player_character_sets[i];
		player_character_sets[player_character_set_count].name = character_set->name;
		csstrnzcpy(player_character_sets[player_character_set_count++].display_name.ascii, character_set->display_name.ascii, 0x20);
		for (long j = 0; j < character_set->characters.count && j < k_maximum_character_count; j++)
		{
			s_mod_globals_player_character *character = &character_set->characters[j];
			player_characters[player_characters_count].character_set_index = i;
			player_characters[player_characters_count].name = character->name;
			csstrnzcpy(player_characters[player_characters_count++].display_name.ascii, character->display_name.ascii, 0x20);
		}
	}
	return true;
}

bool c_user_interface_mods_player_character_data::build_from_cache() // 0x108C2420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_from_cache@c_user_interface_mods_player_character_data@@AAE_NXZ");
	// c_user_interface_mods_player_character_data *const this;
	// s_game_globals *game_globals;

	s_game_globals *game_globals = game_globals_get();

	return build_from_mod_globals(mod_globals_get_definition());
}

bool c_user_interface_mods_player_character_data::build_from_mod_package() // 0x108C2730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_from_mod_package@c_user_interface_mods_player_character_data@@AAE_NXZ");
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
	// std::unique_ptr<unsigned char> tag_memory;
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
		// long i;
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	// function call : bool (*const)(long *, long *)
	// function call : std::shared_ptr<c_cache_file_interface> (bool) const
	// function call : std::shared_ptr<c_cache_file_tag_cache> () const

	IMod *mod = c_mod_system::GetModManager().GetMod(kGame);
	if (!mod)
		return false;
	c_mod_package *mod_package = mod->GetPak(true);
	if (!mod_package)
		return false;
	long campaign_id;
	long map_id;
	if (!eldorado::user_interface_session_get_map(&campaign_id, &map_id))
		return false;
	long cache_index = mod_package->get_tag_cache_index_for_map_id(map_id);
	if (cache_index == -1)
		return false;
	std::shared_ptr<c_cache_file_interface> mod_cache = mod->GetCache(true);
	if (!mod_cache)
		return false;
	std::shared_ptr<c_cache_file_tag_cache> tag_cache = mod_cache->get_tag_cache();
	if (!tag_cache)
		return false;
	long modg_tag_index = tag_cache->find_by_name('modg', "multiplayer\\mod_globals");
	if (modg_tag_index == -1)
		return false;
	s_cache_tag_instance const *header = tag_cache->get_instance(modg_tag_index);
	if (!header)
		return false;
	if (header->definition_offset == header->size)
		return false;
	c_file_reference file = tag_cache->get_file();
	std::unique_ptr<unsigned char> tag_memory(new unsigned char[header->size]);
	if (!tag_cache->read_tag_data(&file, modg_tag_index, 0, header->size, tag_memory.get()))
		return false;
	s_cache_tag_instance *tag_instance = (s_cache_tag_instance *)tag_memory.get();
	s_mod_globals_definition *definition = (s_mod_globals_definition *)&tag_memory.get()[header->definition_offset];
	unsigned long *fixups = (unsigned long *)&tag_instance[1] + tag_instance->dependency_count;
	for (long i = 0; i < tag_instance->fixup_count; i++)
		*(unsigned long *)((char *)tag_instance + fixups[i] - 0x40000000) = (unsigned long)((char *)tag_instance + *(unsigned long *)((char *)tag_instance + fixups[i] - 0x40000000) - 0x40000000);
	if (!build_from_mod_globals(definition))
		return false;
	return true;
}

void c_user_interface_mods_player_character_data::update() // 0x108C2F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update@c_user_interface_mods_player_character_data@@QAEXXZ");
	// c_user_interface_mods_player_character_data *const this;

	if (build_from_mod_package())
	{
	}
	else
	{
		build_from_cache();
	}
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
