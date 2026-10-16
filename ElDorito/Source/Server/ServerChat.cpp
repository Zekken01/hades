/* ---------- headers */

#include "Server/ServerChat.hpp"
#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_infection.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
#include "mods/font_package.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/Bits.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10C255D0

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <bitset>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct c_game_engine;
struct end;
struct s_game_options;
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
namespace Modules
{
	class ModuleServer;
}
namespace Server
{
	namespace Chat
	{
		class ChatHandler;
		enum ChatMessageType : unsigned __int32;
		struct ChatMessage;
	}
}
namespace hades_file_local
{
	struct ClientSpamStats;
	class ChatMessagePacketHandler;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace ChatCommands {}
using namespace ::ChatCommands;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Rcon {}
	using namespace Server::Rcon;
	namespace Chat {}
	using namespace Server::Chat;
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
	struct ClientSpamStats
	{
		ClientSpamStats();
		__int32 SpamScore; // 0x0
		__int32 TimeoutSeconds; // 0x4
		__int32 NextTimeoutSeconds; // 0x8
		__int32 TimeoutResetSeconds; // 0xC
	};
	static_assert(sizeof(ClientSpamStats) == 16, "Invalid ClientSpamStats size");
}
using namespace hades_file_local;
namespace Server
{
	namespace Chat
	{
		typedef std::bitset<17> PeerBitSet;
	}
}

namespace hades_file_local
{

}
using namespace hades_file_local;
namespace Patches
{
	namespace CustomPackets
	{
		typedef Packet<Server::Chat::ChatMessage> ChatMessagePacket;
	}
}

namespace hades_file_local
{
	class ChatMessagePacketHandler :
		public Patches::CustomPackets::PacketHandler<Server::Chat::ChatMessage>
	{
	public:
		virtual void Serialize(Blam::BitStream *, Server::Chat::ChatMessage const *);
		virtual bool Deserialize(Blam::BitStream *, Server::Chat::ChatMessage *);
		virtual void HandlePacket(Blam::Network::ObserverChannel *, Patches::CustomPackets::Packet<Server::Chat::ChatMessage> const *);
		ChatMessagePacketHandler(ChatMessagePacketHandler &); /* compiler_generated() */
		ChatMessagePacketHandler(ChatMessagePacketHandler const &); /* compiler_generated() */
		ChatMessagePacketHandler() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		virtual ~ChatMessagePacketHandler() = default; /* compiler_generated() */
		ChatMessagePacketHandler &operator=(ChatMessagePacketHandler &); /* compiler_generated() */
		ChatMessagePacketHandler &operator=(ChatMessagePacketHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(ChatMessagePacketHandler) == 4, "Invalid ChatMessagePacketHandler size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Server::Rcon { void SendMessageToClients(std::string message); }  // hades: added for 0x10C1F070

extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x10C1E500

namespace Patches { namespace CustomPackets { template<typename TPacket> std::shared_ptr<PacketSender<TPacket> > RegisterPacket(std::string const &name, std::shared_ptr<PacketHandler<TPacket> > handler); } }  // hades: added for 0x10C1F5A0

namespace Blam::Network { Session *GetActiveSession(); }  // hades: added for 0X10C20620

namespace Server
{
	namespace Chat
	{
		extern void Initialize();
		extern void Tick();
		extern bool SendGlobalMessage(std::string const &body);
		extern bool SendServerMessage(std::string const &body);
		extern bool SendTeamMessage(std::string const &body);
		extern bool SetPlayerMuteStatus(__int32 peer, bool muted);
		extern void ClearAllPlayersMuteStatus();
		extern bool SendAndLogServerMessage(std::string const &body);
		extern bool SendServerMessage(std::string const &body, __int32 peer);
		extern bool SendServerMessage(std::string const &body, std::bitset<17> peers);
		extern void AddHandler(std::shared_ptr<Server::Chat::ChatHandler> handler);
		extern std::string GetSenderName(Server::Chat::ChatMessage const &message);
	}
}

bool SendMessagePacket(__int32 peer, Server::Chat::ChatMessage const &message);
bool BroadcastMessage(Blam::Network::Session *session, __int32 senderPeer, Server::Chat::ChatMessage *message, std::bitset<17> peers);
bool GetTeamPeers(Blam::Network::Session *session, __int32 senderPeer, std::bitset<17> *result);
bool GetMessagePeers(Blam::Network::Session *session, __int32 senderPeer, Server::Chat::ChatMessage const &message, std::bitset<17> *result);
std::string GetSenderName(Blam::Network::Session *session, Server::Chat::ChatMessage const &message);
__int32 CalculateSpamScore(unsigned __int32 ip, ClientSpamStats *stats, Server::Chat::ChatMessage const &message);
bool ChangePlayerMuteStatus(Blam::Network::Session *session, __int32 peer, bool mute);
void UnmuteAllPlayers(Blam::Network::Session *session);
bool FloodFilterMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message);
std::string GetLogString(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message);
void LogMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message);
std::string toLower(std::string const &str);
std::string replaceAllCaseInsensitive(std::string const &str, std::string const &find, std::string const &replace);
char *handleWordFilter(char const *input);
bool HostReceivedMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message);
void ClientReceivedMessage(Server::Chat::ChatMessage const &message);
bool SendClientMessage(Blam::Network::Session *session, Server::Chat::ChatMessage const &message);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::vector<std::shared_ptr<Server::Chat::ChatHandler> > chatHandlers; // 0x12467EF4
	extern std::list<unsigned int> MutedPlayers; // 0x12467F04
	std::unordered_map<unsigned int,ClientSpamStats> SpamStats; // 0x12467F10  // hades: defined, so its atexit destructor emits ~unordered_map and ~_Hash here
	std::shared_ptr<Patches::CustomPackets::PacketSender<Server::Chat::ChatMessage> > PacketSender; // 0x12467F38
	extern unsigned long LastTimeMs; // 0x12467F40
	extern unsigned long SpamUpdateMs; // 0x12467F44
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace Chat
	{
		void Initialize() // 0x10C1F5A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@Chat@Server@@YAXXZ");

					hades_file_local::LastTimeMs = system_milliseconds();
					std::shared_ptr<ChatMessagePacketHandler> handler = std::make_shared<ChatMessagePacketHandler>();
					hades_file_local::PacketSender = Patches::CustomPackets::RegisterPacket<Server::Chat::ChatMessage>("eldewrito-text-chat", handler);
		}

		void Tick() // 0x10C206C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Chat@Server@@YAXXZ");

			unsigned long currentTimeMs = system_milliseconds();
			unsigned long timeDeltaMs = currentTimeMs - LastTimeMs;
			LastTimeMs = currentTimeMs;
			SpamUpdateMs += timeDeltaMs;
			while (SpamUpdateMs >= 1000)
			{
				SpamUpdateMs -= 1000;
				for (auto it = SpamStats.begin(); it != SpamStats.end();)
				{
					auto nextIt = it;
					++nextIt;
					if (it->second.SpamScore > 0)
						it->second.SpamScore--;
					if (it->second.TimeoutSeconds > 0)
						it->second.TimeoutSeconds--;
					else if (it->second.TimeoutResetSeconds > 0)
						it->second.TimeoutResetSeconds--;
					if (it->second.TimeoutResetSeconds == 0)
						it->second.NextTimeoutSeconds = 0;
					if (it->second.TimeoutSeconds <= 0 && it->second.SpamScore <= 0 && it->second.TimeoutResetSeconds <= 0)
						SpamStats.erase(it);
					it = nextIt;
				}
			}
		}

		bool SendGlobalMessage(std::string const &body) // 0x10C1FDB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendGlobalMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished())
				return false;
			Server::Chat::ChatMessage message(Server::Chat::Global, body);
			return SendClientMessage(session, message);
		}

		bool SendServerMessage(std::string const &body) // 0x10C1FFB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return false;
			std::bitset<17> p;
			p.set();
			Server::Chat::ChatMessage message((Server::Chat::ChatMessageType)3, body);
			return BroadcastMessage(session, session->MembershipInfo.LocalPeerIndex, &message, p);
		}

		bool SendTeamMessage(std::string const &body) // 0x10C20340
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendTeamMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			s_game_options *(*const game_options_get)() = reinterpret_cast<s_game_options *(*)()>(0x5322D0);
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished())
				return false;
			if (!session->HasTeams())
			{
				s_game_options *game = game_options_get();
				if (game)
				{
					if (game_options_get()->game_variant.game_engine_type != (e_game_engine_type)10)
						return false;
				}
				else
				{
					return false;
				}
			}
			Server::Chat::ChatMessage message(Server::Chat::Team, body);
			return SendClientMessage(session, message);
		}

		bool SetPlayerMuteStatus(__int32 peer, bool muted) // 0x10C20620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetPlayerMuteStatus@Chat@Server@@YA_NH_N@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return false;
			return ChangePlayerMuteStatus(session, peer, muted);
		}

		void ClearAllPlayersMuteStatus() // 0x10C1DD10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ClearAllPlayersMuteStatus@Chat@Server@@YAXXZ");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
			{
				return;
			}

			UnmuteAllPlayers(session);
		}

		bool SendAndLogServerMessage(std::string const &body) // 0x10C1FB70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendAndLogServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return false;
			std::bitset<17> p;
			p.set();
			Server::Chat::ChatMessage message((Server::Chat::ChatMessageType)3, body);
			if (Utils::Singleton<Modules::ModuleServer>::Instance().VarSendChatToRconClients->ValueInt == 1)
				Server::Rcon::SendMessageToClients(GetLogString(session, session->MembershipInfo.LocalPeerIndex, message));
			LogMessage(session, session->MembershipInfo.LocalPeerIndex, message);
			return BroadcastMessage(session, session->MembershipInfo.LocalPeerIndex, &message, p);
		}

		bool SendServerMessage(std::string const &body, __int32 peer) // 0x10C200F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return false;
			std::bitset<17> peers;
			peers.set(peer);
			Server::Chat::ChatMessage message((Server::Chat::ChatMessageType)3, body);
			return BroadcastMessage(session, session->MembershipInfo.LocalPeerIndex, &message, peers);
		}

		bool SendServerMessage(std::string const &body, std::bitset<17> peers) // 0x10C20230
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$bitset@$0BB@@4@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return false;
			Server::Chat::ChatMessage message((Server::Chat::ChatMessageType)3, body);
			return BroadcastMessage(session, session->MembershipInfo.LocalPeerIndex, &message, peers);
		}

		void AddHandler(std::shared_ptr<Server::Chat::ChatHandler> handler) // 0x10C1D460
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddHandler@Chat@Server@@YAXV?$shared_ptr@VChatHandler@Chat@Server@@@std@@@Z");

			chatHandlers.push_back(handler);
		}
	}
}


namespace Server
{
	namespace Chat
	{
		std::string GetSenderName(Server::Chat::ChatMessage const &message) // 0x10C1EBA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetSenderName@Chat@Server@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUChatMessage@12@@Z");

			return ::GetSenderName(Blam::Network::GetActiveSession(), message);
		}

		ChatMessage::ChatMessage(Server::Chat::ChatMessageType type, std::string const &body) // 0x10C1B120
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0ChatMessage@Chat@Server@@QAE@W4ChatMessageType@12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			memset(this, 0, sizeof(*this));
			Type = type;
			strncpy(Body, body.c_str(), sizeof(Body) - 1);
		}
	}
}

/* ---------- private code */

_inline ClientSpamStats::ClientSpamStats() // 0x10C1B230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0ClientSpamStats@hades_file_local@@QAE@XZ");

	SpamScore = 0;
	TimeoutSeconds = 0;
	NextTimeoutSeconds = 0;
	TimeoutResetSeconds = 0;
}


_inline void ChatMessagePacketHandler::Serialize(Blam::BitStream *stream, Server::Chat::ChatMessage const *data) // 0x10C204D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Serialize@ChatMessagePacketHandler@hades_file_local@@UAEXPAVBitStream@Blam@@PBUChatMessage@Chat@Server@@@Z");

	stream->WriteUnsigned(static_cast<unsigned int>(data->Type), 0U, static_cast<unsigned int>(Server::Chat::ChatMessageType::Count));
	stream->WriteString(data->Body);
	if (data->Type != Server::Chat::ChatMessageType::Server)
	{
		stream->WriteUnsigned<unsigned char>(data->SenderPlayer, 0, 15);
	}

	if (data->Type == Server::Chat::ChatMessageType::Whisper)
	{
		stream->WriteUnsigned<unsigned char>(data->TargetPlayer, 0, 15);
	}
}

_inline bool ChatMessagePacketHandler::Deserialize(Blam::BitStream *stream, Server::Chat::ChatMessage *data) // 0x10C1DE70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Deserialize@ChatMessagePacketHandler@hades_file_local@@UAE_NPAVBitStream@Blam@@PAUChatMessage@Chat@Server@@@Z");

	memset(data, 0, sizeof(*data));

	// Message type
	data->Type = static_cast<ChatMessageType>(stream->ReadUnsigned(0U, static_cast<unsigned __int32>(ChatMessageType::Count)));
	if (static_cast<unsigned __int32>(data->Type) >= static_cast<unsigned __int32>(ChatMessageType::Count))
		return false;

	// Body
	if (!stream->ReadString(data->Body))
		return false;

	// For non-server messages, deserialize the sender index
	if (data->Type != ChatMessageType::Server)
		data->SenderPlayer = stream->ReadUnsigned<unsigned char>(0, 15);

	// For whisper messages, deserialize the target index
	if (data->Type == ChatMessageType::Whisper)
		data->TargetPlayer = stream->ReadUnsigned<unsigned char>(0, 15);

	return true;
}

_inline void ChatMessagePacketHandler::HandlePacket(Blam::Network::ObserverChannel *sender, Patches::CustomPackets::Packet<Server::Chat::ChatMessage> const *packet) // 0x10C1EF20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandlePacket@ChatMessagePacketHandler@hades_file_local@@UAEXPAUObserverChannel@Network@Blam@@PBU?$Packet@UChatMessage@Chat@Server@@@CustomPackets@Patches@@@Z");

	auto session = Blam::Network::GetActiveSession();
	if (!session)
		return;
	auto peer = session->GetChannelPeer(sender);
	if (peer < 0)
		return;
	if (session->IsHost())
		HostReceivedMessage(session, peer, packet->Data);
	else if (peer == session->MembershipInfo.HostPeerIndex)
		ClientReceivedMessage(packet->Data);
}

bool SendMessagePacket(__int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1FEA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SendMessagePacket@@YA_NHABUChatMessage@Chat@Server@@@Z");

	if (peer < 0)
		return false;
	auto packet = hades_file_local::PacketSender->New();
	packet.Data = message;
	hades_file_local::PacketSender->Send(peer, packet);
	return true;
}

bool BroadcastMessage(Blam::Network::Session *session, __int32 senderPeer, Server::Chat::ChatMessage *message, std::bitset<17> peers) // 0x10C1D500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BroadcastMessage@@YA_NPAUSession@Network@Blam@@HPAUChatMessage@Chat@Server@@V?$bitset@$0BB@@std@@@Z");

	if (senderPeer < 0)
		return false;
	bool ignore = false;
	for (auto &handler : chatHandlers)
		handler->MessageSent(senderPeer, message, &ignore);
	if (ignore)
		return true;
	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	for (__int32 peer = membership->FindFirstPeer(); peer >= 0; peer = membership->FindNextPeer(peer))
	{
		if (!peers[peer])
			continue;
		if (peer == membership->LocalPeerIndex)
			ClientReceivedMessage(*message);
		else if (!SendMessagePacket(peer, *message))
			return false;
	}
	return true;
}

bool GetTeamPeers(Blam::Network::Session *session, __int32 senderPeer, std::bitset<17> *result) // 0x10C1EC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetTeamPeers@@YA_NPAUSession@Network@Blam@@HPAV?$bitset@$0BB@@std@@@Z");

	s_game_options *(*const game_options_get)() = reinterpret_cast<s_game_options *(*)()>(0x5322D0);
	result->reset();
	s_game_options *game = game_options_get();
	if (game && ((c_game_engine *(__cdecl *)())0x5CE150)() && ((bool(__cdecl *)())0x5314B0)() && game->game_variant.game_engine_type == (e_game_engine_type)10)
	{
		Blam::Network::SessionMembership *membership = &session->MembershipInfo;
		long player_datum_index = membership->GetPeerPlayer(senderPeer);
		__int32 player_absolute_index = ((__int32(__cdecl *)(long))0x53B1A0)(player_datum_index);
		bool sender_is_zombie = (get_infection_globals()->zombie_bit_vector & (1 << player_absolute_index)) != 0;
		for (__int32 peer = membership->FindFirstPeer(); peer >= 0; peer = membership->FindNextPeer(peer))
		{
			long peer_player_datum_index = membership->GetPeerPlayer(peer);
			if (peer_player_datum_index == -1)
				continue;
			__int32 peer_player_absoulte_index = ((__int32(__cdecl *)(long))0x53B1A0)(peer_player_datum_index);
			if (((get_infection_globals()->zombie_bit_vector & (1 << peer_player_absoulte_index)) != 0) == sender_is_zombie)
				result->set(peer);
		}
		return true;
	}
	if (!session->HasTeams())
		return false;
	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	__int32 senderTeam = membership->GetPeerTeam(senderPeer);
	if (senderTeam < 0)
		return false;
	for (__int32 peer = membership->FindFirstPeer(); peer >= 0; peer = membership->FindNextPeer(peer))
	{
		if (membership->GetPeerTeam(peer) == senderTeam)
			result->set(peer);
	}
	return true;
}

bool GetMessagePeers(Blam::Network::Session *session, __int32 senderPeer, Server::Chat::ChatMessage const &message, std::bitset<17> *result) // 0x10C1E9D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMessagePeers@@YA_NPAUSession@Network@Blam@@HABUChatMessage@Chat@Server@@PAV?$bitset@$0BB@@std@@@Z");

	switch (message.Type)
	{
	case ChatMessageType::Global:
		result->set();
		break;
	case ChatMessageType::Team:
		GetTeamPeers(session, senderPeer, result);
		break;
	// TODO: ChatMessageType::Whisper
	default:
		return false;
	}
	return true;
}

std::string GetSenderName(Blam::Network::Session *session, Server::Chat::ChatMessage const &message) // 0x10C1EAA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetSenderName@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUSession@Network@Blam@@ABUChatMessage@Chat@Server@@@Z");

	if (message.Type == (Server::Chat::ChatMessageType)3 || message.SenderPlayer >= 16)
		return "SERVER";

	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	Blam::Network::PlayerSession *player = &membership->PlayerSessions[message.SenderPlayer];
	return Utils::String::ThinString((wchar_t const *)((unsigned char *)player + 0x58));
}

__int32 CalculateSpamScore(unsigned __int32 ip, ClientSpamStats *stats, Server::Chat::ChatMessage const &message) // 0x10C1D740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CalculateSpamScore@@YAHIPAUClientSpamStats@hades_file_local@@ABUChatMessage@Chat@Server@@@Z");

	auto &serverModule = Modules::ModuleServer::Instance();
	int shortScore = serverModule.VarFloodMessageScoreShort->ValueInt;
	int longScore = serverModule.VarFloodMessageScoreLong->ValueInt;

	return shortScore + strlen(message.Body) * (longScore + 1 - shortScore) / 0x101;
}

bool ChangePlayerMuteStatus(Blam::Network::Session *session, __int32 peer, bool mute) // 0x10C1D7E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ChangePlayerMuteStatus@@YA_NPAUSession@Network@Blam@@H_N@Z");

	unsigned __int32 ip = session->GetPeerAddress(peer).Address.IPv4;
	bool playerInList = false;
	if (!MutedPlayers.empty())
	{
		for (unsigned __int32 player_ip : MutedPlayers)
		{
			if (player_ip == ip)
			{
				playerInList = true;
				break;
			}
		}
	}
	if (mute && !playerInList)
	{
		MutedPlayers.push_front(ip);
		std::bitset<17> targetPeers;
		targetPeers.set(peer);
		Server::Chat::SendServerMessage("You have been muted.", targetPeers);
		return true;
	}
	else if (!mute)
	{
		auto spamIt = SpamStats.find(ip);
		bool cleared = false;
		if (spamIt == SpamStats.end())
			spamIt = SpamStats.insert({ ip, ClientSpamStats() }).first;
		if (spamIt->second.TimeoutSeconds > 0)
		{
			spamIt->second.SpamScore = 0;
			spamIt->second.TimeoutSeconds = 0;
			spamIt->second.NextTimeoutSeconds = 0;
			spamIt->second.TimeoutResetSeconds = 0;
			cleared = true;
		}
		if (playerInList)
		{
			MutedPlayers.remove(ip);
			cleared = true;
		}
		if (cleared)
		{
			std::bitset<17> targetPeers;
			targetPeers.set(peer);
			Server::Chat::SendServerMessage("You have been unmuted.", targetPeers);
			return true;
		}
		return false;
	}
	if ((mute && playerInList) || (!mute && !playerInList))
		return false;
	return false;
}

void UnmuteAllPlayers(Blam::Network::Session *session) // 0x10C209E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UnmuteAllPlayers@@YAXPAUSession@Network@Blam@@@Z");

	for (auto ip : MutedPlayers)
	{
		__int32 peer = -1;
		for (__int32 i = 0; i < 15; i++)
		{
			if (session->GetPeerAddress(i).Address.IPv4 == ip)
			{
				peer = i;
				break;
			}
		}
		if (peer != -1)
		{
			auto spamIt = SpamStats.find(ip);
			if (spamIt != SpamStats.end())
			{
				spamIt->second.SpamScore = 0;
				spamIt->second.TimeoutSeconds = 0;
				spamIt->second.NextTimeoutSeconds = 0;
				spamIt->second.TimeoutResetSeconds = 0;
			}
			std::bitset<17> targetPeers;
			targetPeers.set(peer);
			Server::Chat::SendServerMessage("You have been unmuted.", targetPeers);
		}
	}
	MutedPlayers.clear();
}

bool FloodFilterMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1E000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FloodFilterMessage@@YA_NPAUSession@Network@Blam@@HABUChatMessage@Chat@Server@@@Z");

	unsigned __int32 ip = session->GetPeerAddress(peer).Address.IPv4;
	auto spamIt = SpamStats.find(ip);
	if (spamIt == SpamStats.end())
		spamIt = SpamStats.insert({ ip, ClientSpamStats() }).first;
	if (spamIt->second.TimeoutSeconds <= 0)
	{
		__int32 score = CalculateSpamScore(ip, &spamIt->second, message);
		spamIt->second.SpamScore += score;
		Modules::ModuleServer &serverModule = Modules::ModuleServer::Instance();
		if (spamIt->second.SpamScore >= static_cast<__int32>(serverModule.VarFloodTimeoutScore->ValueInt))
		{
			if (spamIt->second.NextTimeoutSeconds > 0)
				spamIt->second.NextTimeoutSeconds *= 2;
			else
				spamIt->second.NextTimeoutSeconds = serverModule.VarFloodTimeoutSeconds->ValueInt;
			spamIt->second.TimeoutSeconds = spamIt->second.NextTimeoutSeconds;
			spamIt->second.TimeoutResetSeconds = serverModule.VarFloodTimeoutResetSeconds->ValueInt;
		}
	}
	if (spamIt->second.TimeoutSeconds > 0)
	{
		std::bitset<17> targetPeers;
		targetPeers.set(peer);
		Server::Chat::SendServerMessage("You have exceeded the server's spam limit. You can chat again in " + std::to_string(spamIt->second.TimeoutSeconds) + " second(s).", targetPeers);
		return true;
	}
	return false;
}

std::string GetLogString(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1E500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetLogString@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUSession@Network@Blam@@HABUChatMessage@Chat@Server@@@Z");

	std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<__int64, std::ratio<1, 10000000> > > now = std::chrono::system_clock::now();
	long long time = std::chrono::system_clock::to_time_t(now);
	tm gmTime;
	gmtime_s(&gmTime, &time);
	std::string sender = GetSenderName(session, message);
	unsigned __int32 ip = session->GetPeerAddress(peer).Address.IPv4;
	unsigned long long uid = 0;
	__int32 playerIndex = session->MembershipInfo.GetPeerPlayer(peer);
	if (playerIndex >= 0)
		uid = session->MembershipInfo.PlayerSessions[playerIndex].Properties.host.player_uid;
	std::ostringstream ss;
	char uidStr[17];
	player_format_uid(uidStr, uid);
	ss << "[" << std::put_time(&gmTime, "%m/%d/%y %H:%M:%S") << "] ";
	ss << "<" << sender << "/";
	ss << uidStr << "/";
	ss << (ip >> 24) << "." << ((ip >> 16) & 0xFF) << "." << ((ip >> 8) & 0xFF) << "." << (ip & 0xFF) << "> ";
	if (message.Type == Server::Chat::ChatMessageType::Team)
		ss << "(TEAM) ";
	ss << message.Body;
	return ss.str();
}

void LogMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1F730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LogMessage@@YAXPAUSession@Network@Blam@@HABUChatMessage@Chat@Server@@@Z");

	Modules::ModuleServer &serverModule = Modules::ModuleServer::Instance();
	if (!serverModule.VarChatLogEnabled->ValueInt)
		return;
	std::string chatLogFile = Modules::ModuleServer::Instance().VarChatLogFile->ValueString;
	std::filesystem::path logFilePath(chatLogFile);
	std::filesystem::path parentDirectory = logFilePath.parent_path();
	if (parentDirectory != "")
		std::filesystem::create_directories(parentDirectory);
	std::ofstream logFile(chatLogFile, std::ios::app);
	if (!logFile)
		return;
	logFile << GetLogString(session, peer, message) << "\n";
}

std::string toLower(std::string const &str) // 0x10C26790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?toLower@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV12@@Z");

	std::string lowerStr;
	for (char c : str)
	{
		lowerStr += tolower(static_cast<unsigned char>(c));
	}

	return lowerStr;
}

std::string replaceAllCaseInsensitive(std::string const &str, std::string const &find, std::string const &replace) // 0x10C26230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?replaceAllCaseInsensitive@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV12@00@Z");

	if (find.empty())
		return str;
	std::string lowerStr = toLower(str);
	std::string lowerFind = toLower(find);
	std::string result;
	unsigned __int32 startPos = 0;
	unsigned __int32 findLen = find.length();
	unsigned __int32 replaceLen = replace.length();
	while (true)
	{
		unsigned __int32 pos = lowerStr.find(lowerFind, startPos);
		if (pos == std::string::npos)
			break;
		result += str.substr(startPos, pos - startPos);
		result += replace;
		startPos = pos + findLen;
	}
	result += str.substr(startPos);
	return result;
}

char *handleWordFilter(char const *input) // 0x10C255D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleWordFilter@@YAPADPBD@Z");

	std::string strInput = input;
	std::unordered_set<std::string> FilteredWords = Utils::Singleton<Modules::ModuleServer>::Instance().GetFilteredWordsList();
	std::unordered_set<std::string> FilteredPatterns = Utils::Singleton<Modules::ModuleServer>::Instance().GetFilteredPatternsList();
	std::string FilterReplacementWord = Utils::Singleton<Modules::ModuleServer>::Instance().GetFilterReplacementWord();
	if (!FilteredWords.empty())
	{
		for (const auto &word : FilteredWords)
		{
			if (!word.empty())
				strInput = replaceAllCaseInsensitive(strInput, word, FilterReplacementWord);
		}
	}
	if (!FilteredPatterns.empty())
	{
		std::string pattern;
		bool first = true;
		for (const auto &pat : FilteredPatterns)
		{
			if (!pat.empty())
			{
				if (!first)
					pattern += "|";
				pattern += "(" + pat + ")";
				first = false;
			}
		}
		if (!pattern.empty())
		{
			try
			{
				std::regex regex(pattern, std::regex::ECMAScript);
				strInput = std::regex_replace(strInput, regex, FilterReplacementWord);
			}
			catch (...)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Regex patterns in server.json are incorrect");
			}
		}
	}
	unsigned __int32 len = strInput.size();
	char *output = new char[len + 1];
	memcpy(output, strInput.c_str(), len + 1);
	return output;
}

bool HostReceivedMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1F070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HostReceivedMessage@@YA_NPAUSession@Network@Blam@@HABUChatMessage@Chat@Server@@@Z");

	if (peer < 0 || !message.Body[0] || message.Type == Server::Chat::ChatMessageType::Server)
		return false;
	Server::Chat::ChatMessage broadcastMessage = message;
	__int32 player = session->MembershipInfo.GetPeerPlayer(peer);
	if (player < 0)
		return false;
	broadcastMessage.SenderPlayer = static_cast<unsigned char>(player);
	Modules::ModuleServer &serverModule = Modules::ModuleServer::Instance();
	if (peer != session->MembershipInfo.LocalPeerIndex && serverModule.VarFloodFilterEnabled->ValueInt && FloodFilterMessage(session, peer, broadcastMessage))
		return true;
	if (!MutedPlayers.empty())
	{
		unsigned __int32 ip = session->GetPeerAddress(peer).Address.IPv4;
		for (unsigned __int32 player_ip : MutedPlayers)
		{
			if (player_ip == ip)
			{
				std::bitset<17> targetPeers;
				targetPeers.set(peer);
				Server::Chat::SendServerMessage("You are muted.", targetPeers);
				return true;
			}
		}
	}
	char *filteredMessage;
	if (Modules::ModuleServer::Instance().VarChatFilterEnabled->ValueInt == 1)
	{
		filteredMessage = handleWordFilter(broadcastMessage.Body);
		strncpy(broadcastMessage.Body, filteredMessage, 256);
		broadcastMessage.Body[256] = 0;
		delete[] filteredMessage;
	}
	if (Modules::ModuleServer::Instance().VarSendChatToRconClients->ValueInt == 1)
		Server::Rcon::SendMessageToClients(GetLogString(session, peer, broadcastMessage));
	LogMessage(session, peer, broadcastMessage);
	if (message.Type != Server::Chat::ChatMessageType::Team && ChatCommands::handleChatMessage(message, peer))
		return true;
	std::bitset<17> targetPeers;
	if (!GetMessagePeers(session, peer, message, &targetPeers))
		return false;
	return BroadcastMessage(session, peer, &broadcastMessage, targetPeers);
}

void ClientReceivedMessage(Server::Chat::ChatMessage const &message) // 0x10C1DDA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ClientReceivedMessage@@YAXABUChatMessage@Chat@Server@@@Z");

	// Send the message out to handlers
	for (auto &&handler : chatHandlers)
		handler->MessageReceived(message);
}

bool SendClientMessage(Blam::Network::Session *session, Server::Chat::ChatMessage const &message) // 0x10C1FD20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SendClientMessage@@YA_NPAUSession@Network@Blam@@ABUChatMessage@Chat@Server@@@Z");

	if (session->IsHost())
	{
		return HostReceivedMessage(session, session->MembershipInfo.LocalPeerIndex, message);
	}

	return SendMessagePacket(session->MembershipInfo.HostPeerIndex, message);
}

// mangled_x86(MANGLED_DEFAULT, "??0ChatMessagePacketHandler@hades_file_local@@QAE@XZ"); no body to assert in
// _inline ChatMessagePacketHandler::ChatMessagePacketHandler() = default; // 0x10C1B1D0  // hades: defaulted on its declaration

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Patches::CustomPackets::Packet<Server::Chat::ChatMessage> Patches::CustomPackets::PacketSender<Server::Chat::ChatMessage>::New() const;
template Patches::CustomPackets::Packet<Server::Chat::ChatMessage>::Packet(unsigned __int32);
template Patches::CustomPackets::PacketSender<Server::Chat::ChatMessage>::PacketSender(unsigned __int32);
template __int32 Patches::CustomPackets::PacketHandler<Server::Chat::ChatMessage>::GetMaxRawPacketSize() const;
template __int32 Patches::CustomPackets::PacketHandler<Server::Chat::ChatMessage>::GetMinRawPacketSize() const;
template bool Patches::CustomPackets::PacketHandler<Server::Chat::ChatMessage>::DeserializeRawPacket(Blam::BitStream *, __int32, void *);
template void Blam::BitStream::WriteUnsigned<unsigned int>(unsigned __int32, unsigned __int32, unsigned __int32);
template void Patches::CustomPackets::PacketHandler<Server::Chat::ChatMessage>::HandleRawPacket(Blam::Network::ObserverChannel *, void const *);
template void Patches::CustomPackets::PacketHandler<Server::Chat::ChatMessage>::SerializeRawPacket(Blam::BitStream *, __int32, void const *);
template void Patches::CustomPackets::PacketSender<Server::Chat::ChatMessage>::Send(__int32, Patches::CustomPackets::Packet<Server::Chat::ChatMessage> const &) const;

/* ---------- explicit instantiations */
template std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > >,std::_Iterator_base12>::_List_unchecked_const_iterator(std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > >,std::_Iterator_base12> const &);
template std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > >,std::_Iterator_base12> & std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > >,std::_Iterator_base12>::operator=(std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > >,std::_Iterator_base12> const &);
template std::_Hash<std::_Umap_traits<unsigned int,ClientSpamStats,std::_Uhash_compare<unsigned int,std::hash<unsigned int>,std::equal_to<unsigned int> >,std::allocator<std::pair<unsigned int const ,ClientSpamStats> >,0> >::~_Hash();
template std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::_List_const_iterator(std::_List_node<std::pair<unsigned int const ,ClientSpamStats>,void *> *, std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > const *);
template std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::_List_iterator(std::_List_node<std::pair<unsigned int const ,ClientSpamStats>,void *> *, std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > const *);
template std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::_List_unchecked_iterator(std::_List_node<std::pair<unsigned int const ,ClientSpamStats>,void *> *, std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > const *);
template Patches::CustomPackets::PacketHandler<Server::Chat::ChatMessage>::PacketHandler();
template std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::_List_const_iterator(std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > const &);
template std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::_List_iterator(std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > const &);
template std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > & std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::operator=(std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > const &);
template std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > & std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::operator=(std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > const &);
template std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::~_List_const_iterator();
template std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >::~_List_iterator();
template std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > >,std::_Iterator_base12>::~_List_unchecked_const_iterator();
template std::pair<std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > >,bool>::~pair();
template std::unordered_map<unsigned int,ClientSpamStats>::~unordered_map();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { std::vector<std::shared_ptr<Server::Chat::ChatHandler> > chatHandlers; }
namespace hades_file_local { std::list<unsigned int> MutedPlayers; }
namespace hades_file_local { unsigned long LastTimeMs; }
namespace hades_file_local { unsigned long SpamUpdateMs; }
