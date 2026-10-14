/* ---------- headers */

#include "Modules/ModuleCampaign.hpp"
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
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleBase.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/String.hpp"

#include "Objects/ObjectMessaging.hpp"  // hades: added for 0x108C55D0

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
#include <limits>
#include <memory>
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

class c_network_session;
struct lambda_1;
struct s_level_insertion_datum;
namespace Modules
{
	class ModuleBase;
	class ModuleCampaign;
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;
namespace Objects {}
using namespace ::Objects;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

//class CommandCampaignKillEnemies::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//};
//static_assert(sizeof(CommandCampaignKillEnemies::__l2::<lambda_1>) == 1, "Invalid CommandCampaignKillEnemies::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Server { namespace VariableSynchronization { extern void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable); } }  // hades: added for 0x108C38A0

extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x108C4E00

extern bool (*game_is_campaign)();  // hades: added for 0X108C5A50

static std::string camapgin_difficulty_level_to_string(long level);
long camapgin_difficulty_level_from_string(std::string const &str);
std::string camapgin_metagame_scoring_option_to_string(long level);
long camapgin_metagame_scoring_option_from_string(std::string const &str);
bool CommandCampaignInsertionPoint(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandCampaignDifficultyLevel(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandCampaginMetagameScoring(std::vector<std::string> const &arguments, std::string &returnInfo);
std::string GetActiveSkullsForDisplay(unsigned long primarySkulls, unsigned long secondarySkulls);
std::string GetActiveSkullsForDisplay();
bool CommandCampaignListRallyPoints(std::vector<std::string> const &arguments, std::string &returninfo);
bool CommandCampaignSkulls(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandCampaignSave(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandCampaignRevert(std::vector<std::string> const &arguments, std::string &returnInfo);
bool CommandCampaignKillEnemies(std::vector<std::string> const &arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	std::string const kCampaignSkullNames[16] = { "iron", "black_eye", "tough_luck", "catch", "fog", "famine", "thunderstorm", "tilt", "mythic", "assassin", "blind", "superman", "birthday", "daddy", "third_person", "directors_cut" }; // 0x12408060
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	ModuleCampaign::ModuleCampaign() : ModuleBase("Campaign") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x108C38A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleCampaign@Modules@@QAE@XZ");
		// Modules::ModuleCampaign *const this;

		AddCommand("DifficultyLevel", "campaign_difficulty_level", "Sets the campaign difficulty level. (easy, normal, heroic, legendary)", eCommandFlagsNone, CommandCampaignDifficultyLevel);
		AddCommand("InsertionPoint", "campaign_insertion_point", "Changes the current insertion point.", eCommandFlagsNone, CommandCampaignInsertionPoint);
		AddCommand("MetagameScoring", "campaign_metagame_scoring", "Changes the metagame scoring options. (off, team, ffa)", eCommandFlagsNone, CommandCampaginMetagameScoring);
		AddCommand("Skulls", "campaign_skulls", "Set the campaign skulls (" + GetActiveSkullsForDisplay(-1, -1) + ")", eCommandFlagsHostOnly, CommandCampaignSkulls);
		AddCommand("GetRallyPoints", "get_rally_points", "lists out the currently available rally points for the selected map", eCommandFlagsInternal, CommandCampaignListRallyPoints);
		AddCommand("Save", "campaign_save", "Forces a campaign checkpoint", eCommandFlagsHostOnly, CommandCampaignSave);
		AddCommand("Revert", "campaign_revert", "Reverts to the last checkpoint", eCommandFlagsHostOnly, CommandCampaignRevert);
		AddCommand("KillEnemy", "campaign_kill_enemy", "Kills all enemies on the map", eCommandFlagsNone, CommandCampaignKillEnemies);
		VarCinematicFrameRate = AddVariableInt("CinematicFrameRate", "cinematic_frame_rate", "Set the cinematic frame rate in seconds", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsReplicated), 0x3C);
		VarCinematicFrameRate->ValueIntMin = 1;
		VarCinematicFrameRate->ValueIntMax = 144;
		VarCinematicFrameRateClient = AddVariableInt("CinematicFrameRateClient", "cinematic_frame_rate_client", "Set the cinematic frame rate in seconds", eCommandFlagsInternal, 0x3C);
		Server::VariableSynchronization::Synchronize(VarCinematicFrameRate, VarCinematicFrameRateClient);
		VarPlayerRepresentationEnabled = AddVariableInt("PlayerRepresentationEnabled", "camapign_player_representation_enabled", "Determines whether the player campaign representation will be used.", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived | eCommandFlagsReplicated), 1);
		VarPlayerRepresentationEnabled->ValueIntMin = 0;
		VarPlayerRepresentationEnabled->ValueIntMax = 1;
		VarPlayerRepresentationEnabledClient = AddVariableInt("PlayerRepresentationEnabledClient", "camapign_player_representation_enabled_client", "Determines whether the player campaign representation will be used", eCommandFlagsInternal, 1);
		Server::VariableSynchronization::Synchronize(VarPlayerRepresentationEnabled, VarPlayerRepresentationEnabledClient);
		VarCampaignSprintEnabled = AddVariableInt("SprintEnabled", "campaign_sprint_enabled", "Sets whether sprint will be enabled during campaign", eCommandFlagsArchived, 0);
		VarCampaignSprintEnabled->ValueIntMin = 0;
		VarCampaignSprintEnabled->ValueIntMax = 1;
		VarCheckpointsDisabled = AddVariableInt("CheckpointsDisabled", "campaign_checkpoints_disabled", "Disables campaign checkpoints", eCommandFlagsArchived, 0);
	}
}

/* ---------- private code */

static std::string camapgin_difficulty_level_to_string(long level) // 0x108C68E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?camapgin_difficulty_level_to_string@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@J@Z");
	// `anonymous-namespace'::camapgin_difficulty_level_to_string
	// static ...; // 0x108C69E4
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// long level;

	switch (level)
	{
	case 0:
		return "easy";
	case 1:
		return "normal";
	case 2:
		return "heroic";
	case 3:
		return "legendary";
	}

	return "unknown";
}

long camapgin_difficulty_level_from_string(std::string const &str) // 0x108C6800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?camapgin_difficulty_level_from_string@@YAJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::camapgin_difficulty_level_from_string
	// std::string const &str;

	if (str == "easy")
	{
		return 0;
	}
	else if (str == "normal")
	{
		return 1;
	}
	else if (str == "heroic")
	{
		return 2;
	}
	else if (str == "legendary")
	{
		return 3;
	}
	return -1;
}

std::string camapgin_metagame_scoring_option_to_string(long level) // 0x108C6AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?camapgin_metagame_scoring_option_to_string@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@J@Z");
	// `anonymous-namespace'::camapgin_metagame_scoring_option_to_string
	// long level;

	switch (level)
	{
	case 0:
		return "off";
	case 1:
		return "team";
	case 2:
		return "ffa";
	}

	return "unknown";
}

long camapgin_metagame_scoring_option_from_string(std::string const &str) // 0x108C6A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?camapgin_metagame_scoring_option_from_string@@YAJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::camapgin_metagame_scoring_option_from_string
	// std::string const &str;

	if (str == "off")
	{
		return 0;
	}
	else if (str == "team")
	{
		return 1;
	}
	else if (str == "ffa")
	{
		return 2;
	}

	return -1;
}

bool CommandCampaignInsertionPoint(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C51A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCampaignInsertionPoint@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCampaignInsertionPoint
	// static ...; // 0x108C54E0
	// static ...; // 0x108C54D8
// $LN18:
// $LN9:
	// std::vector<std::string> const &arguments;
	// std::string &returnInfo;
	// long previous_value;
	// c_network_session *session;
	// long new_value;
	// function call : bool (*const)(c_network_session **)
	// function call : short (*const)()
	// function call : bool (*const)(short)

	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session))
	{
		returnInfo = "Not in active session";
		return false;
	}
	long previous_value = ((short(__cdecl *)())0x435080)();
	if (arguments.size() < 1)
	{
		returnInfo = std::to_string(previous_value);
		return true;
	}
	long new_value = -1;
	try
	{
		new_value = std::stol(arguments[0]);
		if (new_value < 0 || new_value >= 9)
			throw std::out_of_range("");
	}
	catch (std::logic_error &)
	{
		returnInfo = "Invalid index given";
		return false;
	}
	if (!((bool(__cdecl *)(short))0x439580)(new_value))
	{
		returnInfo = "Failed to set session parameter";
		return false;
	}
	returnInfo = "Changed insertion point " + std::to_string(previous_value) + " -> " + std::to_string(new_value);
	return true;
}

bool CommandCampaignDifficultyLevel(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C4E00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCampaignDifficultyLevel@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCampaignDifficultyLevel
	// static ...; // 0x108C50C8
	// static ...; // 0x108C50C0
	// std::vector<std::string> const &arguments;
	// std::string &returnInfo;
	// long previous_value;
	// c_network_session *session;
	// long new_value;
	// function call : bool (*const)(c_network_session **)
	// function call : long (*const)()
	// function call : bool (*const)(long)

	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session))
	{
		returnInfo = "Not in active session";
		return false;
	}
	long previous_value = ((long(__cdecl *)())0x435020)();
	if (arguments.size() < 1)
	{
		returnInfo = camapgin_difficulty_level_to_string(previous_value);
		return true;
	}
	long new_value = camapgin_difficulty_level_from_string(arguments[0]);
	if (new_value == -1)
	{
		returnInfo = "Invalid difficulty level";
		return false;
	}
	if (!((bool(__cdecl *)(long))0x439510)(new_value))
	{
		returnInfo = "Failed to set session parameter";
		return false;
	}
	returnInfo = "Changed campaign difficulty " + camapgin_difficulty_level_to_string(previous_value) + " -> " + camapgin_difficulty_level_to_string(new_value);
	return true;
}

bool CommandCampaginMetagameScoring(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C49E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCampaginMetagameScoring@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCampaginMetagameScoring
	// static ...; // 0x108C4D14
	// static ...; // 0x108C4D0C
// $LN17:
// $LN8:
	// std::vector<std::string> const &arguments;
	// std::string &returnInfo;
	// long previous_value;
	// c_network_session *session;
	// long new_value;
	// function call : bool (*const)(c_network_session **)
	// function call : bool (*const)()
	// function call : bool (*const)(long)

	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session))
	{
		returnInfo = "Not in active session";
		return false;
	}
	long previous_value = ((bool(__cdecl *)())0x4350F0)();
	if (arguments.size() < 1)
	{
		returnInfo = camapgin_metagame_scoring_option_to_string(previous_value);
		return true;
	}
	long new_value = -1;
	try
	{
		new_value = camapgin_metagame_scoring_option_from_string(arguments[0]);
		if (new_value == -1)
			throw std::invalid_argument("arguments[0]");
	}
	catch (std::invalid_argument &)
	{
		returnInfo = "Invalid option given";
		return false;
	}
	if (!((bool(__cdecl *)(long))0x4395F0)(new_value))
	{
		returnInfo = "Failed to set session parameter";
		return false;
	}
	returnInfo = "Changed metagame scoring " + camapgin_metagame_scoring_option_to_string(previous_value) + " -> " + camapgin_metagame_scoring_option_to_string(new_value);
	return true;
}

std::string GetActiveSkullsForDisplay(unsigned long primarySkulls, unsigned long secondarySkulls) // 0x108C6140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetActiveSkullsForDisplay@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@KK@Z");
	// `anonymous-namespace'::GetActiveSkullsForDisplay
	// static ...; // 0x108C630C
	// static ...; // 0x108C62F4
	// static ...; // 0x108C62EC
	// unsigned long primarySkulls;
	// unsigned long secondarySkulls;
	// std::vector<std::string> skulls;
	// std::stringstream ss;
		// __int32 i;
		// unsigned __int32 i;

	std::vector<std::string> skulls;
	for (__int32 i = 0; i < _countof(kCampaignSkullNames); i++)
	{
		if (i >= 9 && (secondarySkulls >> (i - 9)) & 1)
			skulls.push_back(kCampaignSkullNames[i]);
		else if ((primarySkulls >> i) & 1)
			skulls.push_back(kCampaignSkullNames[i]);
	}
	std::stringstream ss;
	for (unsigned __int32 i = 0; i < skulls.size(); i++)
	{
		ss << skulls[i];
		if (i < skulls.size() - 1)
			ss << ", ";
	}
	return ss.str();
}

std::string GetActiveSkullsForDisplay() // 0x108C6390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetActiveSkullsForDisplay@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// `anonymous-namespace'::GetActiveSkullsForDisplay
	// procedure flags: nofpo
	// static ...; // 0x108C646C
	// static ...; // 0x108C645C
	// static ...; // 0x108C6444
	// static ...; // 0x108C643C
	// unsigned long secondarySkulls;
	// unsigned long primarySkulls;
	// function call : unsigned long *(*const)(unsigned long *)
	// function call : unsigned long *(*const)(unsigned long *)

	unsigned long primarySkulls = 0;
	unsigned long secondarySkulls = 0;
	((void (__cdecl *)(unsigned long *))0x434F40)(&primarySkulls);
	((void (__cdecl *)(unsigned long *))0x434FB0)(&secondarySkulls);

	return GetActiveSkullsForDisplay(primarySkulls, secondarySkulls);
}

bool CommandCampaignListRallyPoints(std::vector<std::string> const &arguments, std::string &returninfo) // 0x108C56D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCampaignListRallyPoints@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCampaignListRallyPoints
	// static ...; // 0x108C5985
	// static ...; // 0x108C597B
	// static ...; // 0x108C5970
	// static ...; // 0x108C5965
	// static ...; // 0x108C5960
	// static ...; // 0x108C5918
	// static ...; // 0x108C5910
	// std::vector<std::string> const &arguments;
	// std::string &returninfo;
	// long campaignId;
	// long mapId;
		// s_level_insertion_datum insertion;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
				// __int32 i;
					// std::string name;
	// function call : bool (*const)(long *, long *)
	// function call : bool (*const)(long, s_level_insertion_datum *)

	long campaignId;
	long mapId;
	if (reinterpret_cast<bool (*)(long *, long *)>(0x4354D0)(&campaignId, &mapId))
	{
		s_level_insertion_datum insertion;
		if (reinterpret_cast<bool (*)(long, s_level_insertion_datum *)>(0x54C9E0)(mapId, &insertion))
		{
			rapidjson::StringBuffer jsonBuffer;
			rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
			jsonWriter.StartObject();
			jsonWriter.Key("points");
			jsonWriter.StartArray();
			if (Blam::Network::GetLobbyType() == 0)
			{
				for (__int32 i = 0; i < 4; i++)
				{
					std::string name = Utils::String::ThinString(insertion.names[i].value);
					if (name != "")
						jsonWriter.String(name.c_str());
				}
			}
			jsonWriter.EndArray();
			jsonWriter.EndObject();
			returninfo = jsonBuffer.GetString();
			return true;
		}
	}
	returninfo = "{}";
	return true;
}

bool CommandCampaignSkulls(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C5B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCampaignSkulls@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCampaignSkulls
	// std::string &returnInfo;
		// unsigned long secondarySkulls;
		// bool result;
		// unsigned long primarySkulls;
			// unsigned __int32 i;
				// __int32 index;
	// function call : bool (*const)(unsigned long)
	// function call : bool (*const)(unsigned long)

	if (arguments.size() < 1)
	{
		returnInfo = GetActiveSkullsForDisplay();
		return true;
	}
	else
	{
		unsigned long primarySkulls = 0;
		unsigned long secondarySkulls = 0;
		if (arguments.size() != 1 || arguments[0] != "none")
		{
			for (unsigned __int32 i = 0; i < arguments.size(); i++)
			{
				__int32 index = std::find(std::begin(kCampaignSkullNames), std::end(kCampaignSkullNames), arguments[i]) - kCampaignSkullNames;
				if (index < 0 || index >= _countof(kCampaignSkullNames))
				{
					returnInfo = "Unknown skull '" + arguments[i] + "'\nOptions: [" + GetActiveSkullsForDisplay(-1, -1) + "]";
					return false;
				}
				if (index >= 9)
					secondarySkulls |= 1 << (index - 9);
				else
					primarySkulls |= 1 << index;
			}
		}
		bool result = ((bool (*)(unsigned long))0x439430)(primarySkulls);
		result &= ((bool (*)(unsigned long))0x4394A0)(secondarySkulls);
		if (result)
			returnInfo = "Active skulls -> " + GetActiveSkullsForDisplay();
		else
			returnInfo = "Failed to set skulls. Are you in the lobby?";
		return result;
	}
}

bool CommandCampaignSave(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C5AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCampaignSave@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCampaignSave
	// std::string &returnInfo;
	// void (*const main_save_map)();
	// function call : bool (*)()
	// function call : void (*const)()

	if (!game_is_campaign())
	{
		returnInfo = "Not in campaign";
		return false;
	}

	void (*const campaign_save)() = (void(*const)())0x506d80;

	campaign_save();
	return true;
}

bool CommandCampaignRevert(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C5A50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCampaignRevert@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCampaignRevert
	// std::string &returnInfo;
	// char (*const main_revert_map_scripting)();
	// function call : bool (*)()
	// function call : char (*const)()

	if (!game_is_campaign())
	{
		returnInfo = "Not in campaign";
		return false;
	}

	void (*const campaign_revert)() = (void(*const)())0x506ca0;

	campaign_revert();
	return true;
}

bool CommandCampaignKillEnemies(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C55D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCampaignKillEnemies@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCampaignKillEnemies
	// std::string &returnInfo;
	// constexpr void (*const `CommandCampaignKillEnemies'::`2'::actor_kill)(long, bool, bool); // constant == 21154304
	// constexpr char (*const `CommandCampaignKillEnemies'::`2'::game_team_is_enemy)(long, long); // constant == 6753152
	// function call : bool (*)()

	static void (*const actor_kill)(long, bool, bool) = reinterpret_cast<void (*)(long, bool, bool)>(0x142C900);
	static char (*const game_team_is_enemy)(long, long) = reinterpret_cast<char (*)(long, long)>(0x670B80);

	if (!game_is_campaign())
	{
		returnInfo = "Not in campaign";
		return false;
	}

	Objects::CObjectMessaging::EnqueueAction([]()
	{
		auto playerIndex = ((long (*)(long))0x589C30)(0);
		if (playerIndex == -1)
			return;
		auto playerTeam = player_get(playerIndex)->configuration.host.team;
		auto objects = object_headers_get();
		for (auto it = objects->begin(); it != objects->end(); ++it)
		{
			if (!((1 << (char)it->type) & 0x2003))
				continue;
			auto unit = (s_unit_data *)it->data;
			if (unit->actor_index == -1)
				continue;
			auto actor = actor_get(unit->actor_index);
			if (!game_team_is_enemy(playerTeam, actor->meta.team))
				continue;
			actor_kill(unit->actor_index, false, true);
		}
	});
	return true;
}
