#ifndef __OBJECTS_OBJECTMESSAGING_HPP__
#define __OBJECTS_OBJECTMESSAGING_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <functional>

/* ---------- forward declarations */

namespace Objects
{
	struct CObjectMessaging;
}

/* ---------- constants */

/* ---------- definitions */

namespace Objects
{
	struct CObjectMessaging
	{
		static void EnqueueAction(std::function<void __cdecl(void)> &&action);
		static void Init();
		static void Reset();
		static void RunActions();
	};
	static_assert(sizeof(Objects::CObjectMessaging) == 1, "Invalid Objects::CObjectMessaging size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __OBJECTS_OBJECTMESSAGING_HPP__
