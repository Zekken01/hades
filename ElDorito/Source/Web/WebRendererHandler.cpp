/* ---------- headers */

#include "Web/WebRendererHandler.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/Rectangle.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/WebRendererApp.hpp"
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
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range_core.hpp>
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
#include <wrapper/cef_message_router.h>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/range/detail/implementation_help.hpp>
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
#include <locale>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
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
#include <unordered_map>
#include <utility>
#include <vector>

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
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

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

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			typedef std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::basic_string<char,std::char_traits<char>,std::allocator<char> > *)> WebRendererQuery;
		}
	}
}

typedef double __std_tzdb_epoch_milli;

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		extern WebRendererHandler* _sub_10CC9520(Web::Browser::WebRendererHandler *const, scoped_refptr<Web::Browser::WebRendererRenderHandler>);
		WebRendererHandler::WebRendererHandler(scoped_refptr<Web::Browser::WebRendererRenderHandler> renderHandler) // 0x10CC9520
		{
			mangled_x86(MANGLED_TODO, "??0WebRendererHandler@Browser@Web@@QAE@V?$scoped_refptr@VWebRendererRenderHandler@Browser@Web@@@@@Z");
			// static ...; // 0x10CC97B0
			// static ...; // 0x10CC97A8
			// Web::Browser::WebRendererHandler *const this;
			// scoped_refptr<Web::Browser::WebRendererRenderHandler> renderHandler;
			// CefMessageRouterConfig routerConfig;
			todo("implement");
			_sub_10CC9520(this, renderHandler);
		}

		_extern void _sub_10CCBE20(CefLifeSpanHandler * const, scoped_refptr<CefBrowser>);
		void WebRendererHandler::OnAfterCreated(scoped_refptr<CefBrowser> browser) // 0x10CCBE20
		{
			mangled_x86(MANGLED_TODO, "?OnAfterCreated@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 8);
			// scoped_refptr<CefBrowser> browser;
			// function call : bool (CefMessageRouterBrowserSide::Handler *, bool)
			todo("implement");
			_sub_10CCBE20((CefLifeSpanHandler *)this, browser);
		}

		_extern void _sub_10CCD280(CefLifeSpanHandler * const, scoped_refptr<CefBrowser>);
		void WebRendererHandler::OnBeforeClose(scoped_refptr<CefBrowser> browser) // 0x10CCD280
		{
			mangled_x86(MANGLED_TODO, "?OnBeforeClose@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 8);
			// scoped_refptr<CefBrowser> browser;
			// function call : void (scoped_refptr<CefBrowser>)
			todo("implement");
			_sub_10CCD280((CefLifeSpanHandler *)this, browser);
		}
	}
}

extern scoped_refptr<CefBrowser> _sub_10CCB0B0(Web::Browser::WebRendererHandler *const);
namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefBrowser> WebRendererHandler::GetBrowser() // 0x10CCB0B0
		{
			mangled_x86(MANGLED_TODO, "?GetBrowser@WebRendererHandler@Browser@Web@@QAE?AV?$scoped_refptr@VCefBrowser@@@@XZ");
			// Web::Browser::WebRendererHandler *const this;
			todo("implement");
			scoped_refptr<CefBrowser> __result = _sub_10CCB0B0(this);
			return __result;
		}

		_extern void _sub_10CCE1A0(CefRequestHandler * const, scoped_refptr<CefBrowser>, cef_termination_status_t);
		void WebRendererHandler::OnRenderProcessTerminated(scoped_refptr<CefBrowser> browser, cef_termination_status_t status) // 0x10CCE1A0
		{
			mangled_x86(MANGLED_TODO, "?OnRenderProcessTerminated@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_termination_status_t@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 16);
			// cef_termination_status_t status;
			// function call : void (scoped_refptr<CefBrowser>)
			todo("implement");
			_sub_10CCE1A0((CefRequestHandler *)this, browser, status);
		}

		_extern bool _sub_10CCD0E0(CefRequestHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefRequest>, bool, bool);
		bool WebRendererHandler::OnBeforeBrowse(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefRequest> request, bool userGesture, bool isRedirect) // 0x10CCD0E0
		{
			mangled_x86(MANGLED_TODO, "?OnBeforeBrowse@WebRendererHandler@Browser@Web@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@V?$scoped_refptr@VCefRequest@@@@_N3@Z");
			// __shifted(Web::Browser::WebRendererHandler, 16);
			// bool isRedirect;
			// function call : void (scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>)
			todo("implement");
			bool __result = _sub_10CCD0E0((CefRequestHandler *)this, browser, frame, request, userGesture, isRedirect);
			return __result;
		}

		_extern bool _sub_10CCDF70(Web::Browser::WebRendererHandler *const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, cef_process_id_t, scoped_refptr<CefProcessMessage>);
		bool WebRendererHandler::OnProcessMessageReceived(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, cef_process_id_t sourceProcess, scoped_refptr<CefProcessMessage> message) // 0x10CCDF70
		{
			mangled_x86(MANGLED_TODO, "?OnProcessMessageReceived@WebRendererHandler@Browser@Web@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@W4cef_process_id_t@@V?$scoped_refptr@VCefProcessMessage@@@@@Z");
			// scoped_refptr<CefProcessMessage> message;
			// function call : bool (scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, cef_process_id_t, scoped_refptr<CefProcessMessage>)
			todo("implement");
			bool __result = _sub_10CCDF70(this, browser, frame, sourceProcess, message);
			return __result;
		}

		_extern void _sub_10CCD440(CefContextMenuHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, scoped_refptr<CefContextMenuParams>, scoped_refptr<CefMenuModel>);
		void WebRendererHandler::OnBeforeContextMenu(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefContextMenuParams> params, scoped_refptr<CefMenuModel> model) // 0x10CCD440
		{
			mangled_x86(MANGLED_TODO, "?OnBeforeContextMenu@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@V?$scoped_refptr@VCefContextMenuParams@@@@V?$scoped_refptr@VCefMenuModel@@@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 24);
			// scoped_refptr<CefMenuModel> model;
			// function call : bool ()
			todo("implement");
			_sub_10CCD440((CefContextMenuHandler *)this, browser, frame, params, model);
		}

		_extern bool _sub_10CCD5B0(CefLifeSpanHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, CefStringBase<CefStringTraitsUTF16> const &, CefStringBase<CefStringTraitsUTF16> const &, cef_window_open_disposition_t, bool, CefStructBase<CefPopupFeaturesTraits> const &, CefWindowInfo &, scoped_refptr<CefClient> &, CefStructBase<CefBrowserSettingsTraits> &, scoped_refptr<CefDictionaryValue> &, bool *);
		bool WebRendererHandler::OnBeforePopup(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, CefStringBase<CefStringTraitsUTF16> const &target_url, CefStringBase<CefStringTraitsUTF16> const &target_frame_name, cef_window_open_disposition_t target_disposition, bool user_gesture, CefStructBase<CefPopupFeaturesTraits> const &popupFeatures, CefWindowInfo &windowInfo, scoped_refptr<CefClient> &client, CefStructBase<CefBrowserSettingsTraits> &settings, scoped_refptr<CefDictionaryValue> &extra_info, bool *no_javascript_access) // 0x10CCD5B0
		{
			mangled_x86(MANGLED_TODO, "?OnBeforePopup@WebRendererHandler@Browser@Web@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@ABV?$CefStringBase@UCefStringTraitsUTF16@@@@2W4cef_window_open_disposition_t@@_NABV?$CefStructBase@UCefPopupFeaturesTraits@@@@AAVCefWindowInfo@@AAV?$scoped_refptr@VCefClient@@@@AAV?$CefStructBase@UCefBrowserSettingsTraits@@@@AAV?$scoped_refptr@VCefDictionaryValue@@@@PA_N@Z");
			// __shifted(Web::Browser::WebRendererHandler, 8);
			// scoped_refptr<CefClient> &client;
			// CefStructBase<CefBrowserSettingsTraits> &settings;
			// scoped_refptr<CefDictionaryValue> &extra_info;
			// bool *no_javascript_access;
			// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > s_UrlStr;
			// function call : HINSTANCE__ *(HWND__ *, wchar_t const *, wchar_t const *, wchar_t const *, wchar_t const *, __int32)
			todo("implement");
			bool __result = _sub_10CCD5B0((CefLifeSpanHandler *)this, browser, frame, target_url, target_frame_name, target_disposition, user_gesture, popupFeatures, windowInfo, client, settings, extra_info, no_javascript_access);
			return __result;
		}

		_extern void _sub_10CCDAD0(CefLoadHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, __int32);
		void WebRendererHandler::OnLoadEnd(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, __int32 httpStatusCode) // 0x10CCDAD0
		{
			mangled_x86(MANGLED_TODO, "?OnLoadEnd@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@H@Z");
			// __shifted(Web::Browser::WebRendererHandler, 32);
			// __int32 httpStatusCode;
			todo("implement");
			_sub_10CCDAD0((CefLoadHandler *)this, browser, frame, httpStatusCode);
		}

		_extern void _sub_10CCDCE0(CefLoadHandler * const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, cef_transition_type_t);
		void WebRendererHandler::OnLoadStart(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, cef_transition_type_t transition_type) // 0x10CCDCE0
		{
			mangled_x86(MANGLED_TODO, "?OnLoadStart@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@W4cef_transition_type_t@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 32);
			// cef_transition_type_t transition_type;
			todo("implement");
			_sub_10CCDCE0((CefLoadHandler *)this, browser, frame, transition_type);
		}
	}
}

/* ---------- private code */
