/* ---------- headers */

#include "Utils/Assert.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

typedef void *(*CreateInterface_t)(char const *, __int32 *);

/* ---------- prototypes */

namespace Utils
{
	extern Utils::FailBehavior ReportFailure(char const *condition, char const *msg, char const *file, char const *fnc, long line);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	extern FailBehavior _sub_10C53CB0(char const *, char const *, char const *, char const *, long);
	Utils::FailBehavior ReportFailure(char const *condition, char const *msg, char const *file, char const *fnc, long line) // 0x10C53CB0
	{
		mangled_x86(MANGLED_TODO, "?ReportFailure@Utils@@YA?AW4FailBehavior@1@PBD000J@Z");
		// char const *condition;
		// char const *msg;
		// char const *file;
		// char const *fnc;
		// long line;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > file_name;
		// char messageBuffer[2048];
		// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
		todo("implement");
		Utils::FailBehavior __result = _sub_10C53CB0(condition, msg, file, fnc, line);
		return __result;
	}
}

/* ---------- private code */
