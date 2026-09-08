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

extern void game_state_patches_apply();

bool file_read_from_path(wchar_t const *path, unsigned long size, void *buffer);
bool file_write_to_path(wchar_t const *path, unsigned long size, void *buffer);
std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > get_save_location(wchar_t const *filename);
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

/* ---------- private variables */

namespace hades_file_local
{
	extern wchar_t const *k_game_state_path; // 0x113533A0
	extern wchar_t const *k_game_state_filename; // 0x113533A4
	extern wchar_t const *k_game_state_header_filename; // 0x113533A8
	extern void **const global_game_state_data; // 0x11197A30
}
using namespace hades_file_local;
/* ---------- public code */

_extern void _sub_10919BE0();
void game_state_patches_apply() // 0x10919BE0
{
	mangled_x86(MANGLED_TODO, "?game_state_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10919BE0();
}

/* ---------- private code */

_extern bool _sub_10919520(wchar_t const *, unsigned long, void *);
bool file_read_from_path(wchar_t const *path, unsigned long size, void *buffer) // 0x10919520
{
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
	todo("implement");
	bool __result = _sub_10919520(path, size, buffer);
	return __result;
}

_extern bool _sub_109196E0(wchar_t const *, unsigned long, void *);
bool file_write_to_path(wchar_t const *path, unsigned long size, void *buffer) // 0x109196E0
{
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
	todo("implement");
	bool __result = _sub_109196E0(path, size, buffer);
	return __result;
}

extern std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > _sub_1091AE50(wchar_t const *);
std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > get_save_location(wchar_t const *filename) // 0x1091AE50
{
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
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > modhash;
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > combined;
	// c_mod_package_manager::s_entry mod_package;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > modName;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mod_version;
	}
	todo("implement");
	std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > __result = _sub_1091AE50(filename);
	return __result;
}

_extern bool _sub_1091A6B0(long, long);
bool game_state_read_file_from_storage(long storage_index, long flags) // 0x1091A6B0
{
	// `anonymous-namespace'::game_state_read_file_from_storage
	// long flags;
	// bool result;
	// function call : __int32 (*const)(char)
	// function call : __int32 (*const)()
	// function call : __int32 (*const)(__int32)
	todo("implement");
	bool __result = _sub_1091A6B0(storage_index, flags);
	return __result;
}

_extern bool _sub_1091A850(long, void *, unsigned long);
bool game_state_read_from_persistent_storage_blocking(long controller_index, void *buffer, unsigned long size) // 0x1091A850
{
	// `anonymous-namespace'::game_state_read_from_persistent_storage_blocking
	// unsigned long size;
	todo("implement");
	bool __result = _sub_1091A850(controller_index, buffer, size);
	return __result;
}

_extern void _sub_1091AA70();
void game_state_write_file_to_storage() // 0x1091AA70
{
	// `anonymous-namespace'::game_state_write_file_to_storage
	// procedure flags: nofpo
	// bool result;
	// void *header;
	// function call : bool (*const)(void *)
	todo("implement");
	_sub_1091AA70();
}

_extern bool _sub_1091A960(long, void *, unsigned long);
bool game_state_read_header_from_persistent_storage_blocking(long controller_index, void *buffer, unsigned long size) // 0x1091A960
{
	// `anonymous-namespace'::game_state_read_header_from_persistent_storage_blocking
	// unsigned long size;
	todo("implement");
	bool __result = _sub_1091A960(controller_index, buffer, size);
	return __result;
}

_extern void _sub_1091AC70(void *, unsigned long, void *, unsigned long);
void game_state_write_file_to_storage_blocking(void *header, unsigned long header_size, void *buffer, unsigned long buffer_size) // 0x1091AC70
{
	// `anonymous-namespace'::game_state_write_file_to_storage_blocking
	// unsigned long buffer_size;
	// c_player_profile_interface *profile_interface;
	// c_controller_interface *controller_interface;
	// function call : bool (*const)(void *)
	// function call : c_controller_interface *(*const)(long)
	todo("implement");
	_sub_1091AC70(header, header_size, buffer, buffer_size);
}

_extern bool _sub_109192C0(__int32);
bool campaign_save_exists(__int32 __formal) // 0x109192C0
{
	// `anonymous-namespace'::campaign_save_exists
	// static ...; // 0x10919400
	// static ...; // 0x109193F4
	// static ...; // 0x109193EC
	// __int32 __formal;
	// s_file_reference file;
	// function call : s_file_reference *(*const)(s_file_reference *, wchar_t const *, bool)
	// function call : bool (*const)(s_file_reference const *)
	todo("implement");
	bool __result = _sub_109192C0(__formal);
	return __result;
}

extern c_content_catalogue *_sub_10919460(long);
c_content_catalogue *content_catalogue_get_for_game_state_hook(long controller_index) // 0x10919460
{
	// `anonymous-namespace'::content_catalogue_get_for_game_state_hook
	// long controller_index;
	// c_content_catalogue *catalogue;
	// c_content_catalogue *(*const content_catalog_get)(long);
	// function call : c_content_catalogue *(*const)(long)
	todo("implement");
	c_content_catalogue * __result = _sub_10919460(controller_index);
	return __result;
}

_extern bool _sub_10919B70(s_game_state_header *);
bool game_state_header_matches_current_network_session_settings_hook(s_game_state_header *header) // 0x10919B70
{
	// `anonymous-namespace'::game_state_header_matches_current_network_session_settings_hook
	// s_game_state_header *header;
	// bool (*const game_state_header_matches_current_network_session_settings)(s_game_state_header *);
	// function call : bool (*const)(s_game_state_header *)
	todo("implement");
	bool __result = _sub_10919B70(header);
	return __result;
}

bool hash_verification(void *data, unsigned long size, bool a3, void *input_hash, void *output_hash) // 0x1091B390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hash_verification@@YA_NPAXK_N00@Z");
	// `anonymous-namespace'::hash_verification
	// void *output_hash;

	return true;
}

_extern void _sub_10918EE0();
void ai_initialize_for_saved_game_hook() // 0x10918EE0
{
	// `anonymous-namespace'::ai_initialize_for_saved_game_hook
	// procedure flags: nofpo
	// void (*const ai_globals_initialize_for_new_map)();
	// void (*const ai_initialize_for_saved_game)();
	// ai_initialize_for_saved_game_hook::__l2::s_ai_mission_critical_actor *actor;
	{
		// long i;
	}
	// function call : void (*const)()
	todo("implement");
	_sub_10918EE0();
}

_extern void _sub_10919930(s_player_collection *);
void fixup_player_identifier_for_saved_game(s_player_collection *player_collection) // 0x10919930
{
	// `anonymous-namespace'::fixup_player_identifier_for_saved_game
	// static ...; // 0x10919AF3
	// static ...; // 0x10919AF0
	// static ...; // 0x10919AD8
	// static ...; // 0x10919AD0
	// s_player_collection *player_collection;
	// void (*const simulation_player_collection_clear)(s_player_collection *);
	// c_network_session *session;
	{
		// c_network_session_membership *membership;
		// long network_player_index;
		// c_data_array<s_player_datum> *players;
		{
			// s_network_session_peer *peer;
			// s_network_session_player *network_player;
			{
				// c_data_iterator<s_player_datum> it;
			}
		}
	}
	// function call : bool (*const)(c_network_session **)
	// function call : void (*const)(s_player_collection *)
	todo("implement");
	_sub_10919930(player_collection);
}

_extern void _sub_10919010(long);
void c_saved_games__delete_campaign_save_blocking(long controller_index) // 0x10919010
{
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
	todo("implement");
	_sub_10919010(controller_index);
}
