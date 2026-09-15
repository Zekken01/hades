/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/player_control.hpp"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/input/input_abstraction.hpp"
#include "Blam/interface/gui/gui_location_manager.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/motor/motor_system.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "CommandScript.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleInput.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Input.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
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
#include <functional>
#include <initializer_list>
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
#include "Modules/ModuleSettings.hpp"  // hades: added for 0X10A815F0

/* ---------- forward declarations */

class c_gui_screen_widget;
struct begin;
struct c_abstract_button;
struct c_gui_location_manager;
struct end;
struct s_debug_gamepad_data;
struct s_game_input_preferences;
struct s_game_input_state;
struct s_gamepad_state;
struct s_mouse_state;
struct s_object_data;
struct s_player_control_input;
struct s_player_datum;
struct s_rumble_state;
struct s_unit_data;
struct short_point_2d;
namespace Blam
{
	namespace Input
	{
		enum GameAction : unsigned char;
		enum InputType : unsigned __int32;
		enum KeyCode : unsigned short;
		struct ActionState;
		struct BindingsPreferences;
		struct BindingsTable;
		struct ConfigurableAction;
		struct KeyState;
	}
}
namespace Modules
{
	class ModuleInput;
}
namespace Patches
{
	namespace Input
	{
		class InputContext;
	}
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
namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
namespace Patches {}
using namespace ::Patches;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

//struct SetControllerVibrationHook::__l2::CONTROLLER_VIBRATION
//{
//	unsigned short LeftMotorSpeed; // 0x0
//	unsigned short RightMotorSpeed; // 0x2
//};
//static_assert(sizeof(SetControllerVibrationHook::__l2::CONTROLLER_VIBRATION) == 4, "Invalid SetControllerVibrationHook::__l2::CONTROLLER_VIBRATION size");

/* ---------- prototypes */

extern float real_pin(float x, float min, float max);  // hades: added for 0x10A80F50

extern long(__cdecl *const game_seconds_to_ticks_round)(float);  // hades: added for 0X10A7B740

namespace Blam::Input { void BlockInput(InputType type, bool block); }  // hades: added for 0X10A79380

namespace Patches
{
	namespace Input
	{
		extern void ApplyAll();
		extern void PushContext(std::shared_ptr<Patches::Input::InputContext> context);
		extern void RegisterDefaultInputHandler(void (*func)());
		extern void RegisterMenuUIInputHandler(void (*func)());
		extern void SetKeyboardSettingsMenu(std::vector<Blam::Input::ConfigurableAction> const &infantrySettings, std::vector<Blam::Input::ConfigurableAction> const &vehicleSettings);
		extern void TestControllerVibration(float durationSeconds);
		extern void InvalidateBindings();
	}
}

void null_stub();
void PopContext();
void UpdateInputHook();
void UiInputTick();
void ProcessUiInputHook();
void QuickUpdateUiInputHook();
void BlockInputHook(Blam::Input::InputType type, bool blocked);
void UpdateForgeMonitorBindings();
void InitBindingsHook(Blam::Input::BindingsTable *bindings);
Blam::Input::BindingsPreferences *PreferencesGetKeyBindingsHook(Blam::Input::BindingsPreferences *result);

void PreferencesSetKeyBindingsHook(Blam::Input::BindingsPreferences newBindings);
void GetDefaultBindingsHook(__int32 type, Blam::Input::BindingsTable *result);
void GetKeyboardActionTypeHook();
bool InMonitorMode();
void ProcessKeyBindingsHook(Blam::Input::BindingsTable const &bindings, Blam::Input::ActionState *actions);
void ProcessMouseBindingsHook(Blam::Input::BindingsTable const &bindings, Blam::Input::ActionState *actions);
void UpdateUiControllerInputHook(__int32 a0);
void SetControllerVibrationHook(__int32 controllerIndex, unsigned short leftMotorSpeed, unsigned short rightMotorSpeed);
bool IsDualWielding();
bool HasEqualBindingsDown(Blam::Input::GameAction action1, Blam::Input::GameAction action2, Blam::Input::InputType inputType);
void player_control_update_boots_off_ground(long controller_index, s_player_control_input *input);
void LocalPlayerInputHook(__int32 localPlayerIndex, unsigned __int32 playerIndex, __int32 a3, __int32 a4, __int32 a5, s_player_control_input *state);
bool InitializeDirectInput();
void update_key_state(Blam::Input::KeyState *key, bool is_down, long delta_msec);
void update_keyboard_input_di(long delta_msec, bool enabled, bool *input_detected);
void update_keyboard_input_win32(long delta_msec, bool enabled, bool *out_input_detected);
void input_update_mouse(unsigned long milliseconds, long delta_milliseconds, bool enabled, bool *input_detected);
void input_update_keyboard(long delta_milliseconds, bool enabled, bool *out_input_detected);
void update_button(unsigned char *frames, unsigned short *milliseconds, bool is_pressed, unsigned long delta_milliseconds);
void update_threshold(unsigned char *threshold, bool is_pressed, unsigned char value);
void apply_radial_deadzone(float &x, float &y, float deadzone);
float apply_axial_deadzone(float x, float deadzone);
void apply_deadzone(short_point_2d *output, short thumb_x, short thumb_y, float axial_deadzone, float radial_deadzone);
void input_xinput_update_gamepad_core(long controller_index, long delta_milliseconds, _XINPUT_STATE const *xinput_data, s_gamepad_state *out_gamepad_data, s_debug_gamepad_data *out_debug_gamepad_data, bool *out_input_detected);
bool input_xinput_update_gamepad(long controller_index, long delta_milliseconds, s_gamepad_state *out_gamepad_data, s_debug_gamepad_data *out_debug_gamepad_data, bool *out_input_detected);
void input_update_gamepads(long delta_milliseconds, bool *out_input_detected);
void input_update_gamepads_rumble();
void set_control_method(long method);
void input_update_hook();
void normalize_thumbstick_classic(short thumb_x, short thumb_y, float *out_normalized_x, float *out_normalized_y, bool legacy, float legacy_threshold);
void normalize_thumbstick_modern(short thumb_x, short thumb_y, float *out_normalized_x, float *out_normalized_y);
void input_abstraction_update_gamepad(s_gamepad_state const *gamepad_state, s_game_input_preferences const *preferences, s_game_input_state *input_state, long controller_index);
void input_abstraction_update_hook();

/* ---------- globals */

extern s_input_globals &input_globals; // 0x1135A184
extern s_input_abstraction_globals &input_abstraction_globals; // 0x1135A2F0

template<typename t_arg0> t_arg0 *object_get(unsigned long object_index);  // hades: added for 0X10A79CD0

c_gui_screen_widget *(*c_gui_location_manager::get_location_gui_screen)(); // 0x1135459C

/* ---------- private variables */

namespace hades_file_local
{
	extern "C" std::stack<std::shared_ptr<Patches::Input::InputContext> > contextStack; // 0x12458880
	extern std::vector<void (__cdecl*)(void)> defaultHandlers; // 0x12458850
	extern std::vector<void (__cdecl*)(void)> uiHandlers; // 0x12458870
	extern "C" bool contextDone; // 0x12458894
	extern "C" bool blockStates[3]; // 0x124588A0
	extern std::vector<Blam::Input::ConfigurableAction> settings; // 0x12458860
	extern "C" Blam::Input::InputType actionInputTypes[63]; // 0x11354458
	extern Blam::Input::BindingsTable s_ForgeMonitorModeBindings; // 0x124588A8
	extern unsigned __int32 s_ControllerVibrationTestTicks; // 0x124588A4
	extern "C" unsigned __int32 bindingsNextUpdateTicks; // 0x11354454
	extern IDirectInput8A *g_diInterface; // 0x12458AB0
	extern IDirectInputDevice8A *g_diKeyboardDevice; // 0x12458AB4
	extern bool g_diInitialized; // 0x12458895
	extern std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > lastRotateUpdateTime; // 0x12458898
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Input
	{
		_extern void _sub_10A780B0();
		void ApplyAll() // 0x10A780B0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Input@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A78FA8
			// static ...; // 0x10A78F9C
			// static ...; // 0x10A78F94
			// unsigned __int32 keyboardFixPointers[6];
			{
				// unsigned __int32 &<range>$L0[6];
				// unsigned __int32 *<begin>$L0;
				// unsigned __int32 *<end>$L0;
				{
					// unsigned __int32 pointer;
				}
			}
			todo("implement");
			_sub_10A780B0();
		}

		_extern void _sub_10A7AB70(std::shared_ptr<Patches::Input::InputContext>);
		void PushContext(std::shared_ptr<Patches::Input::InputContext> context) // 0x10A7AB70
		{
			mangled_x86(MANGLED_TODO, "?PushContext@Input@Patches@@YAXV?$shared_ptr@VInputContext@Input@Patches@@@std@@@Z");
			// std::shared_ptr<Patches::Input::InputContext> context;
			{
				// __int32 i;
			}
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_10A7AB70(context);
		}

		void RegisterDefaultInputHandler(void (*func)()) // 0x10A7AD30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterDefaultInputHandler@Input@Patches@@YAXP6AXXZ@Z");
			// void (*func)();

			defaultHandlers.push_back(func);
		}

		void RegisterMenuUIInputHandler(void (*func)()) // 0x10A7AD80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterMenuUIInputHandler@Input@Patches@@YAXP6AXXZ@Z");
			// void (*func)();

			uiHandlers.push_back(func);
		}

		_extern void _sub_10A7AEB0(std::vector<Blam::Input::ConfigurableAction> const &, std::vector<Blam::Input::ConfigurableAction> const &);
		void SetKeyboardSettingsMenu(std::vector<Blam::Input::ConfigurableAction> const &infantrySettings, std::vector<Blam::Input::ConfigurableAction> const &vehicleSettings) // 0x10A7AEB0
		{
			mangled_x86(MANGLED_TODO, "?SetKeyboardSettingsMenu@Input@Patches@@YAXABV?$vector@UConfigurableAction@Input@Blam@@V?$allocator@UConfigurableAction@Input@Blam@@@std@@@std@@0@Z");
			// static ...; // 0x10A7B567
			// static ...; // 0x10A7B55B
			// static ...; // 0x10A7B545
			// static ...; // 0x10A7B530
			// static ...; // 0x10A7B4F4
			// static ...; // 0x10A7B4EC
			// std::vector<Blam::Input::ConfigurableAction> const &infantrySettings;
			// std::vector<Blam::Input::ConfigurableAction> const &vehicleSettings;
			// unsigned __int32 vehiclePointers[5];
			// unsigned __int32 endPointers[1];
			// unsigned __int32 infantryCountPointers[3];
			// unsigned __int32 vehicleCountPointers[3];
			// unsigned __int32 vehicleCount;
			// unsigned __int32 infantryCount;
			// unsigned __int32 infantryPointers[4];
			{
				// unsigned __int32 &<range>$L0[4];
				// unsigned __int32 *<begin>$L0;
				// unsigned __int32 *<end>$L0;
				{
					// unsigned __int32 pointer;
				}
			}
			{
				// unsigned __int32 *<end>$L1;
				// unsigned __int32 *<begin>$L1;
				// unsigned __int32 &<range>$L1[5];
				{
				}
			}
			{
				// unsigned __int32 *<end>$L2;
				// unsigned __int32 &<range>$L2[1];
				// unsigned __int32 *<begin>$L2;
				{
				}
			}
			{
				// unsigned __int32 &<range>$L3[3];
				// unsigned __int32 *<begin>$L3;
				// unsigned __int32 *<end>$L3;
				{
				}
			}
			{
				// unsigned __int32 *<end>$L4;
				// unsigned __int32 *<begin>$L4;
				// unsigned __int32 &<range>$L4[3];
				{
				}
			}
			todo("implement");
			_sub_10A7AEB0(infantrySettings, vehicleSettings);
		}

		void TestControllerVibration(float durationSeconds) // 0x10A7B740
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?TestControllerVibration@Input@Patches@@YAXM@Z");
			// float durationSeconds;
			// function call : long (*const)(float)

			s_ControllerVibrationTestTicks = game_seconds_to_ticks_round(durationSeconds);
		}

		void InvalidateBindings() // 0x10A79CA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InvalidateBindings@Input@Patches@@YAXXZ");
			// procedure flags: nofpo

			bindingsNextUpdateTicks = 100;
		}
	}
}

/* ---------- private code */

void null_stub() // 0x10A81040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?null_stub@@YAXXZ");
	// the original is empty
	// `anonymous-namespace'::null_stub
	// procedure flags: nofpo
}

void PopContext() // 0x10A7A430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PopContext@@YAXXZ");
	// `anonymous-namespace'::PopContext
	// procedure flags: nofpo
		// __int32 i;
	// function call : void ()
	// function call : void ()

	contextStack.top()->Deactivated();
	contextStack.pop();
	if (!contextStack.empty())
	{
		// Activate the previous context
		contextStack.top()->Activated();
	}
	else
	{
		// Restore the game's input block states
		for (auto i = 0; i < eInputType_Count; i++)
			BlockInput(static_cast<InputType>(i), blockStates[i]);
	}
}

_extern void _sub_10A7B9C0();
void UpdateInputHook() // 0x10A7B9C0
{
	// `anonymous-namespace'::UpdateInputHook
	// procedure flags: nofpo
	// static ...; // 0x10A7BD30
	// static ...; // 0x10A7BD24
	// static ...; // 0x10A7BD1C
	// bool allowHandlers;
	{
		// std::vector<void (__cdecl*)(void)> &<range>$L0;
		// void (**<begin>$L0)();
		// void (**<end>$L0)();
		{
			// void (*&handler)();
		}
	}
	{
		// void (**<end>$L1)();
		// void (**<begin>$L1)();
		// std::vector<void (__cdecl*)(void)> &<range>$L1;
		{
		}
	}
	{
		// std::stringstream ss;
		// unsigned long value;
	}
	// function call : void ()
	// function call : bool ()
	// function call : void ()
	// function call : void (*)()
	// function call : void (*)()
	todo("implement");
	_sub_10A7B9C0();
}

void UiInputTick() // 0x10A7B7C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UiInputTick@@YAXXZ");
	// `anonymous-namespace'::UiInputTick
	// procedure flags: nofpo
	// function call : void ()
	// function call : bool ()
	// function call : void ()

	if (contextStack.empty())
		return;

	// Tick the active context
	contextStack.top()->InputUnblock();
	if (!contextStack.top()->UiInputTick())
		contextDone = true;
	contextStack.top()->InputBlock();
}

void ProcessUiInputHook() // 0x10A7AB30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ProcessUiInputHook@@YAXXZ");
	// `anonymous-namespace'::ProcessUiInputHook
	// procedure flags: nofpo

	UiInputTick();
}

void QuickUpdateUiInputHook() // 0x10A7ACD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?QuickUpdateUiInputHook@@YAXXZ");
	// `anonymous-namespace'::QuickUpdateUiInputHook
	// procedure flags: nofpo
	// void (*QuickPumpMessages)();
	// function call : void (*)()

	void (*QuickPumpMessages)() = (void(*)())0x42e940;

	QuickPumpMessages();
	UiInputTick();
}

void BlockInputHook(Blam::Input::InputType type, bool blocked) // 0x10A79380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BlockInputHook@@YAXW4InputType@Input@Blam@@_N@Z");
	// `anonymous-namespace'::BlockInputHook
	// bool blocked;

	if (contextStack.empty())
		Blam::Input::BlockInput(type, blocked);
	blockStates[type] = blocked;
}

void UpdateForgeMonitorBindings() // 0x10A7B8F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateForgeMonitorBindings@@YAXXZ");
	// `anonymous-namespace'::UpdateForgeMonitorBindings
	// procedure flags: nofpo

	// TODO: move these into ModuleInput and possibly add them to the config
	s_ForgeMonitorModeBindings = *Modules::ModuleInput::GetBindings();

	// prevent moving while using rotation snap
	s_ForgeMonitorModeBindings.SecondaryKeys[eGameActionMoveLeft] = eKeyCode_None;
	s_ForgeMonitorModeBindings.SecondaryKeys[eGameActionMoveRight] = eKeyCode_None;
	s_ForgeMonitorModeBindings.SecondaryKeys[eGameActionMoveForward] = eKeyCode_None;
	s_ForgeMonitorModeBindings.SecondaryKeys[eGameActionMoveBack] = eKeyCode_None;
	s_ForgeMonitorModeBindings.PrimaryKeys[eGameActionUiB] = eKeyCodeC; // Clone
}

void InitBindingsHook(Blam::Input::BindingsTable *bindings) // 0x10A79A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitBindingsHook@@YAXPAUBindingsTable@Input@Blam@@@Z");
	// `anonymous-namespace'::InitBindingsHook
	// Blam::Input::BindingsTable *bindings;

	*bindings = *Modules::ModuleInput::GetBindings();
	bindingsNextUpdateTicks = 100;
}

Blam::Input::BindingsPreferences *PreferencesGetKeyBindingsHook(Blam::Input::BindingsPreferences *result) // 0x10A7A550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PreferencesGetKeyBindingsHook@@YAPAUBindingsPreferences@Input@Blam@@PAU123@@Z");
	// `anonymous-namespace'::PreferencesGetKeyBindingsHook
	// Blam::Input::BindingsPreferences *result;
	// Blam::Input::BindingsTable *bindings;

	auto bindings = Modules::ModuleInput::GetBindings();
	memcpy(result->PrimaryKeys, bindings->PrimaryKeys, sizeof(result->PrimaryKeys));
	memcpy(result->PrimaryMouseButtons, bindings->PrimaryMouseButtons, sizeof(result->PrimaryMouseButtons));
	memcpy(result->SecondaryKeys, bindings->SecondaryKeys, sizeof(result->SecondaryKeys));
	memcpy(result->SecondaryMouseButtons, bindings->SecondaryMouseButtons, sizeof(result->SecondaryMouseButtons));
	return result;
}

void PreferencesSetKeyBindingsHook(Blam::Input::BindingsPreferences newBindings) // 0x10A7A620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PreferencesSetKeyBindingsHook@@YAXUBindingsPreferences@Input@Blam@@@Z");
	// `anonymous-namespace'::PreferencesSetKeyBindingsHook
	// Blam::Input::BindingsPreferences newBindings;
	// Blam::Input::BindingsTable *bindings;

	auto bindings = Modules::ModuleInput::GetBindings();
	memcpy(bindings->PrimaryKeys, newBindings.PrimaryKeys, sizeof(bindings->PrimaryKeys));
	memcpy(bindings->PrimaryMouseButtons, newBindings.PrimaryMouseButtons, sizeof(bindings->PrimaryMouseButtons));
	memcpy(bindings->SecondaryKeys, newBindings.SecondaryKeys, sizeof(bindings->SecondaryKeys));
	memcpy(bindings->SecondaryMouseButtons, newBindings.SecondaryMouseButtons, sizeof(bindings->SecondaryMouseButtons));
	Modules::ModuleInput::UpdateBindings();
	Modules::CommandMap::Instance().ExecuteCommand("WriteConfig");
}

void GetDefaultBindingsHook(__int32 type, Blam::Input::BindingsTable *result) // 0x10A793F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDefaultBindingsHook@@YAXHPAUBindingsTable@Input@Blam@@@Z");
	// `anonymous-namespace'::GetDefaultBindingsHook
	// Blam::Input::BindingsTable *result;

	*result = *Modules::ModuleInput::GetBindings();
}

__declspec(naked) void GetKeyboardActionTypeHook() // 0x10A794B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetKeyboardActionTypeHook@@YAXXZ");
	// `anonymous-namespace'::GetKeyboardActionTypeHook
	// procedure flags: nofpo

	__asm
	{
		mov eax, dword ptr actionInputTypes[ecx * 4]
		xor ecx, ecx
		push 060C51Eh
		ret
	}
}

bool InMonitorMode() // 0x10A79A00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InMonitorMode@@YA_NXZ");
	// `anonymous-namespace'::InMonitorMode
	// procedure flags: nofpo
	// static bool (*`InMonitorMode'::`2'::Forge_GetEditorModeState)(unsigned __int32, unsigned __int32 *, unsigned __int32 *); // 0x11354554
	// function call : unsigned long (*const)(long)
	// function call : bool (*)(unsigned __int32, unsigned __int32 *, unsigned __int32 *)

	static auto Forge_GetEditorModeState = (bool(*)(unsigned __int32 playerIndex, unsigned __int32 *heldObjectIndex, unsigned __int32 *objectIndexUnderCrosshair))(0x59A6F0);
	return Forge_GetEditorModeState(((unsigned long(*)(long))0x589C30)(0), nullptr, nullptr);
}

_extern void _sub_10A7A760(Blam::Input::BindingsTable const &, Blam::Input::ActionState *);
void ProcessKeyBindingsHook(Blam::Input::BindingsTable const &bindings, Blam::Input::ActionState *actions) // 0x10A7A760
{
	// `anonymous-namespace'::ProcessKeyBindingsHook
	// Blam::Input::ActionState *actions;
	// void (*EngineProcessKeyBindings)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *);
	{
		// __int32 i;
	}
	// function call : void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)
	// function call : void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)
	todo("implement");
	_sub_10A7A760(bindings, actions);
}

void ProcessMouseBindingsHook(Blam::Input::BindingsTable const &bindings, Blam::Input::ActionState *actions) // 0x10A7AA80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ProcessMouseBindingsHook@@YAXABUBindingsTable@Input@Blam@@PAUActionState@23@@Z");
	// `anonymous-namespace'::ProcessMouseBindingsHook
	// Blam::Input::ActionState *actions;
	// static void (*`ProcessMouseBindingsHook'::`2'::ProcessMouseBindings)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *); // 0x11354558
	// function call : void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)
	// function call : void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)

	static auto ProcessMouseBindings = (void(*)(const BindingsTable &bindings, ActionState *actions))(0x60CE70);
	if (InMonitorMode())
		ProcessMouseBindings(s_ForgeMonitorModeBindings, actions);
	else
		ProcessMouseBindings(bindings, actions);
}

void UpdateUiControllerInputHook(__int32 a0) // 0x10A7BE10
{
	// `anonymous-namespace'::UpdateUiControllerInputHook
	// static ...; // 0x10A7C194
	// static ...; // 0x10A7C188
	// static ...; // 0x10A7C170
	// static ...; // 0x10A7C168
	// __int32 a0;
	// static bool `UpdateUiControllerInputHook'::`2'::returnedBiped; // 0x12458896
	// void (*UpdateCharPlatform)();
	// c_gui_screen_widget *screen;
	// void (*UiUpdateControllerInput)(__int32);
		// std::chrono::duration<double,std::ratio<1> > elapsedTime;
		// float const rotationRate;
		// float angleIncrement;
		// __int32 rotateAmount;
		// long location;
		// bool rotateLeft;
		// Blam::Input::ActionState *leftAction;
		// float &customzation_biped_angle_degrees;
		// Blam::Input::ActionState *rightAction;
		// bool rotateRight;
		// std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > now;
			// float angle;
		// std::vector<void (__cdecl*)(void)> &<range>$L0;
		// void (**<begin>$L0)();
		// void (**<end>$L0)();
			// void (*&handler)();
	// function call : c_gui_screen_widget *(*)()
	// function call : void (*)(__int32)
	// function call : bool (*const)()
	// function call : long ()
	// function call : long ()
	// function call : void (*)()
	// function call : void (*)()

	typedef void(*UiUpdateControllerInputPtr)(int a0);
	auto UiUpdateControllerInput = reinterpret_cast<UiUpdateControllerInputPtr>(0xA93A50);
	typedef bool(*IsMainMenuPtr)();
	auto IsMainMenu = reinterpret_cast<IsMainMenuPtr>(0x531E90);
	typedef float(*UiGetTimeDeltaPtr)();
	auto UiGetTimeDelta = reinterpret_cast<UiGetTimeDeltaPtr>(0xA844E0);
	typedef void(*UpdateCharPlatformPtr)();
	auto UpdateCharPlatform = reinterpret_cast<UpdateCharPlatformPtr>(0xBB5F00);
	typedef void(*RotateCharPlatformPtr)(float timeDelta, float amount);
	auto RotateCharPlatform = reinterpret_cast<RotateCharPlatformPtr>(0xBB5DA0);

	UiUpdateControllerInput(a0);

	// Handle char_platform controls
	//
	// This spices things up a bit compared to the default implementation
	// by making the platform automatically rotate slowly until the player
	// manually rotates it.

	static auto firstRotate = true;
	if (!IsMainMenu())
	{
		// char_platform is only on the main menu
		firstRotate = true;
		return;
	}
	if (firstRotate)
	{
		// Rotate it to the left a bit initially so that you can see the
		// front of your Spartan at the start
		RotateCharPlatform(1.0f, -0.25f);
		firstRotate = false;
		return;
	}
	auto leftAction = GetActionState(eGameActionUiLeft);
	auto rightAction = GetActionState(eGameActionUiRight);
	auto rotateLeft = (!(leftAction->Flags & eActionStateFlagsHandled) && leftAction->Ticks != 0);
	auto rotateRight = (!(rightAction->Flags & eActionStateFlagsHandled) && rightAction->Ticks != 0);
	auto rotateAmount = static_cast<int>(rotateRight) - static_cast<int>(rotateLeft);
	if (rotateAmount)
	{
		RotateCharPlatform(UiGetTimeDelta(), rotateAmount * 1.0f);
	}
	else
	{
		UpdateCharPlatform();
	}

	//main menu ui handlers
	for (auto &&handler : uiHandlers)
		handler();
}

void SetControllerVibrationHook(__int32 controllerIndex, unsigned short leftMotorSpeed, unsigned short rightMotorSpeed) // 0x10A7ADD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetControllerVibrationHook@@YAXHGG@Z");
	// `anonymous-namespace'::SetControllerVibrationHook
	// unsigned short rightMotorSpeed;
	// Modules::ModuleInput const &moduleInput;
	// SetControllerVibrationHook::__l2::CONTROLLER_VIBRATION &vibration;
	// float intensity;

	Modules::ModuleInput &moduleInput = Modules::ModuleInput::Instance();
	float intensity = moduleInput.VarControllerVibrationIntensity->ValueFloat;
	if (s_ControllerVibrationTestTicks > 0)
	{
		leftMotorSpeed = 0xFFFF;
		rightMotorSpeed = 0xFFFF;
	}
	leftMotorSpeed = (unsigned short)(leftMotorSpeed * intensity);
	rightMotorSpeed = (unsigned short)(rightMotorSpeed * intensity);
	unsigned short *vibration = (unsigned short *)(4 * controllerIndex + 0x238e840);
	*vibration = leftMotorSpeed;
	*(vibration + 1) = rightMotorSpeed;
}

bool IsDualWielding() // 0x10A79CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsDualWielding@@YA_NXZ");
	// `anonymous-namespace'::IsDualWielding
	// procedure flags: nofpo
	// s_unit_data *unit;
	// long unit_index;

	long unit_index = player_control_input_get(0)->unit_index;
	if (unit_index == -1)
		return false;
	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	if (!unit)
		return false;
	return unit->current_weapon_set.indices[1] != -1;
}

bool HasEqualBindingsDown(Blam::Input::GameAction action1, Blam::Input::GameAction action2, Blam::Input::InputType inputType) // 0x10A794D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HasEqualBindingsDown@@YA_NW4GameAction@Input@Blam@@0W4InputType@23@@Z");
	// `anonymous-namespace'::HasEqualBindingsDown
	// Blam::Input::InputType inputType;
	// bool isUsingController;
	// Blam::Input::BindingsTable *bindings;
	// Modules::ModuleInput &moduleInput;
		// Blam::Input::ActionState *action2State;
		// Blam::Input::ActionState *action1State;
		// Blam::Input::KeyCode action1SecondaryKey;
		// Blam::Input::MouseButton action1SecondaryMouseButton;
		// Blam::Input::KeyCode action1PrimaryKey;
		// Blam::Input::MouseButton action1PrimaryMouseButton;
		// bool action1PrimaryMouseButtonDown;
		// bool action1PrimaryKeyDown;
		// bool action2SecondaryMouseButtonDown;
		// bool action2PrimaryMouseButtonDown;
		// bool action2PrimaryKeyDown;
		// bool action1SecondaryMouseButtonDown;
		// bool action2SecondaryKeyDown;
		// bool action1SecondaryKeyDown;
		// Blam::Input::KeyCode action2PrimaryKey;
		// Blam::Input::MouseButton action2SecondaryMouseButton;
		// Blam::Input::KeyCode action2SecondaryKey;
		// Blam::Input::MouseButton action2PrimaryMouseButton;

	auto isUsingController = *(bool*)0x0244DE98;
	auto& moduleInput = Modules::ModuleInput::Instance();
	auto bindings = moduleInput.GetBindings();

	//Controller's easy, so check that first.
	if (isUsingController)
	{
		auto action1State = GetActionState(action1);
		auto action2State = GetActionState(action2);

		if (action1State->Ticks != 0 && action2State->Ticks != 0)
			return true;
	}
	else
	{
		//Check keyboard first, with the most bindings it's most likely.

		//Find all keyboard/mouse bindings for the two actions
		KeyCode action1PrimaryKey = bindings->PrimaryKeys[action1];
		KeyCode action1SecondaryKey = bindings->SecondaryKeys[action1];

		KeyCode action2PrimaryKey = bindings->PrimaryKeys[action2];
		KeyCode action2SecondaryKey = bindings->SecondaryKeys[action2];

		//Find which bindings are active
		bool action1PrimaryKeyDown = GetKeyTicks(action1PrimaryKey, inputType) != 0;
		bool action1SecondaryKeyDown = GetKeyTicks(action1SecondaryKey, inputType) != 0;

		bool action2PrimaryKeyDown = GetKeyTicks(action2PrimaryKey, inputType) != 0;
		bool action2SecondaryKeyDown = GetKeyTicks(action2SecondaryKey, inputType) != 0;

		if (action1PrimaryKeyDown)
		{
			if (action1PrimaryKey == action2PrimaryKey && action2PrimaryKeyDown)
				return true;
			if (action1PrimaryKey == action1SecondaryKey && action1SecondaryKeyDown)
				return true;
		}
		if(action1SecondaryKeyDown)
		{
			if (action1SecondaryKey == action2PrimaryKey && action2PrimaryKeyDown)
				return true;
			if (action1SecondaryKey == action1SecondaryKey && action1SecondaryKeyDown)
				return true;
		}

		//Now check mouse bindings.

		MouseButton action1PrimaryMouseButton = bindings->PrimaryMouseButtons[action1];
		MouseButton action1SecondaryMouseButton = bindings->SecondaryMouseButtons[action1];

		MouseButton action2PrimaryMouseButton = bindings->PrimaryMouseButtons[action2];
		MouseButton action2SecondaryMouseButton = bindings->SecondaryMouseButtons[action2];

		bool action1PrimaryMouseButtonDown = GetMouseButtonTicks(action1PrimaryMouseButton, inputType) != 0;
		bool action1SecondaryMouseButtonDown = GetMouseButtonTicks(action1SecondaryMouseButton, inputType) != 0;

		bool action2PrimaryMouseButtonDown = GetMouseButtonTicks(action2PrimaryMouseButton, inputType) != 0;
		bool action2SecondaryMouseButtonDown = GetMouseButtonTicks(action2SecondaryMouseButton, inputType) != 0;

		if (action1PrimaryMouseButtonDown)
		{
			if (action1PrimaryMouseButton == action2PrimaryMouseButton && action2PrimaryMouseButton)
				return true;
			if (action1PrimaryMouseButton == action2SecondaryMouseButton && action2SecondaryMouseButton)
				return true;
		}
		if (action1SecondaryMouseButtonDown)
		{
			if (action1SecondaryMouseButton == action2PrimaryMouseButton && action2PrimaryMouseButton)
				return true;
			if (action1SecondaryMouseButton == action2SecondaryMouseButton && action2SecondaryMouseButton)
				return true;
		}
	}
	return false;
}

_extern void _sub_10A81060(long, s_player_control_input *);
void player_control_update_boots_off_ground(long controller_index, s_player_control_input *input) // 0x10A81060
{
	// `anonymous-namespace'::player_control_update_boots_off_ground
	// s_player_control_input *input;
	// s_unit_data *biped;
	// long unit_index;
	// bool boots_off_ground;
	{
		// unsigned char jump_control_ticks;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : e_motor_program (*const)(long)
	// function call : long (*const)()
	todo("implement");
	_sub_10A81060(controller_index, input);
}

_extern void _sub_10A79DA0(__int32, unsigned __int32, __int32, __int32, __int32, s_player_control_input *);
void LocalPlayerInputHook(__int32 localPlayerIndex, unsigned __int32 playerIndex, __int32 a3, __int32 a4, __int32 a5, s_player_control_input *state) // 0x10A79DA0
{
	// `anonymous-namespace'::LocalPlayerInputHook
	// __int32 a3;
	// __int32 a4;
	// __int32 a5;
	// s_player_control_input *state;
	// void (*const LocalPlayerInputHook)(__int32, unsigned __int32, __int32, __int32, __int32, s_player_control_input *);
	// static bool `LocalPlayerInputHook'::`2'::s_SprintToggled; // 0x12458897
	// bool (*const game_engine_is_forge)();
	// bool isUsingController;
	// Blam::Input::BindingsTable *bindings;
	// Modules::ModuleInput &moduleInput;
	// LocalPlayerInputHook::__l2::ControlGlobalsAction *(*const GetPlayerControlsAction)(__int32);
	// static bool `LocalPlayerInputHook'::`2'::s_ConsumablesLocked; // 0x124588A3
	// bool isDualWielding;
	{
		// Blam::Input::ActionState *fireRightAction;
		// Blam::Input::ActionState *fireLeftAction;
		// Blam::Input::ActionState tmp;
	}
	{
		// s_player_datum *player;
		// unsigned long playerIndex;
		// c_data_array<s_player_datum> *players;
		{
			// unsigned short ticksSprinting;
		}
	}
	{
		// LocalPlayerInputHook::__l2::ControlGlobalsAction *controlGlobalsAction;
	}
	{
		// Blam::Input::ActionState *flashlight_state;
	}
	// function call : void (*const)(__int32, unsigned __int32, __int32, __int32, __int32, s_player_control_input *)
	// function call : unsigned long (*const)(long)
	// function call : LocalPlayerInputHook::__l2::ControlGlobalsAction *(*const)(__int32)
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	_sub_10A79DA0(localPlayerIndex, playerIndex, a3, a4, a5, state);
}

_extern bool _sub_10A79AE0();
bool InitializeDirectInput() // 0x10A79AE0
{
	// `anonymous-namespace'::InitializeDirectInput
	// procedure flags: nofpo
	// HRESULT hr;
	// function call : HINSTANCE__ *(char const *)
	// function call : HRESULT (_GUID const &, IDirectInputDevice8A **, IUnknown *)
	// function call : HRESULT (HWND__ *, unsigned long)
	// function call : HRESULT (_DIDATAFORMAT const *)
	// function call : HRESULT ()
	todo("implement");
	bool __result = _sub_10A79AE0();
	return __result;
}

void update_key_state(Blam::Input::KeyState *key, bool is_down, long delta_msec) // 0x10A81A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_key_state@@YAXPAUKeyState@Input@Blam@@_NJ@Z");
	// `anonymous-namespace'::update_key_state
	// long delta_msec;

	if (!key->unknown || !is_down)
	{
		key->unknown = 0;
		if (is_down)
		{
			if (key->Ticks < 255)
				++key->Ticks;
		}
		else
		{
			key->Ticks = 0;
		}
		if (is_down)
		{
			if (key->Msec + delta_msec < 0xFFFF)
				key->Msec += delta_msec;
		}
		else
		{
			key->Msec = 0;
		}
	}
}

void update_keyboard_input_di(long delta_msec, bool enabled, bool *input_detected) // 0x10A81B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_keyboard_input_di@@YAXJ_NPA_N@Z");
	// `anonymous-namespace'::update_keyboard_input_di
	// static ...; // 0x10A81C5C
	// long delta_msec;
	// bool enabled;
	// bool *input_detected;
	// unsigned char diKeys[256];
		// long i;
			// Blam::Input::KeyState *key;
			// bool is_down;
	// function call : HRESULT (unsigned long, void *)

	if (!InitializeDirectInput())
		return;

	unsigned char diKeys[256];
	g_diKeyboardDevice->GetDeviceState(sizeof(diKeys), diKeys);

	for (long i = 0; i < 104; i++)
	{
		Blam::Input::KeyState *key = Blam::Input::GetKeyState((Blam::Input::KeyCode)i);
		bool is_down;
		if (enabled)
			is_down = (diKeys[Blam::Input::GetDirectInputKey((Blam::Input::KeyCode)i)] & 0x80) != 0;
		else
			is_down = false;
		if (is_down)
			*input_detected = true;
		update_key_state(key, is_down, delta_msec);
	}
}

_extern void _sub_10A81CE0(long, bool, bool *);
void update_keyboard_input_win32(long delta_msec, bool enabled, bool *out_input_detected) // 0x10A81CE0
{
	// `anonymous-namespace'::update_keyboard_input_win32
	// bool *out_input_detected;
	// bool in_foreground;
	{
		// long i;
		{
			// Blam::Input::KeyState *key;
			// bool is_down;
		}
	}
	// function call : HWND__ *()
	// function call : short (__int32)
	todo("implement");
	_sub_10A81CE0(delta_msec, enabled, out_input_detected);
}

_extern void _sub_10A7FB90(unsigned long, long, bool, bool *);
void input_update_mouse(unsigned long milliseconds, long delta_milliseconds, bool enabled, bool *input_detected) // 0x10A7FB90
{
	// `anonymous-namespace'::input_update_mouse
	// bool enabled;
	// bool *input_detected;
	{
		// unsigned long v9;
	}
	{
		// long i;
	}
	todo("implement");
	_sub_10A7FB90(milliseconds, delta_milliseconds, enabled, input_detected);
}

void input_update_keyboard(long delta_milliseconds, bool enabled, bool *out_input_detected) // 0x10A7FB10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_update_keyboard@@YAXJ_NPA_N@Z");
	// `anonymous-namespace'::input_update_keyboard
	// bool *out_input_detected;

	if (Utils::Singleton<Modules::ModuleInput>::Instance().VarDirectInput->ValueInt == 1)
	{
		update_keyboard_input_di(delta_milliseconds, enabled, out_input_detected);
	}
	else
	{
		update_keyboard_input_win32(delta_milliseconds, enabled, out_input_detected);
	}
}

void update_button(unsigned char *frames, unsigned short *milliseconds, bool is_pressed, unsigned long delta_milliseconds) // 0x10A81970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_button@@YAXPAEPAG_NK@Z");
	// `anonymous-namespace'::update_button
	// unsigned long delta_milliseconds;

	if (is_pressed)
	{
		*frames = *frames + 1 >= 255 ? 255 : *frames + 1;
		*milliseconds = *milliseconds + delta_milliseconds >= 0xFFFF ? (unsigned short)0xFFFF : (unsigned short)(*milliseconds + delta_milliseconds);
	}
	else
	{
		*frames = 0;
		*milliseconds = 0;
	}
}

_extern void _sub_10A81E60(unsigned char *, bool, unsigned char);
void update_threshold(unsigned char *threshold, bool is_pressed, unsigned char value) // 0x10A81E60
{
	// `anonymous-namespace'::update_threshold
	// unsigned char value;
	{
		// unsigned char new_Value;
	}
	{
		// unsigned char new_value;
	}
	todo("implement");
	_sub_10A81E60(threshold, is_pressed, value);
}

_extern void _sub_10A7E350(float &, float &, float);
void apply_radial_deadzone(float &x, float &y, float deadzone) // 0x10A7E350
{
	// `anonymous-namespace'::apply_radial_deadzone
	// float deadzone;
	// float const magnitude;
	{
		// float const angle;
		// float const scale;
	}
	todo("implement");
	_sub_10A7E350(x, y, deadzone);
}

float apply_axial_deadzone(float x, float deadzone) // 0x10A7E120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_axial_deadzone@@YAMMM@Z");
	// `anonymous-namespace'::apply_axial_deadzone
	// float deadzone;

	if (x > deadzone)
	{
		return (x - deadzone) / (1.0f - deadzone);
	}
	else if (x < -deadzone)
	{
		return (x + deadzone) / (1.0f - deadzone);
	}
	return 0.0f;
}

void apply_deadzone(short_point_2d *output, short thumb_x, short thumb_y, float axial_deadzone, float radial_deadzone) // 0x10A7E1D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_deadzone@@YAXPAUshort_point_2d@@FFMM@Z");
	// `anonymous-namespace'::apply_deadzone
	// short_point_2d *output;
	// short thumb_x;
	// short thumb_y;
	// float axial_deadzone;
	// float radial_deadzone;
	// float x;
	// float y;

	float x;
	float y;

	x = apply_axial_deadzone((float)thumb_x / 32767.0f, axial_deadzone);
	y = apply_axial_deadzone((float)thumb_y / 32767.0f, axial_deadzone);
	if (radial_deadzone > 0.0f)
	{
		apply_radial_deadzone(x, y, radial_deadzone);
	}

	output->x = (short)(x * 32767.0f);
	output->y = (short)(y * 32767.0f);
}

_extern void _sub_10A80190(long, long, _XINPUT_STATE const *, s_gamepad_state *, s_debug_gamepad_data *, bool *);
void input_xinput_update_gamepad_core(long controller_index, long delta_milliseconds, _XINPUT_STATE const *xinput_data, s_gamepad_state *out_gamepad_data, s_debug_gamepad_data *out_debug_gamepad_data, bool *out_input_detected) // 0x10A80190
{
	// `anonymous-namespace'::input_xinput_update_gamepad_core
	// bool *out_input_detected;
	// float left_axial_deadzone;
	// float right_radial_deadzone;
	// float left_radial_deadzone;
	// Modules::ModuleInput const &module_input;
	// float right_axial_deadzone;
	{
		// long i;
		{
			// bool trigger_pressed;
		}
	}
	{
		{
			// bool button_pressed;
		}
	}
	{
		// float preferred_axial_deadzone;
		// long stick_layout;
		// float preferred_radial_deadzone;
	}
	todo("implement");
	_sub_10A80190(controller_index, delta_milliseconds, xinput_data, out_gamepad_data, out_debug_gamepad_data, out_input_detected);
}

_extern bool _sub_10A80040(long, long, s_gamepad_state *, s_debug_gamepad_data *, bool *);
bool input_xinput_update_gamepad(long controller_index, long delta_milliseconds, s_gamepad_state *out_gamepad_data, s_debug_gamepad_data *out_debug_gamepad_data, bool *out_input_detected) // 0x10A80040
{
	// `anonymous-namespace'::input_xinput_update_gamepad
	// long delta_milliseconds;
	// s_gamepad_state *out_gamepad_data;
	// s_debug_gamepad_data *out_debug_gamepad_data;
	// bool *out_input_detected;
	// unsigned long (*XInputSetStateFn)(unsigned long, _XINPUT_STATE *);
	// unsigned long (*XInputGetStateFn)(unsigned long, _XINPUT_STATE *);
	// _XINPUT_STATE xinput_state;
	// HINSTANCE__ *hModule;
	// function call : unsigned long (*)(unsigned long, _XINPUT_STATE *)
	todo("implement");
	bool __result = _sub_10A80040(controller_index, delta_milliseconds, out_gamepad_data, out_debug_gamepad_data, out_input_detected);
	return __result;
}

void input_update_gamepads(long delta_milliseconds, bool *out_input_detected) // 0x10A7F5E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_update_gamepads@@YAXJPA_N@Z");
	// `anonymous-namespace'::input_update_gamepads
	// bool *out_input_detected;
	// long port;
		// long i;
			// s_gamepad_state *gamepad_state;

	long port = Modules::ModuleInput::Instance().VarInputControllerPort->ValueInt;
	for (long i = 0; i < 4; i++)
	{
		input_globals.active_gamepads &= ~(1 << i);
		if (port == 0 || port - 1 == i)
		{
			s_gamepad_state *gamepad_state = &input_globals.gamepad_states[i];
			if (input_xinput_update_gamepad(i, delta_milliseconds, gamepad_state, nullptr, out_input_detected))
				input_globals.active_gamepads |= 1 << i;
		}
	}
}

_extern void _sub_10A7F710();
void input_update_gamepads_rumble() // 0x10A7F710
{
	// `anonymous-namespace'::input_update_gamepads_rumble
	// procedure flags: nofpo
	// void (*const input_xinput_update_rumble_state)(long, s_rumble_state *, bool);
	// bool disabled;
	{
		// long i;
		{
			// bool disable_index;
		}
	}
	// function call : bool (*const)()
	// function call : void (*const)(long, s_rumble_state *, bool)
	todo("implement");
	_sub_10A7F710();
}

void set_control_method(long method) // 0x10A815F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_control_method@@YAXJ@Z");
	// `anonymous-namespace'::set_control_method
	// long method;
	// function call : void (*const)(long)

	if (input_abstraction_globals.control_method != method)
	{
		((void (__cdecl *)(long))0x60D7B0)(method);
		Modules::CommandMap::Instance().SetVariable(Modules::ModuleSettings::Instance().VarGamepadEnabled, std::to_string(method), false);
	}
}

_extern void _sub_10A7F880();
void input_update_hook() // 0x10A7F880
{
	// `anonymous-namespace'::input_update_hook
	// procedure flags: nofpo
	// static ...; // 0x10A7FA73
	// static ...; // 0x10A7FA5C
	// static ...; // 0x10A7FA44
	// static ...; // 0x10A7FA3C
	// bool (*const game_in_editor)();
	// bool mkb_input_enabled;
	// long delta_milliseconds;
	// bool mkb_input_detected;
	// bool gamepad_input_detected;
	// bool (*const sub_42E000)();
	// unsigned long milliseconds;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : HWND__ *()
	todo("implement");
	_sub_10A7F880();
}

_extern void _sub_10A80840(short, short, float *, float *, bool, float);
void normalize_thumbstick_classic(short thumb_x, short thumb_y, float *out_normalized_x, float *out_normalized_y, bool legacy, float legacy_threshold) // 0x10A80840
{
	// `anonymous-namespace'::normalize_thumbstick_classic
	// float legacy_threshold;
	// float const real_thumb_y;
	// float yaw;
	// float const angle;
	// float const real_thumb_x;
	// float const scale;
	// float const max_component;
	// float pitch;
	{
		// float adjusted_angle;
		// float abs_adjusted_angle;
		// float magnitude;
		{
			// float v30;
			// float v29;
		}
		{
			// float abs_angle;
		}
	}
	todo("implement");
	_sub_10A80840(thumb_x, thumb_y, out_normalized_x, out_normalized_y, legacy, legacy_threshold);
}

void normalize_thumbstick_modern(short thumb_x, short thumb_y, float *out_normalized_x, float *out_normalized_y) // 0x10A80F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?normalize_thumbstick_modern@@YAXFFPAM0@Z");
	// `anonymous-namespace'::normalize_thumbstick_modern
	// float *out_normalized_y;

	*out_normalized_x = real_pin((float)thumb_x * 1.0f / 32767.0f, -1.0f, 1.0f);
	*out_normalized_y = real_pin((float)thumb_y * 1.0f / 32767.0f, -1.0f, 1.0f);
}

_extern void _sub_10A7EB40(s_gamepad_state const *, s_game_input_preferences const *, s_game_input_state *, long);
void input_abstraction_update_gamepad(s_gamepad_state const *gamepad_state, s_game_input_preferences const *preferences, s_game_input_state *input_state, long controller_index) // 0x10A7EB40
{
	// `anonymous-namespace'::input_abstraction_update_gamepad
	// static ...; // 0x10A7F0F0
	// static ...; // 0x10A7F0C0
	// static ...; // 0x10A7F0B8
	// s_gamepad_state const *gamepad_state;
	// s_game_input_preferences const *preferences;
	// s_game_input_state *input_state;
	// long controller_index;
	// float left_thumb_y;
	// float right_thumb_y;
	// bool (*const input_blocked)(long);
	// float left_thumb_x;
	// float right_thumb_x;
	{
		// bool legacy;
	}
	{
		// long i;
		{
			// unsigned short down_msec;
			// unsigned char down_frames;
			// c_abstract_button *abstract_button;
			// long button_index;
			// unsigned char down_amount;
		}
	}
	// function call : bool (*const)(long)
	// function call : bool (*const)(long)
	todo("implement");
	_sub_10A7EB40(gamepad_state, preferences, input_state, controller_index);
}

_extern void _sub_10A7F2A0();
void input_abstraction_update_hook() // 0x10A7F2A0
{
	// `anonymous-namespace'::input_abstraction_update_hook
	// procedure flags: nofpo
	// s_gamepad_state *gamepad_data;
	// void (*const input_abstraction_set_control_method)(long);
	// void (*const input_abstraction_update_keyboard)(s_game_input_preferences *, s_game_input_state *);
	// void (*const input_abstraction_process_mouse)(s_mouse_state *, s_game_input_state *, long);
	// void (*const input_abstraction_process_keyboard)(s_game_input_preferences *, s_game_input_state *);
	// bool (*const user_interface_is_active)();
	// s_gamepad_state *(*const input_get_gamepad_state)(long);
	// long delta_milliseconds;
	// long control_method;
	// char (*const input_abstraction_update_mouse)(s_game_input_preferences *, s_game_input_state *);
	// s_mouse_state *(*const input_get_mouse_state)(long);
	// unsigned long milliseconds;
	{
		// long i;
	}
	{
	}
	// function call : s_gamepad_state *(*const)(long)
	// function call : bool (*const)()
	// function call : s_mouse_state *(*const)(long)
	// function call : void (*const)(s_mouse_state *, s_game_input_state *, long)
	// function call : void (*const)(s_game_input_preferences *, s_game_input_state *)
	todo("implement");
	_sub_10A7F2A0();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::Write<Blam::Input::ConfigurableAction *>(Blam::Input::ConfigurableAction *const) const;

/* ---------- explicit instantiations */
template unsigned short & Pointer::Read<unsigned short>() const;
