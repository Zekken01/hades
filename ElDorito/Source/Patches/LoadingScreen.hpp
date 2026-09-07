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
			_inline LoadingScreenUi(); /* compiler_generated() */
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
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > MapPath; // 0x8
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > MapName; // 0x24
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > MapAuthor; // 0x40
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > MapDescription; // 0x5C
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > InsertionName; // 0x78
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > InsertionDescription; // 0x94
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > VariantName; // 0xB0
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > VariantDescription; // 0xCC
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > ServerName; // 0xE8
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > ServerMessage; // 0x104
			std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > Skulls; // 0x120
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > Difficulty; // 0x130
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > modHash; // 0x14C
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > modAuthor; // 0x168
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > modDescription; // 0x184
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > modName; // 0x1A0
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > modVersion; // 0x1BC
			LoadingScreenShowInfo(Patches::LoadingScreen::LoadingScreenShowInfo &); /* compiler_generated() */
			LoadingScreenShowInfo(Patches::LoadingScreen::LoadingScreenShowInfo const &); /* compiler_generated() */
			LoadingScreenShowInfo(); /* compiler_generated() */
			_inline ~LoadingScreenShowInfo(); /* compiler_generated() */
			Patches::LoadingScreen::LoadingScreenShowInfo &operator=(Patches::LoadingScreen::LoadingScreenShowInfo &); /* compiler_generated() */
			Patches::LoadingScreen::LoadingScreenShowInfo &operator=(Patches::LoadingScreen::LoadingScreenShowInfo const &); /* compiler_generated() */
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
		_extern void _sub_10CAA140(Patches::LoadingScreen::LoadingScreenUi *const);
		_inline LoadingScreenUi::~LoadingScreenUi() // 0x10CAA140
		{
			mangled_x86(MANGLED_TODO, "??1LoadingScreenUi@LoadingScreen@Patches@@UAE@XZ");
			// Patches::LoadingScreen::LoadingScreenUi *const this;
			todo("implement");
			_sub_10CAA140(this);
		}
	}
}

/* ---------- private code */

#endif // __PATCHES_LOADINGSCREEN_HPP__
