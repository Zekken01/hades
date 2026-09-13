#ifndef __MODULES_MODULESCRIPT_HPP__
#define __MODULES_MODULESCRIPT_HPP__
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
	class ModuleScript;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class ModuleScript :
		public Modules::ModuleBase,
		public Utils::Singleton<Modules::ModuleScript>
	{
	public:
		ModuleScript();
		Modules::Command *VarPrintToConsole; // 0x1C
		~ModuleScript() = default; /* compiler_generated() */
	};
	static_assert(sizeof(Modules::ModuleScript) == 32, "Invalid Modules::ModuleScript size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULESCRIPT_HPP__
