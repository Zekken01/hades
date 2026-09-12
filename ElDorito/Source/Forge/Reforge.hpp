#ifndef __FORGE_REFORGE_HPP__
#define __FORGE_REFORGE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"

/* ---------- forward declarations */

namespace Forge
{
	struct ReforgeObjectProperties;
}
namespace Forge
{
	namespace Reforge
	{
		struct SRenderMaterialParameters;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	namespace Reforge
	{
		struct SRenderMaterialParameters
		{
			bool customTextureMode; // 0x0
			float textureScale; // 0x4
			float textureOffsetU; // 0x8
			float textureOffsetV; // 0xC
		};
		static_assert(sizeof(Forge::Reforge::SRenderMaterialParameters) == 16, "Invalid Forge::Reforge::SRenderMaterialParameters size");
		static_assert(offsetof(Forge::Reforge::SRenderMaterialParameters, textureScale) == 0x4, "Forge::Reforge::SRenderMaterialParameters::textureScale moved when its reconstructed padding was removed");
	}
}

/* ---------- prototypes */

namespace Forge
{
	namespace Reforge
	{
		extern void InitializeForNewMap();
		extern bool IsReforgeObject(long objectIndex);
		extern bool IsForgeScenery(long objectIndex);
		extern Forge::ReforgeObjectProperties *GetReforgeObject(long objectIndex);
		extern bool IsMapModifierObject(long objectIndex);
		extern bool IsGarbageCollectionObject(long objectIndex);
		extern bool IsKillVolumeObject(long objectIndex);
		extern bool IsPrematchCameraObject(long objectIndex);
		extern bool IsPodiumPointObject(long objectIndex);
		extern bool IsActiveTeamBarrierObject(long objectIndex);
		extern bool TeamBarrierTestPlayer(long barrierObjectIndex, long playerIndex);
		extern bool TeamBarrierTestUnit(long barrierObjectIndex, long unitIndex);
		extern bool ValidRenderMaterialIndex(long objectIndex, __int32 index);
		extern short GetRenderMaterialOverride(long objectIndex, Forge::Reforge::SRenderMaterialParameters *parameters);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_REFORGE_HPP__
