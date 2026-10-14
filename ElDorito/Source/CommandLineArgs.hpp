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

_inline char const *CommandLineArgs::GetArg(__int32 index) const // 0x10667640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetArg@CommandLineArgs@@QBEPBDH@Z");
	// __int32 index;

	(void)((!!(index >= 0 && index < GetArgCount())) || (_wassert(L"index >= 0 && index < GetArgCount()", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\CommandLineArgs.hpp", 23), 0));
	if (index < 0 || index >= GetArgCount())
	{
		return nullptr;
	}

	return m_args[index];
}

_inline char const *CommandLineArgs::operator[](__int32 index) const // 0x106609F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??ACommandLineArgs@@QBEPBDH@Z");
	// __int32 index;

	return GetArg(index);
}

/* ---------- private code */

#endif // __COMMANDLINEARGS_HPP__
