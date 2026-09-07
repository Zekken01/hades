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
//	<lambda_1>(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &);
//private:
//	std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &mapNames; // 0x0
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

void GetMapNameList(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &mapNames);
bool CommandGameLogLevel(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameLogTypes(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameLogFilter(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameInfo(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameExit(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameRestart(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameForceLoad(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameShowUI(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
unsigned __int32 GetFileSize(std::basic_ifstream<char,std::char_traits<char> > &file);
__int32 GetMapId(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapName);
bool LoadDefaultMapVariant(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapName, unsigned char *out);
__int32 GetUiGameMode();
void SetOwnedContentData(s_owned_content_item *content_item, bool built_in, char const *file_path);
void SaveMapVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path);
void SaveGameVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path);
bool CommandGameLoadMap(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool LoadGameVariant(std::basic_ifstream<char,std::char_traits<char> > &file, unsigned char *out);
__int32 FindDefaultGameVariant(s_game_engine_settings_definition const *wezr, e_game_engine_type type, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name);
bool LoadDefaultGameVariant(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, unsigned char *out);
bool CommandAnnoucementViewedDate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameType(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameStart(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameStartCountdown(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameStop(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameLeave(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameEnd(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameEndRound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameVersion(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandListMaps(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandShowScreen(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandPlayUiSound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandPlaySound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandPlayLoopingSound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandStopLoopingSound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameTakeScreenshot(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandExecuteScenarioScript(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandExecutePrintScript(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGetTagAddress(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandDisableScreenEffect(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableLanguageUpdated(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool ShowTickrate();
bool CommandShowTickrate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandGameUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandFullScreenBlurLayer(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandFontPackage(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSetMainMenuMod(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSetCampaignMod(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSetFirefightMod(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSetMultiplayerMod(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandCloseStartMenu(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandShowLocalServersUI(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandShowModBrowser(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandShowServerModBrowser(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandShowModInfo(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandVersionCompat(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const GameTypeExtensions[9]; // 0x12454D80
	extern std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,bool,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,bool> > > layerBlurMap; // 0x12454D70
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	extern ModuleGame* _sub_1098BDE0(Modules::ModuleGame *const);
	ModuleGame::ModuleGame() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x1098BDE0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleGame@Modules@@QAE@XZ");
		// Modules::ModuleGame *const this;
		todo("implement");
		_sub_1098BDE0(this);
	}
}

/* ---------- private code */

_extern void _sub_1099C4E0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &);
void GetMapNameList(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &mapNames) // 0x1099C4E0
{
	// `anonymous-namespace'::GetMapNameList
	// static ...; // 0x1099C578
	// static ...; // 0x1099C56C
	// static ...; // 0x1099C564
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &mapNames;
	// GetMapNameList::__l2::<lambda_1> addMap;
	todo("implement");
	_sub_1099C4E0(mapNames);
}

_extern bool _sub_10997E90(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameLogLevel(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10997E90
{
	// `anonymous-namespace'::CommandGameLogLevel
	// static ...; // 0x109980E8
	// static ...; // 0x109980E0
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	{
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &<range>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<begin>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<end>$L0;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > arg;
		}
	}
	todo("implement");
	bool __result = _sub_10997E90(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109981A0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameLogTypes(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109981A0
{
	// `anonymous-namespace'::CommandGameLogTypes
	// static ...; // 0x1099842C
	// static ...; // 0x10998424
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// unsigned __int32 types;
	{
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &<range>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<begin>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<end>$L0;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > arg;
		}
	}
	todo("implement");
	bool __result = _sub_109981A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109974D0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameLogFilter(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109974D0
{
	// `anonymous-namespace'::CommandGameLogFilter
	// static ...; // 0x10997C96
	// static ...; // 0x10997C92
	// static ...; // 0x10997C8B
	// static ...; // 0x10997C84
	// static ...; // 0x10997C48
	// static ...; // 0x10997C40
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	{
		// bool remove;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > str;
		// bool exists;
		// bool exclude;
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > *vect;
		{
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > pos;
		}
	}
	{
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > filter;
		}
	}
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L1;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L1;
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L1;
		{
		}
	}
	todo("implement");
	bool __result = _sub_109974D0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10994D20(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameInfo(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10994D20
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
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > Build;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > FlashVersion;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > DevKitVersion;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > ArgList;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > SystemID;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > SessionID;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > Xnaddr;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > LocalSecureKey;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > Xnkid;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > MapName;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > DevKitName;
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > VariantName;
	todo("implement");
	bool __result = _sub_10994D20(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10993FF0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameExit(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10993FF0
{
	// `anonymous-namespace'::CommandGameExit
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_10993FF0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109984F0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameRestart(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109984F0
{
	// `anonymous-namespace'::CommandGameRestart
	// static ...; // 0x1099875B
	// static ...; // 0x10998758
	// static ...; // 0x10998734
	// static ...; // 0x1099872C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool ret;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > str;
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

_extern bool _sub_10994020(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameForceLoad(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10994020
{
	// `anonymous-namespace'::CommandGameForceLoad
	// static ...; // 0x10994A76
	// static ...; // 0x10994A6E
	// static ...; // 0x10994A68
	// static ...; // 0x10994A38
	// static ...; // 0x10994A30
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// char const *gameTypeStr;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapName;
	// s_level_datum level;
	// e_game_mode gameMode;
	// e_game_engine_type gameType;
	{
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > mapNames;
		{
			// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &map;
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

_extern bool _sub_10998800(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameShowUI(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10998800
{
	// `anonymous-namespace'::CommandGameShowUI
	// static ...; // 0x10998BD4
	// static ...; // 0x10998BBC
	// static ...; // 0x10998BB4
// $LN26:
// $LN28:
// $LN27:
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// __int32 dialogArg1;
	// unsigned __int32 dialogParentStringId;
	// unsigned __int32 dialogStringId;
	// __int32 dialogFlags;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > str_arg;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > str_arg;
		}
	}
	todo("implement");
	bool __result = _sub_10998800(Arguments, returnInfo);
	return __result;
}

_extern unsigned __int32 _sub_1099C310(std::basic_ifstream<char,std::char_traits<char> > &);
unsigned __int32 GetFileSize(std::basic_ifstream<char,std::char_traits<char> > &file) // 0x1099C310
{
	// `anonymous-namespace'::GetFileSize
	// static ...; // 0x1099C3CC
	// static ...; // 0x1099C3C0
	// static ...; // 0x1099C3B8
	// std::basic_ifstream<char,std::char_traits<char> > &file;
	// std::fpos<_Mbstatet> originalPos;
	// unsigned __int32 size;
	todo("implement");
	unsigned __int32 __result = _sub_1099C310(file);
	return __result;
}

_extern __int32 _sub_1099C410(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
__int32 GetMapId(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapName) // 0x1099C410
{
	// `anonymous-namespace'::GetMapId
	// static ...; // 0x1099C4A8
	// static ...; // 0x1099C49C
	// static ...; // 0x1099C494
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapName;
	// s_level_datum level;
	todo("implement");
	__int32 __result = _sub_1099C410(mapName);
	return __result;
}

_extern bool _sub_1099CE50(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned char *);
bool LoadDefaultMapVariant(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapName, unsigned char *out) // 0x1099CE50
{
	// `anonymous-namespace'::LoadDefaultMapVariant
	// unsigned char *out;
	// __int32 secondMapId;
	// __int32 firstMapId;
	// __int32 mapId;
	todo("implement");
	bool __result = _sub_1099CE50(mapName, out);
	return __result;
}

_extern __int32 _sub_1099C5E0();
__int32 GetUiGameMode() // 0x1099C5E0
{
	// `anonymous-namespace'::GetUiGameMode
	// procedure flags: nofpo
	// __int32 (*GetUiGameModeImpl)();
	// function call : __int32 (*)()
	todo("implement");
	__int32 __result = _sub_1099C5E0();
	return __result;
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

_extern void _sub_1099D8D0(unsigned char const *, bool, char const *);
void SaveMapVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path) // 0x1099D8D0
{
	// `anonymous-namespace'::SaveMapVariantToPreferences
	// char const *file_path;
	// unsigned __int32 variantOffset;
	// unsigned char *savedVariant;
	// s_owned_content_item *owned_content_item;
	todo("implement");
	_sub_1099D8D0(data, built_in, file_path);
}

_extern void _sub_1099D830(unsigned char const *, bool, char const *);
void SaveGameVariantToPreferences(unsigned char const *data, bool built_in, char const *file_path) // 0x1099D830
{
	// `anonymous-namespace'::SaveGameVariantToPreferences
	// char const *file_path;
	// unsigned char *savedVariant;
	// s_owned_content_item *owned_content_item;
	todo("implement");
	_sub_1099D830(data, built_in, file_path);
}

_extern bool _sub_10996D90(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameLoadMap(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10996D90
{
	// `anonymous-namespace'::CommandGameLoadMap
	// static ...; // 0x10997345
	// static ...; // 0x10997335
	// static ...; // 0x1099732A
	// static ...; // 0x10997324
	// static ...; // 0x109972E8
	// static ...; // 0x109972E0
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// __int32 lobbyType;
	// unsigned char variantData[57488];
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapName;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > variantFileName;
	// std::basic_ifstream<char,std::char_traits<char> > mapVariant;
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

_extern bool _sub_1099CF20(std::basic_ifstream<char,std::char_traits<char> > &, unsigned char *);
bool LoadGameVariant(std::basic_ifstream<char,std::char_traits<char> > &file, unsigned char *out) // 0x1099CF20
{
	// `anonymous-namespace'::LoadGameVariant
	// static ...; // 0x1099CFE4
	// static ...; // 0x1099CFDC
	// std::basic_ifstream<char,std::char_traits<char> > &file;
	// unsigned char *out;
	// bool (*ParseGameVariant)(void *, unsigned char *, bool *);
	// unsigned char blfData[956];
	// __int32 const GameVariantBlfSize;
	// function call : bool (*)(void *, unsigned char *, bool *)
	todo("implement");
	bool __result = _sub_1099CF20(file, out);
	return __result;
}

_extern __int32 _sub_1099C080(s_game_engine_settings_definition const *, e_game_engine_type, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
__int32 FindDefaultGameVariant(s_game_engine_settings_definition const *wezr, e_game_engine_type type, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name) // 0x1099C080
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
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name;
	todo("implement");
	__int32 __result = _sub_1099C080(wezr, type, name);
	return __result;
}

_extern bool _sub_1099CD30(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned char *);
bool LoadDefaultGameVariant(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, unsigned char *out) // 0x1099CD30
{
	// `anonymous-namespace'::LoadDefaultGameVariant
	// unsigned char *out;
	// __int32 const VariantDataSize;
	// __int32 index;
	// bool (*LoadBuiltInGameVariant)(e_game_engine_type, __int32, unsigned char *);
	// s_game_engine_settings_definition const *wezr;
	// __int32 type;
	// function call : s_game_engine_settings_definition const *(*const)()
	// function call : bool (*)(e_game_engine_type, __int32, unsigned char *)
	todo("implement");
	bool __result = _sub_1099CD30(name, out);
	return __result;
}

_extern bool _sub_109931F0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandAnnoucementViewedDate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109931F0
{
	// `anonymous-namespace'::CommandAnnoucementViewedDate
	// static ...; // 0x109932F4
	// static ...; // 0x109932EC
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > date;
	}
	todo("implement");
	bool __result = _sub_109931F0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10999240(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameType(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10999240
{
	// `anonymous-namespace'::CommandGameType
	// static ...; // 0x109997A0
	// static ...; // 0x10999794
	// static ...; // 0x10999784
	// static ...; // 0x10999754
	// static ...; // 0x1099974C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// unsigned char variantData[612];
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > variantFileName;
	// std::basic_ifstream<char,std::char_traits<char> > gameVariant;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
	// bool (*LoadGameVariant)(unsigned char *);
	// bool built_in;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &<range>$L0[9];
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<begin>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<end>$L0;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &extension;
		}
	}
	// function call : bool (*)(unsigned char *)
	todo("implement");
	bool __result = _sub_10999240(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10998CE0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameStart(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10998CE0
{
	// `anonymous-namespace'::CommandGameStart
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Blam::Network::Session *session;
	todo("implement");
	bool __result = _sub_10998CE0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10998D80(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameStartCountdown(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10998D80
{
	// `anonymous-namespace'::CommandGameStartCountdown
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const user_interface_squad_start_countdown_timer)(long, long);
	// function call : bool (*const)(long, long)
	todo("implement");
	bool __result = _sub_10998D80(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10998E20(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameStop(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10998E20
{
	// `anonymous-namespace'::CommandGameStop
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Blam::Network::Session *session;
	todo("implement");
	bool __result = _sub_10998E20(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10996C80(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameLeave(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10996C80
{
	// `anonymous-namespace'::CommandGameLeave
	// static ...; // 0x10996D40
	// static ...; // 0x10996D38
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// void (*const c_network_session__leave_session_and_disconnect)(c_network_session *);
	// c_network_session *session;
	// function call : bool (*const)(c_network_session **)
	// function call : void (*const)(c_network_session *)
	todo("implement");
	bool __result = _sub_10996C80(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10993DE0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameEnd(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10993DE0
{
	// `anonymous-namespace'::CommandGameEnd
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Blam::Network::Session *session;
	{
		// Blam::Network::Session *session;
	}
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_10993DE0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10993F10(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameEndRound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10993F10
{
	// `anonymous-namespace'::CommandGameEndRound
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Blam::Network::Session *session;
	// function call : c_game_engine *(*const)()
	// function call : void (*const)(long, bool, long)
	todo("implement");
	bool __result = _sub_10993F10(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10999BD0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameVersion(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10999BD0
{
	// `anonymous-namespace'::CommandGameVersion
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_10999BD0(arguments, returnInfo);
	return __result;
}

_extern bool _sub_10999F30(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandListMaps(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10999F30
{
	// `anonymous-namespace'::CommandListMaps
	// static ...; // 0x1099A034
	// static ...; // 0x1099A02C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > mapNames;
	{
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &map;
		}
	}
	todo("implement");
	bool __result = _sub_10999F30(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099B0D0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandShowScreen(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099B0D0
{
	// `anonymous-namespace'::CommandShowScreen
	// static ...; // 0x1099B428
	// static ...; // 0x1099B423
	// static ...; // 0x1099B41C
	// static ...; // 0x1099B3EC
	// static ...; // 0x1099B3E4
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> doc;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > jsonArg;
	// __int32 pos;
	todo("implement");
	bool __result = _sub_1099B0D0(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A270(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPlayUiSound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099A270
{
	// `anonymous-namespace'::CommandPlayUiSound
	// static ...; // 0x1099A348
	// static ...; // 0x1099A340
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// char *endp;
	// long index;
	// function call : long (*const)(e_user_interface_sound, long)
	todo("implement");
	bool __result = _sub_1099A270(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A180(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPlaySound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099A180
{
	// `anonymous-namespace'::CommandPlaySound
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// long tag_index;
	// static void (*`CommandPlaySound'::`2'::Sound_PlaySoundEffect)(unsigned __int32, float); // 0x11353F84
	// function call : void (*)(unsigned __int32, float)
	todo("implement");
	bool __result = _sub_1099A180(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A090(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPlayLoopingSound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099A090
{
	// `anonymous-namespace'::CommandPlayLoopingSound
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// static void (*`CommandPlayLoopingSound'::`2'::Sound_LoopingSound_Start)(unsigned __int32, __int32, __int32, __int32, char); // 0x11353F88
	// long tag_index;
	// function call : void (*)(unsigned __int32, __int32, __int32, __int32, char)
	todo("implement");
	bool __result = _sub_1099A090(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099B7F0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandStopLoopingSound(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099B7F0
{
	// `anonymous-namespace'::CommandStopLoopingSound
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// static void (*`CommandStopLoopingSound'::`2'::Sound_LoopingSound_Stop)(unsigned __int32, __int32); // 0x11353F8C
	// long tag_index;
	// function call : void (*)(unsigned __int32, __int32)
	todo("implement");
	bool __result = _sub_1099B7F0(arguments, returnInfo);
	return __result;
}

_extern bool _sub_10998EC0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameTakeScreenshot(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10998EC0
{
	// `anonymous-namespace'::CommandGameTakeScreenshot
	// static ...; // 0x10999166
	// static ...; // 0x1099915B
	// static ...; // 0x10999150
	// static ...; // 0x10999120
	// static ...; // 0x10999118
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// wchar_t *(*TakeScreenshotImpl)();
	// wchar_t *path;
	// std::wstring_convert<std::codecvt_utf8<wchar_t,1114111,0>,wchar_t,std::allocator<wchar_t>,std::allocator<char> > wstring_to_string;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > screenshot_path;
	{
		// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
		// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	}
	// function call : wchar_t *(*)()
	// function call : wchar_t *(*)()
	todo("implement");
	bool __result = _sub_10998EC0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10993800(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandExecuteScenarioScript(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10993800
{
	// `anonymous-namespace'::CommandExecuteScenarioScript
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
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

_extern bool _sub_109936A0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandExecutePrintScript(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109936A0
{
	// `anonymous-namespace'::CommandExecutePrintScript
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
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

_extern bool _sub_10999C70(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGetTagAddress(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10999C70
{
	// `anonymous-namespace'::CommandGetTagAddress
	// static ...; // 0x10999E90
	// static ...; // 0x10999E88
// $LN10:
// $LN5:
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// void *(*GetTagAddressImpl)(__int32, unsigned __int32);
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// __int32 tagIndex;
	// void *address;
	// function call : void *(*)(__int32, unsigned __int32)
	todo("implement");
	bool __result = _sub_10999C70(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109933F0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandDisableScreenEffect(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109933F0
{
	// `anonymous-namespace'::CommandDisableScreenEffect
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
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

_extern bool _sub_1099DD90(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableLanguageUpdated(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099DD90
{
	// `anonymous-namespace'::VariableLanguageUpdated
	// static ...; // 0x1099E13C
	// static ...; // 0x1099E134
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,int> > > > it;
	// static std::unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,int,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,int> > > `VariableLanguageUpdated'::`2'::languageIds; // 0x12454E7C
	// static __int32 `VariableLanguageUpdated'::`2'::$TSS0; // 0x12454D7C
	todo("implement");
	bool __result = _sub_1099DD90(arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099DB70();
bool ShowTickrate() // 0x1099DB70
{
	// `anonymous-namespace'::ShowTickrate
	// procedure flags: nofpo
	// static ...; // 0x1099DC58
	// static ...; // 0x1099DC4C
	// static ...; // 0x1099DC44
	// Pointer Tickrate;
	todo("implement");
	bool __result = _sub_1099DB70();
	return __result;
}

_extern bool _sub_1099B650(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandShowTickrate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099B650
{
	// `anonymous-namespace'::CommandShowTickrate
	// static ...; // 0x1099B78C
	// static ...; // 0x1099B784
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	todo("implement");
	bool __result = _sub_1099B650(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10999910(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGameUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10999910
{
	// `anonymous-namespace'::CommandGameUpdate
	// static ...; // 0x10999B33
	// static ...; // 0x10999B2E
	// static ...; // 0x10999B28
	// static ...; // 0x10999AF8
	// static ...; // 0x10999AF0
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > args;
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

_extern bool _sub_10993A10(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandFullScreenBlurLayer(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10993A10
{
	// `anonymous-namespace'::CommandFullScreenBlurLayer
	// static ...; // 0x10993D00
	// static ...; // 0x10993CF5
	// static ...; // 0x10993CEC
	// static ...; // 0x10993CBC
	// static ...; // 0x10993CB4
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > layerName;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > toggle;
	// bool blurEnabled;
	{
		// std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,bool,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,bool> > > &<range>$L0;
		// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,bool> > > > <begin>$L0;
		// std::_Default_sentinel <end>$L0;
		{
			// std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,bool> const &pair;
		}
	}
	todo("implement");
	bool __result = _sub_10993A10(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109939A0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandFontPackage(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109939A0
{
	// `anonymous-namespace'::CommandFontPackage
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109939A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A820(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetMainMenuMod(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099A820
{
	// `anonymous-namespace'::CommandSetMainMenuMod
	// static ...; // 0x1099AAEC
	// static ...; // 0x1099AAE4
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
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

_extern bool _sub_1099A3A0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetCampaignMod(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099A3A0
{
	// `anonymous-namespace'::CommandSetCampaignMod
	// static ...; // 0x1099A550
	// static ...; // 0x1099A538
	// static ...; // 0x1099A530
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const game_is_mainmenu)();
	// __int32 lobbyType;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > campaignPakName;
		// s_static_string<256> file_path;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099A3A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099A5E0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetFirefightMod(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099A5E0
{
	// `anonymous-namespace'::CommandSetFirefightMod
	// static ...; // 0x1099A790
	// static ...; // 0x1099A778
	// static ...; // 0x1099A770
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const game_is_mainmenu)();
	// __int32 lobbyType;
	{
		// s_static_string<256> file_path;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > FirefightPakName;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099A5E0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099ABC0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetMultiplayerMod(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099ABC0
{
	// `anonymous-namespace'::CommandSetMultiplayerMod
	// static ...; // 0x1099AD78
	// static ...; // 0x1099AD60
	// static ...; // 0x1099AD58
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const game_is_mainmenu)();
	// __int32 lobbyType;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > MultiplayerPakName;
		// s_static_string<256> file_path;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099ABC0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10993350(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandCloseStartMenu(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x10993350
{
	// `anonymous-namespace'::CommandCloseStartMenu
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// c_gui_screen_widget *screen;
	// function call : void (*const)(void *, __int32)
	todo("implement");
	bool __result = _sub_10993350(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099AE10(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandShowLocalServersUI(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099AE10
{
	// `anonymous-namespace'::CommandShowLocalServersUI
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const game_is_mainmenu)();
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099AE10(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099AE90(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandShowModBrowser(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099AE90
{
	// `anonymous-namespace'::CommandShowModBrowser
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const game_is_mainmenu)();
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099AE90(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099B510(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandShowServerModBrowser(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099B510
{
	// `anonymous-namespace'::CommandShowServerModBrowser
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const game_is_mainmenu)();
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1099B510(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099AFD0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandShowModInfo(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099AFD0
{
	// `anonymous-namespace'::CommandShowModInfo
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_1099AFD0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1099B8D0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandVersionCompat(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x1099B8D0
{
	// `anonymous-namespace'::CommandVersionCompat
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_1099B8D0(Arguments, returnInfo);
	return __result;
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
