/* ---------- headers */

#include "Common/Http/WinHttp/WinHttpManager.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpManager.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Common/Http/WinHttp/WinHttpCommon.hpp"
#include "Common/Http/WinHttp/WinHttpRequest.hpp"
#include "Patches/CustomPackets.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

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
	class CWinHttpManager;
	class IHttpRequest;
	struct WinHttpHandlerDeleter;
}

namespace Http {}
using namespace ::Http;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Http
{
	extern CWinHttpManager* _sub_10803520(Http::CWinHttpManager *const);
	CWinHttpManager::CWinHttpManager() // 0x10803520
	{
		mangled_x86(MANGLED_TODO, "??0CWinHttpManager@Http@@AAE@XZ");
		// Http::CWinHttpManager *const this;
		// function call : unsigned long ()
		todo("implement");
		_sub_10803520(this);
	}
}

extern std::unique_ptr<void *,Http::WinHttpHandlerDeleter> _sub_108039C0(Http::CWinHttpManager *const);
namespace Http
{
	std::unique_ptr<void *,Http::WinHttpHandlerDeleter> CWinHttpManager::CreateSession() // 0x108039C0
	{
		mangled_x86(MANGLED_TODO, "?CreateSession@CWinHttpManager@Http@@QAE?AV?$unique_ptr@PAXUWinHttpHandlerDeleter@Http@@@std@@XZ");
		// static ...; // 0x10803AE6
		// static ...; // 0x10803ADC
		// static ...; // 0x10803AD8
		// static ...; // 0x10803AB4
		// static ...; // 0x10803AAC
		// Http::CWinHttpManager *const this;
		// unsigned long protocols;
		// unsigned long val;
		// std::unique_ptr<void *,Http::WinHttpHandlerDeleter> session;
		// function call : void *(wchar_t const *, unsigned long, wchar_t const *, wchar_t const *, unsigned long)
		// function call : __int32 (void *, unsigned long, void *, unsigned long)
		// function call : __int32 (void *, unsigned long, void *, unsigned long)
		todo("implement");
		std::unique_ptr<void *,Http::WinHttpHandlerDeleter> __result = _sub_108039C0(this);
		return __result;
	}
}

extern std::shared_ptr<Http::IHttpRequest> _sub_10803910(Http::CWinHttpManager *const);
namespace Http
{
	std::shared_ptr<Http::IHttpRequest> CWinHttpManager::CreateRequest() // 0x10803910
	{
		mangled_x86(MANGLED_TODO, "?CreateRequest@CWinHttpManager@Http@@UAE?AV?$shared_ptr@VIHttpRequest@Http@@@std@@XZ");
		// Http::CWinHttpManager *const this;
		todo("implement");
		std::shared_ptr<Http::IHttpRequest> __result = _sub_10803910(this);
		return __result;
	}
}

/* ---------- private code */
