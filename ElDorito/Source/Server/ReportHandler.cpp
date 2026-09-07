/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
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
#include "Utils/DewritoReader.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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

namespace
{
	struct ReportRequest;
}

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

namespace
{
	struct ReportRequest
	{
		long long CreationTime; // 0x0
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > Token; // 0x8
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
/* ---------- prototypes */

namespace Server
{
	namespace ReportHandler
	{
		extern void Handle(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &token);
		extern void Tick();
		extern void Init();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern std::mutex mutex; // 0x12467960
	extern std::condition_variable signal; // 0x12467990
	extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > playerReportUrls; // 0x124679B8
	extern bool shouldExit; // 0x124679D8
}
/* ---------- public code */

namespace Server
{
	namespace ReportHandler
	{
		_extern void _sub_10B22A80(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		void Handle(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &token) // 0x10B22A80
		{
			mangled_x86(MANGLED_TODO, "?Handle@ReportHandler@Server@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10B22B8C
			// static ...; // 0x10B22B84
			// static ...; // 0x10B22B6C
			// static ...; // 0x10B22B64
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &token;
			{
				// std::lock_guard<std::mutex> guard;
				// ReportRequest request;
			}
			todo("implement");
			_sub_10B22A80(token);
		}

		_extern void _sub_10B23BF0();
		void Tick() // 0x10B23BF0
		{
			mangled_x86(MANGLED_TODO, "?Tick@ReportHandler@Server@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10B23BF0();
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
