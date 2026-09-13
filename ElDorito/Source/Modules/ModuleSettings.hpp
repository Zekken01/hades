#ifndef __MODULES_MODULESETTINGS_HPP__
#define __MODULES_MODULESETTINGS_HPP__
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
	class ModuleSettings;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class ModuleSettings :
		public Utils::Singleton<Modules::ModuleSettings>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarAntialiasing; // 0x1C
		Modules::Command *VarAutoCentering; // 0x20
		Modules::Command *VarBrightness; // 0x24
		Modules::Command *VarContrast; // 0x28
		Modules::Command *VarDetailsQuality; // 0x2C
		Modules::Command *VarDisplayHints; // 0x30
		Modules::Command *VarEffectsQuality; // 0x34
		Modules::Command *VarFullscreen; // 0x38
		Modules::Command *VarScreenResolution; // 0x3C
		Modules::Command *VarHUDShake; // 0x40
		Modules::Command *VarInvertLook; // 0x44
		Modules::Command *VarInvertMouse; // 0x48
		Modules::Command *VarLightingQuality; // 0x4C
		Modules::Command *VarLookSensitivity; // 0x50
		Modules::Command *VarMotionBlur; // 0x54
		Modules::Command *VarMouseAcceleration; // 0x58
		Modules::Command *VarGamepadEnabled; // 0x5C
		Modules::Command *VarMouseSensitivityHorizontal; // 0x60
		Modules::Command *VarMouseSensitivityVertical; // 0x64
		Modules::Command *VarMouseSensitivityVehicleHorizontal; // 0x68
		Modules::Command *VarMouseSensitivityVehicleVertical; // 0x6C
		Modules::Command *VarPlayerMarkerColors; // 0x70
		Modules::Command *VarPostprocessingQuality; // 0x74
		Modules::Command *VarShadowQuality; // 0x78
		Modules::Command *VarShadowResolution; // 0x7C
		Modules::Command *VarTextureFilteringQuality; // 0x80
		Modules::Command *VarTextureResolution; // 0x84
		Modules::Command *VarToggleCrouch; // 0x88
		Modules::Command *VarFpJumpLandAnimationsDisabled; // 0x8C
		Modules::Command *VarVSync; // 0x90
		Modules::Command *VarMasterVolume; // 0x94
		Modules::Command *VarSfxVolume; // 0x98
		Modules::Command *VarMusicVolume; // 0x9C
		Modules::Command *VarMainMenuMusicVolume; // 0xA0
		Modules::Command *VarMusicInLobby; // 0xA4
		Modules::Command *VarPersistentLobby; // 0xA8
		Modules::Command *VarAudioOutputDevice; // 0xAC
		Modules::Command *VarAnisotropicFiltering; // 0xB0
		Modules::Command *VarMotionBlurStrength; // 0xB4
		Modules::Command *VarMotionBlurAlways; // 0xB8
		Modules::Command *VarDecoratorDistance; // 0xBC
		Modules::Command *VarLODDistance; // 0xC0
		Modules::Command *VarSsao; // 0xC4
		Modules::Command *VarSubtitles; // 0xC8
		Modules::Command *VarExposureCpu; // 0xCC
		ModuleSettings();
		void GetScreenResolution(__int32 *width, __int32 *height) const;
		~ModuleSettings() = default; /* compiler_generated() */
	};
	static_assert(sizeof(Modules::ModuleSettings) == 208, "Invalid Modules::ModuleSettings size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULESETTINGS_HPP__
