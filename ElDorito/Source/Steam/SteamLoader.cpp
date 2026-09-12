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

extern void *(*_sub_10C52220(Steam::SteamLoader *const))(char const *, __int32 *);
void *(*Steam::SteamLoader::GetCreateInterfaceFunc())(char const *, __int32 *) // 0x10C52220
{
	mangled_x86(MANGLED_TODO, "?GetCreateInterfaceFunc@SteamLoader@Steam@@QAEP6APAXPBDPAH@ZXZ");
	// Steam::SteamLoader *const this;
	todo("implement");
	auto __result = _sub_10C52220(this);
	return __result;
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
			func = GetProcAddress(m_hSteamClient, name);
		return func;
	}

	_extern bool _sub_10C52750(Steam::SteamLoader *const, bool);
	bool SteamLoader::IsSteamRunning(bool ignoreCreateFunc) // 0x10C52750
	{
		mangled_x86(MANGLED_TODO, "?IsSteamRunning@SteamLoader@Steam@@QAE_N_N@Z");
		// bool ignoreCreateFunc;
		// bool retval;
		// unsigned __int32 pid;
		{
			// void *steamProcess;
		}
		// function call : void *(unsigned long, __int32, unsigned long)
		// function call : __int32 (void *)
		todo("implement");
		bool __result = _sub_10C52750(this, ignoreCreateFunc);
		return __result;
	}

	_extern unsigned __int32 _sub_10C52470(Steam::SteamLoader *const);
	unsigned __int32 SteamLoader::GetSteamProcessId() // 0x10C52470
	{
		mangled_x86(MANGLED_TODO, "?GetSteamProcessId@SteamLoader@Steam@@AAEIXZ");
		// static ...; // 0x10C5251C
		// static ...; // 0x10C52514
		// static ...; // 0x10C524FC
		// static ...; // 0x10C524F4
		// Steam::SteamLoader *const this;
		// unsigned long pid;
		// unsigned long pidSize;
		// function call : long (HKEY__ *, char const *, char const *, unsigned long, unsigned long *, void *, unsigned long *)
		todo("implement");
		unsigned __int32 __result = _sub_10C52470(this);
		return __result;
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
