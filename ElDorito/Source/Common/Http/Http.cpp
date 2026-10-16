/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpManager.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Common/Http/WinHttp/WinHttpCommon.hpp"
#include "Common/Http/WinHttp/WinHttpManager.hpp"
#include "Patches/CustomPackets.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/core/demangle.hpp>
#include <boost/exception/all.hpp>
#include <boost/function/function_base.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_index/stl_type_index.hpp>

#include <Windows.h>
#include <boost/current_function.hpp>
#include <boost/range/detail/implementation_help.hpp>
#include <boost/type_index.hpp>
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
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Http
{
	class CHttpManager;
	class IHttpRequest;
}

namespace Http {}
using namespace ::Http;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Http
{
	extern Http::CHttpManager &GetManager();
	extern std::shared_ptr<Http::IHttpRequest> CreateRequest();
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Http
{
	Http::CHttpManager &GetManager() // 0x107F7330
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetManager@Http@@YAAAVCHttpManager@1@XZ");

		return Http::CWinHttpManager::Instance();
	}
}


namespace Http
{
	std::shared_ptr<Http::IHttpRequest> CreateRequest() // 0x107F7290
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CreateRequest@Http@@YA?AV?$shared_ptr@VIHttpRequest@Http@@@std@@XZ");

		return GetManager().CreateRequest();
	}

}

/* ---------- private code */
