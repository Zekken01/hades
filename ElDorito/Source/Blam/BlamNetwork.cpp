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

#include "Discord/DiscordRPC.h"  // hades: added for 0x1092CB20

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
	}
}

Blam::Network::PingPacket MakePingPacket(unsigned short id);

/* ---------- globals */

void UpdatePresence(__int32 networkMode);

/* ---------- private variables */

/* ---------- public code */

namespace Blam
{
	namespace Network
	{
		Blam::Network::Session *GetActiveSession() // 0x1092BB10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetActiveSession@Network@Blam@@YAPAUSession@12@XZ");
			// procedure flags: nofpo
			// static ...; // 0x1092BBD0
			// static ...; // 0x1092BBC4
			// static ...; // 0x1092BBBC
			// Pointer networkSessionPtr;


			Pointer networkSessionPtr = Pointer::Base(0x15AB848, 1);
			return networkSessionPtr.Read<Blam::Network::Session *>();
		}

		__int32 SessionMembership::FindFirstPeer() const // 0x1092B580
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindFirstPeer@SessionMembership@Network@Blam@@QBEHXZ");
			// Blam::Network::SessionMembership const *const this;
			// __int32 (*MembershipFindFirstPeer)(Blam::Network::SessionMembership const *);
			// function call : __int32 (*)(Blam::Network::SessionMembership const *)

			__int32 (__thiscall *FindFirstPeer)(const SessionMembership *) = (__int32(__thiscall *)(const SessionMembership *))0x44E690;

			return FindFirstPeer(this);
		}

		__int32 SessionMembership::FindNextPeer(__int32 lastPeer) const // 0x1092B660
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindNextPeer@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 lastPeer;
			// __int32 (*MembershipFindNextPeer)(Blam::Network::SessionMembership const *, __int32);
			// function call : __int32 (*)(Blam::Network::SessionMembership const *, __int32)

			__int32 (__thiscall *FindNextPeerImpl)(const SessionMembership *, __int32) = (__int32(__thiscall *)(const SessionMembership *, __int32))0x44e710;

			return FindNextPeerImpl(this, lastPeer);
		}

		__int32 SessionMembership::FindFirstPlayer() const // 0x1092B5F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindFirstPlayer@SessionMembership@Network@Blam@@QBEHXZ");
			// Blam::Network::SessionMembership const *const this;
			// __int32 (*MembershipFindFirstPlayer)(Blam::Network::SessionMembership const *);
			// function call : __int32 (*)(Blam::Network::SessionMembership const *)

			__int32 (__thiscall *FindFirstPlayerImpl)(const SessionMembership *) = (__int32(__thiscall *)(const SessionMembership *))0x44e6c0;

			return FindFirstPlayerImpl(this);
		}

		__int32 SessionMembership::FindNextPlayer(__int32 lastPlayer) const // 0x1092B6E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindNextPlayer@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 lastPlayer;
			// __int32 (*MembershipFindNextPlayer)(Blam::Network::SessionMembership const *, __int32);
			// function call : __int32 (*)(Blam::Network::SessionMembership const *, __int32)

			__int32 (__thiscall *FindNextPlayerImpl)(const SessionMembership *, __int32) = (__int32(__thiscall *)(const SessionMembership *, __int32))0x44e750;

			return FindNextPlayerImpl(this, lastPlayer);
		}

		__int32 SessionMembership::GetPeerPlayer(__int32 peer) const // 0x1092C0E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPeerPlayer@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 peer;
			// __int32 (*MembershipGetPeerPlayer)(unsigned __int32 const *, __int32);
			// function call : __int32 (*)(unsigned __int32 const *, __int32)

			typedef int(*MembershipGetPeerPlayerPtr)(const uint32_t *playerMasks, int max);
			auto MembershipGetPeerPlayer = reinterpret_cast<MembershipGetPeerPlayerPtr>(0x52E280);
			return MembershipGetPeerPlayer(Peers[peer].PlayerMasks, 16);
		}

		__int32 SessionMembership::GetPlayerPeer(__int32 player) const // 0x1092C1F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerPeer@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 player;

			if (player < 0 || player >= 16)
			{
				return -1;
			}

			return PlayerSessions[player].PeerIndex;
		}

		__int32 SessionMembership::GetPeerTeam(__int32 peer) const // 0x1092C170
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPeerTeam@SessionMembership@Network@Blam@@QBEHH@Z");
			// __int32 peer;
			// __int32 playerIndex;

			__int32 playerIndex = GetPeerPlayer(peer);
			if (playerIndex < 0)
				return -1;
			return PlayerSessions[playerIndex].Properties.host.team;
		}

		__int32 SessionMembership::FindPlayerByName(std::string const &name) // 0x1092B760
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindPlayerByName@SessionMembership@Network@Blam@@QAEHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x1092B8D0
			// static ...; // 0x1092B8C8
			// Blam::Network::SessionMembership *const this;
			// std::string const &name;
			// __int32 playerIdx;
			// std::wstring wideName;
			// Blam::Network::Session *session;

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished())
				return -1;
			std::wstring wideName = Utils::String::WidenString(name);
			__int32 playerIdx = session->MembershipInfo.FindFirstPlayer();
			while (playerIdx != -1)
			{
				if (wideName == session->MembershipInfo.PlayerSessions[playerIdx].Properties.host.player_name)
					return playerIdx;
				playerIdx = session->MembershipInfo.FindNextPlayer(playerIdx);
			}
			return -1;
		}

		Blam::Network::PlayerSession SessionMembership::GetLocalPlayerSession() const // 0x1092BD50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetLocalPlayerSession@SessionMembership@Network@Blam@@QBE?AUPlayerSession@23@XZ");
			// Blam::Network::SessionMembership const *const this;

			return PlayerSessions[GetPeerPlayer(LocalPeerIndex)];
		}

		void SessionMembership::Update() // 0x1092CED0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Update@SessionMembership@Network@Blam@@QAEXXZ");
			// Blam::Network::SessionMembership *const this;

			++PlayerUpdateCount;
			++PeerUpdateCount;
		}

		void Observer::ObserverChannelSendMessage(__int32 ownerIndex, __int32 channelIndex, bool secure, __int32 id, __int32 packetSize, void const *packet) // 0x1092C570
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ObserverChannelSendMessage@Observer@Network@Blam@@QAEXHH_NHHPBX@Z");
			// void const *packet;
			// __int32 (*ObserverChannelSendMessage)(Blam::Network::Observer *, __int32, __int32, bool, __int32, __int32, void const *);
			// function call : __int32 (*)(Blam::Network::Observer *, __int32, __int32, bool, __int32, __int32, void const *)

			void (__thiscall *ObserverChannelSendMessageImpl)(Observer *, __int32, __int32, bool, __int32, __int32, void const *) = (void(__thiscall *)(Observer *, __int32, __int32, bool, __int32, __int32, void const *))0x4474f0;

			ObserverChannelSendMessageImpl(this, ownerIndex, channelIndex, secure, id, packetSize, packet);
		}

		void Observer::Ping(__int32 ownerIndex, __int32 channelIndex, unsigned short id) // 0x1092C860
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Ping@Observer@Network@Blam@@QAEXHHG@Z");
			// Blam::Network::Observer *const this;
			// __int32 ownerIndex;
			// __int32 channelIndex;
			// unsigned short id;
			// Blam::Network::PingPacket packet;

			auto packet = MakePingPacket(id);
			ObserverChannelSendMessage(ownerIndex, channelIndex, true, ePacketIDPing, sizeof(packet), &packet);
		}

		PacketHeader::PacketHeader() // 0x1092B3A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0PacketHeader@Network@Blam@@QAE@XZ");
			// Blam::Network::PacketHeader *const this;
			// void (*InitPacket)(__int32, Blam::Network::PacketHeader *);
			// Blam::Network::Session *session;
			// function call : void (*)(__int32, Blam::Network::PacketHeader *)

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session)
			{
				memset(XnkAddr, 0, sizeof(Blam::Network::PacketHeader));
			}
			else
			{
				void (__cdecl *ResolveAddress)(int, Blam::Network::PacketHeader *) = (void(__cdecl *)(int, Blam::Network::PacketHeader *))0x482040;

				ResolveAddress(session->AddressIndex, this);
			}
		}

		__int32 Session::GetChannelPeer(Blam::Network::ObserverChannel const *channel) const // 0x1092BC20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetChannelPeer@Session@Network@Blam@@QBEHPBUObserverChannel@23@@Z");
			// Blam::Network::ObserverChannel const *channel;
			// __int32 (*GetChannelIndex)(Blam::Network::Observer const *, unsigned __int32, Blam::Network::ObserverChannel const *);
			// __int32 index;
			// __int32 (*GetChannelPeer)(Blam::Network::SessionMembership const *, __int32);
			// function call : __int32 (*)(Blam::Network::Observer const *, unsigned __int32, Blam::Network::ObserverChannel const *)
			// function call : __int32 (*)(Blam::Network::SessionMembership const *, __int32)

			// Look up the channel index
			typedef int(__thiscall *GetChannelIndexPtr)(const Network::Observer *thisPtr, uint32_t unk0, const ObserverChannel *channel);
			auto GetChannelIndex = reinterpret_cast<GetChannelIndexPtr>(0x447150);
			auto index = GetChannelIndex(Observer, Unknown10, channel);
			if (index < 0)
				return index;

			// Use the channel index to look up the peer
			typedef int(__thiscall *GetChannelPeerPtr)(const SessionMembership *thisPtr, int channelIndex);
			auto GetChannelPeer = reinterpret_cast<GetChannelPeerPtr>(0x44E860);
			return GetChannelPeer(&MembershipInfo, index);
		}

		bool Session::HasTeams() const // 0x1092C330
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasTeams@Session@Network@Blam@@QBE_NXZ");
			// Blam::Network::Session const *const this;
			// Blam::Network::GameVariantSessionParameter const *gameVariantParameter;
			// c_game_variant *gameVariant;


			Blam::Network::GameVariantSessionParameter const *gameVariantParameter = &Parameters.GameVariant;
			if (!gameVariantParameter->IsAvailable())
				return false;
			c_game_variant *gameVariant = gameVariantParameter->Get();
			if (!gameVariant)
				return false;
			return gameVariant->get_base_variant()->miscellaneous_options.teams_enabled();
		}

		Blam::Network::NetworkAddress Session::GetPeerAddress(__int32 peerIndex) const // 0x1092BFD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPeerAddress@Session@Network@Blam@@QBE?AUNetworkAddress@23@H@Z");
			// __int32 peerIndex;
				// __int32 channelIndex;

			if (peerIndex != MembershipInfo.LocalPeerIndex)
			{
				auto channelIndex = MembershipInfo.PeerChannels[peerIndex].ChannelIndex;
				if (channelIndex >= 0)
					return Observer->Channels[channelIndex].Address;
			}
			return NetworkAddress::FromInAddr(0x0100007F, 11774);
		}

		Blam::Network::NetworkAddress Session::GetServerIPAddress() const // 0x1092C240
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetServerIPAddress@Session@Network@Blam@@QBE?AUNetworkAddress@23@XZ");
			// Blam::Network::Session const *const this;

			return Observer->Channels[MembershipInfo.PeerChannels[MembershipInfo.HostPeerIndex].ChannelIndex].Address;
		}

		__int32 SessionParameters::GetSessionMode() // 0x1092C2C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetSessionMode@SessionParameters@Network@Blam@@QAEHXZ");
			// Blam::Network::SessionParameters *const this;
			// __int32 (*GetSessionMode)(Blam::Network::SessionParameters *);
			// function call : __int32 (*)(Blam::Network::SessionParameters *)

			__int32 (__thiscall *F)(Blam::Network::SessionParameters *) = (__int32(__thiscall *)(Blam::Network::SessionParameters *))0x458FE0;

			return F(this);
		}

		bool SessionParameters::SetSessionMode(__int32 mode) // 0x1092CCC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetSessionMode@SessionParameters@Network@Blam@@QAE_NH@Z");
			// __int32 mode;
			// bool (*SetSessionMode)(Blam::Network::SessionParameters *, __int32);
			// function call : bool (*)(Blam::Network::SessionParameters *, __int32)

			bool (__thiscall *SetSessionModeImpl)(SessionParameters *, __int32) = (bool(__thiscall *)(SessionParameters *, __int32))0x459a40;

			return SetSessionModeImpl(this, mode);
		}

		bool SessionParameter::IsAvailable() const // 0x1092C3D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsAvailable@SessionParameter@Network@Blam@@QBE_NXZ");
			// Blam::Network::SessionParameter const *const this;
			// bool (*IsAvailable)(Blam::Network::SessionParameter const *);
			// function call : bool (*)(Blam::Network::SessionParameter const *)

			bool (__thiscall *IsAvailableImpl)(const SessionParameter *) = (bool(__thiscall *)(const SessionParameter *))0x450cf0;

			return IsAvailableImpl(this);
		}
	}
}


namespace Blam
{
	namespace Network
	{
		c_game_variant *GameVariantSessionParameter::Get() const // 0x1092BA30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Get@GameVariantSessionParameter@Network@Blam@@QBEPAUc_game_variant@@XZ");
			// Blam::Network::GameVariantSessionParameter const *const this;
			// c_game_variant *(*GetGameVariant)(Blam::Network::GameVariantSessionParameter const *);
			// function call : c_game_variant *(*)(Blam::Network::GameVariantSessionParameter const *)

			c_game_variant *(__thiscall *F)(Blam::Network::GameVariantSessionParameter const *) = (c_game_variant *(__thiscall *)(Blam::Network::GameVariantSessionParameter const *))0x456140;

			return F(this);
		}
	}
}


namespace Blam
{
	namespace Network
	{
		s_map_variant *MapVariantSessionParameter::Get() const // 0x1092BAA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Get@MapVariantSessionParameter@Network@Blam@@QBEPAUs_map_variant@@XZ");
			// Blam::Network::MapVariantSessionParameter const *const this;
			// s_map_variant *(*GetMapVariant)(Blam::Network::MapVariantSessionParameter const *);
			// function call : s_map_variant *(*)(Blam::Network::MapVariantSessionParameter const *)

			s_map_variant *(__thiscall *MapVariantGet)(const MapVariantSessionParameter *) = (s_map_variant *(__thiscall *)(const MapVariantSessionParameter *))0x456410;

			return MapVariantGet(this);
		}

		Blam::Network::PacketTable *GetPacketTable() // 0x1092BEC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPacketTable@Network@Blam@@YAPAUPacketTable@12@XZ");
			// procedure flags: nofpo
			// static ...; // 0x1092BF80
			// static ...; // 0x1092BF74
			// static ...; // 0x1092BF6C
			// Pointer packetTablePtr;


			Pointer packetTablePtr = Pointer::Base(0x1E4A498, 1);
			return packetTablePtr.Read<Blam::Network::PacketTable *>();
		}

		void SetPacketTable(Blam::Network::PacketTable const *newTable) // 0x1092CBC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetPacketTable@Network@Blam@@YAXPBUPacketTable@12@@Z");
			// static ...; // 0x1092CC74
			// static ...; // 0x1092CC68
			// static ...; // 0x1092CC60
			// Blam::Network::PacketTable const *newTable;
			// Pointer packetTablePtr;

			Pointer packetTablePtr = Pointer::Base(0x1E4A498, 1);
			packetTablePtr.Write<Blam::Network::PacketTable const *>(newTable);
		}

		void PacketTable::Register(__int32 index, char const *name, __int32 unk8, __int32 minSize, __int32 maxSize, void (*serializeFunc)(Blam::BitStream *, __int32, void const *), bool (*deserializeFunc)(Blam::BitStream *, __int32, void *), __int32 unk1C, __int32 unk20) // 0x1092C980
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Register@PacketTable@Network@Blam@@QAEXHPBDHHHP6AXPAVBitStream@3@HPBX@ZP6A_N1HPAX@ZHH@Z");
			// __int32 unk20;
			// void (*RegisterPacket)(Blam::Network::PacketTable *, __int32, char const *, __int32, __int32, __int32, void (*)(Blam::BitStream *, __int32, void const *), bool (*)(Blam::BitStream *, __int32, void *), __int32, __int32);
			// function call : void (*)(Blam::Network::PacketTable *, __int32, char const *, __int32, __int32, __int32, void (*)(Blam::BitStream *, __int32, void const *), bool (*)(Blam::BitStream *, __int32, void *), __int32, __int32)

			void (__thiscall *RegisterImpl)(Blam::Network::PacketTable *, __int32, char const *, __int32, __int32, __int32, void (*)(Blam::BitStream *, __int32, void const *), bool (*)(Blam::BitStream *, __int32, void *), __int32, __int32) = (void(__thiscall *)(Blam::Network::PacketTable *, __int32, char const *, __int32, __int32, __int32, void (*)(Blam::BitStream *, __int32, void const *), bool (*)(Blam::BitStream *, __int32, void *), __int32, __int32))0x4801b0;

			RegisterImpl(this, index, name, unk8, minSize, maxSize, serializeFunc, deserializeFunc, unk1C, unk20);
		}

		bool MessageGateway::SendDirectedMessage(Blam::Network::NetworkAddress const &address, __int32 id, __int32 packetSize, void const *packet) // 0x1092CA20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendDirectedMessage@MessageGateway@Network@Blam@@QAE_NABUNetworkAddress@23@HHPBX@Z");
			// void const *packet;
			// bool (*SendDirectedMessage)(Blam::Network::MessageGateway *, Blam::Network::NetworkAddress const &, __int32, __int32, void const *);
			// function call : bool (*)(Blam::Network::MessageGateway *, Blam::Network::NetworkAddress const &, __int32, __int32, void const *)

			bool (__thiscall *Impl)(Blam::Network::MessageGateway *, Blam::Network::NetworkAddress const *, __int32, __int32, void const *) = (bool(__thiscall *)(Blam::Network::MessageGateway *, Blam::Network::NetworkAddress const *, __int32, __int32, void const *))0x4840c0;

			return Impl(this, &address, id, packetSize, packet);
		}

		bool MessageGateway::Ping(Blam::Network::NetworkAddress &address, unsigned short id) // 0x1092C750
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Ping@MessageGateway@Network@Blam@@QAE_NAAUNetworkAddress@23@G@Z");
			// static ...; // 0x1092C808
			// Blam::Network::MessageGateway *const this;
			// Blam::Network::NetworkAddress &address;
			// unsigned short id;
			// Blam::Network::PingPacket packet;

			auto packet = MakePingPacket(id);
			return SendDirectedMessage(address, ePacketIDPing, sizeof(packet), &packet);
		}

		__int32 GetNumPlayers() // 0x1092BE50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetNumPlayers@Network@Blam@@YAHXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished())
				return session->MembershipInfo.PlayerCount;
			return 0;
		}

		bool BootPlayer(__int32 playerIndex, __int32 reason) // 0x1092B450
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BootPlayer@Network@Blam@@YA_NHH@Z");
			// __int32 reason;
			// bool (*Network_squad_session_boot_player)(__int32, __int32);
			// function call : bool (*)(__int32, __int32)

			bool (__cdecl *Boot)(__int32, __int32) = (bool(__cdecl *)(__int32, __int32))0x437d60;

			return Boot(playerIndex, reason);
		}

		bool EndGame() // 0x1092B520
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?EndGame@Network@Blam@@YA_NXZ");
			// procedure flags: nofpo
			// bool (*Network_squad_session_end_game)();
			// function call : bool (*)()

			bool (__cdecl *Network_squad_session_end_game)() = (bool(__cdecl *)())0x438780;

			return Network_squad_session_end_game();
		}

		__int32 GetLobbyType() // 0x1092BCF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetLobbyType@Network@Blam@@YAHXZ");
			// procedure flags: nofpo
			// __int32 (*Get_Type)();
			// function call : __int32 (*)()

			__int32 (__cdecl *Get_Type)() = (__int32(__cdecl *)())0x435640;

			return Get_Type();
		}

		__int32 GetNetworkMode() // 0x1092BDF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetNetworkMode@Network@Blam@@YAHXZ");
			// procedure flags: nofpo
			// __int32 (*Get_Mode)();
			// function call : __int32 (*)()

			__int32 (__cdecl *Get_Mode)() = (__int32(__cdecl *)())0xa7f160;

			return Get_Mode();
		}

		bool SetLobbyType(__int32 type) // 0x1092CAB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetLobbyType@Network@Blam@@YA_NH@Z");
			// __int32 type;
			// bool (*set_server_lobby_type)(__int32);
			// function call : bool (*)(__int32)

			bool (__cdecl *F)(int) = (bool(__cdecl *)(int))0xa7ee70;

			return F(type);
		}

		bool SetNetworkMode(__int32 mode) // 0x1092CB20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetNetworkMode@Network@Blam@@YA_NH@Z");
			// __int32 mode;
			// bool (*Set_Network_Mode)(__int32);
			// bool success;
			// function call : bool (*)(__int32)

			bool (*Set_Network_Mode)(__int32) = reinterpret_cast<bool (*)(__int32)>(0xA7F950);
			bool success = Set_Network_Mode(mode);
			Utils::Singleton<Discord::DiscordRPC>::Instance().UpdatePresence(mode);
			return success;
		}

		bool Disconnect() // 0x1092B4C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Disconnect@Network@Blam@@YA_NXZ");
			// procedure flags: nofpo
			// bool (*Network_network_life_cycle_end)();
			// function call : bool (*)()

			bool (__cdecl *Network_network_life_cycle_end)() = (bool(__cdecl *)())0x454b40;

			return Network_network_life_cycle_end();
		}

		void LeaveGame() // 0x1092C440
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LeaveGame@Network@Blam@@YAXXZ");
			// procedure flags: nofpo
			// void (*Network_LeaveGame)();
			// function call : void (*)()

			void (__cdecl *Network_LeaveGame)() = (void(__cdecl *)())0xa81270;

			Network_LeaveGame();
		}

		bool NetworkAddress::Parse(std::string const &addr, unsigned short port, Blam::Network::NetworkAddress *result) // 0x1092C600
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Parse@NetworkAddress@Network@Blam@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@GPAU123@@Z");
			// static ...; // 0x1092C6F0
			// std::string const &addr;
			// unsigned short port;
			// Blam::Network::NetworkAddress *result;
			// in_addr inAddr;
			// function call : __int32 (__int32, char const *, void *)

			in_addr inAddr;
			if (!inet_pton(AF_INET, addr.c_str(), &inAddr))
				return false;
			*result = FromInAddr(inAddr.s_addr, port);
			return true;
		}
	}
}


namespace Blam
{
	namespace Network
	{
		std::string NetworkAddress::ToString() const // 0x1092CDA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ToString@NetworkAddress@Network@Blam@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// static ...; // 0x1092CE8A
			// static ...; // 0x1092CE84
			// static ...; // 0x1092CE6C
			// static ...; // 0x1092CE64
			// Blam::Network::NetworkAddress const *const this;
			// char ipStr[22];
			// in_addr inAddr;

			in_addr inAddr;
			inAddr.s_addr = ToInAddr();
			char ipStr[22];
			if (!inet_ntop(AF_INET, &inAddr, ipStr, sizeof(ipStr)))
				return "";
			return ipStr;
		}
	}
}

/* ---------- private code */

Blam::Network::PingPacket MakePingPacket(unsigned short id) // 0x1092C4A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MakePingPacket@@YA?AUPingPacket@Network@Blam@@G@Z");
	// `anonymous-namespace'::MakePingPacket
	// static ...; // 0x1092C534
	// static ...; // 0x1092C528
	// static ...; // 0x1092C520
	// unsigned short id;
	// Blam::Network::PingPacket packet;


	Blam::Network::PingPacket packet;
	packet.ID = id;
	packet.QosResponse = false;
	packet.Timestamp = system_milliseconds();
	return packet;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum c_game_engine_miscellaneous_options::e_flags,unsigned char>::test(c_game_engine_miscellaneous_options::e_flags) const;
template void Pointer::Write<Blam::Network::PacketTable const *>(Blam::Network::PacketTable const *const) const;

/* ---------- explicit instantiations */
template Blam::Network::PacketTable * & Pointer::Read<Blam::Network::PacketTable *>() const;
template Blam::Network::Session * & Pointer::Read<Blam::Network::Session *>() const;
