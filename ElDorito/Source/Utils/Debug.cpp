/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Utils/Singleton.hpp"

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
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetStackTraceString(__int32 framesToSkip, __int32 framesToCapture);
	extern void LogEthernetAdapterInfo();
	extern char const *GetLastErrorToText(unsigned long lastError);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastErrorToString(unsigned long lastError);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C56120(__int32, __int32);
namespace Utils
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetStackTraceString(__int32 framesToSkip, __int32 framesToCapture) // 0x10C56120
	{
		mangled_x86(MANGLED_TODO, "?GetStackTraceString@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HH@Z");
		// static ...; // 0x10C56398
		// static ...; // 0x10C56380
		// static ...; // 0x10C56378
		// __int32 framesToSkip;
		// __int32 framesToCapture;
		// std::vector<unsigned int,std::allocator<unsigned int> > backTrace;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		// __int32 capturedFrames;
		{
			// __int32 i;
		}
		// function call : unsigned short (unsigned long, unsigned long, void **, unsigned long *)
		todo("implement");
		std::string __result = _sub_10C56120(framesToSkip, framesToCapture);
		return __result;
	}

	_extern void _sub_10C56450();
	void LogEthernetAdapterInfo() // 0x10C56450
	{
		mangled_x86(MANGLED_TODO, "?LogEthernetAdapterInfo@Utils@@YAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x10C569B8
		// static ...; // 0x10C569AC
		// static ...; // 0x10C569A4
		// _IP_ADAPTER_INFO *pAdapterInfo;
		// _IP_ADAPTER_INFO *pAdapter;
		// unsigned long dwRetVal;
		// unsigned long ulOutBufLen;
		// function call : unsigned long (_IP_ADAPTER_INFO *, unsigned long *)
		// function call : unsigned long (_IP_ADAPTER_INFO *, unsigned long *)
		todo("implement");
		_sub_10C56450();
	}
}

extern char const *_sub_10C55FC0(unsigned long);
namespace Utils
{
	char const *GetLastErrorToText(unsigned long lastError) // 0x10C55FC0
	{
		mangled_x86(MANGLED_TODO, "?GetLastErrorToText@Utils@@YAPBDK@Z");
		// unsigned long lastError;
		// thread_local char buf[256]; // 0x12579430
		{
			// char *ptr;
		}
		// function call : unsigned long (unsigned long, void const *, unsigned long, unsigned long, char *, unsigned long, char **)
		todo("implement");
		char const * __result = _sub_10C55FC0(lastError);
		return __result;
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C55F40(unsigned long);
namespace Utils
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastErrorToString(unsigned long lastError) // 0x10C55F40
	{
		mangled_x86(MANGLED_TODO, "?GetLastErrorToString@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@K@Z");
		// unsigned long lastError;
		todo("implement");
		std::string __result = _sub_10C55F40(lastError);
		return __result;
	}
}

/* ---------- private code */
