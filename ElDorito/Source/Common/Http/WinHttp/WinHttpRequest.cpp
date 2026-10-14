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

#include "Utils/Uri.hpp"  // hades: added for 0x10808B90

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

namespace Http
{
	// hades: a `static` template in the original (`Http::DebugTrace<...>` carries no
	// decoration in the PDB); one body, one instantiation per argument pack.
	template <typename ...Args>
	static void DebugTrace(char const *format, Args &&...args)
	{
		char buffer[8192];
		int len = sprintf_s(buffer, "Http :: ");
		sprintf_s(buffer + len, sizeof(buffer) - len, format, std::forward<Args>(args)...);

		static std::mutex mutex;
		std::scoped_lock lock(mutex);
		Console::WriteLine(buffer);
	}
}

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


namespace Http
{
	std::shared_ptr<Http::IHttpResponse> CWinHttpRequest::GetResponse() // 0x10808A90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetResponse@CWinHttpRequest@Http@@UAE?AV?$shared_ptr@VIHttpResponse@Http@@@std@@XZ");
		// Http::CWinHttpRequest *const this;

		return m_response;
	}

	// mangled_x86(MANGLED_DEFAULT, "??4CHttpHeaders@Http@@QAEAAV01@ABV01@@Z"); no body to assert in
	_inline Http::CHttpHeaders &CHttpHeaders::operator=(Http::CHttpHeaders const &__that) = default; // 0x10807C10

	void CWinHttpRequest::SetMethod(std::string method) // 0x1080A540
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetMethod@CWinHttpRequest@Http@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string method;

		m_method = method;
	}

	void CWinHttpRequest::SetUrl(std::string url) // 0x1080A840
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetUrl@CWinHttpRequest@Http@@UAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string url;

		m_url = url;
	}

	void CWinHttpRequest::SetMaxRedirects(__int32 count) // 0x1080A510
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetMaxRedirects@CWinHttpRequest@Http@@UAEXH@Z");
		// __int32 count;

		m_maxRedirects = count;
	}

	void CWinHttpRequest::SetBody(std::string &&body) // 0x1080A3F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetBody@CWinHttpRequest@Http@@UAEX$$QAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string &body;

		m_body = std::move(body);
	}

	void CWinHttpRequest::SetHeaders(Http::CHttpHeaders headers) // 0x1080A460
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetHeaders@CWinHttpRequest@Http@@UAEXVCHttpHeaders@2@@Z");
		// Http::CHttpHeaders headers;

		m_headers = headers;
	}

	void CWinHttpRequest::SetReceiver(std::function<bool __cdecl(char const *,unsigned int)> &&receiver) // 0x1080A720
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetReceiver@CWinHttpRequest@Http@@UAEX$$QAV?$function@$$A6A_NPBDI@Z@std@@@Z");
		// std::function<bool __cdecl(char const *,unsigned int)> &receiver;

		m_contentReceiver = std::move(receiver);
	}

	void CWinHttpRequest::SetReceiveBufferSize(unsigned __int32 size) // 0x1080A6B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetReceiveBufferSize@CWinHttpRequest@Http@@UAEXI@Z");
		// unsigned __int32 size;

		m_receiveBuffer.resize(size);
	}

	bool CWinHttpRequest::SendRequestInternal() // 0x10809A50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SendRequestInternal@CWinHttpRequest@Http@@AAE_NXZ");
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

			URL_COMPONENTS uc;
			memset(&uc, 0, sizeof(uc));
			uc.dwStructSize = sizeof(uc);
			uc.dwHostNameLength = (DWORD)-1;
			uc.dwSchemeLength = (DWORD)-1;
			uc.dwUrlPathLength = (DWORD)-1;
			std::wstring wideUrl = Utils::String::WidenString(m_url);
			std::wstring method = Utils::String::WidenString(m_method);
			if (!WinHttpCrackUrl(wideUrl.data(), m_url.length(), 0, &uc))
				return false;
			std::wstring hostname;
			if (uc.lpszHostName)
				hostname = std::wstring(uc.lpszHostName, uc.dwHostNameLength);
			void *sessHandle = CWinHttpManager::Instance().GetSessionHandle();
			m_connHandle.reset(WinHttpConnect(sessHandle, hostname.c_str(), uc.nPort, 0));
			if (!m_connHandle)
				return false;
			unsigned long requestFlags = 0;
			if (uc.nScheme == INTERNET_SCHEME_HTTPS)
				requestFlags |= WINHTTP_FLAG_SECURE;
			m_reqHandle.reset(WinHttpOpenRequest(m_connHandle.get(), Utils::String::WidenString(m_method).c_str(), uc.dwUrlPathLength == 0 ? L"/" : uc.lpszUrlPath, nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, requestFlags));
			if (!m_reqHandle)
				return false;
			CHttpHeaders headers(m_headers);
			headers.Add("Host", Utils::String::ThinString(hostname), CHttpHeaders::Reject);
			headers.Add("Accept", "*/*", CHttpHeaders::Reject);
			std::wstring serializedHeaders = Utils::String::WidenString(headers.ToString());
			CWinHttpManager::Instance().AddRequest(shared_from_this());
			SetRequestOptions();
			WinHttpSetStatusCallback(m_reqHandle.get(), WinHttpStatusCallback, WINHTTP_CALLBACK_FLAG_ALL_NOTIFICATIONS, 0);
			if (!WinHttpSendRequest(m_reqHandle.get(), serializedHeaders.data(), serializedHeaders.length(), m_body.empty() ? nullptr : (void *)m_body.data(), m_body.length(), m_body.length(), (DWORD_PTR)this))
			{
				DebugTrace("WinHttpSendRequest() failed");
				FinishRequest(false);
				return false;
			}
			return true;
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


namespace Http
{
	std::shared_ptr<Http::CWinHttpResponse> CWinHttpRequest::CreateResponse() // 0x108085B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CreateResponse@CWinHttpRequest@Http@@QAE?AV?$shared_ptr@VCWinHttpResponse@Http@@@std@@XZ");
		// static ...; // 0x108086D0
		// static ...; // 0x108086C4
		// static ...; // 0x108086BC
		// Http::CWinHttpRequest *const this;
		// std::shared_ptr<Http::CWinHttpResponse> response;

		std::shared_ptr<Http::CWinHttpResponse> response = std::make_shared<Http::CWinHttpResponse>();
		if (!response->Process(*this))
			return nullptr;
		return response;
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

	void CWinHttpRequest::HandleHeadersAvailable() // 0x10808B90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleHeadersAvailable@CWinHttpRequest@Http@@QAEXXZ");
		// static ...; // 0x10809002
		// static ...; // 0x10808FF5
		// static ...; // 0x10808FEC
		// static ...; // 0x10808FE0
		// static ...; // 0x10808FB0
		// static ...; // 0x10808FA8
		// Http::CWinHttpRequest *const this;
		// __int32 responseCode;
		// std::shared_ptr<Http::IHttpRequest> self;
			// std::string location;
			// std::string redirectUrl;
		// function call : __int32 () const
		// function call : Http::CHttpHeaders const &() const

		auto self = shared_from_this();
		m_response = CreateResponse();
		if (!m_response)
		{
			DebugTrace("Failed to parse http response");
			FinishRequest(false);
			return;
		}
		__int32 responseCode = m_response->GetResponseCode();
		if (responseCode / 100 == 3 && m_maxRedirects > 0)
		{
			if (m_redirectCount++ >= m_maxRedirects)
			{
				DebugTrace("Maximum number of redirects (%d) exceeded", m_maxRedirects);
				FinishRequest(false);
				return;
			}
			std::string location = m_response->GetHeaders().Get("Location");
			if (location.empty())
			{
				DebugTrace("Server returned redirect status code: %d without location header", responseCode);
				FinishRequest(false);
				return;
			}
			std::string redirectUrl;
			if (!Utils::Uri::ResolveUrl(m_url, location, redirectUrl))
			{
				DebugTrace("Failed to resolve redirect location %s", location.c_str());
				FinishRequest(false);
				return;
			}
			m_url = redirectUrl;
			SendRequestInternal();
			return;
		}
		if (m_responseCallback)
			m_responseCallback(self);
		if (m_contentReceiver)
		{
			if (m_receiveBuffer.size() == 0)
				m_receiveBuffer.resize(0x2000);
			ReadNext();
		}
		else
		{
			FinishRequest(true);
		}
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

	void CWinHttpRequest::HandleRequestError(unsigned __int32 errorCode) // 0x108091F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleRequestError@CWinHttpRequest@Http@@QAEXI@Z");
		// static ...; // 0x10809310
		// static ...; // 0x10809308
		// Http::CWinHttpRequest *const this;
		// unsigned __int32 errorCode;
		// std::error_code ec;

		std::error_code ec(errorCode, WinHttpErrorCategory::Get());
		DebugTrace("Request Error. %d (%s)", errorCode, ec.message().c_str());
		FinishRequest(false);
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

	void CWinHttpRequest::FinishRequest(bool success) // 0x10808730
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FinishRequest@CWinHttpRequest@Http@@QAEX_N@Z");
		// static ...; // 0x108088E0
		// static ...; // 0x108088C8
		// static ...; // 0x108088C0
		// Http::CWinHttpRequest *const this;
		// bool success;
		// std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> callback;
		// std::shared_ptr<Http::IHttpRequest> self;

		std::shared_ptr<Http::IHttpRequest> self = shared_from_this();
		m_reqHandle.reset();
		m_connHandle.reset();
		CWinHttpManager::Instance().RemoveRequest(self);
		m_responseCallback = nullptr;
		m_contentReceiver = nullptr;
		std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> callback = std::move(m_completedCallback);
		if (callback)
			callback(std::move(self), success);
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

	void QueryHeaders(void *handle, Http::CHttpHeaders &headers, bool request) // 0x108095D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?QueryHeaders@Http@@YAXPAXAAVCHttpHeaders@1@_N@Z");
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

		unsigned long flags = WINHTTP_QUERY_RAW_HEADERS_CRLF;
		if (request)
			flags |= WINHTTP_QUERY_FLAG_REQUEST_HEADERS;
		std::wstring buffer;
		unsigned long bytesNeeded = 0;
		unsigned long headerIndex = 0;
		WinHttpQueryHeaders(handle, flags, WINHTTP_HEADER_NAME_BY_INDEX, WINHTTP_NO_OUTPUT_BUFFER, &bytesNeeded, &headerIndex);
		buffer.resize(bytesNeeded / sizeof(wchar_t));
		WinHttpQueryHeaders(handle, flags, WINHTTP_HEADER_NAME_BY_INDEX, buffer.data(), &bytesNeeded, &headerIndex);
		CHttpHeaders::Parse(Utils::String::ThinString(buffer), headers);
	}
}
