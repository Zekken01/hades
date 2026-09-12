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
		ModuleBase(std::string moduleName);
		bool GetVariableInt(std::string const &name, unsigned long &value);
		bool GetVariableFloat(std::string const &name, float &value);
		bool GetVariableString(std::string const &name, std::string &value);
	protected:
		Modules::Command *AddCommand(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, bool (*updateEvent)(std::vector<std::string> const &, std::string &), std::initializer_list<std::string> arguments = {});  /* hades: default from 0.6.1 */
		Modules::Command *AddVariableInt(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, unsigned long defaultValue = 0, bool (*updateEvent)(std::vector<std::string> const &, std::string &) = nullptr);  /* hades: default from 0.6.1 */
		Modules::Command *AddVariableInt64(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, unsigned long long defaultValue = 0, bool (*updateEvent)(std::vector<std::string> const &, std::string &) = nullptr);  /* hades: default from 0.6.1 */
		Modules::Command *AddVariableFloat(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, float defaultValue = 0, bool (*updateEvent)(std::vector<std::string> const &, std::string &) = nullptr);  /* hades: default from 0.6.1 */
		Modules::Command *AddVariableString(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, std::string defaultValue = "", bool (*updateEvent)(std::vector<std::string> const &, std::string &) = nullptr);  /* hades: default from 0.6.1 */
	private:
		std::string moduleName; // 0x0
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
