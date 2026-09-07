#ifndef __MODULES_MODULEVOTING_HPP__
#define __MODULES_MODULEVOTING_HPP__
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
	class ModuleVoting;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleVoting :
		public Utils::Singleton<Modules::ModuleVoting>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarServerMapVotingTime; // 0x1C
		Modules::Command *VarServerVotingType; // 0x20
		Modules::Command *VarServerNumberOfRevotesAllowed; // 0x24
		Modules::Command *VarServerNumberOfVotingOptions; // 0x28
		Modules::Command *VarServerNumberOfRematchesAllowed; // 0x2C
		Modules::Command *VarInstantSkipVoteMinPlayers; // 0x30
		Modules::Command *VarInstantSkipVotingEnabled; // 0x34
		Modules::Command *VarServerTimeBetweenVoteEndAndGameStart; // 0x38
		Modules::Command *VarServerVotingDuplicationLevel; // 0x3C
		Modules::Command *VarVotingJsonPath; // 0x40
		Modules::Command *VarNumberOfVetoVotes; // 0x44
		Modules::Command *VarVetoWinningOptionShownTime; // 0x48
		Modules::Command *VarVetoVotePassPercentage; // 0x4C
		Modules::Command *VarVetoSystemSelectionType; // 0x50
		ModuleVoting();
		~ModuleVoting(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleVoting) == 84, "Invalid Modules::ModuleVoting size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEVOTING_HPP__
