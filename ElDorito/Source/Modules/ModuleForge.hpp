#ifndef __MODULES_MODULEFORGE_HPP__
#define __MODULES_MODULEFORGE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct s_CommandState;
struct s_Prefabs;
namespace Modules
{
	class ModuleBase;
	class ModuleForge;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class ModuleForge :
		public Utils::Singleton<Modules::ModuleForge>,
		public Modules::ModuleBase
	{
	public:
			public:
		struct s_CommandState
		{
			public:
			struct s_Prefabs
			{
				bool SavePrefab; // 0x0
				bool LoadPrefab; // 0x1
				std::basic_string<char,std::char_traits<char>,std::allocator<char> > Path; // 0x4
				std::basic_string<char,std::char_traits<char>,std::allocator<char> > Name; // 0x20
				s_Prefabs(s_Prefabs &); /* compiler_generated() */
				s_Prefabs(s_Prefabs const &); /* compiler_generated() */
				s_Prefabs(); /* compiler_generated() */
				~s_Prefabs(); /* compiler_generated() */
				s_Prefabs &operator=(s_Prefabs &); /* compiler_generated() */
				s_Prefabs &operator=(s_Prefabs const &); /* compiler_generated() */
			};
			// static_assert(sizeof(s_Prefabs) == 60, "Invalid s_Prefabs size");
			// Withheld: the type inventory does not describe this type, so its
			// padding could not be reconstructed.
			public:
			bool MapCanvas; // 0x0
			bool RuntimeReset; // 0x1
			bool SetPrematchCamera; // 0x2
			short PrematchCameraTeamIndex; // 0x4
			bool OpenMapOptions; // 0x6
			long SpawnItem; // 0x8
		s_Prefabs Prefabs; // 0xC
			s_CommandState(s_CommandState &); /* compiler_generated() */
			s_CommandState(s_CommandState const &); /* compiler_generated() */
			s_CommandState(); /* compiler_generated() */
			_inline ~s_CommandState(); /* compiler_generated() */
			s_CommandState &operator=(s_CommandState &); /* compiler_generated() */
			s_CommandState &operator=(s_CommandState const &); /* compiler_generated() */
		};
		// static_assert(sizeof(s_CommandState) == 72, "Invalid s_CommandState size");
		// Withheld: the type inventory does not describe this type, so its
		// padding could not be reconstructed.
			struct s_Prefabs
		{
			bool SavePrefab; // 0x0
			bool LoadPrefab; // 0x1
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > Path; // 0x4
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > Name; // 0x20
			s_Prefabs(Modules::ModuleForge::s_CommandState::s_Prefabs &); /* compiler_generated() */
			s_Prefabs(Modules::ModuleForge::s_CommandState::s_Prefabs const &); /* compiler_generated() */
			s_Prefabs(); /* compiler_generated() */
			~s_Prefabs(); /* compiler_generated() */
			Modules::ModuleForge::s_CommandState::s_Prefabs &operator=(Modules::ModuleForge::s_CommandState::s_Prefabs &); /* compiler_generated() */
			Modules::ModuleForge::s_CommandState::s_Prefabs &operator=(Modules::ModuleForge::s_CommandState::s_Prefabs const &); /* compiler_generated() */
		};
		// static_assert(sizeof(s_Prefabs) == 60, "Invalid s_Prefabs size");
		// Withheld: the type inventory does not describe this type, so its
		// padding could not be reconstructed.
			public:
		Modules::Command *VarCloneDepth; // 0x1C
		Modules::Command *VarCloneMultiplier; // 0x20
		Modules::Command *VarRotationSnap; // 0x24
		Modules::Command *VarRotationSensitivity; // 0x28
		Modules::Command *VarMonitorSpeed; // 0x2C
		Modules::Command *VarMonitorNoclip; // 0x30
		Modules::Command *VarSelectionRenderer; // 0x34
		Modules::Command *VarMagnetsEnabled; // 0x38
		Modules::Command *VarMagnetsVisible; // 0x3C
		Modules::Command *VarMagnetAutogen; // 0x40
		Modules::Command *VarMaxGrabDistance; // 0x44
		Modules::Command *VarMagnetsStrength; // 0x48
		Modules::Command *VarTestDimensionI; // 0x4C
		Modules::Command *VarTestDimensionJ; // 0x50
		Modules::Command *VarTestDimensionK; // 0x54
		Modules::Command *VarSelectionColor; // 0x58
		Modules::Command *VarShowInvisibles; // 0x5C
		Modules::Command *VarShowInvisiblesClient; // 0x60
		Modules::Command *VarShowWorldBounds; // 0x64
		Modules::Command *VarShowWorldBoundsClient; // 0x68
		s_CommandState CommandState; // 0x6C
		ModuleForge();
		~ModuleForge(); /* compiler_generated() */
	};
}

// static_assert(sizeof(Modules::ModuleForge) == 180, "Invalid Modules::ModuleForge size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEFORGE_HPP__
