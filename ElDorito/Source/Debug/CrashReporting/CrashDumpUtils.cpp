/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Debug {}
using namespace ::Debug;
namespace Debug
{
	namespace CrashReporting {}
	using namespace Debug::CrashReporting;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Debug
{
	namespace CrashReporting
	{
		extern bool IsRunningUnderProton();
		extern bool GetOSVersionInfo(_OSVERSIONINFOW *info);
		extern std::string GetFriendlyOSName();
		extern std::string GetCPUName();
		extern bool GetGPUInfo(std::string &description, std::string &driverVersion);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Debug
{
	namespace CrashReporting
	{
		bool IsRunningUnderProton() // 0x1068A850
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsRunningUnderProton@CrashReporting@Debug@@YA_NXZ");
			// procedure flags: nofpo
			// function call : unsigned long (char const *, char *, unsigned long)

			return GetEnvironmentVariableA("STEAM_COMPAT_DATA_PATH", nullptr, 0) > 0;
		}

		_extern bool _sub_1068A710(_OSVERSIONINFOW *);
		bool GetOSVersionInfo(_OSVERSIONINFOW *info) // 0x1068A710
		{
			mangled_x86(MANGLED_TODO, "?GetOSVersionInfo@CrashReporting@Debug@@YA_NPAU_OSVERSIONINFOW@@@Z");
			// _OSVERSIONINFOW *info;
			// long (*pRtlGetVersion)(_OSVERSIONINFOW *);
			// HINSTANCE__ *ntdll;
			// function call : HINSTANCE__ *(char const *)
			// function call : __int32 (*(HINSTANCE__ *, char const *))()
			// function call : long (*)(_OSVERSIONINFOW *)
			todo("implement");
			bool __result = _sub_1068A710(info);
			return __result;
		}
	}
}

extern std::string _sub_1068A260();
namespace Debug
{
	namespace CrashReporting
	{
		std::string GetFriendlyOSName() // 0x1068A260
		{
			mangled_x86(MANGLED_TODO, "?GetFriendlyOSName@CrashReporting@Debug@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			// static ...; // 0x1068A465
			// static ...; // 0x1068A458
			// static ...; // 0x1068A440
			// static ...; // 0x1068A438
			// char const *friendlyName;
			// _OSVERSIONINFOW ovi;
			todo("implement");
			std::string __result = _sub_1068A260();
			return __result;
		}
	}
}

extern std::string _sub_1068A060();
namespace Debug
{
	namespace CrashReporting
	{
		std::string GetCPUName() // 0x1068A060
		{
			mangled_x86(MANGLED_TODO, "?GetCPUName@CrashReporting@Debug@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			// static ...; // 0x1068A1F5
			// static ...; // 0x1068A1ED
			// static ...; // 0x1068A1E4
			// static ...; // 0x1068A1C0
			// static ...; // 0x1068A1B8
			// unsigned long dataSize;
			// HKEY__ *hKey;
			// long result;
			// char cpuName[256];
			// function call : long (HKEY__ *, char const *, unsigned long, unsigned long, HKEY__ **)
			// function call : long (HKEY__ *, char const *, unsigned long *, unsigned long *, unsigned char *, unsigned long *)
			// function call : long (HKEY__ *)
			// function call : long (HKEY__ *)
			todo("implement");
			std::string __result = _sub_1068A060();
			return __result;
		}

		_extern bool _sub_1068A4F0(std::string &, std::string &);
		bool GetGPUInfo(std::string &description, std::string &driverVersion) // 0x1068A4F0
		{
			mangled_x86(MANGLED_TODO, "?GetGPUInfo@CrashReporting@Debug@@YA_NAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// static ...; // 0x1068A68D
			// static ...; // 0x1068A682
			// static ...; // 0x1068A67C
			// static ...; // 0x1068A64C
			// static ...; // 0x1068A644
			// std::string &description;
			// std::string &driverVersion;
			// __int32 Build;
			// __int32 currentGpuAdapterIndex;
			// _D3DADAPTER_IDENTIFIER9 *adapter;
			// __int32 Product;
			// __int32 SubVersion;
			// __int32 gpuAdapterCount;
			// __int32 Version;
			todo("implement");
			bool __result = _sub_1068A4F0(description, driverVersion);
			return __result;
		}
	}
}

/* ---------- private code */
