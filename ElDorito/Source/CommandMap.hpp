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
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > Name; // 0x0
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ModuleName; // 0x1C
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ShortName; // 0x38
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > Description; // 0x54
		CommandFlags Flags; // 0x70
		Modules::CommandType Type; // 0x74
		bool (*UpdateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &); // 0x78
		unsigned long ValueInt; // 0x7C
		unsigned long long ValueInt64; // 0x80
		float ValueFloat; // 0x88
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ValueString; // 0x8C
		unsigned long DefaultValueInt; // 0xA8
		unsigned char __pad0[4]; // 0xAC
		unsigned long long DefaultValueInt64; // 0xB0
		float DefaultValueFloat; // 0xB8
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > DefaultValueString; // 0xBC
		unsigned long ValueIntMin; // 0xD8
		unsigned long ValueIntMax; // 0xDC
		unsigned long long ValueInt64Min; // 0xE0
		unsigned long long ValueInt64Max; // 0xE8
		float ValueFloatMin; // 0xF0
		float ValueFloatMax; // 0xF4
		bool IsDirty; // 0xF8
		unsigned char __pad1[3]; // 0xF9
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > DirtyValue; // 0xFC
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > CommittedValue; // 0x118
		std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > CommandArgs; // 0x134
		_inline Command(Modules::Command &&__that); /* compiler_generated() */
		_inline Command(Modules::Command const &__that); /* compiler_generated() */
		Command();
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GenerateHelpText();
		_inline ~Command(); /* compiler_generated() */
		_inline Modules::Command &operator=(Modules::Command &&__that); /* compiler_generated() */
		Modules::Command &operator=(Modules::Command const &); /* compiler_generated() */
		unsigned char __pad2[4]; // 0x144
	};
	static_assert(sizeof(Modules::Command) == 328, "Invalid Modules::Command size");
}

#pragma pack(push, 4)
namespace Modules
{
	class CommandMap :
		public Utils::Singleton<Modules::CommandMap>
	{
	public:
		std::deque<Modules::Command,std::allocator<Modules::Command> > Commands; // 0x0
	private:
		std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > queuedCommands; // 0x14
		std::vector<std::function<void __cdecl(Modules::Command const *)>,std::allocator<std::function<void __cdecl(Modules::Command const *)> > > variableUpdateCallbacks; // 0x24
	public:
		Modules::Command *AddCommand(Modules::Command command);
		void FinishAddCommands();
		Modules::Command *FindCommand(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name);
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ExecuteCommand(std::basic_string<char,std::char_traits<char>,std::allocator<char> > command, bool isUserInput);
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ExecuteCommand(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > command, bool isUserInput);
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ExecuteCommands(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &commands, bool isUserInput, bool stopOnFirstError);
		bool ExecuteCommandWithStatus(std::basic_string<char,std::char_traits<char>,std::allocator<char> > command, bool isUserInput, std::basic_string<char,std::char_traits<char>,std::allocator<char> > *output);
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ExecuteQueue();
		void OnVariableUpdate(std::function<void __cdecl(Modules::Command const *)> callback);
		void NotifyVariableUpdated(Modules::Command const *command);
		bool GetVariableInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, unsigned long &value);
		bool GetVariableInt64(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, unsigned long long &value);
		bool GetVariableFloat(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, float &value);
		bool GetVariableString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &value);
		VariableSetReturnValue SetVariable(Modules::Command *command, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &value, bool markDirty);
		VariableSetReturnValue SetVariable(Modules::Command *command, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &value, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &previousValue, bool markDirty);
		VariableSetReturnValue SetVariable(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &value, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &previousValue, bool markDirty);
		VariableSetReturnValue SetVariable(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &value, bool markDirty);
		VariableSetReturnValue SetVariable2(Modules::Command *command, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &value, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &previousValue);
		VariableSetReturnValue ResetVariable(Modules::Command *command, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &previousValue, bool markDirty);
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GenerateHelpText(std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleFilter);
		void CommitDirtyVariables();
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > SaveVariables();
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > SaveKeys();
		void Update();
		_inline CommandMap(); /* compiler_generated() */
		~CommandMap(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::CommandMap) == 52, "Invalid Modules::CommandMap size");

/* ---------- prototypes */

namespace Modules
{
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetDefaultValueString(Modules::Command *command);
	extern bool compare_commands(Modules::Command const &lhs, Modules::Command const &rhs);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __COMMANDMAP_HPP__
