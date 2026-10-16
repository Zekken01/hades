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

CommandLineArgs::CommandLineArgs(std::string const &line) // 0x106D12C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CommandLineArgs@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	m_args = (char const **)CommandLineToArgvA((char *)line.c_str(), &m_numArgs);
}

CommandLineArgs::~CommandLineArgs() // 0x106D1330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CommandLineArgs@@QAE@XZ");

	if (m_args)
		GlobalFree((HGLOBAL)m_args);
}

/* ---------- private code */

char **CommandLineToArgvA(char *CmdLine, __int32 *_argc) // 0x106D13A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandLineToArgvA@@YAPAPADPADPAH@Z");

	char **argv;
	char *_argv;
	unsigned long len;
	unsigned long argc;
	char a;
	unsigned long i;
	unsigned long j;
	unsigned char in_QM;
	unsigned char in_TEXT;
	unsigned char in_SPACE;
	len = strlen(CmdLine);
	i = ((len + 2) / 2) * sizeof(void *) + sizeof(void *);
	argv = (char **)GlobalAlloc(GMEM_FIXED, i + (len + 2) * sizeof(char));
	if (!argv)
		return nullptr;
	_argv = (char *)(((unsigned char *)argv) + i);
	argc = 0;
	argv[argc] = _argv;
	in_QM = FALSE;
	in_TEXT = FALSE;
	in_SPACE = TRUE;
	i = 0;
	j = 0;
	while (a = CmdLine[i])
	{
		if (in_QM)
		{
			if (a == '\"')
				in_QM = FALSE;
			else
			{
				_argv[j] = a;
				j++;
			}
		}
		else
		{
			switch (a)
			{
			case '\"':
				in_QM = TRUE;
				in_TEXT = TRUE;
				if (in_SPACE)
				{
					argv[argc] = _argv + j;
					argc++;
				}
				in_SPACE = FALSE;
				break;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				if (in_TEXT)
				{
					_argv[j] = '\0';
					j++;
				}
				in_TEXT = FALSE;
				in_SPACE = TRUE;
				break;
			default:
				in_TEXT = TRUE;
				if (in_SPACE)
				{
					argv[argc] = _argv + j;
					argc++;
				}
				_argv[j] = a;
				j++;
				in_SPACE = FALSE;
				break;
			}
		}
		i++;
	}
	_argv[j] = '\0';
	argv[argc] = nullptr;
	(*_argc) = argc;
	return argv;
}
