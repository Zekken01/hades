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

#include "Web/WebRenderer.hpp"  // hades: added for 0x10CCDAD0, 0x10CCDCE0  // hades: added for 0x10CCDAD0

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
			typedef std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)> WebRendererQuery;
		}
	}
}

typedef double __std_tzdb_epoch_milli;

/* ---------- prototypes */

#include "Web/Ui/ScreenLayer.hpp"  // hades: added for 0x10CCBE20
namespace Web { namespace Browser { namespace Bridge { namespace ClientFunctions { QueryError OnShow(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnHide(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnScreenState(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnCommand(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnSetVariables(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnPing(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnCaptureInput(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnVersion(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnMapVariantInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnGameVariantInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnCommands(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnSendChat(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnChatBoxOpened(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnSessionInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnScoreboard(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnScoreboardHide(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnStats(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnVoIPSpeakingChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnVoIPConnectedChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnVoIPPlayerSpeakingChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnVoIPPlayerVoipLevelChanged(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnVoIPPlayerVoipJoined(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnIsMapLoading(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnForgeAction(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnForgePalette(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnShowLan(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnPlayerReportInfo(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnSubmitDialogResult(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnGetAssetUrl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); QueryError OnShowScoreboard(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result); } } } }  // hades: added for 0x10CCBE20  // hades: added for 0x10CCBE20

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		WebRendererHandler::WebRendererHandler(scoped_refptr<Web::Browser::WebRendererRenderHandler> renderHandler) : m_Browser(nullptr), m_RenderHandler(renderHandler) /* hades-mem-init:  */ // 0x10CC9520
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WebRendererHandler@Browser@Web@@QAE@V?$scoped_refptr@VWebRendererRenderHandler@Browser@Web@@@@@Z");
			// static ...; // 0x10CC97B0
			// static ...; // 0x10CC97A8
			// Web::Browser::WebRendererHandler *const this;
			// scoped_refptr<Web::Browser::WebRendererRenderHandler> renderHandler;
			// CefMessageRouterConfig routerConfig;

			CefMessageRouterConfig routerConfig;
			routerConfig.js_query_function = "dewQuery";
			routerConfig.js_cancel_function = "dewQueryCancel";
			m_BrowserRouter = CefMessageRouterBrowserSide::Create(routerConfig);
		}

		void WebRendererHandler::OnAfterCreated(scoped_refptr<CefBrowser> browser) // 0x10CCBE20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnAfterCreated@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 8);
			// scoped_refptr<CefBrowser> browser;
			// function call : bool (CefMessageRouterBrowserSide::Handler *, bool)

			m_Browser = browser;
			if (!m_QueryHandler)
			{
				m_QueryHandler = std::make_shared<Bridge::WebRendererQueryHandler>();
				m_QueryHandler->AddMethod("show", Bridge::ClientFunctions::OnShow);
				m_QueryHandler->AddMethod("hide", Bridge::ClientFunctions::OnHide);
				m_QueryHandler->AddMethod("screenState", Bridge::ClientFunctions::OnScreenState);
				m_QueryHandler->AddMethod("command", Bridge::ClientFunctions::OnCommand);
				m_QueryHandler->AddMethod("setVariables", Bridge::ClientFunctions::OnSetVariables);
				m_QueryHandler->AddMethod("ping", Bridge::ClientFunctions::OnPing);
				m_QueryHandler->AddMethod("captureInput", Bridge::ClientFunctions::OnCaptureInput);
				m_QueryHandler->AddMethod("version", Bridge::ClientFunctions::OnVersion);
				m_QueryHandler->AddMethod("mapVariantInfo", Bridge::ClientFunctions::OnMapVariantInfo);
				m_QueryHandler->AddMethod("gameVariantInfo", Bridge::ClientFunctions::OnGameVariantInfo);
				m_QueryHandler->AddMethod("commands", Bridge::ClientFunctions::OnCommands);
				m_QueryHandler->AddMethod("sendChat", Bridge::ClientFunctions::OnSendChat);
				m_QueryHandler->AddMethod("chatBoxOpened", Bridge::ClientFunctions::OnChatBoxOpened);
				m_QueryHandler->AddMethod("sessionInfo", Bridge::ClientFunctions::OnSessionInfo);
				m_QueryHandler->AddMethod("scoreboard", Bridge::ClientFunctions::OnScoreboard);
				m_QueryHandler->AddMethod("scoreboardHide", Bridge::ClientFunctions::OnScoreboardHide);
				m_QueryHandler->AddMethod("stats", Bridge::ClientFunctions::OnStats);
				m_QueryHandler->AddMethod("voipSpeaking", Bridge::ClientFunctions::OnVoIPSpeakingChanged);
				m_QueryHandler->AddMethod("voipConnected", Bridge::ClientFunctions::OnVoIPConnectedChanged);
				m_QueryHandler->AddMethod("playerSpeaking", Bridge::ClientFunctions::OnVoIPPlayerSpeakingChanged);
				m_QueryHandler->AddMethod("playerVoipLevelChanged", Bridge::ClientFunctions::OnVoIPPlayerVoipLevelChanged);
				m_QueryHandler->AddMethod("voipUserJoined", Bridge::ClientFunctions::OnVoIPPlayerVoipJoined);
				m_QueryHandler->AddMethod("isMapLoading", Bridge::ClientFunctions::OnIsMapLoading);
				m_QueryHandler->AddMethod("forgeaction", Bridge::ClientFunctions::OnForgeAction);
				m_QueryHandler->AddMethod("forgePalette", Bridge::ClientFunctions::OnForgePalette);
				m_QueryHandler->AddMethod("showlan", Bridge::ClientFunctions::OnShowLan);
				m_QueryHandler->AddMethod("playerReportInfo", Bridge::ClientFunctions::OnPlayerReportInfo);
				m_QueryHandler->AddMethod("submitDialogResult", Bridge::ClientFunctions::OnSubmitDialogResult);
				m_QueryHandler->AddMethod("getAssetUrl", Bridge::ClientFunctions::OnGetAssetUrl);
				m_QueryHandler->AddMethod("showScoreboard", Bridge::ClientFunctions::OnShowScoreboard);
				m_BrowserRouter->AddHandler(m_QueryHandler.get(), true);
			}
			m_RenderHandler->OnAfterCreated(browser);
			Ui::ScreenLayer::CreateScreens();
		}

		void WebRendererHandler::OnBeforeClose(scoped_refptr<CefBrowser> browser) // 0x10CCD280
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnBeforeClose@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 8);
			// scoped_refptr<CefBrowser> browser;
			// function call : void (scoped_refptr<CefBrowser>)

			if (m_BrowserRouter)
				m_BrowserRouter->OnBeforeClose(browser);
			m_QueryHandler = nullptr;
			m_BrowserRouter = nullptr;
			m_Browser = nullptr;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefBrowser> WebRendererHandler::GetBrowser() // 0x10CCB0B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetBrowser@WebRendererHandler@Browser@Web@@QAE?AV?$scoped_refptr@VCefBrowser@@@@XZ");
			// Web::Browser::WebRendererHandler *const this;

			return m_Browser;
		}

		void WebRendererHandler::OnRenderProcessTerminated(scoped_refptr<CefBrowser> browser, cef_termination_status_t status) // 0x10CCE1A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnRenderProcessTerminated@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_termination_status_t@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 16);
			// cef_termination_status_t status;
			// function call : void (scoped_refptr<CefBrowser>)

			if (m_BrowserRouter)
				m_BrowserRouter->OnRenderProcessTerminated(browser);
		}

		bool WebRendererHandler::OnBeforeBrowse(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefRequest> request, bool userGesture, bool isRedirect) // 0x10CCD0E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnBeforeBrowse@WebRendererHandler@Browser@Web@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@V?$scoped_refptr@VCefRequest@@@@_N3@Z");
			// __shifted(Web::Browser::WebRendererHandler, 16);
			// bool isRedirect;
			// function call : void (scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>)

			if (m_BrowserRouter)
				m_BrowserRouter->OnBeforeBrowse(browser, frame);
			return false;
		}

		bool WebRendererHandler::OnProcessMessageReceived(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, cef_process_id_t sourceProcess, scoped_refptr<CefProcessMessage> message) // 0x10CCDF70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnProcessMessageReceived@WebRendererHandler@Browser@Web@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@W4cef_process_id_t@@V?$scoped_refptr@VCefProcessMessage@@@@@Z");
			// scoped_refptr<CefProcessMessage> message;
			// function call : bool (scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, cef_process_id_t, scoped_refptr<CefProcessMessage>)

			return m_BrowserRouter->OnProcessMessageReceived(browser, frame, sourceProcess, message);
		}

		void WebRendererHandler::OnBeforeContextMenu(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, scoped_refptr<CefContextMenuParams> params, scoped_refptr<CefMenuModel> model) // 0x10CCD440
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnBeforeContextMenu@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@V?$scoped_refptr@VCefContextMenuParams@@@@V?$scoped_refptr@VCefMenuModel@@@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 24);
			// scoped_refptr<CefMenuModel> model;
			// function call : bool ()

			model->Clear();
		}

		bool WebRendererHandler::OnBeforePopup(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, CefStringBase<CefStringTraitsUTF16> const &target_url, CefStringBase<CefStringTraitsUTF16> const &target_frame_name, cef_window_open_disposition_t target_disposition, bool user_gesture, CefStructBase<CefPopupFeaturesTraits> const &popupFeatures, CefWindowInfo &windowInfo, scoped_refptr<CefClient> &client, CefStructBase<CefBrowserSettingsTraits> &settings, scoped_refptr<CefDictionaryValue> &extra_info, bool *no_javascript_access) // 0x10CCD5B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnBeforePopup@WebRendererHandler@Browser@Web@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@ABV?$CefStringBase@UCefStringTraitsUTF16@@@@2W4cef_window_open_disposition_t@@_NABV?$CefStructBase@UCefPopupFeaturesTraits@@@@AAVCefWindowInfo@@AAV?$scoped_refptr@VCefClient@@@@AAV?$CefStructBase@UCefBrowserSettingsTraits@@@@AAV?$scoped_refptr@VCefDictionaryValue@@@@PA_N@Z");
			// __shifted(Web::Browser::WebRendererHandler, 8);
			// scoped_refptr<CefClient> &client;
			// CefStructBase<CefBrowserSettingsTraits> &settings;
			// scoped_refptr<CefDictionaryValue> &extra_info;
			// bool *no_javascript_access;
			// std::wstring s_UrlStr;
			// function call : HINSTANCE__ *(HWND__ *, wchar_t const *, wchar_t const *, wchar_t const *, wchar_t const *, __int32)

			std::wstring s_UrlStr = target_url.ToWString();
			if (!boost::istarts_with(s_UrlStr, L"http://") && !boost::istarts_with(s_UrlStr, L"https://"))
				s_UrlStr = L"http://" + s_UrlStr;
			ShellExecuteW(nullptr, L"open", s_UrlStr.c_str(), L"", nullptr, SW_SHOWNORMAL);
			return true;
		}

		void WebRendererHandler::OnLoadEnd(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, __int32 httpStatusCode) // 0x10CCDAD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnLoadEnd@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@H@Z");
			// __shifted(Web::Browser::WebRendererHandler, 32);
			// __int32 httpStatusCode;

			WebRenderer::GetInstance()->OnFrameLoadEnd(browser, frame);
		}

		void WebRendererHandler::OnLoadStart(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, cef_transition_type_t transition_type) // 0x10CCDCE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnLoadStart@WebRendererHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@W4cef_transition_type_t@@@Z");
			// __shifted(Web::Browser::WebRendererHandler, 32);
			// cef_transition_type_t transition_type;

			WebRenderer::GetInstance()->OnFrameLoadStart(browser, frame);
		}
	}
}

/* ---------- private code */
