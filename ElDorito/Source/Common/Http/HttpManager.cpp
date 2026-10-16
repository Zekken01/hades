/* ---------- headers */

#include "Common/Http/HttpManager.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Patches/CustomPackets.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
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

struct begin;
struct end;
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

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Http
{
	void CHttpManager::AddRequest(std::shared_ptr<Http::IHttpRequest> request) // 0x108001A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddRequest@CHttpManager@Http@@QAEXV?$shared_ptr@VIHttpRequest@Http@@@std@@@Z");

		std::scoped_lock<std::mutex> lock(m_mutex);
		m_activeRequests.push_back(request);
	}

	bool CHttpManager::RemoveRequest(std::shared_ptr<Http::IHttpRequest> request) // 0x10800620
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RemoveRequest@CHttpManager@Http@@QAE_NV?$shared_ptr@VIHttpRequest@Http@@@std@@@Z");

		std::scoped_lock<std::mutex> lock(m_mutex);
		if (auto it = std::find(std::begin(m_activeRequests), std::end(m_activeRequests), request); it != std::end(m_activeRequests))
		{
			m_activeRequests.erase(it);
			return true;
		}
		return false;
	}
}


namespace Http
{
	std::shared_ptr<Http::IHttpRequest> CHttpManager::LockRequest(Http::IHttpRequest *request) // 0x10800460
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LockRequest@CHttpManager@Http@@QAE?AV?$shared_ptr@VIHttpRequest@Http@@@std@@PAVIHttpRequest@2@@Z");

		std::scoped_lock<std::mutex> lock(m_mutex);
		for (std::shared_ptr<Http::IHttpRequest> &req : m_activeRequests)
		{
			if (req.get() == request)
				return request->shared_from_this();
		}
		return nullptr;
	}

	void CHttpManager::CancelAllRequests() // 0x108002C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CancelAllRequests@CHttpManager@Http@@QAEXXZ");

		std::unique_lock<std::mutex> lock(m_mutex);
		std::vector<std::shared_ptr<Http::IHttpRequest> > list = m_activeRequests;
		lock.unlock();
		for (auto &request : m_activeRequests)
			request->Cancel();
	}
}

/* ---------- private code */
