#ifndef __WEB_WEBRENDERERRENDERHANDLER_HPP__
#define __WEB_WEBRENDERERRENDERHANDLER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderHandlerGpu.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include <memory>
#include <vector>

/* ---------- forward declarations */

namespace Web
{
	namespace Browser
	{
		class RenderHandlerOsr;
		class WebRendererRenderHandler;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class WebRendererRenderHandler :
			public CefRenderHandler,
			public virtual CefBaseRefCounted
		{
		public:
			WebRendererRenderHandler(IDirect3DDevice9 *device9, HWND__ *window);
			virtual _inline ~WebRendererRenderHandler() = default;
			void OnAfterCreated(scoped_refptr<CefBrowser> browser);
			void OnPreResetDevice();
			void OnPostResetDevice();
			bool InitRenderer();
			void Shutdown();
			bool Resize(unsigned __int32 width, unsigned __int32 height);
			bool Render(bool clear);
			bool IsAccelerated() const;
			bool GetViewportInformation(unsigned __int32 &width, unsigned __int32 &height);
		private:
			virtual void OnPopupShow(scoped_refptr<CefBrowser> browser, bool show);
			virtual void OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect);
			virtual void GetViewRect(scoped_refptr<CefBrowser> browser, CefRect &rect);
			virtual bool GetScreenInfo(scoped_refptr<CefBrowser> browser, CefScreenInfo &screenInfo);
			virtual bool GetScreenPoint(scoped_refptr<CefBrowser> browser, __int32 viewX, __int32 viewY, __int32 &screenX, __int32 &screenY);
			virtual void OnPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void const *buffer, __int32 width, __int32 height);
			virtual void OnAcceleratedPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void *sharedHandle);
			Microsoft::WRL::ComPtr<IDirect3DDevice9> m_Device; // 0x8
			bool m_GpuEnable; // 0xC
			HWND__ *m_Window; // 0x10
			scoped_refptr<Web::Browser::RenderHandlerOsr> m_Deglate; // 0x14
			CefRefCount ref_count_; // 0x18
		public:
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
		};
		static_assert(sizeof(Web::Browser::WebRendererRenderHandler) == 36, "Invalid Web::Browser::WebRendererRenderHandler size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{


		_inline void WebRendererRenderHandler::AddRef() const // 0x10CD0B80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@WebRendererRenderHandler@Browser@Web@@UBEXXZ");
			// __shifted(Web::Browser::WebRendererRenderHandler, 32);
			// Web::Browser::WebRendererRenderHandler const *const this;

			ref_count_.AddRef();
		}

		_inline bool WebRendererRenderHandler::HasAtLeastOneRef() const // 0x10CD12A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasAtLeastOneRef@WebRendererRenderHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererRenderHandler, 32);
			// Web::Browser::WebRendererRenderHandler const *const this;

			return ref_count_.HasAtLeastOneRef();
		}

		_inline bool WebRendererRenderHandler::HasOneRef() const // 0x10CD1300
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasOneRef@WebRendererRenderHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererRenderHandler, 32);
			// Web::Browser::WebRendererRenderHandler const *const this;

			return ref_count_.HasOneRef();
		}

		_inline bool WebRendererRenderHandler::Release() const // 0x10CD2270
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@WebRendererRenderHandler@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::WebRendererRenderHandler, 32);
			// Web::Browser::WebRendererRenderHandler const *const this;
			// function call : void *(unsigned __int32)

			if (ref_count_.Release())
			{
				delete static_cast<WebRendererRenderHandler const *>(this);
				return true;
			}

			return false;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBRENDERERRENDERHANDLER_HPP__
