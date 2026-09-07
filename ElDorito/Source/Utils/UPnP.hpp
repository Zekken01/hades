#ifndef __UTILS_UPNP_HPP__
#define __UTILS_UPNP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

namespace Utils
{
	struct UPnPResult;
}

/* ---------- constants */

namespace Utils
{
	enum UPnPIGDErrors
	{
		UPNP_IGD_NONE = 0,
		UPNP_IGD_VALID_CONNECTED,
		UPNP_IGD_VALID_NOT_CONNECTED,
		UPNP_IGD_INVALID,
	};
}

/* ---------- definitions */

namespace Utils
{
	struct UPnPResult
	{
		Utils::UPnPErrorType ErrorType; // 0x0
		__int32 ErrorCode; // 0x4
		_inline UPnPResult(Utils::UPnPErrorType type, __int32 code);
	};
	static_assert(sizeof(Utils::UPnPResult) == 8, "Invalid Utils::UPnPResult size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Utils
{
	extern UPnPResult* _sub_10A232C0(Utils::UPnPResult *const, Utils::UPnPErrorType, __int32);
	_inline UPnPResult::UPnPResult(Utils::UPnPErrorType type, __int32 code) // 0x10A232C0
	{
		mangled_x86(MANGLED_TODO, "??0UPnPResult@Utils@@QAE@W4UPnPErrorType@1@H@Z");
		// __int32 code;
		todo("implement");
		_sub_10A232C0(this, type, code);
	}
}

/* ---------- private code */

#endif // __UTILS_UPNP_HPP__
