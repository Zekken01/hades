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
	_extern void _sub_10C52550(Steam::SteamLoader *const);
	void SteamLoader::Initialize() // 0x10C52550
	{
		mangled_x86(MANGLED_TODO, "?Initialize@SteamLoader@Steam@@QAEXXZ");
		// static ...; // 0x10C526D3
		// static ...; // 0x10C526C4
		// static ...; // 0x10C526AC
		// static ...; // 0x10C526A4
		// Steam::SteamLoader *const this;
		{
			// static char pathBuffer[65536]; // 0x1246B930
			// std::string steamDllPath;
			// std::string steamDirectory;
		}
		// function call : unsigned long (char const *, char *, unsigned long)
		// function call : __int32 (char const *, char const *)
		// function call : HINSTANCE__ *(char const *)
		todo("implement");
		_sub_10C52550(this);
	}
}

void *(*Steam::SteamLoader::GetCreateInterfaceFunc())(char const *, __int32 *) // 0x10C52220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetCreateInterfaceFunc@SteamLoader@Steam@@QAEP6APAXPBDPAH@ZXZ");
	// Steam::SteamLoader *const this;

	return GetProcAddress<void *(__cdecl *)(char const *, int *)>("CreateInterface");
}

namespace Steam
{
	void *SteamLoader::GetProcAddressInternal(char const *name) // 0x10C52280
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetProcAddressInternal@SteamLoader@Steam@@AAEPAXPBD@Z");
		// char const *name;
		// void *func;
		// function call : __int32 (*(HINSTANCE__ *, char const *))()

		void *func = nullptr;
		if (m_hSteamClient)
			func = ::GetProcAddress(m_hSteamClient, name);  // hades: the member template GetProcAddress now shadows the Win32 one
		return func;
	}

	bool SteamLoader::IsSteamRunning(bool ignoreCreateFunc) // 0x10C52750
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsSteamRunning@SteamLoader@Steam@@QAE_N_N@Z");
		// bool ignoreCreateFunc;
		// bool retval;
		// unsigned __int32 pid;
			// void *steamProcess;
		// function call : void *(unsigned long, __int32, unsigned long)
		// function call : __int32 (void *)

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
		// static ...; // 0x10C5251C
		// static ...; // 0x10C52514
		// static ...; // 0x10C524FC
		// static ...; // 0x10C524F4
		// Steam::SteamLoader *const this;
		// unsigned long pid;
		// unsigned long pidSize;
		// function call : long (HKEY__ *, char const *, char const *, unsigned long, unsigned long *, void *, unsigned long *)

		DWORD pid;
		DWORD size = sizeof(pid);

		if (RegGetValueA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", "pid", RRF_RT_REG_DWORD, nullptr, &pid, &size) == ERROR_SUCCESS)
			return pid;

		return 0;
	}
}

extern std::string _sub_10C52300(Steam::SteamLoader *const);
namespace Steam
{
	std::string SteamLoader::GetSteamDllPath() // 0x10C52300
	{
		mangled_x86(MANGLED_TODO, "?GetSteamDllPath@SteamLoader@Steam@@AAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x10C52417
		// static ...; // 0x10C52408
		// static ...; // 0x10C523F0
		// static ...; // 0x10C523E8
		// Steam::SteamLoader *const this;
		// char pathString[512];
		// unsigned long pathStringSize;
		// function call : long (HKEY__ *, char const *, char const *, unsigned long, unsigned long *, void *, unsigned long *)
		todo("implement");
		std::string __result = _sub_10C52300(this);
		return __result;
	}

	_extern void _sub_10C52820(Steam::SteamLoader *const, std::string const &);
	void SteamLoader::LoadGameOverlayRenderer(std::string const &baseDllPath) // 0x10C52820
	{
		mangled_x86(MANGLED_TODO, "?LoadGameOverlayRenderer@SteamLoader@Steam@@AAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10C52928
		// static ...; // 0x10C52920
		// Steam::SteamLoader *const this;
		// std::string const &baseDllPath;
		// std::string overlayDllPath;
		// function call : HINSTANCE__ *(char const *)
		todo("implement");
		_sub_10C52820(this, baseDllPath);
	}
}

/* ---------- private code */

/* ---------- explicit instantiations */
template void * (*Steam::SteamLoader::GetProcAddress<void * (__cdecl*)(char const *,int *)>(char const *name))(char const *, __int32 *);
