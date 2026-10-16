/* ---------- headers */

#include "Server/Voting/VetoSystem.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
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
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Server/Voting/AbstractVotingSystem.hpp"
#include "Server/Voting/VotingJson.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingUtil.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x1073D4E0

#include "Utils/Logger.hpp"  // hades: added for 0x1073D970  // hades: added for 0x1073D970
#include <format>  // hades: added for 0x1073D970  // hades: added for 0x1073D970
#include "Server/Voting/HaloTypeInheritance.hpp"  // hades: added for 0x1073D970  // hades: added for 0x1073D970

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
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
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
		struct AllowedPlayerCount;
		struct HaloMap;
		struct HaloType;
		struct MapAndType;
		struct PlaylistItem;
		struct SMapListItem;
		struct VotingJson;
		struct VotingMessage;
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
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

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

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const levels_enumeration_in_progress = reinterpret_cast<bool (*)()>(0x54B3A0);
}

extern float real_random_range(float minimum, float maximum);  // hades: added for 0x1073CF30

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x11388A10  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x11388AF0  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		VetoSystem::VetoSystem() : AbstractVotingSystem(), startime(0), willSetMap(false), numberOfVetosUsed(0), currentNumberOfVotes(0), shouldRunPreviousCommands(false) /* hades-mem-init:  */ // 0x1073A8D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0VetoSystem@Voting@Server@@QAE@XZ");
		}

		// mangled_x86(MANGLED_DEFAULT, "??0VotingJson@Voting@Server@@QAE@XZ"); no body to assert in

		void VetoSystem::Init() // 0x1073D950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@VetoSystem@Voting@Server@@UAEXXZ");
		}

		void VetoSystem::SendVoteCountsToEveryone() // 0x1073E4C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendVoteCountsToEveryone@VetoSystem@Voting@Server@@UAEXXZ");

			countVotes();

			VotingMessage newmessage(VoteTally);

			newmessage.votes[0] = currentNumberOfVotes;
			newmessage.votes[1] = currentNumberOfVotes;
			newmessage.votesNeededToPass = getVoteNeededToPass();

			BroadcastVotingMessage(newmessage);
		}

		// mangled_x86(MANGLED_DEFAULT, "??1PlaylistItem@Voting@Server@@QAE@XZ"); no body to assert in
		_inline PlaylistItem::~PlaylistItem() = default; // 0x1073B780

		// mangled_x86(MANGLED_DEFAULT, "??1VotingJson@Voting@Server@@QAE@XZ"); no body to assert in
		_inline VotingJson::~VotingJson() = default; // 0x1073B890

		Server::Voting::MapAndType VetoSystem::GenerateVotingOption() // 0x1073CF30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateVotingOption@VetoSystem@Voting@Server@@EAE?AUMapAndType@23@XZ");

			MapAndType m;
			if (Modules::ModuleVoting::Instance().VarVetoSystemSelectionType->ValueInt == 0)
			{
				__int32 optionIndex = rand() % currentPlaylist.size();
				float sum_of_weights = 0.0f;
				for (unsigned __int32 i = 0; i < currentPlaylist.size(); i++)
					sum_of_weights += currentPlaylist[i].haloMap.randomChance;
				float p = real_random_range(0.0f, sum_of_weights);
				for (unsigned __int32 i = 0; i < currentPlaylist.size(); i++)
				{
					if (currentPlaylist[i].haloMap.randomChance > p)
					{
						optionIndex = i;
						break;
					}
					p -= currentPlaylist[i].haloMap.randomChance;
				}
				m = currentPlaylist[optionIndex];
				currentPlaylist.erase(currentPlaylist.begin() + optionIndex);
			}
			else
			{
				m = currentPlaylist.front();
				currentPlaylist.erase(currentPlaylist.begin());
			}
			if (currentPlaylist.size() == 0)
				currentPlaylist = entirePlaylist;
			__int32 playerCount = Blam::Network::GetNumPlayers();
			if (m.haloMap.allowedPlayerCount.minimumPlayersAllowed <= playerCount && m.haloMap.allowedPlayerCount.maximumPlayersAllowed >= playerCount && m.haloType.allowedPlayerCount.minimumPlayersAllowed <= playerCount && m.haloType.allowedPlayerCount.maximumPlayersAllowed >= playerCount)
				return m;
			else
				return VetoSystem::GenerateVotingOption();
		}

		// mangled_x86(MANGLED_DEFAULT, "??4HaloMap@Voting@Server@@QAEAAU012@$$QAU012@@Z"); no body to assert in
		_inline Server::Voting::HaloMap &HaloMap::operator=(Server::Voting::HaloMap &&__that) noexcept = default; // 0x1073BDA0

		// mangled_x86(MANGLED_DEFAULT, "??4HaloMap@Voting@Server@@QAEAAU012@ABU012@@Z"); no body to assert in
		_inline Server::Voting::HaloMap &HaloMap::operator=(Server::Voting::HaloMap const &__that) = default; // 0x1073BE80

		// mangled_x86(MANGLED_DEFAULT, "??4HaloType@Voting@Server@@QAEAAU012@$$QAU012@@Z"); no body to assert in
		_inline Server::Voting::HaloType &HaloType::operator=(Server::Voting::HaloType &&__that) noexcept = default; // 0x1073BF60

		// mangled_x86(MANGLED_DEFAULT, "??4HaloType@Voting@Server@@QAEAAU012@ABU012@@Z"); no body to assert in
		_inline Server::Voting::HaloType &HaloType::operator=(Server::Voting::HaloType const &__that) = default; // 0x1073C0E0

		// mangled_x86(MANGLED_DEFAULT, "??4MapAndType@Voting@Server@@QAEAAU012@$$QAU012@@Z"); no body to assert in
		_inline Server::Voting::MapAndType &MapAndType::operator=(Server::Voting::MapAndType &&__that) noexcept = default; // 0x1073C260

		// mangled_x86(MANGLED_DEFAULT, "??4MapAndType@Voting@Server@@QAEAAU012@ABU012@@Z"); no body to assert in
		_inline Server::Voting::MapAndType &MapAndType::operator=(Server::Voting::MapAndType const &__that) = default; // 0x1073C350

		Server::Voting::VotingMessage VetoSystem::GenerateVotingOptionsMessage(bool updateTime) // 0x1073D4E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateVotingOptionsMessage@VetoSystem@Voting@Server@@UAE?AUVotingMessage@23@_N@Z");

			VotingMessage newmessage(VotingMessageType::VetoOption);
			strncpy_s(newmessage.votingOptions[0].scnrName, currentVetoOption.haloMap.scnrName.c_str(), _TRUNCATE);
			strncpy_s(newmessage.votingOptions[0].mapName, currentVetoOption.haloMap.mapDisplayName.c_str(), _TRUNCATE);
			strncpy_s(newmessage.votingOptions[0].typeName, currentVetoOption.haloType.typeDisplayName.c_str(), _TRUNCATE);
			strncpy_s(newmessage.votingOptions[0].modName, currentVetoOption.haloType.modDisplayName.c_str(), _TRUNCATE);
			std::string modHash = c_mod_system::get_mod_hash_by_identifier(currentVetoOption.haloType.modPack.c_str());
			strncpy_s(newmessage.votingOptions[0].modHash, modHash.c_str(), _TRUNCATE);
			strncpy_s(newmessage.votingOptions[0].imageUri, currentVetoOption.haloMap.imageUri.c_str(), _TRUNCATE);
			newmessage.votingOptions[0].canVeto = currentVetoOption.canveto;
			time_t curTime;
			time(&curTime);
			if (currentVetoOption.canveto)
			{
				if (updateTime && voteStartedTime > 0)
					newmessage.voteTime = Modules::ModuleVoting::Instance().VarServerMapVotingTime->ValueInt + 2 - (int)difftime(curTime, voteStartedTime);
				else
					newmessage.voteTime = Modules::ModuleVoting::Instance().VarServerMapVotingTime->ValueInt + 2;
				newmessage.votesNeededToPass = getVoteNeededToPass();
			}
			else
			{
				if (updateTime && startime > 0)
					newmessage.voteTime = Modules::ModuleVoting::Instance().VarVetoWinningOptionShownTime->ValueInt + 2 - (int)difftime(curTime, startime);
				else
					newmessage.voteTime = Modules::ModuleVoting::Instance().VarVetoWinningOptionShownTime->ValueInt + 2;
				newmessage.votesNeededToPass = 0;
			}
			return newmessage;
		}

		// AbstractVotingSystem() is defaulted in its class (0x10739F90): a
		// derived constructor's `: AbstractVotingSystem()` then zero-fills the
		// base before calling it, as the original's VetoSystem() and
		// VotingSystem() do, which a user-provided constructor never allows.
		// The members it initializes carry default member initializers.
		// (These lines keep every later head line where it was.)


		// mangled_x86(MANGLED_DEFAULT, "??0MapAndType@Voting@Server@@QAE@$$QAU012@@Z"); no body to assert in
		_inline MapAndType::MapAndType(Server::Voting::MapAndType &&__that) = default; // 0x1073A550

		void VetoSystem::countVotes() // 0x10742160
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?countVotes@VetoSystem@Voting@Server@@AAEXXZ");

			currentNumberOfVotes = 0;
			for (auto const &vote : mapVotes)
			{
				//in case someone modifies the js and sends something other than a valid vote.
				if (vote.second != 1)
					continue;
				currentNumberOfVotes++;
			}
		}

		bool VetoSystem::isEnabled() // 0x10742780
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?isEnabled@VetoSystem@Voting@Server@@UAE_NXZ");

			return Modules::ModuleVoting::Instance().VarServerVotingType->ValueInt == 2;
		}

		void VetoSystem::Reset() // 0x1073E3C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@VetoSystem@Voting@Server@@UAEXXZ");

			voteStartedTime = 0;
			willSetMap = false;
			numberOfVetosUsed = 0;
			startime = 0;
			currentNumberOfVotes = 0;
			finalTally = Server::Voting::VotingMessage();
			mapVotes.clear();
		}

		void VetoSystem::StartVoting() // 0x1073EC30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StartVoting@VetoSystem@Voting@Server@@UAEXXZ");

			if (idle)
				return;
			if (shouldRunPreviousCommands)
			{
				for (auto const &command : previousWinner.haloType.endOfMatchCommands)
					Modules::CommandMap::Instance().ExecuteCommand(command, false);
				shouldRunPreviousCommands = false;
			}
			numberOfVetosUsed++;
			currentVetoOption = GenerateVotingOption();
			currentVetoOption.canveto = true;
			SetGameAndMap();
			SetVoteStartedTime();
		}

		void VetoSystem::FindWinner() // 0x1073CE60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindWinner@VetoSystem@Voting@Server@@AAEXXZ");

			countVotes();

			if (currentNumberOfVotes >= getVoteNeededToPass()){
				revoteFlag = true;
			}
			else {
				currentVetoOption.canveto = false;
				SetStartTimer();
				NotifyVotePassed(currentVetoOption);
			}

			voteStartedTime = 0;
			mapVotes.clear();
		}

		void VetoSystem::SetGameAndMap() // 0x1073E5E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetGameAndMap@VetoSystem@Voting@Server@@AAEXXZ");

			if (currentVetoOption.haloType.modPack.size() > 0)
				Modules::CommandMap::Instance().ExecuteCommand("Server.Mod \"" + currentVetoOption.haloType.modPack + "\"");
			else
				Modules::CommandMap::Instance().ExecuteCommand("Server.Mod none");
			for (auto const &command : currentVetoOption.haloType.commands)
				Modules::CommandMap::Instance().ExecuteCommand(command);
			previousWinner = currentVetoOption;
			shouldRunPreviousCommands = true;
			willSetMap = true;
		}

		void VetoSystem::SetStartTimer() // 0x1073EA30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetStartTimer@VetoSystem@Voting@Server@@AAEXXZ");

			auto message = GenerateVotingOptionsMessage(false);
			BroadcastVotingMessage(message);
			time(&startime);
		}

		void VetoSystem::SetVoteStartedTime() // 0x1073EB30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetVoteStartedTime@VetoSystem@Voting@Server@@AAEXXZ");


			auto message = GenerateVotingOptionsMessage(false);
			BroadcastVotingMessage(message);
			time(&voteStartedTime);
		}

		void VetoSystem::onExit() // 0x10742FE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?onExit@VetoSystem@Voting@Server@@UAEXXZ");

			if (shouldRunPreviousCommands)
			{
				for (auto &command : previousWinner.haloType.endOfMatchCommands)
				{
					Modules::CommandMap::Instance().ExecuteCommand(command, false);
				}
				shouldRunPreviousCommands = false;
			}
		}

		bool VetoSystem::LoadJson(std::string filename) // 0x1073D970
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LoadJson@VetoSystem@Voting@Server@@EAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			entirePlaylist.clear();
			Server::Voting::VotingJson voting;
			if (!LoadVotingJson(filename, voting))
				return false;
			std::vector<Server::Voting::HaloType> gameTypes;
			HaloTypeInheritance::BuildHaloTypes(gameTypes, voting.types);
			for (auto const &playlistItem : voting.vetoPlaylist)
			{
				Server::Voting::HaloType ht;
				if (playlistItem.type.has_value())
				{
					if (!HaloTypeInheritance::BuildHaloType(ht, playlistItem.type.value(), voting.types))
					{
						Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, std::format("Failed to buld type in vetoPlaylist. Skipping."));
						continue;
					}
				}
				else
				{
					unsigned __int32 typeIndex = FindTypeByName(gameTypes, playlistItem.typeName);
					if (typeIndex == -1)
					{
						Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, std::format("Failed to find type '{}' in vetoPlaylist. Skipping.", playlistItem.typeName));
						continue;
					}
					ht = voting.types[typeIndex];
				}
				entirePlaylist.push_back(Server::Voting::MapAndType(playlistItem.map, ht));
			}
			if (entirePlaylist.size() < 1)
				BuildRandomPlaylist(entirePlaylist, gameTypes.size(), gameTypes, voting.maps);
			if (entirePlaylist.size() < 1)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "No items in playlist items. Using default maps and gametypes.");
				return false;
			}
			currentPlaylist = entirePlaylist;
			return true;
		}

		void VetoSystem::Tick() // 0x1073EE10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@VetoSystem@Voting@Server@@UAEXXZ");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!(session && session->IsEstablished() && session->IsHost() && Modules::ModuleVoting::Instance().VarServerVotingType->ValueInt == 2))
				return;
			time_t curTime1;
			time(&curTime1);
			if (idle)
			{
				if (Blam::Network::GetNumPlayers() > 0)
				{
					idle = false;
					if (Blam::Network::GetActiveSession()->Parameters.GetSessionMode() == 1)
						NewVote();
				}
				return;
			}
			else if (Blam::Network::GetNumPlayers() == 0)
			{
				idle = true;
				Reset();
				return;
			}
			if (startime != 0)
			{
				if (willSetMap && !eldorado::levels_enumeration_in_progress())
				{
					willSetMap = false;
					Modules::CommandMap::Instance().ExecuteCommand("Game.GameType \"" + currentVetoOption.haloType.typeName + "\"", false);
					Modules::CommandMap::Instance().ExecuteCommand("Game.Map \"" + currentVetoOption.haloMap.mapName + "\"", false);
				}
				long long elapsed = curTime1 - startime;
				if (elapsed > Modules::ModuleVoting::Instance().VarVetoWinningOptionShownTime->ValueInt + 2)
				{
					Modules::CommandMap::Instance().ExecuteCommand("Game.Start", false);
					Reset();
				}
			}
			if (revoteFlag)
			{
				NewVote();
				revoteFlag = false;
				return;
			}
			if (voteStartedTime == 0)
				return;
			long long elapsed = curTime1 - voteStartedTime;
			long VoteTime = Modules::ModuleVoting::Instance().VarServerMapVotingTime->ValueInt + 2;
			if (elapsed < VoteTime)
				return;
			FindWinner();
		}

		void VetoSystem::LogVote(Server::Voting::VotingMessage const &message, std::string name) // 0x1073DF30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LogVote@VetoSystem@Voting@Server@@UAEXABUVotingMessage@23@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost() || Utils::Singleton<Modules::ModuleVoting>::Instance().VarServerVotingType->ValueInt != 2 || !voteStartedTime)
				return;
			unsigned __int32 vote = message.Vote;
			auto it = mapVotes.find(name);
			if (it != mapVotes.end())
				mapVotes.erase(it);
			else
				mapVotes.insert(std::make_pair(name, vote));
			SendVoteCountsToEveryone();
		}

		void VetoSystem::NewVote() // 0x1073E280
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?NewVote@VetoSystem@Voting@Server@@UAEXXZ");

			if (numberOfVetosUsed < static_cast<long>(Modules::ModuleVoting::Instance().VarNumberOfVetoVotes->ValueInt))
			{
				mapVotes.clear();
				voteStartedTime = 0;
				StartVoting();
			}
			else
			{
				currentVetoOption = GenerateVotingOption();
				currentVetoOption.canveto = false;
				SetGameAndMap();
				SetStartTimer();
			}
		}

		void VetoSystem::EndVote() // 0x1073CD90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?EndVote@VetoSystem@Voting@Server@@UAEXXZ");


			Server::Voting::VotingMessage newmessage(Server::Voting::VoteEnded);
			newmessage.voteEnded = true;
			BroadcastVotingMessage(newmessage);
		}

		void VetoSystem::loadDefaultMapsAndTypes() // 0x10742800
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?loadDefaultMapsAndTypes@VetoSystem@Voting@Server@@EAEXXZ");

			std::vector<Server::Voting::HaloType> gameTypes;
			std::vector<Server::Voting::HaloMap> haloMaps;
			for (auto &m : GetDefaultMapList())
			{
				if (m.name == "mainmenu")
					continue;
				Server::Voting::AllowedPlayerCount playerCount;
				playerCount.minimumPlayersAllowed = 0;
				playerCount.maximumPlayersAllowed = 16;
				Server::Voting::HaloMap map(m.name, m.name, m.displayName, m.name, m.mapId, 0.1f, playerCount);
				haloMaps.push_back(map);
			}
			__int32 index = 0;
			for (auto &t : DefaultTypes)
			{
				Server::Voting::HaloType type(t, DefaultTypeNames[index]);
				gameTypes.push_back(type);
				index++;
			}
			for (__int32 i = 0; i < 10; i++)
			{
				Server::Voting::HaloType gametype = gameTypes[rand() % gameTypes.size()];
				Server::Voting::HaloMap &map = haloMaps[rand() % haloMaps.size()];
				entirePlaylist.push_back(Server::Voting::MapAndType(map, gametype));
			}
			currentPlaylist = entirePlaylist;
		}
	}
}

/* ---------- private code */
