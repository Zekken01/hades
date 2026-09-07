/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "ElDorito.hpp"
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

namespace
{
	enum TrayEvent
	{
		TrayEvent_Action = 0,
		TrayEvent_MenuUpdate,
	};
}
/* ---------- definitions */

/* ---------- prototypes */

namespace Server
{
	namespace ContextMenu
	{
		extern __int32 __stdcall HandleWindowMessage(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled);
	}
}

/* ---------- globals */

namespace Utils
{
	Server::TempBanList *Utils::Singleton<Server::TempBanList>::m_instance; // 0x1138832C
}

/* ---------- private variables */

namespace Server
{
	namespace
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > DefaultBanListPath; // 0x11388338
	}
}
namespace
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
