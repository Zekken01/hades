#ifndef __PATCHES_LOADINGSCREEN_HPP__
#define __PATCHES_LOADINGSCREEN_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Patches
{
	namespace LoadingScreen
	{
		class LoadingScreenUi;
		struct LoadingScreenShowInfo;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Patches
{
	namespace LoadingScreen
	{
		class LoadingScreenUi
		{
		public:
			virtual _inline ~LoadingScreenUi();
			virtual void Show(Patches::LoadingScreen::LoadingScreenShowInfo const &) = 0;
			virtual void Begin(unsigned __int32) = 0;
			virtual void UpdateProgress(unsigned __int32) = 0;
			virtual void Hide() = 0;
			LoadingScreenUi(Patches::LoadingScreen::LoadingScreenUi const &); /* compiler_generated() */
			_inline LoadingScreenUi() = default; /* compiler_generated() */
			Patches::LoadingScreen::LoadingScreenUi &operator=(Patches::LoadingScreen::LoadingScreenUi const &); /* compiler_generated() */
		};
		static_assert(sizeof(Patches::LoadingScreen::LoadingScreenUi) == 4, "Invalid Patches::LoadingScreen::LoadingScreenUi size");

		struct LoadingScreenShowInfo
		{
			char GameMode; // 0x0
			char VariantType; // 0x1
			short NumberOfRounds; // 0x2
			short ScoreToWin; // 0x4
			short TimeLimit; // 0x6
			std::string MapPath; // 0x8
			std::string MapName; // 0x24
			std::string MapAuthor; // 0x40
			std::string MapDescription; // 0x5C
			std::string InsertionName; // 0x78
			std::string InsertionDescription; // 0x94
			std::string VariantName; // 0xB0
			std::string VariantDescription; // 0xCC
			std::string ServerName; // 0xE8
			std::string ServerMessage; // 0x104
			std::vector<std::string> Skulls; // 0x120
			std::string Difficulty; // 0x130
			std::string modHash; // 0x14C
			std::string modAuthor; // 0x168
			std::string modDescription; // 0x184
			std::string modName; // 0x1A0
			std::string modVersion; // 0x1BC
			// LoadingScreenShowInfo(Patches::LoadingScreen::LoadingScreenShowInfo &); /* compiler_generated() */ hades: implicit
			// LoadingScreenShowInfo(Patches::LoadingScreen::LoadingScreenShowInfo const &); /* compiler_generated() */ hades: implicit
			// LoadingScreenShowInfo(); /* compiler_generated() */ hades: implicit
			// _inline ~LoadingScreenShowInfo(); /* compiler_generated() */ hades: implicit
			// Patches::LoadingScreen::LoadingScreenShowInfo &operator=(Patches::LoadingScreen::LoadingScreenShowInfo &); /* compiler_generated() */ hades: implicit
			// Patches::LoadingScreen::LoadingScreenShowInfo &operator=(Patches::LoadingScreen::LoadingScreenShowInfo const &); /* compiler_generated() */ hades: implicit
		};
		static_assert(sizeof(Patches::LoadingScreen::LoadingScreenShowInfo) == 472, "Invalid Patches::LoadingScreen::LoadingScreenShowInfo size");
	}
}

/* ---------- prototypes */

namespace Patches
{
	namespace LoadingScreen
	{
		extern void ApplyAll();
		extern void SetUi(std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ui);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Patches
{
	namespace LoadingScreen
	{
		_inline LoadingScreenUi::~LoadingScreenUi() // 0x10CAA140
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1LoadingScreenUi@LoadingScreen@Patches@@UAE@XZ");
			// Patches::LoadingScreen::LoadingScreenUi *const this;
		}
	}
}

/* ---------- private code */

#endif // __PATCHES_LOADINGSCREEN_HPP__
