#ifndef __DEBUG_CRASHREPORTING_CRASHREPORTER_HPP__
#define __DEBUG_CRASHREPORTING_CRASHREPORTER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeUndo.hpp"
#include "mods/font_package.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"

#include <memory>
#include <string>
#include <vector>
#include <Windows.h>

/* ---------- forward declarations */

struct s_exception;
struct s_game_options;
namespace Debug
{
	namespace CrashReporting
	{
		struct s_crash_info;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Debug
{
	namespace CrashReporting
	{
		struct s_crash_info
		{
			public:
			struct s_exception
			{
				std::string msg; // 0x0
				unsigned __int32 code; // 0x1C
				unsigned __int32 flags; // 0x20
				unsigned __int32 address; // 0x24
				__int32 num_parameters; // 0x28
				s_exception(s_exception &); /* compiler_generated() */
				s_exception(s_exception const &); /* compiler_generated() */
				_inline s_exception(); /* compiler_generated() */
				_inline ~s_exception(); /* compiler_generated() */
				s_exception &operator=(s_exception &); /* compiler_generated() */
				s_exception &operator=(s_exception const &); /* compiler_generated() */
			};
			// static_assert(sizeof(s_exception) == 44, "Invalid s_exception size");
			// Withheld: the type inventory does not describe this type, so its
			// padding could not be reconstructed.
			public:
			_CONTEXT *ctx; // 0x0
			std::string info; // 0x4
			s_exception exception; // 0x20
			std::vector<std::string,std::allocator<std::string> > tag_history; // 0x4C
			s_crash_info(Debug::CrashReporting::s_crash_info &); /* compiler_generated() */
			s_crash_info(Debug::CrashReporting::s_crash_info const &); /* compiler_generated() */
			_inline s_crash_info(); /* compiler_generated() */
			_inline ~s_crash_info(); /* compiler_generated() */
			Debug::CrashReporting::s_crash_info &operator=(Debug::CrashReporting::s_crash_info &); /* compiler_generated() */
			Debug::CrashReporting::s_crash_info &operator=(Debug::CrashReporting::s_crash_info const &); /* compiler_generated() */
		};
	}
}

// static_assert(sizeof(Debug::CrashReporting::s_crash_info) == 92, "Invalid Debug::CrashReporting::s_crash_info size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

/* ---------- prototypes */

namespace Debug
{
	namespace CrashReporting
	{
		extern char const *GetGameModeName(s_game_options *options);
		extern char const *FormatRegister(unsigned long value);
		extern void BuildStackTraceJSON(_CONTEXT const &ctx, rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer);
		extern void AddSystemInfo(rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer);
		extern void WriteDumpForCrashReporter(rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> &buffer, Debug::CrashReporting::s_crash_info const &crash);
		extern bool LaunchExternalCrashReporter(std::string &LaunchCommand);
		extern void ReportCrash(Debug::CrashReporting::s_crash_info const &crash);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __DEBUG_CRASHREPORTING_CRASHREPORTER_HPP__
