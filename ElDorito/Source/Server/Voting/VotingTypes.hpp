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
			_inline AllowedPlayerCount(); /* compiler_generated() */
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
			_inline HaloMap(Server::Voting::HaloMap &&__that); /* compiler_generated() */
			_inline HaloMap(Server::Voting::HaloMap const &__that); /* compiler_generated() */
			_inline HaloMap(std::string sn, std::string m, std::string dn, std::string img, __int32 id, float rc, Server::Voting::AllowedPlayerCount apc);
			_inline HaloMap();
			_inline void SetMembers(std::string sn, std::string m, std::string dn, std::string img, __int32 id, float rc, Server::Voting::AllowedPlayerCount apc);
			_inline ~HaloMap(); /* compiler_generated() */
			_inline Server::Voting::HaloMap &operator=(Server::Voting::HaloMap &&__that); /* compiler_generated() */
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
				CharacterOverride(CharacterOverride &); /* compiler_generated() */
				_inline CharacterOverride(CharacterOverride const &__that); /* compiler_generated() */
				_inline CharacterOverride(); /* compiler_generated() */
				_inline ~CharacterOverride(); /* compiler_generated() */
				_inline CharacterOverride &operator=(CharacterOverride &&__that); /* compiler_generated() */
				_inline CharacterOverride &operator=(CharacterOverride const &__that); /* compiler_generated() */
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
			_inline Server::Voting::HaloType &operator=(Server::Voting::HaloType &&__that); /* compiler_generated() */
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
			_inline PlaylistItem(); /* compiler_generated() */
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
			_inline Server::Voting::MapAndType &operator=(Server::Voting::MapAndType &&__that); /* compiler_generated() */
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
			_inline SMapListItem(); /* compiler_generated() */
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
		extern HaloMap* _sub_1073A280(Server::Voting::HaloMap *const);
		_inline HaloMap::HaloMap() // 0x1073A280
		{
			mangled_x86(MANGLED_TODO, "??0HaloMap@Voting@Server@@QAE@XZ");
			// Server::Voting::HaloMap *const this;
			todo("implement");
			_sub_1073A280(this);
		}

		_extern void _sub_1073E880(Server::Voting::HaloMap *const, std::string, std::string, std::string, std::string, __int32, float, Server::Voting::AllowedPlayerCount);
		_inline void HaloMap::SetMembers(std::string sn, std::string m, std::string dn, std::string img, __int32 id, float rc, Server::Voting::AllowedPlayerCount apc) // 0x1073E880
		{
			mangled_x86(MANGLED_TODO, "?SetMembers@HaloMap@Voting@Server@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@000HMUAllowedPlayerCount@23@@Z");
			// Server::Voting::AllowedPlayerCount apc;
			todo("implement");
			_sub_1073E880(this, sn, m, dn, img, id, rc, apc);
		}

		extern HaloMap* _sub_1073A090(Server::Voting::HaloMap *const, std::string, std::string, std::string, std::string, __int32, float, Server::Voting::AllowedPlayerCount);
		_inline HaloMap::HaloMap(std::string sn, std::string m, std::string dn, std::string img, __int32 id, float rc, Server::Voting::AllowedPlayerCount apc) // 0x1073A090
		{
			mangled_x86(MANGLED_TODO, "??0HaloMap@Voting@Server@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@000HMUAllowedPlayerCount@12@@Z");
			// Server::Voting::AllowedPlayerCount apc;
			todo("implement");
			_sub_1073A090(this, sn, m, dn, img, id, rc, apc);
		}

		extern HaloType* _sub_10732C10(Server::Voting::HaloType *const);
		_inline HaloType::HaloType() // 0x10732C10
		{
			mangled_x86(MANGLED_TODO, "??0HaloType@Voting@Server@@QAE@XZ");
			// Server::Voting::HaloType *const this;
			todo("implement");
			_sub_10732C10(this);
		}

		extern HaloType* _sub_1073A330(Server::Voting::HaloType *const, std::string, std::string);
		_inline HaloType::HaloType(std::string t, std::string dn) // 0x1073A330
		{
			mangled_x86(MANGLED_TODO, "??0HaloType@Voting@Server@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// std::string dn;
			todo("implement");
			_sub_1073A330(this, t, dn);
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

		_extern bool _sub_10C4D9E0(Server::Voting::MapAndType const *const, Server::Voting::MapAndType const &);
		_inline bool MapAndType::operator<(Server::Voting::MapAndType const &val) const // 0x10C4D9E0
		{
			mangled_x86(MANGLED_TODO, "??MMapAndType@Voting@Server@@QBE_NABU012@@Z");
			// Server::Voting::MapAndType const &val;
			todo("implement");
			bool __result = _sub_10C4D9E0((Server::Voting::MapAndType const *)this, val);
			return __result;
		}

		_extern bool _sub_10C4D880(Server::Voting::MapAndType const *const, Server::Voting::MapAndType const &);
		_inline bool MapAndType::operator==(Server::Voting::MapAndType const &val) const // 0x10C4D880
		{
			mangled_x86(MANGLED_TODO, "??8MapAndType@Voting@Server@@QBE_NABU012@@Z");
			// Server::Voting::MapAndType const &val;
			// Modules::ModuleVoting &votingModule;
			todo("implement");
			bool __result = _sub_10C4D880((Server::Voting::MapAndType const *)this, val);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __SERVER_VOTING_VOTINGTYPES_HPP__
