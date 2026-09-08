#ifndef __SCRIPTING_HALOSCRIPT_HALOSCRIPT_HPP__
#define __SCRIPTING_HALOSCRIPT_HALOSCRIPT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/hs/hs.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Reforge.hpp"

#include <span>
#include <string>
#include <string_view>

/* ---------- forward declarations */

struct hs_value;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Scripting
{
	namespace HS
	{
		extern char const *MarshalString(__int32 threadIndex, std::string_view str);
		extern hs_value MarshalArgument(long threadIndex, e_hs_type type, hs_value const &value);
		extern hs_value MarshalReturn(long threadIndex, e_hs_type type, hs_value value);
		extern __int32 FindScriptByName(std::string_view name);
		extern void InitializeForNewMap();
		extern void Init();
		extern void Tick();
		extern void PushScript(long threadIndex, short scriptIndex, long **outReturnValueAddr, std::span<hs_value const> arguments);
		extern void ExecuteScript(__int32 scriptIndex, std::span<hs_value const> arguments);
		extern void ExecuteScript(std::string_view name, std::span<hs_value const> arguments);
		extern hs_value ExecuteScriptWithReturn(short scriptIndex, std::span<hs_value const> arguments);
		extern hs_value ExecuteScriptWithReturn(std::string_view name, std::span<hs_value const> arguments);
		extern void AddHookCallback(std::string_view name, short callbackScriptIndex);
		extern void RemoveHookCallback(std::string_view name, short callbackScriptIndex);
		extern void CallHook(std::string_view name, std::span<hs_value const> arguments);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SCRIPTING_HALOSCRIPT_HALOSCRIPT_HPP__
