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
#include "Web/WebRendererHandler.hpp"
#include "Web/WebRendererRenderHandler.hpp"
#include "Web/WebRendererSchemeHandlerFactory.hpp"
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
		extern WebRenderer* _sub_10CBA660(Web::Browser::WebRenderer *const);
		WebRenderer::WebRenderer() // 0x10CBA660
		{
			mangled_x86(MANGLED_TODO, "??0WebRenderer@Browser@Web@@QAE@XZ");
			// Web::Browser::WebRenderer *const this;
			// function call : __int32 (wchar_t const *)
			// function call : HINSTANCE__ *(wchar_t const *)
			todo("implement");
			_sub_10CBA660(this);
		}

		_inline WebRendererApp::WebRendererApp() // 0x10CBA990
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WebRendererApp@Browser@Web@@QAE@XZ");
			// Web::Browser::WebRendererApp *const this;

			compiler_generated();
		}
	}
}

extern std::shared_ptr<Web::Browser::WebRenderer> _sub_10CBDF10();
namespace Web
{
	namespace Browser
	{
		std::shared_ptr<Web::Browser::WebRenderer> WebRenderer::GetInstance() // 0x10CBDF10
		{
			mangled_x86(MANGLED_TODO, "?GetInstance@WebRenderer@Browser@Web@@SA?AV?$shared_ptr@VWebRenderer@Browser@Web@@@std@@XZ");
			// procedure flags: nofpo
			// static std::shared_ptr<Web::Browser::WebRenderer> instance; // 0x1247EE1C
			// static __int32 $TSS0; // 0x1247EE24
			todo("implement");
			std::shared_ptr<Web::Browser::WebRenderer> __result = _sub_10CBDF10();
			return __result;
		}

		_inline WebEmblemSchemeHandlerFactory::~WebEmblemSchemeHandlerFactory() // 0x10CBB8A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1WebEmblemSchemeHandlerFactory@Browser@Web@@UAE@XZ");
			// __shifted(Web::Browser::WebEmblemSchemeHandlerFactory, 12);
			// Web::Browser::WebEmblemSchemeHandlerFactory *const this;

			compiler_generated();
		}

		_inline WebRenderer::~WebRenderer() // 0x10CBB8F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1WebRenderer@Browser@Web@@QAE@XZ");
			// Web::Browser::WebRenderer *const this;

			compiler_generated();
		}
	}
}

extern std::string _sub_10CBE270(Web::Browser::WebRenderer *const);
namespace Web
{
	namespace Browser
	{
		std::string WebRenderer::GetUIDirectory() // 0x10CBE270
		{
			mangled_x86(MANGLED_TODO, "?GetUIDirectory@WebRenderer@Browser@Web@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// Web::Browser::WebRenderer *const this;
			todo("implement");
			std::string __result = _sub_10CBE270(this);
			return __result;
		}

		_extern bool _sub_10CC0D90(Web::Browser::WebRenderer const *const);
		bool WebRenderer::IsAccelerated() const // 0x10CC0D90
		{
			mangled_x86(MANGLED_TODO, "?IsAccelerated@WebRenderer@Browser@Web@@QBE_NXZ");
			// Web::Browser::WebRenderer const *const this;
			todo("implement");
			bool __result = _sub_10CC0D90((Web::Browser::WebRenderer const *)this);
			return __result;
		}

		_extern bool _sub_10CBE930(Web::Browser::WebRenderer *const, std::string const &, bool);
		bool WebRenderer::Init(std::string const &url, bool debugEnable) // 0x10CBE930
		{
			mangled_x86(MANGLED_TODO, "?Init@WebRenderer@Browser@Web@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
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
			{
				// tagRECT rc;
			}
			// function call : HINSTANCE__ *(char const *)
			// function call : void *()
			// function call : __int32 (void *, unsigned __int32)
			// function call : void (unsigned __int32)
			// function call : __int32 (HWND__ *, tagRECT *)
			todo("implement");
			bool __result = _sub_10CBE930(this, url, debugEnable);
			return __result;
		}

		_extern bool _sub_10CC09F0(Web::Browser::WebRenderer *const, IDirect3DDevice9 *);
		bool WebRenderer::InitRenderer(IDirect3DDevice9 *device) // 0x10CC09F0
		{
			mangled_x86(MANGLED_TODO, "?InitRenderer@WebRenderer@Browser@Web@@QAE_NPAUIDirect3DDevice9@@@Z");
			// static ...; // 0x10CC0C4C
			// static ...; // 0x10CC0C44
			// Web::Browser::WebRenderer *const this;
			// IDirect3DDevice9 *device;
			// _D3DDEVICE_CREATION_PARAMETERS d3dpp;
			// HRESULT hr;
			// function call : HRESULT (_D3DDEVICE_CREATION_PARAMETERS *)
			todo("implement");
			bool __result = _sub_10CC09F0(this, device);
			return __result;
		}

		_extern bool _sub_10CC2510(Web::Browser::WebRenderer *const, IDirect3DDevice9 *);
		bool WebRenderer::Render(IDirect3DDevice9 *device) // 0x10CC2510
		{
			mangled_x86(MANGLED_TODO, "?Render@WebRenderer@Browser@Web@@QAE_NPAUIDirect3DDevice9@@@Z");
			// IDirect3DDevice9 *device;
			// Web::Browser::RendererState state;
			todo("implement");
			bool __result = _sub_10CC2510(this, device);
			return __result;
		}

		_extern bool _sub_10CC3EB0(Web::Browser::WebRenderer *const);
		bool WebRenderer::Update() // 0x10CC3EB0
		{
			mangled_x86(MANGLED_TODO, "?Update@WebRenderer@Browser@Web@@QAE_NXZ");
			// static ...; // 0x10CC3FA4
			// static ...; // 0x10CC3F98
			// static ...; // 0x10CC3F90
			// Web::Browser::WebRenderer *const this;
			// std::shared_ptr<Web::Browser::Bridge::WebRendererQueryHandler> queryHandler;
			todo("implement");
			bool __result = _sub_10CC3EB0(this);
			return __result;
		}

		_extern bool _sub_10CC0D00(Web::Browser::WebRenderer *const);
		bool WebRenderer::Initialized() // 0x10CC0D00
		{
			mangled_x86(MANGLED_TODO, "?Initialized@WebRenderer@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRenderer *const this;
			// Web::Browser::RendererState state;
			todo("implement");
			bool __result = _sub_10CC0D00(this);
			return __result;
		}

		_extern bool _sub_10CC0E10(Web::Browser::WebRenderer *const);
		bool WebRenderer::IsRendering() // 0x10CC0E10
		{
			mangled_x86(MANGLED_TODO, "?IsRendering@WebRenderer@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRenderer *const this;
			todo("implement");
			bool __result = _sub_10CC0E10(this);
			return __result;
		}

		_extern bool _sub_10CC3790(Web::Browser::WebRenderer *const, bool, bool);
		bool WebRenderer::ShowRenderer(bool show, bool overlay) // 0x10CC3790
		{
			mangled_x86(MANGLED_TODO, "?ShowRenderer@WebRenderer@Browser@Web@@QAE_N_N0@Z");
			// static ...; // 0x10CC3A70
			// static ...; // 0x10CC3A68
			// Web::Browser::WebRenderer *const this;
			// bool show;
			// bool overlay;
			// Web::Browser::RendererState state;
			{
				// scoped_refptr<CefBrowser> browser;
			}
			{
			}
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (bool)
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (bool)
			todo("implement");
			bool __result = _sub_10CC3790(this, show, overlay);
			return __result;
		}

		_extern bool _sub_10CC25C0(Web::Browser::WebRenderer *const, unsigned __int32, unsigned __int32);
		bool WebRenderer::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CC25C0
		{
			mangled_x86(MANGLED_TODO, "?Resize@WebRenderer@Browser@Web@@QAE_NII@Z");
			// static ...; // 0x10CC2A08
			// Web::Browser::WebRenderer *const this;
			// unsigned __int32 width;
			// unsigned __int32 height;
			// CefBrowser *browser;
			// bool res;
			{
				// tagRECT rc;
			}
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
			todo("implement");
			bool __result = _sub_10CC25C0(this, width, height);
			return __result;
		}

		_extern bool _sub_10CC2FE0(Web::Browser::WebRenderer *const, CefStructBase<CefMouseEventTraits> const &, bool);
		bool WebRenderer::SendMouseMoveEvent(CefStructBase<CefMouseEventTraits> const &p_Event, bool p_MouseLeave) // 0x10CC2FE0
		{
			mangled_x86(MANGLED_TODO, "?SendMouseMoveEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefMouseEventTraits@@@@_N@Z");
			// bool p_MouseLeave;
			// CefBrowser *browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefMouseEventTraits> const &, bool)
			todo("implement");
			bool __result = _sub_10CC2FE0(this, p_Event, p_MouseLeave);
			return __result;
		}

		_extern bool _sub_10CC2D70(Web::Browser::WebRenderer *const, CefStructBase<CefMouseEventTraits> const &, cef_mouse_button_type_t, bool, __int32);
		bool WebRenderer::SendMouseClickEvent(CefStructBase<CefMouseEventTraits> const &event, cef_mouse_button_type_t button, bool mouseUp, __int32 clickCount) // 0x10CC2D70
		{
			mangled_x86(MANGLED_TODO, "?SendMouseClickEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefMouseEventTraits@@@@W4cef_mouse_button_type_t@@_NH@Z");
			// CefStructBase<CefMouseEventTraits> const &event;
			// cef_mouse_button_type_t button;
			// bool mouseUp;
			// __int32 clickCount;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefMouseEventTraits> const &, cef_mouse_button_type_t, bool, __int32)
			todo("implement");
			bool __result = _sub_10CC2D70(this, event, button, mouseUp, clickCount);
			return __result;
		}

		_extern bool _sub_10CC31D0(Web::Browser::WebRenderer *const, CefStructBase<CefMouseEventTraits> const &, __int32, __int32);
		bool WebRenderer::SendMouseWheelEvent(CefStructBase<CefMouseEventTraits> const &event, __int32 deltaX, __int32 deltaY) // 0x10CC31D0
		{
			mangled_x86(MANGLED_TODO, "?SendMouseWheelEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefMouseEventTraits@@@@HH@Z");
			// Web::Browser::WebRenderer *const this;
			// CefStructBase<CefMouseEventTraits> const &event;
			// __int32 deltaX;
			// __int32 deltaY;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefMouseEventTraits> const &, __int32, __int32)
			todo("implement");
			bool __result = _sub_10CC31D0(this, event, deltaX, deltaY);
			return __result;
		}

		_extern bool _sub_10CC2B40(Web::Browser::WebRenderer *const, CefStructBase<CefKeyEventTraits> const &);
		bool WebRenderer::SendKeyEvent(CefStructBase<CefKeyEventTraits> const &p_Event) // 0x10CC2B40
		{
			mangled_x86(MANGLED_TODO, "?SendKeyEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefKeyEventTraits@@@@@Z");
			// static ...; // 0x10CC2CEC
			// static ...; // 0x10CC2CE4
			// Web::Browser::WebRenderer *const this;
			// CefStructBase<CefKeyEventTraits> const &p_Event;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefKeyEventTraits> const &)
			todo("implement");
			bool __result = _sub_10CC2B40(this, p_Event);
			return __result;
		}

		_extern bool _sub_10CC3410(Web::Browser::WebRenderer *const, CefStructBase<CefPlatformEventTraits> const &);
		bool WebRenderer::SendPlatformEvent(CefStructBase<CefPlatformEventTraits> const &event) // 0x10CC3410
		{
			mangled_x86(MANGLED_TODO, "?SendPlatformEvent@WebRenderer@Browser@Web@@QAE_NABV?$CefStructBase@UCefPlatformEventTraits@@@@@Z");
			// static ...; // 0x10CC35BC
			// static ...; // 0x10CC35B4
			// Web::Browser::WebRenderer *const this;
			// CefStructBase<CefPlatformEventTraits> const &event;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (CefStructBase<CefPlatformEventTraits> const &)
			todo("implement");
			bool __result = _sub_10CC3410(this, event);
			return __result;
		}

		_extern bool _sub_10CC1500(Web::Browser::WebRenderer *const, std::string const &);
		bool WebRenderer::OpenUrl(std::string const &p_Url) // 0x10CC1500
		{
			mangled_x86(MANGLED_TODO, "?OpenUrl@WebRenderer@Browser@Web@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10CC16D8
			// static ...; // 0x10CC16D0
			// Web::Browser::WebRenderer *const this;
			// std::string const &p_Url;
			// scoped_refptr<CefBrowser> browser;
			// function call : scoped_refptr<CefFrame> ()
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			todo("implement");
			bool __result = _sub_10CC1500(this, p_Url);
			return __result;
		}

		_extern bool _sub_10CC2330(Web::Browser::WebRenderer *const, bool);
		bool WebRenderer::Reload(bool p_IgnoreCache) // 0x10CC2330
		{
			mangled_x86(MANGLED_TODO, "?Reload@WebRenderer@Browser@Web@@QAE_N_N@Z");
			// static ...; // 0x10CC249C
			// static ...; // 0x10CC2494
			// Web::Browser::WebRenderer *const this;
			// bool p_IgnoreCache;
			// scoped_refptr<CefBrowser> browser;
			// function call : void ()
			// function call : void ()
			todo("implement");
			bool __result = _sub_10CC2330(this, p_IgnoreCache);
			return __result;
		}

		_extern bool _sub_10CC1910(Web::Browser::WebRenderer *const, std::string const &, std::string const &);
		bool WebRenderer::RegisterScheme(std::string const &p_Name, std::string const &p_Directory) // 0x10CC1910
		{
			mangled_x86(MANGLED_TODO, "?RegisterScheme@WebRenderer@Browser@Web@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// std::string const &p_Directory;
			// Web::Browser::WebRendererSchemeHandlerFactory *schemeHandlerFactory;
			todo("implement");
			bool __result = _sub_10CC1910(this, p_Name, p_Directory);
			return __result;
		}

		_extern bool _sub_10CBD950(Web::Browser::WebRenderer *const, std::string, bool);
		bool WebRenderer::ExecuteJavascript(std::string p_Code, bool deferIfNeeded) // 0x10CBD950
		{
			mangled_x86(MANGLED_TODO, "?ExecuteJavascript@WebRenderer@Browser@Web@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
			// static ...; // 0x10CBDC1C
			// Web::Browser::WebRenderer *const this;
			// std::string p_Code;
			// bool deferIfNeeded;
			// scoped_refptr<CefBrowser> browser;
			{
			}
			// function call : scoped_refptr<CefFrame> ()
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &, CefStringBase<CefStringTraitsUTF16> const &, __int32)
			todo("implement");
			bool __result = _sub_10CBD950(this, p_Code, deferIfNeeded);
			return __result;
		}

		_extern bool _sub_10CC17E0(Web::Browser::WebRenderer *const);
		bool WebRenderer::PreReset() // 0x10CC17E0
		{
			mangled_x86(MANGLED_TODO, "?PreReset@WebRenderer@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRenderer *const this;
			todo("implement");
			bool __result = _sub_10CC17E0(this);
			return __result;
		}

		_extern bool _sub_10CC1770(Web::Browser::WebRenderer *const);
		bool WebRenderer::PostReset() // 0x10CC1770
		{
			mangled_x86(MANGLED_TODO, "?PostReset@WebRenderer@Browser@Web@@QAE_NXZ");
			// Web::Browser::WebRenderer *const this;
			todo("implement");
			bool __result = _sub_10CC1770(this);
			return __result;
		}

		_extern bool _sub_10CC3B60(Web::Browser::WebRenderer *const);
		bool WebRenderer::Shutdown() // 0x10CC3B60
		{
			mangled_x86(MANGLED_TODO, "?Shutdown@WebRenderer@Browser@Web@@QAE_NXZ");
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
			todo("implement");
			bool __result = _sub_10CC3B60(this);
			return __result;
		}

		Web::Browser::RendererState WebRenderer::GetState() // 0x10CBE240
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetState@WebRenderer@Browser@Web@@QAE?AW4RendererState@23@XZ");
			// Web::Browser::WebRenderer *const this;

			return m_State;
		}

		_extern bool _sub_10CC3730(Web::Browser::WebRenderer *const, Web::Browser::RendererState);
		bool WebRenderer::SetState(Web::Browser::RendererState p_State) // 0x10CC3730
		{
			mangled_x86(MANGLED_TODO, "?SetState@WebRenderer@Browser@Web@@QAE_NW4RendererState@23@@Z");
			// Web::Browser::RendererState p_State;
			todo("implement");
			bool __result = _sub_10CC3730(this, p_State);
			return __result;
		}
	}
}

extern scoped_refptr<Web::Browser::WebRendererHandler> _sub_10CBDE10(Web::Browser::WebRenderer const *const);
namespace Web
{
	namespace Browser
	{
		scoped_refptr<Web::Browser::WebRendererHandler> WebRenderer::GetClientHandler() const // 0x10CBDE10
		{
			mangled_x86(MANGLED_TODO, "?GetClientHandler@WebRenderer@Browser@Web@@QBE?AV?$scoped_refptr@VWebRendererHandler@Browser@Web@@@@XZ");
			// Web::Browser::WebRenderer const *const this;
			todo("implement");
			scoped_refptr<Web::Browser::WebRendererHandler> __result = _sub_10CBDE10((Web::Browser::WebRenderer const *)this);
			return __result;
		}

		_inline WebEmblemSchemeHandlerFactory::WebEmblemSchemeHandlerFactory() // 0x10CBA540
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WebEmblemSchemeHandlerFactory@Browser@Web@@QAE@XZ");
			// Web::Browser::WebEmblemSchemeHandlerFactory *const this;

			compiler_generated();
		}
	}
}

extern scoped_refptr<Web::Browser::WebRendererRenderHandler> _sub_10CBE0C0(Web::Browser::WebRenderer const *const);
namespace Web
{
	namespace Browser
	{
		scoped_refptr<Web::Browser::WebRendererRenderHandler> WebRenderer::GetRenderHandler() const // 0x10CBE0C0
		{
			mangled_x86(MANGLED_TODO, "?GetRenderHandler@WebRenderer@Browser@Web@@QBE?AV?$scoped_refptr@VWebRendererRenderHandler@Browser@Web@@@@XZ");
			// Web::Browser::WebRenderer const *const this;
			todo("implement");
			scoped_refptr<Web::Browser::WebRendererRenderHandler> __result = _sub_10CBE0C0((Web::Browser::WebRenderer const *)this);
			return __result;
		}

		_extern void _sub_10CC08F0(Web::Browser::WebRenderer *const);
		void WebRenderer::InitPakFileSystem() // 0x10CC08F0
		{
			mangled_x86(MANGLED_TODO, "?InitPakFileSystem@WebRenderer@Browser@Web@@AAEXXZ");
			// Web::Browser::WebRenderer *const this;
			todo("implement");
			_sub_10CC08F0(this);
		}

		_extern void _sub_10CC1850(Web::Browser::WebRenderer *const);
		void WebRenderer::PurgeDOMTasks() // 0x10CC1850
		{
			mangled_x86(MANGLED_TODO, "?PurgeDOMTasks@WebRenderer@Browser@Web@@AAEXXZ");
			// static ...; // 0x10CC18E0
			// static ...; // 0x10CC18D4
			// static ...; // 0x10CC18CC
			// Web::Browser::WebRenderer *const this;
			// std::scoped_lock<std::mutex> lock;
			todo("implement");
			_sub_10CC1850(this);
		}

		_extern void _sub_10CBD670(Web::Browser::WebRenderer *const, std::function<void __cdecl(void)> &);
		void WebRenderer::EnqueueDOMTask(std::function<void __cdecl(void)> &&task) // 0x10CBD670
		{
			mangled_x86(MANGLED_TODO, "?EnqueueDOMTask@WebRenderer@Browser@Web@@QAEX$$QAV?$function@$$A6AXXZ@std@@@Z");
			// static ...; // 0x10CBD734
			// static ...; // 0x10CBD72C
			// Web::Browser::WebRenderer *const this;
			// std::function<void __cdecl(void)> &task;
			// std::scoped_lock<std::mutex> lock;
			todo("implement");
			_sub_10CBD670(this, task);
		}

		_extern void _sub_10CBD780(Web::Browser::WebRenderer *const);
		void WebRenderer::ExecuteDOMTasks() // 0x10CBD780
		{
			mangled_x86(MANGLED_TODO, "?ExecuteDOMTasks@WebRenderer@Browser@Web@@AAEXXZ");
			// static ...; // 0x10CBD8E6
			// static ...; // 0x10CBD8E0
			// static ...; // 0x10CBD8C8
			// static ...; // 0x10CBD8C0
			// Web::Browser::WebRenderer *const this;
			// std::unique_lock<std::mutex> lock;
			// std::queue<std::function<void __cdecl(void)>,std::deque<std::function<void __cdecl(void)>,std::allocator<std::function<void __cdecl(void)> > > > tasks;
			todo("implement");
			_sub_10CBD780(this);
		}

		_extern void _sub_10CC12A0(Web::Browser::WebRenderer *const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>);
		void WebRenderer::OnFrameLoadStart(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame) // 0x10CC12A0
		{
			mangled_x86(MANGLED_TODO, "?OnFrameLoadStart@WebRenderer@Browser@Web@@QAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@@Z");
			// scoped_refptr<CefFrame> frame;
			// function call : bool ()
			todo("implement");
			_sub_10CC12A0(this, browser, frame);
		}

		_extern void _sub_10CC1190(Web::Browser::WebRenderer *const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>);
		void WebRenderer::OnFrameLoadEnd(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame) // 0x10CC1190
		{
			mangled_x86(MANGLED_TODO, "?OnFrameLoadEnd@WebRenderer@Browser@Web@@QAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@@Z");
			// scoped_refptr<CefFrame> frame;
			// function call : bool ()
			todo("implement");
			_sub_10CC1190(this, browser, frame);
		}
	}
}

/* ---------- private code */
