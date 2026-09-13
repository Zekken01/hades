#ifndef __MODULES_MODULECAMERA_HPP__
#define __MODULES_MODULECAMERA_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

/* ---------- forward declarations */

class Patch;
struct real_euler_angles2d;
namespace Modules
{
	class ModuleBase;
	class ModuleCamera;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleCamera :
		public Utils::Singleton<Modules::ModuleCamera>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarCameraCenteredCrosshairFirst; // 0x1C
		Modules::Command *VarCameraCenteredCrosshairThird; // 0x20
		Modules::Command *VarVehicleCameraFov; // 0x24
		Modules::Command *VarCameraFov; // 0x28
		Modules::Command *VarCameraHideHud; // 0x2C
		Modules::Command *VarCameraHideKillFeed; // 0x30
		Modules::Command *VarCameraMode; // 0x34
		Modules::Command *VarCameraSpeed; // 0x38
		Modules::Command *VarCameraPosition; // 0x3C
		Modules::Command *VarCameraShowCoordinates; // 0x40
		Modules::Command *VarCameraVertSpeed; // 0x44
		Modules::Command *VarCameraSmoothing; // 0x48
		Modules::Command *VarCameraFocusDistance; // 0x4C
		Modules::Command *VarOldViewOffsetScale; // 0x50
		Patch HideHudPatch; // 0x54
		Patch HideKillFeedPatch; // 0x78
		ModuleCamera();
		void SetInputAngularVelocity(real_euler_angles2d const *velocity);
		void GetInputAngularVelocity(real_euler_angles2d *velocity) const;
		~ModuleCamera() = default; /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleCamera) == 156, "Invalid Modules::ModuleCamera size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULECAMERA_HPP__
