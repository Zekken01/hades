/* ---------- headers */

#include "Web/WebRendererApp.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Utils/Rectangle.hpp"
#include "Web/WebRendererRenderHandler.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include "Web/WebRenderer.hpp"  // hades: added for 0x10CC5330

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
		void WebRendererApp::OnRegisterCustomSchemes(CefSchemeRegistrar *registrar) // 0x10CC5F90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnRegisterCustomSchemes@WebRendererApp@Browser@Web@@UAEXPAVCefSchemeRegistrar@@@Z");

			__int32 scheme = CEF_SCHEME_OPTION_STANDARD | CEF_SCHEME_OPTION_SECURE | CEF_SCHEME_OPTION_CORS_ENABLED | CEF_SCHEME_OPTION_FETCH_ENABLED;
			registrar->AddCustomScheme("dew", scheme);
			registrar->AddCustomScheme("medals", scheme);
			registrar->AddCustomScheme("emblems", scheme);
			registrar->AddCustomScheme("pak", scheme);
		}
	}
}


namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefBrowserProcessHandler> WebRendererApp::GetBrowserProcessHandler() // 0x10CC51F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetBrowserProcessHandler@WebRendererApp@Browser@Web@@UAE?AV?$scoped_refptr@VCefBrowserProcessHandler@@@@XZ");

			return this;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefRenderProcessHandler> WebRendererApp::GetRenderProcessHandler() // 0x10CC5290
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetRenderProcessHandler@WebRendererApp@Browser@Web@@UAE?AV?$scoped_refptr@VCefRenderProcessHandler@@@@XZ");

			return this;
		}

		void WebRendererApp::OnContextInitialized() // 0x10CC5F70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnContextInitialized@WebRendererApp@Browser@Web@@UAEXXZ");
		}

		void WebRendererApp::OnContextCreated(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefV8Context> context) // 0x10CC5F00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnContextCreated@WebRendererApp@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@V?$scoped_refptr@VCefV8Context@@@@@Z");
		}

		void WebRendererApp::OnBeforeCommandLineProcessing(CefStringBase<CefStringTraitsUTF16> const &process_type, scoped_refptr<CefCommandLine> command_line) // 0x10CC5330
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnBeforeCommandLineProcessing@WebRendererApp@Browser@Web@@UAEXABV?$CefStringBase@UCefStringTraitsUTF16@@@@V?$scoped_refptr@VCefCommandLine@@@@@Z");

			if (Web::Browser::WebRenderer::GetInstance()->IsAccelerated())
			{
				command_line->AppendSwitchWithValue("use-angle", "d3d11");
				command_line->AppendSwitch("ignore-gpu-blacklist");
				command_line->AppendSwitch("ignore-gpu-blocklist");
				command_line->AppendSwitch("force-gpu-rasterization");
				command_line->AppendSwitchWithValue("disable-features", "UseSkiaRenderer");
				command_line->AppendSwitch("disable-gpu-vsync");
			}
			else
			{
				command_line->AppendSwitch("disable-gpu");
				command_line->AppendSwitch("disable-gpu-compositing");
			}
			command_line->AppendSwitch("disable-extensions");
			command_line->AppendSwitchWithValue("autoplay-policy", "no-user-gesture-required");
			command_line->AppendSwitch("enable-experimental-web-platform-features");
			command_line->AppendSwitch("enable-media-stream");
			command_line->AppendSwitch("enable-precise-memory-info");
			command_line->AppendSwitch("no-proxy-server");
			command_line->AppendSwitch("disable-renderer-backgrounding");
			command_line->AppendSwitch("file_access_from_file_urls");
			command_line->AppendSwitch("universal_access_from_file_urls");
			command_line->AppendSwitch("disable-back-forward-cache");
			command_line->AppendSwitch("disable-renderer-accessibility");
			command_line->AppendSwitch("disable-site-isolation-trials");
			command_line->AppendSwitchWithValue("force-device-scale-factor", "1");
		}
	}
}

/* ---------- private code */
