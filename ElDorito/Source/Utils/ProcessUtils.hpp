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

extern HINSTANCE__ *_sub_1068F4D0(void *);
namespace Utils
{
	namespace ProcessUtils
	{
		_inline HINSTANCE__ *GetModuleFromAddress(void *address) // 0x1068F4D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetModuleFromAddress@ProcessUtils@Utils@@YAPAUHINSTANCE__@@PAX@Z");
			// static ...; // 0x1068F548
			// static ...; // 0x1068F53C
			// static ...; // 0x1068F534
			// void *address;
			// HINSTANCE__ *hMod;
			// function call : __int32 (unsigned long, char const *, HINSTANCE__ **)

			HMODULE hMod;
			if (!GetModuleHandleExA(6, (LPCSTR)address, &hMod))
				return nullptr;
			return hMod;
		}
	}
}

extern std::string _sub_1068F570(HINSTANCE__ *);
namespace Utils
{
	namespace ProcessUtils
	{
		_inline std::string GetModuleNameForDisplay(HINSTANCE__ *hMod) // 0x1068F570
		{
			mangled_x86(MANGLED_TODO, "?GetModuleNameForDisplay@ProcessUtils@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUHINSTANCE__@@@Z");
			// static ...; // 0x1068F660
			// static ...; // 0x1068F654
			// static ...; // 0x1068F64C
			// HINSTANCE__ *hMod;
			// char modulePath[520];
			// function call : unsigned long (HINSTANCE__ *, char *, unsigned long)
			todo("implement");
			std::string __result = _sub_1068F570(hMod);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __UTILS_PROCESSUTILS_HPP__
