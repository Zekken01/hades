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
			extern std::string const DefaultTypes[8]; // 0x11387E88
			extern std::string const DefaultTypeNames[8]; // 0x11387F68
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Modules
{
	extern ModuleVoting* _sub_106D5100(Modules::ModuleVoting *const);
	ModuleVoting::ModuleVoting() : ModuleBase(todo_result<std::string>()) // 0x106D5100
	{
		mangled_x86(MANGLED_TODO, "??0ModuleVoting@Modules@@QAE@XZ");
		// Modules::ModuleVoting *const this;
		todo("implement");
		_sub_106D5100(this);
	}
}

/* ---------- private code */

_extern bool _sub_106D6110(std::vector<std::string> const &, std::string &);
bool ReloadJson(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x106D6110
{
	// `anonymous-namespace'::ReloadJson
	// std::string &returnInfo;
	// unsigned long VotingType;
	// bool loadFileFromDisc;
	todo("implement");
	bool __result = _sub_106D6110(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_106D6210(std::vector<std::string> const &, std::string &);
bool VarVotingSystemUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x106D6210
{
	// `anonymous-namespace'::VarVotingSystemUpdated
	// std::string &returnInfo;
	// Blam::Network::Session *session;
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_106D6210(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_106D5F80(std::vector<std::string> const &, std::string &);
bool CommandServerCancelVote(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x106D5F80
{
	// `anonymous-namespace'::CommandServerCancelVote
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_106D5F80(Arguments, returnInfo);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleVoting & Utils::Singleton<Modules::ModuleVoting>::Instance();
