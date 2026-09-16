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
		extern Player::Emblems::e_emblem_color steel; // 0x1240928C
		extern Player::Emblems::e_emblem_color silver; // 0x12409274
		extern Player::Emblems::e_emblem_color white; // 0x124092A0
		extern Player::Emblems::e_emblem_color red; // 0x124092BC
		extern Player::Emblems::e_emblem_color mauve; // 0x12409298
		extern Player::Emblems::e_emblem_color salmon; // 0x124092C8
		extern Player::Emblems::e_emblem_color orange; // 0x124092C4
		extern Player::Emblems::e_emblem_color coral; // 0x124092E4
		extern Player::Emblems::e_emblem_color peach; // 0x12409290
		extern Player::Emblems::e_emblem_color gold; // 0x12409270
		extern Player::Emblems::e_emblem_color yellow; // 0x124092B4
		extern Player::Emblems::e_emblem_color pale; // 0x1240927C
		extern Player::Emblems::e_emblem_color sage; // 0x124092C0
		extern Player::Emblems::e_emblem_color green; // 0x124092D0
		extern Player::Emblems::e_emblem_color olive; // 0x12409294
		extern Player::Emblems::e_emblem_color teal; // 0x124092AC
		extern Player::Emblems::e_emblem_color aqua; // 0x124092D8
		extern Player::Emblems::e_emblem_color cyan; // 0x124092B8
		extern Player::Emblems::e_emblem_color blue; // 0x124092CC
		extern Player::Emblems::e_emblem_color cobalt; // 0x12409284
		extern Player::Emblems::e_emblem_color sapphire; // 0x12409278
		extern Player::Emblems::e_emblem_color violet; // 0x1240929C
		extern Player::Emblems::e_emblem_color orchid; // 0x124092E0
		extern Player::Emblems::e_emblem_color lavendar; // 0x124092D4
		extern Player::Emblems::e_emblem_color crimson; // 0x124092A4
		extern Player::Emblems::e_emblem_color rubine; // 0x124092A8
		extern Player::Emblems::e_emblem_color pink; // 0x124092B0
		extern Player::Emblems::e_emblem_color brown; // 0x124092DC
		extern Player::Emblems::e_emblem_color tan; // 0x12409288
		extern Player::Emblems::e_emblem_color khaki; // 0x12409280
		extern Player::Emblems::e_emblem_color color_list[30]; // 0x124092E8
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

		_extern void _sub_1090C5E0(float *, Player::Emblems::e_emblem_color, float);
		_inline void ColorPixel(float *pixelDest, Player::Emblems::e_emblem_color color, float alpha) // 0x1090C5E0
		{
			mangled_x86(MANGLED_TODO, "?ColorPixel@Emblems@Player@@YAXPAMUe_emblem_color@12@M@Z");
			// float alpha;
			// float final_a;
			// float dest_a;
			todo("implement");
			_sub_1090C5E0(pixelDest, color, alpha);
		}

		_extern bool _sub_1090CBB0(IDirect3DTexture9 *, IDirect3DTexture9 *, IDirect3DTexture9 *, bool, Player::Emblems::e_emblem_color const &, Player::Emblems::e_emblem_color const &, Player::Emblems::e_emblem_color const &);
		bool GenerateEmblem(IDirect3DTexture9 *destTexture, IDirect3DTexture9 *backgroundTexture, IDirect3DTexture9 *foregroundTexture, bool secondaryEnabled, Player::Emblems::e_emblem_color const &background, Player::Emblems::e_emblem_color const &primary, Player::Emblems::e_emblem_color const &secondary) // 0x1090CBB0
		{
			mangled_x86(MANGLED_TODO, "?GenerateEmblem@Emblems@Player@@YA_NPAUIDirect3DTexture9@@00_NABUe_emblem_color@12@22@Z");
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
			{
				// _D3DLOCKED_RECT bgLockedSrc;
				{
					// unsigned char *bgPixelsSrc;
					// _D3DLOCKED_RECT fgLockedSrc;
					// bool reuseTexture;
					// unsigned char *fgPixelsSrc;
					{
						// unsigned char *pixelsDest;
						{
							// __int32 i;
							{
								// unsigned char *bgPixelSrc;
								// unsigned char *fgPixelSrc;
								// float decPixelDest[4];
								// unsigned char *pixelDest;
							}
						}
					}
				}
			}
			// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
			// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
			// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
			// function call : HRESULT (unsigned __int32)
			// function call : HRESULT (unsigned __int32)
			// function call : HRESULT (unsigned __int32)
			todo("implement");
			bool __result = _sub_1090CBB0(destTexture, backgroundTexture, foregroundTexture, secondaryEnabled, background, primary, secondary);
			return __result;
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

		_extern bool _sub_1090C8C0(s_player_emblem_configuration const &, IDirect3DTexture9 **, bool);
		bool GenerateEmblem(s_player_emblem_configuration const &emblem_config, IDirect3DTexture9 **outEmblem, bool forGPU) // 0x1090C8C0
		{
			mangled_x86(MANGLED_TODO, "?GenerateEmblem@Emblems@Player@@YA_NABUs_player_emblem_configuration@@PAPAUIDirect3DTexture9@@_N@Z");
			// static ...; // 0x1090CAE4
			// static ...; // 0x1090CAC0
			// static ...; // 0x1090CAB8
			// s_player_emblem_configuration const &emblem_config;
			// IDirect3DTexture9 **outEmblem;
			// bool forGPU;
			// IDirect3DDevice9Ex *device;
			// IDirect3DTexture9 *texture;
			{
				// IDirect3DTexture9 *backgroundTexture;
				// IDirect3DTexture9 *foregroundTexture;
				{
					// bool result;
				}
			}
			// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
			// function call : unsigned long ()
			// function call : unsigned long ()
			todo("implement");
			bool __result = _sub_1090C8C0(emblem_config, outEmblem, forGPU);
			return __result;
		}
	}
}

/* ---------- private code */
