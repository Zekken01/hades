#ifndef __PATCHES_NETWORK_HPP__
#define __PATCHES_NETWORK_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/map_variant_loader.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"

#include <functional>
#include <memory>

/* ---------- forward declarations */

struct s_map_variant;
namespace Blam
{
	namespace Network
	{
		struct NetworkAddress;
	}
}
namespace Patches
{
	namespace Network
	{
		class NetworkSessionListener;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Patches
{
	namespace Network
	{
		class NetworkSessionListener
		{
		public:
			virtual _inline ~NetworkSessionListener();
			virtual void SessionCreated() = 0;
			virtual void SessionDestroyed() = 0;
			virtual void PeerAdded(__int32) = 0;
			virtual void PeerRemoved(__int32) = 0;
			virtual void PlayerAdded(__int32) = 0;
			virtual void PlayerRemoved(__int32) = 0;
			NetworkSessionListener(Patches::Network::NetworkSessionListener const &); /* compiler_generated() */
			_inline NetworkSessionListener(); /* compiler_generated() */
			Patches::Network::NetworkSessionListener &operator=(Patches::Network::NetworkSessionListener const &); /* compiler_generated() */
		};
		static_assert(sizeof(Patches::Network::NetworkSessionListener) == 4, "Invalid Patches::Network::NetworkSessionListener size");
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

/* ---------- globals */

/* ---------- public code */

namespace Patches
{
	namespace Network
	{
		_inline NetworkSessionListener::~NetworkSessionListener() // 0x10AFF880
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1NetworkSessionListener@Network@Patches@@UAE@XZ");
			// Patches::Network::NetworkSessionListener *const this;
		}
	}
}

/* ---------- private code */

#endif // __PATCHES_NETWORK_HPP__
