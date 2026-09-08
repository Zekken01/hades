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
	extern Modules::CommandScriptStack scriptStack; // 0x1240DA14
}

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern Command* _sub_10944CB0(Modules::Command *const);
	Command::Command() // 0x10944CB0
	{
		mangled_x86(MANGLED_TODO, "??0Command@Modules@@QAE@XZ");
		// Modules::Command *const this;
		todo("implement");
		_sub_10944CB0(this);
	}

	_inline CommandScriptStack::CommandScriptStack() // 0x10944F60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CommandScriptStack@Modules@@QAE@XZ");
		// Modules::CommandScriptStack *const this;

		compiler_generated();
	}
}

extern std::string _sub_10949150(Modules::Command *const);
namespace Modules
{
	std::string Command::GenerateHelpText() // 0x10949150
	{
		mangled_x86(MANGLED_TODO, "?GenerateHelpText@Command@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
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
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		{
			// std::string paramDescs;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > paramStream;
			{
				// std::vector<std::string,std::allocator<std::string> > &<range>$L0;
				// std::string *<begin>$L0;
				// std::string *<end>$L0;
				{
					// std::string arg;
					{
						// std::string argdesc;
						// unsigned __int32 nameEnd;
						// std::string argname;
					}
				}
			}
		}
		todo("implement");
		std::string __result = _sub_10949150(this);
		return __result;
	}

	_inline Command::~Command() // 0x10945510
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1Command@Modules@@QAE@XZ");
		// Modules::Command *const this;

		compiler_generated();
	}

	_inline CommandScript::~CommandScript() // 0x109455E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CommandScript@Modules@@QAE@XZ");
		// Modules::CommandScript *const this;

		compiler_generated();
	}

	_inline CommandScriptStack::~CommandScriptStack() // 0x10945660
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CommandScriptStack@Modules@@QAE@XZ");
		// Modules::CommandScriptStack *const this;

		compiler_generated();
	}

	extern Command &_sub_109456B0(Modules::Command *const, Modules::Command &);
	_inline Modules::Command &Command::operator=(Modules::Command &&__that) // 0x109456B0
	{
		mangled_x86(MANGLED_TODO, "??4Command@Modules@@QAEAAU01@$$QAU01@@Z");
		// Modules::Command &__that;
		compiler_generated();
		todo("implement");
		Modules::Command & __result = _sub_109456B0(this, __that);
		return __result;
	}

	_inline Command::Command(Modules::Command &&__that) // 0x109445D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0Command@Modules@@QAE@$$QAU01@@Z");
		// Modules::Command &__that;

		compiler_generated();
	}

	_inline Command::Command(Modules::Command const &__that) // 0x10944910
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0Command@Modules@@QAE@ABU01@@Z");
		// Modules::Command const &__that;

		compiler_generated();
	}

	extern Command *_sub_10948CA0(Modules::CommandMap *const, std::string const &);
	Modules::Command *CommandMap::FindCommand(std::string const &name) // 0x10948CA0
	{
		mangled_x86(MANGLED_TODO, "?FindCommand@CommandMap@Modules@@QAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10948E60
		// static ...; // 0x10948E58
		// Modules::CommandMap *const this;
		// std::string const &name;
		{
			// std::_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > it;
		}
		todo("implement");
		Modules::Command * __result = _sub_10948CA0(this, name);
		return __result;
	}

	extern Command *_sub_109469C0(Modules::CommandMap *const, Modules::Command);
	Modules::Command *CommandMap::AddCommand(Modules::Command command) // 0x109469C0
	{
		mangled_x86(MANGLED_TODO, "?AddCommand@CommandMap@Modules@@QAEPAUCommand@2@U32@@Z");
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_109469C0(this, command);
		return __result;
	}

	_extern void _sub_10948EF0(Modules::CommandMap *const);
	void CommandMap::FinishAddCommands() // 0x10948EF0
	{
		mangled_x86(MANGLED_TODO, "?FinishAddCommands@CommandMap@Modules@@QAEXXZ");
		// static ...; // 0x109490C4
		// static ...; // 0x109490B9
		// static ...; // 0x109490B0
		// static ...; // 0x109490A8
		// static ...; // 0x10949078
		// static ...; // 0x10949070
		// Modules::CommandMap *const this;
		// std::string previousValue;
		{
			// std::deque<Modules::Command,std::allocator<Modules::Command> > &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
			{
				// Modules::Command command;
			}
		}
		// function call : bool (*)(std::vector<std::string,std::allocator<std::string> > const &, std::string &)
		todo("implement");
		_sub_10948EF0(this);
	}
}

extern std::string _sub_10946DC0(Modules::CommandMap *const, std::vector<std::string,std::allocator<std::string> >, bool);
namespace Modules
{
	std::string CommandMap::ExecuteCommand(std::vector<std::string,std::allocator<std::string> > command, bool isUserInput) // 0x10946DC0
	{
		mangled_x86(MANGLED_TODO, "?ExecuteCommand@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@_N@Z");
		// static ...; // 0x10946FE4
		// static ...; // 0x10946FC0
		// static ...; // 0x10946FB8
		// Modules::CommandMap *const this;
		// std::vector<std::string,std::allocator<std::string> > command;
		// bool isUserInput;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > buff;
		// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::string> > > commandEnd;
		{
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::string> > > it;
		}
		todo("implement");
		std::string __result = _sub_10946DC0(this, command, isUserInput);
		return __result;
	}

	_extern bool _sub_10947090(Modules::CommandMap *const, std::string, bool, std::string *);
	bool CommandMap::ExecuteCommandWithStatus(std::string command, bool isUserInput, std::string *output) // 0x10947090
	{
		mangled_x86(MANGLED_TODO, "?ExecuteCommandWithStatus@CommandMap@Modules@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_NPAV34@@Z");
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
		// std::vector<std::string,std::allocator<std::string> > argsVect;
		// bool SkipHostCheck;
		{
			// Blam::Network::Session *session;
		}
		{
		}
		{
			// bool (*const game_options_is_valid)();
			// bool (*const game_engine_is_forge)();
		}
		{
			// __int32 i;
		}
		// function call : bool (*const)()
		// function call : bool (*const)()
		// function call : bool (*)(std::vector<std::string,std::allocator<std::string> > const &, std::string &)
		// function call : bool (*)(std::vector<std::string,std::allocator<std::string> > const &, std::string &)
		// function call : bool (*)(std::vector<std::string,std::allocator<std::string> > const &, std::string &)
		todo("implement");
		bool __result = _sub_10947090(this, command, isUserInput, output);
		return __result;
	}
}

extern std::string _sub_10949E80(Modules::Command *);
namespace Modules
{
	std::string GetDefaultValueString(Modules::Command *command) // 0x10949E80
	{
		mangled_x86(MANGLED_TODO, "?GetDefaultValueString@Modules@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUCommand@1@@Z");
		// Modules::Command *command;
		todo("implement");
		std::string __result = _sub_10949E80(command);
		return __result;
	}
}

extern VariableSetReturnValue _sub_1094A370(Modules::CommandMap *const, Modules::Command *, std::string &, bool);
namespace Modules
{
	VariableSetReturnValue CommandMap::ResetVariable(Modules::Command *command, std::string &previousValue, bool markDirty) // 0x1094A370
	{
		mangled_x86(MANGLED_TODO, "?ResetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@PAUCommand@2@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
		// bool markDirty;
		todo("implement");
		VariableSetReturnValue __result = _sub_1094A370(this, command, previousValue, markDirty);
		return __result;
	}
}

extern std::string _sub_10946C60(Modules::CommandMap *const, std::string, bool);
namespace Modules
{
	std::string CommandMap::ExecuteCommand(std::string command, bool isUserInput) // 0x10946C60
	{
		mangled_x86(MANGLED_TODO, "?ExecuteCommand@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V34@_N@Z");
		// static ...; // 0x10946D5C
		// Modules::CommandMap *const this;
		// std::string command;
		// bool isUserInput;
		// std::string output;
		todo("implement");
		std::string __result = _sub_10946C60(this, command, isUserInput);
		return __result;
	}

	_extern bool _sub_1094A100(Modules::CommandMap *const, std::string const &, unsigned long &);
	bool CommandMap::GetVariableInt(std::string const &name, unsigned long &value) // 0x1094A100
	{
		mangled_x86(MANGLED_TODO, "?GetVariableInt@CommandMap@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAK@Z");
		// unsigned long &value;
		// Modules::Command *command;
		todo("implement");
		bool __result = _sub_1094A100(this, name, value);
		return __result;
	}

	_extern bool _sub_1094A070(Modules::CommandMap *const, std::string const &, unsigned long long &);
	bool CommandMap::GetVariableInt64(std::string const &name, unsigned long long &value) // 0x1094A070
	{
		mangled_x86(MANGLED_TODO, "?GetVariableInt64@CommandMap@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AA_K@Z");
		// unsigned long long &value;
		// Modules::Command *command;
		todo("implement");
		bool __result = _sub_1094A070(this, name, value);
		return __result;
	}

	_extern bool _sub_10949FE0(Modules::CommandMap *const, std::string const &, float &);
	bool CommandMap::GetVariableFloat(std::string const &name, float &value) // 0x10949FE0
	{
		mangled_x86(MANGLED_TODO, "?GetVariableFloat@CommandMap@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAM@Z");
		// float &value;
		// Modules::Command *command;
		todo("implement");
		bool __result = _sub_10949FE0(this, name, value);
		return __result;
	}

	_extern bool _sub_1094A180(Modules::CommandMap *const, std::string const &, std::string &);
	bool CommandMap::GetVariableString(std::string const &name, std::string &value) // 0x1094A180
	{
		mangled_x86(MANGLED_TODO, "?GetVariableString@CommandMap@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &value;
		// Modules::Command *command;
		todo("implement");
		bool __result = _sub_1094A180(this, name, value);
		return __result;
	}
}

extern VariableSetReturnValue _sub_1094B130(Modules::CommandMap *const, std::string const &, std::string const &, bool);
namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable(std::string const &name, std::string const &value, bool markDirty) // 0x1094B130
	{
		mangled_x86(MANGLED_TODO, "?SetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0_N@Z");
		// Modules::CommandMap *const this;
		// std::string const &name;
		// std::string const &value;
		// bool markDirty;
		// std::string previousValue;
		todo("implement");
		VariableSetReturnValue __result = _sub_1094B130(this, name, value, markDirty);
		return __result;
	}
}

extern VariableSetReturnValue _sub_1094B0A0(Modules::CommandMap *const, std::string const &, std::string const &, std::string &, bool);
namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable(std::string const &name, std::string const &value, std::string &previousValue, bool markDirty) // 0x1094B0A0
	{
		mangled_x86(MANGLED_TODO, "?SetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0AAV45@_N@Z");
		// bool markDirty;
		// Modules::Command *command;
		todo("implement");
		VariableSetReturnValue __result = _sub_1094B0A0(this, name, value, previousValue, markDirty);
		return __result;
	}
}

extern VariableSetReturnValue _sub_1094B880(Modules::CommandMap *const, Modules::Command *, std::string const &, bool);
namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable(Modules::Command *command, std::string const &value, bool markDirty) // 0x1094B880
	{
		mangled_x86(MANGLED_TODO, "?SetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@PAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
		// Modules::CommandMap *const this;
		// Modules::Command *command;
		// std::string const &value;
		// bool markDirty;
		// std::string previousValue;
		todo("implement");
		VariableSetReturnValue __result = _sub_1094B880(this, command, value, markDirty);
		return __result;
	}
}

extern VariableSetReturnValue _sub_1094B250(Modules::CommandMap *const, Modules::Command *, std::string const &, std::string &, bool);
namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable(Modules::Command *command, std::string const &value, std::string &previousValue, bool markDirty) // 0x1094B250
	{
		mangled_x86(MANGLED_TODO, "?SetVariable@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@PAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV56@_N@Z");
	// $LN15:
	// $LN11:
	// $LN7:
	// $LN6:
		// Modules::CommandMap *const this;
		// Modules::Command *command;
		// std::string const &value;
		// std::string &previousValue;
		// bool markDirty;
		{
			// unsigned long newValue;
		}
		{
			// unsigned long long newValue;
		}
		{
			// float newValue;
		}
		todo("implement");
		VariableSetReturnValue __result = _sub_1094B250(this, command, value, previousValue, markDirty);
		return __result;
	}
}

extern VariableSetReturnValue _sub_1094AAC0(Modules::CommandMap *const, Modules::Command *, std::string const &, std::string &);
namespace Modules
{
	VariableSetReturnValue CommandMap::SetVariable2(Modules::Command *command, std::string const &value, std::string &previousValue) // 0x1094AAC0
	{
		mangled_x86(MANGLED_TODO, "?SetVariable2@CommandMap@Modules@@QAE?AW4VariableSetReturnValue@@PAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV56@@Z");
	// $LN14:
	// $LN10:
	// $LN6:
	// $LN5:
		// Modules::CommandMap *const this;
		// Modules::Command *command;
		// std::string const &value;
		// std::string &previousValue;
		{
			// unsigned long newValue;
		}
		{
			// unsigned long long newValue;
		}
		{
			// float newValue;
		}
		todo("implement");
		VariableSetReturnValue __result = _sub_1094AAC0(this, command, value, previousValue);
		return __result;
	}

	_extern bool _sub_1094DC20(Modules::Command const &, Modules::Command const &);
	bool compare_commands(Modules::Command const &lhs, Modules::Command const &rhs) // 0x1094DC20
	{
		mangled_x86(MANGLED_TODO, "?compare_commands@Modules@@YA_NABUCommand@1@0@Z");
		// Modules::Command const &rhs;
		todo("implement");
		bool __result = _sub_1094DC20(lhs, rhs);
		return __result;
	}
}

extern std::string _sub_109498B0(Modules::CommandMap *const, std::string);
namespace Modules
{
	std::string CommandMap::GenerateHelpText(std::string moduleFilter) // 0x109498B0
	{
		mangled_x86(MANGLED_TODO, "?GenerateHelpText@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V34@@Z");
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
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > hasParent;
		// std::deque<Modules::Command,std::allocator<Modules::Command> > tempCommands;
		{
			// std::deque<Modules::Command,std::allocator<Modules::Command> > &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
			{
				// Modules::Command cmd;
				{
					// std::string helpText;
				}
			}
		}
		todo("implement");
		std::string __result = _sub_109498B0(this, moduleFilter);
		return __result;
	}
}

extern std::string _sub_1094A750(Modules::CommandMap *const);
namespace Modules
{
	std::string CommandMap::SaveVariables() // 0x1094A750
	{
		mangled_x86(MANGLED_TODO, "?SaveVariables@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x1094AA04
		// static ...; // 0x1094A9F9
		// static ...; // 0x1094A9F0
		// static ...; // 0x1094A9CC
		// static ...; // 0x1094A9C4
		// Modules::CommandMap *const this;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		{
			// std::deque<Modules::Command,std::allocator<Modules::Command> > &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
			{
				// Modules::Command &cmd;
			}
		}
		todo("implement");
		std::string __result = _sub_1094A750(this);
		return __result;
	}
}

extern std::string _sub_1094A480(Modules::CommandMap *const);
namespace Modules
{
	std::string CommandMap::SaveKeys() // 0x1094A480
	{
		mangled_x86(MANGLED_TODO, "?SaveKeys@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x1094A6B4
		// static ...; // 0x1094A6A9
		// static ...; // 0x1094A6A0
		// static ...; // 0x1094A69C
		// static ...; // 0x1094A66C
		// static ...; // 0x1094A664
		// Modules::CommandMap *const this;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		{
			// std::deque<Modules::Command,std::allocator<Modules::Command> > &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
			{
				// Modules::Command cmd;
			}
		}
		todo("implement");
		std::string __result = _sub_1094A480(this);
		return __result;
	}
}

extern std::string _sub_109486F0(Modules::CommandMap *const, std::string &, bool, bool);
namespace Modules
{
	std::string CommandMap::ExecuteCommands(std::string &commands, bool isUserInput, bool stopOnFirstError) // 0x109486F0
	{
		mangled_x86(MANGLED_TODO, "?ExecuteCommands@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@_N1@Z");
		// Modules::CommandMap *const this;
		// std::string &commands;
		// bool isUserInput;
		// bool stopOnFirstError;
		// std::shared_ptr<Modules::CommandScript> script;
		todo("implement");
		std::string __result = _sub_109486F0(this, commands, isUserInput, stopOnFirstError);
		return __result;
	}
}

extern std::string _sub_10948A20(Modules::CommandMap *const);
namespace Modules
{
	std::string CommandMap::ExecuteQueue() // 0x10948A20
	{
		mangled_x86(MANGLED_TODO, "?ExecuteQueue@CommandMap@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x10948C18
		// static ...; // 0x10948C14
		// static ...; // 0x10948BFC
		// static ...; // 0x10948BF4
		// Modules::CommandMap *const this;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		{
			// std::vector<std::string,std::allocator<std::string> > &<range>$L0;
			// std::string *<begin>$L0;
			// std::string *<end>$L0;
			{
				// std::string cmd;
			}
		}
		todo("implement");
		std::string __result = _sub_10948A20(this);
		return __result;
	}

	_extern void _sub_1094A210(Modules::CommandMap *const, Modules::Command const *);
	void CommandMap::NotifyVariableUpdated(Modules::Command const *command) // 0x1094A210
	{
		mangled_x86(MANGLED_TODO, "?NotifyVariableUpdated@CommandMap@Modules@@QAEXPBUCommand@2@@Z");
		// Modules::Command const *command;
		{
			// std::vector<std::function<void __cdecl(Modules::Command const *)>,std::allocator<std::function<void __cdecl(Modules::Command const *)> > > &<range>$L0;
			// std::function<void __cdecl(Modules::Command const *)> *<begin>$L0;
			// std::function<void __cdecl(Modules::Command const *)> *<end>$L0;
			{
				// std::function<void __cdecl(Modules::Command const *)> &callback;
			}
		}
		todo("implement");
		_sub_1094A210(this, command);
	}

	_extern void _sub_1094A2B0(Modules::CommandMap *const, std::function<void __cdecl(Modules::Command const *)>);
	void CommandMap::OnVariableUpdate(std::function<void __cdecl(Modules::Command const *)> callback) // 0x1094A2B0
	{
		mangled_x86(MANGLED_TODO, "?OnVariableUpdate@CommandMap@Modules@@QAEXV?$function@$$A6AXPBUCommand@Modules@@@Z@std@@@Z");
		// std::function<void __cdecl(Modules::Command const *)> callback;
		todo("implement");
		_sub_1094A2B0(this, callback);
	}

	_extern void _sub_10946AE0(Modules::CommandMap *const);
	void CommandMap::CommitDirtyVariables() // 0x10946AE0
	{
		mangled_x86(MANGLED_TODO, "?CommitDirtyVariables@CommandMap@Modules@@QAEXXZ");
		// static ...; // 0x10946C01
		// static ...; // 0x10946BF8
		// static ...; // 0x10946BE0
		// static ...; // 0x10946BD8
		// Modules::CommandMap *const this;
		{
			// std::deque<Modules::Command,std::allocator<Modules::Command> > &<range>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
			// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
			{
				// Modules::Command &cmd;
			}
		}
		todo("implement");
		_sub_10946AE0(this);
	}

	_extern void _sub_1094B9A0(Modules::CommandMap *const);
	void CommandMap::Update() // 0x1094B9A0
	{
		mangled_x86(MANGLED_TODO, "?Update@CommandMap@Modules@@QAEXXZ");
		// Modules::CommandMap *const this;
		todo("implement");
		_sub_1094B9A0(this);
	}
}

/* ---------- private code */
