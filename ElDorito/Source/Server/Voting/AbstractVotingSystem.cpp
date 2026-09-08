/* ---------- headers */

#include "Server/Voting/AbstractVotingSystem.hpp"
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
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
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
		struct HaloMap;
		struct HaloType;
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

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::string const DefaultTypes[8]; // 0x113885D0
			extern std::string const DefaultTypeNames[8]; // 0x113886B0
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		_extern bool _sub_1072D740(Server::Voting::AbstractVotingSystem *const, std::string, bool);
		bool AbstractVotingSystem::ReloadVotingJson(std::string fileName, bool loadFileFromDisc) // 0x1072D740
		{
			mangled_x86(MANGLED_TODO, "?ReloadVotingJson@AbstractVotingSystem@Voting@Server@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
			// bool loadFileFromDisc;
			// bool success;
			// function call : bool (std::string)
			// function call : void ()
			// function call : void ()
			// function call : void ()
			todo("implement");
			bool __result = _sub_1072D740(this, fileName, loadFileFromDisc);
			return __result;
		}

		_extern __int32 _sub_1072E450(Server::Voting::AbstractVotingSystem *const);
		__int32 AbstractVotingSystem::getVoteNeededToPass() // 0x1072E450
		{
			mangled_x86(MANGLED_TODO, "?getVoteNeededToPass@AbstractVotingSystem@Voting@Server@@UAEHXZ");
			// Server::Voting::AbstractVotingSystem *const this;
			todo("implement");
			__int32 __result = _sub_1072E450(this);
			return __result;
		}

		_extern void _sub_1072D550(Server::Voting::AbstractVotingSystem *const, __int32);
		void AbstractVotingSystem::GenerateVotingOptionsMessage(__int32 peer) // 0x1072D550
		{
			mangled_x86(MANGLED_TODO, "?GenerateVotingOptionsMessage@AbstractVotingSystem@Voting@Server@@QAEXH@Z");
			// static ...; // 0x1072D654
			// static ...; // 0x1072D64C
			// Server::Voting::AbstractVotingSystem *const this;
			// __int32 peer;
			// Server::Voting::VotingMessage newmessage;
			// Blam::Network::Session *session;
			// function call : bool ()
			// function call : Server::Voting::VotingMessage (bool)
			todo("implement");
			_sub_1072D550(this, peer);
		}

		_extern void _sub_1072D6C0(Server::Voting::AbstractVotingSystem *const, Server::Voting::MapAndType const &);
		void AbstractVotingSystem::NotifyVotePassed(Server::Voting::MapAndType const &winner) // 0x1072D6C0
		{
			mangled_x86(MANGLED_TODO, "?NotifyVotePassed@AbstractVotingSystem@Voting@Server@@IAEXABUMapAndType@23@@Z");
			// Server::Voting::MapAndType const &winner;
			todo("implement");
			_sub_1072D6C0(this, winner);
		}

		_extern void _sub_1072D4B0(Server::Voting::AbstractVotingSystem *const);
		void AbstractVotingSystem::CheckAndLoadJson() // 0x1072D4B0
		{
			mangled_x86(MANGLED_TODO, "?CheckAndLoadJson@AbstractVotingSystem@Voting@Server@@QAEXXZ");
			// Server::Voting::AbstractVotingSystem *const this;
			todo("implement");
			_sub_1072D4B0(this);
		}

		// mangled_x86(MANGLED_DEFAULT, "??0CharacterOverride@HaloType@Voting@Server@@QAE@ABU0123@@Z"); no body to assert in
		_inline HaloType::CharacterOverride::CharacterOverride(Server::Voting::HaloType::CharacterOverride const &__that) = default; // 0x1072C610

		// mangled_x86(MANGLED_DEFAULT, "??0HaloMap@Voting@Server@@QAE@ABU012@@Z"); no body to assert in
		_inline HaloMap::HaloMap(Server::Voting::HaloMap const &__that) = default; // 0x1072C6E0

		// mangled_x86(MANGLED_DEFAULT, "??0HaloType@Voting@Server@@QAE@ABU012@@Z"); no body to assert in
		_inline HaloType::HaloType(Server::Voting::HaloType const &__that) = default; // 0x1072C840

		// mangled_x86(MANGLED_DEFAULT, "??0MapAndType@Voting@Server@@QAE@ABU012@@Z"); no body to assert in
		_inline MapAndType::MapAndType(Server::Voting::MapAndType const &__that) = default; // 0x1072CAB0

		// mangled_x86(MANGLED_DEFAULT, "??1CharacterOverride@HaloType@Voting@Server@@QAE@XZ"); no body to assert in
		_inline HaloType::CharacterOverride::~CharacterOverride() = default; // 0x1072D0B0

		// mangled_x86(MANGLED_DEFAULT, "??1HaloMap@Voting@Server@@QAE@XZ"); no body to assert in
		_inline HaloMap::~HaloMap() = default; // 0x1072D110

		// mangled_x86(MANGLED_DEFAULT, "??1HaloType@Voting@Server@@QAE@XZ"); no body to assert in
		_inline HaloType::~HaloType() = default; // 0x1072D190

		// mangled_x86(MANGLED_DEFAULT, "??1MapAndType@Voting@Server@@QAE@XZ"); no body to assert in
		_inline MapAndType::~MapAndType() = default; // 0x1072D260
	}
}

/* ---------- private code */
