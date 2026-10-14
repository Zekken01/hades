#ifndef __PERSISTENTMEMORY_PERSISTENTMEMORYSYSTEM_HPP__
#define __PERSISTENTMEMORY_PERSISTENTMEMORYSYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Prefab.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/stream.h"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace PersistentMemory
{
	struct SPersistentMemoryDB;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace PersistentMemory
{
	struct SPersistentMemoryDB
	{
		public:
		struct SPersistantMute
		{
			std::string player_name; // 0x0
			std::string player_uid; // 0x1C
			// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
			// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
			// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
			// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
			// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
			// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
		};
		static_assert(sizeof(SPersistantMute) == 56, "Invalid SPersistantMute size");
		public:
		__int32 lastMapID = 30; // 0x0
		std::string lastAnnoucementViewedDate = ""; // 0x4
		std::string lastMapName = ""; // 0x20
		std::string lastGameType = ""; // 0x3C
		std::string lastMultiplayerMod = ""; // 0x58
		std::string lastCampaignMod = ""; // 0x74
		std::string lastFirefightMod = ""; // 0x90
		std::vector<SPersistantMute> mutedVoipPlayers; // 0xAC
		// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
		// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
		// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
		// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
		// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
		// hades: special members left implicit (aggregate init and noexcept moves in LoadPersistentMemory/Load/Add/RemoveMutedVoipPlayer)
	};
}

#pragma pack(pop)
static_assert(sizeof(PersistentMemory::SPersistentMemoryDB) == 188, "Invalid PersistentMemory::SPersistentMemoryDB size");

/* ---------- prototypes */

namespace PersistentMemory
{
	extern PersistentMemory::SPersistentMemoryDB LoadPersistentMemory(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern bool Load(std::string const &filename);
	extern void Save();
	extern void Init();
	extern std::string GetLastAnnoucementViewedDate();
	extern void SetLastAnnoucementViewedDate(std::string annoucementViewedDate);
	extern __int32 GetLastMapID();
	extern void SetLastMapID(__int32 mapID);
	extern std::string GetLastMapName();
	extern void SetLastMapName(std::string mapName);
	extern std::string GetLastGameType();
	extern void SetLastGameType(std::string gameType);
	extern std::string GetLastMultiplayerMod();
	extern void SetLastMultiplayerMod(std::string multiplayerMod);
	extern std::string GetLastCampaignMod();
	extern void SetLastCampaignMod(std::string campaignMod);
	extern std::string GetLastFirefightMod();
	extern void SetLastFirefightMod(std::string firefightMod);
	extern void AddMutedVoipPlayer(std::string name, std::string uid);
	extern bool RemoveMutedVoipPlayer(std::string uid);
	extern bool PlayerIsVoipMuted(std::string uid);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PERSISTENTMEMORY_PERSISTENTMEMORYSYSTEM_HPP__
