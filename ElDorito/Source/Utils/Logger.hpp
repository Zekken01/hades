#ifndef __UTILS_LOGGER_HPP__
#define __UTILS_LOGGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Patches/PlayerPropertiesExtension.hpp"
#include "ThirdParty/rapidjson/rapidjson.h"
#include "Utils/WebSocket.hpp"

#include <chrono>
#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Utils
{
	struct LogEntry;
}

/* ---------- constants */

namespace Utils
{
	enum class LogTypes
	{
		None = 0, // 0x0000
		Game = 1, // 0x0001
		Network = 2, // 0x0002
		Graphics = 4, // 0x0004
		Memory = 8, // 0x0008
		Sound = 16, // 0x0010
		Input = 32, // 0x0020 ' '
		Debug = -2147483648, // 0x80000000
		All = -1, // 0xFF
	};
}

/* ---------- definitions */

namespace Utils
{
	struct LogEntry
	{
		std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > Time; // 0x0
		Utils::LogTypes Type; // 0x8
		char const *Message; // 0xC
		_inline LogEntry(); /* compiler_generated() */
	};
	static_assert(sizeof(Utils::LogEntry) == 16, "Invalid Utils::LogEntry size");
}

// Utils::Logger is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace Utils
{
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > LogLevelToString(Utils::LogLevel level);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > LogTypesToString(Utils::LogTypes types);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __UTILS_LOGGER_HPP__
