/* ---------- headers */

#include "Server/Voting/VotingPackets.hpp"
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
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "Utils/Bits.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include <ios>
#include <iosfwd>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
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
		struct SessionMembership;
	}
}
namespace Server
{
	namespace Voting
	{
		class VotingMessageHandler;
		enum VotingMessageType : unsigned __int32;
		struct VotingMessage;
	}
}
namespace
{
	class VotingMessagePacketHandler;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Voting {}
	using namespace Server::Voting;
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
	class VotingMessagePacketHandler :
		public Patches::CustomPackets::PacketHandler<Server::Voting::VotingMessage>
	{
	public:
		virtual void Serialize(Blam::BitStream *, Server::Voting::VotingMessage const *);
		virtual bool Deserialize(Blam::BitStream *, Server::Voting::VotingMessage *);
		virtual void HandlePacket(Blam::Network::ObserverChannel *, Patches::CustomPackets::Packet<Server::Voting::VotingMessage> const *);
		VotingMessagePacketHandler(VotingMessagePacketHandler &); /* compiler_generated() */
		VotingMessagePacketHandler(VotingMessagePacketHandler const &); /* compiler_generated() */
		VotingMessagePacketHandler(); /* compiler_generated() */
		virtual ~VotingMessagePacketHandler(); /* compiler_generated() */
		VotingMessagePacketHandler &operator=(VotingMessagePacketHandler &); /* compiler_generated() */
		VotingMessagePacketHandler &operator=(VotingMessagePacketHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(VotingMessagePacketHandler) == 4, "Invalid VotingMessagePacketHandler size");
}
namespace Patches
{
	namespace CustomPackets
	{
		typedef Packet<Server::Voting::VotingMessage> VotingMessagePacket;
		typedef unsigned __int32 PacketGuid;
	}
}

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern void AddMessageHandler(std::shared_ptr<Server::Voting::VotingMessageHandler> handler);
		extern void InitializePackets();
		extern bool BroadcastVotingMessage(Server::Voting::VotingMessage &message);
		extern bool SendVotingMessageToPeer(Server::Voting::VotingMessage &message, __int32 peer);
		extern bool SendVoteToHost(__int32 const vote);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern std::shared_ptr<Patches::CustomPackets::PacketSender<Server::Voting::VotingMessage> > VotingPacketSender; // 0x1246B6A8
	extern std::vector<std::shared_ptr<Server::Voting::VotingMessageHandler>,std::allocator<std::shared_ptr<Server::Voting::VotingMessageHandler> > > votingMessageHandlers; // 0x1246B698
}
namespace Server
{
	namespace Voting
	{
		namespace
		{
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x1246B4D8
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x1246B5B8
		}
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		extern VotingMessage* _sub_10C47FC0(Server::Voting::VotingMessage *const, Server::Voting::VotingMessageType);
		VotingMessage::VotingMessage(Server::Voting::VotingMessageType type) // 0x10C47FC0
		{
			mangled_x86(MANGLED_TODO, "??0VotingMessage@Voting@Server@@QAE@W4VotingMessageType@12@@Z");
			// Server::Voting::VotingMessageType type;
			todo("implement");
			_sub_10C47FC0(this, type);
		}

		_extern void _sub_10C48740(std::shared_ptr<Server::Voting::VotingMessageHandler>);
		void AddMessageHandler(std::shared_ptr<Server::Voting::VotingMessageHandler> handler) // 0x10C48740
		{
			mangled_x86(MANGLED_TODO, "?AddMessageHandler@Voting@Server@@YAXV?$shared_ptr@VVotingMessageHandler@Voting@Server@@@std@@@Z");
			// std::shared_ptr<Server::Voting::VotingMessageHandler> handler;
			todo("implement");
			_sub_10C48740(handler);
		}

		_extern void _sub_10C48D70();
		void InitializePackets() // 0x10C48D70
		{
			mangled_x86(MANGLED_TODO, "?InitializePackets@Voting@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C48E98
			// static ...; // 0x10C48E8C
			// static ...; // 0x10C48E84
			// std::shared_ptr<VotingMessagePacketHandler> handler;
			todo("implement");
			_sub_10C48D70();
		}

		_extern bool _sub_10C487E0(Server::Voting::VotingMessage &);
		bool BroadcastVotingMessage(Server::Voting::VotingMessage &message) // 0x10C487E0
		{
			mangled_x86(MANGLED_TODO, "?BroadcastVotingMessage@Voting@Server@@YA_NAAUVotingMessage@12@@Z");
			// Server::Voting::VotingMessage &message;
			// Blam::Network::SessionMembership *membership;
			// Blam::Network::Session *session;
			{
				// __int32 peer;
			}
			todo("implement");
			bool __result = _sub_10C487E0(message);
			return __result;
		}

		_extern bool _sub_10C49400(Server::Voting::VotingMessage &, __int32);
		bool SendVotingMessageToPeer(Server::Voting::VotingMessage &message, __int32 peer) // 0x10C49400
		{
			mangled_x86(MANGLED_TODO, "?SendVotingMessageToPeer@Voting@Server@@YA_NAAUVotingMessage@12@H@Z");
			// __int32 peer;
			// Blam::Network::Session *session;
			todo("implement");
			bool __result = _sub_10C49400(message, peer);
			return __result;
		}

		_extern bool _sub_10C491C0(__int32 const);
		bool SendVoteToHost(__int32 const vote) // 0x10C491C0
		{
			mangled_x86(MANGLED_TODO, "?SendVoteToHost@Voting@Server@@YA_NH@Z");
			// static ...; // 0x10C49270
			// static ...; // 0x10C49264
			// static ...; // 0x10C4925C
			// __int32 const vote;
			// Blam::Network::Session *session;
			// Server::Voting::VotingMessage message;
			todo("implement");
			bool __result = _sub_10C491C0(vote);
			return __result;
		}
	}
}

/* ---------- private code */
