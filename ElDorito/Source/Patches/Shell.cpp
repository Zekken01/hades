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
#include "Web/Ui/ScreenLayer.hpp"

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

namespace Server { namespace InfoServer { extern __int32 __stdcall networkWndProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled); } }  // hades: added for 0x10ACBDE0
namespace Server { namespace ContextMenu { extern __int32 __stdcall HandleWindowMessage(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled); } }  // hades: added for 0x10ACBDE0
namespace Patches { namespace MouseSupport { extern void NotifyMouseMove(__int32 x, __int32 y); } }  // hades: added for 0x10ACBDE0
__int32 __stdcall WndProcHook(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam);
void EnableImmersiveDarkMode(HWND__ *hWnd);
__int32 __stdcall SetWindowPosHook(HWND__ *hWnd, HWND__ *hWndInsertAfter, __int32 x, __int32 y, __int32 cx, __int32 cy, unsigned __int32 uFlags);
void DisplayCreateWindowError();
namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x10ACB3C0
static HWND__ *CreateGameWindowHook();

/* ---------- globals */

extern unsigned __int32 const c_DwmMaxQueuedBuffers; // 0x111B218C
extern unsigned __int32 const c_DwmMaxMonitors; // 0x111B2190
extern unsigned __int32 const c_DwmMaxAdapters; // 0x111B2194

/* ---------- private variables */

namespace hades_file_local
{
	namespace hades_file_local_Shell { extern __int32 g_last_mouse_x; } using namespace hades_file_local_Shell; // 0x12467408
	namespace hades_file_local_Shell { extern __int32 g_last_mouse_y; } using namespace hades_file_local_Shell; // 0x1246740C
}
using namespace hades_file_local;
namespace Server
{
	namespace hades_file_local_Server
	{
		// extern std::string DefaultBanListPath; // 0x124673EC  // hades: defined (with its initialiser) elsewhere now
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

/* ---------- private code */

__int32 __stdcall WndProcHook(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam) // 0x10ACBDE0
{
	bool handled = false;
	__int32 result = Server::InfoServer::networkWndProc(hWnd, msg, wParam, lParam, &handled);
	if (handled)
		return result;
	if (msg == WM_XBUTTONDOWN && !Utils::Singleton<ElDorito>::Instance().IsDedicated())
	{
		__int32 mouseXButton = GET_XBUTTON_WPARAM(wParam);
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("xbutton");
		jsonWriter.Int(mouseXButton);
		jsonWriter.EndObject();
		Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Settings, "mouse-xbutton-event", jsonBuffer.GetString());
	}
	if (msg == WM_MOUSEMOVE)
	{
		__int32 x = (__int32)(short)LOWORD(lParam);
		__int32 y = (__int32)(short)HIWORD(lParam);
		if (g_last_mouse_x != x || g_last_mouse_y != y)
		{
			g_last_mouse_x = x;
			g_last_mouse_y = y;
			Patches::MouseSupport::NotifyMouseMove(x, y);
		}
	}
	if (Utils::Singleton<ElDorito>::Instance().IsHeadless())
	{
		result = Server::ContextMenu::HandleWindowMessage(hWnd, msg, wParam, lParam, &handled);
		if (handled)
			return result;
	}
	return ((__int32 (__stdcall *)(HWND__ *, unsigned __int32, unsigned __int32, long))0x42E6A0)(hWnd, msg, wParam, lParam);
}

void EnableImmersiveDarkMode(HWND__ *hWnd) // 0x10ACBBA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EnableImmersiveDarkMode@@YAXPAUHWND__@@@Z");

	__int32 appsUseLightTheme;
	unsigned long cb = sizeof(appsUseLightTheme);
	if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"AppsUseLightTheme", RRF_RT_REG_DWORD, nullptr, &appsUseLightTheme, &cb) == ERROR_SUCCESS && !appsUseLightTheme)
	{
		__int32 value = TRUE;
		DwmSetWindowAttribute(hWnd, 20, &value, sizeof(value));
	}
}

__int32 __stdcall SetWindowPosHook(HWND__ *hWnd, HWND__ *hWndInsertAfter, __int32 x, __int32 y, __int32 cx, __int32 cy, unsigned __int32 uFlags) // 0x10ACBCC0
{

	tagRECT rc;
	GetClientRect(GetDesktopWindow(), &rc);
	x = (rc.right - rc.left - cx) / 2;
	y = (rc.bottom - rc.top - cy) / 2;
	return SetWindowPos(hWnd, hWndInsertAfter, x, y, cx, cy, uFlags & ~(SWP_NOMOVE | SWP_NOOWNERZORDER));
}

void DisplayCreateWindowError() // 0x10ACBAA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DisplayCreateWindowError@@YAXXZ");

	char buffer[1024];

	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, 0, NULL);
	MessageBoxA(NULL, buffer, "ERROR - failed to create window", MB_ICONINFORMATION);
}

static HWND__ *CreateGameWindowHook() // 0x10ACB3C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CreateGameWindowHook@@YAPAUHWND__@@XZ");

	bool (*const global_preferences_get_fullscreen)() = (bool (*)())0x50B250;
	long *resolution = (long *)0x19106C8;
	long *client_resolution = (long *)0x19106E4;
	long width = resolution[0];
	long height = resolution[1];
	tagWNDCLASSEXA wc;
	memset(&wc, 0, sizeof(wc));
	wc.lpfnWndProc = (WNDPROC)WndProcHook;
	wc.cbSize = sizeof(wc);
	wc.style = CS_CLASSDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = *(HINSTANCE *)0x199C010;
	wc.hIcon = LoadIconA(GetModuleHandleA(NULL), MAKEINTRESOURCEA(0x67));
	HICON hcursor = (HICON)LoadImageA(NULL, "halo3.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	if (!hcursor)
	{
		hcursor = (HICON)LoadImageA(GetModuleHandleA(NULL), MAKEINTRESOURCEA(0x66), IMAGE_CURSOR, 0, 0, 0);
		if (!hcursor)
			hcursor = LoadCursorA(NULL, IDC_ARROW);
	}
	wc.hCursor = hcursor;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "ElDewrito";
	wc.hIconSm = wc.hIcon;
	unsigned short atom = RegisterClassExA(&wc);
	if (!atom)
	{
		DisplayCreateWindowError();
		return nullptr;
	}
	std::string windowTitle = "ElDewrito | Version: " + Utils::Version::GetVersionString() + " | Build Date: Oct  3 2025";
	HWND hwnd = CreateWindowExA(0, wc.lpszClassName, windowTitle.c_str(), WS_BORDER, 0, 0, width, height, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	*(HWND *)0x199C014 = hwnd;
	if (!hwnd)
	{
		DisplayCreateWindowError();
		return nullptr;
	}
	bool is_fullscreen = global_preferences_get_fullscreen();
	unsigned long window_style = is_fullscreen ? 0 : 0xCA0000;
	unsigned long old_window_style = SetWindowLongA(hwnd, GWL_STYLE, window_style);
	tagRECT client_rect;
	client_rect.right = resolution[0];
	client_rect.bottom = resolution[1];
	client_rect.left = 0;
	client_rect.top = 0;
	AdjustWindowRect(&client_rect, window_style, FALSE);
	unsigned long swp_flags = 0x226;
	__int32 ret = SetWindowPosHook(hwnd, (HWND)-1, 0, 0, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, swp_flags);
	if (!ret)
	{
		DisplayCreateWindowError();
		return nullptr;
	}
	EnableImmersiveDarkMode(hwnd);
	ShowWindow(hwnd, 2 * (is_fullscreen ? 1 : 0) + 1);
	GetClientRect(hwnd, &client_rect);
	client_resolution[0] = client_rect.right - client_rect.left;
	client_resolution[1] = client_rect.bottom - client_rect.top;
	return hwnd;
}

namespace Patches
{
	namespace Shell
	{
		void ApplyAll() // 0x10ACB020
		{

					Pointer::Base(0x2EB63).Write<unsigned int>((unsigned int)&WndProcHook);
					Hook(0x6223F0, CreateGameWindowHook).Apply();
					Hook(0x6225BD, SetWindowPosHook, static_cast<__int32>(HookFlags::IsIndirectCall)).Apply();
					Hook(0x62275C, SetWindowPosHook, static_cast<__int32>(HookFlags::IsIndirectCall)).Apply();
		}
	}
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { namespace hades_file_local_Shell { __int32 g_last_mouse_x; } }
namespace hades_file_local { namespace hades_file_local_Shell { __int32 g_last_mouse_y; } }
