#ifndef __BLAM_BLAMNETWORK_HPP__
#define __BLAM_BLAMNETWORK_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Forge/Magnets.hpp"
#include "ThirdParty/rapidjson/rapidjson.h"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct c_game_variant;
struct s_map_variant;
struct s_player_configuration;
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
		struct PeerChannel;
		struct PeerInfo;
		struct PingPacket;
		struct PlayerSession;
		struct PongPacket;
		struct RegisteredPacket;
		struct Session;
		struct SessionMembership;
		struct SessionParameter;
		struct SessionParameters;
	}
}

/* ---------- constants */

namespace Blam
{
	namespace Network
	{
		enum PeerConnectionState
		{
			ePeerConnectionStateNone = 0,
			ePeerConnectionStateRejoining,
			ePeerConnectionStateReserved,
			ePeerConnectionStateDisconnected,
			ePeerConnectionStateConnected,
			ePeerConnectionStateJoining,
			ePeerConnectionStateJoined,
			ePeerConnectionStateWaiting,
			ePeerConnectionStateEstablished,
		};

		enum PacketID
		{
			ePacketIDPing = 0,
			ePacketIDPong,
		};

		enum LifeCycleState
		{
			eLifeCycleStateNone = 0,
			eLifeCycleStatePreGame,
			eLifeCycleStateStartGame,
			eLifeCycleStateInGame,
			eLifeCycleStateEndGameWriteStats,
			eLifeCycleStateLeaving,
			eLifeCycleStateJoining,
			eLifeCycleStateMatchmakingStart,
			eLifeCycleStateMatchmakingFindMatchClient,
			eLifeCycleStateMatchmakingFindMatch,
			eLifeCycleStateMatchmakingFindAndAssembleMatch,
			eLifeCycleStateMatchmakingAssembleMatch,
			eLifeCycleStateMatchmakingArbitration,
			eLifeCycleStateMatchmakingSelectHost,
			eLifeCycleStateMatchmakingPrepareMap,
			eLifeCycleStateInMatch,
			eLifeCycleStateEndMatchWriteStats,
			eLifeCycleStatePostMatch,
		};
	}
}

/* ---------- definitions */

namespace Blam
{
	namespace Network
	{
		struct PeerInfo
		{
			unsigned char Unknown0[16]; // 0x0
			Blam::Network::PeerConnectionState ConnectionState; // 0x10
			__int32 Unknown14; // 0x14
			unsigned __int32 StartTime; // 0x18
			unsigned char Unknown1C[212]; // 0x1C
			unsigned __int32 PlayerMasks[2]; // 0xF0
			bool IsConnected() const;
			_inline bool IsEstablished() const;
			bool OwnsPlayer(__int32) const;
		};
		static_assert(sizeof(Blam::Network::PeerInfo) == 248, "Invalid Blam::Network::PeerInfo size");

		struct PeerChannel
		{
			bool Unavailable; // 0x0
			unsigned char __pad0[3]; // 0x1
			__int32 ChannelIndex; // 0x4
			__int32 Unknown8; // 0x8
		};
		static_assert(sizeof(Blam::Network::PeerChannel) == 12, "Invalid Blam::Network::PeerChannel size");

		struct PlayerSession
		{
			unsigned __int32 Unknown0; // 0x0
			unsigned __int32 Unknown4; // 0x4
			unsigned __int32 Unknown8; // 0x8
			__int32 PeerIndex; // 0xC
			unsigned __int32 Unknown10; // 0x10
			unsigned __int32 Unknown14; // 0x14
			unsigned __int32 Unknown18; // 0x18
			unsigned __int32 Unknown1C; // 0x1C
			s_player_configuration Properties; // 0x20
			unsigned __int32 Unknown1640; // 0x1640
			unsigned __int32 Unknown1644; // 0x1644
			PlayerSession(); /* compiler_generated() */
		};
		static_assert(sizeof(Blam::Network::PlayerSession) == 5704, "Invalid Blam::Network::PlayerSession size");

		struct SessionMembership
		{
			__int32 Unknown0; // 0x0
			__int32 Unknown4; // 0x4
			__int32 PlayerUpdateCount; // 0x8
			__int32 LeaderPeerIndex; // 0xC
			__int32 HostPeerIndex; // 0x10
			__int32 Unknown14; // 0x14
			__int32 SessionMaxPlayers; // 0x18
			__int32 Unknown1C; // 0x1C
			__int32 Unknown20; // 0x20
			unsigned long ActivePeerMask; // 0x24
			Blam::Network::PeerInfo Peers[17]; // 0x28
			unsigned __int32 PlayerCount; // 0x10A0
			unsigned __int32 ActivePlayerMask; // 0x10A4
			Blam::Network::PlayerSession PlayerSessions[16]; // 0x10A8
			unsigned char Unknown17528[1624056]; // 0x17528
			__int32 LocalPeerIndex; // 0x1A3D20
			__int32 PeerUpdateCount; // 0x1A3D24
			Blam::Network::PeerChannel PeerChannels[17]; // 0x1A3D28
			unsigned char Unknown1A3DF8[300]; // 0x1A3DF4
			__int32 FindFirstPeer() const;
			__int32 FindNextPeer(__int32 lastPeer) const;
			__int32 FindFirstPlayer() const;
			__int32 FindNextPlayer(__int32 lastPlayer) const;
			__int32 GetPeerPlayer(__int32 peer) const;
			__int32 GetPlayerPeer(__int32 player) const;
			__int32 GetPeerTeam(__int32 peer) const;
			__int32 FindPlayerByName(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name);
			Blam::Network::PlayerSession GetLocalPlayerSession() const;
			void Update();
			SessionMembership(); /* compiler_generated() */
		};
		static_assert(sizeof(Blam::Network::SessionMembership) == 1720096, "Invalid Blam::Network::SessionMembership size");

		struct SessionParameter
		{
			bool IsAvailable() const;
		};
		static_assert(sizeof(Blam::Network::SessionParameter) == 1, "Invalid Blam::Network::SessionParameter size");

		struct GameVariantSessionParameter :
			public Blam::Network::SessionParameter
		{
			unsigned char Unknown0[13680]; // 0x0
			c_game_variant *Get() const;
		};
		static_assert(sizeof(Blam::Network::GameVariantSessionParameter) == 13680, "Invalid Blam::Network::GameVariantSessionParameter size");

		struct MapVariantSessionParameter :
			public Blam::Network::SessionParameter
		{
			unsigned char Unknown0[280]; // 0x0
			__int32 MapID; // 0x118
			unsigned char Unknown1[172212]; // 0x11C
			s_map_variant *Get() const;
		};
		static_assert(sizeof(Blam::Network::MapVariantSessionParameter) == 172496, "Invalid Blam::Network::MapVariantSessionParameter size");
	}
}

#pragma pack(push, 4)
namespace Blam
{
	namespace Network
	{
		struct SessionParameters
		{
			unsigned char Unknown0[185048]; // 0x0
			Blam::Network::GameVariantSessionParameter GameVariant; // 0x2D2D8
			Blam::Network::MapVariantSessionParameter MapVariant; // 0x30848
			unsigned char Unknown30848[380684]; // 0x5AA18
			__int32 GetSessionMode();
			bool SetSessionMode(__int32 mode);
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Blam::Network::SessionParameters) == 751908, "Invalid Blam::Network::SessionParameters size");

namespace Blam
{
	namespace Network
	{
		struct NetworkAddress
		{
			public:
			union s_Address
			{
				unsigned __int32 IPv4; // 0x0
				unsigned char Data[16]; // 0x0
			};
			// static_assert(sizeof(s_Address) == 16, "Invalid s_Address size");
			// Withheld: the type inventory does not describe this type, so its
			// padding could not be reconstructed.
			public:
			union
			{
				unsigned __int32 IPv4; // 0x0
				unsigned char Data[16]; // 0x0
			} Address; // 0x0
			unsigned short Port; // 0x10
			unsigned short AddressSize; // 0x12
			static _inline Blam::Network::NetworkAddress FromInAddr(unsigned long address, unsigned short port);
			_inline unsigned long ToInAddr() const;
			static bool Parse(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &addr, unsigned short port, Blam::Network::NetworkAddress *result);
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > ToString() const;
		};
	}
}

// static_assert(sizeof(Blam::Network::NetworkAddress) == 20, "Invalid Blam::Network::NetworkAddress size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace Blam
{
	namespace Network
	{
		struct ObserverChannel
		{
			unsigned char Unknown0[2772]; // 0x0
			Blam::Network::NetworkAddress Address; // 0xAD4
			unsigned char UnknownAE8[1520]; // 0xAE8
		};
	}
}

// static_assert(sizeof(Blam::Network::ObserverChannel) == 4312, "Invalid Blam::Network::ObserverChannel size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace Blam
{
	namespace Network
	{
		struct PacketHeader
		{
			PacketHeader();
			unsigned char XnkAddr[16]; // 0x0
		};
	}
}

// static_assert(sizeof(Blam::Network::PacketHeader) == 16, "Invalid Blam::Network::PacketHeader size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace Blam
{
	namespace Network
	{
		struct RegisteredPacket
		{
			bool Initialized; // 0x0
			unsigned char __pad0[3]; // 0x1
			char const *Name; // 0x4
			__int32 Unknown8; // 0x8
			__int32 MinSize; // 0xC
			__int32 MaxSize; // 0x10
			void (*Serialize)(Blam::BitStream *, __int32, void const *); // 0x14
			bool (*Deserialize)(Blam::BitStream *, __int32, void *); // 0x18
			__int32 Unknown1C; // 0x1C
			__int32 Unknown20; // 0x20
		};
	}
}

// static_assert(sizeof(Blam::Network::RegisteredPacket) == 36, "Invalid Blam::Network::RegisteredPacket size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

#pragma pack(push, 4)
namespace Blam
{
	namespace Network
	{
		struct PacketTable
		{
			Blam::Network::RegisteredPacket Packets[1]; // 0x0
			void Register(__int32 index, char const *name, __int32 unk8, __int32 minSize, __int32 maxSize, void (*serializeFunc)(Blam::BitStream *, __int32, void const *), bool (*deserializeFunc)(Blam::BitStream *, __int32, void *), __int32 unk1C, __int32 unk20);
		};
	}
}

#pragma pack(pop)
// static_assert(sizeof(Blam::Network::PacketTable) == 36, "Invalid Blam::Network::PacketTable size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace Blam
{
	namespace Network
	{
		struct PingPacket
		{
			unsigned short ID; // 0x0
			unsigned char __pad0[2]; // 0x2
			unsigned __int32 Timestamp; // 0x4
			bool QosResponse; // 0x8
			unsigned char __pad1[3]; // 0x9
		};
		static_assert(sizeof(Blam::Network::PingPacket) == 12, "Invalid Blam::Network::PingPacket size");

		struct PongPacket
		{
			unsigned short ID; // 0x0
			unsigned char __pad0[2]; // 0x2
			unsigned __int32 Timestamp; // 0x4
			__int32 Unknown8; // 0x8
		};
		static_assert(sizeof(Blam::Network::PongPacket) == 12, "Invalid Blam::Network::PongPacket size");

		struct Observer
		{
			Blam::Network::ObserverChannel Channels[34]; // 0x0
			unsigned char Unknown0[624]; // 0x23CB0
			void ObserverChannelSendMessage(__int32 ownerIndex, __int32 channelIndex, bool secure, __int32 id, __int32 packetSize, void const *packet);
			void Ping(__int32 ownerIndex, __int32 channelIndex, unsigned short id);
		};
		static_assert(sizeof(Blam::Network::Observer) == 147232, "Invalid Blam::Network::Observer size");

		struct MessageGateway
		{
			unsigned char Unknown0[1672]; // 0x0
			bool SendDirectedMessage(Blam::Network::NetworkAddress const &address, __int32 id, __int32 packetSize, void const *packet);
			bool Ping(Blam::Network::NetworkAddress &address, unsigned short id);
		};
		static_assert(sizeof(Blam::Network::MessageGateway) == 1672, "Invalid Blam::Network::MessageGateway size");

		struct Session
		{
			unsigned __int32 Unknown0; // 0x0
			Blam::Network::MessageGateway *Gateway; // 0x4
			Blam::Network::Observer *Observer; // 0x8
			unsigned __int32 UnknownC; // 0xC
			unsigned __int32 Unknown10; // 0x10
			unsigned __int32 Unknown14; // 0x14
			unsigned __int32 Unknown18; // 0x18
			unsigned __int32 Unknown1C; // 0x1C
			Blam::Network::SessionMembership MembershipInfo; // 0x20
			Blam::Network::SessionParameters Parameters; // 0x1A3F40
			__int32 Unknown25B864; // 0x25B864
			__int32 Unknown25B868; // 0x25B868
			__int32 Unknown25B86C; // 0x25B86C
			__int32 Type; // 0x25B870
			unsigned char Unknown25B874[892]; // 0x25B874
			__int32 AddressIndex; // 0x25BBF0
			unsigned char Unknown25BBF4[76]; // 0x25BBF4
			__int32 GetChannelPeer(Blam::Network::ObserverChannel const *channel) const;
			_inline bool IsEstablished() const;
			_inline bool IsHost() const;
			bool HasTeams() const;
			Blam::Network::NetworkAddress GetPeerAddress(__int32 peerIndex) const;
			Blam::Network::NetworkAddress GetServerIPAddress() const;
			Session(); /* compiler_generated() */
		};
		static_assert(sizeof(Blam::Network::Session) == 2473024, "Invalid Blam::Network::Session size");
	}
}

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

/* ---------- globals */

/* ---------- public code */

namespace Blam
{
	namespace Network
	{
		_extern bool _sub_1092FC00(Blam::Network::PeerInfo const *const);
		_inline bool PeerInfo::IsEstablished() const // 0x1092FC00
		{
			mangled_x86(MANGLED_TODO, "?IsEstablished@PeerInfo@Network@Blam@@QBE_NXZ");
			// Blam::Network::PeerInfo const *const this;
			todo("implement");
			bool __result = _sub_1092FC00((Blam::Network::PeerInfo const *)this);
			return __result;
		}

		extern NetworkAddress _sub_1092B950(unsigned long, unsigned short);
		_inline Blam::Network::NetworkAddress NetworkAddress::FromInAddr(unsigned long address, unsigned short port) // 0x1092B950
		{
			mangled_x86(MANGLED_TODO, "?FromInAddr@NetworkAddress@Network@Blam@@SA?AU123@KG@Z");
			// static ...; // 0x1092B9F0
			// static ...; // 0x1092B9E8
			// unsigned long address;
			// unsigned short port;
			// Blam::Network::NetworkAddress result;
			todo("implement");
			Blam::Network::NetworkAddress __result = _sub_1092B950(address, port);
			return __result;
		}

		_extern unsigned long _sub_1092CD40(Blam::Network::NetworkAddress const *const);
		_inline unsigned long NetworkAddress::ToInAddr() const // 0x1092CD40
		{
			mangled_x86(MANGLED_TODO, "?ToInAddr@NetworkAddress@Network@Blam@@QBEKXZ");
			// Blam::Network::NetworkAddress const *const this;
			todo("implement");
			unsigned long __result = _sub_1092CD40((Blam::Network::NetworkAddress const *)this);
			return __result;
		}

		_extern bool _sub_106CFA00(Blam::Network::Session const *const);
		_inline bool Session::IsEstablished() const // 0x106CFA00
		{
			mangled_x86(MANGLED_TODO, "?IsEstablished@Session@Network@Blam@@QBE_NXZ");
			// Blam::Network::Session const *const this;
			todo("implement");
			bool __result = _sub_106CFA00((Blam::Network::Session const *)this);
			return __result;
		}

		_extern bool _sub_106CFA50(Blam::Network::Session const *const);
		_inline bool Session::IsHost() const // 0x106CFA50
		{
			mangled_x86(MANGLED_TODO, "?IsHost@Session@Network@Blam@@QBE_NXZ");
			// Blam::Network::Session const *const this;
			todo("implement");
			bool __result = _sub_106CFA50((Blam::Network::Session const *)this);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __BLAM_BLAMNETWORK_HPP__
