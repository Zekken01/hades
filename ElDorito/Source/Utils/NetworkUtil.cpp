/* ---------- headers */

#include "Utils/NetworkUtil.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <ws2ipdef.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace Network {}
	using namespace Utils::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	namespace Network
	{
		extern Utils::Network::EResolveAddressResult ResolveAddress(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &hostname, unsigned __int32 *outAddr);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace Network
	{
		extern EResolveAddressResult _sub_1090D620(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned __int32 *);
		Utils::Network::EResolveAddressResult ResolveAddress(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &hostname, unsigned __int32 *outAddr) // 0x1090D620
		{
			mangled_x86(MANGLED_TODO, "?ResolveAddress@Network@Utils@@YA?AW4EResolveAddressResult@12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAI@Z");
			// static ...; // 0x1090D768
			// static ...; // 0x1090D760
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &hostname;
			// unsigned __int32 *outAddr;
			// __int32 retval;
			// addrinfo *ptr;
			// addrinfo *info;
			// unsigned __int32 rawIpaddr;
			{
				// __int32 error;
			}
			// function call : __int32 (char const *, char const *, addrinfo const *, addrinfo **)
			// function call : __int32 ()
			// function call : unsigned long (unsigned long)
			// function call : void (addrinfo *)
			todo("implement");
			Utils::Network::EResolveAddressResult __result = _sub_1090D620(hostname, outAddr);
			return __result;
		}
	}
}

/* ---------- private code */
