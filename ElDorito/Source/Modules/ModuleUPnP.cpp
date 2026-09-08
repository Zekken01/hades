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
//	<lambda_1>(Modules::ModuleUPnP *, bool const &, __int32 const &, __int32 const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
//private:
//	Modules::ModuleUPnP *__this; // 0x0
//	bool tcp; // 0x4
//	__int32 externalport; // 0x8
//	__int32 internalport; // 0xC
//	std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ruleName; // 0x10
//public:
//	Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1> &operator=(Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1>) == 44, "Invalid Modules::ModuleUPnP::UPnPForwardPort::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModuleUPnP* _sub_10A230D0(Modules::ModuleUPnP *const);
	ModuleUPnP::ModuleUPnP() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x10A230D0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleUPnP@Modules@@QAE@XZ");
		// Modules::ModuleUPnP *const this;
		todo("implement");
		_sub_10A230D0(this);
	}

	_inline ModuleUPnP::CachedIGD::~CachedIGD() // 0x10A233A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CachedIGD@ModuleUPnP@Modules@@QAE@XZ");
		// Modules::ModuleUPnP::CachedIGD *const this;

		compiler_generated();
	}

	_extern void _sub_10A235C0(Modules::ModuleUPnP *const, bool, __int32, __int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	void ModuleUPnP::UPnPForwardPort(bool tcp, __int32 externalport, __int32 internalport, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &ruleName) // 0x10A235C0
	{
		mangled_x86(MANGLED_TODO, "?UPnPForwardPort@ModuleUPnP@Modules@@QAEX_NHHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &ruleName;
		todo("implement");
		_sub_10A235C0(this, tcp, externalport, internalport, ruleName);
	}
}

namespace Utils
{
	extern UPnPResult _sub_10A23670(Modules::ModuleUPnP *const, bool, __int32, __int32, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
}

namespace Modules
{
	Utils::UPnPResult ModuleUPnP::UPnPForwardPort_Blocking(bool tcp, __int32 externalport, __int32 internalport, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &ruleName) // 0x10A23670
	{
		mangled_x86(MANGLED_TODO, "?UPnPForwardPort_Blocking@ModuleUPnP@Modules@@QAE?AUUPnPResult@Utils@@_NHHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10A23C1C
		// static ...; // 0x10A23BE0
		// static ...; // 0x10A23BD8
		// Modules::ModuleUPnP *const this;
		// bool tcp;
		// __int32 externalport;
		// __int32 internalport;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &ruleName;
		// std::unique_lock<std::mutex> lock;
		// char const *protocol;
		// __int32 ret;
		// Utils::UPnPErrorType type;
		{
			// char lanaddr[16];
			// __int32 ret;
			// IGDdatas data;
			// __int32 upnpDiscoverError;
			// UPNPDev *upnpDevice;
			// UPNPUrls urls;
		}
		todo("implement");
		Utils::UPnPResult __result = _sub_10A23670(this, tcp, externalport, internalport, ruleName);
		return __result;
	}

	_inline ModuleUPnP::CachedIGD::CachedIGD() // 0x10A23070
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CachedIGD@ModuleUPnP@Modules@@QAE@XZ");
		// Modules::ModuleUPnP::CachedIGD *const this;

		compiler_generated();
	}
}

/* ---------- private code */
