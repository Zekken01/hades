/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_results.hpp"
#include "Blam/game/game_statborg.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
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
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/Core.hpp"
#include "Patches/Events.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
#include "ThirdParty/HttpRequest.hpp"
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
#include "Utils/DewritoReader.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <WinSock2.h>
#include <WS2tcpip.h>
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
#include <ws2ipdef.h>
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
#include <fstream>
#include <functional>
#include <iomanip>
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

class HttpRequest;
class c_mod_package_manager;
struct begin;
struct c_game_engine;
struct c_game_results;
struct c_game_statborg;
struct end;
struct s_game_engine_event_data;
struct s_game_options;
struct s_game_results_events;
struct s_game_results_player_statistics;
struct s_multiplayer_event_response_definition;
struct s_player_emblem_configuration;
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
		struct SessionMembership;
	}
}

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
	namespace Stats {}
	using namespace Server::Stats;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
	namespace Events {}
	using namespace Patches::Events;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
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

namespace Server
{
	namespace Stats
	{
		extern void GetStatsEndpoints(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &destVect);
		extern void GetPlayersInfoEndpoint();
		extern void GetStatsPublicKey(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &dest);
		extern unsigned long __stdcall GetPlayersInfo_Thread(void *lpParam);
		extern bool AnnounceStats(std::basic_string<char,std::char_traits<char>,std::allocator<char> > payload, std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > endpoints);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetStatsPayload();
		extern void LifeCycleStateChanged(Blam::Network::LifeCycleState newState);
		extern void OnGameStart();
		extern unsigned __int32 GetPeerIp(Blam::Network::Session *session, __int32 peer);
		extern void LogListPlayers();
		extern void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition);
		extern void Init();
		extern void UpdatePlayersInfo();
		extern void Tick();
		extern bool localPlayerIsPostMatch();
	}
}

/* ---------- globals */

namespace Server
{
	namespace Stats
	{
		extern long long matchStartTime; // 0x124679F8
		extern long long matchEndTime; // 0x12467A00
		extern long long sendStatsTime; // 0x12467A08
		extern long long listPlayersTime; // 0x12467A10
		extern bool postMatch; // 0x12467A18
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > playersInfoEndpoint; // 0x12467A1C
		extern __int32 numberOfRounds; // 0x11354E40
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Server
{
	namespace Stats
	{
		_extern void _sub_10B28760(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &);
		void GetStatsEndpoints(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &destVect) // 0x10B28760
		{
			mangled_x86(MANGLED_TODO, "?GetStatsEndpoints@Stats@Server@@YAXAAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z");
			// static ...; // 0x10B288F8
			// static ...; // 0x10B288EC
			// static ...; // 0x10B288E4
			// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &destVect;
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &statsObject;
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &submitUrls;
					{
						// unsigned __int32 i;
					}
				}
			}
			todo("implement");
			_sub_10B28760(destVect);
		}

		_extern void _sub_10B271C0();
		void GetPlayersInfoEndpoint() // 0x10B271C0
		{
			mangled_x86(MANGLED_TODO, "?GetPlayersInfoEndpoint@Stats@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B272FC
			// static ...; // 0x10B272F0
			// static ...; // 0x10B272E8
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &statsObject;
			}
			todo("implement");
			_sub_10B271C0();
		}

		_extern void _sub_10B2BE60(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		void GetStatsPublicKey(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &dest) // 0x10B2BE60
		{
			mangled_x86(MANGLED_TODO, "?GetStatsPublicKey@Stats@Server@@YAXAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10B2BF98
			// static ...; // 0x10B2BF8C
			// static ...; // 0x10B2BF84
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &dest;
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &statsObject;
			}
			todo("implement");
			_sub_10B2BE60(dest);
		}

		_extern unsigned long _sub_10B27360(void *);
		unsigned long __stdcall GetPlayersInfo_Thread(void *lpParam) // 0x10B27360
		{
			mangled_x86(MANGLED_TODO, "?GetPlayersInfo_Thread@Stats@Server@@YGKPAX@Z");
			// static ...; // 0x10B28353
			// static ...; // 0x10B2834C
			// static ...; // 0x10B28345
			// static ...; // 0x10B2833F
			// static ...; // 0x10B2833B
			// static ...; // 0x10B2832E
			// static ...; // 0x10B2832A
			// static ...; // 0x10B2831F
			// static ...; // 0x10B28316
			// static ...; // 0x10B28311
			// static ...; // 0x10B2830C
			// static ...; // 0x10B28288
			// static ...; // 0x10B28280
		// $LN69:
			// void *lpParam;
			// __int32 player_index;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// HttpRequest req;
			// Blam::Network::Session *session;
			{
				// Blam::Network::PlayerSession *player;
				// char ipStr[22];
				// s_player_emblem_configuration emblemConfig;
				// char uid[17];
				// unsigned short team;
				// in_addr inAddr;
			}
			{
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > sendObject;
				// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > expected;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > resp;
			}
			todo("implement");
			unsigned long __result = _sub_10B27360(lpParam);
			return __result;
		}

		_extern bool _sub_10B26B90(std::string, std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > >);
		bool AnnounceStats(std::basic_string<char,std::char_traits<char>,std::allocator<char> > payload, std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > endpoints) // 0x10B26B90
		{
			mangled_x86(MANGLED_TODO, "?AnnounceStats@Stats@Server@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z");
			// static ...; // 0x10B27010
			// static ...; // 0x10B26FF8
			// static ...; // 0x10B26FF0
		// $LN29:
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > payload;
			// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > endpoints;
			{
				// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > server;
					{
						// HttpRequest req;
					}
				}
			}
			todo("implement");
			bool __result = _sub_10B26B90(payload, endpoints);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10B28970();
namespace Server
{
	namespace Stats
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetStatsPayload() // 0x10B28970
		{
			mangled_x86(MANGLED_TODO, "?GetStatsPayload@Stats@Server@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			// static ...; // 0x10B2B3B2
			// static ...; // 0x10B2B3AE
			// static ...; // 0x10B2B3AA
			// static ...; // 0x10B2B3A3
			// static ...; // 0x10B2B399
			// static ...; // 0x10B2B397
			// static ...; // 0x10B2B390
			// static ...; // 0x10B2B38C
			// static ...; // 0x10B2B384
			// static ...; // 0x10B2B375
			// static ...; // 0x10B2B369
			// static ...; // 0x10B2B35C
			// static ...; // 0x10B2B354
			// static ...; // 0x10B2B34E
			// static ...; // 0x10B2B347
			// static ...; // 0x10B2B341
			// static ...; // 0x10B2B33D
			// static ...; // 0x10B2B335
			// static ...; // 0x10B2B328
			// static ...; // 0x10B2B244
			// static ...; // 0x10B2B23C
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > modHash;
			// char const *const sig;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > pubKey;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > signature;
			// char uid[17];
			// __int32 matchLengthSeconds;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapName;
			// c_mod_package_manager::s_entry packageEntry;
			// c_game_statborg *scoreboard;
			// e_game_engine_type variantType;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > encryptedString;
			// char buf[42];
			// Blam::Network::Session *session;
			// unsigned __int32 TeamMode;
			// tm *now_tm;
			// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > mapVariantName;
			// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > variantName;
			// __int32 roundCount;
			// e_game_mode gameMode;
			// long long now;
			{
				// c_game_statborg *statborg;
				{
					// __int32 t;
					{
						// c_game_statborg::s_team_row &teamScore;
					}
				}
			}
			{
				// __int32 peerIdx;
				{
					// Blam::Network::PlayerSession *player;
					// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > color;
					// __int32 nemesisIdx;
					// __int32 playerIdx;
					// char ipStr[22];
					// s_player_emblem_configuration emblemConfig;
					// char uid[17];
					// s_game_results_player_statistics *player_stats;
					// c_game_results *current_results;
					// in_addr inAddr;
					// unsigned short team;
					// Pointer pvpBase;
					{
						// __int32 i;
					}
					{
					}
					{
						// __int32 nemesisKills;
						{
							// unsigned short currKills;
						}
					}
					{
					}
				}
			}
			{
				// __int32 e;
				{
					// s_game_results_events *resultsEvent;
				}
			}
			// function call : c_game_statborg *(*const)()
			// function call : long (*const)()
			// function call : s_game_options *(*)()
			// function call : c_game_engine *(*const)()
			// function call : c_game_statborg *(*const)()
			todo("implement");
			std::string __result = _sub_10B28970();
			return __result;
		}

		_extern void _sub_10B2C0B0(Blam::Network::LifeCycleState);
		void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x10B2C0B0
		{
			mangled_x86(MANGLED_TODO, "?LifeCycleStateChanged@Stats@Server@@YAXW4LifeCycleState@Network@Blam@@@Z");
			// Blam::Network::LifeCycleState newState;
			// Blam::Network::Session *session;
			todo("implement");
			_sub_10B2C0B0(newState);
		}

		_extern void _sub_10B2CBA0();
		void OnGameStart() // 0x10B2CBA0
		{
			mangled_x86(MANGLED_TODO, "?OnGameStart@Stats@Server@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			// function call : long (*const)()
			todo("implement");
			_sub_10B2CBA0();
		}

		_extern unsigned __int32 _sub_10B27140(Blam::Network::Session *, __int32);
		unsigned __int32 GetPeerIp(Blam::Network::Session *session, __int32 peer) // 0x10B27140
		{
			mangled_x86(MANGLED_TODO, "?GetPeerIp@Stats@Server@@YAIPAUSession@Network@Blam@@H@Z");
			// __int32 peer;
			// Blam::Network::SessionMembership *membership;
			// __int32 channelIndex;
			todo("implement");
			unsigned __int32 __result = _sub_10B27140(session, peer);
			return __result;
		}

		_extern void _sub_10B2C170();
		void LogListPlayers() // 0x10B2C170
		{
			mangled_x86(MANGLED_TODO, "?LogListPlayers@Stats@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B2C7DE
			// static ...; // 0x10B2C7CB
			// static ...; // 0x10B2C7BF
			// static ...; // 0x10B2C7AF
			// static ...; // 0x10B2C7A7
			// static ...; // 0x10B2C7A3
			// static ...; // 0x10B2C79E
			// static ...; // 0x10B2C797
			// static ...; // 0x10B2C792
			// static ...; // 0x10B2C78B
			// static ...; // 0x10B2C784
			// static ...; // 0x10B2C700
			// static ...; // 0x10B2C6F8
			// std::filesystem::path parentDirectory;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
			// std::basic_ofstream<char,std::char_traits<char> > logFile;
			// long long time;
			// std::filesystem::path logFilePath;
			// Blam::Network::Session *session;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > listPlayersLogFile;
			// tm gmTime;
			// std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > now;
			// __int32 peerIdx;
			{
				// __int32 playerIdx;
				{
					// Blam::Network::PlayerSession *player;
					// unsigned long long uid;
					// unsigned __int32 ip;
					// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > stream;
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > hexUID;
				}
			}
			todo("implement");
			_sub_10B2C170();
		}

		_extern void _sub_10B2C980(unsigned long, s_game_engine_event_data const *, s_multiplayer_event_response_definition const *);
		void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10B2C980
		{
			mangled_x86(MANGLED_TODO, "?OnEvent@Stats@Server@@YAXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z");
		// $LN15:
		// $LN6:
		// $LN1:
			// unsigned long player;
			// s_game_engine_event_data const *event;
			// s_multiplayer_event_response_definition const *definition;
			// Blam::Network::Session *session;
			// function call : long (*const)()
			// function call : __int32 (*const)()
			todo("implement");
			_sub_10B2C980(player, event, definition);
		}

		_extern void _sub_10B2BFF0();
		void Init() // 0x10B2BFF0
		{
			mangled_x86(MANGLED_TODO, "?Init@Stats@Server@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10B2BFF0();
		}

		_extern void _sub_10B2CF80();
		void UpdatePlayersInfo() // 0x10B2CF80
		{
			mangled_x86(MANGLED_TODO, "?UpdatePlayersInfo@Stats@Server@@YAXXZ");
			// procedure flags: nofpo
			// void *thread;
			// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)
			todo("implement");
			_sub_10B2CF80();
		}

		_extern void _sub_10B2CC30();
		void Tick() // 0x10B2CC30
		{
			mangled_x86(MANGLED_TODO, "?Tick@Stats@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B2CEC6
			// static ...; // 0x10B2CEB7
			// static ...; // 0x10B2CEAA
			// static ...; // 0x10B2CEA0
			// static ...; // 0x10B2CE70
			// static ...; // 0x10B2CE68
			// long long curTime1;
			// Blam::Network::Session *session;
			{
				// long long elapsed;
				{
					// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > statsEndpoints;
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > statsPayload;
						{
							// std::thread SendStats;
						}
					}
				}
			}
			{
			}
			todo("implement");
			_sub_10B2CC30();
		}

		_extern bool _sub_10B2D5E0();
		bool localPlayerIsPostMatch() // 0x10B2D5E0
		{
			mangled_x86(MANGLED_TODO, "?localPlayerIsPostMatch@Stats@Server@@YA_NXZ");
			// procedure flags: nofpo
			todo("implement");
			bool __result = _sub_10B2D5E0();
			return __result;
		}
	}
}

/* ---------- private code */
