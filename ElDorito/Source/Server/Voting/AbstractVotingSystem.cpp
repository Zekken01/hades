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
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x113885D0
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x113886B0
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
		bool AbstractVotingSystem::ReloadVotingJson(std::basic_string<char,std::char_traits<char>,std::allocator<char> > fileName, bool loadFileFromDisc) // 0x1072D740
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

		extern HaloType::CharacterOverride* _sub_1072C610(Server::Voting::HaloType::CharacterOverride *const, Server::Voting::HaloType::CharacterOverride const &);
		_inline HaloType::CharacterOverride::CharacterOverride(Server::Voting::HaloType::CharacterOverride const &__that) // 0x1072C610
		{
			mangled_x86(MANGLED_TODO, "??0CharacterOverride@HaloType@Voting@Server@@QAE@ABU0123@@Z");
			// Server::Voting::HaloType::CharacterOverride const &__that;
			compiler_generated();
			todo("implement");
			_sub_1072C610(this, __that);
		}

		extern HaloMap* _sub_1072C6E0(Server::Voting::HaloMap *const, Server::Voting::HaloMap const &);
		_inline HaloMap::HaloMap(Server::Voting::HaloMap const &__that) // 0x1072C6E0
		{
			mangled_x86(MANGLED_TODO, "??0HaloMap@Voting@Server@@QAE@ABU012@@Z");
			// Server::Voting::HaloMap const &__that;
			compiler_generated();
			todo("implement");
			_sub_1072C6E0(this, __that);
		}

		extern HaloType* _sub_1072C840(Server::Voting::HaloType *const, Server::Voting::HaloType const &);
		_inline HaloType::HaloType(Server::Voting::HaloType const &__that) // 0x1072C840
		{
			mangled_x86(MANGLED_TODO, "??0HaloType@Voting@Server@@QAE@ABU012@@Z");
			// Server::Voting::HaloType const &__that;
			compiler_generated();
			todo("implement");
			_sub_1072C840(this, __that);
		}

		extern MapAndType* _sub_1072CAB0(Server::Voting::MapAndType *const, Server::Voting::MapAndType const &);
		_inline MapAndType::MapAndType(Server::Voting::MapAndType const &__that) // 0x1072CAB0
		{
			mangled_x86(MANGLED_TODO, "??0MapAndType@Voting@Server@@QAE@ABU012@@Z");
			// Server::Voting::MapAndType const &__that;
			compiler_generated();
			todo("implement");
			_sub_1072CAB0(this, __that);
		}

		_extern void _sub_1072D0B0(Server::Voting::HaloType::CharacterOverride *const);
		_inline HaloType::CharacterOverride::~CharacterOverride() // 0x1072D0B0
		{
			mangled_x86(MANGLED_TODO, "??1CharacterOverride@HaloType@Voting@Server@@QAE@XZ");
			// Server::Voting::HaloType::CharacterOverride *const this;
			compiler_generated();
			todo("implement");
			_sub_1072D0B0(this);
		}

		_extern void _sub_1072D110(Server::Voting::HaloMap *const);
		_inline HaloMap::~HaloMap() // 0x1072D110
		{
			mangled_x86(MANGLED_TODO, "??1HaloMap@Voting@Server@@QAE@XZ");
			// Server::Voting::HaloMap *const this;
			compiler_generated();
			todo("implement");
			_sub_1072D110(this);
		}

		_extern void _sub_1072D190(Server::Voting::HaloType *const);
		_inline HaloType::~HaloType() // 0x1072D190
		{
			mangled_x86(MANGLED_TODO, "??1HaloType@Voting@Server@@QAE@XZ");
			// Server::Voting::HaloType *const this;
			compiler_generated();
			todo("implement");
			_sub_1072D190(this);
		}

		_extern void _sub_1072D260(Server::Voting::MapAndType *const);
		_inline MapAndType::~MapAndType() // 0x1072D260
		{
			mangled_x86(MANGLED_TODO, "??1MapAndType@Voting@Server@@QAE@XZ");
			// Server::Voting::MapAndType *const this;
			compiler_generated();
			todo("implement");
			_sub_1072D260(this);
		}
	}
}

/* ---------- private code */
