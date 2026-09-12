#ifndef __COMMON_HTTP_WINHTTP_WINHTTPMANAGER_HPP__
#define __COMMON_HTTP_WINHTTP_WINHTTPMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpManager.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Common/Http/WinHttp/WinHttpCommon.hpp"
#include "Patches/CustomPackets.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <memory>

/* ---------- forward declarations */

namespace Http
{
	class CHttpManager;
	class CWinHttpManager;
	class IHttpRequest;
	struct WinHttpHandlerDeleter;
}

/* ---------- constants */

/* ---------- definitions */

namespace Http
{
	class CWinHttpManager :
		public Http::CHttpManager
	{
	public:
		_inline ~CWinHttpManager();
		static _inline Http::CWinHttpManager &Instance();
		std::unique_ptr<void *,Http::WinHttpHandlerDeleter> CreateSession();
		_inline void *GetSessionHandle();
		virtual std::shared_ptr<Http::IHttpRequest> CreateRequest();
	private:
		CWinHttpManager();
		std::unique_ptr<void *,Http::WinHttpHandlerDeleter> m_sessHandle; // 0x44
	};
	static_assert(sizeof(Http::CWinHttpManager) == 72, "Invalid Http::CWinHttpManager size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Http
{
	_extern void _sub_107F7160(Http::CWinHttpManager *const);
	_inline CWinHttpManager::~CWinHttpManager() // 0x107F7160
	{
		mangled_x86(MANGLED_TODO, "??1CWinHttpManager@Http@@QAE@XZ");
		// Http::CWinHttpManager *const this;
		todo("implement");
		_sub_107F7160(this);
	}

	extern CWinHttpManager &_sub_107F7370();
	_inline Http::CWinHttpManager &CWinHttpManager::Instance() // 0x107F7370
	{
		mangled_x86(MANGLED_TODO, "?Instance@CWinHttpManager@Http@@SAAAV12@XZ");
		// procedure flags: nofpo
		// static Http::CWinHttpManager instance; // 0x1138F3E0
		// static __int32 $TSS0; // 0x1138F438
		todo("implement");
		Http::CWinHttpManager & __result = _sub_107F7370();
		return __result;
	}

	_inline void *CWinHttpManager::GetSessionHandle() // 0x10808B40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetSessionHandle@CWinHttpManager@Http@@QAEPAXXZ");
		// Http::CWinHttpManager *const this;

		return m_sessHandle.get();
	}
}

/* ---------- private code */

#endif // __COMMON_HTTP_WINHTTP_WINHTTPMANAGER_HPP__
