/* ---------- headers */

#include "Blam/BlamNetwork.hpp"
#include "hades/hades.h"

#include "Blam/BitStream.hpp"
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
#include "Forge/ForgeUtil.hpp"
#include "Forge/Magnets.hpp"
#include "mods/map_variant_loader.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <ws2ipdef.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
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
#include <utility>

/* ---------- forward declarations */

struct c_game_variant;
struct s_map_variant;
namespace Blam
{
	class BitStream;
}
namespace Blam
{
	namespace Network
	{
		struct GameVariantSessionParameter;
		struct MapVariantSessionParameter;
		struct MessageGateway;
		struct NetworkAddress;
		struct Observer;
		struct ObserverChannel;
		struct PacketHeader;
		struct PacketTable;
		struct PingPacket;
		struct PlayerSession;
		struct Session;
		struct SessionMembership;
		struct SessionParameter;
		struct SessionParameters;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Blam
{
	namespace Network
	{
		extern Blam::Network::Session *GetActiveSession();
		extern Blam::Network::PacketTable *GetPacketTable();
		extern void SetPacketTable(Blam::Network::PacketTable const *newTable);
		extern __int32 GetNumPlayers();
		extern bool BootPlayer(__int32 playerIndex, __int32 reason);
		extern bool EndGame();
		extern __int32 GetLobbyType();
		extern __int32 GetNetworkMode();
		extern bool SetLobbyType(__int32 type);
		extern bool SetNetworkMode(__int32 mode);
		extern bool Disconnect();
		extern void LeaveGame();

		PingPacket MakePingPacket(unsigned short id);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Blam
{
	namespace Network
	{
		extern Session *_sub_1092BB10();
		Blam::Network::Session *GetActiveSession() // 0x1092BB10
		{
			mangled_x86(MANGLED_TODO, "?GetActiveSession@Network@Blam@@YAPAUSession@12@XZ");
			// procedure flags: nofpo
			// static ...; // 0x1092BBD0
			// static ...; // 0x1092BBC4
			// static ...; // 0x1092BBBC
			// Pointer networkSessionPtr;
			todo("implement");
			Blam::Network::Session * __result = _sub_1092BB10();
			return __result;
		}

		_extern __int32 _sub_1092B580(Blam::Network::SessionMembership const *const);
		__int32 SessionMembership::FindFirstPeer() const // 0x1092B580
		{
			mangled_x86(MANGLED_TODO, "?FindFirstPeer@SessionMembership@Network@Blam@@QBEHXZ");
			// Blam::Network::SessionMembership const *const this;
			// __int32 (*MembershipFindFirstPeer)(Blam::Network::SessionMembership const *);
			// function call : __int32 (*)(Blam::Network::SessionMembership const *)
			todo("implement");
			__int32 __result = _sub_1092B580((Blam::Network::SessionMembership const *)this);
			return __result;
		}

		_extern __int32 _sub_1092B660(Blam::Network::SessionMembership const *const, __int32);
		__int32 SessionMembership::FindNextPeer(__int32 lastPeer) const // 0x1092B660
		{
			mangled_x86(MANGLED_TODO, "?FindNextPeer@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 lastPeer;
			// __int32 (*MembershipFindNextPeer)(Blam::Network::SessionMembership const *, __int32);
			// function call : __int32 (*)(Blam::Network::SessionMembership const *, __int32)
			todo("implement");
			__int32 __result = _sub_1092B660((Blam::Network::SessionMembership const *)this, lastPeer);
			return __result;
		}

		_extern __int32 _sub_1092B5F0(Blam::Network::SessionMembership const *const);
		__int32 SessionMembership::FindFirstPlayer() const // 0x1092B5F0
		{
			mangled_x86(MANGLED_TODO, "?FindFirstPlayer@SessionMembership@Network@Blam@@QBEHXZ");
			// Blam::Network::SessionMembership const *const this;
			// __int32 (*MembershipFindFirstPlayer)(Blam::Network::SessionMembership const *);
			// function call : __int32 (*)(Blam::Network::SessionMembership const *)
			todo("implement");
			__int32 __result = _sub_1092B5F0((Blam::Network::SessionMembership const *)this);
			return __result;
		}

		_extern __int32 _sub_1092B6E0(Blam::Network::SessionMembership const *const, __int32);
		__int32 SessionMembership::FindNextPlayer(__int32 lastPlayer) const // 0x1092B6E0
		{
			mangled_x86(MANGLED_TODO, "?FindNextPlayer@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 lastPlayer;
			// __int32 (*MembershipFindNextPlayer)(Blam::Network::SessionMembership const *, __int32);
			// function call : __int32 (*)(Blam::Network::SessionMembership const *, __int32)
			todo("implement");
			__int32 __result = _sub_1092B6E0((Blam::Network::SessionMembership const *)this, lastPlayer);
			return __result;
		}

		_extern __int32 _sub_1092C0E0(Blam::Network::SessionMembership const *const, __int32);
		__int32 SessionMembership::GetPeerPlayer(__int32 peer) const // 0x1092C0E0
		{
			mangled_x86(MANGLED_TODO, "?GetPeerPlayer@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 peer;
			// __int32 (*MembershipGetPeerPlayer)(unsigned __int32 const *, __int32);
			// function call : __int32 (*)(unsigned __int32 const *, __int32)
			todo("implement");
			__int32 __result = _sub_1092C0E0((Blam::Network::SessionMembership const *)this, peer);
			return __result;
		}

		_extern __int32 _sub_1092C1F0(Blam::Network::SessionMembership const *const, __int32);
		__int32 SessionMembership::GetPlayerPeer(__int32 player) const // 0x1092C1F0
		{
			mangled_x86(MANGLED_TODO, "?GetPlayerPeer@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 player;
			todo("implement");
			__int32 __result = _sub_1092C1F0((Blam::Network::SessionMembership const *)this, player);
			return __result;
		}

		_extern __int32 _sub_1092C170(Blam::Network::SessionMembership const *const, __int32);
		__int32 SessionMembership::GetPeerTeam(__int32 peer) const // 0x1092C170
		{
			mangled_x86(MANGLED_TODO, "?GetPeerTeam@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 peer;
			// __int32 playerIndex;
			todo("implement");
			__int32 __result = _sub_1092C170((Blam::Network::SessionMembership const *)this, peer);
			return __result;
		}

		_extern __int32 _sub_1092B760(Blam::Network::SessionMembership *const, std::string const &);
		__int32 SessionMembership::FindPlayerByName(std::string const &name) // 0x1092B760
		{
			mangled_x86(MANGLED_TODO, "?FindPlayerByName@SessionMembership@Network@Blam@@QAEHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x1092B8D0
			// static ...; // 0x1092B8C8
			// Blam::Network::SessionMembership *const this;
			// std::string const &name;
			// __int32 playerIdx;
			// std::wstring wideName;
			// Blam::Network::Session *session;
			todo("implement");
			__int32 __result = _sub_1092B760(this, name);
			return __result;
		}

		extern PlayerSession _sub_1092BD50(Blam::Network::SessionMembership const *const);
		Blam::Network::PlayerSession SessionMembership::GetLocalPlayerSession() const // 0x1092BD50
		{
			mangled_x86(MANGLED_TODO, "?GetLocalPlayerSession@SessionMembership@Network@Blam@@QBE?AUPlayerSession@23@XZ");
			// Blam::Network::SessionMembership const *const this;
			todo("implement");
			Blam::Network::PlayerSession __result = _sub_1092BD50((Blam::Network::SessionMembership const *)this);
			return __result;
		}

		_extern void _sub_1092CED0(Blam::Network::SessionMembership *const);
		void SessionMembership::Update() // 0x1092CED0
		{
			mangled_x86(MANGLED_TODO, "?Update@SessionMembership@Network@Blam@@QAEXXZ");
			// Blam::Network::SessionMembership *const this;
			todo("implement");
			_sub_1092CED0(this);
		}

		_extern void _sub_1092C570(Blam::Network::Observer *const, __int32, __int32, bool, __int32, __int32, void const *);
		void Observer::ObserverChannelSendMessage(__int32 ownerIndex, __int32 channelIndex, bool secure, __int32 id, __int32 packetSize, void const *packet) // 0x1092C570
		{
			mangled_x86(MANGLED_TODO, "?ObserverChannelSendMessage@Observer@Network@Blam@@QAEXHH_NHHPBX@Z");
			// void const *packet;
			// __int32 (*ObserverChannelSendMessage)(Blam::Network::Observer *, __int32, __int32, bool, __int32, __int32, void const *);
			// function call : __int32 (*)(Blam::Network::Observer *, __int32, __int32, bool, __int32, __int32, void const *)
			todo("implement");
			_sub_1092C570(this, ownerIndex, channelIndex, secure, id, packetSize, packet);
		}

		_extern void _sub_1092C860(Blam::Network::Observer *const, __int32, __int32, unsigned short);
		void Observer::Ping(__int32 ownerIndex, __int32 channelIndex, unsigned short id) // 0x1092C860
		{
			mangled_x86(MANGLED_TODO, "?Ping@Observer@Network@Blam@@QAEXHHG@Z");
			// Blam::Network::Observer *const this;
			// __int32 ownerIndex;
			// __int32 channelIndex;
			// unsigned short id;
			// Blam::Network::PingPacket packet;
			todo("implement");
			_sub_1092C860(this, ownerIndex, channelIndex, id);
		}

		extern PacketHeader* _sub_1092B3A0(Blam::Network::PacketHeader *const);
		PacketHeader::PacketHeader() // 0x1092B3A0
		{
			mangled_x86(MANGLED_TODO, "??0PacketHeader@Network@Blam@@QAE@XZ");
			// Blam::Network::PacketHeader *const this;
			// void (*InitPacket)(__int32, Blam::Network::PacketHeader *);
			// Blam::Network::Session *session;
			// function call : void (*)(__int32, Blam::Network::PacketHeader *)
			todo("implement");
			_sub_1092B3A0(this);
		}

		_extern __int32 _sub_1092BC20(Blam::Network::Session const *const, Blam::Network::ObserverChannel const *);
		__int32 Session::GetChannelPeer(Blam::Network::ObserverChannel const *channel) const // 0x1092BC20
		{
			mangled_x86(MANGLED_TODO, "?GetChannelPeer@Session@Network@Blam@@QBEHPBUObserverChannel@23@@Z");
			// Blam::Network::ObserverChannel const *channel;
			// __int32 (*GetChannelIndex)(Blam::Network::Observer const *, unsigned __int32, Blam::Network::ObserverChannel const *);
			// __int32 index;
			// __int32 (*GetChannelPeer)(Blam::Network::SessionMembership const *, __int32);
			// function call : __int32 (*)(Blam::Network::Observer const *, unsigned __int32, Blam::Network::ObserverChannel const *)
			// function call : __int32 (*)(Blam::Network::SessionMembership const *, __int32)
			todo("implement");
			__int32 __result = _sub_1092BC20((Blam::Network::Session const *)this, channel);
			return __result;
		}

		_extern bool _sub_1092C330(Blam::Network::Session const *const);
		bool Session::HasTeams() const // 0x1092C330
		{
			mangled_x86(MANGLED_TODO, "?HasTeams@Session@Network@Blam@@QBE_NXZ");
			// Blam::Network::Session const *const this;
			// Blam::Network::GameVariantSessionParameter const *gameVariantParameter;
			// c_game_variant *gameVariant;
			todo("implement");
			bool __result = _sub_1092C330((Blam::Network::Session const *)this);
			return __result;
		}

		extern NetworkAddress _sub_1092BFD0(Blam::Network::Session const *const, __int32);
		Blam::Network::NetworkAddress Session::GetPeerAddress(__int32 peerIndex) const // 0x1092BFD0
		{
			mangled_x86(MANGLED_TODO, "?GetPeerAddress@Session@Network@Blam@@QBE?AUNetworkAddress@23@H@Z");
			// __int32 peerIndex;
			{
				// __int32 channelIndex;
			}
			todo("implement");
			Blam::Network::NetworkAddress __result = _sub_1092BFD0((Blam::Network::Session const *)this, peerIndex);
			return __result;
		}

		extern NetworkAddress _sub_1092C240(Blam::Network::Session const *const);
		Blam::Network::NetworkAddress Session::GetServerIPAddress() const // 0x1092C240
		{
			mangled_x86(MANGLED_TODO, "?GetServerIPAddress@Session@Network@Blam@@QBE?AUNetworkAddress@23@XZ");
			// Blam::Network::Session const *const this;
			todo("implement");
			Blam::Network::NetworkAddress __result = _sub_1092C240((Blam::Network::Session const *)this);
			return __result;
		}

		_extern __int32 _sub_1092C2C0(Blam::Network::SessionParameters *const);
		__int32 SessionParameters::GetSessionMode() // 0x1092C2C0
		{
			mangled_x86(MANGLED_TODO, "?GetSessionMode@SessionParameters@Network@Blam@@QAEHXZ");
			// Blam::Network::SessionParameters *const this;
			// __int32 (*GetSessionMode)(Blam::Network::SessionParameters *);
			// function call : __int32 (*)(Blam::Network::SessionParameters *)
			todo("implement");
			__int32 __result = _sub_1092C2C0(this);
			return __result;
		}

		_extern bool _sub_1092CCC0(Blam::Network::SessionParameters *const, __int32);
		bool SessionParameters::SetSessionMode(__int32 mode) // 0x1092CCC0
		{
			mangled_x86(MANGLED_TODO, "?SetSessionMode@SessionParameters@Network@Blam@@QAE_NH@Z");
			// __int32 mode;
			// bool (*SetSessionMode)(Blam::Network::SessionParameters *, __int32);
			// function call : bool (*)(Blam::Network::SessionParameters *, __int32)
			todo("implement");
			bool __result = _sub_1092CCC0(this, mode);
			return __result;
		}

		_extern bool _sub_1092C3D0(Blam::Network::SessionParameter const *const);
		bool SessionParameter::IsAvailable() const // 0x1092C3D0
		{
			mangled_x86(MANGLED_TODO, "?IsAvailable@SessionParameter@Network@Blam@@QBE_NXZ");
			// Blam::Network::SessionParameter const *const this;
			// bool (*IsAvailable)(Blam::Network::SessionParameter const *);
			// function call : bool (*)(Blam::Network::SessionParameter const *)
			todo("implement");
			bool __result = _sub_1092C3D0((Blam::Network::SessionParameter const *)this);
			return __result;
		}
	}
}

extern c_game_variant *_sub_1092BA30(Blam::Network::GameVariantSessionParameter const *const);
namespace Blam
{
	namespace Network
	{
		c_game_variant *GameVariantSessionParameter::Get() const // 0x1092BA30
		{
			mangled_x86(MANGLED_TODO, "?Get@GameVariantSessionParameter@Network@Blam@@QBEPAUc_game_variant@@XZ");
			// Blam::Network::GameVariantSessionParameter const *const this;
			// c_game_variant *(*GetGameVariant)(Blam::Network::GameVariantSessionParameter const *);
			// function call : c_game_variant *(*)(Blam::Network::GameVariantSessionParameter const *)
			todo("implement");
			c_game_variant * __result = _sub_1092BA30((Blam::Network::GameVariantSessionParameter const *)this);
			return __result;
		}
	}
}

extern s_map_variant *_sub_1092BAA0(Blam::Network::MapVariantSessionParameter const *const);
namespace Blam
{
	namespace Network
	{
		s_map_variant *MapVariantSessionParameter::Get() const // 0x1092BAA0
		{
			mangled_x86(MANGLED_TODO, "?Get@MapVariantSessionParameter@Network@Blam@@QBEPAUs_map_variant@@XZ");
			// Blam::Network::MapVariantSessionParameter const *const this;
			// s_map_variant *(*GetMapVariant)(Blam::Network::MapVariantSessionParameter const *);
			// function call : s_map_variant *(*)(Blam::Network::MapVariantSessionParameter const *)
			todo("implement");
			s_map_variant * __result = _sub_1092BAA0((Blam::Network::MapVariantSessionParameter const *)this);
			return __result;
		}

		extern PacketTable *_sub_1092BEC0();
		Blam::Network::PacketTable *GetPacketTable() // 0x1092BEC0
		{
			mangled_x86(MANGLED_TODO, "?GetPacketTable@Network@Blam@@YAPAUPacketTable@12@XZ");
			// procedure flags: nofpo
			// static ...; // 0x1092BF80
			// static ...; // 0x1092BF74
			// static ...; // 0x1092BF6C
			// Pointer packetTablePtr;
			todo("implement");
			Blam::Network::PacketTable * __result = _sub_1092BEC0();
			return __result;
		}

		_extern void _sub_1092CBC0(Blam::Network::PacketTable const *);
		void SetPacketTable(Blam::Network::PacketTable const *newTable) // 0x1092CBC0
		{
			mangled_x86(MANGLED_TODO, "?SetPacketTable@Network@Blam@@YAXPBUPacketTable@12@@Z");
			// static ...; // 0x1092CC74
			// static ...; // 0x1092CC68
			// static ...; // 0x1092CC60
			// Blam::Network::PacketTable const *newTable;
			// Pointer packetTablePtr;
			todo("implement");
			_sub_1092CBC0(newTable);
		}

		_extern void _sub_1092C980(Blam::Network::PacketTable *const, __int32, char const *, __int32, __int32, __int32, void (*)(Blam::BitStream *, __int32, void const *), bool (*)(Blam::BitStream *, __int32, void *), __int32, __int32);
		void PacketTable::Register(__int32 index, char const *name, __int32 unk8, __int32 minSize, __int32 maxSize, void (*serializeFunc)(Blam::BitStream *, __int32, void const *), bool (*deserializeFunc)(Blam::BitStream *, __int32, void *), __int32 unk1C, __int32 unk20) // 0x1092C980
		{
			mangled_x86(MANGLED_TODO, "?Register@PacketTable@Network@Blam@@QAEXHPBDHHHP6AXPAVBitStream@3@HPBX@ZP6A_N1HPAX@ZHH@Z");
			// __int32 unk20;
			// void (*RegisterPacket)(Blam::Network::PacketTable *, __int32, char const *, __int32, __int32, __int32, void (*)(Blam::BitStream *, __int32, void const *), bool (*)(Blam::BitStream *, __int32, void *), __int32, __int32);
			// function call : void (*)(Blam::Network::PacketTable *, __int32, char const *, __int32, __int32, __int32, void (*)(Blam::BitStream *, __int32, void const *), bool (*)(Blam::BitStream *, __int32, void *), __int32, __int32)
			todo("implement");
			_sub_1092C980(this, index, name, unk8, minSize, maxSize, serializeFunc, deserializeFunc, unk1C, unk20);
		}

		_extern bool _sub_1092CA20(Blam::Network::MessageGateway *const, Blam::Network::NetworkAddress const &, __int32, __int32, void const *);
		bool MessageGateway::SendDirectedMessage(Blam::Network::NetworkAddress const &address, __int32 id, __int32 packetSize, void const *packet) // 0x1092CA20
		{
			mangled_x86(MANGLED_TODO, "?SendDirectedMessage@MessageGateway@Network@Blam@@QAE_NABUNetworkAddress@23@HHPBX@Z");
			// void const *packet;
			// bool (*SendDirectedMessage)(Blam::Network::MessageGateway *, Blam::Network::NetworkAddress const &, __int32, __int32, void const *);
			// function call : bool (*)(Blam::Network::MessageGateway *, Blam::Network::NetworkAddress const &, __int32, __int32, void const *)
			todo("implement");
			bool __result = _sub_1092CA20(this, address, id, packetSize, packet);
			return __result;
		}

		_extern bool _sub_1092C750(Blam::Network::MessageGateway *const, Blam::Network::NetworkAddress &, unsigned short);
		bool MessageGateway::Ping(Blam::Network::NetworkAddress &address, unsigned short id) // 0x1092C750
		{
			mangled_x86(MANGLED_TODO, "?Ping@MessageGateway@Network@Blam@@QAE_NAAUNetworkAddress@23@G@Z");
			// static ...; // 0x1092C808
			// Blam::Network::MessageGateway *const this;
			// Blam::Network::NetworkAddress &address;
			// unsigned short id;
			// Blam::Network::PingPacket packet;
			todo("implement");
			bool __result = _sub_1092C750(this, address, id);
			return __result;
		}

		_extern __int32 _sub_1092BE50();
		__int32 GetNumPlayers() // 0x1092BE50
		{
			mangled_x86(MANGLED_TODO, "?GetNumPlayers@Network@Blam@@YAHXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			todo("implement");
			__int32 __result = _sub_1092BE50();
			return __result;
		}

		_extern bool _sub_1092B450(__int32, __int32);
		bool BootPlayer(__int32 playerIndex, __int32 reason) // 0x1092B450
		{
			mangled_x86(MANGLED_TODO, "?BootPlayer@Network@Blam@@YA_NHH@Z");
			// __int32 reason;
			// bool (*Network_squad_session_boot_player)(__int32, __int32);
			// function call : bool (*)(__int32, __int32)
			todo("implement");
			bool __result = _sub_1092B450(playerIndex, reason);
			return __result;
		}

		_extern bool _sub_1092B520();
		bool EndGame() // 0x1092B520
		{
			mangled_x86(MANGLED_TODO, "?EndGame@Network@Blam@@YA_NXZ");
			// procedure flags: nofpo
			// bool (*Network_squad_session_end_game)();
			// function call : bool (*)()
			todo("implement");
			bool __result = _sub_1092B520();
			return __result;
		}

		_extern __int32 _sub_1092BCF0();
		__int32 GetLobbyType() // 0x1092BCF0
		{
			mangled_x86(MANGLED_TODO, "?GetLobbyType@Network@Blam@@YAHXZ");
			// procedure flags: nofpo
			// __int32 (*Get_Type)();
			// function call : __int32 (*)()
			todo("implement");
			__int32 __result = _sub_1092BCF0();
			return __result;
		}

		_extern __int32 _sub_1092BDF0();
		__int32 GetNetworkMode() // 0x1092BDF0
		{
			mangled_x86(MANGLED_TODO, "?GetNetworkMode@Network@Blam@@YAHXZ");
			// procedure flags: nofpo
			// __int32 (*Get_Mode)();
			// function call : __int32 (*)()
			todo("implement");
			__int32 __result = _sub_1092BDF0();
			return __result;
		}

		_extern bool _sub_1092CAB0(__int32);
		bool SetLobbyType(__int32 type) // 0x1092CAB0
		{
			mangled_x86(MANGLED_TODO, "?SetLobbyType@Network@Blam@@YA_NH@Z");
			// __int32 type;
			// bool (*set_server_lobby_type)(__int32);
			// function call : bool (*)(__int32)
			todo("implement");
			bool __result = _sub_1092CAB0(type);
			return __result;
		}

		_extern bool _sub_1092CB20(__int32);
		bool SetNetworkMode(__int32 mode) // 0x1092CB20
		{
			mangled_x86(MANGLED_TODO, "?SetNetworkMode@Network@Blam@@YA_NH@Z");
			// __int32 mode;
			// bool (*Set_Network_Mode)(__int32);
			// bool success;
			// function call : bool (*)(__int32)
			todo("implement");
			bool __result = _sub_1092CB20(mode);
			return __result;
		}

		_extern bool _sub_1092B4C0();
		bool Disconnect() // 0x1092B4C0
		{
			mangled_x86(MANGLED_TODO, "?Disconnect@Network@Blam@@YA_NXZ");
			// procedure flags: nofpo
			// bool (*Network_network_life_cycle_end)();
			// function call : bool (*)()
			todo("implement");
			bool __result = _sub_1092B4C0();
			return __result;
		}

		_extern void _sub_1092C440();
		void LeaveGame() // 0x1092C440
		{
			mangled_x86(MANGLED_TODO, "?LeaveGame@Network@Blam@@YAXXZ");
			// procedure flags: nofpo
			// void (*Network_LeaveGame)();
			// function call : void (*)()
			todo("implement");
			_sub_1092C440();
		}

		_extern bool _sub_1092C600(std::string const &, unsigned short, Blam::Network::NetworkAddress *);
		bool NetworkAddress::Parse(std::string const &addr, unsigned short port, Blam::Network::NetworkAddress *result) // 0x1092C600
		{
			mangled_x86(MANGLED_TODO, "?Parse@NetworkAddress@Network@Blam@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@GPAU123@@Z");
			// static ...; // 0x1092C6F0
			// std::string const &addr;
			// unsigned short port;
			// Blam::Network::NetworkAddress *result;
			// in_addr inAddr;
			// function call : __int32 (__int32, char const *, void *)
			todo("implement");
			bool __result = _sub_1092C600(addr, port, result);
			return __result;
		}
	}
}

extern std::string _sub_1092CDA0(Blam::Network::NetworkAddress const *const);
namespace Blam
{
	namespace Network
	{
		std::string NetworkAddress::ToString() const // 0x1092CDA0
		{
			mangled_x86(MANGLED_TODO, "?ToString@NetworkAddress@Network@Blam@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// static ...; // 0x1092CE8A
			// static ...; // 0x1092CE84
			// static ...; // 0x1092CE6C
			// static ...; // 0x1092CE64
			// Blam::Network::NetworkAddress const *const this;
			// char ipStr[22];
			// in_addr inAddr;
			todo("implement");
			std::string __result = _sub_1092CDA0((Blam::Network::NetworkAddress const *)this);
			return __result;
		}
	}
}

/* ---------- private code */

namespace Blam
{
	namespace Network
	{
		extern PingPacket _sub_1092C4A0(unsigned short);
		PingPacket MakePingPacket(unsigned short id) // 0x1092C4A0
		{
			// `anonymous-namespace'::MakePingPacket
			// static ...; // 0x1092C534
			// static ...; // 0x1092C528
			// static ...; // 0x1092C520
			// unsigned short id;
			// Blam::Network::PingPacket packet;
			todo("implement");
			Blam::Network::PingPacket __result = _sub_1092C4A0(id);
			return __result;
		}
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum c_game_engine_miscellaneous_options::e_flags,unsigned char>::test(c_game_engine_miscellaneous_options::e_flags) const;
template void Pointer::Write<Blam::Network::PacketTable const *>(Blam::Network::PacketTable const *const) const;
