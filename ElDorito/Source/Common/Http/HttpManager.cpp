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
	_extern void _sub_108001A0(Http::CHttpManager *const, std::shared_ptr<Http::IHttpRequest>);
	void CHttpManager::AddRequest(std::shared_ptr<Http::IHttpRequest> request) // 0x108001A0
	{
		mangled_x86(MANGLED_TODO, "?AddRequest@CHttpManager@Http@@QAEXV?$shared_ptr@VIHttpRequest@Http@@@std@@@Z");
		// static ...; // 0x1080026C
		// static ...; // 0x10800264
		// Http::CHttpManager *const this;
		// std::shared_ptr<Http::IHttpRequest> request;
		// std::scoped_lock<std::mutex> lock;
		todo("implement");
		_sub_108001A0(this, request);
	}

	_extern bool _sub_10800620(Http::CHttpManager *const, std::shared_ptr<Http::IHttpRequest>);
	bool CHttpManager::RemoveRequest(std::shared_ptr<Http::IHttpRequest> request) // 0x10800620
	{
		mangled_x86(MANGLED_TODO, "?RemoveRequest@CHttpManager@Http@@QAE_NV?$shared_ptr@VIHttpRequest@Http@@@std@@@Z");
		// static ...; // 0x10800844
		// static ...; // 0x1080082C
		// static ...; // 0x10800824
		// Http::CHttpManager *const this;
		// std::shared_ptr<Http::IHttpRequest> request;
		// std::scoped_lock<std::mutex> lock;
		{
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Http::IHttpRequest> > > > it;
		}
		todo("implement");
		bool __result = _sub_10800620(this, request);
		return __result;
	}
}

extern std::shared_ptr<Http::IHttpRequest> _sub_10800460(Http::CHttpManager *const, Http::IHttpRequest *);
namespace Http
{
	std::shared_ptr<Http::IHttpRequest> CHttpManager::LockRequest(Http::IHttpRequest *request) // 0x10800460
	{
		mangled_x86(MANGLED_TODO, "?LockRequest@CHttpManager@Http@@QAE?AV?$shared_ptr@VIHttpRequest@Http@@@std@@PAVIHttpRequest@2@@Z");
		// static ...; // 0x108005AC
		// static ...; // 0x108005A4
		// Http::CHttpManager *const this;
		// Http::IHttpRequest *request;
		// std::scoped_lock<std::mutex> lock;
		{
			// std::vector<std::shared_ptr<Http::IHttpRequest> > &<range>$L0;
			// std::shared_ptr<Http::IHttpRequest> *<begin>$L0;
			// std::shared_ptr<Http::IHttpRequest> *<end>$L0;
			{
				// std::shared_ptr<Http::IHttpRequest> &req;
			}
		}
		todo("implement");
		std::shared_ptr<Http::IHttpRequest> __result = _sub_10800460(this, request);
		return __result;
	}

	_extern void _sub_108002C0(Http::CHttpManager *const);
	void CHttpManager::CancelAllRequests() // 0x108002C0
	{
		mangled_x86(MANGLED_TODO, "?CancelAllRequests@CHttpManager@Http@@QAEXXZ");
		// static ...; // 0x10800405
		// static ...; // 0x10800400
		// static ...; // 0x108003E8
		// static ...; // 0x108003E0
		// Http::CHttpManager *const this;
		// std::vector<std::shared_ptr<Http::IHttpRequest> > list;
		// std::unique_lock<std::mutex> lock;
		{
			// std::vector<std::shared_ptr<Http::IHttpRequest> > &<range>$L0;
			// std::shared_ptr<Http::IHttpRequest> *<begin>$L0;
			// std::shared_ptr<Http::IHttpRequest> *<end>$L0;
			{
				// std::shared_ptr<Http::IHttpRequest> &request;
			}
		}
		// function call : void ()
		todo("implement");
		_sub_108002C0(this);
	}
}

/* ---------- private code */
