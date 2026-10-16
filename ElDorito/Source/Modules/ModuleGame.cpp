/* ---------- headers */

#include "Modules/ModuleGame.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_group.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/controller.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/interface/user_interface_sound.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Ui/Screen.hpp"

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
#include <charconv>
#include <chrono>
#include <cmath>
#include <codecvt>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
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
#include <unordered_map>
#include <utility>
#include <vector>
#include "Blam/interface/gui/gui_screen_manager.hpp"  // hades: added for 0x10993350

#include "mods/mod_system.hpp"  // hades: added for 0x1099A820

#include "PersistentMemory/PersistentMemorySystem.hpp"  // hades: added for 0x109931F0

#include "Utils/Logger.hpp"  // hades: added for 0x10997E90

#include "Blam/Cache/StringIdCache.hpp"  // hades: added for 0x10998800

/* ---------- forward declarations */

class IMod;
class c_controller_interface;
class c_gui_screen_widget;
class c_network_session;
struct _Mbstatet;
struct begin;
struct c_game_engine;
struct end;
struct lambda_1;
struct s_area_screen_effect_definition;
struct s_game_engine_settings_definition;
struct s_hs_global;
struct s_hs_script;
struct s_level_datum;
struct s_player_identifier;
struct s_scenario;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleGame;
}
namespace hades_file_local
{
	struct s_owned_content_item;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

namespace PersistentMemory {}
using namespace ::PersistentMemory;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

//class GetMapNameList::__l2::<lambda_1>
//{
//public:
//	void operator()(s_level_datum *) const;
//	<lambda_1>(GetMapNameList::__l2::<lambda_1> &);
//	<lambda_1>(std::vector<std::string> &);
//private:
//	std::vector<std::string> &mapNames; // 0x0
//public:
//	GetMapNameList::__l2::<lambda_1> &operator=(GetMapNameList::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(GetMapNameList::__l2::<lambda_1>) == 4, "Invalid GetMapNameList::__l2::<lambda_1> size");

typedef long s_async_task_id;

namespace hades_file_local
{
	struct s_owned_content_item
	{
		bool valid; // 0x0
		unsigned char __pad0[3]; // 0x1
		__int32 content_type; // 0x4
		s_player_identifier player_identifier; // 0x8
		wchar_t file_path[256]; // 0x10
	};
	static_assert(sizeof(s_owned_content_item) == 528, "Invalid s_owned_content_item size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Server { namespace VariableSynchronization { extern void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable); } }  // hades: added for 0x1098BDE0

template<typename T> __int32 FindDefaultGameVariant(c_tag_block<T> const &variants, std::string const &name) { for (__int32 i = 0; i < variants.count; i++) { if (variants[i].name_ascii[0] && strcmp(variants[i].name_ascii, name.c_str()) == 0) return i; } return -1; }  // hades: added for 0x1099C080

long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0X1099A180

namespace Patches::Ui { void ShowLanBrowser(); }  // hades: added for 0X1099AE10

namespace Blam::Network { Session *GetActiveSession(); }  // hades: added for 0X10993F10

namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0X10999BD0

bool font_package_begin_load_package(char const *filename);  // hades: added for 0X109939A0

namespace Utils::Version { std::string GetCompatibleVersionString(); }  // hades: added for 0X1099B8D0

void GetMapNameList(std::vector<std::string> &mapNames);
bool CommandGameLogLevel(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameLogTypes(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameLogFilter(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameInfo(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameExit(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameRestart(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameForceLoad(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameShowUI(std::vector<std::string> const &Arguments, std::string &returnInfo);
unsigned __int32 GetFileSize(std::ifstream &file);
__int32 GetMapId(std::string const &mapName);
bool LoadDefaultMapVariant(std::string const &mapName, unsigned char *out);
__int32 GetUiGameMode();
void SetOwnedContentData(s_owned_content_item *content_item, bool built_in, char const *file_path);
void SaveMapVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path);
void SaveGameVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path);
bool CommandGameLoadMap(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool LoadGameVariant(std::ifstream &file, unsigned char *out);
__int32 FindDefaultGameVariant(s_game_engine_settings_definition const *wezr, e_game_engine_type type, std::string const &name);
bool LoadDefaultGameVariant(std::string const &name, unsigned char *out);
bool CommandAnnoucementViewedDate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameType(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameStart(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameStartCountdown(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameStop(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameLeave(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameEnd(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameEndRound(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameVersion(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandListMaps(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandShowScreen(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandPlayUiSound(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandPlaySound(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandPlayLoopingSound(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandStopLoopingSound(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandGameTakeScreenshot(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandExecuteScenarioScript(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandExecutePrintScript(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGetTagAddress(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDisableScreenEffect(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableLanguageUpdated(std::vector<std::string> const &arguments, std::string &returnInfo);
bool ShowTickrate();
bool CommandShowTickrate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandFullScreenBlurLayer(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandFontPackage(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetMainMenuMod(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetCampaignMod(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetFirefightMod(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetMultiplayerMod(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandCloseStartMenu(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandShowLocalServersUI(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandShowModBrowser(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandShowServerModBrowser(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandShowModInfo(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandVersionCompat(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

extern bool (*const network_session_interface_get_squad_session)(c_network_session **); // 0x11248780

/* ---------- private variables */

namespace hades_file_local
{
	std::string const GameTypeExtensions[9] = { "ctf", "slayer", "oddball", "koth", "jugg", "terries", "assault", "zombiez", "vip" }; // 0x12454D80
	extern std::map<std::string,bool> layerBlurMap; // 0x12454D70
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	ModuleGame::ModuleGame() : ModuleBase("Game") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x1098BDE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleGame@Modules@@QAE@XZ");

		AddCommand("AnnoucementViewed", "annoucementviewed", "Retrieves or sets the date of the last viewed annoucement message", eCommandFlagsHidden, CommandAnnoucementViewedDate);
		AddCommand("LogLevel", "loglevel", "Debug log verbosity level", eCommandFlagsNone, CommandGameLogLevel, { "trace|info|warning|error|none The log verbosity level" });
		AddCommand("LogTypes", "logtypes", "Chooses which kinds of debug messages to print to the log file", eCommandFlagsNone, CommandGameLogTypes, { "game|network|graphics|memory|sound|input|debug|all|none The message types to log" });
		AddCommand("LogFilter", "debug_filter", "Allows you to set filters to apply to the debug messages", eCommandFlagsNone, CommandGameLogFilter, { "include/exclude The type of filter", "add/remove Add or remove the filter", "string The filter to add" });
		AddCommand("Info", "info", "Displays information about the game", eCommandFlagsNone, CommandGameInfo);
		AddCommand("Exit", "exit", "Ends the game process", eCommandFlagsNone, CommandGameExit);
		AddCommand("Restart", "restart", "Restart the game process", eCommandFlagsNone, CommandGameRestart);
		AddCommand("ForceLoad", "forceload", "Forces a map to load", eCommandFlagsNone, CommandGameForceLoad, { "mapname(string) The name of the map to load", "gametype(int) The gametype to load", "gamemode(int) The type of gamemode to play" });
		AddCommand("ShowUI", "show_ui", "Attempts to force a UI widget to open", eCommandFlagsNone, CommandGameShowUI, { "dialogID(int) The dialog ID to open", "arg1(int) Unknown argument", "flags(int) Unknown argument", "parentdialogID(int) The ID of the parent dialog" });
		AddCommand("Map", "map", "Loads a map or map variant", eCommandFlagsNone, CommandGameLoadMap, { "name(string) The internal name of the map or Forge map to load" });
		AddCommand("GameType", "gametype", "Loads a gametype", eCommandFlagsNone, CommandGameType, { "name(string) The internal name of the built-in gametype or custom gametype to load" });
		AddCommand("Start", "start", "Starts or restarts the game", eCommandFlagsNone, CommandGameStart);
		AddCommand("StartCountdown", "start_countdown", "Starts the game start countdown", eCommandFlagsNone, CommandGameStartCountdown);
		AddCommand("End", "end", "Ends the game", eCommandFlagsNone, CommandGameEnd);
		AddCommand("EndRound", "endround", "Ends the round", eCommandFlagsNone, CommandGameEndRound);
		AddCommand("Stop", "stop", "Stops the game, goes back to lobby", eCommandFlagsNone, CommandGameStop);
		AddCommand("Leave", "leave", "Leaves the game, goes back to menu", eCommandFlagsNone, CommandGameLeave);
		AddCommand("Version", "version", "Displays the game's version", eCommandFlagsNone, CommandGameVersion);
		AddCommand("VersionCompat", "version_compat", "Gets the minimum compatible version", eCommandFlagsHidden, CommandVersionCompat);
		AddCommand("ListMaps", "maps", "List all available map files", eCommandFlagsNone, CommandListMaps);
		AddCommand("ShowScreen", "showscreen", "Displays the specified screen", eCommandFlagsArgsNoParse, CommandShowScreen);
		AddCommand("PlayUiSound", "play_ui_sound", "Plays a ui sound", CommandFlags(eCommandFlagsOmitValueInList | eCommandFlagsHidden), CommandPlayUiSound);
		AddCommand("PlaySound", "play_sound", "Plays a sound effect", CommandFlags(eCommandFlagsOmitValueInList | eCommandFlagsHidden), CommandPlaySound);
		AddCommand("PlayLoopingSound", "play_looping_sound", "Plays a looping sound effect", CommandFlags(eCommandFlagsOmitValueInList | eCommandFlagsHidden), CommandPlayLoopingSound);
		AddCommand("StopLoopingSound", "stop_looping_sound", "Stops a looping sound effect", CommandFlags(eCommandFlagsOmitValueInList | eCommandFlagsHidden), CommandStopLoopingSound);
		AddCommand("TakeScreenshot", "take_screenshot", "Take a screenshot", eCommandFlagsNone, CommandGameTakeScreenshot);
		AddCommand("ScenarioScript", "scnr_script", "Executes a scenario script", eCommandFlagsRunOnMainMenu, CommandExecuteScenarioScript);
		AddCommand("PrintScript", "print_script", "Prints information about a scenario script expression", eCommandFlagsNone, CommandExecutePrintScript);
		AddCommand("TagAddress", "tag_address", "Gets the address of a tag in memory", eCommandFlagsNone, CommandGetTagAddress);
		AddCommand("DisableScreenEffect", "disable_sefc", "Used to disable the screen effect for customization", eCommandFlagsHidden, CommandDisableScreenEffect);
		AddCommand("ShowTickrate", "show_tickrate", "Toggle the on-screen Tickrate", eCommandFlagsNone, CommandShowTickrate);
		AddCommand("Update", "update", "Update the game to the latest version", eCommandFlagsNone, CommandGameUpdate);
		AddCommand("ShowLocalServersUI", "show_Local_server_browser", "Opens the local server browser UI", eCommandFlagsRunOnMainMenu, CommandShowLocalServersUI);
		AddCommand("ShowModBrowser", "show_mod_browser", "Opens the mod browser UI with the correct lobby", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsRunOnMainMenu), CommandShowModBrowser);
		AddCommand("ShowServerModBrowser", "show_server_mod_browserr", "Opens the server mod browser UI", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsRunOnMainMenu), CommandShowServerModBrowser);
		AddCommand("ShowModInfo", "show_mod_info", "Opens the mod info UI with details about the currently loaded mod", eCommandFlagsNone, CommandShowModInfo);
		VarMenuURL = AddVariableString("MenuURL", "menu_url", "url(string) The URL of the page you want to load inside the menu", eCommandFlagsArchived, "dew://screens/browser/");
		VarConsoleURL = AddVariableString("ConsoleURL", "console_url", "url(string) The URL of the page you want to load for the console screen", eCommandFlagsArchived, "dew://screens/console/");
		VarChatURL = AddVariableString("ChatURL", "chat_url", "url(string) The URL of the page you want to load for the chat screen", eCommandFlagsArchived, "dew://screens/chat/");
		VarLoadingURL = AddVariableString("LoadingURL", "loading_url", "url(string) The URL of the page you want to load for the loading screen", eCommandFlagsArchived, "dew://screens/loading/");
		VarVotingURL = AddVariableString("VotingURL", "voting_url", "url(string) The URL of the page you want to load for the voting screen", eCommandFlagsArchived, "dew://screens/voting/");
		VarTitleURL = AddVariableString("TitleURL", "title_url", "url(string) The URL of the page you want to load for the title screen", eCommandFlagsArchived, "dew://screens/title/");
		VarScoreboardURL = AddVariableString("ScoreboardURL", "scoreboard_url", "url(string) The URL of the page you want to load for the scoreboard screen", eCommandFlagsArchived, "dew://screens/scoreboard/");
		VarDialogURL = AddVariableString("DialogURL", "dialog_url", "url(string) The URL of the page you want to load for the dialog screen", eCommandFlagsArchived, "dew://screens/dialog/");
		VarSettingsURL = AddVariableString("SettingsURL", "settings_url", "url(string) The URL of the page you want to load for the settings screen", eCommandFlagsArchived, "dew://screens/settings/");
		VarProfileSettingsURL = AddVariableString("ProfileSettingsURL", "profile_settings_url", "url(string) The URL of the page you want to load for the profile_settings screen", eCommandFlagsArchived, "dew://screens/profile_settings/");
		VarServerSettingsURL = AddVariableString("ServerSettingsURL", "server_settings_url", "url(string) The URL of the page you want to load for the server_settings screen", eCommandFlagsArchived, "dew://screens/server_settings/");
		VarForgeObjectPropertiesURL = AddVariableString("ForgeObjectPropertiesURL", "forge_object_properties_url", "url(string) The URL of the page you want to load for the forge_object_properties screen", eCommandFlagsArchived, "dew://screens/forge/object_properties/");
		VarForgeObjectCreationURL = AddVariableString("ForgeObjectCreationURL", "forge_object_creation_url", "url(string) The URL of the page you want to load for the forge_object_creation screen", eCommandFlagsArchived, "dew://screens/forge/object_creation/");
		VarVoipURL = AddVariableString("VoipURL", "voip_url", "url(string) The URL of the page you want to load for the voip screen", eCommandFlagsArchived, "dew://screens/voip/");
		VarWeaponOffsetURL = AddVariableString("WeaponOffsetURL", "weapon_offset_url", "url(string) The URL of the page you want to load for the weapon_offset screen", eCommandFlagsArchived, "dew://screens/weapon_offset/");
		VarScreenshotNoticeURL = AddVariableString("ScreenshotNoticeURL", "screenshot_notice_url", "url(string) The URL of the page you want to load for the screenshot_notice screen", eCommandFlagsArchived, "dew://screens/screenshot_notice/");
		VarDiscordURL = AddVariableString("DiscordURL", "discord_url", "url(string) The URL of the page you want to load for the discord screen", eCommandFlagsArchived, "dew://screens/discord/");
		VarPlayerReportURL = AddVariableString("PlayerReportURL", "player_report_url", "url(string) The URL of the page you want to load for the report screen", eCommandFlagsArchived, "dew://screens/report/");
		VarInGameVotingURL = AddVariableString("InGameVotingURL", "ingame_voting_url", "url(string) The URL of the page you want to load for the ingame_voting screen", eCommandFlagsArchived, "dew://screens/ingame_voting/");
		VarEmoteScreenURL = AddVariableString("EmoteScreenURL", "emote_screen_url", "url(string) The URL of the page you want to load for the emote screen", eCommandFlagsArchived, "dew://screens/emote/");
		VarLanguage = AddVariableString("Language", "language", "The language to use", eCommandFlagsArchived, "english", VariableLanguageUpdated);
		VarSkipTitleSplash = AddVariableInt("SkipTitleSplash", "titlesplash", "Skip the ElDewrito splash screen and go straight to the main menu", eCommandFlagsArchived, 0);
		VarSkipTitleSplash->ValueIntMin = 0;
		VarSkipTitleSplash->ValueIntMax = 1;
		VarSkipIntroVideos = AddVariableInt("SkipIntroVideos", "skipintro", "Skip the game's intro videos.", eCommandFlagsArchived, 0);
		VarSkipIntroVideos->ValueIntMin = 0;
		VarSkipIntroVideos->ValueIntMax = 1;
		VarLogName = AddVariableString("LogName", "debug_logname", "Filename to store debug log messages", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), "logs\\dorito.log");
		VarRconPort = AddVariableInt("RconPort", "rcon_port", "The port to use for rcon in this instance of the game", eCommandFlagsArchived, 0x2E00);
		VarFirstRun = AddVariableInt("FirstRun", "first_run", "Show the first run setup next time the game starts", eCommandFlagsArchived, 1);
		VarFirstRun->ValueIntMin = 0;
		VarFirstRun->ValueIntMax = 1;
		VarExpandedScoreboard = AddVariableInt("ExpandedScoreboard", "expanded_scoreboard", "Always show full scoreboard, instead of just while locked/postgame", eCommandFlagsArchived, 0);
		VarExpandedScoreboard->ValueIntMin = 0;
		VarExpandedScoreboard->ValueIntMax = 1;
		VarHideChat = AddVariableInt("HideChat", "hide_chat", "Hide in-game chat screen", eCommandFlagsArchived, 0);
		VarHideChat->ValueIntMin = 0;
		VarHideChat->ValueIntMax = 1;
		VarChatMessageLimit = AddVariableInt("ChatMessageLimit", "chat_message_limt", "Sets the max limit for the number of messages in chat history that should be saved", eCommandFlagsArchived, 0x32);
		VarChatMessageLimit->ValueIntMin = 1;
		VarChatMessageLimit->ValueIntMax = 10000;
		VarHideH3UI = AddVariableInt("HideH3UI", "hide_h3ui", "Hide the H3 UI", eCommandFlagsHidden, 0);
		VarHideH3UI->ValueIntMin = 0;
		VarHideH3UI->ValueIntMax = 1;
		VarFullscreenBlur = AddVariableInt("FullscreenBlur", "fullscreen_blur", "Applies a fullscreen blur filter for use in CEF", eCommandFlagsHidden, 0);
		VarFullscreenBlurTime = AddVariableFloat("FullscreenBlurTime", "fullscreen_blur_time", "Sets the time it takes for fullcreen blur", eCommandFlagsHidden, 5.0f);
		AddCommand("FullscreenBlurLayer", "fullscreen_blur_screen", "Enable or disable blur from a specific layer name", eCommandFlagsHidden, CommandFullScreenBlurLayer);
		VarScreenshotsFolder = AddVariableString("ScreenshotsFolder", "screenshots_folder", "The location where the game will save screenshots", eCommandFlagsArchived, "%userprofile%\\Pictures\\Screenshots\\blam");
		VarScreenshotNoticeDisabled = AddVariableInt("ScreenshotNoticeDisabled", "screenshot_notice_disabled", "Disables the screenshot notifications", eCommandFlagsArchived, 0);
		VarDiscordEnable = AddVariableInt("Discord.Enable", "discord.enable", "Enable/disable discord integration", eCommandFlagsArchived, 1);
		VarDiscordAutoAccept = AddVariableInt("Discord.AutoAccept", "discord.auto_accept", "Allow auto accepting join requests", eCommandFlagsArchived, 0);
		VarCEFGpuEnable = AddVariableInt("CEFGpuEnable", "cef_gpu_enable", "0 = Disable CEF gpu acceleration / 1 = Enable CEF gpu acceleration", CommandFlags(eCommandFlagsRestartRequired | eCommandFlagsArchived), 1);
		VarCEFAtlasRendererEnable = AddVariableInt("CEFAtlasRendererEnable", "cef_atlas_path_renderer_enable", "Enables CEF Atlas path rendering", CommandFlags(eCommandFlagsRestartRequired | eCommandFlagsArchived), 0);
		VarMainMenuMod = AddVariableString("MainMenuMod", "main_menu_mod", "The filename of the mod to load on the main menu", eCommandFlagsArchived, "", CommandSetMainMenuMod);
		VarCampaignMod = AddVariableString("CampaignMod", "campaign_mod", "The filename of the mod to load on loading the campaign lobby", eCommandFlagsArchived, "", CommandSetCampaignMod);
		VarFirefightMod = AddVariableString("FirefightMod", "firefight_mod", "The filename of the mod to load on loading the firefight lobby", eCommandFlagsArchived, "", CommandSetFirefightMod);
		VarMultiplayerMod = AddVariableString("MultiplayerMod", "multiplayer_mod", "The filename of the mod to load on loading the Multiplayer lobby", eCommandFlagsArchived, "", CommandSetMultiplayerMod);
		AddCommand("UnPause", "close_start_menu", "Close the Start menu and unpause the game", eCommandFlagsHidden, CommandCloseStartMenu);
		VarTickRate = AddVariableInt("TickRate", "tick_rate", "Set the game tick rate in seconds", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsReplicated), 0x3C);
		VarTickRate->ValueIntMin = 1;
		VarTickRate->ValueIntMax = 144;
		VarTickRateClient = AddVariableInt("TickRateClient", "tick_rate_client", "Set the game tick rate in seconds", eCommandFlagsInternal, 0x3C);
		Server::VariableSynchronization::Synchronize(VarTickRate, VarTickRateClient);
		AddCommand("FontPackage", "font_package", "set the current font package path", eCommandFlagsNone, CommandFontPackage);
	}
}

/* ---------- private code */

void GetMapNameList(std::vector<std::string> &mapNames) // 0x1099C4E0
{

	auto addMap = [&mapNames](s_level_datum *level)
	{
		mapNames.push_back(std::filesystem::path(level->file_path).filename().string());
	};

	levels_iterate_multiplayer_maps(addMap);
	levels_iterate_campaign_maps(addMap);
}

bool CommandGameLogLevel(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10997E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameLogLevel@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	for (auto arg : Arguments)
	{
		if (arg.compare("none") == 0)
		{
			Utils::Singleton<Utils::Logger>::Instance().Level = Utils::LogLevel::None;
			break;
		}
		else if (arg.compare("trace") == 0)
		{
			Utils::Singleton<Utils::Logger>::Instance().Level = Utils::LogLevel::Trace;
			break;
		}
		else if (arg.compare("info") == 0)
		{
			Utils::Singleton<Utils::Logger>::Instance().Level = Utils::LogLevel::Info;
			break;
		}
		else if (arg.compare("warning") == 0)
		{
			Utils::Singleton<Utils::Logger>::Instance().Level = Utils::LogLevel::Warning;
			break;
		}
		else if (arg.compare("error") == 0)
		{
			Utils::Singleton<Utils::Logger>::Instance().Level = Utils::LogLevel::Error;
			break;
		}
	}
	returnInfo = "Log Level: " + Utils::LogLevelToString(Utils::Singleton<Utils::Logger>::Instance().Level);
	return true;
}

bool CommandGameLogTypes(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109981A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameLogTypes@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	unsigned __int32 types = (unsigned __int32)Utils::Singleton<Utils::Logger>::Instance().Types;
	for (auto arg : Arguments)
	{
		if (arg.find("all") != std::string::npos)
		{
			types = 0xFFFFFFFF;
			break;
		}
		else if (arg.find("none") != std::string::npos)
		{
			types = 0;
			break;
		}
		else
			types = 0;
		if (arg.find("game") != std::string::npos)
			types |= 0x1;
		if (arg.find("network") != std::string::npos)
			types |= 0x2;
		if (arg.find("graphics") != std::string::npos)
			types |= 0x4;
		if (arg.find("memory") != std::string::npos)
			types |= 0x8;
		if (arg.find("sound") != std::string::npos)
			types |= 0x10;
		if (arg.find("input") != std::string::npos)
			types |= 0x20;
		if (arg.find("debug") != std::string::npos)
			types |= 0x80000000;
	}
	Utils::Singleton<Utils::Logger>::Instance().Types = (Utils::LogTypes)types;
	returnInfo = "Log Types: " + Utils::LogTypesToString(Utils::Singleton<Utils::Logger>::Instance().Types);
	return true;
}

bool CommandGameLogFilter(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109974D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameLogFilter@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::stringstream ss;
	if (Arguments.size() != 3)
	{
		ss << "Usage: Game.LogFilter <include/exclude> <add/remove> <string>" << std::endl << std::endl;
	}
	else
	{
		bool exclude = (Arguments[0].compare("exclude") == 0);
		bool remove = Arguments[1].compare("remove") == 0;
		auto vect = exclude ? &Modules::ModuleGame::Instance().FiltersExclude : &Modules::ModuleGame::Instance().FiltersInclude;
		auto str = Arguments[2];
		bool exists = std::find(vect->begin(), vect->end(), str) != vect->end();
		if (remove && !exists)
		{
			ss << "Failed to find string \"" << str << "\" inside " << (exclude ? "exclude" : "include") << " filters list" << std::endl << std::endl;
		}
		else if (remove)
		{
			auto pos = std::find(vect->begin(), vect->end(), str);
			vect->erase(pos);
			ss << "Removed \"" << str << "\" from " << (exclude ? "exclude" : "include") << " filters list" << std::endl << std::endl;
		}
		else
		{
			vect->push_back(str);
			ss << "Added \"" << str << "\" to " << (exclude ? "exclude" : "include") << " filters list" << std::endl << std::endl;
		}
	}

	ss << "Include filters (message must contain these strings):";

	for (auto filter : Modules::ModuleGame::Instance().FiltersInclude)
		ss << std::endl << filter;

	ss << std::endl << std::endl << "Exclude filters (message must not contain these strings):";

	for (auto filter : Modules::ModuleGame::Instance().FiltersExclude)
		ss << std::endl << filter;

	returnInfo = ss.str();
	return true;
}

bool CommandGameInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10994D20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameInfo@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::stringstream ss;
	std::string ArgList((char *)Pointer(0x199C0A4)[0]);
	std::string LocalSecureKey((char *)Pointer(0x50CCDB5));
	std::string Xnkid;
	std::string Xnaddr;
	std::string Build((char *)Pointer(0x199C0F0));
	std::string SystemID((char *)Pointer(0x199C130));
	std::string SessionID((char *)Pointer(0x199C1D0));
	std::string DevKitName((char *)Pointer(0x160C8C8));
	std::string DevKitVersion((char *)Pointer(0x199C350));
	std::string FlashVersion((char *)Pointer(0x199C350));
	std::string MapName((char *)Pointer(0x22AB018)(0x1A4, 1));
	std::wstring VariantName((wchar_t *)Pointer(0x23DAF4C));
	Utils::String::BytesToHexString((char *)Pointer(0x2247B80), 0x10, Xnkid);
	Utils::String::BytesToHexString((char *)Pointer(0x2247B90), 0x10, Xnaddr);
	ss << std::hex << "ThreadLocalStorage: 0x" << std::hex << (unsigned __int32)tls_get(0) << std::endl;
	ss << "Command line args: " << (ArgList.empty() ? "(null)" : ArgList) << std::endl;
	ss << "Local Secure Key: " << (LocalSecureKey.empty() ? "(null)" : LocalSecureKey) << std::endl;
	ss << "XNKID: " << Xnkid << std::endl;
	ss << "XNAddr: " << Xnaddr << std::endl;
	ss << "Server Port: " << std::dec << Modules::ModuleServer::Instance().VarServerPort->ValueInt << std::endl;
	ss << "Server Endpoint Port: " << std::dec << Pointer(0x1860454).Read<unsigned int>() << std::endl;
	ss << "Build: " << (Build.empty() ? "(null)" : Build) << std::endl;
	ss << "SystemID: " << (SystemID.empty() ? "(null)" : SystemID) << std::endl;
	ss << "SessionID: " << (SessionID.empty() ? "(null)" : SessionID) << std::endl;
	ss << "SDK Info: " << (DevKitName.empty() ? "(null)" : DevKitName) << '|';
	ss << (DevKitVersion.empty() ? "(null)" : DevKitVersion) << std::endl;
	ss << "Flash Version: " << (FlashVersion.empty() ? "(null)" : FlashVersion) << std::endl;
	ss << "Current Map: " << (MapName.empty() ? "(null)" : MapName) << std::endl;
	ss << "Current Map Cache Size: " << std::dec << Pointer(0x22AB018)(0x8, 1).Read<int>() << std::endl;
	ss << "Loaded Game Variant: " << (VariantName.empty() ? "(null)" : Utils::String::ThinString(VariantName)) << std::endl;
	ss << "Loaded Game Type: 0x" << std::hex << Pointer(0x23DAF18).Read<int>() << std::endl;
	ss << "Tag Table Offset: 0x" << std::hex << Pointer(0x22AAFF4).Read<unsigned int>() << std::endl;
	ss << "Tag Bank Offset: 0x" << std::hex << Pointer(0x22AAFF8).Read<unsigned int>() << std::endl;
	ss << "Players global addr: 0x" << std::hex << (unsigned __int32)tls_getd().players_globals << std::endl;
	returnInfo = ss.str();
	return true;
}

bool CommandGameExit(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993FF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameExit@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	*reinterpret_cast<bool *>(0x22B473C) = true;
	return true;
}

bool CommandGameRestart(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109984F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameRestart@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool ret = true;
	std::string str = GetCommandLineA();
	_STARTUPINFOA si = {};
	_PROCESS_INFORMATION pi = {};
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOWNORMAL;
	if (!CreateProcessA(NULL, str.data(), NULL, NULL, FALSE, CREATE_BREAKAWAY_FROM_JOB, NULL, NULL, &si, &pi))
	{
		returnInfo = std::format("CreateProcess() failed. Error: {}", GetLastError());
		return false;
	}

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	Modules::CommandMap::Instance().ExecuteCommand("exit", false);
	return ret;
}

bool CommandGameForceLoad(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10994020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameForceLoad@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	extern char const *game_mode_get_string(e_game_mode);
	std::stringstream ss;
	if (Arguments.size() <= 0)
	{
		ss << "Current map: " << std::string((char *)0x2391824) << std::endl;
		ss << "Usage: Game.ForceLoad <mapname> [gametype] [maptype]" << std::endl;
		ss << "Available maps:";
		std::vector<std::string> mapNames;
		GetMapNameList(mapNames);
		for (std::string const &map : mapNames)
			ss << std::endl << "\t" << map;
		ss << std::endl << std::endl << "Valid gametypes:";
		for (long i = 0; i < k_number_of_game_engine_types; i++)
			ss << std::endl << "\t" << "[" << i << "] " << game_engine_type_get_string((e_game_engine_type)i);
		ss << std::endl << std::endl << "Valid gamemodes:";
		for (long i = 0; i < k_number_of_game_modes; i++)
			ss << std::endl << "\t" << "[" << i << "] " << game_mode_get_string((e_game_mode)i);
		returnInfo = ss.str();
		return false;
	}
	std::string mapName = Arguments[0];
	char const *gameTypeStr = "none";
	e_game_engine_type gameType = _game_engine_type_none;
	e_game_mode gameMode = _game_mode_multiplayer;
	s_level_datum level;
	if (!levels_find_map_by_name(mapName.c_str(), &level))
	{
		returnInfo = "Unable to find map " + mapName;
		return false;
	}
	mapName = ElDorito::Instance().GetMapsFolder() + mapName;
	if (Arguments.size() >= 2)
	{
		unsigned __int32 i;
		for (i = 0; i < k_number_of_game_engine_types; i++)
		{
			if (!_stricmp(game_engine_type_get_string((e_game_engine_type)i), Arguments[1].c_str()))
			{
				gameType = (e_game_engine_type)i;
				break;
			}
		}
		if (i == k_number_of_game_engine_types)
			gameType = (e_game_engine_type)atoi(Arguments[1].c_str());
		if (gameType > k_number_of_game_engine_types)
			gameType = _game_engine_type_slayer;
	}
	if (Arguments.size() >= 3)
	{
		unsigned __int32 i;
		for (i = 0; i < k_number_of_game_modes; i++)
		{
			if (!_stricmp(game_mode_get_string((e_game_mode)i), Arguments[2].c_str()))
			{
				gameMode = (e_game_mode)i;
				break;
			}
		}
		if (i == k_number_of_game_modes)
			gameMode = (e_game_mode)atoi(Arguments[2].c_str());
		if (gameMode > k_number_of_game_modes)
			gameMode = _game_mode_multiplayer;
	}
	ss << "Loading " << mapName << " gametype: " << game_engine_type_get_string(gameType) << " gamemode: " << game_mode_get_string(gameMode);
	Pointer(0x2391B2C).Write<unsigned int>(gameType);
	Pointer(0x2391C51).Write<unsigned char>(0);
	Pointer(0x2391800).Write<unsigned int>(gameMode);
	Pointer(0x2391824).Write(mapName.c_str(), mapName.length() + 1);
	Pointer(0x23917F0).Write<unsigned char>(1);
	returnInfo = ss.str();
	return true;
}

bool CommandGameShowUI(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10998800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameShowUI@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() <= 0)
	{
		returnInfo = "You must specify at least a dialog ID!";
		return false;
	}
	unsigned __int32 dialogStringId = 0;
	__int32 dialogArg1 = 0;
	__int32 dialogFlags = 4;
	unsigned __int32 dialogParentStringId = 0x1000C;
	try
	{
		std::string str_arg = Arguments[0];
		dialogStringId = Blam::Cache::StringIDCache::GetCurrent()->GetStringId(str_arg);
		if (dialogStringId == 0)
			dialogStringId = std::stoul(Arguments[0], 0, 0);
		if (Arguments.size() > 1)
			dialogArg1 = std::stoi(Arguments[1], 0, 0);
		if (Arguments.size() > 2)
			dialogFlags = std::stoi(Arguments[2], 0, 0);
		if (Arguments.size() > 3)
		{
			std::string str_arg = Arguments[3];
			dialogParentStringId = Blam::Cache::StringIDCache::GetCurrent()->GetStringId(str_arg);
			if (dialogParentStringId == 0)
				dialogParentStringId = std::stoul(Arguments[3], 0, 0);
		}
	}
	catch (std::invalid_argument &)
	{
		returnInfo = "Invalid argument given.";
		return false;
	}
	catch (std::out_of_range &)
	{
		returnInfo = "Invalid arguments.";
		return false;
	}
	Patches::Ui::ShowDialog(dialogStringId, dialogArg1, dialogFlags, dialogParentStringId);
	returnInfo = "Sent Show_UI notification to game.";
	return true;
}

unsigned __int32 GetFileSize(std::ifstream &file) // 0x1099C310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetFileSize@@YAIAAV?$basic_ifstream@DU?$char_traits@D@std@@@std@@@Z");

	auto originalPos = file.tellg();
	file.seekg(0, std::ios::end);
	auto size = static_cast<size_t>(file.tellg());
	file.seekg(originalPos);
	return size;
}

__int32 GetMapId(std::string const &mapName) // 0x1099C410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapId@@YAHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	s_level_datum level;

	if (levels_find_map_by_name(mapName.c_str(), &level))
	{
		return level.map_id;
	}
	else
	{
		return -1;
	}
}

bool LoadDefaultMapVariant(std::string const &mapName, unsigned char *out) // 0x1099CE50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadDefaultMapVariant@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAE@Z");

	__int32 mapId = GetMapId(mapName);
	if (mapId < 0)
	{
		return false;
	}
	if (!c_map_variant_loader::load_default(mapId, (s_map_variant *)out))
	{
		return false;
	}
	__int32 firstMapId = *(__int32 *)(out + 0xE0);
	__int32 secondMapId = *(__int32 *)(out + 0x100);
	return firstMapId == mapId && secondMapId == mapId;
}

__int32 GetUiGameMode() // 0x1099C5E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetUiGameMode@@YAHXZ");

	__int32 (__cdecl *GetUiGameModeImpl)() = (__int32(__cdecl *)())0x435640;

	return GetUiGameModeImpl();
}

void SetOwnedContentData(s_owned_content_item *content_item, bool built_in, char const *file_path) // 0x1099D9B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetOwnedContentData@@YAXPAUs_owned_content_item@hades_file_local@@_NPBD@Z");

	c_controller_interface *(*const controller_get)(long) = reinterpret_cast<c_controller_interface *(*)(long)>(0xA7CD50);
	s_player_identifier *(__thiscall *const c_controller_interface__get_player_identifier)(void *, s_player_identifier *) = reinterpret_cast<s_player_identifier *(__thiscall *)(void *, s_player_identifier *)>(0xA7D500);
	memset(content_item, 0, sizeof(content_item));
	content_item->valid = true;
	content_item->content_type = built_in ? 0 : 1;
	c_controller_interface__get_player_identifier(controller_get(0), &content_item->player_identifier);
	if (!built_in)
		wcsncpy_s(content_item->file_path, std::filesystem::absolute(file_path).c_str(), 255);
}

void SaveMapVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path) // 0x1099D8D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SaveMapVariantToPreferences@@YAXPBE_NPBD@Z");

	unsigned __int32 variantOffset;
	switch (GetUiGameMode())
	{
	case 2:
		variantOffset = 0x7F0;
		break;
	case 3:
		variantOffset = 0xEA98;
		break;
	default:
		return;
	}

	unsigned char *savedVariant = (unsigned char *)(variantOffset + 0x22C0130);
	memcpy(savedVariant, data, 0xE090);
	s_owned_content_item *owned_content_item = (s_owned_content_item *)(variantOffset + 0x22CE1C0);
	SetOwnedContentData(owned_content_item, built_in, file_path);
	*(bool *)0x22C0129 = true;
}

void SaveGameVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path) // 0x1099D830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SaveGameVariantToPreferences@@YAXPBE_NPBD@Z");

	if (GetUiGameMode() != 2)
	{
		return;
	}
	unsigned char *game_variant = (unsigned char *)0x22C04AC;
	memcpy(game_variant, data, 0x264);
	s_owned_content_item *content_item = (s_owned_content_item *)0x22C0710;
	SetOwnedContentData(content_item, built_in, file_path);
	*(bool *)0x22C0129 = true;
}

bool CommandGameLoadMap(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10996D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameLoadMap@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() != 1)
	{
		returnInfo = "You must specify an internal map or Forge map name!";
		return false;
	}
	__int32 lobbyType = GetUiGameMode();
	if (lobbyType != 2 && lobbyType != 3)
	{
		returnInfo = "You can only change maps from a Custom Games or Forge lobby.";
		return false;
	}
	std::string mapName = Arguments[0];
	unsigned char variantData[57488];
	bool built_in = true;
	std::string variantFileName = "data/map_variants/" + mapName + "/sandbox.map";
	returnInfo = "Loading map variant " + variantFileName + "...";
	std::ifstream mapVariant(variantFileName, std::ios::binary);
	if (mapVariant.is_open())
	{
		built_in = false;
		returnInfo = "Loading map variant " + variantFileName + "...";
		if (!c_map_variant_loader::load_from_file(variantFileName.c_str(), (s_map_variant *)variantData))
		{
			returnInfo += "\nInvalid map variant file!";
			return false;
		}
	}
	else
	{
		s_level_datum level;
		if (!levels_find_map_by_name(mapName.c_str(), &level))
		{
			returnInfo = "Invalid map!";
			return false;
		}
		returnInfo = "Loading built-in map " + std::string(level.file_path) + ".map...";
		if (!LoadDefaultMapVariant(mapName, variantData))
		{
			returnInfo += "\nInvalid map file!";
			return false;
		}
	}
	bool (*LoadMapVariant)(unsigned char *, void *) = reinterpret_cast<bool (*)(unsigned char *, void *)>(0xA83AF0);
	if (!LoadMapVariant(variantData, nullptr))
	{
		returnInfo += "\nLoad failed.";
		return false;
	}
	SaveMapVariantToPreferences(variantData, built_in, variantFileName.c_str());
	returnInfo += "\nMap variant loaded successfully!";
	return true;
}

bool LoadGameVariant(std::ifstream &file, unsigned char *out) // 0x1099CF20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadGameVariant@@YA_NAAV?$basic_ifstream@DU?$char_traits@D@std@@@std@@PAE@Z");

	// Verify file size
	const auto GameVariantBlfSize = 0x3BC;
	if (GetFileSize(file) < GameVariantBlfSize)
		return false;

	// Load it into a buffer and have the game parse it
	uint8_t blfData[GameVariantBlfSize];
	file.read(reinterpret_cast<char*>(blfData), GameVariantBlfSize);

	typedef bool(__thiscall *ParseGameVariantBlfPtr)(void *blf, uint8_t *outVariant, bool *result);
	auto ParseGameVariant = reinterpret_cast<ParseGameVariantBlfPtr>(0x573150);
	return ParseGameVariant(blfData, out, nullptr);
}

__int32 FindDefaultGameVariant(s_game_engine_settings_definition const *wezr, e_game_engine_type type, std::string const &name) // 0x1099C080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindDefaultGameVariant@@YAHPBUs_game_engine_settings_definition@@W4e_game_engine_type@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	switch (type)
	{
	case _game_engine_type_ctf:
		return FindDefaultGameVariant(wezr->ctf_variants, name);
	case _game_engine_type_slayer:
		return FindDefaultGameVariant(wezr->slayer_variants, name);
	case _game_engine_type_oddball:
		return FindDefaultGameVariant(wezr->oddball_variants, name);
	case _game_engine_type_koth:
		return FindDefaultGameVariant(wezr->koth_variants, name);
	case _game_engine_type_vip:
		return FindDefaultGameVariant(wezr->vip_variants, name);
	case _game_engine_type_juggernaut:
		return FindDefaultGameVariant(wezr->juggernaut_variants, name);
	case _game_engine_type_territories:
		return FindDefaultGameVariant(wezr->territories_variants, name);
	case _game_engine_type_assault:
		return FindDefaultGameVariant(wezr->assault_variants, name);
	case _game_engine_type_infection:
		return FindDefaultGameVariant(wezr->infection_variants, name);
	}
	return -1;
}

bool LoadDefaultGameVariant(std::string const &name, unsigned char *out) // 0x1099CD30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadDefaultGameVariant@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAE@Z");

	s_game_engine_settings_definition const *wezr = ((s_game_engine_settings_definition const *(__cdecl *const)())0x719290)();
	if (!wezr)
	{
		return false;
	}

	__int32 index = -1;
	__int32 type;
	for (type = _game_engine_type_ctf; type < k_number_of_game_engine_types; type++)
	{
		index = FindDefaultGameVariant(wezr, (e_game_engine_type)type, name);
		if (index != -1)
		{
			break;
		}
	}

	if (type == k_number_of_game_engine_types)
	{
		return false;
	}

	__int32 const VariantDataSize = 0x264;
	memset(out, 0, VariantDataSize);

	bool (__cdecl *LoadBuiltInGameVariant)(e_game_engine_type, __int32, unsigned char *) = (bool(__cdecl *)(e_game_engine_type, __int32, unsigned char *))0x572270;
	return LoadBuiltInGameVariant((e_game_engine_type)type, index, out);
}

bool CommandAnnoucementViewedDate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109931F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandAnnoucementViewedDate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() == 1)
	{
		PersistentMemory::SetLastAnnoucementViewedDate(Arguments[0]);
		PersistentMemory::Save();
		returnInfo = "Date Updated";
		return true;
	}
	else
	{
		std::string date = PersistentMemory::GetLastAnnoucementViewedDate();
		returnInfo = date;
		return true;
	}
}

bool CommandGameType(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10999240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameType@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() != 1)
	{
		returnInfo = "You must specify a built-in gametype or custom gametype name!";
		return false;
	}
	if (GetUiGameMode() != 2)
	{
		returnInfo = "You can only change gametypes from a Custom Games lobby.";
		return false;
	}
	std::string name = Arguments[0];
	unsigned char variantData[612];
	bool built_in = true;
	std::ifstream gameVariant;
	std::string variantFileName;
	for (auto &extension : GameTypeExtensions)
	{
		variantFileName = "data/game_variants/" + name + "/variant." + extension;
		gameVariant.open(variantFileName, std::ios::binary);
		if (gameVariant.is_open())
			break;
	}
	if (gameVariant.is_open())
	{
		built_in = false;
		returnInfo = "Loading game variant " + variantFileName + "...";
		if (!LoadGameVariant(gameVariant, variantData))
		{
			returnInfo += "\nInvalid game variant file!";
			return false;
		}
	}
	else
	{
		returnInfo = "Loading built-in game variant " + name + "...";
		if (!LoadDefaultGameVariant(name, variantData))
		{
			returnInfo += "\nInvalid game variant name!";
			return false;
		}
	}
	bool (*LoadGameVariant)(unsigned char *) = reinterpret_cast<bool (*)(unsigned char *)>(0x439860);
	if (!LoadGameVariant(variantData))
	{
		returnInfo += "\nLoad failed.";
		return false;
	}
	SaveGameVariantToPreferences(variantData, built_in, variantFileName.c_str());
	returnInfo += "\nGame variant loaded successfully!";
	return true;
}

bool CommandGameStart(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10998CE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameStart@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	auto session = Blam::Network::GetActiveSession();
	if (!session || !session->Parameters.SetSessionMode(2))
	{
		returnInfo = "Unable to start the game!";
		return false;
	}
	returnInfo = "Starting game...";
	return true;
}

bool CommandGameStartCountdown(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10998D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameStartCountdown@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool (__cdecl *const StartCountdownImpl)(int, int) = (bool(__cdecl *const)(int, int))0xa83cf0;

	if (StartCountdownImpl(0, 6))
	{
		returnInfo = "Starting Countdown...";
		return true;
	}
	returnInfo = "failed to start game";
	return false;
}

bool CommandGameStop(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10998E20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameStop@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	auto session = Blam::Network::GetActiveSession();
	if (!session || !session->Parameters.SetSessionMode(1))
	{
		returnInfo = "Unable to stop the game!";
		return false;
	}
	returnInfo = "Stopping game...";
	return true;
}

bool CommandGameLeave(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10996C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameLeave@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	c_network_session *session = nullptr;
	network_session_interface_get_squad_session(&session);
	if (!session || !session->established())
	{
		returnInfo = "Unable to leave the game!";
		return false;
	}

	void (__thiscall *const c_network_session__leave_session_and_disconnect)(c_network_session *) = (void(__thiscall *const)(c_network_session *))0x47dc40;
	c_network_session__leave_session_and_disconnect(session);
	returnInfo = "Leaving game...";
	return true;
}

bool CommandGameEnd(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameEnd@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
	{
		returnInfo = "Unable to end the game!";
		return false;
	}
	if (((bool(__cdecl *)())0x531B20)())
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (!session || !session->Parameters.SetSessionMode(1))
		{
			returnInfo = "Unable to stop the game!";
			return false;
		}
		returnInfo = "Stopping game...";
		return true;
	}
	Blam::Network::EndGame();
	returnInfo = "Ending game...";
	return true;
}

bool CommandGameEndRound(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameEndRound@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost() || !((__int32(__cdecl *)())0x5ce150)())
	{
		returnInfo = "Unable to end the round!";
		return false;
	}

	((void(__cdecl *)(__int32, __int32, __int32))0x54e390)(-1, 0, 22);
	returnInfo = "Ending round...";
	return true;
}

bool CommandGameVersion(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x10999BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameVersion@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	returnInfo = Utils::Version::GetVersionString();
	return true;
}

bool CommandListMaps(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x10999F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandListMaps@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::vector<std::string> mapNames;
	GetMapNameList(mapNames);

	for (std::string const &map : mapNames)
	{
		if (returnInfo.length() > 0)
			returnInfo += ',';
		returnInfo += map;
	}

	return true;
}

bool CommandShowScreen(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099B0D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandShowScreen@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (arguments.size() == 0)
	{
		returnInfo = "Usage: Game.ShowScreen <screen name> <opt json>";
		return false;
	}
	if (arguments[0].find(' ') == std::string::npos)
	{
		Web::Ui::ScreenLayer::Show(arguments[0], "{}");
		return true;
	}

	int pos = arguments[0].find(' ') + 1;
	std::string jsonArg = arguments[0].substr(pos);
	rapidjson::Document doc;
	doc.Parse(jsonArg.c_str());
	if (doc.HasParseError())
	{
		returnInfo = "The passed json argument was invalid: " + jsonArg;
		return false;
	}
	rapidjson::StringBuffer buff;
	buff.Clear();
	rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
	doc.Accept(writer);
	Web::Ui::ScreenLayer::Show(arguments[0].substr(0, pos - 1), buff.GetString());
	return true;
}

bool CommandPlayUiSound(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099A270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandPlayUiSound@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (arguments.size() < 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}

	char *endp;
	long index = strtol(arguments[0].c_str(), &endp, 10);
	if (endp == arguments[0].c_str() || index < 0 || index >= 20)
	{
		returnInfo = "Invalid index";
		return false;
	}

	((long(__cdecl *)(e_user_interface_sound, long))0xAA5CD0)((e_user_interface_sound)index, -1);
	return true;
}

bool CommandPlaySound(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099A180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandPlaySound@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (arguments.size() < 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}

	long tag_index = tag_find_by_name(0x736E6421, arguments[0].c_str());
	if (tag_index == -1)
	{
		returnInfo = "Sound not found!";
		return false;
	}

	static auto Sound_PlaySoundEffect = (void(__cdecl *)(long, float))0x005DE300;
	Sound_PlaySoundEffect(tag_index, 1.0f);
	return true;
}

bool CommandPlayLoopingSound(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099A090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandPlayLoopingSound@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (arguments.size() < 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}

	long tag_index = tag_find_by_name(0x6C736E64, arguments[0].c_str());
	if (tag_index == -1)
	{
		returnInfo = "Looping Sound not found";
		return false;
	}

	static auto Sound_LoopingSound_Start = (void(__cdecl *)(long, long, long, long, long))0x005DC530;
	Sound_LoopingSound_Start(tag_index, -1, 0x3F800000, 0, 0);
	return true;
}

bool CommandStopLoopingSound(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099B7F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandStopLoopingSound@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (arguments.size() < 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}

	long tag_index = tag_find_by_name('lsnd', arguments[0].c_str());
	if (tag_index == -1)
	{
		returnInfo = "Looping Sound not found";
		return false;
	}

	static void (*Sound_LoopingSound_Stop)(long, long) = (void (*)(long, long))0x005DC6B0;
	Sound_LoopingSound_Stop(tag_index, -1);
	return true;
}

bool CommandGameTakeScreenshot(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10998EC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameTakeScreenshot@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	wchar_t *(*TakeScreenshotImpl)() = (wchar_t *(*)())0x60f420;
	return TakeScreenshotImpl();
	wchar_t *path = TakeScreenshotImpl();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wstring_to_string;
	std::string screenshot_path = wstring_to_string.to_bytes(path);
	if (!Modules::ModuleGame::Instance().VarScreenshotNoticeDisabled->ValueInt)
	{
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("filepath");
		jsonWriter.String(screenshot_path.c_str());
		jsonWriter.EndObject();
		Web::Ui::ScreenLayer::Notify("screenshot_taken", jsonBuffer.GetString(), true);
	}
	returnInfo = "Screenshot saved to: " + screenshot_path;
	return true;
}

bool CommandExecuteScenarioScript(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandExecuteScenarioScript@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() == 0)
	{
		returnInfo = "Expected script name";
		return false;
	}
	if (*(bool *)0x23917F0)
	{
		returnInfo = "Can not run script while in a loading screen";
		return false;
	}
	s_scenario *scnr = global_scenario_get();
	if (!scnr)
	{
		returnInfo = "No scenario loaded";
		return false;
	}
	for (__int32 i = 0; i < scnr->scripts.count; i++)
	{
		s_hs_script const &script = scnr->scripts[i];
		if (!_stricmp(script.name.ascii, Arguments[0].c_str()))
		{
			if (((long(__cdecl *)(short, e_hs_script_type, e_hs_script_type))0x598050)((short)i, script.type, (e_hs_script_type)3) == -1)
			{
				returnInfo = "Failed execution failed";
				return false;
			}
			return true;
		}
	}
	returnInfo = "Script not found";
	return false;
}

bool CommandExecutePrintScript(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109936A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandExecutePrintScript@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() == 0)
	{
		returnInfo = "Expected script name";
		return false;
	}
	if (*(bool *)0x23917F0)
	{
		returnInfo = "Can not print a script while in a loading screen";
		return false;
	}
	s_scenario *scnr = global_scenario_get();
	if (!scnr)
	{
		returnInfo = "No scenario loaded";
		return false;
	}
	for (__int32 i = 0; i < scnr->script_globals.count; i++)
	{
		s_hs_global const &script = scnr->script_globals[i];
		if (!_stricmp(script.name.ascii, Arguments[0].c_str()))
		{
			void *result = hs_get_node_data(script.root_expression_index);
			return true;
		}
	}
	returnInfo = "Script not found";
	return false;
}

bool CommandGetTagAddress(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10999C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGetTagAddress@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() <= 0)
	{
		returnInfo = "You must specify a tag index!";
		return false;
	}
	int tagIndex = 0;
	try
	{
		tagIndex = std::stoi(Arguments[0], 0, 0);
	}
	catch (std::invalid_argument &)
	{
		returnInfo = "Invalid argument given.";
		return false;
	}
	typedef void *(*GetTagAddressPtr)(int groupTag, uint32_t index);
	auto GetTagAddressImpl = reinterpret_cast<GetTagAddressPtr>(0x503370);
	void* address = GetTagAddressImpl(0, tagIndex);
	std::stringstream ss;
	ss << "Tag 0x" << std::hex << tagIndex << " is located at 0x" << std::hex << (int)address;
	returnInfo = ss.str();
	return true;
}

bool CommandDisableScreenEffect(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109933F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDisableScreenEffect@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() < 2)
	{
		returnInfo = "You must include an index and a range!";
		return false;
	}
	__int32 index = 0;
	__int32 value = 0;
	try
	{
		index = std::stoi(Arguments[0], nullptr, 0);
		value = std::stof(Arguments[1]);
	}
	catch (std::invalid_argument &)
	{
		returnInfo = "Invalid argument given.";
		return false;
	}
	if (!((bool(__cdecl *)())0x5314B0)())
		return false;
	s_scenario const *scnr = global_scenario_get();
	if (!scnr)
	{
		returnInfo = "A scenario must be loaded!";
		return false;
	}
	if (scnr->default_screen_fx.index == -1)
	{
		returnInfo = "Current scenario does not have a default screen fx";
		return true;
	}
	s_area_screen_effect_definition *sefc = (s_area_screen_effect_definition *)tag_get('sefc', scnr->default_screen_fx.index);
	if (sefc)
	{
		if (value)
			sefc->screen_effects[index].flags |= 1;
		else
			sefc->screen_effects[index].flags &= ~1;
		return true;
	}
	returnInfo = "Failed to get sefc";
	return false;
}

bool VariableLanguageUpdated(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099DD90
{

	if (arguments.size() < 1)
		return false;

	static const std::unordered_map<std::string, int> languageIds =
	{
		{ "english", 0 },
		{ "japanese", 1 },
		{ "german", 2 },
		{ "french", 3 },
		{ "spanish", 4 },
		{ "mexican", 5 },
		{ "italian", 6 },
		{ "korean", 7 },
		{ "chinese", 9 },
		{ "portuguese", 10 },
		{ "russian", 11 }
	};

	auto it = languageIds.find(Utils::String::ToLower(arguments[0]));
	if (it == languageIds.end())
		return false;

	*(uint32_t*)0x189DEE4 = it->second;
	return true;
}

bool ShowTickrate() // 0x1099DB70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShowTickrate@@YA_NXZ");

	auto Tickrate = Pointer(0x22B47FC);
	Tickrate.Write(!Tickrate.Read<bool>());
	return Tickrate.Read<bool>();
}

bool CommandShowTickrate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099B650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandShowTickrate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::stringstream ss;
	ss << "Tickrate: " << (ShowTickrate() ? "shown." : "hidden.");
	returnInfo = ss.str();
	return true;
}

bool CommandGameUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10999910
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	_STARTUPINFOW si = {};
	_PROCESS_INFORMATION pi = {};
	si.cb = sizeof(si);
	si.wShowWindow = 1;
	std::wstring args = L"launcher.exe";
	if (!CreateProcessW(nullptr, args.data(), nullptr, nullptr, FALSE, 0x1000000, nullptr, nullptr, &si, &pi))
	{
		unsigned long ret = GetLastError();
		if (ret == 2 || ret == 3)
			returnInfo = "\"launcher.exe\" not found in current directory";
		else
		{
			char error[256];
			sprintf_s(error, "failed to execute launcher. error: %d %d", ret, GetLastError());
			returnInfo = error;
		}
		return false;
	}
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return CommandGameExit(Arguments, returnInfo);
}

bool CommandFullScreenBlurLayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandFullScreenBlurLayer@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() == 1 && Arguments[0] == "reset")
	{
		layerBlurMap.clear();
		Modules::CommandMap::Instance().ExecuteCommand("Game.fullscreenblur 0", false);
		return true;
	}
	if (Arguments.size() != 2)
		return false;
	std::string layerName = Arguments[0];
	std::string toggle = Arguments[1];
	bool blurEnabled = false;
	if (toggle == "1")
		layerBlurMap[layerName] = true;
	else
		layerBlurMap.erase(layerName);
	for (std::pair<std::string const, bool> const &pair : layerBlurMap)
	{
		if (pair.second)
		{
			blurEnabled = true;
			break;
		}
	}
	if (blurEnabled)
		Modules::CommandMap::Instance().ExecuteCommand("Game.fullscreenblur 1", false);
	else
		Modules::CommandMap::Instance().ExecuteCommand("Game.fullscreenblur 0", false);
	return true;
}

bool CommandFontPackage(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109939A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandFontPackage@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() < 1)
	{
		return false;
	}

	font_package_begin_load_package(Arguments[0].c_str());

	return true;
}

bool CommandSetMainMenuMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099A820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetMainMenuMod@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	void (*const main_menu_launch_force)() = reinterpret_cast<void (*)()>(0x568190);
	if (Arguments.empty())
		return false;
	if (!((bool(__cdecl *)())0x5314B0)())
		return true;
	std::filesystem::path filename = std::filesystem::path(c_mod_system::get_package_directory()) / Arguments[0];
	IMod const *currentMod = c_mod_system::GetModManager().GetMod(kMainMenu);
	if ((currentMod && filename == currentMod->GetFilename()) || (!currentMod && Arguments[0] == ""))
		return true;
	bool (*const game_is_mainmenu)() = reinterpret_cast<bool (*)()>(0x531E90);
	if (game_is_mainmenu())
		main_menu_launch_force();
	return true;
}

bool CommandSetCampaignMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099A3A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetCampaignMod@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (!((bool(__cdecl *)())0x5314B0)())
		return true;
	bool (*const game_is_mainmenu)() = reinterpret_cast<bool (*)()>(0x531E90);
	__int32 lobbyType = GetUiGameMode();
	if (game_is_mainmenu() && lobbyType == 0)
	{
		s_static_string<256> file_path;
		std::string campaignPakName = Modules::ModuleGame::Instance().VarCampaignMod->ValueString.c_str();
		file_path.print("%s\\%s", c_mod_system::get_package_directory(), campaignPakName);
		if (file_path.length() > 1 && campaignPakName.length() > 0)
			c_mod_system::load_package_by_identifier(campaignPakName.c_str());
	}
	return true;
}

bool CommandSetFirefightMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099A5E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetFirefightMod@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (!((bool(__cdecl *)())0x5314B0)())
		return true;
	bool (*const game_is_mainmenu)() = reinterpret_cast<bool (*)()>(0x531E90);
	__int32 lobbyType = GetUiGameMode();
	if (game_is_mainmenu() && lobbyType == 5)
	{
		s_static_string<256> file_path;
		std::string FirefightPakName = Modules::ModuleGame::Instance().VarFirefightMod->ValueString.c_str();
		file_path.print("%s\\%s", c_mod_system::get_package_directory(), FirefightPakName);
		if (file_path.length() > 1 && FirefightPakName.length() > 0)
			c_mod_system::load_package_by_identifier(FirefightPakName.c_str());
	}
	return true;
}

bool CommandSetMultiplayerMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099ABC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetMultiplayerMod@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (!((bool(__cdecl *)())0x5314B0)())
		return true;
	bool (*const game_is_mainmenu)() = reinterpret_cast<bool (*)()>(0x531E90);
	__int32 lobbyType = GetUiGameMode();
	if (game_is_mainmenu() && (lobbyType == 2 || lobbyType == 3))
	{
		s_static_string<256> file_path;
		std::string MultiplayerPakName = Modules::ModuleGame::Instance().VarMultiplayerMod->ValueString.c_str();
		file_path.print("%s\\%s", c_mod_system::get_package_directory(), MultiplayerPakName);
		if (file_path.length() > 1 && MultiplayerPakName.length() > 0)
			c_mod_system::load_package_by_identifier(MultiplayerPakName.c_str());
	}
	return true;
}

bool CommandCloseStartMenu(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCloseStartMenu@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	c_gui_screen_widget *screen = c_gui_screen_manager::get()->find_screen(4, 0x10084);

	if (screen)
	{
		((void(__thiscall *)(void *, __int32))0xab2830)(screen, 0);
		return true;
	}

	returnInfo = "Start menu isnt open";
	return false;
}

bool CommandShowLocalServersUI(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099AE10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandShowLocalServersUI@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool (__cdecl *const IsMainMenu)() = (bool(__cdecl *const)())0x531e90;

	if (IsMainMenu())
	{
		Patches::Ui::ShowLanBrowser();
		return true;
	}
	else
	{
		returnInfo = "Must be on MainMenu";
		return false;
	}
}

bool CommandShowModBrowser(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099AE90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandShowModBrowser@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool (*const game_in_main_menu)() = reinterpret_cast<bool (*)()>(0x531E90);
	if (game_in_main_menu())
	{
		Web::Ui::ScreenLayer::Show("mod_browse", "{}");
		return true;
	}
	else
	{
		returnInfo = "Must be on MainMenu";
		return false;
	}
}

bool CommandShowServerModBrowser(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099B510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandShowServerModBrowser@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool (*const game_in_main_menu)() = reinterpret_cast<bool (*)()>(0x531E90);
	if (game_in_main_menu())
	{
		Web::Ui::ScreenLayer::Show("server_mod_browser", "{}");
		return true;
	}
	else
	{
		returnInfo = "Must be on MainMenu";
		return false;
	}
}

bool CommandShowModInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099AFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandShowModInfo@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Web::Ui::ScreenLayer::Show("mod_info", "{}");
	return true;
}

bool CommandVersionCompat(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099B8D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandVersionCompat@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	returnInfo = Utils::Version::GetCompatibleVersionString();
	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_game_engine_assault_variant_definition>::try_get_element(__int32, s_game_engine_assault_variant_definition **) const;
template bool c_tag_block<s_game_engine_ctf_variant_definition>::try_get_element(__int32, s_game_engine_ctf_variant_definition **) const;
template bool c_tag_block<s_game_engine_infection_variant_definition>::try_get_element(__int32, s_game_engine_infection_variant_definition **) const;
template bool c_tag_block<s_game_engine_juggernaut_variant_definition>::try_get_element(__int32, s_game_engine_juggernaut_variant_definition **) const;
template bool c_tag_block<s_game_engine_king_variant_definition>::try_get_element(__int32, s_game_engine_king_variant_definition **) const;
template bool c_tag_block<s_game_engine_oddball_variant_definition>::try_get_element(__int32, s_game_engine_oddball_variant_definition **) const;
template bool c_tag_block<s_game_engine_slayer_variant_definition>::try_get_element(__int32, s_game_engine_slayer_variant_definition **) const;
template bool c_tag_block<s_game_engine_territories_variant_definition>::try_get_element(__int32, s_game_engine_territories_variant_definition **) const;
template bool c_tag_block<s_game_engine_vip_variant_definition>::try_get_element(__int32, s_game_engine_vip_variant_definition **) const;
template bool c_tag_block<s_hs_global>::try_get_element(__int32, s_hs_global **) const;
template c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short> & c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short>::operator&=(__int32 const);
template c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short> & c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short>::operator|=(__int32 const);
template s_game_engine_assault_variant_definition * c_tag_block<s_game_engine_assault_variant_definition>::get_element(__int32) const;
template s_game_engine_assault_variant_definition const & c_tag_block<s_game_engine_assault_variant_definition>::operator[](__int32) const;
template s_game_engine_ctf_variant_definition * c_tag_block<s_game_engine_ctf_variant_definition>::get_element(__int32) const;
template s_game_engine_ctf_variant_definition const & c_tag_block<s_game_engine_ctf_variant_definition>::operator[](__int32) const;
template s_game_engine_infection_variant_definition * c_tag_block<s_game_engine_infection_variant_definition>::get_element(__int32) const;
template s_game_engine_infection_variant_definition const & c_tag_block<s_game_engine_infection_variant_definition>::operator[](__int32) const;
template s_game_engine_juggernaut_variant_definition * c_tag_block<s_game_engine_juggernaut_variant_definition>::get_element(__int32) const;
template s_game_engine_juggernaut_variant_definition const & c_tag_block<s_game_engine_juggernaut_variant_definition>::operator[](__int32) const;
template s_game_engine_king_variant_definition * c_tag_block<s_game_engine_king_variant_definition>::get_element(__int32) const;
template s_game_engine_king_variant_definition const & c_tag_block<s_game_engine_king_variant_definition>::operator[](__int32) const;
template s_game_engine_oddball_variant_definition * c_tag_block<s_game_engine_oddball_variant_definition>::get_element(__int32) const;
template s_game_engine_oddball_variant_definition const & c_tag_block<s_game_engine_oddball_variant_definition>::operator[](__int32) const;
template s_game_engine_slayer_variant_definition * c_tag_block<s_game_engine_slayer_variant_definition>::get_element(__int32) const;
template s_game_engine_slayer_variant_definition const & c_tag_block<s_game_engine_slayer_variant_definition>::operator[](__int32) const;
template s_game_engine_territories_variant_definition * c_tag_block<s_game_engine_territories_variant_definition>::get_element(__int32) const;
template s_game_engine_territories_variant_definition const & c_tag_block<s_game_engine_territories_variant_definition>::operator[](__int32) const;
template s_game_engine_vip_variant_definition * c_tag_block<s_game_engine_vip_variant_definition>::get_element(__int32) const;
template s_game_engine_vip_variant_definition const & c_tag_block<s_game_engine_vip_variant_definition>::operator[](__int32) const;
template s_hs_global & c_tag_block<s_hs_global>::operator[](__int32);
template s_hs_global * c_tag_block<s_hs_global>::get_element(__int32) const;
template void Pointer::Write<bool>(bool const) const;

/* ---------- explicit instantiations */
template Pointer::operator wchar_t *() const;
template __int32 & Pointer::Read<int>() const;
template unsigned __int32 & Pointer::Read<unsigned int>() const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { std::map<std::string,bool> layerBlurMap; }
