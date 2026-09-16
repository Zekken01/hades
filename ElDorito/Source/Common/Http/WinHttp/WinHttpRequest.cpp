/* ---------- headers */

#include "Common/Http/WinHttp/WinHttpRequest.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpManager.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Common/Http/WinHttp/WinHttpCommon.hpp"
#include "Common/Http/WinHttp/WinHttpManager.hpp"
#include "Console/Console.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/String.hpp"

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
#include <iosfwd>
#include <limits>
#include <map>
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

namespace Http
{
	class CHttpHeaders;
	class CWinHttpManager;
	class CWinHttpRequest;
	class CWinHttpResponse;
	class IHttpRequest;
	class IHttpResponse;
	struct WinHttpErrorCategory;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace Uri {}
	using namespace Utils::Uri;
}

namespace Console {}
using namespace ::Console;
namespace Http {}
using namespace ::Http;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Http
{
	__int32 QueryStatusCode(void *handle);
	void QueryHeaders(void *handle, Http::CHttpHeaders &headers, bool request);
}

/* ---------- globals */

template <typename ...Args> void DebugTrace(char const *format, Args &&...args);

/* ---------- private variables */

/* ---------- public code */

namespace Http
{
	// mangled_x86(MANGLED_DEFAULT, "??0CHttpHeaders@Http@@QAE@ABV01@@Z"); no body to assert in
	_inline CHttpHeaders::CHttpHeaders(Http::CHttpHeaders const &__that) = default; // 0x10806D20

	bool CWinHttpResponse::Process(Http::CWinHttpRequest &request) // 0x10809540
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Process@CWinHttpResponse@Http@@QAE_NAAVCWinHttpRequest@2@@Z");
		// Http::CWinHttpRequest &request;
		// void *reqHandle;

		void *reqHandle = request.GetRequestHandle();
		m_responseCode = QueryStatusCode(reqHandle);
		QueryHeaders(reqHandle, m_headers, false);
		return true;
	}

	CWinHttpRequest::CWinHttpRequest(Http::CWinHttpManager &winhttpManager) : m_winhttpManager(winhttpManager), m_maxRedirects(20), m_redirectCount(0) /* hades-mem-init: : m_winhttpManager(winhttpManager) */ // 0x10806DE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CWinHttpRequest@Http@@QAE@AAVCWinHttpManager@1@@Z");
		// Http::CWinHttpManager &winhttpManager;
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CWinHttpResponse@Http@@QAE@XZ"); no body to assert in

	// mangled_x86(MANGLED_DEFAULT, "??0IHttpRequest@Http@@QAE@XZ"); no body to assert in

	// mangled_x86(MANGLED_DEFAULT, "??0IHttpResponse@Http@@QAE@XZ"); no body to assert in

	// mangled_x86(MANGLED_DEFAULT, "??0WinHttpErrorCategory@Http@@QAE@XZ"); no body to assert in

	bool CWinHttpRequest::IsComplete() const // 0x108094E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsComplete@CWinHttpRequest@Http@@UBE_NXZ");
		// Http::CWinHttpRequest const *const this;

		return m_bIsCompleted;
	}

	// mangled_x86(MANGLED_DEFAULT, "??1CHttpHeaders@Http@@QAE@XZ"); no body to assert in
	_inline CHttpHeaders::~CHttpHeaders() = default; // 0x10807570
}

extern std::shared_ptr<Http::IHttpResponse> _sub_10808A90(Http::CWinHttpRequest *const);
namespace Http
{
	std::shared_ptr<Http::IHttpResponse> CWinHttpRequest::GetResponse() // 0x10808A90
	{
		mangled_x86(MANGLED_TODO, "?GetResponse@CWinHttpRequest@Http@@UAE?AV?$shared_ptr@VIHttpResponse@Http@@@std@@XZ");
		// Http::CWinHttpRequest *const this;
		todo("implement");
		std::shared_ptr<Http::IHttpResponse> __result = _sub_10808A90(this);
		return __result;
	}

	// mangled_x86(MANGLED_DEFAULT, "??1CWinHttpResponse@Http@@QAE@XZ"); no body to assert in
	_inline CWinHttpResponse::~CWinHttpResponse() = default; // 0x108076C0

	// mangled_x86(MANGLED_DEFAULT, "??4CHttpHeaders@Http@@QAEAAV01@ABV01@@Z"); no body to assert in
	_inline Http::CHttpHeaders &CHttpHeaders::operator=(Http::CHttpHeaders const &__that) = default; // 0x10807C10

	_extern void _sub_1080A540(Http::CWinHttpRequest *const, std::string);
	void CWinHttpRequest::SetMethod(std::string method) // 0x1080A540
	{
		mangled_x86(MANGLED_TODO, "?SetMethod@CWinHttpRequest@Http@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string method;
		todo("implement");
		_sub_1080A540(this, method);
	}

	_extern void _sub_1080A840(Http::CWinHttpRequest *const, std::string);
	void CWinHttpRequest::SetUrl(std::string url) // 0x1080A840
	{
		mangled_x86(MANGLED_TODO, "?SetUrl@CWinHttpRequest@Http@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string url;
		todo("implement");
		_sub_1080A840(this, url);
	}

	void CWinHttpRequest::SetMaxRedirects(__int32 count) // 0x1080A510
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetMaxRedirects@CWinHttpRequest@Http@@UAEXH@Z");
		// __int32 count;

		m_maxRedirects = count;
	}

	_extern void _sub_1080A3F0(Http::CWinHttpRequest *const, std::string &);
	void CWinHttpRequest::SetBody(std::string &&body) // 0x1080A3F0
	{
		mangled_x86(MANGLED_TODO, "?SetBody@CWinHttpRequest@Http@@UAEX$$QAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string &body;
		todo("implement");
		_sub_1080A3F0(this, body);
	}

	void CWinHttpRequest::SetHeaders(Http::CHttpHeaders headers) // 0x1080A460
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetHeaders@CWinHttpRequest@Http@@UAEXVCHttpHeaders@2@@Z");
		// Http::CHttpHeaders headers;

		m_headers = headers;
	}

	_extern void _sub_1080A720(Http::CWinHttpRequest *const, std::function<bool __cdecl(char const *,unsigned int)> &);
	void CWinHttpRequest::SetReceiver(std::function<bool __cdecl(char const *,unsigned int)> &&receiver) // 0x1080A720
	{
		mangled_x86(MANGLED_TODO, "?SetReceiver@CWinHttpRequest@Http@@UAEX$$QAV?$function@$$A6A_NPBDI@Z@std@@@Z");
		// std::function<bool __cdecl(char const *,unsigned int)> &receiver;
		todo("implement");
		_sub_1080A720(this, receiver);
	}

	void CWinHttpRequest::SetReceiveBufferSize(unsigned __int32 size) // 0x1080A6B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetReceiveBufferSize@CWinHttpRequest@Http@@UAEXI@Z");
		// unsigned __int32 size;

		m_receiveBuffer.resize(size);
	}

	_extern bool _sub_10809A50(Http::CWinHttpRequest *const);
	bool CWinHttpRequest::SendRequestInternal() // 0x10809A50
	{
		mangled_x86(MANGLED_TODO, "?SendRequestInternal@CWinHttpRequest@Http@@AAE_NXZ");
		// static ...; // 0x1080A1FE
		// static ...; // 0x1080A1F6
		// static ...; // 0x1080A1EF
		// static ...; // 0x1080A1E6
		// static ...; // 0x1080A1DE
		// static ...; // 0x1080A1CC
		// static ...; // 0x1080A184
		// static ...; // 0x1080A17C
		// Http::CWinHttpRequest *const this;
		// std::wstring method;
		// Http::CHttpHeaders headers;
		// std::wstring wideUrl;
		// void *sessHandle;
		// std::wstring serializedHeaders;
		// unsigned long requestFlags;
		// _WINHTTP_URL_COMPONENTS uc;
		// std::wstring hostname;
		// function call : __int32 (wchar_t const *, unsigned long, unsigned long, _WINHTTP_URL_COMPONENTS *)
		// function call : void *(void *, wchar_t const *, unsigned short, unsigned long)
		// function call : void *(void *, wchar_t const *, wchar_t const *, wchar_t const *, wchar_t const *, wchar_t const **, unsigned long)
		// function call : void (*(void *, void (*)(void *, unsigned long, unsigned long, void *, unsigned long), unsigned long, unsigned long))(void *, unsigned long, unsigned long, void *, unsigned long)
		// function call : __int32 (void *, wchar_t const *, unsigned long, void *, unsigned long, unsigned long, unsigned long)
		todo("implement");
		bool __result = _sub_10809A50(this);
		return __result;
	}

	bool CWinHttpRequest::Send() // 0x108099F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Send@CWinHttpRequest@Http@@UAE_NXZ");
		// Http::CWinHttpRequest *const this;

		m_redirectCount = 0;
		return SendRequestInternal();
	}

	void CWinHttpRequest::SetRequestOptions() // 0x1080A790
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetRequestOptions@CWinHttpRequest@Http@@AAEXXZ");
		// static ...; // 0x1080A814
		// static ...; // 0x1080A808
		// static ...; // 0x1080A800
		// Http::CWinHttpRequest *const this;
		// unsigned long value;
		// function call : __int32 (void *, unsigned long, void *, unsigned long)

		unsigned long value = WINHTTP_OPTION_REDIRECT_POLICY_NEVER;
		WinHttpSetOption(m_reqHandle.get(), WINHTTP_OPTION_REDIRECT_POLICY, &value, sizeof(value));
	}

	void CWinHttpRequest::Cancel() // 0x10808560
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Cancel@CWinHttpRequest@Http@@UAEXXZ");
		// Http::CWinHttpRequest *const this;

		FinishRequest(false);
	}
}

extern std::shared_ptr<Http::CWinHttpResponse> _sub_108085B0(Http::CWinHttpRequest *const);
namespace Http
{
	std::shared_ptr<Http::CWinHttpResponse> CWinHttpRequest::CreateResponse() // 0x108085B0
	{
		mangled_x86(MANGLED_TODO, "?CreateResponse@CWinHttpRequest@Http@@QAE?AV?$shared_ptr@VCWinHttpResponse@Http@@@std@@XZ");
		// static ...; // 0x108086D0
		// static ...; // 0x108086C4
		// static ...; // 0x108086BC
		// Http::CWinHttpRequest *const this;
		// std::shared_ptr<Http::CWinHttpResponse> response;
		todo("implement");
		std::shared_ptr<Http::CWinHttpResponse> __result = _sub_108085B0(this);
		return __result;
	}

	void CWinHttpRequest::ReadNext() // 0x10809910
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReadNext@CWinHttpRequest@Http@@QAEXXZ");
		// Http::CWinHttpRequest *const this;
		// function call : __int32 (void *, void *, unsigned long, unsigned long *)

		if (!WinHttpReadData(m_reqHandle.get(), m_receiveBuffer.data(), m_receiveBuffer.size(), nullptr))
		{
			DebugTrace("WinHttpReadData() failed");
			FinishRequest(false);
		}
	}

	void CWinHttpRequest::HandleSendRequestComplete() // 0x10809370
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleSendRequestComplete@CWinHttpRequest@Http@@QAEXXZ");
		// Http::CWinHttpRequest *const this;
		// function call : __int32 (void *, void *)

		if (!WinHttpReceiveResponse(m_reqHandle.get(), nullptr))
		{
			DebugTrace("WinHttpReceiveResponse() failed");
			FinishRequest(false);
		}
	}

	_extern void _sub_10808B90(Http::CWinHttpRequest *const);
	void CWinHttpRequest::HandleHeadersAvailable() // 0x10808B90
	{
		mangled_x86(MANGLED_TODO, "?HandleHeadersAvailable@CWinHttpRequest@Http@@QAEXXZ");
		// static ...; // 0x10809002
		// static ...; // 0x10808FF5
		// static ...; // 0x10808FEC
		// static ...; // 0x10808FE0
		// static ...; // 0x10808FB0
		// static ...; // 0x10808FA8
		// Http::CWinHttpRequest *const this;
		// __int32 responseCode;
		// std::shared_ptr<Http::IHttpRequest> self;
		{
			// std::string location;
			// std::string redirectUrl;
		}
		// function call : __int32 () const
		// function call : Http::CHttpHeaders const &() const
		todo("implement");
		_sub_10808B90(this);
	}

	void CWinHttpRequest::HandleReadComplete(unsigned __int32 bytesRead) // 0x10809130
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleReadComplete@CWinHttpRequest@Http@@QAEXI@Z");
		// unsigned __int32 bytesRead;

		if (!m_contentReceiver(m_receiveBuffer.data(), bytesRead))
		{
			FinishRequest(false);
		}
		else if (bytesRead == 0)
		{
			FinishRequest(true);
		}
		else
		{
			ReadNext();
		}
	}

	_extern void _sub_108091F0(Http::CWinHttpRequest *const, unsigned __int32);
	void CWinHttpRequest::HandleRequestError(unsigned __int32 errorCode) // 0x108091F0
	{
		mangled_x86(MANGLED_TODO, "?HandleRequestError@CWinHttpRequest@Http@@QAEXI@Z");
		// static ...; // 0x10809310
		// static ...; // 0x10809308
		// Http::CWinHttpRequest *const this;
		// unsigned __int32 errorCode;
		// std::error_code ec;
		todo("implement");
		_sub_108091F0(this, errorCode);
	}

	void CWinHttpRequest::HandleStatusCallback(unsigned __int32 status, void *data, unsigned __int32 length) // 0x10809400
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleStatusCallback@CWinHttpRequest@Http@@QAEXIPAXI@Z");
		// unsigned __int32 length;

		switch (status)
		{
		case WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE:
			HandleSendRequestComplete();
			break;
		case WINHTTP_CALLBACK_STATUS_HEADERS_AVAILABLE:
			HandleHeadersAvailable();
			break;
		case WINHTTP_CALLBACK_STATUS_READ_COMPLETE:
			HandleReadComplete(length);
			break;
		case WINHTTP_CALLBACK_STATUS_REQUEST_ERROR:
			HandleRequestError(((WINHTTP_ASYNC_RESULT *)data)->dwError);
			break;
		}
	}

	_extern void _sub_10808730(Http::CWinHttpRequest *const, bool);
	void CWinHttpRequest::FinishRequest(bool success) // 0x10808730
	{
		mangled_x86(MANGLED_TODO, "?FinishRequest@CWinHttpRequest@Http@@QAEX_N@Z");
		// static ...; // 0x108088E0
		// static ...; // 0x108088C8
		// static ...; // 0x108088C0
		// Http::CWinHttpRequest *const this;
		// bool success;
		// std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> callback;
		// std::shared_ptr<Http::IHttpRequest> self;
		todo("implement");
		_sub_10808730(this, success);
	}

	void __stdcall CWinHttpRequest::WinHttpStatusCallback(void *hInternet, unsigned long dwContext, unsigned long dwInternetStatus, void *lpvStatusInformation, unsigned long dwStatusInformationLength) // 0x1080A8F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?WinHttpStatusCallback@CWinHttpRequest@Http@@CGXPAXKK0K@Z");
		// unsigned long dwContext;
		// unsigned long dwInternetStatus;
		// void *lpvStatusInformation;
		// unsigned long dwStatusInformationLength;
		// std::shared_ptr<Http::CWinHttpRequest> request;

		std::shared_ptr<CWinHttpRequest> request = std::static_pointer_cast<CWinHttpRequest>(CWinHttpManager::Instance().LockRequest((IHttpRequest *)dwContext));

		if (request)
		{
			request->HandleStatusCallback(dwInternetStatus, lpvStatusInformation, dwStatusInformationLength);
		}
	}
}

/* ---------- private code */

namespace Http
{
	__int32 QueryStatusCode(void *handle) // 0x10809810
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?QueryStatusCode@Http@@YAHPAX@Z");
		// Http::QueryStatusCode
		// static ...; // 0x108098CE
		// static ...; // 0x108098C2
		// static ...; // 0x108098BC
		// static ...; // 0x10809898
		// static ...; // 0x10809890
		// void *handle;
		// unsigned long bytesNeeded;
		// unsigned long index;
		// unsigned long code;
		// function call : __int32 (void *, unsigned long, wchar_t const *, void *, unsigned long *, unsigned long *)

		unsigned long code = 0;
		unsigned long bytesNeeded = 4;
		unsigned long index = 0;

		WinHttpQueryHeaders(handle, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &code, &bytesNeeded, &index);

		return code;
	}

	_extern void _sub_108095D0(void *, Http::CHttpHeaders &, bool);
	void QueryHeaders(void *handle, Http::CHttpHeaders &headers, bool request) // 0x108095D0
	{
		// Http::QueryHeaders
		// static ...; // 0x10809778
		// static ...; // 0x10809754
		// static ...; // 0x1080974C
		// void *handle;
		// Http::CHttpHeaders &headers;
		// bool request;
		// unsigned long flags;
		// std::wstring buffer;
		// unsigned long bytesNeeded;
		// unsigned long headerIndex;
		// function call : __int32 (void *, unsigned long, wchar_t const *, void *, unsigned long *, unsigned long *)
		// function call : __int32 (void *, unsigned long, wchar_t const *, void *, unsigned long *, unsigned long *)
		todo("implement");
		_sub_108095D0(handle, headers, request);
	}
}
