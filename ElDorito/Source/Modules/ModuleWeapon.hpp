#ifndef __MODULES_MODULEWEAPON_HPP__
#define __MODULES_MODULEWEAPON_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleWeapon;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class ModuleWeapon :
		public Utils::Singleton<Modules::ModuleWeapon>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarWeaponJSON; // 0x1C
		std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > WeaponsJSONList; // 0x20
		ModuleWeapon();
		~ModuleWeapon(); /* compiler_generated() */
	};
	static_assert(sizeof(Modules::ModuleWeapon) == 48, "Invalid Modules::ModuleWeapon size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEWEAPON_HPP__
