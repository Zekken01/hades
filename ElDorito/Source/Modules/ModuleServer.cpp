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

#include "PersistentMemory/PersistentMemorySystem.hpp"  // hades: added for 0x10A14740

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

namespace Server { namespace VariableSynchronization { extern void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable); } }  // hades: added for 0x109FE0E0

#include "Utils/Logger.hpp"  // hades: added for 0x10A0F2D0
namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x10A0F2D0

#include "Modules/ModuleVoting.hpp"  // hades: added for 0x10A0D720
namespace Server { namespace Voting { bool CancelVoteInProgress(); } }  // hades: added for 0x10A0D720
namespace Web { namespace Ui { namespace Voting { void Hide(); } } }  // hades: added for 0x10A0D720

namespace Utils { namespace String { template<typename t_type> std::string Join(std::vector<t_type> const &items, char const *separator); } }  // hades: added for 0x10A11AA0

extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x10A0C5F0

namespace Server { namespace Signaling { extern std::string GetPassword(); extern unsigned short GetPort(); } }  // hades: added for 0x10A10E60

namespace Utils { namespace Cryptography { extern std::string ReformatKey(bool isPrivateKey, std::string key); extern bool PublicEncrypt(std::string publicKey, void *data, unsigned __int32 dataSize, std::string &encrypted); } }  // hades: added for 0x10A12C20
namespace Server { namespace Stats { extern void GetStatsPublicKey(std::string &dest); } }  // hades: added for 0x10A12C20

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
static void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency);
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

namespace Patches::PlayerUid { bool ParseUid(std::string const &str, unsigned long long *out); }  // hades: added for 0X10A07BD0

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		// extern std::string DefaultBanListPath; // 0x12456040  // hades: defined (with its initialiser) elsewhere now
	}
	using namespace hades_file_local_Server;
}
namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x12455E80  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x12455F60  // hades: defined in VotingTypes.hpp, one copy per file
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
	ModuleServer::ModuleServer() : ModuleBase("Server") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x109FE0E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleServer@Modules@@QAE@XZ");
		// Modules::ModuleServer *const this;
		// Modules::Command *syncTestServer;
		// Modules::Command *syncTestClient;

		VarServerName = AddVariableString("Name", "server_name", "The name of the server (limited to 128 characters)", CommandFlags(eCommandFlagsArchived | eCommandFlagsReplicated), "HaloOnline Server", VarServerNameUpdated);
		VarServerNameClient = AddVariableString("NameClient", "server_name_client", "", eCommandFlagsInternal, "");
		Server::VariableSynchronization::Synchronize(VarServerName, VarServerNameClient);
		VarServerHost = AddVariableString("HostPlayer", "server_player_host_name", "The host name of the server", CommandFlags(eCommandFlagsInternal | eCommandFlagsReplicated), "");
		VarServerHostClient = AddVariableString("HostPlayerClient", "server_player_host_name_client", "", eCommandFlagsInternal, "");
		Server::VariableSynchronization::Synchronize(VarServerHost, VarServerHostClient);
		AddCommand("EncryptMessage", "encryptmessage", "encrypts a message.", eCommandFlagsHidden, EncryptMessageWithPublicKey);
		VarServerMessage = AddVariableString("Message", "server_msg", "Text to display on the loading screen (limited to 512 chars)", CommandFlags(eCommandFlagsArchived | eCommandFlagsReplicated), "");
		VarServerMessageClient = AddVariableString("MessageClient", "server_msg_client", "", eCommandFlagsInternal, "");
		Server::VariableSynchronization::Synchronize(VarServerMessage, VarServerMessageClient);
		VarServerPassword = AddVariableString("Password", "password", "The server password", eCommandFlagsArchived, "");
		VarShouldSubmitStats = AddVariableInt("ShouldSubmitStats", "shouldsubmitstats", "Sets whether the server should ever submit stats to the stats servers", eCommandFlagsArchived, 1);
		VarShouldSubmitStats->ValueIntMin = 0;
		VarShouldSubmitStats->ValueIntMax = 1;
		VarServerCountdown = AddVariableInt("Countdown", "countdown", "The number of seconds to wait at the start of the game", eCommandFlagsArchived, 5);
		VarServerCountdown->ValueIntMin = 0;
		VarServerCountdown->ValueIntMax = 20;
		VarServerCountdownClient = AddVariableInt("CountdownClient", "countdown_client", "The number of seconds to wait at the start of the game", eCommandFlagsInternal, 5, VariableServerCountdownUpdate);
		Server::VariableSynchronization::Synchronize(VarServerCountdown, VarServerCountdownClient);
		VarShowDisconnectedPlayers = AddVariableInt("ShowDisconnectedPlayers", "show_disconnected_players", "Show disconnected players in the scoreboard", eCommandFlagsArchived, 0);
		VarShowDisconnectedPlayers->ValueIntMin = 0;
		VarShowDisconnectedPlayers->ValueIntMax = 1;
		VarShowDisconnectedPlayersClient = AddVariableInt("ShowDisconnectedPlayersClient", "show_disconnected_players_client", "Show disconnected players in the scoreboard", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarShowDisconnectedPlayers, VarShowDisconnectedPlayersClient);
		VarServerPodiumEnabled = AddVariableInt("PodiumEnabled", "podium_enabled", "should run podium hsc script at game finish. 0 = Disabled; 1 = Enabled; 2 = Forged maps Only (When podium was placed on a forged map)", eCommandFlagsArchived, 0);
		VarServerPodiumEnabled->ValueIntMin = 0;
		VarServerPodiumEnabled->ValueIntMax = 2;
		VarServerPodiumEnabledClient = AddVariableInt("PodiumEnabledClient", "podium_enabled_client", "should run podium hsc script at game finish", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerPodiumEnabled, VarServerPodiumEnabledClient);
		VarServerPodiumForgeEnabled = AddVariableInt("PodiumEnabledDuringForge", "podium_enabled_during_forge", "should run podium hsc script in forge at game finish", eCommandFlagsArchived, 0);
		VarServerPodiumForgeEnabled->ValueIntMin = 0;
		VarServerPodiumForgeEnabled->ValueIntMax = 1;
		VarServerPodiumForgeEnabledClient = AddVariableInt("PodiumEnabledDuringForgeClient", "podium_enabled_during_forge_client", "should run podium hsc script in forge at game finish", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerPodiumForgeEnabled, VarServerPodiumForgeEnabledClient);
		VarServerKillCommandDuringPodiumEnabled = AddVariableInt("KillCommandDuringPodiumEnabled", "kill_command__during_podium_enabled", "Controls whether players can use the kill during the end game podium", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0);
		VarServerKillCommandDuringPodiumEnabled->ValueIntMin = 0;
		VarServerKillCommandDuringPodiumEnabled->ValueIntMax = 1;
		VarServerCountdownLobby = AddVariableInt("CountdownLobby", "countdown_lobby", "The number of seconds to wait in the lobby before the game starts", eCommandFlagsArchived, 3);
		VarServerCountdownLobby->ValueIntMin = 0;
		VarServerCountdownLobby->ValueIntMax = 20;
		VarServerMaxPlayers = AddVariableInt("MaxPlayers", "maxplayers", "Maximum number of connected players", eCommandFlagsArchived, 0x10, VariableServerMaxPlayersUpdate);
		VarServerMaxPlayers->ValueIntMin = 1;
		VarServerMaxPlayers->ValueIntMax = 16;
		VarServerPort = AddVariableInt("Port", "server_port", "The port number the HTTP server runs on, the game uses Server.GamePort", eCommandFlagsArchived, 0x2DFF);
		VarServerPort->ValueIntMin = 1;
		VarServerPort->ValueIntMax = 0xFFFF;
		VarServerGamePort = AddVariableInt("GamePort", "server_gameport", "The port number used by Halo Online", eCommandFlagsArchived, 0x2DFE, VariableServerGamePortUpdate);
		VarServerGamePort->ValueIntMin = 1;
		VarServerGamePort->ValueIntMax = 0xFFFF;
		VarFileServerPort = AddVariableInt("FileServerPort", "file_server_port", "The port number used by the file server (for serving mod packages)", eCommandFlagsArchived, 0x2E02);
		VarServerGamePort->ValueIntMin = 1;
		VarServerGamePort->ValueIntMax = 0xFFFF;
		VarFileServerEnabled = AddVariableInt("FileServerEnabled", "file_server_enabled", "Enable/Disable local file server (for serving mod packages)", eCommandFlagsArchived, 0);
		VarFileServerEnabled->ValueIntMin = 0;
		VarFileServerEnabled->ValueIntMax = 1;
		VarServerShouldAnnounce = AddVariableInt("ShouldAnnounce", "should_announce", "Controls whether the server will be announced to the master servers", eCommandFlagsArchived, 1, VariableServerShouldAnnounceUpdate);
		VarServerShouldAnnounce->ValueIntMin = 0;
		VarServerShouldAnnounce->ValueIntMax = 1;
		AddCommand("Connect", "connect", "Begins establishing a connection to a server", eCommandFlagsRunOnMainMenu, CommandServerConnect, { "host:port The server info to connect to", "password(string) The password for the server" });
		AddCommand("Announce", "announce", "Announces this server to the master servers", eCommandFlagsHostOnly, CommandServerAnnounce);
		AddCommand("Unannounce", "unannounce", "Notifies the master servers to remove this server", eCommandFlagsHostOnly, CommandServerUnannounce);
		AddCommand("KickPlayer", "k", "Kicks a player from the game by name (host only)", eCommandFlagsHostOnly, CommandServerKickPlayer, { "playername The name of the player to kick" });
		AddCommand("KickBanPlayer", "kb", "Kicks and IP bans a player from the game by name (host only)", eCommandFlagsHostOnly, CommandServerBanPlayer, { "playername The name of the player to ban" });
		AddCommand("KickTempBanPlayer", "ktb", "Kicks and temporarily IP bans a player from the game by name (host only)", eCommandFlagsHostOnly, CommandServerTempBanPlayer, { "playername The name of the player to ban" });
		AddCommand("KickUid", "ku", "Kicks players from the game by UID (host only)", eCommandFlagsHostOnly, CommandServerKickPlayerUid, { "uid The UID of the players to kick" });
		AddCommand("KickBanUid", "kbu", "Kicks and IP bans players from the game by UID (host only)", eCommandFlagsHostOnly, CommandServerBanPlayerUid, { "uid The UID of the players to ban" });
		AddCommand("KickTempBanUid", "ktbu", "Kicks and temporarily IP bans players from the game by UID (host only)", eCommandFlagsHostOnly, CommandServerTempBanPlayerUid, { "uid The UID of the players to ban" });
		AddCommand("KickIndex", "ki", "Kicks a player from the game by index (host only)", eCommandFlagsHostOnly, CommandServerKickPlayerIndex, { "index The index of the player to kick" });
		AddCommand("KickBanIndex", "kbi", "Kicks and IP bans a player from the game by index (host only)", eCommandFlagsHostOnly, CommandServerBanPlayerIndex, { "index The index of the player to ban" });
		AddCommand("KickBan", "kickban", "Adds to the ban list and kicks the player", eCommandFlagsHostOnly, CommandServerKickBan, { "type The ban type (ip, uid, name)", "val The value to add to the ban list" });
		AddCommand("AddBan", "addban", "Adds to the ban list (does NOT kick anyone)", eCommandFlagsHostOnly, CommandServerBan, { "type The ban type (ip, uid, name)", "val The value to add to the ban list" });
		AddCommand("Unban", "unban", "Removes from the ban list", eCommandFlagsHostOnly, CommandServerUnban, { "type The ban type (ip, uid,  name)", "val The value to remove from the ban list" });
		AddCommand("MutePlayer", "mutep", "Mutes Player from Chat", eCommandFlagsHostOnly, CommandServerMutePlayer, { "type the players Index", "Index The player index of the player to mute" });
		AddCommand("UnmutePlayer", "unmutep", "unmutes Player from Chat", eCommandFlagsHostOnly, CommandServerUnmutePlayer, { "type the players Index", "Index The player index of the player to unmute" });
		AddCommand("ClearMutes", "clearmutes", "unmutes all player from chat", eCommandFlagsHostOnly, CommandServerClearAllMutes);
		AddCommand("ClearTempBans", "cleartempbans", "clears the temp ban list", eCommandFlagsHostOnly, CommandServerClearTempBans);
		AddCommand("RemoveTempBan", "removetempban", "Removes a player by index from the temp ban list", eCommandFlagsHostOnly, CommandServerRemoveTempBan);
		AddCommand("ListTempBans", "listtempbans", "List all ips that have a temporary ban", eCommandFlagsHostOnly, CommandServerListTempBans);
		AddCommand("ListPlayers", "list", "Lists players in the game", eCommandFlagsNone, CommandServerListPlayers);
		AddCommand("ListPlayersJSON", "listjson", "Returns JSON with data about the players in the game. Intended for server browser use only.", eCommandFlagsHidden, CommandServerListPlayersJSON);
		AddCommand("Ping", "ping", "Ping a server", eCommandFlagsNone, CommandServerPing, { "[ip] The IP address of the server to ping. Omit to ping the host." });
		AddCommand("ShuffleTeams", "shuffleteams", "Evenly distributes players between the red and blue teams", eCommandFlagsHostOnly, CommandServerShuffleTeams);
		VarNumTeams = AddVariableInt("NumberOfTeams", "num_teams", "Set the desired number of teams", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 2);
		VarNumTeams->ValueIntMin = 1;
		VarNumTeams->ValueIntMax = 8;
		VarMinTeamSize = AddVariableInt("TeamSize", "min_team_size", "Set the minimum number of players each team must have before a new team is assigned", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 1);
		VarMinTeamSize->ValueIntMin = 1;
		VarMinTeamSize->ValueIntMax = 8;
		AddCommand("Say", "say", "Sends a chat message as the server", eCommandFlagsHostOnly, CommandServerSay);
		AddCommand("PM", "pm", "Sends a pm to a player as the server. First argument is the player name, second is the message in quotes", eCommandFlagsHostOnly, CommandServerPM);
		AddCommand("SubmitVote", "submitvote", "Sumbits a vote", eCommandFlagsNone, CommandServerSubmitVote, { "The vote to send to the host" });
		AddCommand("Mode", "mode", "Changes the network mode for the server. 0 = Xbox Live (Open Party); 1 = Xbox Live (Friends Only); 2 = Xbox Live (Invite Only); 3 = Online; 4 = Offline;", eCommandFlagsNone, CommandServerMode, { "The network mode" });
		AddCommand("LobbyType", "lobbytype", "Changes the lobby type for the server. 0 = Campaign; 1 = Matchmaking; 2 = Multiplayer; 3 = Forge; 4 = Theater;", eCommandFlagsNone, CommandServerLobbyType, { "The lobby type" });
		VarServerDedicated = AddVariableInt("Dedicated", "dedicated", "Used only to let clients know if the server is dedicated or not", eCommandFlagsReplicated, 0);
		VarServerDedicatedClient = AddVariableInt("DedicatedClient", "dedicated_client", "", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerDedicated, VarServerDedicatedClient);
		VarServerSprintState = AddVariableInt("Sprint", "sprint", "Controls whether sprint is enabled on the server. 0 = Disabled Globally; 1 = Enabled Globally; 2 = Inherited by gametype settings;", CommandFlags(eCommandFlagsArchived | eCommandFlagsReplicated), 2);
		VarServerSprintState->ValueIntMin = 0;
		VarServerSprintState->ValueIntMax = 2;
		VarServerSprintStateClient = AddVariableInt("SprintClient", "sprint_client", "", eCommandFlagsInternal, 2, SprintStateChanged);
		Server::VariableSynchronization::Synchronize(VarServerSprintState, VarServerSprintStateClient);
		VarHitMarkersEnabled = AddVariableInt("HitMarkersEnabled", "hitmarkersenabled", "Controls whether or not hitmarkers are enabled on this server", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarHitMarkersEnabledClient = AddVariableInt("HitMarkersEnabledClient", "hitmarkersenabled_client", "", eCommandFlagsInternal, 0, HitmarkersEnabledChanged);
		Server::VariableSynchronization::Synchronize(VarHitMarkersEnabled, VarHitMarkersEnabledClient);
		VarHUDWaypointStyle = AddVariableInt("HUDWaypointStyle", "hud_waypoint_style", "0 = Halo Online, 1 = Halo 3", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarHUDWaypointStyle->ValueIntMin = 0;
		VarHUDWaypointStyle->ValueIntMax = 1;
		VarHUDWaypointStyleClient = AddVariableInt("HUDWaypointStyleClient", "hud_waypoint_style_client", "0 = Halo Online, 1 = Halo 3", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarHUDWaypointStyle, VarHUDWaypointStyleClient);
		VarServerBottomlessClipEnabled = AddVariableInt("BottomlessClipEnabled", "bottomlessclip", "Controls whether bottomless clip is enabled on the server", CommandFlags(eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarServerBottomlessClipEnabledClient = AddVariableInt("BottomlessClipEnabledClient", "bottomlessclip_client", "", eCommandFlagsInternal, 0, BottomlessClipEnabledChanged);
		Server::VariableSynchronization::Synchronize(VarServerBottomlessClipEnabled, VarServerBottomlessClipEnabledClient);
		VarServerSprintUnlimited = AddVariableInt("UnlimitedSprint", "unlimited_sprint", "Controls whether unlimited sprint is enabled on the server", CommandFlags(eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarServerSprintUnlimited->ValueIntMin = 0;
		VarServerSprintUnlimited->ValueIntMax = 1;
		VarServerSprintUnlimitedClient = AddVariableInt("UnlimitedSprintClient", "unlimited_sprint_client", "", eCommandFlagsInternal, 0, UnlimitedSprintEnabledChanged);
		Server::VariableSynchronization::Synchronize(VarServerSprintUnlimited, VarServerSprintUnlimitedClient);
		VarServerDualWieldEnabled = AddVariableInt("DualWieldEnabled", "dualwield", "Controls whether dual wielding is enabled on the server", CommandFlags(eCommandFlagsArchived | eCommandFlagsReplicated), 1);
		VarServerDualWieldEnabledClient = AddVariableInt("DualWieldEnabledClient", "dualwield_client", "", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerDualWieldEnabled, VarServerDualWieldEnabledClient);
		VarServerFallDamageMPEnabled = AddVariableInt("FallDamageMP", "fall_damage_mp", "Controls whether fall damage takes effect in multiplayer on the server", CommandFlags(eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarServerFallDamageMPEnabledClient = AddVariableInt("FallDamageMPClient", "fall_damage_mp_client", "", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerFallDamageMPEnabled, VarServerFallDamageMPEnabledClient);
		VarServerMuteSoundsDuringPostGame = AddVariableInt("MuteSoundsDuringPostGame", "mute_sounds_post_game", "Controls whether the game will mute sounds during the post game time", eCommandFlagsArchived, 1);
		VarServerMuteSoundsDuringPostGame->ValueIntMin = 0;
		VarServerMuteSoundsDuringPostGame->ValueIntMax = 1;
		VarServerMuteSoundsDuringPostGameClient = AddVariableInt("MuteSoundsDuringPostGameClient", "mute_sounds_post_game_client", "", eCommandFlagsInternal, 1);
		Server::VariableSynchronization::Synchronize(VarServerMuteSoundsDuringPostGame, VarServerMuteSoundsDuringPostGameClient);
		VarPlayersInfo = AddVariableString("PlayersInfo", "players_info", "Emblem and Rank info for each player", eCommandFlagsReplicated, "{}");
		VarPlayersInfoClient = AddVariableString("PlayersInfoClient", "players_info_client", "Emblem and Rank info for each player", eCommandFlagsInternal, "{}", VariablePlayersInfoClientUpdate);
		Server::VariableSynchronization::Synchronize(VarPlayersInfo, VarPlayersInfoClient);
		VarPlayersPingInfo = AddVariableString("PlayersPingInfo", "players_pint_info", "ping info for each player", eCommandFlagsReplicated, "{}");
		VarPlayersPingInfoClient = AddVariableString("PlayersPingInfoClient", "players_ping_info_client", "ping info for each player", eCommandFlagsInternal, "{}");
		Server::VariableSynchronization::Synchronize(VarPlayersPingInfo, VarPlayersPingInfoClient);
		VarServerShowPlayerPing = AddVariableInt("ShowPlayerPing", "show_player_ping", "Controls whether the game will show ping on client scoreboards", eCommandFlagsArchived, 1);
		VarServerShowPlayerPing->ValueIntMin = 0;
		VarServerShowPlayerPing->ValueIntMax = 1;
		VarServerAssassinationEnabled = AddVariableInt("AssassinationEnabled", "assassination", "Controls whether assassinations are enabled on the server", CommandFlags(eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarServerAssassinationEnabledClient = AddVariableInt("AssassinationEnabledClient", "assassination_client", "Controls whether assassinations are enabled on the server", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerAssassinationEnabled, VarServerAssassinationEnabledClient);
		VarFloodFilterEnabled = AddVariableInt("FloodFilterEnabled", "floodfilter", "Controls whether chat flood filtering is enabled", eCommandFlagsArchived, 1);
		VarFloodMessageScoreShort = AddVariableInt("FloodMessageScoreShort", "floodscoreshort", "Sets the flood filter score for short messages", eCommandFlagsArchived, 2);
		VarFloodMessageScoreLong = AddVariableInt("FloodMessageScoreLong", "floodscorelong", "Sets the flood filter score for long messages", eCommandFlagsArchived, 5);
		VarFloodTimeoutScore = AddVariableInt("FloodTimeoutScore", "floodscoremax", "Sets the flood filter score that triggers a timeout", eCommandFlagsArchived, 0xA);
		VarFloodTimeoutSeconds = AddVariableInt("FloodTimeoutSeconds", "floodtimeout", "Sets the timeout period in seconds before a spammer can send messages again", eCommandFlagsArchived, 0x78);
		VarFloodTimeoutResetSeconds = AddVariableInt("FloodTimeoutResetSeconds", "floodtimeoutreset", "Sets the period in seconds before a spammer's next timeout is reset", eCommandFlagsArchived, 0x708);
		VarChatLogEnabled = AddVariableInt("ChatLogEnabled", "chatlog", "Controls whether chat logging is enabled", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), 1);
		VarChatLogFile = AddVariableString("ChatLogFile", "chatlogfile", "Sets the name of the file to log chat to", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), "logs\\chat.log");
		VarListPlayersLogEnabled = AddVariableInt("ListPlayersLogEnabled", "listplayerslogenabled", "Controls whether player list logging is enabled", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), 0);
		VarListPlayersLogFile = AddVariableString("ListPlayersLogFile", "listplayerslogfile", "Sets the name of the file to log player lists to", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), "logs\\listplayers.log");
		VarServerKillCommandEnabled = AddVariableInt("KillCommandEnabled", "kill_command_enabled", "Controls whether players can use the kill", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0);
		VarServerKillCommandEnabled->ValueIntMin = 0;
		VarServerKillCommandEnabled->ValueIntMax = 1;
		VarKillCommandMessage = AddVariableString("KillCommandMessage", "kill_command_message", "Sets the message that is sent when a user uses the kill command", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), "Spartans never die, they're just missing in action.");
		VarServerEmotesEnabled = AddVariableInt("EmotesEnabled", "emotes_enabled", "Controls whether players can use emotes", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarServerEmotesEnabled->ValueIntMin = 0;
		VarServerEmotesEnabled->ValueIntMax = 1;
		VarServerEmotesEnabledClient = AddVariableInt("EmotesEnabledClient", "emotes_enabled_client", "", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerEmotesEnabled, VarServerEmotesEnabledClient);
		VarServerEmotesDuringPodiumEnabled = AddVariableInt("EmotesDuringPodiumEnabled", "emotes_during_podium_enabled", "Controls whether players can use emotes during podium", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarServerEmotesDuringPodiumEnabled->ValueIntMin = 0;
		VarServerEmotesDuringPodiumEnabled->ValueIntMax = 1;
		VarServerEmotesDuringPodiumEnabledClient = AddVariableInt("EmotesDuringPodiumEnabledClient", "emotes_enabled_during_podium_client", "", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerEmotesDuringPodiumEnabled, VarServerEmotesDuringPodiumEnabledClient);
		VarServerPostMatchMusicEnabled = AddVariableInt("PostMatchMusicEnabled", "post_match_music_enabled", "Controls whether the postmatch music will play during podium/postmatch time", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarServerPostMatchMusicEnabled->ValueIntMin = 0;
		VarServerPostMatchMusicEnabled->ValueIntMax = 1;
		VarServerPostMatchMusicEnabledClient = AddVariableInt("PostMatchMusicEnabledClient", "post_match_music_enabledclient", "", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerPostMatchMusicEnabled, VarServerPostMatchMusicEnabledClient);
		VarServerNearVictoryMusicEnabled = AddVariableInt("NearVictoryMusicEnabled", "near_victor_music_enabled", "controls if music should start to play in a match based on the scores of the match", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived | eCommandFlagsReplicated), 0);
		VarServerNearVictoryMusicEnabled->ValueIntMin = 0;
		VarServerNearVictoryMusicEnabled->ValueIntMax = 1;
		VarServerNearVictoryMusicEnabledClient = AddVariableInt("NearVictoryMusicEnabledClient", "near_victor_music_enabled_client", "", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarServerNearVictoryMusicEnabled, VarServerNearVictoryMusicEnabledClient);
		VarServerNearVictoryMusicPercent = AddVariableInt("NearVictoryMusicPercentage", "near_victory_music_percent", "controls when music should start to play in a match based on the required score_to_win for the gametype. 0 = disabled", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived | eCommandFlagsReplicated), 0x5A);
		VarServerNearVictoryMusicPercent->ValueIntMin = 0;
		VarServerNearVictoryMusicPercent->ValueIntMax = 100;
		VarServerNearVictoryMusicPercentClient = AddVariableInt("NearVictoryMusicPercentageClient", "near_victory_music_percent_client", "", eCommandFlagsInternal, 0x5A);
		Server::VariableSynchronization::Synchronize(VarServerNearVictoryMusicPercent, VarServerNearVictoryMusicPercentClient);
		VarRconPassword = AddVariableString("RconPassword", "rconpassword", "Password for the remote console", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), "");
		VarChatCommandKickPlayerEnabled = AddVariableInt("ChatCommandKickPlayerEnabled", "chat_command_kick_player_enabled", "Controls whether or not players can vote to kick someone. ", eCommandFlagsArchived, 1);
		VarChatCommandKickPlayerEnabled->ValueIntMin = 0;
		VarChatCommandKickPlayerEnabled->ValueIntMax = 1;
		VarRconLogEnabled = AddVariableInt("RconLogEnabled", "rconlog", "Controls whether rcon logging is enabled", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), 1);
		VarRconConsoleOutputEnabled = AddVariableInt("RconConsoleOutputEnabled", "rcon_console_output_enabled", "Controls whether the console ouput of the server is forwarded out through rcon", eCommandFlagsArchived, 0);
		VarRconConsoleOutputEnabled->ValueIntMin = 0;
		VarRconConsoleOutputEnabled->ValueIntMax = 1;
		VarRconLogFile = AddVariableString("RconLogFile", "rconlogfile", "Sets the name of the file to log rcon messages to", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), "logs\\rcon.log");
		VarChatCommandShuffleTeamsEnabled = AddVariableInt("ChatCommandShuffleTeamsEnabled", "chat_command_shuffle_teams_enabled", "Controls whether or not players can vote to shuffle the teams. ", eCommandFlagsArchived, 1);
		VarChatCommandShuffleTeamsEnabled->ValueIntMin = 0;
		VarChatCommandShuffleTeamsEnabled->ValueIntMax = 1;
		VarChatCommandEndGameEnabled = AddVariableInt("ChatCommandEndGameEnabled", "chat_command_end_game_enabled", "Controls whether or not players can vote to end the game. ", eCommandFlagsArchived, 1);
		VarChatCommandEndGameEnabled->ValueIntMin = 0;
		VarChatCommandEndGameEnabled->ValueIntMax = 1;
		VarChatCommandEndRoundEnabled = AddVariableInt("ChatCommandEndRoundEnabled", "chat_command_end_round_enabled", "Controls whether or not players can vote to end the round. ", eCommandFlagsArchived, 1);
		VarChatCommandEndRoundEnabled->ValueIntMin = 0;
		VarChatCommandEndRoundEnabled->ValueIntMax = 1;
		VarChatVotesNeeded = AddVariableInt("ChatVotesNeeded", "chat_votes_needed", "Current number of chat votes needed to pass", CommandFlags(eCommandFlagsInternal | eCommandFlagsReplicated), 0);
		VarChatVotesNeededClient = AddVariableInt("ChatVotesNeededClient", "chat_votes_needed_client", "Current number of chat votes needed to pass", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarChatVotesNeeded, VarChatVotesNeededClient);
		VarChatVoteAction = AddVariableString("ChatVoteAction", "chat_vote_action", "Current chat vote action", CommandFlags(eCommandFlagsInternal | eCommandFlagsReplicated), "");
		VarChatVoteActionClient = AddVariableString("ChatVoteActionClient", "chat_vote_action_client", "Current chat vote action", eCommandFlagsInternal, "");
		Server::VariableSynchronization::Synchronize(VarChatVoteAction, VarChatVoteActionClient);
		VarChatVoteStarted = AddVariableInt("ChatVoteStarted", "chat_vote_started", "Current status of a chat vote", CommandFlags(eCommandFlagsInternal | eCommandFlagsReplicated), 0);
		VarChatVoteStartedClient = AddVariableInt("ChatVoteStartedClient", "chat_vote_started_client", "Current status of a chat vote", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarChatVoteStarted, VarChatVoteStartedClient);
		VarChatVoteStartedByUid = AddVariableString("ChatVoteStartedByUid", "chat_vote_started_by_uid", "Uid of the player who started the vote", CommandFlags(eCommandFlagsInternal | eCommandFlagsReplicated), "");
		VarChatVoteStartedByUidClient = AddVariableString("ChatVoteStartedByUidClient", "chat_vote_started_by_uid_client", "Uid of the player who started the vote", eCommandFlagsInternal, "");
		Server::VariableSynchronization::Synchronize(VarChatVoteStartedByUid, VarChatVoteStartedByUidClient);
		VarReturnToLobbyTimeoutSeconds = AddVariableInt("ReturnToLobbyTimeout", "server_return_to_lobby_timeout", "Controls the maximum duration of blackscreens postgame", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0xA);
		VarBanListSyncIntervalSeconds = AddVariableInt("BanListSyncIntervalSeconds", "server_banlist_sync_internval", "The interval at which banlists synced and enforced", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0x3C);
		VarSendChatToRconClients = AddVariableInt("SendChatToRconClients", "send_chat_to_rcon", "Controls whether or not chat should be sent through rcon", eCommandFlagsArchived, 0);
		VarSendChatToRconClients->ValueIntMin = 0;
		VarSendChatToRconClients->ValueIntMax = 1;
		VarServerVotePassPercentage = AddVariableInt("VotePassPercentage", "vote_pass_percentage", "Percentage of players required to vote yes for a chat command vote to pass ", eCommandFlagsArchived, 0x32);
		VarServerVotePassPercentage->ValueIntMin = 0;
		VarServerVotePassPercentage->ValueIntMax = 100;
		VarChatCommandVoteTime = AddVariableInt("ChatCommandVoteTime", "chat_command_vote_time", "The number of seconds a chat command vote lasts", eCommandFlagsArchived, 0x2D);
		VarChatCommandVoteTime->ValueIntMin = 1;
		VarChatCommandVoteTime->ValueIntMax = 200;
		VarTempBanDuration = AddVariableInt("TempBanDuration", "temp_ban_duration", "Duration of a temporary ban (in games)", eCommandFlagsArchived, 2);
		VarTempBanDuration->ValueIntMin = 1;
		VarTempBanDuration->ValueIntMax = 10;
		VarServerTeamShuffleEnabled = AddVariableInt("TeamShuffleEnabled", "team_shuffle_enabled", "Controls whether or not the teams will be automatically shuffled before the game starts.", eCommandFlagsArchived, 1);
		VarServerTeamShuffleEnabled->ValueIntMin = 0;
		VarServerTeamShuffleEnabled->ValueIntMax = 1;
		VarPostGameTimeSeconds = AddVariableInt("PostGameTimeSeconds", "post_game_time_seconds", "Time in seconds from game over to return to lobby", eCommandFlagsArchived, 7);
		VarPostGameTimeSeconds->ValueIntMin = 0;
		VarPostGameTimeSeconds->ValueIntMax = 40;
		VarPostGameFadeStartDelay = AddVariableInt("PostGameFadeStartDelay", "post_game_fade_start_delay", "Time in seconds from game over to start fading to black", eCommandFlagsArchived, 4, VariablePostGameFadeDelayUpdate);
		VarPostGameFadeStartDelay->ValueIntMin = 0;
		VarPostGameFadeStartDelay->ValueIntMax = 40;
		AddCommand("WebsocketInfo", "websocketinfo", "Display the websocket password for the current server", eCommandFlagsNone, CommandWebsocketInfo);
		VarSignalServerPort = AddVariableInt("SignalServerPort", "signalserverport", "The port the signaling server will listen on", eCommandFlagsArchived, 0x2E01);
		VarSignalServerPort->ValueIntMin = 0;
		VarSignalServerPort->ValueIntMax = 0xFFFF;
		VarHttpServerCacheTime = AddVariableInt("Http.CacheTime", "http.cache_time", "Time in seconds the server should cache the http server response", eCommandFlagsArchived, 5);
		VarHttpServerCacheTime->ValueIntMin = 0;
		VarHttpServerCacheTime->ValueIntMax = 20;
		AddCommand("GetEndpoint", "gep", "Get an endpoint url from dewrito.json", eCommandFlagsHidden, CommandServerGetEndpoint, { "name The Name of the entry in dewrito.json" });
		AddCommand("Mod", "mod", "Sets the current tag mod", eCommandFlagsHostOnly, CommandLoadMod, { "identifier(string) The identifier of the mod to load - A named mod in mods.json, a filename, or a hash" });
		AddCommand("ListMods", "list_mods", "Lists the available tag mods", eCommandFlagsHidden, CommandListMods);
		AddCommand("ListModInfo", "modinfo", "Prints out the currently loaded game mod info", eCommandFlagsHidden, CommandListModInfo);
		AddCommand("ListModFiles", "list_mod_files", "Lists all mod files in the package with the given hash", eCommandFlagsHidden, CommandListModFiles);
		AddCommand("RefreshMods", "refresh_mods", "Searches for mods in the mods directory", eCommandFlagsNone, CommandEnumerateMods);
		AddCommand("DeleteMod", "delete_mod", "Deletes a mod package given its hash", eCommandFlagsHidden, CommandDeleteMod);
		VarModsJsonFile = AddVariableString("ModsJsonFile", "mods_json_file", "Sets the path to the mods.json file for automatic mod downloads on boot", CommandFlags(eCommandFlagsNoRcon | eCommandFlagsArchived), "data\\server\\mods.json");
		VarCameraAllowedOnClients = AddVariableInt("CameraAllowedOnClients", "camera_allowed_on_clients", "Allows certain Camera modes to be used on Clients", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0);
		VarCameraAllowedOnClients->ValueIntMin = 0;
		VarCameraAllowedOnClients->ValueIntMax = 1;
		VarCameraAllowedOnClientsClient = AddVariableInt("CameraAllowedOnClientsClient", "camera_allowed_on_clients_client", "Allows certain Camera modes to be used on Clients", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarCameraAllowedOnClients, VarCameraAllowedOnClientsClient);
		VarDebugAllowedOnClients = AddVariableInt("DebugAllowedOnClients", "Debug_allowed_on_clients", "Allows certain Debug commands to be used on Clients", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0);
		VarDebugAllowedOnClients->ValueIntMin = 0;
		VarDebugAllowedOnClients->ValueIntMax = 1;
		VarDebugAllowedOnClientsClient = AddVariableInt("DebugAllowedOnClientsClient", "Debug_allowed_on_clients_client", "Allows certain Debug commands to be used on Clients", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarDebugAllowedOnClients, VarDebugAllowedOnClientsClient);
		AddCommand("RefreshServerFilters", "refresh_filters", "Reloads the data from the server.json file", eCommandFlagsHostOnly, CommandRefreshServerFilters);
		VarChatFilterEnabled = AddVariableInt("ChatFilterEnabled", "chat_filter_enabled", "Controls whether or not the chat filter should be enabled", eCommandFlagsArchived, 0);
		VarChatFilterEnabled->ValueIntMin = 0;
		VarChatFilterEnabled->ValueIntMax = 1;
		Modules::Command *syncTestServer = AddVariableInt("SyncTest", "synctest", "Sync test server", eCommandFlagsHidden, 0);
		Modules::Command *syncTestClient = AddVariableInt("SyncTestClient", "synctestclient", "Sync test client", eCommandFlagsHidden, 0);
		Server::VariableSynchronization::Synchronize(syncTestServer, syncTestClient);
		PingId = Patches::Network::OnPong(PongReceived);
		refreshServerFilters();
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0SServerConnectOptions@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1SServerConnectOptions@@QAE@XZ"); no body to assert in
_inline SServerConnectOptions::~SServerConnectOptions() = default; // 0x10A07290

// mangled_x86(MANGLED_DEFAULT, "??1c_threadsafe_iterator@c_mod_package_manager@@QAE@XZ"); no body to assert in
_inline c_mod_package_manager::c_threadsafe_iterator::~c_threadsafe_iterator() = default; // 0x10A073C0

namespace Modules
{
	void ModuleServer::refreshServerFilters() // 0x10A186A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?refreshServerFilters@ModuleServer@Modules@@QAEXXZ");
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
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			// std::string contents;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &namesArray;
					// unsigned __int32 i;
						// std::string name;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &wordsArray;
						// std::string word;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &patternArray;
						// std::string pattern;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &replacementWord;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// std::ofstream outFile;

		NonAllowedNames.clear();
		FilteredWords.clear();
		FilteredPatterns.clear();
		FilterReplacementWord = "blam";
		std::ifstream in("data/server/server.json", std::ios::in | std::ios::binary);
		if (in && in.is_open())
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			rapidjson::Document json;
			if (!json.Parse<0>(contents.c_str()).HasParseError() && json.IsObject())
			{
				if (json.HasMember("nonAllowedNames"))
				{
					rapidjson::Value &namesArray = json["nonAllowedNames"];
					for (unsigned __int32 i = 0; i < namesArray.Size(); i++)
					{
						std::string name = namesArray[i].GetString();
						std::transform(name.begin(), name.end(), name.begin(), ::tolower);
						NonAllowedNames.insert(name);
					}
				}
				if (json.HasMember("filteredWords"))
				{
					rapidjson::Value &wordsArray = json["filteredWords"];
					for (unsigned __int32 i = 0; i < wordsArray.Size(); i++)
					{
						std::string word = wordsArray[i].GetString();
						std::transform(word.begin(), word.end(), word.begin(), ::tolower);
						FilteredWords.insert(word);
					}
				}
				if (json.HasMember("filteredPatterns"))
				{
					rapidjson::Value &patternArray = json["filteredPatterns"];
					for (unsigned __int32 i = 0; i < patternArray.Size(); i++)
					{
						std::string pattern = patternArray[i].GetString();
						FilteredPatterns.insert(pattern);
					}
				}
				if (json.HasMember("filterReplacementWord"))
				{
					rapidjson::Value &replacementWord = json["filterReplacementWord"];
					FilterReplacementWord = replacementWord.GetString();
				}
			}
		}
		else
		{
			std::ofstream outFile("data/server/server.json", std::ios::out | std::ios::binary);
			if (outFile.fail())
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Info, "Failed to create server.json");
				return;
			}
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);
			writer.StartObject();
			writer.Key("nonAllowedNames");
			writer.StartArray();
			writer.EndArray();
			writer.Key("filteredWords");
			writer.StartArray();
			writer.EndArray();
			writer.Key("filteredPatterns");
			writer.StartArray();
			writer.EndArray();
			writer.Key("filterReplacementWord");
			writer.String("blam");
			writer.EndObject();
			outFile << s.GetString();
		}
	}
}


namespace Modules
{
	std::unordered_set<std::string> ModuleServer::GetFilteredWordsList() // 0x10A139E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetFilteredWordsList@ModuleServer@Modules@@QAE?AV?$unordered_set@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// Modules::ModuleServer *const this;

		return FilteredWords;
	}
}


namespace Modules
{
	std::unordered_set<std::string> ModuleServer::GetFilteredPatternsList() // 0x10A13960
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetFilteredPatternsList@ModuleServer@Modules@@QAE?AV?$unordered_set@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// Modules::ModuleServer *const this;

		return FilteredPatterns;
	}
}


namespace Modules
{
	std::string ModuleServer::GetFilterReplacementWord() // 0x10A138E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetFilterReplacementWord@ModuleServer@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// Modules::ModuleServer *const this;

		return FilterReplacementWord;
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

bool VariablePostGameFadeDelayUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A14A50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariablePostGameFadeDelayUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariablePostGameFadeDelayUpdate
	// std::string &returnInfo;
	// unsigned long seconds;

	unsigned long seconds = Modules::ModuleServer::Instance().VarPostGameFadeStartDelay->ValueInt;

	Pointer(0x553750).Write<unsigned char>(seconds);
	return true;
}

bool VariableServerCountdownUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A14B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableServerCountdownUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableServerCountdownUpdate
	// std::string &returnInfo;
	// unsigned long offset;
	// unsigned long seconds;

	unsigned long seconds = Modules::ModuleServer::Instance().VarServerCountdownClient->ValueInt;
	unsigned long offset = 4;
	if (seconds == 0)
	{
		offset = 2;
		Pointer::Base(0x1536F0).Write<unsigned char>(offset + 2);
		Pointer::Base(0x153720).Write<unsigned char>(offset + 5);
	}
	else
		Pointer::Base(0x153720).Write<unsigned char>(5);
	Pointer::Base(0x153708).Write<unsigned char>(seconds);
	Pointer::Base(0x153738).Write<unsigned char>((unsigned char)seconds + offset);
	Pointer::Base(0x1521D1).Write<unsigned char>((unsigned char)seconds + offset);
	if (seconds > 0 && seconds <= 4)
		Pointer::Base(0x1536F0).Write<unsigned char>(2);
	else if (seconds > 4)
		Pointer::Base(0x1536F0).Write<unsigned char>(3);
	return true;
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

void GetEndpoints(std::vector<std::string> &destVect, std::string endpointType) // 0x10A136F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetEndpoints@@YAXAAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::GetEndpoints
	// static ...; // 0x10A1386C
	// static ...; // 0x10A13864
	// std::vector<std::string> &destVect;
	// std::string endpointType;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &mastersArray;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *it;

	if (Utils::DewritoReader::Instance().IsValid())
	{
		rapidjson::Document json = Utils::DewritoReader::Instance().GetDewritoJson();
		if (json.IsObject() && json.HasMember("masterServers"))
		{
			auto &mastersArray = json["masterServers"];
			for (auto it = mastersArray.Begin(); it != mastersArray.End(); it++)
				destVect.push_back((*it)[endpointType.c_str()].GetString());
		}
	}
}

bool GetEndpoint(std::string endpointName, std::string &returnInfo) // 0x10A132A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetEndpoint@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV12@@Z");
	// `anonymous-namespace'::GetEndpoint
	// static ...; // 0x10A13600
	// static ...; // 0x10A135F9
	// static ...; // 0x10A135F0
	// static ...; // 0x10A135C0
	// static ...; // 0x10A135B8
	// std::string endpointName;
	// std::string &returnInfo;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &mastersArray;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *it;
			// std::string endpoint;

	if (Utils::DewritoReader::Instance().IsValid())
	{
		rapidjson::Document json = Utils::DewritoReader::Instance().GetDewritoJson();
		if (json.IsObject() && json.HasMember(endpointName.c_str()))
		{
			if (endpointName == "masterServers")
			{
				if (json.HasMember("masterServers"))
				{
					rapidjson::StringBuffer buffer;
					rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
					writer.StartArray();
					auto &mastersArray = json["masterServers"];
					for (auto it = mastersArray.Begin(); it != mastersArray.End(); it++)
						writer.Key((*it)["list"].GetString());
					writer.EndArray();
					returnInfo = buffer.GetString();
					return true;
				}
			}
			else
			{
				std::string endpoint = Utils::DewritoReader::Instance().GetDewritoJson()[endpointName.c_str()].GetString();
				returnInfo = endpoint;
				return true;
			}
		}
	}
	return false;
}

unsigned long __stdcall CommandServerAnnounce_Thread(void *lpParam) // 0x10A09A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerAnnounce_Thread@@YGKPAX@Z");
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
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
			// std::string server;
				// std::wstring respHdr;
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
				// std::wstring expected;
				// HttpRequest req;
				// std::string resp;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &result;
	// function call : unsigned long ()

	std::stringstream ss;
	std::vector<std::string> announceEndpoints;

	GetEndpoints(announceEndpoints, "announce");

	for (auto server : announceEndpoints)
	{
		HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");

		try
		{
			if (!req.SendRequest(Utils::String::WidenString(server + "?port=" + Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPort->ValueString), L"GET", L"", L"", L"", NULL, 0))
			{
				ss << "Unable to connect to master server " << server << " (error: " << req.lastError << "/" << std::to_string(GetLastError()) << ")" << std::endl << std::endl;
				continue;
			}
		}
		catch(...)
		{
			ss << "Exception during master server announce request to " << server << std::endl << std::endl;
			continue;
		}

		std::wstring expected = L"HTTP/1.1 200 OK";
		if (req.responseHeader.length() < expected.length())
		{
			ss << "Invalid master server announce response from " << server << std::endl << std::endl;
			continue;
		}

		auto respHdr = req.responseHeader.substr(0, expected.length());
		if (respHdr.compare(expected))
		{
			ss << "Invalid master server announce response from " << server << std::endl << std::endl;
			continue;
		}

		std::string resp = std::string(req.responseBody.begin(), req.responseBody.end());
		rapidjson::Document json;
		if (json.Parse<0>(resp.c_str()).HasParseError() || !json.IsObject())
		{
			ss << "Invalid master server JSON response from " << server << std::endl << std::endl;
			continue;
		}

		if (!json.HasMember("result"))
		{
			ss << "Master server JSON response from " << server << " is missing data." << std::endl << std::endl;
			continue;
		}

		auto& result = json["result"];
		if (result["code"].GetInt() != 0)
		{
			ss << "Master server " << server << " returned error code " << result["code"].GetInt() << " (" << result["msg"].GetString() << ")" << std::endl << std::endl;
			continue;
		}
	}

	std::string errors = ss.str();
	if (errors.length() > 0)
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Announce: " + ss.str());

	return true;
}

unsigned long __stdcall CommandServerUnannounce_Thread(void *lpParam) // 0x10A0F2D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerUnannounce_Thread@@YGKPAX@Z");
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
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
			// std::string server;
				// std::wstring respHdr;
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
				// std::wstring expected;
				// HttpRequest req;
				// std::string resp;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &result;
	// function call : unsigned long ()

	std::stringstream ss;
	std::vector<std::string> announceEndpoints;

	GetEndpoints(announceEndpoints, "announce");

	for (auto server : announceEndpoints)
	{
		HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");

		try
		{
			if (!req.SendRequest(Utils::String::WidenString(server + "?port=" + Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPort->ValueString + "&shutdown=true"), L"GET", L"", L"", L"", NULL, 0))
			{
				ss << "Unable to connect to master server " << server << " (error: " << req.lastError << "/" << std::to_string(GetLastError()) << ")" << std::endl << std::endl;
				continue;
			}
		}
		catch (...)
		{
			ss << "Exception during master server unannounce request to " << server << std::endl << std::endl;
			continue;
		}

		std::wstring expected = L"HTTP/1.1 200 OK";
		if (req.responseHeader.length() < expected.length())
		{
			ss << "Invalid master server unannounce response from " << server << std::endl << std::endl;
			continue;
		}

		auto respHdr = req.responseHeader.substr(0, expected.length());
		if (respHdr.compare(expected))
		{
			ss << "Invalid master server unannounce response from " << server << std::endl << std::endl;
			continue;
		}

		std::string resp = std::string(req.responseBody.begin(), req.responseBody.end());
		rapidjson::Document json;
		if (json.Parse<0>(resp.c_str()).HasParseError() || !json.IsObject())
		{
			ss << "Invalid master server JSON response from " << server << std::endl << std::endl;
			continue;
		}

		if (!json.HasMember("result"))
		{
			ss << "Master server JSON response from " << server << " is missing data." << std::endl << std::endl;
			continue;
		}

		auto& result = json["result"];
		if (result["code"].GetInt() != 0)
		{
			ss << "Master server " << server << " returned error code " << result["code"].GetInt() << " (" << result["msg"].GetString() << ")" << std::endl << std::endl;
			continue;
		}
	}

	std::string errors = ss.str();
	if (errors.length() > 0)
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Unannounce: " + ss.str());

	return true;
}

bool CommandServerAnnounce(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A09760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerAnnounce@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerAnnounce
	// static ...; // 0x10A099BC
	// static ...; // 0x10A099B4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			// void *thread;
	// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)

	returnInfo = "Not available in debug builds";
	return false;
	if (!Server::InfoServer::IsInfoSocketOpen())
	{
		returnInfo = "Network mode must be Online to announce";
		return false;
	}
	if (Utils::DewritoReader::Instance().IsValid())
	{
		rapidjson::Document json = Utils::DewritoReader::Instance().GetDewritoJson();
		if (json.IsObject() && json.HasMember("masterServers"))
		{
			if (Utils::DewritoReader::Instance().GetDewritoJson()["masterServers"].GetArray().Size() > 0)
			{
				HANDLE thread = CreateThread(nullptr, 0, CommandServerAnnounce_Thread, (LPVOID)&Arguments, 0, nullptr);
				returnInfo = "Announcing to master servers...";
				return true;
			}
		}
	}
	returnInfo = "No master servers in \\data\\dewrito.json to announce to";
	return false;
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

bool VariableServerShouldAnnounceUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A15090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableServerShouldAnnounceUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableServerShouldAnnounceUpdate
	// static ...; // 0x10A15158
	// static ...; // 0x10A15150
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string returnValueIgnored;

	std::string returnValueIgnored;
	if (!Modules::ModuleServer::Instance().VarServerShouldAnnounce->ValueInt)
		CommandServerUnannounce(Arguments, returnValueIgnored);
	return true;
}

bool CommandServerConnect(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerConnect@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// std::string port;

	if (Arguments.size() <= 0)
	{
		returnInfo = "Invalid arguments.";
		return false;
	}
	std::string address = Arguments[0];
	std::string password = "";
	if (Arguments.size() > 1)
		password = Arguments[1];
	unsigned __int32 rawIpaddr = 0;
	__int32 httpPort = 11775;
	unsigned __int32 portOffset = address.find(':');
	std::string host = address;
	if (portOffset != std::string::npos && portOffset + 1 < address.size())
	{
		try
		{
			std::string port = address.substr(portOffset + 1);
			httpPort = (unsigned short)std::stoi(port);
			host = address.substr(0, portOffset);
		}
		catch (std::logic_error &)
		{
			returnInfo = "Invalid arguments.";
			return false;
		}
	}
	SServerConnectOptions options;
	options.hostname = host;
	options.password = password;
	options.port = httpPort;
	if (!Utils::Singleton<CServerConnectManager>::Instance().ConnectToServer(options))
	{
		returnInfo = "Another connection attempt is pending. Try again.";
		return false;
	}
	returnInfo = "Attempting connection to " + address + "...";
	return true;
}

__int32 FindPlayerByName(std::string const &name, bool findPeer) // 0x10A12E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindPlayerByName@@YAHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
	// `anonymous-namespace'::FindPlayerByName
	// bool findPeer;
	// Blam::Network::SessionMembership *membership;
	// Blam::Network::Session *session;
		// __int32 peerIdx;
			// Blam::Network::PlayerSession *player;
			// __int32 playerIdx;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
		return -1;
	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	for (__int32 peerIdx = membership->FindFirstPeer(); peerIdx >= 0; peerIdx = membership->FindNextPeer(peerIdx))
	{
		__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
		if (playerIdx == -1)
			continue;
		Blam::Network::PlayerSession *player = &membership->PlayerSessions[playerIdx];
		if (Utils::String::ThinString(player->Properties.host.player_name) == name)
		{
			if (findPeer)
				return peerIdx;
			else
				return playerIdx;
		}
	}
	return -1;
}

std::vector<int> FindPlayersByUid(unsigned long long uid) // 0x10A13040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindPlayersByUid@@YA?AV?$vector@HV?$allocator@H@std@@@std@@_K@Z");
	// `anonymous-namespace'::FindPlayersByUid
	// static ...; // 0x10A13216
	// static ...; // 0x10A1320C
	// static ...; // 0x10A131F4
	// static ...; // 0x10A131EC
	// unsigned long long uid;
	// Blam::Network::SessionMembership *membership;
	// Blam::Network::Session *session;
	// std::vector<int> indices;
		// __int32 peerIdx;
			// Blam::Network::PlayerSession *player;
			// __int32 playerIdx;

	std::vector<int> indices;
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
		return indices;
	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	for (__int32 peerIdx = membership->FindFirstPeer(); peerIdx >= 0; peerIdx = membership->FindNextPeer(peerIdx))
	{
		__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
		if (playerIdx == -1)
			continue;
		Blam::Network::PlayerSession *player = &membership->PlayerSessions[playerIdx];
		if (player->Properties.host.player_uid == uid)
			indices.push_back(playerIdx);
	}
	return indices;
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

void BanUid(std::string const &playerUid) // 0x10A07BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BanUid@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::BanUid
	// static ...; // 0x10A07CC8
	// static ...; // 0x10A07CC0
	// static ...; // 0x10A07CA8
	// static ...; // 0x10A07CA0
	// std::string const &playerUid;
	// unsigned long long uid;
		// Server::BanList banList;

	unsigned long long uid;
	if (Patches::PlayerUid::ParseUid(playerUid, &uid))
	{
		auto banList = Server::LoadDefaultBanList();
		banList.AddUid(uid);
		Server::SaveDefaultBanList(banList);
	}
}

void BanName(std::string const &name) // 0x10A07AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BanName@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::BanName
	// static ...; // 0x10A07B88
	// static ...; // 0x10A07B7C
	// static ...; // 0x10A07B74
	// std::string const &name;
	// Server::BanList banList;

	auto banList = Server::LoadDefaultBanList();
	banList.AddName(name);
	Server::SaveDefaultBanList(banList);
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

bool UnbanUid(std::string const &playerUid) // 0x10A144E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UnbanUid@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::UnbanUid
	// static ...; // 0x10A14634
	// static ...; // 0x10A14630
	// static ...; // 0x10A14618
	// static ...; // 0x10A14610
	// std::string const &playerUid;
	// Server::BanList banList;
	// unsigned long long uid;

	auto banList = Server::LoadDefaultBanList();
	unsigned long long uid;
	if (Patches::PlayerUid::ParseUid(playerUid, &uid))
	{
		if (!banList.RemoveUid(uid))
			return false;
	}
	else
	{
		return false;
	}
	Server::SaveDefaultBanList(banList);
	return true;
}

bool UnbanName(std::string const &name) // 0x10A14390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UnbanName@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::UnbanName
	// static ...; // 0x10A1448C
	// static ...; // 0x10A14480
	// static ...; // 0x10A14478
	// std::string const &name;
	// Server::BanList banList;

	auto banList = Server::LoadDefaultBanList();
	if (!banList.RemoveName(name))
		return false;
	Server::SaveDefaultBanList(banList);
	return true;
}

bool DoKickPlayerCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A11AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DoKickPlayerCommand@@YA_NW4KickType@hades_file_local@@ABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
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

	if (Arguments.size() <= 0)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	std::string kickPlayerName = Utils::String::Join(Arguments, " ");
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
	{
		returnInfo = "You must be hosting a game to use this command";
		return false;
	}
	__int32 playerIdx = FindPlayerByName(kickPlayerName, false);
	if (playerIdx < 0)
	{
		returnInfo = "Player \"" + kickPlayerName + "\" not found.";
		return false;
	}
	__int32 peer = session->MembershipInfo.GetPlayerPeer(playerIdx);
	if (peer == session->MembershipInfo.HostPeerIndex)
	{
		returnInfo = "You cannot kick yourself.";
		return false;
	}
	std::stringstream ss;
	e_network_session_boot_reason banReason = (e_network_session_boot_reason)4;
	ss << "You have been ";
	switch (type)
	{
	case Ban:
		ss << "banned.";
		banReason = (e_network_session_boot_reason)13;
		break;
	case TempBan:
		ss << "temporarily banned.";
		banReason = (e_network_session_boot_reason)14;
		break;
	case Kick:
		ss << "kicked.";
		banReason = (e_network_session_boot_reason)4;
		break;
	}
	Server::Chat::SendServerMessage(ss.str().c_str(), peer);
	std::string ip = session->GetPeerAddress(peer).ToString();
	if (!Blam::Network::BootPlayer(playerIdx, banReason))
	{
		returnInfo = "Failed to kick player " + kickPlayerName;
		return false;
	}
	if (type == Ban)
	{
		BanIp(ip);
		returnInfo = "Added IP " + ip + " to the ban list\n";
	}
	else if (type == TempBan)
	{
		TempBanIP(ip);
		returnInfo = "Added IP " + ip + " to the temp ban list\n";
	}
	returnInfo += "Issued kick request for player " + kickPlayerName + " (" + std::to_string(playerIdx) + ")";
	return true;
}

bool DoKickUidCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A12370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DoKickUidCommand@@YA_NW4KickType@hades_file_local@@ABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
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
		// std::vector<int> &<range>$L0;
		// __int32 *<begin>$L0;
		// __int32 *<end>$L0;
			// __int32 playerIdx;
				// std::string kickPlayerName;
				// std::string ip;

	if (Arguments.size() != 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	unsigned long long uid;
	if (!Patches::PlayerUid::ParseUid(Arguments[0], &uid))
	{
		returnInfo = "Invalid UID";
		return false;
	}
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
	{
		returnInfo = "You must be hosting a game to use this command";
		return false;
	}
	std::vector<int> indices = FindPlayersByUid(uid);
	if (indices.size() == 0)
	{
		returnInfo = "Player with UID " + Arguments[0] + " not found.";
		return false;
	}
	e_network_session_boot_reason banReason = (e_network_session_boot_reason)4;
	switch (type)
	{
	case Ban:
		banReason = (e_network_session_boot_reason)13;
		break;
	case TempBan:
		banReason = (e_network_session_boot_reason)14;
		break;
	case Kick:
		banReason = (e_network_session_boot_reason)4;
		break;
	}
	bool success = false;
	for (__int32 playerIdx : indices)
	{
		std::string ip = session->GetPeerAddress(session->MembershipInfo.GetPlayerPeer(playerIdx)).ToString();
		std::string kickPlayerName = Utils::String::ThinString(session->MembershipInfo.PlayerSessions[playerIdx].Properties.host.player_name);
		if (!Blam::Network::BootPlayer(playerIdx, banReason))
		{
			returnInfo += "Failed to kick player " + kickPlayerName + "\n";
			continue;
		}
		if (type == Ban)
		{
			BanIp(ip);
			returnInfo += "Added IP " + ip + " to the ban list\n";
		}
		else if (type == TempBan)
		{
			TempBanIP(ip);
			returnInfo = "Added IP " + ip + " to the temp ban list\n";
		}
		returnInfo += "Issued kick request for player " + kickPlayerName + " (" + std::to_string(playerIdx) + ")\n";
		success = true;
	}
	return success;
}

bool DoKickIndexCommand(KickType type, std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A11390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DoKickIndexCommand@@YA_NW4KickType@hades_file_local@@ABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
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

	if (Arguments.size() != 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	__int32 index = -1;
	unsigned __int32 pos = 0;
	try
	{
		index = std::stoi(Arguments[0], &pos);
	}
	catch (std::logic_error &)
	{
	}
	if (pos != Arguments[0].length() || index < 0 || index > 15)
	{
		returnInfo = "Invalid player index";
		return false;
	}
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
	{
		returnInfo = "You must be hosting a game to use this command";
		return false;
	}
	Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[index];
	std::string kickPlayerName = Utils::String::ThinString(player->Properties.host.player_name);
	std::string ip = session->GetPeerAddress(player->PeerIndex).ToString();
	__int32 banReason = 0;
	switch (type)
	{
	case KickType::Ban:
		banReason = 5;
		break;
	case KickType::TempBan:
		banReason = 6;
		break;
	case KickType::Kick:
		banReason = 4;
		break;
	}
	if (!Blam::Network::BootPlayer(index, banReason))
	{
		returnInfo = "Failed to kick player " + kickPlayerName;
		return false;
	}
	if (type == KickType::Ban)
	{
		BanIp(ip);
		returnInfo = "Added IP " + ip + " to the ban list\n";
	}
	else if (type == KickType::TempBan)
	{
		TempBanIP(ip);
		returnInfo = "Added IP " + ip + " to the temp ban list\n";
	}
	returnInfo += "Issued kick request for player " + kickPlayerName + " (" + std::to_string(index) + ")";
	return true;
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

bool CommandServerKickBan(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerKickBan@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// Blam::Network::SessionMembership *membership;
		// std::string ip;
			// __int32 peerIdx;
				// __int32 playerIdx;
				// std::string playerIp;
		// unsigned long long uid;
		// std::string playerUid;
			// std::vector<int> indices;
				// std::vector<int> &<range>$L0;
				// __int32 *<begin>$L0;
				// __int32 *<end>$L0;
					// __int32 playerIdx;
		// __int32 playerIdx;
		// std::string name;

	if (Arguments.size() != 2)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
	{
		returnInfo = "You must be hosting a game to use this command";
		return false;
	}
	std::string banType = Arguments[0];
	if (banType == "ip")
	{
		std::string ip = Arguments[1];
		Blam::Network::SessionMembership *membership = &session->MembershipInfo;
		for (__int32 peerIdx = membership->FindFirstPeer(); peerIdx >= 0; peerIdx = membership->FindNextPeer(peerIdx))
		{
			__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
			std::string playerIp = session->GetPeerAddress(session->MembershipInfo.GetPlayerPeer(playerIdx)).ToString();
			if (playerIp == ip)
			{
				if (!Blam::Network::BootPlayer(playerIdx, 13))
					returnInfo += "Failed to kick player with ip" + ip + "\n";
				else
					returnInfo += "Kicked and ";
			}
		}
		BanIp(ip);
		returnInfo += "added IP " + ip + " to the ban list";
		return true;
	}
	else if (banType == "uid")
	{
		std::string playerUid = Arguments[1];
		unsigned long long uid;
		if (Patches::PlayerUid::ParseUid(playerUid, &uid))
		{
			std::vector<int> indices = FindPlayersByUid(uid);
			if (!indices.size())
			{
				returnInfo += "Player with UID " + playerUid + " not found.";
				return false;
			}
			for (__int32 playerIdx : indices)
			{
				if (!Blam::Network::BootPlayer(playerIdx, 13))
				{
					returnInfo += "Failed to kick player with uid " + playerUid + "\n";
					continue;
				}
				else
				{
					returnInfo += "Kicked and ";
				}
			}
		}
		BanUid(playerUid);
		returnInfo += "added UID " + playerUid + " to the ban list";
		return true;
	}
	else if (banType == "name")
	{
		std::string name = Arguments[1];
		__int32 playerIdx = FindPlayerByName(name, false);
		if (playerIdx == -1)
		{
			returnInfo += "Player with Name " + name + " not found.";
			return false;
		}
		if (!Blam::Network::BootPlayer(playerIdx, 13))
			returnInfo += "Failed to kick player with name " + name + "\n";
		else
			returnInfo += "Kicked and ";
		BanName(name);
		returnInfo += "added NAME " + name + " to the ban list";
		return true;
	}
	returnInfo = "Unsupported ban type " + banType;
	return false;
}

bool CommandServerBan(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0ABB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerBan@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerBan
	// static ...; // 0x10A0AFCD
	// static ...; // 0x10A0AFC9
	// static ...; // 0x10A0AFC4
	// static ...; // 0x10A0AF94
	// static ...; // 0x10A0AF8C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string banType;
		// std::string ip;
		// std::string uid;
		// std::string name;

	if (Arguments.size() != 2)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	std::string banType = Arguments[0];
	if (banType == "ip")
	{
		std::string ip = Arguments[1];
		DoKickUidCommand(Ban, Arguments, returnInfo);
		BanIp(ip);
		returnInfo = "Added IP " + ip + " to the ban list";
		return true;
	}
	else if (banType == "uid")
	{
		std::string uid = Arguments[1];
		BanUid(uid);
		returnInfo = "Added UID " + uid + " to the ban list";
		return true;
	}
	else if (banType == "name")
	{
		std::string name = Arguments[1];
		BanName(name);
		returnInfo = "Added Name " + name + " to the ban list";
		return true;
	}
	returnInfo = "Unsupported ban type " + banType;
	return false;
}

bool CommandServerUnban(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A10460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerUnban@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerUnban
	// static ...; // 0x10A10A81
	// static ...; // 0x10A10A7D
	// static ...; // 0x10A10A78
	// static ...; // 0x10A10A48
	// static ...; // 0x10A10A40
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string banType;
		// std::string ip;
		// std::string uid;
		// std::string name;

	if (Arguments.size() != 2)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	std::string banType = Arguments[0];
	if (banType == "ip")
	{
		std::string ip = Arguments[1];
		if (!UnbanIp(ip))
		{
			returnInfo = "IP " + ip + " is not banned";
			return false;
		}
		returnInfo = "Removed IP " + ip + " from the ban list";
		return true;
	}
	else if (banType == "uid")
	{
		std::string uid = Arguments[1];
		if (!UnbanUid(uid))
		{
			returnInfo = "UID " + uid + " is not banned";
			return false;
		}
		returnInfo = "Removed UID " + uid + " from the ban list";
		return true;
	}
	else if (banType == "name")
	{
		std::string name = Arguments[1];
		if (!UnbanName(name))
		{
			returnInfo = "Name " + name + " is not banned";
			return false;
		}
		returnInfo = "Removed Name " + name + " from the ban list";
		return true;
	}
	returnInfo = "Unsupported ban type " + banType;
	return false;
}

bool CommandServerMutePlayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0DAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerMutePlayer@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	if (Arguments.size() != 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	__int32 index = -1;
	unsigned __int32 pos = 0;
	try
	{
		index = std::stoi(Arguments[0], &pos);
	}
	catch (std::logic_error &)
	{
	}
	if (pos != Arguments[0].length() || index < 0 || index > 15)
	{
		returnInfo = "Invalid player index";
		return false;
	}
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
	{
		returnInfo = "You must be hosting a game to use this command";
		return false;
	}
	Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[index];
	if (!player)
	{
		returnInfo = "Player index is not valid";
		return false;
	}
	bool result = Server::Chat::SetPlayerMuteStatus(player->PeerIndex, true);
	if (!result)
		returnInfo = "Could not mute player";
	return result;
}

bool CommandServerUnmutePlayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A10C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerUnmutePlayer@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	if (Arguments.size() != 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	__int32 index = -1;
	unsigned __int32 pos = 0;
	try
	{
		index = std::stoi(Arguments[0], &pos);
	}
	catch (std::logic_error &)
	{
	}
	if (pos != Arguments[0].length() || index < 0 || index > 15)
	{
		returnInfo = "Invalid player index";
		return false;
	}
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
	{
		returnInfo = "You must be hosting a game to use this command";
		return false;
	}
	Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[index];
	if (!player)
	{
		returnInfo = "Player index is not valid";
		return false;
	}
	bool result = Server::Chat::SetPlayerMuteStatus(player->PeerIndex, false);
	if (!result)
		returnInfo = "Could not unmute player";
	return result;
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

bool CommandServerRemoveTempBan(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0E3A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerRemoveTempBan@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// bool success;
		// std::map<std::string,int> &<range>$L0;
		// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > <begin>$L0;
		// std::_Default_sentinel <end>$L0;
			// std::pair<std::string const ,int> entry;

	if (Arguments.size() != 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	std::map<std::string, int> list = Utils::Singleton<Server::TempBanList>::Instance().TempBannedList();
	std::string arg = Arguments[0];
	if (arg.size() > 7)
	{
		bool success = Utils::Singleton<Server::TempBanList>::Instance().RemoveIp(arg);
		if (success)
		{
			returnInfo = "Temporary Ban removed for " + arg;
			return true;
		}
		else
		{
			returnInfo = "Invalid Ip Address";
			return false;
		}
	}
	__int32 index = -1;
	try
	{
		index = std::stoi(arg);
	}
	catch (std::logic_error &)
	{
	}
	if (index < 0)
	{
		returnInfo = "Invalid index";
		return false;
	}
	__int32 i = 0;
	for (auto entry : list)
	{
		if (i == index)
		{
			Utils::Singleton<Server::TempBanList>::Instance().RemoveIp(entry.first);
			returnInfo = "Temporary Ban removed for " + entry.first;
			return true;
		}
		i++;
	}
	returnInfo = "Invalid Index";
	return false;
}

bool CommandServerListTempBans(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0D020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerListTempBans@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// std::map<std::string,int> &<range>$L0;
		// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > <begin>$L0;
		// std::_Default_sentinel <end>$L0;
			// std::pair<std::string const ,int> entry;

	std::map<std::string, int> list = Server::TempBanList::Instance().TempBannedList();
	std::stringstream ss;
	__int32 i = 0;
	for (auto entry : list)
	{
		ss << std::dec << "[" << i << "]  \"" << entry.first << "\" Games Left: " << entry.second << std::endl;
		i++;
	}
	returnInfo = ss.str();
	return true;
}

bool CommandServerListPlayers(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0C5F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerListPlayers@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// Blam::Network::PlayerSession player;
		// char uid[17];
		// std::string name;
			// Blam::Network::NetworkAddress ip;

	std::stringstream ss;
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished())
	{
		returnInfo = "No session found, are you in a game?";
		return false;
	}
	__int32 playerIdx = session->MembershipInfo.FindFirstPlayer();
	while (playerIdx != -1)
	{
		Blam::Network::PlayerSession player = session->MembershipInfo.PlayerSessions[playerIdx];
		std::string name = Utils::String::ThinString(player.Properties.host.player_name);
		char uid[17];
		player_format_uid(uid, player.Properties.host.player_uid);
		ss << std::dec << "[" << playerIdx << "] \"" << name << "\" (uid: " << uid;
		if (session->IsHost())
		{
			Blam::Network::NetworkAddress ip = session->GetPeerAddress(session->MembershipInfo.GetPlayerPeer(playerIdx));
			ss << ", ip: " << ip.ToString();
		}
		ss << ")" << std::endl;
		playerIdx = session->MembershipInfo.FindNextPlayer(playerIdx);
	}
	returnInfo = ss.str();
	return true;
}

bool CommandServerListPlayersJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0CAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerListPlayersJSON@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// Blam::Network::PlayerSession player;
		// std::stringstream color;
		// char uid[17];

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished())
	{
		returnInfo = "No session found, are you in a game?";
		return false;
	}
	writer.StartArray();
	__int32 playerIdx = session->MembershipInfo.FindFirstPlayer();
	while (playerIdx != -1)
	{
		Blam::Network::PlayerSession player = session->MembershipInfo.PlayerSessions[playerIdx];
		writer.StartObject();
		writer.Key("name");
		writer.String(Utils::String::ThinString(player.Properties.host.player_name).c_str());
		writer.Key("teamIndex");
		writer.Int(player.Properties.host.team);
		char uid[17];
		player_format_uid(uid, player.Properties.host.player_uid);
		writer.Key("UID");
		writer.String(uid);
		std::stringstream color;
		color << "#" << std::setw(6) << std::setfill('0') << std::hex << player.Properties.host.appearance.model_customization.colors[0];
		writer.Key("color");
		writer.String(color.str().c_str());
		writer.Key("isHost");
		writer.Bool(playerIdx == session->MembershipInfo.HostPeerIndex);
		writer.EndObject();
		playerIdx = session->MembershipInfo.FindNextPlayer(playerIdx);
	}
	writer.EndArray();
	returnInfo = buffer.GetString();
	return true;
}

bool CommandServerMode(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0D720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerMode@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerMode
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// __int32 previous;
	// __int32 serverMode;
	// bool retVal;

	if (Arguments.size() < 1 || Arguments.size() > 1)
	{
		returnInfo = std::to_string(Blam::Network::GetNetworkMode());
		return true;
	}
	__int32 previous = Blam::Network::GetNetworkMode();
	__int32 serverMode = -1;
	try
	{
		serverMode = std::atoi(Arguments[0].c_str());
	}
	catch (std::logic_error &)
	{
	}
	if (serverMode < 0 || serverMode > 4)
	{
		returnInfo = "0 = Xbox Live (Open Party); 1 = Xbox Live (Friends Only); 2 = Xbox Live (Invite Only); 3 = Online; 4 = Offline;";
		return false;
	}
	bool retVal = Blam::Network::SetNetworkMode(serverMode);
	if (retVal)
	{
		if (previous == 3 && Utils::Singleton<Modules::ModuleVoting>::Instance().VarServerVotingType->ValueInt > 0)
		{
			if (!Utils::Singleton<ElDorito>::Instance().IsDedicated())
				Web::Ui::Voting::Hide();
			Server::Voting::CancelVoteInProgress();
		}
		returnInfo = "Changed network mode " + std::to_string(previous) + " -> " + std::to_string(serverMode);
		return true;
	}
	returnInfo = "Hmm, weird. Are you at the main menu?";
	return true;
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

bool CommandServerPing(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0E040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerPing@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// Blam::Network::NetworkAddress blamAddress;
		// unsigned short port;

	if (Arguments.size() > 2)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session)
	{
		returnInfo = "No session available";
		return false;
	}
	if (Arguments.size() > 0)
	{
		Blam::Network::NetworkAddress blamAddress;
		unsigned short port = 11774;
		if (Arguments.size() == 2)
		{
			try
			{
				port = std::atoi(Arguments[1].c_str());
			}
			catch (std::logic_error &)
			{
				returnInfo = "Invalid Port Supplied";
				return false;
			}
		}
		if (!Blam::Network::NetworkAddress::Parse(Arguments[0], port, &blamAddress))
		{
			returnInfo = "Invalid IPv4 address";
			return false;
		}
		if (!session->Gateway->Ping(blamAddress, PingId))
		{
			returnInfo = "Failed to send ping packet";
			return false;
		}
		return true;
	}
	if (!session->IsEstablished())
	{
		returnInfo = "You are not in a game. Use \"ping <ip>\" instead.";
		return false;
	}
	if (session->IsHost())
	{
		if (Utils::Singleton<ElDorito>::Instance().IsDedicated())
		{
			returnInfo = "pong";
			return true;
		}
		returnInfo = "You can't ping yourself. Use \"ping <ip>\" to ping someone else.";
		return false;
	}
	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	__int32 channelIndex = membership->PeerChannels[membership->HostPeerIndex].ChannelIndex;
	if (channelIndex == -1)
	{
		returnInfo = "You are not connected to a game. Use \"ping <ip>\" instead.";
		return false;
	}
	session->Observer->Ping(0, channelIndex, PingId);
	return true;
}

bool CommandServerShuffleTeams(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0EAC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerShuffleTeams@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// __int32 player;
		// __int32 i;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished())
	{
		returnInfo = "No session available";
		return false;
	}
	if (!session->HasTeams())
	{
		returnInfo = "Teams are not enabled";
		return false;
	}
	__int32 players[16];
	__int32 numPlayers = 0;
	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	for (__int32 player = membership->FindFirstPlayer(); player >= 0; player = membership->FindNextPlayer(player))
	{
		players[numPlayers] = player;
		numPlayers++;
	}
	if (numPlayers == 0)
	{
		returnInfo = "No players connected";
		return false;
	}
	if (numPlayers < 2)
	{
		returnInfo = "Need at least 2 players to shuffle the teams";
		return false;
	}
	Modules::ModuleServer &moduleServer = Utils::Singleton<Modules::ModuleServer>::Instance();
	unsigned long maxPlayers = moduleServer.VarServerMaxPlayers->ValueInt;
	unsigned long minTeamSize = moduleServer.VarMinTeamSize->ValueInt;
	__int32 minTeams = __int32(std::ceil(numPlayers / float(minTeamSize)));
	__int32 numTeams = std::min<__int32>(minTeams, moduleServer.VarNumTeams->ValueInt);
	static std::random_device rng;
	static std::mt19937 urng(rng());
	std::shuffle(&players[0], &players[numPlayers], urng);
	__int32 teamIndex = 0;
	for (__int32 i = 0; i < numPlayers; i++)
	{
		membership->PlayerSessions[players[i]].Properties.client.multiplayer_team = teamIndex;
		teamIndex++;
		if (teamIndex == numTeams)
			teamIndex = 0;
	}
	membership->Update();
	std::bitset<17> peers;
	peers.set();
	Server::Chat::SendServerMessage("Teams have been shuffled.", peers);
	returnInfo = "Teams have been shuffled.";
	return true;
}

bool CommandServerGetEndpoint(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0B790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerGetEndpoint@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerGetEndpoint
	// std::string &returnInfo;

	return GetEndpoint(Arguments[0], returnInfo);
}

static void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency) // 0x10A13AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PongReceived@@YAXABUNetworkAddress@Network@Blam@@IGI@Z");
	// `anonymous-namespace'::PongReceived
	// static ...; // 0x10A13DB4
	// Blam::Network::NetworkAddress const &from;
	// unsigned __int32 timestamp;
	// unsigned short id;
	// unsigned __int32 latency;
	// std::string ipStr;
	// std::string message;

	if (id != PingId)
		return;
	std::string ipStr = from.ToString();
	std::string message = "PONG " + ipStr + " " + std::to_string(timestamp) + " " + std::to_string(latency) + "ms";
	::Console::WriteLine(message);
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

bool CommandServerSay(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A0E8A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerSay@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandServerSay
	// static ...; // 0x10A0EA34
	// static ...; // 0x10A0EA2C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::Session *session;
	// std::string message;
		// std::vector<std::string> const &<range>$L0;
		// std::string const *<begin>$L0;
		// std::string const *<end>$L0;
			// std::string const &word;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished())
	{
		returnInfo = "No session available";
		return false;
	}
	if (Arguments.size() <= 0)
	{
		returnInfo = "No message to send";
		return false;
	}
	std::string message = "";
	for (auto &word : Arguments)
		message += word + " ";
	Server::Chat::SendAndLogServerMessage(message);
	return true;
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

bool EncryptMessageWithPublicKey(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A12C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EncryptMessageWithPublicKey@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	if (Arguments.size() < 1)
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	Modules::ModulePlayer &modulePlayer = Modules::ModulePlayer::Instance();
	std::string value = Arguments[0];
	Modules::ModuleServer &moduleServer = Modules::ModuleServer::Instance();
	std::string encryptedString;
	char const *const PasswordChars = value.c_str();
	std::string pubKey;
	Server::Stats::GetStatsPublicKey(pubKey);
	Utils::Cryptography::PublicEncrypt(Utils::Cryptography::ReformatKey(false, pubKey), (void *)PasswordChars, strlen(PasswordChars), encryptedString);
	returnInfo = encryptedString;
	return true;
}

bool CommandWebsocketInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A10E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandWebsocketInfo@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished())
	{
		returnInfo = "No session available";
		return true;
	}
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	writer.StartObject();
	writer.Key("server");
	std::string ip = "";
	if (!session->GetServerIPAddress().ToString().compare("0.0.0.0"))
		ip = "127.0.0.1:" + std::to_string(Server::Signaling::GetPort());
	else
		ip = session->GetServerIPAddress().ToString() + ":" + std::to_string(Server::Signaling::GetPort());
	writer.String(ip.c_str());
	writer.Key("password");
	writer.String(Server::Signaling::GetPassword().c_str());
	writer.EndObject();
	returnInfo = buffer.GetString();
	return true;
}

void UpdatePersistentMod(std::string mod) // 0x10A14740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdatePersistentMod@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::UpdatePersistentMod
	// std::string mod;
	// __int32 lobbyType;

	if (ElDorito::Instance().IsDedicated())
		return;
	__int32 lobbyType = Blam::Network::GetLobbyType();
	if (lobbyType == 0)
		PersistentMemory::SetLastCampaignMod(mod);
	if (lobbyType == 2 || lobbyType == 3)
		PersistentMemory::SetLastMultiplayerMod(mod);
	if (lobbyType == 5)
		PersistentMemory::SetLastFirefightMod(mod);
	PersistentMemory::Save();
}

bool CommandLoadMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A094E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandLoadMod@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandLoadMod
	// std::string &returnInfo;
	// std::string const &path;

	if (Arguments.size() < 1)
	{
		returnInfo = c_mod_system::get_current_package_filename((EModIndex)0);
		return true;
	}

	std::string const &path = Arguments[0];
	if (path.empty())
	{
		UpdatePersistentMod("");
		if (!c_mod_system::unload_current_package())
		{
			returnInfo = "Failed to unload package!";
			return false;
		}
		return true;
	}
	else if (strcmp(path.c_str(), "none") == 0)
	{
		UpdatePersistentMod("");
		if (!c_mod_system::unload_current_package())
		{
			returnInfo = "Failed to unload package!";
			return false;
		}
		returnInfo = "Mod unloaded.";
		return true;
	}
	else if (!c_mod_system::load_package_by_identifier(path.c_str()))
	{
		returnInfo = "Failed to load mod package";
		return false;
	}

	UpdatePersistentMod(path);
	returnInfo = "Mod loaded.";
	return true;
}

bool CommandListMods(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A08C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandListMods@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// char buffer[32];
		// std::string version;
		// std::string hash_str;
		// std::string filename;
		// tm *convertedLocal;
		// s_static_string<32> metadata_name;

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	writer.StartArray();
	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	c_mod_package_manager::c_threadsafe_iterator it = package_manager.lock_for_iteration();
	while (it.next())
	{
		s_static_string<32> metadata_name;
		metadata_name.set_wchar(it->name);
		std::string hash_str;
		Utils::String::BytesToHexString(it->hash, sizeof(it->hash), hash_str);
		writer.StartObject();
		writer.Key("verified");
		writer.Bool(it->verified);
		writer.Key("name");
		writer.String(metadata_name.get_string());
		writer.Key("author");
		writer.String(it->author);
		writer.Key("authorUid");
		writer.Uint64(it->author_uid);
		writer.Key("description");
		writer.String(it->description);
		writer.Key("website");
		writer.String(it->website);
		writer.Key("filesize");
		writer.Int64(it->file_size);
		writer.Key("hash");
		writer.String(hash_str.c_str());
		writer.Key("filename");
		std::string filename = it->file.filename;
		writer.String(filename.substr(filename.find_last_of("\\") + 1, filename.length()).c_str());
		writer.Key("version");
		std::string version = std::to_string(it->version_major) + "." + std::to_string(it->version_minor);
		writer.String(version.c_str());
		writer.Key("mainmenuType");
		writer.Bool(it->modtype.mainmenu);
		writer.Key("characterType");
		writer.Bool(it->modtype.character);
		writer.Key("multiplayerType");
		writer.Bool(it->modtype.multiplayer);
		writer.Key("campaignType");
		writer.Bool(it->modtype.campaign);
		writer.Key("firefightType");
		writer.Bool(it->modtype.firefight);
		writer.Key("downloadDate");
		tm *convertedLocal = localtime(&it->dateAdded);
		char buffer[32];
		strftime(buffer, 32, "%m/%d/%Y", convertedLocal);
		writer.String(buffer);
		writer.Key("lastUsedDate");
		writer.String(std::to_string(it->lastUsed).c_str());
		writer.Key("source");
		writer.String(it->origin.server_name.c_str());
		writer.EndObject();
	}
	writer.EndArray();
	returnInfo = buffer.GetString();
	return true;
}

bool CommandListModInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A08250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandListModInfo@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// char buffer[32];
		// std::string version;
		// std::string hash_str;
		// std::string filename;
		// tm *convertedLocal;
		// s_static_string<32> metadata_name;

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	c_mod_package_manager::c_threadsafe_iterator it = package_manager.lock_for_iteration();
	std::string modHash = c_mod_system::get_current_package_hash();
	if (Arguments.size() == 1)
		modHash = Arguments[0];
	while (it.next())
	{
		std::string hash_str;
		Utils::String::BytesToHexString(it->hash, sizeof(it->hash), hash_str);
		if (!(hash_str == modHash))
			continue;
		s_static_string<32> metadata_name;
		metadata_name.set_wchar(it->name);
		writer.StartObject();
		writer.Key("verified");
		writer.Bool(it->verified);
		writer.Key("name");
		writer.String(metadata_name.get_string());
		writer.Key("author");
		writer.String(it->author);
		writer.Key("authorUid");
		writer.Uint64(it->author_uid);
		writer.Key("description");
		writer.String(it->description);
		writer.Key("website");
		writer.String(it->website);
		writer.Key("filesize");
		writer.Int64(it->file_size);
		writer.Key("hash");
		writer.String(hash_str.c_str());
		writer.Key("filename");
		std::string filename = it->file.filename;
		writer.String(filename.substr(filename.find_last_of("\\") + 1, filename.length()).c_str());
		writer.Key("version");
		std::string version = std::to_string(it->version_major) + "." + std::to_string(it->version_minor);
		writer.String(version.c_str());
		writer.Key("mainmenuType");
		writer.Bool(it->modtype.mainmenu);
		writer.Key("characterType");
		writer.Bool(it->modtype.character);
		writer.Key("multiplayerType");
		writer.Bool(it->modtype.multiplayer);
		writer.Key("campaignType");
		writer.Bool(it->modtype.campaign);
		writer.Key("firefightType");
		writer.Bool(it->modtype.firefight);
		writer.Key("downloadDate");
		tm *convertedLocal = localtime(&it->dateAdded);
		char buffer[32];
		strftime(buffer, 32, "%m/%d/%Y", convertedLocal);
		writer.String(buffer);
		writer.Key("lastUsedDate");
		writer.String(std::to_string(it->lastUsed).c_str());
		writer.Key("source");
		writer.String(it->origin.server_name.c_str());
		writer.EndObject();
		if (hash_str == modHash)
			break;
	}
	returnInfo = buffer.GetString();
	return true;
}

bool CommandListModFiles(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A07EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandListModFiles@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
		// std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry> modFileList;
		// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
			// std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry> &<range>$L0;
			// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > > <begin>$L0;
			// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > > <end>$L0;
				// std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> fileEntry;
					// std::string file;

	if (Arguments.size() == 1)
	{
		std::unordered_map<std::string, CModPackageFileSystemView::SFileEntry> modFileList = c_mod_system::get_package_file_list(Arguments[0]);
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("Files");
		jsonWriter.StartArray();
		for (auto fileEntry : modFileList)
		{
			std::string file = fileEntry.first;
			jsonWriter.String(file.c_str());
		}
		jsonWriter.EndArray();
		jsonWriter.EndObject();
		returnInfo = jsonBuffer.GetString();
		return true;
	}
	returnInfo = "Missing Mod hash Argument.";
	return false;
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

bool CommandDeleteMod(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A07DA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDeleteMod@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandDeleteMod
	// std::string &returnInfo;
	// c_mod_package_manager &package_manager;

	if (Arguments.size() < 1)
		return false;

	c_mod_package_manager *package_manager = &c_mod_system::get_package_manager();

	if (!package_manager->delete_package_by_filename(Arguments[0].c_str()))
	{
		returnInfo = "failed to delete mod package";
		return false;
	}

	returnInfo = "mod package deleted";
	return true;
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
