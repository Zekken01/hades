#ifndef __PATCHES_CORE_HPP__
#define __PATCHES_CORE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/Audio.hpp"

#include <functional>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Core
	{
		extern void ApplyAll();
		extern void ApplyAfterInit();
		extern void OnShutdown(std::function<void __cdecl(void)> callback);
		extern void ExecuteShutdownCallbacks();
		extern void OnMapLoaded(std::function<void __cdecl(char const *)> callback);
		extern void OnGameStart(std::function<void __cdecl(void)> callback);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PATCHES_CORE_HPP__
