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

#include "Patches/Input.hpp"  // hades: added for 0x109C4B60

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

namespace Patches { namespace Input { void TestControllerVibration(float durationSeconds); } }  // hades: added for 0X109CEE40

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
	std::vector<Blam::Input::ConfigurableAction> vehicleControls = { { "settings_actions_vehicle_accelerate", -1, -1, 51 }, { "settings_actions_vehicle_reverse", -1, -1, 52 }, { "settings_actions_vehicle_boost", -1, -1, 48 }, { "settings_actions_vehicle_raise", -1, -1, 50 }, { "settings_actions_vehicle_dive", -1, -1, 49 }, { "settings_actions_vehicle_fire", -1, -1, 53 }, { "settings_actions_vehicle_alt_fire", -1, -1, 54 }, { "settings_actions_vehicle_bansheebomb", -1, -1, 28 } }; // 0x12454EE8
	std::vector<Blam::Input::ConfigurableAction> infantryControls = { { "settings_actions_move_forward", -1, -1, 59 }, { "settings_actions_move_backward", -1, -1, 60 }, { "settings_actions_move_left", -1, -1, 61 }, { "settings_actions_move_right", -1, -1, 62 }, { "settings_actions_sprint", -1, -1, 33 }, { "settings_actions_jump", -1, -1, 16 }, { "settings_actions_crouch", -1, -1, 29 }, { "settings_actions_use", -1, -1, 21 }, { "settings_actions_dualwield", -1, -1, 23 }, { "settings_actions_shoot", -1, -1, 26 }, { "settings_actions_shoot_left", -1, -1, 27 }, { "settings_actions_reload", -1, -1, 20 }, { "settings_actions_reload_left", -1, -1, 22 }, { "settings_actions_zoom", -1, -1, 30 }, { "settings_actions_switch_weapons", -1, -1, 18 }, { "settings_actions_melee", -1, -1, 24 }, { "settings_actions_throw_grenade", -1, -1, 25 }, { "settings_actions_toggle_grenade_type", -1, -1, 17 }, { "settings_actions_show_scores", -1, -1, 7 }, { "settings_actions_forge_delete", -1, -1, 13 }, { "settings_actions_chat_all", -1, -1, 39 }, { "settings_actions_chat_team", -1, -1, 40 }, { "settings_actions_chat_voice", -1, -1, 41 }, { "settings_actions_emote", -1, -1, 31 } }; // 0x12454EF8
	Utils::NameValueTable<enum Blam::Input::KeyCode> keyCodes = { { "Escape", (Blam::Input::KeyCode)0 }, { "F1", (Blam::Input::KeyCode)1 }, { "F2", (Blam::Input::KeyCode)2 }, { "F3", (Blam::Input::KeyCode)3 }, { "F4", (Blam::Input::KeyCode)4 }, { "F5", (Blam::Input::KeyCode)5 }, { "F6", (Blam::Input::KeyCode)6 }, { "F7", (Blam::Input::KeyCode)7 }, { "F8", (Blam::Input::KeyCode)8 }, { "F9", (Blam::Input::KeyCode)9 }, { "F10", (Blam::Input::KeyCode)10 }, { "F11", (Blam::Input::KeyCode)11 }, { "F12", (Blam::Input::KeyCode)12 }, { "PrintScreen", (Blam::Input::KeyCode)13 }, { "F14", (Blam::Input::KeyCode)14 }, { "F15", (Blam::Input::KeyCode)15 }, { "Tilde", (Blam::Input::KeyCode)16 }, { "1", (Blam::Input::KeyCode)17 }, { "2", (Blam::Input::KeyCode)18 }, { "3", (Blam::Input::KeyCode)19 }, { "4", (Blam::Input::KeyCode)20 }, { "5", (Blam::Input::KeyCode)21 }, { "6", (Blam::Input::KeyCode)22 }, { "7", (Blam::Input::KeyCode)23 }, { "8", (Blam::Input::KeyCode)24 }, { "9", (Blam::Input::KeyCode)25 }, { "0", (Blam::Input::KeyCode)26 }, { "Minus", (Blam::Input::KeyCode)27 }, { "Plus", (Blam::Input::KeyCode)28 }, { "Back", (Blam::Input::KeyCode)29 }, { "Tab", (Blam::Input::KeyCode)30 }, { "Q", (Blam::Input::KeyCode)31 }, { "W", (Blam::Input::KeyCode)32 }, { "E", (Blam::Input::KeyCode)33 }, { "R", (Blam::Input::KeyCode)34 }, { "T", (Blam::Input::KeyCode)35 }, { "Y", (Blam::Input::KeyCode)36 }, { "U", (Blam::Input::KeyCode)37 }, { "I", (Blam::Input::KeyCode)38 }, { "O", (Blam::Input::KeyCode)39 }, { "P", (Blam::Input::KeyCode)40 }, { "LBracket", (Blam::Input::KeyCode)41 }, { "RBracket", (Blam::Input::KeyCode)42 }, { "Pipe", (Blam::Input::KeyCode)43 }, { "CapsLock", (Blam::Input::KeyCode)44 }, { "A", (Blam::Input::KeyCode)45 }, { "S", (Blam::Input::KeyCode)46 }, { "D", (Blam::Input::KeyCode)47 }, { "F", (Blam::Input::KeyCode)48 }, { "G", (Blam::Input::KeyCode)49 }, { "H", (Blam::Input::KeyCode)50 }, { "J", (Blam::Input::KeyCode)51 }, { "K", (Blam::Input::KeyCode)52 }, { "L", (Blam::Input::KeyCode)53 }, { "Colon", (Blam::Input::KeyCode)54 }, { "Quote", (Blam::Input::KeyCode)55 }, { "Enter", (Blam::Input::KeyCode)56 }, { "LShift", (Blam::Input::KeyCode)57 }, { "Z", (Blam::Input::KeyCode)58 }, { "X", (Blam::Input::KeyCode)59 }, { "C", (Blam::Input::KeyCode)60 }, { "V", (Blam::Input::KeyCode)61 }, { "B", (Blam::Input::KeyCode)62 }, { "N", (Blam::Input::KeyCode)63 }, { "M", (Blam::Input::KeyCode)64 }, { "Comma", (Blam::Input::KeyCode)65 }, { "Period", (Blam::Input::KeyCode)66 }, { "Question", (Blam::Input::KeyCode)67 }, { "RShift", (Blam::Input::KeyCode)68 }, { "LControl", (Blam::Input::KeyCode)69 }, { "LAlt", (Blam::Input::KeyCode)71 }, { "Space", (Blam::Input::KeyCode)72 }, { "RAlt", (Blam::Input::KeyCode)73 }, { "Apps", (Blam::Input::KeyCode)75 }, { "RControl", (Blam::Input::KeyCode)76 }, { "Up", (Blam::Input::KeyCode)77 }, { "Down", (Blam::Input::KeyCode)78 }, { "Left", (Blam::Input::KeyCode)79 }, { "Right", (Blam::Input::KeyCode)80 }, { "Insert", (Blam::Input::KeyCode)81 }, { "Home", (Blam::Input::KeyCode)82 }, { "PageUp", (Blam::Input::KeyCode)83 }, { "Delete", (Blam::Input::KeyCode)84 }, { "End", (Blam::Input::KeyCode)85 }, { "PageDown", (Blam::Input::KeyCode)86 }, { "NumLock", (Blam::Input::KeyCode)87 }, { "Divide", (Blam::Input::KeyCode)88 }, { "Multiply", (Blam::Input::KeyCode)89 }, { "Numpad0", (Blam::Input::KeyCode)90 }, { "Numpad1", (Blam::Input::KeyCode)91 }, { "Numpad2", (Blam::Input::KeyCode)92 }, { "Numpad3", (Blam::Input::KeyCode)93 }, { "Numpad4", (Blam::Input::KeyCode)94 }, { "Numpad5", (Blam::Input::KeyCode)95 }, { "Numpad6", (Blam::Input::KeyCode)96 }, { "Numpad7", (Blam::Input::KeyCode)97 }, { "Numpad8", (Blam::Input::KeyCode)98 }, { "Numpad9", (Blam::Input::KeyCode)99 }, { "Subtract", (Blam::Input::KeyCode)100 }, { "Add", (Blam::Input::KeyCode)101 }, { "NumpadEnter", (Blam::Input::KeyCode)102 }, { "Decimal", (Blam::Input::KeyCode)103 }, { "Shift", (Blam::Input::KeyCode)105 }, { "Ctrl", (Blam::Input::KeyCode)106 }, { "Alt", (Blam::Input::KeyCode)108 } }; // 0x12454F08
	Utils::NameValueTable<enum Blam::Input::GameAction> gameActions = { { "Forward", (Blam::Input::GameAction)59 }, { "Back", (Blam::Input::GameAction)60 }, { "Left", (Blam::Input::GameAction)61 }, { "Right", (Blam::Input::GameAction)62 }, { "Sprint", (Blam::Input::GameAction)33 }, { "Jump", (Blam::Input::GameAction)16 }, { "Crouch", (Blam::Input::GameAction)29 }, { "Use", (Blam::Input::GameAction)21 }, { "DualWield", (Blam::Input::GameAction)23 }, { "UseEquipment", (Blam::Input::GameAction)44 }, { "Fire", (Blam::Input::GameAction)26 }, { "FireLeft", (Blam::Input::GameAction)27 }, { "Reload", (Blam::Input::GameAction)20 }, { "ReloadLeft", (Blam::Input::GameAction)22 }, { "Zoom", (Blam::Input::GameAction)30 }, { "SwitchWeapons", (Blam::Input::GameAction)18 }, { "Melee", (Blam::Input::GameAction)24 }, { "Grenade", (Blam::Input::GameAction)25 }, { "SwitchGrenades", (Blam::Input::GameAction)17 }, { "Flashlight", (Blam::Input::GameAction)34 }, { "VehicleAccelerate", (Blam::Input::GameAction)51 }, { "VehicleBrake", (Blam::Input::GameAction)52 }, { "VehicleBoost", (Blam::Input::GameAction)48 }, { "VehicleRaise", (Blam::Input::GameAction)50 }, { "VehicleDive", (Blam::Input::GameAction)49 }, { "VehicleFire", (Blam::Input::GameAction)53 }, { "VehicleAltFire", (Blam::Input::GameAction)54 }, { "BansheeBomb", (Blam::Input::GameAction)28 }, { "Menu", (Blam::Input::GameAction)6 }, { "Scoreboard", (Blam::Input::GameAction)7 }, { "Emote", (Blam::Input::GameAction)31 }, { "Chat", (Blam::Input::GameAction)39 }, { "TeamChat", (Blam::Input::GameAction)40 }, { "VoiceChat", (Blam::Input::GameAction)41 }, { "UiLeftTrigger", (Blam::Input::GameAction)0 }, { "UiRightTrigger", (Blam::Input::GameAction)1 }, { "UiUp", (Blam::Input::GameAction)2 }, { "UiDown", (Blam::Input::GameAction)3 }, { "UiLeft", (Blam::Input::GameAction)4 }, { "UiRight", (Blam::Input::GameAction)5 }, { "UiLeftStick", (Blam::Input::GameAction)8 }, { "UiRightStick", (Blam::Input::GameAction)9 }, { "UiA", (Blam::Input::GameAction)10 }, { "UiB", (Blam::Input::GameAction)11 }, { "UiX", (Blam::Input::GameAction)12 }, { "UiY", (Blam::Input::GameAction)13 }, { "UiLeftBumper", (Blam::Input::GameAction)14 }, { "UiRightBumper", (Blam::Input::GameAction)15 }, { "NextPlayer", (Blam::Input::GameAction)56 }, { "PrevPlayer", (Blam::Input::GameAction)57 } }; // 0x12454F90
	Utils::NameValueTable<enum Blam::Input::MouseButton> mouseButtons = { { "MouseLeft", (Blam::Input::MouseButton)0 }, { "MouseMiddle", (Blam::Input::MouseButton)1 }, { "MouseRight", (Blam::Input::MouseButton)2 }, { "Mouse4", (Blam::Input::MouseButton)3 }, { "Mouse5", (Blam::Input::MouseButton)4 }, { "MouseWheelUp", (Blam::Input::MouseButton)8 }, { "MouseWheelDown", (Blam::Input::MouseButton)9 } }; // 0x12455018
	extern "C" { Utils::NameValueTable<enum Blam::Input::ControllerButton> controllerButtons = { { "LT", (Blam::Input::ControllerButton)0 }, { "RT", (Blam::Input::ControllerButton)1 }, { "Up", (Blam::Input::ControllerButton)2 }, { "Down", (Blam::Input::ControllerButton)3 }, { "Left", (Blam::Input::ControllerButton)4 }, { "Right", (Blam::Input::ControllerButton)5 }, { "Start", (Blam::Input::ControllerButton)6 }, { "Select", (Blam::Input::ControllerButton)7 }, { "LS", (Blam::Input::ControllerButton)8 }, { "RS", (Blam::Input::ControllerButton)9 }, { "A", (Blam::Input::ControllerButton)10 }, { "B", (Blam::Input::ControllerButton)11 }, { "X", (Blam::Input::ControllerButton)12 }, { "Y", (Blam::Input::ControllerButton)13 }, { "LB", (Blam::Input::ControllerButton)14 }, { "RB", (Blam::Input::ControllerButton)15 } }; } // 0x124550A0
	CommandBinding commandBindings[109]; // 0x12455128
	extern "C" Blam::Input::BindingsTable bindings; // 0x124559B0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	ModuleInput::ModuleInput() : ModuleBase("Input") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x109C4B60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleInput@Modules@@QAE@XZ");
		// Modules::ModuleInput *const this;

		VarInputRawInput = AddVariableInt("RawInput", "rawinput", "Enables raw mouse input with no acceleration applied", eCommandFlagsArchived, 1, VariableInputRawInputUpdate);
		VarInputRawInput->ValueIntMin = 0;
		VarInputRawInput->ValueIntMax = 1;
		VarDirectInput = AddVariableInt("DirectInput", "directinput", "Enables the DirectInput keyboard device", eCommandFlagsArchived, 0);
		VarDirectInput->ValueIntMin = 0;
		VarDirectInput->ValueIntMax = 1;
		VarInputControllerPort = AddVariableInt("ControllerPort", "controllerport", "The port number of the player's controller. 0 = Auto Detect", eCommandFlagsNone, 0);
		VarInputControllerPort->ValueIntMin = 0;
		VarInputControllerPort->ValueIntMax = 8;
		AddCommand("Bind", "bind", "Binds a command to a key", eCommandFlagsArgsNoParse, CommandBind, { "key", "[+]command", "arguments" });
		Patches::Input::RegisterDefaultInputHandler(KeyboardUpdated);
		CommandBindControllerAction = AddCommand("ControllerAction", "controller", "Binds an in-game action to a controller button", eCommandFlagsNone, ::CommandBindControllerAction, { "action The name of the action to bind", "button The button name" });
		CommandBindKeyboardAction = AddCommand("KeyboardAction", "keyboard", "Binds an in-game action to keyboard keys or mouse buttons", eCommandFlagsNone, ::CommandBindKeyboardAction, { "action The name of the action to bind", "[primary] The primary key name", "[secondary] The secondary key name" });
		AddCommand("DebugBindings", "debugbindings", "Dumps the input bindings table", eCommandFlagsNone, CommandDumpBindings);
		AddCommand("DumpBindingsJson", "dumpbindingsjson", "Dumps the input bindings table in json", eCommandFlagsNone, CommandDumpBindingsJson);
		AddCommand("FindBind", "findbind", "Finds the key bound to a command passed", eCommandFlagsNone, CommandFindKeybdBinding);
		AddCommand("ResetBindings", "reset_bindings", "Restores default bindings", eCommandFlagsNone, CommandResetBindings);
		VarControllerSensitivityX = AddVariableFloat("ControllerSensitivityX", "xsens", "Horizontal controller look sensitivity", eCommandFlagsArchived, 120.0f, VariableControllerSensitivityXUpdated);
		VarControllerSensitivityY = AddVariableFloat("ControllerSensitivityY", "ysens", "Vertical controller look sensitivity", eCommandFlagsArchived, 60.0f, VariableControllerSensitivityYUpdated);
		VarControllerVibrationIntensity = AddVariableFloat("ControllerVibrationIntensity", "vibration", "Controls the controller vibration intensity", eCommandFlagsArchived, 1.0f);
		VarControllerVibrationIntensity->ValueFloatMin = 0.0f;
		VarControllerVibrationIntensity->ValueFloatMax = 1.0f;
		AddCommand("ControllerVibrationTest", "vibration_test", "Test the controller vibration", eCommandFlagsNone, CommandControllerVibrationTest);
		VarControllerStickLayout = AddVariableInt("ControllerStickLayout", "stick_layout", "Controller stick layout", eCommandFlagsArchived, 0, VariableControllerStickLayoutUpdated);
		VarControllerStickLayout->ValueIntMin = 0;
		VarControllerStickLayout->ValueIntMax = 3;
		VarSpectateSensitivity = AddVariableFloat("SpectateSensitivity", "specsens", "Spectator camera sensitivity", eCommandFlagsArchived, 1.0f);
		VarControllerInvertY = AddVariableInt("ControllerInvertY", "yinvert", "Invert the controller Y look axis", eCommandFlagsArchived, 0);
		VarControllerInvertY->ValueIntMin = 0;
		VarControllerInvertY->ValueIntMax = 1;
		VarToggleSprint = AddVariableInt("ToggleSprint", "toggle_sprint", "Sprint toggle enabled (1) or disabled (0)", eCommandFlagsArchived, 0);
		VarTapScoreboard = AddVariableInt("TapScoreboard", "tap_scoreboard", "Enable/disable double tap to lock scoreboard", eCommandFlagsArchived, 1);
		VarSmartScoreboard = AddVariableInt("SmartScoreboard", "smart_scoreboard", "Enable for smarter scoreboard locking", eCommandFlagsArchived, 1);
		VarMouseWheelInputDelay = AddVariableInt("MouseWheelCooldown", "mouse_wheel_cooldown", "Time between consecutive mouse wheel inputs in milliseconds", eCommandFlagsArchived, 0xC8, CommandSetMouseWheelEventTime);
		VarMouseWheelInputDelay->ValueIntMin = 50;
		VarMouseWheelInputDelay->ValueIntMax = 700;
		VarControllerAimControl = AddVariableInt("ControllerAimControl", "aim_control", "Sets the aim control. 0=Classic, 1=Modern", eCommandFlagsArchived, 1);
		VarControllerAimControl->ValueIntMin = 0;
		VarControllerAimControl->ValueIntMax = 1;
		VarControllerAxialDeadzone = AddVariableInt("ControllerAxialDeadzone", "axial_deadzone", "The minimum amount along the vertical or horizontal axis before it registers as input", eCommandFlagsArchived, 0xC);
		VarControllerAxialDeadzone->ValueIntMin = 0;
		VarControllerAxialDeadzone->ValueIntMax = 20;
		VarControllerRadialDeadzone = AddVariableInt("ControllerRadialDeadzone", "radial_deadzone", "The minimum amount from the center in any direction before it registers as input", eCommandFlagsArchived, 0xC);
		VarControllerRadialDeadzone->ValueIntMin = 0;
		VarControllerRadialDeadzone->ValueIntMax = 20;
		LoadDefaultBindings();
		BuildSettingsMenu();
	}
}

namespace Blam
{
	namespace Input
	{

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


namespace Modules
{
	std::string ModuleInput::ExportBindings() const // 0x109D0560
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExportBindings@ModuleInput@Modules@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
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
			// Utils::NameValueTable<enum Blam::Input::GameAction> &<range>$L0;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::string,enum Blam::Input::GameAction> > > > <begin>$L0;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::string,enum Blam::Input::GameAction> > > > <end>$L0;
				// std::pair<std::string,enum Blam::Input::GameAction> const &action;
					// Blam::Input::ControllerButton button;
					// std::string buttonName;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::string,enum Blam::Input::GameAction> > > > <end>$L1;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::string,enum Blam::Input::GameAction> > > > <begin>$L1;
			// Utils::NameValueTable<enum Blam::Input::GameAction> &<range>$L1;
					// std::string primaryName;
					// std::string secondaryName;
					// Blam::Input::KeyCode primaryKey;
					// Blam::Input::MouseButton primaryMouse;
					// Blam::Input::KeyCode secondaryKey;
					// Blam::Input::MouseButton secondaryMouse;
			// __int32 i;
				// CommandBinding *const binding;
				// std::string line;
				// std::string prefix;
				// std::string key_name;
					// std::string *<end>$L2;
					// std::vector<std::string> &<range>$L2;
					// std::string *<begin>$L2;
						// std::string command;

		std::string result;
		for (auto const &action : gameActions)
		{
			if (action.second >= 59)
				continue;
			Blam::Input::ControllerButton button = bindings.ControllerButtons[action.second];
			std::string buttonName = "";
			if (button < 16)
				controllerButtons.FindName(button, &buttonName);
			result += CommandBindControllerAction->Name + " \"" + action.first + "\"";
			if (buttonName.length() > 0)
				result += " \"" + buttonName + "\"";
			result += "\n";
		}
		result += "\n";
		for (auto const &action : gameActions)
		{
			if (action.second >= 63)
				continue;
			std::string primaryName;
			std::string secondaryName;
			Blam::Input::KeyCode primaryKey = bindings.PrimaryKeys[action.second];
			Blam::Input::KeyCode secondaryKey = bindings.SecondaryKeys[action.second];
			Blam::Input::MouseButton primaryMouse = bindings.PrimaryMouseButtons[action.second];
			Blam::Input::MouseButton secondaryMouse = bindings.SecondaryMouseButtons[action.second];
			if (primaryKey < 0x6D)
				keyCodes.FindName(primaryKey, &primaryName);
			if (secondaryKey < 0x6D)
				keyCodes.FindName(secondaryKey, &secondaryName);
			if (action.second < 59)
			{
				if (primaryMouse < 10)
					mouseButtons.FindName(primaryMouse, &primaryName);
				if (secondaryMouse < 10)
					mouseButtons.FindName(secondaryMouse, &secondaryName);
			}
			result += CommandBindKeyboardAction->Name + " \"" + action.first + "\"";
			if (primaryName.length() > 0)
				result += " \"" + primaryName + "\"";
			if (secondaryName.length() > 0)
				result += " \"" + secondaryName + "\"";
			result += "\n";
		}
		for (__int32 i = 0; i < 0x6D; i++)
		{
			CommandBinding *const binding = &commandBindings[i];
			if (binding->command.size() == 0)
				continue;
			std::string key_name;
			std::string line;
			keyCodes.FindName((Blam::Input::KeyCode)i, &key_name);
			std::string prefix = "";
			if (binding->isHold)
				prefix = "+";
			line += "bind " + key_name + " " + prefix;
			for (auto command : binding->command)
				line += command + " ";
			line.erase(line.find_last_not_of(" \n\r\t") + 1);
			result += line + "\n";
		}
		return result;
	}

	bool ModuleInput::IsCommandBound(std::string command) // 0x109D2480
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsCommandBound@ModuleInput@Modules@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x109D2724
		// static ...; // 0x109D271C
		// Modules::ModuleInput *const this;
		// std::string command;
			// __int32 i;
				// CommandBinding *const binding;
				// std::string bound_command;

		for (__int32 i = 0; i < 109; i++)
		{
			CommandBinding *const binding = &commandBindings[i];
			if (binding->command.size() == 0)
				continue;
			std::string bound_command = "";
			if (binding->command[1] == "")
				bound_command = binding->command[0];
			else
				bound_command = binding->command[0] + " " + binding->command[1];
			std::transform(bound_command.begin(), bound_command.end(), bound_command.begin(), tolower);
			if (command.compare(bound_command) == 0)
				return true;
		}
		return false;
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

void LoadDefaultBindings() // 0x109D2C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadDefaultBindings@@YAXXZ");
	// `anonymous-namespace'::LoadDefaultBindings
	// procedure flags: nofpo
		// __int32 i;

	memset(&bindings, 0, sizeof(bindings));
	bindings.ControllerSensitivityX = 120;
	bindings.ControllerSensitivityY = 60;
	bindings.FlyingCameraSpeed = .8f;
	bindings.FlyingCameraThrust = 1.f;
	for (__int32 i = 0; i < 63; i++)
	{
		if (i < 59)
			bindings.ControllerButtons[i] = Blam::Input::eControllerButton_None;
		bindings.PrimaryKeys[i] = Blam::Input::eKeyCode_None;
		bindings.SecondaryKeys[i] = Blam::Input::eKeyCode_None;
		bindings.PrimaryMouseButtons[i] = Blam::Input::eMouseButton_None;
		bindings.SecondaryMouseButtons[i] = Blam::Input::eMouseButton_None;
	}
	for (__int32 i = 0; i < 16; i++)
		bindings.ControllerButtons[i] = static_cast<Blam::Input::ControllerButton>(i);
	bindings.ControllerButtons[16] = Blam::Input::eControllerButtonA;
	bindings.ControllerButtons[17] = Blam::Input::eControllerButtonDpadRight;
	bindings.ControllerButtons[18] = Blam::Input::eControllerButtonY;
	bindings.ControllerButtons[19] = Blam::Input::eControllerButtonY;
	bindings.ControllerButtons[20] = Blam::Input::eControllerButtonRightBumper;
	bindings.ControllerButtons[21] = Blam::Input::eControllerButtonRightBumper;
	bindings.ControllerButtons[22] = Blam::Input::eControllerButtonLeftBumper;
	bindings.ControllerButtons[23] = Blam::Input::eControllerButtonLeftBumper;
	bindings.ControllerButtons[24] = Blam::Input::eControllerButtonB;
	bindings.ControllerButtons[25] = Blam::Input::eControllerButtonLeftTrigger;
	bindings.ControllerButtons[26] = Blam::Input::eControllerButtonRightTrigger;
	bindings.ControllerButtons[27] = Blam::Input::eControllerButtonLeftTrigger;
	bindings.ControllerButtons[29] = Blam::Input::eControllerButtonX;
	bindings.ControllerButtons[30] = Blam::Input::eControllerButtonRightStick;
	bindings.ControllerButtons[31] = Blam::Input::eControllerButtonDpadLeft;
	bindings.ControllerButtons[32] = Blam::Input::eControllerButtonDpadRight;
	bindings.ControllerButtons[33] = Blam::Input::eControllerButtonLeftStick;
	bindings.ControllerButtons[34] = Blam::Input::eControllerButtonDpadUp;
	bindings.ControllerButtons[35] = Blam::Input::eControllerButtonDpadDown;
	bindings.ControllerButtons[36] = Blam::Input::eControllerButtonDpadUp;
	bindings.ControllerButtons[37] = Blam::Input::eControllerButtonDpadLeft;
	bindings.ControllerButtons[38] = Blam::Input::eControllerButtonDpadRight;
	bindings.ControllerButtons[41] = Blam::Input::eControllerButtonDpadDown;
	bindings.ControllerButtons[42] = Blam::Input::eControllerButtonA;
	bindings.ControllerButtons[48] = Blam::Input::eControllerButtonLeftTrigger;
	bindings.ControllerButtons[49] = Blam::Input::eControllerButtonX;
	bindings.ControllerButtons[50] = Blam::Input::eControllerButtonA;
	bindings.ControllerButtons[53] = Blam::Input::eControllerButtonRightTrigger;
	bindings.ControllerButtons[54] = Blam::Input::eControllerButtonLeftTrigger;
	bindings.ControllerButtons[28] = Blam::Input::eControllerButtonB;
	bindings.ControllerButtons[56] = Blam::Input::eControllerButtonDpadRight;
	bindings.ControllerButtons[57] = Blam::Input::eControllerButtonDpadLeft;
	bindings.ControllerButtons[58] = Blam::Input::eControllerButtonA;
	bindings.ControllerButtons[44] = Blam::Input::eControllerButtonLeftBumper;
	bindings.ControllerButtons[6] = Blam::Input::eControllerButtonStart;
	bindings.ControllerButtons[7] = Blam::Input::eControllerButtonSelect;
	bindings.ControllerHoldButtons[19] = true;
	bindings.ControllerHoldButtons[21] = true;
	bindings.ControllerHoldButtons[23] = true;
	bindings.PrimaryKeys[2] = Blam::Input::eKeyCodeUp;
	bindings.PrimaryKeys[3] = Blam::Input::eKeyCodeDown;
	bindings.PrimaryKeys[4] = Blam::Input::eKeyCodeLeft;
	bindings.PrimaryKeys[5] = Blam::Input::eKeyCodeRight;
	bindings.PrimaryKeys[6] = Blam::Input::eKeyCodeEscape;
	bindings.PrimaryKeys[7] = Blam::Input::eKeyCodeTab;
	bindings.PrimaryKeys[10] = Blam::Input::eKeyCodeEnter;
	bindings.SecondaryKeys[10] = Blam::Input::eKeyCodeSpace;
	bindings.PrimaryKeys[11] = Blam::Input::eKeyCodeEscape;
	bindings.SecondaryKeys[11] = Blam::Input::eKeyCodeBack;
	bindings.PrimaryKeys[12] = Blam::Input::eKeyCodeX;
	bindings.PrimaryKeys[13] = Blam::Input::eKeyCodeDelete;
	bindings.PrimaryKeys[14] = Blam::Input::eKeyCodeQ;
	bindings.PrimaryKeys[15] = Blam::Input::eKeyCodeE;
	bindings.PrimaryKeys[16] = Blam::Input::eKeyCodeSpace;
	bindings.PrimaryKeys[17] = Blam::Input::eKeyCodeG;
	bindings.PrimaryMouseButtons[18] = Blam::Input::eMouseButtonWheelUp;
	bindings.SecondaryMouseButtons[18] = Blam::Input::eMouseButtonWheelDown;
	bindings.PrimaryKeys[20] = Blam::Input::eKeyCodeR;
	bindings.PrimaryKeys[21] = Blam::Input::eKeyCodeE;
	bindings.PrimaryKeys[22] = Blam::Input::eKeyCodeZ;
	bindings.PrimaryKeys[23] = Blam::Input::eKeyCodeZ;
	bindings.PrimaryKeys[24] = Blam::Input::eKeyCodeQ;
	bindings.SecondaryKeys[24] = Blam::Input::eKeyCodeV;
	bindings.PrimaryKeys[25] = Blam::Input::eKeyCodeF;
	bindings.SecondaryMouseButtons[25] = Blam::Input::eMouseButtonMiddle;
	bindings.PrimaryMouseButtons[26] = Blam::Input::eMouseButtonLeft;
	bindings.PrimaryMouseButtons[27] = Blam::Input::eMouseButtonRight;
	bindings.PrimaryKeys[29] = Blam::Input::eKeyCodeLControl;
	bindings.PrimaryMouseButtons[30] = Blam::Input::eMouseButtonRight;
	bindings.PrimaryKeys[33] = Blam::Input::eKeyCodeLShift;
	bindings.PrimaryKeys[39] = Blam::Input::eKeyCodeT;
	bindings.PrimaryKeys[40] = Blam::Input::eKeyCodeY;
	bindings.PrimaryKeys[41] = Blam::Input::eKeyCodeCapital;
	bindings.PrimaryKeys[42] = Blam::Input::eKeyCodeSpace;
	bindings.PrimaryKeys[48] = Blam::Input::eKeyCodeLShift;
	bindings.PrimaryKeys[49] = Blam::Input::eKeyCodeLControl;
	bindings.SecondaryMouseButtons[49] = Blam::Input::eMouseButtonWheelDown;
	bindings.PrimaryKeys[50] = Blam::Input::eKeyCodeSpace;
	bindings.SecondaryMouseButtons[50] = Blam::Input::eMouseButtonWheelUp;
	bindings.PrimaryKeys[51] = Blam::Input::eKeyCodeW;
	bindings.SecondaryKeys[51] = Blam::Input::eKeyCodeUp;
	bindings.PrimaryKeys[52] = Blam::Input::eKeyCodeS;
	bindings.SecondaryKeys[52] = Blam::Input::eKeyCodeDown;
	bindings.PrimaryMouseButtons[53] = Blam::Input::eMouseButtonLeft;
	bindings.PrimaryMouseButtons[54] = Blam::Input::eMouseButtonRight;
	bindings.PrimaryKeys[28] = Blam::Input::eKeyCodeQ;
	bindings.SecondaryKeys[28] = Blam::Input::eKeyCodeV;
	bindings.PrimaryKeys[56] = Blam::Input::eKeyCodeDown;
	bindings.PrimaryKeys[57] = Blam::Input::eKeyCodeUp;
	bindings.PrimaryKeys[58] = Blam::Input::eKeyCodeSpace;
	bindings.PrimaryKeys[59] = Blam::Input::eKeyCodeW;
	bindings.PrimaryKeys[60] = Blam::Input::eKeyCodeS;
	bindings.PrimaryKeys[61] = Blam::Input::eKeyCodeA;
	bindings.PrimaryKeys[62] = Blam::Input::eKeyCodeD;
	bindings.SecondaryKeys[44] = Blam::Input::eKeyCode1;
	bindings.SecondaryKeys[34] = Blam::Input::eKeyCode2;
	bindings.PrimaryKeys[31] = Blam::Input::eKeyCode3;
	Modules::ModuleInput::UpdateBindings();
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

void KeyboardUpdated() // 0x109D2900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?KeyboardUpdated@@YAXXZ");
	// `anonymous-namespace'::KeyboardUpdated
	// procedure flags: nofpo
	// static ...; // 0x109D2B6B
	// static ...; // 0x109D2B64
	// static ...; // 0x109D2B4C
	// static ...; // 0x109D2B44
		// __int32 i;
			// unsigned char keyTicks;
			// CommandBinding *const binding;
			// std::vector<std::string> command;
			// Blam::Input::KeyCode keyCode;
			// std::string result;

	for (__int32 i = 0; i < 109; i++)
	{
		CommandBinding *const binding = &commandBindings[i];
		if (binding->command.size() == 0)
			continue;
		Blam::Input::KeyCode keyCode = (Blam::Input::KeyCode)i;
		unsigned char keyTicks = Blam::Input::GetKeyTicks(keyCode, Blam::Input::eInputTypeSpecial);
		if (keyTicks > 1 || (keyTicks == 0 && (!binding->isHold || !binding->active)))
			continue;
		if (!IsModifierKey(keyCode) && IsModifierKeyDown())
			continue;
		std::vector<std::string> command = binding->command;
		if (binding->isHold)
		{
			if (keyTicks == 1)
				command.push_back("1");
			else if (keyTicks == 0)
				command.push_back("0");
			binding->active = keyTicks > 0;
		}
		std::string result = Modules::CommandMap::Instance().ExecuteCommand(command, true);
		Console::WriteLine(result);
	}
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
	// Parse the action name
	// If a button name was passed, parse it
	// Update the bindings table!

	if (Arguments.size() < 1 || Arguments.size() > 2)
		return false;
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
	bindings.ControllerButtons[action] = button;
	Modules::ModuleInput::UpdateBindings();
	if (button != eKeyCode_None)
		returnInfo = "Action binding set.";
	else
		returnInfo = "Action binding cleared.";
	return true;
}

bool CommandBindKeyboardAction(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CE810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandBindKeyboardAction@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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
		// std::string primaryKeyName;
		// std::string secondaryKeyName;

	if (Arguments.size() < 1 || Arguments.size() > 3)
		return false;
	std::string actionName = Arguments[0];
	Blam::Input::GameAction action;
	if (!gameActions.FindValueIgnoreCase(actionName, &action))
	{
		returnInfo = "Unrecognized action name: " + actionName;
		return false;
	}
	Blam::Input::KeyCode primaryKey = Blam::Input::eKeyCode_None;
	Blam::Input::MouseButton primaryMouse = Blam::Input::eMouseButton_None;
	if (Arguments.size() > 1)
	{
		std::string primaryKeyName = Arguments[1];
		if (!ParseKeyOrMouseButton(primaryKeyName, &primaryKey, &primaryMouse))
		{
			returnInfo = "Unrecognized primary key name: " + primaryKeyName;
			return false;
		}
	}
	Blam::Input::KeyCode secondaryKey = Blam::Input::eKeyCode_None;
	Blam::Input::MouseButton secondaryMouse = Blam::Input::eMouseButton_None;
	if (Arguments.size() > 2)
	{
		std::string secondaryKeyName = Arguments[2];
		if (!ParseKeyOrMouseButton(secondaryKeyName, &secondaryKey, &secondaryMouse))
		{
			returnInfo = "Unrecognized secondary key name: " + secondaryKeyName;
			return false;
		}
	}
	if (primaryKey == Blam::Input::eKeyCode_None && (unsigned char)primaryMouse == (unsigned char)Blam::Input::eMouseButton_None)
	{
		primaryKey = secondaryKey;
		primaryMouse = secondaryMouse;
		secondaryKey = Blam::Input::eKeyCode_None;
		secondaryMouse = Blam::Input::eMouseButton_None;
	}
	if (action >= Blam::Input::eGameActionMoveForward && ((unsigned char)primaryMouse != (unsigned char)Blam::Input::eMouseButton_None || (unsigned char)secondaryMouse != (unsigned char)Blam::Input::eMouseButton_None))
	{
		returnInfo = "Movement actions cannot be bound to mouse buttons.";
		return false;
	}
	if (action < 0 || action >= Blam::Input::eGameAction_KeyboardMouseCount)
	{
		returnInfo = "Invalid action.";
		return false;
	}
	bindings.PrimaryKeys[action] = primaryKey;
	bindings.PrimaryMouseButtons[action] = primaryMouse;
	bindings.SecondaryKeys[action] = secondaryKey;
	bindings.SecondaryMouseButtons[action] = secondaryMouse;
	Modules::ModuleInput::UpdateBindings();
	if (primaryKey != Blam::Input::eKeyCode_None || (unsigned char)primaryMouse != (unsigned char)Blam::Input::eMouseButton_None)
		returnInfo = "Action binding set.";
	else
		returnInfo = "Action binding cleared.";
	return true;
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

bool CommandControllerVibrationTest(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109CEE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandControllerVibrationTest@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandControllerVibrationTest
	// static ...; // 0x109CEED4
	// static ...; // 0x109CEECC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// float duration;

	float duration = 0.5f;
	if (Arguments.size() > 0)
		TryParseFloat(Arguments[0].c_str(), &duration);

	Patches::Input::TestControllerVibration(duration);
	return true;
}

bool CommandSetMouseWheelEventTime(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109D03A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetMouseWheelEventTime@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandSetMouseWheelEventTime
	// std::string &returnInfo;

	Pointer(0x512833).Write<int>(Modules::ModuleInput::Instance().VarMouseWheelInputDelay->ValueInt);
	return true;
}


/* ---------- explicit instantiations */
template Utils::NameValueTable<enum Blam::Input::ControllerButton>::~NameValueTable();
template Utils::NameValueTable<enum Blam::Input::GameAction>::~NameValueTable();
template Utils::NameValueTable<enum Blam::Input::KeyCode>::~NameValueTable();
template Utils::NameValueTable<enum Blam::Input::MouseButton>::~NameValueTable();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { extern "C" { Blam::Input::BindingsTable bindings; } }
