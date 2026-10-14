/* ---------- headers */

#include "Web/WebRenderer.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/Magnets.hpp"
#include "mods/mod_package_updater.hpp"
#include "Patches/CustomPackets.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Macros.hpp"
#include "Utils/Rectangle.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebEmblemSchemeHandler.hpp"
#include "Web/WebRendererApp.hpp"
#include "Web/WebEmblemSchemeHandler.hpp"  // hades: added for 0x10CBA540
#include "Web/WebRendererHandler.hpp"
#include "Web/WebRendererRenderHandler.hpp"
#include "Web/WebRendererSchemeHandlerFactory.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include "Web/Bridge/WebRendererQueryHandler.hpp"  // hades: added for 0x10CC3EB0

#include "Utils/Logger.hpp"  // hades: added for 0x10CBA660

#include <cef_origin_whitelist.h>  // hades: added for 0x10CC1910  // hades: added for 0x10CC1910

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
#include <cef_scheme.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_message_router.h>

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
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <queue>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct CefStringTraitsUTF16;
struct _D3DDEVICE_CREATION_PARAMETERS;
struct lambda_1;
namespace Web
{
	namespace Browser
	{
		class WebEmblemSchemeHandlerFactory;
		class WebRenderer;
		class WebRendererApp;
		class WebRendererHandler;
		class WebRendererRenderHandler;
		class WebRendererSchemeHandlerFactory;
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

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

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

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

/* ---------- constants */

/* ---------- definitions */

//class Web::Browser::WebRenderer::ExecuteJavascript::__l7::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(Web::Browser::WebRenderer::ExecuteJavascript::__l7::<lambda_1> &);
//	<lambda_1>(Web::Browser::WebRenderer::ExecuteJavascript::__l7::<lambda_1> const &);
//	<lambda_1>(Web::Browser::WebRenderer *, std::string &);
//private:
//	Web::Browser::WebRenderer *__this; // 0x0
//	std::string code; // 0x4
//public:
//	Web::Browser::WebRenderer::ExecuteJavascript::__l7::<lambda_1> &operator=(Web::Browser::WebRenderer::ExecuteJavascript::__l7::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(Web::Browser::WebRenderer::ExecuteJavascript::__l7::<lambda_1>) == 32, "Invalid Web::Browser::WebRenderer::ExecuteJavascript::__l7::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		WebRenderer::WebRenderer() : m_Handler(nullptr), m_RenderHandler(nullptr), m_App(nullptr), m_State(RendererState_Disabled), m_HostWindow(nullptr), m_MainFrameLoaded(false), m_useOSR(false), m_cefPath(std::filesystem::absolute("bin\\cef")) /* hades-mem-init:  */ // 0x10CBA660
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WebRenderer@Browser@Web@@QAE@XZ");
			// Web::Browser::WebRenderer *const this;
			// function call : __int32 (wchar_t const *)
			// function call : HINSTANCE__ *(wchar_t const *)

			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::WebRenderer:26 - WebRenderer Ctor.");
			SetDllDirectoryW(m_cefPath.wstring().c_str());
			LoadLibraryW((m_cefPath / "libcef.dll").wstring().c_str());
		}

		// mangled_x86(MANGLED_DEFAULT, "??0WebRendererApp@Browser@Web@@QAE@XZ"); no body to assert in
	}
}


namespace Web
{
	namespace Browser
	{
		std::shared_ptr<Web::Browser::WebRenderer> WebRenderer::GetInstance() // 0x10CBDF10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetInstance@WebRenderer@Browser@Web@@SA?AV?$shared_ptr@VWebRenderer@Browser@Web@@@std@@XZ");
			// procedure flags: nofpo
			// static std::shared_ptr<Web::Browser::WebRenderer> instance; // 0x1247EE1C
			// static __int32 $TSS0; // 0x1247EE24

			static std::shared_ptr<Web::Browser::WebRenderer> instance = std::make_shared<Web::Browser::WebRenderer>();
			return instance;
		}

		// mangled_x86(MANGLED_DEFAULT, "??1WebRenderer@Browser@Web@@QAE@XZ"); no body to assert in
		_inline WebRenderer::~WebRenderer() = default; // 0x10CBB8F0
	}
}


namespace Web
{
	namespace Browser
	{
		std::string WebRenderer::GetUIDirectory() // 0x10CBE270
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetUIDirectory@WebRenderer@Browser@Web@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// Web::Browser::WebRenderer *const this;

			return std::filesystem::absolute("ui").string();
		}

		bool WebRenderer::IsAccelerated() const // 0x10CC0D90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsAccelerated@WebRenderer@Browser@Web@@QBE_NXZ");
			// Web::Browser::WebRenderer const *const this;

			if (!m_RenderHandler)
			{
				return false;
			}

			return m_RenderHandler->IsAccelerated();
		}

		bool WebRenderer::Init(std::string const &url, bool debugEnable) // 0x10CBE930
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@WebRenderer@Browser@Web@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
			// static ...; // 0x10CC0279
			// static ...; // 0x10CC0271
			// static ...; // 0x10CC0268
			// static ...; // 0x10CC0265
			// static ...; // 0x10CC0255
			// static ...; // 0x10CC024A
			// static ...; // 0x10CC0247
			// static ...; // 0x10CC0239
			// static ...; // 0x10CC022D
			// static ...; // 0x10CC0227
			// static ...; // 0x10CC0220
			// static ...; // 0x10CC0184
			// static ...; // 0x10CC017C
			// Web::Browser::WebRenderer *const this;
			// std::string const &url;
			// bool debugEnable;
			// std::error_code ec;
			// std::string uiDirectory;
			// std::string logFile;
			// std::filesystem::path cefCache;
			// std::string containerPath;
			// __int32 res;
			// CefWindowInfo windowInfo;
			// std::filesystem::path log_dir;
			// CefStructBase<CefBrowserSettingsTraits> browserSettings;
			// unsigned __int32 width;
			// CefMainArgs mainArgs;
			// CefStructBase<CefSettingsTraits> settings;
			// unsigned __int32 height;
				// tagRECT rc;
			// function call : HINSTANCE__ *(char const *)
			// function call : void *()
			// function call : __int32 (void *, unsigned __int32)
			// function call : void (unsigned __int32)
			// function call : __int32 (HWND__ *, tagRECT *)

			if (GetState() != RendererState_Startup)
				return false;
			m_HostWindow = *(HWND__ **)0x199C014;
			m_App = new WebRendererApp();
			if (!m_App)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:62 - App (%p) is invalid.", m_App);
				Shutdown();
				return false;
			}
			m_useOSR = true;
			CefMainArgs mainArgs(GetModuleHandleA(nullptr));
			__int32 res = CefExecuteProcess(mainArgs, m_App, nullptr);
			if (res >= 0)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:74 - CefExecuteProcess failed (%x).", res);
				TerminateProcess(GetCurrentProcess(), 0);
				return false;
			}
			CefSettings settings;
			CefString(&settings.user_agent) = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.67 Safari/537.36";
			settings.multi_threaded_message_loop = true;
			CefString(&settings.user_agent_product) = "ElDewrito";
			settings.no_sandbox = true;
			settings.pack_loading_disabled = false;
			settings.windowless_rendering_enabled = m_useOSR;
			std::filesystem::path log_dir = std::filesystem::absolute("logs");
			std::filesystem::create_directories(log_dir);
			std::string logFile = "custom_menu.log";
			if (ElDorito::Instance().GetInstanceName() != "")
				logFile = "custom_menu_" + ElDorito::Instance().GetInstanceName() + ".log";
			settings.persist_user_preferences = true;
			CefString(&settings.browser_subprocess_path) = std::filesystem::absolute("custom_menu.exe");
			CefString(&settings.log_file) = log_dir / logFile;
			CefString(&settings.resources_dir_path) = m_cefPath / "resources";
			CefString(&settings.locales_dir_path) = m_cefPath / "resources/locales";
			std::filesystem::path cefCache = std::filesystem::absolute("data/cache/cef");
			if (ElDorito::Instance().GetInstanceName() != "")
				cefCache = std::filesystem::absolute("data/cache/cef_" + ElDorito::Instance().GetInstanceName());
			CefString(&settings.user_data_path) = cefCache;
			CefString(&settings.cache_path) = cefCache;
			settings.log_severity = ElDorito::Instance().IsWebDebugLoggingEnabled() ? LOGSEVERITY_VERBOSE : LOGSEVERITY_WARNING;
			if (debugEnable)
			{
				settings.remote_debugging_port = ElDorito::Instance().GetWebDebugPort();
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:118 - Web renderer debugging enabled on port %d", settings.remote_debugging_port);
			}
			std::error_code ec;
			std::filesystem::remove(settings.log_file.str, ec);
			if (ec)
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:125 - Failed to remove log file.");
			if (!CefInitialize(mainArgs, settings, m_App, nullptr))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:129 - CefInitialize failed.");
				ExitProcess(0);
				return false;
			}
			CefBrowserSettings browserSettings;
			browserSettings.windowless_frame_rate = 60;
			browserSettings.webgl = STATE_ENABLED;
			browserSettings.javascript = STATE_ENABLED;
			browserSettings.local_storage = STATE_ENABLED;
			browserSettings.databases = STATE_ENABLED;
			browserSettings.javascript_close_windows = STATE_DISABLED;
			browserSettings.javascript_access_clipboard = STATE_DISABLED;
			browserSettings.remote_fonts = STATE_ENABLED;
			browserSettings.image_loading = STATE_ENABLED;
			CefWindowInfo windowInfo;
			if (m_useOSR)
			{
				windowInfo.SetAsWindowless(m_HostWindow);
				windowInfo.shared_texture_enabled = IsAccelerated();
			}
			else
			{
				tagRECT rc;
				GetClientRect(m_HostWindow, &rc);
				windowInfo.SetAsChild(m_HostWindow, CefRect(0, 0, rc.right - rc.left, rc.bottom - rc.top));
				windowInfo.style |= WS_DISABLED;
			}
			m_Handler = new WebRendererHandler(m_RenderHandler);
			if (!m_Handler)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:168 - WebRendererHandler failed to initialize.");
				Shutdown();
				return false;
			}
			RegisterScheme("dew", GetUIDirectory());
			CefAddCrossOriginWhitelistEntry("dew://ui", "http", "", true);
			CefAddCrossOriginWhitelistEntry("dew://ui", "https", "", true);
			if (!CefRegisterSchemeHandlerFactory("emblems", "", new WebEmblemSchemeHandlerFactory()))
				return false;
			CefAddCrossOriginWhitelistEntry("dew://*", "emblems", "", true);
			InitPakFileSystem();
			std::string containerPath = url;
			std::string uiDirectory = GetUIDirectory();
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:189 - UI Directory: %s", uiDirectory.c_str());
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:190 - Container Path: %s.", containerPath.c_str());
			if (!CefBrowserHost::CreateBrowser(windowInfo, m_Handler.get(), containerPath.c_str(), browserSettings, nullptr, nullptr))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:194 - Failed to initialize WebRenderer.");
				Shutdown();
				return false;
			}
			unsigned __int32 width = 0;
			unsigned __int32 height = 0;
			if (!m_RenderHandler->GetViewportInformation(width, height))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:202 - Failed to get viewport dimensions.");
				Shutdown();
				return false;
			}
			if (!Resize(width, height))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Init:209 - Resize failed.");
				Shutdown();
				return false;
			}
			SetState(RendererState_Overlay);
			return true;
		}

		bool WebRenderer::InitRenderer(IDirect3DDevice9 *device) // 0x10CC09F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitRenderer@WebRenderer@Browser@Web@@QAE_NPAUIDirect3DDevice9@@@Z");
			// static ...; // 0x10CC0C4C
			// static ...; // 0x10CC0C44
			// Web::Browser::WebRenderer *const this;
			// IDirect3DDevice9 *device;
			// _D3DDEVICE_CREATION_PARAMETERS d3dpp;
			// HRESULT hr;
			// function call : HRESULT (_D3DDEVICE_CREATION_PARAMETERS *)

			if (GetState() != RendererState_Disabled)
				return false;
			if (!device)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::InitRenderer:228 - Device is invalid.");
				Shutdown();
				return false;
			}
			_D3DDEVICE_CREATION_PARAMETERS d3dpp;
			memset(&d3dpp, 0, sizeof(d3dpp));
			HRESULT hr = device->GetCreationParameters(&d3dpp);
			if (FAILED(hr))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::InitRenderer:240 - Could not get the creation parameters.");
				Shutdown();
				return false;
			}
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::InitRenderer:245 - WebRenderer InitRenderer.");
			m_RenderHandler = new WebRendererRenderHandler(device, d3dpp.hFocusWindow);
			if (!m_RenderHandler->InitRenderer())
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::InitRenderer:251 - Failed to initialize renderer");
				Shutdown();
				return false;
			}
			SetState(RendererState_Startup);
			return true;
		}

		bool WebRenderer::Render(IDirect3DDevice9 *device) // 0x10CC2510
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Render@WebRenderer@Browser@Web@@QAE_NPAUIDirect3DDevice9@@@Z");
			// IDirect3DDevice9 *device;
			// Web::Browser::RendererState state;

			Web::Browser::RendererState state = GetState();
			if (state != Web::Browser::RendererState_Overlay && state != Web::Browser::RendererState_Shown)
			{
				return false;
			}

			return m_RenderHandler->Render(state == Web::Browser::RendererState_Shown);
		}

		bool WebRenderer::Update() // 0x10CC3EB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Update@WebRenderer@Browser@Web@@QAE_NXZ");
			// static ...; // 0x10CC3FA4
			// static ...; // 0x10CC3F98
			// static ...; // 0x10CC3F90
			// Web::Browser::WebRenderer *const this;
			// std::shared_ptr<Web::Browser::Bridge::WebRendererQueryHandler> queryHandler;

			if (!Initialized())
				return false;

			std::shared_ptr<Web::Browser::Bridge::WebRendererQueryHandler> queryHandler = m_Handler->GetQueryHandler();
			if (queryHandler)
				queryHandler->Update();
			return true;
		}

		bool WebRenderer::Initialized() // 0x10CC0D00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Initialized@WebRenderer@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRenderer *const this;
			// Web::Browser::RendererState state;

			Web::Browser::RendererState state = GetState();
			return state == Web::Browser::RendererState_Overlay || state == Web::Browser::RendererState_Shown || state == Web::Browser::RendererState_Hidden;
		}

		bool WebRenderer::IsRendering() // 0x10CC0E10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsRendering@WebRenderer@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRenderer *const this;

			return GetState() == Web::Browser::RendererState_Overlay || GetState() == Web::Browser::RendererState_Shown;
		}

		bool WebRenderer::ShowRenderer(bool show, bool overlay) // 0x10CC3790
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ShowRenderer@WebRenderer@Browser@Web@@QAE_N_N0@Z");
			// static ...; // 0x10CC3A70
			// static ...; // 0x10CC3A68
			// Web::Browser::WebRenderer *const this;
			// bool show;
			// bool overlay;
			// Web::Browser::RendererState state;
				// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (bool)
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (bool)

			Web::Browser::RendererState state = GetState();
			if (state == RendererState_Hidden && show)
			{
				SetState(overlay ? RendererState_Overlay : RendererState_Shown);
				if (m_Handler)
				{
					scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
					if (browser)
						browser->GetHost()->SetFocus(true);
				}
				return true;
			}
			if ((state == RendererState_Overlay || state == RendererState_Shown) && !show)
			{
				SetState(RendererState_Hidden);
				if (m_Handler)
				{
					scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
					if (browser)
						browser->GetHost()->SetFocus(false);
				}
				return true;
			}
			return false;
		}

		bool WebRenderer::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CC25C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Resize@WebRenderer@Browser@Web@@QAE_NII@Z");
			// static ...; // 0x10CC2A08
			// Web::Browser::WebRenderer *const this;
			// unsigned __int32 width;
			// unsigned __int32 height;
			// CefBrowser *browser;
			// bool res;
				// tagRECT rc;
			// function call : __int32 (HWND__ *, tagRECT *)
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : HWND__ *()
			// function call : __int32 (HWND__ *, HWND__ *, __int32, __int32, __int32, __int32, unsigned __int32)
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void ()
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void ()
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (cef_paint_element_type_t)
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (cef_paint_element_type_t)

			if (!m_Handler)
				return false;
			bool res = m_RenderHandler->Resize(width, height);
			if (!res)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::WebRenderer::Resize:346 - Resize failed.");
				return false;
			}
			CefBrowser *browser = m_Handler->GetBrowser().get();
			if (browser)
			{
				if (!m_useOSR)
				{
					RECT rc;
					GetClientRect(m_HostWindow, &rc);
					SetWindowPos(browser->GetHost()->GetWindowHandle(), nullptr, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);
				}
				browser->GetHost()->NotifyScreenInfoChanged();
				browser->GetHost()->WasResized();
				browser->GetHost()->Invalidate(PET_VIEW);
				browser->GetHost()->Invalidate(PET_POPUP);
			}
			return true;
		}

		bool WebRenderer::SendMouseMoveEvent(CefStructBase<CefMouseEventTraits> const &p_Event, bool p_MouseLeave) // 0x10CC2FE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendMouseMoveEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefMouseEventTraits@@@@_N@Z");
			// bool p_MouseLeave;
			// CefBrowser *browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefMouseEventTraits> const &, bool)

			if (!m_Handler || !IsRendering())
				return false;
			CefBrowser *browser = m_Handler->GetBrowser().get();
			if (!browser)
				return false;
			browser->GetHost()->SendMouseMoveEvent(p_Event, p_MouseLeave);
			return true;
		}

		bool WebRenderer::SendMouseClickEvent(CefStructBase<CefMouseEventTraits> const &event, cef_mouse_button_type_t button, bool mouseUp, __int32 clickCount) // 0x10CC2D70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendMouseClickEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefMouseEventTraits@@@@W4cef_mouse_button_type_t@@_NH@Z");
			// CefStructBase<CefMouseEventTraits> const &event;
			// cef_mouse_button_type_t button;
			// bool mouseUp;
			// __int32 clickCount;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefMouseEventTraits> const &, cef_mouse_button_type_t, bool, __int32)

			if (clickCount < 1)
				clickCount = 1;
			if (clickCount > 2)
				clickCount = 2;
			if (!m_Handler || !IsRendering())
				return false;
			scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
			if (!browser)
				return false;
			browser->GetHost()->SendMouseClickEvent(event, button, mouseUp, clickCount);
			return true;
		}

		bool WebRenderer::SendMouseWheelEvent(CefStructBase<CefMouseEventTraits> const &event, __int32 deltaX, __int32 deltaY) // 0x10CC31D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendMouseWheelEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefMouseEventTraits@@@@HH@Z");
			// Web::Browser::WebRenderer *const this;
			// CefStructBase<CefMouseEventTraits> const &event;
			// __int32 deltaX;
			// __int32 deltaY;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefMouseEventTraits> const &, __int32, __int32)

			if (!m_Handler || !IsRendering())
				return false;
			scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
			if (!browser)
				return false;
			browser->GetHost()->SendMouseWheelEvent(event, deltaX, deltaY);
			return true;
		}

		bool WebRenderer::SendKeyEvent(CefStructBase<CefKeyEventTraits> const &p_Event) // 0x10CC2B40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendKeyEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefKeyEventTraits@@@@@Z");
			// static ...; // 0x10CC2CEC
			// static ...; // 0x10CC2CE4
			// Web::Browser::WebRenderer *const this;
			// CefStructBase<CefKeyEventTraits> const &p_Event;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefKeyEventTraits> const &)

			if (!m_Handler || !IsRendering())
				return false;
			scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
			if (!browser)
				return false;
			browser->GetHost()->SendKeyEvent(p_Event);
			return true;
		}

		bool WebRenderer::SendPlatformEvent(CefStructBase<CefPlatformEventTraits> const &event) // 0x10CC3410
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendPlatformEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefPlatformEventTraits@@@@@Z");
			// static ...; // 0x10CC35BC
			// static ...; // 0x10CC35B4
			// Web::Browser::WebRenderer *const this;
			// CefStructBase<CefPlatformEventTraits> const &event;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefPlatformEventTraits> const &)

			if (!m_Handler || !IsRendering())
				return false;
			scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
			if (!browser)
				return false;
			browser->GetHost()->SendPlatformEvent(event);
			return true;
		}

		bool WebRenderer::OpenUrl(std::string const &p_Url) // 0x10CC1500
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OpenUrl@WebRenderer@Browser@Web@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10CC16D8
			// static ...; // 0x10CC16D0
			// Web::Browser::WebRenderer *const this;
			// std::string const &p_Url;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefFrame> ()
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)

			if (!m_Handler || !Initialized())
				return false;
			PurgeDOMTasks();
			scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
			if (!browser)
				return false;
			browser->GetMainFrame()->LoadURL(p_Url);
			return true;
		}

		bool WebRenderer::Reload(bool p_IgnoreCache) // 0x10CC2330
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Reload@WebRenderer@Browser@Web@@QAE_N_N@Z");
			// static ...; // 0x10CC249C
			// static ...; // 0x10CC2494
			// Web::Browser::WebRenderer *const this;
			// bool p_IgnoreCache;
			// scoped_refptr<CefBrowser> browser;
			// function call : void ()
			// function call : void ()

			if (!m_Handler || !Initialized())
				return false;

			scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
			if (!browser)
				return false;

			if (p_IgnoreCache)
				browser->ReloadIgnoreCache();
			else
				browser->Reload();
			return true;
		}

		bool WebRenderer::RegisterScheme(std::string const &p_Name, std::string const &p_Directory) // 0x10CC1910
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterScheme@WebRenderer@Browser@Web@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// std::string const &p_Directory;
			// Web::Browser::WebRendererSchemeHandlerFactory *schemeHandlerFactory;

			if (!std::filesystem::exists(p_Directory))
				return false;
			WebRendererSchemeHandlerFactory *schemeHandlerFactory = new WebRendererSchemeHandlerFactory(p_Name, p_Directory);
			if (!CefRegisterSchemeHandlerFactory(p_Name, "", schemeHandlerFactory))
				return false;
			if (p_Name != "dew")
				CefAddCrossOriginWhitelistEntry("dew://*", p_Name, "", true);
			return true;
		}

		bool WebRenderer::ExecuteJavascript(std::string p_Code, bool deferIfNeeded) // 0x10CBD950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteJavascript@WebRenderer@Browser@Web@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
			// static ...; // 0x10CBDC1C
			// Web::Browser::WebRenderer *const this;
			// std::string p_Code;
			// bool deferIfNeeded;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefFrame> ()
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &, CefStringBase<CefStringTraitsUTF16> const &, __int32)

			if (!m_Handler)
				return false;
			scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
			if (!browser || !m_MainFrameLoaded.load())
			{
				if (!deferIfNeeded)
					return false;
				EnqueueDOMTask([this, p_Code = std::move(p_Code)]() { ExecuteJavascript(p_Code, false); });
				return true;
			}
			browser->GetMainFrame()->ExecuteJavaScript(p_Code, "internal", 0);
			return true;
		}

		bool WebRenderer::PreReset() // 0x10CC17E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PreReset@WebRenderer@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRenderer *const this;

			if (m_RenderHandler)
			{
				m_RenderHandler->OnPreResetDevice();
			}

			return true;
		}

		bool WebRenderer::PostReset() // 0x10CC1770
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PostReset@WebRenderer@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRenderer *const this;

			if (m_RenderHandler)
			{
				m_RenderHandler->OnPostResetDevice();
			}

			return true;
		}

		bool WebRenderer::Shutdown() // 0x10CC3B60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@WebRenderer@Browser@Web@@QAE_NXZ");
			// static ...; // 0x10CC3DFC
			// static ...; // 0x10CC3DF0
			// static ...; // 0x10CC3DE8
		// $LN15:
		// $LN10:
			// Web::Browser::WebRenderer *const this;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (bool)
			// function call : bool () const
			// function call : void (unsigned long)

			if (m_State == RendererState_Disabled || m_State == RendererState_Shutdown)
				return false;
			SetState(RendererState_Shutdown);
			m_RenderHandler->Shutdown();
			scoped_refptr<CefBrowser> browser = m_Handler->GetBrowser();
			if (browser)
				browser->GetHost()->CloseBrowser(true);
			m_App = nullptr;
			m_RenderHandler = nullptr;
			m_Handler = nullptr;
			PurgeDOMTasks();
			if (browser)
			{
				while (!browser->HasOneRef())
					Sleep(0);
				browser = nullptr;
			}
			CefClearSchemeHandlerFactories();
			CefShutdown();
			try
			{
				SetState(RendererState_Disabled);
			}
			catch (...)
			{
				return false;
			}
			return true;
		}

		Web::Browser::RendererState WebRenderer::GetState() // 0x10CBE240
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetState@WebRenderer@Browser@Web@@QAE?AW4RendererState@23@XZ");
			// Web::Browser::WebRenderer *const this;

			return m_State;
		}

		bool WebRenderer::SetState(Web::Browser::RendererState p_State) // 0x10CC3730
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetState@WebRenderer@Browser@Web@@QAE_NW4RendererState@23@@Z");
			// Web::Browser::RendererState p_State;

			if (m_State == p_State)
			{
				return false;
			}
			if (m_State >= Web::Browser::RendererState_Count || m_State < Web::Browser::RendererState_Disabled)
			{
				return false;
			}
			m_State = p_State;
			return true;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		scoped_refptr<Web::Browser::WebRendererHandler> WebRenderer::GetClientHandler() const // 0x10CBDE10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetClientHandler@WebRenderer@Browser@Web@@QBE?AV?$scoped_refptr@VWebRendererHandler@Browser@Web@@@@XZ");
			// Web::Browser::WebRenderer const *const this;

			return m_Handler;
		}

	}
}


namespace Web
{
	namespace Browser
	{
		scoped_refptr<Web::Browser::WebRendererRenderHandler> WebRenderer::GetRenderHandler() const // 0x10CBE0C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetRenderHandler@WebRenderer@Browser@Web@@QBE?AV?$scoped_refptr@VWebRendererRenderHandler@Browser@Web@@@@XZ");
			// Web::Browser::WebRenderer const *const this;

			return m_RenderHandler;
		}

		void WebRenderer::InitPakFileSystem() // 0x10CC08F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitPakFileSystem@WebRenderer@Browser@Web@@AAEXXZ");
			// Web::Browser::WebRenderer *const this;

			RegisterScheme("pak", "mods");
		}

		void WebRenderer::PurgeDOMTasks() // 0x10CC1850
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PurgeDOMTasks@WebRenderer@Browser@Web@@AAEXXZ");
			// static ...; // 0x10CC18E0
			// static ...; // 0x10CC18D4
			// static ...; // 0x10CC18CC
			// Web::Browser::WebRenderer *const this;
			// std::scoped_lock<std::mutex> lock;

			std::scoped_lock<std::mutex> lock(m_mutex);

			while (!m_DomTasks.empty())
			{
				m_DomTasks.pop();
			}
		}

		void WebRenderer::EnqueueDOMTask(std::function<void __cdecl(void)> &&task) // 0x10CBD670
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?EnqueueDOMTask@WebRenderer@Browser@Web@@QAEX$$QAV?$function@$$A6AXXZ@std@@@Z");
			// static ...; // 0x10CBD734
			// static ...; // 0x10CBD72C
			// Web::Browser::WebRenderer *const this;
			// std::function<void __cdecl(void)> &task;
			// std::scoped_lock<std::mutex> lock;

			std::scoped_lock<std::mutex> lock(m_mutex);
			m_DomTasks.push(std::move(task));
		}

		void WebRenderer::ExecuteDOMTasks() // 0x10CBD780
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteDOMTasks@WebRenderer@Browser@Web@@AAEXXZ");
			// static ...; // 0x10CBD8E6
			// static ...; // 0x10CBD8E0
			// static ...; // 0x10CBD8C8
			// static ...; // 0x10CBD8C0
			// Web::Browser::WebRenderer *const this;
			// std::unique_lock<std::mutex> lock;
			// std::queue<std::function<void __cdecl(void)> > tasks;

			std::unique_lock<std::mutex> lock(m_mutex);
			std::queue<std::function<void __cdecl(void)> > tasks(std::move(m_DomTasks));
			m_DomTasks = {};
			lock.unlock();

			while (!tasks.empty())
			{
				std::move(tasks.front())();
				tasks.pop();
			}
		}

		void WebRenderer::OnFrameLoadStart(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame) // 0x10CC12A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnFrameLoadStart@WebRenderer@Browser@Web@@QAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@@Z");
			// scoped_refptr<CefFrame> frame;
			// function call : bool ()

			if (frame->IsMain())
				m_MainFrameLoaded.store(false);
		}

		void WebRenderer::OnFrameLoadEnd(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame) // 0x10CC1190
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnFrameLoadEnd@WebRenderer@Browser@Web@@QAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@@Z");
			// scoped_refptr<CefFrame> frame;
			// function call : bool ()

			if (frame->IsMain())
			{
				m_MainFrameLoaded.store(true);
				ExecuteDOMTasks();
			}
		}
	}
}

/* ---------- private code */
