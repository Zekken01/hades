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

/* ---------- prototypes */

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

void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency);

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
			extern QueryError _sub_10C67820(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnShow@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C67820(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C64FA0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnHide@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C64FA0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C66730(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnScreenState@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C668F0
					// static ...; // 0x10C668D8
					// static ...; // 0x10C668D0
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > screenIdMember;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > stateMember;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C66730(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C63390(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnCommand@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C63530
					// static ...; // 0x10C63518
					// static ...; // 0x10C63510
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_CommandValue;
					// bool s_IsInternal;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_InternalValue;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C63390(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C67130(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnSetVariables@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					{
						// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
						{
							// VariableSetReturnValue retValue;
						}
					}
					{
						// char const *const kVariableReturnValueErrors[1];
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuff;
						{
							// std::vector<std::pair<std::string,enum VariableSetReturnValue> > &<range>$L0;
							// std::pair<std::string,enum VariableSetReturnValue> *<begin>$L0;
							// std::pair<std::string,enum VariableSetReturnValue> *<end>$L0;
							{
								// std::pair<std::string,enum VariableSetReturnValue> const &pair;
							}
						}
					}
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C67130(args, result);
					return __result;
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
			extern QueryError _sub_10C64770(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnGetAssetUrl@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					{
						// rapidjson::GenericArray<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L0;
						// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const *<begin>$L0;
						// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const *<end>$L0;
						{
							// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &val;
						}
					}
					{
						// std::string url;
					}
					{
					}
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C64770(p_Args, p_Result);
					return __result;
				}
			}
		}
	}
}

_inline s_map_variant::s_map_variant(s_map_variant const &__that) // 0x10C62AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_map_variant@@QAE@ABU0@@Z");
	// s_map_variant const &__that;

	compiler_generated();
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			extern QueryError _sub_10C65960(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnPing@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C65960(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C63080(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnCaptureInput@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C631C8
					// static ...; // 0x10C631B0
					// static ...; // 0x10C631A8
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// bool capturePointer;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_CaptureValue;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_CapturePointerValue;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C63080(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C687E0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnVersion@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C687E0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C65180(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnMapVariantInfo@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					{
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
						// char const *description;
						// char const *author;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
						// unsigned char *mapVariant;
						// s_level_datum map_level;
						// s_map_variant map;
						// std::string name;
						// unsigned __int32 mapId;
					}
					{
						// bool (*const network_squad_session_get_map)(long *, long *);
						// long campaignId;
						// s_level_datum level;
						// long mapId;
					}
					// function call : s_game_options *(*)()
					// function call : bool (*const)(long *, long *)
					// function call : bool (*const)(long, s_level_datum *)
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C65180(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C66620(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnScoreboard@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					// Blam::Network::Session *session;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C66620(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C678B0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnShowScoreboard@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C67A88
					// static ...; // 0x10C67A80
					// static ...; // 0x10C67A5C
					// static ...; // 0x10C67A54
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > animate;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > locked;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > pregame;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C678B0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C666F0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnScoreboardHide@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C666F0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C63FE0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnGameVariantInfo@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					{
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
					}
					{
						// s_game_options *game;
					}
					// function call : s_game_options *(*)()
					// function call : long (*const)()
					// function call : short (*const)()
					// function call : bool (*const)()
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C63FE0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C635C0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnCommands@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					{
						// std::deque<Modules::Command> const &<range>$L0;
						// std::_Deque_unchecked_const_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
						// std::_Deque_unchecked_const_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
						{
							// Modules::Command const &command;
							{
								// std::string const *<end>$L1;
								// std::string const *<begin>$L1;
								// std::vector<std::string> const &<range>$L1;
								{
									// std::string const &arg;
								}
							}
						}
					}
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C635C0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C66990(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnSendChat@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C66BB0
					// static ...; // 0x10C66B98
					// static ...; // 0x10C66B90
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > teamChat;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > message;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C66990(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C63250(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnChatBoxOpened@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C63334
					// static ...; // 0x10C6332C
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > opened;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C63250(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C66C50(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnSessionInfo@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C67020
					// static ...; // 0x10C6701C
					// static ...; // 0x10C66FF8
					// static ...; // 0x10C66FF0
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
					// Blam::Network::Session *session;
					{
						// char uid[17];
					}
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C66C50(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C67B10(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnStats@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					{
						// Blam::Network::PlayerSession player;
						{
							// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
							// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
							// s_game_results_player_statistics *player_stats;
							// s_game_results_player_vs_player_statistics *player_vs_player_stats;
							{
								// __int32 i;
								{
									// Blam::Network::PlayerSession p;
								}
							}
							{
								{
								}
							}
							{
								// __int32 medal;
							}
							{
								// __int32 weapon;
								{
									// s_game_results_player_weapon_statistics wep;
								}
							}
						}
					}
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C67B10(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C69820(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnVoIPSpeakingChanged@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C69A28
					// static ...; // 0x10C69A20
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// __int32 player_index;
					// Blam::Network::Session *session;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > value;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C69820(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C68880(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnVoIPConnectedChanged@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C68950
					// static ...; // 0x10C68948
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > value;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C68880(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C69180(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnVoIPPlayerVoipLevelChanged@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					{
						// double volume;
					}
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C69180(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C689A0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnVoIPPlayerSpeakingChanged@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C68CD8
					// static ...; // 0x10C68CC0
					// static ...; // 0x10C68CB8
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// __int32 player_index;
					// Blam::Network::Session *session;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > name;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > value;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C689A0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C68DC0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnVoIPPlayerVoipJoined@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C690B2
					// static ...; // 0x10C690A7
					// static ...; // 0x10C6909C
					// static ...; // 0x10C6906C
					// static ...; // 0x10C69064
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > uid;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > name;
					{
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
					}
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C68DC0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C64FF0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnIsMapLoading@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C6511C
					// static ...; // 0x10C65104
					// static ...; // 0x10C650FC
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
					// static bool (*IsMapLoading)(); // 0x11355190
					// function call : bool (*)()
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C64FF0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C63EF0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnForgeAction@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C63EF0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C63F40(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnForgePalette@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C63F40(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C67870(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnShowLan@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// std::string *p_Result;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C67870(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C65CD0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnPlayerReportInfo@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
					{
						// Blam::Network::NetworkAddress serverAddress;
					}
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C65CD0(p_Args, p_Result);
					return __result;
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
			extern QueryError _sub_10C685A0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *);
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
					mangled_x86(MANGLED_TODO, "?OnSubmitDialogResult@ClientFunctions@Bridge@Browser@Web@@YA?AW4QueryError@234@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
					// static ...; // 0x10C68754
					// static ...; // 0x10C6873C
					// static ...; // 0x10C68734
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
					// std::string *p_Result;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > idMember;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > resultMember;
					todo("implement");
					Web::Browser::Bridge::QueryError __result = _sub_10C685A0(p_Args, p_Result);
					return __result;
				}
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_10C69AC0(Blam::Network::NetworkAddress const &, unsigned __int32, unsigned short, unsigned __int32);
void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency) // 0x10C69AC0
{
	// `anonymous-namespace'::PongReceived
	// Blam::Network::NetworkAddress const &from;
	// unsigned __int32 timestamp;
	// unsigned short id;
	// unsigned __int32 latency;
	// std::string data;
	todo("implement");
	_sub_10C69AC0(from, timestamp, id, latency);
}
