#ifndef __MODULES_MODULETWEAKS_HPP__
#define __MODULES_MODULETWEAKS_HPP__
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
	class ModuleTweaks;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleTweaks :
		public Utils::Singleton<Modules::ModuleTweaks>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarDisableReactorFog; // 0x1C
		Modules::Command *VarDisableWeaponOutline; // 0x20
		Modules::Command *VarDisableHitMarkers; // 0x24
		Modules::Command *VarFlatHUD; // 0x28
		ModuleTweaks();
		~ModuleTweaks(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleTweaks) == 44, "Invalid Modules::ModuleTweaks size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULETWEAKS_HPP__
