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
		ClientInfoDataPacketHandler(); /* compiler_generated() */
		virtual ~ClientInfoDataPacketHandler(); /* compiler_generated() */
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
		extern std::unordered_map<int,Server::ClientDataTracker::ClientData,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,Server::ClientDataTracker::ClientData> > > dataMap; // 0x124675A0
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	extern std::shared_ptr<Patches::CustomPackets::PacketSender<Server::ClientDataTracker::ClientInfoData> > PacketSender; // 0x124675C8
}
using namespace hades_file_local;
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

		_extern void _sub_10B000B0();
		void Initialize() // 0x10B000B0
		{
			mangled_x86(MANGLED_TODO, "?Initialize@ClientDataTracker@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B00229
			// static ...; // 0x10B00220
			// static ...; // 0x10B00208
			// static ...; // 0x10B00200
			// std::shared_ptr<ClientInfoDataPacketHandler> handler;
			// std::shared_ptr<Server::ClientDataTracker::MyNetworkSessionListener> listener;
			todo("implement");
			_sub_10B000B0();
		}

		extern ClientInfoData* _sub_10AFF060(Server::ClientDataTracker::ClientInfoData *const, std::string const &);
		ClientInfoData::ClientInfoData(std::string const &body) // 0x10AFF060
		{
			mangled_x86(MANGLED_TODO, "??0ClientInfoData@ClientDataTracker@Server@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::string const &body;
			todo("implement");
			_sub_10AFF060(this, body);
		}
	}
}

namespace Patches
{
	namespace Network
	{
		_inline NetworkSessionListener::NetworkSessionListener() // 0x10AFF1C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0NetworkSessionListener@Network@Patches@@QAE@XZ");
			// Patches::Network::NetworkSessionListener *const this;

			compiler_generated();
		}
	}
}

namespace Patches
{
	namespace CustomPackets
	{
		_inline RawPacketHandler::RawPacketHandler() // 0x10AFF250
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0RawPacketHandler@CustomPackets@Patches@@QAE@XZ");
			// Patches::CustomPackets::RawPacketHandler *const this;

			compiler_generated();
		}
	}
}

namespace Server
{
	namespace ClientDataTracker
	{
		_extern bool _sub_10AFFCF0(std::string const &);
		bool BroadcastClientInfoData(std::string const &body) // 0x10AFFCF0
		{
			mangled_x86(MANGLED_TODO, "?BroadcastClientInfoData@ClientDataTracker@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10AFFDA4
			// static ...; // 0x10AFFD98
			// static ...; // 0x10AFFD90
			// std::string const &body;
			// Blam::Network::Session *session;
			// Server::ClientDataTracker::ClientInfoData message;
			todo("implement");
			bool __result = _sub_10AFFCF0(body);
			return __result;
		}

		_inline MyNetworkSessionListener::~MyNetworkSessionListener() // 0x10AFF830
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1MyNetworkSessionListener@ClientDataTracker@Server@@UAE@XZ");
			// Server::ClientDataTracker::MyNetworkSessionListener *const this;

			compiler_generated();
		}
	}
}

/* ---------- private code */

_extern void _sub_10B00590(ClientInfoDataPacketHandler *const, Blam::BitStream *, Server::ClientDataTracker::ClientInfoData const *);
_inline void ClientInfoDataPacketHandler::Serialize(Blam::BitStream *stream, Server::ClientDataTracker::ClientInfoData const *data) // 0x10B00590
{
	// `anonymous-namespace'::ClientInfoDataPacketHandler::Serialize
	// Server::ClientDataTracker::ClientInfoData const *data;
	todo("implement");
	_sub_10B00590(this, stream, data);
}

_extern bool _sub_10AFFDE0(ClientInfoDataPacketHandler *const, Blam::BitStream *, Server::ClientDataTracker::ClientInfoData *);
_inline bool ClientInfoDataPacketHandler::Deserialize(Blam::BitStream *stream, Server::ClientDataTracker::ClientInfoData *data) // 0x10AFFDE0
{
	// `anonymous-namespace'::ClientInfoDataPacketHandler::Deserialize
	// Server::ClientDataTracker::ClientInfoData *data;
	todo("implement");
	bool __result = _sub_10AFFDE0(this, stream, data);
	return __result;
}

_extern void _sub_10AFFF60(ClientInfoDataPacketHandler *const, Blam::Network::ObserverChannel *, Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> const *);
_inline void ClientInfoDataPacketHandler::HandlePacket(Blam::Network::ObserverChannel *sender, Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> const *packet) // 0x10AFFF60
{
	// `anonymous-namespace'::ClientInfoDataPacketHandler::HandlePacket
	// Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> const *packet;
	// __int32 peer;
	// Blam::Network::Session *session;
	todo("implement");
	_sub_10AFFF60(this, sender, packet);
}

_extern bool _sub_10B00470(__int32, Server::ClientDataTracker::ClientInfoData const &);
bool SendMessagePacket(__int32 peer, Server::ClientDataTracker::ClientInfoData const &message) // 0x10B00470
{
	// `anonymous-namespace'::SendMessagePacket
	// static ...; // 0x10B00540
	// static ...; // 0x10B00538
	// __int32 peer;
	// Server::ClientDataTracker::ClientInfoData const &message;
	// Patches::CustomPackets::Packet<Server::ClientDataTracker::ClientInfoData> packet;
	todo("implement");
	bool __result = _sub_10B00470(peer, message);
	return __result;
}

bool HostReceivedMessage(Blam::Network::Session *session, __int32 peer, Server::ClientDataTracker::ClientInfoData const &message) // 0x10B00090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HostReceivedMessage@@YA_NPAUSession@Network@Blam@@HABUClientInfoData@ClientDataTracker@Server@@@Z");
	// `anonymous-namespace'::HostReceivedMessage
	// Server::ClientDataTracker::ClientInfoData const &message;

	return true;
}

_extern bool _sub_10B003E0(Blam::Network::Session *, Server::ClientDataTracker::ClientInfoData const &);
bool SendClientMessage(Blam::Network::Session *session, Server::ClientDataTracker::ClientInfoData const &message) // 0x10B003E0
{
	// `anonymous-namespace'::SendClientMessage
	// Server::ClientDataTracker::ClientInfoData const &message;
	todo("implement");
	bool __result = _sub_10B003E0(session, message);
	return __result;
}

_inline ClientInfoDataPacketHandler::ClientInfoDataPacketHandler() // 0x10AFF100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0ClientInfoDataPacketHandler@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::ClientInfoDataPacketHandler::ClientInfoDataPacketHandler
	// ClientInfoDataPacketHandler *const this;

	compiler_generated();
}

_inline ClientInfoDataPacketHandler::~ClientInfoDataPacketHandler() // 0x10AFF7E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1ClientInfoDataPacketHandler@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::ClientInfoDataPacketHandler::~ClientInfoDataPacketHandler
	// ClientInfoDataPacketHandler *const this;

	compiler_generated();
}

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
