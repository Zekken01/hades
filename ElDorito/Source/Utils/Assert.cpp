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
	Utils::FailBehavior ReportFailure(char const *condition, char const *msg, char const *file, char const *fnc, long line) // 0x10C53CB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReportFailure@Utils@@YA?AW4FailBehavior@1@PBD000J@Z");

		// Parse file name
		std::string file_name(file);

		char messageBuffer[2048];
		sprintf_s(messageBuffer, "%s\nFile: %s\nFunction: %s\nLine: %d\nCondition: '%s'", msg, file_name.c_str(), fnc, line, condition);

		if( MessageBox(NULL, "Assertion", messageBuffer, MB_ICONERROR | MB_YESNO | MB_DEFBUTTON1) == IDYES )
		{
			return Utils::FailBehavior::Halt;
		}

		return Utils::FailBehavior::Continue;
	}
}

/* ---------- private code */
