#ifndef __WEB_WEBRENDERERAPP_HPP__
#define __WEB_WEBRENDERERAPP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class CefCommandLine;
struct CefStringTraitsUTF16;
namespace Web
{
	namespace Browser
	{
		class WebRendererApp;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class WebRendererApp :
			public CefApp,
			public CefBrowserProcessHandler,
			public CefRenderProcessHandler,
			public virtual CefBaseRefCounted
		{
		public:
			virtual _inline ~WebRendererApp();
			virtual void OnRegisterCustomSchemes(CefSchemeRegistrar *registrar);
			virtual scoped_refptr<CefBrowserProcessHandler> GetBrowserProcessHandler();
			virtual scoped_refptr<CefRenderProcessHandler> GetRenderProcessHandler();
			virtual void OnContextInitialized();
			virtual void OnContextCreated(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefV8Context> context);
			virtual void OnBeforeCommandLineProcessing(CefStringBase<CefStringTraitsUTF16> const &process_type, scoped_refptr<CefCommandLine> command_line);
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
		private:
			CefRefCount ref_count_; // 0x18
		public:
			_inline WebRendererApp(); /* compiler_generated() */
		};
		static_assert(sizeof(Web::Browser::WebRendererApp) == 36, "Invalid Web::Browser::WebRendererApp size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		_extern void _sub_10CBB980(Web::Browser::WebRendererApp * const);
		_inline WebRendererApp::~WebRendererApp() // 0x10CBB980
		{
			mangled_x86(MANGLED_TODO, "??1WebRendererApp@Browser@Web@@UAE@XZ");
			// __shifted(Web::Browser::WebRendererApp, 32);
			// Web::Browser::WebRendererApp *const this;
			todo("implement");
			_sub_10CBB980(this);
		}

		_inline void WebRendererApp::AddRef() const // 0x10CBD420
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@WebRendererApp@Browser@Web@@UBEXXZ");
			// __shifted(Web::Browser::WebRendererApp, 32);
			// Web::Browser::WebRendererApp const *const this;

			ref_count_.AddRef();
		}

		_inline bool WebRendererApp::HasAtLeastOneRef() const // 0x10CBE420
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasAtLeastOneRef@WebRendererApp@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererApp, 32);
			// Web::Browser::WebRendererApp const *const this;

			return ref_count_.HasAtLeastOneRef();
		}

		_inline bool WebRendererApp::HasOneRef() const // 0x10CBE4D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasOneRef@WebRendererApp@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererApp, 32);
			// Web::Browser::WebRendererApp const *const this;

			return ref_count_.HasOneRef();
		}

		_inline bool WebRendererApp::Release() const // 0x10CC2240
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@WebRendererApp@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererApp, 32);
			// Web::Browser::WebRendererApp const *const this;
			// function call : void *(unsigned __int32)

			if (ref_count_.Release())
			{
				delete static_cast<WebRendererApp const *>(this);
				return true;
			}

			return false;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBRENDERERAPP_HPP__
