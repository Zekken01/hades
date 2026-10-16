/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_results.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleVoIP.hpp"  // hades: added for 0x10C68880
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/map_variant_loader.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patch.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
#include "Server/ServerChat.hpp"
#undef GetObject  // hades: the original resolves rapidjson's GetObject members, so the Windows macro must not rename them
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
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/WebFileReadHandler.hpp"

#include "Web/Ui/WebAssetService.hpp"  // hades: added for 0x10C64770  // hades: added for 0x10C64770

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <cef_base.h>
#include <cef_devtools_message_observer.h>
#include <cef_extension_handler.h>
#include <cef_resource_handler.h>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_stream_resource_handler.h>

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
#include <fstream>
#include <functional>
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
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct c_game_engine_base_variant;
struct c_game_variant;
struct end;
struct s_game_options;
struct s_game_results_player_statistics;
struct s_game_results_player_vs_player_statistics;
struct s_game_results_player_weapon_statistics;
struct s_level_datum;
struct s_map_variant;
namespace Blam
{
	namespace Network
	{
		struct NetworkAddress;
		struct PlayerSession;
		struct Session;
	}
}
namespace Modules
{
	class CommandMap;
	struct Command;
}

namespace Utils {}
using namespace ::Utils;
namespace base {}
using namespace ::base;
namespace base
{
	namespace cef_subtle {}
	using namespace base::cef_subtle;
	namespace cef_internal {}
	using namespace base::cef_internal;
	namespace internal {}
	using namespace base::internal;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Chat {}
	using namespace Server::Chat;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
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
		namespace WebDialog {}
		using namespace Web::Ui::WebDialog;
		namespace WebScoreboard {}
		using namespace Web::Ui::WebScoreboard;
		namespace WebForge {}
		using namespace Web::Ui::WebForge;
		namespace WebChat {}
		using namespace Web::Ui::WebChat;
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
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
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

namespace Web { namespace Ui { namespace WebScoreboard { void Hide(); } } }  // hades: added for 0x10C666F0
namespace Web { namespace Ui { namespace ScreenLayer { void Show(bool show); } } }  // hades: added for 0x10C67820
namespace Patches { namespace Ui { void ShowLanBrowser(); } }  // hades: added for 0x10C67870
namespace Web { namespace Ui { namespace WebForge { Web::Browser::Bridge::QueryError ProcessAction(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); } } }  // hades: added for 0x10C63EF0

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const network_life_cycle_session_get_campaign_difficulty = reinterpret_cast<long (*)()>(0x435020);
	static auto const network_squad_session_get_campaign_insertion_point = reinterpret_cast<short (*)()>(0x435080);
	static auto const network_squad_session_get_campaign_metagame_scoring = reinterpret_cast<bool (*)()>(0x4350F0);
}

extern char const *g_player_medal_names[58]; extern char const *g_damage_reporting_type_names[64];  // hades: added for 0x10C67B10  // hades: added for 0x10C67B10
#include "Player/PlayerInfo.hpp"  // hades: added for 0x10C67B10  // hades: added for 0x10C67B10
#include "Blam/game/game_results.hpp"  // hades: added for 0x10C67B10  // hades: added for 0x10C67B10
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10C65CD0  // hades: added for 0x10C67B10

extern s_game_options *(*game_options_get)();  // hades: added for 0x10C65180, 0x10C63FE0  // hades: added for 0x10C65180
extern bool (*const levels_try_and_get_campaign_map)(long, s_level_datum *);  // hades: added for 0x10C65180  // hades: added for 0x10C65180
extern bool levels_find_level_by_map_id(long map_id, s_level_datum *out_level);  // hades: added for 0x10C65180  // hades: added for 0x10C65180

namespace PersistentMemory { extern bool PlayerIsVoipMuted(std::string uid); extern void AddMutedVoipPlayer(std::string name, std::string uid); extern bool RemoveMutedVoipPlayer(std::string uid); extern void Save(); }  // hades: added for 0x10C69180  // hades: added for 0x10C69180

extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x10C66C50  // hades: added for 0x10C66C50

#include "Modules/ModulePlayer.hpp"  // hades: added for 0x10C69820  // hades: added for 0x10C69820
namespace Patches { namespace Ui { void ToggleSpeakingPlayerName(std::string name, bool speaking); } }  // hades: added for 0x10C69820, 0x10C689A0  // hades: added for 0x10C69820

namespace PersistentMemory { bool PlayerIsVoipMuted(std::string uid); }  // hades: added for 0x10C68DC0  // hades: added for 0x10C68DC0

namespace Web { namespace Ui { namespace WebDialog { void SubmitDialogResult(__int32 dialogId, std::string const &result); } } }  // hades: added for 0x10C685A0  // hades: added for 0x10C685A0

namespace Web { namespace Ui { namespace WebScoreboard { void Show(bool locked, bool pregame, bool animate); } } }  // hades: added for 0x10C678B0  // hades: added for 0x10C678B0

namespace Web { namespace Ui { namespace WebChat { void SetChatBoxVisible(bool visible); } } }  // hades: added for 0x10C63250  // hades: added for 0x10C63250

namespace Web { namespace Ui { namespace WebScoreboard { std::string getScoreboard(); } } }  // hades: added for 0x10C66620  // hades: added for 0x10C66620

namespace Utils { namespace Version { std::string GetVersionString(); } }  // hades: added for 0x10C687E0  // hades: added for 0x10C687E0

namespace Web { namespace Ui { namespace WebForge { std::string BuildForgePaletteJSON(); } } }  // hades: added for 0x10C63F40  // hades: added for 0x10C63F40

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				extern Web::Browser::Bridge::QueryError OnShow(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnHide(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnScreenState(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnCommand(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnSetVariables(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &args, std::string *result);
				extern Web::Browser::Bridge::QueryError OnGetAssetUrl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnPing(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnCaptureInput(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnVersion(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnMapVariantInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnScoreboard(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnShowScoreboard(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnScoreboardHide(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnGameVariantInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnCommands(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnSendChat(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnChatBoxOpened(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnSessionInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnStats(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnVoIPSpeakingChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnVoIPConnectedChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnVoIPPlayerVoipLevelChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnVoIPPlayerSpeakingChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnVoIPPlayerVoipJoined(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnIsMapLoading(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnForgeAction(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnForgePalette(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnShowLan(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnPlayerReportInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
				extern Web::Browser::Bridge::QueryError OnSubmitDialogResult(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
			}
		}
	}
}

static void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern unsigned short PingId; // 0x1247EC8C
	extern bool PingHandlerRegistered; // 0x1247EC8E
}
using namespace hades_file_local;
/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnShow(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C67820
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnShow@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;

					Web::Ui::ScreenLayer::Show(true);
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnHide(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C64FA0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnHide@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;

					Web::Ui::ScreenLayer::Show(false);
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnScreenState(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C66730
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnScreenState@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C668F0
					// static ...; // 0x10C668D8
					// static ...; // 0x10C668D0
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > screenIdMember;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > stateMember;

					auto screenIdMember = p_Args.FindMember("screenId");
					if (screenIdMember == p_Args.MemberEnd() || !screenIdMember->value.IsString())
					{
						*p_Result = "Bad query: A \"screenId\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					auto stateMember = p_Args.FindMember("state");
					if (stateMember == p_Args.MemberEnd() || !stateMember->value.IsInt())
					{
						*p_Result = "Bad query: A \"state\" argument is required and must be a int";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Web::Ui::ScreenLayer::NotifyScreenStateChanged(screenIdMember->value.GetString(), (Web::Ui::ScreenLayer::EScreenState)stateMember->value.GetInt());
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnCommand(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C63390
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnCommand@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C63530
					// static ...; // 0x10C63518
					// static ...; // 0x10C63510
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_CommandValue;
					// bool s_IsInternal;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_InternalValue;

					auto s_CommandValue = p_Args.FindMember("command");
					if (s_CommandValue == p_Args.MemberEnd() || !s_CommandValue->value.IsString())
					{
						*p_Result = "Bad query: A \"command\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					auto s_InternalValue = p_Args.FindMember("internal");
					bool s_IsInternal = s_InternalValue != p_Args.MemberEnd() && s_InternalValue->value.IsBool() && s_InternalValue->value.GetBool();
					if (!Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommandWithStatus(s_CommandValue->value.GetString(), true, p_Result))
						return Web::Browser::Bridge::QueryError_CommandFailed;
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnSetVariables(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &args, std::string *result) // 0x10C67130
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnSetVariables@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C67697
					// static ...; // 0x10C67690
					// static ...; // 0x10C6768B
					// static ...; // 0x10C67688
					// static ...; // 0x10C6767F
					// static ...; // 0x10C67664
					// static ...; // 0x10C6765B
					// static ...; // 0x10C67654
					// static ...; // 0x10C675E8
					// static ...; // 0x10C675E0
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &args;
					// std::string *result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > saveMember;
					// Modules::CommandMap &commandMap;
					// bool save;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > variablesMember;
					// std::vector<std::pair<std::string,enum VariableSetReturnValue> > failed;
					// rapidjson::GenericObject<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &jsonVariableMap;
						// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
							// VariableSetReturnValue retValue;
						// char const *const kVariableReturnValueErrors[1];
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuff;
							// std::vector<std::pair<std::string,enum VariableSetReturnValue> > &<range>$L0;
							// std::pair<std::string,enum VariableSetReturnValue> *<begin>$L0;
							// std::pair<std::string,enum VariableSetReturnValue> *<end>$L0;
								// std::pair<std::string,enum VariableSetReturnValue> const &pair;

					Modules::CommandMap &commandMap = Utils::Singleton<Modules::CommandMap>::Instance();
					bool save = false;
					auto variablesMember = args.FindMember("variables");
					if (variablesMember == args.MemberEnd() || !variablesMember->value.IsObject())
					{
						*result = "Bad query: A \"variables\" argument is required and must be an object";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					auto saveMember = args.FindMember("save");
					if (saveMember != args.MemberEnd())
					{
						if (!saveMember->value.IsBool())
						{
							*result = "Bad query: A \"save\" argument must be a boolean";
							return Web::Browser::Bridge::QueryError_BadQuery;
						}
						save = saveMember->value.GetBool();
					}
					std::vector<std::pair<std::string,enum VariableSetReturnValue> > failed;
					auto const &jsonVariableMap = variablesMember->value.GetObject();
					for (auto it = jsonVariableMap.begin(); it != jsonVariableMap.MemberEnd(); ++it)
					{
						if (!it->name.IsString() || !it->value.IsString())
						{
							*result = "Bad query: A \"variables\" argument must be an object consisting of only string keys/value pairs";
							return Web::Browser::Bridge::QueryError_BadQuery;
						}
						VariableSetReturnValue retValue = commandMap.SetVariable(it->name.GetString(), it->value.GetString(), true);
						if (retValue != eVariableSetReturnValueSuccess)
							failed.emplace_back(it->name.GetString(), retValue);
					}
					if (save)
						commandMap.ExecuteCommand("writeconfig", false);
					if (!failed.empty())
					{
						char const *const kVariableReturnValueErrors[] = { "Success" "Error" "OutOfRange" "InvalidArgument" };
						rapidjson::StringBuffer jsonBuff;
						rapidjson::Writer<rapidjson::StringBuffer> writer(jsonBuff);
						writer.StartObject();
						for (auto const &pair : failed)
						{
							writer.Key(pair.first.c_str());
							writer.String(kVariableReturnValueErrors[pair.second]);
						}
						writer.EndObject();
						*result = jsonBuff.GetString();
						return Web::Browser::Bridge::QueryError_CommandFailed;
					}
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnGetAssetUrl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C64770
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnGetAssetUrl@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C64DE8
					// static ...; // 0x10C64DDE
					// static ...; // 0x10C64DCE
					// static ...; // 0x10C64DC9
					// static ...; // 0x10C64DC5
					// static ...; // 0x10C64DBB
					// static ...; // 0x10C64DA4
					// static ...; // 0x10C64DA0
					// static ...; // 0x10C64D9C
					// static ...; // 0x10C64D24
					// static ...; // 0x10C64D1C
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > fileTypesMember;
					// std::string path;
					// std::vector<std::string_view> fileTypes;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > pathMember;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > searchBaseAssetsMember;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > pakMember;
					// bool searchBaseAssets;
					// std::string pak;
						// rapidjson::GenericArray<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L0;
						// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const *<begin>$L0;
						// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const *<end>$L0;
							// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &val;
						// std::string url;

					auto pathMember = p_Args.FindMember("path");
					if (pathMember == p_Args.MemberEnd() || !pathMember->value.IsString())
					{
						*p_Result = "Bad query: A \"path\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					std::string path = pathMember->value.GetString();
					std::vector<std::string_view> fileTypes;
					auto fileTypesMember = p_Args.FindMember("fileTypes");
					if (fileTypesMember != p_Args.MemberEnd())
					{
						if (!fileTypesMember->value.IsArray())
						{
							*p_Result = "Bad query: \"fileTypes\" argument must be an array of fileTypes e.g [\"jpg\", \"png\"]";
							return Web::Browser::Bridge::QueryError_BadQuery;
						}
						for (auto const &val : fileTypesMember->value.GetArray())
							fileTypes.push_back(val.GetString());
					}
					std::string pak = "";
					auto pakMember = p_Args.FindMember("pak");
					if (pakMember != p_Args.MemberEnd())
					{
						if (!pakMember->value.IsString())
						{
							*p_Result = "Bad query: \"pak\" must be a string";
							return Web::Browser::Bridge::QueryError_BadQuery;
						}
						pak = pakMember->value.GetString();
					}
					bool searchBaseAssets = true;
					auto searchBaseAssetsMember = p_Args.FindMember("searchBaseAssets");
					if (searchBaseAssetsMember != p_Args.MemberEnd())
					{
						if (!searchBaseAssetsMember->value.IsBool())
						{
							*p_Result = "Bad query: \"searchBaseAssets\" must be a boolean";
							return Web::Browser::Bridge::QueryError_BadQuery;
						}
						searchBaseAssets = searchBaseAssetsMember->value.GetBool();
					}
					if (!pak.empty())
					{
						std::string url = Web::Ui::AssetService::FindAssetInModVfs(pakMember->value.GetString(), path, fileTypes);
						if (!url.empty())
						{
							*p_Result = std::move(url);
							return Web::Browser::Bridge::QueryError_Ok;
						}
					}
					if (searchBaseAssets)
					{
						std::string url = Web::Ui::AssetService::FindAssetInBaseDir(path, fileTypes);
						if (!url.empty())
						{
							*p_Result = std::move(url);
							return Web::Browser::Bridge::QueryError_Ok;
						}
					}
					*p_Result = "";
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0s_map_variant@@QAE@ABU0@@Z"); no body to assert in
_inline s_map_variant::s_map_variant(s_map_variant const &__that) = default; // 0x10C62AC0

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnPing(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C65960
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnPing@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C65C08
					// static ...; // 0x10C65BFC
					// static ...; // 0x10C65BD8
					// static ...; // 0x10C65BD0
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_AddressValue;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_port;
					// Blam::Network::Session *session;
					// Blam::Network::NetworkAddress blamAddress;

					auto s_AddressValue = p_Args.FindMember("address");
					auto s_port = p_Args.FindMember("port");
					if (s_AddressValue == p_Args.MemberEnd() || !s_AddressValue->value.IsString() || s_port == p_Args.MemberEnd() || !s_port->value.IsInt())
					{
						*p_Result = "Bad query: The \"address\" argument must be a string and the \"port\" argument must be an int";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Blam::Network::NetworkAddress blamAddress;
					if (!Blam::Network::NetworkAddress::Parse(s_AddressValue->value.GetString(), (unsigned short)s_port->value.GetInt(), &blamAddress))
					{
						*p_Result = "Invalid argument: The \"address\" argument is not a valid IP address.";
						return Web::Browser::Bridge::QueryError_InvalidArgument;
					}
					if (!PingHandlerRegistered)
					{
						PingId = Patches::Network::OnPong(PongReceived);
						PingHandlerRegistered = true;
					}
					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					if (!session || !session->Gateway->Ping(blamAddress, PingId))
					{
						*p_Result = "Network error: Failed to send ping";
						return Web::Browser::Bridge::QueryError_NetworkError;
					}
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnCaptureInput(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C63080
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnCaptureInput@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C631C8
					// static ...; // 0x10C631B0
					// static ...; // 0x10C631A8
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// bool capturePointer;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_CaptureValue;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_CapturePointerValue;

					auto s_CaptureValue = p_Args.FindMember("capture");
					auto s_CapturePointerValue = p_Args.FindMember("capturePointer");
					bool capturePointer = false;
					if (s_CaptureValue == p_Args.MemberEnd() || !s_CaptureValue->value.IsBool())
					{
						*p_Result = "Bad query: A \"capture\" argument is required and must be a boolean";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					if (s_CapturePointerValue != p_Args.MemberEnd() && s_CapturePointerValue->value.IsBool())
						capturePointer = s_CapturePointerValue->value.GetBool();
					Web::Ui::ScreenLayer::CaptureInput(s_CaptureValue->value.GetBool(), capturePointer);
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnVersion(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C687E0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnVersion@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;

					*p_Result = Utils::Version::GetVersionString();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnMapVariantInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C65180
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnMapVariantInfo@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C657C1
					// static ...; // 0x10C657BA
					// static ...; // 0x10C657B3
					// static ...; // 0x10C657A9
					// static ...; // 0x10C6579E
					// static ...; // 0x10C65798
					// static ...; // 0x10C65792
					// static ...; // 0x10C6578B
					// static ...; // 0x10C65784
					// static ...; // 0x10C6570C
					// static ...; // 0x10C65704
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// __int32 lobbyType;
					// Blam::Network::Session *session;
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
						// char const *description;
						// char const *author;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
						// unsigned char *mapVariant;
						// s_level_datum map_level;
						// s_map_variant map;
						// std::string name;
						// unsigned __int32 mapId;
						// bool (*const network_squad_session_get_map)(long *, long *);
						// long campaignId;
						// s_level_datum level;
						// long mapId;
					// function call : s_game_options *(*)()
					// function call : bool (*const)(long *, long *)
					// function call : bool (*const)(long, s_level_datum *)

					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					if (!session || !session->IsEstablished())
					{
						*p_Result = "Not available: A game session is not active";
						return Web::Browser::Bridge::QueryError_NotAvailable;
					}
					__int32 lobbyType = Blam::Network::GetLobbyType();
					if (lobbyType == 2 || lobbyType == 3)
					{
						unsigned char *mapVariant = reinterpret_cast<unsigned char *>(session->Parameters.MapVariant.Get());
						if (!mapVariant)
						{
							*p_Result = "Not available: Map variant data is not available";
							return Web::Browser::Bridge::QueryError_NotAvailable;
						}
						s_map_variant map = static_cast<s_map_variant const &>(game_options_get()->map_variant);
						std::string name = Utils::String::ThinString(reinterpret_cast<wchar_t *>(mapVariant + 0x8));
						char const *description = reinterpret_cast<char const *>(mapVariant + 0x28);
						char const *author = reinterpret_cast<char const *>(mapVariant + 0xA8);
						unsigned __int32 mapId = *reinterpret_cast<unsigned __int32 *>(mapVariant + 0x100);
						rapidjson::StringBuffer buffer;
						rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
						writer.StartObject();
						writer.Key("name");
						writer.String(name.c_str());
						writer.Key("description");
						writer.String(description);
						writer.Key("author");
						writer.String(author);
						writer.Key("mapId");
						writer.Int64(mapId);
						writer.Key("map_path");
						s_level_datum map_level;
						if (levels_find_level_by_map_id(mapId, &map_level))
							writer.String(map_level.file_path);
						else
							writer.String("");
						writer.EndObject();
						*p_Result = buffer.GetString();
						return Web::Browser::Bridge::QueryError_Ok;
					}
					else if (lobbyType == 0)
					{
						bool (*const network_squad_session_get_map)(long *, long *) = reinterpret_cast<bool (*)(long *, long *)>(0x4354D0);
						long campaignId;
						long mapId;
						if (!network_squad_session_get_map(&campaignId, &mapId))
						{
							*p_Result = "Not available: Campaign map id is not available";
							return Web::Browser::Bridge::QueryError_NotAvailable;
						}
						s_level_datum level;
						if (!levels_try_and_get_campaign_map(mapId, &level))
						{
							*p_Result = "Not available: Campaign level datum is not available";
							return Web::Browser::Bridge::QueryError_NotAvailable;
						}
						rapidjson::StringBuffer buffer;
						rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
						writer.StartObject();
						writer.Key("mapId");
						writer.Int64(level.map_id);
						writer.Key("map_image");
						writer.String(level.image_file_path);
						writer.Key("name");
						writer.String(Utils::String::ThinString(level.name).c_str());
						writer.Key("map_path");
						writer.String(level.file_path);
						writer.Key("description");
						writer.String(Utils::String::ThinString(level.description).c_str());
						writer.EndObject();
						*p_Result = buffer.GetString();
						return Web::Browser::Bridge::QueryError_Ok;
					}
					else
					{
						*p_Result = "Not available: Map variant data is not available";
						return Web::Browser::Bridge::QueryError_NotAvailable;
					}
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnScoreboard(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C66620
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnScoreboard@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					// Blam::Network::Session *session;

					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					if (!session || !session->IsEstablished())
					{
						*p_Result = "Cannot get scoreboard data when there is not an active session.";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					*p_Result = Web::Ui::WebScoreboard::getScoreboard();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnShowScoreboard(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C678B0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnShowScoreboard@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C67A88
					// static ...; // 0x10C67A80
					// static ...; // 0x10C67A5C
					// static ...; // 0x10C67A54
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > animate;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > locked;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > pregame;

					auto locked = p_Args.FindMember("locked");
					auto pregame = p_Args.FindMember("preGame");
					auto animate = p_Args.FindMember("animate");
					if (locked == p_Args.MemberEnd() || !locked->value.IsBool() || animate == p_Args.MemberEnd() || !animate->value.IsBool() || pregame == p_Args.MemberEnd() || !pregame->value.IsBool())
					{
						*p_Result = "Bad query: arguments must be booleans";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Web::Ui::WebScoreboard::Show(locked->value.GetBool(), pregame->value.GetBool(), animate->value.GetBool());
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnScoreboardHide(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C666F0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnScoreboardHide@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;

					Web::Ui::WebScoreboard::Hide();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnGameVariantInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C63FE0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnGameVariantInfo@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C645BC
					// static ...; // 0x10C645B5
					// static ...; // 0x10C645AE
					// static ...; // 0x10C645A7
					// static ...; // 0x10C645A0
					// static ...; // 0x10C64564
					// static ...; // 0x10C6455C
				// $LN16:
				// $LN15:
				// $LN14:
				// $LN13:
				// $LN12:
				// $LN11:
				// $LN10:
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// __int32 lobbyType;
					// Blam::Network::Session *session;
						// bool teams;
						// c_game_engine_base_variant *base_variant;
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
						// __int32 scoreToWin;
						// char *description;
						// char *author;
						// unsigned char *rawGameVariant;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
						// unsigned char rounds;
						// c_game_variant *gameVariant;
						// std::string name;
						// unsigned char timeLimit;
						// e_game_engine_type mode;
						// s_game_options *game;
					// function call : s_game_options *(*)()
					// function call : long (*const)()
					// function call : short (*const)()
					// function call : bool (*const)()

					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					if (!session || !session->IsEstablished())
					{
						*p_Result = "Not available: A game session is not active";
						return Web::Browser::Bridge::QueryError_NotAvailable;
					}
					__int32 lobbyType = Blam::Network::GetLobbyType();
					if (lobbyType == 2 || lobbyType == 3)
					{
						c_game_variant *gameVariant = session->Parameters.GameVariant.Get();
						if (!gameVariant)
						{
							*p_Result = "Not available: Game variant data is not available";
							return Web::Browser::Bridge::QueryError_NotAvailable;
						}
						e_game_engine_type mode = gameVariant->game_engine_type;
						c_game_engine_base_variant *base_variant = gameVariant->get_base_variant();
						std::string name = Utils::String::ThinString(base_variant->metadata.name);
						char *description = base_variant->metadata.description;
						char *author = base_variant->metadata.author;
						bool teams = base_variant->miscellaneous_options.teams_enabled();
						unsigned char timeLimit = base_variant->miscellaneous_options.time_limit_in_minutes;
						unsigned char rounds = base_variant->miscellaneous_options.round_count;
						__int32 scoreToWin = -1;
						unsigned char *rawGameVariant = reinterpret_cast<unsigned char *>(gameVariant);
						switch ((e_game_engine_type)gameVariant->game_engine_type)
						{
						case _game_engine_type_slayer:
							scoreToWin = *reinterpret_cast<short *>(rawGameVariant + 0x1D4);
							break;
						case _game_engine_type_oddball:
							scoreToWin = *reinterpret_cast<short *>(rawGameVariant + 0x1D8);
							break;
						case _game_engine_type_koth:
							scoreToWin = *reinterpret_cast<short *>(rawGameVariant + 0x1D8);
							break;
						case _game_engine_type_ctf:
							scoreToWin = *reinterpret_cast<short *>(rawGameVariant + 0x1DC);
							break;
						case _game_engine_type_assault:
							scoreToWin = *reinterpret_cast<short *>(rawGameVariant + 0x1DC);
							break;
						case _game_engine_type_juggernaut:
							scoreToWin = *reinterpret_cast<short *>(rawGameVariant + 0x1D4);
							break;
						case _game_engine_type_vip:
							scoreToWin = *reinterpret_cast<short *>(rawGameVariant + 0x1D4);
							break;
						}
						rapidjson::StringBuffer buffer;
						rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
						writer.StartObject();
						writer.Key("mode");
						writer.Int(mode);
						writer.Key("name");
						writer.String(name.c_str());
						writer.Key("description");
						writer.String(description);
						writer.Key("author");
						writer.String(author);
						writer.Key("teams");
						writer.Bool(teams);
						writer.Key("timeLimit");
						writer.Int(timeLimit);
						writer.Key("rounds");
						writer.Int(rounds);
						writer.Key("scoreToWin");
						writer.Int(scoreToWin);
						writer.EndObject();
						*p_Result = buffer.GetString();
						return Web::Browser::Bridge::QueryError_Ok;
					}
					else if (lobbyType == 0)
					{
						s_game_options *game = game_options_get();
						if (!game)
						{
							*p_Result = "Not available: Game variant data is not available";
							return Web::Browser::Bridge::QueryError_NotAvailable;
						}
						rapidjson::StringBuffer buffer;
						rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
						writer.StartObject();
						writer.Key("difficulty");
						writer.Int(eldorado::network_life_cycle_session_get_campaign_difficulty());
						writer.Key("insertionPoint");
						writer.Int(eldorado::network_squad_session_get_campaign_insertion_point());
						writer.Key("metagameScoring");
						writer.Int(eldorado::network_squad_session_get_campaign_metagame_scoring());
						writer.EndObject();
						*p_Result = buffer.GetString();
						return Web::Browser::Bridge::QueryError_Ok;
					}
					else
					{
						*p_Result = "Not available: Game variant data is not available";
						return Web::Browser::Bridge::QueryError_NotAvailable;
					}
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnCommands(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C635C0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnCommands@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C63CFB
					// static ...; // 0x10C63CF4
					// static ...; // 0x10C63CE9
					// static ...; // 0x10C63CE0
					// static ...; // 0x10C63CB0
					// static ...; // 0x10C63CA8
				// $LN13:
				// $LN12:
				// $LN11:
				// $LN10:
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
					// Modules::CommandMap const &commandMap;
						// std::deque<Modules::Command> const &<range>$L0;
						// std::_Deque_unchecked_const_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
						// std::_Deque_unchecked_const_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
							// Modules::Command const &command;
								// std::string const *<end>$L1;
								// std::string const *<begin>$L1;
								// std::vector<std::string> const &<range>$L1;
									// std::string const &arg;

					Modules::CommandMap const &commandMap = Utils::Singleton<Modules::CommandMap>::Instance();
					rapidjson::StringBuffer buffer;
					rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
					writer.StartArray();
					for (auto const &command : commandMap.Commands)
					{
						writer.StartObject();
						writer.Key("type");
						writer.Int(command.Type);
						writer.Key("module");
						writer.String(command.ModuleName.c_str());
						writer.Key("name");
						writer.String(command.Name.c_str());
						writer.Key("shortName");
						writer.String(command.ShortName.c_str());
						writer.Key("description");
						writer.String(command.Description.c_str());
						switch (command.Type)
						{
						case Modules::eCommandTypeVariableInt:
							writer.Key("value");
							writer.Int(command.ValueInt);
							writer.Key("defaultValue");
							writer.Int(command.DefaultValueInt);
							writer.Key("minValue");
							writer.Int(command.ValueIntMin);
							writer.Key("maxValue");
							writer.Int(command.ValueIntMax);
							break;
						case Modules::eCommandTypeVariableInt64:
							writer.Key("value");
							writer.Int64(command.ValueInt64);
							writer.Key("defaultValue");
							writer.Int64(command.DefaultValueInt64);
							writer.Key("minValue");
							writer.Int64(command.ValueInt64Min);
							writer.Key("maxValue");
							writer.Int64(command.ValueInt64Max);
							break;
						case Modules::eCommandTypeVariableFloat:
							writer.Key("value");
							writer.Double(command.ValueFloat);
							writer.Key("defaultValue");
							writer.Double(command.DefaultValueFloat);
							writer.Key("minValue");
							writer.Double(command.ValueFloatMin);
							writer.Key("maxValue");
							writer.Double(command.ValueFloatMax);
							break;
						case Modules::eCommandTypeVariableString:
							writer.Key("value");
							writer.String(command.ValueString.c_str());
							writer.Key("defaultValue");
							writer.String(command.DefaultValueString.c_str());
							writer.Key("minValue");
							writer.Null();
							writer.Key("maxValue");
							writer.Null();
							break;
						default:
							writer.Key("value");
							writer.Null();
							writer.Key("defaultValue");
							writer.Null();
							writer.Key("minValue");
							writer.Null();
							writer.Key("maxValue");
							writer.Null();
							break;
						}
						writer.Key("replicated");
						writer.Bool((command.Flags & eCommandFlagsReplicated) != 0);
						writer.Key("archived");
						writer.Bool((command.Flags & eCommandFlagsArchived) != 0);
						writer.Key("hidden");
						writer.Bool((command.Flags & eCommandFlagsHidden) != 0);
						writer.Key("hostOnly");
						writer.Bool((command.Flags & eCommandFlagsHostOnly) != 0);
						writer.Key("hideValue");
						writer.Bool((command.Flags & eCommandFlagsOmitValueInList) != 0);
						writer.Key("internal");
						writer.Bool((command.Flags & eCommandFlagsInternal) != 0);
						writer.Key("arguments");
						writer.StartArray();
						for (auto const &arg : command.CommandArgs)
							writer.String(arg.c_str());
						writer.EndArray();
						writer.EndObject();
					}
					writer.EndArray();
					*p_Result = buffer.GetString();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnSendChat(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C66990
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnSendChat@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C66BB0
					// static ...; // 0x10C66B98
					// static ...; // 0x10C66B90
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > teamChat;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > message;

					auto message = p_Args.FindMember("message");
					auto teamChat = p_Args.FindMember("teamChat");
					if (message == p_Args.MemberEnd() || !message->value.IsString())
					{
						*p_Result = "Bad query: A \"message\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					if (teamChat == p_Args.MemberEnd() || !teamChat->value.IsBool())
					{
						*p_Result = "Bad query: A \"teamChat\" argument is required and must be a boolean";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					if (teamChat->value.GetBool())
						*p_Result = Server::Chat::SendTeamMessage(message->value.GetString());
					else
						*p_Result = Server::Chat::SendGlobalMessage(message->value.GetString());
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnChatBoxOpened(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C63250
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnChatBoxOpened@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C63334
					// static ...; // 0x10C6332C
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > opened;

					auto opened = p_Args.FindMember("opened");
					if (opened == p_Args.MemberEnd() || !opened->value.IsBool())
					{
						*p_Result = "Bad query: A \"opened\" argument is required and must be a boolean";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					if (opened->value.GetBool())
						Web::Ui::WebChat::SetChatBoxVisible(true);
					else
						Web::Ui::WebChat::SetChatBoxVisible(false);
					*p_Result = true;
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnSessionInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C66C50
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnSessionInfo@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C67020
					// static ...; // 0x10C6701C
					// static ...; // 0x10C66FF8
					// static ...; // 0x10C66FF0
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
					// Blam::Network::Session *session;
						// char uid[17];

					rapidjson::StringBuffer buffer;
					rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
					writer.StartObject();
					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					if (!session || !session->IsEstablished())
					{
						writer.Key("established");
						writer.Bool(false);
						writer.Key("hasTeams");
						writer.Bool(false);
						writer.Key("isHost");
						writer.Bool(false);
						writer.Key("playerInfo");
						writer.StartObject();
						writer.Key("Name");
						writer.String("");
						writer.Key("Uid");
						writer.String("");
						writer.EndObject();
					}
					else
					{
						writer.Key("established");
						writer.Bool(true);
						writer.Key("hasTeams");
						writer.Bool(session->HasTeams());
						writer.Key("isHost");
						writer.Bool(session->IsHost());
						writer.Key("playerInfo");
						writer.StartObject();
						writer.Key("Name");
						writer.String(Utils::String::ThinString(session->MembershipInfo.GetLocalPlayerSession().Properties.host.player_name).c_str());
						writer.Key("Uid");
						char uid[17];
						player_format_uid(uid, session->MembershipInfo.GetLocalPlayerSession().Properties.host.player_uid);
						writer.String(uid);
						writer.EndObject();
					}
					writer.Key("mapName");
					writer.String((char *)Pointer(0x22AB018)(0x1A4, 1));
					writer.EndObject();
					*p_Result = buffer.GetString();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnStats(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C67B10
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnStats@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C68372
					// static ...; // 0x10C6836B
					// static ...; // 0x10C68364
					// static ...; // 0x10C68362
					// static ...; // 0x10C68360
					// static ...; // 0x10C6835C
					// static ...; // 0x10C68308
					// static ...; // 0x10C68300
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// __int32 playerIdx;
					// Blam::Network::Session *session;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > name;
						// Blam::Network::PlayerSession player;
							// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
							// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
							// s_game_results_player_statistics *player_stats;
							// s_game_results_player_vs_player_statistics *player_vs_player_stats;
								// __int32 i;
									// Blam::Network::PlayerSession p;
								// __int32 medal;
								// __int32 weapon;
									// s_game_results_player_weapon_statistics wep;

					auto name = p_Args.FindMember("playerName");
					if (name == p_Args.MemberEnd() || !name->value.IsString())
					{
						*p_Result = "Bad query: A \"playerName\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					if (!session || !session->IsEstablished())
					{
						*p_Result = "Cannot get stat data when there is not an active session.";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					__int32 playerIdx = session->MembershipInfo.FindFirstPlayer();
					while (playerIdx != -1)
					{
						Blam::Network::PlayerSession player = session->MembershipInfo.PlayerSessions[playerIdx];
						if (strcmp(Utils::String::ThinString(player.Properties.host.player_name).c_str(), name->value.GetString()) == 0)
						{
							rapidjson::StringBuffer buffer;
							rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
							s_game_results_player_statistics *player_stats = game_results_get_player_stats(playerIdx);
							s_game_results_player_vs_player_statistics *player_vs_player_stats = game_results_get_player_vs_player_stats(playerIdx);
							writer.StartObject();
							writer.Key("playerrank");
							if (Player::CPlayersInfo::IsAvailable())
								writer.Int(Player::CPlayersInfo::GetRank(playerIdx));
							else
								writer.Int(-1);
							writer.Key("playerskill");
							if (Player::CPlayersInfo::IsAvailable())
								writer.Int(Player::CPlayersInfo::GetSkill(playerIdx));
							else
								writer.Int(-1);
							writer.Key("playerkilledplayer");
							writer.StartArray();
							{
								for (__int32 i = 0; i < 16; i++)
								{
									if (player_vs_player_stats->stats_against_each_player[i].kills > 0)
									{
										Blam::Network::PlayerSession p = session->MembershipInfo.PlayerSessions[i];
										writer.StartObject();
										writer.Key("PlayerName");
										writer.String(Utils::String::ThinString(p.Properties.host.player_name).c_str());
										writer.Key("Kills");
										writer.Int(player_vs_player_stats->stats_against_each_player[i].kills);
										writer.EndObject();
									}
								}
							}
							writer.EndArray();
							writer.Key("playerkilledby");
							writer.StartArray();
							{
								for (__int32 i = 0; i < 16; i++)
								{
									if (player_vs_player_stats->stats_against_each_player[i].killed_by > 0)
									{
										Blam::Network::PlayerSession p = session->MembershipInfo.PlayerSessions[i];
										writer.StartObject();
										writer.Key("PlayerName");
										writer.String(Utils::String::ThinString(p.Properties.host.player_name).c_str());
										writer.Key("Kills");
										writer.Int(player_vs_player_stats->stats_against_each_player[i].killed_by);
										writer.EndObject();
									}
								}
							}
							writer.EndArray();
							writer.Key("medals");
							writer.StartObject();
							for (__int32 medal = 0; medal < 58; medal++)
							{
								writer.Key(g_player_medal_names[medal]);
								writer.Int(player_stats->medals[medal].earned);
							}
							writer.EndObject();
							writer.Key("weapons");
							writer.StartObject();
							for (__int32 weapon = 0; weapon < 64; weapon++)
							{
								writer.Key(g_damage_reporting_type_names[weapon]);
								writer.StartObject();
								s_game_results_player_weapon_statistics wep = player_stats->weapon_stats[weapon];
								writer.Key("BetrayalsWith");
								writer.Int(wep.betrayals_with);
								writer.Key("HeadshotsWith");
								writer.Int(wep.headshots_with);
								writer.Key("KilledBy");
								writer.Int(wep.killed_by);
								writer.Key("Kills");
								writer.Int(wep.kills);
								writer.Key("SuicidesWith");
								writer.Int(wep.suicides_with);
								writer.EndObject();
							}
							writer.EndObject();
							writer.EndObject();
							*p_Result = buffer.GetString();
							return Web::Browser::Bridge::QueryError_Ok;
						}
						playerIdx = session->MembershipInfo.FindNextPlayer(playerIdx);
					}
					*p_Result = "Could not find player.";
					return Web::Browser::Bridge::QueryError_BadQuery;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnVoIPSpeakingChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C69820
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnVoIPSpeakingChanged@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C69A28
					// static ...; // 0x10C69A20
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// __int32 player_index;
					// Blam::Network::Session *session;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > value;

					auto value = p_Args.FindMember("value");
					if (value == p_Args.MemberEnd() || !value->value.IsBool())
					{
						*p_Result = "Bad query : A \"value\" argument is required and must be a bool";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Utils::Singleton<Modules::ModuleVoIP>::Instance().voiceDetected = value->value.GetBool();
					__int32 player_index = 0;
					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					player_index = session->MembershipInfo.GetPeerPlayer(session->MembershipInfo.LocalPeerIndex);
					if (player_index != -1)
					{
						if (value->value.GetBool())
						{
							Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpeaking |= 1 << player_index;
							Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpoke |= 1 << player_index;
						}
						else
						{
							Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpeaking &= ~(1 << player_index);
						}
					}
					if (Utils::Singleton<Modules::ModuleVoIP>::Instance().VarSpeakingPlayerOnHUD->ValueInt == 1)
						Patches::Ui::ToggleSpeakingPlayerName(Utils::Singleton<Modules::ModulePlayer>::Instance().VarPlayerName->ValueString, value->value.GetBool());
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnVoIPConnectedChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C68880
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnVoIPConnectedChanged@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C68950
					// static ...; // 0x10C68948
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > value;

					auto value = p_Args.FindMember("value");
					if (value == p_Args.MemberEnd() || !value->value.IsBool())
					{
						*p_Result = "Bad query : A \"value\" argument is required and must be a bool";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Modules::ModuleVoIP::Instance().voipConnected = value->value.GetBool();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnVoIPPlayerVoipLevelChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C69180
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnVoIPPlayerVoipLevelChanged@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C696B8
					// static ...; // 0x10C696AE
					// static ...; // 0x10C696A0
					// static ...; // 0x10C69670
					// static ...; // 0x10C69668
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > currentVolume;
					// __int32 player_index;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > uid;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > peerLevel;
					// Blam::Network::Session *session;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > name;
						// double volume;

					auto name = p_Args.FindMember("name");
					auto uid = p_Args.FindMember("uid");
					auto peerLevel = p_Args.FindMember("peerLevel");
					auto currentVolume = p_Args.FindMember("currentVolume");
					if (name == p_Args.MemberEnd() || !name->value.IsString())
					{
						*p_Result = "Bad query : A \"name\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					else if (uid == p_Args.MemberEnd() || !uid->value.IsString())
					{
						*p_Result = "Bad query : A \"uid\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					else if (peerLevel == p_Args.MemberEnd() || !peerLevel->value.IsNumber())
					{
						*p_Result = "Bad query : A \"peerLevel\" argument is required and must be a number";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					else if (currentVolume == p_Args.MemberEnd() || !currentVolume->value.IsNumber())
					{
						*p_Result = "Bad query : A \"currentVolume\" argument is required and must be a number";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					__int32 player_index = 0;
					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					player_index = session->MembershipInfo.FindPlayerByName(name->value.GetString());
					if (player_index != -1)
					{
						if (peerLevel->value.GetDouble() == 0)
						{
							if (!PersistentMemory::PlayerIsVoipMuted(uid->value.GetString()))
							{
								PersistentMemory::AddMutedVoipPlayer(name->value.GetString(), uid->value.GetString());
								PersistentMemory::Save();
							}
							Utils::Singleton<Modules::ModuleVoIP>::Instance().playersMuted |= 1 << player_index;
						}
						else
						{
							if (PersistentMemory::PlayerIsVoipMuted(uid->value.GetString()))
							{
								PersistentMemory::RemoveMutedVoipPlayer(uid->value.GetString());
								PersistentMemory::Save();
							}
							Utils::Singleton<Modules::ModuleVoIP>::Instance().playersMuted &= ~(1 << player_index);
							double volume = currentVolume->value.GetDouble();
							if (volume < -15.0 && volume > -75.0)
							{
								Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpeaking |= 1 << player_index;
								Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpoke |= 1 << player_index;
							}
							else
								Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpeaking &= ~(1 << player_index);
						}
					}
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnVoIPPlayerSpeakingChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C689A0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnVoIPPlayerSpeakingChanged@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C68CD8
					// static ...; // 0x10C68CC0
					// static ...; // 0x10C68CB8
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// __int32 player_index;
					// Blam::Network::Session *session;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > name;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > value;

					auto name = p_Args.FindMember("name");
					auto value = p_Args.FindMember("value");
					if (name == p_Args.MemberEnd() || !name->value.IsString())
					{
						*p_Result = "Bad query : A \"name\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					else if (value == p_Args.MemberEnd() || !value->value.IsBool())
					{
						*p_Result = "Bad query : A \"value\" argument is required and must be a bool";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					__int32 player_index = 0;
					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					player_index = session->MembershipInfo.FindPlayerByName(name->value.GetString());
					if (player_index != -1)
					{
						if (value->value.GetBool())
						{
							Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpeaking |= 1 << player_index;
							Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpoke |= 1 << player_index;
						}
						else
						{
							Utils::Singleton<Modules::ModuleVoIP>::Instance().playersSpeaking &= ~(1 << player_index);
						}
					}
					if (Utils::Singleton<Modules::ModuleVoIP>::Instance().VarSpeakingPlayerOnHUD->ValueInt == 1)
						Patches::Ui::ToggleSpeakingPlayerName(name->value.GetString(), value->value.GetBool());
					else if (!value->value.GetBool())
						Patches::Ui::ToggleSpeakingPlayerName(name->value.GetString(), value->value.GetBool());
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnVoIPPlayerVoipJoined(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C68DC0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnVoIPPlayerVoipJoined@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C690B2
					// static ...; // 0x10C690A7
					// static ...; // 0x10C6909C
					// static ...; // 0x10C6906C
					// static ...; // 0x10C69064
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > uid;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > name;
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;

					auto name = p_Args.FindMember("name");
					auto uid = p_Args.FindMember("uid");
					if (name == p_Args.MemberEnd() || !name->value.IsString())
					{
						*p_Result = "Bad query : A \"name\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					else if (uid == p_Args.MemberEnd() || !uid->value.IsString())
					{
						*p_Result = "Bad query : A \"uid\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					if (PersistentMemory::PlayerIsVoipMuted(uid->value.GetString()))
					{
						rapidjson::StringBuffer jsonBuffer;
						rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
						jsonWriter.StartObject();
						jsonWriter.Key("name");
						jsonWriter.String(name->value.GetString());
						jsonWriter.Key("uid");
						jsonWriter.String(uid->value.GetString());
						jsonWriter.Key("muted");
						jsonWriter.Bool(true);
						jsonWriter.EndObject();
						Web::Ui::ScreenLayer::Notify("mute-voip-player", jsonBuffer.GetString(), true);
					}
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnIsMapLoading(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C64FF0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnIsMapLoading@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C6511C
					// static ...; // 0x10C65104
					// static ...; // 0x10C650FC
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
					// static bool (*IsMapLoading)(); // 0x11355190
					// function call : bool (*)()

					static auto IsMapLoading = reinterpret_cast<bool (*)()>(0x5670E0);
					rapidjson::StringBuffer buffer;
					rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
					writer.StartObject();
					writer.Key("loading");
					writer.Bool(IsMapLoading());
					writer.EndObject();
					*p_Result = buffer.GetString();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnForgeAction(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C63EF0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnForgeAction@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;

					Web::Ui::WebForge::ProcessAction(p_Args, p_Result);
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnForgePalette(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C63F40
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnForgePalette@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;

					*p_Result = Web::Ui::WebForge::BuildForgePaletteJSON();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnShowLan(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C67870
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnShowLan@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;

					Patches::Ui::ShowLanBrowser();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnPlayerReportInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C65CD0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnPlayerReportInfo@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C6641A
					// static ...; // 0x10C66410
					// static ...; // 0x10C66404
					// static ...; // 0x10C663FD
					// static ...; // 0x10C663F6
					// static ...; // 0x10C663E8
					// static ...; // 0x10C66394
					// static ...; // 0x10C6638C
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// char offenderUid[17];
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
					// char senderUid[17];
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
					// Blam::Network::PlayerSession &offenderPlayerSession;
					// __int32 offenderPlayerIndex;
					// Blam::Network::PlayerSession senderPlayerSession;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > networkPlayerIndex;
					// Blam::Network::Session *const session;
						// Blam::Network::NetworkAddress serverAddress;

					auto networkPlayerIndex = p_Args.FindMember("playerIndex");
					if (networkPlayerIndex == p_Args.MemberEnd() || !networkPlayerIndex->value.IsInt())
					{
						*p_Result = "Bad query : A \"playerIndex\" argument is required and must be a number";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Blam::Network::Session *const session = Blam::Network::GetActiveSession();
					if (!session || !session->IsEstablished())
					{
						*p_Result = "Session not established";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					__int32 offenderPlayerIndex = networkPlayerIndex->value.GetInt();
					if (offenderPlayerIndex == -1)
					{
						*p_Result = "Player not found";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Blam::Network::PlayerSession senderPlayerSession = session->MembershipInfo.GetLocalPlayerSession();
					char senderUid[17];
					player_format_uid(senderUid, senderPlayerSession.Properties.host.player_uid);
					Blam::Network::PlayerSession &offenderPlayerSession = session->MembershipInfo.PlayerSessions[offenderPlayerIndex];
					char offenderUid[17];
					player_format_uid(offenderUid, offenderPlayerSession.Properties.host.player_uid);
					rapidjson::StringBuffer buffer;
					rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
					writer.StartObject();
					writer.Key("sender");
					writer.StartObject();
					writer.Key("ip");
					writer.String(session->GetPeerAddress(senderPlayerSession.PeerIndex).ToString().c_str());
					writer.Key("name");
					writer.String(Utils::String::ThinString(senderPlayerSession.Properties.host.player_name).c_str());
					writer.Key("serviceTag");
					writer.String(Utils::String::ThinString(senderPlayerSession.Properties.host.appearance.service_tag).c_str());
					writer.Key("uid");
					writer.String(senderUid);
					writer.EndObject();
					writer.Key("offender");
					writer.StartObject();
					writer.Key("ip");
					writer.String(session->GetPeerAddress(offenderPlayerSession.PeerIndex).ToString().c_str());
					writer.Key("name");
					writer.String(Utils::String::ThinString(offenderPlayerSession.Properties.host.player_name).c_str());
					writer.Key("serviceTag");
					writer.String(Utils::String::ThinString(offenderPlayerSession.Properties.host.appearance.service_tag).c_str());
					writer.Key("uid");
					writer.String(offenderUid);
					writer.EndObject();
					if (session->IsHost())
					{
						writer.Key("serverIp");
						writer.String("127.0.0.1");
						writer.Key("serverPort");
						writer.Uint(Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPort->ValueInt);
					}
					else
					{
						Blam::Network::NetworkAddress serverAddress = session->GetServerIPAddress();
						writer.Key("serverIp");
						writer.String(serverAddress.ToString().c_str());
						writer.Key("serverPort");
						writer.Uint(serverAddress.Port);
					}
					writer.Key("serverName");
					writer.String(Utils::Singleton<Modules::ModuleServer>::Instance().VarServerNameClient->ValueString.c_str());
					writer.EndObject();
					*p_Result = buffer.GetString();
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{

		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			namespace ClientFunctions
			{
				Web::Browser::Bridge::QueryError OnSubmitDialogResult(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10C685A0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?OnSubmitDialogResult@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C68754
					// static ...; // 0x10C6873C
					// static ...; // 0x10C68734
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > idMember;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > resultMember;

					auto id = p_Args.FindMember("id");
					auto result = p_Args.FindMember("result");
					if (id == p_Args.MemberEnd() || !id->value.IsInt())
					{
						*p_Result = "Bad query : A \"dialogId\" argument is required and must be a integer";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					if (result == p_Args.MemberEnd() || !result->value.IsString())
					{
						*p_Result = "Bad query : A \"result\" argument is required and must be a string";
						return Web::Browser::Bridge::QueryError_BadQuery;
					}
					Web::Ui::WebDialog::SubmitDialogResult(id->value.GetInt(), result->value.GetString());
					return Web::Browser::Bridge::QueryError_Ok;
				}
			}
		}
	}
}

/* ---------- private code */

static void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency) // 0x10C69AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PongReceived@@YAXABUNetworkAddress@Network@Blam@@IGI@Z");
	// `anonymous-namespace'::PongReceived
	// Blam::Network::NetworkAddress const &from;
	// unsigned __int32 timestamp;
	// unsigned short id;
	// unsigned __int32 latency;
	// std::string data;

	if (id != PingId)
		return;
	std::string data = "{";
	data += "address: '" + from.ToString() + "'";
	data += ",latency: " + std::to_string(latency);
	data += ",timestamp: " + std::to_string(timestamp);
	data += "}";
	Web::Ui::ScreenLayer::Notify("pong", data, true);
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool PingHandlerRegistered; }
