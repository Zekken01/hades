#ifndef __PLAYER_PLAYERSERVICERECORD_HPP__
#define __PLAYER_PLAYERSERVICERECORD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Player
{
	namespace ServiceRecord
	{
		struct PlayerTopMedals;
		struct ServiceRecord;
		struct ServiceRecordPlayer;
	}
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Player
{
	namespace ServiceRecord
	{
		struct PlayerTopMedals
		{
			__int32 id = 0; // 0x0
			__int32 count = 0; // 0x4
			std::wstring countStr = L""; // 0x8
			// hades: no declared special members - an aggregate, as __call_empty_init_list_helper shows
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Player::ServiceRecord::PlayerTopMedals) == 36, "Invalid Player::ServiceRecord::PlayerTopMedals size");

namespace Player
{
	namespace ServiceRecord
	{
		struct ServiceRecord
		{
			__int32 playerId = -1; // 0x0
			std::string name = ""; // 0x4
			unsigned long long uid; // 0x20
			bool Empty = false; // 0x28
			__int32 exp = 0; // 0x2C
			__int32 skill = 0; // 0x30
			__int32 games = 0; // 0x34
			__int32 wins = 0; // 0x38
			__int32 kills = 0; // 0x3C
			__int32 deaths = 0; // 0x40
			__int32 medals = 0; // 0x44
			__int32 best_streak = 0; // 0x48
			__int32 ranked_matches = 0; // 0x4C
			__int32 social_matches = 0; // 0x50
			__int32 custom_games = 0; // 0x54
			PlayerTopMedals top_medals[8]; // 0x58
			// ServiceRecord(ServiceRecord &); /* compiler_generated() */ hades: implicit, the type is an aggregate
			// _inline ServiceRecord(ServiceRecord const &__that); /* compiler_generated() */ hades: implicit
			// _inline ServiceRecord() = default; /* compiler_generated() */ hades: implicit
			// _inline ~ServiceRecord(); /* compiler_generated() */ hades: implicit
			// _inline ServiceRecord &operator=(ServiceRecord &&__that); /* compiler_generated() */ hades: implicit
			// _inline ServiceRecord &operator=(ServiceRecord const &__that); /* compiler_generated() */ hades: implicit
			public:
			unsigned long __stdcall GetServiceRecord_Thread(void *lpParam);
			ServiceRecord getCachedServiceRecord(__int32 networkPlayerIndex);
			void clearCache();
			void requestPlayerServiceRecord(__int32 networkPlayerIndex);
		};
		static_assert(sizeof(Player::ServiceRecord::ServiceRecord) == 376, "Invalid Player::ServiceRecord::ServiceRecord size");
		static_assert(offsetof(Player::ServiceRecord::ServiceRecord, exp) == 0x2C, "Player::ServiceRecord::ServiceRecord::exp moved when its reconstructed padding was removed");

		struct ServiceRecordPlayer
		{
			wchar_t name[16]; // 0x0
			unsigned long long uid; // 0x20
			__int32 networkPlayerIndex = -1; // 0x28
			// _inline ServiceRecordPlayer(); /* compiler_generated() */  // hades: implicit, so `= {}` is aggregate initialization (0x106CAB50)
		};
		static_assert(sizeof(Player::ServiceRecord::ServiceRecordPlayer) == 48, "Invalid Player::ServiceRecord::ServiceRecordPlayer size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERSERVICERECORD_HPP__
