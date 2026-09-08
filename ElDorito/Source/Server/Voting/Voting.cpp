/* ---------- headers */

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
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/Network.hpp"
#include "Patches/Weapon.hpp"
#include "Server/Voting/AbstractVotingSystem.hpp"
#include "Server/Voting/VetoSystem.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingSystem.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <ios>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Server
{
	namespace Voting
	{
		class AbstractVotingSystem;
		class VetoSystem;
		class VotingSystem;
		struct MapAndType;
		struct VotingMessage;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
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

/* ---------- constants */

/* ---------- definitions */

namespace Server
{
	namespace Voting
	{
		typedef std::function<void __cdecl(Server::Voting::MapAndType)> VotePassedCallback;
	}
}

namespace Patches
{
	namespace Core
	{
		typedef std::function<void __cdecl(char const *)> MapLoadedCallback;
	}
}

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern void OnVotePassed(std::function<void __cdecl(Server::Voting::MapAndType)> &&callback);
		extern void NotifyVotePassed(Server::Voting::MapAndType const &winner);
		extern void MapLoadedCallback(char const *mapPath);
		extern void LifeCycleStateChanged(Blam::Network::LifeCycleState newState);
		extern void Init();
		extern bool ReloadVotingJson(bool loadFileFromDisc);
		extern bool ReloadVetoJson(bool loadFileFromDisc);
		extern void Tick();
		extern void PlayerJoinedVoteInProgress(__int32 playerIndex);
		extern void PlayerLeftVoting(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name);
		extern void StartNewVote();
		extern bool CancelVoteInProgress();
		extern void LogVote(Server::Voting::VotingMessage const &message, std::basic_string<char,std::char_traits<char>,std::allocator<char> > name);
	}
}

/* ---------- globals */

namespace Server
{
	namespace Voting
	{
		extern std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > VotingSystems; // 0x12468748
		extern Server::Voting::VotingSystem votingSystem; // 0x12468848
		extern Server::Voting::VetoSystem vetoSystem; // 0x12469AC0
		extern std::vector<std::function<void __cdecl(Server::Voting::MapAndType)>,std::allocator<std::function<void __cdecl(Server::Voting::MapAndType)> > > votePassedCallbacks; // 0x12468838
	}
}

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x12468668
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x12468758
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		_extern void _sub_10C43AB0(std::function<void __cdecl(Server::Voting::MapAndType)> &);
		void OnVotePassed(std::function<void __cdecl(Server::Voting::MapAndType)> &&callback) // 0x10C43AB0
		{
			mangled_x86(MANGLED_TODO, "?OnVotePassed@Voting@Server@@YAX$$QAV?$function@$$A6AXUMapAndType@Voting@Server@@@Z@std@@@Z");
			// std::function<void __cdecl(Server::Voting::MapAndType)> &callback;
			todo("implement");
			_sub_10C43AB0(callback);
		}

		_extern void _sub_10C43A00(Server::Voting::MapAndType const &);
		void NotifyVotePassed(Server::Voting::MapAndType const &winner) // 0x10C43A00
		{
			mangled_x86(MANGLED_TODO, "?NotifyVotePassed@Voting@Server@@YAXABUMapAndType@12@@Z");
			// Server::Voting::MapAndType const &winner;
			{
				// std::vector<std::function<void __cdecl(Server::Voting::MapAndType)>,std::allocator<std::function<void __cdecl(Server::Voting::MapAndType)> > > &<range>$L0;
				// std::function<void __cdecl(Server::Voting::MapAndType)> *<begin>$L0;
				// std::function<void __cdecl(Server::Voting::MapAndType)> *<end>$L0;
				{
					// std::function<void __cdecl(Server::Voting::MapAndType)> &callback;
				}
			}
			todo("implement");
			_sub_10C43A00(winner);
		}

		_extern void _sub_10C43990(char const *);
		void MapLoadedCallback(char const *mapPath) // 0x10C43990
		{
			mangled_x86(MANGLED_TODO, "?MapLoadedCallback@Voting@Server@@YAXPBD@Z");
			// char const *mapPath;
			todo("implement");
			_sub_10C43990(mapPath);
		}

		_extern void _sub_10C435D0(Blam::Network::LifeCycleState);
		void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x10C435D0
		{
			mangled_x86(MANGLED_TODO, "?LifeCycleStateChanged@Voting@Server@@YAXW4LifeCycleState@Network@Blam@@@Z");
			// Blam::Network::LifeCycleState newState;
			{
				// std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > &<range>$L0;
				// Server::Voting::AbstractVotingSystem **<begin>$L0;
				// Server::Voting::AbstractVotingSystem **<end>$L0;
				{
					// Server::Voting::AbstractVotingSystem *elem;
				}
			}
			{
				// Server::Voting::AbstractVotingSystem **<end>$L1;
				// Server::Voting::AbstractVotingSystem **<begin>$L1;
				// std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > &<range>$L1;
				{
				}
			}
			// function call : bool ()
			// function call : void ()
			// function call : bool ()
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_10C435D0(newState);
		}

		_extern void _sub_10C43480();
		void Init() // 0x10C43480
		{
			mangled_x86(MANGLED_TODO, "?Init@Voting@Server@@YAXXZ");
			// procedure flags: nofpo
			{
				// std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > &<range>$L0;
				// Server::Voting::AbstractVotingSystem **<begin>$L0;
				// Server::Voting::AbstractVotingSystem **<end>$L0;
				{
					// Server::Voting::AbstractVotingSystem *elem;
				}
			}
			// function call : void ()
			todo("implement");
			_sub_10C43480();
		}

		_inline VotingSystem::~VotingSystem() // 0x10C43260
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1VotingSystem@Voting@Server@@UAE@XZ");
			// Server::Voting::VotingSystem *const this;

			compiler_generated();
		}

		_extern bool _sub_10C43EA0(bool);
		bool ReloadVotingJson(bool loadFileFromDisc) // 0x10C43EA0
		{
			mangled_x86(MANGLED_TODO, "?ReloadVotingJson@Voting@Server@@YA_N_N@Z");
			// bool loadFileFromDisc;
			todo("implement");
			bool __result = _sub_10C43EA0(loadFileFromDisc);
			return __result;
		}

		_extern bool _sub_10C43E10(bool);
		bool ReloadVetoJson(bool loadFileFromDisc) // 0x10C43E10
		{
			mangled_x86(MANGLED_TODO, "?ReloadVetoJson@Voting@Server@@YA_N_N@Z");
			// bool loadFileFromDisc;
			todo("implement");
			bool __result = _sub_10C43E10(loadFileFromDisc);
			return __result;
		}

		_extern void _sub_10C44070();
		void Tick() // 0x10C44070
		{
			mangled_x86(MANGLED_TODO, "?Tick@Voting@Server@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			{
				// std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > &<range>$L0;
				// Server::Voting::AbstractVotingSystem **<begin>$L0;
				// Server::Voting::AbstractVotingSystem **<end>$L0;
				{
					// Server::Voting::AbstractVotingSystem *elem;
				}
			}
			// function call : bool ()
			// function call : void ()
			todo("implement");
			_sub_10C44070();
		}

		_extern void _sub_10C43B10(__int32);
		void PlayerJoinedVoteInProgress(__int32 playerIndex) // 0x10C43B10
		{
			mangled_x86(MANGLED_TODO, "?PlayerJoinedVoteInProgress@Voting@Server@@YAXH@Z");
			// __int32 playerIndex;
			// Blam::Network::Session *session;
			// __int32 peerIdx;
			{
				// std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > &<range>$L0;
				// Server::Voting::AbstractVotingSystem **<begin>$L0;
				// Server::Voting::AbstractVotingSystem **<end>$L0;
				{
					// Server::Voting::AbstractVotingSystem *elem;
				}
			}
			// function call : bool ()
			// function call : bool ()
			// function call : void ()
			todo("implement");
			_sub_10C43B10(playerIndex);
		}

		_extern void _sub_10C43C90(std::string);
		void PlayerLeftVoting(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name) // 0x10C43C90
		{
			mangled_x86(MANGLED_TODO, "?PlayerLeftVoting@Voting@Server@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C43DB4
			// static ...; // 0x10C43DA8
			// static ...; // 0x10C43DA0
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
			// Blam::Network::Session *session;
			// Server::Voting::VotingMessage message;
			todo("implement");
			_sub_10C43C90(name);
		}

		_extern void _sub_10C43F30();
		void StartNewVote() // 0x10C43F30
		{
			mangled_x86(MANGLED_TODO, "?StartNewVote@Voting@Server@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			{
				// std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > &<range>$L0;
				// Server::Voting::AbstractVotingSystem **<begin>$L0;
				// Server::Voting::AbstractVotingSystem **<end>$L0;
				{
					// Server::Voting::AbstractVotingSystem *elem;
				}
			}
			// function call : bool ()
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_10C43F30();
		}

		_extern bool _sub_10C43380();
		bool CancelVoteInProgress() // 0x10C43380
		{
			mangled_x86(MANGLED_TODO, "?CancelVoteInProgress@Voting@Server@@YA_NXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			{
				// std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > &<range>$L0;
				// Server::Voting::AbstractVotingSystem **<begin>$L0;
				// Server::Voting::AbstractVotingSystem **<end>$L0;
				{
					// Server::Voting::AbstractVotingSystem *elem;
				}
			}
			// function call : void ()
			// function call : void ()
			todo("implement");
			bool __result = _sub_10C43380();
			return __result;
		}

		_extern void _sub_10C43800(Server::Voting::VotingMessage const &, std::string);
		void LogVote(Server::Voting::VotingMessage const &message, std::basic_string<char,std::char_traits<char>,std::allocator<char> > name) // 0x10C43800
		{
			mangled_x86(MANGLED_TODO, "?LogVote@Voting@Server@@YAXABUVotingMessage@12@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
			// Blam::Network::Session *session;
			{
				// std::vector<Server::Voting::AbstractVotingSystem *,std::allocator<Server::Voting::AbstractVotingSystem *> > &<range>$L0;
				// Server::Voting::AbstractVotingSystem **<begin>$L0;
				// Server::Voting::AbstractVotingSystem **<end>$L0;
				{
					// Server::Voting::AbstractVotingSystem *elem;
				}
			}
			// function call : bool ()
			// function call : void (Server::Voting::VotingMessage const &, std::string)
			todo("implement");
			_sub_10C43800(message, name);
		}
	}
}

/* ---------- private code */
