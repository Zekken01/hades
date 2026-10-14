/* ---------- headers */

#include "Server/Voting/VotingJson.hpp"
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
#include "Server/Voting/VotingUtil.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/en.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10746890  // hades: added for 0x10746890

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
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
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
		struct PlaylistItem;
		struct SMapListItem;
		struct VotingJson;
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
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern bool LoadVotingJson(std::string const &filename, Server::Voting::VotingJson &voting);
		extern bool LoadPlaylistItem(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::PlaylistItem &item, std::vector<Server::Voting::HaloType> const &types);
		extern bool LoadHaloMap(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject, std::string const &modPack, Server::Voting::HaloMap &map);
		extern bool LoadHaloType(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::HaloType &ht);

		static unsigned __int32 FindTypeByName(std::vector<Server::Voting::HaloType> const &types, std::string const &name);
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
			// extern std::string const DefaultTypes[8]; // 0x11388C30  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x11388D10  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		bool LoadVotingJson(std::string const &filename, Server::Voting::VotingJson &voting) // 0x10747C00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LoadVotingJson@Voting@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUVotingJson@12@@Z");
			// static ...; // 0x107483F0
			// static ...; // 0x107483E7
			// static ...; // 0x107483E3
			// static ...; // 0x107483DB
			// static ...; // 0x107483D6
			// static ...; // 0x107483D3
			// static ...; // 0x107483CE
			// static ...; // 0x107483C9
			// static ...; // 0x107483C0
			// static ...; // 0x10748348
			// static ...; // 0x10748340
			// std::string const &filename;
			// Server::Voting::VotingJson &voting;
			// std::ifstream in;
			// std::string contents;
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> document;
				// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L0;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<begin>$L0;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<end>$L0;
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject;
						// Server::Voting::HaloMap haloMap;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<end>$L1;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<begin>$L1;
				// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L1;
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &typeObject;
						// Server::Voting::HaloType ht;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<end>$L2;
				// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L2;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<begin>$L2;
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &itemObject;
						// Server::Voting::PlaylistItem item;
				// std::string errorMsg;

			std::ifstream in(filename, std::ios::in | std::ios::binary);
			if (!in || !in.is_open())
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Could not find or open 'voting.json' file");
				return false;
			}
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			rapidjson::Document document;
			if (!document.Parse<0>(contents.c_str()).HasParseError() && document.IsObject())
			{
				if (document.HasMember("maps"))
				{
					for (rapidjson::Value const &mapObject : document["maps"].GetArray())
					{
						Server::Voting::HaloMap haloMap;
						if (LoadHaloMap(mapObject, "", haloMap))
							voting.maps.push_back(std::move(haloMap));
					}
				}
				if (document.HasMember("types"))
				{
					for (rapidjson::Value const &typeObject : document["types"].GetArray())
					{
						Server::Voting::HaloType ht;
						if (LoadHaloType(typeObject, ht))
							voting.types.push_back(ht);
					}
				}
				if (document.HasMember("vetoPlaylist"))
				{
					for (rapidjson::Value const &itemObject : document["vetoPlaylist"].GetArray())
					{
						Server::Voting::PlaylistItem item;
						if (LoadPlaylistItem(itemObject, item, voting.types))
							voting.vetoPlaylist.push_back(item);
					}
				}
				return true;
			}
			else
			{
				std::string errorMsg = std::format("Could not parse voting json. Error: {} line {}.  Using defaults instead.", rapidjson::GetParseError_En(document.GetParseError()), Utils::String::GetLineFromOffset(contents, document.GetErrorOffset()));
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, errorMsg);
				return false;
			}
		}

		// mangled_x86(MANGLED_DEFAULT, "??0PlaylistItem@Voting@Server@@QAE@$$QAU012@@Z"); no body to assert in
		_inline PlaylistItem::PlaylistItem(Server::Voting::PlaylistItem &&__that) = default; // 0x107459E0

		// mangled_x86(MANGLED_DEFAULT, "??0PlaylistItem@Voting@Server@@QAE@ABU012@@Z"); no body to assert in
		_inline PlaylistItem::PlaylistItem(Server::Voting::PlaylistItem const &__that) = default; // 0x10745AE0

		// mangled_x86(MANGLED_DEFAULT, "??0PlaylistItem@Voting@Server@@QAE@XZ"); no body to assert in

		// mangled_x86(MANGLED_DEFAULT, "??0SMapListItem@Voting@Server@@QAE@XZ"); no body to assert in

		// mangled_x86(MANGLED_DEFAULT, "??1SMapListItem@Voting@Server@@QAE@XZ"); no body to assert in
		_inline SMapListItem::~SMapListItem() = default; // 0x10745DE0

		// mangled_x86(MANGLED_DEFAULT, "??4CharacterOverride@HaloType@Voting@Server@@QAEAAU0123@$$QAU0123@@Z"); no body to assert in
		// _inline Server::Voting::HaloType::CharacterOverride &HaloType::CharacterOverride::operator=(Server::Voting::HaloType::CharacterOverride &&__that) = default; // 0x10745E40  // hades: left implicit

		bool LoadPlaylistItem(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::PlaylistItem &item, std::vector<Server::Voting::HaloType> const &types) // 0x107477D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LoadPlaylistItem@Voting@Server@@YA_NABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@AAUPlaylistItem@12@ABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@@Z");
			// static ...; // 0x10747B0D
			// static ...; // 0x10747B04
			// static ...; // 0x10747AD4
			// static ...; // 0x10747ACC
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c;
			// Server::Voting::PlaylistItem &item;
			// std::vector<Server::Voting::HaloType> const &types;
			// std::string modPack;
				// std::string errorMsg;
				// unsigned __int32 typeIndex;
				// Server::Voting::HaloType ht;

			if (!c.HasMember("map"))
			{
				std::string errorMsg = std::format("Veto playlist item must have either a 'map' member");
				return false;
			}
			std::string modPack;
			if (c.HasMember("typeName"))
			{
				item.typeName = c["typeName"].GetString();
				unsigned __int32 typeIndex = FindTypeByName(types, item.typeName);
				if (typeIndex == -1 || types[typeIndex].isTemplate)
					return false;
				modPack = types[typeIndex].modPack;
			}
			else if (c.HasMember("type"))
			{
				Server::Voting::HaloType ht;
				if (!LoadHaloType(c["type"], ht))
					return false;
				modPack = ht.modPack;
				item.type = std::move(ht);
			}
			else
			{
				std::string errorMsg = std::format("Veto playlist item must have either a 'type' or 'typeName' member");
				return false;
			}
			if (!LoadHaloMap(c["map"], modPack, item.map))
				return false;
			return true;
		}

		bool LoadHaloMap(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject, std::string const &modPack, Server::Voting::HaloMap &map) // 0x10746890
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LoadHaloMap@Voting@Server@@YA_NABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUHaloMap@12@@Z");
			// static ...; // 0x10746C34
			// static ...; // 0x10746C2C
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject;
			// std::string const &modPack;
			// Server::Voting::HaloMap &map;
			// std::string displayName;
			// Server::Voting::SMapListItem mapInfo;

			std::string displayName = "";
			if (!mapObject.HasMember("mapName"))
				return false;
			if (!mapObject.HasMember("displayName"))
				map.mapDisplayName = mapObject["mapName"].GetString();
			else
				map.mapDisplayName = mapObject["displayName"].GetString();
			if (map.mapDisplayName.length() > 16)
				map.mapDisplayName = map.mapDisplayName.substr(0, 16);
			map.mapName = mapObject["mapName"].GetString();
			Server::Voting::SMapListItem mapInfo;
			if (!getMapInfo(map.mapName, modPack, &mapInfo))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Voting Could not find map '" + map.mapName + "'");
				return false;
			}
			map.mapId = mapInfo.mapId;
			map.scnrName = mapInfo.name;
			if (mapObject.HasMember("randomChance"))
				map.randomChance = mapObject["randomChance"].GetFloat();
			if (mapObject.HasMember("minPlayersAllowed"))
				map.allowedPlayerCount.minimumPlayersAllowed = mapObject["minPlayersAllowed"].GetInt();
			if (mapObject.HasMember("maxPlayersAllowed"))
				map.allowedPlayerCount.maximumPlayersAllowed = mapObject["maxPlayersAllowed"].GetInt();
			if (mapObject.HasMember("imageUrl") && strlen(mapObject["imageUrl"].GetString()) > 0)
				map.imageUri = mapObject["imageUrl"].GetString();
			else
				map.imageUri = map.mapName;
			return true;
		}

		bool LoadHaloType(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::HaloType &ht) // 0x10746D60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LoadHaloType@Voting@Server@@YA_NABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@AAUHaloType@12@@Z");
			// static ...; // 0x107475A2
			// static ...; // 0x1074759D
			// static ...; // 0x1074759A
			// static ...; // 0x10747595
			// static ...; // 0x10747590
			// static ...; // 0x10747584
			// static ...; // 0x10747530
			// static ...; // 0x10747528
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c;
			// Server::Voting::HaloType &ht;
			// std::string typeDisplayName;
			// Server::Voting::AllowedPlayerCount playerCount;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &commands;
					// unsigned __int32 i;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &smaps;
						// Server::Voting::HaloMap haloMap;
				// rapidjson::GenericObject<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &overridesArr;
					// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
						// rapidjson::GenericArray<1,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &overrideObj;
						// std::string const &teamDesignator;

			if (!c.HasMember("typeName"))
				return false;
			std::string typeDisplayName = "";
			if (!c.HasMember("displayName"))
				typeDisplayName = c["typeName"].GetString();
			else
				typeDisplayName = c["displayName"].GetString();
			if (typeDisplayName.length() > 16)
				typeDisplayName = typeDisplayName.substr(0, 16);
			if (c.HasMember("isTemplate"))
				ht.isTemplate = c["isTemplate"].GetBool();
			if (c.HasMember("inherits"))
				ht.inherits = c["inherits"].GetString();
			ht.typeName = c["typeName"].GetString();
			ht.typeDisplayName = typeDisplayName;
			if (c.HasMember("modDisplayName"))
			{
				ht.modDisplayName = c["modDisplayName"].GetString();
				ht.modDisplayName = ht.modDisplayName.substr(0, 16);
			}
			else if (c.HasMember("modPack"))
			{
				ht.modDisplayName = c["modPack"].GetString();
				ht.modDisplayName = ht.modDisplayName.substr(0, 16);
			}
			if (c.HasMember("modPack"))
				ht.modPack = c["modPack"].GetString();
			if (c.HasMember("commands"))
			{
				rapidjson::Value const &commands = c["commands"];
				for (unsigned __int32 i = 0; i < commands.Size(); i++)
					ht.commands.push_back(commands[i].GetString());
			}
			if (c.HasMember("endOfMatchCommands"))
			{
				rapidjson::Value const &commands = c["endOfMatchCommands"];
				for (unsigned __int32 i = 0; i < commands.Size(); i++)
					ht.endOfMatchCommands.push_back(commands[i].GetString());
			}
			if (c.HasMember("specificMaps"))
			{
				rapidjson::Value const &smaps = c["specificMaps"];
				if (!smaps.IsNull())
				{
					for (unsigned __int32 i = 0; i < smaps.Size(); i++)
					{
						Server::Voting::HaloMap haloMap;
						if (!LoadHaloMap(smaps[i], ht.modPack, haloMap))
							continue;
						ht.specificMaps.push_back(std::move(haloMap));
					}
				}
			}
			if (c.HasMember("characterOverrides") && c["characterOverrides"].IsObject())
			{
				auto const &overridesArr = c["characterOverrides"].GetObject();
				for (auto it = overridesArr.MemberBegin(); it != overridesArr.MemberEnd(); ++it)
				{
					std::string const &teamDesignator = it->name.GetString();
					auto const &overrideObj = it->value.GetArray();
					ht.characterOverrides[teamDesignator] = { overrideObj[0].GetString(), overrideObj[1].GetString() };
				}
			}
			if (c.HasMember("randomChance"))
				ht.randomChance = c["randomChance"].GetFloat();
			else
				ht.randomChance = 0.1f;
			Server::Voting::AllowedPlayerCount playerCount;
			if (c.HasMember("minPlayersAllowed"))
				playerCount.minimumPlayersAllowed = c["minPlayersAllowed"].GetInt();
			if (c.HasMember("maxPlayersAllowed"))
				playerCount.maximumPlayersAllowed = c["maxPlayersAllowed"].GetInt();
			ht.allowedPlayerCount = playerCount;
			return true;
		}
	}
}

/* ---------- private code */

namespace Server
{
	namespace Voting
	{
		static unsigned __int32 FindTypeByName(std::vector<Server::Voting::HaloType> const &types, std::string const &name) // 0x10746060
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindTypeByName@Voting@Server@@YAIABV?$vector@UHaloType@Voting@Server@@V?$allocator@UHaloType@Voting@Server@@@std@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
			// Server::Voting::FindTypeByName
			// std::string const &name;
				// unsigned __int32 i;

			for (unsigned __int32 i = 0; i < types.size(); i++)
			{
				if (types[i].typeName == name)
					return i;
			}

			return -1;
		}
	}
}
