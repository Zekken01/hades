#ifndef __WEB_WEBRENDERHANDLEROSR_HPP__
#define __WEB_WEBRENDERHANDLEROSR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <memory>
#include <vector>

/* ---------- forward declarations */

namespace Web
{
	namespace Browser
	{
		class RenderHandlerOsr;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class RenderHandlerOsr :
			public virtual CefBaseRefCounted
		{
		public:
			public:
			enum PaintElementType
			{
				PET_VIEW = 0,
				PET_POPUP,
			};
			public:
			virtual _inline ~RenderHandlerOsr();
			virtual _inline void OnPopupShow(scoped_refptr<CefBrowser> browser, bool show);
			virtual _inline void OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect);
			virtual _inline void OnPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void const *buffer, __int32 width, __int32 height);
			virtual _inline void OnAcceleratedPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void *sharedHandle);
			virtual _inline bool InitRenderer();
			virtual _inline bool Resize(unsigned __int32 width, unsigned __int32 height);
			virtual _inline bool Render();
			virtual _inline void OnPreResetDevice();
			virtual _inline void OnPostResetDevice();
			virtual _inline void Shutdown();
			RenderHandlerOsr(Web::Browser::RenderHandlerOsr const &); /* compiler_generated() */
			_inline RenderHandlerOsr(); /* compiler_generated() */
			Web::Browser::RenderHandlerOsr &operator=(Web::Browser::RenderHandlerOsr const &); /* compiler_generated() */
		};
		static_assert(sizeof(Web::Browser::RenderHandlerOsr) == 12, "Invalid Web::Browser::RenderHandlerOsr size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		_inline RenderHandlerOsr::~RenderHandlerOsr() // 0x10CE8350
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1RenderHandlerOsr@Browser@Web@@UAE@XZ");
			// __shifted(Web::Browser::RenderHandlerOsr, 8);
			// Web::Browser::RenderHandlerOsr *const this;
		}

		_extern void _sub_10CE9550(Web::Browser::RenderHandlerOsr *const, scoped_refptr<CefBrowser>, bool);
		_inline void RenderHandlerOsr::OnPopupShow(scoped_refptr<CefBrowser> browser, bool show) // 0x10CE9550
		{
			mangled_x86(MANGLED_TODO, "?OnPopupShow@RenderHandlerOsr@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@_N@Z");
			// bool show;
			todo("implement");
			_sub_10CE9550(this, browser, show);
		}

		_extern void _sub_10CE96D0(Web::Browser::RenderHandlerOsr *const, scoped_refptr<CefBrowser>, CefRect const &);
		_inline void RenderHandlerOsr::OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect) // 0x10CE96D0
		{
			mangled_x86(MANGLED_TODO, "?OnPopupSize@RenderHandlerOsr@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@ABVCefRect@@@Z");
			// CefRect const &rect;
			todo("implement");
			_sub_10CE96D0(this, browser, rect);
		}

		_extern void _sub_10CE9390(Web::Browser::RenderHandlerOsr *const, scoped_refptr<CefBrowser>, cef_paint_element_type_t, std::vector<CefRect> const &, void const *, __int32, __int32);
		_inline void RenderHandlerOsr::OnPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void const *buffer, __int32 width, __int32 height) // 0x10CE9390
		{
			mangled_x86(MANGLED_TODO, "?OnPaint@RenderHandlerOsr@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_paint_element_type_t@@ABV?$vector@VCefRect@@V?$allocator@VCefRect@@@std@@@std@@PBXHH@Z");
			// __int32 height;
			todo("implement");
			_sub_10CE9390(this, browser, type, dirtyRects, buffer, width, height);
		}

		_extern void _sub_10CE8D20(Web::Browser::RenderHandlerOsr *const, scoped_refptr<CefBrowser>, cef_paint_element_type_t, std::vector<CefRect> const &, void *);
		_inline void RenderHandlerOsr::OnAcceleratedPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void *sharedHandle) // 0x10CE8D20
		{
			mangled_x86(MANGLED_TODO, "?OnAcceleratedPaint@RenderHandlerOsr@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_paint_element_type_t@@ABV?$vector@VCefRect@@V?$allocator@VCefRect@@@std@@@std@@PAX@Z");
			// void *sharedHandle;
			todo("implement");
			_sub_10CE8D20(this, browser, type, dirtyRects, sharedHandle);
		}

		_inline bool RenderHandlerOsr::InitRenderer() // 0x10CE8C30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitRenderer@RenderHandlerOsr@Browser@Web@@UAE_NXZ");
			// Web::Browser::RenderHandlerOsr *const this;

			return true;
		}

		_inline bool RenderHandlerOsr::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CEA180
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Resize@RenderHandlerOsr@Browser@Web@@UAE_NII@Z");
			// unsigned __int32 height;

			return true;
		}

		_inline bool RenderHandlerOsr::Render() // 0x10CE9DB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Render@RenderHandlerOsr@Browser@Web@@UAE_NXZ");
			// Web::Browser::RenderHandlerOsr *const this;

			return true;
		}

		_inline void RenderHandlerOsr::OnPreResetDevice() // 0x10CE9860
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPreResetDevice@RenderHandlerOsr@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerOsr *const this;
		}

		_inline void RenderHandlerOsr::OnPostResetDevice() // 0x10CE97B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPostResetDevice@RenderHandlerOsr@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerOsr *const this;
		}

		_inline void RenderHandlerOsr::Shutdown() // 0x10CEA2A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@RenderHandlerOsr@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerOsr *const this;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBRENDERHANDLEROSR_HPP__
