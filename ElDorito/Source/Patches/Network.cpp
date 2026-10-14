/* ---------- headers */

#include "Patches/Network.hpp"
#include "hades/hades.h"

namespace Utils { namespace Version {
	extern unsigned __int32 GetVersionInt();
} }  // hades: added for 0x10C60D90, declared only in VersionInfo.cpp

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
#include "Modules/ModuleVoIP.hpp"
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

#include "Modules/ModulePlayer.hpp"  // hades: added for 0x10A9A570

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

#include "Utils/Logger.hpp"  // hades: added for 0x10A996B0
extern "C" char const *__stdcall inet_ntop(int Family, void const *pAddr, char *pStringBuf, size_t StringBufSize);  // hades: added for 0x10A996B0

namespace Server { namespace Voting { extern void PlayerLeftVoting(std::string name); } namespace Stats { extern void UpdatePlayersInfo(); } } namespace Server { namespace Signaling { extern void SendPeerPassword(__int32 playerIndex); } namespace Voting { extern void PlayerJoinedVoteInProgress(__int32 playerIndex); } namespace HsGlobalSync { extern void InvalidatePlayerMask(unsigned short playerMask); } } void player_format_uid(char *string, unsigned __int64 id);  // hades: added for 0x10A99000, 0x10A934B0

namespace Utils { namespace String { template<typename t_char> void StrzCopy(t_char *dest, int dest_size, t_char const *src); } }  // hades: added for 0x10A9ABC0

extern bool (*game_is_campaign)();  // hades: added for 0x10A9D870

namespace Server::InfoServer { bool StartInfoServer(); bool StopInfoServer(); }  // hades: added for 0X10A995B0
namespace Server::Signaling { void StartServer(); void StopServer(); }  // hades: added for 0X10A995B0

namespace Server::InfoServer { bool StopInfoServer(); }  // hades: added for 0X10A9A2C0
namespace Server::Signaling { void StopServer(); }  // hades: added for 0X10A9A2C0

namespace Server::Signaling { void RemovePeer(__int32 peerIndex); }  // hades: added for 0X10A9A150

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
void __fastcall network_session_send_peer_establish_hook(c_network_session *thisPtr, void *unused, long transmission_type, long peer_index, long message_type, long data_length, void const *data);
char *Network_GetIPStringFromInAddr(void *inaddr);
unsigned __int32 GetPlayerPropertiesPacketSize();
void __fastcall RegisterPlayerPropertiesPacketHook(void *thisPtr, void *unused, __int32 packetId, char const *packetName, __int32 arg8, __int32 size1, __int32 size2, void *serializeFunc, void *deserializeFunc, __int32 arg1C, __int32 arg20);
bool IsNameNotAllowed(std::string name);
void SanitizePlayerName(wchar_t *name);
void __fastcall ApplyPlayerPropertiesExtended(Blam::Network::SessionMembership *thisPtr, void *unused, __int32 playerIndex, unsigned __int32 arg4, unsigned __int32 arg8, unsigned char *data, unsigned __int32 arg10);
bool __fastcall Network_leader_request_boot_machineHook(void *thisPtr, void *unused, Blam::Network::PeerInfo *peer, __int32 reason);
bool __fastcall Network_session_handle_join_requestHook(Blam::Network::Session *thisPtr, void *unused, Blam::Network::NetworkAddress const &address, void *request);
__int32 Network_GetMaxPlayersHook();
__int32 Pregame_Lobby_Max_Player_Count_Offline_hook();
bool __fastcall PeerRequestPlayerDesiredPropertiesUpdateHook(Blam::Network::Session *thisPtr, void *unused, unsigned __int32 arg0, unsigned __int32 arg4, s_player_configuration_from_client *properties, unsigned __int32 argC);
bool __fastcall Network_Session_Membership__Add_Peer_Hook(c_network_session_membership *thisptr, void *unused, long peer_index, Blam::Network::PeerConnectionState connection_state, long version, void *xnaddr, unsigned long long unknown_nonce, unsigned long long join_nonce);
char __fastcall Network_Session_Membership_Remove_Peer_Hook(c_network_session_membership *thisptr, void *unused, long peer_index);
void SerializePlayerPropertiesHook(Blam::BitStream *stream, unsigned char *buffer, bool flag);
bool DeserializePlayerPropertiesHook(Blam::BitStream *stream, unsigned char *buffer, bool flag);
char __fastcall Network_state_end_game_write_stats_enterHook(void *thisPtr, __int32 unused, __int32 a2, __int32 a3, __int32 a4);
char __fastcall Network_state_leaving_enterHook(void *thisPtr, __int32 unused, __int32 a2, __int32 a3, __int32 a4);
void __fastcall c_network_session__host_connection_refused_hook(void *session, void *unused, __int32 a2, __int32 type);
void PongReceivedHookImpl(Blam::Network::NetworkAddress const &from, Blam::Network::PongPacket const &pong, unsigned __int32 latency);
void PongReceivedHook();
void LifeCycleStateChangedHookImpl(Blam::Network::LifeCycleState newState);
void LifeCycleStateChangedHook();
void GetTextureDimensionsHook();
bool __fastcall Network_GetEndpointHook(char *thisPtr, void *unused);
char __fastcall Network_session_join_remote_sessionHook(void *thisPtr, __int32 unused, char a2, __int32 a3, __int32 a4, __int32 a5, __int32 a6, __int32 a7, __int32 a8, __int32 a9, __int32 a10, __int32 a11, void *a12, __int32 a13, __int32 a14);
__int32 __fastcall Network_session_initiate_leave_protocolHook(void *thisPtr, __int32 unused, char forceClose);
__int32 __fastcall Network_session_parameters_clearHook(void *thisPtr, __int32 unused);
__int32 __fastcall Network_session_remove_peerHook(Blam::Network::SessionMembership *membership, void *unused, __int32 peerIndex);
bool __fastcall Network_session_parameter_countdown_timer_request_change_hook(void *thisPtr, void *unused, __int32 state, __int32 value);
bool __fastcall c_network_session_parameter_map_variant__request_change_hook(void *thisptr, void *unused, s_map_variant *mapVariant);
unsigned long long local_user_get_identifier_hook();
void network_broadcast_search_handle_reply_hook(s_transport_address const *usable_address, void *data);
void __fastcall c_network_session_membership__build_membership_update_hook(c_network_session_membership *thisptr, void *__formal, long peer_index, s_network_session_shared_membership const *membership, s_network_session_shared_membership const *baseline, s_network_session_membership_update_message *update);
void __fastcall c_network_session_membership__copy_current_to_transmitted_hook(c_network_session_membership *thisptr, void *__formal, long peer_index, s_network_session_shared_membership const *current);
void __fastcall c_network_message_handler__handle_parameters_request_hook(c_network_message_handler *thisptr, void *__formal, void *channel, void *message);
void __fastcall c_network_message_handler__handle_delegate_leadership_hook(c_network_message_handler *__formal, void *__formal, void *channel, void *message);
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
		// extern std::string DefaultBanListPath; // 0x12464800  // hades: defined (with its initialiser) elsewhere now
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
			// extern std::string const DefaultTypes[8]; // 0x12464610  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x124646F0  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
namespace hades_file_local
{
	extern std::vector<std::function<void __cdecl(enum Blam::Network::LifeCycleState)> > lifeCycleStateChangedCallbacks; // 0x124647D0
	std::shared_ptr<Patches::Network::NetworkSessionListener> sessionObserver; // 0x1246481C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Network
	{

		void ApplyAll() // 0x10A90670
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Network@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x9C864, c_network_message_handler__handle_parameters_request_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9CDD0, c_network_message_handler__handle_delegate_leadership_hook).Apply();
			Hook(0x38640, network_squad_session_delegate_leadership_hook).Apply();
			Hook(0x3F6F0, Network_GetIPStringFromInAddr).Apply();
			Hook(0x82AAC, Network_managed_session_create_session_internalHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			unsigned __int32 version = ::Utils::Version::GetVersionInt();
			Hook(0x5DD20, PeerRequestPlayerDesiredPropertiesUpdateHook).Apply();
			Hook(0xDAF4F, ApplyPlayerPropertiesExtended, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xDFF7E, RegisterPlayerPropertiesPacketHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xDFD53, SerializePlayerPropertiesHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xDE178, DeserializePlayerPropertiesHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5B567, Network_Session_Membership__Add_Peer_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5CED6, Network_Session_Membership__Add_Peer_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9BB34, Network_Session_Membership__Add_Peer_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9BB5B, Network_Session_Membership__Add_Peer_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5A573, Network_Session_Membership_Remove_Peer_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5BA67, Network_Session_Membership_Remove_Peer_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5BB96, Network_Session_Membership_Remove_Peer_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5C395, Network_Session_Membership_Remove_Peer_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x37E17, Network_leader_request_boot_machineHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9D9DB, PongReceivedHook).Apply();
			Hook(0x8E527, LifeCycleStateChangedHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x8E10F, LifeCycleStateChangedHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9D0F7, Network_session_handle_join_requestHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			unsigned long temp;
			unsigned long temp2;
			Pointer writeAddr(0x16183A0);
			if (!VirtualProtect(writeAddr, 4, PAGE_READWRITE, &temp))
			{
				std::stringstream ss;
				ss << "Failed to set protection on memory address " << std::hex << static_cast<void *>(writeAddr);
				OutputDebugStringA(ss.str().c_str());
			}
			else
			{
				writeAddr.Write<unsigned int>(reinterpret_cast<unsigned int>(Network_state_end_game_write_stats_enterHook));
				VirtualProtect(writeAddr, 4, temp, &temp2);
			}
			writeAddr = Pointer(0x16183BC);
			if (!VirtualProtect(writeAddr, 4, PAGE_READWRITE, &temp))
			{
				std::stringstream ss;
				ss << "Failed to set protection on memory address " << std::hex << static_cast<void *>(writeAddr);
				OutputDebugStringA(ss.str().c_str());
			}
			else
			{
				writeAddr.Write<unsigned int>(reinterpret_cast<unsigned int>(Network_state_leaving_enterHook));
				VirtualProtect(writeAddr, 4, temp, &temp2);
			}
			Hook(0x7228D9, Pregame_Lobby_Max_Player_Count_Offline_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x67FA0D, Network_GetMaxPlayersHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x3BAFB, Network_GetEndpointHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7F5B9, Network_session_join_remote_sessionHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9BFCA, Network_session_initiate_leave_protocolHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9C0BE, Network_session_initiate_leave_protocolHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x899AF, Network_session_parameters_clearHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x683D45, Network_session_parameter_countdown_timer_request_change_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x4FF3E, Network_session_remove_peerHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x39AE4, c_network_session_parameter_map_variant__request_change_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9D047, c_network_session__host_connection_refused_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x67E01F, local_user_get_identifier_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x9C2EE, network_broadcast_search_handle_reply_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x92F7B, { 0xB8, 0x01, 0x00, 0x00, 0x00 }).Apply();
			Patch(0x92E3B, { 0x90, 0x90 }).Apply();
			Hook(0x5AC64, c_network_session_membership__build_membership_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5AD20, c_network_session_membership__copy_current_to_transmitted_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x43B873).Write<long>(0x4A8);
			Pointer(0x43B8D3).Write<long>(0x4A8);
			Pointer(0x43B8F4).Write<long>(0x4A8);
			Pointer(0x43C0B3).Write<long>(0x4A8);
			Pointer(0x43C2D3).Write<long>(0x4A8);
			Pointer(0x43C33D).Write<long>(0x4A8);
			Pointer(0x445CD2).Write<long>(0x4A8);
			Pointer(0x45FFFA).Write<long>(0x4A8);
			Pointer(0x460FD4).Write<long>(0x4A8);
			Pointer(0x46169E).Write<long>(0x4A8);
			Pointer(0x484115).Write<long>(0x4A8);
			Pointer(0x49F244).Write<long>(0x4A8);
			Pointer(0x49F261).Write<long>(0x4A8);
		}

		void ForceDedicated() // 0x10A95310
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ForceDedicated@Network@Patches@@YAXXZ");
			// procedure flags: nofpo

			//pit
			Hook(0x2D0EAC, reinterpret_cast<void*>(0x6D0EBC)).Apply();

			// Put the game into dedicated server mode
			Patch(0x2E600, { 0xB0, 0x01 }).Apply();

			// Force syslink to still work
			Patch(0x12D62E, { 0xEB }).Apply();
			Patch(0x12D67A, { 0xEB }).Apply();
			Patch(0x5A8BB, { 0xEB }).Apply();

			// Crash fixes
			Patch(0xC9C5E0, { 0xC2, 0x08, 0x00 }).Apply();

			//Allows for switching of teams
			Patch(0x378C0, { 0xB0, 0x00, 0x90, 0x90, 0x90 }).Apply();

			// Fixes dedicated host crash caused accessing uninitialized player mapping globals by forcing a player datum index of 0 to always be used instead
			Patch(0x62E636, { 0x33, 0xFF }).Apply();
			// Prevents dedicated hosts from crashing due to invalid texture datum lookup
			Hook(0x66E982, GetTextureDimensionsHook).Apply();
			Hook(0x9C057, network_session_send_peer_establish_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();

			// Fixes the game being stuck in some d3d-related while loop
			Patch(0x622290, { 0xC3 }).Apply();

			*reinterpret_cast<uint8_t*>(0x1917CED) = 0;	// fix dedi crash @ 0xA22325 (pairs with patch above)

														// Fixes an exception that happens with null d3d
			Patch(0x675E30, { 0xC3 }).Apply();

			*(uint8_t*)0x0244F970 = 1; // g_IsDedicatedServer
			*(uint8_t*)0x0244F971 = 1; // g_SoundDisabled

			// dedicated server server optimization
			Patch(0x1075A0, { 0xC3 }).Apply(); // main_render_thread_proc
			Patch(0x24E190, { 0xC3 }).Apply(); // disable sound halo system/fmod (prevents output thread from being created up)
			Patch(0x112690, { 0xC3 }).Apply(); // xinput, mouse, keyboard
			Patch(0x20D880, { 0xC3 }).Apply(); // input bindings handler
			Patch(0x215BA0, { 0xC3 }).Apply(); // controller feedback
			Patch(0x726710, { 0xC3 }).Apply(); // saber
			Patch(0x2173A0, { 0xC3 }).Apply(); // bink
			Patch(0x68AAE0, { 0xC3 }).Apply(); // chud state
			Patch(0x1D4990, { 0xC3 }).Apply(); // local input
			Patch(0x219770, { 0xC3 }).Apply(); // fileshare ui
			Patch(0x219C00, { 0xC3 }).Apply(); // spartan rank/milestone ui
			Patch(0x151780, { 0xC3 }).Apply(); // betrayal boot ui
			Patch::NopFill(Pointer::Base(0x00684F3F), 5); // ui input
			Patch::NopFill(Pointer::Base(0x00684F44), 5); // display adapter preferences
			Patch::NopFill(Pointer::Base(0x00684F49), 5); // null_sub
			Patch::NopFill(Pointer::Base(0x00684F4E), 5); // scoreboard ui
			Patch(0x0067FE50, { 0xC3 }).Apply(); // campaign ui
			Patch(0x1926C0, { 0xC3 }).Apply(); // director update
			Patch(0x213A60, { 0xC3 }).Apply(); // observer update
			Patch(0x69EDF0, { 0xC3 }).Apply(); // fp weapon transform
			// bitmap resource allocation
			Patch(0x5DFBC0, { 0xC3 }).Apply();
			Patch(0x5DFAF0, { 0xC3 }).Apply();
			Patch(0x1114A0, { 0xC3 }).Apply();
			Patch(0x1129B0, { 0xC3 }).Apply();
		}

		void ForceBotClient() // 0x10A94A20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ForceBotClient@Network@Patches@@YAXXZ");
			// procedure flags: nofpo

			Patch(0x1075A0, { 0xC3 }).Apply();
			Patch(0x24E190, { 0xC3 }).Apply();
			Patch(0x5DFBC0, { 0xC3 }).Apply();
			Patch(0x5DFAF0, { 0xC3 }).Apply();
			Patch(0x1114A0, { 0xC3 }).Apply();
			Patch(0x1129B0, { 0xC3 }).Apply();
		}

		unsigned short OnPong(std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> callback) // 0x10A9A490
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPong@Network@Patches@@YAGV?$function@$$A6AXABUNetworkAddress@Network@Blam@@IGI@Z@std@@@Z");
			// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> callback;
			// static unsigned short id; // 0x12464824

			pongCallbacks.push_back(callback);
			static unsigned short id;
			return id++;
		}

		void OnLifeCycleStateChanged(std::function<void __cdecl(enum Blam::Network::LifeCycleState)> callback) // 0x10A9A350
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnLifeCycleStateChanged@Network@Patches@@YAXV?$function@$$A6AXW4LifeCycleState@Network@Blam@@@Z@std@@@Z");
			// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> callback;

			lifeCycleStateChangedCallbacks.push_back(callback);
		}

		void RegisterSessionListener(std::shared_ptr<Patches::Network::NetworkSessionListener> observer) // 0x10A9AB60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterSessionListener@Network@Patches@@YAXV?$shared_ptr@VNetworkSessionListener@Network@Patches@@@std@@@Z");
			// std::shared_ptr<Patches::Network::NetworkSessionListener> observer;

			sessionObserver = observer;
		}

		void OnMapVariantRequestChange(std::function<void __cdecl(s_map_variant *)> callback) // 0x10A9A3F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnMapVariantRequestChange@Network@Patches@@YAXV?$function@$$A6AXPAUs_map_variant@@@Z@std@@@Z");
			// std::function<void __cdecl(s_map_variant *)> callback;

			mapVariantRequestChangeCallbacks.push_back(callback);
		}

		void Tick() // 0x10A9B020
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
				// __int32 i;
					// Blam::Network::PlayerSession *player;
					// Blam::Network::PeerInfo *peer;
					// __int32 peerIndex;

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
			{
				Modules::ModuleVoIP::Instance().playersSpeaking &= session->MembershipInfo.ActivePlayerMask;
				Modules::ModuleVoIP::Instance().playersSpoke &= session->MembershipInfo.ActivePlayerMask;
				Modules::ModuleVoIP::Instance().playersMuted &= session->MembershipInfo.ActivePlayerMask;
				if (session->IsHost())
				{
					for (__int32 i = session->MembershipInfo.FindFirstPlayer(); i != -1; i = session->MembershipInfo.FindNextPlayer(i))
					{
						__int32 peerIndex = session->MembershipInfo.GetPlayerPeer(i);
						Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[i];
						Blam::Network::PeerInfo *peer = &session->MembershipInfo.Peers[peerIndex];
						if (peer->ConnectionState == Blam::Network::ePeerConnectionStateEstablished && system_milliseconds() - peer->StartTime > 7000 && !player->Unknown0)
							Blam::Network::BootPlayer(i, 4);
					}
				}
			}
			else
			{
				Modules::ModuleVoIP::Instance().playersSpeaking = 0;
				Modules::ModuleVoIP::Instance().playersSpoke = 0;
				Modules::ModuleVoIP::Instance().playersMuted = 0;
			}
		}
	}
}

/* ---------- private code */

unsigned long Network_managed_session_create_session_internalHook(__int32 a1, __int32 a2) // 0x10A995B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_managed_session_create_session_internalHook@@YAKHH@Z");
	// `anonymous-namespace'::Network_managed_session_create_session_internalHook
	// __int32 a2;
	// unsigned long retval;
	// unsigned long (*Network_managed_session_create_session_internal)(__int32, __int32);
	// bool isHost;
	// unsigned long isOnline;
	// function call : unsigned long (*)(__int32, __int32)
	// function call : void ()

	unsigned long isOnline = *(unsigned long *)a2;
	bool isHost = *(unsigned short *)(a2 + 284) & 1;
	unsigned long (__cdecl *managed_session_create_session_internal)(__int32, __int32) = (unsigned long(__cdecl *)(__int32, __int32))0x481550;
	unsigned long retval = managed_session_create_session_internal(a1, a2);
	if (!isHost)
		return retval;
	if (isOnline == 1)
	{
		sessionObserver->SessionCreated();
		Server::InfoServer::StartInfoServer();
		Server::Signaling::StartServer();
	}
	else
	{
		Server::InfoServer::StopInfoServer();
		Server::Signaling::StopServer();
	}
	return retval;
}

void __fastcall network_session_send_peer_establish_hook(c_network_session *thisPtr, void *unused, long transmission_type, long peer_index, long message_type, long data_length, void const *data) // 0x10A9E630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?network_session_send_peer_establish_hook@@YIXPAVc_network_session@@PAXJJJJPBX@Z");
	// `anonymous-namespace'::network_session_send_peer_establish_hook
	// void const *data;
	// constexpr void (*const `network_session_send_peer_establish_hook'::`2'::c_network_session__send_message_to_peer)(c_network_session *, long, long, long, long, void const *); // constant == 4582224
	// function call : void (*const)(c_network_session *, long, long, long, long, void const *)

	((void(__thiscall *)(c_network_session *, long, long, long, long, void const *))0x45eb50)(thisPtr, transmission_type, peer_index, message_type, data_length, data);
}

char *Network_GetIPStringFromInAddr(void *inaddr) // 0x10A98EC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_GetIPStringFromInAddr@@YAPADPAX@Z");
	// `anonymous-namespace'::Network_GetIPStringFromInAddr
	// void *inaddr;
	// unsigned char ip3;
	// unsigned char ip2;
	// unsigned char ip1;
	// unsigned char ip0;
	// static char `Network_GetIPStringFromInAddr'::`2'::ipAddrStr[64]; // 0x12464828
	// unsigned short port;
	// unsigned short type;

	static char ipAddrStr[64];
	memset(ipAddrStr, 0, sizeof(ipAddrStr));
	unsigned char ip3 = *(unsigned char *)inaddr;
	unsigned char ip2 = *((unsigned char *)inaddr + 1);
	unsigned char ip1 = *((unsigned char *)inaddr + 2);
	unsigned char ip0 = *((unsigned char *)inaddr + 3);
	unsigned short port = *((unsigned short *)inaddr + 8);
	unsigned short type = *((unsigned short *)inaddr + 9);
	sprintf_s(ipAddrStr, 64, "%hd.%hd.%hd.%hd:%hu (%hd)", ip0, ip1, ip2, ip3, port, type);
	return ipAddrStr;
}

unsigned __int32 GetPlayerPropertiesPacketSize() // 0x10A98140
{
	// `anonymous-namespace'::GetPlayerPropertiesPacketSize
	// procedure flags: nofpo
	// static unsigned __int32 `GetPlayerPropertiesPacketSize'::`2'::size; // 0x12464868
		// unsigned __int32 extensionSize;

	static unsigned int size = 0;
	if (size == 0)
	{
		unsigned int totalSize = Utils::Singleton<Patches::Network::PlayerPropertiesExtender>::Instance().GetTotalSize();
		size = totalSize + 76;
	}
	return size;
}

void __fastcall RegisterPlayerPropertiesPacketHook(void *thisPtr, void *unused, __int32 packetId, char const *packetName, __int32 arg8, __int32 size1, __int32 size2, void *serializeFunc, void *deserializeFunc, __int32 arg1C, __int32 arg20) // 0x10A9AAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterPlayerPropertiesPacketHook@@YIXPAX0HPBDHHH00HH@Z");
	// `anonymous-namespace'::RegisterPlayerPropertiesPacketHook
	// __int32 arg20;
	// unsigned __int32 newSize;
	// void (*RegisterPacket)(void *, __int32, char const *, __int32, __int32, __int32, void *, void *, __int32, __int32);
	// function call : void (*)(void *, __int32, char const *, __int32, __int32, __int32, void *, void *, __int32, __int32)

	unsigned int newSize = GetPlayerPropertiesPacketSize();
	void (__thiscall *RegisterPacket)(void *, __int32, char const *, __int32, unsigned int, unsigned int, void *, void *, __int32, __int32) = (void(__thiscall *)(void *, __int32, char const *, __int32, unsigned int, unsigned int, void *, void *, __int32, __int32))0x4801b0;

	RegisterPacket(thisPtr, packetId, packetName, arg8, newSize, newSize, serializeFunc, deserializeFunc, arg1C, arg20);
}

bool IsNameNotAllowed(std::string name) // 0x10A98410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsNameNotAllowed@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::IsNameNotAllowed
	// static ...; // 0x10A98577
	// static ...; // 0x10A9856E
	// static ...; // 0x10A9856C
	// static ...; // 0x10A98548
	// static ...; // 0x10A98540
	// std::string name;
		// std::unordered_set<std::string> &<range>$L0;
		// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <begin>$L0;
		// std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<std::string> >,std::_Iterator_base0> <end>$L0;
			// std::string s;

	for (std::string s : Modules::ModuleServer::Instance().NonAllowedNames) {
		if (name.find(s) != std::string::npos)
			return true;
	}
	return false;
}

void SanitizePlayerName(wchar_t *name) // 0x10A9ABC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SanitizePlayerName@@YAXPA_W@Z");
	// `anonymous-namespace'::SanitizePlayerName
	// static ...; // 0x10A9AEAC
	// static ...; // 0x10A9AEA0
	// static ...; // 0x10A9AE98
	// wchar_t *name;
	// __int32 i;
	// __int32 dest;
	// bool space;
		// bool allowed;
		// std::string lowercasename;

	__int32 i;
	__int32 dest = 0;
	bool space = false;
	for (i = 0; i < 15 && dest < 15 && name[i]; i++)
	{
		bool allowed = name[i] == L'_' || name[i] == L'-' || (name[i] >= L'0' && name[i] <= L'9') || (name[i] >= L'A' && name[i] <= L'Z') || (name[i] >= L'a' && name[i] <= L'z');
		if (!allowed)
		{
			if (name[i] == L' ' && dest > 0)
				space = true;
		}
		else
		{
			if (space && dest < 14)
			{
				name[dest] = L' ';
				dest++;
				space = false;
			}
			name[dest] = name[i];
			dest++;
		}
	}
	memset(&name[dest], 0, (16 - dest) * sizeof(wchar_t));
	if (!dest)
	{
		Utils::String::StrzCopy(name, 16, L"Forgot");
	}
	else
	{
		std::string lowercasename = Utils::String::ThinString(name);
		std::transform(lowercasename.begin(), lowercasename.end(), lowercasename.begin(), tolower);
		if (IsNameNotAllowed(lowercasename))
			Utils::String::StrzCopy(name, 16, L"Filtered");
	}
}

void __fastcall ApplyPlayerPropertiesExtended(Blam::Network::SessionMembership *thisPtr, void *unused, __int32 playerIndex, unsigned __int32 arg4, unsigned __int32 arg8, unsigned char *data, unsigned __int32 arg10) // 0x10A934B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyPlayerPropertiesExtended@@YIXPAUSessionMembership@Network@Blam@@PAXHIIPAEI@Z");
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
		// long currentTeamIndex;
		// __int32 playerIdx;
		// __int32 numTeams;
		// Modules::ModuleServer &moduleServer;
		// __int32 minTeams;
		// __int32 numPlayers;
		// unsigned long minTeamSize;
		// unsigned long maxPlayers;
		// s_player_configuration *prop;
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
				// long teamIndex;
				// __int32 i;
	// function call : void (__int32)
	// function call : void (*const)(void *, __int32, unsigned __int32, unsigned __int32, void *, unsigned __int32)

	s_player_configuration *properties = &thisPtr->PlayerSessions[playerIndex].Properties;
	bool isNewMember = false;
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	s_player_configuration_from_client *packetProperties = (s_player_configuration_from_client *)data;
	if (properties->host.player_name[0])
		memcpy(data, properties->host.player_name, sizeof(properties->host.player_name));
	else
	{
		SanitizePlayerName((wchar_t *)packetProperties);
		Server::Signaling::SendPeerPassword(playerIndex);
		Server::Voting::PlayerJoinedVoteInProgress(playerIndex);
		if (session->MembershipInfo.GetLocalPlayerSession().PeerIndex != thisPtr->PlayerSessions[playerIndex].PeerIndex)
			Server::Stats::UpdatePlayersInfo();
		isNewMember = true;
	}
	if (session->HasTeams() && session->MembershipInfo.PlayerSessions[playerIndex].Properties.host.team != packetProperties->multiplayer_team)
	{
		__int32 numPlayers = 0;
		__int32 playerIdx = session->MembershipInfo.FindFirstPlayer();
		while (playerIdx > -1)
		{
			numPlayers++;
			playerIdx = session->MembershipInfo.FindNextPlayer(playerIdx);
		}
		long currentTeamIndex = session->MembershipInfo.PlayerSessions[playerIndex].Properties.host.team;
		Modules::ModuleServer &moduleServer = Modules::ModuleServer::Instance();
		unsigned long maxPlayers = moduleServer.VarServerMaxPlayers->ValueInt;
		unsigned long minTeamSize = moduleServer.VarMinTeamSize->ValueInt;
		__int32 minTeams = (int)ceil(numPlayers / (float)minTeamSize);
		__int32 numTeams = std::min<int>(minTeams, moduleServer.VarNumTeams->ValueInt);
		if (packetProperties->multiplayer_team < 0 || packetProperties->multiplayer_team >= 8)
			packetProperties->multiplayer_team = (unsigned char)currentTeamIndex;
	}
	if (isNewMember)
	{
		s_player_configuration *prop = &session->MembershipInfo.PlayerSessions[playerIndex].Properties;
		if (session->HasTeams())
		{
			__int32 teamSizes[8] = { 0 };
			__int32 playerIdx = session->MembershipInfo.FindFirstPlayer();
			__int32 numPlayers = 0;
			while (playerIdx > -1)
			{
				long teamIndex = session->MembershipInfo.PlayerSessions[playerIdx].Properties.host.team;
				if (teamIndex > -1 && teamIndex < 8)
					teamSizes[teamIndex]++;
				numPlayers++;
				playerIdx = session->MembershipInfo.FindNextPlayer(playerIdx);
			}
			if (prop->host.team > -1 && prop->host.team < 8)
				teamSizes[prop->host.team]--;
			Modules::ModuleServer &moduleServer = Modules::ModuleServer::Instance();
			unsigned long maxPlayers = moduleServer.VarServerMaxPlayers->ValueInt;
			unsigned long minTeamSize = moduleServer.VarMinTeamSize->ValueInt;
			__int32 minTeams = (int)ceil(numPlayers / (float)minTeamSize);
			__int32 numTeams = std::min<int>(minTeams, moduleServer.VarNumTeams->ValueInt);
			__int32 smallest = 17;
			__int32 smallIndex = 0;
			for (__int32 i = 0; i < numTeams; i++)
			{
				if (teamSizes[i] < smallest)
				{
					smallest = teamSizes[i];
					smallIndex = i;
				}
			}
			if (smallIndex > -1 && smallIndex < 8)
				packetProperties->multiplayer_team = (unsigned char)smallIndex;
			sessionObserver->PlayerAdded(playerIndex);
		}
	}
	void (__thiscall *const ApplyPlayerProperties)(void *, __int32, unsigned __int32, unsigned __int32, void *, unsigned __int32) = (void (__thiscall *)(void *, __int32, unsigned __int32, unsigned __int32, void *, unsigned __int32))0x450890;
	ApplyPlayerProperties(thisPtr, playerIndex, arg4, arg8, data, arg10);
	Utils::Singleton<Patches::Network::PlayerPropertiesExtender>::Instance().ApplyData(playerIndex, properties, data + 0x30);
	Server::BanList banList = Server::LoadDefaultBanList();
	char uidst[17];
	player_format_uid(uidst, properties->host.player_uid);
	std::string uidStr(uidst);
	if (banList.ContainsUid(properties->host.player_uid) || Utils::Singleton<Server::StatsServersBanList>::Instance().ContainsUID(uidst))
	{
		if (!Blam::Network::BootPlayer(playerIndex, 13))
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Failed to Kick Banned UID: " + uidStr);
		else
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Successfully Kicked Banned UID: " + uidStr);
	}
	std::string name = Utils::String::ThinString(packetProperties->player_name);
	if (banList.ContainsName(name) || Utils::Singleton<Server::StatsServersBanList>::Instance().ContainsName(name))
	{
		if (!Blam::Network::BootPlayer(playerIndex, 13))
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Failed to Kick Banned Name: " + name);
		else
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Successfully Kicked Banned Name: " + name);
	}
	Server::HsGlobalSync::InvalidatePlayerMask(1 << playerIndex);
}

bool __fastcall Network_leader_request_boot_machineHook(void *thisPtr, void *unused, Blam::Network::PeerInfo *peer, __int32 reason) // 0x10A99390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_leader_request_boot_machineHook@@YI_NPAX0PAUPeerInfo@Network@Blam@@H@Z");
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

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	Blam::Network::SessionMembership *membership = &session->MembershipInfo;
	__int32 peerIndex = peer - membership->Peers;
	__int32 playerIndex = membership->GetPeerPlayer(peerIndex);
	std::string playerName;
	if (playerIndex >= 0)
		playerName = Utils::String::ThinString(membership->PlayerSessions[playerIndex].Properties.host.player_name);

	bool (__thiscall *Network_leader_request_boot_machine)(void *, void *, __int32) = reinterpret_cast<bool (__thiscall *)(void *, void *, __int32)>(0x45D4A0);
	if (!Network_leader_request_boot_machine(thisPtr, peer, reason))
		return false;
	return true;
}

bool __fastcall Network_session_handle_join_requestHook(Blam::Network::Session *thisPtr, void *unused, Blam::Network::NetworkAddress const &address, void *request) // 0x10A996B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_session_handle_join_requestHook@@YI_NPAUSession@Network@Blam@@PAXABUNetworkAddress@23@1@Z");
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
		// Server::BanList banList;
		// Server::BanList::BanType banType;
			// constexpr void (*const `Network_session_handle_join_requestHook'::`8'::Network_session_acknowledge_join_request)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, __int32); // constant == 4563504
	// function call : void (*const)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, __int32)
	// function call : void (*const)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, __int32)
	// function call : bool (*)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, void *)

	in_addr inAddr;
	inAddr.s_addr = address.ToInAddr();
	char ipStr[22];
	if (inet_ntop(AF_INET, &inAddr, ipStr, sizeof(ipStr)))
	{
		Server::BanList banList = Server::LoadDefaultBanList();
		Server::BanList::BanType banType = banList.IsBanned(ipStr);
		if (banType != Server::BanList::eNone)
		{
			static void (__thiscall *const Network_session_acknowledge_join_request)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, __int32) = reinterpret_cast<void (__thiscall *)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, __int32)>(0x45A230);
			if (banType == Server::BanList::eTemp)
				Network_session_acknowledge_join_request(thisPtr, address, 0x2B);
			else
				Network_session_acknowledge_join_request(thisPtr, address, 0);
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Refused join request from banned IP %s", ipStr);
			return true;
		}
	}
	bool (__thiscall *Network_session_handle_join_request)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, void *) = reinterpret_cast<bool (__thiscall *)(Blam::Network::Session *, Blam::Network::NetworkAddress const &, void *)>(0x4DA410);
	return Network_session_handle_join_request(thisPtr, address, request);
}

__int32 Network_GetMaxPlayersHook() // 0x10A98FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_GetMaxPlayersHook@@YAHXZ");
	// `anonymous-namespace'::Network_GetMaxPlayersHook
	// procedure flags: nofpo
	// __int32 maxPlayers;

	__int32 maxPlayers = Utils::Singleton<Modules::ModuleServer>::Instance().VarServerMaxPlayers->ValueInt;
	return Utils::Clamp(maxPlayers, 1, 16);
}

__int32 Pregame_Lobby_Max_Player_Count_Offline_hook() // 0x10A9AA90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Pregame_Lobby_Max_Player_Count_Offline_hook@@YAHXZ");
	// `anonymous-namespace'::Pregame_Lobby_Max_Player_Count_Offline_hook
	// procedure flags: nofpo

	return 1;
}

bool __fastcall PeerRequestPlayerDesiredPropertiesUpdateHook(Blam::Network::Session *thisPtr, void *unused, unsigned __int32 arg0, unsigned __int32 arg4, s_player_configuration_from_client *properties, unsigned __int32 argC) // 0x10A9A570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PeerRequestPlayerDesiredPropertiesUpdateHook@@YI_NPAUSession@Network@Blam@@PAXIIPAUs_player_configuration_from_client@@I@Z");
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
		// __int32 channelIndex;
		// void (*InitPacket)(__int32, void *);
		// __int32 hostPeer;
		// std::unique_ptr<unsigned char [0]> packet;
	// function call : void (*)(__int32, void *)

	if (thisPtr->Type == 3)
		return false;
	Blam::Network::SessionMembership *membership = &thisPtr->MembershipInfo;
	__int32 playerIndex = thisPtr->MembershipInfo.GetPeerPlayer(membership->LocalPeerIndex);
	if (playerIndex == -1)
		return false;
	memcpy(properties, Utils::Singleton<Modules::ModulePlayer>::Instance().UserName, 0x20);
	unsigned __int32 packetSize = GetPlayerPropertiesPacketSize();
	unsigned __int32 extendedSize = packetSize - 0x1C;
	std::unique_ptr<unsigned char[]> extendedProperties = std::make_unique<unsigned char[]>(extendedSize);
	memcpy(&extendedProperties[0], properties, 0x30);
	Utils::Singleton<Patches::Network::PlayerPropertiesExtender>::Instance().BuildData(playerIndex, &extendedProperties[0x30]);
	if (thisPtr->Type == 6 || thisPtr->Type == 7)
	{
		ApplyPlayerPropertiesExtended(membership, nullptr, playerIndex, arg0, arg4, &extendedProperties[0], argC);
	}
	else
	{
		__int32 hostPeer = membership->HostPeerIndex;
		__int32 channelIndex = membership->PeerChannels[hostPeer].ChannelIndex;
		if (channelIndex == -1)
			return true;
		std::unique_ptr<unsigned char[]> packet = std::make_unique<unsigned char[]>(packetSize);
		memset(&packet[0], 0, packetSize);
		void (*InitPacket)(__int32, void *) = reinterpret_cast<void (*)(__int32, void *)>(0x482040);
		InitPacket(thisPtr->AddressIndex, &packet[0]);
		*reinterpret_cast<unsigned __int32 *>(&packet[0x10]) = arg0;
		*reinterpret_cast<unsigned __int32 *>(&packet[0x14]) = arg4;
		*reinterpret_cast<unsigned __int32 *>(&packet[packetSize - 4]) = argC;
		memcpy(&packet[0x18], &extendedProperties[0], extendedSize);
		thisPtr->Observer->ObserverChannelSendMessage(thisPtr->Unknown10, channelIndex, false, 0x1A, packetSize, &packet[0]);
	}
	return true;
}

bool __fastcall Network_Session_Membership__Add_Peer_Hook(c_network_session_membership *thisptr, void *unused, long peer_index, Blam::Network::PeerConnectionState connection_state, long version, void *xnaddr, unsigned long long unknown_nonce, unsigned long long join_nonce) // 0x10A99250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_Session_Membership__Add_Peer_Hook@@YI_NPAVc_network_session_membership@@PAXJW4PeerConnectionState@Network@Blam@@J1_K3@Z");
	// `anonymous-namespace'::Network_Session_Membership__Add_Peer_Hook
	// unsigned long long join_nonce;
	// constexpr bool (*const `Network_Session_Membership__Add_Peer_Hook'::`2'::c_network_session_membership__add_peer)(void *, long, Blam::Network::PeerConnectionState, long, void *, unsigned long long, unsigned long long); // constant == 4509152
	// bool result;
	// function call : bool (*const)(void *, long, Blam::Network::PeerConnectionState, long, void *, unsigned long long, unsigned long long)
	// function call : void ()
	// function call : void (__int32)

	bool result = ((bool (__thiscall *)(c_network_session_membership *, long, Blam::Network::PeerConnectionState, long, void *, unsigned long long, unsigned long long))0x44cde0)(thisptr, peer_index, connection_state, version, xnaddr, unknown_nonce, join_nonce);

	if (Blam::Network::GetActiveSession()->IsHost())
	{
		if (thisptr->host_peer_index() == peer_index)
			sessionObserver->SessionCreated();

		sessionObserver->PeerAdded(peer_index);
	}

	return result;
}

char __fastcall Network_Session_Membership_Remove_Peer_Hook(c_network_session_membership *thisptr, void *unused, long peer_index) // 0x10A99000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_Session_Membership_Remove_Peer_Hook@@YIDPAVc_network_session_membership@@PAXJ@Z");
	// `anonymous-namespace'::Network_Session_Membership_Remove_Peer_Hook
	// static ...; // 0x10A991B0
	// c_network_session_membership *thisptr;
	// void *unused;
	// long peer_index;
	// constexpr char (*const `Network_Session_Membership_Remove_Peer_Hook'::`2'::c_network_session_membership__remove_peer)(c_network_session_membership *, long); // constant == 4521520
		// std::string playerName;
		// __int32 playerIdx;
		// Blam::Network::SessionMembership *membership;
	// function call : void (__int32)
	// function call : void ()
	// function call : char (*const)(c_network_session_membership *, long)

	static char (__thiscall *const c_network_session_membership__remove_peer)(c_network_session_membership *, long) = (char (__thiscall *)(c_network_session_membership *, long))0x44FE30;
	if (Blam::Network::GetActiveSession()->IsHost())
	{
		Blam::Network::SessionMembership *membership = reinterpret_cast<Blam::Network::SessionMembership *>(thisptr);
		__int32 playerIdx = membership->GetPeerPlayer(peer_index);
		std::string playerName = Utils::String::ThinString(membership->PlayerSessions[playerIdx].Properties.host.player_name);
		Server::Voting::PlayerLeftVoting(playerName);
		sessionObserver->PeerRemoved(peer_index);
		if (thisptr->host_peer_index() == peer_index || !thisptr->has_membership())
			sessionObserver->SessionDestroyed();
		Server::Stats::UpdatePlayersInfo();
	}
	return c_network_session_membership__remove_peer(thisptr, peer_index);
}

void SerializePlayerPropertiesHook(Blam::BitStream *stream, unsigned char *buffer, bool flag) // 0x10A9AF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SerializePlayerPropertiesHook@@YAXPAVBitStream@Blam@@PAE_N@Z");
	// `anonymous-namespace'::SerializePlayerPropertiesHook
	// bool flag;
	// void (*SerializePlayerProperties)(Blam::BitStream *, unsigned char *, bool);
	// function call : void (*)(Blam::BitStream *, unsigned char *, bool)

	void (*SerializePlayerProperties)(Blam::BitStream *, unsigned char *, bool) = (void(*)(Blam::BitStream *, unsigned char *, bool))0x4433c0;

	SerializePlayerProperties(stream, buffer, flag);
	Utils::Singleton<Patches::Network::PlayerPropertiesExtender>::Instance().SerializeData(stream, buffer + 48);
}

bool DeserializePlayerPropertiesHook(Blam::BitStream *stream, unsigned char *buffer, bool flag) // 0x10A94970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DeserializePlayerPropertiesHook@@YA_NPAVBitStream@Blam@@PAE_N@Z");
	// `anonymous-namespace'::DeserializePlayerPropertiesHook
	// bool flag;
	// bool succeeded;
	// bool (*DeserializePlayerProperties)(Blam::BitStream *, unsigned char *, bool);
	// function call : bool (*)(Blam::BitStream *, unsigned char *, bool)

	bool (*DeserializePlayerProperties)(Blam::BitStream *, unsigned char *, bool) = (bool(*)(Blam::BitStream *, unsigned char *, bool))0x4432e0;

	bool succeeded = DeserializePlayerProperties(stream, buffer, flag);
	if (succeeded)
		Utils::Singleton<Patches::Network::PlayerPropertiesExtender>::Instance().DeserializeData(stream, buffer + 48);

	return succeeded;
}

char __fastcall Network_state_end_game_write_stats_enterHook(void *thisPtr, __int32 unused, __int32 a2, __int32 a3, __int32 a4) // 0x10A9A240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_state_end_game_write_stats_enterHook@@YIDPAXHHHH@Z");
	// `anonymous-namespace'::Network_state_end_game_write_stats_enterHook
	// __int32 a4;
	// char (*Network_state_end_game_write_stats_enter)(void *, __int32, __int32, __int32);
	// function call : char (*)(void *, __int32, __int32, __int32)

	char (__thiscall *Network_state_end_game_write_stats_enter)(void *, __int32, __int32, __int32) = (char(__thiscall *)(void *, __int32, __int32, __int32))0x492b50;

	return Network_state_end_game_write_stats_enter(thisPtr, a2, a3, a4);
}

char __fastcall Network_state_leaving_enterHook(void *thisPtr, __int32 unused, __int32 a2, __int32 a3, __int32 a4) // 0x10A9A2C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_state_leaving_enterHook@@YIDPAXHHHH@Z");
	// `anonymous-namespace'::Network_state_leaving_enterHook
	// __int32 a4;
	// char (*Network_state_leaving_enter)(void *, __int32, __int32, __int32);
	// function call : char (*)(void *, __int32, __int32, __int32)

	Server::InfoServer::StopInfoServer();
	Server::Signaling::StopServer();

	char (__thiscall *original)(void *, __int32, __int32, __int32) = (char(__thiscall *)(void *, __int32, __int32, __int32))0x4933e0;

	return original(thisPtr, a2, a3, a4);
}

void __fastcall c_network_session__host_connection_refused_hook(void *session, void *unused, __int32 a2, __int32 type) // 0x10A9D920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_network_session__host_connection_refused_hook@@YIXPAX0HH@Z");
	// `anonymous-namespace'::c_network_session__host_connection_refused_hook
	// __int32 type;
	// constexpr void (*const `c_network_session__host_connection_refused_hook'::`2'::c_network_session__host_connection_refused)(void *, __int32, __int32); // constant == 4572464
	// function call : void (*const)(void *, __int32, __int32)

	switch (type)
	{
	case 0x2b:
		Web::Ui::ScreenLayer::ShowAlert("Connection Refused", "You are temporarily banned", (Web::Ui::ScreenLayer::AlertIcon)0, 0.0f);
		break;
	}

	((void (__thiscall *)(void *, __int32, __int32))0x45c530)(session, a2, type);
}

void PongReceivedHookImpl(Blam::Network::NetworkAddress const &from, Blam::Network::PongPacket const &pong, unsigned __int32 latency) // 0x10A9A9E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PongReceivedHookImpl@@YAXABUNetworkAddress@Network@Blam@@ABUPongPacket@23@I@Z");
	// `anonymous-namespace'::PongReceivedHookImpl
	// unsigned __int32 latency;
		// std::vector<std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> > &<range>$L0;
		// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> *<begin>$L0;
		// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> *<end>$L0;
			// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> &callback;

	for (auto &&callback : pongCallbacks)
		callback(from, pong.Timestamp, pong.ID, latency);
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

void LifeCycleStateChangedHookImpl(Blam::Network::LifeCycleState newState) // 0x10A98600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LifeCycleStateChangedHookImpl@@YAXW4LifeCycleState@Network@Blam@@@Z");
	// `anonymous-namespace'::LifeCycleStateChangedHookImpl
	// static ...; // 0x10A98AF4
	// static ...; // 0x10A98AE8
	// static ...; // 0x10A98AE0
	// Blam::Network::LifeCycleState newState;
		// std::string previousValue;
		// std::vector<std::function<void __cdecl(enum Blam::Network::LifeCycleState)> > &<range>$L0;
		// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> *<begin>$L0;
		// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> *<end>$L0;
			// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> &callback;

	switch (newState)
	{
	case Blam::Network::eLifeCycleStateEndGameWriteStats:
	case Blam::Network::eLifeCycleStateLeaving:
	{
		std::string previousValue;
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVoteStarted, std::string("0"), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVoteStartedByUid, std::string(""), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVoteAction, std::string(""), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVotesNeeded, std::string("0"), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVoteStartedClient, std::string("0"), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVoteStartedByUidClient, std::string(""), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVoteActionClient, std::string(""), previousValue);
		Modules::CommandMap::Instance().SetVariable2(Modules::ModuleServer::Instance().VarChatVotesNeededClient, std::string("0"), previousValue);
		break;
	}
	}
	for (auto &callback : lifeCycleStateChangedCallbacks)
		callback(newState);
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

bool __fastcall Network_GetEndpointHook(char *thisPtr, void *unused) // 0x10A98C50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_GetEndpointHook@@YI_NPADPAX@Z");
	// `anonymous-namespace'::Network_GetEndpointHook
	// void *unused;
	// char *socket;
	// bool (*Network_link_create_endpoint)(__int32, short, char, void *);
	// bool success;
	// void *(*sub_43FED0)(unsigned __int32);
	// unsigned __int32 port;
	// function call : bool (*)(__int32, short, char, void *)
	// function call : void *(*)(unsigned __int32)

	char* socket = thisPtr + 12;
	uint32_t port = Modules::ModuleServer::Instance().VarServerGamePort->ValueInt;
	bool success = false;

	//bool __cdecl Network_c_network_link::create_endpoint(int a1, __int16 GamePort, char a3, _DWORD *a4)
	typedef bool(__cdecl *Network_link_create_endpointFunc)(int a1, __int16 GamePort, char a3, void *a4);
	Network_link_create_endpointFunc Network_link_create_endpoint = reinterpret_cast<Network_link_create_endpointFunc>(0x43B6F0);

	//LPVOID __cdecl sub_43FED0(SOCKET socket)
	typedef LPVOID(__cdecl *sub_43FED0Func)(SOCKET socket);
	sub_43FED0Func sub_43FED0 = reinterpret_cast<sub_43FED0Func>(0x43FED0);

	while (true)
	{
		Pointer(0x1860454).WriteFast<uint32_t>(port);
		success = Network_link_create_endpoint(0, (short)port, 1, socket);

		if (success)
			break;

		if (*socket)
		{
			sub_43FED0(*socket);
			*socket = 0;
		}

		if (++port - Modules::ModuleServer::Instance().VarServerGamePort->ValueInt >= 1000)
		{
			Pointer(0x1860454).WriteFast<uint32_t>(Modules::ModuleServer::Instance().VarServerGamePort->ValueInt);
			return success;
		}
	}
	return success;
}

char __fastcall Network_session_join_remote_sessionHook(void *thisPtr, __int32 unused, char a2, __int32 a3, __int32 a4, __int32 a5, __int32 a6, __int32 a7, __int32 a8, __int32 a9, __int32 a10, __int32 a11, void *a12, __int32 a13, __int32 a14) // 0x10A99BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_session_join_remote_sessionHook@@YIDPAXHDHHHHHHHHH0HH@Z");
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

	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	jsonWriter.Key("connecting");
	jsonWriter.Bool(true);
	jsonWriter.Key("success");
	jsonWriter.Bool(false);
	jsonWriter.EndObject();

	Web::Ui::ScreenLayer::Notify("serverconnect", jsonBuffer.GetString(), true);

	typedef char(__fastcall *Network_session_join_remote_sessionFunc)(void* thisPtr, int unused, char a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, void *a12, int a13, int a14);
	Network_session_join_remote_sessionFunc Network_session_join_remote_session = reinterpret_cast<Network_session_join_remote_sessionFunc>(0x45D1E0);
	return Network_session_join_remote_session(thisPtr, unused, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);;
}

__int32 __fastcall Network_session_initiate_leave_protocolHook(void *thisPtr, __int32 unused, char forceClose) // 0x10A99960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_session_initiate_leave_protocolHook@@YIHPAXHD@Z");
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

	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	jsonWriter.Key("connecting");
	jsonWriter.Bool(false);
	jsonWriter.Key("success");
	jsonWriter.Bool(false);
	jsonWriter.EndObject();

	Web::Ui::ScreenLayer::Notify("serverconnect", jsonBuffer.GetString(), true);

	typedef int(__fastcall *Network_session_initiate_leave_protocolFunc)(void* thisPtr, int unused, char forceClose);
	Network_session_initiate_leave_protocolFunc Network_session_initiate_leave_protocol = reinterpret_cast<Network_session_initiate_leave_protocolFunc>(0x45CB80);
	return Network_session_initiate_leave_protocol(thisPtr, unused, forceClose);
}

__int32 __fastcall Network_session_parameters_clearHook(void *thisPtr, __int32 unused) // 0x10A99F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_session_parameters_clearHook@@YIHPAXH@Z");
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

	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	jsonWriter.Key("connecting");
	jsonWriter.Bool(false);
	jsonWriter.Key("success");
	jsonWriter.Bool(true);
	jsonWriter.EndObject();

	Web::Ui::ScreenLayer::Notify("serverconnect", jsonBuffer.GetString(), true);

	typedef int(__fastcall *Network_session_parameters_clearFunc)(void* thisPtr, int unused);
	Network_session_parameters_clearFunc Network_session_parameters_clear = reinterpret_cast<Network_session_parameters_clearFunc>(0x486580);
	return Network_session_parameters_clear(thisPtr, unused);
}

__int32 __fastcall Network_session_remove_peerHook(Blam::Network::SessionMembership *membership, void *unused, __int32 peerIndex) // 0x10A9A150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_session_remove_peerHook@@YIHPAUSessionMembership@Network@Blam@@PAXH@Z");
	// `anonymous-namespace'::Network_session_remove_peerHook
	// __int32 peerIndex;
	// __int32 (*Network_session_remove_peer)(Blam::Network::SessionMembership *, __int32);
	// function call : void (__int32)
	// function call : __int32 (*)(Blam::Network::SessionMembership *, __int32)

	if (membership->HostPeerIndex == membership->LocalPeerIndex)
		Server::Signaling::RemovePeer(peerIndex);

	sessionObserver->PeerRemoved(peerIndex);

	__int32 (__thiscall *session_remove_peer)(Blam::Network::SessionMembership *, __int32) = (__int32(__thiscall *)(Blam::Network::SessionMembership *, __int32))0x4500d0;

	return session_remove_peer(membership, peerIndex);
}

bool __fastcall Network_session_parameter_countdown_timer_request_change_hook(void *thisPtr, void *unused, __int32 state, __int32 value) // 0x10A99E40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Network_session_parameter_countdown_timer_request_change_hook@@YI_NPAX0HH@Z");
	// `anonymous-namespace'::Network_session_parameter_countdown_timer_request_change_hook
	// __int32 value;
	// static bool (*`Network_session_parameter_countdown_timer_request_change_hook'::`2'::Network_session_parameter_countdown_timer_request_change)(void *, __int32, __int32); // 0x1135475C
		// unsigned long countDownTimer;
	// function call : bool (*)(void *, __int32, __int32)

	if (state == 2)
	{
		unsigned long countDownTimer = Modules::ModuleServer::Instance().VarServerCountdownLobby->ValueInt;
		value = countDownTimer == 0 ? 0 : countDownTimer + 1;
	}

	static bool (__thiscall *Network_session_parameter_countdown_timer_request_change)(void *, __int32, __int32) = (bool(__thiscall *)(void *, __int32, __int32))0x453740;

	return Network_session_parameter_countdown_timer_request_change(thisPtr, state, value);
}

bool __fastcall c_network_session_parameter_map_variant__request_change_hook(void *thisptr, void *unused, s_map_variant *mapVariant) // 0x10A9DB70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_network_session_parameter_map_variant__request_change_hook@@YI_NPAX0PAUs_map_variant@@@Z");
	// `anonymous-namespace'::c_network_session_parameter_map_variant__request_change_hook
	// s_map_variant *mapVariant;
	// bool (*const c_network_session_parameter_map_variant__request_change)(void *, s_map_variant *);
	// bool ret;
		// std::vector<std::function<void __cdecl(s_map_variant *)> > &<range>$L0;
		// std::function<void __cdecl(s_map_variant *)> *<begin>$L0;
		// std::function<void __cdecl(s_map_variant *)> *<end>$L0;
			// std::function<void __cdecl(s_map_variant *)> &callback;
	// function call : bool (*const)(void *, s_map_variant *)

	bool (__thiscall *const c_network_session_parameter_map_variant__request_change)(void *, s_map_variant *) = (bool(__thiscall *const)(void *, s_map_variant *))0x456480;

	bool ret = c_network_session_parameter_map_variant__request_change(thisptr, mapVariant);
	if (ret)
	{
		for (auto &&callback : mapVariantRequestChangeCallbacks)
			callback(mapVariant);
	}

	return ret;
}

unsigned long long local_user_get_identifier_hook() // 0x10A9E2A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?local_user_get_identifier_hook@@YA_KXZ");
	// `anonymous-namespace'::local_user_get_identifier_hook
	// procedure flags: nofpo

	return *(unsigned long long *)0x199FAB2;
}

void network_broadcast_search_handle_reply_hook(s_transport_address const *usable_address, void *data) // 0x10A9E4E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?network_broadcast_search_handle_reply_hook@@YAXPBUs_transport_address@@PAX@Z");
	// `anonymous-namespace'::network_broadcast_search_handle_reply_hook
	// void *data;
	// char *xnkid;
	// void (*const network_broadcast_search_handle_reply)(s_transport_address const *, void *);
	// void (*const xnet_shim_table_add)(s_transport_address const *, void const *, void const *);
	// char *xnaddr;
	// s_available_session *available_sessions;
	// bool found;
	// long max_session_count;
		// long i;
			// s_available_session *session;
	// function call : void (*const)(s_transport_address const *, void *)
	// function call : void (*const)(s_transport_address const *, void const *, void const *)

	void (*const xnet_shim_table_add)(s_transport_address const *, void const *, void const *) = (void(*const)(s_transport_address const *, void const *, void const *))0x430cd0;
	void (*const network_broadcast_search_handle_reply)(s_transport_address const *, void *) = (void(*const)(s_transport_address const *, void *))0x4d9d30;

	network_broadcast_search_handle_reply(usable_address, data);

	char *xnkid = (char *)data + 0x76;
	char *xnaddr = (char *)data + 0x86;
	long max_session_count = *(long *)0x228E6D8;
	s_available_session *available_sessions = *(s_available_session **)0x228E6DC;
	bool found = false;

	for (long i = 0; !found && i < max_session_count; i++)
	{
		s_available_session *session = &available_sessions[i];
		if (!session->valid)
			continue;

		if (memcmp(session->status.session_id, xnkid, 0x10) == 0)
			found = true;
	}

	if (found)
		xnet_shim_table_add(usable_address, xnaddr, xnkid);
}

void __fastcall c_network_session_membership__build_membership_update_hook(c_network_session_membership *thisptr, void *__formal, long peer_index, s_network_session_shared_membership const *membership, s_network_session_shared_membership const *baseline, s_network_session_membership_update_message *update) // 0x10A9DA60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_network_session_membership__build_membership_update_hook@@YIXPAVc_network_session_membership@@PAXJPBUs_network_session_shared_membership@@2PAUs_network_session_membership_update_message@@@Z");
	// `anonymous-namespace'::c_network_session_membership__build_membership_update_hook
	// s_network_session_membership_update_message *update;
	// void (*const c_network_session_membership__build_membership_update)(c_network_session_membership *, long, s_network_session_shared_membership const *, s_network_session_shared_membership const *, s_network_session_membership_update_message *);
	// function call : void (*const)(c_network_session_membership *, long, s_network_session_shared_membership const *, s_network_session_shared_membership const *, s_network_session_membership_update_message *)

	void (__thiscall *const build_membership_update)(c_network_session_membership *, long, s_network_session_shared_membership const *, s_network_session_shared_membership const *, s_network_session_membership_update_message *) = (void(__thiscall *const)(c_network_session_membership *, long, s_network_session_shared_membership const *, s_network_session_shared_membership const *, s_network_session_membership_update_message *))0x44d400;

	build_membership_update(thisptr, peer_index, thisptr->get_current_membership(), baseline, update);
}

void __fastcall c_network_session_membership__copy_current_to_transmitted_hook(c_network_session_membership *thisptr, void *__formal, long peer_index, s_network_session_shared_membership const *current) // 0x10A9DAF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_network_session_membership__copy_current_to_transmitted_hook@@YIXPAVc_network_session_membership@@PAXJPBUs_network_session_shared_membership@@@Z");
	// `anonymous-namespace'::c_network_session_membership__copy_current_to_transmitted_hook
	// s_network_session_shared_membership const *current;
	// void (*const c_network_session_membership__copy_current_to_transmitted)(c_network_session_membership *, long, s_network_session_shared_membership const *);
	// function call : void (*const)(c_network_session_membership *, long, s_network_session_shared_membership const *)

	void (__thiscall *const copy_current_to_transmitted)(c_network_session_membership *, long, s_network_session_shared_membership const *) = (void(__thiscall *const)(c_network_session_membership *, long, s_network_session_shared_membership const *))0x4509b0;

	copy_current_to_transmitted(thisptr, peer_index, thisptr->get_current_membership());
}

void __fastcall c_network_message_handler__handle_parameters_request_hook(c_network_message_handler *thisptr, void *__formal, void *channel, void *message) // 0x10A9D870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_network_message_handler__handle_parameters_request_hook@@YIXPAUc_network_message_handler@@PAX11@Z");
	// `anonymous-namespace'::c_network_message_handler__handle_parameters_request_hook
	// void *message;
	// void (*const c_network_message_handler__handle_parameters_request)(c_network_message_handler *, void *, void *);
	// function call : bool (*const)()
	// function call : bool (*)()
	// function call : void (*const)(c_network_message_handler *, void *, void *)

	if (!((bool(*)())0x5314B0)() || !game_is_campaign())
		return;
	const auto c_network_message_handler__handle_parameters_request = (void(__thiscall *)(c_network_message_handler *, void *, void *))0x49D4E0;
	c_network_message_handler__handle_parameters_request(thisptr, channel, message);
}

void __fastcall c_network_message_handler__handle_delegate_leadership_hook(c_network_message_handler *__formal, void *__formal1, void *channel, void *message) // 0x10A9D840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_network_message_handler__handle_delegate_leadership_hook@@YIXPAUc_network_message_handler@@PAX11@Z");
	// the original is empty
	// `anonymous-namespace'::c_network_message_handler__handle_delegate_leadership_hook
	// void *message;
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
