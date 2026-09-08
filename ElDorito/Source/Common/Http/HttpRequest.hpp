#ifndef __COMMON_HTTP_HTTPREQUEST_HPP__
#define __COMMON_HTTP_HTTPREQUEST_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/CustomPackets.hpp"

#include <functional>
#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Http
{
	class CHttpHeaders;
	class IHttpRequest;
	class IHttpResponse;
}

/* ---------- constants */

/* ---------- definitions */

namespace Http
{
	class IHttpResponse
	{
	public:
		virtual __int32 GetResponseCode() const = 0;
		virtual Http::CHttpHeaders const &GetHeaders() const = 0;
		IHttpResponse(Http::IHttpResponse &); /* compiler_generated() */
		IHttpResponse(Http::IHttpResponse const &); /* compiler_generated() */
		_inline IHttpResponse(); /* compiler_generated() */
		Http::IHttpResponse &operator=(Http::IHttpResponse &); /* compiler_generated() */
		Http::IHttpResponse &operator=(Http::IHttpResponse const &); /* compiler_generated() */
	};
	static_assert(sizeof(Http::IHttpResponse) == 4, "Invalid Http::IHttpResponse size");
}

#pragma pack(push, 4)
namespace Http
{
	class IHttpRequest :
		public std::enable_shared_from_this<Http::IHttpRequest>
	{
	public:
		virtual _inline ~IHttpRequest();
		virtual bool IsComplete() const = 0;
		virtual std::shared_ptr<Http::IHttpResponse> GetResponse() = 0;
		virtual void SetMethod(std::string) = 0;
		virtual void SetUrl(std::string) = 0;
		virtual void SetMaxRedirects(__int32) = 0;
		virtual void SetBody(std::string &) = 0;
		virtual void SetHeaders(Http::CHttpHeaders) = 0;
		virtual void SetReceiver(std::function<bool __cdecl(char const *,unsigned int)> &) = 0;
		virtual void SetReceiveBufferSize(unsigned __int32) = 0;
		virtual void SetOnCompleted(std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> &) = 0;
		virtual void SetOnResponse(std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>)> &) = 0;
		virtual bool Send() = 0;
		virtual void Cancel() = 0;
		IHttpRequest(Http::IHttpRequest const &); /* compiler_generated() */
		_inline IHttpRequest(); /* compiler_generated() */
		Http::IHttpRequest &operator=(Http::IHttpRequest const &); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Http::IHttpRequest) == 12, "Invalid Http::IHttpRequest size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Http
{
	_extern void _sub_10807710(Http::IHttpRequest *const);
	_inline IHttpRequest::~IHttpRequest() // 0x10807710
	{
		mangled_x86(MANGLED_TODO, "??1IHttpRequest@Http@@UAE@XZ");
		// Http::IHttpRequest *const this;
		todo("implement");
		_sub_10807710(this);
	}
}

/* ---------- private code */

#endif // __COMMON_HTTP_HTTPREQUEST_HPP__
