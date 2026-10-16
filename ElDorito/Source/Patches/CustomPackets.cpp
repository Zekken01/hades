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
		std::string Name; // 0x0
		std::shared_ptr<Patches::CustomPackets::RawPacketHandler> Handler; // 0x1C
		// CustomPacket(CustomPacket &); /* compiler_generated(): left implicit, as the original's was */
		// CustomPacket(CustomPacket const &); /* compiler_generated(): left implicit, as the original's was */
		CustomPacket() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		~CustomPacket() = default;
		// CustomPacket &operator=(CustomPacket &); /* compiler_generated(): left implicit, as the original's was */
		CustomPacket &operator=(CustomPacket const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(CustomPacket) == 36, "Invalid CustomPacket size");

}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Utils { namespace Cryptography { bool Hash32(std::string const &str, unsigned __int32 *out); } }  // hades: added for 0x10A50480  // hades: added for 0x10A50480

namespace Patches
{
	namespace CustomPackets
	{
		extern void ApplyAll();
		extern void SendPacket(__int32 targetPeer, void const *packet, __int32 packetSize);
		extern unsigned __int32 RegisterPacketImpl(std::string const &name, std::shared_ptr<Patches::CustomPackets::RawPacketHandler> handler);
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

namespace hades_file_local
{
	std::unordered_map<unsigned int,CustomPacket> customPackets; // 0x12458470
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace CustomPackets
	{
		void ApplyAll() // 0x10A4FBF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@CustomPackets@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x9E226, InitializePacketsHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9CAFA, HandlePacketHook).Apply();
		}

		void SendPacket(__int32 targetPeer, void const *packet, __int32 packetSize) // 0x10A50660
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendPacket@CustomPackets@Patches@@YAXHPBXH@Z");
			// __int32 packetSize;
			// __int32 channelIndex;
			// Blam::Network::Session *session;

			auto session = Blam::Network::GetActiveSession();
			if (!session)
				return;

			auto channelIndex = session->MembershipInfo.PeerChannels[targetPeer].ChannelIndex;
			if (channelIndex == -1)
				return;

			session->Observer->ObserverChannelSendMessage(0, channelIndex, false, 0x27, packetSize, packet);
		}

		unsigned __int32 RegisterPacketImpl(std::string const &name, std::shared_ptr<Patches::CustomPackets::RawPacketHandler> handler) // 0x10A50480
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterPacketImpl@CustomPackets@Patches@@YAIABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$shared_ptr@VRawPacketHandler@CustomPackets@Patches@@@4@@Z");
			// static ...; // 0x10A505F0
			// static ...; // 0x10A505D8
			// static ...; // 0x10A505D0
			// std::string const &name;
			// std::shared_ptr<Patches::CustomPackets::RawPacketHandler> handler;
			// unsigned __int32 guid;
			// CustomPacket packet;

			unsigned __int32 guid;
			if (!Utils::Cryptography::Hash32(name, &guid))
				throw std::runtime_error("Failed to generate packet GUID");
			if (LookUpPacketType(guid))
				throw std::runtime_error("Duplicate packet GUID");
			CustomPacket packet;
			packet.Name = name;
			packet.Handler = handler;
			customPackets[guid] = packet;
			return guid;
		}
	}
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??0CustomPacket@hades_file_local@@QAE@XZ"); no body to assert in
// _inline CustomPacket::CustomPacket() = default; // 0x10A4ED70  // hades: defaulted on its declaration

void InitializePacketsHook() // 0x10A500D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitializePacketsHook@@YAXXZ");
	// `anonymous-namespace'::InitializePacketsHook
	// procedure flags: nofpo
	// Blam::Network::PacketTable *customPacketTable;
	// __int32 const maxSize;
	// __int32 packetCount;
	// char const *name;
	// __int32 minSize;

	__int32 packetCount = 40;
	Blam::Network::PacketTable *customPacketTable = new Blam::Network::PacketTable[packetCount];
	Blam::Network::SetPacketTable(customPacketTable);
	memset(customPacketTable, 0, packetCount * sizeof(Blam::Network::PacketTable));
	char const *name = "eldewrito-custom-packet";
	__int32 minSize = 0;
	__int32 const maxSize = 0x7FFFFFFF;
	customPacketTable->Register(39, name, 0, minSize, maxSize, SerializeCustomPacket, DeserializeCustomPacket, 0, 0);
	Patch(0x80022, { 0x28 }).Apply();
}


_inline CustomPacket &CustomPacket::operator=(CustomPacket const &__that) = default; // 0x10A4F5E0

CustomPacket *LookUpPacketType(unsigned __int32 guid) // 0x10A50360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LookUpPacketType@@YAPAUCustomPacket@hades_file_local@@I@Z");
	// `anonymous-namespace'::LookUpPacketType
	// static ...; // 0x10A50444
	// static ...; // 0x10A50438
	// static ...; // 0x10A50430
	// unsigned __int32 guid;
	// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,CustomPacket> > > > it;

	auto it = customPackets.find(guid);
	if (it == customPackets.end())
		return nullptr;
	return &it->second;
}

void SerializeCustomPacket(Blam::BitStream *stream, __int32 packetSize, void const *packet) // 0x10A50710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SerializeCustomPacket@@YAXPAVBitStream@Blam@@HPBX@Z");
	// `anonymous-namespace'::SerializeCustomPacket
	// void const *packet;
	// Patches::CustomPackets::PacketBase const *packetBase;
	// __int32 maxSize;
	// __int32 minSize;
	// CustomPacket *type;
	// function call : __int32 () const
	// function call : __int32 () const
	// function call : void (Blam::BitStream *, __int32, void const *)

	Patches::CustomPackets::PacketBase const *packetBase = static_cast<Patches::CustomPackets::PacketBase const *>(packet);
	stream->WriteBlock(128, packetBase->Header);
	stream->WriteUnsigned<unsigned int>(packetBase->TypeGuid, 32);
	CustomPacket *type = LookUpPacketType(packetBase->TypeGuid);
	if (!type)
		return;
	__int32 minSize = type->Handler->GetMinRawPacketSize();
	__int32 maxSize = type->Handler->GetMaxRawPacketSize();
	if (packetSize < minSize || packetSize > maxSize)
		return;
	type->Handler->SerializeRawPacket(stream, packetSize, packet);
}

bool DeserializeCustomPacket(Blam::BitStream *stream, __int32 packetSize, void *packet) // 0x10A4FE30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DeserializeCustomPacket@@YA_NPAVBitStream@Blam@@HPAX@Z");
	// `anonymous-namespace'::DeserializeCustomPacket
	// void *packet;
	// Patches::CustomPackets::PacketBase *packetBase;
	// __int32 maxSize;
	// __int32 minSize;
	// CustomPacket *type;
	// function call : __int32 () const
	// function call : __int32 () const
	// function call : bool (Blam::BitStream *, __int32, void *)

	if (packetSize < static_cast<__int32>(sizeof(Patches::CustomPackets::PacketBase)))
		return false;
	Patches::CustomPackets::PacketBase *packetBase = static_cast<Patches::CustomPackets::PacketBase *>(packet);
	stream->ReadBlock(128, packetBase->Header);
	packetBase->TypeGuid = stream->ReadUnsigned<unsigned int>(32);
	CustomPacket *type = LookUpPacketType(packetBase->TypeGuid);
	if (!type)
		return false;
	__int32 minSize = type->Handler->GetMinRawPacketSize();
	__int32 maxSize = type->Handler->GetMaxRawPacketSize();
	if (packetSize < minSize || packetSize > maxSize)
		return false;
	return type->Handler->DeserializeRawPacket(stream, packetSize, packet);
}

bool HandleCustomPacket(__int32 id, Blam::Network::ObserverChannel *sender, void const *packet) // 0x10A4FFC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleCustomPacket@@YA_NHPAUObserverChannel@Network@Blam@@PBX@Z");
	// `anonymous-namespace'::HandleCustomPacket
	// void const *packet;
	// Patches::CustomPackets::PacketBase const *packetBase;
	// CustomPacket *type;
	// function call : void (Blam::Network::ObserverChannel *, void const *)

	if (id != 0x27)
	{
		return false;
	}

	Patches::CustomPackets::PacketBase const *packetBase = static_cast<Patches::CustomPackets::PacketBase const *>(packet);
	CustomPacket *type = LookUpPacketType(packetBase->TypeGuid);
	if (!type)
	{
		return false;
	}

	type->Handler->HandleRawPacket(sender, packet);
	return true;
}

__declspec(naked) void HandlePacketHook() // 0x10A50090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandlePacketHook@@YAXXZ");
	// `anonymous-namespace'::HandlePacketHook
	// procedure flags: nofpo
// failed:

	__asm
	{
		mov edx, [ebp + 8]
		cmp dword ptr [edx + 0A10h], 5
		jne Lfailed
		push dword ptr [ebp + 14h]
		push edx
		push edi
		call HandleCustomPacket
		test al, al
		je Lfailed
		push 049CB14h
		ret
		Lfailed:
		mov ecx, [esi + 8]
		push 0
		push 049CAFFh
		ret
	}
}

/* ---------- explicit instantiations */
template class std::unordered_map<unsigned int,CustomPacket>;
template std::_Hash<std::_Umap_traits<unsigned int,CustomPacket,std::_Uhash_compare<unsigned int,std::hash<unsigned int>,std::equal_to<unsigned int> >,std::allocator<std::pair<unsigned int const ,CustomPacket> >,0> >::~_Hash();
template std::pair<unsigned int const ,CustomPacket>::~pair();
template std::unordered_map<unsigned int,CustomPacket>::~unordered_map();
