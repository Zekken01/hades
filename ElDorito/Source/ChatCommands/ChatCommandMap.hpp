#ifndef __CHATCOMMANDS_CHATCOMMANDMAP_HPP__
#define __CHATCOMMANDS_CHATCOMMANDMAP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Common/Http/HttpHeaders.hpp"

#include <functional>
#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace ChatCommands
{
	struct ChatCommand;
}
namespace Server
{
	namespace Chat
	{
		struct ChatMessage;
	}
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace ChatCommands
{
	extern void LifeCycleStateChanged(Blam::Network::LifeCycleState newState);
	extern void Init();
	extern bool addToVoteTimes(unsigned long long sender);
	extern void Tick();
	extern std::vector<std::string,std::allocator<std::string> > getHelpText();
	extern void RegisterCommand(std::string const &name, std::string const &description, ChatCommands::CommandFlags flags, std::function<bool __cdecl(int,std::vector<std::string,std::allocator<std::string> > const &,std::string &)> &&handler);
	extern ChatCommands::ChatCommand *FindChatCommand(std::string const &name);
	extern bool handleChatMessage(Server::Chat::ChatMessage const &message, __int32 peer);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __CHATCOMMANDS_CHATCOMMANDMAP_HPP__
