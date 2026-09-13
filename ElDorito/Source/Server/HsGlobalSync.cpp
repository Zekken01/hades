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

/* ---------- private variables */

namespace hades_file_local
{
	extern unsigned __int32 lastSynchronizeTime; // 0x1134D8F0
	extern std::vector<HsGlobalSyncState> registeredGlobals; // 0x113882E8
	extern std::function<void __cdecl(short,unsigned short)> sendGlobal; // 0x113882F8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace HsGlobalSync
	{
		_extern void _sub_1071FD60(short);
		void RegisterGlobal(short globalIndex) // 0x1071FD60
		{
			mangled_x86(MANGLED_TODO, "?RegisterGlobal@HsGlobalSync@Server@@YAXF@Z");
			// static ...; // 0x1071FDE4
			// static ...; // 0x1071FDD8
			// static ...; // 0x1071FDD0
			// short globalIndex;
			// HsGlobalSyncState stateDatum;
			todo("implement");
			_sub_1071FD60(globalIndex);
		}

		_extern void _sub_107201E0(short);
		void UnregisterGlobal(short globalIndex) // 0x107201E0
		{
			mangled_x86(MANGLED_TODO, "?UnregisterGlobal@HsGlobalSync@Server@@YAXF@Z");
			// short globalIndex;
			// __int32 index;
			todo("implement");
			_sub_107201E0(globalIndex);
		}

		_extern void _sub_1071FCA0(unsigned short);
		void InvalidatePlayerMask(unsigned short playerMask) // 0x1071FCA0
		{
			mangled_x86(MANGLED_TODO, "?InvalidatePlayerMask@HsGlobalSync@Server@@YAXG@Z");
			// unsigned short playerMask;
			{
				// unsigned __int32 i;
			}
			todo("implement");
			_sub_1071FCA0(playerMask);
		}

		_extern void _sub_1071FC10(short);
		void InvalidateGlobal(short globalIndex) // 0x1071FC10
		{
			mangled_x86(MANGLED_TODO, "?InvalidateGlobal@HsGlobalSync@Server@@YAXF@Z");
			// short globalIndex;
			// __int32 index;
			// HsGlobalSyncState *global;
			todo("implement");
			_sub_1071FC10(globalIndex);
		}

		_extern void _sub_1071FEC0();
		void Synchronize() // 0x1071FEC0
		{
			mangled_x86(MANGLED_TODO, "?Synchronize@HsGlobalSync@Server@@YAXXZ");
			// procedure flags: nofpo
			{
				// unsigned __int32 i;
			}
			todo("implement");
			_sub_1071FEC0();
		}

		void InitializeForNewMap() // 0x1071FBC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@HsGlobalSync@Server@@YAXXZ");
			// procedure flags: nofpo

			lastSynchronizeTime = -1;
			registeredGlobals.clear();
		}

		_extern void _sub_1071FB50();
		void Init() // 0x1071FB50
		{
			mangled_x86(MANGLED_TODO, "?Init@HsGlobalSync@Server@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1071FB50();
		}

		_extern void _sub_10720120();
		void Tick() // 0x10720120
		{
			mangled_x86(MANGLED_TODO, "?Tick@HsGlobalSync@Server@@YAXXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()
			// function call : bool (*const)()
			// function call : bool (*const)()
			todo("implement");
			_sub_10720120();
		}

		_extern void _sub_1071FE20(std::function<void __cdecl(short,unsigned short)>);
		void SetupFuncs(std::function<void __cdecl(short,unsigned short)> sendGlobal_) // 0x1071FE20
		{
			mangled_x86(MANGLED_TODO, "?SetupFuncs@HsGlobalSync@Server@@YAXV?$function@$$A6AXFG@Z@std@@@Z");
			// std::function<void __cdecl(short,unsigned short)> sendGlobal_;
			todo("implement");
			_sub_1071FE20(sendGlobal_);
		}
	}
}

/* ---------- private code */

_extern __int32 _sub_1071FAC0(unsigned long);
__int32 FindGlobalSyncState(unsigned long globalIndex) // 0x1071FAC0
{
	// `anonymous-namespace'::FindGlobalSyncState
	// unsigned long globalIndex;
	{
		// unsigned __int32 i;
	}
	todo("implement");
	__int32 __result = _sub_1071FAC0(globalIndex);
	return __result;
}

namespace Server
{
	namespace HsGlobalSync
	{
		_extern void _sub_1071FF70(HsGlobalSyncState *);
		void SynchronizeGlobalInternal(HsGlobalSyncState *global) // 0x1071FF70
		{
			// Server::HsGlobalSync::SynchronizeGlobalInternal
			// HsGlobalSyncState *global;
			// unsigned __int32 needsSyncPlayerMask;
			// unsigned short syncPlayerMask;
			// c_data_array<s_player_datum> *players;
			// Blam::Network::Session *session;
			// unsigned __int32 activePlayerMask;
			{
				// __int32 i;
				{
					// s_player_datum *player;
					// __int32 playerIdx;
				}
			}
			todo("implement");
			_sub_1071FF70(global);
		}
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_player_datum * c_data_array<s_player_datum>::get_absolute(long);
