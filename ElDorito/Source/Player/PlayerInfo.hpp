#ifndef __PLAYER_PLAYERINFO_HPP__
#define __PLAYER_PLAYERINFO_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Player
{
	struct CPlayersInfo;
}

/* ---------- constants */

/* ---------- definitions */

namespace Player
{
	struct CPlayersInfo
	{
		static bool IsAvailable();
		static __int32 GetRank(__int32 networkPlayerIndex);
		static __int32 GetSkill(__int32 networkPlayerIndex);
		static std::string GeEmblemUrl(__int32 networkPlayerIndex);
		static std::string GeneratePlayerInfo();
		static void Update(std::string const &payload);
		static void Init();
		static void Tick();
	};
	static_assert(sizeof(Player::CPlayersInfo) == 1, "Invalid Player::CPlayersInfo size");
}

/* ---------- prototypes */

namespace Player
{
	extern bool GetRankedUpRecently();
	extern void ClearRankUp();
	extern std::string getLocalEmblem(__int32 networkPlayerIndex);
	extern void LifeCycleStateChanged(Blam::Network::LifeCycleState newState);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERINFO_HPP__
