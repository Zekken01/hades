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
namespace
{
	class ClientInfoDataPacketHandler;
}

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

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace
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
		extern bool BroadcastClientInfoData(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body);
	}
}

/* ---------- globals */

namespace Server
{
	namespace ClientDataTracker
	{
		extern std::unordered_map<int,Server::ClientDataTracker::ClientData,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,Server::ClientDataTracker::ClientData> > > dataMap; // 0x124675A0
	}
}

/* ---------- private variables */

namespace
{
	extern std::shared_ptr<Patches::CustomPackets::PacketSender<Server::ClientDataTracker::ClientInfoData> > PacketSender; // 0x124675C8
}
/* ---------- public code */

namespace Server
{
	namespace ClientDataTracker
	{
		_extern void _sub_10B00680(Server::ClientDataTracker::MyNetworkSessionListener *const);
		void MyNetworkSessionListener::SessionCreated() // 0x10B00680
		{
			mangled_x86(MANGLED_TODO, "?SessionCreated@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXXZ");
			// Server::ClientDataTracker::MyNetworkSessionListener *const this;
			todo("implement");
			_sub_10B00680(this);
		}

		_extern void _sub_10B006A0(Server::ClientDataTracker::MyNetworkSessionListener *const);
		void MyNetworkSessionListener::SessionDestroyed() // 0x10B006A0
		{
			mangled_x86(MANGLED_TODO, "?SessionDestroyed@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXXZ");
			// Server::ClientDataTracker::MyNetworkSessionListener *const this;
			todo("implement");
			_sub_10B006A0(this);
		}

		_extern void _sub_10B00300(Server::ClientDataTracker::MyNetworkSessionListener *const, __int32);
		void MyNetworkSessionListener::PeerAdded(__int32 peerIndex) // 0x10B00300
		{
			mangled_x86(MANGLED_TODO, "?PeerAdded@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXH@Z");
			// __int32 peerIndex;
			todo("implement");
			_sub_10B00300(this, peerIndex);
		}

		_extern void _sub_10B00320(Server::ClientDataTracker::MyNetworkSessionListener *const, __int32);
		void MyNetworkSessionListener::PeerRemoved(__int32 peerIndex) // 0x10B00320
		{
			mangled_x86(MANGLED_TODO, "?PeerRemoved@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXH@Z");
			// __int32 peerIndex;
			todo("implement");
			_sub_10B00320(this, peerIndex);
		}

		_extern void _sub_10B00340(Server::ClientDataTracker::MyNetworkSessionListener *const, __int32);
		void MyNetworkSessionListener::PlayerAdded(__int32 playerIndex) // 0x10B00340
		{
			mangled_x86(MANGLED_TODO, "?PlayerAdded@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXH@Z");
			// __int32 playerIndex;
			todo("implement");
			_sub_10B00340(this, playerIndex);
		}

		_extern void _sub_10B00360(Server::ClientDataTracker::MyNetworkSessionListener *const, __int32);
		void MyNetworkSessionListener::PlayerRemoved(__int32 playerIndex) // 0x10B00360
		{
			mangled_x86(MANGLED_TODO, "?PlayerRemoved@MyNetworkSessionListener@ClientDataTracker@Server@@UAEXH@Z");
			// __int32 playerIndex;
			todo("implement");
			_sub_10B00360(this, playerIndex);
		}

		_extern void _sub_10B006C0();
		void Tick() // 0x10B006C0
		{
			mangled_x86(MANGLED_TODO, "?Tick@ClientDataTracker@Server@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10B006C0();
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

		extern ClientInfoData* _sub_10AFF060(Server::ClientDataTracker::ClientInfoData *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		ClientInfoData::ClientInfoData(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body) // 0x10AFF060
		{
			mangled_x86(MANGLED_TODO, "??0ClientInfoData@ClientDataTracker@Server@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
			todo("implement");
			_sub_10AFF060(this, body);
		}
	}
}

namespace Patches
{
	namespace Network
	{
		extern NetworkSessionListener* _sub_10AFF1C0(Patches::Network::NetworkSessionListener *const);
		_inline NetworkSessionListener::NetworkSessionListener() // 0x10AFF1C0
		{
			mangled_x86(MANGLED_TODO, "??0NetworkSessionListener@Network@Patches@@QAE@XZ");
			// Patches::Network::NetworkSessionListener *const this;
			compiler_generated();
			todo("implement");
			_sub_10AFF1C0(this);
		}
	}
}

namespace Patches
{
	namespace CustomPackets
	{
		extern RawPacketHandler* _sub_10AFF250(Patches::CustomPackets::RawPacketHandler *const);
		_inline RawPacketHandler::RawPacketHandler() // 0x10AFF250
		{
			mangled_x86(MANGLED_TODO, "??0RawPacketHandler@CustomPackets@Patches@@QAE@XZ");
			// Patches::CustomPackets::RawPacketHandler *const this;
			compiler_generated();
			todo("implement");
			_sub_10AFF250(this);
		}
	}
}

namespace Server
{
	namespace ClientDataTracker
	{
		_extern bool _sub_10AFFCF0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool BroadcastClientInfoData(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body) // 0x10AFFCF0
		{
			mangled_x86(MANGLED_TODO, "?BroadcastClientInfoData@ClientDataTracker@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10AFFDA4
			// static ...; // 0x10AFFD98
			// static ...; // 0x10AFFD90
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
			// Blam::Network::Session *session;
			// Server::ClientDataTracker::ClientInfoData message;
			todo("implement");
			bool __result = _sub_10AFFCF0(body);
			return __result;
		}

		_extern void _sub_10AFF830(Server::ClientDataTracker::MyNetworkSessionListener *const);
		_inline MyNetworkSessionListener::~MyNetworkSessionListener() // 0x10AFF830
		{
			mangled_x86(MANGLED_TODO, "??1MyNetworkSessionListener@ClientDataTracker@Server@@UAE@XZ");
			// Server::ClientDataTracker::MyNetworkSessionListener *const this;
			compiler_generated();
			todo("implement");
			_sub_10AFF830(this);
		}
	}
}

/* ---------- private code */
