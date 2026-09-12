/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "Server/BanList.hpp"
#include "Server/StatsServerBanList.hpp"
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
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include <Windows.h>
#include <commctrl.h>
#include <dpa_dsa.h>
#include <dwmapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <uxtheme.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace InfoServer {}
	using namespace Server::InfoServer;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

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
	namespace MouseSupport {}
	using namespace Patches::MouseSupport;
	namespace Shell {}
	using namespace Patches::Shell;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

__int32 __stdcall WndProcHook(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam);
void EnableImmersiveDarkMode(HWND__ *hWnd);
__int32 __stdcall SetWindowPosHook(HWND__ *hWnd, HWND__ *hWndInsertAfter, __int32 x, __int32 y, __int32 cx, __int32 cy, unsigned __int32 uFlags);
void DisplayCreateWindowError();
HWND__ *CreateGameWindowHook();

/* ---------- globals */

extern unsigned __int32 const c_DwmMaxQueuedBuffers; // 0x111B218C
extern unsigned __int32 const c_DwmMaxMonitors; // 0x111B2190
extern unsigned __int32 const c_DwmMaxAdapters; // 0x111B2194

/* ---------- private variables */

namespace hades_file_local
{
	extern __int32 g_last_mouse_x; // 0x12467408
	extern __int32 g_last_mouse_y; // 0x1246740C
}
using namespace hades_file_local;
namespace Server
{
	namespace hades_file_local_Server
	{
		extern std::string DefaultBanListPath; // 0x124673EC
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

/* ---------- private code */

_extern __int32 _sub_10ACBDE0(HWND__ *, unsigned __int32, unsigned __int32, long);
__int32 __stdcall WndProcHook(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam) // 0x10ACBDE0
{
	// `anonymous-namespace'::WndProcHook
	// static ...; // 0x10ACC06C
	// static ...; // 0x10ACC064
	// HWND__ *hWnd;
	// unsigned __int32 msg;
	// unsigned __int32 wParam;
	// long lParam;
	// bool handled;
	// __int32 result;
	// constexpr __int32 (*const `WndProcHook'::`2'::Game_WndProc)(HWND__ *, unsigned __int32, unsigned __int32, long); // constant == 4384416
	{
		// __int32 mouseXButton;
		// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
		// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	}
	{
		// __int32 x;
		// __int32 y;
	}
	// function call : __int32 (*const)(HWND__ *, unsigned __int32, unsigned __int32, long)
	todo("implement");
	__int32 __result = _sub_10ACBDE0(hWnd, msg, wParam, lParam);
	return __result;
}

_extern void _sub_10ACBBA0(HWND__ *);
void EnableImmersiveDarkMode(HWND__ *hWnd) // 0x10ACBBA0
{
	// `anonymous-namespace'::EnableImmersiveDarkMode
	// static ...; // 0x10ACBC75
	// static ...; // 0x10ACBC72
	// static ...; // 0x10ACBC6C
	// static ...; // 0x10ACBC48
	// static ...; // 0x10ACBC40
	// HWND__ *hWnd;
	// unsigned long cb;
	// __int32 appsUseLightTheme;
	{
		// __int32 value;
	}
	// function call : long (HKEY__ *, wchar_t const *, wchar_t const *, unsigned long, unsigned long *, void *, unsigned long *)
	// function call : HRESULT (HWND__ *, unsigned long, void const *, unsigned long)
	todo("implement");
	_sub_10ACBBA0(hWnd);
}

_extern __int32 _sub_10ACBCC0(HWND__ *, HWND__ *, __int32, __int32, __int32, __int32, unsigned __int32);
__int32 __stdcall SetWindowPosHook(HWND__ *hWnd, HWND__ *hWndInsertAfter, __int32 x, __int32 y, __int32 cx, __int32 cy, unsigned __int32 uFlags) // 0x10ACBCC0
{
	// `anonymous-namespace'::SetWindowPosHook
	// __int32 y;
	// __int32 cx;
	// __int32 cy;
	// unsigned __int32 uFlags;
	// tagRECT rc;
	// function call : HWND__ *()
	// function call : __int32 (HWND__ *, tagRECT *)
	// function call : __int32 (HWND__ *, HWND__ *, __int32, __int32, __int32, __int32, unsigned __int32)
	todo("implement");
	__int32 __result = _sub_10ACBCC0(hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
	return __result;
}

_extern void _sub_10ACBAA0();
void DisplayCreateWindowError() // 0x10ACBAA0
{
	// `anonymous-namespace'::DisplayCreateWindowError
	// procedure flags: nofpo
	// static ...; // 0x10ACBB60
	// static ...; // 0x10ACBB54
	// static ...; // 0x10ACBB4C
	// char buffer[1024];
	// function call : unsigned long ()
	// function call : unsigned long (unsigned long, void const *, unsigned long, unsigned long, char *, unsigned long, char **)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	todo("implement");
	_sub_10ACBAA0();
}

extern HWND__ *_sub_10ACB3C0();
HWND__ *CreateGameWindowHook() // 0x10ACB3C0
{
	// `anonymous-namespace'::CreateGameWindowHook
	// procedure flags: nofpo
	// static ...; // 0x10ACB938
	// static ...; // 0x10ACB92C
	// static ...; // 0x10ACB920
	// static ...; // 0x10ACB8FC
	// static ...; // 0x10ACB8F4
	// __int32 ret;
	// tagRECT client_rect;
	// unsigned long old_window_style;
	// HICON__ *hcursor;
	// HWND__ *hwnd;
	// unsigned long swp_flags;
	// bool is_fullscreen;
	// tagWNDCLASSEXA wc;
	// bool (*const global_preferences_get_fullscreen)();
	// std::string windowTitle;
	// unsigned long window_style;
	// long *resolution;
	// long *client_resolution;
	// long width;
	// long height;
	// unsigned short atom;
	// function call : HINSTANCE__ *(char const *)
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : void *(HINSTANCE__ *, char const *, unsigned __int32, __int32, __int32, unsigned __int32)
	// function call : HINSTANCE__ *(char const *)
	// function call : void *(HINSTANCE__ *, char const *, unsigned __int32, __int32, __int32, unsigned __int32)
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : void *(__int32)
	// function call : unsigned short (tagWNDCLASSEXA const *)
	// function call : HWND__ *()
	// function call : HWND__ *(unsigned long, char const *, char const *, unsigned long, __int32, __int32, __int32, __int32, HWND__ *, HMENU__ *, HINSTANCE__ *, void *)
	// function call : bool (*const)()
	// function call : long (HWND__ *, __int32, long)
	// function call : __int32 (tagRECT *, unsigned long, __int32)
	// function call : __int32 (HWND__ *, __int32)
	// function call : __int32 (HWND__ *, tagRECT *)
	todo("implement");
	HWND__ * __result = _sub_10ACB3C0();
	return __result;
}
