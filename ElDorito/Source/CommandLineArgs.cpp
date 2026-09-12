/* ---------- headers */

#include "CommandLineArgs.hpp"
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

/* ---------- forward declarations */

class CommandLineArgs;

namespace Debug {}
using namespace ::Debug;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

char **CommandLineToArgvA(char *CmdLine, __int32 *_argc);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern CommandLineArgs* _sub_106D12C0(CommandLineArgs *const, std::string const &);
CommandLineArgs::CommandLineArgs(std::string const &line) // 0x106D12C0
{
	mangled_x86(MANGLED_TODO, "??0CommandLineArgs@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::string const &line;
	todo("implement");
	_sub_106D12C0(this, line);
}

CommandLineArgs::~CommandLineArgs() // 0x106D1330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CommandLineArgs@@QAE@XZ");
	// CommandLineArgs *const this;
	// function call : void *(void *)

	if (m_args)
		GlobalFree((HGLOBAL)m_args);
}

/* ---------- private code */

_extern char **_sub_106D13A0(char *, __int32 *);
char **CommandLineToArgvA(char *CmdLine, __int32 *_argc) // 0x106D13A0
{
	// `anonymous-namespace'::CommandLineToArgvA
	// static ...; // 0x106D158C
// $LN18:
// $LN16:
// $LN11:
	// char *CmdLine;
	// __int32 *_argc;
	// unsigned long argc;
	// unsigned char in_QM;
	// unsigned long i;
	// unsigned long j;
	// char *_argv;
	// unsigned char in_TEXT;
	// unsigned char in_SPACE;
	// char **argv;
	// char a;
	// unsigned long len;
	// function call : void *(unsigned __int32, unsigned long)
	todo("implement");
	char ** __result = _sub_106D13A0(CmdLine, _argc);
	return __result;
}
