#ifndef __WEB_WEBEMBLEMSCHEMEHANDLER_HPP__
#define __WEB_WEBEMBLEMSCHEMEHANDLER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct CefStringTraitsUTF16;
namespace Web
{
	namespace Browser
	{
		class WebEmblemSchemeHandlerFactory;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class WebEmblemSchemeHandlerFactory :
			public CefSchemeHandlerFactory,
			public virtual CefBaseRefCounted
		{
		protected:
			virtual scoped_refptr<CefResourceHandler> Create(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, CefStringBase<CefStringTraitsUTF16> const &scheme, scoped_refptr<CefRequest> request);
		public:
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
		private:
			CefRefCount ref_count_; // 0x8
		public:
			_inline WebEmblemSchemeHandlerFactory(); /* compiler_generated() */
			virtual _inline ~WebEmblemSchemeHandlerFactory(); /* compiler_generated() */
		};
	}
}

// static_assert(sizeof(Web::Browser::WebEmblemSchemeHandlerFactory) == 16, "Invalid Web::Browser::WebEmblemSchemeHandlerFactory size");
// Withheld: the compiler lays this type out through a base a
// real header declares, and that layout contradicts the size
// the PDB recorded. Derives from CefSchemeHandlerFactory (CEF 101).

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		_inline void WebEmblemSchemeHandlerFactory::AddRef() const // 0x10CBD3C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@WebEmblemSchemeHandlerFactory@Browser@Web@@UBEXXZ");
			// __shifted(Web::Browser::WebEmblemSchemeHandlerFactory, 12);
			// Web::Browser::WebEmblemSchemeHandlerFactory const *const this;

			ref_count_.AddRef();
		}

		_inline bool WebEmblemSchemeHandlerFactory::HasAtLeastOneRef() const // 0x10CBE3C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasAtLeastOneRef@WebEmblemSchemeHandlerFactory@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebEmblemSchemeHandlerFactory, 12);
			// Web::Browser::WebEmblemSchemeHandlerFactory const *const this;

			return ref_count_.HasAtLeastOneRef();
		}

		_inline bool WebEmblemSchemeHandlerFactory::HasOneRef() const // 0x10CBE470
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasOneRef@WebEmblemSchemeHandlerFactory@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebEmblemSchemeHandlerFactory, 12);
			// Web::Browser::WebEmblemSchemeHandlerFactory const *const this;

			return ref_count_.HasOneRef();
		}

		_inline bool WebEmblemSchemeHandlerFactory::Release() const // 0x10CC2140
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@WebEmblemSchemeHandlerFactory@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebEmblemSchemeHandlerFactory, 12);
			// Web::Browser::WebEmblemSchemeHandlerFactory const *const this;
			// function call : void *(unsigned __int32)

			if (ref_count_.Release())
			{
				delete static_cast<WebEmblemSchemeHandlerFactory const *>(this);
				return true;
			}

			return false;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBEMBLEMSCHEMEHANDLER_HPP__
