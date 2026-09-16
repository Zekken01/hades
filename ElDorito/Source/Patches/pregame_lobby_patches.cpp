/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/gui/gui_pregame_setup_manager.hpp"
#include "Blam/interface/gui/gui_selected_items.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
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
#include "CommandMap.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
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
#include <optional>
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

class IMod;
class IModListener;
class c_mod_package_manager;
class c_network_session;
struct c_gui_game_variant_selected_item;
struct c_gui_level_selected_item;
struct c_gui_map_selected_item;
struct c_gui_pregame_setup_manager;
class c_gui_selected_item;
struct s_level_datum;
namespace hades_file_local
{
	class ModListener;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PregameLobby {}
	using namespace Patches::PregameLobby;
}

namespace PersistentMemory {}
using namespace ::PersistentMemory;
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
	private:
		virtual void OnModChanged(EModIndex, IMod *);
	public:
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

#include "mods/mod_system.hpp"  // hades: added for 0x107BC140

namespace Patches
{
	namespace PregameLobby
	{
		extern void ApplyAll();
		extern void Tick();
	}
}

void LoadDefaultModPackageAsync(std::string const &id);
void __fastcall c_gui_pregame_setup_manager__initialize_game_mode_hook(c_gui_pregame_setup_manager *thisptr, void *unused, long ui_game_mode, long a3);
void __fastcall c_gui_pregame_setup_manager__handle_item_chosen_hook(c_gui_pregame_setup_manager *thisptr, void *__formal, long controller_index, c_gui_selected_item *item, char arg8, long screen_index);
void __fastcall c_gui_pregame_setup_manager__update_hook(c_gui_pregame_setup_manager *thisptr);
void notify_mod_package_opened_or_closed(EModIndex index);
void notify_lobby_changed();
void lobby_update();
void clear_mod_cached_map_files();

/* ---------- globals */

extern bool (*const network_session_interface_get_squad_session)(c_network_session **); // 0x11248780

/* ---------- private variables */

namespace hades_file_local
{
	extern bool levels_dirty; // 0x1138DEDB
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace PregameLobby
	{
		_extern void _sub_107BBC90();
		void ApplyAll() // 0x107BBC90
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@PregameLobby@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : void (IModListener *)
			todo("implement");
			_sub_107BBC90();
		}

		void Tick() // 0x107BC1F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@PregameLobby@Patches@@YAXXZ");
			// procedure flags: nofpo

			lobby_update();
		}
	}
}

/* ---------- private code */

void LoadDefaultModPackageAsync(std::string const &id) // 0x107BC140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadDefaultModPackageAsync@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::LoadDefaultModPackageAsync
	// std::string const &id;

	c_mod_system::load_package_by_identifier(id.c_str());
}

_extern void _sub_107BCE00(c_gui_pregame_setup_manager *, void *, long, long);
void __fastcall c_gui_pregame_setup_manager__initialize_game_mode_hook(c_gui_pregame_setup_manager *thisptr, void *unused, long ui_game_mode, long a3) // 0x107BCE00
{
	// `anonymous-namespace'::c_gui_pregame_setup_manager__initialize_game_mode_hook
	// static ...; // 0x107BD935
	// static ...; // 0x107BD928
	// static ...; // 0x107BD917
	// static ...; // 0x107BD90F
	// static ...; // 0x107BD901
	// static ...; // 0x107BD8EC
	// static ...; // 0x107BD8DF
	// static ...; // 0x107BD8CC
	// static ...; // 0x107BD8C4
	// static ...; // 0x107BD8B6
	// static ...; // 0x107BD8A1
	// static ...; // 0x107BD894
	// static ...; // 0x107BD7E0
	// static ...; // 0x107BD7D8
	// c_gui_pregame_setup_manager *thisptr;
	// void *unused;
	// long ui_game_mode;
	// long a3;
	{
		// std::string CampaignPakName;
		// std::string lastMod;
		{
			// c_mod_package_manager::s_entry defaultSetMod;
			{
				// c_mod_package_manager::s_entry currentLoadedPackage;
			}
		}
		{
			// c_mod_package_manager::s_entry packageEntry;
		}
	}
	{
		// std::string FireFightPakName;
		{
			{
			}
		}
		{
		}
	}
	{
		// std::string MultiplayerPakName;
		{
			{
			}
		}
		{
		}
	}
	// function call : void (*)(c_gui_pregame_setup_manager *, long, long)
	todo("implement");
	_sub_107BCE00(thisptr, unused, ui_game_mode, a3);
}

_extern void _sub_107BC3F0(c_gui_pregame_setup_manager *, void *, long, c_gui_selected_item *, char, long);
void __fastcall c_gui_pregame_setup_manager__handle_item_chosen_hook(c_gui_pregame_setup_manager *thisptr, void *__formal, long controller_index, c_gui_selected_item *item, char arg8, long screen_index) // 0x107BC3F0
{
	// `anonymous-namespace'::c_gui_pregame_setup_manager__handle_item_chosen_hook
	// static ...; // 0x107BCBC2
	// static ...; // 0x107BCBBE
	// static ...; // 0x107BCBB7
	// static ...; // 0x107BCBA8
	// static ...; // 0x107BCB9A
	// static ...; // 0x107BCB90
	// static ...; // 0x107BCB8C
	// static ...; // 0x107BCB84
	// static ...; // 0x107BCAE8
	// static ...; // 0x107BCAE0
	// c_gui_pregame_setup_manager *thisptr;
	// void *__formal;
	// long controller_index;
	// c_gui_selected_item *item;
	// char arg8;
	// long screen_index;
	// void (*const c_gui_pregame_setup_manager__handle_item_chosen)(c_gui_pregame_setup_manager *, long, c_gui_selected_item *, char, long);
	{
		// __int32 mapID;
		{
			// c_gui_level_selected_item *selectedItem;
		}
		{
			// c_gui_game_variant_selected_item *selectedItem;
			// bool valid;
			{
				// char *const path;
				// std::filesystem::path dir;
				{
					// std::string parent;
				}
			}
			{
				// wchar_t *const gameType;
				// std::wstring GameTypeWString;
				// std::string gameTypeString;
			}
		}
		{
			// c_gui_map_selected_item *selectedItem;
			{
				{
				}
			}
			{
				// std::string mapNameString;
				// std::wstring MapNameWString;
				// wchar_t *const mapName;
				{
					// s_level_datum map_level;
					{
						// std::string mapName;
						// std::filesystem::path dir;
					}
				}
			}
		}
	}
	// function call : void (*const)(c_gui_pregame_setup_manager *, long, c_gui_selected_item *, char, long)
	todo("implement");
	_sub_107BC3F0(thisptr, __formal, controller_index, item, arg8, screen_index);
}

_extern void _sub_107BDC50(c_gui_pregame_setup_manager *);
void __fastcall c_gui_pregame_setup_manager__update_hook(c_gui_pregame_setup_manager *thisptr) // 0x107BDC50
{
	// `anonymous-namespace'::c_gui_pregame_setup_manager__update_hook
	// static ...; // 0x107BE02D
	// static ...; // 0x107BE020
	// static ...; // 0x107BE008
	// static ...; // 0x107BE000
	// c_gui_pregame_setup_manager *thisptr;
	// void (*const c_gui_screen_pregame_lobby_campaign__restore_save_game)(void *, long);
	// void (*const restore_game_setup_internal)(c_gui_pregame_setup_manager *, void *);
	{
		// bool waiting_for_mod_cache_load;
		{
			// IMod *mod;
		}
		{
			// __int32 const lobbyType;
			// std::string lastGameType;
			// std::string lastMap;
		}
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : IMod *(EModIndex) const
	// function call : bool () const
	// function call : bool (*const)()
	// function call : void (*const)(c_gui_pregame_setup_manager *, e_gui_game_mode)
	// function call : void (*const)(void *, long)
	// function call : void (*const)(c_gui_pregame_setup_manager *, void *)
	todo("implement");
	_sub_107BDC50(thisptr);
}

_extern void _sub_107BE5C0(EModIndex);
void notify_mod_package_opened_or_closed(EModIndex index) // 0x107BE5C0
{
	// `anonymous-namespace'::notify_mod_package_opened_or_closed
	// EModIndex index;
	todo("implement");
	_sub_107BE5C0(index);
}

void notify_lobby_changed() // 0x107BE510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?notify_lobby_changed@@YAXXZ");
	// `anonymous-namespace'::notify_lobby_changed
	// procedure flags: nofpo

	Modules::CommandMap::Instance().ExecuteCommand("Game.ScenarioScript lobby_updated");
}

void lobby_update() // 0x107BE3D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?lobby_update@@YAXXZ");
	// `anonymous-namespace'::lobby_update
	// procedure flags: nofpo
	// static ...; // 0x107BE4C4
	// static ...; // 0x107BE4B8
	// static ...; // 0x107BE4B0
	// c_network_session *session;
	// static long `lobby_update'::`2'::last_update_number; // 0x1135235C
		// long update_number;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)(c_network_session **)

	c_network_session *session;
	static long last_update_number = -1;

	if (((bool (*const)())0x5314b0)()
		&& ((bool (*const)())0x531e90)()
		&& network_session_interface_get_squad_session(&session)
		&& session->established())
	{
		long update_number = session->get_session_membership_update_number();

		if (update_number != last_update_number)
		{
			last_update_number = update_number;
			notify_lobby_changed();
		}
	}
	else if (last_update_number != -1)
	{
		last_update_number = -1;
	}
}

void clear_mod_cached_map_files() // 0x107BE130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?clear_mod_cached_map_files@@YAXXZ");
	// `anonymous-namespace'::clear_mod_cached_map_files
	// procedure flags: nofpo
	// long (*const cached_map_file_close)(long);
		// long i;
	// function call : long (*const)(long)

	long (__cdecl *const cached_map_file_close)(long) = (long (__cdecl *const)(long))0x5ab630;

	for (long i = 8; i < 15; i++)
	{
		cached_map_file_close(i);
	}

	*(long *)0x243B848 = -1;
	*(long *)0x243B84C = -1;
	*(long *)0x243B850 = -1;
	*(long *)0x243B854 = -1;
	memset((void *)0x243B858, 0, 0x840);
	memset((void *)0x243C098, 0, 0x3390);
}

_inline void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x107BC190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModChanged@ModListener@hades_file_local@@EAEXW4EModIndex@@PAVIMod@@@Z");
	// `anonymous-namespace'::ModListener::OnModChanged
	// IMod *mod;

	clear_mod_cached_map_files();
	notify_mod_package_opened_or_closed(index);
}

// mangled_x86(MANGLED_DEFAULT, "??0ModListener@hades_file_local@@QAE@XZ"); no body to assert in
_inline ModListener::ModListener() = default; // 0x107BBB20


/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<long,enum e_gui_selected_item_type>::operator==(e_gui_selected_item_type const &) const;
