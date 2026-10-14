#ifndef __COMMON_HTTP_WINHTTP_WINHTTPREQUEST_HPP__
#define __COMMON_HTTP_WINHTTP_WINHTTPREQUEST_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Common/Http/WinHttp/WinHttpCommon.hpp"
#include "Common/Http/WinHttp/WinHttpManager.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Patches/CustomPackets.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <atomic>
#include <functional>
#include <memory>
#include <string>
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
	struct WinHttpHandlerDeleter;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Http
{
	class CWinHttpResponse :
		public Http::IHttpResponse
	{
	public:
		virtual _inline __int32 GetResponseCode() const;
		virtual _inline Http::CHttpHeaders const &GetHeaders() const;
		bool Process(Http::CWinHttpRequest &request);
	private:
		unsigned __int32 m_responseCode = 0; // 0x4
		Http::CHttpHeaders m_headers; // 0x8
	public:
		CWinHttpResponse(Http::CWinHttpResponse &); /* compiler_generated() */
		CWinHttpResponse(Http::CWinHttpResponse const &); /* compiler_generated() */
		_inline CWinHttpResponse() = default; /* compiler_generated() */
		// mangled_x86(MANGLED_KNOWN_GOOD, "??1CWinHttpResponse@Http@@QAE@XZ"); defaulted on its declaration
		_inline ~CWinHttpResponse() = default; // 0x108076c0
		Http::CWinHttpResponse &operator=(Http::CWinHttpResponse &); /* compiler_generated() */
		Http::CWinHttpResponse &operator=(Http::CWinHttpResponse const &); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Http::CWinHttpResponse) == 20, "Invalid Http::CWinHttpResponse size");

namespace Http
{
	class CWinHttpRequest :
		public Http::IHttpRequest
	{
	public:
		CWinHttpRequest(Http::CWinHttpManager &winhttpManager);
		_inline void *GetRequestHandle();
		virtual bool IsComplete() const;
		virtual std::shared_ptr<Http::IHttpResponse> GetResponse();
		virtual void SetMethod(std::string method);
		virtual void SetUrl(std::string url);
		virtual void SetMaxRedirects(__int32 count);
		virtual void SetBody(std::string &&body);
		virtual void SetHeaders(Http::CHttpHeaders headers);
		virtual void SetReceiver(std::function<bool __cdecl(char const *,unsigned int)> &&receiver);
		virtual void SetReceiveBufferSize(unsigned __int32 size);
		virtual _inline void SetOnCompleted(std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> &&callback);
		virtual _inline void SetOnResponse(std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>)> &&callback);
		virtual bool Send();
		virtual void Cancel();
		void HandleStatusCallback(unsigned __int32 status, void *data, unsigned __int32 length);
		void HandleSendRequestComplete();
		void HandleHeadersAvailable();
		void HandleReadComplete(unsigned __int32 bytesRead);
		void HandleRequestError(unsigned __int32 errorCode);
		void FinishRequest(bool success);
		void ReadNext();
		std::shared_ptr<Http::CWinHttpResponse> CreateResponse();
	private:
		static void __stdcall WinHttpStatusCallback(void *hInternet, unsigned long dwContext, unsigned long dwInternetStatus, void *lpvStatusInformation, unsigned long dwStatusInformationLength);
		void SetRequestOptions();
		bool SendRequestInternal();
		Http::CWinHttpManager &m_winhttpManager; // 0xC
		std::unique_ptr<void *,Http::WinHttpHandlerDeleter> m_connHandle; // 0x10
		std::unique_ptr<void *,Http::WinHttpHandlerDeleter> m_reqHandle; // 0x14
		std::string m_method; // 0x18
		std::string m_url; // 0x34
		std::string m_body; // 0x50
		Http::CHttpHeaders m_headers; // 0x6C
		__int32 m_maxRedirects; // 0x78
		__int32 m_redirectCount; // 0x7C
		std::atomic<bool> m_bIsCompleted; // 0x80
		unsigned char __pad0[3]; // 0x81
		std::shared_ptr<Http::CWinHttpResponse> m_response; // 0x84
		std::vector<char> m_receiveBuffer; // 0x8C
		std::function<bool __cdecl(char const *,unsigned int)> m_contentReceiver; // 0xA0
		std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> m_completedCallback; // 0xC8
		std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>)> m_responseCallback; // 0xF0
	public:
		virtual _inline ~CWinHttpRequest() = default; /* compiler_generated() */ // 0x108075C0
	};
	static_assert(sizeof(Http::CWinHttpRequest) == 280, "Invalid Http::CWinHttpRequest size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Http
{
	_inline __int32 CWinHttpResponse::GetResponseCode() const // 0x10808B10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetResponseCode@CWinHttpResponse@Http@@UBEHXZ");
		// Http::CWinHttpResponse const *const this;

		return m_responseCode;
	}

	_inline Http::CHttpHeaders const &CWinHttpResponse::GetHeaders() const // 0x10808A10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetHeaders@CWinHttpResponse@Http@@UBEABVCHttpHeaders@2@XZ");
		// Http::CWinHttpResponse const *const this;

		return m_headers;
	}

	_inline void *CWinHttpRequest::GetRequestHandle() // 0x10808A40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetRequestHandle@CWinHttpRequest@Http@@QAEPAXXZ");
		// Http::CWinHttpRequest *const this;

		return m_reqHandle.get();
	}

	_inline void CWinHttpRequest::SetOnCompleted(std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> &&callback) // 0x1080A5F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetOnCompleted@CWinHttpRequest@Http@@UAEX$$QAV?$function@$$A6AXV?$shared_ptr@VIHttpRequest@Http@@@std@@_N@Z@std@@@Z");
		// std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> &callback;

		m_completedCallback = callback;
	}

	_inline void CWinHttpRequest::SetOnResponse(std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>)> &&callback) // 0x1080A650
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetOnResponse@CWinHttpRequest@Http@@UAEX$$QAV?$function@$$A6AXV?$shared_ptr@VIHttpRequest@Http@@@std@@@Z@std@@@Z");
		// std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>)> &callback;

		m_responseCallback = callback;
	}
}

/* ---------- private code */

#endif // __COMMON_HTTP_WINHTTP_WINHTTPREQUEST_HPP__
