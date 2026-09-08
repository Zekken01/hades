#ifndef __UTILS_NETWORKUTIL_HPP__
#define __UTILS_NETWORKUTIL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <string>

/* ---------- constants */

namespace Utils
{
	namespace Network
	{
		enum EResolveAddressResult
		{
			Success = 0,
			NoData,
			HostNotFound,
			NoRecords,
			UnknownError,
		};
	}
}

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

/* ---------- public code */

/* ---------- private code */

#endif // __UTILS_NETWORKUTIL_HPP__
