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
void OnShutdown();
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
		extern std::string DefaultBanListPath; // 0x11388338
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
	extern std::thread g_contextMenuthread; // 0x11388330
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace ContextMenu
	{
		_extern __int32 _sub_10728DF0(HWND__ *, unsigned __int32, unsigned __int32, long, bool *);
		__int32 __stdcall HandleWindowMessage(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled) // 0x10728DF0
		{
			mangled_x86(MANGLED_TODO, "?HandleWindowMessage@ContextMenu@Server@@YGHPAUHWND__@@IIJPA_N@Z");
			// bool *outHandled;
			todo("implement");
			__int32 __result = _sub_10728DF0(hWnd, msg, wParam, lParam, outHandled);
			return __result;
		}
	}
}

/* ---------- private code */

_extern void _sub_107287B0();
void CreateWindowExCM() // 0x107287B0
{
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
	todo("implement");
	_sub_107287B0();
}

_extern void _sub_10729260();
void UpdateMenu() // 0x10729260
{
	// `anonymous-namespace'::UpdateMenu
	// procedure flags: nofpo
	// static ...; // 0x107293F8
	// static ...; // 0x107293EC
	// static ...; // 0x107293E4
	// std::string serverName;
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32, unsigned __int32, char const *)
	todo("implement");
	_sub_10729260();
}

_extern void _sub_10728E90();
void InitNotifyIconData() // 0x10728E90
{
	// `anonymous-namespace'::InitNotifyIconData
	// procedure flags: nofpo
	// function call : HINSTANCE__ *(char const *)
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : __int32 (unsigned long, _NOTIFYICONDATAA *)
	todo("implement");
	_sub_10728E90();
}

_extern void _sub_107291D0();
void OnShutdown() // 0x107291D0
{
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo
	// function call : __int32 (unsigned long, _NOTIFYICONDATAA *)
	// function call : __int32 (HWND__ *)
	todo("implement");
	_sub_107291D0();
}

_extern void _sub_10728990(unsigned __int32);
void HandleMenuAction(unsigned __int32 action) // 0x10728990
{
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
	todo("implement");
	_sub_10728990(action);
}

_extern long _sub_10728460(HWND__ *, unsigned __int32, unsigned __int32, long);
long __stdcall ContextMenuWindowProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam) // 0x10728460
{
	// `anonymous-namespace'::ContextMenuWindowProc
	// HWND__ *hWnd;
	// unsigned __int32 msg;
	// unsigned __int32 wParam;
	// long lParam;
	{
		// tagPOINT curPoint;
		// unsigned __int32 clicked;
	}
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
	todo("implement");
	long __result = _sub_10728460(hWnd, msg, wParam, lParam);
	return __result;
}

_extern void _sub_10728390();
void ContextMenuThreadProc() // 0x10728390
{
	// `anonymous-namespace'::ContextMenuThreadProc
	// procedure flags: nofpo
	// static ...; // 0x10728430
	// static ...; // 0x10728424
	// static ...; // 0x1072841C
	// tagMSG msg;
	// function call : __int32 (tagMSG *, HWND__ *, unsigned __int32, unsigned __int32)
	// function call : __int32 (tagMSG const *)
	// function call : long (tagMSG const *)
	todo("implement");
	_sub_10728390();
}

_extern void _sub_10728F90(void *);
void Initialize(void *parentHwnd) // 0x10728F90
{
	// `anonymous-namespace'::Initialize
	// static ...; // 0x10729060
	// static ...; // 0x10729054
	// static ...; // 0x1072904C
	// void *parentHwnd;
	// std::thread thread;
	todo("implement");
	_sub_10728F90(parentHwnd);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Server::TempBanList & Utils::Singleton<Server::TempBanList>::Instance();
