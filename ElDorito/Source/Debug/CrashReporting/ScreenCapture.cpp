/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
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
#include <cstddef>
#include <cstdlib>
#include <exception>
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

namespace Utils {}
using namespace ::Utils;
namespace Debug {}
using namespace ::Debug;
namespace Debug
{
	namespace CrashReporting {}
	using namespace Debug::CrashReporting;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Debug
{
	namespace CrashReporting
	{
		extern std::string TakeScreenshot();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern std::string _sub_106978B0();
namespace Debug
{
	namespace CrashReporting
	{
		std::string TakeScreenshot() // 0x106978B0
		{
			mangled_x86(MANGLED_TODO, "?TakeScreenshot@CrashReporting@Debug@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			// static ...; // 0x10697CD8
			// static ...; // 0x10697CD4
			// static ...; // 0x10697CD0
			// static ...; // 0x10697CAC
			// static ...; // 0x10697CA4
		// $LN19:
			{
				// HBITMAP__ *bmpDest;
				// HWND__ *hwndSrc;
				// unsigned char *bits;
				// tagRECT rc;
				// __int32 sx;
				// std::vector<unsigned char> buf;
				// __int32 sy;
				// HDC__ *dcSrc;
				// HDC__ *dcDst;
				// tagBITMAPINFO bmi;
			}
			// function call : __int32 (HWND__ *, tagRECT *)
			// function call : HDC__ *(HWND__ *)
			// function call : HDC__ *(HDC__ *)
			// function call : HBITMAP__ *(HDC__ *, __int32, __int32)
			// function call : void *(HDC__ *, void *)
			// function call : __int32 (HDC__ *, __int32, __int32, __int32, __int32, HDC__ *, __int32, __int32, unsigned long)
			// function call : __int32 (HDC__ *, HBITMAP__ *, unsigned __int32, unsigned __int32, void *, tagBITMAPINFO *, unsigned __int32)
			// function call : __int32 (HDC__ *, HBITMAP__ *, unsigned __int32, unsigned __int32, void *, tagBITMAPINFO *, unsigned __int32)
			todo("implement");
			std::string __result = _sub_106978B0();
			return __result;
		}
	}
}

/* ---------- private code */
