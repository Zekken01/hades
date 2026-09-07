/* ---------- headers */

#include "Patches/CustomPackets.hpp"
#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
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
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/NameValueTable.hpp"

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
	class BitStream;
}
namespace Blam
{
	namespace Network
	{
		struct ObserverChannel;
		struct PacketTable;
		struct Session;
	}
}
namespace Patches
{
	namespace CustomPackets
	{
		class RawPacketHandler;
		struct PacketBase;
	}
}
namespace hades_file_local
{
	struct CustomPacket;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
using namespace hades_file_local;
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

void InitializePacketsHook();
CustomPacket *LookUpPacketType(unsigned __int32 guid);
void SerializeCustomPacket(Blam::BitStream *stream, __int32 packetSize, void const *packet);
bool DeserializeCustomPacket(Blam::BitStream *stream, __int32 packetSize, void *packet);
bool HandleCustomPacket(__int32 id, Blam::Network::ObserverChannel *sender, void const *packet);
void HandlePacketHook();

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

extern CustomPacket* _sub_10A4ED70(CustomPacket *const);
_inline CustomPacket::CustomPacket() // 0x10A4ED70
{
	// `anonymous-namespace'::CustomPacket::CustomPacket
	// CustomPacket *const this;
	compiler_generated();
	todo("implement");
	_sub_10A4ED70(this);
}

_extern void _sub_10A500D0();
void InitializePacketsHook() // 0x10A500D0
{
	// `anonymous-namespace'::InitializePacketsHook
	// procedure flags: nofpo
	// Blam::Network::PacketTable *customPacketTable;
	// __int32 const maxSize;
	// __int32 packetCount;
	// char const *name;
	// __int32 minSize;
	todo("implement");
	_sub_10A500D0();
}

_extern void _sub_10A4F420(CustomPacket *const);
_inline CustomPacket::~CustomPacket() // 0x10A4F420
{
	// `anonymous-namespace'::CustomPacket::~CustomPacket
	// CustomPacket *const this;
	compiler_generated();
	todo("implement");
	_sub_10A4F420(this);
}

extern CustomPacket &_sub_10A4F5E0(CustomPacket *const, CustomPacket const &);
_inline CustomPacket &CustomPacket::operator=(CustomPacket const &__that) // 0x10A4F5E0
{
	// `anonymous-namespace'::CustomPacket::operator=
	// CustomPacket const &__that;
	compiler_generated();
	todo("implement");
	CustomPacket & __result = _sub_10A4F5E0(this, __that);
	return __result;
}

extern CustomPacket *_sub_10A50360(unsigned __int32);
CustomPacket *LookUpPacketType(unsigned __int32 guid) // 0x10A50360
{
	// `anonymous-namespace'::LookUpPacketType
	// static ...; // 0x10A50444
	// static ...; // 0x10A50438
	// static ...; // 0x10A50430
	// unsigned __int32 guid;
	// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,CustomPacket> > > > it;
	todo("implement");
	CustomPacket * __result = _sub_10A50360(guid);
	return __result;
}

_extern void _sub_10A50710(Blam::BitStream *, __int32, void const *);
void SerializeCustomPacket(Blam::BitStream *stream, __int32 packetSize, void const *packet) // 0x10A50710
{
	// `anonymous-namespace'::SerializeCustomPacket
	// void const *packet;
	// Patches::CustomPackets::PacketBase const *packetBase;
	// __int32 maxSize;
	// __int32 minSize;
	// CustomPacket *type;
	// function call : __int32 () const
	// function call : __int32 () const
	// function call : void (Blam::BitStream *, __int32, void const *)
	todo("implement");
	_sub_10A50710(stream, packetSize, packet);
}

_extern bool _sub_10A4FE30(Blam::BitStream *, __int32, void *);
bool DeserializeCustomPacket(Blam::BitStream *stream, __int32 packetSize, void *packet) // 0x10A4FE30
{
	// `anonymous-namespace'::DeserializeCustomPacket
	// void *packet;
	// Patches::CustomPackets::PacketBase *packetBase;
	// __int32 maxSize;
	// __int32 minSize;
	// CustomPacket *type;
	// function call : __int32 () const
	// function call : __int32 () const
	// function call : bool (Blam::BitStream *, __int32, void *)
	todo("implement");
	bool __result = _sub_10A4FE30(stream, packetSize, packet);
	return __result;
}

_extern bool _sub_10A4FFC0(__int32, Blam::Network::ObserverChannel *, void const *);
bool HandleCustomPacket(__int32 id, Blam::Network::ObserverChannel *sender, void const *packet) // 0x10A4FFC0
{
	// `anonymous-namespace'::HandleCustomPacket
	// void const *packet;
	// Patches::CustomPackets::PacketBase const *packetBase;
	// CustomPacket *type;
	// function call : void (Blam::Network::ObserverChannel *, void const *)
	todo("implement");
	bool __result = _sub_10A4FFC0(id, sender, packet);
	return __result;
}

extern void _sub_10A50090();
__declspec(naked) void HandlePacketHook() // 0x10A50090
{
	// `anonymous-namespace'::HandlePacketHook
	// procedure flags: nofpo
// failed:
	todo("implement");
	_sub_10A50090();
}
