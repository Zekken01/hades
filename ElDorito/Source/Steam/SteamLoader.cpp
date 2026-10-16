/* ---------- headers */

#include "Steam/SteamLoader.h"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

namespace Steam
{
	class SteamLoader;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Steam
{
	void SteamLoader::Initialize() // 0x10C52550
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@SteamLoader@Steam@@QAEXXZ");

		if (IsSteamRunning(true))
		{
			static char pathBuffer[65536];
			std::string steamDllPath = GetSteamDllPath();
			std::string steamDirectory = steamDllPath.substr(0, steamDllPath.rfind('\\'));
			GetEnvironmentVariableA("PATH", pathBuffer, 0x10000);
			strcat_s(pathBuffer, ";");
			strcat_s(pathBuffer, steamDirectory.c_str());
			SetEnvironmentVariableA("PATH", pathBuffer);
			m_hSteamClient = LoadLibraryA(steamDllPath.c_str());
		}
	}
}

void *(*Steam::SteamLoader::GetCreateInterfaceFunc())(char const *, __int32 *) // 0x10C52220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetCreateInterfaceFunc@SteamLoader@Steam@@QAEP6APAXPBDPAH@ZXZ");

	return GetProcAddress<void *(__cdecl *)(char const *, int *)>("CreateInterface");
}

namespace Steam
{
	void *SteamLoader::GetProcAddressInternal(char const *name) // 0x10C52280
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetProcAddressInternal@SteamLoader@Steam@@AAEPAXPBD@Z");

		void *func = nullptr;
		if (m_hSteamClient)
			func = ::GetProcAddress(m_hSteamClient, name);  // hades: the member template GetProcAddress now shadows the Win32 one
		return func;
	}

	bool SteamLoader::IsSteamRunning(bool ignoreCreateFunc) // 0x10C52750
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsSteamRunning@SteamLoader@Steam@@QAE_N_N@Z");

		bool retval = false;
		DWORD pid = GetSteamProcessId();
		if (pid != 0)
		{
			HANDLE steamProcess = OpenProcess(0x1000, FALSE, pid);
			if (steamProcess != INVALID_HANDLE_VALUE)
			{
				CloseHandle(steamProcess);
				retval = true;
			}
		}

		if (!GetCreateInterfaceFunc() && !ignoreCreateFunc)
			retval = false;

		return retval;
	}

	unsigned __int32 SteamLoader::GetSteamProcessId() // 0x10C52470
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetSteamProcessId@SteamLoader@Steam@@AAEIXZ");

		DWORD pid;
		DWORD pidSize = sizeof(pid);

		if (RegGetValueA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", "pid", RRF_RT_REG_DWORD, nullptr, &pid, &pidSize) == ERROR_SUCCESS)
			return pid;

		return 0;
	}
}


namespace Steam
{
	std::string SteamLoader::GetSteamDllPath() // 0x10C52300
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetSteamDllPath@SteamLoader@Steam@@AAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

		char pathString[512];
		unsigned long pathStringSize = sizeof(pathString);
		if (RegGetValueA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", "SteamClientDll", RRF_RT_REG_SZ, nullptr, pathString, &pathStringSize) == ERROR_SUCCESS)
			return pathString;
		return "";
	}

	void SteamLoader::LoadGameOverlayRenderer(std::string const &baseDllPath) // 0x10C52820
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LoadGameOverlayRenderer@SteamLoader@Steam@@AAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		std::string overlayDllPath = baseDllPath.substr(0, baseDllPath.rfind('\\')) + "\\GameOverlayRenderer.dll";
		LoadLibraryA(overlayDllPath.c_str());
	}
}

/* ---------- private code */

template<typename t_arg0>
t_arg0 Steam::SteamLoader::GetProcAddress(char const *name) // 0x10C52170
{
	return reinterpret_cast<t_arg0>(GetProcAddressInternal(name));
}

/* ---------- explicit instantiations */
template void * (*Steam::SteamLoader::GetProcAddress<void * (__cdecl*)(char const *,int *)>(char const *name))(char const *, __int32 *);
