#ifndef __COMMON_HTTP_HTTPMANAGER_HPP__
#define __COMMON_HTTP_HTTPMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>
#include <mutex>
#include <vector>

/* ---------- forward declarations */

namespace Http
{
	class CHttpManager;
	class IHttpRequest;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Http
{
	class CHttpManager
	{
	public:
		_inline CHttpManager();
		void AddRequest(std::shared_ptr<Http::IHttpRequest> request);
		bool RemoveRequest(std::shared_ptr<Http::IHttpRequest> request);
		std::shared_ptr<Http::IHttpRequest> LockRequest(Http::IHttpRequest *request);
		void CancelAllRequests();
		virtual std::shared_ptr<Http::IHttpRequest> CreateRequest() = 0;
	private:
		std::mutex m_mutex; // 0x4
		std::vector<std::shared_ptr<Http::IHttpRequest> > m_activeRequests; // 0x34
	public:
		// mangled_x86(MANGLED_KNOWN_GOOD, "??1CHttpManager@Http@@QAE@XZ"); defaulted on its declaration
		_inline ~CHttpManager() = default; // 0x107f7100
	};
}

#pragma pack(pop)
static_assert(sizeof(Http::CHttpManager) == 68, "Invalid Http::CHttpManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Http
{
	inline CHttpManager::CHttpManager() // 0x108034B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CHttpManager@Http@@QAE@XZ");
	}
}

/* ---------- private code */

#endif // __COMMON_HTTP_HTTPMANAGER_HPP__
