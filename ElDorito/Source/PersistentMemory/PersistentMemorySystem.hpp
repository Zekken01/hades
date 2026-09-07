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
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > player_name; // 0x0
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > player_uid; // 0x1C
			_inline SPersistantMute(SPersistantMute &&__that); /* compiler_generated() */
			_inline SPersistantMute(SPersistantMute const &__that); /* compiler_generated() */
			SPersistantMute(); /* compiler_generated() */
			_inline ~SPersistantMute(); /* compiler_generated() */
			_inline SPersistantMute &operator=(SPersistantMute &&__that); /* compiler_generated() */
			SPersistantMute &operator=(SPersistantMute const &); /* compiler_generated() */
		};
		static_assert(sizeof(SPersistantMute) == 56, "Invalid SPersistantMute size");
		public:
		__int32 lastMapID; // 0x0
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > lastAnnoucementViewedDate; // 0x4
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > lastMapName; // 0x20
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > lastGameType; // 0x3C
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > lastMultiplayerMod; // 0x58
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > lastCampaignMod; // 0x74
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > lastFirefightMod; // 0x90
		std::vector<SPersistantMute,std::allocator<SPersistantMute> > mutedVoipPlayers; // 0xAC
		_inline SPersistentMemoryDB(PersistentMemory::SPersistentMemoryDB &&__that); /* compiler_generated() */
		SPersistentMemoryDB(PersistentMemory::SPersistentMemoryDB const &); /* compiler_generated() */
		_inline SPersistentMemoryDB(); /* compiler_generated() */
		_inline ~SPersistentMemoryDB(); /* compiler_generated() */
		_inline PersistentMemory::SPersistentMemoryDB &operator=(PersistentMemory::SPersistentMemoryDB &&__that); /* compiler_generated() */
		PersistentMemory::SPersistentMemoryDB &operator=(PersistentMemory::SPersistentMemoryDB const &); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(PersistentMemory::SPersistentMemoryDB) == 188, "Invalid PersistentMemory::SPersistentMemoryDB size");

/* ---------- prototypes */

namespace PersistentMemory
{
	extern PersistentMemory::SPersistentMemoryDB LoadPersistentMemory(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern bool Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filename);
	extern void Save();
	extern void Init();
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastAnnoucementViewedDate();
	extern void SetLastAnnoucementViewedDate(std::basic_string<char,std::char_traits<char>,std::allocator<char> > annoucementViewedDate);
	extern __int32 GetLastMapID();
	extern void SetLastMapID(__int32 mapID);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastMapName();
	extern void SetLastMapName(std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapName);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastGameType();
	extern void SetLastGameType(std::basic_string<char,std::char_traits<char>,std::allocator<char> > gameType);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastMultiplayerMod();
	extern void SetLastMultiplayerMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > multiplayerMod);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastCampaignMod();
	extern void SetLastCampaignMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > campaignMod);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastFirefightMod();
	extern void SetLastFirefightMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > firefightMod);
	extern void AddMutedVoipPlayer(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid);
	extern bool RemoveMutedVoipPlayer(std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid);
	extern bool PlayerIsVoipMuted(std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PERSISTENTMEMORY_PERSISTENTMEMORYSYSTEM_HPP__
