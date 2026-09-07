/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
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
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/HsGlobalSync.hpp"
#include "Utils/Bits.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <limits>
#include <list>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Blam
{
	class BitStream;
}
namespace Blam
{
	namespace Network
	{
		struct ObserverChannel;
		struct Session;
	}
}
namespace Modules
{
	struct Command;
}
namespace
{
	struct SynchronizationBinding;
	class SyncUpdateHandler;
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace CustomPackets {}
	using namespace Patches::CustomPackets;
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

namespace
{
	struct SynchronizationBinding
	{
		unsigned __int32 ID; // 0x0
		Modules::Command *ServerVariable; // 0x4
		Modules::Command *ClientVariable; // 0x8
		std::bitset<17> SynchronizedPeers; // 0xC
		SynchronizationBinding(); /* compiler_generated() */
	};
	static_assert(sizeof(SynchronizationBinding) == 16, "Invalid SynchronizationBinding size");

	//@@anonymous-namespace@@
	// SyncUpdatePacketVar is defined in hades/recovered_types.h, which the synthesised
	// templates in hades/recovered_templates.h inherit from.

	//@@anonymous-namespace@@

	//@@anonymous-namespace@@

	//@@anonymous-namespace@@

	//@@anonymous-namespace@@
	#pragma pack(push, 4)
	class SyncUpdateHandler :
		public Patches::CustomPackets::VariadicPacketHandler<SyncUpdatePacketData,SyncUpdatePacketVar>
	{
	public:
		SyncUpdateHandler(SyncUpdateHandler &); /* compiler_generated() */
		SyncUpdateHandler(SyncUpdateHandler const &); /* compiler_generated() */
		SyncUpdateHandler();
		virtual void Serialize(Blam::BitStream *, SyncUpdatePacketData const *, __int32, SyncUpdatePacketVar const *);
		virtual bool Deserialize(Blam::BitStream *, SyncUpdatePacketData *, __int32, SyncUpdatePacketVar *);
		virtual void HandlePacket(Blam::Network::ObserverChannel *, Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> const *);
		virtual ~SyncUpdateHandler(); /* compiler_generated() */
		SyncUpdateHandler &operator=(SyncUpdateHandler &); /* compiler_generated() */
		SyncUpdateHandler &operator=(SyncUpdateHandler const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(SyncUpdateHandler) == 12, "Invalid SyncUpdateHandler size");

}
typedef unsigned __int32 SyncID;

namespace
{

}
/* ---------- prototypes */

namespace Server
{
	namespace VariableSynchronization
	{
		extern void Initialize();
		extern void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable);
		extern void Tick();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Server
{
	namespace VariableSynchronization
	{
		_extern void _sub_10C3CB00();
		void Initialize() // 0x10C3CB00
		{
			mangled_x86(MANGLED_TODO, "?Initialize@VariableSynchronization@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C3CC28
			// static ...; // 0x10C3CC1C
			// static ...; // 0x10C3CC14
			// std::shared_ptr<SyncUpdateHandler> updateHandler;
			todo("implement");
			_sub_10C3CB00();
		}

		_extern void _sub_10C3D8F0(Modules::Command *, Modules::Command *);
		void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable) // 0x10C3D8F0
		{
			mangled_x86(MANGLED_TODO, "?Synchronize@VariableSynchronization@Server@@YAXPAUCommand@Modules@@0@Z");
			// static ...; // 0x10C3D9B4
			// static ...; // 0x10C3D9AC
			// Modules::Command *serverVariable;
			// Modules::Command *clientVariable;
			// SynchronizationBinding binding;
			todo("implement");
			_sub_10C3D8F0(serverVariable, clientVariable);
		}

		_extern void _sub_10C3DE10();
		void Tick() // 0x10C3DE10
		{
			mangled_x86(MANGLED_TODO, "?Tick@VariableSynchronization@Server@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			todo("implement");
			_sub_10C3DE10();
		}
	}
}

/* ---------- private code */
