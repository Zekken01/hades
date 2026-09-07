#ifndef __PLAYER_PLAYEREMBLEMGENERATOR_HPP__
#define __PLAYER_PLAYEREMBLEMGENERATOR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/player_appearance.hpp"

#include <d3d9.h>

/* ---------- forward declarations */

struct s_player_emblem_configuration;
namespace Player
{
	namespace Emblems
	{
		struct e_emblem_color;
	}
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Player
{
	namespace Emblems
	{
		extern Player::Emblems::e_emblem_color HexToRgb(__int32 hexValue);
		extern bool CopyToGPUTexture(IDirect3DDevice9 *device, IDirect3DTexture9 *texture, IDirect3DTexture9 **outGpuTexture);
		extern _inline void ColorPixel(float *pixelDest, Player::Emblems::e_emblem_color color, float alpha);
		extern bool GenerateEmblem(IDirect3DTexture9 *destTexture, IDirect3DTexture9 *backgroundTexture, IDirect3DTexture9 *foregroundTexture, bool secondaryEnabled, Player::Emblems::e_emblem_color const &background, Player::Emblems::e_emblem_color const &primary, Player::Emblems::e_emblem_color const &secondary);
		extern Player::Emblems::e_emblem_color GetPrimaryColor(s_player_emblem_configuration const &config);
		extern Player::Emblems::e_emblem_color GetSecondaryColor(s_player_emblem_configuration const &config);
		extern Player::Emblems::e_emblem_color GetBackgroundColor(s_player_emblem_configuration const &config);
		extern bool GenerateEmblem(s_player_emblem_configuration const &emblem_config, IDirect3DTexture9 **outEmblem, bool forGPU);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYEREMBLEMGENERATOR_HPP__
