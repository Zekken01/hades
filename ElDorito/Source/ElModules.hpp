#ifndef __ELMODULES_HPP__
#define __ELMODULES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

/* ---------- forward declarations */

namespace Modules
{
	class ElModules;
	class ModuleBase;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ElModules :
		public Utils::Singleton<Modules::ElModules>,
		public Modules::ModuleBase
	{
	public:
		ElModules();
		~ElModules(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ElModules) == 28, "Invalid Modules::ElModules size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __ELMODULES_HPP__
