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

#include <format>  // hades: added for 0x1068A4F0  // hades: added for 0x1068A4F0

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

			return GetEnvironmentVariableA("STEAM_COMPAT_DATA_PATH", nullptr, 0) > 0;
		}

		bool GetOSVersionInfo(_OSVERSIONINFOW *info) // 0x1068A710
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetOSVersionInfo@CrashReporting@Debug@@YA_NPAU_OSVERSIONINFOW@@@Z");

			HINSTANCE__ *ntdll = LoadLibraryA("ntdll.dll");
			if (!ntdll)
				return false;

			long (__stdcall *pRtlGetVersion)(_OSVERSIONINFOW *) = (long (__stdcall *)(_OSVERSIONINFOW *))GetProcAddress(ntdll, "RtlGetVersion");
			if (!pRtlGetVersion)
				return false;

			*info = { sizeof(_OSVERSIONINFOW) };
			return pRtlGetVersion(info) == 0;
		}
	}
}


namespace Debug
{
	namespace CrashReporting
	{
		std::string GetFriendlyOSName() // 0x1068A260
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetFriendlyOSName@CrashReporting@Debug@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

			if (IsRunningUnderProton())
				return "Proton";
			_OSVERSIONINFOW ovi;
			if (!GetOSVersionInfo(&ovi))
				return "Unknown";
			char const *friendlyName;
			if (ovi.dwMajorVersion == 10 && ovi.dwBuildNumber >= 22000)
				friendlyName = "Windows 11+";
			else if (ovi.dwMajorVersion == 10)
				friendlyName = "Windows 10";
			else if (ovi.dwMajorVersion == 6 && ovi.dwMinorVersion == 3)
				friendlyName = "Windows 8.1";
			else if (ovi.dwMajorVersion == 6 && ovi.dwMinorVersion == 2)
				friendlyName = "Windows 8";
			else if (ovi.dwMajorVersion == 6 && ovi.dwMinorVersion == 1)
				friendlyName = "Windows 7";
			else if (ovi.dwMajorVersion == 6 && ovi.dwMinorVersion == 0)
				friendlyName = "Windows Vista";
			else
				friendlyName = "Unknown";
			return std::format("{} Build {}", friendlyName, ovi.dwBuildNumber);
		}
	}
}


namespace Debug
{
	namespace CrashReporting
	{
		std::string GetCPUName() // 0x1068A060
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetCPUName@CrashReporting@Debug@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

			HKEY__ *hKey;
			long result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
			if (result != ERROR_SUCCESS)
				return "";
			char cpuName[256];
			unsigned long dataSize = sizeof(cpuName);
			result = RegQueryValueExA(hKey, "ProcessorNameString", nullptr, nullptr, (unsigned char *)cpuName, &dataSize);
			if (result != ERROR_SUCCESS)
			{
				RegCloseKey(hKey);
				return "";
			}
			RegCloseKey(hKey);
			return cpuName;
		}

		bool GetGPUInfo(std::string &description, std::string &driverVersion) // 0x1068A4F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetGPUInfo@CrashReporting@Debug@@YA_NAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");

			__int32 gpuAdapterCount = *(__int32 *)0x50DD6F0;
			if (!gpuAdapterCount)
				return false;
			__int32 currentGpuAdapterIndex = *(__int32 *)0x50DD9C4;
			_D3DADAPTER_IDENTIFIER9 *adapter = (_D3DADAPTER_IDENTIFIER9 *)(0x50DCA44 + currentGpuAdapterIndex * 0x658);
			__int32 Product = HIWORD(adapter->DriverVersion.HighPart);
			__int32 Version = LOWORD(adapter->DriverVersion.HighPart);
			__int32 SubVersion = HIWORD(adapter->DriverVersion.LowPart);
			__int32 Build = LOWORD(adapter->DriverVersion.LowPart);
			description = adapter->Description;
			driverVersion = std::format("{}.{}.{}.{}", Product, Version, SubVersion, Build);
			return true;
		}
	}
}

/* ---------- private code */
