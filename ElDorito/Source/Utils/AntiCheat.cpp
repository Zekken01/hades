/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Utils/Singleton.hpp"

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
#include <deque>
#include <exception>
#include <forward_list>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	namespace AntiCheat
	{
		extern void AntiSpeed();
		extern __int32 __stdcall AntiTrainer(HWND__ *hwnd, long lParam);
		extern void OnTickCheck();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace AntiCheat
	{
		_extern void _sub_10C53880();
		void AntiSpeed() // 0x10C53880
		{
			mangled_x86(MANGLED_TODO, "?AntiSpeed@AntiCheat@Utils@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C53A1F
			// static ...; // 0x10C53A16
			// static ...; // 0x10C53A0C
			// static ...; // 0x10C539E8
			// static ...; // 0x10C539E0
			// HINSTANCE__ *hMods[1024];
			// unsigned __int32 i;
			// unsigned long cbNeeded;
			{
				// char szModName[260];
			}
			// function call : void *()
			// function call : void *()
			todo("implement");
			_sub_10C53880();
		}

		__int32 __stdcall AntiTrainer(HWND__ *hwnd, long lParam) // 0x10C53A90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AntiTrainer@AntiCheat@Utils@@YGHPAUHWND__@@J@Z");
			// static ...; // 0x10C53BBC
			// static ...; // 0x10C53BB4
			// HWND__ *hwnd;
			// long lParam;
			// char title[80];
				// Blam::Network::Session *session;
			// function call : __int32 (HWND__ *, char *, __int32)
			// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)

			char title[80];
			GetWindowText(hwnd, title, sizeof(title));
			if (strcmp(title, "Halo Online Trainer") == 0)
			{
				auto session = Blam::Network::GetActiveSession();
				if (session && session->IsEstablished() && !session->IsHost())
				{
					MessageBox(NULL, "Detected Halo Online Trainer!\nOnly hosts are allowed to use a trainer!", "AntiCheat", MB_OK); //Tell the user what they did wrong.
					Modules::CommandMap::Instance().ExecuteCommand("exit"); //exit game
				}
			}

			return TRUE;
		}

		void OnTickCheck() // 0x10C53C20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnTickCheck@AntiCheat@Utils@@YAXXZ");
			// procedure flags: nofpo
		}
	}
}

/* ---------- private code */
