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
#include "Modules/ModuleServer.hpp"
#include "Patches/Core.hpp"
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
#include "Modules/ModuleVoting.hpp"  // hades: added for 0x10C43EA0

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
		extern void PlayerLeftVoting(std::string name);
		extern void StartNewVote();
		extern bool CancelVoteInProgress();
		extern void LogVote(Server::Voting::VotingMessage const &message, std::string name);
	}
}

/* ---------- globals */

namespace Server
{
	namespace Voting
	{
		extern std::vector<Server::Voting::AbstractVotingSystem *> VotingSystems; // 0x12468748
		Server::Voting::VotingSystem votingSystem; // 0x12468848  // hades: defined, so its dynamic initializer emits the constructor
		extern Server::Voting::VetoSystem vetoSystem; // 0x12469AC0
		extern std::vector<std::function<void __cdecl(Server::Voting::MapAndType)> > votePassedCallbacks; // 0x12468838
	}
}

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x12468668  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x12468758  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		void OnVotePassed(std::function<void __cdecl(Server::Voting::MapAndType)> &&callback) // 0x10C43AB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnVotePassed@Voting@Server@@YAX$$QAV?$function@$$A6AXUMapAndType@Voting@Server@@@Z@std@@@Z");

			votePassedCallbacks.push_back(std::move(callback));
		}

		void NotifyVotePassed(Server::Voting::MapAndType const &winner) // 0x10C43A00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyVotePassed@Voting@Server@@YAXABUMapAndType@12@@Z");

			for (auto &callback : votePassedCallbacks)
			{
				callback(winner);
			}
		}

		void MapLoadedCallback(char const *mapPath) // 0x10C43990
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MapLoadedCallback@Voting@Server@@YAXPBD@Z");

			if(Blam::Network::GetActiveSession()->Parameters.GetSessionMode() == 1 && Blam::Network::GetNetworkMode() == 3){
				StartNewVote();
			}
		}

		void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x10C435D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LifeCycleStateChanged@Voting@Server@@YAXW4LifeCycleState@Network@Blam@@@Z");

			switch (newState)
			{
			case Blam::Network::eLifeCycleStateStartGame:
				if (votingSystem.AllowShuffle && Modules::ModuleServer::Instance().VarServerTeamShuffleEnabled->ValueInt == 1)
					Modules::CommandMap::Instance().ExecuteCommand("Server.ShuffleTeams");
				for (auto elem : VotingSystems)
				{
					if (elem->isEnabled())
						elem->Reset();
				}
				break;
			case Blam::Network::eLifeCycleStateNone:
				for (auto elem : VotingSystems)
				{
					if (elem->isEnabled())
					{
						elem->Reset();
						elem->onExit();
					}
				}
				break;
			}
		}

		void Init() // 0x10C43480
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@Voting@Server@@YAXXZ");

			InitializePackets();
			Patches::Core::OnMapLoaded(MapLoadedCallback);
			Patches::Network::OnLifeCycleStateChanged(LifeCycleStateChanged);
			VotingSystems.push_back(&votingSystem);
			VotingSystems.push_back(&vetoSystem);
			for (auto elem : VotingSystems)
			{
				elem->Init();
				elem->votePassedCallback = NotifyVotePassed;
			}
		}

		bool ReloadVotingJson(bool loadFileFromDisc) // 0x10C43EA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReloadVotingJson@Voting@Server@@YA_N_N@Z");

			return votingSystem.ReloadVotingJson(Utils::Singleton<Modules::ModuleVoting>::Instance().VarVotingJsonPath->ValueString, loadFileFromDisc);
		}

		bool ReloadVetoJson(bool loadFileFromDisc) // 0x10C43E10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReloadVetoJson@Voting@Server@@YA_N_N@Z");

			return vetoSystem.ReloadVotingJson(Utils::Singleton<Modules::ModuleVoting>::Instance().VarVotingJsonPath->ValueString, loadFileFromDisc);
		}

		void Tick() // 0x10C44070
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Voting@Server@@YAXXZ");

			auto* session = Blam::Network::GetActiveSession();
			if (!(session && session->IsEstablished() && session->IsHost()))
				return;

			for (auto elem : VotingSystems)
			{
				if (elem->isEnabled()) {
					elem->Tick();
				}
			}
		}

		void PlayerJoinedVoteInProgress(__int32 playerIndex) // 0x10C43B10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerJoinedVoteInProgress@Voting@Server@@YAXH@Z");

			//if we aren't in a vote or voting isn't enabled, then do nothing
			auto* session = Blam::Network::GetActiveSession();
			if (!(session && session->IsEstablished() && session->IsHost() && Blam::Network::GetLobbyType() == 2))
				return;

			auto peerIdx = session->MembershipInfo.GetPlayerPeer(playerIndex);
			if (peerIdx != session->MembershipInfo.LocalPeerIndex)
			{

				for (auto elem : VotingSystems)
				{
					if (elem->isEnabled()) {
						elem->GenerateVotingOptionsMessage(peerIdx);
						if(elem->ShouldSendVotingOptions())
							elem->SendVoteCountsToEveryone();
					}
				}
			}
		}

		void PlayerLeftVoting(std::string name) // 0x10C43C90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerLeftVoting@Voting@Server@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost() || Blam::Network::GetLobbyType() != 2)
				return;
			Server::Voting::VotingMessage message((Server::Voting::VotingMessageType)2);
			message.Vote = 0;
			LogVote(message, name);
		}

		void StartNewVote() // 0x10C43F30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StartNewVote@Voting@Server@@YAXXZ");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost() || Blam::Network::GetLobbyType() != 2)
				return;
			for (auto elem : VotingSystems)
			{
				if (elem->isEnabled())
				{
					elem->CheckAndLoadJson();
					elem->Reset();
					elem->NewVote();
				}
			}
		}

		bool CancelVoteInProgress() // 0x10C43380
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CancelVoteInProgress@Voting@Server@@YA_NXZ");

			auto* session = Blam::Network::GetActiveSession();
			if (!(session && session->IsEstablished() && session->IsHost()))
				return false;

			for (auto elem : VotingSystems)
			{
				elem->Reset();
				elem->EndVote();
			}

			return true;
		}

		void LogVote(Server::Voting::VotingMessage const &message, std::string name) // 0x10C43800
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LogVote@Voting@Server@@YAXABUVotingMessage@12@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return;
			for (Server::Voting::AbstractVotingSystem *elem : VotingSystems)
			{
				if (elem->isEnabled())
					elem->LogVote(message, name);
			}
		}
	}
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Server { namespace Voting { std::vector<Server::Voting::AbstractVotingSystem *> VotingSystems; } }
namespace Server { namespace Voting { Server::Voting::VetoSystem vetoSystem; } }
namespace Server { namespace Voting { std::vector<std::function<void __cdecl(Server::Voting::MapAndType)> > votePassedCallbacks; } }
