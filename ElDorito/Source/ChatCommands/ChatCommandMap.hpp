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
	extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > getHelpText();
	extern void RegisterCommand(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, ChatCommands::CommandFlags flags, std::function<bool __cdecl(int,std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &,std::basic_string<char,std::char_traits<char>,std::allocator<char> > &)> &&handler);
	extern ChatCommands::ChatCommand *FindChatCommand(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name);
	extern bool handleChatMessage(Server::Chat::ChatMessage const &message, __int32 peer);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __CHATCOMMANDS_CHATCOMMANDMAP_HPP__
