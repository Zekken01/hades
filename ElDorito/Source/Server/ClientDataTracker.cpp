/* ---------- headers */

#include "Server/ClientDataTracker.hpp"
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
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Network.hpp"
#include "Utils/Bits.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

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
#include <list>
#include <memory>
#include <string>
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
namespace Patches
{
	namespace CustomPackets
	{
		class RawPacketHandler;
	}
}
namespace Patches
{
	namespace Network
	{
		class NetworkSessionListener;
	}
}
namespace Server
{
	namespace ClientDataTracker
	{
		class MyNetworkSessionListener;
		struct ClientData;
		struct ClientInfoData;
	}
}
namespace hades_file_local
{
	class ClientInfoDataPacketHandler;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace ClientDataTracker {}
	using namespace Server::ClientDataTracker;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace CustomPackets {}
	using namespace Patches::CustomPackets;
}

namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class ClientInfoDataPacketHandler :
		public Patches::CustomPackets::PacketHandler<Server::ClientDataTracker::ClientInfoData>
	{
	public:
		virtual void Serialize(Blam::BitStream *, Server::ClientDataTracker::ClientInfoData const *);
		virtual bool Deserialize(Blam::BitStream *, Server::ClientDataTracker::ClientInfoData *);
		virtual void HandlePacket(Blam::Network::ObserverChannel *, Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> const *);
		ClientInfoDataPacketHandler(ClientInfoDataPacketHandler &); /* compiler_generated() */
		ClientInfoDataPacketHandler(ClientInfoDataPacketHandler const &); /* compiler_generated() */
		ClientInfoDataPacketHandler() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		virtual ~ClientInfoDataPacketHandler() = default; /* compiler_generated() */
		ClientInfoDataPacketHandler &operator=(ClientInfoDataPacketHandler &); /* compiler_generated() */
		ClientInfoDataPacketHandler &operator=(ClientInfoDataPacketHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(ClientInfoDataPacketHandler) == 4, "Invalid ClientInfoDataPacketHandler size");
}
using namespace hades_file_local;
namespace Patches
{
	namespace CustomPackets
	{
		typedef Packet<Server::ClientDataTracker::ClientInfoData> ClientInfoDataPacket;
	}
}

// Server::ClientDataTracker::ClientData is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace Server
{
	namespace ClientDataTracker
	{
		extern void Tick();
		extern void Initialize();
		extern bool BroadcastClientInfoData(std::string const &body);
	}
}

bool SendMessagePacket(__int32 peer, Server::ClientDataTracker::ClientInfoData const &message);
bool HostReceivedMessage(Blam::Network::Session *session, __int32 peer, Server::ClientDataTracker::ClientInfoData const &message);
bool SendClientMessage(Blam::Network::Session *session, Server::ClientDataTracker::ClientInfoData const &message);

/* ---------- globals */

namespace Server
{
	namespace ClientDataTracker
	{
		std::unordered_map<int,Server::ClientDataTracker::ClientData> dataMap; // 0x124675A0
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	std::shared_ptr<Patches::CustomPackets::PacketSender<Server::ClientDataTracker::ClientInfoData> > PacketSender; // 0x124675C8
}
using namespace hades_file_local;
namespace Patches { namespace CustomPackets { template<typename TPacket> std::shared_ptr<PacketSender<TPacket> > RegisterPacket(std::string const &name, std::shared_ptr<PacketHandler<TPacket> > handler); } }  // hades: added for 0x10B000B0

/* ---------- public code */

namespace Server
{
	namespace ClientDataTracker
	{
		void MyNetworkSessionListener::SessionCreated() // 0x10B00680
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SessionCreated@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXXZ");
			// Server::ClientDataTracker::MyNetworkSessionListener *const this;
		}

		void MyNetworkSessionListener::SessionDestroyed() // 0x10B006A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SessionDestroyed@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXXZ");
			// Server::ClientDataTracker::MyNetworkSessionListener *const this;
		}

		void MyNetworkSessionListener::PeerAdded(__int32 peerIndex) // 0x10B00300
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PeerAdded@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXH@Z");
			// __int32 peerIndex;
		}

		void MyNetworkSessionListener::PeerRemoved(__int32 peerIndex) // 0x10B00320
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PeerRemoved@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXH@Z");
			// __int32 peerIndex;
		}

		void MyNetworkSessionListener::PlayerAdded(__int32 playerIndex) // 0x10B00340
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerAdded@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXH@Z");
			// __int32 playerIndex;
		}

		void MyNetworkSessionListener::PlayerRemoved(__int32 playerIndex) // 0x10B00360
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerRemoved@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXH@Z");
			// __int32 playerIndex;
		}

		void Tick() // 0x10B006C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ClientDataTracker@Server@@YAXXZ");
			// procedure flags: nofpo
		}

		void Initialize() // 0x10B000B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@ClientDataTracker@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B00229
			// static ...; // 0x10B00220
			// static ...; // 0x10B00208
			// static ...; // 0x10B00200
			// std::shared_ptr<ClientInfoDataPacketHandler> handler;
			// std::shared_ptr<Server::ClientDataTracker::MyNetworkSessionListener> listener;

			auto handler = std::make_shared<hades_file_local::ClientInfoDataPacketHandler>();
			hades_file_local::PacketSender = Patches::CustomPackets::RegisterPacket<ClientInfoData>("eldewrito-test-packet", handler);
			auto listener = std::make_shared<MyNetworkSessionListener>();
			Patches::Network::RegisterSessionListener(listener);
		}

		ClientInfoData::ClientInfoData(std::string const &body) // 0x10AFF060
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0ClientInfoData@ClientDataTracker@Server@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::string const &body;

			memset(this, 0, sizeof(*this));
			strncpy(Body, body.c_str(), sizeof(Body) - 1);
		}
	}
}

namespace Patches
{
	namespace Network
	{
		// mangled_x86(MANGLED_DEFAULT, "??0NetworkSessionListener@Network@Patches@@QAE@XZ"); no body to assert in
	}
}

namespace Patches
{
	namespace CustomPackets
	{
		// mangled_x86(MANGLED_DEFAULT, "??0RawPacketHandler@CustomPackets@Patches@@QAE@XZ"); no body to assert in
		// _inline RawPacketHandler::RawPacketHandler() = default; // 0x10AFF250  // hades: defaulted on its declaration
	}
}

namespace Server
{
	namespace ClientDataTracker
	{
		bool BroadcastClientInfoData(std::string const &body) // 0x10AFFCF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BroadcastClientInfoData@ClientDataTracker@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10AFFDA4
			// static ...; // 0x10AFFD98
			// static ...; // 0x10AFFD90
			// std::string const &body;
			// Blam::Network::Session *session;
			// Server::ClientDataTracker::ClientInfoData message;

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished())
				return false;
			Server::ClientDataTracker::ClientInfoData message(body);
			return SendClientMessage(session, message);
		}

	}
}

/* ---------- private code */

_inline void ClientInfoDataPacketHandler::Serialize(Blam::BitStream *stream, Server::ClientDataTracker::ClientInfoData const *data) // 0x10B00590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Serialize@ClientInfoDataPacketHandler@hades_file_local@@UAEXPAVBitStream@Blam@@PBUClientInfoData@ClientDataTracker@Server@@@Z");
	// `anonymous-namespace'::ClientInfoDataPacketHandler::Serialize
	// Server::ClientDataTracker::ClientInfoData const *data;

	stream->WriteString<char, 4096>(data->Body);
}

_inline bool ClientInfoDataPacketHandler::Deserialize(Blam::BitStream *stream, Server::ClientDataTracker::ClientInfoData *data) // 0x10AFFDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Deserialize@ClientInfoDataPacketHandler@hades_file_local@@UAE_NPAVBitStream@Blam@@PAUClientInfoData@ClientDataTracker@Server@@@Z");
	// `anonymous-namespace'::ClientInfoDataPacketHandler::Deserialize
	// Server::ClientDataTracker::ClientInfoData *data;

	memset(data, 0, sizeof(Server::ClientDataTracker::ClientInfoData));

	if (!stream->ReadString<char, 4096>(data->Body))
	{
		return false;
	}

	return true;
}

_inline void ClientInfoDataPacketHandler::HandlePacket(Blam::Network::ObserverChannel *sender, Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> const *packet) // 0x10AFFF60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandlePacket@ClientInfoDataPacketHandler@hades_file_local@@UAEXPAUObserverChannel@Network@Blam@@PBU?$Packet@UClientInfoData@ClientDataTracker@Server@@@CustomPackets@Patches@@@Z");
	// `anonymous-namespace'::ClientInfoDataPacketHandler::HandlePacket
	// Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> const *packet;
	// __int32 peer;
	// Blam::Network::Session *session;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session)
	{
		return;
	}

	__int32 peer = session->GetChannelPeer(sender);
	if (peer < 0)
	{
		return;
	}

	if (session->IsHost())
	{
		HostReceivedMessage(session, peer, packet->Data);
	}
}

bool SendMessagePacket(__int32 peer, Server::ClientDataTracker::ClientInfoData const &message) // 0x10B00470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SendMessagePacket@@YA_NHABUClientInfoData@ClientDataTracker@Server@@@Z");
	// `anonymous-namespace'::SendMessagePacket
	// static ...; // 0x10B00540
	// static ...; // 0x10B00538
	// __int32 peer;
	// Server::ClientDataTracker::ClientInfoData const &message;
	// Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> packet;

	if (peer < 0)
		return false;
	auto packet = hades_file_local::PacketSender->New();
	memcpy(&packet.Data, &message, sizeof(message));
	hades_file_local::PacketSender->Send(peer, packet);
	return true;
}

bool HostReceivedMessage(Blam::Network::Session *session, __int32 peer, Server::ClientDataTracker::ClientInfoData const &message) // 0x10B00090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HostReceivedMessage@@YA_NPAUSession@Network@Blam@@HABUClientInfoData@ClientDataTracker@Server@@@Z");
	// `anonymous-namespace'::HostReceivedMessage
	// Server::ClientDataTracker::ClientInfoData const &message;

	return true;
}

bool SendClientMessage(Blam::Network::Session *session, Server::ClientDataTracker::ClientInfoData const &message) // 0x10B003E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SendClientMessage@@YA_NPAUSession@Network@Blam@@ABUClientInfoData@ClientDataTracker@Server@@@Z");
	// `anonymous-namespace'::SendClientMessage
	// Server::ClientDataTracker::ClientInfoData const &message;

	if (session->IsHost())
	{
		return HostReceivedMessage(session, session->MembershipInfo.LocalPeerIndex, message);
	}
	return SendMessagePacket(session->MembershipInfo.HostPeerIndex, message);
}

// mangled_x86(MANGLED_DEFAULT, "??0ClientInfoDataPacketHandler@hades_file_local@@QAE@XZ"); no body to assert in
// _inline ClientInfoDataPacketHandler::ClientInfoDataPacketHandler() = default; // 0x10AFF100  // hades: defaulted on its declaration


/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> Patches::CustomPackets::PacketSender<Server::ClientDataTracker::ClientInfoData>::New() const;
template Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData>::Packet(unsigned __int32);
template Patches::CustomPackets::PacketSender<Server::ClientDataTracker::ClientInfoData>::PacketSender(unsigned __int32);
template __int32 Patches::CustomPackets::PacketHandler<Server::ClientDataTracker::ClientInfoData>::GetMaxRawPacketSize() const;
template __int32 Patches::CustomPackets::PacketHandler<Server::ClientDataTracker::ClientInfoData>::GetMinRawPacketSize() const;
template bool Patches::CustomPackets::PacketHandler<Server::ClientDataTracker::ClientInfoData>::DeserializeRawPacket(Blam::BitStream *, __int32, void *);
template unsigned __int32 Blam::BitStream::ReadUnsigned<unsigned int>(unsigned __int32, unsigned __int32);
template void Blam::BitStream::WriteUnsigned<unsigned __int64>(unsigned long long, unsigned long long, unsigned long long);
template void Patches::CustomPackets::PacketHandler<Server::ClientDataTracker::ClientInfoData>::HandleRawPacket(Blam::Network::ObserverChannel *, void const *);
template void Patches::CustomPackets::PacketHandler<Server::ClientDataTracker::ClientInfoData>::SerializeRawPacket(Blam::BitStream *, __int32, void const *);
template void Patches::CustomPackets::PacketSender<Server::ClientDataTracker::ClientInfoData>::Send(__int32, Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> const &) const;

/* ---------- explicit instantiations */
template Patches::CustomPackets::PacketHandler<Server::ClientDataTracker::ClientInfoData>::PacketHandler();
