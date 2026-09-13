#ifndef __MODULES_MODULEPLAYER_HPP__
#define __MODULES_MODULEPLAYER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCustomizationExtension.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModulePlayer;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class ModulePlayer :
		public Utils::Singleton<Modules::ModulePlayer>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarPlayerEmblem; // 0x1C
		Modules::Command *VarPlayerName; // 0x20
		Modules::Command *VarPlayerGender; // 0x24
		Modules::Command *VarPlayerServiceTag; // 0x28
		Modules::Command *VarPlayerPrivKey; // 0x2C
		Modules::Command *VarPlayerPubKey; // 0x30
		Modules::Command *VarNameplateColor; // 0x34
		Modules::Command *VarNameplate; // 0x38
		Modules::Command *VarSprintAnimationHack; // 0x3C
		wchar_t UserName[16]; // 0x40
		ModulePlayer();
		static bool ValidServiceTag(std::string const &tag);
		static bool ValidPlayerName(std::string const &name);
		~ModulePlayer() = default; /* compiler_generated() */
	};
	static_assert(sizeof(Modules::ModulePlayer) == 96, "Invalid Modules::ModulePlayer size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEPLAYER_HPP__
