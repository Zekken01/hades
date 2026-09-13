#ifndef __MODULES_MODULEGRAPHICS_HPP__
#define __MODULES_MODULEGRAPHICS_HPP__
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
	class ModuleGraphics;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class ModuleGraphics :
		public Utils::Singleton<Modules::ModuleGraphics>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarSaturation; // 0x1C
		Modules::Command *VarRedHue; // 0x20
		Modules::Command *VarGreenHue; // 0x24
		Modules::Command *VarBlueHue; // 0x28
		Modules::Command *VarGammaPower; // 0x2C
		Modules::Command *VarContrailsEnabled; // 0x30
		Modules::Command *VarDecalsEnabled; // 0x34
		Modules::Command *VarParticlesEnabled; // 0x38
		Modules::Command *VarReflectionsEnabled; // 0x3C
		Modules::Command *VarBloom; // 0x40
		Modules::Command *VarDepthOfField; // 0x44
		Modules::Command *VarLetterbox; // 0x48
		Modules::Command *VarCustomHUDColorsEnabled; // 0x4C
		Modules::Command *VarCustomHUDColorsPrimary; // 0x50
		Modules::Command *VarCustomHUDColorsSecondary; // 0x54
		Modules::Command *VarCenteredHUD; // 0x58
		Modules::Command *VarHUDScaleX; // 0x5C
		Modules::Command *VarUIScaling; // 0x60
		Modules::Command *VarDisableContrails; // 0x64
		Modules::Command *VarForceDefaultLighting; // 0x68
		Modules::Command *VarFrameRateLimit; // 0x6C
		ModuleGraphics();
		~ModuleGraphics() = default; /* compiler_generated() */
	};
	static_assert(sizeof(Modules::ModuleGraphics) == 112, "Invalid Modules::ModuleGraphics size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEGRAPHICS_HPP__
