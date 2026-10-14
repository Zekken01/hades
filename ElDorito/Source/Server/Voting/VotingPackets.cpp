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
		VotingMessagePacketHandler() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		virtual ~VotingMessagePacketHandler() = default; /* compiler_generated() */  // hades: defaulted in the class, so it does not reset the vtable pointer (0x10C48430)
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

namespace Patches { namespace CustomPackets { template<typename TPacket> std::shared_ptr<PacketSender<TPacket> > RegisterPacket(std::string const &name, std::shared_ptr<PacketHandler<TPacket> > handler); } }  // hades: added for 0x10C48D70

namespace Server { namespace Voting { extern void LogVote(Server::Voting::VotingMessage const &message, std::string name); } }  // hades: added for 0x10C48F50

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
	std::shared_ptr<Patches::CustomPackets::PacketSender<Server::Voting::VotingMessage> > VotingPacketSender; // 0x1246B6A8
	std::vector<std::shared_ptr<Server::Voting::VotingMessageHandler> > votingMessageHandlers; // 0x1246B698
}
using namespace hades_file_local;
namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x1246B4D8  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x1246B5B8  // hades: defined in VotingTypes.hpp, one copy per file
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

		void AddMessageHandler(std::shared_ptr<Server::Voting::VotingMessageHandler> handler) // 0x10C48740
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddMessageHandler@Voting@Server@@YAXV?$shared_ptr@VVotingMessageHandler@Voting@Server@@@std@@@Z");
			// std::shared_ptr<Server::Voting::VotingMessageHandler> handler;

			votingMessageHandlers.push_back(handler);
		}

		void InitializePackets() // 0x10C48D70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitializePackets@Voting@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C48E98
			// static ...; // 0x10C48E8C
			// static ...; // 0x10C48E84
			// std::shared_ptr<VotingMessagePacketHandler> handler;

			auto handler = std::make_shared<VotingMessagePacketHandler>();
			VotingPacketSender = Patches::CustomPackets::RegisterPacket<VotingMessage>("eldewrito-voting-message", handler);
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

_inline void VotingMessagePacketHandler::Serialize(Blam::BitStream *stream, Server::Voting::VotingMessage const *data) // 0x10C49460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Serialize@VotingMessagePacketHandler@hades_file_local@@UAEXPAVBitStream@Blam@@PBUVotingMessage@Voting@Server@@@Z");
	// `anonymous-namespace'::VotingMessagePacketHandler::Serialize
	// Server::Voting::VotingMessage const *data;
		// __int32 i;

	stream->WriteUnsigned<unsigned __int32>(data->Type, 0, Server::Voting::Count);
	if (data->Type == Server::Voting::VotingOptions || data->Type == Server::Voting::VetoOption)
	{
		for (__int32 i = 0; i < 6; i++)
		{
			stream->WriteString(data->votingOptions[i].scnrName);
			stream->WriteString(data->votingOptions[i].mapName);
			stream->WriteString(data->votingOptions[i].typeName);
			stream->WriteString(data->votingOptions[i].modName);
			stream->WriteString(data->votingOptions[i].modHash);
			stream->WriteString(data->votingOptions[i].imageUri);
			stream->WriteBool(data->votingOptions[i].canVeto);
		}
		stream->WriteUnsigned<unsigned char>(data->voteTime, 0, 200);
	}
	if (data->Type == Server::Voting::Vote || data->Type == Server::Voting::VetoVote)
		stream->WriteUnsigned<unsigned char>(data->Vote, 0, 6);
	if (data->Type == Server::Voting::VoteTally)
	{
		for (__int32 i = 0; i < 6; i++)
			stream->WriteUnsigned<unsigned char>(data->votes[i], 0, 16);
	}
	if (data->Type == Server::Voting::VoteTally || data->Type == Server::Voting::VetoOption)
		stream->WriteUnsigned<unsigned char>(data->votesNeededToPass, 0, 16);
	if (data->Type == Server::Voting::Winner)
		stream->WriteUnsigned<unsigned char>(data->winner, 0, 6);
	if (data->Type == Server::Voting::VoteTimerUpdated)
	{
		stream->WriteBool(data->shouldUpdateTimer);
		stream->WriteUnsigned<unsigned char>(data->voteTime, 0, 200);
	}
	if (data->Type == Server::Voting::VoteEnded)
		stream->WriteBool(data->voteEnded);
}

_inline bool VotingMessagePacketHandler::Deserialize(Blam::BitStream *stream, Server::Voting::VotingMessage *data) // 0x10C48890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Deserialize@VotingMessagePacketHandler@hades_file_local@@UAE_NPAVBitStream@Blam@@PAUVotingMessage@Voting@Server@@@Z");
	// `anonymous-namespace'::VotingMessagePacketHandler::Deserialize
	// Server::Voting::VotingMessage *data;
		// __int32 i;

	memset(data, 0, sizeof(Server::Voting::VotingMessage));
	data->Type = static_cast<Server::Voting::VotingMessageType>(stream->ReadUnsigned<unsigned __int32>(0, Server::Voting::Count));
	if (data->Type >= Server::Voting::Count)
		return false;
	if (data->Type == Server::Voting::VotingOptions || data->Type == Server::Voting::VetoOption)
	{
		for (__int32 i = 0; i < 6; i++)
		{
			stream->ReadString(data->votingOptions[i].scnrName);
			stream->ReadString(data->votingOptions[i].mapName);
			stream->ReadString(data->votingOptions[i].typeName);
			stream->ReadString(data->votingOptions[i].modName);
			stream->ReadString(data->votingOptions[i].modHash);
			stream->ReadString(data->votingOptions[i].imageUri);
			data->votingOptions[i].canVeto = stream->ReadBool();
		}
		data->voteTime = stream->ReadUnsigned<unsigned char>(0, 200);
	}
	if (data->Type == Server::Voting::Vote || data->Type == Server::Voting::VetoVote)
		data->Vote = stream->ReadUnsigned<unsigned char>(0, 6);
	if (data->Type == Server::Voting::VoteTally)
	{
		for (__int32 i = 0; i < 6; i++)
			data->votes[i] = stream->ReadUnsigned<unsigned char>(0, 16);
	}
	if (data->Type == Server::Voting::VoteTally || data->Type == Server::Voting::VetoOption)
		data->votesNeededToPass = stream->ReadUnsigned<unsigned char>(0, 16);
	if (data->Type == Server::Voting::Winner)
		data->winner = stream->ReadUnsigned<unsigned char>(0, 6);
	if (data->Type == Server::Voting::VoteTimerUpdated)
	{
		data->shouldUpdateTimer = stream->ReadBool();
		data->voteTime = stream->ReadUnsigned<unsigned char>(0, 200);
	}
	if (data->Type == Server::Voting::VoteEnded)
		data->voteEnded = stream->ReadBool();
	return true;
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

void ReceivedVotingMessage(Blam::Network::Session *session, __int32 peer, Server::Voting::VotingMessage const &message) // 0x10C48F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ReceivedVotingMessage@@YAXPAUSession@Network@Blam@@HABUVotingMessage@Voting@Server@@@Z");
	// `anonymous-namespace'::ReceivedVotingMessage
	// static ...; // 0x10C490D4
	// Blam::Network::Session *session;
	// __int32 peer;
	// Server::Voting::VotingMessage const &message;
		// Blam::Network::PlayerSession &player;
		// Blam::Network::SessionMembership &membership;
		// std::string name;
		// std::vector<std::shared_ptr<Server::Voting::VotingMessageHandler> > &<range>$L0;
		// std::shared_ptr<Server::Voting::VotingMessageHandler> *<begin>$L0;
		// std::shared_ptr<Server::Voting::VotingMessageHandler> *<end>$L0;
			// std::shared_ptr<Server::Voting::VotingMessageHandler> &handler;
	// function call : void (Server::Voting::VotingMessage const &)

	if (message.Type == Server::Voting::Vote && peer >= 0)
	{
		auto &membership = session->MembershipInfo;
		auto &player = membership.PlayerSessions[membership.GetPeerPlayer(peer)];
		std::string name = Utils::String::ThinString(player.Properties.host.player_name);
		Server::Voting::LogVote(message, name);
	}
	else
	{
		for (auto &handler : votingMessageHandlers)
			handler->MessageReceived(message);
	}
}

bool SendVotingMessagePacket(Blam::Network::Session *session, __int32 peer, Server::Voting::VotingMessage const &message) // 0x10C492B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SendVotingMessagePacket@@YA_NPAUSession@Network@Blam@@HABUVotingMessage@Voting@Server@@@Z");
	// `anonymous-namespace'::SendVotingMessagePacket
	// static ...; // 0x10C49398
	// Blam::Network::Session *session;
	// __int32 peer;
	// Server::Voting::VotingMessage const &message;
	// Patches::CustomPackets::Packet<Server::Voting::VotingMessage> packet;

	if (peer < 0)
		return false;
	if (peer == session->MembershipInfo.LocalPeerIndex)
	{
		ReceivedVotingMessage(session, peer, message);
		return true;
	}
	auto packet = hades_file_local::VotingPacketSender->New();
	packet.Data = message;
	hades_file_local::VotingPacketSender->Send(peer, packet);
	return true;
}

// mangled_x86(MANGLED_DEFAULT, "??0VotingMessagePacketHandler@hades_file_local@@QAE@XZ"); no body to assert in
// _inline VotingMessagePacketHandler::VotingMessagePacketHandler() = default; // 0x10C48030  // hades: defaulted on its declaration

// mangled_x86(MANGLED_DEFAULT, "??1VotingMessagePacketHandler@hades_file_local@@UAE@XZ"); no body to assert in
// hades: VotingMessagePacketHandler::~VotingMessagePacketHandler() is defaulted in the class (0x10C48430)

/* ---------- explicit instantiations */
template void Patches::CustomPackets::PacketSender<Server::Voting::VotingMessage>::Send(__int32, Patches::CustomPackets::Packet<Server::Voting::VotingMessage> const &) const;
template Patches::CustomPackets::PacketHandler<Server::Voting::VotingMessage>::PacketHandler();
template Patches::CustomPackets::Packet<Server::Voting::VotingMessage> Patches::CustomPackets::PacketSender<Server::Voting::VotingMessage>::New() const;
template Patches::CustomPackets::Packet<Server::Voting::VotingMessage>::Packet(unsigned __int32);
template Patches::CustomPackets::PacketSender<Server::Voting::VotingMessage>::PacketSender(unsigned __int32);

/* ---------- explicit instantiations (hades: the original object carries these) */
template bool Blam::BitStream::ReadString<char,17>(char (&)[17]);
template bool Blam::BitStream::ReadString<char,32>(char (&)[32]);
template bool Blam::BitStream::ReadString<char,41>(char (&)[41]);
template bool Blam::BitStream::ReadString<char,512>(char (&)[512]);
template void Blam::BitStream::WriteString<char,17>(char const (&)[17]);
template void Blam::BitStream::WriteString<char,32>(char const (&)[32]);
template void Blam::BitStream::WriteString<char,41>(char const (&)[41]);
template void Blam::BitStream::WriteString<char,512>(char const (&)[512]);
