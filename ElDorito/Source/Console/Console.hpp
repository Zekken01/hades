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
		virtual void WriteLine(std::string const &) = 0;
		ConsoleOutputHandler(Console::ConsoleOutputHandler const &); /* compiler_generated() */
		_inline ConsoleOutputHandler() = default; /* compiler_generated() */
		Console::ConsoleOutputHandler &operator=(Console::ConsoleOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(Console::ConsoleOutputHandler) == 4, "Invalid Console::ConsoleOutputHandler size");
}

/* ---------- prototypes */

namespace Console
{
	extern void Init();
	extern void WriteLine(std::string const &line);
	extern void RegisterHandler(std::shared_ptr<Console::ConsoleOutputHandler> handler);
}

/* ---------- globals */

/* ---------- public code */

namespace Console
{
	inline ConsoleOutputHandler::~ConsoleOutputHandler() // 0x10950600
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1ConsoleOutputHandler@Console@@UAE@XZ");
	}
}

/* ---------- private code */

#endif // __CONSOLE_CONSOLE_HPP__
