#ifndef __WEB_WEBRENDERERHANDLER_HPP__
#define __WEB_WEBRENDERERHANDLER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/CustomPackets.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/WebRendererRenderHandler.hpp"

#include <memory>

/* ---------- forward declarations */

class CefDictionaryValue;
class CefMenuModel;
class CefProcessMessage;
struct CefStringTraitsUTF16;
namespace Web
{
	namespace Browser
	{
		class WebRendererHandler;
		class WebRendererRenderHandler;
	}
}
namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			class WebRendererQueryHandler;
		}
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class WebRendererHandler :
			public CefClient,
			public CefLifeSpanHandler,
			public CefRequestHandler,
			public CefContextMenuHandler,
			public CefLoadHandler,
			public virtual CefBaseRefCounted
		{
		private:
			scoped_refptr<CefBrowser> m_Browser; // 0x28
			scoped_refptr<CefMessageRouterBrowserSide> m_BrowserRouter; // 0x2C
			scoped_refptr<Web::Browser::WebRendererRenderHandler> m_RenderHandler; // 0x30
			std::shared_ptr<Web::Browser::Bridge::WebRendererQueryHandler> m_QueryHandler; // 0x34
			CefRefCount ref_count_; // 0x3C
		public:
			WebRendererHandler(scoped_refptr<Web::Browser::WebRendererRenderHandler> renderHandler);
			virtual _inline ~WebRendererHandler() = default;
			virtual _inline scoped_refptr<CefLifeSpanHandler> GetLifeSpanHandler();
			virtual _inline scoped_refptr<CefRenderHandler> GetRenderHandler();
			virtual _inline scoped_refptr<CefRequestHandler> GetRequestHandler();
			virtual _inline scoped_refptr<CefContextMenuHandler> GetContextMenuHandler();
			virtual _inline scoped_refptr<CefLoadHandler> GetLoadHandler();
			_inline std::shared_ptr<Web::Browser::Bridge::WebRendererQueryHandler> GetQueryHandler() const;
			virtual void OnAfterCreated(scoped_refptr<CefBrowser> browser);
			virtual void OnBeforeClose(scoped_refptr<CefBrowser> browser);
			virtual void OnLoadStart(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, cef_transition_type_t transition_type);
			virtual void OnLoadEnd(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, __int32 httpStatusCode);
			virtual void OnRenderProcessTerminated(scoped_refptr<CefBrowser> browser, cef_termination_status_t status);
			virtual bool OnBeforeBrowse(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefRequest> request, bool userGesture, bool isRedirect);
			virtual bool OnProcessMessageReceived(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, cef_process_id_t sourceProcess, scoped_refptr<CefProcessMessage> message);
			virtual void OnBeforeContextMenu(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefContextMenuParams> params, scoped_refptr<CefMenuModel> model);
			virtual bool OnBeforePopup(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, CefStringBase<CefStringTraitsUTF16> const &target_url, CefStringBase<CefStringTraitsUTF16> const &target_frame_name, cef_window_open_disposition_t target_disposition, bool user_gesture, CefStructBase<CefPopupFeaturesTraits> const &popupFeatures, CefWindowInfo &windowInfo, scoped_refptr<CefClient> &client, CefStructBase<CefBrowserSettingsTraits> &settings, scoped_refptr<CefDictionaryValue> &extra_info, bool *no_javascript_access);
			scoped_refptr<CefBrowser> GetBrowser();
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
		};
		static_assert(sizeof(Web::Browser::WebRendererHandler) == 72, "Invalid Web::Browser::WebRendererHandler size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{

	}
}


namespace Web
{
	namespace Browser
	{
		_inline scoped_refptr<CefLifeSpanHandler> WebRendererHandler::GetLifeSpanHandler() // 0x10CCB7D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetLifeSpanHandler@WebRendererHandler@Browser@Web@@UAE?AV?$scoped_refptr@VCefLifeSpanHandler@@@@XZ");
			// Web::Browser::WebRendererHandler *const this;

			return this;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		_inline scoped_refptr<CefRenderHandler> WebRendererHandler::GetRenderHandler() // 0x10CCBA90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetRenderHandler@WebRendererHandler@Browser@Web@@UAE?AV?$scoped_refptr@VCefRenderHandler@@@@XZ");
			// Web::Browser::WebRendererHandler *const this;

			return m_RenderHandler;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		_inline scoped_refptr<CefRequestHandler> WebRendererHandler::GetRequestHandler() // 0x10CCBB90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetRequestHandler@WebRendererHandler@Browser@Web@@UAE?AV?$scoped_refptr@VCefRequestHandler@@@@XZ");
			// Web::Browser::WebRendererHandler *const this;

			return this;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		_inline scoped_refptr<CefContextMenuHandler> WebRendererHandler::GetContextMenuHandler() // 0x10CCB230
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetContextMenuHandler@WebRendererHandler@Browser@Web@@UAE?AV?$scoped_refptr@VCefContextMenuHandler@@@@XZ");
			// Web::Browser::WebRendererHandler *const this;

			return this;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		_inline scoped_refptr<CefLoadHandler> WebRendererHandler::GetLoadHandler() // 0x10CCB8F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetLoadHandler@WebRendererHandler@Browser@Web@@UAE?AV?$scoped_refptr@VCefLoadHandler@@@@XZ");
			// Web::Browser::WebRendererHandler *const this;

			return this;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		_inline std::shared_ptr<Web::Browser::Bridge::WebRendererQueryHandler> WebRendererHandler::GetQueryHandler() const // 0x10C93610
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetQueryHandler@WebRendererHandler@Browser@Web@@QBE?AV?$shared_ptr@VWebRendererQueryHandler@Bridge@Browser@Web@@@std@@XZ");
			// Web::Browser::WebRendererHandler const *const this;

			return m_QueryHandler;
		}

		_inline void WebRendererHandler::AddRef() const // 0x10CCAEC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@WebRendererHandler@Browser@Web@@UBEXXZ");
			// __shifted(Web::Browser::WebRendererHandler, 68);
			// Web::Browser::WebRendererHandler const *const this;

			ref_count_.AddRef();
		}

		_inline bool WebRendererHandler::HasAtLeastOneRef() const // 0x10CCBD20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasAtLeastOneRef@WebRendererHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererHandler, 68);
			// Web::Browser::WebRendererHandler const *const this;

			return ref_count_.HasAtLeastOneRef();
		}

		_inline bool WebRendererHandler::HasOneRef() const // 0x10CCBD80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasOneRef@WebRendererHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererHandler, 68);
			// Web::Browser::WebRendererHandler const *const this;

			return ref_count_.HasOneRef();
		}

		_inline bool WebRendererHandler::Release() const // 0x10CCE740
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@WebRendererHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererHandler, 68);
			// Web::Browser::WebRendererHandler const *const this;
			// function call : void *(unsigned __int32)

			if (ref_count_.Release())
			{
				delete static_cast<WebRendererHandler const *>(this);
				return true;
			}

			return false;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBRENDERERHANDLER_HPP__
