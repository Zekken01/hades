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

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <ws2ipdef.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace DedicatedServer {}
	using namespace Server::DedicatedServer;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Blam::Network { int GetLobbyType(); }  // hades: added for 0X10B1ABC0
namespace Blam::Network { bool SetNetworkMode(int mode); }  // hades: added for 0X10B1ABC0
namespace Blam::Network { bool SetLobbyType(int type); }  // hades: added for 0X10B1ABC0

namespace Server
{
	namespace DedicatedServer
	{
		extern void Init();
		extern void Tick();
	}
}

/* ---------- globals */

namespace Server
{
	namespace DedicatedServer
	{
		extern bool needToSetMode; // 0x124676D9
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Server
{
	namespace DedicatedServer
	{
		void Init() // 0x10B1AB70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@DedicatedServer@Server@@YAXXZ");
			// procedure flags: nofpo

			Blam::Network::SetLobbyType(2);
			needToSetMode = true;
		}

		void Tick() // 0x10B1ABC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@DedicatedServer@Server@@YAXXZ");
			// procedure flags: nofpo

			if (!needToSetMode)
			{
				if (Blam::Network::GetLobbyType() != 2)
				{
					Blam::Network::SetLobbyType(2);
					needToSetMode = true;
				}
			}
			else if (Blam::Network::GetLobbyType() == 2 && Blam::Network::SetNetworkMode(3))
				needToSetMode = false;
		}
	}
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Server { namespace DedicatedServer { bool needToSetMode; } }
