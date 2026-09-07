/* ---------- headers */

#include "Player/PlayerEmblemTextureCache.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <Windows.h>
#include <stdio.h>

/* ---------- forward declarations */

namespace Player
{
	namespace Emblems
	{
		class PlayerEmblemTextureCache;
	}
}
namespace hades_file_local
{
	struct CachedTexture;
}
using namespace hades_file_local;

namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct CachedTexture
	{
		bool valid; // 0x0
		unsigned char __pad0[3]; // 0x1
		IDirect3DTexture9 *texture; // 0x4
	};
	static_assert(sizeof(CachedTexture) == 8, "Invalid CachedTexture size");
}
using namespace hades_file_local;
/* ---------- prototypes */

bool LoadEmblemTexture(__int32 index, IDirect3DTexture9 **texture);
bool GetTextureInternal(__int32 index, IDirect3DTexture9 **texture);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	namespace Emblems
	{
		_extern bool _sub_107E9EC0(__int32, IDirect3DTexture9 **);
		bool PlayerEmblemTextureCache::GetEmblemTexture(__int32 index, IDirect3DTexture9 **texture) // 0x107E9EC0
		{
			mangled_x86(MANGLED_TODO, "?GetEmblemTexture@PlayerEmblemTextureCache@Emblems@Player@@SA_NHPAPAUIDirect3DTexture9@@@Z");
			// IDirect3DTexture9 **texture;
			todo("implement");
			bool __result = _sub_107E9EC0(index, texture);
			return __result;
		}
	}
}

/* ---------- private code */

_extern bool _sub_107E9FC0(__int32, IDirect3DTexture9 **);
bool LoadEmblemTexture(__int32 index, IDirect3DTexture9 **texture) // 0x107E9FC0
{
	// `anonymous-namespace'::LoadEmblemTexture
	// static ...; // 0x107EA084
	// static ...; // 0x107EA07C
	// __int32 index;
	// IDirect3DTexture9 **texture;
	// char path[260];
	todo("implement");
	bool __result = _sub_107E9FC0(index, texture);
	return __result;
}

_extern bool _sub_107E9F10(__int32, IDirect3DTexture9 **);
bool GetTextureInternal(__int32 index, IDirect3DTexture9 **texture) // 0x107E9F10
{
	// `anonymous-namespace'::GetTextureInternal
	// IDirect3DTexture9 **texture;
	// CachedTexture &cachedTexture;
	todo("implement");
	bool __result = _sub_107E9F10(index, texture);
	return __result;
}
