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
		_extern void _sub_10B1AB70();
		void Init() // 0x10B1AB70
		{
			mangled_x86(MANGLED_TODO, "?Init@DedicatedServer@Server@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10B1AB70();
		}

		_extern void _sub_10B1ABC0();
		void Tick() // 0x10B1ABC0
		{
			mangled_x86(MANGLED_TODO, "?Tick@DedicatedServer@Server@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10B1ABC0();
		}
	}
}

/* ---------- private code */
