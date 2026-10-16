/* ---------- headers */

#include "Modules/ModuleVoting.hpp"
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
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
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
		struct Session;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleVoting;
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
namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

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

namespace Web { namespace Ui { namespace Voting { void VotingEnded(); } } }  // hades: added for 0x106D6210
namespace Server { namespace Voting { void StartNewVote(); } }  // hades: added for 0x106D6210

namespace Web { namespace Ui { namespace Voting { void Hide(); } } }  // hades: added for 0X106D5F80
namespace Server { namespace Voting { bool CancelVoteInProgress(); } }  // hades: added for 0X106D5F80

namespace Server::Voting { bool ReloadVotingJson(bool loadFileFromDisc); }  // hades: added for 0X106D6110
namespace Server::Voting { bool ReloadVetoJson(bool loadFileFromDisc); }  // hades: added for 0X106D6110

bool ReloadJson(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VarVotingSystemUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandServerCancelVote(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

namespace Utils
{
	Modules::ModuleVoting *Utils::Singleton<Modules::ModuleVoting>::m_instance; // 0x11387E84
}

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x11387E88  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x11387F68  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Modules
{
	ModuleVoting::ModuleVoting() : ModuleBase("Voting") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x106D5100
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleVoting@Modules@@QAE@XZ");

		VarVotingJsonPath = AddVariableString("JsonPath", "voting_json_path", "Voting Json Path", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), "data/server/voting.json");
		AddCommand("ReloadJson", "reload_voting_json", "Manually Reloads Json", eCommandFlagsHostOnly, ReloadJson);
		AddCommand("CancelVote", "cancelvote", "Cancels the vote", eCommandFlagsHostOnly, CommandServerCancelVote);
		VarServerVotingDuplicationLevel = AddVariableInt("DuplicationLevel", "voting_duplication_level", "Whether duplicate voting options will be allowed.", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 1);
		VarServerVotingDuplicationLevel->ValueIntMin = 0;
		VarServerVotingDuplicationLevel->ValueIntMax = 2;
		VarServerTimeBetweenVoteEndAndGameStart = AddVariableInt("VoteGameStartCountdown", "time_between_vote_end_and_game_start", "Controls how many seconds to wait after a vote passes before calling 'game.start'. ", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 5);
		VarServerTimeBetweenVoteEndAndGameStart->ValueIntMin = 4;
		VarServerTimeBetweenVoteEndAndGameStart->ValueIntMax = 100;
		VarServerVotingType = AddVariableInt("SystemType", "voting_enabled", "0 = Disabled, 1 = Voting, 2 = Vetoing", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0, VarVotingSystemUpdated);
		VarServerVotingType->ValueIntMin = 0;
		VarServerVotingType->ValueIntMax = 2;
		VarServerMapVotingTime = AddVariableInt("VoteTime", "map_voting_time", "Controls how long the vote lasts for Map Voting. ", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0x14);
		VarServerMapVotingTime->ValueIntMin = 1;
		VarServerMapVotingTime->ValueIntMax = 100;
		VarServerNumberOfRevotesAllowed = AddVariableInt("MaxRevoteCount", "number_of_revotes_allowed", "Controls how many revotes are allowed in the voting system ", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 3);
		VarServerNumberOfRevotesAllowed->ValueIntMin = 0;
		VarServerNumberOfRevotesAllowed->ValueIntMax = 100;
		VarServerNumberOfVotingOptions = AddVariableInt("VoteOptionCount", "number_of_voting_options", "Controls how many voting options are displayed ", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 3);
		VarServerNumberOfVotingOptions->ValueIntMin = 1;
		VarServerNumberOfVotingOptions->ValueIntMax = 4;
		VarServerNumberOfRematchesAllowed = AddVariableInt("MaxRematchCount", "number_of_rematches_allowed", "Controls how many rematches are allowed in the voting system ", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0);
		VarServerNumberOfRematchesAllowed->ValueIntMin = 0;
		VarServerNumberOfRematchesAllowed->ValueIntMax = 100;
		VarNumberOfVetoVotes = AddVariableInt("MaxVetoCount", "number_of_veto_votes", "Controls how many veto votes are allowed ", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 1);
		VarNumberOfVetoVotes->ValueIntMin = 0;
		VarNumberOfVetoVotes->ValueIntMax = 100;
		VarVetoWinningOptionShownTime = AddVariableInt("VetoWinnerShowTime", "vwost", "The length of time the winning option is show", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 5);
		VarVetoWinningOptionShownTime->ValueIntMin = 1;
		VarVetoWinningOptionShownTime->ValueIntMax = 100;
		VarVetoVotePassPercentage = AddVariableInt("VetoPassPercentage", "vvpp", "Percentage of players that need to vote for it to pass", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0x32);
		VarVetoVotePassPercentage->ValueIntMin = 1;
		VarVetoVotePassPercentage->ValueIntMax = 100;
		VarVetoSystemSelectionType = AddVariableInt("VetoSelectionType", "veto_system_selection_type", "0 = random, 1 = ordered ", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0);
		VarVetoSystemSelectionType->ValueIntMin = 0;
		VarVetoSystemSelectionType->ValueIntMax = 1;
		VarInstantSkipVotingEnabled = AddVariableInt("InstantVoteSkipEnabled", "instant_skip_voting", "Controls whether instant skip voting is enabled when majority of players vote for an option", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0);
		VarInstantSkipVotingEnabled->ValueIntMin = 0;
		VarInstantSkipVotingEnabled->ValueIntMax = 1;
		VarInstantSkipVoteMinPlayers = AddVariableInt("InstantVoteSkipMinPlayers", "instant_vote_skip_min_players", "Minimum number of players that need to vote for an instant skip to be considered", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 4);
		VarInstantSkipVoteMinPlayers->ValueIntMin = 1;
		VarInstantSkipVoteMinPlayers->ValueIntMax = 16;
	}
}

/* ---------- private code */

bool ReloadJson(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x106D6110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ReloadJson@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool loadFileFromDisc = true;
	if (Arguments.size() == 1)
	{
		if (Arguments[0] == "0")
		{
			loadFileFromDisc = false;
		}
	}
	unsigned int VotingType = Modules::ModuleVoting::Instance().VarServerVotingType->ValueInt;
	if ((VotingType == 1 && !Server::Voting::ReloadVotingJson(loadFileFromDisc)) || (VotingType == 2 && !Server::Voting::ReloadVetoJson(loadFileFromDisc)))
	{
		returnInfo = "Failed - Defaults used instead - Check log.";
		return false;
	}
	returnInfo = "Success";
	return true;
}

bool VarVotingSystemUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x106D6210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VarVotingSystemUpdated@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
		return true;
	if (!((bool(__cdecl *)())0x531E90)())
		return true;

	if (Blam::Network::GetNetworkMode() == 3)
	{
		if (!ElDorito::Instance().IsDedicated())
		{
			Web::Ui::Voting::Hide();
			Web::Ui::Voting::VotingEnded();
		}
		Server::Voting::CancelVoteInProgress();
		if (Modules::ModuleVoting::Instance().VarServerVotingType->ValueInt > 0)
			Server::Voting::StartNewVote();
	}

	return true;
}

bool CommandServerCancelVote(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x106D5F80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandServerCancelVote@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (!ElDorito::Instance().IsDedicated())
	{
		Web::Ui::Voting::Hide();
	}
	Server::Voting::CancelVoteInProgress();
	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleVoting & Utils::Singleton<Modules::ModuleVoting>::Instance();
