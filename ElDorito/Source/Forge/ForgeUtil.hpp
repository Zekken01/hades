#ifndef __FORGE_FORGEUTIL_HPP__
#define __FORGE_FORGEUTIL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Forge/Geoemetry.hpp"
#include "mods/map_variant_loader.hpp"

/* ---------- forward declarations */

struct real_point3d;
struct real_rectangle3d;
struct real_vector3d;
struct s_map_variant;
namespace Forge
{
	struct ForgeObjectQuota;
}

/* ---------- constants */

namespace Forge
{
	enum EForgeObjectPhysics
	{
		Normal = 0,
		Phased,
	};
}

/* ---------- definitions */

namespace Forge
{
	struct ForgeObjectQuota
	{
		unsigned short TotalObjectsAvailable; // 0x0
		unsigned short TotalObjectsUsed; // 0x2
	};
	static_assert(sizeof(Forge::ForgeObjectQuota) == 4, "Invalid Forge::ForgeObjectQuota size");
}

/* ---------- prototypes */

namespace Forge
{
	extern s_map_variant *GetMapVariant();
	extern void PrintKillFeedText(long user_index, wchar_t const *message, long unused);
	extern real_rectangle3d const *GetObjectBoundingBox(long tag_index);
	extern void DeleteObject(long player_index, long map_variant_index);
	extern long CloneObject(long player_index, long object_index, float depth, real_vector3d const &normal);
	extern void ThrowObject(long player_index, long object_index, float throwForce);
	extern real_vector3d GetClosestCardianalAxix(real_vector3d const &v);
	extern Forge::ForgeObjectQuota CalculateObjectQuota();
	extern bool PointInWorldBounds(real_point3d const &point);
	extern bool ObjectInWorldBounds(long objectIndex);
	extern void SetObjectPhysicsMode(long objectIndex, Forge::EForgeObjectPhysics mode, bool atRest);
	extern Forge::EForgeObjectPhysics GetObjectPhysicsMode(long objectIndex);
	extern bool ObjectIsForgeScenery(long objectIndex);
	extern void ScaleForgeSceneryObject(long objectIndex, float scale);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGEUTIL_HPP__
