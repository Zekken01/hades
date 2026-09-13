#ifndef __MODULES_MODULETIME_HPP__
#define __MODULES_MODULETIME_HPP__
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
	class ModuleTime;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleTime :
		public Utils::Singleton<Modules::ModuleTime>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarSpeed; // 0x1C
		Modules::Command *VarSpeedClient; // 0x20
		ModuleTime();
		~ModuleTime() = default; /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleTime) == 36, "Invalid Modules::ModuleTime size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULETIME_HPP__
