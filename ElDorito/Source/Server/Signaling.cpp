/* ---------- headers */

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
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Network.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Bits.hpp"
#include "Utils/DewritoReader.hpp"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/UPnP.hpp"
#include "Utils/Uri.hpp"
#include "Utils/WebSocket.hpp"
#include "Web/Ui/Screen.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/bind/bind.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/numeric/conversion/converter_policies.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/regex/v5/match_flags.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/system/errc.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/throw_exception.hpp>
#include <boost/winapi/error_handling.hpp>
#include <websocketpp/base64/base64.hpp>
#include <websocketpp/close.hpp>
#include <websocketpp/common/asio.hpp>
#include <websocketpp/common/md5.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/connection.hpp>
#include <websocketpp/extensions/extension.hpp>
#include <websocketpp/extensions/permessage_deflate/disabled.hpp>
#include <websocketpp/frame.hpp>
#include <websocketpp/http/constants.hpp>
#include <websocketpp/http/parser.hpp>
#include <websocketpp/http/request.hpp>
#include <websocketpp/http/response.hpp>
#include <websocketpp/message_buffer/alloc.hpp>
#include <websocketpp/message_buffer/message.hpp>
#include <websocketpp/processors/base.hpp>
#include <websocketpp/processors/hybi00.hpp>
#include <websocketpp/processors/hybi07.hpp>
#include <websocketpp/processors/hybi08.hpp>
#include <websocketpp/processors/hybi13.hpp>
#include <websocketpp/processors/processor.hpp>
#include <websocketpp/random/none.hpp>
#include <websocketpp/roles/server_endpoint.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/sha1/sha1.hpp>
#include <websocketpp/utf8_validator.hpp>
#include <websocketpp/utilities.hpp>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/system/detail/throws.hpp>
#include <mswsockdef.h>
#include <pplcancellation_token.h>
#include <pplinterface.h>
#include <ppltasks.h>
#include <ppltaskscheduler.h>
#include <pplwin.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <ws2ipdef.h>
#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <forward_list>
#include <functional>
#include <future>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <queue>
#include <ratio>
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
		struct Session;
	}
}
namespace hades_file_local
{
	struct coninfo;
	struct WebSocketPacketData;
	class WebSocketPacketHandler;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
	namespace WebSocket {}
	using namespace Utils::WebSocket;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Signaling {}
	using namespace Server::Signaling;
}

namespace asio_require_fn {}
using namespace ::asio_require_fn;
namespace Modules {}
using namespace ::Modules;
namespace asio_query_fn {}
using namespace ::asio_query_fn;
namespace asio_require_concept_fn {}
using namespace ::asio_require_concept_fn;
namespace asio_execution_bulk_execute_fn {}
using namespace ::asio_execution_bulk_execute_fn;
namespace asio_execution_submit_fn {}
using namespace ::asio_execution_submit_fn;
namespace asio_execution_set_value_fn {}
using namespace ::asio_execution_set_value_fn;
namespace asio_prefer_fn {}
using namespace ::asio_prefer_fn;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace asio_execution_set_error_fn {}
using namespace ::asio_execution_set_error_fn;
namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace asio_execution_start_fn {}
using namespace ::asio_execution_start_fn;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace CustomPackets {}
	using namespace Patches::CustomPackets;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace asio_execution_execute_fn {}
using namespace ::asio_execution_execute_fn;
namespace asio_execution_set_done_fn {}
using namespace ::asio_execution_set_done_fn;
namespace asio_execution_schedule_fn {}
using namespace ::asio_execution_schedule_fn;
namespace asio_execution_connect_fn {}
using namespace ::asio_execution_connect_fn;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

namespace hades_file_local
{
	enum RejectionReason
	{
		eBadPassword = 0,
		eSessionHasBadInfo,
		eNone,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

namespace hades_file_local
{
	struct coninfo
	{
		std::string uid; // 0x0
		std::string subprotocol; // 0x1C
		bool authed; // 0x38
		unsigned char __pad0[3]; // 0x39
		__int32 peerIdx; // 0x3C
		coninfo(coninfo &); /* compiler_generated() */
		coninfo(coninfo const &); /* compiler_generated() */
		coninfo(); /* compiler_generated() */
		~coninfo(); /* compiler_generated() */
		coninfo &operator=(coninfo &); /* compiler_generated() */
		coninfo &operator=(coninfo const &); /* compiler_generated() */
	};
	static_assert(sizeof(coninfo) == 64, "Invalid coninfo size");

	//@@anonymous-namespace@@
	#pragma pack(push, 4)
	struct WebSocketPacketData
	{
		char echoString[9]; // 0x0
		unsigned char __pad0[1]; // 0x9
		unsigned short serverPort; // 0xA
	};
	#pragma pack(pop)
	static_assert(sizeof(WebSocketPacketData) == 12, "Invalid WebSocketPacketData size");

	//@@anonymous-namespace@@

	//@@anonymous-namespace@@

	//@@anonymous-namespace@@
	class WebSocketPacketHandler :
		public Patches::CustomPackets::PacketHandler<WebSocketPacketData>
	{
	private:
		virtual void Serialize(Blam::BitStream *, WebSocketPacketData const *);
		virtual bool Deserialize(Blam::BitStream *, WebSocketPacketData *);
		virtual void HandlePacket(Blam::Network::ObserverChannel *, Patches::CustomPackets::Packet<WebSocketPacketData> const *);
	public:
		WebSocketPacketHandler(WebSocketPacketHandler &); /* compiler_generated() */
		WebSocketPacketHandler(WebSocketPacketHandler const &); /* compiler_generated() */
		WebSocketPacketHandler(); /* compiler_generated() */
		virtual ~WebSocketPacketHandler(); /* compiler_generated() */
		WebSocketPacketHandler &operator=(WebSocketPacketHandler &); /* compiler_generated() */
		WebSocketPacketHandler &operator=(WebSocketPacketHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(WebSocketPacketHandler) == 4, "Invalid WebSocketPacketHandler size");

}
using namespace hades_file_local;
typedef char const *LPCCH;
typedef wchar_t const *LPCWCH;
namespace Patches
{
	namespace CustomPackets
	{
		typedef Packet<WebSocketPacketData> WebSocketPacket;
	}
}

/* ---------- prototypes */

namespace Server
{
	namespace Signaling
	{
		extern void Initialize();
		extern void StartServer();
		extern void StopServer();
		extern void Tick();
		extern void SendPeerPassword(__int32 playerIndex);
		extern void RemovePeer(__int32 peerIndex);
		extern std::string GetPassword();
		extern unsigned short GetPort();
	}
}

void LifeCycleChanged(Blam::Network::LifeCycleState state);
std::string ServerPortJson();
void ForceStopServer();
bool OnValidate(websocketpp::server<Utils::WebSocket::Config> *signalServer, std::weak_ptr<void> hdl);
void HandleMessage(websocketpp::server<Utils::WebSocket::Config> *signalServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg);
void OnMessage(websocketpp::server<Utils::WebSocket::Config> *signalServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg);
void OnClose(websocketpp::server<Utils::WebSocket::Config> *signalServer, std::weak_ptr<void> hdl);
RejectionReason ProcessPassword(char const *echo, coninfo &info);
void CreatePasswords();
void ResetPassword(__int32 peerIndex);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern websocketpp::server<Utils::WebSocket::Config> signalServer; // 0x12467F80
	extern std::string currentPassword; // 0x12468268
	extern std::map<std::weak_ptr<void>,coninfo,std::owner_less<std::weak_ptr<void> > > connectedSockets; // 0x12468284
	extern std::string authStrings[17]; // 0x12468290
	extern rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> iceServers; // 0x12468470
	extern unsigned short port; // 0x124684F4
	extern std::shared_ptr<Patches::CustomPackets::PacketSender<WebSocketPacketData> > wspsender; // 0x124684F8
	extern std::shared_ptr<WebSocketPacketHandler> wsphandler; // 0x12468500
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace Signaling
	{
		_extern void _sub_10C2E280();
		void Initialize() // 0x10C2E280
		{
			mangled_x86(MANGLED_TODO, "?Initialize@Signaling@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C2E5A4
			// static ...; // 0x10C2E598
			// static ...; // 0x10C2E590
		// $LN17:
			{
				// websocketpp::exception const &e;
			}
			// function call : char const *() const
			todo("implement");
			_sub_10C2E280();
		}

		_extern void _sub_10C305F0();
		void StartServer() // 0x10C305F0
		{
			mangled_x86(MANGLED_TODO, "?StartServer@Signaling@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C308F6
			// static ...; // 0x10C308F4
			// static ...; // 0x10C308DC
			// static ...; // 0x10C308D4
		// $LN16:
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> dewrito;
			// Blam::Network::Session *session;
			{
				// websocketpp::exception const &e;
			}
			// function call : char const *() const
			todo("implement");
			_sub_10C305F0();
		}

		_extern void _sub_10C309D0();
		void StopServer() // 0x10C309D0
		{
			mangled_x86(MANGLED_TODO, "?StopServer@Signaling@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10C30BA8
			// static ...; // 0x10C30B9F
			// static ...; // 0x10C30B98
			// static ...; // 0x10C30B74
			// static ...; // 0x10C30B6C
			{
				// std::map<std::weak_ptr<void>,coninfo,std::owner_less<std::weak_ptr<void> > > &<range>$L0;
				// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::weak_ptr<void> const ,coninfo> > > > <begin>$L0;
				// std::_Default_sentinel <end>$L0;
				{
					// std::pair<std::weak_ptr<void> const ,coninfo> client;
				}
			}
			todo("implement");
			_sub_10C309D0();
		}

		void Tick() // 0x10C30C30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Signaling@Server@@YAXXZ");
			// procedure flags: nofpo

			signalServer.poll();
		}

		_extern void _sub_10C2FC30(__int32);
		void SendPeerPassword(__int32 playerIndex) // 0x10C2FC30
		{
			mangled_x86(MANGLED_TODO, "?SendPeerPassword@Signaling@Server@@YAXH@Z");
			// static ...; // 0x10C2FD34
			// static ...; // 0x10C2FD28
			// static ...; // 0x10C2FD20
			// __int32 playerIndex;
			// Blam::Network::Session *session;
			// Patches::CustomPackets::Packet<WebSocketPacketData> packet;
			// __int32 peerIdx;
			todo("implement");
			_sub_10C2FC30(playerIndex);
		}

		_extern void _sub_10C2F520(__int32);
		void RemovePeer(__int32 peerIndex) // 0x10C2F520
		{
			mangled_x86(MANGLED_TODO, "?RemovePeer@Signaling@Server@@YAXH@Z");
			// static ...; // 0x10C2FA05
			// static ...; // 0x10C2F9FA
			// static ...; // 0x10C2F9F1
			// static ...; // 0x10C2F9EA
			// static ...; // 0x10C2F9E3
			// static ...; // 0x10C2F9DC
			// static ...; // 0x10C2F9D1
			// static ...; // 0x10C2F9C8
			// static ...; // 0x10C2F9BC
			// static ...; // 0x10C2F9B8
			// static ...; // 0x10C2F940
			// static ...; // 0x10C2F938
			// __int32 peerIndex;
			// std::vector<std::weak_ptr<void> > handlesToClose;
			{
				// std::map<std::weak_ptr<void>,coninfo,std::owner_less<std::weak_ptr<void> > > &<range>$L0;
				// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::weak_ptr<void> const ,coninfo> > > > <begin>$L0;
				// std::_Default_sentinel <end>$L0;
				{
					// std::pair<std::weak_ptr<void> const ,coninfo> client;
					{
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
						{
							// std::_Default_sentinel <end>$L1;
							// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::weak_ptr<void> const ,coninfo> > > > <begin>$L1;
							// std::map<std::weak_ptr<void>,coninfo,std::owner_less<std::weak_ptr<void> > > &<range>$L1;
							{
								// std::pair<std::weak_ptr<void> const ,coninfo> otherClient;
							}
						}
					}
				}
			}
			{
				// std::weak_ptr<void> *<end>$L2;
				// std::vector<std::weak_ptr<void> > &<range>$L2;
				// std::weak_ptr<void> *<begin>$L2;
				{
					// std::weak_ptr<void> hdl;
				}
			}
			todo("implement");
			_sub_10C2F520(peerIndex);
		}
	}
}

extern std::string _sub_10C2CEC0();
namespace Server
{
	namespace Signaling
	{
		std::string GetPassword() // 0x10C2CEC0
		{
			mangled_x86(MANGLED_TODO, "?GetPassword@Signaling@Server@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			todo("implement");
			std::string __result = _sub_10C2CEC0();
			return __result;
		}

		unsigned short GetPort() // 0x10C2CF30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPort@Signaling@Server@@YAGXZ");
			// procedure flags: nofpo

			return port;
		}
	}
}

/* ---------- private code */

void LifeCycleChanged(Blam::Network::LifeCycleState state) // 0x10C2E670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LifeCycleChanged@@YAXW4LifeCycleState@Network@Blam@@@Z");
	// `anonymous-namespace'::LifeCycleChanged
	// Blam::Network::LifeCycleState state;

	if (state == Blam::Network::eLifeCycleStateNone || state == Blam::Network::eLifeCycleStateLeaving)
	{
		currentPassword = "not-connected";
	}
}

_extern void _sub_10C2FD80(WebSocketPacketHandler *const, Blam::BitStream *, WebSocketPacketData const *);
void WebSocketPacketHandler::Serialize(Blam::BitStream *stream, WebSocketPacketData const *data) // 0x10C2FD80
{
	// `anonymous-namespace'::WebSocketPacketHandler::Serialize
	// WebSocketPacketData const *data;
	todo("implement");
	_sub_10C2FD80(this, stream, data);
}

_extern bool _sub_10C2CCF0(WebSocketPacketHandler *const, Blam::BitStream *, WebSocketPacketData *);
bool WebSocketPacketHandler::Deserialize(Blam::BitStream *stream, WebSocketPacketData *data) // 0x10C2CCF0
{
	// `anonymous-namespace'::WebSocketPacketHandler::Deserialize
	// WebSocketPacketData *data;
	todo("implement");
	bool __result = _sub_10C2CCF0(this, stream, data);
	return __result;
}

void WebSocketPacketHandler::HandlePacket(Blam::Network::ObserverChannel *sender, Patches::CustomPackets::Packet<WebSocketPacketData> const *packet) // 0x10C2E030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandlePacket@WebSocketPacketHandler@hades_file_local@@EAEXPAUObserverChannel@Network@Blam@@PBU?$Packet@UWebSocketPacketData@hades_file_local@@@CustomPackets@Patches@@@Z");
	// `anonymous-namespace'::WebSocketPacketHandler::HandlePacket
	// Patches::CustomPackets::Packet<WebSocketPacketData> const *packet;
	// Blam::Network::Session *session;
	// __int32 sendingPeer;

	auto *session = Blam::Network::GetActiveSession();
	auto sendingPeer = session->GetChannelPeer(sender);
	if (sendingPeer < 0)
		return;

	if (session->IsHost())
		return;

	currentPassword = std::string(packet->Data.echoString);
	port = packet->Data.serverPort;

	Web::Ui::ScreenLayer::Notify("signal-ready", ServerPortJson(), true);
}

std::string ServerPortJson() // 0x10C2FE80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ServerPortJson@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// `anonymous-namespace'::ServerPortJson
	// procedure flags: nofpo
	// static ...; // 0x10C3033A
	// static ...; // 0x10C30333
	// static ...; // 0x10C30330
	// static ...; // 0x10C3030C
	// static ...; // 0x10C30304
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::string ip;
	// Blam::Network::Session *session;

	auto session = Blam::Network::GetActiveSession();
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	buffer.Clear();

	writer.StartObject();
	writer.Key("server");
	std::string ip = "";
	if (!session->GetServerIPAddress().ToString().compare("0.0.0.0") || !session->GetServerIPAddress().ToString().compare("1.0.0.0"))
		ip = "127.0.0.1:" + std::to_string(Server::Signaling::GetPort());
	else
		ip = session->GetServerIPAddress().ToString() + ":" + std::to_string(Server::Signaling::GetPort());
	writer.String(ip.c_str());

	writer.Key("password");
	writer.String(Server::Signaling::GetPassword().c_str());
	writer.EndObject();
	return buffer.GetString();
}

void ForceStopServer() // 0x10C2CE00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ForceStopServer@@YAXXZ");
	// `anonymous-namespace'::ForceStopServer
	// procedure flags: nofpo

	if (signalServer.is_listening())
	{
		signalServer.stop();
	}
}

_extern bool _sub_10C2ED70(websocketpp::server<Utils::WebSocket::Config> *, std::weak_ptr<void>);
bool OnValidate(websocketpp::server<Utils::WebSocket::Config> *signalServer, std::weak_ptr<void> hdl) // 0x10C2ED70
{
	// `anonymous-namespace'::OnValidate
	// static ...; // 0x10C2EF6D
	// static ...; // 0x10C2EF68
	// static ...; // 0x10C2EF44
	// static ...; // 0x10C2EF3C
	// websocketpp::server<Utils::WebSocket::Config> *signalServer;
	// std::weak_ptr<void> hdl;
	// std::vector<std::string> subprotocols;
	// coninfo info;
	// std::shared_ptr<websocketpp::connection<Utils::WebSocket::Config> > connection;
	todo("implement");
	bool __result = _sub_10C2ED70(signalServer, hdl);
	return __result;
}

_extern void _sub_10C2CF50(websocketpp::server<Utils::WebSocket::Config> *, std::weak_ptr<void>, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> >);
void HandleMessage(websocketpp::server<Utils::WebSocket::Config> *signalServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg) // 0x10C2CF50
{
	// `anonymous-namespace'::HandleMessage
	// static ...; // 0x10C2DCBA
	// static ...; // 0x10C2DCB6
	// static ...; // 0x10C2DCB0
	// static ...; // 0x10C2DCA9
	// static ...; // 0x10C2DCA2
	// static ...; // 0x10C2DC9B
	// static ...; // 0x10C2DC90
	// static ...; // 0x10C2DC87
	// static ...; // 0x10C2DC82
	// static ...; // 0x10C2DC7B
	// static ...; // 0x10C2DC74
	// static ...; // 0x10C2DC6D
	// static ...; // 0x10C2DC62
	// static ...; // 0x10C2DC59
	// static ...; // 0x10C2DC54
	// static ...; // 0x10C2DB88
	// static ...; // 0x10C2DB80
	// websocketpp::server<Utils::WebSocket::Config> *signalServer;
	// std::weak_ptr<void> hdl;
	// std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg;
	// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::weak_ptr<void> const ,coninfo> > > > it;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> doc;
	// std::string proto;
	// rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator;
	{
		// RejectionReason reject;
		{
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
		}
	}
	{
		// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > setUid;
		// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
		{
			// std::map<std::weak_ptr<void>,coninfo,std::owner_less<std::weak_ptr<void> > > &<range>$L0;
			// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::weak_ptr<void> const ,coninfo> > > > <begin>$L0;
			// std::_Default_sentinel <end>$L0;
			{
				// std::pair<std::weak_ptr<void> const ,coninfo> peer;
			}
		}
	}
	{
		{
			// std::_Default_sentinel <end>$L1;
			// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::weak_ptr<void> const ,coninfo> > > > <begin>$L1;
			// std::map<std::weak_ptr<void>,coninfo,std::owner_less<std::weak_ptr<void> > > &<range>$L1;
			{
			}
		}
	}
	todo("implement");
	_sub_10C2CF50(signalServer, hdl, msg);
}

_extern void _sub_10C2EBC0(websocketpp::server<Utils::WebSocket::Config> *, std::weak_ptr<void>, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> >);
void OnMessage(websocketpp::server<Utils::WebSocket::Config> *signalServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg) // 0x10C2EBC0
{
	// `anonymous-namespace'::OnMessage
	// static ...; // 0x10C2ECF8
// $LN12:
	// websocketpp::server<Utils::WebSocket::Config> *signalServer;
	// std::weak_ptr<void> hdl;
	// std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg;
	{
		// std::exception const &e;
	}
	// function call : char const *() const
	todo("implement");
	_sub_10C2EBC0(signalServer, hdl, msg);
}

_extern void _sub_10C2E730(websocketpp::server<Utils::WebSocket::Config> *, std::weak_ptr<void>);
void OnClose(websocketpp::server<Utils::WebSocket::Config> *signalServer, std::weak_ptr<void> hdl) // 0x10C2E730
{
	// `anonymous-namespace'::OnClose
	// static ...; // 0x10C2EACB
	// static ...; // 0x10C2EAC4
	// static ...; // 0x10C2EABB
	// static ...; // 0x10C2EAB0
	// static ...; // 0x10C2EAA7
	// static ...; // 0x10C2EAA0
	// static ...; // 0x10C2EA4C
	// static ...; // 0x10C2EA44
	// websocketpp::server<Utils::WebSocket::Config> *signalServer;
	// std::weak_ptr<void> hdl;
	// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::weak_ptr<void> const ,coninfo> > > > it;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::string subproto;
	{
		// std::map<std::weak_ptr<void>,coninfo,std::owner_less<std::weak_ptr<void> > > &<range>$L0;
		// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::weak_ptr<void> const ,coninfo> > > > <begin>$L0;
		// std::_Default_sentinel <end>$L0;
		{
			// std::pair<std::weak_ptr<void> const ,coninfo> client;
		}
	}
	todo("implement");
	_sub_10C2E730(signalServer, hdl);
}

extern RejectionReason _sub_10C2F010(char const *, coninfo &);
RejectionReason ProcessPassword(char const *echo, coninfo &info) // 0x10C2F010
{
	// `anonymous-namespace'::ProcessPassword
	// static ...; // 0x10C2F2FB
	// static ...; // 0x10C2F2F8
	// static ...; // 0x10C2F2D4
	// static ...; // 0x10C2F2CC
	// char const *echo;
	// coninfo &info;
	// Blam::Network::Session *session;
	// __int32 peerIdx;
	{
		// char uid[17];
		// std::stringstream ss;
		// std::string name;
	}
	todo("implement");
	RejectionReason __result = _sub_10C2F010(echo, info);
	return __result;
}

_extern void _sub_10C2CC60();
void CreatePasswords() // 0x10C2CC60
{
	// `anonymous-namespace'::CreatePasswords
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	todo("implement");
	_sub_10C2CC60();
}

_extern void _sub_10C2FB60(__int32);
void ResetPassword(__int32 peerIndex) // 0x10C2FB60
{
	// `anonymous-namespace'::ResetPassword
	// __int32 peerIndex;
	todo("implement");
	_sub_10C2FB60(peerIndex);
}

// mangled_x86(MANGLED_DEFAULT, "??0WebSocketPacketHandler@hades_file_local@@QAE@XZ"); no body to assert in
_inline WebSocketPacketHandler::WebSocketPacketHandler() = default; // 0x10C2B4F0

// mangled_x86(MANGLED_DEFAULT, "??0coninfo@hades_file_local@@QAE@AAU01@@Z"); no body to assert in
_inline coninfo::coninfo(coninfo &__that) = default; // 0x10C2B550

// mangled_x86(MANGLED_DEFAULT, "??0coninfo@hades_file_local@@QAE@ABU01@@Z"); no body to assert in
_inline coninfo::coninfo(coninfo const &__that) = default; // 0x10C2B600

_inline WebSocketPacketHandler::~WebSocketPacketHandler() // 0x10C2BF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1WebSocketPacketHandler@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::WebSocketPacketHandler::~WebSocketPacketHandler
	// WebSocketPacketHandler *const this;

	compiler_generated();
}

// mangled_x86(MANGLED_DEFAULT, "??1coninfo@hades_file_local@@QAE@XZ"); no body to assert in
_inline coninfo::~coninfo() = default; // 0x10C2BFD0

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Blam::BitStream::WriteUnsigned<unsigned short>(unsigned short, unsigned short, unsigned short);
