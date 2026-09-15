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
#include "ChatCommands/ChatCommandMap.hpp"
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

struct begin;
struct end;
namespace Blam
{
	class BitStream;
}
namespace Blam
{
	namespace Network
	{
		struct ObserverChannel;
		struct PlayerSession;
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
namespace hades_file_local
{
	class VotingMessagePacketHandler;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
using namespace hades_file_local;
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

void ReceivedVotingMessage(Blam::Network::Session *session, __int32 peer, Server::Voting::VotingMessage const &message);
bool SendVotingMessagePacket(Blam::Network::Session *session, __int32 peer, Server::Voting::VotingMessage const &message);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::shared_ptr<Patches::CustomPackets::PacketSender<Server::Voting::VotingMessage> > VotingPacketSender; // 0x1246B6A8
	extern std::vector<std::shared_ptr<Server::Voting::VotingMessageHandler> > votingMessageHandlers; // 0x1246B698
}
using namespace hades_file_local;
namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::string const DefaultTypes[8]; // 0x1246B4D8
			extern std::string const DefaultTypeNames[8]; // 0x1246B5B8
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		VotingMessage::VotingMessage(Server::Voting::VotingMessageType type) // 0x10C47FC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0VotingMessage@Voting@Server@@QAE@W4VotingMessageType@12@@Z");
			// Server::Voting::VotingMessageType type;

			memset(this, 0, sizeof(VotingMessage));
			Type = type;
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

		bool BroadcastVotingMessage(Server::Voting::VotingMessage &message) // 0x10C487E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BroadcastVotingMessage@Voting@Server@@YA_NAAUVotingMessage@12@@Z");
			// Server::Voting::VotingMessage &message;
			// Blam::Network::SessionMembership *membership;
			// Blam::Network::Session *session;
				// __int32 peer;

			auto session = Blam::Network::GetActiveSession();
			auto membership = &session->MembershipInfo;
			for (auto peer = membership->FindFirstPeer(); peer >= 0; peer = membership->FindNextPeer(peer))
			{
				if (!SendVotingMessagePacket(session, peer, message))
					return false;
			}
			return true;
		}

		bool SendVotingMessageToPeer(Server::Voting::VotingMessage &message, __int32 peer) // 0x10C49400
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendVotingMessageToPeer@Voting@Server@@YA_NAAUVotingMessage@12@H@Z");
			// __int32 peer;
			// Blam::Network::Session *session;

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			return SendVotingMessagePacket(session, peer, message);
		}

		bool SendVoteToHost(__int32 const vote) // 0x10C491C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendVoteToHost@Voting@Server@@YA_NH@Z");
			// static ...; // 0x10C49270
			// static ...; // 0x10C49264
			// static ...; // 0x10C4925C
			// __int32 const vote;
			// Blam::Network::Session *session;
			// Server::Voting::VotingMessage message;

			auto session = Blam::Network::GetActiveSession();
			if (!session)
				return false;

			VotingMessage message(VotingMessageType::Vote);
			message.Vote = vote;
			return SendVotingMessagePacket(session, session->MembershipInfo.HostPeerIndex, message);
		}
	}
}

/* ---------- private code */

_extern void _sub_10C49460(VotingMessagePacketHandler *const, Blam::BitStream *, Server::Voting::VotingMessage const *);
_inline void VotingMessagePacketHandler::Serialize(Blam::BitStream *stream, Server::Voting::VotingMessage const *data) // 0x10C49460
{
	// `anonymous-namespace'::VotingMessagePacketHandler::Serialize
	// Server::Voting::VotingMessage const *data;
	{
		// __int32 i;
	}
	{
	}
	todo("implement");
	_sub_10C49460(this, stream, data);
}

_extern bool _sub_10C48890(VotingMessagePacketHandler *const, Blam::BitStream *, Server::Voting::VotingMessage *);
_inline bool VotingMessagePacketHandler::Deserialize(Blam::BitStream *stream, Server::Voting::VotingMessage *data) // 0x10C48890
{
	// `anonymous-namespace'::VotingMessagePacketHandler::Deserialize
	// Server::Voting::VotingMessage *data;
	{
		// __int32 i;
	}
	{
	}
	todo("implement");
	bool __result = _sub_10C48890(this, stream, data);
	return __result;
}

_inline void VotingMessagePacketHandler::HandlePacket(Blam::Network::ObserverChannel *sender, Patches::CustomPackets::Packet<Server::Voting::VotingMessage> const *packet) // 0x10C48C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandlePacket@VotingMessagePacketHandler@hades_file_local@@UAEXPAUObserverChannel@Network@Blam@@PBU?$Packet@UVotingMessage@Voting@Server@@@CustomPackets@Patches@@@Z");
	// `anonymous-namespace'::VotingMessagePacketHandler::HandlePacket
	// Patches::CustomPackets::Packet<Server::Voting::VotingMessage> const *packet;
	// Blam::Network::Session *session;

	auto session = Blam::Network::GetActiveSession();
	if (!session)
		return;

	//at this level, it doesnt matter if we are the host or not. If we receive any sort of voting message, handle it
	ReceivedVotingMessage(session, session->GetChannelPeer(sender), packet->Data);
}

_extern void _sub_10C48F50(Blam::Network::Session *, __int32, Server::Voting::VotingMessage const &);
void ReceivedVotingMessage(Blam::Network::Session *session, __int32 peer, Server::Voting::VotingMessage const &message) // 0x10C48F50
{
	// `anonymous-namespace'::ReceivedVotingMessage
	// static ...; // 0x10C490D4
	// Blam::Network::Session *session;
	// __int32 peer;
	// Server::Voting::VotingMessage const &message;
	{
		// Blam::Network::PlayerSession &player;
		// Blam::Network::SessionMembership &membership;
		// std::string name;
	}
	{
		// std::vector<std::shared_ptr<Server::Voting::VotingMessageHandler> > &<range>$L0;
		// std::shared_ptr<Server::Voting::VotingMessageHandler> *<begin>$L0;
		// std::shared_ptr<Server::Voting::VotingMessageHandler> *<end>$L0;
		{
			// std::shared_ptr<Server::Voting::VotingMessageHandler> &handler;
		}
	}
	// function call : void (Server::Voting::VotingMessage const &)
	todo("implement");
	_sub_10C48F50(session, peer, message);
}

_extern bool _sub_10C492B0(Blam::Network::Session *, __int32, Server::Voting::VotingMessage const &);
bool SendVotingMessagePacket(Blam::Network::Session *session, __int32 peer, Server::Voting::VotingMessage const &message) // 0x10C492B0
{
	// `anonymous-namespace'::SendVotingMessagePacket
	// static ...; // 0x10C49398
	// Blam::Network::Session *session;
	// __int32 peer;
	// Server::Voting::VotingMessage const &message;
	// Patches::CustomPackets::Packet<Server::Voting::VotingMessage> packet;
	todo("implement");
	bool __result = _sub_10C492B0(session, peer, message);
	return __result;
}

// mangled_x86(MANGLED_DEFAULT, "??0VotingMessagePacketHandler@hades_file_local@@QAE@XZ"); no body to assert in
_inline VotingMessagePacketHandler::VotingMessagePacketHandler() = default; // 0x10C48030

// mangled_x86(MANGLED_DEFAULT, "??1VotingMessagePacketHandler@hades_file_local@@UAE@XZ"); no body to assert in
_inline VotingMessagePacketHandler::~VotingMessagePacketHandler() = default; // 0x10C48430
