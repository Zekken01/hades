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
			__int32 id; // 0x0
			__int32 count; // 0x4
			std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > countStr; // 0x8
			PlayerTopMedals(Player::ServiceRecord::PlayerTopMedals &); /* compiler_generated() */
			_inline PlayerTopMedals(Player::ServiceRecord::PlayerTopMedals const &__that); /* compiler_generated() */
			_inline PlayerTopMedals(); /* compiler_generated() */
			_inline ~PlayerTopMedals(); /* compiler_generated() */
			_inline Player::ServiceRecord::PlayerTopMedals &operator=(Player::ServiceRecord::PlayerTopMedals &&__that); /* compiler_generated() */
			_inline Player::ServiceRecord::PlayerTopMedals &operator=(Player::ServiceRecord::PlayerTopMedals const &__that); /* compiler_generated() */
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
			__int32 playerId; // 0x0
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > name; // 0x4
			unsigned long long uid; // 0x20
			bool Empty; // 0x28
			unsigned char __pad0[3]; // 0x29
			__int32 exp; // 0x2C
			__int32 skill; // 0x30
			__int32 games; // 0x34
			__int32 wins; // 0x38
			__int32 kills; // 0x3C
			__int32 deaths; // 0x40
			__int32 medals; // 0x44
			__int32 best_streak; // 0x48
			__int32 ranked_matches; // 0x4C
			__int32 social_matches; // 0x50
			__int32 custom_games; // 0x54
			PlayerTopMedals top_medals[8]; // 0x58
			ServiceRecord(ServiceRecord &); /* compiler_generated() */
			_inline ServiceRecord(ServiceRecord const &__that); /* compiler_generated() */
			_inline ServiceRecord(); /* compiler_generated() */
			_inline ~ServiceRecord(); /* compiler_generated() */
			_inline ServiceRecord &operator=(ServiceRecord &&__that); /* compiler_generated() */
			_inline ServiceRecord &operator=(ServiceRecord const &__that); /* compiler_generated() */
			public:
			unsigned long __stdcall GetServiceRecord_Thread(void *lpParam);
			ServiceRecord getCachedServiceRecord(__int32 networkPlayerIndex);
			void clearCache();
			void requestPlayerServiceRecord(__int32 networkPlayerIndex);
		};
		static_assert(sizeof(Player::ServiceRecord::ServiceRecord) == 376, "Invalid Player::ServiceRecord::ServiceRecord size");

		struct ServiceRecordPlayer
		{
			wchar_t name[16]; // 0x0
			unsigned long long uid; // 0x20
			__int32 networkPlayerIndex; // 0x28
			_inline ServiceRecordPlayer(); /* compiler_generated() */
			unsigned char __pad0[4]; // 0x2C
		};
		static_assert(sizeof(Player::ServiceRecord::ServiceRecordPlayer) == 48, "Invalid Player::ServiceRecord::ServiceRecordPlayer size");
	}
}

/* ---------- prototypes */

namespace Player
{
	namespace ServiceRecord
	{
		extern unsigned long __stdcall GetServiceRecord_Thread(void *lpParam);
		extern Player::ServiceRecord::ServiceRecord getCachedServiceRecord(__int32 networkPlayerIndex);
		extern void clearCache();
		extern void requestPlayerServiceRecord(__int32 networkPlayerIndex);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERSERVICERECORD_HPP__
