#ifndef __UTILS_PROCESSUTILS_HPP__
#define __UTILS_PROCESSUTILS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <memory>
#include <string>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils { namespace FileUtils { char const *GetName(char const *filename); } }  // hades: added for 0x1068F570  // hades: added for 0x1068F570

namespace Utils
{
	namespace ProcessUtils
	{
		extern _inline HINSTANCE__ *GetModuleFromAddress(void *address);
		extern _inline std::string GetModuleNameForDisplay(HINSTANCE__ *hMod);
	}
}

/* ---------- globals */

/* ---------- public code */


namespace Utils
{
	namespace ProcessUtils
	{
		inline HINSTANCE__ *GetModuleFromAddress(void *address) // 0x1068F4D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetModuleFromAddress@ProcessUtils@Utils@@YAPAUHINSTANCE__@@PAX@Z");

			HMODULE hMod;
			if (!GetModuleHandleExA(6, (LPCSTR)address, &hMod))
				return nullptr;
			return hMod;
		}
	}
}


namespace Utils
{
	namespace ProcessUtils
	{
		inline std::string GetModuleNameForDisplay(HINSTANCE__ *hMod) // 0x1068F570
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetModuleNameForDisplay@ProcessUtils@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUHINSTANCE__@@@Z");

			char modulePath[520];
			if (!GetModuleFileNameA(hMod, modulePath, std::size(modulePath)))
				return "??";
			return Utils::FileUtils::GetName(modulePath);
		}
	}
}

/* ---------- private code */

#endif // __UTILS_PROCESSUTILS_HPP__
