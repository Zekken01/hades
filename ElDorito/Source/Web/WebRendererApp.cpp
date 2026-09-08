/* ---------- headers */

#include "Web/WebRendererApp.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Utils/Rectangle.hpp"
#include "Web/WebRendererRenderHandler.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
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
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
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

class CefCommandLine;
struct CefStringTraitsUTF16;
namespace Web
{
	namespace Browser
	{
		class WebRendererApp;
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
		_extern void _sub_10CC5F90(Web::Browser::WebRendererApp *const, CefSchemeRegistrar *);
		void WebRendererApp::OnRegisterCustomSchemes(CefSchemeRegistrar *registrar) // 0x10CC5F90
		{
			mangled_x86(MANGLED_TODO, "?OnRegisterCustomSchemes@WebRendererApp@Browser@Web@@UAEXPAVCefSchemeRegistrar@@@Z");
			// CefSchemeRegistrar *registrar;
			// __int32 scheme;
			// function call : bool (CefStringBase<CefStringTraitsUTF16> const &, __int32)
			// function call : bool (CefStringBase<CefStringTraitsUTF16> const &, __int32)
			// function call : bool (CefStringBase<CefStringTraitsUTF16> const &, __int32)
			// function call : bool (CefStringBase<CefStringTraitsUTF16> const &, __int32)
			todo("implement");
			_sub_10CC5F90(this, registrar);
		}
	}
}

extern scoped_refptr<CefBrowserProcessHandler> _sub_10CC51F0(Web::Browser::WebRendererApp *const);
namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefBrowserProcessHandler> WebRendererApp::GetBrowserProcessHandler() // 0x10CC51F0
		{
			mangled_x86(MANGLED_TODO, "?GetBrowserProcessHandler@WebRendererApp@Browser@Web@@UAE?AV?$scoped_refptr@VCefBrowserProcessHandler@@@@XZ");
			// Web::Browser::WebRendererApp *const this;
			todo("implement");
			scoped_refptr<CefBrowserProcessHandler> __result = _sub_10CC51F0(this);
			return __result;
		}
	}
}

extern scoped_refptr<CefRenderProcessHandler> _sub_10CC5290(Web::Browser::WebRendererApp *const);
namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefRenderProcessHandler> WebRendererApp::GetRenderProcessHandler() // 0x10CC5290
		{
			mangled_x86(MANGLED_TODO, "?GetRenderProcessHandler@WebRendererApp@Browser@Web@@UAE?AV?$scoped_refptr@VCefRenderProcessHandler@@@@XZ");
			// Web::Browser::WebRendererApp *const this;
			todo("implement");
			scoped_refptr<CefRenderProcessHandler> __result = _sub_10CC5290(this);
			return __result;
		}

		void WebRendererApp::OnContextInitialized() // 0x10CC5F70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnContextInitialized@WebRendererApp@Browser@Web@@UAEXXZ");
			// __shifted(Web::Browser::WebRendererApp, 8);
			// Web::Browser::WebRendererApp *const this;
		}

		_extern void _sub_10CC5F00(CefRenderProcessHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefV8Context>);
		void WebRendererApp::OnContextCreated(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefV8Context> context) // 0x10CC5F00
		{
			mangled_x86(MANGLED_TODO, "?OnContextCreated@WebRendererApp@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@V?$scoped_refptr@VCefV8Context@@@@@Z");
			// __shifted(Web::Browser::WebRendererApp, 16);
			// scoped_refptr<CefV8Context> context;
			todo("implement");
			_sub_10CC5F00((CefRenderProcessHandler *)this, browser, frame, context);
		}

		_extern void _sub_10CC5330(Web::Browser::WebRendererApp *const, CefStringBase<CefStringTraitsUTF16> const &, scoped_refptr<CefCommandLine>);
		void WebRendererApp::OnBeforeCommandLineProcessing(CefStringBase<CefStringTraitsUTF16> const &process_type, scoped_refptr<CefCommandLine> command_line) // 0x10CC5330
		{
			mangled_x86(MANGLED_TODO, "?OnBeforeCommandLineProcessing@WebRendererApp@Browser@Web@@UAEXABV?$CefStringBase@UCefStringTraitsUTF16@@@@V?$scoped_refptr@VCefCommandLine@@@@@Z");
			// scoped_refptr<CefCommandLine> command_line;
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &, CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &, CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &, CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &, CefStringBase<CefStringTraitsUTF16> const &)
			todo("implement");
			_sub_10CC5330(this, process_type, command_line);
		}
	}
}

/* ---------- private code */
