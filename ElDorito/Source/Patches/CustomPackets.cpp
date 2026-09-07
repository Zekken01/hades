/* ---------- headers */

#include "Patches/CustomPackets.hpp"
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
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
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
#include <unordered_map>
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
namespace Patches
{
	namespace CustomPackets
	{
		class RawPacketHandler;
	}
}
namespace
{
	struct CustomPacket;
}

namespace Utils {}
using namespace ::Utils;
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
	#pragma pack(push, 4)
	struct CustomPacket
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > Name; // 0x0
		std::shared_ptr<Patches::CustomPackets::RawPacketHandler> Handler; // 0x1C
		CustomPacket(CustomPacket &); /* compiler_generated() */
		CustomPacket(CustomPacket const &); /* compiler_generated() */
		CustomPacket(); /* compiler_generated() */
		~CustomPacket(); /* compiler_generated() */
		CustomPacket &operator=(CustomPacket &); /* compiler_generated() */
		CustomPacket &operator=(CustomPacket const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(CustomPacket) == 36, "Invalid CustomPacket size");

}
/* ---------- prototypes */

namespace Patches
{
	namespace CustomPackets
	{
		extern void ApplyAll();
		extern void SendPacket(__int32 targetPeer, void const *packet, __int32 packetSize);
		extern unsigned __int32 RegisterPacketImpl(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::shared_ptr<Patches::CustomPackets::RawPacketHandler> handler);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace CustomPackets
	{
		_extern void _sub_10A4FBF0();
		void ApplyAll() // 0x10A4FBF0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@CustomPackets@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A4FBF0();
		}

		_extern void _sub_10A50660(__int32, void const *, __int32);
		void SendPacket(__int32 targetPeer, void const *packet, __int32 packetSize) // 0x10A50660
		{
			mangled_x86(MANGLED_TODO, "?SendPacket@CustomPackets@Patches@@YAXHPBXH@Z");
			// __int32 packetSize;
			// __int32 channelIndex;
			// Blam::Network::Session *session;
			todo("implement");
			_sub_10A50660(targetPeer, packet, packetSize);
		}

		_extern unsigned __int32 _sub_10A50480(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::shared_ptr<Patches::CustomPackets::RawPacketHandler>);
		unsigned __int32 RegisterPacketImpl(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::shared_ptr<Patches::CustomPackets::RawPacketHandler> handler) // 0x10A50480
		{
			mangled_x86(MANGLED_TODO, "?RegisterPacketImpl@CustomPackets@Patches@@YAIABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$shared_ptr@VRawPacketHandler@CustomPackets@Patches@@@4@@Z");
			// static ...; // 0x10A505F0
			// static ...; // 0x10A505D8
			// static ...; // 0x10A505D0
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name;
			// std::shared_ptr<Patches::CustomPackets::RawPacketHandler> handler;
			// unsigned __int32 guid;
			// CustomPacket packet;
			todo("implement");
			unsigned __int32 __result = _sub_10A50480(name, handler);
			return __result;
		}
	}
}

/* ---------- private code */
