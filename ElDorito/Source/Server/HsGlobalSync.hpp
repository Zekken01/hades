#ifndef __SERVER_HSGLOBALSYNC_HPP__
#define __SERVER_HSGLOBALSYNC_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Reforge.hpp"

#include <functional>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Server
{
	namespace HsGlobalSync
	{
		extern void RegisterGlobal(short globalIndex);
		extern void UnregisterGlobal(short globalIndex);
		extern void InvalidatePlayerMask(unsigned short playerMask);
		extern void InvalidateGlobal(short globalIndex);
		extern void Synchronize();
		extern void InitializeForNewMap();
		extern void Init();
		extern void Tick();
		extern void SetupFuncs(std::function<void __cdecl(short,unsigned short)> sendGlobal_);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_HSGLOBALSYNC_HPP__
