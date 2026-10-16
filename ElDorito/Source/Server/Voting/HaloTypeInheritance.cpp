/* ---------- headers */

#include "Server/Voting/HaloTypeInheritance.hpp"
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
#include "Common/Http/HttpHeaders.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10733810  // hades: added for 0x10733810

#include "Server/Voting/VotingUtil.hpp"  // hades: added for 0x10733360  // hades: added for 0x10733360

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
#include <exception>
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Server
{
	namespace Voting
	{
		struct AllowedPlayerCount;
		struct HaloMap;
		struct HaloType;
		struct HaloTypeInheritance;
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

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Server { namespace Voting { unsigned __int32 FindMapByName(std::vector<Server::Voting::HaloMap> const &maps, std::string const &name); } }  // hades: added for 0x10733A40  // hades: added for 0x10733A40

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x113887F0  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x113888D0  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		void HaloTypeInheritance::MergeMaps(std::vector<Server::Voting::HaloMap> &maps, std::vector<Server::Voting::HaloMap> const &newMaps) // 0x10733A40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MergeMaps@HaloTypeInheritance@Voting@Server@@SAXAAV?$vector@UHaloMap@Voting@Server@@V?$allocator@UHaloMap@Voting@Server@@@std@@@std@@ABV45@@Z");

			for (Server::Voting::HaloMap const &map : newMaps)
			{
				if (FindMapByName(maps, map.mapName) == -1)
					maps.push_back(map);
			}
		}

		bool HaloTypeInheritance::BuildHaloType(Server::Voting::HaloType &newType, Server::Voting::HaloType const &currentType, std::vector<Server::Voting::HaloType> const &types) // 0x10733360
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BuildHaloType@HaloTypeInheritance@Voting@Server@@SA_NAAUHaloType@23@ABU423@ABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@@Z");

			if (!currentType.inherits.empty())
			{
				unsigned __int32 baseTypeIndex = FindTypeByName(types, currentType.inherits);
				if (baseTypeIndex == -1 || !BuildHaloType(newType, types[baseTypeIndex], types))
					return false;
			}
			if (!currentType.typeName.empty())
				newType.typeName = currentType.typeName;
			if (!currentType.typeDisplayName.empty())
				newType.typeDisplayName = currentType.typeDisplayName;
			if (!currentType.modPack.empty())
				newType.modPack = currentType.modPack;
			if (!currentType.modDisplayName.empty())
				newType.modDisplayName = currentType.modDisplayName;
			if (currentType.randomChance != 0.1f)
				newType.randomChance = currentType.randomChance;
			if (currentType.allowedPlayerCount.maximumPlayersAllowed < newType.allowedPlayerCount.maximumPlayersAllowed)
				newType.allowedPlayerCount.maximumPlayersAllowed = currentType.allowedPlayerCount.maximumPlayersAllowed;
			if (currentType.allowedPlayerCount.minimumPlayersAllowed > newType.allowedPlayerCount.minimumPlayersAllowed)
				newType.allowedPlayerCount.minimumPlayersAllowed = currentType.allowedPlayerCount.minimumPlayersAllowed;
			for (auto const &cmd : currentType.commands)
				newType.commands.push_back(cmd);
			for (auto const &cmd : currentType.endOfMatchCommands)
				newType.endOfMatchCommands.push_back(cmd);
			for (auto const &[k, v] : currentType.characterOverrides)
				newType.characterOverrides[k] = v;
			for (auto const &map : currentType.specificMaps)
				MergeMaps(newType.specificMaps, currentType.specificMaps);
			return true;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0AllowedPlayerCount@Voting@Server@@QAE@XZ"); no body to assert in
		_inline AllowedPlayerCount::AllowedPlayerCount() noexcept // 0x107327F0
		{
			minimumPlayersAllowed = 0;
			maximumPlayersAllowed = 0x10;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0CharacterOverride@HaloType@Voting@Server@@QAE@XZ"); no body to assert in

		// mangled_x86(MANGLED_DEFAULT, "??0HaloMap@Voting@Server@@QAE@$$QAU012@@Z"); no body to assert in
		_inline HaloMap::HaloMap(Server::Voting::HaloMap &&__that) noexcept = default; // 0x10732890

		void HaloTypeInheritance::BuildHaloTypes(std::vector<Server::Voting::HaloType> &newTypes, std::vector<Server::Voting::HaloType> const &allTypes) // 0x10733810
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BuildHaloTypes@HaloTypeInheritance@Voting@Server@@SAXAAV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@ABV45@@Z");

			for (Server::Voting::HaloType const &ht : allTypes)
			{
				if (ht.isTemplate)
					continue;
				Server::Voting::HaloType newHaloType;
				if (!BuildHaloType(newHaloType, ht, allTypes))
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, std::format("Voting failed to build game type \"{}\"", ht.typeName));
					continue;
				}
				newTypes.push_back(std::move(newHaloType));
			}
		}

		// mangled_x86(MANGLED_DEFAULT, "??0HaloType@Voting@Server@@QAE@$$QAU012@@Z"); no body to assert in
		_inline HaloType::HaloType(Server::Voting::HaloType &&__that) = default; // 0x107329A0

		// mangled_x86(MANGLED_DEFAULT, "??4CharacterOverride@HaloType@Voting@Server@@QAEAAU0123@ABU0123@@Z"); no body to assert in
		// _inline Server::Voting::HaloType::CharacterOverride &HaloType::CharacterOverride::operator=(Server::Voting::HaloType::CharacterOverride const &__that) = default; // 0x10732F60  // hades: left implicit
	}
}

/* ---------- private code */
