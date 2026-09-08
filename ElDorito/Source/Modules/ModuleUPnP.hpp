#ifndef __MODULES_MODULEUPNP_HPP__
#define __MODULES_MODULEUPNP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/UPnP.hpp"

#include <memory>
#include <mutex>
#include <string>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleUPnP;
	struct Command;
}
namespace Utils
{
	struct UPnPResult;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class ModuleUPnP :
		public Utils::Singleton<Modules::ModuleUPnP>,
		public Modules::ModuleBase
	{
	public:
		public:
		struct CachedIGD
		{
			char lanaddr[16]; // 0x0
			std::string controlUrl; // 0x10
			std::string serviceType; // 0x2C
			CachedIGD(CachedIGD &); /* compiler_generated() */
			CachedIGD(CachedIGD const &); /* compiler_generated() */
			_inline CachedIGD(); /* compiler_generated() */
			_inline ~CachedIGD(); /* compiler_generated() */
			CachedIGD &operator=(CachedIGD &); /* compiler_generated() */
			CachedIGD &operator=(CachedIGD const &); /* compiler_generated() */
		};
		static_assert(sizeof(CachedIGD) == 72, "Invalid CachedIGD size");
		public:
		static __int32 const IGDCacheDurationSecs;
		Modules::Command *VarUPnPEnabled; // 0x1C
	private:
		std::mutex mutex; // 0x20
		long long lastDiscover; // 0x50
		__int32 numPendingRequests; // 0x58
		CachedIGD cachedIGD; // 0x5C
	public:
		ModuleUPnP();
		Utils::UPnPResult UPnPForwardPort_Blocking(bool tcp, __int32 externalport, __int32 internalport, std::string const &ruleName);
		void UPnPForwardPort(bool tcp, __int32 externalport, __int32 internalport, std::string const &ruleName);
		~ModuleUPnP(); /* compiler_generated() */
	unsigned char __pad0[4]; // 0xA4
	};
	static_assert(sizeof(Modules::ModuleUPnP) == 168, "Invalid Modules::ModuleUPnP size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEUPNP_HPP__
