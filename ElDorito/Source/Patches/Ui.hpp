#ifndef __PATCHES_UI_HPP__
#define __PATCHES_UI_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/Audio.hpp"

#include <functional>
#include <memory>
#include <string>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Ui
	{
		extern void ApplyAfterTagsLoaded();
		extern void ApplyAll();
		extern void *ShowDialog(unsigned long const p_DialogID, __int32 const p_Arg1, __int32 const p_Flags, unsigned long const p_ParentID);
		extern void OnCreateWindow(std::function<void __cdecl(HWND__ *)> callback);
		extern void TogglePTTSound(bool enabled);
		extern void ToggleSpeakingPlayerName(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name, bool speaking);
		extern void ApplyUIResolution();
		extern void ShowLanBrowser();
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PATCHES_UI_HPP__
