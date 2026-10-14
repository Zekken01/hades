/* ---------- headers */

#include "Server/HsGlobalSync.hpp"
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
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Reforge.hpp"

#include "Patches/Core.hpp"  // hades: added for 0x1071FB50

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct lambda_1;
struct s_player_datum;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace hades_file_local
{
	struct HsGlobalSyncState;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace HsGlobalSync {}
	using namespace Server::HsGlobalSync;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct HsGlobalSyncState
	{
		short globalIndex; // 0x0
		unsigned short synchronizedPlayersMask; // 0x2
	};
	static_assert(sizeof(HsGlobalSyncState) == 4, "Invalid HsGlobalSyncState size");

}
using namespace hades_file_local;
//class Server::HsGlobalSync::Init::__l2::<lambda_1>
//{
//public:
//	void operator()(char const *) const;
//};
//static_assert(sizeof(Server::HsGlobalSync::Init::__l2::<lambda_1>) == 1, "Invalid Server::HsGlobalSync::Init::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Server
{
	namespace HsGlobalSync
	{
		extern void RegisterGlobal(short globalIndex);
		extern void UnregisterGlobal(short globalIndex);
		extern void InvalidatePlayerMask(unsigned short playerMask);
		extern void InvalidateGlobal(short globalIndex);
		extern void Synchronize();
		extern void InitializeForNewMap();
		extern void Init();
		extern void Tick();
		extern void SetupFuncs(std::function<void __cdecl(short,unsigned short)> sendGlobal_);
	}
}

__int32 FindGlobalSyncState(unsigned long globalIndex);
namespace Server
{
	namespace HsGlobalSync
	{
		void SynchronizeGlobalInternal(HsGlobalSyncState *global);
	}
}

/* ---------- globals */

extern bool (*const game_is_distributed)();  // hades: added for 0X10720120
extern void OnMapLoaded(std::function<void __cdecl(char const *)> callback);

/* ---------- private variables */

namespace hades_file_local
{
	extern unsigned __int32 lastSynchronizeTime; // 0x1134D8F0
	std::vector<HsGlobalSyncState> registeredGlobals; // 0x113882E8  // hades: defined, so its dynamic initializer emits the _Vector_val constructor
	std::function<void __cdecl(short,unsigned short)> sendGlobal; // 0x113882F8  // hades: defined, so its dynamic initializer emits the default constructor
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace HsGlobalSync
	{
		void RegisterGlobal(short globalIndex) // 0x1071FD60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterGlobal@HsGlobalSync@Server@@YAXF@Z");
			// static ...; // 0x1071FDE4
			// static ...; // 0x1071FDD8
			// static ...; // 0x1071FDD0
			// short globalIndex;
			// HsGlobalSyncState stateDatum;

			HsGlobalSyncState stateDatum;

			if (FindGlobalSyncState(globalIndex) != -1)
				return;

			stateDatum.globalIndex = globalIndex;
			stateDatum.synchronizedPlayersMask = 0;
			registeredGlobals.push_back(stateDatum);
		}

		void UnregisterGlobal(short globalIndex) // 0x107201E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?UnregisterGlobal@HsGlobalSync@Server@@YAXF@Z");
			// short globalIndex;
			// __int32 index;

			__int32 index = FindGlobalSyncState(globalIndex);
			if (index == -1)
				return;
			registeredGlobals.erase(registeredGlobals.begin() + index);
		}

		void InvalidatePlayerMask(unsigned short playerMask) // 0x1071FCA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InvalidatePlayerMask@HsGlobalSync@Server@@YAXG@Z");
			// unsigned short playerMask;
				// unsigned __int32 i;

			for (unsigned __int32 i = 0; i < registeredGlobals.size(); i++)
			{
				registeredGlobals[i].synchronizedPlayersMask &= ~playerMask;
				SynchronizeGlobalInternal(&registeredGlobals[i]);
			}
		}

		void InvalidateGlobal(short globalIndex) // 0x1071FC10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InvalidateGlobal@HsGlobalSync@Server@@YAXF@Z");
			// short globalIndex;
			// __int32 index;
			// HsGlobalSyncState *global;

			__int32 index = FindGlobalSyncState(globalIndex);
			if (index == -1)
			{
				return;
			}

			HsGlobalSyncState *global = &registeredGlobals[index];
			global->synchronizedPlayersMask = 0;
			SynchronizeGlobalInternal(global);
		}

		void Synchronize() // 0x1071FEC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Synchronize@HsGlobalSync@Server@@YAXXZ");
			// procedure flags: nofpo
				// unsigned __int32 i;

			if (!sendGlobal)
			{
				return;
			}

			for (unsigned __int32 i = 0; i < registeredGlobals.size(); i++)
			{
				SynchronizeGlobalInternal(&registeredGlobals[i]);
			}

			lastSynchronizeTime = system_milliseconds();
		}

		void InitializeForNewMap() // 0x1071FBC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@HsGlobalSync@Server@@YAXXZ");
			// procedure flags: nofpo

			lastSynchronizeTime = -1;
			registeredGlobals.clear();
		}

		void Init() // 0x1071FB50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@HsGlobalSync@Server@@YAXXZ");
			// procedure flags: nofpo

			Patches::Core::OnMapLoaded([](char const *map)
			{
				InitializeForNewMap();
			});
		}

		void Tick() // 0x10720120
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@HsGlobalSync@Server@@YAXXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()
			// function call : bool (*const)()
			// function call : bool (*const)()

			if (!((bool (*const)())0x5314b0)() || !((bool (*const)())0x5319c0)() || !game_is_distributed())
				return;

			if (lastSynchronizeTime == -1 || system_milliseconds() - lastSynchronizeTime >= 50)
			{
				Synchronize();
			}
		}

		void SetupFuncs(std::function<void __cdecl(short,unsigned short)> sendGlobal_) // 0x1071FE20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetupFuncs@HsGlobalSync@Server@@YAXV?$function@$$A6AXFG@Z@std@@@Z");
			// std::function<void __cdecl(short,unsigned short)> sendGlobal_;

			sendGlobal = sendGlobal_;
		}
	}
}

/* ---------- private code */

__int32 FindGlobalSyncState(unsigned long globalIndex) // 0x1071FAC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindGlobalSyncState@@YAHK@Z");
	// `anonymous-namespace'::FindGlobalSyncState
	// unsigned long globalIndex;
		// unsigned __int32 i;

	for (unsigned __int32 i = 0; i < registeredGlobals.size(); i++)
	{
		if (registeredGlobals[i].globalIndex == globalIndex)
			return i;
	}

	return -1;
}

namespace Server
{
	namespace HsGlobalSync
	{
		void SynchronizeGlobalInternal(HsGlobalSyncState *global) // 0x1071FF70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SynchronizeGlobalInternal@HsGlobalSync@Server@@YAXPAUHsGlobalSyncState@hades_file_local@@@Z");
			// Server::HsGlobalSync::SynchronizeGlobalInternal
			// HsGlobalSyncState *global;
			// unsigned __int32 needsSyncPlayerMask;
			// unsigned short syncPlayerMask;
			// c_data_array<s_player_datum> *players;
			// Blam::Network::Session *session;
			// unsigned __int32 activePlayerMask;
				// __int32 i;
					// s_player_datum *player;
					// __int32 playerIdx;

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return;
			unsigned __int32 activePlayerMask = session->MembershipInfo.ActivePlayerMask;
			unsigned __int32 needsSyncPlayerMask = (global->synchronizedPlayersMask ^ activePlayerMask) & activePlayerMask;
			if (!needsSyncPlayerMask)
				return;
			unsigned short syncPlayerMask = 0;
			c_data_array<s_player_datum> *players = players_get();
			for (__int32 i = 0; i < 16; i++)
			{
				s_player_datum *player = players->get_absolute(i);
				if (!player->salt || !(player->flags & 1))
					continue;
				__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(player->machine_index);
				if (playerIdx == -1 || !(needsSyncPlayerMask & (1 << playerIdx)))
					continue;
				syncPlayerMask |= 1 << i;
			}
			if (syncPlayerMask)
			{
				sendGlobal(global->globalIndex, syncPlayerMask);
				global->synchronizedPlayersMask |= syncPlayerMask;
			}
		}
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_player_datum * c_data_array<s_player_datum>::get_absolute(long);

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { unsigned __int32 lastSynchronizeTime = 0xffffffff; }
