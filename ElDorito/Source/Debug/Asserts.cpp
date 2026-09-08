/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

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
	_extern void _sub_106D1810(char const *, char const *, __int32, char const *, char const *, ...);
	void AssertHandle(char const *filename, char const *funcName, __int32 lineNum, char const *expr, char const *msg, ...) // 0x106D1810
	{
		mangled_x86(MANGLED_TODO, "?AssertHandle@Debug@@YAXPBD0H00ZZ");
		// char const *funcName;
		// __int32 lineNum;
		// char const *expr;
		// char const *msg;
		// __int32 msgLen;
		// char messageBuff[8192];
		// std::stringstream ss;
		// unsigned long decision;
		{
			// char *va;
		}
		// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
		// function call : void ()
		todo("implement");
		_sub_106D1810(filename, funcName, lineNum, expr, msg);
	}
}

/* ---------- private code */
