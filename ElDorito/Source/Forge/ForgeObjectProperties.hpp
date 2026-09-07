#ifndef __FORGE_FORGEOBJECTPROPERTIES_HPP__
#define __FORGE_FORGEOBJECTPROPERTIES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/ForgeUndo.hpp"
#include "Forge/Geoemetry.hpp"
#include "ThirdParty/rapidjson/rapidjson.h"

/* ---------- forward declarations */

namespace Forge
{
	struct ForgeGarbageVolumeProperties;
	struct ForgeKillVolumeProperties;
	struct ForgeLightProperties;
	struct ForgeMapModifierProperties;
	struct ForgeScreenFxProperties;
	struct ReforgeObjectProperties;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	struct ForgeLightProperties
	{
		public:
		enum FunctionType
		{
			FunctionType_None = 0,
			FunctionType_Pulse,
			FunctionType_Flicker,
		};
		enum LightType
		{
			LightType_Point = 0,
			LightType_Directional,
		};
		struct s_Function
		{
			unsigned char Type : 3; // 0x0
			unsigned char Reserved : 5; // 0x0
			unsigned char Base; // 0x1
			unsigned char Freq; // 0x2
		};
		// static_assert(sizeof(s_Function) == 3, "Invalid s_Function size");
		// Withheld: the type inventory does not describe this type, so its
		// padding could not be reconstructed.
		public:
		unsigned char Type : 2; // 0x0
		unsigned char Flags : 6; // 0x0
		unsigned char ColorR; // 0x1
		unsigned char ColorG; // 0x2
		unsigned char ColorB; // 0x3
		unsigned char Intensity; // 0x4
		unsigned short Range; // 0x6
		unsigned char FieldOfView; // 0x8
		unsigned char NearWidth; // 0x9
		struct
		{
			unsigned char Type : 3; // 0x0
			unsigned char Reserved : 5; // 0x0
			unsigned char Base; // 0x1
			unsigned char Freq; // 0x2
		} Function; // 0xA
	};
}

// static_assert(sizeof(Forge::ForgeLightProperties) == 14, "Invalid Forge::ForgeLightProperties size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace Forge
{
	struct ForgeScreenFxProperties
	{
		unsigned char Flags; // 0x0
		unsigned char LightIntensity; // 0x1
		unsigned char Hue; // 0x2
		unsigned char Saturation; // 0x3
		unsigned char Desaturation; // 0x4
		unsigned char GammaIncrease; // 0x5
		unsigned char GammaDecrease; // 0x6
		unsigned char MaximumDistance; // 0x7
		unsigned char ColorFilterR; // 0x8
		unsigned char ColorFilterG; // 0x9
		unsigned char ColorFilterB; // 0xA
		unsigned char ColorFloorR; // 0xB
		unsigned char ColorFloorG; // 0xC
		unsigned char ColorFloorB; // 0xD
		unsigned char Tracing; // 0xE
		unsigned char DistanceFalloffFunction : 4; // 0xF
		unsigned char TimeEvolutionFunction : 4; // 0xF
	};
	static_assert(sizeof(Forge::ForgeScreenFxProperties) == 16, "Invalid Forge::ForgeScreenFxProperties size");

	struct ReforgeObjectProperties
	{
		public:
		enum Flags
		{
			MaterialOverrideTextureCoords = (1 << 0),
			MaterialAllowsProjectiles = (1 << 1),
			MaterialIsClimbable = (1 << 2),
		};
		struct s_TextureData
		{
			unsigned char Scale; // 0x0
			unsigned char OffsetX; // 0x1
			unsigned char OffsetY; // 0x2
		};
		// static_assert(sizeof(s_TextureData) == 3, "Invalid s_TextureData size");
		// Withheld: the type inventory does not describe this type, so its
		// padding could not be reconstructed.
		public:
		unsigned char ColorR; // 0x0
		unsigned char ColorG; // 0x1
		unsigned char ColorB; // 0x2
		unsigned char Flags; // 0x3
		struct
		{
			unsigned char Scale; // 0x0
			unsigned char OffsetX; // 0x1
			unsigned char OffsetY; // 0x2
		} TextureData; // 0x4
		unsigned char MaterialType : 5; // 0x7
		unsigned char TeamBarrier : 8; // 0x8
	};
}

// static_assert(sizeof(Forge::ReforgeObjectProperties) == 9, "Invalid Forge::ReforgeObjectProperties size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace Forge
{
	struct ForgeMapModifierProperties
	{
		public:
		enum MapModifierFlags : unsigned short
		{
			eMapModifierFlags_DisablePushBarrier = 1, // 0x0001
			eMapModifierFlags_DisableDeathBarrier = 2, // 0x0002
		};
		struct s_AtmosphereProperties
		{
			unsigned char Flags : 4; // 0x0
			unsigned char Weather : 4; // 0x0
			unsigned char FogColorR; // 0x1
			unsigned char FogColorG; // 0x2
			unsigned char FogColorB; // 0x3
			unsigned char FogDensity; // 0x4
			unsigned char FogVisibility; // 0x5
			unsigned char Brightness; // 0x6
			unsigned char Skybox : 8; // 0x7
			unsigned char SkyboxZOffset; // 0x8
		};
		// static_assert(sizeof(s_AtmosphereProperties) == 9, "Invalid s_AtmosphereProperties size");
		// Withheld: the type inventory does not describe this type, so its
		// padding could not be reconstructed.
		public:
		unsigned short Flags; // 0x0
		unsigned char CameraFxExposure; // 0x2
		unsigned char CameraFxLightIntensity; // 0x3
		unsigned char CameraFxBloom; // 0x4
		unsigned char CameraFxLightBloom; // 0x5
		struct
		{
			unsigned char Flags : 4; // 0x0
			unsigned char Weather : 4; // 0x0
			unsigned char FogColorR; // 0x1
			unsigned char FogColorG; // 0x2
			unsigned char FogColorB; // 0x3
			unsigned char FogDensity; // 0x4
			unsigned char FogVisibility; // 0x5
			unsigned char Brightness; // 0x6
			unsigned char Skybox : 8; // 0x7
			unsigned char SkyboxZOffset; // 0x8
		} AtmosphereProperties; // 0x6
		unsigned char PhysicsGravity; // 0xF
	};
}

// static_assert(sizeof(Forge::ForgeMapModifierProperties) == 16, "Invalid Forge::ForgeMapModifierProperties size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace Forge
{
	struct ForgeGarbageVolumeProperties
	{
		public:
		enum GarbageVolumeFlags
		{
			eGarbageVolumeFlags_CollectDeadBipeds = (1 << 0),
			eGarbageVolumeFlags_CollectWeapons = (1 << 1),
			eGarbageVolumeFlags_CollectObjectives = (1 << 2),
			eGarbageVolumeFlags_CollectEquipment = (1 << 3),
			eGarbageVolumeFlags_CollectGrenades = (1 << 4),
			eGarbageVolumeFlags_CollectVehicles = (1 << 5),
		};
		enum GarbageVolumeInterval
		{
			eGarbageVolumeInterval_Instant = 0,
			eGarbageVolumeInterval_3_Seconds,
			eGarbageVolumeInterval_15_Seconds,
			eGarbageVolumeInterval_30_Seconds,
		};
		public:
		unsigned char Flags : 6; // 0x0
		unsigned char Interval : 2; // 0x0
	};
	static_assert(sizeof(Forge::ForgeGarbageVolumeProperties) == 1, "Invalid Forge::ForgeGarbageVolumeProperties size");

	struct ForgeKillVolumeProperties
	{
		public:
		enum KillVolumeFlags
		{
			eKillVolumeFlags_AlwaysVisible = 1, // 0x0001
			eKillVolumeFlags_DestroyVehicles = 2, // 0x0002
		};
		enum KillVolumeDamageCause
		{
			eKillVolumeDamageCause_Default = 0,
			eKillVolumeDamageCause_Guardians,
			eKillVolumeDamageCause_Falling,
		};
		public:
		unsigned char Flags : 6; // 0x0
		unsigned char DamageCause : 2; // 0x0
	};
	static_assert(sizeof(Forge::ForgeKillVolumeProperties) == 1, "Invalid Forge::ForgeKillVolumeProperties size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGEOBJECTPROPERTIES_HPP__
