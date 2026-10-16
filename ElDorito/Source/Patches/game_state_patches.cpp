/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/controller.hpp"
#include "Blam/interface/player_profile.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "Utils/String.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x1091AE50

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
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_controller_interface;
class c_mod_package_manager;
class c_network_session;
class c_network_session_membership;
class c_player_profile_interface;
struct c_content_catalogue;
struct s_file_reference;
struct s_game_state_header;
struct s_network_session_peer;
struct s_network_session_player;
struct s_player_collection;
struct s_player_datum;

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

//struct ai_initialize_for_saved_game_hook::__l2::s_ai_mission_critical_actor
//{
//	long unit_index; // 0x0
//	long field_04; // 0x4
//	long field_08; // 0x8
//	long field_0C; // 0xC
//};
//static_assert(sizeof(ai_initialize_for_saved_game_hook::__l2::s_ai_mission_critical_actor) == 16, "Invalid ai_initialize_for_saved_game_hook::__l2::s_ai_mission_critical_actor size");

/* ---------- prototypes */

extern bool (*const network_session_interface_get_squad_session)(c_network_session **out_session);  // hades: added for 0x10919930

extern bool (*const file_delete)(s_file_reference *);  // hades: added for 0x10919010

extern bool (*const file_create)(s_file_reference *);  // hades: added for 0x109196E0
extern bool (*const file_create_parent_directories_if_not_present)(s_file_reference *);  // hades: added for 0x109196E0
extern bool (*const file_write)(s_file_reference *, unsigned long, void *);  // hades: added for 0x109196E0
extern bool (*const file_exists)(s_file_reference const *);  // hades: added for 0x109196E0

extern bool (*const file_close)(s_file_reference *);  // hades: added for 0x10919520
extern bool (*const file_open)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *);  // hades: added for 0x10919520
extern bool (*const file_read)(s_file_reference *, unsigned long, bool, void *);  // hades: added for 0x10919520

extern void game_state_patches_apply();

bool file_read_from_path(wchar_t const *path, unsigned long size, void *buffer);
bool file_write_to_path(wchar_t const *path, unsigned long size, void *buffer);
std::wstring get_save_location(wchar_t const *filename);
bool game_state_read_file_from_storage(long storage_index, long flags);
bool game_state_read_from_persistent_storage_blocking(long controller_index, void *buffer, unsigned long size);
void game_state_write_file_to_storage();
bool game_state_read_header_from_persistent_storage_blocking(long controller_index, void *buffer, unsigned long size);
void game_state_write_file_to_storage_blocking(void *header, unsigned long header_size, void *buffer, unsigned long buffer_size);
bool campaign_save_exists(__int32 __formal);
c_content_catalogue *content_catalogue_get_for_game_state_hook(long controller_index);
bool game_state_header_matches_current_network_session_settings_hook(s_game_state_header *header);
bool hash_verification(void *data, unsigned long size, bool a3, void *input_hash, void *output_hash);
void ai_initialize_for_saved_game_hook();
void fixup_player_identifier_for_saved_game(s_player_collection *player_collection);
void c_saved_games__delete_campaign_save_blocking(long controller_index);

/* ---------- globals */

extern s_file_reference *(*const file_reference_create_from_path_wide)(s_file_reference *, wchar_t const *, bool); // 0x112492EC  -- pointer global, called via `call dword ptr [ebp-0x210]` after `mov eax,[?file_reference_create_from_path_wide@@3Q6APAUs_file_reference@@PAU1@PB_W_N@ZA]`. It is declared ONLY in blamlib/source/Blam/tag_files/files.cpp:45 and is not visible from game_state_patches.cpp, so it must be added to that file's prototypes block. file_exists, tls_get, get_save_location, file_read_from_path and the k_* globals are all already reachable.

/* ---------- private variables */

namespace hades_file_local
{
	extern wchar_t const *const k_game_state_path; // 0x113533A0
	extern wchar_t const *const k_game_state_filename; // 0x113533A4
	extern wchar_t const *const k_game_state_header_filename; // 0x113533A8
	extern void **const global_game_state_data; // 0x11197A30
}
using namespace hades_file_local;
/* ---------- public code */

void game_state_patches_apply() // 0x10919BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_state_patches_apply@@YAXXZ");
	// procedure flags: nofpo

	Hook(0x25DB10, game_state_read_file_from_storage).Apply();
	Hook(0x25DBE0, game_state_write_file_to_storage).Apply();
	Hook(0x1265E0, game_state_read_from_persistent_storage_blocking).Apply();
	Hook(0x1266E0, game_state_read_header_from_persistent_storage_blocking).Apply();
	Hook(0x1270F0, game_state_write_file_to_storage_blocking).Apply();
	Hook(0x109020, hash_verification).Apply();
	Hook(0x1254A0, campaign_save_exists).Apply();
	Hook(0x7003E9, content_catalogue_get_for_game_state_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x110CB9, game_state_header_matches_current_network_session_settings_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x6CB1A, fixup_player_identifier_for_saved_game, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x125D20, c_saved_games__delete_campaign_save_blocking).Apply();
	Pointer(0x18A0E20).Write<unsigned long>(reinterpret_cast<unsigned long>(ai_initialize_for_saved_game_hook));
}

/* ---------- private code */

bool file_read_from_path(wchar_t const *path, unsigned long size, void *buffer) // 0x10919520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?file_read_from_path@@YA_NPB_WKPAX@Z");
	// `anonymous-namespace'::file_read_from_path
	// static ...; // 0x10919658
	// static ...; // 0x10919650
	// wchar_t const *path;
	// unsigned long size;
	// void *buffer;
	// s_file_reference file;
	// unsigned long file_error;
	// bool result;
	// function call : s_file_reference *(*const)(s_file_reference *, wchar_t const *, bool)
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, bool, void *)
	// function call : bool (*const)(s_file_reference *)

	s_file_reference file;
	file_reference_create_from_path_wide(&file, path, false);
	unsigned long file_error;
	if (!file_open(&file, 1, &file_error))
		return false;

	bool result = file_read(&file, size, false, buffer);
	file_close(&file);
	return result;
}

bool file_write_to_path(wchar_t const *path, unsigned long size, void *buffer) // 0x109196E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?file_write_to_path@@YA_NPB_WKPAX@Z");
	// `anonymous-namespace'::file_write_to_path
	// static ...; // 0x1091988C
	// static ...; // 0x10919884
	// wchar_t const *path;
	// unsigned long size;
	// void *buffer;
	// s_file_reference file;
	// unsigned long file_error;
	// bool result;
	// function call : s_file_reference *(*const)(s_file_reference *, wchar_t const *, bool)
	// function call : bool (*const)(s_file_reference *)
	// function call : bool (*const)(s_file_reference const *)
	// function call : bool (*const)(s_file_reference *)
	// function call : bool (*const)(s_file_reference *, c_flags<enum e_file_permission_flags,long>, unsigned long *)
	// function call : bool (*const)(s_file_reference *, unsigned long, void *)
	// function call : bool (*const)(s_file_reference *)

	s_file_reference file;
	file_reference_create_from_path_wide(&file, path, false);
	file_create_parent_directories_if_not_present(&file);
	if (!file_exists(&file))
		file_create(&file);

	unsigned long file_error;
	if (!file_open(&file, 2, &file_error))
		return false;

	bool result = file_write(&file, size, buffer);
	file_close(&file);
	return result;
}

std::wstring get_save_location(wchar_t const *filename) // 0x1091AE50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_save_location@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@PB_W@Z");
	// `anonymous-namespace'::get_save_location
	// static ...; // 0x1091B270
	// static ...; // 0x1091B268
	// static ...; // 0x1091B25C
	// static ...; // 0x1091B254
	// static ...; // 0x1091B248
	// static ...; // 0x1091B20C
	// static ...; // 0x1091B204
	// wchar_t const *filename;
	// bool hasModSet;
	// std::string modhash;
	// std::wstring combined;
	// c_mod_package_manager::s_entry mod_package;
		// std::string modName;
		// std::string mod_version;

	std::wstring combined;
	std::string modhash = c_mod_system::get_current_package_hash();
	c_mod_package_manager::s_entry mod_package;
	bool hasModSet = c_mod_system::get_mod_info_by_hash(modhash.c_str(), &mod_package);
	if (!hasModSet)
		combined = L"data\\game_saves\\default\\";
	else
	{
		std::string modName = Utils::String::ThinString(mod_package.name);
		std::string mod_version = std::to_string(mod_package.version_major) + "." + std::to_string(mod_package.version_minor);
		combined = k_game_state_path + Utils::String::WidenString(c_mod_system::GetNewPackageFilename(modName, modhash, mod_version));
	}
	combined += filename;
	return combined;
}

bool game_state_read_file_from_storage(long storage_index, long flags) // 0x1091A6B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_state_read_file_from_storage@@YA_NJJ@Z");
	// `anonymous-namespace'::game_state_read_file_from_storage
	// long flags;
	// bool result;
	// function call : __int32 (*const)(char)
	// function call : __int32 (*const)()
	// function call : __int32 (*const)(__int32)

	bool result = false;
	if (*(bool *)0x2497CD0)
	{
		((__int32 (__cdecl *)(char))0x58A5F0)(flags);
		result = file_read_from_path(get_save_location(k_game_state_filename).c_str(), *(unsigned long *)0x2497CDC, *global_game_state_data);
		((__int32 (__cdecl *)())0x50F280)();
		((__int32 (__cdecl *)(__int32))0x58A4B0)(flags);
	}
	return result;
}

bool game_state_read_from_persistent_storage_blocking(long controller_index, void *buffer, unsigned long size) // 0x1091A850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_state_read_from_persistent_storage_blocking@@YA_NJPAXK@Z");
	// `anonymous-namespace'::game_state_read_from_persistent_storage_blocking
	// unsigned long size;

	return file_read_from_path(get_save_location(k_game_state_filename).c_str(), size, buffer);
}

void game_state_write_file_to_storage() // 0x1091AA70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_state_write_file_to_storage@@YAXXZ");
	// `anonymous-namespace'::game_state_write_file_to_storage
	// procedure flags: nofpo
	// bool result;
	// void *header;
	// function call : bool (*const)(void *)

	bool result = false;
	if (*(bool *)0x2497CD0)
		result = file_write_to_path(get_save_location(k_game_state_filename).c_str(), *(unsigned long *)0x2497CDC, *global_game_state_data);

	void *header = *(void **)0x238DB18;
	if (((bool (__cdecl *)(void *))0x50FCF0)(header))
		file_write_to_path(get_save_location(k_game_state_header_filename).c_str(), 0x24CD0, header);
	*(bool *)0x2497CE0 = result;
}

bool game_state_read_header_from_persistent_storage_blocking(long controller_index, void *buffer, unsigned long size) // 0x1091A960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_state_read_header_from_persistent_storage_blocking@@YA_NJPAXK@Z");
	// `anonymous-namespace'::game_state_read_header_from_persistent_storage_blocking
	// unsigned long size;

	return file_read_from_path(get_save_location(k_game_state_header_filename).c_str(), size, buffer);
}

void game_state_write_file_to_storage_blocking(void *header, unsigned long header_size, void *buffer, unsigned long buffer_size) // 0x1091AC70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_state_write_file_to_storage_blocking@@YAXPAXK0K@Z");
	// `anonymous-namespace'::game_state_write_file_to_storage_blocking
	// unsigned long buffer_size;
	// c_player_profile_interface *profile_interface;
	// c_controller_interface *controller_interface;
	// function call : bool (*const)(void *)
	// function call : c_controller_interface *(*const)(long)

	if (!reinterpret_cast<bool (*)(void *)>(0x50FCF0)(header))
		return;
	file_write_to_path(get_save_location(k_game_state_header_filename).c_str(), header_size, header);
	file_write_to_path(get_save_location(k_game_state_filename).c_str(), buffer_size, buffer);
	c_controller_interface *controller_interface = reinterpret_cast<c_controller_interface *(*)(long)>(0xA7CD50)(0);
	c_player_profile_interface *profile_interface = controller_interface->get_player_profile_interface();
	profile_interface->set_last_campaign_played_time(0, _time64(nullptr), true);
}

bool campaign_save_exists(__int32 __formal) // 0x109192C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?campaign_save_exists@@YA_NH@Z");
	// `anonymous-namespace'::campaign_save_exists
	// static ...; // 0x10919400
	// static ...; // 0x109193F4
	// static ...; // 0x109193EC
	// __int32 __formal;
	// s_file_reference file;
	// function call : s_file_reference *(*const)(s_file_reference *, wchar_t const *, bool)
	// function call : bool (*const)(s_file_reference const *)

	s_file_reference file;
	file_reference_create_from_path_wide(&file, get_save_location(k_game_state_filename).c_str(), false);

	if (!file_exists(&file))
	{
		return false;
	}

	return true;
}

c_content_catalogue *content_catalogue_get_for_game_state_hook(long controller_index) // 0x10919460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?content_catalogue_get_for_game_state_hook@@YAPAUc_content_catalogue@@J@Z");
	// `anonymous-namespace'::content_catalogue_get_for_game_state_hook
	// long controller_index;
	// c_content_catalogue *catalogue;
	// c_content_catalogue *(*const content_catalog_get)(long);
	// function call : c_content_catalogue *(*const)(long)

	c_content_catalogue *(__cdecl *const content_catalogue_get)(long) = (c_content_catalogue *(__cdecl *const)(long))0x5a5600;

	c_content_catalogue *catalogue = content_catalogue_get(controller_index);
	if (campaign_save_exists(0))
	{
		*(unsigned long *)offset_pointer(catalogue, 680) |= 2;
	}
	return catalogue;
}

bool game_state_header_matches_current_network_session_settings_hook(s_game_state_header *header) // 0x10919B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_state_header_matches_current_network_session_settings_hook@@YA_NPAUs_game_state_header@@@Z");
	// `anonymous-namespace'::game_state_header_matches_current_network_session_settings_hook
	// s_game_state_header *header;
	// bool (*const game_state_header_matches_current_network_session_settings)(s_game_state_header *);
	// function call : bool (*const)(s_game_state_header *)

	bool (*const game_state_header_matches_current_network_session_settings)(s_game_state_header *header) = (bool (*const)(s_game_state_header *header))0x50FAA0;

	if (!game_state_header_matches_current_network_session_settings(header))
		return false;

	return true;
}

bool hash_verification(void *data, unsigned long size, bool a3, void *input_hash, void *output_hash) // 0x1091B390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hash_verification@@YA_NPAXK_N00@Z");
	// `anonymous-namespace'::hash_verification
	// void *output_hash;

	return true;
}

void ai_initialize_for_saved_game_hook() // 0x10918EE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ai_initialize_for_saved_game_hook@@YAXXZ");
	// `anonymous-namespace'::ai_initialize_for_saved_game_hook
	// procedure flags: nofpo
	// void (*const ai_globals_initialize_for_new_map)();
	// void (*const ai_initialize_for_saved_game)();
	// ai_initialize_for_saved_game_hook::__l2::s_ai_mission_critical_actor *actor;
		// long i;
	// function call : void (*const)()

	struct s_ai_mission_critical_actor
	{
		long unit_index;
		long field_04;
		long field_08;
		long field_0C;
	};

	void (__cdecl *const ai_globals_initialize_for_new_map)() = (void (__cdecl *const)())0x1434150;
	void (__cdecl *const ai_initialize_for_saved_game)() = (void (__cdecl *const)())0x1431F90;

	ai_globals_initialize_for_new_map();

	s_ai_mission_critical_actor *actor = (s_ai_mission_critical_actor *)(*(long *)tls_get(0x528) + 1028);
	for (long i = 0; i < 8; i++)
	{
		actor[i].unit_index = -1;
	}
}

void fixup_player_identifier_for_saved_game(s_player_collection *player_collection) // 0x10919930
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?fixup_player_identifier_for_saved_game@@YAXPAUs_player_collection@@@Z");
	// `anonymous-namespace'::fixup_player_identifier_for_saved_game
	// static ...; // 0x10919AF3
	// static ...; // 0x10919AF0
	// static ...; // 0x10919AD8
	// static ...; // 0x10919AD0
	// s_player_collection *player_collection;
	// void (*const simulation_player_collection_clear)(s_player_collection *);
	// c_network_session *session;
		// c_network_session_membership *membership;
		// long network_player_index;
		// c_data_array<s_player_datum> *players;
			// s_network_session_peer *peer;
			// s_network_session_player *network_player;
				// c_data_iterator<s_player_datum> it;
	// function call : bool (*const)(c_network_session **)
	// function call : void (*const)(s_player_collection *)

	void (*const simulation_player_collection_clear)(s_player_collection *) = reinterpret_cast<void (*)(s_player_collection *)>(0x4A7E50);
	c_network_session *session;
	if (network_session_interface_get_squad_session(&session) && session->established())
	{
		c_data_array<s_player_datum> *players = players_get();
		c_network_session_membership *membership = session->get_session_membership();
		long network_player_index = membership->find_first_player();
		while (network_player_index != -1)
		{
			s_network_session_player *network_player = membership->get_player(network_player_index);
			s_network_session_peer *peer = membership->get_peer(network_player->peer_index);
			for (c_data_iterator<s_player_datum> it = players->begin(); it != players->end(); ++it)
			{
				if (it->flags & 2)
					continue;
				if (!memcmp(&it->machine_identifier, &peer->secure_address, 16))
					it->player_identifier = network_player->player_identifier;
			}
			network_player_index = membership->find_next_player(network_player_index);
		}
	}
	simulation_player_collection_clear(player_collection);
}

void c_saved_games__delete_campaign_save_blocking(long controller_index) // 0x10919010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_saved_games__delete_campaign_save_blocking@@YAXJ@Z");
	// `anonymous-namespace'::c_saved_games__delete_campaign_save_blocking
	// static ...; // 0x10919230
	// static ...; // 0x10919224
	// static ...; // 0x1091921C
	// long controller_index;
	// s_file_reference file;
	// function call : s_file_reference *(*const)(s_file_reference *, wchar_t const *, bool)
	// function call : bool (*const)(s_file_reference const *)
	// function call : bool (*const)(s_file_reference *)
	// function call : s_file_reference *(*const)(s_file_reference *, wchar_t const *, bool)
	// function call : bool (*const)(s_file_reference const *)
	// function call : bool (*const)(s_file_reference *)

	s_file_reference file;
	file_reference_create_from_path_wide(&file, get_save_location(k_game_state_header_filename).c_str(), false);
	if (file_exists(&file))
		file_delete(&file);
	file_reference_create_from_path_wide(&file, get_save_location(k_game_state_filename).c_str(), false);
	if (file_exists(&file))
		file_delete(&file);
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { void **const global_game_state_data = reinterpret_cast<void **>(0x2497CD4); }
namespace hades_file_local { wchar_t const *const k_game_state_path = L"data\\game_saves\\"; }
namespace hades_file_local { wchar_t const *const k_game_state_filename = L"\\mmiof.bmf"; }
namespace hades_file_local { wchar_t const *const k_game_state_header_filename = L"\\gamestate.hdr"; }
