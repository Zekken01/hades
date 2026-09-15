/* ---------- headers */

#include "Modules/ModuleInput.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/input/input.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Blam
{
	namespace Input
	{
		enum GameAction : unsigned char;
		enum KeyCode : unsigned short;
		struct BindingsTable;
		struct ConfigurableAction;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleInput;
}
namespace hades_file_local
{
	struct CommandBinding;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

//enum CommandBind::__l2::s_state
//{
//	KEYNAME_PART = 0,
//	COMMAND_HOLD_PART,
//	COMMAND_PART,
//};

/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct CommandBinding
	{
		std::vector<std::string> command; // 0x0
		bool isHold; // 0x10
		bool active; // 0x11
		CommandBinding(CommandBinding &); /* compiler_generated() */
		CommandBinding(CommandBinding const &); /* compiler_generated() */
		CommandBinding(); /* compiler_generated() */
		~CommandBinding() = default;
		CommandBinding &operator=(CommandBinding &); /* compiler_generated() */
		CommandBinding &operator=(CommandBinding const &); /* compiler_generated() */
		unsigned char __pad0[2]; // 0x12
	};
	#pragma pack(pop)
	static_assert(sizeof(CommandBinding) == 20, "Invalid CommandBinding size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches { namespace Input { extern void InvalidateBindings(); } }  // hades: added for 0x109D39A0

namespace Patches { namespace Input { void SetKeyboardSettingsMenu(const std::vector<Blam::Input::ConfigurableAction> &, const std::vector<Blam::Input::ConfigurableAction> &); } }  // hades: added for 0X109CD830

namespace Blam::Input { unsigned char GetKeyTicks(KeyCode key, InputType type); }  // hades: added for 0X109D2850

void CopyBinding(Blam::Input::GameAction sourceAction, Blam::Input::GameAction destAction);
void LoadDefaultBindings();
__int32 GetDefaultSettingsKey(__int32 action, Blam::Input::KeyCode *keys, Blam::Input::MouseButton *mouseButtons);
void PopulateDefaultKeys(std::vector<Blam::Input::ConfigurableAction> *actions);
void BuildSettingsMenu();
bool VariableInputRawInputUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandBind(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool IsModifierKeyDown();
bool IsModifierKey(Blam::Input::KeyCode code);
void KeyboardUpdated();
bool ParseKeyOrMouseButton(std::string const &name, Blam::Input::KeyCode *resultKey, Blam::Input::MouseButton *resultMouse);
bool ParseControllerButton(std::string const &name, Blam::Input::ControllerButton *result);
bool CommandBindControllerAction(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandBindKeyboardAction(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableControllerSensitivityXUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableControllerSensitivityYUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableControllerStickLayoutUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDumpBindingsJson(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandFindKeybdBinding(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDumpBindings(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandResetBindings(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool TryParseFloat(char const *str, float *value);
bool CommandControllerVibrationTest(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetMouseWheelEventTime(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::vector<Blam::Input::ConfigurableAction> vehicleControls; // 0x12454EE8
	extern std::vector<Blam::Input::ConfigurableAction> infantryControls; // 0x12454EF8
	extern Utils::NameValueTable<enum Blam::Input::KeyCode> keyCodes; // 0x12454F08
	extern Utils::NameValueTable<enum Blam::Input::GameAction> gameActions; // 0x12454F90
	extern Utils::NameValueTable<enum Blam::Input::MouseButton> mouseButtons; // 0x12455018
	extern "C" Utils::NameValueTable<enum Blam::Input::ControllerButton> controllerButtons; // 0x124550A0
	CommandBinding commandBindings[109]; // 0x12455128
	extern "C" Blam::Input::BindingsTable bindings; // 0x124559B0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	extern ModuleInput* _sub_109C4B60(Modules::ModuleInput *const);
	ModuleInput::ModuleInput() : ModuleBase(todo_result<std::string>()) // 0x109C4B60
	{
		mangled_x86(MANGLED_TODO, "??0ModuleInput@Modules@@QAE@XZ");
		// Modules::ModuleInput *const this;
		todo("implement");
		_sub_109C4B60(this);
	}
}

namespace Blam
{
	namespace Input
	{
		extern BindingsTable *_sub_109D23F0();
	}
}

namespace Modules
{
	Blam::Input::BindingsTable *ModuleInput::GetBindings() // 0x109D23F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetBindings@ModuleInput@Modules@@SAPAUBindingsTable@Input@Blam@@XZ");
		// procedure flags: nofpo

		return &bindings;
	}

	void ModuleInput::UpdateBindings() // 0x109D39A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateBindings@ModuleInput@Modules@@SAXXZ");
		// procedure flags: nofpo

		CopyBinding(Blam::Input::eGameActionUse, Blam::Input::eGameActionVehicleExit);
		Blam::Input::SetBindings(0, bindings);
		Patches::Input::InvalidateBindings();
	}
}

extern std::string _sub_109D0560(Modules::ModuleInput const *const);
namespace Modules
{
	std::string ModuleInput::ExportBindings() const // 0x109D0560
	{
		mangled_x86(MANGLED_TODO, "?ExportBindings@ModuleInput@Modules@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x109D1086
		// static ...; // 0x109D107B
		// static ...; // 0x109D1072
		// static ...; // 0x109D1067
		// static ...; // 0x109D105C
		// static ...; // 0x109D1053
		// static ...; // 0x109D1047
		// static ...; // 0x109D1039
		// static ...; // 0x109D1030
		// static ...; // 0x109D102B
		// static ...; // 0x109D1024
		// static ...; // 0x109D101C
		// static ...; // 0x109D0F8C
		// static ...; // 0x109D0F84
		// Modules::ModuleInput const *const this;
		// std::string result;
		{
			// Utils::NameValueTable<enum Blam::Input::GameAction> &<range>$L0;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::string,enum Blam::Input::GameAction> > > > <begin>$L0;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::string,enum Blam::Input::GameAction> > > > <end>$L0;
			{
				// std::pair<std::string,enum Blam::Input::GameAction> const &action;
				{
					// Blam::Input::ControllerButton button;
					// std::string buttonName;
				}
			}
		}
		{
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::string,enum Blam::Input::GameAction> > > > <end>$L1;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::string,enum Blam::Input::GameAction> > > > <begin>$L1;
			// Utils::NameValueTable<enum Blam::Input::GameAction> &<range>$L1;
			{
				{
					// std::string primaryName;
					// std::string secondaryName;
					// Blam::Input::KeyCode primaryKey;
					// Blam::Input::MouseButton primaryMouse;
					// Blam::Input::KeyCode secondaryKey;
					// Blam::Input::MouseButton secondaryMouse;
				}
			}
		}
		{
			// __int32 i;
			{
				// CommandBinding *const binding;
				// std::string line;
				// std::string prefix;
				// std::string key_name;
				{
					// std::string *<end>$L2;
					// std::vector<std::string> &<range>$L2;
					// std::string *<begin>$L2;
					{
						// std::string command;
					}
				}
			}
		}
		todo("implement");
		std::string __result = _sub_109D0560((Modules::ModuleInput const *)this);
		return __result;
	}

	_extern bool _sub_109D2480(Modules::ModuleInput *const, std::string);
	bool ModuleInput::IsCommandBound(std::string command) // 0x109D2480
	{
		mangled_x86(MANGLED_TODO, "?IsCommandBound@ModuleInput@Modules@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x109D2724
		// static ...; // 0x109D271C
		// Modules::ModuleInput *const this;
		// std::string command;
		{
			// __int32 i;
			{
				// CommandBinding *const binding;
				// std::string bound_command;
			}
		}
		todo("implement");
		bool __result = _sub_109D2480(this, command);
		return __result;
	}
}

/* ---------- private code */

void CopyBinding(Blam::Input::GameAction sourceAction, Blam::Input::GameAction destAction) // 0x109D04A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CopyBinding@@YAXW4GameAction@Input@Blam@@0@Z");
	// `anonymous-namespace'::CopyBinding
	// Blam::Input::GameAction destAction;

	bindings.ControllerButtons[(unsigned char)destAction] = bindings.ControllerButtons[(unsigned char)sourceAction];
	bindings.ControllerHoldButtons[(unsigned char)destAction] = bindings.ControllerHoldButtons[(unsigned char)sourceAction];
	bindings.PrimaryKeys[(unsigned char)destAction] = bindings.PrimaryKeys[(unsigned char)sourceAction];
	bindings.SecondaryKeys[(unsigned char)destAction] = bindings.SecondaryKeys[(unsigned char)sourceAction];
	bindings.PrimaryMouseButtons[(unsigned char)destAction] = bindings.PrimaryMouseButtons[(unsigned char)sourceAction];
	bindings.SecondaryMouseButtons[(unsigned char)destAction] = bindings.SecondaryMouseButtons[(unsigned char)sourceAction];
}

_extern void _sub_109D2C10();
void LoadDefaultBindings() // 0x109D2C10
{
	// `anonymous-namespace'::LoadDefaultBindings
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	{
	}
	todo("implement");
	_sub_109D2C10();
}

__int32 GetDefaultSettingsKey(__int32 action, Blam::Input::KeyCode *keys, Blam::Input::MouseButton *mouseButtons) // 0x109D2410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDefaultSettingsKey@@YAHHPAW4KeyCode@Input@Blam@@PAW4MouseButton@23@@Z");
	// `anonymous-namespace'::GetDefaultSettingsKey
	// Blam::Input::MouseButton *mouseButtons;
	// Blam::Input::KeyCode primaryKey;
	// Blam::Input::MouseButton mouseButton;

	Blam::Input::KeyCode primaryKey = keys[action];
	if (primaryKey != Blam::Input::eKeyCode_None)
		return primaryKey;
	Blam::Input::MouseButton mouseButton = mouseButtons[action];
	if ((unsigned char)mouseButton != (unsigned char)Blam::Input::eMouseButton_None)
		return ((unsigned char)mouseButton + 1) << 8;
	return -1;
}

void PopulateDefaultKeys(std::vector<Blam::Input::ConfigurableAction> *actions) // 0x109D3810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PopulateDefaultKeys@@YAXPAV?$vector@UConfigurableAction@Input@Blam@@V?$allocator@UConfigurableAction@Input@Blam@@@std@@@std@@@Z");
	// `anonymous-namespace'::PopulateDefaultKeys
	// std::vector<Blam::Input::ConfigurableAction> *actions;
		// std::vector<Blam::Input::ConfigurableAction> &<range>$L0;
		// Blam::Input::ConfigurableAction *<begin>$L0;
		// Blam::Input::ConfigurableAction *<end>$L0;
			// Blam::Input::ConfigurableAction &configAction;

	for (auto &configAction : *actions)
	{
		configAction.DefaultPrimaryKey = GetDefaultSettingsKey(configAction.Action, bindings.PrimaryKeys, bindings.PrimaryMouseButtons);
		configAction.DefaultSecondaryKey = GetDefaultSettingsKey(configAction.Action, bindings.SecondaryKeys, bindings.SecondaryMouseButtons);
	}
}

void BuildSettingsMenu() // 0x109CD830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildSettingsMenu@@YAXXZ");
	// `anonymous-namespace'::BuildSettingsMenu
	// procedure flags: nofpo

	PopulateDefaultKeys(&infantryControls);
	PopulateDefaultKeys(&vehicleControls);
	Patches::Input::SetKeyboardSettingsMenu(infantryControls, vehicleControls);
}

bool VariableInputRawInputUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109D3C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableInputRawInputUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableInputRawInputUpdate
	// static ...; // 0x109D3D60
	// static ...; // 0x109D3D58
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool statusBool;
	// std::string status;
	// unsigned long value;

	unsigned long value = Modules::ModuleInput::Instance().VarInputRawInput->ValueInt;

	std::string status = "disabled.";
	bool statusBool = value != 0;
	if (statusBool)
		status = "enabled.";

	returnInfo = "Raw input " + status;
	return true;
}

bool CommandBind(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CD8A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandBind@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandBind
	// static ...; // 0x109CE21F
	// static ...; // 0x109CE217
	// static ...; // 0x109CE20F
	// static ...; // 0x109CE20C
	// static ...; // 0x109CE204
	// static ...; // 0x109CE1BC
	// static ...; // 0x109CE1B4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// constexpr CommandBind::__l2::s_state KEYNAME_PART; // constant == 0
	// constexpr CommandBind::__l2::s_state COMMAND_PART; // constant == 2
	// bool isHold;
	// CommandBinding *binding;
	// CommandBind::__l2::s_state state;
	// std::string const &rawArguments;
	// std::string keyName;
	// std::string command;
	// Blam::Input::KeyCode keyCode;
	// std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > > partStart;
	// constexpr CommandBind::__l2::s_state COMMAND_HOLD_PART; // constant == 1
		// std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > > it;
			// bool isEnd;
			// char ch;
				// std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > > partEnd;

	if (Arguments.size() < 1)
	{
		returnInfo =  "Usage: Bind <key> [[+]command] [arguments]\n";
		returnInfo += "If the command starts with a +, then it will be ";
		returnInfo += "passed an argument of 1 on key down and 0 on key ";
		returnInfo += "up. Omit the command to unbind the key.";
		return false;
	}

	const auto& rawArguments = Arguments[0];
	auto partStart = rawArguments.begin();

	std::string keyName, command;
	KeyCode keyCode;
	bool isHold = false;

	enum { KEYNAME_PART, COMMAND_HOLD_PART, COMMAND_PART, } state = KEYNAME_PART;

	for (auto it = rawArguments.begin(); it != rawArguments.end(); ++it)
	{
		auto isEnd = it == rawArguments.end() - 1;
		auto ch = *it;

		switch (state)
		{
		case KEYNAME_PART:
			if (ch == ' ' || isEnd)
			{
				keyName = std::string(partStart, isEnd ? it + 1 : it);
				if (keyName.length() == 0 || !keyCodes.FindValueIgnoreCase(keyName, &keyCode))
				{
					returnInfo = "Unrecognized key name: " + keyName;
					return false;
				}
				state = COMMAND_HOLD_PART;
				partStart = it + 1;
				break;
			}
			break;
		case COMMAND_HOLD_PART:
			partStart = it--;
			isHold = ch == '+';
			if (isHold)
				partStart++;
			state = COMMAND_PART;
			break;
		case COMMAND_PART:
			if (ch == ' ' || isEnd)
			{
				auto partEnd = isEnd ? it + 1 : it;
				command = std::string(partStart, partEnd);
				partStart = it + 1;
				it = rawArguments.end() - 1;
			}
			break;
		}
	}

	auto binding = &commandBindings[keyCode];

	// If no command was specified, unset the binding
	if (command.length() == 0)
	{
		binding->command.clear();
		returnInfo = "Binding cleared.";
		return true;
	}

	// Set the binding
	binding->isHold = isHold;
	binding->command.clear();
	binding->command.push_back(command);
	binding->command.push_back(std::string(partStart, rawArguments.end()));

	returnInfo = "Binding set.";
	return true;
}

bool IsModifierKeyDown() // 0x109D2850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsModifierKeyDown@@YA_NXZ");
	// `anonymous-namespace'::IsModifierKeyDown
	// procedure flags: nofpo

	return Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeCtrl, Blam::Input::eInputTypeSpecial) > 0
		|| Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeAlt, Blam::Input::eInputTypeSpecial) > 0
		|| Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeShift, Blam::Input::eInputTypeSpecial) > 0;
}

bool IsModifierKey(Blam::Input::KeyCode code) // 0x109D27F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsModifierKey@@YA_NW4KeyCode@Input@Blam@@@Z");
	// `anonymous-namespace'::IsModifierKey
	// Blam::Input::KeyCode code;

	return code == Blam::Input::eKeyCodeCtrl || code == Blam::Input::eKeyCodeAlt || code == Blam::Input::eKeyCodeShift;
}

_extern void _sub_109D2900();
void KeyboardUpdated() // 0x109D2900
{
	// `anonymous-namespace'::KeyboardUpdated
	// procedure flags: nofpo
	// static ...; // 0x109D2B6B
	// static ...; // 0x109D2B64
	// static ...; // 0x109D2B4C
	// static ...; // 0x109D2B44
	{
		// __int32 i;
		{
			// unsigned char keyTicks;
			// CommandBinding *const binding;
			// std::vector<std::string> command;
			// Blam::Input::KeyCode keyCode;
			// std::string result;
		}
	}
	todo("implement");
	_sub_109D2900();
}

// mangled_x86(MANGLED_DEFAULT, "??0CommandBinding@hades_file_local@@QAE@XZ"); no body to assert in
_inline CommandBinding::CommandBinding() = default; // 0x109C4B10

bool ParseKeyOrMouseButton(std::string const &name, Blam::Input::KeyCode *resultKey, Blam::Input::MouseButton *resultMouse) // 0x109D36C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ParseKeyOrMouseButton@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAW4KeyCode@Input@Blam@@PAW4MouseButton@45@@Z");
	// `anonymous-namespace'::ParseKeyOrMouseButton
	// Blam::Input::MouseButton *resultMouse;

	*resultKey = eKeyCode_None;
	*resultMouse = eMouseButton_None;
	if (Utils::String::ToLower(name) == "none")
		return true;
	if (keyCodes.FindValueIgnoreCase(name, resultKey))
		return true;
	return mouseButtons.FindValueIgnoreCase(name, resultMouse);
}

bool ParseControllerButton(std::string const &name, Blam::Input::ControllerButton *result) // 0x109D35A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ParseControllerButton@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAW4ControllerButton@Input@Blam@@@Z");
	// `anonymous-namespace'::ParseControllerButton
	// Blam::Input::ControllerButton *result;

	*result = eControllerButton_None;
	if (Utils::String::ToLower(name) == "none")
		return true;
	return controllerButtons.FindValueIgnoreCase(name, result);
}

bool CommandBindControllerAction(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CE4A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandBindControllerAction@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandBindControllerAction
	// static ...; // 0x109CE74E
	// static ...; // 0x109CE747
	// static ...; // 0x109CE73C
	// static ...; // 0x109CE70C
	// static ...; // 0x109CE704
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Input::GameAction action;
	// Blam::Input::ControllerButton button;
	// std::string actionName;
		// std::string buttonName;

	if (Arguments.size() < 1 || Arguments.size() > 2)
		return false;

	// Parse the action name
	auto actionName = Arguments[0];
	GameAction action;
	if (!gameActions.FindValueIgnoreCase(actionName, &action))
	{
		returnInfo = "Unrecognized action name: " + actionName;
		return false;
	}
	if (action >= eGameAction_ControllerCount)
	{
		returnInfo = "Movement actions cannot be bound to controller buttons.";
		return false;
	}

	// If a button name was passed, parse it
	auto button = eControllerButton_None;
	if (Arguments.size() > 1)
	{
		auto buttonName = Arguments[1];
		if (!ParseControllerButton(buttonName, &button))
		{
			returnInfo = "Unrecognized button name: " + buttonName;
			return false;
		}
	}

	// Update the bindings table!
	bindings.ControllerButtons[action] = button;

	Modules::ModuleInput::UpdateBindings();
	if (button != eKeyCode_None)
		returnInfo = "Action binding set.";
	else
		returnInfo = "Action binding cleared.";
	return true;
}

_extern bool _sub_109CE810(std::vector<std::string> const &, std::string &);
bool CommandBindKeyboardAction(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CE810
{
	// `anonymous-namespace'::CommandBindKeyboardAction
	// static ...; // 0x109CECF0
	// static ...; // 0x109CECE5
	// static ...; // 0x109CECD8
	// static ...; // 0x109CECC9
	// static ...; // 0x109CECBC
	// static ...; // 0x109CECAD
	// static ...; // 0x109CEC9C
	// static ...; // 0x109CEC3C
	// static ...; // 0x109CEC34
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Input::GameAction action;
	// Blam::Input::KeyCode primaryKey;
	// Blam::Input::MouseButton primaryMouse;
	// std::string actionName;
	// Blam::Input::KeyCode secondaryKey;
	// Blam::Input::MouseButton secondaryMouse;
	{
		// std::string primaryKeyName;
	}
	{
		// std::string secondaryKeyName;
	}
	todo("implement");
	bool __result = _sub_109CE810(Arguments, returnInfo);
	return __result;
}

bool VariableControllerSensitivityXUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109D3A00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableControllerSensitivityXUpdated@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableControllerSensitivityXUpdated
	// static ...; // 0x109D3A94
	// static ...; // 0x109D3A8C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// float newSensitivity;

	auto newSensitivity = Modules::ModuleInput::Instance().VarControllerSensitivityX->ValueFloat;
	bindings.ControllerSensitivityX = std::max(1.f, newSensitivity);
	Modules::ModuleInput::UpdateBindings();
	return true;
}

bool VariableControllerSensitivityYUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109D3AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableControllerSensitivityYUpdated@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableControllerSensitivityYUpdated
	// static ...; // 0x109D3B74
	// static ...; // 0x109D3B6C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// float newSensitivity;

	auto newSensitivity = Modules::ModuleInput::Instance().VarControllerSensitivityY->ValueFloat;
	bindings.ControllerSensitivityY = std::max(1.f, newSensitivity);
	Modules::ModuleInput::UpdateBindings();
	return true;
}

bool VariableControllerStickLayoutUpdated(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109D3BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableControllerStickLayoutUpdated@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableControllerStickLayoutUpdated
	// std::string &returnInfo;
	// unsigned long layout;

	auto layout = Modules::ModuleInput::Instance().VarControllerStickLayout->ValueInt;
	bindings.JoystickLayout = layout;
	Modules::ModuleInput::UpdateBindings();
	return true;
}

bool CommandDumpBindingsJson(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CF820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDumpBindingsJson@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandDumpBindingsJson
	// static ...; // 0x109CFD74
	// static ...; // 0x109CFD6D
	// static ...; // 0x109CFD67
	// static ...; // 0x109CFD5C
	// static ...; // 0x109CFD20
	// static ...; // 0x109CFD18
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// Blam::Input::BindingsTable currentBindings;
		// __int32 i;
			// std::string names[6];
			// std::string actionName;

	returnInfo = "";
	BindingsTable currentBindings;
	GetBindings(0, &currentBindings);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	writer.StartArray();
	for (auto i = 0; i < eGameAction_KeyboardMouseCount; i++)
	{
		std::string names[6] = { "none", "n/a", "none", "none", "none", "none" };
		if (i < eGameAction_ControllerCount)
		{
			controllerButtons.FindName(currentBindings.ControllerButtons[i], &names[0]);
			names[1] = currentBindings.ControllerHoldButtons[i] ? "true" : "false";
		}
		keyCodes.FindName(currentBindings.PrimaryKeys[i], &names[2]);
		keyCodes.FindName(currentBindings.SecondaryKeys[i], &names[3]);
		mouseButtons.FindName(currentBindings.PrimaryMouseButtons[i], &names[4]);
		mouseButtons.FindName(currentBindings.SecondaryMouseButtons[i], &names[5]);
		writer.StartObject();

		std::string actionName;
		if (gameActions.FindName(static_cast<GameAction>(i), &actionName))
		{
			writer.Key("actionName");
			writer.String(actionName.c_str());
		}
		else{
			writer.Key("actionName");
			writer.String(std::to_string(i).c_str());
		}
		writer.Key("controllerButton");
		writer.String(names[0].c_str());

		writer.Key("controllerHoldButton");
		writer.String(names[1].c_str());

		writer.Key("primaryKey");
		writer.String(names[2].c_str());

		writer.Key("secondaryKey");
		writer.String(names[3].c_str());

		writer.Key("primaryMouseButton");
		writer.String(names[4].c_str());

		writer.Key("secondaryMouseButton");
		writer.String(names[5].c_str());
		writer.EndObject();

	}
	writer.EndArray();
	returnInfo += buffer.GetString();

	return true;
}

bool CommandFindKeybdBinding(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CFEF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandFindKeybdBinding@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandFindKeybdBinding
	// static ...; // 0x109D0258
	// static ...; // 0x109D0251
	// static ...; // 0x109D0244
	// static ...; // 0x109D0240
	// static ...; // 0x109D0204
	// static ...; // 0x109D01FC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string search_for;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
		// __int32 i;
			// __int32 k;
				// std::string command_part;
					// std::string key;

	if (Arguments.size() < 1)
	{
		returnInfo = "Not enough arguments";
		return false;
	}
	std::string search_for = Arguments[0];
	std::transform(search_for.begin(), search_for.end(), search_for.begin(), ::tolower);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

	writer.StartArray();
	for (int i = 0; i < eKeyCode_Count; i++)
	{
		for (int k = 0; k < commandBindings[i].command.size(); k++)
		{
			std::string command_part = commandBindings[i].command[k];
			std::transform(command_part.begin(), command_part.end(), command_part.begin(), ::tolower);
			if (command_part.compare(search_for) == 0)
			{
				std::string key;
				keyCodes.FindName((Blam::Input::KeyCode)i, &key);
				writer.String(key.c_str());
			}
		}
	}
	writer.EndArray();
	returnInfo = buffer.GetString();
	return true;
}

bool CommandDumpBindings(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CEF20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDumpBindings@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandDumpBindings
	// static ...; // 0x109CF637
	// static ...; // 0x109CF62C
	// static ...; // 0x109CF608
	// static ...; // 0x109CF600
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Input::BindingsTable currentBindings;
		// __int32 i;
			// std::string names[6];
			// std::string actionName;

	returnInfo = "";
	BindingsTable currentBindings;
	GetBindings(0, &currentBindings);
	for (auto i = 0; i < eGameAction_KeyboardMouseCount; i++)
	{
		std::string names[6] = { "none", "n/a", "none", "none", "none", "none" };
		if (i < eGameAction_ControllerCount)
		{
			controllerButtons.FindName(currentBindings.ControllerButtons[i], &names[0]);
			names[1] = currentBindings.ControllerHoldButtons[i] ? "true" : "false";
		}
		keyCodes.FindName(currentBindings.PrimaryKeys[i], &names[2]);
		keyCodes.FindName(currentBindings.SecondaryKeys[i], &names[3]);
		mouseButtons.FindName(currentBindings.PrimaryMouseButtons[i], &names[4]);
		mouseButtons.FindName(currentBindings.SecondaryMouseButtons[i], &names[5]);
		returnInfo += std::to_string(i);
		std::string actionName;
		if (gameActions.FindName(static_cast<GameAction>(i), &actionName))
			returnInfo += " (" + actionName + ")";
		returnInfo += ": " + names[0] + " " + names[1] + " " + names[2] + " " + names[3] + " " + names[4] + " " + names[5] + "\n";
	}
	return true;
}

bool CommandResetBindings(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109D0350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandResetBindings@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandResetBindings
	// std::string &returnInfo;

	LoadDefaultBindings();
	returnInfo = "Default bindings restored";
	return true;
}

bool TryParseFloat(char const *str, float *value) // 0x109D38E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryParseFloat@@YA_NPBDPAM@Z");
	// `anonymous-namespace'::TryParseFloat
	// static ...; // 0x109D3964
	// static ...; // 0x109D395C
	// char const *str;
	// float *value;
	// char *endp;

	char *endp;

	*value = (float)strtod(str, &endp);
	return endp != str;
}

_extern bool _sub_109CEE40(std::vector<std::string> const &, std::string &);
bool CommandControllerVibrationTest(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CEE40
{
	// `anonymous-namespace'::CommandControllerVibrationTest
	// static ...; // 0x109CEED4
	// static ...; // 0x109CEECC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// float duration;
	todo("implement");
	bool __result = _sub_109CEE40(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109D03A0(std::vector<std::string> const &, std::string &);
bool CommandSetMouseWheelEventTime(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109D03A0
{
	// `anonymous-namespace'::CommandSetMouseWheelEventTime
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_109D03A0(Arguments, returnInfo);
	return __result;
}


/* ---------- explicit instantiations */
template Utils::NameValueTable<enum Blam::Input::ControllerButton>::~NameValueTable();
template Utils::NameValueTable<enum Blam::Input::GameAction>::~NameValueTable();
template Utils::NameValueTable<enum Blam::Input::KeyCode>::~NameValueTable();
template Utils::NameValueTable<enum Blam::Input::MouseButton>::~NameValueTable();
