/* ---------- headers */

#include "Patches/LoadingScreen.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/map_variant_loader.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/mod_system.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Pointer.hpp"
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

class c_mod_package_manager;
struct c_game_engine_base_variant;
struct s_game_options;
struct s_level_datum;
struct s_level_insertion_datum;
struct s_map_variant;
namespace Modules
{
	class ModuleServer;
}
namespace Patches
{
	namespace LoadingScreen
	{
		class LoadingScreenUi;
		struct LoadingScreenShowInfo;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace LoadingScreen {}
	using namespace Patches::LoadingScreen;
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

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const levels_try_and_get_campaign_insertion = reinterpret_cast<bool (*)(long, s_level_insertion_datum *)>(0x54C9E0);
	static auto const network_life_cycle_session_get_campaign_difficulty = reinterpret_cast<long (*)()>(0x435020);
}

extern bool (*const levels_try_and_get_multiplayer_map)(long, s_level_datum *);  // hades: added for 0x10A82F40
extern bool (*const levels_try_and_get_campaign_map)(long, s_level_datum *);  // hades: added for 0x10A82F40

namespace Patches
{
	namespace LoadingScreen
	{
		extern void ApplyAll();
		extern void SetUi(std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ui);
	}
}

bool ShowLoadingScreenHook(s_game_options &options);
void BeginLoadingHook(unsigned __int32 totalBytes);
void UpdateLoadingProgressHook(unsigned __int32 bytes);
void HideLoadingScreenHook();
std::vector<std::string> GetActiveSkullsForDisplay(unsigned long primarySkulls, unsigned long secondarySkulls);
std::vector<std::string> GetActiveSkullsForDisplay();
std::string camapgin_difficulty_level_to_string(long level);
bool BuildLoadingScreenShowInfo(s_game_options &gameOptions, Patches::LoadingScreen::LoadingScreenShowInfo &outInfo);

/* ---------- globals */

namespace Patches
{
	namespace LoadingScreen
	{
		extern bool firstRun; // 0x113545A0
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ActiveUi; // 0x12458CF8
	std::string const kCampaignSkullNames[16] = { "iron", "black_eye", "tough_luck", "catch", "fog", "famine", "thunderstorm", "tilt", "mythic", "assassin", "blind", "superman", "birthday", "daddy", "third_person", "directors_cut" }; // 0x12458B38
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace LoadingScreen
	{
		void ApplyAll() // 0x10A82A90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@LoadingScreen@Patches@@YAXXZ");

			Hook(0x166FB3, ShowLoadingScreenHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x161E1E, BeginLoadingHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2EBA07, UpdateLoadingProgressHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x167ABA, HideLoadingScreenHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}

		void SetUi(std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ui) // 0x10A840A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetUi@LoadingScreen@Patches@@YAXV?$shared_ptr@VLoadingScreenUi@LoadingScreen@Patches@@@std@@@Z");

			ActiveUi = ui;
		}

		// mangled_x86(MANGLED_DEFAULT, "??1LoadingScreenShowInfo@LoadingScreen@Patches@@QAE@XZ"); no body to assert in
		// _inline LoadingScreenShowInfo::~LoadingScreenShowInfo() = default; // 0x10A827C0 hades: implicit
	}
}

/* ---------- private code */

bool ShowLoadingScreenHook(s_game_options &options) // 0x10A84100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShowLoadingScreenHook@@YA_NAAUs_game_options@@@Z");

	if (strcmp(options.scenario_path, "maps\\mainmenu") == 0 && Patches::LoadingScreen::firstRun)
	{
		bool HasIntroBinks = std::filesystem::exists("bink\\intro.bik") || std::filesystem::exists("bink\\logo_343.bik") || std::filesystem::exists("bink\\logo_microsoft.bik");
		if (HasIntroBinks)
		{
			Patches::LoadingScreen::firstRun = false;
			((bool (*)(s_game_options &))0x567850)(options);
			return true;
		}
	}
	if (ActiveUi)
	{
		Patches::LoadingScreen::LoadingScreenShowInfo info = {};
		if (BuildLoadingScreenShowInfo(options, info))
			ActiveUi->Show(info);
	}
	return ((bool (*)(s_game_options &))0x567850)(options);
}

void BeginLoadingHook(unsigned __int32 totalBytes) // 0x10A82EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BeginLoadingHook@@YAXI@Z");

	if (ActiveUi)
	{
		ActiveUi->Begin(totalBytes);
	}
}

void UpdateLoadingProgressHook(unsigned __int32 bytes) // 0x10A84590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateLoadingProgressHook@@YAXI@Z");

	if (ActiveUi)
	{
		ActiveUi->UpdateProgress(bytes);
	}
}

void HideLoadingScreenHook() // 0x10A84000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HideLoadingScreenHook@@YAXXZ");

	void (__cdecl *HideLoadingScreen)() = (void(__cdecl *)())0x52ee20;

	HideLoadingScreen();
	if (ActiveUi)
		ActiveUi->Hide();
}

std::vector<std::string> GetActiveSkullsForDisplay(unsigned long primarySkulls, unsigned long secondarySkulls) // 0x10A83D50
{

	std::vector<std::string> skulls;
	for (__int32 i = 0; i < _countof(kCampaignSkullNames); i++)
	{
		if (i >= 9 && ((secondarySkulls >> (i - 9)) & 1))
			skulls.push_back(kCampaignSkullNames[i]);
		else if ((primarySkulls >> i) & 1)
			skulls.push_back(kCampaignSkullNames[i]);
	}
	return skulls;
}

std::vector<std::string> GetActiveSkullsForDisplay() // 0x10A83ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetActiveSkullsForDisplay@@YA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");

	unsigned long primarySkulls = 0;
	unsigned long secondarySkulls = 0;
	((void (__cdecl *)(unsigned long *))0x434F40)(&primarySkulls);
	((void (__cdecl *)(unsigned long *))0x434FB0)(&secondarySkulls);

	return GetActiveSkullsForDisplay(primarySkulls, secondarySkulls);
}

std::string camapgin_difficulty_level_to_string(long level) // 0x10A84770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??$const_formatter@$$BY03D@algorithm@boost@@YA?AU?$const_formatF@V?$iterator_range@PBD@boost@@@detail@01@AAY03$$CBD@Z");

	switch (level)
	{
	case 0:
		return "easy";
	case 1:
		return "normal";
	case 2:
		return "heroic";
	case 3:
		return "legendary";
	}
	return "unknown";
}

bool BuildLoadingScreenShowInfo(s_game_options &gameOptions, Patches::LoadingScreen::LoadingScreenShowInfo &outInfo) // 0x10A82F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildLoadingScreenShowInfo@@YA_NAAUs_game_options@@AAULoadingScreenShowInfo@LoadingScreen@Patches@@@Z");

	Modules::ModuleServer const &moduleServer = Utils::Singleton<Modules::ModuleServer>::Instance();
	outInfo.GameMode = (long)gameOptions.game_mode;
	outInfo.MapPath = gameOptions.scenario_path;
	outInfo.ServerName = moduleServer.VarServerNameClient->ValueString;
	outInfo.ServerMessage = moduleServer.VarServerMessageClient->ValueString;
	std::string modhash = c_mod_system::get_current_package_hash();
	outInfo.modHash = modhash;
	c_mod_package_manager::s_entry mod_package;
	bool hasModSet = c_mod_system::get_mod_info_by_hash(modhash.c_str(), &mod_package);
	outInfo.modAuthor = hasModSet ? mod_package.author : "";
	outInfo.modDescription = hasModSet ? mod_package.description : "";
	outInfo.modName = hasModSet ? Utils::String::ThinString(mod_package.name) : "";
	outInfo.modVersion = hasModSet ? std::to_string(mod_package.version_major) + "." + std::to_string(mod_package.version_minor) : "";
	if (gameOptions.game_mode == _game_mode_multiplayer)
	{
		s_level_datum level;
		if (!levels_try_and_get_multiplayer_map(gameOptions.map_id, &level))
			return true;
		c_game_engine_base_variant *gameVariant = gameOptions.game_variant.get_base_variant();
		s_map_variant const &mapVariant = gameOptions.map_variant;
		char *rawGameVariant = (char *)&gameOptions.game_variant;
		outInfo.VariantType = (long)gameOptions.game_variant.game_engine_type;
		outInfo.MapName = Utils::String::ThinString(mapVariant.metadata.name);
		outInfo.MapAuthor = mapVariant.metadata.author;
		outInfo.MapDescription = mapVariant.metadata.description;
		outInfo.VariantName = Utils::String::ThinString(gameVariant->metadata.name);
		outInfo.TimeLimit = gameVariant->miscellaneous_options.time_limit_in_minutes;
		outInfo.NumberOfRounds = gameVariant->miscellaneous_options.round_count;
		switch ((long)gameOptions.game_variant.game_engine_type)
		{
		case _game_engine_type_slayer:
			outInfo.ScoreToWin = *(short *)(rawGameVariant + 0x1D4);
			break;
		case _game_engine_type_oddball:
			outInfo.ScoreToWin = *(short *)(rawGameVariant + 0x1D8);
			break;
		case _game_engine_type_koth:
			outInfo.ScoreToWin = *(short *)(rawGameVariant + 0x1D8);
			break;
		case _game_engine_type_ctf:
			outInfo.ScoreToWin = *(short *)(rawGameVariant + 0x1DC);
			break;
		case _game_engine_type_assault:
			outInfo.ScoreToWin = *(short *)(rawGameVariant + 0x1DC);
			break;
		case _game_engine_type_juggernaut:
			outInfo.ScoreToWin = *(short *)(rawGameVariant + 0x1D4);
			break;
		case _game_engine_type_vip:
			outInfo.ScoreToWin = *(short *)(rawGameVariant + 0x1D4);
			break;
		default:
			outInfo.ScoreToWin = -1;
			break;
		}
	}
	else if (gameOptions.game_mode == _game_mode_campaign || gameOptions.game_mode == _game_mode_shared)
	{
		s_level_datum level;
		if (!levels_try_and_get_campaign_map(gameOptions.map_id, &level))
			return true;
		s_level_insertion_datum insertion;
		if (!eldorado::levels_try_and_get_campaign_insertion(gameOptions.map_id, &insertion))
			return true;
		outInfo.Difficulty = camapgin_difficulty_level_to_string(eldorado::network_life_cycle_session_get_campaign_difficulty());
		outInfo.Skulls = GetActiveSkullsForDisplay();
		outInfo.MapName = Utils::String::ThinString(level.name);
		outInfo.MapDescription = Utils::String::ThinString(level.description);
		if (gameOptions.campaign_insertion_index >= 0 && gameOptions.campaign_insertion_index < 9)
		{
			outInfo.InsertionName = Utils::String::ThinString(insertion.names[gameOptions.campaign_insertion_index].value);
			outInfo.InsertionDescription = Utils::String::ThinString(insertion.descriptions[gameOptions.campaign_insertion_index].value);
		}
	}
	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_game_engine_type,long>::operator long() const;
template c_enum<enum e_game_mode,long>::operator long() const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Patches { namespace LoadingScreen { bool firstRun = true; } }
