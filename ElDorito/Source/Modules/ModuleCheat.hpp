#ifndef __MODULES_MODULECHEAT_HPP__
#define __MODULES_MODULECHEAT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleCheat;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleCheat :
		public Utils::Singleton<Modules::ModuleCheat>,
		public Modules::ModuleBase
	{
	public:
		ModuleCheat();
		~ModuleCheat() = default; /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleCheat) == 28, "Invalid Modules::ModuleCheat size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULECHEAT_HPP__
