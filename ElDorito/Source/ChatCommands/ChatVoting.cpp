/* ---------- headers */

#include "ChatCommands/ChatVoting.hpp"
#include "hades/hades.h"

#include "Modules/ModuleServer.hpp"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "ElDorito.hpp"
#include "Pointer.hpp"
#include "Server/ServerChat.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
		struct SessionMembership;
	}
}
namespace ChatCommands
{
	class EndGameCommand;
	class EndRoundCommand;
	class KickIndexCommand;
	class KickPlayerCommand;
	class ShuffleTeamsCommand;
	class VotingChatCommand;
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
	namespace Chat {}
	using namespace Server::Chat;
}

namespace Modules {}
using namespace ::Modules;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x10933FC0  // hades: added for 0x10933FC0
namespace ChatCommands { extern bool addToVoteTimes(unsigned long long sender); }  // hades: added for 0x10933FC0  // hades: added for 0x10933FC0

namespace Server::Chat { bool SendServerMessage(const std::string &message); }  // hades: added for 0X10930A70

namespace ChatCommands
{
	extern __int32 findNumberOfPlayersInGame();
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace ChatCommands
{
	__int32 findNumberOfPlayersInGame() // 0x10933000
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?findNumberOfPlayersInGame@ChatCommands@@YAHXZ");
		// procedure flags: nofpo
		// Blam::Network::SessionMembership *membership;
		// __int32 numberOfPlayers;
		// Blam::Network::Session *session;
			// __int32 peerIdx;
				// __int32 playerIdx;

		auto* session = Blam::Network::GetActiveSession();
		if (!session || !session->IsEstablished() || !session->IsHost())
			return 0;

		int numberOfPlayers = 0;
		auto membership = &session->MembershipInfo;
		for (auto peerIdx = membership->FindFirstPeer(); peerIdx >= 0; peerIdx = membership->FindNextPeer(peerIdx))
		{
			auto playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
			if (playerIdx == -1 || !session->MembershipInfo.Peers[peerIdx].IsEstablished())
				continue;

			numberOfPlayers++;
		}
		return numberOfPlayers;
	}

	ShuffleTeamsCommand::ShuffleTeamsCommand() : VotingChatCommand("shuffleTeams", "Starts a vote to shuffle the teams. Type !yes to vote.") /* hades-mem-init: : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) */ // 0x1092F740
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ShuffleTeamsCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::ShuffleTeamsCommand *const this;
	}

	void ShuffleTeamsCommand::doOnVotePass(std::string name) // 0x10931630
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVotePass@ShuffleTeamsCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;

		Server::Chat::SendServerMessage("Final vote cast by " + name + ". Vote has passed.");
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("server.shuffleteams", false);
	}

	bool ShuffleTeamsCommand::isEnabled() // 0x10933450
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isEnabled@ShuffleTeamsCommand@ChatCommands@@UAE_NXZ");
		// ChatCommands::ShuffleTeamsCommand *const this;

		return Modules::ModuleServer::Instance().VarChatCommandShuffleTeamsEnabled->ValueInt == 1;
	}

	void ShuffleTeamsCommand::doOnVoteFail() // 0x10930D00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteFail@ShuffleTeamsCommand@ChatCommands@@UAEXXZ");
		// ChatCommands::ShuffleTeamsCommand *const this;

		Server::Chat::SendServerMessage("Vote has not passed.");
	}

	void ShuffleTeamsCommand::doOnVoteStart(std::string starterName) // 0x109328A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteStart@ShuffleTeamsCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10932B94
		// static ...; // 0x10932B8C
		// ChatCommands::ShuffleTeamsCommand *const this;
		// std::string starterName;
		// std::string previousValue;

		std::string previousValue;
		Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVoteAction, std::string("shuffle teams"), previousValue);
		Server::Chat::SendServerMessage(starterName + " has started a vote to shuffle the teams. " + std::to_string(votesNeeded) + " vote" + (votesNeeded > 1 ? "s" : "") + " needed to pass. Type !yes to vote");
	}

	bool ShuffleTeamsCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x10933E00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isValidArgument@ShuffleTeamsCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &returnInfo;

		if (Blam::Network::GetActiveSession()->HasTeams())
		{
			return true;
		}
		else
		{
			returnInfo = "Only team games can be shuffled.";
			return false;
		}
	}

	EndGameCommand::EndGameCommand() : VotingChatCommand("endGame", "Starts a vote to end the current game. Type !yes to vote.") /* hades-mem-init: : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) */ // 0x1092F360
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0EndGameCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::EndGameCommand *const this;
	}

	void EndGameCommand::doOnVotePass(std::string name) // 0x10930DD0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVotePass@EndGameCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;

		Server::Chat::SendServerMessage("Final vote cast by " + name + ". Vote has passed.");
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("game.end", false);
	}

	bool EndGameCommand::isEnabled() // 0x10933250
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isEnabled@EndGameCommand@ChatCommands@@UAE_NXZ");
		// ChatCommands::EndGameCommand *const this;

		return Modules::ModuleServer::Instance().VarChatCommandEndGameEnabled->ValueInt == 1;
	}

	void EndGameCommand::doOnVoteFail() // 0x109309A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteFail@EndGameCommand@ChatCommands@@UAEXXZ");
		// ChatCommands::EndGameCommand *const this;

		Server::Chat::SendServerMessage("Vote has not passed.");
	}

	void EndGameCommand::doOnVoteStart(std::string starterName) // 0x109317E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteStart@EndGameCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10931AD4
		// static ...; // 0x10931ACC
		// ChatCommands::EndGameCommand *const this;
		// std::string starterName;
		// std::string previousValue;

		std::string previousValue;
		Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVoteAction, std::string("end the game"), previousValue);
		Server::Chat::SendServerMessage(starterName + " has started a vote to end the game. " + std::to_string(votesNeeded) + " vote" + (votesNeeded > 1 ? "s" : "") + " needed to pass. Type !yes to vote.");
	}

	bool EndGameCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x109334D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isValidArgument@EndGameCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &returnInfo;
		// function call : bool (*const)()

		if (((bool (*const)())0x550F90)())
			return true;
		returnInfo = "You must be currently in a round.";
		return false;
	}

	EndRoundCommand::EndRoundCommand() : VotingChatCommand("endRound", "Starts a vote to end the current round. Type !yes to vote.") /* hades-mem-init: : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) */ // 0x1092F450
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0EndRoundCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::EndRoundCommand *const this;
	}

	void EndRoundCommand::doOnVotePass(std::string name) // 0x10930F80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVotePass@EndRoundCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;

		Server::Chat::SendServerMessage("Final vote cast by " + name + ". Vote has passed.");
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("game.endround", false);
	}

	bool EndRoundCommand::isEnabled() // 0x109332D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isEnabled@EndRoundCommand@ChatCommands@@UAE_NXZ");
		// ChatCommands::EndRoundCommand *const this;

		return Modules::ModuleServer::Instance().VarChatCommandEndRoundEnabled->ValueInt == 1;
	}

	void EndRoundCommand::doOnVoteFail() // 0x10930A70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteFail@EndRoundCommand@ChatCommands@@UAEXXZ");
		// ChatCommands::EndRoundCommand *const this;

		Server::Chat::SendServerMessage("Vote has not passed.");
	}

	void EndRoundCommand::doOnVoteStart(std::string starterName) // 0x10931BC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteStart@EndRoundCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10931EB4
		// static ...; // 0x10931EAC
		// ChatCommands::EndRoundCommand *const this;
		// std::string starterName;
		// std::string previousValue;

		std::string previousValue;
		Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVoteAction, std::string("end the round"), previousValue);
		Server::Chat::SendServerMessage(starterName + " has started a vote to end the round. " + std::to_string(votesNeeded) + " vote" + (votesNeeded > 1 ? "s" : "") + " needed to pass. Type !yes to vote.");
	}

	bool EndRoundCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x109335D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isValidArgument@EndRoundCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &returnInfo;
		// function call : bool (*const)()

		if (((bool (*const)())0x550F90)())
			return true;
		returnInfo = "You must be currently in a round.";
		return false;
	}

	KickIndexCommand::KickIndexCommand() : VotingChatCommand("kickIndex", "Starts a vote to kick a player by index.") /* hades-mem-init: : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) */ // 0x1092F540
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0KickIndexCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::KickIndexCommand *const this;
	}

	void KickIndexCommand::doOnVotePass(std::string name) // 0x10931130
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVotePass@KickIndexCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;

		Server::Chat::SendServerMessage("Final vote cast by " + name + ". " + playerName + " has been kicked and temporarily banned.");
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("server.KickTempBanPlayer " + playerName, false);
		playerName = "";
	}

	void KickIndexCommand::doOnVoteFail() // 0x10930B40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteFail@KickIndexCommand@ChatCommands@@UAEXXZ");
		// ChatCommands::KickIndexCommand *const this;

		playerName = "";
		Server::Chat::SendServerMessage("Vote has not passed.");
	}

	bool KickIndexCommand::isEnabled() // 0x10933350
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isEnabled@KickIndexCommand@ChatCommands@@UAE_NXZ");
		// ChatCommands::KickIndexCommand *const this;

		return Modules::ModuleServer::Instance().VarChatCommandKickPlayerEnabled->ValueInt == 1;
	}

	void KickIndexCommand::doOnVoteStart(std::string starterName) // 0x10931FA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteStart@KickIndexCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10932320
		// static ...; // 0x10932318
		// ChatCommands::KickIndexCommand *const this;
		// std::string starterName;
		// std::string previousValue;

		std::string previousValue;
		Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVoteAction, "kick " + playerName, previousValue);
		Server::Chat::SendServerMessage(starterName + " has started a kick vote for: \"" + playerName + "\"; Type !yes to vote. " + std::to_string(votesNeeded) + " vote" + (votesNeeded > 1 ? "s" : "") + " needed to kick.");
	}

	bool KickIndexCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x109336D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isValidArgument@KickIndexCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// static ...; // 0x1093395C
	// $LN16:
		// ChatCommands::KickIndexCommand *const this;
		// std::string s;
		// std::string &returnInfo;
		// Blam::Network::PlayerSession *player;
		// __int32 indexToKick;
		// std::string kickPlayerName;
		// Blam::Network::Session *session;

		if (s.empty())
		{
			returnInfo = "You must enter a valid player index to use this command.";
			return false;
		}
		__int32 indexToKick = -1;
		try
		{
			indexToKick = std::stoi(s);
		}
		catch (...)
		{
		}
		if (indexToKick < 0 || indexToKick > 15)
		{
			returnInfo = "Invalid index";
			return false;
		}
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (indexToKick == starterIndex)
		{
			returnInfo = "You cannot kick yourself.";
			return false;
		}
		else if (indexToKick == session->MembershipInfo.HostPeerIndex && !ElDorito::Instance().IsDedicated())
		{
			returnInfo = "You cannot kick the host.";
			return false;
		}
		Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[indexToKick];
		std::string kickPlayerName = Utils::String::ThinString(player->Properties.host.player_name);
		if (kickPlayerName.empty())
		{
			returnInfo = "Could not find player.";
			return false;
		}
		playerName = kickPlayerName;
		return true;
	}

	KickPlayerCommand::KickPlayerCommand() : VotingChatCommand("kick", "Starts a vote to kick a player.") /* hades-mem-init: : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) */ // 0x1092F640
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0KickPlayerCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::KickPlayerCommand *const this;
	}

	void KickPlayerCommand::doOnVotePass(std::string name) // 0x109313B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVotePass@KickPlayerCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;

		Server::Chat::SendServerMessage("Final vote cast by " + name + ". " + playerName + " has been kicked and temporarily banned.");
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("server.KickTempBanPlayer " + playerName, false);
		playerName = "";
	}

	void KickPlayerCommand::doOnVoteFail() // 0x10930C20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteFail@KickPlayerCommand@ChatCommands@@UAEXXZ");
		// ChatCommands::KickPlayerCommand *const this;

		playerName = "";
		Server::Chat::SendServerMessage("Vote has not passed.");
	}

	bool KickPlayerCommand::isEnabled() // 0x109333D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isEnabled@KickPlayerCommand@ChatCommands@@UAE_NXZ");
		// ChatCommands::KickPlayerCommand *const this;

		return Modules::ModuleServer::Instance().VarChatCommandKickPlayerEnabled->ValueInt == 1;
	}

	void KickPlayerCommand::doOnVoteStart(std::string starterName) // 0x10932420
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?doOnVoteStart@KickPlayerCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x109327A0
		// static ...; // 0x10932798
		// ChatCommands::KickPlayerCommand *const this;
		// std::string starterName;
		// std::string previousValue;

		std::string previousValue;
		Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVoteAction, "kick " + playerName, previousValue);
		Server::Chat::SendServerMessage(starterName + " has started a kick vote for: \"" + playerName + "\"; Type !yes to vote. " + std::to_string(votesNeeded) + " vote" + (votesNeeded > 1 ? "s" : "") + " needed to kick.");
	}

	bool KickPlayerCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x10933A30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isValidArgument@KickPlayerCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &returnInfo;
		// __int32 playerToKickIdx;
		// Blam::Network::SessionMembership *membership;
			// __int32 peerIdx;
				// Blam::Network::PlayerSession *player;
				// __int32 playerIdx;

		if (s.empty())
		{
			returnInfo = "You must enter a name to use this command.";
			return false;
		}
		else if (s.length() > 16)
		{
			returnInfo = "Player not found.";
			return false;
		}
		__int32 playerToKickIdx = -1;
		Blam::Network::SessionMembership *membership = &Blam::Network::GetActiveSession()->MembershipInfo;
		for (__int32 peerIdx = membership->FindFirstPeer(); peerIdx >= 0; peerIdx = membership->FindNextPeer(peerIdx))
		{
			__int32 playerIdx = membership->GetPeerPlayer(peerIdx);
			if (playerIdx == -1)
				continue;
			Blam::Network::PlayerSession *player = &membership->PlayerSessions[playerIdx];
			if (Utils::String::ThinString(player->Properties.host.player_name) == s)
				playerToKickIdx = playerIdx;
		}
		if (playerToKickIdx < 0)
		{
			returnInfo = "Player \"" + s + "\" not found.";
			return false;
		}
		else if (playerToKickIdx == starterIndex)
		{
			returnInfo = "You cannot kick yourself.";
			return false;
		}
		else if (playerToKickIdx == 0 && !ElDorito::Instance().IsDedicated())
		{
			returnInfo = "You cannot kick the host.";
			return false;
		}
		playerName = s;
		return true;
	}

	VotingChatCommand::VotingChatCommand(std::string n, std::string d) : starterIndex(-1), votesNeeded(0), currentlyVoting(false), voteTimeStarted(0) /* hades-mem-init:  */ // 0x1092F830
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0VotingChatCommand@ChatCommands@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
		// std::string d;

		name = n;
		description = d;
	}

	bool VotingChatCommand::isCurrentlyVoting() // 0x10933220
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?isCurrentlyVoting@VotingChatCommand@ChatCommands@@QAE_NXZ");
		// ChatCommands::VotingChatCommand *const this;

		return currentlyVoting;
	}

	void VotingChatCommand::tick() // 0x10934EB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?tick@VotingChatCommand@ChatCommands@@QAEXXZ");
		// static ...; // 0x10934FBC
		// static ...; // 0x10934FB0
		// static ...; // 0x10934FA8
		// ChatCommands::VotingChatCommand *const this;
		// long long curTime;
		// long long elapsed;
		// function call : bool ()
		// function call : void ()
		//Exit if we haven't used up the time yet.
		//Exit if we haven't used up the time yet.

		if (!isEnabled() || voteTimeStarted == 0)
			return;

		time_t curTime;
		time(&curTime);
		auto elapsed = curTime - voteTimeStarted;

		//Exit if we haven't used up the time yet.
		if (elapsed < Modules::ModuleServer::Instance().VarChatCommandVoteTime->ValueInt)
			return;

		doOnVoteFail();
		endVoting();
	}

	void VotingChatCommand::endVoting() // 0x10932D10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?endVoting@VotingChatCommand@ChatCommands@@QAEXXZ");
		// static ...; // 0x10932F5C
		// static ...; // 0x10932F50
		// static ...; // 0x10932F48
		// ChatCommands::VotingChatCommand *const this;
		// std::string previousValue;

		yesVoters.clear();
		currentlyVoting = false;
		voteTimeStarted = 0;
		votesNeeded = 0;
		std::string previousValue;
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVoteStartedByUid, std::string(""), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVotesNeeded, std::to_string(0), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVoteStarted, std::to_string(0), previousValue);
	}

	void VotingChatCommand::processMessage(unsigned char sender, std::string argument) // 0x10933FC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?processMessage@VotingChatCommand@ChatCommands@@QAEXEV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x109344AA
		// static ...; // 0x109344A0
		// static ...; // 0x10934470
		// static ...; // 0x10934468
		// ChatCommands::VotingChatCommand *const this;
		// unsigned char sender;
		// std::string argument;
		// std::string returnInfo;
		// unsigned long long uid;
		// Blam::Network::SessionMembership &membership;
		// std::string name;
			// char uidString[32];
			// __int32 numPlayers;
			// std::string previousValue;
		// function call : bool ()
		// function call : bool (std::string, std::string &)
		// function call : void (std::string)

		if (!isEnabled())
			return;
		std::string returnInfo;
		Blam::Network::SessionMembership &membership = Blam::Network::GetActiveSession()->MembershipInfo;
		starterIndex = membership.GetPeerPlayer(sender);
		if (!isValidArgument(argument, returnInfo))
		{
			Server::Chat::SendServerMessage(returnInfo, sender);
			return;
		}
		unsigned long long uid = membership.PlayerSessions[starterIndex].Properties.host.player_uid;
		std::string name = Utils::String::ThinString(membership.PlayerSessions[starterIndex].Properties.host.player_name);
		if (addToVoteTimes(uid))
		{
			__int32 numPlayers = findNumberOfPlayersInGame();
			votesNeeded = (numPlayers - 1) * Utils::Singleton<Modules::ModuleServer>::Instance().VarServerVotePassPercentage->ValueInt / 100 + 1;
			currentlyVoting = true;
			time(&voteTimeStarted);
			doOnVoteStart(name);
			std::string previousValue;
			char uidString[32] = {};
			player_format_uid(uidString, uid);
			Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVoteStartedByUid, std::string(uidString), previousValue);
			Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVotesNeeded, std::to_string(votesNeeded), previousValue);
			Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVoteStarted, std::to_string(1), previousValue);
			processVote(sender, "yes");
		}
		else
			Server::Chat::SendServerMessage("You must wait to start another vote.", sender);
	}

	void VotingChatCommand::processVote(unsigned char sender, std::string message) // 0x10934610
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?processVote@VotingChatCommand@ChatCommands@@QAEXEV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10934C54
		// static ...; // 0x10934C30
		// static ...; // 0x10934C28
		// ChatCommands::VotingChatCommand *const this;
		// unsigned char sender;
		// std::string message;
			// unsigned long long uid;
			// Blam::Network::SessionMembership &membership;
			// std::string name;
				// std::string previousValue;
				// unsigned __int32 votesRemaining;
		// function call : bool ()
		// function call : void (std::string)

		if (!isEnabled())
			return;
		std::transform(message.begin(), message.end(), message.begin(), ::tolower);
		if (message == "yes" || message == Utils::String::ToLower(name))
		{
			Blam::Network::SessionMembership &membership = Blam::Network::GetActiveSession()->MembershipInfo;
			unsigned long long uid = membership.PlayerSessions[membership.GetPeerPlayer(sender)].Properties.host.player_uid;
			std::string name = Utils::String::ThinString(membership.PlayerSessions[membership.GetPeerPlayer(sender)].Properties.host.player_name);
			if (uid == 0)
				return;
			if (std::find(yesVoters.begin(), yesVoters.end(), uid) != yesVoters.end())
			{
				Server::Chat::SendServerMessage("You cannot vote twice.", sender);
				return;
			}
			yesVoters.push_back(uid);
			if (yesVoters.size() >= votesNeeded)
			{
				doOnVotePass(name);
				endVoting();
			}
			else
			{
				unsigned __int32 votesRemaining = votesNeeded - yesVoters.size();
				Server::Chat::SendServerMessage("Vote cast by \"" + name + "\". Remaining votes needed: " + std::to_string(votesRemaining));
				std::string previousValue;
				Utils::Singleton<Modules::CommandMap>::Instance().SetVariable2(Utils::Singleton<Modules::ModuleServer>::Instance().VarChatVotesNeeded, std::to_string(votesRemaining), previousValue);
			}
		}
	}
}


namespace ChatCommands
{
	std::string VotingChatCommand::getName() // 0x109331A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?getName@VotingChatCommand@ChatCommands@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// ChatCommands::VotingChatCommand *const this;

		return name;
	}
}


namespace ChatCommands
{
	std::string VotingChatCommand::getDescription() // 0x10933120
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?getDescription@VotingChatCommand@ChatCommands@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// ChatCommands::VotingChatCommand *const this;

		return description;
	}
}

/* ---------- private code */
