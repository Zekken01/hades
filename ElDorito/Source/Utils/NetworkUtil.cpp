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
		extern Utils::Network::EResolveAddressResult ResolveAddress(std::string const &hostname, unsigned __int32 *outAddr);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace Network
	{
		Utils::Network::EResolveAddressResult ResolveAddress(std::string const &hostname, unsigned __int32 *outAddr) // 0x1090D620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ResolveAddress@Network@Utils@@YA?AW4EResolveAddressResult@12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAI@Z");
			// static ...; // 0x1090D768
			// static ...; // 0x1090D760
			// std::string const &hostname;
			// unsigned __int32 *outAddr;
			// __int32 retval;
			// addrinfo *ptr;
			// addrinfo *info;
			// unsigned __int32 rawIpaddr;
				// __int32 error;
			// function call : __int32 (char const *, char const *, addrinfo const *, addrinfo **)
			// function call : __int32 ()
			// function call : unsigned long (unsigned long)
			// function call : void (addrinfo *)

			addrinfo *info = nullptr;
			__int32 retval = getaddrinfo(hostname.c_str(), nullptr, nullptr, &info);
			if (retval != 0)
			{
				__int32 error = WSAGetLastError();
				if (error)
				{
					if (error == WSAHOST_NOT_FOUND)
						return HostNotFound;
					else if (error == WSANO_DATA)
						return NoData;
					else
						return UnknownError;
				}
				else
					return UnknownError;
			}
			unsigned __int32 rawIpaddr = 0;
			addrinfo *ptr = nullptr;
			for (ptr = info; ptr != nullptr; ptr = ptr->ai_next)
			{
				if (ptr->ai_family != AF_INET)
					continue;
				rawIpaddr = ntohl(((sockaddr_in *)ptr->ai_addr)->sin_addr.S_un.S_addr);
				break;
			}
			freeaddrinfo(info);
			if (rawIpaddr == 0)
				return NoRecords;
			*outAddr = rawIpaddr;
			return Success;
		}
	}
}

/* ---------- private code */
