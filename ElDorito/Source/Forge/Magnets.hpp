#ifndef __FORGE_MAGNETS_HPP__
#define __FORGE_MAGNETS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"

/* ---------- forward declarations */

namespace Forge
{
	namespace Magnets
	{
		struct Magnet;
		struct MagnetPair;
	}
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Forge
{
	namespace Magnets
	{
		struct Magnet
		{
			real_point3d Position; // 0x0
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Forge::Magnets::Magnet) == 12, "Invalid Forge::Magnets::Magnet size");

namespace Forge
{
	namespace Magnets
	{
		struct MagnetPair
		{
			bool IsValid; // 0x0
			Forge::Magnets::Magnet *Source; // 0x4
			Forge::Magnets::Magnet *Dest; // 0x8
		};
		static_assert(sizeof(Forge::Magnets::MagnetPair) == 12, "Invalid Forge::Magnets::MagnetPair size");
	}
}

/* ---------- prototypes */

namespace Forge
{
	namespace Magnets
	{
		extern bool Initialize();
		extern void Shutdown();
		extern void Update();
		extern void Render();
		extern Forge::Magnets::MagnetPair const &GetMagnetPair();
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_MAGNETS_HPP__
