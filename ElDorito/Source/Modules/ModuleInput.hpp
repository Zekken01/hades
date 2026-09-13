#ifndef __MODULES_MODULEINPUT_HPP__
#define __MODULES_MODULEINPUT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Blam
{
	namespace Input
	{
		enum KeyCode : unsigned short;
		struct BindingsTable;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleInput;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Blam
{
	namespace Input
	{
		struct BindingsTable
		{
			float ControllerSensitivityX; // 0x0
			float ControllerSensitivityY; // 0x4
			Blam::Input::ControllerButton ControllerButtons[59]; // 0x8
			bool ControllerHoldButtons[59]; // 0x43
			Blam::Input::KeyCode PrimaryKeys[63]; // 0x7E
			Blam::Input::KeyCode SecondaryKeys[63]; // 0xFC
			Blam::Input::MouseButton PrimaryMouseButtons[63]; // 0x17A
			Blam::Input::MouseButton SecondaryMouseButtons[63]; // 0x1B9
			unsigned short JoystickLayout; // 0x1F8
			unsigned short Unknown1FA; // 0x1FA
			unsigned __int32 Unknown1FC; // 0x1FC
			float FlyingCameraSpeed; // 0x200
			float FlyingCameraThrust; // 0x204
		};
		static_assert(sizeof(Blam::Input::BindingsTable) == 520, "Invalid Blam::Input::BindingsTable size");
	}
}

#pragma pack(push, 4)
namespace Modules
{
	class ModuleInput :
		public Utils::Singleton<Modules::ModuleInput>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarInputRawInput; // 0x1C
		Modules::Command *VarDirectInput; // 0x20
		Modules::Command *VarInputControllerPort; // 0x24
		Modules::Command *VarControllerSensitivityX; // 0x28
		Modules::Command *VarControllerSensitivityY; // 0x2C
		Modules::Command *VarControllerVibrationIntensity; // 0x30
		Modules::Command *VarControllerInvertY; // 0x34
		Modules::Command *VarControllerStickLayout; // 0x38
		Modules::Command *VarControllerAimControl; // 0x3C
		Modules::Command *VarControllerAxialDeadzone; // 0x40
		Modules::Command *VarControllerRadialDeadzone; // 0x44
		Modules::Command *VarSpectateSensitivity; // 0x48
		Modules::Command *VarToggleSprint; // 0x4C
		Modules::Command *VarTapScoreboard; // 0x50
		Modules::Command *VarSmartScoreboard; // 0x54
		Modules::Command *VarMouseWheelInputDelay; // 0x58
		Modules::Command *CommandBindControllerAction; // 0x5C
		Modules::Command *CommandBindKeyboardAction; // 0x60
		ModuleInput();
		static Blam::Input::BindingsTable *GetBindings();
		static void UpdateBindings();
		std::string ExportBindings() const;
		bool IsCommandBound(std::string command);
		~ModuleInput() = default; /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleInput) == 100, "Invalid Modules::ModuleInput size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEINPUT_HPP__
