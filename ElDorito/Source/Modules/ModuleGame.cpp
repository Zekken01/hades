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
	extern std::string const GameTypeExtensions[9]; // 0x12454D80
	extern std::map<std::string,bool> layerBlurMap; // 0x12454D70
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	extern ModuleGame* _sub_1098BDE0(Modules::ModuleGame *const);
	ModuleGame::ModuleGame() : ModuleBase(todo_result<std::string>()) // 0x1098BDE0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleGame@Modules@@QAE@XZ");
		// Modules::ModuleGame *const this;
		todo("implement");
		_sub_1098BDE0(this);
	}
}

/* ---------- private code */

_extern void _sub_1099C4E0(std::vector<std::string> &);
void GetMapNameList(std::vector<std::string> &mapNames) // 0x1099C4E0
{
	// `anonymous-namespace'::GetMapNameList
	// static ...; // 0x1099C578
	// static ...; // 0x1099C56C
	// static ...; // 0x1099C564
	// std::vector<std::string> &mapNames;
	// GetMapNameList::__l2::<lambda_1> addMap;
	todo("implement");
	_sub_1099C4E0(mapNames);
}

_extern bool _sub_10997E90(std::vector<std::string> const &, std::string &);
bool CommandGameLogLevel(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10997E90
{
	// `anonymous-namespace'::CommandGameLogLevel
	// static ...; // 0x109980E8
	// static ...; // 0x109980E0
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	{
		// std::vector<std::string> const &<range>$L0;
		// std::string const *<begin>$L0;
		// std::string const *<end>$L0;
		{
			// std::string arg;
		}
	}
	todo("implement");
	bool __result = _sub_10997E90(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109981A0(std::vector<std::string> const &, std::string &);
bool CommandGameLogTypes(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109981A0
{
	// `anonymous-namespace'::CommandGameLogTypes
	// static ...; // 0x1099842C
	// static ...; // 0x10998424
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// unsigned __int32 types;
	{
		// std::vector<std::string> const &<range>$L0;
		// std::string const *<begin>$L0;
		// std::string const *<end>$L0;
		{
			// std::string arg;
		}
	}
	todo("implement");
	bool __result = _sub_109981A0(Arguments, returnInfo);
	return __result;
}

bool CommandGameLogFilter(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109974D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameLogFilter@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandGameLogFilter
	// static ...; // 0x10997C96
	// static ...; // 0x10997C92
	// static ...; // 0x10997C8B
	// static ...; // 0x10997C84
	// static ...; // 0x10997C48
	// static ...; // 0x10997C40
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::stringstream ss;
		// bool remove;
		// std::string str;
		// bool exists;
		// bool exclude;
		// std::vector<std::string> *vect;
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::string> > > pos;
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
			// std::string filter;
		// std::string *<end>$L1;
		// std::string *<begin>$L1;
		// std::vector<std::string> &<range>$L1;

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

_extern bool _sub_10994D20(std::vector<std::string> const &, std::string &);
bool CommandGameInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10994D20
{
	// `anonymous-namespace'::CommandGameInfo
	// static ...; // 0x1099662B
	// static ...; // 0x1099661C
	// static ...; // 0x10996616
	// static ...; // 0x1099660F
	// static ...; // 0x10996609
	// static ...; // 0x10996600
	// static ...; // 0x109965F6
	// static ...; // 0x109965EB
	// static ...; // 0x109965DD
	// static ...; // 0x109965D0
	// static ...; // 0x109965C8
	// static ...; // 0x109965BC
	// static ...; // 0x10996520
	// static ...; // 0x10996518
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string Build;
	// std::string FlashVersion;
	// std::string DevKitVersion;
	// std::string ArgList;
	// std::string SystemID;
	// std::stringstream ss;
	// std::string SessionID;
	// std::string Xnaddr;
	// std::string LocalSecureKey;
	// std::string Xnkid;
	// std::string MapName;
	// std::string DevKitName;
	// std::wstring VariantName;
	todo("implement");
	bool __result = _sub_10994D20(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10993FF0(std::vector<std::string> const &, std::string &);
bool CommandGameExit(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993FF0
{
	// `anonymous-namespace'::CommandGameExit
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_10993FF0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109984F0(std::vector<std::string> const &, std::string &);
bool CommandGameRestart(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109984F0
{
	// `anonymous-namespace'::CommandGameRestart
	// static ...; // 0x1099875B
	// static ...; // 0x10998758
	// static ...; // 0x10998734
	// static ...; // 0x1099872C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool ret;
	// std::string str;
	// _PROCESS_INFORMATION pi;
	// _STARTUPINFOA si;
	// function call : char *()
	// function call : __int32 (char const *, char *, _SECURITY_ATTRIBUTES *, _SECURITY_ATTRIBUTES *, __int32, unsigned long, void *, char const *, _STARTUPINFOA *, _PROCESS_INFORMATION *)
	// function call : unsigned long ()
	// function call : __int32 (void *)
	// function call : __int32 (void *)
	todo("implement");
	bool __result = _sub_109984F0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10994020(std::vector<std::string> const &, std::string &);
bool CommandGameForceLoad(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10994020
{
	// `anonymous-namespace'::CommandGameForceLoad
	// static ...; // 0x10994A76
	// static ...; // 0x10994A6E
	// static ...; // 0x10994A68
	// static ...; // 0x10994A38
	// static ...; // 0x10994A30
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// char const *gameTypeStr;
	// std::stringstream ss;
	// std::string mapName;
	// s_level_datum level;
	// e_game_mode gameMode;
	// e_game_engine_type gameType;
	{
		// std::vector<std::string> mapNames;
		{
			// std::vector<std::string> &<range>$L0;
			// std::string *<begin>$L0;
			// std::string *<end>$L0;
			{
				// std::string const &map;
			}
		}
		{
			// long i;
		}
		{
		}
	}
	{
		// unsigned __int32 i;
	}
	{
	}
	todo("implement");
	bool __result = _sub_10994020(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10998800(std::vector<std::string> const &, std::string &);
bool CommandGameShowUI(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10998800
{
	// `anonymous-namespace'::CommandGameShowUI
	// static ...; // 0x10998BD4
	// static ...; // 0x10998BBC
	// static ...; // 0x10998BB4
// $LN26:
// $LN28:
// $LN27:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 dialogArg1;
	// unsigned __int32 dialogParentStringId;
	// unsigned __int32 dialogStringId;
	// __int32 dialogFlags;
	{
		// std::string str_arg;
		{
			// std::string str_arg;
		}
	}
	todo("implement");
	bool __result = _sub_10998800(Arguments, returnInfo);
	return __result;
}

unsigned __int32 GetFileSize(std::ifstream &file) // 0x1099C310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetFileSize@@YAIAAV?$basic_ifstream@DU?$char_traits@D@std@@@std@@@Z");
	// `anonymous-namespace'::GetFileSize
	// static ...; // 0x1099C3CC
	// static ...; // 0x1099C3C0
	// static ...; // 0x1099C3B8
	// std::ifstream &file;
	// std::fpos<_Mbstatet> originalPos;
	// unsigned __int32 size;

	auto originalPos = file.tellg();
	file.seekg(0, std::ios::end);
	auto size = static_cast<size_t>(file.tellg());
	file.seekg(originalPos);
	return size;
}

__int32 GetMapId(std::string const &mapName) // 0x1099C410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapId@@YAHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::GetMapId
	// static ...; // 0x1099C4A8
	// static ...; // 0x1099C49C
	// static ...; // 0x1099C494
	// std::string const &mapName;
	// s_level_datum level;

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
	// `anonymous-namespace'::LoadDefaultMapVariant
	// unsigned char *out;
	// __int32 secondMapId;
	// __int32 firstMapId;
	// __int32 mapId;

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
	// `anonymous-namespace'::GetUiGameMode
	// procedure flags: nofpo
	// __int32 (*GetUiGameModeImpl)();
	// function call : __int32 (*)()

	__int32 (__cdecl *GetUiGameModeImpl)() = (__int32(__cdecl *)())0x435640;

	return GetUiGameModeImpl();
}

_extern void _sub_1099D9B0(s_owned_content_item *, bool, char const *);
void SetOwnedContentData(s_owned_content_item *content_item, bool built_in, char const *file_path) // 0x1099D9B0
{
	// `anonymous-namespace'::SetOwnedContentData
	// char const *file_path;
	// c_controller_interface *(*const controller_get)(long);
	// s_player_identifier *(*const c_controller_interface__get_player_identifier)(void *, s_player_identifier *);
	// function call : c_controller_interface *(*const)(long)
	// function call : s_player_identifier *(*const)(void *, s_player_identifier *)
	todo("implement");
	_sub_1099D9B0(content_item, built_in, file_path);
}

void SaveMapVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path) // 0x1099D8D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SaveMapVariantToPreferences@@YAXPBE_NPBD@Z");
	// `anonymous-namespace'::SaveMapVariantToPreferences
	// char const *file_path;
	// unsigned __int32 variantOffset;
	// unsigned char *savedVariant;
	// s_owned_content_item *owned_content_item;

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
	// `anonymous-namespace'::SaveGameVariantToPreferences
	// char const *file_path;
	// unsigned char *savedVariant;
	// s_owned_content_item *owned_content_item;

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

_extern bool _sub_10996D90(std::vector<std::string> const &, std::string &);
bool CommandGameLoadMap(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10996D90
{
	// `anonymous-namespace'::CommandGameLoadMap
	// static ...; // 0x10997345
	// static ...; // 0x10997335
	// static ...; // 0x1099732A
	// static ...; // 0x10997324
	// static ...; // 0x109972E8
	// static ...; // 0x109972E0
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 lobbyType;
	// unsigned char variantData[57488];
	// std::string mapName;
	// std::string variantFileName;
	// std::ifstream mapVariant;
	// bool (*LoadMapVariant)(unsigned char *, void *);
	// bool built_in;
	{
		// s_level_datum level;
	}
	// function call : bool (*)(unsigned char *, void *)
	todo("implement");
	bool __result = _sub_10996D90(Arguments, returnInfo);
	return __result;
}

bool LoadGameVariant(std::ifstream &file, unsigned char *out) // 0x1099CF20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadGameVariant@@YA_NAAV?$basic_ifstream@DU?$char_traits@D@std@@@std@@PAE@Z");
	// `anonymous-namespace'::LoadGameVariant
	// static ...; // 0x1099CFE4
	// static ...; // 0x1099CFDC
	// std::ifstream &file;
	// unsigned char *out;
	// bool (*ParseGameVariant)(void *, unsigned char *, bool *);
	// unsigned char blfData[956];
	// __int32 const GameVariantBlfSize;
	// function call : bool (*)(void *, unsigned char *, bool *)

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

_extern __int32 _sub_1099C080(s_game_engine_settings_definition const *, e_game_engine_type, std::string const &);
__int32 FindDefaultGameVariant(s_game_engine_settings_definition const *wezr, e_game_engine_type type, std::string const &name) // 0x1099C080
{
	// `anonymous-namespace'::FindDefaultGameVariant
// $LN11:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// s_game_engine_settings_definition const *wezr;
	// e_game_engine_type type;
	// std::string const &name;
	todo("implement");
	__int32 __result = _sub_1099C080(wezr, type, name);
	return __result;
}

bool LoadDefaultGameVariant(std::string const &name, unsigned char *out) // 0x1099CD30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadDefaultGameVariant@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAE@Z");
	// `anonymous-namespace'::LoadDefaultGameVariant
	// unsigned char *out;
	// __int32 const VariantDataSize;
	// __int32 index;
	// bool (*LoadBuiltInGameVariant)(e_game_engine_type, __int32, unsigned char *);
	// s_game_engine_settings_definition const *wezr;
	// __int32 type;
	// function call : s_game_engine_settings_definition const *(*const)()
	// function call : bool (*)(e_game_engine_type, __int32, unsigned char *)

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

_extern bool _sub_109931F0(std::vector<std::string> const &, std::string &);
bool CommandAnnoucementViewedDate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109931F0
{
	// `anonymous-namespace'::CommandAnnoucementViewedDate
	// static ...; // 0x109932F4
	// static ...; // 0x109932EC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	{
		// std::string date;
	}
	todo("implement");
	bool __result = _sub_109931F0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10999240(std::vector<std::string> const &, std::string &);
bool CommandGameType(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10999240
{
	// `anonymous-namespace'::CommandGameType
	// static ...; // 0x109997A0
	// static ...; // 0x10999794
	// static ...; // 0x10999784
	// static ...; // 0x10999754
	// static ...; // 0x1099974C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// unsigned char variantData[612];
	// std::string variantFileName;
	// std::ifstream gameVariant;
	// std::string name;
	// bool (*LoadGameVariant)(unsigned char *);
	// bool built_in;
	{
		// std::string const &<range>$L0[9];
		// std::string const *<begin>$L0;
		// std::string const *<end>$L0;
		{
			// std::string const &extension;
		}
	}
	// function call : bool (*)(unsigned char *)
	todo("implement");
	bool __result = _sub_10999240(Arguments, returnInfo);
	return __result;
}

bool CommandGameStart(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10998CE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameStart@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandGameStart
	// std::string &returnInfo;
	// Blam::Network::Session *session;

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
	// `anonymous-namespace'::CommandGameStartCountdown
	// std::string &returnInfo;
	// bool (*const user_interface_squad_start_countdown_timer)(long, long);
	// function call : bool (*const)(long, long)

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
	// `anonymous-namespace'::CommandGameStop
	// std::string &returnInfo;
	// Blam::Network::Session *session;

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
	// `anonymous-namespace'::CommandGameLeave
	// static ...; // 0x10996D40
	// static ...; // 0x10996D38
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// void (*const c_network_session__leave_session_and_disconnect)(c_network_session *);
	// c_network_session *session;
	// function call : bool (*const)(c_network_session **)
	// function call : void (*const)(c_network_session *)

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

_extern bool _sub_10993DE0(std::vector<std::string> const &, std::string &);
bool CommandGameEnd(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993DE0
{
	// `anonymous-namespace'::CommandGameEnd
	// std::string &returnInfo;
	// Blam::Network::Session *session;
	{
		// Blam::Network::Session *session;
	}
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_10993DE0(Arguments, returnInfo);
	return __result;
}

bool CommandGameEndRound(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameEndRound@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandGameEndRound
	// std::string &returnInfo;
	// Blam::Network::Session *session;
	// function call : c_game_engine *(*const)()
	// function call : void (*const)(long, bool, long)

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
	// `anonymous-namespace'::CommandGameVersion
	// std::string &returnInfo;

	returnInfo = Utils::Version::GetVersionString();
	return true;
}

bool CommandListMaps(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x10999F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandListMaps@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandListMaps
	// static ...; // 0x1099A034
	// static ...; // 0x1099A02C
	// std::vector<std::string> const &arguments;
	// std::string &returnInfo;
	// std::vector<std::string> mapNames;
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
			// std::string const &map;

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
	// `anonymous-namespace'::CommandShowScreen
	// static ...; // 0x1099B428
	// static ...; // 0x1099B423
	// static ...; // 0x1099B41C
	// static ...; // 0x1099B3EC
	// static ...; // 0x1099B3E4
	// std::vector<std::string> const &arguments;
	// std::string &returnInfo;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> doc;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::string jsonArg;
	// __int32 pos;

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

_extern bool _sub_1099A270(std::vector<std::string> const &, std::string &);
bool CommandPlayUiSound(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099A270
{
	// `anonymous-namespace'::CommandPlayUiSound
	// static ...; // 0x1099A348
	// static ...; // 0x1099A340
	// std::vector<std::string> const &arguments;
	// std::string &returnInfo;
	// char *endp;
	// long index;
	// function call : long (*const)(e_user_interface_sound, long)
	todo("implement");
	bool __result = _sub_1099A270(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A180(std::vector<std::string> const &, std::string &);
bool CommandPlaySound(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099A180
{
	// `anonymous-namespace'::CommandPlaySound
	// std::string &returnInfo;
	// long tag_index;
	// static void (*`CommandPlaySound'::`2'::Sound_PlaySoundEffect)(unsigned __int32, float); // 0x11353F84
	// function call : void (*)(unsigned __int32, float)
	todo("implement");
	bool __result = _sub_1099A180(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A090(std::vector<std::string> const &, std::string &);
bool CommandPlayLoopingSound(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099A090
{
	// `anonymous-namespace'::CommandPlayLoopingSound
	// std::string &returnInfo;
	// static void (*`CommandPlayLoopingSound'::`2'::Sound_LoopingSound_Start)(unsigned __int32, __int32, __int32, __int32, char); // 0x11353F88
	// long tag_index;
	// function call : void (*)(unsigned __int32, __int32, __int32, __int32, char)
	todo("implement");
	bool __result = _sub_1099A090(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099B7F0(std::vector<std::string> const &, std::string &);
bool CommandStopLoopingSound(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099B7F0
{
	// `anonymous-namespace'::CommandStopLoopingSound
	// std::string &returnInfo;
	// static void (*`CommandStopLoopingSound'::`2'::Sound_LoopingSound_Stop)(unsigned __int32, __int32); // 0x11353F8C
	// long tag_index;
	// function call : void (*)(unsigned __int32, __int32)
	todo("implement");
	bool __result = _sub_1099B7F0(arguments, returnInfo);
	return __result;
}

bool CommandGameTakeScreenshot(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10998EC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameTakeScreenshot@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandGameTakeScreenshot
	// static ...; // 0x10999166
	// static ...; // 0x1099915B
	// static ...; // 0x10999150
	// static ...; // 0x10999120
	// static ...; // 0x10999118
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// wchar_t *(*TakeScreenshotImpl)();
	// wchar_t *path;
	// std::wstring_convert<std::codecvt_utf8<wchar_t,1114111,0>,wchar_t,std::allocator<wchar_t>,std::allocator<char> > wstring_to_string;
	// std::string screenshot_path;
		// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
		// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	// function call : wchar_t *(*)()
	// function call : wchar_t *(*)()

	wchar_t *(*TakeScreenshotImpl)() = (wchar_t *(*)())0x60f420;
	return TakeScreenshotImpl() != nullptr;

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

_extern bool _sub_10993800(std::vector<std::string> const &, std::string &);
bool CommandExecuteScenarioScript(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993800
{
	// `anonymous-namespace'::CommandExecuteScenarioScript
	// std::string &returnInfo;
	// s_scenario *scnr;
	{
		// __int32 i;
		{
			// s_hs_script const &script;
		}
	}
	// function call : long (*const)(short, e_hs_script_type, e_hs_script_type)
	todo("implement");
	bool __result = _sub_10993800(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109936A0(std::vector<std::string> const &, std::string &);
bool CommandExecutePrintScript(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109936A0
{
	// `anonymous-namespace'::CommandExecutePrintScript
	// std::string &returnInfo;
	// s_scenario *scnr;
	{
		// __int32 i;
		{
			// s_hs_global const &script;
			{
				// void *result;
			}
		}
	}
	todo("implement");
	bool __result = _sub_109936A0(Arguments, returnInfo);
	return __result;
}

bool CommandGetTagAddress(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10999C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGetTagAddress@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandGetTagAddress
	// static ...; // 0x10999E90
	// static ...; // 0x10999E88
// $LN10:
// $LN5:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// void *(*GetTagAddressImpl)(__int32, unsigned __int32);
	// std::stringstream ss;
	// __int32 tagIndex;
	// void *address;
	// function call : void *(*)(__int32, unsigned __int32)

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
	catch (std::invalid_argument)
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

_extern bool _sub_109933F0(std::vector<std::string> const &, std::string &);
bool CommandDisableScreenEffect(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109933F0
{
	// `anonymous-namespace'::CommandDisableScreenEffect
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 index;
	// s_scenario const *scnr;
	// s_area_screen_effect_definition *sefc;
	// __int32 value;
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_109933F0(Arguments, returnInfo);
	return __result;
}

bool VariableLanguageUpdated(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x1099DD90
{
	// `anonymous-namespace'::VariableLanguageUpdated
	// static ...; // 0x1099E13C
	// static ...; // 0x1099E134
	// std::vector<std::string> const &arguments;
	// std::string &returnInfo;
	// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,int> > > > it;
	// static std::unordered_map<std::string,int> `VariableLanguageUpdated'::`2'::languageIds; // 0x12454E7C
	// static __int32 `VariableLanguageUpdated'::`2'::$TSS0; // 0x12454D7C

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
	// `anonymous-namespace'::ShowTickrate
	// procedure flags: nofpo
	// static ...; // 0x1099DC58
	// static ...; // 0x1099DC4C
	// static ...; // 0x1099DC44
	// Pointer Tickrate;

	auto Tickrate = Pointer(0x22B47FC);
	Tickrate.Write(!Tickrate.Read<bool>());
	return Tickrate.Read<bool>();
}

bool CommandShowTickrate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099B650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandShowTickrate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandShowTickrate
	// static ...; // 0x1099B78C
	// static ...; // 0x1099B784
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::stringstream ss;

	std::stringstream ss;
	ss << "Tickrate: " << (ShowTickrate() ? "shown." : "hidden.");
	returnInfo = ss.str();
	return true;
}

_extern bool _sub_10999910(std::vector<std::string> const &, std::string &);
bool CommandGameUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10999910
{
	// `anonymous-namespace'::CommandGameUpdate
	// static ...; // 0x10999B33
	// static ...; // 0x10999B2E
	// static ...; // 0x10999B28
	// static ...; // 0x10999AF8
	// static ...; // 0x10999AF0
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::wstring args;
	// _PROCESS_INFORMATION pi;
	// _STARTUPINFOW si;
	{
		// unsigned long ret;
		{
			// char error[256];
		}
	}
	// function call : __int32 (wchar_t const *, wchar_t *, _SECURITY_ATTRIBUTES *, _SECURITY_ATTRIBUTES *, __int32, unsigned long, void *, wchar_t const *, _STARTUPINFOW *, _PROCESS_INFORMATION *)
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : __int32 (void *)
	// function call : __int32 (void *)
	todo("implement");
	bool __result = _sub_10999910(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10993A10(std::vector<std::string> const &, std::string &);
bool CommandFullScreenBlurLayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993A10
{
	// `anonymous-namespace'::CommandFullScreenBlurLayer
	// static ...; // 0x10993D00
	// static ...; // 0x10993CF5
	// static ...; // 0x10993CEC
	// static ...; // 0x10993CBC
	// static ...; // 0x10993CB4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string layerName;
	// std::string toggle;
	// bool blurEnabled;
	{
		// std::map<std::string,bool> &<range>$L0;
		// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,bool> > > > <begin>$L0;
		// std::_Default_sentinel <end>$L0;
		{
			// std::pair<std::string const ,bool> const &pair;
		}
	}
	todo("implement");
	bool __result = _sub_10993A10(Arguments, returnInfo);
	return __result;
}

bool CommandFontPackage(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109939A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandFontPackage@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandFontPackage
	// std::string &returnInfo;

	if (Arguments.size() < 1)
	{
		return false;
	}

	font_package_begin_load_package(Arguments[0].c_str());

	return true;
}

_extern bool _sub_1099A820(std::vector<std::string> const &, std::string &);
bool CommandSetMainMenuMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099A820
{
	// `anonymous-namespace'::CommandSetMainMenuMod
	// static ...; // 0x1099AAEC
	// static ...; // 0x1099AAE4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool (*const game_is_mainmenu)();
	// std::filesystem::path filename;
	// IMod const *currentMod;
	// void (*const main_menu_launch_force)();
	// function call : bool (*const)()
	// function call : IMod *(EModIndex) const
	// function call : char const *() const
	// function call : bool (*const)()
	// function call : void (*const)()
	todo("implement");
	bool __result = _sub_1099A820(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A3A0(std::vector<std::string> const &, std::string &);
bool CommandSetCampaignMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099A3A0
{
	// `anonymous-namespace'::CommandSetCampaignMod
	// static ...; // 0x1099A550
	// static ...; // 0x1099A538
	// static ...; // 0x1099A530
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool (*const game_is_mainmenu)();
	// __int32 lobbyType;
	{
		// std::string campaignPakName;
		// s_static_string<256> file_path;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099A3A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A5E0(std::vector<std::string> const &, std::string &);
bool CommandSetFirefightMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099A5E0
{
	// `anonymous-namespace'::CommandSetFirefightMod
	// static ...; // 0x1099A790
	// static ...; // 0x1099A778
	// static ...; // 0x1099A770
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool (*const game_is_mainmenu)();
	// __int32 lobbyType;
	{
		// s_static_string<256> file_path;
		// std::string FirefightPakName;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099A5E0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099ABC0(std::vector<std::string> const &, std::string &);
bool CommandSetMultiplayerMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099ABC0
{
	// `anonymous-namespace'::CommandSetMultiplayerMod
	// static ...; // 0x1099AD78
	// static ...; // 0x1099AD60
	// static ...; // 0x1099AD58
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool (*const game_is_mainmenu)();
	// __int32 lobbyType;
	{
		// std::string MultiplayerPakName;
		// s_static_string<256> file_path;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099ABC0(Arguments, returnInfo);
	return __result;
}

bool CommandCloseStartMenu(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10993350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCloseStartMenu@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCloseStartMenu
	// std::string &returnInfo;
	// c_gui_screen_widget *screen;
	// function call : void (*const)(void *, __int32)

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
	// `anonymous-namespace'::CommandShowLocalServersUI
	// std::string &returnInfo;
	// bool (*const game_is_mainmenu)();
	// function call : bool (*const)()

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

_extern bool _sub_1099AE90(std::vector<std::string> const &, std::string &);
bool CommandShowModBrowser(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099AE90
{
	// `anonymous-namespace'::CommandShowModBrowser
	// std::string &returnInfo;
	// bool (*const game_is_mainmenu)();
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099AE90(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099B510(std::vector<std::string> const &, std::string &);
bool CommandShowServerModBrowser(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099B510
{
	// `anonymous-namespace'::CommandShowServerModBrowser
	// std::string &returnInfo;
	// bool (*const game_is_mainmenu)();
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099B510(Arguments, returnInfo);
	return __result;
}

bool CommandShowModInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099AFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandShowModInfo@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandShowModInfo
	// std::string &returnInfo;

	Web::Ui::ScreenLayer::Show("mod_info", "{}");
	return true;
}

bool CommandVersionCompat(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1099B8D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandVersionCompat@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandVersionCompat
	// std::string &returnInfo;

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
