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
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleBase@Modules@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string moduleName;

		this->moduleName = moduleName;
	}

	Modules::Command *ModuleBase::AddCommand(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, bool (*updateEvent)(std::vector<std::string> const &, std::string &), std::initializer_list<std::string> arguments) // 0x10977780
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddCommand@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@P6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@ZV?$initializer_list@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@5@@Z");
		// std::string const &shortName;
		// std::string const &description;
		// CommandFlags flags;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// std::initializer_list<std::string> arguments;
		// Modules::Command command;
			// std::initializer_list<std::string> &<range>$L0;
			// std::string const *<begin>$L0;
			// std::string const *<end>$L0;
				// std::string arg;

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
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddVariableInt@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@KP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::string const &description;
		// CommandFlags flags;
		// unsigned long defaultValue;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// Modules::Command command;

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
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddVariableInt64@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@_KP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::string const &description;
		// CommandFlags flags;
		// unsigned long long defaultValue;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// Modules::Command command;

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
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddVariableFloat@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@MP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::string const &description;
		// CommandFlags flags;
		// float defaultValue;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// Modules::Command command;

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
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddVariableString@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@V45@P6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::string const &description;
		// CommandFlags flags;
		// std::string defaultValue;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// Modules::Command command;

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
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetVariableInt@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAK@Z");
		// unsigned long &value;

		return Modules::CommandMap::Instance().GetVariableInt(moduleName + "." + name, value);
	}

	bool ModuleBase::GetVariableFloat(std::string const &name, float &value) // 0x10978600
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetVariableFloat@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAM@Z");
		// float &value;

		return Modules::CommandMap::Instance().GetVariableFloat(moduleName + "." + name, value);
	}

	bool ModuleBase::GetVariableString(std::string const &name, std::string &value) // 0x10978900
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetVariableString@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &value;

		return Modules::CommandMap::Instance().GetVariableString(moduleName + "." + name, value);
	}
}

/* ---------- private code */
