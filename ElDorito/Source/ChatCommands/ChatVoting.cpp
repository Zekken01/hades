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

	extern ShuffleTeamsCommand* _sub_1092F740(ChatCommands::ShuffleTeamsCommand *const);
	ShuffleTeamsCommand::ShuffleTeamsCommand() : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) // 0x1092F740
	{
		mangled_x86(MANGLED_TODO, "??0ShuffleTeamsCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::ShuffleTeamsCommand *const this;
		todo("implement");
		_sub_1092F740(this);
	}

	_extern void _sub_10931630(ChatCommands::ShuffleTeamsCommand *const, std::string);
	void ShuffleTeamsCommand::doOnVotePass(std::string name) // 0x10931630
	{
		mangled_x86(MANGLED_TODO, "?doOnVotePass@ShuffleTeamsCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;
		todo("implement");
		_sub_10931630(this, name);
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

	_extern void _sub_109328A0(ChatCommands::ShuffleTeamsCommand *const, std::string);
	void ShuffleTeamsCommand::doOnVoteStart(std::string starterName) // 0x109328A0
	{
		mangled_x86(MANGLED_TODO, "?doOnVoteStart@ShuffleTeamsCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10932B94
		// static ...; // 0x10932B8C
		// ChatCommands::ShuffleTeamsCommand *const this;
		// std::string starterName;
		// std::string previousValue;
		todo("implement");
		_sub_109328A0(this, starterName);
	}

	_extern bool _sub_10933E00(ChatCommands::ShuffleTeamsCommand *const, std::string, std::string &);
	bool ShuffleTeamsCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x10933E00
	{
		mangled_x86(MANGLED_TODO, "?isValidArgument@ShuffleTeamsCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &returnInfo;
		todo("implement");
		bool __result = _sub_10933E00(this, s, returnInfo);
		return __result;
	}

	extern EndGameCommand* _sub_1092F360(ChatCommands::EndGameCommand *const);
	EndGameCommand::EndGameCommand() : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) // 0x1092F360
	{
		mangled_x86(MANGLED_TODO, "??0EndGameCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::EndGameCommand *const this;
		todo("implement");
		_sub_1092F360(this);
	}

	_extern void _sub_10930DD0(ChatCommands::EndGameCommand *const, std::string);
	void EndGameCommand::doOnVotePass(std::string name) // 0x10930DD0
	{
		mangled_x86(MANGLED_TODO, "?doOnVotePass@EndGameCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;
		todo("implement");
		_sub_10930DD0(this, name);
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

	_extern void _sub_109317E0(ChatCommands::EndGameCommand *const, std::string);
	void EndGameCommand::doOnVoteStart(std::string starterName) // 0x109317E0
	{
		mangled_x86(MANGLED_TODO, "?doOnVoteStart@EndGameCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10931AD4
		// static ...; // 0x10931ACC
		// ChatCommands::EndGameCommand *const this;
		// std::string starterName;
		// std::string previousValue;
		todo("implement");
		_sub_109317E0(this, starterName);
	}

	_extern bool _sub_109334D0(ChatCommands::EndGameCommand *const, std::string, std::string &);
	bool EndGameCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x109334D0
	{
		mangled_x86(MANGLED_TODO, "?isValidArgument@EndGameCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &returnInfo;
		// function call : bool (*const)()
		todo("implement");
		bool __result = _sub_109334D0(this, s, returnInfo);
		return __result;
	}

	extern EndRoundCommand* _sub_1092F450(ChatCommands::EndRoundCommand *const);
	EndRoundCommand::EndRoundCommand() : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) // 0x1092F450
	{
		mangled_x86(MANGLED_TODO, "??0EndRoundCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::EndRoundCommand *const this;
		todo("implement");
		_sub_1092F450(this);
	}

	_extern void _sub_10930F80(ChatCommands::EndRoundCommand *const, std::string);
	void EndRoundCommand::doOnVotePass(std::string name) // 0x10930F80
	{
		mangled_x86(MANGLED_TODO, "?doOnVotePass@EndRoundCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;
		todo("implement");
		_sub_10930F80(this, name);
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

	_extern void _sub_10931BC0(ChatCommands::EndRoundCommand *const, std::string);
	void EndRoundCommand::doOnVoteStart(std::string starterName) // 0x10931BC0
	{
		mangled_x86(MANGLED_TODO, "?doOnVoteStart@EndRoundCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10931EB4
		// static ...; // 0x10931EAC
		// ChatCommands::EndRoundCommand *const this;
		// std::string starterName;
		// std::string previousValue;
		todo("implement");
		_sub_10931BC0(this, starterName);
	}

	_extern bool _sub_109335D0(ChatCommands::EndRoundCommand *const, std::string, std::string &);
	bool EndRoundCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x109335D0
	{
		mangled_x86(MANGLED_TODO, "?isValidArgument@EndRoundCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &returnInfo;
		// function call : bool (*const)()
		todo("implement");
		bool __result = _sub_109335D0(this, s, returnInfo);
		return __result;
	}

	extern KickIndexCommand* _sub_1092F540(ChatCommands::KickIndexCommand *const);
	KickIndexCommand::KickIndexCommand() : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) // 0x1092F540
	{
		mangled_x86(MANGLED_TODO, "??0KickIndexCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::KickIndexCommand *const this;
		todo("implement");
		_sub_1092F540(this);
	}

	_extern void _sub_10931130(ChatCommands::KickIndexCommand *const, std::string);
	void KickIndexCommand::doOnVotePass(std::string name) // 0x10931130
	{
		mangled_x86(MANGLED_TODO, "?doOnVotePass@KickIndexCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;
		todo("implement");
		_sub_10931130(this, name);
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

	_extern void _sub_10931FA0(ChatCommands::KickIndexCommand *const, std::string);
	void KickIndexCommand::doOnVoteStart(std::string starterName) // 0x10931FA0
	{
		mangled_x86(MANGLED_TODO, "?doOnVoteStart@KickIndexCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10932320
		// static ...; // 0x10932318
		// ChatCommands::KickIndexCommand *const this;
		// std::string starterName;
		// std::string previousValue;
		todo("implement");
		_sub_10931FA0(this, starterName);
	}

	_extern bool _sub_109336D0(ChatCommands::KickIndexCommand *const, std::string, std::string &);
	bool KickIndexCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x109336D0
	{
		mangled_x86(MANGLED_TODO, "?isValidArgument@KickIndexCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// static ...; // 0x1093395C
	// $LN16:
		// ChatCommands::KickIndexCommand *const this;
		// std::string s;
		// std::string &returnInfo;
		// Blam::Network::PlayerSession *player;
		// __int32 indexToKick;
		// std::string kickPlayerName;
		// Blam::Network::Session *session;
		todo("implement");
		bool __result = _sub_109336D0(this, s, returnInfo);
		return __result;
	}

	extern KickPlayerCommand* _sub_1092F640(ChatCommands::KickPlayerCommand *const);
	KickPlayerCommand::KickPlayerCommand() : VotingChatCommand(todo_result<std::string>(), todo_result<std::string>()) // 0x1092F640
	{
		mangled_x86(MANGLED_TODO, "??0KickPlayerCommand@ChatCommands@@QAE@XZ");
		// ChatCommands::KickPlayerCommand *const this;
		todo("implement");
		_sub_1092F640(this);
	}

	_extern void _sub_109313B0(ChatCommands::KickPlayerCommand *const, std::string);
	void KickPlayerCommand::doOnVotePass(std::string name) // 0x109313B0
	{
		mangled_x86(MANGLED_TODO, "?doOnVotePass@KickPlayerCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string name;
		todo("implement");
		_sub_109313B0(this, name);
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

	_extern void _sub_10932420(ChatCommands::KickPlayerCommand *const, std::string);
	void KickPlayerCommand::doOnVoteStart(std::string starterName) // 0x10932420
	{
		mangled_x86(MANGLED_TODO, "?doOnVoteStart@KickPlayerCommand@ChatCommands@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x109327A0
		// static ...; // 0x10932798
		// ChatCommands::KickPlayerCommand *const this;
		// std::string starterName;
		// std::string previousValue;
		todo("implement");
		_sub_10932420(this, starterName);
	}

	_extern bool _sub_10933A30(ChatCommands::KickPlayerCommand *const, std::string, std::string &);
	bool KickPlayerCommand::isValidArgument(std::string s, std::string &returnInfo) // 0x10933A30
	{
		mangled_x86(MANGLED_TODO, "?isValidArgument@KickPlayerCommand@ChatCommands@@UAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &returnInfo;
		// __int32 playerToKickIdx;
		// Blam::Network::SessionMembership *membership;
		{
			// __int32 peerIdx;
			{
				// Blam::Network::PlayerSession *player;
				// __int32 playerIdx;
			}
		}
		todo("implement");
		bool __result = _sub_10933A30(this, s, returnInfo);
		return __result;
	}

	extern VotingChatCommand* _sub_1092F830(ChatCommands::VotingChatCommand *const, std::string, std::string);
	VotingChatCommand::VotingChatCommand(std::string n, std::string d) // 0x1092F830
	{
		mangled_x86(MANGLED_TODO, "??0VotingChatCommand@ChatCommands@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
		// std::string d;
		todo("implement");
		_sub_1092F830(this, n, d);
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

	_extern void _sub_10932D10(ChatCommands::VotingChatCommand *const);
	void VotingChatCommand::endVoting() // 0x10932D10
	{
		mangled_x86(MANGLED_TODO, "?endVoting@VotingChatCommand@ChatCommands@@QAEXXZ");
		// static ...; // 0x10932F5C
		// static ...; // 0x10932F50
		// static ...; // 0x10932F48
		// ChatCommands::VotingChatCommand *const this;
		// std::string previousValue;
		todo("implement");
		_sub_10932D10(this);
	}

	_extern void _sub_10933FC0(ChatCommands::VotingChatCommand *const, unsigned char, std::string);
	void VotingChatCommand::processMessage(unsigned char sender, std::string argument) // 0x10933FC0
	{
		mangled_x86(MANGLED_TODO, "?processMessage@VotingChatCommand@ChatCommands@@QAEXEV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
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
		{
			// char uidString[32];
			// __int32 numPlayers;
			// std::string previousValue;
		}
		// function call : bool ()
		// function call : bool (std::string, std::string &)
		// function call : void (std::string)
		todo("implement");
		_sub_10933FC0(this, sender, argument);
	}

	_extern void _sub_10934610(ChatCommands::VotingChatCommand *const, unsigned char, std::string);
	void VotingChatCommand::processVote(unsigned char sender, std::string message) // 0x10934610
	{
		mangled_x86(MANGLED_TODO, "?processVote@VotingChatCommand@ChatCommands@@QAEXEV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10934C54
		// static ...; // 0x10934C30
		// static ...; // 0x10934C28
		// ChatCommands::VotingChatCommand *const this;
		// unsigned char sender;
		// std::string message;
		{
			// unsigned long long uid;
			// Blam::Network::SessionMembership &membership;
			// std::string name;
			{
				// std::string previousValue;
				// unsigned __int32 votesRemaining;
			}
		}
		// function call : bool ()
		// function call : void (std::string)
		todo("implement");
		_sub_10934610(this, sender, message);
	}
}

extern std::string _sub_109331A0(ChatCommands::VotingChatCommand *const);
namespace ChatCommands
{
	std::string VotingChatCommand::getName() // 0x109331A0
	{
		mangled_x86(MANGLED_TODO, "?getName@VotingChatCommand@ChatCommands@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// ChatCommands::VotingChatCommand *const this;
		todo("implement");
		std::string __result = _sub_109331A0(this);
		return __result;
	}
}

extern std::string _sub_10933120(ChatCommands::VotingChatCommand *const);
namespace ChatCommands
{
	std::string VotingChatCommand::getDescription() // 0x10933120
	{
		mangled_x86(MANGLED_TODO, "?getDescription@VotingChatCommand@ChatCommands@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// ChatCommands::VotingChatCommand *const this;
		todo("implement");
		std::string __result = _sub_10933120(this);
		return __result;
	}
}

/* ---------- private code */
