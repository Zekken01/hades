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
	CWinHttpManager::CWinHttpManager() : m_sessHandle(CreateSession()) /* hades-mem-init:  */ // 0x10803520
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CWinHttpManager@Http@@AAE@XZ");

		if (!m_sessHandle)
		{
			throw std::system_error(GetLastError(), std::system_category());
		}
	}
}


namespace Http
{
	std::unique_ptr<void *,Http::WinHttpHandlerDeleter> CWinHttpManager::CreateSession() // 0x108039C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CreateSession@CWinHttpManager@Http@@QAE?AV?$unique_ptr@PAXUWinHttpHandlerDeleter@Http@@@std@@XZ");

		std::unique_ptr<void *,Http::WinHttpHandlerDeleter> session(WinHttpOpen(nullptr, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, WINHTTP_FLAG_ASYNC));
		unsigned long protocols = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1 | WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_1 | WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2;
		WinHttpSetOption(session.get(), WINHTTP_OPTION_SECURE_PROTOCOLS, &protocols, sizeof(protocols));
		unsigned long val = WINHTTP_DISABLE_COOKIES;
		WinHttpSetOption(session.get(), WINHTTP_OPTION_DISABLE_FEATURE, &val, sizeof(val));
		return session;
	}
}


namespace Http
{
	std::shared_ptr<Http::IHttpRequest> CWinHttpManager::CreateRequest() // 0x10803910
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CreateRequest@CWinHttpManager@Http@@UAE?AV?$shared_ptr@VIHttpRequest@Http@@@std@@XZ");

		return std::make_shared<Http::CWinHttpRequest>(*this);
	}
}

/* ---------- private code */
