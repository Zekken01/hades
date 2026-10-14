/* ---------- headers */

#include "ChatCommands/ChatCommandMap.hpp"
#include "hades/hades.h"

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
#include "ChatCommands/ChatVoting.hpp"
#include "CommandLineArgs.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/Network.hpp"
#include "Server/BanList.hpp"
#include "Server/ServerChat.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
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
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
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

class CommandLineArgs;
struct begin;
struct end;
namespace Blam
{
	namespace Network
	{
		struct Session;
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
	struct ChatCommand;
}
namespace Server
{
	namespace Chat
	{
		struct ChatMessage;
	}
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

namespace Debug {}
using namespace ::Debug;
namespace Patches {}
using namespace ::Patches;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Blam {}
using namespace ::Blam; namespace Utils { namespace String { template<class T, class InputIt> std::string Join(InputIt first, InputIt last, const char *delim = " ") { std::ostringstream stream; std::copy(first, last, std::ostream_iterator<T>(stream, delim)); auto str = stream.str(); str.erase(str.length() - 1); return str; } template<class T> std::string Join(const std::vector<T> &vec, const char *delim = " ") { return Join<T>(vec.begin(), vec.end(), delim); } } }

/* ---------- constants */

/* ---------- definitions */

// ChatCommands::ChatCommand is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

namespace ChatCommands
{
	typedef std::function<bool __cdecl(int,std::vector<std::string> const &,std::string &)> ChatCommandHandler;
}

/* ---------- prototypes */

namespace ChatCommands { extern void RegisterCommands(); }  // hades: added for 0x1093A890

namespace ChatCommands
{
	extern void LifeCycleStateChanged(Blam::Network::LifeCycleState newState);
	extern void Init();
	extern bool addToVoteTimes(unsigned long long sender);
	extern void Tick();
	extern std::vector<std::string> getHelpText();
	extern void RegisterCommand(std::string const &name, std::string const &description, ChatCommands::CommandFlags flags, std::function<bool __cdecl(int,std::vector<std::string> const &,std::string &)> &&handler);
	extern ChatCommands::ChatCommand *FindChatCommand(std::string const &name);
	extern bool handleChatMessage(Server::Chat::ChatMessage const &message, __int32 peer);
}

/* ---------- globals */

namespace ChatCommands
{
	std::vector<ChatCommands::ChatCommand> chatCommands; // 0x1240D76C
	extern bool chatCommandsActive; // 0x1240D6F0
	extern std::map<unsigned __int64,__int64> voteTimes; // 0x1240D760
	ChatCommands::KickPlayerCommand kickPlayerCommand; // 0x1240D780
	ChatCommands::KickIndexCommand kickIndexCommand; // 0x1240D808
	ChatCommands::EndGameCommand endGameCommand; // 0x1240D8A0
	ChatCommands::EndRoundCommand endRoundCommand; // 0x1240D908
	ChatCommands::ShuffleTeamsCommand shuffleTeamsCommand; // 0x1240D6F8
	extern std::vector<ChatCommands::VotingChatCommand *> votingCommands; // 0x1240D890
}

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		// extern std::string DefaultBanListPath; // 0x1240D970  // hades: defined (with its initialiser) elsewhere now
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

namespace ChatCommands
{
	void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x1093A9A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LifeCycleStateChanged@ChatCommands@@YAXW4LifeCycleState@Network@Blam@@@Z");
		// Blam::Network::LifeCycleState newState;
		// Blam::Network::Session *session;
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L0;
			// ChatCommands::VotingChatCommand **<begin>$L0;
			// ChatCommands::VotingChatCommand **<end>$L0;
				// ChatCommands::VotingChatCommand *elem;
		// function call : void ()

		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (!session || !session->IsEstablished() || !session->IsHost())
			return;
		switch (newState)
		{
		case Blam::Network::eLifeCycleStateStartGame:
			chatCommandsActive = true;
			break;
		case Blam::Network::eLifeCycleStateEndGameWriteStats:
			Utils::Singleton<Server::TempBanList>::Instance().decrementDuration();
			voteTimes.clear();
			chatCommandsActive = false;
			for (auto elem : votingCommands)
			{
				if (elem->isCurrentlyVoting())
				{
					elem->doOnVoteFail();
					elem->endVoting();
				}
			}
			break;
		}
	}

	void Init() // 0x1093A890
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Init@ChatCommands@@YAXXZ");
		// procedure flags: nofpo

			Patches::Network::OnLifeCycleStateChanged(LifeCycleStateChanged);
			votingCommands.push_back(&kickPlayerCommand);
			votingCommands.push_back(&kickIndexCommand);
			votingCommands.push_back(&endGameCommand);
			votingCommands.push_back(&endRoundCommand);
			votingCommands.push_back(&shuffleTeamsCommand);
			RegisterCommands();
	}

	bool addToVoteTimes(unsigned long long sender) // 0x1093CB80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?addToVoteTimes@ChatCommands@@YA_N_K@Z");
		// static ...; // 0x1093CD6F
		// static ...; // 0x1093CD6C
		// static ...; // 0x1093CD54
		// static ...; // 0x1093CD4C
		// unsigned long long sender;
		// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned __int64 const ,__int64> > > > it;
		// long long curTime;

		time_t curTime;
		time(&curTime);
		//check if the person is spamming voting
		std::map<uint64_t, time_t>::iterator it = voteTimes.find(sender);
		if (it != voteTimes.end())
		{
			//Now we know that the user has started a vote recently. Check to see if it's under 90 seconds ago.
			if (curTime - it->second < 90)
				return false;
			it->second = curTime;
		}
		else
			voteTimes.insert(std::make_pair(sender, curTime));
		return true;
	}

	void Tick() // 0x1093AC40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ChatCommands@@YAXXZ");
		// procedure flags: nofpo
		// Blam::Network::Session *session;
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L0;
			// ChatCommands::VotingChatCommand **<begin>$L0;
			// ChatCommands::VotingChatCommand **<end>$L0;
				// ChatCommands::VotingChatCommand *elem;

		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (!session || !session->IsEstablished() || !session->IsHost())
			return;

		if (chatCommandsActive)
		{
			for (auto command : votingCommands)
				command->tick();
		}
	}

	// mangled_x86(MANGLED_DEFAULT, "??0ChatCommand@ChatCommands@@QAE@$$QAU01@@Z"); no body to assert in
	_inline ChatCommand::ChatCommand(ChatCommands::ChatCommand &&__that) = default; // 0x10939590

	// mangled_x86(MANGLED_DEFAULT, "??0ChatCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline ChatCommand::ChatCommand() = default; // 0x10939660





}


namespace ChatCommands
{
	std::vector<std::string> getHelpText() // 0x1093D450
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?getHelpText@ChatCommands@@YA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// procedure flags: nofpo
		// static ...; // 0x1093D800
		// static ...; // 0x1093D7F4
		// static ...; // 0x1093D7EC
		// std::vector<std::string> helpText;
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L0;
			// ChatCommands::VotingChatCommand **<begin>$L0;
			// ChatCommands::VotingChatCommand **<end>$L0;
				// ChatCommands::VotingChatCommand *elem;
			// ChatCommands::ChatCommand *<end>$L1;
			// ChatCommands::ChatCommand *<begin>$L1;
			// std::vector<ChatCommands::ChatCommand> &<range>$L1;
				// ChatCommands::ChatCommand const &command;
		// function call : bool ()

		std::vector<std::string> helpText;
		for (auto elem : votingCommands)
			if (elem->isEnabled())
				helpText.push_back("!" + elem->getName() + " - " + elem->getDescription());
		for (auto const &command : chatCommands)
		{
			if (*(__int32 const *)command.flags & 1)
				continue;
			helpText.push_back("!" + command.name + " - " + command.description);
		}
		return helpText;
	}



	void RegisterCommand(std::string const &name, std::string const &description, ChatCommands::CommandFlags flags, std::function<bool __cdecl(int,std::vector<std::string> const &,std::string &)> &&handler) // 0x1093AB00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterCommand@ChatCommands@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0W4CommandFlags@1@$$QAV?$function@$$A6A_NHABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z@3@@Z");
		// std::string const &name;
		// std::string const &description;
		// ChatCommands::CommandFlags flags;
		// std::function<bool __cdecl(int,std::vector<std::string> const &,std::string &)> &handler;
		// ChatCommands::ChatCommand command;

		ChatCommands::ChatCommand command;
		*(ChatCommands::CommandFlags *)command.flags = flags;
		command.name = name;
		command.description = description;
		command.handle = std::move(handler);
		chatCommands.push_back(std::move(command));
	}

	ChatCommands::ChatCommand *FindChatCommand(std::string const &name) // 0x1093A7E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FindChatCommand@ChatCommands@@YAPAUChatCommand@1@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &name;
			// unsigned __int32 i;

		for (unsigned __int32 i = 0; i < chatCommands.size(); i++)
		{
			if (chatCommands[i].name == name)
				return &chatCommands[i];
		}
		return nullptr;
	}

	bool handleChatMessage(Server::Chat::ChatMessage const &message, __int32 peer) // 0x1093D900
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?handleChatMessage@ChatCommands@@YA_NABUChatMessage@Chat@Server@@H@Z");
		// static ...; // 0x1093E063
		// static ...; // 0x1093E05F
		// static ...; // 0x1093E05A
		// static ...; // 0x1093E04E
		// static ...; // 0x1093E049
		// static ...; // 0x1093E040
		// static ...; // 0x1093DFEC
		// static ...; // 0x1093DFE4
		// Server::Chat::ChatMessage const &message;
		// __int32 peer;
		// __int32 numArgs;
		// std::vector<std::string> args;
		// CommandLineArgs cmdArgs;
		// std::string line;
		// std::string cmd;
			// unsigned __int32 i;
			// ChatCommands::ChatCommand *command;
				// std::string returnValue;
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L0;
			// ChatCommands::VotingChatCommand **<begin>$L0;
			// ChatCommands::VotingChatCommand **<end>$L0;
				// ChatCommands::VotingChatCommand *elem;
			// ChatCommands::VotingChatCommand **<end>$L1;
			// ChatCommands::VotingChatCommand **<begin>$L1;
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L1;
					// std::string name;
						// std::vector<std::string> argsVect;
							// __int32 i;

		std::string line = Utils::String::Trim(std::string(message.Body), true);
		if (line.empty())
			return true;
		if (line[0] != '!')
			return false;
		line.erase(0, 1);
		CommandLineArgs cmdArgs(line);
		__int32 numArgs = cmdArgs.GetArgCount();
		if (numArgs < 1)
			return false;
		std::string cmd = Utils::String::ToLower(cmdArgs[0]);
		std::vector<std::string> args;
		if (numArgs > 1)
		{
			args.resize(numArgs - 1);
			for (unsigned __int32 i = 0; i < args.size(); i++)
				args[i] = cmdArgs[i + 1];
		}
		ChatCommand *command = FindChatCommand(cmd);
		if (command)
		{
			std::string returnValue;
			command->handle(peer, args, returnValue);
			if (!returnValue.empty())
				Server::Chat::SendServerMessage(returnValue, peer);
			return true;
		}
		for (auto elem : votingCommands)
		{
			if (elem->isCurrentlyVoting())
			{
				elem->processVote(peer, line);
				return true;
			}
		}
		for (auto elem : votingCommands)
		{
			std::string name = elem->getName();
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			if (cmd == name)
			{
				if (!chatCommandsActive)
				{
					Server::Chat::SendServerMessage("This command is not currently active.", peer);
					return true;
				}
				std::vector<std::string> argsVect;
				for (__int32 i = 1; i < numArgs; i++)
					argsVect.push_back(cmdArgs[i]);
				if (argsVect.size() > 0)
					elem->processMessage(peer, Utils::String::Join(argsVect));
				else
					elem->processMessage(peer, "");
			}
		}
		return true;
	}
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace ChatCommands { bool chatCommandsActive; }
namespace ChatCommands { std::map<unsigned __int64,__int64> voteTimes; }
namespace ChatCommands { std::vector<ChatCommands::VotingChatCommand *> votingCommands; }
