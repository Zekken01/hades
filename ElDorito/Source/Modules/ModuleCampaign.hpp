#ifndef __MODULES_MODULECAMPAIGN_HPP__
#define __MODULES_MODULECAMPAIGN_HPP__
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
	class ModuleCampaign;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleCampaign :
		public Utils::Singleton<Modules::ModuleCampaign>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarPlayerRepresentationEnabled; // 0x1C
		Modules::Command *VarPlayerRepresentationEnabledClient; // 0x20
		Modules::Command *VarCinematicFrameRate; // 0x24
		Modules::Command *VarCinematicFrameRateClient; // 0x28
		Modules::Command *VarCampaignSprintEnabled; // 0x2C
		Modules::Command *VarCheckpointsDisabled; // 0x30
		ModuleCampaign();
		~ModuleCampaign() = default; /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleCampaign) == 52, "Invalid Modules::ModuleCampaign size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULECAMPAIGN_HPP__
