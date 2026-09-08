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
		std::vector<std::string,std::allocator<std::string> > command; // 0x0
		bool isHold; // 0x10
		bool active; // 0x11
		CommandBinding(CommandBinding &); /* compiler_generated() */
		CommandBinding(CommandBinding const &); /* compiler_generated() */
		CommandBinding(); /* compiler_generated() */
		~CommandBinding(); /* compiler_generated() */
		CommandBinding &operator=(CommandBinding &); /* compiler_generated() */
		CommandBinding &operator=(CommandBinding const &); /* compiler_generated() */
		unsigned char __pad0[2]; // 0x12
	};
	#pragma pack(pop)
	static_assert(sizeof(CommandBinding) == 20, "Invalid CommandBinding size");
}
using namespace hades_file_local;
/* ---------- prototypes */

void CopyBinding(Blam::Input::GameAction sourceAction, Blam::Input::GameAction destAction);
void LoadDefaultBindings();
__int32 GetDefaultSettingsKey(__int32 action, Blam::Input::KeyCode *keys, Blam::Input::MouseButton *mouseButtons);
void PopulateDefaultKeys(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > *actions);
void BuildSettingsMenu();
bool VariableInputRawInputUpdate(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool CommandBind(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool IsModifierKeyDown();
bool IsModifierKey(Blam::Input::KeyCode code);
void KeyboardUpdated();
bool ParseKeyOrMouseButton(std::string const &name, Blam::Input::KeyCode *resultKey, Blam::Input::MouseButton *resultMouse);
bool ParseControllerButton(std::string const &name, Blam::Input::ControllerButton *result);
bool CommandBindControllerAction(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool CommandBindKeyboardAction(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool VariableControllerSensitivityXUpdated(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool VariableControllerSensitivityYUpdated(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool VariableControllerStickLayoutUpdated(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool CommandDumpBindingsJson(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool CommandFindKeybdBinding(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool CommandDumpBindings(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool CommandResetBindings(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool TryParseFloat(char const *str, float *value);
bool CommandControllerVibrationTest(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);
bool CommandSetMouseWheelEventTime(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern Utils::NameValueTable<enum Blam::Input::ControllerButton> controllerButtons; // 0x124550A0
	extern Utils::NameValueTable<enum Blam::Input::KeyCode> keyCodes; // 0x12454F08
	extern Utils::NameValueTable<enum Blam::Input::MouseButton> mouseButtons; // 0x12455018
	extern Utils::NameValueTable<enum Blam::Input::GameAction> gameActions; // 0x12454F90
	extern std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > infantryControls; // 0x12454EF8
	extern std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > vehicleControls; // 0x12454EE8
	extern Blam::Input::BindingsTable bindings; // 0x124559B0
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
		mangled_x86(MANGLED_TODO, "?GetBindings@ModuleInput@Modules@@SAPAUBindingsTable@Input@Blam@@XZ");
		// procedure flags: nofpo
		todo("implement");
		Blam::Input::BindingsTable * __result = _sub_109D23F0();
		return __result;
	}

	_extern void _sub_109D39A0();
	void ModuleInput::UpdateBindings() // 0x109D39A0
	{
		mangled_x86(MANGLED_TODO, "?UpdateBindings@ModuleInput@Modules@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_109D39A0();
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
					// std::vector<std::string,std::allocator<std::string> > &<range>$L2;
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

_extern void _sub_109D04A0(Blam::Input::GameAction, Blam::Input::GameAction);
void CopyBinding(Blam::Input::GameAction sourceAction, Blam::Input::GameAction destAction) // 0x109D04A0
{
	// `anonymous-namespace'::CopyBinding
	// Blam::Input::GameAction destAction;
	todo("implement");
	_sub_109D04A0(sourceAction, destAction);
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

_extern __int32 _sub_109D2410(__int32, Blam::Input::KeyCode *, Blam::Input::MouseButton *);
__int32 GetDefaultSettingsKey(__int32 action, Blam::Input::KeyCode *keys, Blam::Input::MouseButton *mouseButtons) // 0x109D2410
{
	// `anonymous-namespace'::GetDefaultSettingsKey
	// Blam::Input::MouseButton *mouseButtons;
	// Blam::Input::KeyCode primaryKey;
	// Blam::Input::MouseButton mouseButton;
	todo("implement");
	__int32 __result = _sub_109D2410(action, keys, mouseButtons);
	return __result;
}

_extern void _sub_109D3810(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > *);
void PopulateDefaultKeys(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > *actions) // 0x109D3810
{
	// `anonymous-namespace'::PopulateDefaultKeys
	// std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > *actions;
	{
		// std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > &<range>$L0;
		// Blam::Input::ConfigurableAction *<begin>$L0;
		// Blam::Input::ConfigurableAction *<end>$L0;
		{
			// Blam::Input::ConfigurableAction &configAction;
		}
	}
	todo("implement");
	_sub_109D3810(actions);
}

_extern void _sub_109CD830();
void BuildSettingsMenu() // 0x109CD830
{
	// `anonymous-namespace'::BuildSettingsMenu
	// procedure flags: nofpo
	todo("implement");
	_sub_109CD830();
}

_extern bool _sub_109D3C30(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool VariableInputRawInputUpdate(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109D3C30
{
	// `anonymous-namespace'::VariableInputRawInputUpdate
	// static ...; // 0x109D3D60
	// static ...; // 0x109D3D58
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
	// std::string &returnInfo;
	// bool statusBool;
	// std::string status;
	// unsigned long value;
	todo("implement");
	bool __result = _sub_109D3C30(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109CD8A0(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandBind(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109CD8A0
{
	// `anonymous-namespace'::CommandBind
	// static ...; // 0x109CE21F
	// static ...; // 0x109CE217
	// static ...; // 0x109CE20F
	// static ...; // 0x109CE20C
	// static ...; // 0x109CE204
	// static ...; // 0x109CE1BC
	// static ...; // 0x109CE1B4
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
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
	{
		// std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > > it;
		{
			// bool isEnd;
			// char ch;
			{
				// std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > > partEnd;
			}
		}
	}
	todo("implement");
	bool __result = _sub_109CD8A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109D2850();
bool IsModifierKeyDown() // 0x109D2850
{
	// `anonymous-namespace'::IsModifierKeyDown
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_109D2850();
	return __result;
}

_extern bool _sub_109D27F0(Blam::Input::KeyCode);
bool IsModifierKey(Blam::Input::KeyCode code) // 0x109D27F0
{
	// `anonymous-namespace'::IsModifierKey
	// Blam::Input::KeyCode code;
	todo("implement");
	bool __result = _sub_109D27F0(code);
	return __result;
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
			// std::vector<std::string,std::allocator<std::string> > command;
			// Blam::Input::KeyCode keyCode;
			// std::string result;
		}
	}
	todo("implement");
	_sub_109D2900();
}

_inline CommandBinding::CommandBinding() // 0x109C4B10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CommandBinding@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::CommandBinding::CommandBinding
	// CommandBinding *const this;

	compiler_generated();
}

_extern bool _sub_109D36C0(std::string const &, Blam::Input::KeyCode *, Blam::Input::MouseButton *);
bool ParseKeyOrMouseButton(std::string const &name, Blam::Input::KeyCode *resultKey, Blam::Input::MouseButton *resultMouse) // 0x109D36C0
{
	// `anonymous-namespace'::ParseKeyOrMouseButton
	// Blam::Input::MouseButton *resultMouse;
	todo("implement");
	bool __result = _sub_109D36C0(name, resultKey, resultMouse);
	return __result;
}

_extern bool _sub_109D35A0(std::string const &, Blam::Input::ControllerButton *);
bool ParseControllerButton(std::string const &name, Blam::Input::ControllerButton *result) // 0x109D35A0
{
	// `anonymous-namespace'::ParseControllerButton
	// Blam::Input::ControllerButton *result;
	todo("implement");
	bool __result = _sub_109D35A0(name, result);
	return __result;
}

_extern bool _sub_109CE4A0(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandBindControllerAction(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109CE4A0
{
	// `anonymous-namespace'::CommandBindControllerAction
	// static ...; // 0x109CE74E
	// static ...; // 0x109CE747
	// static ...; // 0x109CE73C
	// static ...; // 0x109CE70C
	// static ...; // 0x109CE704
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
	// std::string &returnInfo;
	// Blam::Input::GameAction action;
	// Blam::Input::ControllerButton button;
	// std::string actionName;
	{
		// std::string buttonName;
	}
	todo("implement");
	bool __result = _sub_109CE4A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109CE810(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandBindKeyboardAction(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109CE810
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
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
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

_extern bool _sub_109D3A00(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool VariableControllerSensitivityXUpdated(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109D3A00
{
	// `anonymous-namespace'::VariableControllerSensitivityXUpdated
	// static ...; // 0x109D3A94
	// static ...; // 0x109D3A8C
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
	// std::string &returnInfo;
	// float newSensitivity;
	todo("implement");
	bool __result = _sub_109D3A00(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109D3AE0(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool VariableControllerSensitivityYUpdated(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109D3AE0
{
	// `anonymous-namespace'::VariableControllerSensitivityYUpdated
	// static ...; // 0x109D3B74
	// static ...; // 0x109D3B6C
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
	// std::string &returnInfo;
	// float newSensitivity;
	todo("implement");
	bool __result = _sub_109D3AE0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109D3BC0(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool VariableControllerStickLayoutUpdated(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109D3BC0
{
	// `anonymous-namespace'::VariableControllerStickLayoutUpdated
	// std::string &returnInfo;
	// unsigned long layout;
	todo("implement");
	bool __result = _sub_109D3BC0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109CF820(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandDumpBindingsJson(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109CF820
{
	// `anonymous-namespace'::CommandDumpBindingsJson
	// static ...; // 0x109CFD74
	// static ...; // 0x109CFD6D
	// static ...; // 0x109CFD67
	// static ...; // 0x109CFD5C
	// static ...; // 0x109CFD20
	// static ...; // 0x109CFD18
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// Blam::Input::BindingsTable currentBindings;
	{
		// __int32 i;
		{
			// std::string names[6];
			// std::string actionName;
		}
	}
	todo("implement");
	bool __result = _sub_109CF820(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109CFEF0(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandFindKeybdBinding(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109CFEF0
{
	// `anonymous-namespace'::CommandFindKeybdBinding
	// static ...; // 0x109D0258
	// static ...; // 0x109D0251
	// static ...; // 0x109D0244
	// static ...; // 0x109D0240
	// static ...; // 0x109D0204
	// static ...; // 0x109D01FC
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
	// std::string &returnInfo;
	// std::string search_for;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	{
		// __int32 i;
		{
			// __int32 k;
			{
				// std::string command_part;
				{
					// std::string key;
				}
			}
		}
	}
	todo("implement");
	bool __result = _sub_109CFEF0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109CEF20(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandDumpBindings(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109CEF20
{
	// `anonymous-namespace'::CommandDumpBindings
	// static ...; // 0x109CF637
	// static ...; // 0x109CF62C
	// static ...; // 0x109CF608
	// static ...; // 0x109CF600
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
	// std::string &returnInfo;
	// Blam::Input::BindingsTable currentBindings;
	{
		// __int32 i;
		{
			// std::string names[6];
			// std::string actionName;
		}
	}
	todo("implement");
	bool __result = _sub_109CEF20(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109D0350(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandResetBindings(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109D0350
{
	// `anonymous-namespace'::CommandResetBindings
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_109D0350(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109D38E0(char const *, float *);
bool TryParseFloat(char const *str, float *value) // 0x109D38E0
{
	// `anonymous-namespace'::TryParseFloat
	// static ...; // 0x109D3964
	// static ...; // 0x109D395C
	// char const *str;
	// float *value;
	// char *endp;
	todo("implement");
	bool __result = _sub_109D38E0(str, value);
	return __result;
}

_extern bool _sub_109CEE40(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandControllerVibrationTest(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109CEE40
{
	// `anonymous-namespace'::CommandControllerVibrationTest
	// static ...; // 0x109CEED4
	// static ...; // 0x109CEECC
	// std::vector<std::string,std::allocator<std::string> > const &Arguments;
	// std::string &returnInfo;
	// float duration;
	todo("implement");
	bool __result = _sub_109CEE40(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109D03A0(std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandSetMouseWheelEventTime(std::vector<std::string,std::allocator<std::string> > const &Arguments, std::string &returnInfo) // 0x109D03A0
{
	// `anonymous-namespace'::CommandSetMouseWheelEventTime
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_109D03A0(Arguments, returnInfo);
	return __result;
}

_inline CommandBinding::~CommandBinding() // 0x109C9F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CommandBinding@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::CommandBinding::~CommandBinding
	// CommandBinding *const this;

	compiler_generated();
}
