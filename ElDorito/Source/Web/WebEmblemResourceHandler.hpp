#ifndef __WEB_WEBEMBLEMRESOURCEHANDLER_HPP__
#define __WEB_WEBEMBLEMRESOURCEHANDLER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/NameValueTable.hpp"

#include <functional>
#include <map>
#include <memory>
#include <utility>

/* ---------- forward declarations */

class CefCallback;
struct CefStringTraitsUTF16;
namespace Web
{
	namespace Browser
	{
		class WebEmblemRenderHandler;
		class WebEmblemResourceHandler;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class WebEmblemResourceHandler :
			public CefResourceHandler,
			public virtual CefBaseRefCounted
		{
		public:
			virtual bool ProcessRequest(scoped_refptr<CefRequest> request, scoped_refptr<CefCallback> callback);
			virtual void GetResponseHeaders(scoped_refptr<CefResponse> response, long long &response_length, CefStringBase<CefStringTraitsUTF16> &redirectUrl);
			virtual bool ReadResponse(void *data_out, __int32 bytes_to_read, __int32 &bytes_read, scoped_refptr<CefCallback> callback);
			virtual void Cancel();
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
		private:
			CefRefCount ref_count_; // 0x8
			std::shared_ptr<Web::Browser::WebEmblemRenderHandler> m_emblemRender; // 0xC
			std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > m_responseHeaders; // 0x14
		public:
			_inline WebEmblemResourceHandler(); /* compiler_generated() */
			virtual _inline ~WebEmblemResourceHandler(); /* compiler_generated() */
		};
	}
}

// static_assert(sizeof(Web::Browser::WebEmblemResourceHandler) == 36, "Invalid Web::Browser::WebEmblemResourceHandler size");
// Withheld: the compiler lays this type out through a base a
// real header declares, and that layout contradicts the size
// the PDB recorded. Derives from CefResourceHandler (CEF 101).

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		_extern void _sub_10CB6770(CefBaseRefCounted * const);
		_inline void WebEmblemResourceHandler::AddRef() const // 0x10CB6770
		{
			mangled_x86(MANGLED_TODO, "?AddRef@WebEmblemResourceHandler@Browser@Web@@UBEXXZ");
			// __shifted(Web::Browser::WebEmblemResourceHandler, 32);
			// Web::Browser::WebEmblemResourceHandler const *const this;
			todo("implement");
			_sub_10CB6770((CefBaseRefCounted *)this);
		}

		_extern bool _sub_10CB6A40(CefBaseRefCounted * const);
		_inline bool WebEmblemResourceHandler::HasAtLeastOneRef() const // 0x10CB6A40
		{
			mangled_x86(MANGLED_TODO, "?HasAtLeastOneRef@WebEmblemResourceHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebEmblemResourceHandler, 32);
			// Web::Browser::WebEmblemResourceHandler const *const this;
			todo("implement");
			bool __result = _sub_10CB6A40((CefBaseRefCounted *)this);
			return __result;
		}

		_extern bool _sub_10CB6AE0(CefBaseRefCounted * const);
		_inline bool WebEmblemResourceHandler::HasOneRef() const // 0x10CB6AE0
		{
			mangled_x86(MANGLED_TODO, "?HasOneRef@WebEmblemResourceHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebEmblemResourceHandler, 32);
			// Web::Browser::WebEmblemResourceHandler const *const this;
			todo("implement");
			bool __result = _sub_10CB6AE0((CefBaseRefCounted *)this);
			return __result;
		}

		_extern bool _sub_10CB7030(CefBaseRefCounted * const);
		_inline bool WebEmblemResourceHandler::Release() const // 0x10CB7030
		{
			mangled_x86(MANGLED_TODO, "?Release@WebEmblemResourceHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebEmblemResourceHandler, 32);
			// Web::Browser::WebEmblemResourceHandler const *const this;
			// function call : void *(unsigned __int32)
			todo("implement");
			bool __result = _sub_10CB7030((CefBaseRefCounted *)this);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBEMBLEMRESOURCEHANDLER_HPP__
