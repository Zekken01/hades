/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCustomization.hpp"
#include "Server/BanList.hpp"
#include "Server/ServerChat.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x106CEA80

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_mod_package_manager;
class c_network_session;
class c_network_session_membership;
struct begin;
struct c_game_engine;
struct end;
struct lambda_1;
struct s_damage_data;
struct s_damage_reporting_info;
struct s_file_reference;
struct s_mod_origin_info;
struct s_network_session_player;
struct s_player_datum;
struct s_player_identifier;
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
	}
}
namespace Modules
{
	class ModuleServer;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace ChatCommands {}
using namespace ::ChatCommands;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace ReportHandler {}
	using namespace Server::ReportHandler;
	namespace Chat {}
	using namespace Server::Chat;
}

namespace Modules {}
using namespace ::Modules;
namespace Objects {}
using namespace ::Objects;
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

//class CommandKill::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(CommandKill::__l2::<lambda_1> &);
//	<lambda_1>(unsigned long, __int32 const &);
//private:
//	unsigned long unitIndex; // 0x0
//	__int32 peer; // 0x4
//public:
//	CommandKill::__l2::<lambda_1> &operator=(CommandKill::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CommandKill::__l2::<lambda_1>) == 8, "Invalid CommandKill::__l2::<lambda_1> size");

/* ---------- prototypes */

#include "Objects/ObjectMessaging.hpp"  // hades: added for 0x106CF2F0
#include "Blam/game/game_globals.hpp"  // hades: added for 0x106CF2F0
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x106CF2F0

namespace Server { namespace ReportHandler { extern void Handle(std::string const &token); } }  // hades: added for 0x106CF550

extern bool (*const network_session_interface_get_squad_session)(c_network_session **out_session);  // hades: added for 0x106CF690

namespace ChatCommands
{
	extern void RegisterCommands();
}

__int32 FindPlayerInGameWithIdentifier(s_player_identifier const &identifier);
__int32 FindNetworkPlayerInGame(char networkPlayerIndex);
bool CommandHelp(__int32 peer, std::vector<std::string> const &args, std::string &returnValue);
bool ComamndListPlayers(__int32 peer, std::vector<std::string> const &args, std::string &returnValue);
bool CommandReportPlayer(__int32 peer, std::vector<std::string> const &args, std::string &returnValue);
bool CommandKill(__int32 peer, std::vector<std::string> const &args, std::string &returnValue);
bool ComamndModInfo(__int32 peer, std::vector<std::string> const &args, std::string &returnValue);

/* ---------- globals */

namespace Utils
{
	Modules::ModuleServer *Utils::Singleton<Modules::ModuleServer>::m_instance; // 0x11387E7C
}

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		// extern std::string DefaultBanListPath; // 0x11387E58  // hades: defined (with its initialiser) elsewhere now
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

namespace ChatCommands
{
	void RegisterCommands() // 0x106CFAB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterCommands@ChatCommands@@YAXXZ");
		// procedure flags: nofpo

		RegisterCommand("list", "Returns the list of players in the server", (CommandFlags)0, ComamndListPlayers);
		RegisterCommand("mod", "returns the mod information", (CommandFlags)0, ComamndModInfo);
		RegisterCommand("listplayers", "Returns the list of players in the server", (CommandFlags)0, ComamndListPlayers);
		RegisterCommand("help", "Displays the list of commands", (CommandFlags)0, CommandHelp);
		RegisterCommand("plrrpt", "Report a player", Hidden, CommandReportPlayer);
		RegisterCommand("kill", "Kills the player that runs this command", (CommandFlags)0, CommandKill);
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0mod_type@c_mod_package_manager@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_damage_data@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_damage_reporting_info@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_entry@c_mod_package_manager@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_file_reference@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_origin_info@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1s_entry@c_mod_package_manager@@QAE@XZ"); no body to assert in
// c_mod_package_manager::s_entry::~s_entry() is implicit; 0x106CDE70

// mangled_x86(MANGLED_DEFAULT, "??1s_mod_origin_info@@QAE@XZ"); no body to assert in
// s_mod_origin_info::~s_mod_origin_info() is implicit; 0x106CDED0

/* ---------- private code */

__int32 FindPlayerInGameWithIdentifier(s_player_identifier const &identifier) // 0x106CF7B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindPlayerInGameWithIdentifier@@YAHABUs_player_identifier@@@Z");
	// `anonymous-namespace'::FindPlayerInGameWithIdentifier
	// static ...; // 0x106CF888
	// static ...; // 0x106CF87C
	// static ...; // 0x106CF874
	// s_player_identifier const &identifier;
	// c_data_array<s_player_datum> *players;
		// c_data_iterator<s_player_datum> it;
	// function call : bool (*const)()

	static bool (*const game_in_progress)() = reinterpret_cast<bool (*)()>(0x5314B0);
	if (!game_in_progress())
		return -1;
	c_data_array<s_player_datum> *players = players_get();
	for (c_data_iterator<s_player_datum> it = players->begin(); it != players->end(); ++it)
	{
		if (it->player_identifier == identifier)
			return it.current_datum_index;
	}
	return -1;
}

__int32 FindNetworkPlayerInGame(char networkPlayerIndex) // 0x106CF690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindNetworkPlayerInGame@@YAHD@Z");
	// `anonymous-namespace'::FindNetworkPlayerInGame
	// static ...; // 0x106CF764
	// static ...; // 0x106CF758
	// static ...; // 0x106CF750
	// char networkPlayerIndex;
	// c_network_session_membership *membership;
	// s_network_session_player *networkPlayer;
	// c_network_session *session;
	// function call : bool (*const)(c_network_session **)

	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session) || !session->established())
		return -1;

	c_network_session_membership *membership = session->get_session_membership();
	if (!membership->is_player_valid(networkPlayerIndex))
		return -1;

	s_network_session_player *networkPlayer = membership->get_player(networkPlayerIndex);
	return FindPlayerInGameWithIdentifier(networkPlayer->player_identifier);
}

bool CommandHelp(__int32 peer, std::vector<std::string> const &args, std::string &returnValue) // 0x106CF180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandHelp@@YA_NHABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandHelp
	// static ...; // 0x106CF280
	// static ...; // 0x106CF278
	// __int32 peer;
	// std::vector<std::string> const &args;
	// std::string &returnValue;
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
			// std::string i;

	for (auto i : ChatCommands::getHelpText())
		Server::Chat::SendServerMessage(i, peer);
	return true;
}

bool ComamndListPlayers(__int32 peer, std::vector<std::string> const &args, std::string &returnValue) // 0x106CE6E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ComamndListPlayers@@YA_NHABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::ComamndListPlayers
	// std::string &returnValue;
	// Blam::Network::Session *session;
	// __int32 peerIdx;
		// __int32 playerIdx;
			// Blam::Network::PlayerSession *player;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	__int32 peerIdx = session->MembershipInfo.FindFirstPeer();
	while (peerIdx != -1)
	{
		__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
		if (playerIdx != -1)
		{
			Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[playerIdx];
			Server::Chat::SendServerMessage("(" + std::to_string(playerIdx) + ") " + "\"" + Utils::String::ThinString(player->Properties.host.player_name) + "\"", peer);
		}
		peerIdx = session->MembershipInfo.FindNextPeer(peerIdx);
	}
	return true;
}

bool CommandReportPlayer(__int32 peer, std::vector<std::string> const &args, std::string &returnValue) // 0x106CF550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandReportPlayer@@YA_NHABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandReportPlayer
	// std::string &returnValue;

	if (args.size() < 1 || args[0].length() <= 128)
	{
		returnValue = "Invalid or missing token";
		return false;
	}

	returnValue = "Player report received";
	Server::ReportHandler::Handle(std::string(args[0]));
	return true;
}

bool CommandKill(__int32 peer, std::vector<std::string> const &args, std::string &returnValue) // 0x106CF2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandKill@@YA_NHABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandKill
	// std::string &returnValue;
	// s_player_datum *player;
	// __int32 playerIndex;
	// __int32 networkPlayerIndex;
	// Blam::Network::Session *session;
	// function call : bool (*const)()
	// function call : c_game_engine *(*const)()
	// function call : bool (*const)()

	static bool (*const game_in_progress)() = reinterpret_cast<bool (*)()>(0x5314B0);
	static c_game_engine *(*const current_game_engine)() = reinterpret_cast<c_game_engine *(*)()>(0x5CE150);
	static bool (*const game_engine_round_in_progress)() = reinterpret_cast<bool (*)()>(0x531B20);
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session->IsEstablished() || !session->IsHost())
		return false;
	__int32 networkPlayerIndex = session->MembershipInfo.GetPeerPlayer(peer);
	if (networkPlayerIndex == -1)
		return false;
	__int32 playerIndex = FindNetworkPlayerInGame(networkPlayerIndex);
	if (playerIndex == -1)
		return false;
	if (!game_in_progress())
	{
		returnValue = "The command cannot be run at this time.";
		return false;
	}
	if (!Utils::Singleton<Modules::ModuleServer>::Instance().VarServerKillCommandEnabled->ValueInt || (current_game_engine() && game_engine_round_in_progress() && !Utils::Singleton<Modules::ModuleServer>::Instance().VarServerKillCommandDuringPodiumEnabled->ValueInt))
	{
		returnValue = "The kill command is not enabled right now.";
		return false;
	}
	s_player_datum *player = player_get(playerIndex);
	if (player->unit_index == -1)
	{
		returnValue = "Stop, he's already dead!";
		return false;
	}
	Objects::CObjectMessaging::EnqueueAction([unitIndex = player->unit_index, peer]()
	{
		s_object_data *unit = object_try_and_get_and_verify_type(unitIndex, 0x2003);
		if (!unit)
			return;
		float const epsilon = 0.001f;
		if (abs(unit->recent_body_damage - 0.0f) > epsilon || abs(unit->recent_shield_damage - 0.0f) > epsilon)
		{
			Server::Chat::SendServerMessage("Man up!", peer);
			return;
		}
		s_damage_data damageData;
		reinterpret_cast<void (*)(s_damage_data *, long)>(0xB50330)(&damageData, game_globals_get()->PlayerFallingDamage->FallingDamage.index);
		damageData.flags |= 4;
		damageData.reporting_info.type = _damage_reporting_type_guardians_unknown;
		reinterpret_cast<void (*)(unsigned long, s_damage_owner *)>(0xB770E0)(unitIndex, &damageData.damage_owner);
		reinterpret_cast<void (*)(s_damage_data *, unsigned long, long)>(0xB542A0)(&damageData, unitIndex, 5);
		std::string response = Utils::Singleton<Modules::ModuleServer>::Instance().VarKillCommandMessage->ValueString;
		if (response.size() > 0)
			Server::Chat::SendServerMessage(response, peer);
	});
	return true;
}

bool ComamndModInfo(__int32 peer, std::vector<std::string> const &args, std::string &returnValue) // 0x106CEA80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ComamndModInfo@@YA_NHABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::ComamndModInfo
	// static ...; // 0x106CEFF9
	// static ...; // 0x106CEFF4
	// static ...; // 0x106CEFEC
	// static ...; // 0x106CEFB0
	// static ...; // 0x106CEFA8
	// __int32 peer;
	// std::vector<std::string> const &args;
	// std::string &returnValue;
	// char buffer[32];
	// std::string desc;
	// bool hasModSet;
	// std::string modhash;
	// c_mod_package_manager::s_entry mod_package;
	// std::string message;
	// tm *convertedLocal;

	std::string modhash = c_mod_system::get_current_package_hash();
	c_mod_package_manager::s_entry mod_package;
	bool hasModSet = c_mod_system::get_mod_info_by_hash(modhash.c_str(), &mod_package);
	if (!hasModSet)
	{
		returnValue = "No Mod Loaded";
		return false;
	}
	Server::Chat::SendServerMessage("Mod: " + Utils::String::ThinString(mod_package.name) + " v" + std::to_string(mod_package.version_major) + "." + std::to_string(mod_package.version_minor), peer);
	tm *convertedLocal = localtime(&mod_package.dateBuilt);
	char buffer[32];
	strftime(buffer, 32, "%m/%d/%Y", convertedLocal);
	Server::Chat::SendServerMessage("Created: " + std::string(buffer), peer);
	std::string desc = mod_package.description;
	std::string message = "Desc: " + desc;
	if (message.size() > 256)
		message = message.substr(0, 253) + "...";
	Server::Chat::SendServerMessage(message, peer);
	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleServer & Utils::Singleton<Modules::ModuleServer>::Instance();
template bool c_data_iterator<s_player_datum>::operator!=(c_data_iterator<s_player_datum> const &) const;
template bool c_data_iterator<s_player_datum>::operator==(c_data_iterator<s_player_datum> const &) const;
template bool c_tag_block<s_game_globals_falling_damage>::try_get_element(__int32, s_game_globals_falling_damage **) const;
template c_data_iterator<s_player_datum> & c_data_iterator<s_player_datum>::operator++();
template c_data_iterator<s_player_datum> c_data_array<s_player_datum>::begin();
template c_data_iterator<s_player_datum> c_data_array<s_player_datum>::end();
template c_data_iterator<s_player_datum>::c_data_iterator(s_data_array *);
template c_enum<enum e_damage_reporting_type,short> & c_enum<enum e_damage_reporting_type,short>::operator=(e_damage_reporting_type const &);
template c_enum<enum e_damage_reporting_type,short>::c_enum();
template c_enum<enum e_file_reference_location,short>::c_enum();
template c_enum<enum e_file_reference_location,short>::c_enum(c_enum<enum e_file_reference_location,short> const &);
template c_enum<enum e_file_reference_location,short>::c_enum(e_file_reference_location const &);
template c_enum<enum e_file_reference_location,short>::c_enum(short const &);
template c_flags<enum e_file_reference_flags,unsigned short>::c_flags();
template s_game_globals_falling_damage * c_tag_block<s_game_globals_falling_damage>::get_element(__int32) const;
template s_game_globals_falling_damage * c_tag_block<s_game_globals_falling_damage>::operator->();
template s_player_datum & c_data_iterator<s_player_datum>::next();
template s_player_datum * c_data_iterator<s_player_datum>::operator->();
