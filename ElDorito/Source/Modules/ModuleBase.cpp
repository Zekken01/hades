/* ---------- headers */

#include "Modules/ModuleBase.hpp"
#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Modules
{
	class ModuleBase;
	struct Command;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModuleBase::ModuleBase(std::string moduleName) // 0x109776C0
	{
		this->moduleName = moduleName;
	}

	Modules::Command *ModuleBase::AddCommand(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, bool (*updateEvent)(std::vector<std::string> const &, std::string &), std::initializer_list<std::string> arguments) // 0x10977780
	{
		Modules::Command command;
		command.Name = moduleName + "." + name;
		command.ModuleName = moduleName;
		command.ShortName = shortName;
		command.Description = description;
		for (std::string arg : arguments)
			command.CommandArgs.push_back(arg);
		if (moduleName.length() <= 0)
			command.Name = name;
		command.Flags = flags;
		command.Type = eCommandTypeCommand;
		command.UpdateEvent = updateEvent;
		return Modules::CommandMap::Instance().AddCommand(command);
	}

	Modules::Command *ModuleBase::AddVariableInt(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, unsigned long defaultValue, bool (*updateEvent)(std::vector<std::string> const &, std::string &)) // 0x10978080
	{
		Modules::Command command;
		command.Name = moduleName + "." + name;
		command.ModuleName = moduleName;
		command.ShortName = shortName;
		command.Description = description;
		if (moduleName.length() <= 0)
			command.Name = name;
		command.Flags = flags;
		command.Type = eCommandTypeVariableInt;
		command.DefaultValueInt = defaultValue;
		command.ValueInt = defaultValue;
		command.ValueString = std::to_string(defaultValue);
		command.CommittedValue = command.ValueString;
		command.UpdateEvent = updateEvent;
		return Modules::CommandMap::Instance().AddCommand(command);
	}

	Modules::Command *ModuleBase::AddVariableInt64(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, unsigned long long defaultValue, bool (*updateEvent)(std::vector<std::string> const &, std::string &)) // 0x10977D90
	{
		Modules::Command command;
		command.Name = moduleName + "." + name;
		command.ModuleName = moduleName;
		command.ShortName = shortName;
		command.Description = description;
		if (moduleName.length() <= 0)
			command.Name = name;
		command.Flags = flags;
		command.Type = eCommandTypeVariableInt64;
		command.DefaultValueInt64 = defaultValue;
		command.ValueInt64 = defaultValue;
		command.ValueString = std::to_string(defaultValue);
		command.CommittedValue = command.ValueString;
		command.UpdateEvent = updateEvent;
		return Modules::CommandMap::Instance().AddCommand(command);
	}

	Modules::Command *ModuleBase::AddVariableFloat(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, float defaultValue, bool (*updateEvent)(std::vector<std::string> const &, std::string &)) // 0x10977AA0
	{
		Modules::Command command;
		command.Name = moduleName + "." + name;
		command.ModuleName = moduleName;
		command.ShortName = shortName;
		command.Description = description;
		if (moduleName.length() <= 0)
			command.Name = name;
		command.Flags = flags;
		command.Type = eCommandTypeVariableFloat;
		command.DefaultValueFloat = defaultValue;
		command.ValueFloat = defaultValue;
		command.ValueString = std::to_string(defaultValue);
		command.CommittedValue = command.ValueString;
		command.UpdateEvent = updateEvent;
		return Modules::CommandMap::Instance().AddCommand(command);
	}

	Modules::Command *ModuleBase::AddVariableString(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, std::string defaultValue, bool (*updateEvent)(std::vector<std::string> const &, std::string &)) // 0x10978350
	{
		Modules::Command command;
		command.Name = moduleName + "." + name;
		command.ModuleName = moduleName;
		command.ShortName = shortName;
		command.Description = description;
		if (moduleName.length() <= 0)
			command.Name = name;
		command.Flags = flags;
		command.Type = eCommandTypeVariableString;
		command.DefaultValueString = defaultValue;
		command.ValueString = defaultValue;
		command.CommittedValue = command.ValueString;
		command.UpdateEvent = updateEvent;
		return Modules::CommandMap::Instance().AddCommand(command);
	}

	bool ModuleBase::GetVariableInt(std::string const &name, unsigned long &value) // 0x10978780
	{
		return Modules::CommandMap::Instance().GetVariableInt(moduleName + "." + name, value);
	}

	bool ModuleBase::GetVariableFloat(std::string const &name, float &value) // 0x10978600
	{
		return Modules::CommandMap::Instance().GetVariableFloat(moduleName + "." + name, value);
	}

	bool ModuleBase::GetVariableString(std::string const &name, std::string &value) // 0x10978900
	{
		return Modules::CommandMap::Instance().GetVariableString(moduleName + "." + name, value);
	}
}

/* ---------- private code */
