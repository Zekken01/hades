#ifndef __MODULES_MODULEBASE_HPP__
#define __MODULES_MODULEBASE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleBase
	{
	public:
		ModuleBase(Modules::ModuleBase &); /* compiler_generated() */
		ModuleBase(Modules::ModuleBase const &); /* compiler_generated() */
		ModuleBase(std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleName);
		bool GetVariableInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, unsigned long &value);
		bool GetVariableFloat(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, float &value);
		bool GetVariableString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &value);
	protected:
		Modules::Command *AddCommand(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &), std::initializer_list<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > arguments);
		Modules::Command *AddVariableInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, unsigned long defaultValue, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &));
		Modules::Command *AddVariableInt64(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, unsigned long long defaultValue, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &));
		Modules::Command *AddVariableFloat(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, float defaultValue, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &));
		Modules::Command *AddVariableString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, std::basic_string<char,std::char_traits<char>,std::allocator<char> > defaultValue, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &));
	private:
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleName; // 0x0
	public:
		_inline ~ModuleBase(); /* compiler_generated() */
		Modules::ModuleBase &operator=(Modules::ModuleBase &); /* compiler_generated() */
		Modules::ModuleBase &operator=(Modules::ModuleBase const &); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleBase) == 28, "Invalid Modules::ModuleBase size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEBASE_HPP__
