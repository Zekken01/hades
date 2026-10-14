#ifndef __PATCHES_CUSTOMPACKETS_HPP__
#define __PATCHES_CUSTOMPACKETS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"
#include "Blam/BlamNetwork.hpp"  // hades: added for 0x10AFF1F0

#include "Patches/Audio.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct lambda_1;

/* ---------- constants */

/* ---------- definitions */

// Patches::CustomPackets::RawPacketHandler is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// Patches::CustomPackets::PacketBase is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar>::Allocate::__l2::<lambda_1>
//{
//public:
//	void operator()(Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar> *) const;
//};
//static_assert(sizeof(Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar>::Allocate::__l2::<lambda_1>) == 1, "Invalid Patches::CustomPackets::VariadicPacket<SyncUpdatePacketData,SyncUpdatePacketVar>::Allocate::__l2::<lambda_1> size");

namespace hades_file_local
{

}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace CustomPackets
	{
		extern void ApplyAll();
		extern void SendPacket(__int32 targetPeer, void const *packet, __int32 packetSize);
		extern unsigned __int32 RegisterPacketImpl(std::string const &name, std::shared_ptr<Patches::CustomPackets::RawPacketHandler> handler);

		// hades: the two register templates, from the 0.6.1 header
		template<typename TPacket>
		std::shared_ptr<PacketSender<TPacket> > RegisterPacket(std::string const &name, std::shared_ptr<PacketHandler<TPacket> > handler)
		{
			auto id = RegisterPacketImpl(name, handler);
			return std::make_shared<PacketSender<TPacket> >(id);
		}

		template<typename TData, typename TVarData>
		std::shared_ptr<VariadicPacketSender<TData, TVarData> > RegisterVariadicPacket(std::string const &name, std::shared_ptr<VariadicPacketHandler<TData, TVarData> > handler)
		{
			auto id = RegisterPacketImpl(name, handler);
			return std::make_shared<VariadicPacketSender<TData, TVarData> >(id);
		}
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Patches
{
	namespace CustomPackets
	{
		inline RawPacketHandler::~RawPacketHandler() // 0x10AFF8B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1RawPacketHandler@CustomPackets@Patches@@UAE@XZ");
			// Patches::CustomPackets::RawPacketHandler *const this;
		}

		inline PacketBase::PacketBase(unsigned __int32 guid) // 0x10AFF1F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0PacketBase@CustomPackets@Patches@@QAE@I@Z");
			// unsigned __int32 guid;

			reinterpret_cast<Blam::Network::PacketHeader *>(Header)->PacketHeader::PacketHeader();
			TypeGuid = guid;
		}
	}
}

/* ---------- private code */

#endif // __PATCHES_CUSTOMPACKETS_HPP__
