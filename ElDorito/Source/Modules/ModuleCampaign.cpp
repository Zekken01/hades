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

std::string camapgin_difficulty_level_to_string(long level);
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
	extern std::string const kCampaignSkullNames[16]; // 0x12408060
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	extern ModuleCampaign* _sub_108C38A0(Modules::ModuleCampaign *const);
	ModuleCampaign::ModuleCampaign() : ModuleBase(todo_result<std::string>()) // 0x108C38A0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleCampaign@Modules@@QAE@XZ");
		// Modules::ModuleCampaign *const this;
		todo("implement");
		_sub_108C38A0(this);
	}
}

/* ---------- private code */

extern std::string _sub_108C68E0(long);
std::string camapgin_difficulty_level_to_string(long level) // 0x108C68E0
{
	// `anonymous-namespace'::camapgin_difficulty_level_to_string
	// static ...; // 0x108C69E4
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// long level;
	todo("implement");
	std::string __result = _sub_108C68E0(level);
	return __result;
}

_extern long _sub_108C6800(std::string const &);
long camapgin_difficulty_level_from_string(std::string const &str) // 0x108C6800
{
	// `anonymous-namespace'::camapgin_difficulty_level_from_string
	// std::string const &str;
	todo("implement");
	long __result = _sub_108C6800(str);
	return __result;
}

extern std::string _sub_108C6AF0(long);
std::string camapgin_metagame_scoring_option_to_string(long level) // 0x108C6AF0
{
	// `anonymous-namespace'::camapgin_metagame_scoring_option_to_string
	// long level;
	todo("implement");
	std::string __result = _sub_108C6AF0(level);
	return __result;
}

_extern long _sub_108C6A40(std::string const &);
long camapgin_metagame_scoring_option_from_string(std::string const &str) // 0x108C6A40
{
	// `anonymous-namespace'::camapgin_metagame_scoring_option_from_string
	// std::string const &str;
	todo("implement");
	long __result = _sub_108C6A40(str);
	return __result;
}

_extern bool _sub_108C51A0(std::vector<std::string> const &, std::string &);
bool CommandCampaignInsertionPoint(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C51A0
{
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
	todo("implement");
	bool __result = _sub_108C51A0(arguments, returnInfo);
	return __result;
}

_extern bool _sub_108C4E00(std::vector<std::string> const &, std::string &);
bool CommandCampaignDifficultyLevel(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C4E00
{
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
	todo("implement");
	bool __result = _sub_108C4E00(arguments, returnInfo);
	return __result;
}

_extern bool _sub_108C49E0(std::vector<std::string> const &, std::string &);
bool CommandCampaginMetagameScoring(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C49E0
{
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
	todo("implement");
	bool __result = _sub_108C49E0(arguments, returnInfo);
	return __result;
}

extern std::string _sub_108C6140(unsigned long, unsigned long);
std::string GetActiveSkullsForDisplay(unsigned long primarySkulls, unsigned long secondarySkulls) // 0x108C6140
{
	// `anonymous-namespace'::GetActiveSkullsForDisplay
	// static ...; // 0x108C630C
	// static ...; // 0x108C62F4
	// static ...; // 0x108C62EC
	// unsigned long primarySkulls;
	// unsigned long secondarySkulls;
	// std::vector<std::string> skulls;
	// std::stringstream ss;
	{
		// __int32 i;
	}
	{
		// unsigned __int32 i;
	}
	todo("implement");
	std::string __result = _sub_108C6140(primarySkulls, secondarySkulls);
	return __result;
}

extern std::string _sub_108C6390();
std::string GetActiveSkullsForDisplay() // 0x108C6390
{
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
	todo("implement");
	std::string __result = _sub_108C6390();
	return __result;
}

_extern bool _sub_108C56D0(std::vector<std::string> const &, std::string &);
bool CommandCampaignListRallyPoints(std::vector<std::string> const &arguments, std::string &returninfo) // 0x108C56D0
{
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
	{
		// s_level_insertion_datum insertion;
		{
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
			{
				// __int32 i;
				{
					// std::string name;
				}
			}
		}
	}
	// function call : bool (*const)(long *, long *)
	// function call : bool (*const)(long, s_level_insertion_datum *)
	todo("implement");
	bool __result = _sub_108C56D0(arguments, returninfo);
	return __result;
}

_extern bool _sub_108C5B70(std::vector<std::string> const &, std::string &);
bool CommandCampaignSkulls(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C5B70
{
	// `anonymous-namespace'::CommandCampaignSkulls
	// std::string &returnInfo;
	{
		// unsigned long secondarySkulls;
		// bool result;
		// unsigned long primarySkulls;
		{
			// unsigned __int32 i;
			{
				// __int32 index;
			}
		}
	}
	// function call : bool (*const)(unsigned long)
	// function call : bool (*const)(unsigned long)
	todo("implement");
	bool __result = _sub_108C5B70(arguments, returnInfo);
	return __result;
}

_extern bool _sub_108C5AE0(std::vector<std::string> const &, std::string &);
bool CommandCampaignSave(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C5AE0
{
	// `anonymous-namespace'::CommandCampaignSave
	// std::string &returnInfo;
	// void (*const main_save_map)();
	// function call : bool (*)()
	// function call : void (*const)()
	todo("implement");
	bool __result = _sub_108C5AE0(arguments, returnInfo);
	return __result;
}

_extern bool _sub_108C5A50(std::vector<std::string> const &, std::string &);
bool CommandCampaignRevert(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C5A50
{
	// `anonymous-namespace'::CommandCampaignRevert
	// std::string &returnInfo;
	// char (*const main_revert_map_scripting)();
	// function call : bool (*)()
	// function call : char (*const)()
	todo("implement");
	bool __result = _sub_108C5A50(arguments, returnInfo);
	return __result;
}

_extern bool _sub_108C55D0(std::vector<std::string> const &, std::string &);
bool CommandCampaignKillEnemies(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x108C55D0
{
	// `anonymous-namespace'::CommandCampaignKillEnemies
	// std::string &returnInfo;
	// constexpr void (*const `CommandCampaignKillEnemies'::`2'::actor_kill)(long, bool, bool); // constant == 21154304
	// constexpr char (*const `CommandCampaignKillEnemies'::`2'::game_team_is_enemy)(long, long); // constant == 6753152
	// function call : bool (*)()
	todo("implement");
	bool __result = _sub_108C55D0(arguments, returnInfo);
	return __result;
}
