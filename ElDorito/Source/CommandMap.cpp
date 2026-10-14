/* ---------- headers */

#include "CommandMap.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandLineArgs.hpp"
#include "CommandScript.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "Modules/ModuleServer.hpp"  // hades: added for 0x10947090

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CommandLineArgs;
struct begin;
struct end;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Modules
{
	class CommandMap;
	class CommandScript;
	class CommandScriptStack;
	struct Command;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Debug {}
using namespace ::Debug;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Modules
{
	extern std::string GetDefaultValueString(Modules::Command *command);
	extern bool compare_commands(Modules::Command const &lhs, Modules::Command const &rhs);
}

/* ---------- globals */

namespace Modules
{
	Modules::CommandScriptStack scriptStack; // 0x1240DA14  // hades: defined, so its dynamic initializer emits the constructor
}

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	Command::Command() : UpdateEvent(nullptr), ValueInt(0), ValueFloat(0.0f), DefaultValueInt(0), DefaultValueFloat(0.0f), ValueIntMin(0), ValueIntMax(0), ValueFloatMin(0.0f), ValueFloatMax(0.0f), IsDirty(false) /* hades-mem-init:  */ // 0x10944CB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0Command@Modules@@QAE@XZ");
		// Modules::Command *const this;
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CommandScriptStack@Modules@@QAE@XZ"); no body to assert in
}


namespace Modules
{
	std::string Command::GenerateHelpText() // 0x10949150
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateHelpText@Command@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x10949720
		// static ...; // 0x1094971B
		// static ...; // 0x1094970F
		// static ...; // 0x1094970B
		// static ...; // 0x10949703
		// static ...; // 0x109496FB
		// static ...; // 0x109496F0
		// static ...; // 0x109496A8
		// static ...; // 0x109496A0
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
		// Modules::Command *const this;
		// std::stringstream ss;
			// std::string paramDescs;
			// std::stringstream paramStream;
				// std::vector<std::string> &<range>$L0;
				// std::string *<begin>$L0;
				// std::string *<end>$L0;
					// std::string arg;
						// std::string argdesc;
						// unsigned __int32 nameEnd;
						// std::string argname;

		std::stringstream ss;
		ss << Name << " - " << Description << "." << std::endl;
		ss << "Usage: " << Name << " ";
		if (Type != eCommandTypeCommand)
		{
			ss << "<value(";
			switch (Type)
			{
			case eCommandTypeVariableInt:
				ss << "int";
				break;
			case eCommandTypeVariableInt64:
				ss << "int64";
				break;
			case eCommandTypeVariableFloat:
				ss << "float";
				break;
			case eCommandTypeVariableString:
				ss << "string";
				break;
			}
			ss << ")>" << std::endl << "Current value: " << ValueString << std::endl << std::endl;
		}
		else
		{
			std::stringstream paramStream;
			for (auto arg : CommandArgs)
			{
				std::string argname = arg;
				std::string argdesc = "";
				unsigned __int32 nameEnd = arg.find(" ");
				if (nameEnd != std::string::npos)
				{
					argname = arg.substr(0, nameEnd);
					if (arg.length() > nameEnd + 1)
						argdesc = arg.substr(nameEnd + 1);
				}
				ss << "<" << argname << "> ";
				if (argdesc.length() > 0)
					paramStream << "  " << argname << ": " << argdesc << std::endl;
			}
			ss << std::endl;
			std::string paramDescs = paramStream.str();
			if (paramDescs.length() > 0)
				ss << paramDescs << std::endl;
			else
				ss << std::endl;
		}
		return ss.str();
	}

	// mangled_x86(MANGLED_DEFAULT, "??1Command@Modules@@QAE@XZ"); no body to assert in
	// _inline Command::~Command() = default; // 0x10945510  // hades: implicit

	// mangled_x86(MANGLED_DEFAULT, "??1CommandScript@Modules@@QAE@XZ"); no body to assert in
	_inline CommandScript::~CommandScript() = default; // 0x109455E0

	// mangled_x86(MANGLED_DEFAULT, "??1CommandScriptStack@Modules@@QAE@XZ"); no body to assert in
	_inline CommandScriptStack::~CommandScriptStack() = default; // 0x10945660

	// mangled_x86(MANGLED_DEFAULT, "??4Command@Modules@@QAEAAU01@$$QAU01@@Z"); no body to assert in
	// _inline Modules::Command &Command::operator=(Modules::Command &&__that) = default; // 0x109456B0  // hades: implicit

	// mangled_x86(MANGLED_DEFAULT, "??0Command@Modules@@QAE@$$QAU01@@Z"); no body to assert in
	// _inline Command::Command(Modules::Command &&__that) = default; // 0x109445D0  // hades: implicit

	// mangled_x86(MANGLED_DEFAULT, "??0Command@Modules@@QAE@ABU01@@Z"); no body to assert in
	// _inline Command::Command(Modules::Command const &__that) = default; // 0x10944910  // hades: implicit

	Modules::Command *CommandMap::FindCommand(std::string const &name) // 0x10948CA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FindCommand@CommandMap@Modules@@QAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10948E60
		// static ...; // 0x10948E58
		// Modules::CommandMap *const this;
		// std::string const &name;
			// std::_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > it;

		for (auto it = Commands.begin(); it < Commands.end(); it++)
		{
			if ((it->Name.length() > 0 && !_stricmp(it->Name.c_str(), name.c_str())) || (it->ShortName.length() > 0 && !_stricmp(it->ShortName.c_str(), name.c_str())))
				return &(*it);
		}
		return nullptr;
	}

	Modules::Command *CommandMap::AddCommand(Modules::Command command) // 0x109469C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddCommand@CommandMap@Modules@@QAEPAUCommand@2@U32@@Z");
		// Modules::Command command;

		if (FindCommand(command.Name) || FindCommand(command.ShortName))
		{
			return nullptr;
		}

		Commands.push_back(command);
		return &Commands.back();
	}

	void CommandMap::FinishAddCommands() // 0x10948EF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FinishAddCommands@CommandMap@Modules@@QAEXXZ");
		// static ...; // 0x109490C4
		// static ...; // 0x109490B9
		// static ...; // 0x109490B0
		// static ...; // 0x109490A8
		// static ...; // 0x10949078
		// static ...; // 0x10949070
		// Modules::CommandMap *const this;
		// std::string previousValue;
			// std::deque<Modules::Command> &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
				// Modules::Command command;
		// function call : bool (*)(std::vector<std::string> const &, std::string &)

		std::string previousValue;
		for (auto command : Commands)
		{
			if (command.Type != eCommandTypeCommand && !(command.Flags & eCommandFlagsDontUpdateInitial))
			{
				if (command.UpdateEvent)
					command.UpdateEvent(std::vector<std::string>(), previousValue);
			}
		}
	}
}


namespace Modules
{
	std::string CommandMap::ExecuteCommand(std::vector<std::string> command, bool isUserInput) // 0x10946DC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteCommand@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@_N@Z");
		// static ...; // 0x10946FE4
		// static ...; // 0x10946FC0
		// static ...; // 0x10946FB8
		// Modules::CommandMap *const this;
		// std::vector<std::string> command;
		// bool isUserInput;
		// std::stringstream buff;
		// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::string> > > commandEnd;
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::string> > > it;

		auto commandEnd = command.end();
		std::stringstream buff;
		for (auto it = command.begin(); it != commandEnd; ++it)
		{
			buff << *it;
			if (it != commandEnd - 1)
				buff << " ";
		}
		return ExecuteCommand(buff.str(), isUserInput);
	}

	bool CommandMap::ExecuteCommandWithStatus(std::string command, bool isUserInput, std::string *output) // 0x10947090
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteCommandWithStatus@CommandMap@Modules@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_NPAV34@@Z");
		// static ...; // 0x10948228
		// static ...; // 0x10948220
		// Modules::CommandMap *const this;
		// std::string command;
		// bool isUserInput;
		// std::string *output;
		// bool ret;
		// bool opReset;
		// __int32 numArgs;
		// CommandLineArgs cmdArgs;
		// VariableSetReturnValue updateRet;
		// std::string previousValue;
		// Modules::Command *cmd;
		// std::vector<std::string> argsVect;
		// bool SkipHostCheck;
			// Blam::Network::Session *session;
			// bool (*const game_options_is_valid)();
			// bool (*const game_engine_is_forge)();
			// __int32 i;
		// function call : bool (*const)()
		// function call : bool (*const)()
		// function call : bool (*)(std::vector<std::string> const &, std::string &)
		// function call : bool (*)(std::vector<std::string> const &, std::string &)
		// function call : bool (*)(std::vector<std::string> const &, std::string &)

		*output = "";
		bool SkipHostCheck = false;
		bool opReset = false;
		opReset = command.starts_with('!');
		if (opReset)
			command = command.substr(1);
		CommandLineArgs cmdArgs(command);
		__int32 numArgs = cmdArgs.GetArgCount();
		if (numArgs <= 0)
		{
			*output = "Invalid input";
			return false;
		}
		Modules::Command *cmd = FindCommand(cmdArgs[0]);
		if (!cmd)
		{
			*output = "Command/Variable not found";
			return false;
		}
		if ((cmd->Flags & eCommandFlagsRunOnMainMenu) && !ElDorito::Instance().GameHasMenuShown)
		{
			queuedCommands.push_back(command);
			*output = "Command queued until mainmenu shows";
			return true;
		}
		if (cmd->Flags & eCommandFlagsClientAllowable)
		{
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished() && !session->IsHost() && ((cmd->ModuleName == "Camera" && Utils::Singleton<Modules::ModuleServer>::Instance().VarCameraAllowedOnClientsClient->ValueInt == 1) || (cmd->ModuleName == "Debug" && Utils::Singleton<Modules::ModuleServer>::Instance().VarDebugAllowedOnClientsClient->ValueInt == 1)))
				SkipHostCheck = true;
		}
		if (!SkipHostCheck && (cmd->Flags & eCommandFlagsCheat || cmd->Flags & eCommandFlagsHostOnly))
		{
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && session->IsEstablished() && !session->IsHost())
			{
				*output = "Only a player hosting a game can use this command";
				return false;
			}
		}
		if (cmd->Flags & eCommandFlagsForge)
		{
			bool (*const game_options_is_valid)() = reinterpret_cast<bool (*)()>(0x5314B0);
			bool (*const game_engine_is_forge)() = reinterpret_cast<bool (*)()>(0x59A780);
			if (!game_options_is_valid() || !game_engine_is_forge())
			{
				*output = "This command can only be run in forge";
				return false;
			}
		}
		std::vector<std::string> argsVect;
		if (numArgs > 1)
			for (__int32 i = 1; i < numArgs; i++)
				argsVect.push_back(cmdArgs[i]);
		if (cmd->Type == eCommandTypeCommand && cmd->Flags == eCommandFlagsArgsNoParse)
		{
			argsVect.clear();
			if (numArgs >= 2)
				argsVect.push_back(command.substr(strlen(cmdArgs[0]) + 1));
			return cmd->UpdateEvent(argsVect, *output);
		}
		if (cmd->Type == eCommandTypeCommand)
			return cmd->UpdateEvent(argsVect, *output);
		if (numArgs <= 1 && !opReset)
		{
			*output = cmd->ValueString;
			return true;
		}
		std::string previousValue;
		VariableSetReturnValue updateRet;
		if (opReset)
			updateRet = ResetVariable(cmd, previousValue, isUserInput);
		else
			updateRet = SetVariable(cmd, argsVect[0], previousValue, isUserInput);
		switch (updateRet)
		{
		case eVariableSetReturnValueError:
			*output = "Command/variable not found";
			return false;
		case eVariableSetReturnValueInvalidArgument:
			*output = "Invalid value";
			return false;
		case eVariableSetReturnValueOutOfRange:
			if (cmd->Type == eCommandTypeVariableInt)
				*output = "Value " + argsVect[0] + " out of range [" + std::to_string(cmd->ValueIntMin) + ".." + std::to_string(cmd->ValueIntMax) + "]";
			else if (cmd->Type == eCommandTypeVariableInt64)
				*output = "Value " + argsVect[0] + " out of range [" + std::to_string(cmd->ValueInt64Min) + ".." + std::to_string(cmd->ValueInt64Max) + "]";
			else if (cmd->Type == eCommandTypeVariableFloat)
				*output = "Value " + argsVect[0] + " out of range [" + std::to_string(cmd->ValueFloatMin) + ".." + std::to_string(cmd->ValueFloatMax) + "]";
			else
				*output = "Value " + argsVect[0] + " out of range [this shouldn't be happening!]";
			return false;
		}
		if (!cmd->UpdateEvent)
		{
			*output = previousValue + " -> " + cmd->ValueString;
			if (cmd->Flags & eCommandFlagsRestartRequired && numArgs > 0)
				*output = *output + "\nGame must be restarted to take effect";
			return true;
		}
		bool ret = cmd->UpdateEvent(argsVect, *output);
		if (!ret)
			SetVariable(cmd, previousValue, false);
		if (output->length() <= 0)
			*output = previousValue + " -> " + cmd->ValueString;
		if (cmd->Flags & eCommandFlagsRestartRequired && numArgs > 0)
			*output = *output + "\nGame must be restarted to take effect";
		return ret;
	}
}


namespace Modules
{
	std::string GetDefaultValueString(Modules::Command *command) // 0x10949E80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetDefaultValueString@Modules@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUCommand@1@@Z");
		// Modules::Command *command;

		switch (command->Type)
		{
		case eCommandTypeVariableInt:
			return std::to_string(command->DefaultValueInt);
		case eCommandTypeVariableInt64:
			return std::to_string(command->DefaultValueInt64);
		case eCommandTypeVariableFloat:
			return std::to_string(command->DefaultValueFloat);
		}
		return command->DefaultValueString;
	}
}


namespace Modules
{
	VariableSetReturnValue CommandMap::ResetVariable(Modules::Command *command, std::string &previousValue, bool markDirty) // 0x1094A370
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ResetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@PAUCommand@2@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
		// bool markDirty;

		return SetVariable(command, GetDefaultValueString(command), previousValue, markDirty);
	}
}


namespace Modules
{
	std::string CommandMap::ExecuteCommand(std::string command, bool isUserInput) // 0x10946C60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteCommand@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V34@_N@Z");
		// static ...; // 0x10946D5C
		// Modules::CommandMap *const this;
		// std::string command;
		// bool isUserInput;
		// std::string output;

		std::string output;
		ExecuteCommandWithStatus(command, isUserInput, &output);
		return output;
	}

	bool CommandMap::GetVariableInt(std::string const &name, unsigned long &value) // 0x1094A100
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetVariableInt@CommandMap@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAK@Z");
		// unsigned long &value;
		// Modules::Command *command;

		Modules::Command *command = FindCommand(name);
		if (!command || command->Type != eCommandTypeVariableInt)
			return false;
		value = command->ValueInt;
		return true;
	}

	bool CommandMap::GetVariableInt64(std::string const &name, unsigned long long &value) // 0x1094A070
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetVariableInt64@CommandMap@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AA_K@Z");
		// unsigned long long &value;
		// Modules::Command *command;

		Modules::Command *command = FindCommand(name);
		if (!command || command->Type != eCommandTypeVariableInt64)
			return false;
		value = command->ValueInt64;
		return true;
	}

	bool CommandMap::GetVariableFloat(std::string const &name, float &value) // 0x10949FE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetVariableFloat@CommandMap@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAM@Z");
		// float &value;
		// Modules::Command *command;

		Modules::Command *command = FindCommand(name);
		if (!command || command->Type != eCommandTypeVariableFloat)
			return false;
		value = command->ValueFloat;
		return true;
	}

	bool CommandMap::GetVariableString(std::string const &name, std::string &value) // 0x1094A180
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetVariableString@CommandMap@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &value;
		// Modules::Command *command;

		Modules::Command *command = FindCommand(name);
		if (!command || command->Type != eCommandTypeVariableString)
			return false;
		value = command->ValueString;
		return true;
	}
}


namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable(std::string const &name, std::string const &value, bool markDirty) // 0x1094B130
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0_N@Z");
		// Modules::CommandMap *const this;
		// std::string const &name;
		// std::string const &value;
		// bool markDirty;
		// std::string previousValue;

		std::string previousValue;
		return SetVariable(name, value, previousValue, markDirty);
	}
}


namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable(std::string const &name, std::string const &value, std::string &previousValue, bool markDirty) // 0x1094B0A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0AAV45@_N@Z");
		// bool markDirty;
		// Modules::Command *command;

		Modules::Command *command = FindCommand(name);
		if (!command)
			return eVariableSetReturnValueError;
		return SetVariable(command, value, previousValue, markDirty);
	}
}


namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable(Modules::Command *command, std::string const &value, bool markDirty) // 0x1094B880
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@PAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
		// Modules::CommandMap *const this;
		// Modules::Command *command;
		// std::string const &value;
		// bool markDirty;
		// std::string previousValue;

		std::string previousValue;
		return SetVariable(command, value, previousValue, markDirty);
	}
}


namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable(Modules::Command *command, std::string const &value, std::string &previousValue, bool markDirty) // 0x1094B250
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@PAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV56@_N@Z");
	// $LN15:
	// $LN11:
	// $LN7:
	// $LN6:
		// Modules::CommandMap *const this;
		// Modules::Command *command;
		// std::string const &value;
		// std::string &previousValue;
		// bool markDirty;
			// unsigned long newValue;
			// unsigned long long newValue;
			// float newValue;

		if (command->Flags & eCommandFlagsInternal)
			return eVariableSetReturnValueError;
		try
		{
			switch (command->Type)
			{
			case eCommandTypeVariableString:
				previousValue = command->ValueString;
				command->ValueString = value;
				break;
			case eCommandTypeVariableInt:
			{
				previousValue = std::to_string(command->ValueInt);
				unsigned long newValue = std::stoul(value, 0, 0);
				if ((command->ValueIntMin || command->ValueIntMax) && (newValue < command->ValueIntMin || newValue > command->ValueIntMax))
					return eVariableSetReturnValueOutOfRange;
				command->ValueInt = newValue;
				command->ValueString = std::to_string(command->ValueInt);
				break;
			}
			case eCommandTypeVariableInt64:
			{
				previousValue = std::to_string(command->ValueInt);
				unsigned long long newValue = std::stoull(value, 0, 0);
				if ((command->ValueInt64Min || command->ValueInt64Max) && (newValue < command->ValueInt64Min || newValue > command->ValueInt64Max))
					return eVariableSetReturnValueOutOfRange;
				command->ValueInt64 = newValue;
				command->ValueString = std::to_string(command->ValueInt64);
				break;
			}
			case eCommandTypeVariableFloat:
			{
				previousValue = std::to_string(command->ValueFloat);
				float newValue = std::stof(value, 0);
				if ((command->ValueFloatMin || command->ValueFloatMax) && (newValue < command->ValueFloatMin || newValue > command->ValueFloatMax))
					return eVariableSetReturnValueOutOfRange;
				command->ValueFloat = newValue;
				command->ValueString = std::to_string(command->ValueFloat);
				break;
			}
			}
		}
		catch (std::invalid_argument &)
		{
			return eVariableSetReturnValueInvalidArgument;
		}
		catch (std::out_of_range &)
		{
			return eVariableSetReturnValueInvalidArgument;
		}
		if (markDirty)
		{
			command->DirtyValue = value;
			command->IsDirty = true;
		}
		NotifyVariableUpdated(command);
		return eVariableSetReturnValueSuccess;
	}
}


namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable2(Modules::Command *command, std::string const &value, std::string &previousValue) // 0x1094AAC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetVariable2@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@PAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV56@@Z");
	// $LN14:
	// $LN10:
	// $LN6:
	// $LN5:
		// Modules::CommandMap *const this;
		// Modules::Command *command;
		// std::string const &value;
		// std::string &previousValue;
			// unsigned long newValue;
			// unsigned long long newValue;
			// float newValue;

		try
		{
			switch (command->Type)
			{
			case eCommandTypeVariableString:
				previousValue = command->ValueString;
				command->ValueString = value;
				break;
			case eCommandTypeVariableInt:
			{
				previousValue = std::to_string(command->ValueInt);
				unsigned long newValue = std::stoul(value, 0, 0);
				if ((command->ValueIntMin || command->ValueIntMax) && (newValue < command->ValueIntMin || newValue > command->ValueIntMax))
					return eVariableSetReturnValueOutOfRange;
				command->ValueInt = newValue;
				command->ValueString = std::to_string(command->ValueInt);
				break;
			}
			case eCommandTypeVariableInt64:
			{
				previousValue = std::to_string(command->ValueInt);
				unsigned long long newValue = std::stoull(value, 0, 0);
				if ((command->ValueInt64Min || command->ValueInt64Max) && (newValue < command->ValueInt64Min || newValue > command->ValueInt64Max))
					return eVariableSetReturnValueOutOfRange;
				command->ValueInt64 = newValue;
				command->ValueString = std::to_string(command->ValueInt64);
				break;
			}
			case eCommandTypeVariableFloat:
			{
				previousValue = std::to_string(command->ValueFloat);
				float newValue = std::stof(value, 0);
				if ((command->ValueFloatMin || command->ValueFloatMax) && (newValue < command->ValueFloatMin || newValue > command->ValueFloatMax))
					return eVariableSetReturnValueOutOfRange;
				command->ValueFloat = newValue;
				command->ValueString = std::to_string(command->ValueFloat);
				break;
			}
			}
		}
		catch (std::invalid_argument &)
		{
			return eVariableSetReturnValueInvalidArgument;
		}
		catch (std::out_of_range &)
		{
			return eVariableSetReturnValueInvalidArgument;
		}
		NotifyVariableUpdated(command);
		return eVariableSetReturnValueSuccess;
	}

	bool compare_commands(Modules::Command const &lhs, Modules::Command const &rhs) // 0x1094DC20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?compare_commands@Modules@@YA_NABUCommand@1@0@Z");
		// Modules::Command const &rhs;

		return (lhs.Name <=> rhs.Name) < 0;
	}
}


namespace Modules
{
	std::string CommandMap::GenerateHelpText(std::string moduleFilter) // 0x109498B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateHelpText@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V34@@Z");
		// static ...; // 0x10949D3F
		// static ...; // 0x10949D35
		// static ...; // 0x10949D2A
		// static ...; // 0x10949D21
		// static ...; // 0x10949D1D
		// static ...; // 0x10949D14
		// static ...; // 0x10949CC0
		// static ...; // 0x10949CB8
		// Modules::CommandMap *const this;
		// std::string moduleFilter;
		// std::stringstream ss;
		// std::stringstream hasParent;
		// std::deque<Modules::Command> tempCommands;
			// std::deque<Modules::Command> &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
				// Modules::Command cmd;
					// std::string helpText;

		std::deque<Modules::Command> tempCommands = Commands;
		std::sort(tempCommands.begin(), tempCommands.end(), compare_commands);
		std::stringstream ss;
		std::stringstream hasParent;
		for (auto cmd : tempCommands)
		{
			if ((cmd.Flags & eCommandFlagsHidden) || (cmd.Flags & eCommandFlagsInternal))
				continue;
			if (!moduleFilter.empty() && (cmd.ModuleName.empty() || _stricmp(cmd.ModuleName.c_str(), moduleFilter.c_str()) != 0))
				continue;
			std::string helpText = cmd.Name;
			if (cmd.Type != eCommandTypeCommand && !(cmd.Flags & eCommandFlagsOmitValueInList))
				helpText += " " + cmd.ValueString;
			helpText += " - " + cmd.Description;
			if (cmd.ModuleName.length() > 0)
				hasParent << helpText << std::endl;
			else
				ss << helpText << std::endl;
		}
		ss << hasParent.str();
		return ss.str();
	}
}


namespace Modules
{
	std::string CommandMap::SaveVariables() // 0x1094A750
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SaveVariables@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x1094AA04
		// static ...; // 0x1094A9F9
		// static ...; // 0x1094A9F0
		// static ...; // 0x1094A9CC
		// static ...; // 0x1094A9C4
		// Modules::CommandMap *const this;
		// std::stringstream ss;
			// std::deque<Modules::Command> &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
				// Modules::Command &cmd;

		std::stringstream ss;
		for (Modules::Command &cmd : Commands)
		{
			if (cmd.Type == eCommandTypeCommand || !(cmd.Flags & eCommandFlagsArchived) || (cmd.Flags & eCommandFlagsInternal))
				continue;
			if (cmd.IsDirty)
			{
				ss << cmd.Name << " \"" << cmd.DirtyValue << "\"" << std::endl;
				cmd.CommittedValue = cmd.DirtyValue;
				cmd.DirtyValue = "";
				cmd.IsDirty = false;
			}
			else
			{
				ss << cmd.Name << " \"" << cmd.CommittedValue << "\"" << std::endl;
			}
		}
		return ss.str();
	}
}


namespace Modules
{
	std::string CommandMap::SaveKeys() // 0x1094A480
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SaveKeys@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x1094A6B4
		// static ...; // 0x1094A6A9
		// static ...; // 0x1094A6A0
		// static ...; // 0x1094A69C
		// static ...; // 0x1094A66C
		// static ...; // 0x1094A664
		// Modules::CommandMap *const this;
		// std::stringstream ss;
			// std::deque<Modules::Command> &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
				// Modules::Command cmd;

		std::stringstream ss;
		for (Modules::Command cmd : Commands)
		{
			if (cmd.Type == eCommandTypeCommand || !(cmd.Flags & eCommandFlagsWriteToKeys) || (cmd.Flags & eCommandFlagsInternal))
				continue;
			ss << cmd.Name << " \"" << cmd.ValueString << "\"" << std::endl;
		}
		return ss.str();
	}
}


namespace Modules
{
	std::string CommandMap::ExecuteCommands(std::string &commands, bool isUserInput, bool stopOnFirstError) // 0x109486F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteCommands@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@_N1@Z");
		// Modules::CommandMap *const this;
		// std::string &commands;
		// bool isUserInput;
		// bool stopOnFirstError;
		// std::shared_ptr<Modules::CommandScript> script;

		std::shared_ptr<Modules::CommandScript> script = std::make_shared<Modules::CommandScript>(std::make_unique<std::stringstream>(commands), isUserInput, stopOnFirstError);
		script->Execute();
		if (script->IsFinished())
			return script->HasError() ? script->GetErrorMessage() : "";
		scriptStack.PushScript(script);
		return "";
	}
}


namespace Modules
{
	std::string CommandMap::ExecuteQueue() // 0x10948A20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteQueue@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x10948C18
		// static ...; // 0x10948C14
		// static ...; // 0x10948BFC
		// static ...; // 0x10948BF4
		// Modules::CommandMap *const this;
		// std::stringstream ss;
			// std::vector<std::string> &<range>$L0;
			// std::string *<begin>$L0;
			// std::string *<end>$L0;
				// std::string cmd;

		std::stringstream ss;
		for (std::string cmd : queuedCommands)
			ss << ExecuteCommand(cmd, true) << std::endl;
		queuedCommands.clear();
		return ss.str();
	}

	void CommandMap::NotifyVariableUpdated(Modules::Command const *command) // 0x1094A210
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyVariableUpdated@CommandMap@Modules@@QAEXPBUCommand@2@@Z");
		// Modules::Command const *command;
			// std::vector<std::function<void __cdecl(Modules::Command const *)> > &<range>$L0;
			// std::function<void __cdecl(Modules::Command const *)> *<begin>$L0;
			// std::function<void __cdecl(Modules::Command const *)> *<end>$L0;
				// std::function<void __cdecl(Modules::Command const *)> &callback;

		for (auto &&callback : variableUpdateCallbacks)
			callback(command);
	}

	void CommandMap::OnVariableUpdate(std::function<void __cdecl(Modules::Command const *)> callback) // 0x1094A2B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnVariableUpdate@CommandMap@Modules@@QAEXV?$function@$$A6AXPBUCommand@Modules@@@Z@std@@@Z");
		// std::function<void __cdecl(Modules::Command const *)> callback;

		variableUpdateCallbacks.push_back(callback);
	}

	void CommandMap::CommitDirtyVariables() // 0x10946AE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CommitDirtyVariables@CommandMap@Modules@@QAEXXZ");
		// static ...; // 0x10946C01
		// static ...; // 0x10946BF8
		// static ...; // 0x10946BE0
		// static ...; // 0x10946BD8
		// Modules::CommandMap *const this;
			// std::deque<Modules::Command> &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
				// Modules::Command &cmd;

		for (auto &cmd : Commands)
		{
			if (cmd.Type == 0 || !(cmd.Flags & 4) || (cmd.Flags & 0x100))
				continue;
			if (cmd.IsDirty)
			{
				cmd.IsDirty = false;
				cmd.CommittedValue = cmd.DirtyValue;
				cmd.DirtyValue = "";
			}
		}
	}

	void CommandMap::Update() // 0x1094B9A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CommandMap@Modules@@QAEXXZ");
		// Modules::CommandMap *const this;

		scriptStack.Update();
	}
}

/* ---------- private code */
