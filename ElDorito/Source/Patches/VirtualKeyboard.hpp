#ifndef __PATCHES_VIRTUALKEYBOARD_HPP__
#define __PATCHES_VIRTUALKEYBOARD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/Audio.hpp"

#include <functional>

/* ---------- forward declarations */

namespace Blam
{
	namespace Input
	{
		class VirtualKeyboard;
	}
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace VirtualKeyboard
	{
		extern void Init();
		extern void ApplyAll();
		extern void SetKeyboardHandler(std::function<void __cdecl(Blam::Input::VirtualKeyboard *)> callback);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PATCHES_VIRTUALKEYBOARD_HPP__
