/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Utils/Singleton.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10C56450
#include <iphlpapi.h>  // hades: added for 0x10C56450

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct _IP_ADAPTER_INFO;

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	extern std::string GetStackTraceString(__int32 framesToSkip, __int32 framesToCapture);
	extern void LogEthernetAdapterInfo();
	extern char const *GetLastErrorToText(unsigned long lastError);
	extern std::string GetLastErrorToString(unsigned long lastError);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */


namespace Utils
{
	std::string GetStackTraceString(__int32 framesToSkip, __int32 framesToCapture) // 0x10C56120
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetStackTraceString@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HH@Z");

		std::stringstream ss;
		std::vector<unsigned int> backTrace(framesToCapture);
		__int32 capturedFrames = RtlCaptureStackBackTrace(framesToSkip + 1, framesToCapture, (void **)backTrace.data(), nullptr);
		for (__int32 i = capturedFrames - 1; i >= 0; i--)
		{
			if (i == capturedFrames - 1)
				ss << "0x" << std::uppercase << std::hex << backTrace[i];
			else
				ss << "->" << "0x" << std::uppercase << std::hex << backTrace[i];
		}
		return ss.str();
	}

	void LogEthernetAdapterInfo() // 0x10C56450
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LogEthernetAdapterInfo@Utils@@YAXXZ");

		PIP_ADAPTER_INFO pAdapterInfo;
		PIP_ADAPTER_INFO pAdapter;
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "GetAdaptersInfo");
		DWORD dwRetVal = 0;
		ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
		if (pAdapterInfo == NULL)
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Error allocating memory needed to call GetAdaptersinfo");
			return;
		}
		if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
		{
			free(pAdapterInfo);
			pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
			if (pAdapterInfo == NULL)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Error allocating memory needed to call GetAdaptersinfo");
				return;
			}
		}
		dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen);
		if (dwRetVal == NO_ERROR)
		{
			pAdapter = pAdapterInfo;
			while (pAdapter)
			{
				if (std::string(pAdapter->IpAddressList.IpAddress.String).find("0.0.0.0") != std::string::npos)
				{
					pAdapter = pAdapter->Next;
					continue;
				}
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "\tAdapter Desc: \t%s", pAdapter->Description);
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "\tMAC Address: \t%02X:%02X:%02X:%02X:%02X:%02X", pAdapter->Address[0], pAdapter->Address[1], pAdapter->Address[2], pAdapter->Address[3], pAdapter->Address[4], pAdapter->Address[5]);
				switch (pAdapter->Type)
				{
				case MIB_IF_TYPE_ETHERNET:
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "\tAdapter Type: \tEthernet");
					break;
				case IF_TYPE_IEEE80211:
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "\tAdapter Type: \tWireless Ethernet");
					break;
				default:
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "\tAdapter Type: \tOther type %ld", pAdapter->Type);
					break;
				}
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "\tIP Address: \t%s", pAdapter->IpAddressList.IpAddress.String);
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "\tIP Mask: \t%s", pAdapter->IpAddressList.IpMask.String);
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "\tGateway: \t%s", pAdapter->GatewayList.IpAddress.String);
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "");
				pAdapter = pAdapter->Next;
			}
		}
		else
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "GetAdaptersInfo failed with error: %d", dwRetVal);
		}
		if (pAdapterInfo)
			free(pAdapterInfo);
	}
}


namespace Utils
{
	char const *GetLastErrorToText(unsigned long lastError) // 0x10C55FC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastErrorToText@Utils@@YAPBDK@Z");

		thread_local char buf[256];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, nullptr);
		for (char *ptr = &buf[strlen(buf) - 1]; ptr >= buf; ptr--)
		{
			if (*ptr == 10 || *ptr == 13)
				*ptr = 0;
			else
				break;
		}
		return buf;
	}
}


namespace Utils
{
	std::string GetLastErrorToString(unsigned long lastError) // 0x10C55F40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastErrorToString@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@K@Z");

		return GetLastErrorToText(lastError);
	}
}

/* ---------- private code */
