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
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

// ChatCommands::ChatCommand is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

namespace ChatCommands
{
	typedef std::function<bool __cdecl(int,std::vector<std::string> const &,std::string &)> ChatCommandHandler;
}

/* ---------- prototypes */

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
	extern std::vector<ChatCommands::ChatCommand> chatCommands; // 0x1240D76C
	extern bool chatCommandsActive; // 0x1240D6F0
	extern std::map<unsigned __int64,__int64> voteTimes; // 0x1240D760
	extern ChatCommands::KickPlayerCommand kickPlayerCommand; // 0x1240D780
	extern ChatCommands::KickIndexCommand kickIndexCommand; // 0x1240D808
	extern ChatCommands::EndGameCommand endGameCommand; // 0x1240D8A0
	extern ChatCommands::EndRoundCommand endRoundCommand; // 0x1240D908
	extern ChatCommands::ShuffleTeamsCommand shuffleTeamsCommand; // 0x1240D6F8
	extern std::vector<ChatCommands::VotingChatCommand *> votingCommands; // 0x1240D890
}

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		extern std::string DefaultBanListPath; // 0x1240D970
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

namespace ChatCommands
{
	_extern void _sub_1093A9A0(Blam::Network::LifeCycleState);
	void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x1093A9A0
	{
		mangled_x86(MANGLED_TODO, "?LifeCycleStateChanged@ChatCommands@@YAXW4LifeCycleState@Network@Blam@@@Z");
		// Blam::Network::LifeCycleState newState;
		// Blam::Network::Session *session;
		{
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L0;
			// ChatCommands::VotingChatCommand **<begin>$L0;
			// ChatCommands::VotingChatCommand **<end>$L0;
			{
				// ChatCommands::VotingChatCommand *elem;
			}
		}
		// function call : void ()
		todo("implement");
		_sub_1093A9A0(newState);
	}

	_extern void _sub_1093A890();
	void Init() // 0x1093A890
	{
		mangled_x86(MANGLED_TODO, "?Init@ChatCommands@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_1093A890();
	}

	_extern bool _sub_1093CB80(unsigned long long);
	bool addToVoteTimes(unsigned long long sender) // 0x1093CB80
	{
		mangled_x86(MANGLED_TODO, "?addToVoteTimes@ChatCommands@@YA_N_K@Z");
		// static ...; // 0x1093CD6F
		// static ...; // 0x1093CD6C
		// static ...; // 0x1093CD54
		// static ...; // 0x1093CD4C
		// unsigned long long sender;
		// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned __int64 const ,__int64> > > > it;
		// long long curTime;
		todo("implement");
		bool __result = _sub_1093CB80(sender);
		return __result;
	}

	_extern void _sub_1093AC40();
	void Tick() // 0x1093AC40
	{
		mangled_x86(MANGLED_TODO, "?Tick@ChatCommands@@YAXXZ");
		// procedure flags: nofpo
		// Blam::Network::Session *session;
		{
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L0;
			// ChatCommands::VotingChatCommand **<begin>$L0;
			// ChatCommands::VotingChatCommand **<end>$L0;
			{
				// ChatCommands::VotingChatCommand *elem;
			}
		}
		todo("implement");
		_sub_1093AC40();
	}

	// mangled_x86(MANGLED_DEFAULT, "??0ChatCommand@ChatCommands@@QAE@$$QAU01@@Z"); no body to assert in
	_inline ChatCommand::ChatCommand(ChatCommands::ChatCommand &&__that) = default; // 0x10939590

	// mangled_x86(MANGLED_DEFAULT, "??0ChatCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline ChatCommand::ChatCommand() = default; // 0x10939660

	// mangled_x86(MANGLED_DEFAULT, "??1ChatCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline ChatCommand::~ChatCommand() = default; // 0x10939E40

	// mangled_x86(MANGLED_DEFAULT, "??1EndGameCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline EndGameCommand::~EndGameCommand() = default; // 0x10939EB0

	// mangled_x86(MANGLED_DEFAULT, "??1EndRoundCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline EndRoundCommand::~EndRoundCommand() = default; // 0x10939F00

	// mangled_x86(MANGLED_DEFAULT, "??1KickIndexCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline KickIndexCommand::~KickIndexCommand() = default; // 0x10939F50

	// mangled_x86(MANGLED_DEFAULT, "??1KickPlayerCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline KickPlayerCommand::~KickPlayerCommand() = default; // 0x10939FB0
}

extern std::vector<std::string> _sub_1093D450();
namespace ChatCommands
{
	std::vector<std::string> getHelpText() // 0x1093D450
	{
		mangled_x86(MANGLED_TODO, "?getHelpText@ChatCommands@@YA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// procedure flags: nofpo
		// static ...; // 0x1093D800
		// static ...; // 0x1093D7F4
		// static ...; // 0x1093D7EC
		// std::vector<std::string> helpText;
		{
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L0;
			// ChatCommands::VotingChatCommand **<begin>$L0;
			// ChatCommands::VotingChatCommand **<end>$L0;
			{
				// ChatCommands::VotingChatCommand *elem;
			}
		}
		{
			// ChatCommands::ChatCommand *<end>$L1;
			// ChatCommands::ChatCommand *<begin>$L1;
			// std::vector<ChatCommands::ChatCommand> &<range>$L1;
			{
				// ChatCommands::ChatCommand const &command;
			}
		}
		// function call : bool ()
		todo("implement");
		std::vector<std::string> __result = _sub_1093D450();
		return __result;
	}

	// mangled_x86(MANGLED_DEFAULT, "??1ShuffleTeamsCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline ShuffleTeamsCommand::~ShuffleTeamsCommand() = default; // 0x1093A010

	// mangled_x86(MANGLED_DEFAULT, "??1VotingChatCommand@ChatCommands@@QAE@XZ"); no body to assert in
	_inline VotingChatCommand::~VotingChatCommand() = default; // 0x1093A060

	_extern void _sub_1093AB00(std::string const &, std::string const &, ChatCommands::CommandFlags, std::function<bool __cdecl(int,std::vector<std::string> const &,std::string &)> &);
	void RegisterCommand(std::string const &name, std::string const &description, ChatCommands::CommandFlags flags, std::function<bool __cdecl(int,std::vector<std::string> const &,std::string &)> &&handler) // 0x1093AB00
	{
		mangled_x86(MANGLED_TODO, "?RegisterCommand@ChatCommands@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0W4CommandFlags@1@$$QAV?$function@$$A6A_NHABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z@3@@Z");
		// std::string const &name;
		// std::string const &description;
		// ChatCommands::CommandFlags flags;
		// std::function<bool __cdecl(int,std::vector<std::string> const &,std::string &)> &handler;
		// ChatCommands::ChatCommand command;
		todo("implement");
		_sub_1093AB00(name, description, flags, handler);
	}

	extern ChatCommand *_sub_1093A7E0(std::string const &);
	ChatCommands::ChatCommand *FindChatCommand(std::string const &name) // 0x1093A7E0
	{
		mangled_x86(MANGLED_TODO, "?FindChatCommand@ChatCommands@@YAPAUChatCommand@1@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &name;
		{
			// unsigned __int32 i;
		}
		todo("implement");
		ChatCommands::ChatCommand * __result = _sub_1093A7E0(name);
		return __result;
	}

	_extern bool _sub_1093D900(Server::Chat::ChatMessage const &, __int32);
	bool handleChatMessage(Server::Chat::ChatMessage const &message, __int32 peer) // 0x1093D900
	{
		mangled_x86(MANGLED_TODO, "?handleChatMessage@ChatCommands@@YA_NABUChatMessage@Chat@Server@@H@Z");
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
		{
			// unsigned __int32 i;
		}
		{
			// ChatCommands::ChatCommand *command;
			{
				// std::string returnValue;
			}
		}
		{
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L0;
			// ChatCommands::VotingChatCommand **<begin>$L0;
			// ChatCommands::VotingChatCommand **<end>$L0;
			{
				// ChatCommands::VotingChatCommand *elem;
			}
		}
		{
			// ChatCommands::VotingChatCommand **<end>$L1;
			// ChatCommands::VotingChatCommand **<begin>$L1;
			// std::vector<ChatCommands::VotingChatCommand *> &<range>$L1;
			{
				{
					// std::string name;
					{
						// std::vector<std::string> argsVect;
						{
							// __int32 i;
						}
					}
				}
			}
		}
		todo("implement");
		bool __result = _sub_1093D900(message, peer);
		return __result;
	}
}

/* ---------- private code */
