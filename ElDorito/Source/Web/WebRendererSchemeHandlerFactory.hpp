#ifndef __WEB_WEBRENDERERSCHEMEHANDLERFACTORY_HPP__
#define __WEB_WEBRENDERERSCHEMEHANDLERFACTORY_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct CefStringTraitsUTF16;
namespace Web
{
	namespace Browser
	{
		class WebRendererSchemeHandlerFactory;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class WebRendererSchemeHandlerFactory :
			public CefSchemeHandlerFactory,
			public virtual CefBaseRefCounted
		{
		private:
			std::string const m_Directory; // 0x8
			std::string const m_Scheme; // 0x24
			CefRefCount ref_count_; // 0x40
		public:
			WebRendererSchemeHandlerFactory(std::string const &scheme, std::string const &directory);
		protected:
			virtual scoped_refptr<CefResourceHandler> Create(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, CefStringBase<CefStringTraitsUTF16> const &schemeName, scoped_refptr<CefRequest> request);
		public:
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
			virtual _inline ~WebRendererSchemeHandlerFactory(); /* compiler_generated() */
		};
		static_assert(sizeof(Web::Browser::WebRendererSchemeHandlerFactory) == 76, "Invalid Web::Browser::WebRendererSchemeHandlerFactory size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		_inline void WebRendererSchemeHandlerFactory::AddRef() const // 0x10CE0110
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@WebRendererSchemeHandlerFactory@Browser@Web@@UBEXXZ");
			// __shifted(Web::Browser::WebRendererSchemeHandlerFactory, 72);
			// Web::Browser::WebRendererSchemeHandlerFactory const *const this;

			ref_count_.AddRef();
		}

		_inline bool WebRendererSchemeHandlerFactory::HasAtLeastOneRef() const // 0x10CE2DF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasAtLeastOneRef@WebRendererSchemeHandlerFactory@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererSchemeHandlerFactory, 72);
			// Web::Browser::WebRendererSchemeHandlerFactory const *const this;

			return ref_count_.HasAtLeastOneRef();
		}

		_inline bool WebRendererSchemeHandlerFactory::HasOneRef() const // 0x10CE2E50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasOneRef@WebRendererSchemeHandlerFactory@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererSchemeHandlerFactory, 72);
			// Web::Browser::WebRendererSchemeHandlerFactory const *const this;

			return ref_count_.HasOneRef();
		}

		_inline bool WebRendererSchemeHandlerFactory::Release() const // 0x10CE3630
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@WebRendererSchemeHandlerFactory@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererSchemeHandlerFactory, 72);
			// Web::Browser::WebRendererSchemeHandlerFactory const *const this;
			// function call : void *(unsigned __int32)

			if (ref_count_.Release())
			{
				delete static_cast<WebRendererSchemeHandlerFactory const *>(this);
				return true;
			}

			return false;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBRENDERERSCHEMEHANDLERFACTORY_HPP__
