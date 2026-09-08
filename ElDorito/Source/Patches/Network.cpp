/* ---------- headers */

#include "Patches/Network.hpp"
#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/BitStream.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/networking/logic/network_broadcast_search.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/transport/transport.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/map_variant_loader.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Server/BanList.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "ThirdParty/rapidjson/allocators.h"
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
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <WinSock2.h>
#include <WS2tcpip.h>
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
#include <ws2ipdef.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_network_session;
class c_network_session_membership;
struct begin;
struct c_network_message_handler;
struct end;
struct s_available_session;
struct s_map_variant;
struct s_network_session_membership_update_message;
struct s_network_session_shared_membership;
struct s_player_configuration;
struct s_player_configuration_from_client;
struct s_transport_address;
namespace Blam
{
	class BitStream;
}
namespace Blam
{
	namespace Network
	{
		struct NetworkAddress;
		struct PeerInfo;
		struct PlayerSession;
		struct PongPacket;
		struct Session;
		struct SessionMembership;
	}
}
namespace Modules
{
	class ModuleServer;
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
	class BanList;
	class StatsServersBanList;
}
namespace hades_file_local
{
	struct struc_703;
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
	namespace Signaling {}
	using namespace Server::Signaling;
	namespace InfoServer {}
	using namespace Server::InfoServer;
	namespace Stats {}
	using namespace Server::Stats;
	namespace HsGlobalSync {}
	using namespace Server::HsGlobalSync;
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

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

namespace Patches {}
using namespace ::Patches;
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
	struct struc_703
	{
		__int32 field_0; // 0x0
		__int32 field_4; // 0x4
		__int32 WindowMin; // 0x8
		__int32 WindowMax; // 0xC
		__int32 field_10; // 0x10
	};
	static_assert(sizeof(struc_703) == 20, "Invalid struc_703 size");
}
using namespace hades_file_local;
namespace Patches
{
	namespace Network
	{
		typedef std::function<void __cdecl(s_map_variant *)> MapVariantRequestChangeCallback;
		typedef std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> PongCallback;
	}
}

/* ---------- prototypes */

namespace Patches
{
	namespace Network
	{
		extern void ApplyAll();
		extern void ForceDedicated();
		extern void ForceBotClient();
		extern unsigned short OnPong(std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> callback);
		extern void OnLifeCycleStateChanged(std::function<void __cdecl(enum Blam::Network::LifeCycleState)> callback);
		extern void RegisterSessionListener(std::shared_ptr<Patches::Network::NetworkSessionListener> observer);
		extern void OnMapVariantRequestChange(std::function<void __cdecl(s_map_variant *)> callback);
		extern void Tick();
	}
}

unsigned long Network_managed_session_create_session_internalHook(__int32 a1, __int32 a2);
void network_session_send_peer_establish_hook(c_network_session *thisPtr, void *unused, long transmission_type, long peer_index, long message_type, long data_length, void const *data);
char *Network_GetIPStringFromInAddr(void *inaddr);
unsigned __int32 GetPlayerPropertiesPacketSize();
void RegisterPlayerPropertiesPacketHook(void *thisPtr, void *unused, __int32 packetId, char const *packetName, __int32 arg8, __int32 size1, __int32 size2, void *serializeFunc, void *deserializeFunc, __int32 arg1C, __int32 arg20);
bool IsNameNotAllowed(std::string name);
void SanitizePlayerName(wchar_t *name);
void ApplyPlayerPropertiesExtended(Blam::Network::SessionMembership *thisPtr, void *unused, __int32 playerIndex, unsigned __int32 arg4, unsigned __int32 arg8, unsigned char *data, unsigned __int32 arg10);
bool Network_leader_request_boot_machineHook(void *thisPtr, void *unused, Blam::Network::PeerInfo *peer, __int32 reason);
bool Network_session_handle_join_requestHook(Blam::Network::Session *thisPtr, void *unused, Blam::Network::NetworkAddress const &address, void *request);
__int32 Network_GetMaxPlayersHook();
__int32 Pregame_Lobby_Max_Player_Count_Offline_hook();
bool PeerRequestPlayerDesiredPropertiesUpdateHook(Blam::Network::Session *thisPtr, void *unused, unsigned __int32 arg0, unsigned __int32 arg4, s_player_configuration_from_client *properties, unsigned __int32 argC);
bool Network_Session_Membership__Add_Peer_Hook(c_network_session_membership *thisptr, void *unused, long peer_index, Blam::Network::PeerConnectionState connection_state, long version, void *xnaddr, unsigned long long unknown_nonce, unsigned long long join_nonce);
char Network_Session_Membership_Remove_Peer_Hook(c_network_session_membership *thisptr, void *unused, long peer_index);
void SerializePlayerPropertiesHook(Blam::BitStream *stream, unsigned char *buffer, bool flag);
bool DeserializePlayerPropertiesHook(Blam::BitStream *stream, unsigned char *buffer, bool flag);
char Network_state_end_game_write_stats_enterHook(void *thisPtr, __int32 unused, __int32 a2, __int32 a3, __int32 a4);
char Network_state_leaving_enterHook(void *thisPtr, __int32 unused, __int32 a2, __int32 a3, __int32 a4);
void c_network_session__host_connection_refused_hook(void *session, void *unused, __int32 a2, __int32 type);
void PongReceivedHookImpl(Blam::Network::NetworkAddress const &from, Blam::Network::PongPacket const &pong, unsigned __int32 latency);
void PongReceivedHook();
void LifeCycleStateChangedHookImpl(Blam::Network::LifeCycleState newState);
void LifeCycleStateChangedHook();
void GetTextureDimensionsHook();
bool Network_GetEndpointHook(char *thisPtr, void *unused);
char Network_session_join_remote_sessionHook(void *thisPtr, __int32 unused, char a2, __int32 a3, __int32 a4, __int32 a5, __int32 a6, __int32 a7, __int32 a8, __int32 a9, __int32 a10, __int32 a11, void *a12, __int32 a13, __int32 a14);
__int32 Network_session_initiate_leave_protocolHook(void *thisPtr, __int32 unused, char forceClose);
__int32 Network_session_parameters_clearHook(void *thisPtr, __int32 unused);
__int32 Network_session_remove_peerHook(Blam::Network::SessionMembership *membership, void *unused, __int32 peerIndex);
bool Network_session_parameter_countdown_timer_request_change_hook(void *thisPtr, void *unused, __int32 state, __int32 value);
bool c_network_session_parameter_map_variant__request_change_hook(void *thisptr, void *unused, s_map_variant *mapVariant);
unsigned long long local_user_get_identifier_hook();
void network_broadcast_search_handle_reply_hook(s_transport_address const *usable_address, void *data);
void c_network_session_membership__build_membership_update_hook(c_network_session_membership *thisptr, void *__formal, long peer_index, s_network_session_shared_membership const *membership, s_network_session_shared_membership const *baseline, s_network_session_membership_update_message *update);
void c_network_session_membership__copy_current_to_transmitted_hook(c_network_session_membership *thisptr, void *__formal, long peer_index, s_network_session_shared_membership const *current);
void c_network_message_handler__handle_parameters_request_hook(c_network_message_handler *thisptr, void *__formal, void *channel, void *message);
void c_network_message_handler__handle_delegate_leadership_hook(c_network_message_handler *__formal, void *__formal, void *channel, void *message);
bool network_squad_session_delegate_leadership_hook(long playerIndex);

/* ---------- globals */

namespace Utils
{
	Server::StatsServersBanList *Utils::Singleton<Server::StatsServersBanList>::m_instance; // 0x1246460C
}

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		extern std::string DefaultBanListPath; // 0x12464800
	}
	using namespace hades_file_local_Server;
}
namespace hades_file_local
{
	extern std::vector<std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> > pongCallbacks; // 0x124647E0
	extern std::vector<std::function<void __cdecl(s_map_variant *)> > mapVariantRequestChangeCallbacks; // 0x124647F0
}
using namespace hades_file_local;
namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::string const DefaultTypes[8]; // 0x12464610
			extern std::string const DefaultTypeNames[8]; // 0x124646F0
		}
		using namespace hades_file_local_Server_Voting;
	}
}
namespace hades_file_local
{
	extern std::vector<std::function<void __cdecl(enum Blam::Network::LifeCycleState)> > lifeCycleStateChangedCallbacks; // 0x124647D0
	extern std::shared_ptr<Patches::Network::NetworkSessionListener> sessionObserver; // 0x1246481C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Network
	{
		_extern void _sub_10A90670();
		void ApplyAll() // 0x10A90670
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A92B66
			// static ...; // 0x10A92B60
			// static ...; // 0x10A92B56
			// static ...; // 0x10A92B53
			// static ...; // 0x10A92B50
			// static ...; // 0x10A92B14
			// static ...; // 0x10A92B0C
			// unsigned long temp;
			// Pointer writeAddr;
			// unsigned __int32 verNum;
			// unsigned long temp2;
			{
				// std::stringstream ss;
			}
			{
			}
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			// function call : void (char const *)
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			// function call : void (char const *)
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			todo("implement");
			_sub_10A90670();
		}

		_extern void _sub_10A95310();
		void ForceDedicated() // 0x10A95310
		{
			mangled_x86(MANGLED_TODO, "?ForceDedicated@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A95310();
		}

		_extern void _sub_10A94A20();
		void ForceBotClient() // 0x10A94A20
		{
			mangled_x86(MANGLED_TODO, "?ForceBotClient@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A94A20();
		}

		_extern unsigned short _sub_10A9A490(std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)>);
		unsigned short OnPong(std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> callback) // 0x10A9A490
		{
			mangled_x86(MANGLED_TODO, "?OnPong@Network@Patches@@YAGV?$function@$$A6AXABUNetworkAddress@Network@Blam@@IGI@Z@std@@@Z");
			// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> callback;
			// static unsigned short id; // 0x12464824
			todo("implement");
			unsigned short __result = _sub_10A9A490(callback);
			return __result;
		}

		_extern void _sub_10A9A350(std::function<void __cdecl(enum Blam::Network::LifeCycleState)>);
		void OnLifeCycleStateChanged(std::function<void __cdecl(enum Blam::Network::LifeCycleState)> callback) // 0x10A9A350
		{
			mangled_x86(MANGLED_TODO, "?OnLifeCycleStateChanged@Network@Patches@@YAXV?$function@$$A6AXW4LifeCycleState@Network@Blam@@@Z@std@@@Z");
			// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> callback;
			todo("implement");
			_sub_10A9A350(callback);
		}

		_extern void _sub_10A9AB60(std::shared_ptr<Patches::Network::NetworkSessionListener>);
		void RegisterSessionListener(std::shared_ptr<Patches::Network::NetworkSessionListener> observer) // 0x10A9AB60
		{
			mangled_x86(MANGLED_TODO, "?RegisterSessionListener@Network@Patches@@YAXV?$shared_ptr@VNetworkSessionListener@Network@Patches@@@std@@@Z");
			// std::shared_ptr<Patches::Network::NetworkSessionListener> observer;
			todo("implement");
			_sub_10A9AB60(observer);
		}

		_extern void _sub_10A9A3F0(std::function<void __cdecl(s_map_variant *)>);
		void OnMapVariantRequestChange(std::function<void __cdecl(s_map_variant *)> callback) // 0x10A9A3F0
		{
			mangled_x86(MANGLED_TODO, "?OnMapVariantRequestChange@Network@Patches@@YAXV?$function@$$A6AXPAUs_map_variant@@@Z@std@@@Z");
			// std::function<void __cdecl(s_map_variant *)> callback;
			todo("implement");
			_sub_10A9A3F0(callback);
		}

		_extern void _sub_10A9B020();
		void Tick() // 0x10A9B020
		{
			mangled_x86(MANGLED_TODO, "?Tick@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			{
				// __int32 i;
				{
					// Blam::Network::PlayerSession *player;
					// Blam::Network::PeerInfo *peer;
					// __int32 peerIndex;
				}
			}
			todo("implement");
			_sub_10A9B020();
		}
	}
}

/* ---------- private code */

_extern unsigned long _sub_10A995B0(__int32, __int32);
unsigned long Network_managed_session_create_session_internalHook(__int32 a1, __int32 a2) // 0x10A995B0
{
	// `anonymous-namespace'::Network_managed_session_create_session_internalHook
	// __int32 a2;
	// unsigned long retval;
	// unsigned long (*Network_managed_session_create_session_internal)(__int32, __int32);
	// bool isHost;
	// unsigned long isOnline;
	// function call : unsigned long (*)(__int32, __int32)
	// function call : void ()
	todo("implement");
	unsigned long __result = _sub_10A995B0(a1, a2);
	return __result;
}

_extern void _sub_10A9E630(c_network_session *, void *, long, long, long, long, void const *);
void network_session_send_peer_establish_hook(c_network_session *thisPtr, void *unused, long transmission_type, long peer_index, long message_type, long data_length, void const *data) // 0x10A9E630
{
	// `anonymous-namespace'::network_session_send_peer_establish_hook
	// void const *data;
	// constexpr void (*const `network_session_send_peer_establish_hook'::`2'::c_network_session__send_message_to_peer)(c_network_session *, long, long, long, long, void const *); // constant == 4582224
	// function call : void (*const)(c_network_session *, long, long, long, long, void const *)
	todo("implement");
	_sub_10A9E630(thisPtr, unused, transmission_type, peer_index, message_type, data_length, data);
}

_extern char *_sub_10A98EC0(void *);
char *Network_GetIPStringFromInAddr(void *inaddr) // 0x10A98EC0
{
	// `anonymous-namespace'::Network_GetIPStringFromInAddr
	// void *inaddr;
	// unsigned char ip3;
	// unsigned char ip2;
	// unsigned char ip1;
	// unsigned char ip0;
	// static char `Network_GetIPStringFromInAddr'::`2'::ipAddrStr[64]; // 0x12464828
	// unsigned short port;
	// unsigned short type;
	todo("implement");
	char * __result = _sub_10A98EC0(inaddr);
	return __result;
}

_extern unsigned __int32 _sub_10A98140();
unsigned __int32 GetPlayerPropertiesPacketSize() // 0x10A98140
{
	// `anonymous-namespace'::GetPlayerPropertiesPacketSize
	// procedure flags: nofpo
	// static unsigned __int32 `GetPlayerPropertiesPacketSize'::`2'::size; // 0x12464868
	{
		// unsigned __int32 extensionSize;
	}
	todo("implement");
	unsigned __int32 __result = _sub_10A98140();
	return __result;
}

_extern void _sub_10A9AAB0(void *, void *, __int32, char const *, __int32, __int32, __int32, void *, void *, __int32, __int32);
void RegisterPlayerPropertiesPacketHook(void *thisPtr, void *unused, __int32 packetId, char const *packetName, __int32 arg8, __int32 size1, __int32 size2, void *serializeFunc, void *deserializeFunc, __int32 arg1C, __int32 arg20) // 0x10A9AAB0
{
	// `anonymous-namespace'::RegisterPlayerPropertiesPacketHook
	// __int32 arg20;
	// unsigned __int32 newSize;
	// void (*RegisterPacket)(void *, __int32, char const *, __int32, __int32, __int32, void *, void *, __int32, __int32);
	// function call : void (*)(void *, __int32, char const *, __int32, __int32, __int32, void *, void *, __int32, __int32)
	todo("implement");
	_sub_10A9AAB0(thisPtr, unused, packetId, packetName, arg8, size1, size2, serializeFunc, deserializeFunc, arg1C, arg20);
}

_extern bool _sub_10A98410(std::string);
bool IsNameNotAllowed(std::string name) // 0x10A98410
{
	// `anonymous-namespace'::IsNameNotAllowed
	// static ...; // 0x10A98577
	// static ...; // 0x10A9856E
	// static ...; // 0x10A9856C
	// static ...; // 0x10A98548
	// static ...; // 0x10A98540
	// std::string name;
	{
		// std::unordered_set<std::string> &<range>$L0;
		// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <begin>$L0;
		// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <end>$L0;
		{
			// std::string s;
		}
	}
	todo("implement");
	bool __result = _sub_10A98410(name);
	return __result;
}

_extern void _sub_10A9ABC0(wchar_t *);
void SanitizePlayerName(wchar_t *name) // 0x10A9ABC0
{
	// `anonymous-namespace'::SanitizePlayerName
	// static ...; // 0x10A9AEAC
	// static ...; // 0x10A9AEA0
	// static ...; // 0x10A9AE98
	// wchar_t *name;
	// __int32 i;
	// __int32 dest;
	// bool space;
	{
		// bool allowed;
	}
	{
		// std::string lowercasename;
	}
	todo("implement");
	_sub_10A9ABC0(name);
}

_extern void _sub_10A934B0(Blam::Network::SessionMembership *, void *, __int32, unsigned __int32, unsigned __int32, unsigned char *, unsigned __int32);
void ApplyPlayerPropertiesExtended(Blam::Network::SessionMembership *thisPtr, void *unused, __int32 playerIndex, unsigned __int32 arg4, unsigned __int32 arg8, unsigned char *data, unsigned __int32 arg10) // 0x10A934B0
{
	// `anonymous-namespace'::ApplyPlayerPropertiesExtended
	// static ...; // 0x10A93D6C
	// static ...; // 0x10A93D18
	// static ...; // 0x10A93D10
	// Blam::Network::SessionMembership *thisPtr;
	// void *unused;
	// __int32 playerIndex;
	// unsigned __int32 arg4;
	// unsigned __int32 arg8;
	// unsigned char *data;
	// unsigned __int32 arg10;
	// Server::BanList banList;
	// s_player_configuration_from_client *packetProperties;
	// char uidst[17];
	// bool isNewMember;
	// s_player_configuration *properties;
	// Blam::Network::Session *session;
	// std::string uidStr;
	// std::string name;
	// void (*const ApplyPlayerProperties)(void *, __int32, unsigned __int32, unsigned __int32, void *, unsigned __int32);
	{
		// long currentTeamIndex;
		// __int32 playerIdx;
		// __int32 numTeams;
		// Modules::ModuleServer &moduleServer;
		// __int32 minTeams;
		// __int32 numPlayers;
		// unsigned long minTeamSize;
		// unsigned long maxPlayers;
	}
	{
		// s_player_configuration *prop;
		{
			// __int32 teamSizes[8];
			// __int32 playerIdx;
			// __int32 smallest;
			// __int32 numTeams;
			// Modules::ModuleServer &moduleServer;
			// __int32 minTeams;
			// __int32 smallIndex;
			// __int32 numPlayers;
			// unsigned long minTeamSize;
			// unsigned long maxPlayers;
			{
				// long teamIndex;
			}
			{
				// __int32 i;
			}
		}
	}
	// function call : void (__int32)
	// function call : void (*const)(void *, __int32, unsigned __int32, unsigned __int32, void *, unsigned __int32)
	todo("implement");
	_sub_10A934B0(thisPtr, unused, playerIndex, arg4, arg8, data, arg10);
}

_extern bool _sub_10A99390(void *, void *, Blam::Network::PeerInfo *, __int32);
bool Network_leader_request_boot_machineHook(void *thisPtr, void *unused, Blam::Network::PeerInfo *peer, __int32 reason) // 0x10A99390
{
	// `anonymous-namespace'::Network_leader_request_boot_machineHook
	// void *thisPtr;
	// void *unused;
	// Blam::Network::PeerInfo *peer;
	// __int32 reason;
	// std::string playerName;
	// Blam::Network::SessionMembership *membership;
	// __int32 playerIndex;
	// __int32 peerIndex;
	// Blam::Network::Session *session;
	// bool (*Network_leader_request_boot_machine)(void *, void *, __int32);
	// function call : bool (*)(void *, void *, __int32)
	todo("implement");
	bool __result = _sub_10A99390(thisPtr, unused, peer, reason);
	return __result;
}

_extern bool _sub_10A996B0(Blam::Network::Session *, void *, Blam::Network::NetworkAddress const &, void *);
bool Network_session_handle_join_requestHook(Blam::Network::Session *thisPtr, void *unused, Blam::Network::NetworkAddress const &address, void *request) // 0x10A996B0
{
	// `anonymous-namespace'::Network_session_handle_join_requestHook
	// static ...; // 0x10A99894
	// static ...; // 0x10A9988C
	// Blam::Network::Session *thisPtr;
	// void *unused;
	// Blam::Network::NetworkAddress const &address;
	// void *request;
	// char ipStr[22];
	// bool (*Network_session_handle_join_request)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, void *);
	// in_addr inAddr;
	{
		// Server::BanList banList;
		// Server::BanList::BanType banType;
		{
			// constexpr void (*const `Network_session_handle_join_requestHook'::`8'::Network_session_acknowledge_join_request)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, __int32); // constant == 4563504
		}
	}
	// function call : void (*const)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, __int32)
	// function call : void (*const)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, __int32)
	// function call : bool (*)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, void *)
	todo("implement");
	bool __result = _sub_10A996B0(thisPtr, unused, address, request);
	return __result;
}

_extern __int32 _sub_10A98FA0();
__int32 Network_GetMaxPlayersHook() // 0x10A98FA0
{
	// `anonymous-namespace'::Network_GetMaxPlayersHook
	// procedure flags: nofpo
	// __int32 maxPlayers;
	todo("implement");
	__int32 __result = _sub_10A98FA0();
	return __result;
}

__int32 Pregame_Lobby_Max_Player_Count_Offline_hook() // 0x10A9AA90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Pregame_Lobby_Max_Player_Count_Offline_hook@@YAHXZ");
	// `anonymous-namespace'::Pregame_Lobby_Max_Player_Count_Offline_hook
	// procedure flags: nofpo

	return 1;
}

_extern bool _sub_10A9A570(Blam::Network::Session *, void *, unsigned __int32, unsigned __int32, s_player_configuration_from_client *, unsigned __int32);
bool PeerRequestPlayerDesiredPropertiesUpdateHook(Blam::Network::Session *thisPtr, void *unused, unsigned __int32 arg0, unsigned __int32 arg4, s_player_configuration_from_client *properties, unsigned __int32 argC) // 0x10A9A570
{
	// `anonymous-namespace'::PeerRequestPlayerDesiredPropertiesUpdateHook
	// void *unused;
	// unsigned __int32 arg0;
	// unsigned __int32 arg4;
	// s_player_configuration_from_client *properties;
	// unsigned __int32 argC;
	// unsigned __int32 packetSize;
	// Blam::Network::SessionMembership *membership;
	// unsigned __int32 extendedSize;
	// __int32 playerIndex;
	// std::unique_ptr<unsigned char [0]> extendedProperties;
	{
		// __int32 channelIndex;
		// void (*InitPacket)(__int32, void *);
		// __int32 hostPeer;
		// std::unique_ptr<unsigned char [0]> packet;
	}
	// function call : void (*)(__int32, void *)
	todo("implement");
	bool __result = _sub_10A9A570(thisPtr, unused, arg0, arg4, properties, argC);
	return __result;
}

_extern bool _sub_10A99250(c_network_session_membership *, void *, long, Blam::Network::PeerConnectionState, long, void *, unsigned long long, unsigned long long);
bool Network_Session_Membership__Add_Peer_Hook(c_network_session_membership *thisptr, void *unused, long peer_index, Blam::Network::PeerConnectionState connection_state, long version, void *xnaddr, unsigned long long unknown_nonce, unsigned long long join_nonce) // 0x10A99250
{
	// `anonymous-namespace'::Network_Session_Membership__Add_Peer_Hook
	// unsigned long long join_nonce;
	// constexpr bool (*const `Network_Session_Membership__Add_Peer_Hook'::`2'::c_network_session_membership__add_peer)(void *, long, Blam::Network::PeerConnectionState, long, void *, unsigned long long, unsigned long long); // constant == 4509152
	// bool result;
	// function call : bool (*const)(void *, long, Blam::Network::PeerConnectionState, long, void *, unsigned long long, unsigned long long)
	// function call : void ()
	// function call : void (__int32)
	todo("implement");
	bool __result = _sub_10A99250(thisptr, unused, peer_index, connection_state, version, xnaddr, unknown_nonce, join_nonce);
	return __result;
}

_extern char _sub_10A99000(c_network_session_membership *, void *, long);
char Network_Session_Membership_Remove_Peer_Hook(c_network_session_membership *thisptr, void *unused, long peer_index) // 0x10A99000
{
	// `anonymous-namespace'::Network_Session_Membership_Remove_Peer_Hook
	// static ...; // 0x10A991B0
	// c_network_session_membership *thisptr;
	// void *unused;
	// long peer_index;
	// constexpr char (*const `Network_Session_Membership_Remove_Peer_Hook'::`2'::c_network_session_membership__remove_peer)(c_network_session_membership *, long); // constant == 4521520
	{
		// std::string playerName;
		// __int32 playerIdx;
		// Blam::Network::SessionMembership *membership;
	}
	// function call : void (__int32)
	// function call : void ()
	// function call : char (*const)(c_network_session_membership *, long)
	todo("implement");
	char __result = _sub_10A99000(thisptr, unused, peer_index);
	return __result;
}

_extern void _sub_10A9AF80(Blam::BitStream *, unsigned char *, bool);
void SerializePlayerPropertiesHook(Blam::BitStream *stream, unsigned char *buffer, bool flag) // 0x10A9AF80
{
	// `anonymous-namespace'::SerializePlayerPropertiesHook
	// bool flag;
	// void (*SerializePlayerProperties)(Blam::BitStream *, unsigned char *, bool);
	// function call : void (*)(Blam::BitStream *, unsigned char *, bool)
	todo("implement");
	_sub_10A9AF80(stream, buffer, flag);
}

_extern bool _sub_10A94970(Blam::BitStream *, unsigned char *, bool);
bool DeserializePlayerPropertiesHook(Blam::BitStream *stream, unsigned char *buffer, bool flag) // 0x10A94970
{
	// `anonymous-namespace'::DeserializePlayerPropertiesHook
	// bool flag;
	// bool succeeded;
	// bool (*DeserializePlayerProperties)(Blam::BitStream *, unsigned char *, bool);
	// function call : bool (*)(Blam::BitStream *, unsigned char *, bool)
	todo("implement");
	bool __result = _sub_10A94970(stream, buffer, flag);
	return __result;
}

_extern char _sub_10A9A240(void *, __int32, __int32, __int32, __int32);
char Network_state_end_game_write_stats_enterHook(void *thisPtr, __int32 unused, __int32 a2, __int32 a3, __int32 a4) // 0x10A9A240
{
	// `anonymous-namespace'::Network_state_end_game_write_stats_enterHook
	// __int32 a4;
	// char (*Network_state_end_game_write_stats_enter)(void *, __int32, __int32, __int32);
	// function call : char (*)(void *, __int32, __int32, __int32)
	todo("implement");
	char __result = _sub_10A9A240(thisPtr, unused, a2, a3, a4);
	return __result;
}

_extern char _sub_10A9A2C0(void *, __int32, __int32, __int32, __int32);
char Network_state_leaving_enterHook(void *thisPtr, __int32 unused, __int32 a2, __int32 a3, __int32 a4) // 0x10A9A2C0
{
	// `anonymous-namespace'::Network_state_leaving_enterHook
	// __int32 a4;
	// char (*Network_state_leaving_enter)(void *, __int32, __int32, __int32);
	// function call : char (*)(void *, __int32, __int32, __int32)
	todo("implement");
	char __result = _sub_10A9A2C0(thisPtr, unused, a2, a3, a4);
	return __result;
}

_extern void _sub_10A9D920(void *, void *, __int32, __int32);
void c_network_session__host_connection_refused_hook(void *session, void *unused, __int32 a2, __int32 type) // 0x10A9D920
{
	// `anonymous-namespace'::c_network_session__host_connection_refused_hook
	// __int32 type;
	// constexpr void (*const `c_network_session__host_connection_refused_hook'::`2'::c_network_session__host_connection_refused)(void *, __int32, __int32); // constant == 4572464
	// function call : void (*const)(void *, __int32, __int32)
	todo("implement");
	_sub_10A9D920(session, unused, a2, type);
}

_extern void _sub_10A9A9E0(Blam::Network::NetworkAddress const &, Blam::Network::PongPacket const &, unsigned __int32);
void PongReceivedHookImpl(Blam::Network::NetworkAddress const &from, Blam::Network::PongPacket const &pong, unsigned __int32 latency) // 0x10A9A9E0
{
	// `anonymous-namespace'::PongReceivedHookImpl
	// unsigned __int32 latency;
	{
		// std::vector<std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> > &<range>$L0;
		// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> *<begin>$L0;
		// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> *<end>$L0;
		{
			// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> &callback;
		}
	}
	todo("implement");
	_sub_10A9A9E0(from, pong, latency);
}

__declspec(naked) void PongReceivedHook() // 0x10A9A9C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PongReceivedHook@@YAXXZ");
	// `anonymous-namespace'::PongReceivedHook
	// procedure flags: nofpo

	__asm
	{
		push esi
		push edi
		push dword ptr [ebp + 8]
		call PongReceivedHookImpl
		add esp, 0Ch
		push 049D9FAh
		ret
	}
}

_extern void _sub_10A98600(Blam::Network::LifeCycleState);
void LifeCycleStateChangedHookImpl(Blam::Network::LifeCycleState newState) // 0x10A98600
{
	// `anonymous-namespace'::LifeCycleStateChangedHookImpl
	// static ...; // 0x10A98AF4
	// static ...; // 0x10A98AE8
	// static ...; // 0x10A98AE0
	// Blam::Network::LifeCycleState newState;
	{
		// std::string previousValue;
	}
	{
		// std::vector<std::function<void __cdecl(enum Blam::Network::LifeCycleState)> > &<range>$L0;
		// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> *<begin>$L0;
		// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> *<end>$L0;
		{
			// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> &callback;
		}
	}
	todo("implement");
	_sub_10A98600(newState);
}

__declspec(naked) void LifeCycleStateChangedHook() // 0x10A985E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LifeCycleStateChangedHook@@YAXXZ");
	// `anonymous-namespace'::LifeCycleStateChangedHook
	// procedure flags: nofpo

	__asm
	{
		pop esi
		mov ecx, edi
		call dword ptr [eax + 8]
		push dword ptr [ebx]
		call LifeCycleStateChangedHookImpl
		add esp, 4
		jmp esi
	}
}

__declspec(naked) void GetTextureDimensionsHook() // 0x10A981B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetTextureDimensionsHook@@YAXXZ");
	// `anonymous-namespace'::GetTextureDimensionsHook
	// procedure flags: nofpo
	// resume:

	__asm
	{
		cmp ecx, [eax + 34h]
		jl Lfound
		xor edx, edx
		push 0A6E9B0h
		ret
		Lfound:
		mov eax, [eax + 44h]
		lea eax, [eax + ecx * 8]
		push 0A6E988h
		ret
	}
}

_extern bool _sub_10A98C50(char *, void *);
bool Network_GetEndpointHook(char *thisPtr, void *unused) // 0x10A98C50
{
	// `anonymous-namespace'::Network_GetEndpointHook
	// void *unused;
	// char *socket;
	// bool (*Network_link_create_endpoint)(__int32, short, char, void *);
	// bool success;
	// void *(*sub_43FED0)(unsigned __int32);
	// unsigned __int32 port;
	// function call : bool (*)(__int32, short, char, void *)
	// function call : void *(*)(unsigned __int32)
	todo("implement");
	bool __result = _sub_10A98C50(thisPtr, unused);
	return __result;
}

_extern char _sub_10A99BB0(void *, __int32, char, __int32, __int32, __int32, __int32, __int32, __int32, __int32, __int32, __int32, void *, __int32, __int32);
char Network_session_join_remote_sessionHook(void *thisPtr, __int32 unused, char a2, __int32 a3, __int32 a4, __int32 a5, __int32 a6, __int32 a7, __int32 a8, __int32 a9, __int32 a10, __int32 a11, void *a12, __int32 a13, __int32 a14) // 0x10A99BB0
{
	// `anonymous-namespace'::Network_session_join_remote_sessionHook
	// __int32 a10;
	// __int32 a11;
	// void *a12;
	// __int32 a13;
	// __int32 a14;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// char (*Network_session_join_remote_session)(void *, __int32, char, __int32, __int32, __int32, __int32, __int32, __int32, __int32, __int32, __int32, void *, __int32, __int32);
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	// function call : char (*)(void *, __int32, char, __int32, __int32, __int32, __int32, __int32, __int32, __int32, __int32, __int32, void *, __int32, __int32)
	todo("implement");
	char __result = _sub_10A99BB0(thisPtr, unused, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
	return __result;
}

_extern __int32 _sub_10A99960(void *, __int32, char);
__int32 Network_session_initiate_leave_protocolHook(void *thisPtr, __int32 unused, char forceClose) // 0x10A99960
{
	// `anonymous-namespace'::Network_session_initiate_leave_protocolHook
	// static ...; // 0x10A99B0C
	// static ...; // 0x10A99B04
	// void *thisPtr;
	// __int32 unused;
	// char forceClose;
	// __int32 (*Network_session_initiate_leave_protocol)(void *, __int32, char);
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	// function call : __int32 (*)(void *, __int32, char)
	todo("implement");
	__int32 __result = _sub_10A99960(thisPtr, unused, forceClose);
	return __result;
}

_extern __int32 _sub_10A99F00(void *, __int32);
__int32 Network_session_parameters_clearHook(void *thisPtr, __int32 unused) // 0x10A99F00
{
	// `anonymous-namespace'::Network_session_parameters_clearHook
	// static ...; // 0x10A9A0BC
	// static ...; // 0x10A9A0A4
	// static ...; // 0x10A9A09C
	// void *thisPtr;
	// __int32 unused;
	// __int32 (*Network_session_parameters_clear)(void *, __int32);
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	// function call : __int32 (*)(void *, __int32)
	todo("implement");
	__int32 __result = _sub_10A99F00(thisPtr, unused);
	return __result;
}

_extern __int32 _sub_10A9A150(Blam::Network::SessionMembership *, void *, __int32);
__int32 Network_session_remove_peerHook(Blam::Network::SessionMembership *membership, void *unused, __int32 peerIndex) // 0x10A9A150
{
	// `anonymous-namespace'::Network_session_remove_peerHook
	// __int32 peerIndex;
	// __int32 (*Network_session_remove_peer)(Blam::Network::SessionMembership *, __int32);
	// function call : void (__int32)
	// function call : __int32 (*)(Blam::Network::SessionMembership *, __int32)
	todo("implement");
	__int32 __result = _sub_10A9A150(membership, unused, peerIndex);
	return __result;
}

_extern bool _sub_10A99E40(void *, void *, __int32, __int32);
bool Network_session_parameter_countdown_timer_request_change_hook(void *thisPtr, void *unused, __int32 state, __int32 value) // 0x10A99E40
{
	// `anonymous-namespace'::Network_session_parameter_countdown_timer_request_change_hook
	// __int32 value;
	// static bool (*`Network_session_parameter_countdown_timer_request_change_hook'::`2'::Network_session_parameter_countdown_timer_request_change)(void *, __int32, __int32); // 0x1135475C
	{
		// unsigned long countDownTimer;
	}
	// function call : bool (*)(void *, __int32, __int32)
	todo("implement");
	bool __result = _sub_10A99E40(thisPtr, unused, state, value);
	return __result;
}

_extern bool _sub_10A9DB70(void *, void *, s_map_variant *);
bool c_network_session_parameter_map_variant__request_change_hook(void *thisptr, void *unused, s_map_variant *mapVariant) // 0x10A9DB70
{
	// `anonymous-namespace'::c_network_session_parameter_map_variant__request_change_hook
	// s_map_variant *mapVariant;
	// bool (*const c_network_session_parameter_map_variant__request_change)(void *, s_map_variant *);
	// bool ret;
	{
		// std::vector<std::function<void __cdecl(s_map_variant *)> > &<range>$L0;
		// std::function<void __cdecl(s_map_variant *)> *<begin>$L0;
		// std::function<void __cdecl(s_map_variant *)> *<end>$L0;
		{
			// std::function<void __cdecl(s_map_variant *)> &callback;
		}
	}
	// function call : bool (*const)(void *, s_map_variant *)
	todo("implement");
	bool __result = _sub_10A9DB70(thisptr, unused, mapVariant);
	return __result;
}

_extern unsigned long long _sub_10A9E2A0();
unsigned long long local_user_get_identifier_hook() // 0x10A9E2A0
{
	// `anonymous-namespace'::local_user_get_identifier_hook
	// procedure flags: nofpo
	todo("implement");
	unsigned long long __result = _sub_10A9E2A0();
	return __result;
}

_extern void _sub_10A9E4E0(s_transport_address const *, void *);
void network_broadcast_search_handle_reply_hook(s_transport_address const *usable_address, void *data) // 0x10A9E4E0
{
	// `anonymous-namespace'::network_broadcast_search_handle_reply_hook
	// void *data;
	// char *xnkid;
	// void (*const network_broadcast_search_handle_reply)(s_transport_address const *, void *);
	// void (*const xnet_shim_table_add)(s_transport_address const *, void const *, void const *);
	// char *xnaddr;
	// s_available_session *available_sessions;
	// bool found;
	// long max_session_count;
	{
		// long i;
		{
			// s_available_session *session;
		}
	}
	// function call : void (*const)(s_transport_address const *, void *)
	// function call : void (*const)(s_transport_address const *, void const *, void const *)
	todo("implement");
	_sub_10A9E4E0(usable_address, data);
}

_extern void _sub_10A9DA60(c_network_session_membership *, void *, long, s_network_session_shared_membership const *, s_network_session_shared_membership const *, s_network_session_membership_update_message *);
void c_network_session_membership__build_membership_update_hook(c_network_session_membership *thisptr, void *__formal, long peer_index, s_network_session_shared_membership const *membership, s_network_session_shared_membership const *baseline, s_network_session_membership_update_message *update) // 0x10A9DA60
{
	// `anonymous-namespace'::c_network_session_membership__build_membership_update_hook
	// s_network_session_membership_update_message *update;
	// void (*const c_network_session_membership__build_membership_update)(c_network_session_membership *, long, s_network_session_shared_membership const *, s_network_session_shared_membership const *, s_network_session_membership_update_message *);
	// function call : void (*const)(c_network_session_membership *, long, s_network_session_shared_membership const *, s_network_session_shared_membership const *, s_network_session_membership_update_message *)
	todo("implement");
	_sub_10A9DA60(thisptr, __formal, peer_index, membership, baseline, update);
}

_extern void _sub_10A9DAF0(c_network_session_membership *, void *, long, s_network_session_shared_membership const *);
void c_network_session_membership__copy_current_to_transmitted_hook(c_network_session_membership *thisptr, void *__formal, long peer_index, s_network_session_shared_membership const *current) // 0x10A9DAF0
{
	// `anonymous-namespace'::c_network_session_membership__copy_current_to_transmitted_hook
	// s_network_session_shared_membership const *current;
	// void (*const c_network_session_membership__copy_current_to_transmitted)(c_network_session_membership *, long, s_network_session_shared_membership const *);
	// function call : void (*const)(c_network_session_membership *, long, s_network_session_shared_membership const *)
	todo("implement");
	_sub_10A9DAF0(thisptr, __formal, peer_index, current);
}

_extern void _sub_10A9D870(c_network_message_handler *, void *, void *, void *);
void c_network_message_handler__handle_parameters_request_hook(c_network_message_handler *thisptr, void *__formal, void *channel, void *message) // 0x10A9D870
{
	// `anonymous-namespace'::c_network_message_handler__handle_parameters_request_hook
	// void *message;
	// void (*const c_network_message_handler__handle_parameters_request)(c_network_message_handler *, void *, void *);
	// function call : bool (*const)()
	// function call : bool (*)()
	// function call : void (*const)(c_network_message_handler *, void *, void *)
	todo("implement");
	_sub_10A9D870(thisptr, __formal, channel, message);
}

_extern void _sub_10A9D840(c_network_message_handler *, void *, void *, void *);
void c_network_message_handler__handle_delegate_leadership_hook(c_network_message_handler *__formal, void *__formal1, void *channel, void *message) // 0x10A9D840
{
	// `anonymous-namespace'::c_network_message_handler__handle_delegate_leadership_hook
	// void *message;
	todo("implement");
	_sub_10A9D840(__formal, __formal1, channel, message);
}

bool network_squad_session_delegate_leadership_hook(long playerIndex) // 0x10A9E6B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?network_squad_session_delegate_leadership_hook@@YA_NJ@Z");
	// `anonymous-namespace'::network_squad_session_delegate_leadership_hook
	// long playerIndex;

	return false;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Server::StatsServersBanList & Utils::Singleton<Server::StatsServersBanList>::Instance();
template void Pointer::Write<long>(long const) const;
template void Pointer::WriteFast<unsigned int>(unsigned __int32 const) const;
