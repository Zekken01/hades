/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <signal.h>  // hades: added for 0x106D1810

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace Debug {}
using namespace ::Debug;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Debug
{
	extern void AssertHandle(char const *filename, char const *funcName, __int32 lineNum, char const *expr, char const *msg, ...);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Debug
{
	void AssertHandle(char const *filename, char const *funcName, __int32 lineNum, char const *expr, char const *msg, ...) // 0x106D1810
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AssertHandle@Debug@@YAXPBD0H00ZZ");
		// char const *funcName;
		// __int32 lineNum;
		// char const *expr;
		// char const *msg;
		// __int32 msgLen;
		// char messageBuff[8192];
		// std::stringstream ss;
		// unsigned long decision;
			// char *va;
		// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
		// function call : void ()

		char messageBuff[8192];
		__int32 msgLen = 0;
		if (msg)
		{
			char *va;
			va_start(va, msg);
			msgLen = vsprintf_s(messageBuff, sizeof(messageBuff), msg, va);
			va_end(va);
		}
		std::stringstream ss;
		ss << "Debug Assertion Failed!" << "\r\n\r\n";
		ss << "Function: " << funcName << "\r\n";
		ss << "File: " << strstr(filename, "ElDorito\\") + 10 << "\r\n";
		ss << "Line: " << lineNum << "\r\n\r\n";
		ss << (msgLen > 0 ? messageBuff : expr);
		unsigned long decision = MessageBoxA(*(HWND *)0x199C014, ss.str().c_str(), "Assertion failed! Abort=Quit, Retry=Debug, Ignore=Continue", MB_ABORTRETRYIGNORE | MB_ICONHAND | MB_TASKMODAL | MB_SETFOREGROUND);
		if (decision == IDABORT)
		{
			raise(SIGABRT);
			_exit(3);
		}
		else if (decision == IDRETRY)
			DebugBreak();
	}
}

/* ---------- private code */
