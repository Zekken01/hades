#ifndef __COMMANDMAP_HPP__
#define __COMMANDMAP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "ThirdParty/rapidjson/rapidjson.h"

#include <deque>
#include <functional>
#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Modules
{
	class CommandMap;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	struct Command
	{
		std::string Name; // 0x0
		std::string ModuleName; // 0x1C
		std::string ShortName; // 0x38
		std::string Description; // 0x54
		CommandFlags Flags; // 0x70
		Modules::CommandType Type; // 0x74
		bool (*UpdateEvent)(std::vector<std::string> const &, std::string &); // 0x78
		unsigned long ValueInt; // 0x7C
		unsigned long long ValueInt64; // 0x80
		float ValueFloat; // 0x88
		std::string ValueString; // 0x8C
		unsigned long DefaultValueInt; // 0xA8
		unsigned long long DefaultValueInt64; // 0xB0
		float DefaultValueFloat; // 0xB8
		std::string DefaultValueString; // 0xBC
		unsigned long ValueIntMin; // 0xD8
		unsigned long ValueIntMax; // 0xDC
		unsigned long long ValueInt64Min; // 0xE0
		unsigned long long ValueInt64Max; // 0xE8
		float ValueFloatMin; // 0xF0
		float ValueFloatMax; // 0xF4
		bool IsDirty; // 0xF8
		std::string DirtyValue; // 0xFC
		std::string CommittedValue; // 0x118
		std::vector<std::string> CommandArgs; // 0x134
		_inline Command(Modules::Command &&__that); /* compiler_generated() */
		_inline Command(Modules::Command const &__that); /* compiler_generated() */
		Command();
		std::string GenerateHelpText();
		_inline ~Command(); /* compiler_generated() */
		_inline Modules::Command &operator=(Modules::Command &&__that); /* compiler_generated() */
		Modules::Command &operator=(Modules::Command const &); /* compiler_generated() */
	};
	static_assert(sizeof(Modules::Command) == 328, "Invalid Modules::Command size");
	static_assert(offsetof(Modules::Command, DefaultValueInt64) == 0xB0, "Modules::Command::DefaultValueInt64 moved when its reconstructed padding was removed");
	static_assert(offsetof(Modules::Command, DirtyValue) == 0xFC, "Modules::Command::DirtyValue moved when its reconstructed padding was removed");
}

#pragma pack(push, 4)
namespace Modules
{
	class CommandMap :
		public Utils::Singleton<Modules::CommandMap>
	{
	public:
		std::deque<Modules::Command> Commands; // 0x0
	private:
		std::vector<std::string> queuedCommands; // 0x14
		std::vector<std::function<void __cdecl(Modules::Command const *)> > variableUpdateCallbacks; // 0x24
	public:
		Modules::Command *AddCommand(Modules::Command command);
		void FinishAddCommands();
		Modules::Command *FindCommand(std::string const &name);
		std::string ExecuteCommand(std::string command, bool isUserInput = false);  /* hades: default from 0.6.1 */
		std::string ExecuteCommand(std::vector<std::string> command, bool isUserInput = false);  /* hades: default from 0.6.1 */
		std::string ExecuteCommands(std::string &commands, bool isUserInput, bool stopOnFirstError);
		bool ExecuteCommandWithStatus(std::string command, bool isUserInput, std::string *output);
		std::string ExecuteQueue();
		void OnVariableUpdate(std::function<void __cdecl(Modules::Command const *)> callback);
		void NotifyVariableUpdated(Modules::Command const *command);
		bool GetVariableInt(std::string const &name, unsigned long &value);
		bool GetVariableInt64(std::string const &name, unsigned long long &value);
		bool GetVariableFloat(std::string const &name, float &value);
		bool GetVariableString(std::string const &name, std::string &value);
		VariableSetReturnValue SetVariable(Modules::Command *command, std::string const &value, bool markDirty);
		VariableSetReturnValue SetVariable(Modules::Command *command, std::string const &value, std::string &previousValue, bool markDirty);
		VariableSetReturnValue SetVariable(std::string const &name, std::string const &value, std::string &previousValue, bool markDirty);
		VariableSetReturnValue SetVariable(std::string const &name, std::string const &value, bool markDirty);
		VariableSetReturnValue SetVariable2(Modules::Command *command, std::string const &value, std::string &previousValue);
		VariableSetReturnValue ResetVariable(Modules::Command *command, std::string &previousValue, bool markDirty);
		std::string GenerateHelpText(std::string moduleFilter);
		void CommitDirtyVariables();
		std::string SaveVariables();
		std::string SaveKeys();
		void Update();
		_inline CommandMap() = default; /* compiler_generated() - defaulted on its
		    first declaration, so it is NOT user-provided and `new CommandMap()`
		    zero-initializes before constructing, as the original does. */
		~CommandMap(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::CommandMap) == 52, "Invalid Modules::CommandMap size");

/* ---------- prototypes */

namespace Modules
{
	extern std::string GetDefaultValueString(Modules::Command *command);
	extern bool compare_commands(Modules::Command const &lhs, Modules::Command const &rhs);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __COMMANDMAP_HPP__
