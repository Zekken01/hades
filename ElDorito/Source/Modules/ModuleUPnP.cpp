/* ---------- headers */

#include "Modules/ModuleUPnP.hpp"
#include "hades/hades.h"

#include "Job/JobDefinitions.hpp"
#include "Modules/ModuleBase.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/UPnP.hpp"

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

/* ---------- forward declarations */

struct lambda_1;
namespace Modules
{
	class ModuleBase;
	class ModuleUPnP;
}
namespace Utils
{
	struct UPnPResult;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

//class Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1>
//{
//public:
//	EJobResult operator()() const;
//	<lambda_1>(Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1> &);
//	<lambda_1>(Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1> const &);
//	<lambda_1>(Modules::ModuleUPnP *, bool const &, __int32 const &, __int32 const &, std::string const &);
//private:
//	Modules::ModuleUPnP *__this; // 0x0
//	bool tcp; // 0x4
//	__int32 externalport; // 0x8
//	__int32 internalport; // 0xC
//	std::string const ruleName; // 0x10
//public:
//	Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1> &operator=(Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1>) == 44, "Invalid Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Job { extern void RunJob(std::function<EJobResult __cdecl(void)> function, SJobCounter *counter, __int32 priority); }  // hades: added for 0x10A235C0  // hades: added for 0x10A235C0

#define MINIUPNP_STATICLIB  // hades: added for 0x10A23670  // hades: added for 0x10A23670
#include <miniupnpc/miniupnpc.h>  // hades: added for 0x10A23670  // hades: added for 0x10A23670
#include <miniupnpc/upnpcommands.h>  // hades: added for 0x10A23670  // hades: added for 0x10A23670
#include "Utils/Logger.hpp"  // hades: added for 0x10A23670  // hades: added for 0x10A23670

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModuleUPnP::ModuleUPnP() : ModuleBase("UPnP"), lastDiscover(0), numPendingRequests(0) /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x10A230D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleUPnP@Modules@@QAE@XZ");
		// Modules::ModuleUPnP *const this;

		VarUPnPEnabled = AddVariableInt("Enabled", "upnp_enabled", "Enables UPnP to automatically port forward when hosting a game.", eCommandFlagsArchived, 1);
		VarUPnPEnabled->ValueIntMin = 0;
		VarUPnPEnabled->ValueIntMax = 1;
	}

	// mangled_x86(MANGLED_DEFAULT, "??1CachedIGD@ModuleUPnP@Modules@@QAE@XZ"); no body to assert in
	_inline ModuleUPnP::CachedIGD::~CachedIGD() = default; // 0x10A233A0

	void ModuleUPnP::UPnPForwardPort(bool tcp, __int32 externalport, __int32 internalport, std::string const &ruleName) // 0x10A235C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UPnPForwardPort@ModuleUPnP@Modules@@QAEX_NHHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &ruleName;

		Job::RunJob([this, tcp, externalport, internalport, ruleName]()
		{
			UPnPForwardPort_Blocking(tcp, externalport, internalport, ruleName);
			return Done;
		}, nullptr, 0);
	}
}

namespace Utils
{

}

namespace Modules
{
	Utils::UPnPResult ModuleUPnP::UPnPForwardPort_Blocking(bool tcp, __int32 externalport, __int32 internalport, std::string const &ruleName) // 0x10A23670
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UPnPForwardPort_Blocking@ModuleUPnP@Modules@@QAE?AUUPnPResult@Utils@@_NHHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10A23C1C
		// static ...; // 0x10A23BE0
		// static ...; // 0x10A23BD8
		// Modules::ModuleUPnP *const this;
		// bool tcp;
		// __int32 externalport;
		// __int32 internalport;
		// std::string const &ruleName;
		// std::unique_lock<std::mutex> lock;
		// char const *protocol;
		// __int32 ret;
		// Utils::UPnPErrorType type;
			// char lanaddr[16];
			// __int32 ret;
			// IGDdatas data;
			// __int32 upnpDiscoverError;
			// UPNPDev *upnpDevice;
			// UPNPUrls urls;

		std::unique_lock<std::mutex> lock(mutex);
		if (lastDiscover == 0 || (difftime(time(nullptr), lastDiscover) >= 3600.0 && numPendingRequests == 0))
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "UPnP: Discovery started");
			__int32 upnpDiscoverError;
			UPNPDev *upnpDevice = upnpDiscover(2000, nullptr, nullptr, 0, 0, 2, &upnpDiscoverError);
			if (upnpDiscoverError != 0 || !upnpDevice)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "UPnP: Discovery failed. Error: %d", upnpDiscoverError);
				return Utils::UPnPResult(Utils::DiscoveryError, upnpDiscoverError);
			}
			UPNPUrls urls;
			IGDdatas data;
			char lanaddr[16];
			__int32 ret = UPNP_GetValidIGD(upnpDevice, &urls, &data, lanaddr, sizeof(lanaddr));
			if (ret != 1)
			{
				freeUPNPDevlist(upnpDevice);
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "UPnP: Failed to find valid IGD. Error: %d", ret);
				return Utils::UPnPResult(Utils::IGDError, ret);
			}
			memcpy(cachedIGD.lanaddr, lanaddr, sizeof(lanaddr));
			cachedIGD.controlUrl = urls.controlURL;
			cachedIGD.serviceType = data.first.servicetype;
			lastDiscover = time(nullptr);
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "UPnP: Found valid IGD '%s'", cachedIGD.controlUrl.c_str());
			FreeUPNPUrls(&urls);
			freeUPNPDevlist(upnpDevice);
		}
		numPendingRequests++;
		lock.unlock();
		char const *protocol = tcp ? "TCP" : "UDP";
		__int32 ret = UPNP_AddPortMapping(cachedIGD.controlUrl.c_str(), cachedIGD.serviceType.c_str(), std::to_string(externalport).c_str(), std::to_string(internalport).c_str(), cachedIGD.lanaddr, ruleName.c_str(), protocol, nullptr, nullptr);
		Utils::UPnPErrorType type;
		if (ret != 0)
		{
			type = Utils::PortMapError;
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "UPnP Failed to add port mapping. Error: %d", ret);
		}
		else
		{
			type = (Utils::UPnPErrorType)0;
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "UPnP: Successfully added %s port mapping '%s' %d -> %d", protocol, ruleName.c_str(), externalport, internalport);
		}
		lock.lock();
		numPendingRequests--;
		return Utils::UPnPResult(type, ret);
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CachedIGD@ModuleUPnP@Modules@@QAE@XZ"); no body to assert in
}

/* ---------- private code */
