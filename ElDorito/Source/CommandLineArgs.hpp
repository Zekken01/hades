#ifndef __COMMANDLINEARGS_HPP__
#define __COMMANDLINEARGS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <string>

/* ---------- forward declarations */

class CommandLineArgs;

/* ---------- constants */

/* ---------- definitions */

class CommandLineArgs
{
public:
	CommandLineArgs(CommandLineArgs const &);
	CommandLineArgs(std::string const &line);
	~CommandLineArgs();
	CommandLineArgs &operator=(CommandLineArgs &);
	_inline __int32 GetArgCount() const;
	_inline char const *GetArg(__int32 index) const;
	_inline char const *operator[](__int32 index) const;
private:
	char const **m_args; // 0x0
	__int32 m_numArgs; // 0x4
};
static_assert(sizeof(CommandLineArgs) == 8, "Invalid CommandLineArgs size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline __int32 CommandLineArgs::GetArgCount() const // 0x106676E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetArgCount@CommandLineArgs@@QBEHXZ");
	// CommandLineArgs const *const this;

	return m_numArgs;
}

extern char const *_sub_10667640(CommandLineArgs const *const, __int32);
_inline char const *CommandLineArgs::GetArg(__int32 index) const // 0x10667640
{
	mangled_x86(MANGLED_TODO, "?GetArg@CommandLineArgs@@QBEPBDH@Z");
	// __int32 index;
	todo("implement");
	char const * __result = _sub_10667640((CommandLineArgs const *)this, index);
	return __result;
}

_inline char const *CommandLineArgs::operator[](__int32 index) const // 0x106609F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??ACommandLineArgs@@QBEPBDH@Z");
	// __int32 index;

	return GetArg(index);
}

/* ---------- private code */

#endif // __COMMANDLINEARGS_HPP__
