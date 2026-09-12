/* ---------- headers */

#include "Web/WebRendererRenderHandler.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Utils/Rectangle.hpp"
#include "Utils/Singleton.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRendererApp.hpp"
#include "Web/WebRenderHandlerCpu.hpp"
#include "Web/WebRenderHandlerGpu.hpp"
#include "Web/WebRenderHandlerNull.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>
#include <cef_app.h>
#include <cef_audio_handler.h>
#include <cef_base.h>
#include <cef_browser_process_handler.h>
#include <cef_client.h>
#include <cef_command_handler.h>
#include <cef_context_menu_handler.h>
#include <cef_devtools_message_observer.h>
#include <cef_dialog_handler.h>
#include <cef_display_handler.h>
#include <cef_download_handler.h>
#include <cef_drag_handler.h>
#include <cef_extension_handler.h>
#include <cef_find_handler.h>
#include <cef_focus_handler.h>
#include <cef_frame_handler.h>
#include <cef_jsdialog_handler.h>
#include <cef_keyboard_handler.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_menu_model_delegate.h>
#include <cef_print_handler.h>
#include <cef_render_handler.h>
#include <cef_render_process_handler.h>
#include <cef_request_handler.h>
#include <cef_resource_handler.h>
#include <cef_resource_request_handler.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct _D3DRECT;
namespace Web
{
	namespace Browser
	{
		class WebRendererRenderHandler;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace base {}
using namespace ::base;
namespace base
{
	namespace cef_subtle {}
	using namespace base::cef_subtle;
	namespace cef_internal {}
	using namespace base::cef_internal;
	namespace internal {}
	using namespace base::internal;
}

namespace Modules {}
using namespace ::Modules;
namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		extern WebRendererRenderHandler* _sub_10CD0220(Web::Browser::WebRendererRenderHandler *const, IDirect3DDevice9 *, HWND__ *);
		WebRendererRenderHandler::WebRendererRenderHandler(IDirect3DDevice9 *device9, HWND__ *window) // 0x10CD0220
		{
			mangled_x86(MANGLED_TODO, "??0WebRendererRenderHandler@Browser@Web@@QAE@PAUIDirect3DDevice9@@PAUHWND__@@@Z");
			// HWND__ *window;
			todo("implement");
			_sub_10CD0220(this, device9, window);
		}

		_extern void _sub_10CD1A40(Web::Browser::WebRendererRenderHandler *const, scoped_refptr<CefBrowser>);
		void WebRendererRenderHandler::OnAfterCreated(scoped_refptr<CefBrowser> browser) // 0x10CD1A40
		{
			mangled_x86(MANGLED_TODO, "?OnAfterCreated@WebRendererRenderHandler@Browser@Web@@QAEXV?$scoped_refptr@VCefBrowser@@@@@Z");
			// scoped_refptr<CefBrowser> browser;
			todo("implement");
			_sub_10CD1A40(this, browser);
		}

		_extern void _sub_10CD1080(Web::Browser::WebRendererRenderHandler *const, scoped_refptr<CefBrowser>, CefRect &);
		void WebRendererRenderHandler::GetViewRect(scoped_refptr<CefBrowser> browser, CefRect &rect) // 0x10CD1080
		{
			mangled_x86(MANGLED_TODO, "?GetViewRect@WebRendererRenderHandler@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@AAVCefRect@@@Z");
			// static ...; // 0x10CD11B0
			// static ...; // 0x10CD11A8
			// Web::Browser::WebRendererRenderHandler *const this;
			// scoped_refptr<CefBrowser> browser;
			// CefRect &rect;
			// unsigned __int32 width;
			// unsigned __int32 height;
			todo("implement");
			_sub_10CD1080(this, browser, rect);
		}

		_extern bool _sub_10CD0D40(Web::Browser::WebRendererRenderHandler *const, scoped_refptr<CefBrowser>, CefScreenInfo &);
		bool WebRendererRenderHandler::GetScreenInfo(scoped_refptr<CefBrowser> browser, CefScreenInfo &screenInfo) // 0x10CD0D40
		{
			mangled_x86(MANGLED_TODO, "?GetScreenInfo@WebRendererRenderHandler@Browser@Web@@EAE_NV?$scoped_refptr@VCefBrowser@@@@AAVCefScreenInfo@@@Z");
			// static ...; // 0x10CD0E98
			// static ...; // 0x10CD0E90
			// Web::Browser::WebRendererRenderHandler *const this;
			// scoped_refptr<CefBrowser> browser;
			// CefScreenInfo &screenInfo;
			// unsigned __int32 width;
			// unsigned __int32 height;
			todo("implement");
			bool __result = _sub_10CD0D40(this, browser, screenInfo);
			return __result;
		}

		_extern bool _sub_10CD0F80(Web::Browser::WebRendererRenderHandler *const, scoped_refptr<CefBrowser>, __int32, __int32, __int32 &, __int32 &);
		bool WebRendererRenderHandler::GetScreenPoint(scoped_refptr<CefBrowser> browser, __int32 viewX, __int32 viewY, __int32 &screenX, __int32 &screenY) // 0x10CD0F80
		{
			mangled_x86(MANGLED_TODO, "?GetScreenPoint@WebRendererRenderHandler@Browser@Web@@EAE_NV?$scoped_refptr@VCefBrowser@@@@HHAAH1@Z");
			// __int32 viewX;
			// __int32 viewY;
			// __int32 &screenX;
			// __int32 &screenY;
			// tagPOINT point;
			// function call : __int32 (HWND__ *, tagPOINT *)
			todo("implement");
			bool __result = _sub_10CD0F80(this, browser, viewX, viewY, screenX, screenY);
			return __result;
		}

		_extern void _sub_10CD1C30(Web::Browser::WebRendererRenderHandler *const, scoped_refptr<CefBrowser>, bool);
		void WebRendererRenderHandler::OnPopupShow(scoped_refptr<CefBrowser> browser, bool show) // 0x10CD1C30
		{
			mangled_x86(MANGLED_TODO, "?OnPopupShow@WebRendererRenderHandler@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@_N@Z");
			// bool show;
			// function call : void (scoped_refptr<CefBrowser>, bool)
			todo("implement");
			_sub_10CD1C30(this, browser, show);
		}

		_extern void _sub_10CD1D70(Web::Browser::WebRendererRenderHandler *const, scoped_refptr<CefBrowser>, CefRect const &);
		void WebRendererRenderHandler::OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect) // 0x10CD1D70
		{
			mangled_x86(MANGLED_TODO, "?OnPopupSize@WebRendererRenderHandler@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@ABVCefRect@@@Z");
			// CefRect const &rect;
			// function call : void (scoped_refptr<CefBrowser>, CefRect const &)
			todo("implement");
			_sub_10CD1D70(this, browser, rect);
		}

		_extern void _sub_10CD1940(Web::Browser::WebRendererRenderHandler *const, scoped_refptr<CefBrowser>, cef_paint_element_type_t, std::vector<CefRect> const &, void *);
		void WebRendererRenderHandler::OnAcceleratedPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void *sharedHandle) // 0x10CD1940
		{
			mangled_x86(MANGLED_TODO, "?OnAcceleratedPaint@WebRendererRenderHandler@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_paint_element_type_t@@ABV?$vector@VCefRect@@V?$allocator@VCefRect@@@std@@@std@@PAX@Z");
			// void *sharedHandle;
			// function call : void (scoped_refptr<CefBrowser>, cef_paint_element_type_t, std::vector<CefRect> const &, void *)
			todo("implement");
			_sub_10CD1940(this, browser, type, dirtyRects, sharedHandle);
		}

		_extern void _sub_10CD1AE0(Web::Browser::WebRendererRenderHandler *const, scoped_refptr<CefBrowser>, cef_paint_element_type_t, std::vector<CefRect> const &, void const *, __int32, __int32);
		void WebRendererRenderHandler::OnPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void const *buffer, __int32 width, __int32 height) // 0x10CD1AE0
		{
			mangled_x86(MANGLED_TODO, "?OnPaint@WebRendererRenderHandler@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_paint_element_type_t@@ABV?$vector@VCefRect@@V?$allocator@VCefRect@@@std@@@std@@PBXHH@Z");
			// __int32 height;
			// function call : void (scoped_refptr<CefBrowser>, cef_paint_element_type_t, std::vector<CefRect> const &, void const *, __int32, __int32)
			todo("implement");
			_sub_10CD1AE0(this, browser, type, dirtyRects, buffer, width, height);
		}

		bool WebRendererRenderHandler::GetViewportInformation(unsigned __int32 &width, unsigned __int32 &height) // 0x10CD1230
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetViewportInformation@WebRendererRenderHandler@Browser@Web@@QAE_NAAI0@Z");
			// unsigned __int32 &height;
			// __int32 *windowResolution;

			__int32 *windowResolution = (__int32 *)0x19106e4;

			width = windowResolution[0];
			height = windowResolution[1];
			return true;
		}

		_extern bool _sub_10CD2450(Web::Browser::WebRendererRenderHandler *const, unsigned __int32, unsigned __int32);
		bool WebRendererRenderHandler::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CD2450
		{
			mangled_x86(MANGLED_TODO, "?Resize@WebRendererRenderHandler@Browser@Web@@QAE_NII@Z");
			// unsigned __int32 height;
			// function call : bool (unsigned __int32, unsigned __int32)
			todo("implement");
			bool __result = _sub_10CD2450(this, width, height);
			return __result;
		}

		void WebRendererRenderHandler::OnPreResetDevice() // 0x10CD2010
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPreResetDevice@WebRendererRenderHandler@Browser@Web@@QAEXXZ");
			// Web::Browser::WebRendererRenderHandler *const this;
			// function call : void ()

			m_Deglate->OnPreResetDevice();
		}

		_extern void _sub_10CD1E60(Web::Browser::WebRendererRenderHandler *const);
		void WebRendererRenderHandler::OnPostResetDevice() // 0x10CD1E60
		{
			mangled_x86(MANGLED_TODO, "?OnPostResetDevice@WebRendererRenderHandler@Browser@Web@@QAEXXZ");
			// static ...; // 0x10CD1FB3
			// static ...; // 0x10CD1FAC
			// static ...; // 0x10CD1F94
			// static ...; // 0x10CD1F8C
			// Web::Browser::WebRendererRenderHandler *const this;
			// unsigned __int32 width;
			// unsigned __int32 height;
			// function call : void ()
			todo("implement");
			_sub_10CD1E60(this);
		}

		_extern bool _sub_10CD1350(Web::Browser::WebRendererRenderHandler *const);
		bool WebRendererRenderHandler::InitRenderer() // 0x10CD1350
		{
			mangled_x86(MANGLED_TODO, "?InitRenderer@WebRendererRenderHandler@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRendererRenderHandler *const this;
			// function call : bool ()
			// function call : bool ()
			todo("implement");
			bool __result = _sub_10CD1350(this);
			return __result;
		}

		bool WebRendererRenderHandler::Render(bool clear) // 0x10CD2360
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Render@WebRendererRenderHandler@Browser@Web@@QAE_N_N@Z");
			// bool clear;
			// function call : HRESULT (unsigned long, _D3DRECT const *, unsigned long, unsigned long, float, unsigned long)
			// function call : bool ()

			if (clear)
			{
				m_Device->Clear(1, nullptr, 1, 0xFF808080, 0.0f, 0);
			}

			return m_Deglate->Render();
		}

		void WebRendererRenderHandler::Shutdown() // 0x10CD25D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@WebRendererRenderHandler@Browser@Web@@QAEXXZ");
			// Web::Browser::WebRendererRenderHandler *const this;
			// function call : void ()

			m_Deglate->Shutdown();
		}

		bool WebRendererRenderHandler::IsAccelerated() const // 0x10CD18C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsAccelerated@WebRendererRenderHandler@Browser@Web@@QBE_NXZ");
			// Web::Browser::WebRendererRenderHandler const *const this;

			return m_GpuEnable;
		}
	}
}

/* ---------- private code */
