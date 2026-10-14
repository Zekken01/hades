/* ---------- headers */

#include "hades/hades.h"

#include "App.hpp"

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
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_message_router.h>

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
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
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class App;

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

/* ---------- constants */

/* ---------- definitions */

typedef _Cnd_internal_imp_t *_Cnd_t;
typedef unsigned __int32 _Thrd_id_t;
typedef _Mtx_internal_imp_t *_Mtx_t;
typedef double __std_tzdb_epoch_milli;

/* ---------- prototypes */

extern "C" __int32 __stdcall WinMain(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, __int32 nCmdShow);

/* ---------- globals */

extern unsigned long NvOptimusEnablement; // 0x75800C
extern __int32 AmdPowerXpressRequestHighPerformance; // 0x758010

/* ---------- private variables */

/* ---------- public code */

extern "C" __int32 __stdcall WinMain(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, __int32 nCmdShow) // 0x42D610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_WinMain@16");
	// __int32 nCmdShow; // local
	// __int32 exitCode; // local
	// CefMainArgs args; // local
	// std::filesystem::path binPath; // local
	// scoped_refptr<App> app; // local
	// HINSTANCE__ *hInstance;
	// HINSTANCE__ *hPrevInstance;
	// char *lpCmdLine;
	// __int32 nCmdShow;
	// CefMainArgs args;
	// std::filesystem::path binPath;
	// scoped_refptr<App> app;
	// function call : __int32 (wchar_t const *)
	// function call : HINSTANCE__ *(wchar_t const *)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)

	std::filesystem::path binPath = std::filesystem::absolute("bin\\cef");
	SetDllDirectoryW(binPath.c_str());
	LoadLibraryW((binPath / "libcef.dll").wstring().c_str());
	CefEnableHighDPISupport();
	CefMainArgs args(hInstance);
	scoped_refptr<App> app(new App());
	__int32 exitCode = CefExecuteProcess(args, app.get(), nullptr);
	if (exitCode < 0)
	{
		MessageBoxA(NULL, "Must be run by mtndew.dll!", "ElDewrito CEF Process", MB_ICONERROR);
		exitCode = 0;
	}
	return exitCode;
}

/* ---------- private code */
