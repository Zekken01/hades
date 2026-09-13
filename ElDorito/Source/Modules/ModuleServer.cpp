/* ---------- headers */

#include "Modules/ModuleServer.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/game/engine/game_engine_option.hpp"
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
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/ObjectSet.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleBase.hpp"
#include "Modules/ModulePlayer.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
#include "Server/BanList.hpp"
#include "Server/Connect/ServerConnect.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/ServerChat.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
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
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Utils/WebSocket.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <WinSock2.h>
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
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iomanip>
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
#include <random>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CModPackageFileSystemView;
class HttpRequest;
class c_mod_package_manager;
struct SServerConnectOptions;
struct begin;
struct end;
namespace Blam
{
	namespace Network
	{
		struct NetworkAddress;
		struct PlayerSession;
		struct Session;
		struct SessionMembership;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModulePlayer;
	class ModuleServer;
	struct Command;
}
namespace Server
{
	class BanList;
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
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
	namespace Signaling {}
	using namespace Server::Signaling;
	namespace InfoServer {}
	using namespace Server::InfoServer;
	namespace Stats {}
	using namespace Server::Stats;
	namespace Chat {}
	using namespace Server::Chat;
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
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

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Sprint {}
	using namespace Patches::Sprint;
	namespace Weapon {}
	using namespace Patches::Weapon;
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
	namespace Assassination {}
	using namespace Patches::Assassination;
	namespace Tweaks {}
	using namespace Patches::Tweaks;
}

namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Console {}
using namespace ::Console;
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

namespace hades_file_local
{
	enum KickType
	{
		Kick = 0,
		Ban,
		TempBan,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

/* ---------- prototypes */

#include "mods/mod_system.hpp"  // hades: added for 0x10A07E50

namespace Patches::Weapon { void SetBottomlessClip(bool enable); }  // hades: added for 0X10A07D10

namespace Server::InfoServer { bool IsInfoSocketOpen(); }  // hades: added for 0X10A0F240

namespace Patches::Tweaks { void EnableHitmarkers(bool enabled); }  // hades: added for 0X10A13A60

namespace Patches::Sprint { void SetState(int state); }  // hades: added for 0X10A140E0

namespace Patches::Sprint { void SetUnlimited(bool unlimited); }  // hades: added for 0X10A146A0

namespace Player { class CPlayersInfo { public: static void Update(std::string const &); }; }  // hades: added for 0X10A149E0

bool VarServerNameUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariablePostGameFadeDelayUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableServerCountdownUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableServerMaxPlayersUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableServerGamePortUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
void GetEndpoints(std::vector<std::string> &destVect, std::string endpointType);
bool GetEndpoint(std::string endpointName, std::string &returnInfo);
unsigned long __stdcall CommandServerAnnounce_Thread(void *lpParam);
unsigned long __stdcall CommandServerUnannounce_Thread(void *lpParam);
bool CommandServerAnnounce(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerUnannounce(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableServerShouldAnnounceUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerConnect(std::vector<std::string> const &Arguments, std::string &returnInfo);
__int32 FindPlayerByName(std::string const &name, bool findPeer);
std::vector<int> FindPlayersByUid(unsigned long long uid);
void BanIp(std::string const &ip);
void BanUid(std::string const &playerUid);
void BanName(std::string const &name);
void TempBanIP(std::string const &ip);
bool UnbanIp(std::string const &ip);
bool UnbanUid(std::string const &playerUid);
bool UnbanName(std::string const &name);
bool DoKickPlayerCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo);
bool DoKickUidCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo);
bool DoKickIndexCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerKickPlayer(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerBanPlayer(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerKickPlayerUid(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerTempBanPlayer(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerTempBanPlayerUid(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerBanPlayerUid(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerKickPlayerIndex(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerBanPlayerIndex(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerKickBan(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerBan(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerUnban(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerMutePlayer(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerUnmutePlayer(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerClearAllMutes(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerClearTempBans(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerRemoveTempBan(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerListTempBans(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerListPlayers(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerListPlayersJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerMode(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerLobbyType(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerPing(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerShuffleTeams(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerGetEndpoint(std::vector<std::string> const &Arguments, std::string &returnInfo);
void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency);
bool HitmarkersEnabledChanged(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool SprintStateChanged(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool BottomlessClipEnabledChanged(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool UnlimitedSprintEnabledChanged(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerSubmitVote(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerSay(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerPM(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool EncryptMessageWithPublicKey(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandWebsocketInfo(std::vector<std::string> const &Arguments, std::string &returnInfo);
void UpdatePersistentMod(std::string mod);
bool CommandLoadMod(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandListMods(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandListModInfo(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandListModFiles(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandEnumerateMods(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDeleteMod(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariablePlayersInfoClientUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandRefreshServerFilters(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		extern std::string DefaultBanListPath; // 0x12456040
	}
	using namespace hades_file_local_Server;
}
namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::string const DefaultTypes[8]; // 0x12455E80
			extern std::string const DefaultTypeNames[8]; // 0x12455F60
		}
		using namespace hades_file_local_Server_Voting;
	}
}
namespace hades_file_local
{
	extern unsigned short PingId; // 0x1245605C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	extern ModuleServer* _sub_109FE0E0(Modules::ModuleServer *const);
	ModuleServer::ModuleServer() : ModuleBase(todo_result<std::string>()) // 0x109FE0E0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleServer@Modules@@QAE@XZ");
		// Modules::ModuleServer *const this;
		// Modules::Command *syncTestServer;
		// Modules::Command *syncTestClient;
		todo("implement");
		_sub_109FE0E0(this);
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0SServerConnectOptions@@QAE@XZ"); no body to assert in
_inline SServerConnectOptions::SServerConnectOptions() = default; // 0x10A06DC0

// mangled_x86(MANGLED_DEFAULT, "??1SServerConnectOptions@@QAE@XZ"); no body to assert in
_inline SServerConnectOptions::~SServerConnectOptions() = default; // 0x10A07290

// mangled_x86(MANGLED_DEFAULT, "??1c_threadsafe_iterator@c_mod_package_manager@@QAE@XZ"); no body to assert in
_inline c_mod_package_manager::c_threadsafe_iterator::~c_threadsafe_iterator() = default; // 0x10A073C0

namespace Modules
{
	_extern void _sub_10A186A0(Modules::ModuleServer *const);
	void ModuleServer::refreshServerFilters() // 0x10A186A0
	{
		mangled_x86(MANGLED_TODO, "?refreshServerFilters@ModuleServer@Modules@@QAEXXZ");
		// static ...; // 0x10A18ED5
		// static ...; // 0x10A18ECC
		// static ...; // 0x10A18EC7
		// static ...; // 0x10A18EC2
		// static ...; // 0x10A18EBD
		// static ...; // 0x10A18EB5
		// static ...; // 0x10A18EAD
		// static ...; // 0x10A18EAB
		// static ...; // 0x10A18EA4
		// static ...; // 0x10A18E38
		// static ...; // 0x10A18E30
		// Modules::ModuleServer *const this;
		// std::ifstream in;
		{
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			// std::string contents;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &namesArray;
				{
					// unsigned __int32 i;
					{
						// std::string name;
					}
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &wordsArray;
				{
					{
						// std::string word;
					}
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &patternArray;
				{
					{
						// std::string pattern;
					}
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &replacementWord;
			}
		}
		{
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// std::ofstream outFile;
		}
		todo("implement");
		_sub_10A186A0(this);
	}
}

extern std::unordered_set<std::string> _sub_10A139E0(Modules::ModuleServer *const);
namespace Modules
{
	std::unordered_set<std::string> ModuleServer::GetFilteredWordsList() // 0x10A139E0
	{
		mangled_x86(MANGLED_TODO, "?GetFilteredWordsList@ModuleServer@Modules@@QAE?AV?$unordered_set@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// Modules::ModuleServer *const this;
		todo("implement");
		std::unordered_set<std::string> __result = _sub_10A139E0(this);
		return __result;
	}
}

extern std::unordered_set<std::string> _sub_10A13960(Modules::ModuleServer *const);
namespace Modules
{
	std::unordered_set<std::string> ModuleServer::GetFilteredPatternsList() // 0x10A13960
	{
		mangled_x86(MANGLED_TODO, "?GetFilteredPatternsList@ModuleServer@Modules@@QAE?AV?$unordered_set@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// Modules::ModuleServer *const this;
		todo("implement");
		std::unordered_set<std::string> __result = _sub_10A13960(this);
		return __result;
	}
}

extern std::string _sub_10A138E0(Modules::ModuleServer *const);
namespace Modules
{
	std::string ModuleServer::GetFilterReplacementWord() // 0x10A138E0
	{
		mangled_x86(MANGLED_TODO, "?GetFilterReplacementWord@ModuleServer@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// Modules::ModuleServer *const this;
		todo("implement");
		std::string __result = _sub_10A138E0(this);
		return __result;
	}
}

/* ---------- private code */

bool VarServerNameUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A148A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VarServerNameUpdated@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VarServerNameUpdated
	// std::string &returnInfo;

	//Trim server name to 128 characters
	if (Modules::ModuleServer::Instance().VarServerName->ValueString.length() > 128)
		Modules::ModuleServer::Instance().VarServerName->ValueString = Modules::ModuleServer::Instance().VarServerName->ValueString.substr(0, 128);

	return true;
}

_extern bool _sub_10A14A50(std::vector<std::string> const &, std::string &);
bool VariablePostGameFadeDelayUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A14A50
{
	// `anonymous-namespace'::VariablePostGameFadeDelayUpdate
	// std::string &returnInfo;
	// unsigned long seconds;
	todo("implement");
	bool __result = _sub_10A14A50(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A14B50(std::vector<std::string> const &, std::string &);
bool VariableServerCountdownUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A14B50
{
	// `anonymous-namespace'::VariableServerCountdownUpdate
	// std::string &returnInfo;
	// unsigned long offset;
	// unsigned long seconds;
	todo("implement");
	bool __result = _sub_10A14B50(Arguments, returnInfo);
	return __result;
}

bool VariableServerMaxPlayersUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A15010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableServerMaxPlayersUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableServerMaxPlayersUpdate
	// std::string &returnInfo;
	// char (*network_squad_session_set_maximum_player_count)(__int32);
	// function call : char (*)(__int32)

	char (__cdecl *network_squad_session_set_maximum_player_count)(__int32) = (char(__cdecl *)(__int32))0x439ba0;

	network_squad_session_set_maximum_player_count(Modules::ModuleServer::Instance().VarServerMaxPlayers->ValueInt);
	return true;
}

bool VariableServerGamePortUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A14FC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableServerGamePortUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableServerGamePortUpdate
	// std::string &returnInfo;

	returnInfo = "Requires a game restart to apply.";
	return true;
}

_extern void _sub_10A136F0(std::vector<std::string> &, std::string);
void GetEndpoints(std::vector<std::string> &destVect, std::string endpointType) // 0x10A136F0
{
	// `anonymous-namespace'::GetEndpoints
	// static ...; // 0x10A1386C
	// static ...; // 0x10A13864
	// std::vector<std::string> &destVect;
	// std::string endpointType;
	{
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
		{
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &mastersArray;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *it;
			}
		}
	}
	todo("implement");
	_sub_10A136F0(destVect, endpointType);
}

_extern bool _sub_10A132A0(std::string, std::string &);
bool GetEndpoint(std::string endpointName, std::string &returnInfo) // 0x10A132A0
{
	// `anonymous-namespace'::GetEndpoint
	// static ...; // 0x10A13600
	// static ...; // 0x10A135F9
	// static ...; // 0x10A135F0
	// static ...; // 0x10A135C0
	// static ...; // 0x10A135B8
	// std::string endpointName;
	// std::string &returnInfo;
	{
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
		{
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &mastersArray;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *it;
			}
		}
		{
			// std::string endpoint;
		}
	}
	todo("implement");
	bool __result = _sub_10A132A0(endpointName, returnInfo);
	return __result;
}

_extern unsigned long _sub_10A09A70(void *);
unsigned long __stdcall CommandServerAnnounce_Thread(void *lpParam) // 0x10A09A70
{
	// `anonymous-namespace'::CommandServerAnnounce_Thread
	// static ...; // 0x10A0A82F
	// static ...; // 0x10A0A81D
	// static ...; // 0x10A0A816
	// static ...; // 0x10A0A812
	// static ...; // 0x10A0A809
	// static ...; // 0x10A0A801
	// static ...; // 0x10A0A7FC
	// static ...; // 0x10A0A7F7
	// static ...; // 0x10A0A7F0
	// static ...; // 0x10A0A784
	// static ...; // 0x10A0A77C
// $LN47:
// $LN49:
	// void *lpParam;
	// std::stringstream ss;
	// std::string errors;
	// std::vector<std::string> announceEndpoints;
	{
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
		{
			// std::string server;
			{
				// std::wstring respHdr;
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
				// std::wstring expected;
				// HttpRequest req;
				// std::string resp;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &result;
			}
		}
	}
	// function call : unsigned long ()
	todo("implement");
	unsigned long __result = _sub_10A09A70(lpParam);
	return __result;
}

_extern unsigned long _sub_10A0F2D0(void *);
unsigned long __stdcall CommandServerUnannounce_Thread(void *lpParam) // 0x10A0F2D0
{
	// `anonymous-namespace'::CommandServerUnannounce_Thread
	// static ...; // 0x10A100CF
	// static ...; // 0x10A100BD
	// static ...; // 0x10A100B6
	// static ...; // 0x10A100B2
	// static ...; // 0x10A100A9
	// static ...; // 0x10A100A1
	// static ...; // 0x10A1009C
	// static ...; // 0x10A10097
	// static ...; // 0x10A10090
	// static ...; // 0x10A10024
	// static ...; // 0x10A1001C
// $LN48:
// $LN50:
	// void *lpParam;
	// std::stringstream ss;
	// std::string errors;
	// std::vector<std::string> announceEndpoints;
	{
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
		{
			// std::string server;
			{
				// std::wstring respHdr;
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
				// std::wstring expected;
				// HttpRequest req;
				// std::string resp;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &result;
			}
		}
	}
	// function call : unsigned long ()
	todo("implement");
	unsigned long __result = _sub_10A0F2D0(lpParam);
	return __result;
}

_extern bool _sub_10A09760(std::vector<std::string> const &, std::string &);
bool CommandServerAnnounce(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A09760
{
	// `anonymous-namespace'::CommandServerAnnounce
	// static ...; // 0x10A099BC
	// static ...; // 0x10A099B4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	{
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
		{
			// void *thread;
		}
	}
	// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)
	todo("implement");
	bool __result = _sub_10A09760(Arguments, returnInfo);
	return __result;
}

bool CommandServerUnannounce(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0F240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerUnannounce@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerUnannounce
	// std::string &returnInfo;
	// void *thread;
	// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)

	if (!Server::InfoServer::IsInfoSocketOpen())
	{
		return false;
	}

	HANDLE thread = CreateThread(nullptr, 0, CommandServerUnannounce_Thread, (LPVOID)&Arguments, 0, nullptr);
	returnInfo = "Unannouncing to master servers...";
	return true;
}

_extern bool _sub_10A15090(std::vector<std::string> const &, std::string &);
bool VariableServerShouldAnnounceUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A15090
{
	// `anonymous-namespace'::VariableServerShouldAnnounceUpdate
	// static ...; // 0x10A15158
	// static ...; // 0x10A15150
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string returnValueIgnored;
	todo("implement");
	bool __result = _sub_10A15090(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A0B280(std::vector<std::string> const &, std::string &);
bool CommandServerConnect(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B280
{
	// `anonymous-namespace'::CommandServerConnect
	// static ...; // 0x10A0B676
	// static ...; // 0x10A0B671
	// static ...; // 0x10A0B66C
	// static ...; // 0x10A0B664
	// static ...; // 0x10A0B628
	// static ...; // 0x10A0B620
// $LN19:
// $LN8:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// SServerConnectOptions options;
	// std::string host;
	// std::string password;
	// unsigned __int32 rawIpaddr;
	// __int32 httpPort;
	// unsigned __int32 portOffset;
	// std::string address;
	{
		// std::string port;
	}
	todo("implement");
	bool __result = _sub_10A0B280(Arguments, returnInfo);
	return __result;
}

_extern __int32 _sub_10A12E90(std::string const &, bool);
__int32 FindPlayerByName(std::string const &name, bool findPeer) // 0x10A12E90
{
	// `anonymous-namespace'::FindPlayerByName
	// bool findPeer;
	// Blam::Network::SessionMembership *membership;
	// Blam::Network::Session *session;
	{
		// __int32 peerIdx;
		{
			// Blam::Network::PlayerSession *player;
			// __int32 playerIdx;
		}
	}
	todo("implement");
	__int32 __result = _sub_10A12E90(name, findPeer);
	return __result;
}

extern std::vector<int> _sub_10A13040(unsigned long long);
std::vector<int> FindPlayersByUid(unsigned long long uid) // 0x10A13040
{
	// `anonymous-namespace'::FindPlayersByUid
	// static ...; // 0x10A13216
	// static ...; // 0x10A1320C
	// static ...; // 0x10A131F4
	// static ...; // 0x10A131EC
	// unsigned long long uid;
	// Blam::Network::SessionMembership *membership;
	// Blam::Network::Session *session;
	// std::vector<int> indices;
	{
		// __int32 peerIdx;
		{
			// Blam::Network::PlayerSession *player;
			// __int32 playerIdx;
		}
	}
	todo("implement");
	std::vector<int> __result = _sub_10A13040(uid);
	return __result;
}

void BanIp(std::string const &ip) // 0x10A079B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BanIp@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::BanIp
	// static ...; // 0x10A07A78
	// static ...; // 0x10A07A6C
	// static ...; // 0x10A07A64
	// std::string const &ip;
	// Server::BanList banList;

	auto banList = Server::LoadDefaultBanList();
	banList.AddIp(ip);
	Server::SaveDefaultBanList(banList);
}

_extern void _sub_10A07BD0(std::string const &);
void BanUid(std::string const &playerUid) // 0x10A07BD0
{
	// `anonymous-namespace'::BanUid
	// static ...; // 0x10A07CC8
	// static ...; // 0x10A07CC0
	// static ...; // 0x10A07CA8
	// static ...; // 0x10A07CA0
	// std::string const &playerUid;
	// unsigned long long uid;
	{
		// Server::BanList banList;
	}
	todo("implement");
	_sub_10A07BD0(playerUid);
}

_extern void _sub_10A07AC0(std::string const &);
void BanName(std::string const &name) // 0x10A07AC0
{
	// `anonymous-namespace'::BanName
	// static ...; // 0x10A07B88
	// static ...; // 0x10A07B7C
	// static ...; // 0x10A07B74
	// std::string const &name;
	// Server::BanList banList;
	todo("implement");
	_sub_10A07AC0(name);
}

void TempBanIP(std::string const &ip) // 0x10A14150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TempBanIP@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::TempBanIP
	// std::string const &ip;

	Utils::Singleton<Server::TempBanList>::Instance().AddIp(ip);
}

bool UnbanIp(std::string const &ip) // 0x10A14240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UnbanIp@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::UnbanIp
	// static ...; // 0x10A1433C
	// static ...; // 0x10A14330
	// static ...; // 0x10A14328
	// std::string const &ip;
	// Server::BanList banList;

	auto banList = Server::LoadDefaultBanList();
	if (!banList.RemoveIp(ip))
		return false;
	Server::SaveDefaultBanList(banList);
	return true;
}

_extern bool _sub_10A144E0(std::string const &);
bool UnbanUid(std::string const &playerUid) // 0x10A144E0
{
	// `anonymous-namespace'::UnbanUid
	// static ...; // 0x10A14634
	// static ...; // 0x10A14630
	// static ...; // 0x10A14618
	// static ...; // 0x10A14610
	// std::string const &playerUid;
	// Server::BanList banList;
	// unsigned long long uid;
	todo("implement");
	bool __result = _sub_10A144E0(playerUid);
	return __result;
}

_extern bool _sub_10A14390(std::string const &);
bool UnbanName(std::string const &name) // 0x10A14390
{
	// `anonymous-namespace'::UnbanName
	// static ...; // 0x10A1448C
	// static ...; // 0x10A14480
	// static ...; // 0x10A14478
	// std::string const &name;
	// Server::BanList banList;
	todo("implement");
	bool __result = _sub_10A14390(name);
	return __result;
}

_extern bool _sub_10A11AA0(KickType, std::vector<std::string> const &, std::string &);
bool DoKickPlayerCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A11AA0
{
	// `anonymous-namespace'::DoKickPlayerCommand
	// static ...; // 0x10A12194
	// static ...; // 0x10A12170
	// static ...; // 0x10A12168
	// KickType type;
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 peer;
	// __int32 playerIdx;
	// std::stringstream ss;
	// std::string kickPlayerName;
	// std::string ip;
	// Blam::Network::Session *session;
	// e_network_session_boot_reason banReason;
	todo("implement");
	bool __result = _sub_10A11AA0(type, Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A12370(KickType, std::vector<std::string> const &, std::string &);
bool DoKickUidCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A12370
{
	// `anonymous-namespace'::DoKickUidCommand
	// static ...; // 0x10A12A53
	// static ...; // 0x10A12A44
	// static ...; // 0x10A12A14
	// static ...; // 0x10A12A0C
	// KickType type;
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool success;
	// unsigned long long uid;
	// Blam::Network::Session *session;
	// e_network_session_boot_reason banReason;
	// std::vector<int> indices;
	{
		// std::vector<int> &<range>$L0;
		// __int32 *<begin>$L0;
		// __int32 *<end>$L0;
		{
			// __int32 playerIdx;
			{
				// std::string kickPlayerName;
				// std::string ip;
			}
		}
	}
	todo("implement");
	bool __result = _sub_10A12370(type, Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A11390(KickType, std::vector<std::string> const &, std::string &);
bool DoKickIndexCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A11390
{
	// `anonymous-namespace'::DoKickIndexCommand
	// static ...; // 0x10A11920
	// static ...; // 0x10A118FC
	// static ...; // 0x10A118F4
// $LN33:
	// KickType type;
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::PlayerSession *player;
	// __int32 index;
	// std::string kickPlayerName;
	// std::string ip;
	// Blam::Network::Session *session;
	// __int32 banReason;
	// unsigned __int32 pos;
	todo("implement");
	bool __result = _sub_10A11390(type, Arguments, returnInfo);
	return __result;
}

bool CommandServerKickPlayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0C500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerKickPlayer@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerKickPlayer
	// std::string &returnInfo;

	return DoKickPlayerCommand(Kick, Arguments, returnInfo);
}

bool CommandServerBanPlayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B0F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerBanPlayer@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerBanPlayer
	// std::string &returnInfo;

	return DoKickPlayerCommand(Ban, Arguments, returnInfo);
}

bool CommandServerKickPlayerUid(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0C5A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerKickPlayerUid@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerKickPlayerUid
	// std::string &returnInfo;

	return DoKickUidCommand(Kick, Arguments, returnInfo);
}

bool CommandServerTempBanPlayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0F1A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerTempBanPlayer@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerTempBanPlayer
	// std::string &returnInfo;

	return DoKickPlayerCommand(TempBan, Arguments, returnInfo);
}

bool CommandServerTempBanPlayerUid(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0F1F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerTempBanPlayerUid@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerTempBanPlayerUid
	// std::string &returnInfo;

	return DoKickUidCommand(TempBan, Arguments, returnInfo);
}

bool CommandServerBanPlayerUid(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerBanPlayerUid@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerBanPlayerUid
	// std::string &returnInfo;

	return DoKickUidCommand(Ban, Arguments, returnInfo);
}

bool CommandServerKickPlayerIndex(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0C550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerKickPlayerIndex@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerKickPlayerIndex
	// std::string &returnInfo;

	return DoKickIndexCommand(Kick, Arguments, returnInfo);
}

bool CommandServerBanPlayerIndex(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerBanPlayerIndex@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerBanPlayerIndex
	// std::string &returnInfo;

	return DoKickIndexCommand(Ban, Arguments, returnInfo);
}

_extern bool _sub_10A0B810(std::vector<std::string> const &, std::string &);
bool CommandServerKickBan(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B810
{
	// `anonymous-namespace'::CommandServerKickBan
	// static ...; // 0x10A0C258
	// static ...; // 0x10A0C24F
	// static ...; // 0x10A0C245
	// static ...; // 0x10A0C241
	// static ...; // 0x10A0C239
	// static ...; // 0x10A0C234
	// static ...; // 0x10A0C1E0
	// static ...; // 0x10A0C1D8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::Session *session;
	// std::string banType;
	{
		// Blam::Network::SessionMembership *membership;
		// std::string ip;
		{
			// __int32 peerIdx;
			{
				// __int32 playerIdx;
				// std::string playerIp;
			}
		}
	}
	{
		// unsigned long long uid;
		// std::string playerUid;
		{
			// std::vector<int> indices;
			{
				// std::vector<int> &<range>$L0;
				// __int32 *<begin>$L0;
				// __int32 *<end>$L0;
				{
					// __int32 playerIdx;
				}
			}
		}
	}
	{
		// __int32 playerIdx;
		// std::string name;
	}
	todo("implement");
	bool __result = _sub_10A0B810(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A0ABB0(std::vector<std::string> const &, std::string &);
bool CommandServerBan(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0ABB0
{
	// `anonymous-namespace'::CommandServerBan
	// static ...; // 0x10A0AFCD
	// static ...; // 0x10A0AFC9
	// static ...; // 0x10A0AFC4
	// static ...; // 0x10A0AF94
	// static ...; // 0x10A0AF8C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string banType;
	{
		// std::string ip;
	}
	{
		// std::string uid;
	}
	{
		// std::string name;
	}
	todo("implement");
	bool __result = _sub_10A0ABB0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A10460(std::vector<std::string> const &, std::string &);
bool CommandServerUnban(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A10460
{
	// `anonymous-namespace'::CommandServerUnban
	// static ...; // 0x10A10A81
	// static ...; // 0x10A10A7D
	// static ...; // 0x10A10A78
	// static ...; // 0x10A10A48
	// static ...; // 0x10A10A40
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string banType;
	{
		// std::string ip;
	}
	{
		// std::string uid;
	}
	{
		// std::string name;
	}
	todo("implement");
	bool __result = _sub_10A10460(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A0DAB0(std::vector<std::string> const &, std::string &);
bool CommandServerMutePlayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0DAB0
{
	// `anonymous-namespace'::CommandServerMutePlayer
	// static ...; // 0x10A0DC68
	// static ...; // 0x10A0DC60
// $LN14:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::PlayerSession *player;
	// __int32 index;
	// Blam::Network::Session *session;
	// bool result;
	// unsigned __int32 pos;
	todo("implement");
	bool __result = _sub_10A0DAB0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A10C20(std::vector<std::string> const &, std::string &);
bool CommandServerUnmutePlayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A10C20
{
	// `anonymous-namespace'::CommandServerUnmutePlayer
	// static ...; // 0x10A10DD8
	// static ...; // 0x10A10DD0
// $LN14:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::PlayerSession *player;
	// __int32 index;
	// Blam::Network::Session *session;
	// bool result;
	// unsigned __int32 pos;
	todo("implement");
	bool __result = _sub_10A10C20(Arguments, returnInfo);
	return __result;
}

bool CommandServerClearAllMutes(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B1E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerClearAllMutes@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerClearAllMutes
	// std::string &returnInfo;

	Server::Chat::ClearAllPlayersMuteStatus();

	return true;
}

bool CommandServerClearTempBans(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerClearTempBans@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerClearTempBans
	// std::string &returnInfo;

	Server::TempBanList::Instance().ClearList();
	returnInfo = "Temporary Bans Cleared";
	return true;
}

_extern bool _sub_10A0E3A0(std::vector<std::string> const &, std::string &);
bool CommandServerRemoveTempBan(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0E3A0
{
	// `anonymous-namespace'::CommandServerRemoveTempBan
	// static ...; // 0x10A0E78E
	// static ...; // 0x10A0E783
	// static ...; // 0x10A0E77A
	// static ...; // 0x10A0E774
	// static ...; // 0x10A0E738
	// static ...; // 0x10A0E730
// $LN21:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::map<std::string,int> list;
	// std::string arg;
	// __int32 i;
	// __int32 index;
	{
		// bool success;
	}
	{
		// std::map<std::string,int> &<range>$L0;
		// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > <begin>$L0;
		// std::_Default_sentinel <end>$L0;
		{
			// std::pair<std::string const ,int> entry;
		}
	}
	todo("implement");
	bool __result = _sub_10A0E3A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A0D020(std::vector<std::string> const &, std::string &);
bool CommandServerListTempBans(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0D020
{
	// `anonymous-namespace'::CommandServerListTempBans
	// static ...; // 0x10A0D2C6
	// static ...; // 0x10A0D2BB
	// static ...; // 0x10A0D2B2
	// static ...; // 0x10A0D2AC
	// static ...; // 0x10A0D270
	// static ...; // 0x10A0D268
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::map<std::string,int> list;
	// std::stringstream ss;
	// __int32 i;
	{
		// std::map<std::string,int> &<range>$L0;
		// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > <begin>$L0;
		// std::_Default_sentinel <end>$L0;
		{
			// std::pair<std::string const ,int> entry;
		}
	}
	todo("implement");
	bool __result = _sub_10A0D020(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A0C5F0(std::vector<std::string> const &, std::string &);
bool CommandServerListPlayers(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0C5F0
{
	// `anonymous-namespace'::CommandServerListPlayers
	// static ...; // 0x10A0C9B0
	// static ...; // 0x10A0C9AB
	// static ...; // 0x10A0C9A7
	// static ...; // 0x10A0C9A4
	// static ...; // 0x10A0C968
	// static ...; // 0x10A0C960
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 playerIdx;
	// std::stringstream ss;
	// Blam::Network::Session *session;
	{
		// Blam::Network::PlayerSession player;
		// char uid[17];
		// std::string name;
		{
			// Blam::Network::NetworkAddress ip;
		}
	}
	todo("implement");
	bool __result = _sub_10A0C5F0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A0CAB0(std::vector<std::string> const &, std::string &);
bool CommandServerListPlayersJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0CAB0
{
	// `anonymous-namespace'::CommandServerListPlayersJSON
	// static ...; // 0x10A0CEF5
	// static ...; // 0x10A0CEEE
	// static ...; // 0x10A0CEEA
	// static ...; // 0x10A0CEE4
	// static ...; // 0x10A0CEA8
	// static ...; // 0x10A0CEA0
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// __int32 playerIdx;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// Blam::Network::Session *session;
	{
		// Blam::Network::PlayerSession player;
		// std::stringstream color;
		// char uid[17];
	}
	todo("implement");
	bool __result = _sub_10A0CAB0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A0D720(std::vector<std::string> const &, std::string &);
bool CommandServerMode(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0D720
{
	// `anonymous-namespace'::CommandServerMode
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 previous;
	// __int32 serverMode;
	// bool retVal;
	todo("implement");
	bool __result = _sub_10A0D720(Arguments, returnInfo);
	return __result;
}

bool CommandServerLobbyType(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0D380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerLobbyType@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerLobbyType
	// static ...; // 0x10A0D650
	// static ...; // 0x10A0D648
// $LN18:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string previous;
	// __int32 lobbyType;
	// bool retVal;

	if (Arguments.size() < 1 || Arguments.size() > 1) {
		returnInfo = std::to_string(Blam::Network::GetLobbyType());
		return true;
	}

	auto previous = std::to_string(Blam::Network::GetLobbyType());
	auto lobbyType = -1;
	try
	{
		lobbyType = std::atoi(Arguments[0].c_str());
	}
	catch (std::logic_error&)
	{
	}

	if (lobbyType < 0 || lobbyType > 5) {
		returnInfo = "0 = Campaign; 1 = Matchmaking; 2 = Multiplayer; 3 = Forge; 4 = Theater; 5 = Mainmenu;";
		return false;
	}

	bool retVal = Blam::Network::SetLobbyType(lobbyType);
	if (retVal)
	{
		returnInfo = "Changed lobby type " + previous + " -> " + std::to_string(lobbyType);
		return true;
	}
	return false;
}

_extern bool _sub_10A0E040(std::vector<std::string> const &, std::string &);
bool CommandServerPing(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0E040
{
	// `anonymous-namespace'::CommandServerPing
	// static ...; // 0x10A0E2CC
	// static ...; // 0x10A0E2C4
// $LN17:
// $LN14:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::SessionMembership *membership;
	// __int32 channelIndex;
	// Blam::Network::Session *session;
	{
		// Blam::Network::NetworkAddress blamAddress;
		// unsigned short port;
	}
	todo("implement");
	bool __result = _sub_10A0E040(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A0EAC0(std::vector<std::string> const &, std::string &);
bool CommandServerShuffleTeams(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0EAC0
{
	// `anonymous-namespace'::CommandServerShuffleTeams
	// static ...; // 0x10A0EEDE
	// static ...; // 0x10A0EED8
	// static ...; // 0x10A0EEB4
	// static ...; // 0x10A0EEAC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 numTeams;
	// __int32 teamIndex;
	// Modules::ModuleServer &moduleServer;
	// Blam::Network::SessionMembership *membership;
	// __int32 minTeams;
	// std::bitset<17> peers;
	// __int32 numPlayers;
	// static __int32 `CommandServerShuffleTeams'::`2'::$TSS1; // 0x12456064
	// __int32 players[16];
	// unsigned long minTeamSize;
	// unsigned long maxPlayers;
	// static std::random_device `CommandServerShuffleTeams'::`2'::rng; // 0x1245605E
	// Blam::Network::Session *session;
	// static std::mersenne_twister_engine<unsigned int,32,624,397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253> `CommandServerShuffleTeams'::`2'::urng; // 0x12456068
	// static __int32 `CommandServerShuffleTeams'::`2'::$TSS0; // 0x12456060
	{
		// __int32 player;
	}
	{
		// __int32 i;
	}
	todo("implement");
	bool __result = _sub_10A0EAC0(Arguments, returnInfo);
	return __result;
}

bool CommandServerGetEndpoint(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerGetEndpoint@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerGetEndpoint
	// std::string &returnInfo;

	return GetEndpoint(Arguments[0], returnInfo);
}

_extern void _sub_10A13AF0(Blam::Network::NetworkAddress const &, unsigned __int32, unsigned short, unsigned __int32);
void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency) // 0x10A13AF0
{
	// `anonymous-namespace'::PongReceived
	// static ...; // 0x10A13DB4
	// Blam::Network::NetworkAddress const &from;
	// unsigned __int32 timestamp;
	// unsigned short id;
	// unsigned __int32 latency;
	// std::string ipStr;
	// std::string message;
	todo("implement");
	_sub_10A13AF0(from, timestamp, id, latency);
}

bool HitmarkersEnabledChanged(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A13A60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HitmarkersEnabledChanged@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::HitmarkersEnabledChanged
	// std::string &returnInfo;
	// bool enabled;
	// Modules::ModuleServer &serverModule;

	Modules::ModuleServer &module = Modules::ModuleServer::Instance();
	bool enabled = module.VarHitMarkersEnabledClient->ValueInt != 0;
	Patches::Tweaks::EnableHitmarkers(enabled);

	return true;
}

bool SprintStateChanged(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A140E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SprintStateChanged@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::SprintStateChanged
	// std::string &returnInfo;
	// unsigned long state;
	// Modules::ModuleServer &serverModule;

	auto &serverModule = Modules::ModuleServer::Instance();
	auto state = serverModule.VarServerSprintStateClient->ValueInt;
	Patches::Sprint::SetState(state);
	return true;
}

bool BottomlessClipEnabledChanged(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A07D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BottomlessClipEnabledChanged@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::BottomlessClipEnabledChanged
	// std::string &returnInfo;
	// bool enabled;
	// Modules::ModuleServer &serverModule;

	Modules::ModuleServer &serverModule = Utils::Singleton<Modules::ModuleServer>::Instance();
	bool enabled = serverModule.VarServerBottomlessClipEnabledClient->ValueInt != 0;
	Patches::Weapon::SetBottomlessClip(enabled);
	return true;
}

bool UnlimitedSprintEnabledChanged(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A146A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UnlimitedSprintEnabledChanged@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::UnlimitedSprintEnabledChanged
	// std::string &returnInfo;
	// Modules::ModuleServer &serverModule;
	// bool unlimited;

	Modules::ModuleServer &moduleServer = Utils::Singleton<Modules::ModuleServer>::Instance();
	bool unlimited = moduleServer.VarServerSprintUnlimitedClient->ValueInt != 0;
	Patches::Sprint::SetUnlimited(unlimited);
	return true;
}

bool CommandServerSubmitVote(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0F000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerSubmitVote@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerSubmitVote
	// static ...; // 0x10A0F12C
	// static ...; // 0x10A0F124
// $LN10:
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 vote;
	// unsigned __int32 pos;

	if (Arguments.size() <= 0)
	{
		returnInfo = "You must supply a vote.";
		return false;
	}
	auto vote = -1;
	size_t pos = 0;
	try
	{
		vote = std::stoi(Arguments[0], &pos);
	}
	catch (std::logic_error&)
	{
	}
	if (pos != Arguments[0].length() || vote < 1 || vote > 6)
	{
		returnInfo = "Invalid Vote";
		return false;
	}
	Server::Voting::SendVoteToHost(vote);

	return true;
}

_extern bool _sub_10A0E8A0(std::vector<std::string> const &, std::string &);
bool CommandServerSay(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0E8A0
{
	// `anonymous-namespace'::CommandServerSay
	// static ...; // 0x10A0EA34
	// static ...; // 0x10A0EA2C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::Session *session;
	// std::string message;
	{
		// std::vector<std::string> const &<range>$L0;
		// std::string const *<begin>$L0;
		// std::string const *<end>$L0;
		{
			// std::string const &word;
		}
	}
	todo("implement");
	bool __result = _sub_10A0E8A0(Arguments, returnInfo);
	return __result;
}

bool CommandServerPM(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0DCF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerPM@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerPM
	// static ...; // 0x10A0DF78
	// static ...; // 0x10A0DF60
	// static ...; // 0x10A0DF58
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 peer;
	// std::string playerName;
	// Blam::Network::Session *session;
	// std::string message;

	if (Arguments.size() <= 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}

	auto playerName = Arguments[0];
	std::string message = Arguments[1];

	auto* session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
	{
		returnInfo = "You must be hosting a game to use this command";
		return false;
	}
	auto peer = FindPlayerByName(playerName, true);
	if (peer < 0)
	{
		returnInfo = "Player \"" + playerName + "\" not found.";
		return false;
	}
	Server::Chat::SendServerMessage("(PM) " + message, peer);

	return true;
}

_extern bool _sub_10A12C20(std::vector<std::string> const &, std::string &);
bool EncryptMessageWithPublicKey(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A12C20
{
	// `anonymous-namespace'::EncryptMessageWithPublicKey
	// static ...; // 0x10A12DFB
	// static ...; // 0x10A12DF4
	// static ...; // 0x10A12DD0
	// static ...; // 0x10A12DC8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Modules::ModulePlayer &modulePlayer;
	// char const *const PasswordChars;
	// std::string pubKey;
	// Modules::ModuleServer &moduleServer;
	// std::string encryptedString;
	// std::string value;
	todo("implement");
	bool __result = _sub_10A12C20(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A10E60(std::vector<std::string> const &, std::string &);
bool CommandWebsocketInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A10E60
{
	// `anonymous-namespace'::CommandWebsocketInfo
	// static ...; // 0x10A11273
	// static ...; // 0x10A11270
	// static ...; // 0x10A1124C
	// static ...; // 0x10A11244
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::string ip;
	// Blam::Network::Session *session;
	todo("implement");
	bool __result = _sub_10A10E60(Arguments, returnInfo);
	return __result;
}

_extern void _sub_10A14740(std::string);
void UpdatePersistentMod(std::string mod) // 0x10A14740
{
	// `anonymous-namespace'::UpdatePersistentMod
	// std::string mod;
	// __int32 lobbyType;
	todo("implement");
	_sub_10A14740(mod);
}

_extern bool _sub_10A094E0(std::vector<std::string> const &, std::string &);
bool CommandLoadMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A094E0
{
	// `anonymous-namespace'::CommandLoadMod
	// std::string &returnInfo;
	// std::string const &path;
	todo("implement");
	bool __result = _sub_10A094E0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A08C10(std::vector<std::string> const &, std::string &);
bool CommandListMods(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A08C10
{
	// `anonymous-namespace'::CommandListMods
	// static ...; // 0x10A0930E
	// static ...; // 0x10A0930B
	// static ...; // 0x10A092FD
	// static ...; // 0x10A092F4
	// static ...; // 0x10A092EB
	// static ...; // 0x10A092E3
	// static ...; // 0x10A092DC
	// static ...; // 0x10A0927C
	// static ...; // 0x10A09274
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// c_mod_package_manager::c_threadsafe_iterator it;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// c_mod_package_manager &package_manager;
	{
		// char buffer[32];
		// std::string version;
		// std::string hash_str;
		// std::string filename;
		// tm *convertedLocal;
		// s_static_string<32> metadata_name;
	}
	todo("implement");
	bool __result = _sub_10A08C10(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A08250(std::vector<std::string> const &, std::string &);
bool CommandListModInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A08250
{
	// `anonymous-namespace'::CommandListModInfo
	// static ...; // 0x10A08A0E
	// static ...; // 0x10A08A0B
	// static ...; // 0x10A08A03
	// static ...; // 0x10A089FA
	// static ...; // 0x10A089EC
	// static ...; // 0x10A089E3
	// static ...; // 0x10A089DB
	// static ...; // 0x10A089D4
	// static ...; // 0x10A08968
	// static ...; // 0x10A08960
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// c_mod_package_manager::c_threadsafe_iterator it;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// std::string modHash;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// c_mod_package_manager &package_manager;
	{
		// char buffer[32];
		// std::string version;
		// std::string hash_str;
		// std::string filename;
		// tm *convertedLocal;
		// s_static_string<32> metadata_name;
	}
	todo("implement");
	bool __result = _sub_10A08250(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A07EB0(std::vector<std::string> const &, std::string &);
bool CommandListModFiles(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A07EB0
{
	// `anonymous-namespace'::CommandListModFiles
	// static ...; // 0x10A0817E
	// static ...; // 0x10A08173
	// static ...; // 0x10A08168
	// static ...; // 0x10A0815F
	// static ...; // 0x10A08155
	// static ...; // 0x10A08150
	// static ...; // 0x10A080FC
	// static ...; // 0x10A080F4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	{
		// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
		// std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry> modFileList;
		// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
		{
			// std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry> &<range>$L0;
			// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > > <begin>$L0;
			// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > > <end>$L0;
			{
				// std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> fileEntry;
				{
					// std::string file;
				}
			}
		}
	}
	todo("implement");
	bool __result = _sub_10A07EB0(Arguments, returnInfo);
	return __result;
}

bool CommandEnumerateMods(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A07E50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandEnumerateMods@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandEnumerateMods
	// std::string &returnInfo;
	// c_mod_package_manager &package_manager;

	c_mod_package_manager *package_manager = &c_mod_system::get_package_manager();

	package_manager->begin_enumerate();
	return true;
}

_extern bool _sub_10A07DA0(std::vector<std::string> const &, std::string &);
bool CommandDeleteMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A07DA0
{
	// `anonymous-namespace'::CommandDeleteMod
	// std::string &returnInfo;
	// c_mod_package_manager &package_manager;
	todo("implement");
	bool __result = _sub_10A07DA0(Arguments, returnInfo);
	return __result;
}

bool VariablePlayersInfoClientUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A149E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariablePlayersInfoClientUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariablePlayersInfoClientUpdate
	// std::string &returnInfo;

	if (Arguments.empty())
	{
		return false;
	}

	Player::CPlayersInfo::Update(Arguments[0]);

	return true;
}

bool CommandRefreshServerFilters(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A09700
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandRefreshServerFilters@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandRefreshServerFilters
	// std::string &returnInfo;

	Modules::ModuleServer::Instance().refreshServerFilters();
	returnInfo = "Refreshed server.json data";
	return true;
}
