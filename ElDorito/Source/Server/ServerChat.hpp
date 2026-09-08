#ifndef __SERVER_SERVERCHAT_HPP__
#define __SERVER_SERVERCHAT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
#include "Patches/CustomPackets.hpp"
#include "ThirdParty/rapidjson/rapidjson.h"

#include <bitset>
#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Server
{
	namespace Chat
	{
		class ChatHandler;
		struct ChatMessage;
	}
}

/* ---------- constants */

namespace Server
{
	namespace Chat
	{
		enum ChatMessageType : unsigned __int32
		{
			Global = 0,
			Team,
			Whisper,
			Server,
			Count,
		};
	}
}

/* ---------- definitions */

namespace Server
{
	namespace Chat
	{
		struct ChatMessage
		{
			ChatMessage(Server::Chat::ChatMessageType type, std::string const &body);
			_inline ChatMessage();
			Server::Chat::ChatMessageType Type; // 0x0
			unsigned char SenderPlayer; // 0x4
			unsigned char TargetPlayer; // 0x5
			char Body[257]; // 0x6
			unsigned char __pad0[1]; // 0x107
		};
		static_assert(sizeof(Server::Chat::ChatMessage) == 264, "Invalid Server::Chat::ChatMessage size");

		class ChatHandler
		{
		public:
			virtual _inline ~ChatHandler();
			virtual void MessageSent(__int32, Server::Chat::ChatMessage *, bool *) = 0;
			virtual void MessageReceived(Server::Chat::ChatMessage const &) = 0;
			ChatHandler(Server::Chat::ChatHandler const &); /* compiler_generated() */
			_inline ChatHandler(); /* compiler_generated() */
			Server::Chat::ChatHandler &operator=(Server::Chat::ChatHandler const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Chat::ChatHandler) == 4, "Invalid Server::Chat::ChatHandler size");
	}
}

/* ---------- prototypes */

namespace Server
{
	namespace Chat
	{
		extern void Initialize();
		extern void Tick();
		extern bool SendGlobalMessage(std::string const &body);
		extern bool SendServerMessage(std::string const &body);
		extern bool SendTeamMessage(std::string const &body);
		extern bool SetPlayerMuteStatus(__int32 peer, bool muted);
		extern void ClearAllPlayersMuteStatus();
		extern bool SendAndLogServerMessage(std::string const &body);
		extern bool SendServerMessage(std::string const &body, __int32 peer);
		extern bool SendServerMessage(std::string const &body, std::bitset<17> peers);
		extern void AddHandler(std::shared_ptr<Server::Chat::ChatHandler> handler);
		extern std::string GetSenderName(Server::Chat::ChatMessage const &message);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	namespace Chat
	{
		_inline ChatMessage::ChatMessage() // 0x10C1B1B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0ChatMessage@Chat@Server@@QAE@XZ");
			// Server::Chat::ChatMessage *const this;

		}

		_extern void _sub_10C9C540(Server::Chat::ChatHandler *const);
		_inline ChatHandler::~ChatHandler() // 0x10C9C540
		{
			mangled_x86(MANGLED_TODO, "??1ChatHandler@Chat@Server@@UAE@XZ");
			// Server::Chat::ChatHandler *const this;
			todo("implement");
			_sub_10C9C540(this);
		}
	}
}

/* ---------- private code */

#endif // __SERVER_SERVERCHAT_HPP__