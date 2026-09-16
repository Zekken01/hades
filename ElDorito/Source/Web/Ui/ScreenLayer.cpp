/* ---------- headers */

#include "Web/Ui/ScreenLayer.hpp"
#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/input/input.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleInput.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Patch.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Input.hpp"
#include "Patches/Ui.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/EventSink.hpp"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Rectangle.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/WebMods.hpp"
#include "Web/WebRenderer.hpp"
#include "Web/WebRendererApp.hpp"
#include "Web/WebRendererHandler.hpp"
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
#include <wrapper/cef_message_router.h>

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
#include <map>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Blam
{
	namespace Input
	{
		struct ActionState;
	}
}
namespace Modules
{
	class ModuleInput;
	class ModuleSettings;
	struct Command;
}
namespace Patches
{
	namespace Input
	{
		class InputContext;
	}
}
namespace Web
{
	namespace Browser
	{
		class WebRenderer;
		class WebRendererHandler;
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
namespace Web
{
	namespace Ui
	{
		class WebScreen;
	}
}
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams;
		}
	}
}
namespace hades_file_local
{
	class WebOverlayInputContext;
}
using namespace hades_file_local;

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

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
	namespace Input {}
	using namespace Patches::Input;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class WebOverlayInputContext :
		public Patches::Input::InputContext
	{
	public:
		virtual void Activated();
		virtual void Deactivated();
		virtual bool GameInputTick();
		virtual bool UiInputTick();
		virtual void InputBlock();
		virtual void InputUnblock();
		WebOverlayInputContext(WebOverlayInputContext &); /* compiler_generated() */
		WebOverlayInputContext(WebOverlayInputContext const &); /* compiler_generated() */
		WebOverlayInputContext(); /* compiler_generated() */
		virtual ~WebOverlayInputContext() = default; /* compiler_generated() */
		WebOverlayInputContext &operator=(WebOverlayInputContext &); /* compiler_generated() */
		WebOverlayInputContext &operator=(WebOverlayInputContext const &); /* compiler_generated() */
	};
	static_assert(sizeof(WebOverlayInputContext) == 8, "Invalid WebOverlayInputContext size");
}
using namespace hades_file_local;
//struct OnUIInputUpdated::__l2::ControllerAxes
//{
//	short LeftX; // 0x0
//	short LeftY; // 0x2
//	short RightX; // 0x4
//	short RightY; // 0x6
//};
//static_assert(sizeof(OnUIInputUpdated::__l2::ControllerAxes) == 8, "Invalid OnUIInputUpdated::__l2::ControllerAxes size");

namespace Modules
{
	typedef std::function<void __cdecl(Modules::Command const *)> VariableUpdateCallback;
}

namespace Patches
{
	namespace Ui
	{
		typedef std::function<void __cdecl(HWND__ *)> CreateWindowCallback;
	}
}

namespace Patches
{
	namespace Core
	{
		typedef std::function<void __cdecl(void)> ShutdownCallback;
	}
}

/* ---------- prototypes */

namespace Patches { namespace Core { void OnShutdown(std::function<void()> callback); } }  // hades: added for 0X10C93FE0
namespace Patches { namespace Input { void RegisterDefaultInputHandler(void (*func)()); } }  // hades: added for 0X10C93FE0

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			extern void Init();
			extern void Tick();
			extern void Resize();
			extern void Show(bool show);
			extern void Show(Web::Ui::ScreenLayer::ScreenId screenId, std::string const &data);
			extern void Show(std::string const &screenId, std::string const &data);
			extern void Hide(Web::Ui::ScreenLayer::ScreenId screenId);
			extern void Hide(std::string const &screenId);
			extern void Notify(std::string const &event, std::string const &data, bool broadcast);
			extern void NotifyScreen(Web::Ui::ScreenLayer::ScreenId screenId, std::string const &event, std::string const &data);
			extern void NotifyScreen(std::string const &screenId, std::string const &event, std::string const &data);
			extern void NotifyScreenStateChanged(std::string const &screenId, Web::Ui::ScreenLayer::EScreenState state);
			extern void CaptureInput(bool capture, bool pointerCapture);
			extern void ShowAlert(std::string const &title, std::string body, Web::Ui::ScreenLayer::AlertIcon icon, float height);
			extern void RegisterScreen(std::string const &screenId, std::shared_ptr<Web::Ui::WebScreen> const &screen);
			extern void RegisterScreen(Web::Ui::ScreenLayer::ScreenId id, std::shared_ptr<Web::Ui::WebScreen> const &screen);
			extern std::shared_ptr<Web::Ui::WebScreen> GetScreen(std::string const &stringId);
			extern void SetDialogHandler(std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> const &handler);
			extern void ShowDialog(Web::Ui::ScreenLayer::SDialogShowParams const &params);
			extern void ShowDialog(std::string const &templateName, std::function<void __cdecl(std::string const &)> callback);
			extern void CreateScreens();
		}
	}
}

void QuickBlockInput();
void QuickUnblockInput();
void WindowCreated(HWND__ *window);
void ShutdownRenderer();
CefStructBase<CefPlatformEventTraits> MakeCefPlatformEvent(tagMSG *msg);
void HandleMouseMessage(tagMSG *msg);
void HandleKeyMessage(tagMSG *msg);
void GetMsgHookImpl(__int32 code, unsigned __int32 wParam, long lParam);
long __stdcall GetMsgHook(__int32 code, unsigned __int32 wParam, long lParam);
void OnGameInputUpdated();
void OnUIInputUpdated();
void OnVariableUpdate(Modules::Command const *command);
void NotifyVariablesUpdated();

/* ---------- globals */

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			extern CEventSink<> BeforeReload; // 0x1247ECDC
			extern std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> dialogHandler; // 0x1247ECF0
		}
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	extern "C" HHOOK__ *MessageHook; // 0x1247ED28
	extern bool InputCaptured; // 0x1247ED2C
	extern "C" bool PointerCaptured; // 0x1247ED2D
	extern unsigned __int32 lastVariableUpdateTicks; // 0x1247ED30
	extern std::vector<Modules::Command const *> lastVariableUpdates; // 0x1247ED18
	extern std::map<std::string,std::shared_ptr<Web::Ui::WebScreen> > registeredScreens; // 0x1247ECD0
	extern __int32 g_last_mouse_x; // 0x1247ED34
	extern __int32 g_last_mouse_y; // 0x1247ED38
	extern "C" char const *ScreenIdString[16]; // 0x11355298
}
using namespace hades_file_local;
/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			void Init() // 0x10C93FE0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@ScreenLayer@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				Patches::Ui::OnCreateWindow(WindowCreated);
				Patches::Core::OnShutdown(ShutdownRenderer);
				Patches::Input::RegisterDefaultInputHandler(OnGameInputUpdated);
				Modules::CommandMap::Instance().OnVariableUpdate(OnVariableUpdate);
			}

			_extern void _sub_10C96F00();
			void Tick() // 0x10C96F00
			{
				mangled_x86(MANGLED_TODO, "?Tick@ScreenLayer@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static ...; // 0x10C9705D
				// static ...; // 0x10C97054
				// static ...; // 0x10C9703C
				// static ...; // 0x10C97034
				{
					// std::map<std::string,std::shared_ptr<Web::Ui::WebScreen> > &<range>$L0;
					// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::shared_ptr<Web::Ui::WebScreen> > > > > <begin>$L0;
					// std::_Default_sentinel <end>$L0;
					{
						// std::pair<std::string const ,std::shared_ptr<Web::Ui::WebScreen> > &screen;
					}
				}
				// function call : void ()
				todo("implement");
				_sub_10C96F00();
			}

			void Resize() // 0x10C96130
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Resize@ScreenLayer@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// __int32 *windowResolution;

				auto *windowResolution = reinterpret_cast<int *>(0x19106E4);
				WebRenderer::GetInstance()->Resize(windowResolution[0], windowResolution[1]);
			}

			void Show(bool show) // 0x10C966B0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Show@ScreenLayer@Ui@Web@@YAX_N@Z");
				// static ...; // 0x10C967B0
				// static ...; // 0x10C967A4
				// static ...; // 0x10C9679C
				// bool show;
				// std::shared_ptr<Web::Browser::WebRenderer> webRenderer;

				if (ElDorito::Instance().IsHeadless())
					return;
				auto webRenderer = WebRenderer::GetInstance();
				if (show == webRenderer->IsRendering())
					return;
				webRenderer->ShowRenderer(show, true);
			}

			_extern void _sub_10C965D0(Web::Ui::ScreenLayer::ScreenId, std::string const &);
			void Show(Web::Ui::ScreenLayer::ScreenId screenId, std::string const &data) // 0x10C965D0
			{
				mangled_x86(MANGLED_TODO, "?Show@ScreenLayer@Ui@Web@@YAXW4ScreenId@123@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// std::string const &data;
				todo("implement");
				_sub_10C965D0(screenId, data);
			}

			_extern void _sub_10C96350(std::string const &, std::string const &);
			void Show(std::string const &screenId, std::string const &data) // 0x10C96350
			{
				mangled_x86(MANGLED_TODO, "?Show@ScreenLayer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
				// static ...; // 0x10C96538
				// static ...; // 0x10C96530
				// std::string const &screenId;
				// std::string const &data;
				// std::string js;
				todo("implement");
				_sub_10C96350(screenId, data);
			}

			void Hide(Web::Ui::ScreenLayer::ScreenId screenId) // 0x10C93E40
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@ScreenLayer@Ui@Web@@YAXW4ScreenId@123@@Z");
				// Web::Ui::ScreenLayer::ScreenId screenId;

				Web::Ui::ScreenLayer::Hide(ScreenIdString[screenId]);
			}

			_extern void _sub_10C93B60(std::string const &);
			void Hide(std::string const &screenId) // 0x10C93B60
			{
				mangled_x86(MANGLED_TODO, "?Hide@ScreenLayer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10C93DA3
				// static ...; // 0x10C93D9C
				// static ...; // 0x10C93D84
				// static ...; // 0x10C93D7C
				// std::string const &screenId;
				// std::string js;
				{
					// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::shared_ptr<Web::Ui::WebScreen> > > > > screen;
				}
				// function call : void ()
				todo("implement");
				_sub_10C93B60(screenId);
			}

			_extern void _sub_10C943A0(std::string const &, std::string const &, bool);
			void Notify(std::string const &event, std::string const &data, bool broadcast) // 0x10C943A0
			{
				mangled_x86(MANGLED_TODO, "?Notify@ScreenLayer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0_N@Z");
				// static ...; // 0x10C94620
				// std::string const &event;
				// std::string const &data;
				// bool broadcast;
				// std::string js;
				todo("implement");
				_sub_10C943A0(event, data, broadcast);
			}

			_extern void _sub_10C94A00(Web::Ui::ScreenLayer::ScreenId, std::string const &, std::string const &);
			void NotifyScreen(Web::Ui::ScreenLayer::ScreenId screenId, std::string const &event, std::string const &data) // 0x10C94A00
			{
				mangled_x86(MANGLED_TODO, "?NotifyScreen@ScreenLayer@Ui@Web@@YAXW4ScreenId@123@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@1@Z");
				// std::string const &data;
				todo("implement");
				_sub_10C94A00(screenId, event, data);
			}

			_extern void _sub_10C946E0(std::string const &, std::string const &, std::string const &);
			void NotifyScreen(std::string const &screenId, std::string const &event, std::string const &data) // 0x10C946E0
			{
				mangled_x86(MANGLED_TODO, "?NotifyScreen@ScreenLayer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z");
				// static ...; // 0x10C94940
				// std::string const &screenId;
				// std::string const &event;
				// std::string const &data;
				// std::string js;
				todo("implement");
				_sub_10C946E0(screenId, event, data);
			}

			_extern void _sub_10C94AE0(std::string const &, Web::Ui::ScreenLayer::EScreenState);
			void NotifyScreenStateChanged(std::string const &screenId, Web::Ui::ScreenLayer::EScreenState state) // 0x10C94AE0
			{
				mangled_x86(MANGLED_TODO, "?NotifyScreenStateChanged@ScreenLayer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4EScreenState@123@@Z");
				// static ...; // 0x10C94C10
				// static ...; // 0x10C94C08
				// std::string const &screenId;
				// Web::Ui::ScreenLayer::EScreenState state;
				// std::shared_ptr<Web::Ui::WebScreen> screen;
				// function call : void ()
				// function call : void ()
				todo("implement");
				_sub_10C94AE0(screenId, state);
			}

			_extern void _sub_10C92B20(bool, bool);
			void CaptureInput(bool capture, bool pointerCapture) // 0x10C92B20
			{
				mangled_x86(MANGLED_TODO, "?CaptureInput@ScreenLayer@Ui@Web@@YAX_N0@Z");
				// static ...; // 0x10C92D04
				// static ...; // 0x10C92CFC
				// bool capture;
				// bool pointerCapture;
				{
					// std::shared_ptr<WebOverlayInputContext> inputContext;
				}
				todo("implement");
				_sub_10C92B20(capture, pointerCapture);
			}

			_extern void _sub_10C96800(std::string const &, std::string, Web::Ui::ScreenLayer::AlertIcon, float);
			void ShowAlert(std::string const &title, std::string body, Web::Ui::ScreenLayer::AlertIcon icon, float height) // 0x10C96800
			{
				mangled_x86(MANGLED_TODO, "?ShowAlert@ScreenLayer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V45@W4AlertIcon@123@M@Z");
				// std::string const &title;
				// std::string body;
				// Web::Ui::ScreenLayer::AlertIcon icon;
				// float height;
				// Web::Ui::ScreenLayer::SDialogShowParams params;
				todo("implement");
				_sub_10C96800(title, body, icon, height);
			}

			_extern void _sub_10C95DE0(std::string const &, std::shared_ptr<Web::Ui::WebScreen> const &);
			void RegisterScreen(std::string const &screenId, std::shared_ptr<Web::Ui::WebScreen> const &screen) // 0x10C95DE0
			{
				mangled_x86(MANGLED_TODO, "?RegisterScreen@ScreenLayer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$shared_ptr@VWebScreen@Ui@Web@@@5@@Z");
				// std::shared_ptr<Web::Ui::WebScreen> const &screen;
				todo("implement");
				_sub_10C95DE0(screenId, screen);
			}

			_extern void _sub_10C95FE0(Web::Ui::ScreenLayer::ScreenId, std::shared_ptr<Web::Ui::WebScreen> const &);
			void RegisterScreen(Web::Ui::ScreenLayer::ScreenId id, std::shared_ptr<Web::Ui::WebScreen> const &screen) // 0x10C95FE0
			{
				mangled_x86(MANGLED_TODO, "?RegisterScreen@ScreenLayer@Ui@Web@@YAXW4ScreenId@123@ABV?$shared_ptr@VWebScreen@Ui@Web@@@std@@@Z");
				// std::shared_ptr<Web::Ui::WebScreen> const &screen;
				todo("implement");
				_sub_10C95FE0(id, screen);
			}
		}
	}
}

extern std::shared_ptr<Web::Ui::WebScreen> _sub_10C93690(std::string const &);
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			std::shared_ptr<Web::Ui::WebScreen> GetScreen(std::string const &stringId) // 0x10C93690
			{
				mangled_x86(MANGLED_TODO, "?GetScreen@ScreenLayer@Ui@Web@@YA?AV?$shared_ptr@VWebScreen@Ui@Web@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@5@@Z");
				// static ...; // 0x10C937FC
				// static ...; // 0x10C937F0
				// static ...; // 0x10C937E8
				// std::string const &stringId;
				{
					// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::shared_ptr<Web::Ui::WebScreen> > > > > it;
				}
				todo("implement");
				std::shared_ptr<Web::Ui::WebScreen> __result = _sub_10C93690(stringId);
				return __result;
			}

			_extern void _sub_10C96300(std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> const &);
			void SetDialogHandler(std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> const &handler) // 0x10C96300
			{
				mangled_x86(MANGLED_TODO, "?SetDialogHandler@ScreenLayer@Ui@Web@@YAXABV?$function@$$A6AXABUSDialogShowParams@ScreenLayer@Ui@Web@@@Z@std@@@Z");
				// std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> const &handler;
				todo("implement");
				_sub_10C96300(handler);
			}

			_extern void _sub_10C96A60(Web::Ui::ScreenLayer::SDialogShowParams const &);
			void ShowDialog(Web::Ui::ScreenLayer::SDialogShowParams const &params) // 0x10C96A60
			{
				mangled_x86(MANGLED_TODO, "?ShowDialog@ScreenLayer@Ui@Web@@YAXABUSDialogShowParams@123@@Z");
				// Web::Ui::ScreenLayer::SDialogShowParams const &params;
				todo("implement");
				_sub_10C96A60(params);
			}

			_extern void _sub_10C96C00(std::string const &, std::function<void __cdecl(std::string const &)>);
			void ShowDialog(std::string const &templateName, std::function<void __cdecl(std::string const &)> callback) // 0x10C96C00
			{
				mangled_x86(MANGLED_TODO, "?ShowDialog@ScreenLayer@Ui@Web@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$function@$$A6AXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z@5@@Z");
				// static ...; // 0x10C96CE4
				// static ...; // 0x10C96CDC
				// std::string const &templateName;
				// std::function<void __cdecl(std::string const &)> callback;
				// Web::Ui::ScreenLayer::SDialogShowParams params;
				todo("implement");
				_sub_10C96C00(templateName, callback);
			}

			_extern void _sub_10C92DF0();
			void CreateScreens() // 0x10C92DF0
			{
				mangled_x86(MANGLED_TODO, "?CreateScreens@ScreenLayer@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static ...; // 0x10C930B1
				// static ...; // 0x10C930A4
				// static ...; // 0x10C93099
				// static ...; // 0x10C93090
				// static ...; // 0x10C93060
				// static ...; // 0x10C93058
				// scoped_refptr<Web::Browser::WebRendererHandler> renderHandler;
				// std::shared_ptr<Web::Browser::Bridge::WebRendererQueryHandler> queryHandler;
				{
					// std::map<std::string,std::shared_ptr<Web::Ui::WebScreen> > &<range>$L0;
					// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::shared_ptr<Web::Ui::WebScreen> > > > > <begin>$L0;
					// std::_Default_sentinel <end>$L0;
					{
						// std::pair<std::string const ,std::shared_ptr<Web::Ui::WebScreen> > &screen;
					}
				}
				// function call : void (Web::Browser::Bridge::WebRendererQueryHandler &)
				todo("implement");
				_sub_10C92DF0();
			}
		}
	}
}

namespace Patches
{
	namespace Input
	{
		// mangled_x86(MANGLED_DEFAULT, "??0InputContext@Input@Patches@@QAE@XZ"); no body to assert in
	}
}

/* ---------- private code */

_inline void WebOverlayInputContext::Activated() // 0x10C92B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Activated@WebOverlayInputContext@hades_file_local@@UAEXXZ");
	// the original is empty
	// `anonymous-namespace'::WebOverlayInputContext::Activated
	// WebOverlayInputContext *const this;
}

_inline void WebOverlayInputContext::Deactivated() // 0x10C93180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Deactivated@WebOverlayInputContext@hades_file_local@@UAEXXZ");
	// the original is empty
	// `anonymous-namespace'::WebOverlayInputContext::Deactivated
	// WebOverlayInputContext *const this;
}

_inline bool WebOverlayInputContext::GameInputTick() // 0x10C931A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GameInputTick@WebOverlayInputContext@hades_file_local@@UAE_NXZ");
	// `anonymous-namespace'::WebOverlayInputContext::GameInputTick
	// WebOverlayInputContext *const this;

	OnGameInputUpdated();
	if (!WebRenderer::GetInstance()->IsRendering())
		InputCaptured = false;
	return InputCaptured || PointerCaptured;
}

_extern bool _sub_10C970D0(WebOverlayInputContext *const);
_inline bool WebOverlayInputContext::UiInputTick() // 0x10C970D0
{
	// `anonymous-namespace'::WebOverlayInputContext::UiInputTick
	// WebOverlayInputContext *const this;
	todo("implement");
	bool __result = _sub_10C970D0(this);
	return __result;
}

_inline void WebOverlayInputContext::InputBlock() // 0x10C94110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InputBlock@WebOverlayInputContext@hades_file_local@@UAEXXZ");
	// `anonymous-namespace'::WebOverlayInputContext::InputBlock
	// WebOverlayInputContext *const this;

	if (!InputCaptured && PointerCaptured)
	{
		QuickUnblockInput();
		return;
	}
	QuickBlockInput();
}

_inline void WebOverlayInputContext::InputUnblock() // 0x10C941E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InputUnblock@WebOverlayInputContext@hades_file_local@@UAEXXZ");
	// `anonymous-namespace'::WebOverlayInputContext::InputUnblock
	// WebOverlayInputContext *const this;

	QuickUnblockInput();
}

void QuickBlockInput() // 0x10C95D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?QuickBlockInput@@YAXXZ");
	// `anonymous-namespace'::QuickBlockInput
	// procedure flags: nofpo

	memset((void *)0x238DBEB, 1, 3);
}

void QuickUnblockInput() // 0x10C95D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?QuickUnblockInput@@YAXXZ");
	// `anonymous-namespace'::QuickUnblockInput
	// procedure flags: nofpo

	memset((bool *)0x238DBEB, 0, 3);
}

void WindowCreated(HWND__ *window) // 0x10C972C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WindowCreated@@YAXPAUHWND__@@@Z");
	// `anonymous-namespace'::WindowCreated
	// HWND__ *window;
	// unsigned long threadId;
	// function call : unsigned long (HWND__ *, unsigned long *)
	// function call : HHOOK__ *(__int32, long (*)(__int32, unsigned __int32, long), HINSTANCE__ *, unsigned long)

	Web::Ui::ScreenLayer::Resize();
	unsigned int threadId = GetWindowThreadProcessId(window, nullptr);
	MessageHook = SetWindowsHookExA(WH_GETMESSAGE, GetMsgHook, nullptr, threadId);
}

_extern void _sub_10C96D40();
void ShutdownRenderer() // 0x10C96D40
{
	// `anonymous-namespace'::ShutdownRenderer
	// procedure flags: nofpo
	// static ...; // 0x10C96E99
	// static ...; // 0x10C96E90
	// static ...; // 0x10C96E78
	// static ...; // 0x10C96E70
	{
		// std::map<std::string,std::shared_ptr<Web::Ui::WebScreen> > &<range>$L0;
		// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::shared_ptr<Web::Ui::WebScreen> > > > > <begin>$L0;
		// std::_Default_sentinel <end>$L0;
		{
			// std::pair<std::string const ,std::shared_ptr<Web::Ui::WebScreen> > &screen;
		}
	}
	// function call : void ()
	todo("implement");
	_sub_10C96D40();
}

extern CefStructBase<CefPlatformEventTraits> _sub_10C94230(tagMSG *);
CefStructBase<CefPlatformEventTraits> MakeCefPlatformEvent(tagMSG *msg) // 0x10C94230
{
	// `anonymous-namespace'::MakeCefPlatformEvent
	// static ...; // 0x10C9434C
	// static ...; // 0x10C94340
	// static ...; // 0x10C94338
	// tagMSG *msg;
	// CefStructBase<CefPlatformEventTraits> event;
	todo("implement");
	CefStructBase<CefPlatformEventTraits> __result = _sub_10C94230(msg);
	return __result;
}

_extern void _sub_10C939D0(tagMSG *);
void HandleMouseMessage(tagMSG *msg) // 0x10C939D0
{
	// `anonymous-namespace'::HandleMouseMessage
	// tagMSG *msg;
	todo("implement");
	_sub_10C939D0(msg);
}

void HandleKeyMessage(tagMSG *msg) // 0x10C93890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleKeyMessage@@YAXPAUtagMSG@@@Z");
	// `anonymous-namespace'::HandleKeyMessage
	// tagMSG *msg;

	Web::Browser::WebRenderer::GetInstance()->SendPlatformEvent(MakeCefPlatformEvent(msg));
}

void GetMsgHookImpl(__int32 code, unsigned __int32 wParam, long lParam) // 0x10C933A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMsgHookImpl@@YAXHIJ@Z");
	// `anonymous-namespace'::GetMsgHookImpl
	// static ...; // 0x10C9352C
	// static ...; // 0x10C93520
	// static ...; // 0x10C93518
// $LN22:
// $LN16:
	// __int32 code;
	// unsigned __int32 wParam;
	// long lParam;
	// std::shared_ptr<Web::Browser::WebRenderer> webRenderer;
	// tagMSG *msg;

	// Ignore messages not sent to a window
	auto msg = reinterpret_cast<LPMSG>(lParam);
	if (!msg->hwnd)
		return;

	// Ignore messages if the web renderer isn't active or if input isn't captured
	auto webRenderer = WebRenderer::GetInstance();
	if ((!InputCaptured && !PointerCaptured) || !webRenderer->IsRendering())
		return;

	switch (msg->message)
	{
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_MOUSEHWHEEL:
		HandleMouseMessage(msg);
		break;

	case WM_CHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		if(InputCaptured)
			HandleKeyMessage(msg);
		break;
	}
}

long __stdcall GetMsgHook(__int32 code, unsigned __int32 wParam, long lParam) // 0x10C93310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMsgHook@@YGJHIJ@Z");
	// `anonymous-namespace'::GetMsgHook
	// long lParam;
	// function call : long (HHOOK__ *, __int32, unsigned __int32, long)

	if (code >= 0)
		GetMsgHookImpl(code, wParam, lParam);

	return CallNextHookEx(MessageHook, code, wParam, lParam);
}

_extern void _sub_10C950F0();
void OnGameInputUpdated() // 0x10C950F0
{
	// `anonymous-namespace'::OnGameInputUpdated
	// procedure flags: nofpo
	// static ...; // 0x10C9542C
	// static ...; // 0x10C95428
	// static ...; // 0x10C95410
	// static ...; // 0x10C95408
	// std::shared_ptr<Web::Browser::WebRenderer> webRenderer;
	{
		// char url[256];
	}
	// function call : HINSTANCE__ *(HWND__ *, char const *, char const *, char const *, char const *, __int32)
	todo("implement");
	_sub_10C950F0();
}

_extern void _sub_10C95510();
void OnUIInputUpdated() // 0x10C95510
{
	// `anonymous-namespace'::OnUIInputUpdated
	// procedure flags: nofpo
	// static ...; // 0x10C95B4E
	// static ...; // 0x10C95B47
	// static ...; // 0x10C95B44
	// static ...; // 0x10C95B20
	// static ...; // 0x10C95B18
	// Modules::ModuleSettings &moduleSettings;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// Modules::ModuleInput &moduleInput;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// OnUIInputUpdated::__l2::ControllerAxes &controllerAxes;
	// std::string js;
	{
		// __int32 i;
		{
			// Blam::Input::ActionState *action;
		}
	}
	// function call : long (*const)()
	// function call : float (*const)()
	todo("implement");
	_sub_10C95510();
}

void OnVariableUpdate(Modules::Command const *command) // 0x10C95CF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnVariableUpdate@@YAXPBUCommand@Modules@@@Z");
	// `anonymous-namespace'::OnVariableUpdate
	// Modules::Command const *command;

	lastVariableUpdates.push_back(command);
}

_extern void _sub_10C94C80();
void NotifyVariablesUpdated() // 0x10C94C80
{
	// `anonymous-namespace'::NotifyVariablesUpdated
	// procedure flags: nofpo
	// static ...; // 0x10C94FFC
	// static ...; // 0x10C94FF3
	// static ...; // 0x10C94FEC
	// static ...; // 0x10C94FD4
	// static ...; // 0x10C94FCC
// $LN11:
// $LN10:
// $LN9:
// $LN8:
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	{
		// Modules::Command const &command;
	}
	// function call : float (*const)(float)
	todo("implement");
	_sub_10C94C80();
}

// mangled_x86(MANGLED_DEFAULT, "??0WebOverlayInputContext@hades_file_local@@QAE@XZ"); no body to assert in
_inline WebOverlayInputContext::WebOverlayInputContext() = default; // 0x10C91390

