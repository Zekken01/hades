#ifndef __CONSOLE_CONSOLE_HPP__
#define __CONSOLE_CONSOLE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Console
{
	class ConsoleOutputHandler;
}

/* ---------- constants */

/* ---------- definitions */

namespace Console
{
	class ConsoleOutputHandler
	{
	public:
		virtual _inline ~ConsoleOutputHandler();
		virtual void WriteLine(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &) = 0;
		ConsoleOutputHandler(Console::ConsoleOutputHandler const &); /* compiler_generated() */
		_inline ConsoleOutputHandler(); /* compiler_generated() */
		Console::ConsoleOutputHandler &operator=(Console::ConsoleOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(Console::ConsoleOutputHandler) == 4, "Invalid Console::ConsoleOutputHandler size");
}

/* ---------- prototypes */

namespace Console
{
	extern void Init();
	extern void WriteLine(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &line);
	extern void RegisterHandler(std::shared_ptr<Console::ConsoleOutputHandler> handler);
}

/* ---------- globals */

/* ---------- public code */

namespace Console
{
	_extern void _sub_10950600(Console::ConsoleOutputHandler *const);
	_inline ConsoleOutputHandler::~ConsoleOutputHandler() // 0x10950600
	{
		mangled_x86(MANGLED_TODO, "??1ConsoleOutputHandler@Console@@UAE@XZ");
		// Console::ConsoleOutputHandler *const this;
		todo("implement");
		_sub_10950600(this);
	}
}

/* ---------- private code */

#endif // __CONSOLE_CONSOLE_HPP__
