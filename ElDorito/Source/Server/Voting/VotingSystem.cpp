/* ---------- headers */

#include "Server/Voting/VotingSystem.hpp"
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

#include "mods/mod_system.hpp"  // hades: added for 0x10C4E800

#include "Utils/Logger.hpp"  // hades: added for 0x10C4F6F0

#include "Server/Voting/HaloTypeInheritance.hpp"  // hades: added for 0x10C4EBE0  // hades: added for 0x10C4EBE0

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
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
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
namespace Server
{
	namespace Voting
	{
		class AbstractVotingSystem;
		class VotingSystem;
		struct AllowedPlayerCount;
		struct HaloMap;
		struct HaloType;
		struct MapAndType;
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
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const levels_enumeration_in_progress = reinterpret_cast<bool (*)()>(0x54B3A0);
}

namespace Server
{
	namespace Voting
	{
		extern double getRandom(double fMin, double fMax);
		extern __int32 getVotesNeededToInstantSkip();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x1246B710  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x1246B7F0  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		VotingSystem::VotingSystem() : AbstractVotingSystem(), winnerChosenTime(0), mapSetTime(0), enumerationTime(0), numberOfRevotesUsed(0), numberOfRematchesUsed(0), isFirstVote(true), shouldRunPreviousCommands(false) /* hades-mem-init:  */ // 0x10C4D570
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0VotingSystem@Voting@Server@@QAE@XZ");
			// Server::Voting::VotingSystem *const this;
		}

		void VotingSystem::Init() // 0x10C4EBC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@VotingSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VotingSystem *const this;
		}

		bool VotingSystem::isEnabled() // 0x10C51440
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?isEnabled@VotingSystem@Voting@Server@@UAE_NXZ");
			// Server::Voting::VotingSystem *const this;

			return Modules::ModuleVoting::Instance().VarServerVotingType->ValueInt == 1;
		}

		void VotingSystem::Reset() // 0x10C4F230
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@VotingSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VotingSystem *const this;

			numberOfRevotesUsed = 0;
			winnerChosenTime = 0;
			enumerationTime = 0;
			voteStartedTime = 0;
			mapSetTime = 0;
			winnerChosen = false;

			mapVotes.clear();
		}

		void VotingSystem::NewVote() // 0x10C4F1B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?NewVote@VotingSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VotingSystem *const this;
			// function call : void ()
			// function call : void ()

			Reset();
			StartVoting();
		}

		void VotingSystem::EndVote() // 0x10C4DAB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?EndVote@VotingSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x10C4DB44
			// static ...; // 0x10C4DB38
			// static ...; // 0x10C4DB30
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage newmessage;

			Server::Voting::VotingMessage newmessage(VoteEnded);

			newmessage.voteEnded = true;
			Server::Voting::BroadcastVotingMessage(newmessage);
		}

		void VotingSystem::LogVote(Server::Voting::VotingMessage const &message, std::string name) // 0x10C4EE90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LogVote@VotingSystem@Voting@Server@@UAEXABUVotingMessage@23@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C4F0E8
			// static ...; // 0x10C4F0E0
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage const &message;
			// std::string name;
			// unsigned __int32 vote;
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > it;
			// function call : void ()

			if (!voteStartedTime || Utils::Singleton<Modules::ModuleVoting>::Instance().VarServerVotingType->ValueInt != 1)
				return;
			unsigned __int32 vote = message.Vote;
			if (vote < 0 || vote > Utils::Singleton<Modules::ModuleVoting>::Instance().VarServerNumberOfVotingOptions->ValueInt + 2)
				return;
			auto it = mapVotes.find(name);
			if (it != mapVotes.end())
				it->second = vote;
			else
				mapVotes.insert(std::make_pair(name, vote));
			SendVoteCountsToEveryone();
		}

		void VotingSystem::SendVoteCountsToEveryone() // 0x10C4F300
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendVoteCountsToEveryone@VotingSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x10C4F5B2
			// static ...; // 0x10C4F5A7
			// static ...; // 0x10C4F597
			// static ...; // 0x10C4F58C
			// static ...; // 0x10C4F55C
			// static ...; // 0x10C4F554
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage newmessage;
			// __int32 optionIndex;
				// unsigned long Timerlength;
				// Server::Voting::VotingMessage newmessageTimer;
				// __int32 time;
				// long long elapsed;
				// Server::Voting::VotingMessage newmessage;
				// long long curTime1;
				// long long elapsed2;
				// std::vector<Server::Voting::MapAndType> &<range>$L0;
				// Server::Voting::MapAndType *<begin>$L0;
				// Server::Voting::MapAndType *<end>$L0;
					// Server::Voting::MapAndType &option;

			if (winnerChosen)
			{
				time_t curTime1;
				time(&curTime1);
				long long elapsed2 = curTime1 - winnerChosenTime;
				long long elapsed = curTime1 - mapSetTime;
				unsigned long Timerlength = Modules::ModuleVoting::Instance().VarServerTimeBetweenVoteEndAndGameStart->ValueInt;
				__int32 time = 0;
				if (mapSetTime != 0 && elapsed < Timerlength)
					time = Timerlength - elapsed;
				VotingMessage newmessage(VotingMessageType::Winner);
				newmessage.winner = winningVotingOption.index;
				BroadcastVotingMessage(newmessage);
				VotingMessage newmessageTimer(VotingMessageType::VoteTimerUpdated);
				newmessageTimer.voteTime = time;
				newmessageTimer.shouldUpdateTimer = false;
				BroadcastVotingMessage(newmessageTimer);
				BroadcastVotingMessage(finalTally);
				return;
			}
			countVotes();
			VotingMessage newmessage(VotingMessageType::VoteTally);
			__int32 optionIndex = 0;
			for (auto &option : currentVotingOptions)
			{
				newmessage.votes[optionIndex] = option.Count;
				optionIndex++;
				option.Count = 0;
			}
			newmessage.votesNeededToPass = 0;
			BroadcastVotingMessage(newmessage);
		}

		void VotingSystem::loadDefaultMapsAndTypes() // 0x10C514C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?loadDefaultMapsAndTypes@VotingSystem@Voting@Server@@EAEXXZ");
			// static ...; // 0x10C51859
			// static ...; // 0x10C51855
			// static ...; // 0x10C51850
			// static ...; // 0x10C5182C
			// static ...; // 0x10C51824
			// Server::Voting::VotingSystem *const this;
			// __int32 index;
				// std::vector<Server::Voting::SMapListItem> const &<range>$L0;
				// Server::Voting::SMapListItem const *<begin>$L0;
				// Server::Voting::SMapListItem const *<end>$L0;
					// Server::Voting::SMapListItem const &m;
						// Server::Voting::AllowedPlayerCount playerCount;
						// Server::Voting::HaloMap map;
				// std::string const *<end>$L1;
				// std::string const *<begin>$L1;
				// std::string const &<range>$L1[8];
					// std::string const &t;
						// Server::Voting::HaloType type;

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
		}

		double getRandom(double fMin, double fMax) // 0x10C512A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?getRandom@Voting@Server@@YANNN@Z");
			// static ...; // 0x10C5137C
			// static ...; // 0x10C51364
			// static ...; // 0x10C5135C
			// double fMin;
			// double fMax;
			// std::uniform_real_distribution<double> dist;
			// std::mersenne_twister_engine<unsigned int,32,624,397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253> rng;

			std::mt19937 rng;
			std::uniform_real_distribution<double> dist(fMin, fMax);

			rng.seed(std::random_device()());

			return dist(rng);
		}

		Server::Voting::MapAndType VotingSystem::GenerateVotingOption() // 0x10C4E190
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateVotingOption@VotingSystem@Voting@Server@@EAE?AUMapAndType@23@XZ");
			// static ...; // 0x10C4E6AD
			// static ...; // 0x10C4E6A9
			// static ...; // 0x10C4E69C
			// static ...; // 0x10C4E678
			// static ...; // 0x10C4E670
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::HaloType gametype;
			// float gametype_sum_of_weights;
			// float pGametype;
			// float maps_sum_of_weights;
			// Server::Voting::HaloMap map;
			// __int32 playerCount;
			// std::vector<Server::Voting::HaloMap> mapsToSearch;
			// float pMap;
				// unsigned __int32 i;

			HaloType gametype;
			HaloMap map;
			float gametype_sum_of_weights = 0.0f;
			for (unsigned __int32 i = 0; i < gameTypes.size(); i++)
				gametype_sum_of_weights += gameTypes[i].randomChance;
			float pGametype = getRandom(0.0, gametype_sum_of_weights);
			for (unsigned __int32 i = 0; i < gameTypes.size(); i++)
			{
				if (gameTypes[i].randomChance > pGametype)
				{
					gametype = gameTypes[i];
					break;
				}
				pGametype -= gameTypes[i].randomChance;
			}
			std::vector<HaloMap> mapsToSearch = haloMaps;
			if (gametype.specificMaps.size() > 0)
				mapsToSearch = gametype.specificMaps;
			float maps_sum_of_weights = 0.0f;
			for (unsigned __int32 i = 0; i < mapsToSearch.size(); i++)
				maps_sum_of_weights += mapsToSearch[i].randomChance;
			float pMap = getRandom(0.0, maps_sum_of_weights);
			for (unsigned __int32 i = 0; i < mapsToSearch.size(); i++)
			{
				if (mapsToSearch[i].randomChance > pMap)
				{
					map = mapsToSearch[i];
					break;
				}
				pMap -= mapsToSearch[i].randomChance;
			}
			__int32 playerCount = Blam::Network::GetNumPlayers();
			if (map.allowedPlayerCount.minimumPlayersAllowed <= playerCount && map.allowedPlayerCount.maximumPlayersAllowed >= playerCount && gametype.allowedPlayerCount.minimumPlayersAllowed <= playerCount && gametype.allowedPlayerCount.maximumPlayersAllowed >= playerCount)
				return MapAndType(map, gametype);
			else
				return VotingSystem::GenerateVotingOption();
		}

		bool AbstractVotingSystem::ShouldSendVotingOptions() // 0x10C4F670
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ShouldSendVotingOptions@AbstractVotingSystem@Voting@Server@@UAE_NXZ");
			// Server::Voting::AbstractVotingSystem *const this;

			return voteStartedTime || winnerChosen;
		}

		Server::Voting::VotingMessage VotingSystem::GenerateVotingOptionsMessage(bool updateTime) // 0x10C4E800
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateVotingOptionsMessage@VotingSystem@Voting@Server@@UAE?AUVotingMessage@23@_N@Z");
			// static ...; // 0x10C4EAEC
			// static ...; // 0x10C4EAE4
			// static ...; // 0x10C4EAC0
			// static ...; // 0x10C4EAB8
			// Server::Voting::VotingSystem *const this;
			// bool updateTime;
			// __int32 i;
			// Server::Voting::VotingMessage newmessage;
			// long long curTime;
				// std::vector<Server::Voting::MapAndType> &<range>$L0;
				// Server::Voting::MapAndType *<begin>$L0;
				// Server::Voting::MapAndType *<end>$L0;
					// Server::Voting::MapAndType const &option;
						// std::string modHash;

			VotingMessage newmessage(VotingMessageType::VotingOptions);
			__int32 i = 0;
			for (auto const &option : currentVotingOptions)
			{
				strncpy_s(newmessage.votingOptions[i].scnrName, option.haloMap.scnrName.c_str(), _TRUNCATE);
				strncpy_s(newmessage.votingOptions[i].mapName, option.haloMap.mapDisplayName.c_str(), _TRUNCATE);
				strncpy_s(newmessage.votingOptions[i].typeName, option.haloType.typeDisplayName.c_str(), _TRUNCATE);
				strncpy_s(newmessage.votingOptions[i].modName, option.haloType.modDisplayName.c_str(), _TRUNCATE);
				std::string modHash = c_mod_system::get_mod_hash_by_identifier(option.haloType.modPack.c_str());
				strncpy_s(newmessage.votingOptions[i].modHash, modHash.c_str(), _TRUNCATE);
				strncpy_s(newmessage.votingOptions[i].imageUri, option.haloMap.imageUri.c_str(), _TRUNCATE);
				i++;
			}
			time_t curTime;
			time(&curTime);
			if (!winnerChosen)
			{
				if (updateTime)
					newmessage.voteTime = Modules::ModuleVoting::Instance().VarServerMapVotingTime->ValueInt + 2 - (int)difftime(curTime, voteStartedTime);
				else
					newmessage.voteTime = Modules::ModuleVoting::Instance().VarServerMapVotingTime->ValueInt + 2;
			}
			else
				newmessage.voteTime = 0;
			return newmessage;
		}
	}
}


namespace Server
{
	namespace Voting
	{
		std::vector<Server::Voting::MapAndType> VotingSystem::countQuickVotes() // 0x10C50E80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?countQuickVotes@VotingSystem@Voting@Server@@AAE?AV?$vector@UMapAndType@Voting@Server@@V?$allocator@UMapAndType@Voting@Server@@@std@@@std@@XZ");
			// static ...; // 0x10C51018
			// static ...; // 0x10C5100D
			// static ...; // 0x10C51004
			// static ...; // 0x10C50FE0
			// static ...; // 0x10C50FD8
			// Server::Voting::VotingSystem *const this;
			// std::vector<Server::Voting::MapAndType> tmp;
				// std::map<std::string,int> &<range>$L0;
				// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > <begin>$L0;
				// std::_Default_sentinel <end>$L0;
					// std::pair<std::string const ,int> const &vote;

			std::vector<Server::Voting::MapAndType> tmp = currentVotingOptions;
			for (std::pair<std::string const ,int> const &vote : mapVotes)
			{
				if (vote.second > (__int32)tmp.size() || vote.second < 1)
					continue;
				tmp.at(vote.second - 1).Count++;
			}
			return tmp;
		}

		void VotingSystem::countVotes() // 0x10C51090
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?countVotes@VotingSystem@Voting@Server@@AAEXXZ");
			// static ...; // 0x10C511B1
			// static ...; // 0x10C511A8
			// static ...; // 0x10C51190
			// static ...; // 0x10C51188
			// Server::Voting::VotingSystem *const this;
				// std::map<std::string,int> &<range>$L0;
				// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,int> > > > <begin>$L0;
				// std::_Default_sentinel <end>$L0;
					// std::pair<std::string const ,int> const &vote;

			for (auto const &vote : mapVotes)
			{
				if (vote.second > (int)currentVotingOptions.size() || vote.second < 1)
					continue;
				currentVotingOptions.at(vote.second - 1).Count++;
			}
		}

		void VotingSystem::FindWinner() // 0x10C4DB80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindWinner@VotingSystem@Voting@Server@@AAEXXZ");
			// static ...; // 0x10C4E041
			// static ...; // 0x10C4E036
			// static ...; // 0x10C4E02C
			// static ...; // 0x10C4E008
			// static ...; // 0x10C4E000
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage newmessage;
			// __int32 optionIndex;
			// std::vector<Server::Voting::MapAndType> finalVotingOptions;
			// Server::Voting::VotingMessage voteTally;
				// std::vector<Server::Voting::MapAndType> &<range>$L0;
				// Server::Voting::MapAndType *<begin>$L0;
				// Server::Voting::MapAndType *<end>$L0;
					// Server::Voting::MapAndType &option;
				// std::string *<end>$L1;
				// std::string *<begin>$L1;
				// std::vector<std::string> &<range>$L1;
					// std::string const &command;

			countVotes();
			std::vector<MapAndType> finalVotingOptions = currentVotingOptions;
			std::sort(finalVotingOptions.begin(), finalVotingOptions.end());
			winningVotingOption = finalVotingOptions.back();
			if (winningVotingOption.isRematchOption)
			{
				AllowShuffle = false;
				numberOfRematchesUsed++;
			}
			else if (winningVotingOption.isRevoteOption)
			{
				numberOfRevotesUsed++;
				mapVotes.clear();
				voteStartedTime = 0;
				revoteFlag = true;
				return;
			}
			else
			{
				AllowShuffle = true;
				previousWinner = winningVotingOption;
				numberOfRematchesUsed = 0;
			}
			VotingMessage newmessage(VotingMessageType::Winner);
			newmessage.winner = winningVotingOption.index;
			BroadcastVotingMessage(newmessage);
			VotingMessage voteTally(VotingMessageType::VoteTally);
			__int32 optionIndex = 0;
			for (auto &option : currentVotingOptions)
			{
				voteTally.votes[optionIndex] = option.Count;
				optionIndex++;
				option.Count = 0;
			}
			voteTally.votesNeededToPass = 0;
			finalTally = voteTally;
			for (std::string const &command : winningVotingOption.haloType.commands)
				Modules::CommandMap::Instance().ExecuteCommand(command, false);
			shouldRunPreviousCommands = true;
			if (winningVotingOption.haloType.modPack.size() > 0)
				Modules::CommandMap::Instance().ExecuteCommand("Server.Mod \"" + winningVotingOption.haloType.modPack + "\"", false);
			else
				Modules::CommandMap::Instance().ExecuteCommand("Server.Mod none", false);
			NotifyVotePassed(winningVotingOption);
			time(&winnerChosenTime);
			voteStartedTime = 0;
			mapVotes.clear();
			winnerChosen = true;
		}

		void VotingSystem::StartVoting() // 0x10C4F6F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StartVoting@VotingSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x10C4FD3B
			// static ...; // 0x10C4FD33
			// static ...; // 0x10C4FD2C
			// static ...; // 0x10C4FD24
			// static ...; // 0x10C4FCF4
			// static ...; // 0x10C4FCEC
			// Server::Voting::VotingSystem *const this;
			// Server::Voting::VotingMessage message;
				// unsigned __int32 i;
					// bool votingOptionsContains;
					// __int32 votingDuplicatesSeen;
					// Server::Voting::MapAndType Option;
				// std::vector<std::string> &<range>$L0;
				// std::string *<begin>$L0;
				// std::string *<end>$L0;
					// std::string const &command;
				// Server::Voting::MapAndType rematch;
				// Server::Voting::MapAndType revote;
			// function call : bool (std::string)
			// function call : void ()
			// function call : Server::Voting::MapAndType ()
			// function call : Server::Voting::MapAndType ()
			// function call : Server::Voting::VotingMessage (bool)

			if (idle)
				return;
			if (!gameTypes.size())
			{
				if (!LoadJson(Modules::ModuleVoting::Instance().VarVotingJsonPath->ValueString))
					loadDefaultMapsAndTypes();
			}
			winningVotingOption = {};
			currentVotingOptions.clear();
			for (unsigned __int32 i = 0; i < Modules::ModuleVoting::Instance().VarServerNumberOfVotingOptions->ValueInt; i++)
			{
				MapAndType Option = GenerateVotingOption();
				__int32 votingDuplicatesSeen = 0;
				bool votingOptionsContains = false;
				while (std::find(currentVotingOptions.begin(), currentVotingOptions.end(), Option) != currentVotingOptions.end())
				{
					Option = GenerateVotingOption();
					if (++votingDuplicatesSeen >= 200)
					{
						votingOptionsContains = true;
						Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Could not Find enough unique options to match Voting Duplication Level and Voting Option Count");
						break;
					}
				}
				if (!votingOptionsContains)
				{
					Option.index = i + 1;
					currentVotingOptions.push_back(Option);
				}
			}
			if (shouldRunPreviousCommands)
			{
				for (auto const &command : previousWinner.haloType.endOfMatchCommands)
					Modules::CommandMap::Instance().ExecuteCommand(command, false);
				shouldRunPreviousCommands = false;
			}
			if (numberOfRematchesUsed < Modules::ModuleVoting::Instance().VarServerNumberOfRematchesAllowed->ValueInt && !isFirstVote)
			{
				MapAndType rematch;
				rematch.isRematchOption = true;
				rematch.index = currentVotingOptions.size() + 1;
				rematch.haloMap = previousWinner.haloMap;
				rematch.haloType = previousWinner.haloType;
				rematch.haloMap.mapDisplayName = "Rematch";
				currentVotingOptions.push_back(rematch);
			}
			if (numberOfRevotesUsed < Modules::ModuleVoting::Instance().VarServerNumberOfRevotesAllowed->ValueInt)
			{
				MapAndType revote;
				revote.isRevoteOption = true;
				revote.haloMap.mapDisplayName = "Revote";
				revote.index = currentVotingOptions.size() + 1;
				currentVotingOptions.push_back(revote);
			}
			time(&voteStartedTime);
			VotingMessage message = GenerateVotingOptionsMessage(false);
			BroadcastVotingMessage(message);
		}

		__int32 getVotesNeededToInstantSkip() // 0x10C513C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?getVotesNeededToInstantSkip@Voting@Server@@YAHXZ");
			// procedure flags: nofpo

			return (__int32)round((Blam::Network::GetNumPlayers() - 1) * 51 / 100 + 1);
		}

		void VotingSystem::Tick() // 0x10C4FEE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@VotingSystem@Voting@Server@@UAEXXZ");
			// static ...; // 0x10C5050E
			// static ...; // 0x10C50503
			// static ...; // 0x10C504F8
			// static ...; // 0x10C504D4
			// static ...; // 0x10C504CC
			// Server::Voting::VotingSystem *const this;
			// long long elapsed;
			// long long curTime1;
				// long long enumerationElapsed;
					// Server::Voting::VotingMessage newmessage;
				// long long elapsed2;
				// __int32 playerCount;
					// std::vector<Server::Voting::MapAndType> voteCounts;
					// Server::Voting::MapAndType const &winningOption;
			// function call : void ()
			// function call : void ()
			// function call : bool (*const)()
			// function call : void ()
			// function call : void ()

			long long curTime1;
			time(&curTime1);
			if (idle)
			{
				if (Blam::Network::GetNumPlayers() > 0)
				{
					idle = false;
					if (Blam::Network::GetActiveSession()->Parameters.GetSessionMode() == 1 && Blam::Network::GetNetworkMode() == 3)
					{
						isFirstVote = true;
						StartVoting();
					}
				}
				return;
			}
			else if (Blam::Network::GetNumPlayers() == 0)
			{
				idle = true;
				Reset();
				return;
			}
			if (winnerChosenTime != 0 && !eldorado::levels_enumeration_in_progress())
			{
				if (enumerationTime == 0)
					time(&enumerationTime);
				if (enumerationTime != 0)
				{
					long long enumerationElapsed = curTime1 - enumerationTime;
					if (enumerationElapsed > 2)
					{
						Modules::CommandMap::Instance().ExecuteCommand("Game.GameType \"" + winningVotingOption.haloType.typeName + "\"", false);
						Modules::CommandMap::Instance().ExecuteCommand("Game.Map \"" + winningVotingOption.haloMap.mapName + "\"", false);
						winnerChosenTime = 0;
						enumerationTime = 0;
						time(&mapSetTime);
						VotingMessage newmessage(VotingMessageType::VoteTimerUpdated);
						newmessage.voteTime = Modules::ModuleVoting::Instance().VarServerTimeBetweenVoteEndAndGameStart->ValueInt;
						newmessage.shouldUpdateTimer = true;
						BroadcastVotingMessage(newmessage);
					}
				}
			}
			if (mapSetTime != 0)
			{
				long long elapsed = curTime1 - mapSetTime;
				if (elapsed > Modules::ModuleVoting::Instance().VarServerTimeBetweenVoteEndAndGameStart->ValueInt)
				{
					Modules::CommandMap::Instance().ExecuteCommand("Game.Start", false);
					isFirstVote = false;
					Reset();
				}
			}
			if (revoteFlag)
			{
				StartVoting();
				revoteFlag = false;
				return;
			}
			if (voteStartedTime == 0)
				return;
			long long elapsed2 = curTime1 - voteStartedTime;
			if (elapsed2 < (long long)Modules::ModuleVoting::Instance().VarServerMapVotingTime->ValueInt + 2)
			{
				__int32 playerCount = Blam::Network::GetNumPlayers();
				if (Modules::ModuleVoting::Instance().VarInstantSkipVotingEnabled->ValueInt == 1 && playerCount >= (__int32)Modules::ModuleVoting::Instance().VarInstantSkipVoteMinPlayers->ValueInt)
				{
					std::vector<MapAndType> voteCounts = countQuickVotes();
					std::sort(voteCounts.begin(), voteCounts.end());
					MapAndType const &winningOption = voteCounts.back();
					if (winningOption.Count >= getVotesNeededToInstantSkip())
						FindWinner();
				}
			}
			else
			{
				FindWinner();
			}
		}

		void VotingSystem::onExit() // 0x10C51970
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?onExit@VotingSystem@Voting@Server@@UAEXXZ");
			// Server::Voting::VotingSystem *const this;
				// std::vector<std::string> &<range>$L0;
				// std::string *<begin>$L0;
				// std::string *<end>$L0;
					// std::string const &command;

			isFirstVote = true;
			if (shouldRunPreviousCommands)
			{
				for (auto &command : previousWinner.haloType.endOfMatchCommands)
				{
					Modules::CommandMap::Instance().ExecuteCommand(command, false);
				}
				shouldRunPreviousCommands = false;
			}
		}

		bool VotingSystem::LoadJson(std::string filename) // 0x10C4EBE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LoadJson@VotingSystem@Voting@Server@@EAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C4EDE8
			// static ...; // 0x10C4EDE0
			// Server::Voting::VotingSystem *const this;
			// std::string filename;
			// Server::Voting::VotingJson voting;
				// std::vector<Server::Voting::HaloMap> &<range>$L0;
				// Server::Voting::HaloMap *<begin>$L0;
				// Server::Voting::HaloMap *<end>$L0;
					// Server::Voting::HaloMap &map;

			haloMaps.clear();
			gameTypes.clear();
			Server::Voting::VotingJson voting;
			if (!LoadVotingJson(filename, voting))
				return false;
			for (Server::Voting::HaloMap &map : voting.maps)
				haloMaps.push_back(map);
			HaloTypeInheritance::BuildHaloTypes(gameTypes, voting.types);
			if (gameTypes.size() < 2 || haloMaps.size() < 2)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Json must contain at least two gametypes and two maps. Using defaults instead.");
				return false;
			}
			return true;
		}
	}
}

/* ---------- private code */
