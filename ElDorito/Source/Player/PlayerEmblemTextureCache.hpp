#ifndef __PLAYER_PLAYEREMBLEMTEXTURECACHE_HPP__
#define __PLAYER_PLAYEREMBLEMTEXTURECACHE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Player/PlayerEmblemGenerator.hpp"

/* ---------- forward declarations */

namespace Player
{
	namespace Emblems
	{
		class PlayerEmblemTextureCache;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Player
{
	namespace Emblems
	{
		class PlayerEmblemTextureCache
		{
		public:
			static bool GetEmblemTexture(__int32 index, IDirect3DTexture9 **texture);
		};
		static_assert(sizeof(Player::Emblems::PlayerEmblemTextureCache) == 1, "Invalid Player::Emblems::PlayerEmblemTextureCache size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYEREMBLEMTEXTURECACHE_HPP__
