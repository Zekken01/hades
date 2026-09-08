#ifndef __PATCHES_CUSTOMPACKETS_HPP__
#define __PATCHES_CUSTOMPACKETS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

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
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Patches
{
	namespace CustomPackets
	{
		_extern void _sub_10AFF8B0(Patches::CustomPackets::RawPacketHandler *const);
		_inline RawPacketHandler::~RawPacketHandler() // 0x10AFF8B0
		{
			mangled_x86(MANGLED_TODO, "??1RawPacketHandler@CustomPackets@Patches@@UAE@XZ");
			// Patches::CustomPackets::RawPacketHandler *const this;
			todo("implement");
			_sub_10AFF8B0(this);
		}

		extern PacketBase* _sub_10AFF1F0(Patches::CustomPackets::PacketBase *const, unsigned __int32);
		_inline PacketBase::PacketBase(unsigned __int32 guid) // 0x10AFF1F0
		{
			mangled_x86(MANGLED_TODO, "??0PacketBase@CustomPackets@Patches@@QAE@I@Z");
			// unsigned __int32 guid;
			todo("implement");
			_sub_10AFF1F0(this, guid);
		}
	}
}

/* ---------- private code */

#endif // __PATCHES_CUSTOMPACKETS_HPP__
