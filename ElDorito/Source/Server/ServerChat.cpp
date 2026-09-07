/* ---------- headers */

#include "Server/ServerChat.hpp"
#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
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
#include "Patches/CustomPackets.hpp"
#include "Utils/Bits.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
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
		struct Session;
	}
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
namespace
{
	struct ClientSpamStats;
	class ChatMessagePacketHandler;
}

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

namespace
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
namespace Server
{
	namespace Chat
	{
		typedef std::bitset<17> PeerBitSet;
	}
}

namespace
{

}
namespace Patches
{
	namespace CustomPackets
	{
		typedef Packet<Server::Chat::ChatMessage> ChatMessagePacket;
	}
}

namespace
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
/* ---------- prototypes */

namespace Server
{
	namespace Chat
	{
		extern void Initialize();
		extern void Tick();
		extern bool SendGlobalMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body);
		extern bool SendServerMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body);
		extern bool SendTeamMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body);
		extern bool SetPlayerMuteStatus(__int32 peer, bool muted);
		extern void ClearAllPlayersMuteStatus();
		extern bool SendAndLogServerMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body);
		extern bool SendServerMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body, __int32 peer);
		extern bool SendServerMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body, std::bitset<17> peers);
		extern void AddHandler(std::shared_ptr<Server::Chat::ChatHandler> handler);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetSenderName(Server::Chat::ChatMessage const &message);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern std::shared_ptr<Patches::CustomPackets::PacketSender<Server::Chat::ChatMessage> > PacketSender; // 0x12467F38
	extern unsigned long LastTimeMs; // 0x12467F40
	extern unsigned long SpamUpdateMs; // 0x12467F44
	extern std::vector<std::shared_ptr<Server::Chat::ChatHandler>,std::allocator<std::shared_ptr<Server::Chat::ChatHandler> > > chatHandlers; // 0x12467EF4
	extern std::list<unsigned int,std::allocator<unsigned int> > MutedPlayers; // 0x12467F04
}
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

		_extern bool _sub_10C1FDB0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool SendGlobalMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body) // 0x10C1FDB0
		{
			mangled_x86(MANGLED_TODO, "?SendGlobalMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C1FE60
			// static ...; // 0x10C1FE54
			// static ...; // 0x10C1FE4C
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C1FDB0(body);
			return __result;
		}

		_extern bool _sub_10C1FFB0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool SendServerMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body) // 0x10C1FFB0
		{
			mangled_x86(MANGLED_TODO, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C200A4
			// static ...; // 0x10C2009C
			// static ...; // 0x10C20084
			// static ...; // 0x10C2007C
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
			// std::bitset<17> p;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C1FFB0(body);
			return __result;
		}

		_extern bool _sub_10C20340(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool SendTeamMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body) // 0x10C20340
		{
			mangled_x86(MANGLED_TODO, "?SendTeamMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C2046C
			// static ...; // 0x10C20460
			// static ...; // 0x10C20458
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
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

		_extern bool _sub_10C1FB70(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool SendAndLogServerMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body) // 0x10C1FB70
		{
			mangled_x86(MANGLED_TODO, "?SendAndLogServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C1FCC4
			// static ...; // 0x10C1FCBC
			// static ...; // 0x10C1FCA4
			// static ...; // 0x10C1FC9C
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
			// std::bitset<17> p;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C1FB70(body);
			return __result;
		}

		_extern bool _sub_10C200F0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, __int32);
		bool SendServerMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body, __int32 peer) // 0x10C200F0
		{
			mangled_x86(MANGLED_TODO, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
			// static ...; // 0x10C201E0
			// static ...; // 0x10C201C8
			// static ...; // 0x10C201C0
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
			// __int32 peer;
			// std::bitset<17> peers;
			// Blam::Network::Session *session;
			// Server::Chat::ChatMessage message;
			todo("implement");
			bool __result = _sub_10C200F0(body, peer);
			return __result;
		}

		_extern bool _sub_10C20230(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::bitset<17>);
		bool SendServerMessage(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body, std::bitset<17> peers) // 0x10C20230
		{
			mangled_x86(MANGLED_TODO, "?SendServerMessage@Chat@Server@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$bitset@$0BB@@4@@Z");
			// static ...; // 0x10C202F4
			// static ...; // 0x10C202EC
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
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

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C1EBA0(Server::Chat::ChatMessage const &);
namespace Server
{
	namespace Chat
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetSenderName(Server::Chat::ChatMessage const &message) // 0x10C1EBA0
		{
			mangled_x86(MANGLED_TODO, "?GetSenderName@Chat@Server@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUChatMessage@12@@Z");
			// Server::Chat::ChatMessage const &message;
			todo("implement");
			std::string __result = _sub_10C1EBA0(message);
			return __result;
		}

		extern ChatMessage* _sub_10C1B120(Server::Chat::ChatMessage *const, Server::Chat::ChatMessageType, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		ChatMessage::ChatMessage(Server::Chat::ChatMessageType type, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body) // 0x10C1B120
		{
			mangled_x86(MANGLED_TODO, "??0ChatMessage@Chat@Server@@QAE@W4ChatMessageType@12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body;
			todo("implement");
			_sub_10C1B120(this, type, body);
		}
	}
}

/* ---------- private code */
