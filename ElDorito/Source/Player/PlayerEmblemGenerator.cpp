/* ---------- headers */

#include "Player/PlayerEmblemGenerator.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/player_appearance.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include "Player/PlayerEmblemTextureCache.hpp"  // hades: added for 0x1090C8C0

#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <ios>
#include <limits>
#include <stdexcept>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct _D3DLOCKED_RECT;
struct s_player_emblem_configuration;
namespace Player
{
	namespace Emblems
	{
		struct e_emblem_color;
	}
}

namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

/* ---------- constants */

/* ---------- definitions */

// Player::Emblems::e_emblem_color is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

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

namespace Player
{
	namespace Emblems
	{
		Player::Emblems::e_emblem_color steel = Player::Emblems::e_emblem_color{ 0x65, 0x65, 0x65 }; // 0x1240928C
		Player::Emblems::e_emblem_color silver = Player::Emblems::e_emblem_color{ 0xb1, 0xb1, 0xb1 }; // 0x12409274
		Player::Emblems::e_emblem_color white = Player::Emblems::e_emblem_color{ 0xde, 0xde, 0xde }; // 0x124092A0
		Player::Emblems::e_emblem_color red = Player::Emblems::e_emblem_color{ 0x9c, 0x34, 0x33 }; // 0x124092BC
		Player::Emblems::e_emblem_color mauve = Player::Emblems::e_emblem_color{ 0xdb, 0x6b, 0x6a }; // 0x12409298
		Player::Emblems::e_emblem_color salmon = Player::Emblems::e_emblem_color{ 0xef, 0x83, 0x83 }; // 0x124092C8
		Player::Emblems::e_emblem_color orange = Player::Emblems::e_emblem_color{ 0xda, 0x8e, 0x7 }; // 0x124092C4
		Player::Emblems::e_emblem_color coral = Player::Emblems::e_emblem_color{ 0xf7, 0xaf, 0x5b }; // 0x124092E4
		Player::Emblems::e_emblem_color peach = Player::Emblems::e_emblem_color{ 0xfe, 0xcb, 0xa0 }; // 0x12409290
		Player::Emblems::e_emblem_color gold = Player::Emblems::e_emblem_color{ 0xcd, 0xae, 0x31 }; // 0x12409270
		Player::Emblems::e_emblem_color yellow = Player::Emblems::e_emblem_color{ 0xf1, 0xbe, 0x31 }; // 0x124092B4
		Player::Emblems::e_emblem_color pale = Player::Emblems::e_emblem_color{ 0xfb, 0xd8, 0x7e }; // 0x1240927C
		Player::Emblems::e_emblem_color sage = Player::Emblems::e_emblem_color{ 0x5d, 0x77, 0x20 }; // 0x124092C0
		Player::Emblems::e_emblem_color green = Player::Emblems::e_emblem_color{ 0x92, 0xa7, 0x64 }; // 0x124092D0
		Player::Emblems::e_emblem_color olive = Player::Emblems::e_emblem_color{ 0xd9, 0xf0, 0xa8 }; // 0x12409294
		Player::Emblems::e_emblem_color teal = Player::Emblems::e_emblem_color{ 0x36, 0x7b, 0x80 }; // 0x124092AC
		Player::Emblems::e_emblem_color aqua = Player::Emblems::e_emblem_color{ 0x4d, 0xbd, 0xc1 }; // 0x124092D8
		Player::Emblems::e_emblem_color cyan = Player::Emblems::e_emblem_color{ 0x92, 0xec, 0xec }; // 0x124092B8
		Player::Emblems::e_emblem_color blue = Player::Emblems::e_emblem_color{ 0x38, 0x5d, 0x94 }; // 0x124092CC
		Player::Emblems::e_emblem_color cobalt = Player::Emblems::e_emblem_color{ 0x59, 0x8a, 0xd9 }; // 0x12409284
		Player::Emblems::e_emblem_color sapphire = Player::Emblems::e_emblem_color{ 0x9a, 0xb7, 0xf3 }; // 0x12409278
		Player::Emblems::e_emblem_color violet = Player::Emblems::e_emblem_color{ 0x59, 0x42, 0x92 }; // 0x1240929C
		Player::Emblems::e_emblem_color orchid = Player::Emblems::e_emblem_color{ 0x93, 0x77, 0xe5 }; // 0x124092E0
		Player::Emblems::e_emblem_color lavendar = Player::Emblems::e_emblem_color{ 0xc5, 0xb5, 0xfc }; // 0x124092D4
		Player::Emblems::e_emblem_color crimson = Player::Emblems::e_emblem_color{ 0x85, 0x6, 0x4b }; // 0x124092A4
		Player::Emblems::e_emblem_color rubine = Player::Emblems::e_emblem_color{ 0xd2, 0x41, 0x86 }; // 0x124092A8
		Player::Emblems::e_emblem_color pink = Player::Emblems::e_emblem_color{ 0xfd, 0x8d, 0xbb }; // 0x124092B0
		Player::Emblems::e_emblem_color brown = Player::Emblems::e_emblem_color{ 0x55, 0x3b, 0x1a }; // 0x124092DC
		Player::Emblems::e_emblem_color tan = Player::Emblems::e_emblem_color{ 0xac, 0x8d, 0x70 }; // 0x12409288
		Player::Emblems::e_emblem_color khaki = Player::Emblems::e_emblem_color{ 0xe1, 0xbf, 0xa3 }; // 0x12409280
		Player::Emblems::e_emblem_color color_list[30] = { steel, silver, white, red, mauve, salmon, orange, coral, peach, gold, yellow, pale, sage, green, olive, teal, aqua, cyan, blue, cobalt, sapphire, violet, orchid, lavendar, crimson, rubine, pink, brown, tan, khaki }; // 0x124092E8
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	namespace Emblems
	{
		Player::Emblems::e_emblem_color HexToRgb(__int32 hexValue) // 0x1090D570
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HexToRgb@Emblems@Player@@YA?AUe_emblem_color@12@H@Z");
			// static ...; // 0x1090D5F4
			// static ...; // 0x1090D5E8
			// static ...; // 0x1090D5E0
			// __int32 hexValue;
			// Player::Emblems::e_emblem_color color;

			Player::Emblems::e_emblem_color color;
			color.red = (hexValue >> 16) & 0xFF;
			color.green = (hexValue >> 8) & 0xFF;
			color.blue = hexValue & 0xFF;
			return color;
		}

		bool CopyToGPUTexture(IDirect3DDevice9 *device, IDirect3DTexture9 *texture, IDirect3DTexture9 **outGpuTexture) // 0x1090C790
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CopyToGPUTexture@Emblems@Player@@YA_NPAUIDirect3DDevice9@@PAUIDirect3DTexture9@@PAPAU4@@Z");
			// static ...; // 0x1090C864
			// IDirect3DDevice9 *device;
			// IDirect3DTexture9 *texture;
			// IDirect3DTexture9 **outGpuTexture;
			// IDirect3DTexture9 *gpuTexture;
			// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
			// function call : HRESULT (IDirect3DBaseTexture9 *, IDirect3DBaseTexture9 *)
			// function call : unsigned long ()

			IDirect3DTexture9 *gpuTexture;

			if (device->CreateTexture(128, 128, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &gpuTexture, nullptr) != D3D_OK)
			{
				return false;
			}

			if (device->UpdateTexture(texture, gpuTexture) != D3D_OK)
			{
				gpuTexture->Release();
				return false;
			}

			*outGpuTexture = gpuTexture;
			return true;
		}

		_inline void ColorPixel(float *pixelDest, Player::Emblems::e_emblem_color color, float alpha) // 0x1090C5E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ColorPixel@Emblems@Player@@YAXPAMUe_emblem_color@12@M@Z");
			// float alpha;
			// float final_a;
			// float dest_a;

			float dest_a = pixelDest[3];
			float final_a = alpha + dest_a - dest_a * alpha;
			pixelDest[0] = (color.blue / 255.0f * alpha + pixelDest[0] * dest_a * (1.0f - alpha)) / final_a;
			pixelDest[1] = (color.green / 255.0f * alpha + pixelDest[1] * dest_a * (1.0f - alpha)) / final_a;
			pixelDest[2] = (color.red / 255.0f * alpha + pixelDest[2] * dest_a * (1.0f - alpha)) / final_a;
			pixelDest[3] = final_a;
		}

		bool GenerateEmblem(IDirect3DTexture9 *destTexture, IDirect3DTexture9 *backgroundTexture, IDirect3DTexture9 *foregroundTexture, bool secondaryEnabled, Player::Emblems::e_emblem_color const &background, Player::Emblems::e_emblem_color const &primary, Player::Emblems::e_emblem_color const &secondary) // 0x1090CBB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateEmblem@Emblems@Player@@YA_NPAUIDirect3DTexture9@@00_NABUe_emblem_color@12@22@Z");
			// static ...; // 0x1090D078
			// IDirect3DTexture9 *destTexture;
			// IDirect3DTexture9 *backgroundTexture;
			// IDirect3DTexture9 *foregroundTexture;
			// bool secondaryEnabled;
			// Player::Emblems::e_emblem_color const &background;
			// Player::Emblems::e_emblem_color const &primary;
			// Player::Emblems::e_emblem_color const &secondary;
			// _D3DLOCKED_RECT lockedDest;
			// bool result;
				// _D3DLOCKED_RECT bgLockedSrc;
					// unsigned char *bgPixelsSrc;
					// _D3DLOCKED_RECT fgLockedSrc;
					// bool reuseTexture;
					// unsigned char *fgPixelsSrc;
						// unsigned char *pixelsDest;
							// __int32 i;
								// unsigned char *bgPixelSrc;
								// unsigned char *fgPixelSrc;
								// float decPixelDest[4];
								// unsigned char *pixelDest;
			// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
			// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
			// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
			// function call : HRESULT (unsigned __int32)
			// function call : HRESULT (unsigned __int32)
			// function call : HRESULT (unsigned __int32)

			bool result = false;
			D3DLOCKED_RECT lockedDest;
			if (SUCCEEDED(destTexture->LockRect(0, &lockedDest, nullptr, 0)))
			{
				D3DLOCKED_RECT bgLockedSrc;
				if (SUCCEEDED(backgroundTexture->LockRect(0, &bgLockedSrc, nullptr, 0)))
				{
					unsigned char *bgPixelsSrc = (unsigned char *)bgLockedSrc.pBits;
					unsigned char *fgPixelsSrc;
					bool reuseTexture = false;
					D3DLOCKED_RECT fgLockedSrc;
					if (backgroundTexture == foregroundTexture)
					{
						reuseTexture = true;
						fgPixelsSrc = bgPixelsSrc;
					}
					if (reuseTexture || SUCCEEDED(foregroundTexture->LockRect(0, &fgLockedSrc, nullptr, 0)))
					{
						unsigned char *pixelsDest = (unsigned char *)lockedDest.pBits;
						if (!reuseTexture)
							fgPixelsSrc = (unsigned char *)fgLockedSrc.pBits;
						for (__int32 i = 0; i < 128 * 128; i++)
						{
							unsigned char *pixelDest = &pixelsDest[i * 4];
							unsigned char *bgPixelSrc = &bgPixelsSrc[i * 4];
							unsigned char *fgPixelSrc = &fgPixelsSrc[i * 4];
							if (bgPixelSrc[0])
							{
								pixelDest[0] = background.blue;
								pixelDest[1] = background.green;
								pixelDest[2] = background.red;
								pixelDest[3] = bgPixelSrc[0];
							}
							float decPixelDest[4] = { pixelDest[0] / 255.0f, pixelDest[1] / 255.0f, pixelDest[2] / 255.0f, pixelDest[3] / 255.0f };
							if (fgPixelSrc[1])
								ColorPixel(decPixelDest, primary, fgPixelSrc[1] / 240.0f);
							if (fgPixelSrc[2] && secondaryEnabled)
								ColorPixel(decPixelDest, secondary, fgPixelSrc[2] / 240.0f);
							pixelDest[0] = (unsigned char)(decPixelDest[0] * 255.0f);
							pixelDest[1] = (unsigned char)(decPixelDest[1] * 255.0f);
							pixelDest[2] = (unsigned char)(decPixelDest[2] * 255.0f);
							pixelDest[3] = (unsigned char)(decPixelDest[3] * 255.0f);
						}
						result = true;
						if (!reuseTexture)
							foregroundTexture->UnlockRect(0);
					}
					backgroundTexture->UnlockRect(0);
				}
				destTexture->UnlockRect(0);
			}
			return result;
		}

		Player::Emblems::e_emblem_color GetPrimaryColor(s_player_emblem_configuration const &config) // 0x1090D350
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPrimaryColor@Emblems@Player@@YA?AUe_emblem_color@12@ABUs_player_emblem_configuration@@@Z");
			// s_player_emblem_configuration const &config;

			return config.primaryHex ? Player::Emblems::HexToRgb(config.primaryColor) : color_list[config.primaryColor];
		}

		Player::Emblems::e_emblem_color GetSecondaryColor(s_player_emblem_configuration const &config) // 0x1090D460
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetSecondaryColor@Emblems@Player@@YA?AUe_emblem_color@12@ABUs_player_emblem_configuration@@@Z");
			// s_player_emblem_configuration const &config;

			return config.secondaryHex ? Player::Emblems::HexToRgb(config.secondaryColor) : Player::Emblems::color_list[config.secondaryColor];
		}

		Player::Emblems::e_emblem_color GetBackgroundColor(s_player_emblem_configuration const &config) // 0x1090D240
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetBackgroundColor@Emblems@Player@@YA?AUe_emblem_color@12@ABUs_player_emblem_configuration@@@Z");
			// s_player_emblem_configuration const &config;

			return config.backgroundHex ? Player::Emblems::HexToRgb(config.backgroundColor) : Player::Emblems::color_list[config.backgroundColor];
		}

		bool GenerateEmblem(s_player_emblem_configuration const &emblem_config, IDirect3DTexture9 **outEmblem, bool forGPU) // 0x1090C8C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateEmblem@Emblems@Player@@YA_NABUs_player_emblem_configuration@@PAPAUIDirect3DTexture9@@_N@Z");
			// static ...; // 0x1090CAE4
			// static ...; // 0x1090CAC0
			// static ...; // 0x1090CAB8
			// s_player_emblem_configuration const &emblem_config;
			// IDirect3DTexture9 **outEmblem;
			// bool forGPU;
			// IDirect3DDevice9Ex *device;
			// IDirect3DTexture9 *texture;
				// IDirect3DTexture9 *backgroundTexture;
				// IDirect3DTexture9 *foregroundTexture;
					// bool result;
			// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
			// function call : unsigned long ()
			// function call : unsigned long ()

			if (emblem_config.foregroundIndex > 185 || emblem_config.backgroundIndex > 52)
				return false;
			IDirect3DDevice9Ex *device = c_rasterizer::get_device();
			IDirect3DTexture9 *texture;
			if (device->CreateTexture(128, 128, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &texture, nullptr) == D3D_OK)
			{
				IDirect3DTexture9 *backgroundTexture;
				IDirect3DTexture9 *foregroundTexture;
				if (PlayerEmblemTextureCache::GetEmblemTexture(emblem_config.backgroundIndex, &backgroundTexture) && PlayerEmblemTextureCache::GetEmblemTexture(emblem_config.foregroundIndex, &foregroundTexture) && GenerateEmblem(texture, backgroundTexture, foregroundTexture, emblem_config.iconEnabled, GetBackgroundColor(emblem_config), GetPrimaryColor(emblem_config), GetSecondaryColor(emblem_config)))
				{
					if (forGPU)
					{
						bool result = CopyToGPUTexture(device, texture, outEmblem);
						texture->Release();
						return result;
					}
					else
					{
						*outEmblem = texture;
						return true;
					}
				}
				texture->Release();
			}
			return false;
		}
	}
}

/* ---------- private code */
