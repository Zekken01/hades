/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Patches/Core.hpp"
#include "ThirdParty/HttpRequest.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/DewritoReader.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/WebSocket.hpp"

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
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
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

class HttpRequest;
struct begin;
struct end;
namespace hades_file_local
{
	struct ReportRequest;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace ReportHandler {}
	using namespace Server::ReportHandler;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct ReportRequest
	{
		long long CreationTime; // 0x0
		std::string Token; // 0x8
		ReportRequest(ReportRequest &); /* compiler_generated() */
		ReportRequest(ReportRequest const &); /* compiler_generated() */
		ReportRequest(); /* compiler_generated() */
		~ReportRequest(); /* compiler_generated() */
		ReportRequest &operator=(ReportRequest &); /* compiler_generated() */
		ReportRequest &operator=(ReportRequest const &); /* compiler_generated() */
		unsigned char __pad0[4]; // 0x24
	};
	static_assert(sizeof(ReportRequest) == 40, "Invalid ReportRequest size");

}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Server
{
	namespace ReportHandler
	{
		extern void Handle(std::string const &token);
		extern void Tick();
		extern void Init();
	}
}

void GetEndpoints();
bool ForwardReportToEndpoint(std::string const &endpoint, std::string const &report);
void ForwardReportToEndpoints(std::string const &report);
bool HandleReport(std::string const &token);
void HandleReports();
unsigned long HandledReportsThreadProc(void *lpParam);
void OnShutdown();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::mutex mutex; // 0x12467960
	extern std::condition_variable signal; // 0x12467990
	extern std::vector<std::string,std::allocator<std::string> > playerReportUrls; // 0x124679B8
	extern bool shouldExit; // 0x124679D8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace ReportHandler
	{
		_extern void _sub_10B22A80(std::string const &);
		void Handle(std::string const &token) // 0x10B22A80
		{
			mangled_x86(MANGLED_TODO, "?Handle@ReportHandler@Server@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10B22B8C
			// static ...; // 0x10B22B84
			// static ...; // 0x10B22B6C
			// static ...; // 0x10B22B64
			// std::string const &token;
			{
				// std::lock_guard<std::mutex> guard;
				// ReportRequest request;
			}
			todo("implement");
			_sub_10B22A80(token);
		}

		void Tick() // 0x10B23BF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ReportHandler@Server@@YAXXZ");
			// procedure flags: nofpo
		}

		_extern void _sub_10B23B10();
		void Init() // 0x10B23B10
		{
			mangled_x86(MANGLED_TODO, "?Init@ReportHandler@Server@@YAXXZ");
			// procedure flags: nofpo
			// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)
			todo("implement");
			_sub_10B23B10();
		}
	}
}

/* ---------- private code */

_extern void _sub_10B22890();
void GetEndpoints() // 0x10B22890
{
	// `anonymous-namespace'::GetEndpoints
	// procedure flags: nofpo
	// static ...; // 0x10B22A0C
	// static ...; // 0x10B22A00
	// static ...; // 0x10B229F8
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
	{
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &urls;
		{
			// unsigned __int32 i;
		}
	}
	todo("implement");
	_sub_10B22890();
}

_extern bool _sub_10B21ED0(std::string const &, std::string const &);
bool ForwardReportToEndpoint(std::string const &endpoint, std::string const &report) // 0x10B21ED0
{
	// `anonymous-namespace'::ForwardReportToEndpoint
	// static ...; // 0x10B22604
	// static ...; // 0x10B225F9
	// static ...; // 0x10B225F4
	// static ...; // 0x10B225EC
	// static ...; // 0x10B225B0
	// static ...; // 0x10B225A8
// $LN43:
// $LN44:
	// std::string const &endpoint;
	// std::string const &report;
	// std::wstring expected;
	// HttpRequest req;
	// std::wstring statusCode;
	// std::string resp;
	// std::basic_ofstream<char,std::char_traits<char> > logfile;
	todo("implement");
	bool __result = _sub_10B21ED0(endpoint, report);
	return __result;
}

_inline ReportRequest::ReportRequest(ReportRequest &__that) // 0x10B21560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0ReportRequest@hades_file_local@@QAE@AAU01@@Z");
	// `anonymous-namespace'::ReportRequest::ReportRequest
	// ReportRequest &__that;

	compiler_generated();
}

_inline ReportRequest::ReportRequest(ReportRequest const &__that) // 0x10B215E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0ReportRequest@hades_file_local@@QAE@ABU01@@Z");
	// `anonymous-namespace'::ReportRequest::ReportRequest
	// ReportRequest const &__that;

	compiler_generated();
}

_inline ReportRequest::ReportRequest() // 0x10B21660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0ReportRequest@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::ReportRequest::ReportRequest
	// ReportRequest *const this;

	compiler_generated();
}

_inline ReportRequest::~ReportRequest() // 0x10B218B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1ReportRequest@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::ReportRequest::~ReportRequest
	// ReportRequest *const this;

	compiler_generated();
}

extern ReportRequest &_sub_10B219D0(ReportRequest *const, ReportRequest &);
_inline ReportRequest &ReportRequest::operator=(ReportRequest &__that) // 0x10B219D0
{
	// `anonymous-namespace'::ReportRequest::operator=
	// ReportRequest &__that;
	compiler_generated();
	todo("implement");
	ReportRequest & __result = _sub_10B219D0(this, __that);
	return __result;
}

_extern void _sub_10B227F0(std::string const &);
void ForwardReportToEndpoints(std::string const &report) // 0x10B227F0
{
	// `anonymous-namespace'::ForwardReportToEndpoints
	// std::string const &report;
	{
		// std::vector<std::string,std::allocator<std::string> > &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
		{
			// std::string &endpoint;
		}
	}
	todo("implement");
	_sub_10B227F0(report);
}

_extern bool _sub_10B22BE0(std::string const &);
bool HandleReport(std::string const &token) // 0x10B22BE0
{
	// `anonymous-namespace'::HandleReport
	// static ...; // 0x10B23459
	// static ...; // 0x10B23451
	// static ...; // 0x10B23448
	// static ...; // 0x10B2343D
	// static ...; // 0x10B23438
	// static ...; // 0x10B23430
	// static ...; // 0x10B233E8
	// static ...; // 0x10B233E0
// $LN39:
// $LN10:
	// std::string const &token;
	// std::wstring expected;
	// HttpRequest req;
	// std::wstring statusCode;
	// std::string resp;
	// std::basic_ofstream<char,std::char_traits<char> > logfile;
	{
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> dewrito;
	}
	todo("implement");
	bool __result = _sub_10B22BE0(token);
	return __result;
}

_extern void _sub_10B23680();
void HandleReports() // 0x10B23680
{
	// `anonymous-namespace'::HandleReports
	// procedure flags: nofpo
	// static ...; // 0x10B238F4
	// static ...; // 0x10B238E8
	// static ...; // 0x10B238E0
	{
		// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<ReportRequest> > > it;
		{
			// long long deltaTime;
			// ReportRequest &request;
		}
	}
	todo("implement");
	_sub_10B23680();
}

_extern unsigned long _sub_10B239A0(void *);
unsigned long HandledReportsThreadProc(void *lpParam) // 0x10B239A0
{
	// `anonymous-namespace'::HandledReportsThreadProc
	// static ...; // 0x10B23AC4
	// static ...; // 0x10B23AC0
	// static ...; // 0x10B23AA8
	// static ...; // 0x10B23AA0
	// void *lpParam;
	{
		// std::unique_lock<std::mutex> lk;
		// std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > now;
	}
	todo("implement");
	unsigned long __result = _sub_10B239A0(lpParam);
	return __result;
}

_extern void _sub_10B23BA0();
void OnShutdown() // 0x10B23BA0
{
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo
	todo("implement");
	_sub_10B23BA0();
}
