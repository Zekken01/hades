#ifndef __SERVER_VOTING_VOTINGTYPES_HPP__
#define __SERVER_VOTING_VOTINGTYPES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleVoting.hpp"
#include "Utils/NameValueTable.hpp"

#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleVoting;
}
namespace Server
{
	namespace Voting
	{
		struct AllowedPlayerCount;
		struct HaloMap;
		struct HaloType;
		struct MapAndType;
		struct PlaylistItem;
		struct SMapListItem;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Server
{
	namespace Voting
	{
		struct AllowedPlayerCount
		{
			__int32 minimumPlayersAllowed; // 0x0
			__int32 maximumPlayersAllowed; // 0x4
			_inline AllowedPlayerCount() noexcept; /* compiler_generated() */  // hades: noexcept - HaloMap() has no EH frame
		};
		static_assert(sizeof(Server::Voting::AllowedPlayerCount) == 8, "Invalid Server::Voting::AllowedPlayerCount size");

		struct HaloMap
		{
			__int32 mapId; // 0x0
			std::string scnrName; // 0x4
			std::string mapName; // 0x20
			std::string mapDisplayName; // 0x3C
			std::string imageUri; // 0x58
			float randomChance; // 0x74
			Server::Voting::AllowedPlayerCount allowedPlayerCount; // 0x78
			_inline HaloMap(Server::Voting::HaloMap &&__that) noexcept; /* compiler_generated() */
			_inline HaloMap(Server::Voting::HaloMap const &__that); /* compiler_generated() */
			_inline HaloMap(std::string sn, std::string m, std::string dn, std::string img, __int32 id, float rc, Server::Voting::AllowedPlayerCount apc);
			_inline HaloMap();
			_inline void SetMembers(std::string sn, std::string m, std::string dn, std::string img, __int32 id, float rc, Server::Voting::AllowedPlayerCount apc);
			_inline ~HaloMap(); /* compiler_generated() */
			_inline Server::Voting::HaloMap &operator=(Server::Voting::HaloMap &&__that) noexcept; /* compiler_generated() */
			_inline Server::Voting::HaloMap &operator=(Server::Voting::HaloMap const &__that); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Voting::HaloMap) == 128, "Invalid Server::Voting::HaloMap size");

		struct HaloType
		{
			public:
			struct CharacterOverride
			{
				std::string characterSetName; // 0x0
				std::string characterName; // 0x1C
				// hades: special members left implicit (LoadHaloType assigns the aggregate `{ a, b }`)
				// hades: special members left implicit (LoadHaloType assigns the aggregate `{ a, b }`)
				// hades: special members left implicit (LoadHaloType assigns the aggregate `{ a, b }`)
				// hades: special members left implicit (LoadHaloType assigns the aggregate `{ a, b }`)
				// hades: special members left implicit (LoadHaloType assigns the aggregate `{ a, b }`)
				// hades: special members left implicit (LoadHaloType assigns the aggregate `{ a, b }`)
			};
			static_assert(sizeof(CharacterOverride) == 56, "Invalid CharacterOverride size");
			public:
			bool isTemplate; // 0x0
			std::vector<Server::Voting::HaloMap> specificMaps; // 0x4
			std::string inherits; // 0x14
			std::string typeName; // 0x30
			std::string typeDisplayName; // 0x4C
			std::string modDisplayName; // 0x68
			std::string modPack; // 0x84
			float randomChance; // 0xA0
			Server::Voting::AllowedPlayerCount allowedPlayerCount; // 0xA4
			std::vector<std::string> commands; // 0xAC
			std::vector<std::string> endOfMatchCommands; // 0xBC
			std::map<std::string,CharacterOverride> characterOverrides; // 0xCC
			_inline HaloType(Server::Voting::HaloType &&__that); /* compiler_generated() */
			_inline HaloType(Server::Voting::HaloType const &__that); /* compiler_generated() */
			_inline HaloType(std::string t, std::string dn);
			_inline HaloType();
			_inline ~HaloType(); /* compiler_generated() */
			_inline Server::Voting::HaloType &operator=(Server::Voting::HaloType &&__that) noexcept; /* compiler_generated() */
			_inline Server::Voting::HaloType &operator=(Server::Voting::HaloType const &__that); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Voting::HaloType) == 216, "Invalid Server::Voting::HaloType size");
		static_assert(offsetof(Server::Voting::HaloType, specificMaps) == 0x4, "Server::Voting::HaloType::specificMaps moved when its reconstructed padding was removed");

		struct PlaylistItem
		{
			std::string typeName; // 0x0
			std::optional<Server::Voting::HaloType> type; // 0x1C
			Server::Voting::HaloMap map; // 0xF8
			_inline PlaylistItem(Server::Voting::PlaylistItem &&__that); /* compiler_generated() */
			_inline PlaylistItem(Server::Voting::PlaylistItem const &__that); /* compiler_generated() */
			_inline PlaylistItem() = default; /* compiler_generated() */
			_inline ~PlaylistItem(); /* compiler_generated() */
			Server::Voting::PlaylistItem &operator=(Server::Voting::PlaylistItem &); /* compiler_generated() */
			Server::Voting::PlaylistItem &operator=(Server::Voting::PlaylistItem const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Voting::PlaylistItem) == 376, "Invalid Server::Voting::PlaylistItem size");
	}
}

#pragma pack(push, 4)
namespace Server
{
	namespace Voting
	{
		struct MapAndType
		{
			Server::Voting::HaloMap haloMap; // 0x0
			Server::Voting::HaloType haloType; // 0x80
			__int32 Count; // 0x158
			__int32 index; // 0x15C
			bool canveto; // 0x160
			bool isRevoteOption; // 0x161
			bool isRematchOption; // 0x162
			_inline MapAndType(Server::Voting::MapAndType &&__that); /* compiler_generated() */
			_inline MapAndType(Server::Voting::MapAndType const &__that); /* compiler_generated() */
			_inline MapAndType(Server::Voting::HaloMap hm, Server::Voting::HaloType ht);
			_inline MapAndType();
			_inline bool operator<(Server::Voting::MapAndType const &val) const;
			_inline bool operator==(Server::Voting::MapAndType const &val) const;
			_inline ~MapAndType(); /* compiler_generated() */
			_inline Server::Voting::MapAndType &operator=(Server::Voting::MapAndType &&__that) noexcept; /* compiler_generated() */
			_inline Server::Voting::MapAndType &operator=(Server::Voting::MapAndType const &__that); /* compiler_generated() */
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Server::Voting::MapAndType) == 356, "Invalid Server::Voting::MapAndType size");

#pragma pack(push, 4)
namespace Server
{
	namespace Voting
	{
		struct SMapListItem
		{
			std::string name; // 0x0
			std::string displayName; // 0x1C
			__int32 mapId; // 0x38
			_inline SMapListItem(Server::Voting::SMapListItem &&__that); /* compiler_generated() */
			_inline SMapListItem(Server::Voting::SMapListItem const &__that); /* compiler_generated() */
			_inline SMapListItem() = default; /* compiler_generated() */
			_inline ~SMapListItem(); /* compiler_generated() */
			Server::Voting::SMapListItem &operator=(Server::Voting::SMapListItem &); /* compiler_generated() */
			_inline Server::Voting::SMapListItem &operator=(Server::Voting::SMapListItem const &__that); /* compiler_generated() */
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Server::Voting::SMapListItem) == 60, "Invalid Server::Voting::SMapListItem size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		_inline HaloMap::HaloMap() : mapId(-1), randomChance(0.1f) /* hades-mem-init:  */ // 0x1073A280
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0HaloMap@Voting@Server@@QAE@XZ");
			// Server::Voting::HaloMap *const this;
		}

		_inline void HaloMap::SetMembers(std::string sn, std::string m, std::string dn, std::string img, __int32 id, float rc, Server::Voting::AllowedPlayerCount apc) // 0x1073E880
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetMembers@HaloMap@Voting@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@000HMUAllowedPlayerCount@23@@Z");
			// Server::Voting::AllowedPlayerCount apc;

			scnrName = sn;
			mapName = m;
			if (dn.length() > 16)
				mapDisplayName = dn.substr(0, 16);
			else
				mapDisplayName = dn;
			mapId = id;
			imageUri = img;
			randomChance = rc;
			allowedPlayerCount = apc;
		}

		_inline HaloMap::HaloMap(std::string sn, std::string m, std::string dn, std::string img, __int32 id, float rc, Server::Voting::AllowedPlayerCount apc) : randomChance(0.1f) /* hades-mem-init:  */ // 0x1073A090
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0HaloMap@Voting@Server@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@000HMUAllowedPlayerCount@12@@Z");
			// Server::Voting::AllowedPlayerCount apc;

			SetMembers(sn, m, dn, img, id, rc, apc);
		}

		_inline HaloType::HaloType() : isTemplate(false), randomChance(0.1f) /* hades-mem-init:  */ // 0x10732C10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0HaloType@Voting@Server@@QAE@XZ");
			// Server::Voting::HaloType *const this;
		}

		_inline HaloType::HaloType(std::string t, std::string dn) : isTemplate(false), randomChance(0.1f) /* hades-mem-init:  */ // 0x1073A330
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0HaloType@Voting@Server@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// std::string dn;

			typeName = t;
			if (dn.length() > 16)
				typeDisplayName = dn.substr(0, 16);
			else
				typeDisplayName = dn;
		}

		_inline MapAndType::MapAndType() // 0x1073A7E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0MapAndType@Voting@Server@@QAE@XZ");
			// Server::Voting::MapAndType *const this;

			index = -1;
			canveto = false;
			isRevoteOption = false;
			isRematchOption = false;
			Count = 0;
		}

		_inline MapAndType::MapAndType(Server::Voting::HaloMap hm, Server::Voting::HaloType ht) // 0x1073A6A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0MapAndType@Voting@Server@@QAE@UHaloMap@12@UHaloType@12@@Z");
			// Server::Voting::HaloType ht;

			index = -1;
			canveto = false;
			isRevoteOption = false;
			isRematchOption = false;
			haloMap = hm;
			haloType = ht;
			Count = 0;
		}

		_inline bool MapAndType::operator<(Server::Voting::MapAndType const &val) const // 0x10C4D9E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??MMapAndType@Voting@Server@@QBE_NABU012@@Z");
			// Server::Voting::MapAndType const &val;

			return Count < val.Count;
		}

		_inline bool MapAndType::operator==(Server::Voting::MapAndType const &val) const // 0x10C4D880
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??8MapAndType@Voting@Server@@QBE_NABU012@@Z");
			// Server::Voting::MapAndType const &val;
			// Modules::ModuleVoting &votingModule;

			auto &votingModule = Modules::ModuleVoting::Instance();
			if (votingModule.VarServerVotingDuplicationLevel->ValueInt == 0)
				return haloMap.mapDisplayName == val.haloMap.mapDisplayName || haloType.typeDisplayName == val.haloType.typeDisplayName;
			else if (votingModule.VarServerVotingDuplicationLevel->ValueInt == 1)
				return haloMap.mapDisplayName == val.haloMap.mapDisplayName && haloType.typeDisplayName == val.haloType.typeDisplayName;
			else
				return false;
		}
	}
}

/* ---------- private code */

// hades: namespace-scope constants, so every file that includes this header gets its own copy
// and its own dynamic initialiser, as the original does (14 copies, one per including file).
namespace Server
{
	namespace Voting
	{
		std::string const DefaultTypes[8] = { "slayer", "team slayer", "multi flag", "team oddball", "oddball", "crazy king", "team king", "assault" };
		std::string const DefaultTypeNames[8] = { "Slayer", "Team Slayer", "Multi Flag", "Team Oddball", "FFA Oddball", "Crazy King", "Team King", "Assault" };
	}
}

#endif // __SERVER_VOTING_VOTINGTYPES_HPP__
