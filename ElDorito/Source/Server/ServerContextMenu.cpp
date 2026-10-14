/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/Core.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Server/BanList.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "Modules/ModuleServer.hpp"  // hades: added for 0x10729260

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Server
{
	class TempBanList;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

/* ---------- constants */

namespace hades_file_local
{
	enum TrayEvent
	{
		TrayEvent_Action = 0,
		TrayEvent_MenuUpdate,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

/* ---------- prototypes */

namespace Server
{
	namespace ContextMenu
	{
		extern __int32 __stdcall HandleWindowMessage(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled);
	}
}

void CreateWindowExCM();
void UpdateMenu();
void InitNotifyIconData();
static void OnShutdown();
void HandleMenuAction(unsigned __int32 action);
long __stdcall ContextMenuWindowProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam);
void ContextMenuThreadProc();
void Initialize(void *parentHwnd);

/* ---------- globals */

namespace Utils
{
	Server::TempBanList *Utils::Singleton<Server::TempBanList>::m_instance; // 0x1138832C
}

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		// extern std::string DefaultBanListPath; // 0x11388338  // hades: defined (with its initialiser) elsewhere now
	}
	using namespace hades_file_local_Server;
}
namespace hades_file_local
{
	extern _NOTIFYICONDATAA notifyIconData; // 0x11388358
	extern char const szTIP[64]; // 0x1117E4D0
	extern char const szClassName[26]; // 0x1117E510
	extern char const szWindowName[18]; // 0x1117E52C
	extern HWND__ *Hwnd; // 0x11388354
	extern HMENU__ *Hmenu; // 0x11388554
	extern HWND__ *g_parenthWnd; // 0x11388558
	std::thread g_contextMenuthread; // 0x11388330
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace ContextMenu
	{
		__int32 __stdcall HandleWindowMessage(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled) // 0x10728DF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HandleWindowMessage@ContextMenu@Server@@YGHPAUHWND__@@IIJPA_N@Z");
			// bool *outHandled;

			switch (msg)
			{
			case WM_CREATE:
				::Initialize(hWnd);
				break;

			case 0x402:
				if (wParam == TrayEvent_Action)
				{
					::HandleMenuAction(lParam);
				}
				else if (wParam == TrayEvent_MenuUpdate)
				{
					::UpdateMenu();
				}
				break;
			}

			return 0;
		}
	}
}

/* ---------- private code */

void CreateWindowExCM() // 0x107287B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CreateWindowExCM@@YAXXZ");
	// `anonymous-namespace'::CreateWindowExCM
	// procedure flags: nofpo
	// static ...; // 0x10728920
	// static ...; // 0x10728914
	// static ...; // 0x1072890C
	// HINSTANCE__ *hInstance;
	// tagWNDCLASSEXA wincl;
	// function call : HINSTANCE__ *(char const *)
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : HBRUSH__ *(unsigned long)
	// function call : unsigned short (tagWNDCLASSEXA const *)
	// function call : HWND__ *(unsigned long, char const *, char const *, unsigned long, __int32, __int32, __int32, __int32, HWND__ *, HMENU__ *, HINSTANCE__ *, void *)

	HINSTANCE hInstance = GetModuleHandleA("mtndew.dll");
	WNDCLASSEXA wincl;
	memset(&wincl, 0, sizeof(wincl));
	wincl.hInstance = hInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = ContextMenuWindowProc;
	wincl.style = 0;
	wincl.cbSize = sizeof(WNDCLASSEXA);
	wincl.hIcon = LoadIconA(nullptr, MAKEINTRESOURCEA(32512));
	wincl.hIconSm = LoadIconA(nullptr, MAKEINTRESOURCEA(32512));
	wincl.hCursor = LoadCursorA(nullptr, MAKEINTRESOURCEA(32512));
	wincl.lpszMenuName = nullptr;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	RegisterClassExA(&wincl);
	Hwnd = CreateWindowExA(0, szClassName, szWindowName, 0, 0, 0, 1, 1, g_parenthWnd, nullptr, hInstance, nullptr);
	if (!notifyIconData.hWnd)
		InitNotifyIconData();
}

void UpdateMenu() // 0x10729260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateMenu@@YAXXZ");
	// `anonymous-namespace'::UpdateMenu
	// procedure flags: nofpo
	// static ...; // 0x107293F8
	// static ...; // 0x107293EC
	// static ...; // 0x107293E4
	// std::string serverName;
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, unsigned __int32, char const *)

	if (!Hmenu)
		return;
	std::string serverName = Utils::Singleton<Modules::ModuleServer>::Instance().VarServerName->ValueString;
	ModifyMenuA(Hmenu, 0, MF_BYPOSITION | MF_DISABLED, 0, (serverName + ":" + Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPort->ValueString).c_str());
}

void InitNotifyIconData() // 0x10728E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitNotifyIconData@@YAXXZ");
	// `anonymous-namespace'::InitNotifyIconData
	// procedure flags: nofpo
	// function call : HINSTANCE__ *(char const *)
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : __int32 (unsigned long, _NOTIFYICONDATAA *)

	memset(&notifyIconData, 0, sizeof(notifyIconData));
	notifyIconData.cbSize = sizeof(notifyIconData);
	notifyIconData.hWnd = Hwnd;
	notifyIconData.uID = 1001;
	notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifyIconData.uCallbackMessage = WM_USER + 1;
	notifyIconData.hIcon = LoadIconA(GetModuleHandleA("mtndew.dll"), MAKEINTRESOURCEA(101));
	strncpy(notifyIconData.szTip, szTIP, sizeof(szTIP));
	Shell_NotifyIconA(NIM_ADD, &notifyIconData);
}

static void OnShutdown() // 0x107291D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnShutdown@@YAXXZ");
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo
	// function call : __int32 (unsigned long, _NOTIFYICONDATAA *)
	// function call : __int32 (HWND__ *)

	if (notifyIconData.hWnd)
	{
		notifyIconData.uFlags = 0;
		Shell_NotifyIconA(NIM_DELETE, &notifyIconData);
		DestroyWindow(Hwnd);
	}
}

void HandleMenuAction(unsigned __int32 action) // 0x10728990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMenuAction@@YAXI@Z");
	// `anonymous-namespace'::HandleMenuAction
	// static ...; // 0x10728CEC
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// unsigned __int32 action;
	// function call : HINSTANCE__ *(HWND__ *, char const *, char const *, char const *, char const *, __int32)
	// function call : HINSTANCE__ *(HWND__ *, char const *, char const *, char const *, char const *, __int32)
	// function call : HINSTANCE__ *(HWND__ *, char const *, char const *, char const *, char const *, __int32)
	// function call : HINSTANCE__ *(HWND__ *, char const *, char const *, char const *, char const *, __int32)

	switch (action)
	{
	case 1002:
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("Exit", false);
		break;
	case 1003:
		Utils::Singleton<Server::TempBanList>::Instance().ClearList();
		break;
	case 1004:
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("Voting.ReloadJson", false);
		break;
	case 1005:
		ShellExecuteA(nullptr, "open", Utils::Singleton<ElDorito>::Instance().GetDirectory().c_str(), nullptr, nullptr, 10);
		break;
	case 1006:
		ShellExecuteA(nullptr, "open", (Utils::Singleton<ElDorito>::Instance().GetDirectory() + "/mods").c_str(), nullptr, nullptr, 10);
		break;
	case 1007:
		ShellExecuteA(nullptr, "open", (Utils::Singleton<ElDorito>::Instance().GetDirectory() + Utils::Singleton<Modules::ModuleServer>::Instance().VarChatLogFile->ValueString).c_str(), nullptr, nullptr, 10);
		break;
	case 1008:
		ShellExecuteA(nullptr, "open", ("http://localhost:" + Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPort->ValueString).c_str(), nullptr, nullptr, 10);
		break;
	}
}

long __stdcall ContextMenuWindowProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam) // 0x10728460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ContextMenuWindowProc@@YGJPAUHWND__@@IIJ@Z");
	// `anonymous-namespace'::ContextMenuWindowProc
	// HWND__ *hWnd;
	// unsigned __int32 msg;
	// unsigned __int32 wParam;
	// long lParam;
		// tagPOINT curPoint;
		// unsigned __int32 clicked;
	// function call : HMENU__ *()
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, char const *)
	// function call : __int32 (tagPOINT *)
	// function call : __int32 (HWND__ *)
	// function call : long (HWND__ *, unsigned __int32, unsigned __int32, long)
	// function call : __int32 (HMENU__ *, unsigned __int32, __int32, __int32, HWND__ *, tagTPMPARAMS *)
	// function call : __int32 (HWND__ *, unsigned __int32, unsigned __int32, long)
	// function call : long (HWND__ *, unsigned __int32, unsigned __int32, long)

	switch (msg)
	{
	case WM_USER + 1:
	{
		if (lParam == WM_RBUTTONUP)
		{
			if (!Hmenu)
			{
				Hmenu = CreatePopupMenu();
				AppendMenuA(Hmenu, MF_DISABLED, 0, "<Server name>");
				AppendMenuA(Hmenu, MF_SEPARATOR, 0, nullptr);
				AppendMenuA(Hmenu, MF_STRING, 0x3EB, "Clear Temp Ban List");
				AppendMenuA(Hmenu, MF_STRING, 0x3EC, "Refresh Voting.json");
				AppendMenuA(Hmenu, MF_STRING, 0x3ED, "Open Server Directory");
				AppendMenuA(Hmenu, MF_STRING, 0x3EE, "Open Mods Directory");
				AppendMenuA(Hmenu, MF_STRING, 0x3EF, "Open Chat.log");
				AppendMenuA(Hmenu, MF_STRING, 0x3F0, "Open Info Server URL");
				AppendMenuA(Hmenu, MF_SEPARATOR, 0, nullptr);
				AppendMenuA(Hmenu, MF_STRING, 0x3EA, "Exit");
			}
			POINT curPoint;
			GetCursorPos(&curPoint);
			SetForegroundWindow(Hwnd);
			SendMessageA(g_parenthWnd, WM_USER + 2, 1, 0);
			UINT clicked = TrackPopupMenuEx(Hmenu, TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, hWnd, nullptr);
			if (clicked)
				PostMessageA(g_parenthWnd, WM_USER + 2, 0, clicked);
		}
		break;
	}
	}
	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

void ContextMenuThreadProc() // 0x10728390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ContextMenuThreadProc@@YAXXZ");
	// `anonymous-namespace'::ContextMenuThreadProc
	// procedure flags: nofpo
	// static ...; // 0x10728430
	// static ...; // 0x10728424
	// static ...; // 0x1072841C
	// tagMSG msg;
	// function call : __int32 (tagMSG *, HWND__ *, unsigned __int32, unsigned __int32)
	// function call : __int32 (tagMSG const *)
	// function call : long (tagMSG const *)

	tagMSG msg;

	::CreateWindowExCM();

	while (GetMessageA(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void Initialize(void *parentHwnd) // 0x10728F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@@YAXPAX@Z");
	// `anonymous-namespace'::Initialize
	// static ...; // 0x10729060
	// static ...; // 0x10729054
	// static ...; // 0x1072904C
	// void *parentHwnd;
	// std::thread thread;

	g_parenthWnd = (HWND__ *)parentHwnd;

	std::thread thread(::ContextMenuThreadProc);
	thread.detach();

	Patches::Core::OnShutdown(::OnShutdown);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Server::TempBanList & Utils::Singleton<Server::TempBanList>::Instance();
