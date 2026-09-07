#ifndef __PLAYER_PLAYERCUSTOMIZATION_HPP__
#define __PLAYER_PLAYERCUSTOMIZATION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/player_configuration.hpp"
#include "Player/PlayerCharacterSystem.hpp"

/* ---------- forward declarations */

struct s_player_identifier;
struct s_player_model_customization;
namespace Player
{
	struct CPlayerCustomization;
}

/* ---------- constants */

/* ---------- definitions */

namespace Player
{
	struct CPlayerCustomization
	{
		static unsigned __int32 GetPlayerPrimaryColor(signed char networkPlayerIndex);
		static s_player_model_customization const *GetInGamePlayerCustomization(__int32 playerIndex);
	};
	static_assert(sizeof(Player::CPlayerCustomization) == 1, "Invalid Player::CPlayerCustomization size");
}

/* ---------- prototypes */

namespace Player
{
	extern __int32 FindPlayerInGameWithIdentifier(s_player_identifier const &identifier);
	extern s_player_model_customization const *GetDefaultCharacterCustomization(__int32 playerIndex, __int32 characterIndex);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERCUSTOMIZATION_HPP__
