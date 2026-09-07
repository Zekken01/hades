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

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern CommandLineArgs* _sub_106D12C0(CommandLineArgs *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
CommandLineArgs::CommandLineArgs(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &line) // 0x106D12C0
{
	mangled_x86(MANGLED_TODO, "??0CommandLineArgs@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &line;
	todo("implement");
	_sub_106D12C0(this, line);
}

_extern void _sub_106D1330(CommandLineArgs *const);
CommandLineArgs::~CommandLineArgs() // 0x106D1330
{
	mangled_x86(MANGLED_TODO, "??1CommandLineArgs@@QAE@XZ");
	// CommandLineArgs *const this;
	// function call : void *(void *)
	todo("implement");
	_sub_106D1330(this);
}

/* ---------- private code */
