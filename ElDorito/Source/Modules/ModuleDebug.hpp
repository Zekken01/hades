#ifndef __MODULES_MODULEDEBUG_HPP__
#define __MODULES_MODULEDEBUG_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleDebug;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleDebug :
		public Utils::Singleton<Modules::ModuleDebug>,
		public Modules::ModuleBase
	{
	public:
		public:
		enum EAssertLevel
		{
			eAssertLevel_Disabled = 0,
			eAssertLevel_Normal,
			eAssertLevel_High,
		};
		public:
		Modules::Command *VarCrashReporting; // 0x1C
		Modules::Command *VarAssertLevel; // 0x20
		Modules::Command *VarCollisionTest; // 0x24
		Modules::Command *VarHavokStats; // 0x28
		Modules::Command *VarSoundDebug; // 0x2C
		Modules::Command *VarLoopingSoundDebug; // 0x30
		Modules::Command *VarSoundFilters; // 0x34
		Modules::Command *VarFModStats; // 0x38
		Modules::Command *VarClusters; // 0x3C
		Modules::Command *VarCollisionModels; // 0x40
		Modules::Command *VarPhysicsModels; // 0x44
		Modules::Command *VarStructureCollision; // 0x48
		Modules::Command *VarMarkerGroups; // 0x4C
		Modules::Command *VarMarkerGroupFilter; // 0x50
		Modules::Command *VarDamageAoe; // 0x54
		Modules::Command *VarDamageAoeDisplayTime; // 0x58
		Modules::Command *VarTraceFilter; // 0x5C
		Modules::Command *VarSoundCache; // 0x60
		Modules::Command *VarSoundSystemTrace; // 0x64
		Modules::Command *VarSoundQueueFilter; // 0x68
		Modules::Command *VarTriggerVolumes; // 0x6C
		Modules::Command *VarZBuffTest; // 0x70
		Modules::Command *VarMouseSupport; // 0x74
		Modules::Command *VarScriptTrace; // 0x78
		Modules::Command *VarScriptTraceFile; // 0x7C
		Modules::Command *VarScriptName; // 0x80
		Modules::Command *VarScriptBreakpoint; // 0x84
		Modules::Command *VarAcrophobia; // 0x88
		Modules::Command *VarAcrophobiaClient; // 0x8C
		Modules::Command *VarPlayerDamageDisabled; // 0x90
		Modules::Command *VarPlayerDamageDisabledClient; // 0x94
		Modules::Command *VarMapBarriersDisabled; // 0x98
		Modules::Command *VarMapBarriersDisabledClient; // 0x9C
		Modules::Command *VarVisibility; // 0xA0
		Modules::Command *VarGeometrySamplerQuality; // 0xA4
		Modules::Command *VarSmaaDebugMode; // 0xA8
		Modules::Command *VarAnimationPhoneboothTestDraw; // 0xAC
		Modules::Command *VarAnimationPhoneboothDrawTime; // 0xB0
		Modules::Command *VarHideForgeObjects; // 0xB4
		Modules::Command *VarD3DResources; // 0xB8
		Modules::Command *VarParticleFilter; // 0xBC
		bool teleportToCamera; // 0xC0
		ModuleDebug();
		~ModuleDebug(); /* compiler_generated() */
	unsigned char __pad0[3]; // 0xC1
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleDebug) == 196, "Invalid Modules::ModuleDebug size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEDEBUG_HPP__
