#ifndef __SERVER_CLIENTDATATRACKER_HPP__
#define __SERVER_CLIENTDATATRACKER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/Network.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Patches
{
	namespace Network
	{
		class NetworkSessionListener;
	}
}
namespace Server
{
	namespace ClientDataTracker
	{
		class ClientInfoDataHandler;
		class MyNetworkSessionListener;
		struct ClientInfoData;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Server
{
	namespace ClientDataTracker
	{
		struct ClientInfoData
		{
			ClientInfoData(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body);
			_inline ClientInfoData();
			char Body[4096]; // 0x0
		};
		static_assert(sizeof(Server::ClientDataTracker::ClientInfoData) == 4096, "Invalid Server::ClientDataTracker::ClientInfoData size");

		class ClientInfoDataHandler
		{
		public:
			virtual ~ClientInfoDataHandler();
			virtual void MessageReceived(Server::ClientDataTracker::ClientInfoData const &) = 0;
			ClientInfoDataHandler(Server::ClientDataTracker::ClientInfoDataHandler const &); /* compiler_generated() */
			ClientInfoDataHandler(); /* compiler_generated() */
			Server::ClientDataTracker::ClientInfoDataHandler &operator=(Server::ClientDataTracker::ClientInfoDataHandler const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::ClientDataTracker::ClientInfoDataHandler) == 4, "Invalid Server::ClientDataTracker::ClientInfoDataHandler size");

		class MyNetworkSessionListener :
			public Patches::Network::NetworkSessionListener
		{
		public:
			MyNetworkSessionListener(Server::ClientDataTracker::MyNetworkSessionListener &); /* compiler_generated() */
			MyNetworkSessionListener(Server::ClientDataTracker::MyNetworkSessionListener const &); /* compiler_generated() */
			_inline MyNetworkSessionListener();
			virtual void SessionCreated();
			virtual void SessionDestroyed();
			virtual void PeerAdded(__int32 peerIndex);
			virtual void PeerRemoved(__int32 peerIndex);
			virtual void PlayerAdded(__int32 playerIndex);
			virtual void PlayerRemoved(__int32 playerIndex);
			virtual _inline ~MyNetworkSessionListener(); /* compiler_generated() */
			Server::ClientDataTracker::MyNetworkSessionListener &operator=(Server::ClientDataTracker::MyNetworkSessionListener &); /* compiler_generated() */
			Server::ClientDataTracker::MyNetworkSessionListener &operator=(Server::ClientDataTracker::MyNetworkSessionListener const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::ClientDataTracker::MyNetworkSessionListener) == 4, "Invalid Server::ClientDataTracker::MyNetworkSessionListener size");
	}
}

/* ---------- prototypes */

namespace Server
{
	namespace ClientDataTracker
	{
		extern void Tick();
		extern void Initialize();
		extern bool BroadcastClientInfoData(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &body);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	namespace ClientDataTracker
	{
		extern ClientInfoData* _sub_10AFF0E0(Server::ClientDataTracker::ClientInfoData *const);
		_inline ClientInfoData::ClientInfoData() // 0x10AFF0E0
		{
			mangled_x86(MANGLED_TODO, "??0ClientInfoData@ClientDataTracker@Server@@QAE@XZ");
			// Server::ClientDataTracker::ClientInfoData *const this;
			todo("implement");
			_sub_10AFF0E0(this);
		}

		extern MyNetworkSessionListener* _sub_10AFF160(Server::ClientDataTracker::MyNetworkSessionListener *const);
		_inline MyNetworkSessionListener::MyNetworkSessionListener() // 0x10AFF160
		{
			mangled_x86(MANGLED_TODO, "??0MyNetworkSessionListener@ClientDataTracker@Server@@QAE@XZ");
			// Server::ClientDataTracker::MyNetworkSessionListener *const this;
			todo("implement");
			_sub_10AFF160(this);
		}
	}
}

/* ---------- private code */

#endif // __SERVER_CLIENTDATATRACKER_HPP__
