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
		ChatMessagePacketHandler(); /* compiler_generated() */
		virtual ~ChatMessagePacketHandler(); /* compiler_generated() */
		ChatMessagePacketHandler &operator=(ChatMessagePacketHandler &); /* compiler_generated() */
		ChatMessagePacketHandler &operator=(ChatMessagePacketHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(ChatMessagePacketHandler) == 4, "Invalid ChatMessagePacketHandler size");
}
using namespace hades_file_local;
/* ---------- prototypes */

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
	extern std::shared_ptr<Patches::CustomPackets::PacketSender<Server::Chat::ChatMessage> > PacketSender; // 0x12467F38
	extern unsigned long LastTimeMs; // 0x12467F40
	extern unsigned long SpamUpdateMs; // 0x12467F44
	extern std::vector<std::shared_ptr<Server::Chat::ChatHandler>,std::allocator<std::shared_ptr<Server::Chat::ChatHandler> > > chatHandlers; // 0x12467EF4
	extern std::list<unsigned int,std::allocator<unsigned int> > MutedPlayers; // 0x12467F04
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace Chat
	{
		_extern void _sub_10C1F5A0();
		void Initialize() // 0x10C1F5A0
		{
			mangled_x86(MANGLED_TODO, "?Initialize@Chat@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C1F6D4
			// static ...; // 0x10C1F6C8
			// static ...; // 0x10C1F6C0
			// std::shared_ptr<ChatMessagePacketHandler> handler;
			todo("implement");
			_sub_10C1F5A0();
		}

		_extern void _sub_10C206C0();
		void Tick() // 0x10C206C0
		{
			mangled_x86(MANGLED_TODO, "?Tick@Chat@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C2093B
			// static ...; // 0x10C20934
			// static ...; // 0x10C2091C
			// static ...; // 0x10C20914
			// unsigned long currentTimeMs;
			// unsigned long timeDeltaMs;
			{
				// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > it;
				{
					// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > nextIt;
				}
			}
			todo("implement");
			_sub_10C206C0();
		}

		_extern bool _sub_10C1FDB0(std::string const &);
		bool SendGlobalMessage(std::string const &body) // 0x10C1FDB0
		{
			mangled_x86(MANGLED_TODO, "?SendGlobalMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C1FE60
			// static ...; // 0x10C1FE54
			// static ...; // 0x10C1FE4C
			// std::string const &body;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C1FDB0(body);
			return __result;
		}

		_extern bool _sub_10C1FFB0(std::string const &);
		bool SendServerMessage(std::string const &body) // 0x10C1FFB0
		{
			mangled_x86(MANGLED_TODO, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C200A4
			// static ...; // 0x10C2009C
			// static ...; // 0x10C20084
			// static ...; // 0x10C2007C
			// std::string const &body;
			// std::bitset<17> p;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C1FFB0(body);
			return __result;
		}

		_extern bool _sub_10C20340(std::string const &);
		bool SendTeamMessage(std::string const &body) // 0x10C20340
		{
			mangled_x86(MANGLED_TODO, "?SendTeamMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C2046C
			// static ...; // 0x10C20460
			// static ...; // 0x10C20458
			// std::string const &body;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			// s_game_options *(*const game_options_get)();
			{
				// s_game_options *game;
			}
			// function call : s_game_options *(*const)()
			// function call : s_game_options *(*const)()
			todo("implement");
			bool __result = _sub_10C20340(body);
			return __result;
		}

		_extern bool _sub_10C20620(__int32, bool);
		bool SetPlayerMuteStatus(__int32 peer, bool muted) // 0x10C20620
		{
			mangled_x86(MANGLED_TODO, "?SetPlayerMuteStatus@Chat@Server@@YA_NH_N@Z");
			// bool muted;
			// Blam::Network::Session *session;
			todo("implement");
			bool __result = _sub_10C20620(peer, muted);
			return __result;
		}

		_extern void _sub_10C1DD10();
		void ClearAllPlayersMuteStatus() // 0x10C1DD10
		{
			mangled_x86(MANGLED_TODO, "?ClearAllPlayersMuteStatus@Chat@Server@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			todo("implement");
			_sub_10C1DD10();
		}

		_extern bool _sub_10C1FB70(std::string const &);
		bool SendAndLogServerMessage(std::string const &body) // 0x10C1FB70
		{
			mangled_x86(MANGLED_TODO, "?SendAndLogServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C1FCC4
			// static ...; // 0x10C1FCBC
			// static ...; // 0x10C1FCA4
			// static ...; // 0x10C1FC9C
			// std::string const &body;
			// std::bitset<17> p;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C1FB70(body);
			return __result;
		}

		_extern bool _sub_10C200F0(std::string const &, __int32);
		bool SendServerMessage(std::string const &body, __int32 peer) // 0x10C200F0
		{
			mangled_x86(MANGLED_TODO, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
			// static ...; // 0x10C201E0
			// static ...; // 0x10C201C8
			// static ...; // 0x10C201C0
			// std::string const &body;
			// __int32 peer;
			// std::bitset<17> peers;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C200F0(body, peer);
			return __result;
		}

		_extern bool _sub_10C20230(std::string const &, std::bitset<17>);
		bool SendServerMessage(std::string const &body, std::bitset<17> peers) // 0x10C20230
		{
			mangled_x86(MANGLED_TODO, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$bitset@$0BB@@4@@Z");
			// static ...; // 0x10C202F4
			// static ...; // 0x10C202EC
			// std::string const &body;
			// std::bitset<17> peers;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C20230(body, peers);
			return __result;
		}

		_extern void _sub_10C1D460(std::shared_ptr<Server::Chat::ChatHandler>);
		void AddHandler(std::shared_ptr<Server::Chat::ChatHandler> handler) // 0x10C1D460
		{
			mangled_x86(MANGLED_TODO, "?AddHandler@Chat@Server@@YAXV?$shared_ptr@VChatHandler@Chat@Server@@@std@@@Z");
			// std::shared_ptr<Server::Chat::ChatHandler> handler;
			todo("implement");
			_sub_10C1D460(handler);
		}
	}
}

extern std::string _sub_10C1EBA0(Server::Chat::ChatMessage const &);
namespace Server
{
	namespace Chat
	{
		std::string GetSenderName(Server::Chat::ChatMessage const &message) // 0x10C1EBA0
		{
			mangled_x86(MANGLED_TODO, "?GetSenderName@Chat@Server@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUChatMessage@12@@Z");
			// Server::Chat::ChatMessage const &message;
			todo("implement");
			std::string __result = _sub_10C1EBA0(message);
			return __result;
		}

		extern ChatMessage* _sub_10C1B120(Server::Chat::ChatMessage *const, Server::Chat::ChatMessageType, std::string const &);
		ChatMessage::ChatMessage(Server::Chat::ChatMessageType type, std::string const &body) // 0x10C1B120
		{
			mangled_x86(MANGLED_TODO, "??0ChatMessage@Chat@Server@@QAE@W4ChatMessageType@12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::string const &body;
			todo("implement");
			_sub_10C1B120(this, type, body);
		}
	}
}

/* ---------- private code */

extern ClientSpamStats* _sub_10C1B230(ClientSpamStats *const);
_inline ClientSpamStats::ClientSpamStats() // 0x10C1B230
{
	// `anonymous-namespace'::ClientSpamStats::ClientSpamStats
	// ClientSpamStats *const this;
	todo("implement");
	_sub_10C1B230(this);
}

_inline ChatMessagePacketHandler::~ChatMessagePacketHandler() // 0x10C1BF30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1ChatMessagePacketHandler@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::ChatMessagePacketHandler::~ChatMessagePacketHandler
	// ChatMessagePacketHandler *const this;

	compiler_generated();
}

_extern void _sub_10C204D0(ChatMessagePacketHandler *const, Blam::BitStream *, Server::Chat::ChatMessage const *);
_inline void ChatMessagePacketHandler::Serialize(Blam::BitStream *stream, Server::Chat::ChatMessage const *data) // 0x10C204D0
{
	// `anonymous-namespace'::ChatMessagePacketHandler::Serialize
	// Server::Chat::ChatMessage const *data;
	todo("implement");
	_sub_10C204D0(this, stream, data);
}

_extern bool _sub_10C1DE70(ChatMessagePacketHandler *const, Blam::BitStream *, Server::Chat::ChatMessage *);
_inline bool ChatMessagePacketHandler::Deserialize(Blam::BitStream *stream, Server::Chat::ChatMessage *data) // 0x10C1DE70
{
	// `anonymous-namespace'::ChatMessagePacketHandler::Deserialize
	// Server::Chat::ChatMessage *data;
	todo("implement");
	bool __result = _sub_10C1DE70(this, stream, data);
	return __result;
}

_extern void _sub_10C1EF20(ChatMessagePacketHandler *const, Blam::Network::ObserverChannel *, Patches::CustomPackets::Packet<Server::Chat::ChatMessage> const *);
_inline void ChatMessagePacketHandler::HandlePacket(Blam::Network::ObserverChannel *sender, Patches::CustomPackets::Packet<Server::Chat::ChatMessage> const *packet) // 0x10C1EF20
{
	// `anonymous-namespace'::ChatMessagePacketHandler::HandlePacket
	// Patches::CustomPackets::Packet<Server::Chat::ChatMessage> const *packet;
	// __int32 peer;
	// Blam::Network::Session *session;
	todo("implement");
	_sub_10C1EF20(this, sender, packet);
}

_extern bool _sub_10C1FEA0(__int32, Server::Chat::ChatMessage const &);
bool SendMessagePacket(__int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1FEA0
{
	// `anonymous-namespace'::SendMessagePacket
	// static ...; // 0x10C1FF64
	// static ...; // 0x10C1FF5C
	// __int32 peer;
	// Server::Chat::ChatMessage const &message;
	// Patches::CustomPackets::Packet<Server::Chat::ChatMessage> packet;
	todo("implement");
	bool __result = _sub_10C1FEA0(peer, message);
	return __result;
}

_extern bool _sub_10C1D500(Blam::Network::Session *, __int32, Server::Chat::ChatMessage *, std::bitset<17>);
bool BroadcastMessage(Blam::Network::Session *session, __int32 senderPeer, Server::Chat::ChatMessage *message, std::bitset<17> peers) // 0x10C1D500
{
	// `anonymous-namespace'::BroadcastMessage
	// Blam::Network::Session *session;
	// __int32 senderPeer;
	// Server::Chat::ChatMessage *message;
	// std::bitset<17> peers;
	// Blam::Network::SessionMembership *membership;
	// bool ignore;
	{
		// std::vector<std::shared_ptr<Server::Chat::ChatHandler>,std::allocator<std::shared_ptr<Server::Chat::ChatHandler> > > &<range>$L0;
		// std::shared_ptr<Server::Chat::ChatHandler> *<begin>$L0;
		// std::shared_ptr<Server::Chat::ChatHandler> *<end>$L0;
		{
			// std::shared_ptr<Server::Chat::ChatHandler> &handler;
		}
	}
	{
		// __int32 peer;
	}
	// function call : void (__int32, Server::Chat::ChatMessage *, bool *)
	todo("implement");
	bool __result = _sub_10C1D500(session, senderPeer, message, peers);
	return __result;
}

_extern bool _sub_10C1EC20(Blam::Network::Session *, __int32, std::bitset<17> *);
bool GetTeamPeers(Blam::Network::Session *session, __int32 senderPeer, std::bitset<17> *result) // 0x10C1EC20
{
	// `anonymous-namespace'::GetTeamPeers
	// std::bitset<17> *result;
	// s_game_options *game;
	// __int32 senderTeam;
	// Blam::Network::SessionMembership *membership;
	// s_game_options *(*const game_options_get)();
	{
		// bool sender_is_zombie;
		// Blam::Network::SessionMembership *membership;
		// long player_datum_index;
		// __int32 player_absolute_index;
		{
			// __int32 peer;
			{
				// long peer_player_datum_index;
				// __int32 peer_player_absoulte_index;
			}
		}
	}
	{
		// __int32 peer;
	}
	// function call : s_game_options *(*const)()
	// function call : c_game_engine *(*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	todo("implement");
	bool __result = _sub_10C1EC20(session, senderPeer, result);
	return __result;
}

_extern bool _sub_10C1E9D0(Blam::Network::Session *, __int32, Server::Chat::ChatMessage const &, std::bitset<17> *);
bool GetMessagePeers(Blam::Network::Session *session, __int32 senderPeer, Server::Chat::ChatMessage const &message, std::bitset<17> *result) // 0x10C1E9D0
{
	// `anonymous-namespace'::GetMessagePeers
	// std::bitset<17> *result;
	todo("implement");
	bool __result = _sub_10C1E9D0(session, senderPeer, message, result);
	return __result;
}

extern std::string _sub_10C1EAA0(Blam::Network::Session *, Server::Chat::ChatMessage const &);
std::string GetSenderName(Blam::Network::Session *session, Server::Chat::ChatMessage const &message) // 0x10C1EAA0
{
	// `anonymous-namespace'::GetSenderName
	// Server::Chat::ChatMessage const &message;
	// Blam::Network::PlayerSession &player;
	// Blam::Network::SessionMembership &membership;
	todo("implement");
	std::string __result = _sub_10C1EAA0(session, message);
	return __result;
}

_extern __int32 _sub_10C1D740(unsigned __int32, ClientSpamStats *, Server::Chat::ChatMessage const &);
__int32 CalculateSpamScore(unsigned __int32 ip, ClientSpamStats *stats, Server::Chat::ChatMessage const &message) // 0x10C1D740
{
	// `anonymous-namespace'::CalculateSpamScore
	// Server::Chat::ChatMessage const &message;
	// unsigned long shortScore;
	// unsigned long longScore;
	// Modules::ModuleServer &serverModule;
	todo("implement");
	__int32 __result = _sub_10C1D740(ip, stats, message);
	return __result;
}

_extern bool _sub_10C1D7E0(Blam::Network::Session *, __int32, bool);
bool ChangePlayerMuteStatus(Blam::Network::Session *session, __int32 peer, bool mute) // 0x10C1D7E0
{
	// `anonymous-namespace'::ChangePlayerMuteStatus
	// static ...; // 0x10C1DBEF
	// static ...; // 0x10C1DBE3
	// static ...; // 0x10C1DBDC
	// static ...; // 0x10C1DBD0
	// static ...; // 0x10C1DB88
	// static ...; // 0x10C1DB80
	// Blam::Network::Session *session;
	// __int32 peer;
	// bool mute;
	// bool playerInList;
	// unsigned __int32 ip;
	{
		// std::list<unsigned int,std::allocator<unsigned int> > &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<unsigned int> > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<unsigned int> > > <end>$L0;
		{
			// unsigned __int32 player_ip;
		}
	}
	{
		// std::bitset<17> targetPeers;
	}
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > spamIt;
		// bool cleared;
		{
			// std::bitset<17> targetPeers;
		}
	}
	todo("implement");
	bool __result = _sub_10C1D7E0(session, peer, mute);
	return __result;
}

_extern void _sub_10C209E0(Blam::Network::Session *);
void UnmuteAllPlayers(Blam::Network::Session *session) // 0x10C209E0
{
	// `anonymous-namespace'::UnmuteAllPlayers
	// static ...; // 0x10C20C93
	// static ...; // 0x10C20C8A
	// static ...; // 0x10C20C87
	// static ...; // 0x10C20C80
	// static ...; // 0x10C20C74
	// static ...; // 0x10C20C38
	// static ...; // 0x10C20C30
	// Blam::Network::Session *session;
	{
		// std::list<unsigned int,std::allocator<unsigned int> > &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<unsigned int> > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<unsigned int> > > <end>$L0;
		{
			// unsigned __int32 ip;
			{
				// __int32 peer;
				{
					// __int32 i;
				}
				{
					// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > spamIt;
					// std::bitset<17> targetPeers;
				}
			}
		}
	}
	todo("implement");
	_sub_10C209E0(session);
}

_extern bool _sub_10C1E000(Blam::Network::Session *, __int32, Server::Chat::ChatMessage const &);
bool FloodFilterMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1E000
{
	// `anonymous-namespace'::FloodFilterMessage
	// static ...; // 0x10C1E3E8
	// static ...; // 0x10C1E3C4
	// static ...; // 0x10C1E3BC
	// Blam::Network::Session *session;
	// __int32 peer;
	// Server::Chat::ChatMessage const &message;
	// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,ClientSpamStats> > > > spamIt;
	// unsigned __int32 ip;
	{
		// __int32 score;
		// Modules::ModuleServer &serverModule;
	}
	{
		// std::bitset<17> targetPeers;
	}
	todo("implement");
	bool __result = _sub_10C1E000(session, peer, message);
	return __result;
}

extern std::string _sub_10C1E500(Blam::Network::Session *, __int32, Server::Chat::ChatMessage const &);
std::string GetLogString(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1E500
{
	// `anonymous-namespace'::GetLogString
	// static ...; // 0x10C1E8A1
	// static ...; // 0x10C1E89A
	// static ...; // 0x10C1E897
	// static ...; // 0x10C1E890
	// static ...; // 0x10C1E848
	// static ...; // 0x10C1E840
	// Blam::Network::Session *session;
	// __int32 peer;
	// Server::Chat::ChatMessage const &message;
	// unsigned long long uid;
	// std::basic_ostringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// long long time;
	// std::string sender;
	// __int32 playerIndex;
	// unsigned __int32 ip;
	// char uidStr[17];
	// tm gmTime;
	// std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > now;
	todo("implement");
	std::string __result = _sub_10C1E500(session, peer, message);
	return __result;
}

_extern void _sub_10C1F730(Blam::Network::Session *, __int32, Server::Chat::ChatMessage const &);
void LogMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1F730
{
	// `anonymous-namespace'::LogMessage
	// static ...; // 0x10C1F9D4
	// static ...; // 0x10C1F9CC
	// static ...; // 0x10C1F99C
	// static ...; // 0x10C1F994
	// Blam::Network::Session *session;
	// __int32 peer;
	// Server::Chat::ChatMessage const &message;
	// std::filesystem::path parentDirectory;
	// std::string chatLogFile;
	// std::basic_ofstream<char,std::char_traits<char> > logFile;
	// std::filesystem::path logFilePath;
	// Modules::ModuleServer &serverModule;
	todo("implement");
	_sub_10C1F730(session, peer, message);
}

extern std::string _sub_10C26790(std::string const &);
std::string toLower(std::string const &str) // 0x10C26790
{
	// `anonymous-namespace'::toLower
	// static ...; // 0x10C268B0
	// static ...; // 0x10C268A4
	// static ...; // 0x10C2689C
	// std::string const &str;
	// std::string lowerStr;
	{
		// std::string const &<range>$L0;
		// char const *<begin>$L0;
		// char const *<end>$L0;
		{
			// char c;
		}
	}
	todo("implement");
	std::string __result = _sub_10C26790(str);
	return __result;
}

extern std::string _sub_10C26230(std::string const &, std::string const &, std::string const &);
std::string replaceAllCaseInsensitive(std::string const &str, std::string const &find, std::string const &replace) // 0x10C26230
{
	// `anonymous-namespace'::replaceAllCaseInsensitive
	// static ...; // 0x10C264AC
	// static ...; // 0x10C26488
	// static ...; // 0x10C26480
	// std::string const &str;
	// std::string const &find;
	// std::string const &replace;
	// unsigned __int32 replaceLen;
	// std::string lowerStr;
	// unsigned __int32 findLen;
	// std::string lowerFind;
	// std::string result;
	// unsigned __int32 startPos;
	{
		// unsigned __int32 pos;
	}
	todo("implement");
	std::string __result = _sub_10C26230(str, find, replace);
	return __result;
}

_extern char *_sub_10C255D0(char const *);
char *handleWordFilter(char const *input) // 0x10C255D0
{
	// `anonymous-namespace'::handleWordFilter
	// static ...; // 0x10C25B67
	// static ...; // 0x10C25B59
	// static ...; // 0x10C25B48
	// static ...; // 0x10C25B32
	// static ...; // 0x10C25B27
	// static ...; // 0x10C25B1E
	// static ...; // 0x10C25B16
	// static ...; // 0x10C25B0B
	// static ...; // 0x10C25B02
	// static ...; // 0x10C25AFC
	// static ...; // 0x10C25A84
	// static ...; // 0x10C25A7C
// $LN30:
	// char const *input;
	// std::unordered_set<std::string,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::string> > FilteredWords;
	// std::string FilterReplacementWord;
	// char *output;
	// std::unordered_set<std::string,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::string> > FilteredPatterns;
	// std::string strInput;
	// unsigned __int32 len;
	{
		// std::unordered_set<std::string,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::string> > &<range>$L0;
		// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <begin>$L0;
		// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <end>$L0;
		{
			// std::string const &word;
		}
	}
	{
		// std::string pattern;
		// bool first;
		{
			// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <end>$L1;
			// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <begin>$L1;
			// std::unordered_set<std::string,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::string> > &<range>$L1;
			{
				// std::string const &pat;
			}
		}
		{
			// std::basic_regex<char,std::regex_traits<char> > regex;
		}
	}
	todo("implement");
	char * __result = _sub_10C255D0(input);
	return __result;
}

_extern bool _sub_10C1F070(Blam::Network::Session *, __int32, Server::Chat::ChatMessage const &);
bool HostReceivedMessage(Blam::Network::Session *session, __int32 peer, Server::Chat::ChatMessage const &message) // 0x10C1F070
{
	// `anonymous-namespace'::HostReceivedMessage
	// static ...; // 0x10C1F468
	// static ...; // 0x10C1F45C
	// static ...; // 0x10C1F450
	// static ...; // 0x10C1F414
	// static ...; // 0x10C1F40C
	// Blam::Network::Session *session;
	// __int32 peer;
	// Server::Chat::ChatMessage const &message;
	// __int32 player;
	// std::bitset<17> targetPeers;
	// Server::Chat::ChatMessage broadcastMessage;
	// Modules::ModuleServer &serverModule;
	{
		// unsigned __int32 ip;
		{
			// std::list<unsigned int,std::allocator<unsigned int> > &<range>$L0;
			// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<unsigned int> > > <begin>$L0;
			// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<unsigned int> > > <end>$L0;
			{
				// unsigned __int32 player_ip;
				{
					// std::bitset<17> targetPeers;
				}
			}
		}
	}
	{
		// char const *filtered;
	}
	todo("implement");
	bool __result = _sub_10C1F070(session, peer, message);
	return __result;
}

_extern void _sub_10C1DDA0(Server::Chat::ChatMessage const &);
void ClientReceivedMessage(Server::Chat::ChatMessage const &message) // 0x10C1DDA0
{
	// `anonymous-namespace'::ClientReceivedMessage
	// Server::Chat::ChatMessage const &message;
	{
		// std::vector<std::shared_ptr<Server::Chat::ChatHandler>,std::allocator<std::shared_ptr<Server::Chat::ChatHandler> > > &<range>$L0;
		// std::shared_ptr<Server::Chat::ChatHandler> *<begin>$L0;
		// std::shared_ptr<Server::Chat::ChatHandler> *<end>$L0;
		{
			// std::shared_ptr<Server::Chat::ChatHandler> &handler;
		}
	}
	// function call : void (Server::Chat::ChatMessage const &)
	todo("implement");
	_sub_10C1DDA0(message);
}

_extern bool _sub_10C1FD20(Blam::Network::Session *, Server::Chat::ChatMessage const &);
bool SendClientMessage(Blam::Network::Session *session, Server::Chat::ChatMessage const &message) // 0x10C1FD20
{
	// `anonymous-namespace'::SendClientMessage
	// Server::Chat::ChatMessage const &message;
	todo("implement");
	bool __result = _sub_10C1FD20(session, message);
	return __result;
}

_inline ChatMessagePacketHandler::ChatMessagePacketHandler() // 0x10C1B1D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0ChatMessagePacketHandler@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::ChatMessagePacketHandler::ChatMessagePacketHandler
	// ChatMessagePacketHandler *const this;

	compiler_generated();
}

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
