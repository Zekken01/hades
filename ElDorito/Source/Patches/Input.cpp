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

#include "Blam/interface/gui/gui_screen_manager.hpp"  // hades: added for 0x10A7F710
#include "Modules/ModuleCamera.hpp"  // hades: added for 0x10A79DA0

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

extern long (*const game_tick_rate)();  // hades: added for 0x10A81060
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10A81060
#include "Modules/ModuleDebug.hpp"  // hades: added for 0x10A81060

unsigned long system_milliseconds();  // hades: added for 0x10A7F880

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

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0X10A79CD0

extern bool CharacterHasFlag(__int32 flag);  // hades: added for 0x10A7BE10
extern void SetUiPlayerModelRotation(float angleDegrees, float seconds);  // hades: added for 0x10A7BE10

c_gui_screen_widget *(*c_gui_location_manager::get_location_gui_screen)(); // 0x1135459C

/* ---------- private variables */

namespace hades_file_local
{
	extern "C" { std::stack<std::shared_ptr<Patches::Input::InputContext> > contextStack; } // 0x12458880
	std::vector<void (__cdecl*)(void)> defaultHandlers; // 0x12458850
	std::vector<void (__cdecl*)(void)> uiHandlers; // 0x12458870
	extern "C" bool contextDone; // 0x12458894
	extern "C" bool blockStates[3]; // 0x124588A0
	std::vector<Blam::Input::ConfigurableAction> settings; // 0x12458860
	extern "C" Blam::Input::InputType actionInputTypes[63]; // 0x11354458
	extern Blam::Input::BindingsTable s_ForgeMonitorModeBindings; // 0x124588A8
	extern unsigned __int32 s_ControllerVibrationTestTicks; // 0x124588A4
	extern "C" unsigned __int32 bindingsNextUpdateTicks; // 0x11354454
	extern IDirectInput8A *g_diInterface; // 0x12458AB0
	extern IDirectInputDevice8A *g_diKeyboardDevice; // 0x12458AB4
	extern bool g_diInitialized; // 0x12458895
	std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > lastRotateUpdateTime = std::chrono::steady_clock::now(); // 0x12458898
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Input
	{
		void ApplyAll() // 0x10A780B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Input@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A78FA8
			// static ...; // 0x10A78F9C
			// static ...; // 0x10A78F94
			// unsigned __int32 keyboardFixPointers[6];
				// unsigned __int32 &<range>$L0[6];
				// unsigned __int32 *<begin>$L0;
				// unsigned __int32 *<end>$L0;
					// unsigned __int32 pointer;

			Hook(0x105CCD, ProcessUiInputHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x106417, QuickUpdateUiInputHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x234238, BlockInputHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x20BF00, InitBindingsHook).Apply();
			Hook(0x10AB40, PreferencesGetKeyBindingsHook).Apply();
			Hook(0x10D040, PreferencesSetKeyBindingsHook).Apply();
			Hook(0x20C040, GetDefaultBindingsHook).Apply();
			Hook(0x20C4F6, GetKeyboardActionTypeHook).Apply();
			Hook(0x1124F0, SetControllerVibrationHook).Apply();
			Hook(0x105C58, null_stub, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x6A225B), 2);
			Patch(0x6940E7, { 0x90, 0xE9 }).Apply();
			Hook(0x695012, UpdateUiControllerInputHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x112613), 2);
			unsigned int keyboardFixPointers[] = { 0x20C529, 0x20C558, 0x20C591, 0x20C5C2, 0x20C5FA, 0x20C63F };
			for (auto pointer : keyboardFixPointers)
				Patch::NopFill(Pointer::Base(pointer), 2);
			Patch(0x20C69F, { 0xEB }).Apply();
			Hook(0x1D4C66, LocalPlayerInputHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x112690, input_update_hook).Apply();
			Hook(0x20D880, input_abstraction_update_hook).Apply();
			Hook(0x20D880, input_abstraction_update_hook).Apply();
		}

		void PushContext(std::shared_ptr<Patches::Input::InputContext> context) // 0x10A7AB70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PushContext@Input@Patches@@YAXV?$shared_ptr@VInputContext@Input@Patches@@@std@@@Z");
			// std::shared_ptr<Patches::Input::InputContext> context;
				// __int32 i;
			// function call : void ()
			// function call : void ()

			if (contextStack.empty())
			{
				for (__int32 i = 0; i < Blam::Input::eInputType_Count; i++)
					Blam::Input::BlockInput(static_cast<Blam::Input::InputType>(i), true);
			}
			else
			{
				contextStack.top()->Deactivated();
			}
			contextStack.push(context);
			context->Activated();
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

		void SetKeyboardSettingsMenu(std::vector<Blam::Input::ConfigurableAction> const &infantrySettings, std::vector<Blam::Input::ConfigurableAction> const &vehicleSettings) // 0x10A7AEB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetKeyboardSettingsMenu@Input@Patches@@YAXABV?$vector@UConfigurableAction@Input@Blam@@V?$allocator@UConfigurableAction@Input@Blam@@@std@@@std@@0@Z");
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
				// unsigned __int32 &<range>$L0[4];
				// unsigned __int32 *<begin>$L0;
				// unsigned __int32 *<end>$L0;
					// unsigned __int32 pointer;
				// unsigned __int32 *<end>$L1;
				// unsigned __int32 *<begin>$L1;
				// unsigned __int32 &<range>$L1[5];
				// unsigned __int32 *<end>$L2;
				// unsigned __int32 &<range>$L2[1];
				// unsigned __int32 *<begin>$L2;
				// unsigned __int32 &<range>$L3[3];
				// unsigned __int32 *<begin>$L3;
				// unsigned __int32 *<end>$L3;
				// unsigned __int32 *<end>$L4;
				// unsigned __int32 *<begin>$L4;
				// unsigned __int32 &<range>$L4[3];

			settings.clear();
			settings.insert(settings.end(), infantrySettings.begin(), infantrySettings.end());
			settings.insert(settings.end(), vehicleSettings.begin(), vehicleSettings.end());
			unsigned __int32 infantryCount = infantrySettings.size();
			unsigned __int32 vehicleCount = vehicleSettings.size();
			unsigned __int32 infantryPointers[] = { 0x398573, 0x3993CF, 0x39A42F, 0x39B4B0 };
			unsigned __int32 vehiclePointers[] = { 0x39856D, 0x3993CA, 0x39A63A, 0x39A645, 0x39B4AB };
			unsigned __int32 endPointers[] = { 0x39A84A };
			unsigned __int32 infantryCountPointers[] = { 0x39857B, 0x3993BC, 0x39B495 };
			unsigned __int32 vehicleCountPointers[] = { 0x398580, 0x3993C1, 0x39B49A };
			for (auto pointer : infantryPointers)
				Pointer::Base(pointer).Write(&settings[0]);
			for (auto pointer : vehiclePointers)
				Pointer::Base(pointer).Write(&settings[0] + infantryCount);
			for (auto pointer : endPointers)
				Pointer::Base(pointer).Write(&settings[0] + settings.size());
			for (auto pointer : infantryCountPointers)
				Pointer::Base(pointer).Write<int>(infantryCount);
			for (auto pointer : vehicleCountPointers)
				Pointer::Base(pointer).Write<int>(vehicleCount);
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

void UpdateInputHook() // 0x10A7B9C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateInputHook@@YAXXZ");
	// `anonymous-namespace'::UpdateInputHook
	// procedure flags: nofpo
	// static ...; // 0x10A7BD30
	// static ...; // 0x10A7BD24
	// static ...; // 0x10A7BD1C
	// bool allowHandlers;
		// std::vector<void (__cdecl*)(void)> &<range>$L0;
		// void (**<begin>$L0)();
		// void (**<end>$L0)();
			// void (*&handler)();
		// void (**<end>$L1)();
		// void (**<begin>$L1)();
		// std::vector<void (__cdecl*)(void)> &<range>$L1;
		// std::stringstream ss;
		// unsigned long value;
	// function call : void ()
	// function call : bool ()
	// function call : void ()
	// function call : void (*)()
	// function call : void (*)()

	if (contextDone)
	{
		PopContext();
		contextDone = false;
	}
	bool allowHandlers = false;
	if (!contextStack.empty())
	{
		contextStack.top()->InputUnblock();
		if (!contextStack.top()->GameInputTick())
			contextDone = true;
		contextStack.top()->InputBlock();
		allowHandlers = contextStack.top()->allowHandlers;
	}
	else
	{
		for (auto &handler : defaultHandlers)
			handler();
	}
	if (allowHandlers)
	{
		for (auto &handler : defaultHandlers)
			handler();
	}
	if (s_ControllerVibrationTestTicks > 0)
		s_ControllerVibrationTestTicks--;
	if (bindingsNextUpdateTicks != -1 && --bindingsNextUpdateTicks == 0)
	{
		bindingsNextUpdateTicks = -1;
		UpdateForgeMonitorBindings();
	}
	if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeAlt, Blam::Input::eInputTypeUi) > 0 && Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeNumpadEnter, Blam::Input::eInputTypeUi) == 1 || Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeAlt, Blam::Input::eInputTypeUi) == 1 && Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeNumpadEnter, Blam::Input::eInputTypeUi) > 0)
	{
		unsigned long value = Utils::Singleton<Modules::ModuleSettings>::Instance().VarFullscreen->ValueInt;
		std::stringstream ss;
		ss << "Settings.Fullscreen " << (value == 0);
		Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand(ss.str());
	}
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

void ProcessKeyBindingsHook(Blam::Input::BindingsTable const &bindings, Blam::Input::ActionState *actions) // 0x10A7A760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ProcessKeyBindingsHook@@YAXABUBindingsTable@Input@Blam@@PAUActionState@23@@Z");
	// `anonymous-namespace'::ProcessKeyBindingsHook
	// Blam::Input::ActionState *actions;
	// void (*EngineProcessKeyBindings)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *);
		// __int32 i;
	// function call : void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)
	// function call : void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)

	void (*EngineProcessKeyBindings)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *) = reinterpret_cast<void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)>(0x60C4A0);
	if (InMonitorMode() && !Pointer(0x5260F34)[0](0x3C, 1).Read<short>())
		EngineProcessKeyBindings(s_ForgeMonitorModeBindings, actions);
	else
		EngineProcessKeyBindings(bindings, actions);
	for (__int32 i = 0; i < 63; i++)
	{
		if (!actions[i].Ticks)
			actions[i].Flags &= ~1;
	}
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
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateUiControllerInputHook@@YAXH@Z");
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
	// Handle char_platform controls
	//
	// This spices things up a bit compared to the default implementation
	// by making the platform automatically rotate slowly until the player
	// manually rotates it.
		// char_platform is only on the main menu
		// Rotate it to the left a bit initially so that you can see the
		// front of your Spartan at the start
	//main menu ui handlers

	void (*UiUpdateControllerInput)(__int32) = reinterpret_cast<void (*)(__int32)>(0xA93A50);
	void (*UpdateCharPlatform)() = reinterpret_cast<void (*)()>(0xBB5F00);
	c_gui_screen_widget *screen = c_gui_location_manager::get_location_gui_screen();
	UiUpdateControllerInput(a0);
	if (!((bool (*const)())0x531E90)())
		return;
	static bool returnedBiped;
	if (screen)
	{
		long location = screen->get_gui_location();
		Blam::Input::ActionState *leftAction = Blam::Input::GetActionState(Blam::Input::eGameActionUiLeft);
		Blam::Input::ActionState *rightAction = Blam::Input::GetActionState(Blam::Input::eGameActionUiRight);
		bool rotateLeft = !(leftAction->Flags & 1) && leftAction->Ticks;
		bool rotateRight = !(rightAction->Flags & 1) && rightAction->Ticks;
		__int32 rotateAmount = rotateRight - rotateLeft;
		float &customzation_biped_angle_degrees = *reinterpret_cast<float *>(0x194A66C);
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = now - lastRotateUpdateTime;
		lastRotateUpdateTime = now;
		float const rotationRate = 90.0f;
		float angleIncrement = (float)elapsedTime.count() * rotationRate;
		switch (screen->get_gui_location())
		{
		case 0:
			if (rotateAmount != 0 && CharacterHasFlag(1))
			{
				float angle = rotateAmount * angleIncrement + customzation_biped_angle_degrees;
				SetUiPlayerModelRotation(angle, 0.0f);
				returnedBiped = false;
			}
			break;
		default:
			if (!returnedBiped)
			{
				Modules::CommandMap::Instance().ExecuteCommand("player.armor.ReturnCustomizationBiped", false);
				returnedBiped = true;
			}
			break;
		}
	}
	UpdateCharPlatform();
	for (auto &handler : uiHandlers)
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

void player_control_update_boots_off_ground(long controller_index, s_player_control_input *input) // 0x10A81060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_control_update_boots_off_ground@@YAXJPAUs_player_control_input@@@Z");
	// `anonymous-namespace'::player_control_update_boots_off_ground
	// s_player_control_input *input;
	// s_unit_data *biped;
	// long unit_index;
	// bool boots_off_ground;
		// unsigned char jump_control_ticks;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : e_motor_program (*const)(long)
	// function call : long (*const)()

	if (!Utils::Singleton<Modules::ModuleDebug>::Instance().VarAcrophobiaClient->ValueInt)
		return;
	long unit_index = player_control_input_get(controller_index)->unit_index;
	s_unit_data *biped = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 1);
	if (!biped)
		return;
	bool boots_off_ground = false;
	if (GetActionState((GameAction)0x10)->GetDownTicks() > 0 && ((long (*)(long))0xBA66A0)(unit_index) == 1)
	{
		unsigned char jump_control_ticks = *(unsigned char *)offset_pointer(biped, 0x5D9);
		if ((biped->unit_control_flags & 2) && jump_control_ticks < game_tick_rate() / 15.0f)
		{
			boots_off_ground = true;
		}
		else if (biped->unit_control_flags & 0x8000)
		{
			if (GetActionState((GameAction)0x21)->GetDownTicks() > 0)
				biped->unit_control_flags |= 0x800;
			boots_off_ground = true;
		}
	}
	if (boots_off_ground)
		input->unit_control_flags |= 0x8000;
	else
		input->unit_control_flags &= ~0x8000;
}

void LocalPlayerInputHook(__int32 localPlayerIndex, unsigned __int32 playerIndex, __int32 a3, __int32 a4, __int32 a5, s_player_control_input *state) // 0x10A79DA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LocalPlayerInputHook@@YAXHIHHHPAUs_player_control_input@@@Z");
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
		// Blam::Input::ActionState *fireRightAction;
		// Blam::Input::ActionState *fireLeftAction;
		// Blam::Input::ActionState tmp;
		// s_player_datum *player;
		// unsigned long playerIndex;
		// c_data_array<s_player_datum> *players;
			// unsigned short ticksSprinting;
		// LocalPlayerInputHook::__l2::ControlGlobalsAction *controlGlobalsAction;
		// Blam::Input::ActionState *flashlight_state;
	// function call : void (*const)(__int32, unsigned __int32, __int32, __int32, __int32, s_player_control_input *)
	// function call : unsigned long (*const)(long)
	// function call : LocalPlayerInputHook::__l2::ControlGlobalsAction *(*const)(__int32)
	// function call : bool (*const)()
	// function call : bool (*const)()

	struct ControlGlobalsAction
	{
		unsigned short Type;
		unsigned short Flags;
	};
	void (*const LocalPlayerInputHook)(__int32, unsigned __int32, __int32, __int32, __int32, s_player_control_input *) = (void (*)(__int32, unsigned __int32, __int32, __int32, __int32, s_player_control_input *))0x5D0C90;
	ControlGlobalsAction *(*const GetPlayerControlsAction)(__int32) = (ControlGlobalsAction *(*)(__int32))0x5D0BD0;
	static bool s_ConsumablesLocked = false;
	static bool s_SprintToggled = false;
	Modules::ModuleInput &moduleInput = Modules::ModuleInput::Instance();
	Blam::Input::BindingsTable *bindings = Modules::ModuleInput::GetBindings();
	bool isDualWielding = IsDualWielding();
	bool isUsingController = *(bool *)0x244DE98;
	if (!isUsingController && isDualWielding)
	{
		Blam::Input::ActionState *fireLeftAction = Blam::Input::GetActionState(Blam::Input::eGameActionFireLeft);
		Blam::Input::ActionState *fireRightAction = Blam::Input::GetActionState(Blam::Input::eGameActionFireRight);
		Blam::Input::ActionState tmp = *fireLeftAction;
		*fireLeftAction = *fireRightAction;
		*fireRightAction = tmp;
	}
	LocalPlayerInputHook(localPlayerIndex, playerIndex, a3, a4, a5, state);
	Modules::ModuleCamera::Instance().SetInputAngularVelocity(&state->aiming);
	if (moduleInput.VarToggleSprint->ValueInt)
	{
		if (s_SprintToggled)
		{
			unsigned long playerIndex = ((unsigned long (*const)(long))0x589C30)(localPlayerIndex);
			c_data_array<s_player_datum> *players = players_get();
			s_player_datum *player = players->try_and_get(playerIndex);
			if (player)
			{
				unsigned short ticksSprinting = Pointer(player)(0x2CE4, 1).Read<unsigned short>();
				if (!ticksSprinting)
					s_SprintToggled = false;
			}
		}
		if (Blam::Input::GetActionState(Blam::Input::eGameActionSprint)->GetDownTicks() == 1)
			s_SprintToggled = !s_SprintToggled;
		if (s_SprintToggled)
			state->unit_control_flags |= 0x100;
	}
	if (state->unit_control_flags & 0x10)
	{
		ControlGlobalsAction *controlGlobalsAction = GetPlayerControlsAction(localPlayerIndex);
		if (controlGlobalsAction->Type == 1 && (controlGlobalsAction->Flags & 4 || controlGlobalsAction->Flags & 8))
		{
			if (isUsingController)
				s_ConsumablesLocked = bindings->ControllerButtons[Blam::Input::eGameActionUseConsumable1] == bindings->ControllerButtons[Blam::Input::eGameActionPickUpLeft];
			else
				s_ConsumablesLocked = HasEqualBindingsDown(Blam::Input::eGameActionUseConsumable1, Blam::Input::eGameActionPickUpLeft, Blam::Input::eInputTypeGame);
		}
	}
	else
	{
		s_ConsumablesLocked = false;
	}
	if (isDualWielding)
	{
		if (!s_ConsumablesLocked)
			s_ConsumablesLocked = HasEqualBindingsDown(Blam::Input::eGameActionUseConsumable1, Blam::Input::eGameActionReloadLeft, Blam::Input::eInputTypeGame);
		if (bindings->ControllerButtons[Blam::Input::eGameActionMelee] == bindings->ControllerButtons[Blam::Input::eGameActionFireLeft])
			state->unit_control_flags &= ~0x20;
		if (bindings->ControllerButtons[Blam::Input::eGameActionThrowGrenade] == bindings->ControllerButtons[Blam::Input::eGameActionFireLeft])
			state->unit_control_flags &= ~0x10000000;
	}
	if (s_ConsumablesLocked)
		state->unit_control_flags &= ~0x10;
	if (Blam::Input::GetActionState(Blam::Input::eGameActionJump)->GetDownTicks() > 0 && ((bool (*)())0x67D270)())
		state->player_action_flags |= 0x1000;
	else
		state->player_action_flags &= ~0x1000;
	player_control_update_boots_off_ground(localPlayerIndex, state);
	bool (*const game_engine_is_forge)() = (bool (*)())0x59A780;
	if (game_engine_is_forge() && Modules::ModuleSettings::Instance().VarGamepadEnabled->ValueInt == 1)
	{
		Blam::Input::ActionState *flashlight_state = Blam::Input::GetActionState(Blam::Input::eGameActionFlashlight);
		if (flashlight_state->Msec < 500)
			state->unit_control_flags &= ~4;
		else
			state->unit_control_flags |= 4;
	}
}

bool InitializeDirectInput() // 0x10A79AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeDirectInput@@YA_NXZ");
	// `anonymous-namespace'::InitializeDirectInput
	// procedure flags: nofpo
	// HRESULT hr;
	// function call : HINSTANCE__ *(char const *)
	// function call : HRESULT (_GUID const &, IDirectInputDevice8A **, IUnknown *)
	// function call : HRESULT (HWND__ *, unsigned long)
	// function call : HRESULT (_DIDATAFORMAT const *)
	// function call : HRESULT ()

	if (g_diInitialized)
		return true;
	g_diInitialized = true;
	HRESULT hr = DirectInput8Create(GetModuleHandleA(NULL), 0x800, IID_IDirectInput8A, (void **)&g_diInterface, NULL);
	if (FAILED(hr))
		return false;
	hr = g_diInterface->CreateDevice(GUID_SysKeyboard, &g_diKeyboardDevice, NULL);
	if (FAILED(hr))
		return false;
	hr = g_diKeyboardDevice->SetCooperativeLevel(*(HWND__ **)0x199C014, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
		return false;
	hr = g_diKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		return false;
	hr = g_diKeyboardDevice->Acquire();
	if (FAILED(hr))
		return false;
	return true;
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

void update_keyboard_input_win32(long delta_msec, bool enabled, bool *out_input_detected) // 0x10A81CE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_keyboard_input_win32@@YAXJ_NPA_N@Z");
	// `anonymous-namespace'::update_keyboard_input_win32
	// bool *out_input_detected;
	// bool in_foreground;
		// long i;
			// Blam::Input::KeyState *key;
			// bool is_down;
	// function call : HWND__ *()
	// function call : short (__int32)

	bool in_foreground = *(HWND *)0x199C014 == GetForegroundWindow();
	for (long i = 0; i < 104; i++)
	{
		Blam::Input::KeyState *key = Blam::Input::GetKeyState((Blam::Input::KeyCode)i);
		bool is_down;
		if (enabled)
		{
			is_down = (::GetKeyState(((unsigned char *)0x1650918)[i]) & 0x8000) != 0;
			if (key->Msec == 1 && !key->Ticks && !is_down)
				is_down = true;
		}
		else
		{
			is_down = false;
		}
		if (is_down)
			*out_input_detected = true;
		update_key_state(key, is_down, delta_msec);
	}
}

void input_update_mouse(unsigned long milliseconds, long delta_milliseconds, bool enabled, bool *input_detected) // 0x10A7FB90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_update_mouse@@YAXKJ_NPA_N@Z");
	// `anonymous-namespace'::input_update_mouse
	// bool enabled;
	// bool *input_detected;
		// unsigned long v9;
		// long i;

	if (!input_globals.mouse_active)
		return;
	if (abs(input_globals.mouse.raw_x) || abs(input_globals.mouse.raw_y) || abs(input_globals.mouse.raw_z))
		*input_detected = true;
	input_globals.buffered_key_read_index = 0;
	input_globals.buffered_key_write_index = 0;
	input_globals.mouse.x = input_globals.field_B1C * (input_globals.mouse.raw_x / input_globals.field_B10);
	input_globals.mouse.y = input_globals.field_B20 * (input_globals.mouse.raw_y / input_globals.field_B14);
	if (input_globals.blocked_inputs[1])
	{
		input_globals.field_C68 = 0;
	}
	else
	{
		unsigned long v9 = input_globals.field_C68;
		if ((long)(milliseconds - input_globals.field_C68) <= 700)
		{
			input_globals.mouse.z = 0;
		}
		else
		{
			v9 = 0;
			input_globals.field_C68 = 0;
		}
		if (!(input_globals.field_B24 * (input_globals.mouse.raw_z / input_globals.field_B18)) || v9)
			goto skip_z;
		input_globals.field_C68 = milliseconds;
	}
	input_globals.mouse.z = input_globals.field_B24 * (input_globals.mouse.raw_z / input_globals.field_B18);
	skip_z:
	input_globals.mouse.raw_y %= input_globals.field_B14;
	input_globals.mouse.raw_x %= input_globals.field_B10;
	input_globals.mouse.raw_z %= input_globals.field_B18;
	input_globals.mouse.x += input_globals.mouse.raw_x;
	input_globals.mouse.y += input_globals.mouse.raw_y;
	input_globals.mouse.z += input_globals.mouse.raw_z;
	for (long i = 0; i < 5; i++)
	{
		if (enabled && (input_globals.mouse.button_mask & (1 << i)))
		{
			*input_detected = true;
			if (input_globals.mouse.down_frames[i] + 1 < 255)
				input_globals.mouse.down_frames[i]++;
			if (input_globals.mouse.down_milliseconds[i] + delta_milliseconds < 0xFFFF)
				input_globals.mouse.down_milliseconds[i] += (unsigned short)delta_milliseconds;
		}
		else
		{
			input_globals.mouse.down_frames[i] = 0;
			input_globals.mouse.down_milliseconds[i] = 0;
		}
	}
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

void update_threshold(unsigned char *threshold, bool is_pressed, unsigned char value) // 0x10A81E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_threshold@@YAXPAE_NE@Z");
	// `anonymous-namespace'::update_threshold
	// unsigned char value;
		// unsigned char new_Value;
		// unsigned char new_value;

	if (is_pressed)
	{
		unsigned char new_value = (unsigned char)(value >= 32 ? value - 32 : 0);
		if (new_value > *threshold)
			*threshold = new_value;
	}
	else
	{
		unsigned char new_value = (unsigned char)(value <= 191 ? value + 64 : 255);
		if (new_value < *threshold)
			*threshold = new_value;
	}
}

void apply_radial_deadzone(float &x, float &y, float deadzone) // 0x10A7E350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_radial_deadzone@@YAXAAM0M@Z");
	// `anonymous-namespace'::apply_radial_deadzone
	// float deadzone;
	// float const magnitude;
		// float const angle;
		// float const scale;

	float const magnitude = real_pin(sqrtf(x * x + y * y), -1.0f, 1.0f);
	if (magnitude <= deadzone)
	{
		x = 0.0f;
		y = 0.0f;
	}
	else
	{
		float const scale = (magnitude - deadzone) / (1.0f - deadzone);
		float const angle = atan2f(y, x);
		x = cosf(angle) * scale;
		y = sinf(angle) * scale;
	}
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

	float x = (float)thumb_x / 32767.0f;
	float y = (float)thumb_y / 32767.0f;
	x = apply_axial_deadzone(x, axial_deadzone);
	y = apply_axial_deadzone(y, axial_deadzone);
	if (radial_deadzone > 0.0f)
	{
		apply_radial_deadzone(x, y, radial_deadzone);
	}

	output->x = (short)(x * 32767.0f);
	output->y = (short)(y * 32767.0f);
}

void input_xinput_update_gamepad_core(long controller_index, long delta_milliseconds, _XINPUT_STATE const *xinput_data, s_gamepad_state *out_gamepad_data, s_debug_gamepad_data *out_debug_gamepad_data, bool *out_input_detected) // 0x10A80190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_xinput_update_gamepad_core@@YAXJJPBU_XINPUT_STATE@@PAUs_gamepad_state@@PAUs_debug_gamepad_data@@PA_N@Z");
	// `anonymous-namespace'::input_xinput_update_gamepad_core
	// bool *out_input_detected;
	// float left_axial_deadzone;
	// float right_radial_deadzone;
	// float left_radial_deadzone;
	// Modules::ModuleInput const &module_input;
	// float right_axial_deadzone;
		// long i;
			// bool trigger_pressed;
			// bool button_pressed;
		// float preferred_axial_deadzone;
		// long stick_layout;
		// float preferred_radial_deadzone;

	if (xinput_data->Gamepad.wButtons)
		*out_input_detected = true;
	if (xinput_data->Gamepad.bLeftTrigger >= 30 || xinput_data->Gamepad.bRightTrigger >= 30)
		*out_input_detected = true;
	if (abs(xinput_data->Gamepad.sThumbLX) >= 7849 || abs(xinput_data->Gamepad.sThumbLY) >= 7849)
		*out_input_detected = true;
	if (abs(xinput_data->Gamepad.sThumbRX) >= 8689 || abs(xinput_data->Gamepad.sThumbRY) >= 8689)
		*out_input_detected = true;
	for (long i = 0; i < 2; i++)
	{
		out_gamepad_data->trigger_values[i] = i > 0 ? xinput_data->Gamepad.bRightTrigger : xinput_data->Gamepad.bLeftTrigger;
		bool trigger_pressed = out_gamepad_data->trigger_values[i] > out_gamepad_data->trigger_thresholds[i];
		update_button(&out_gamepad_data->button_frames[i], &out_gamepad_data->button_milliseconds[i], trigger_pressed, delta_milliseconds);
		update_threshold(&out_gamepad_data->trigger_thresholds[i], trigger_pressed, out_gamepad_data->trigger_values[i]);
	}
	for (long i = 0; i < 14; i++)
	{
		bool button_pressed = (xinput_data->Gamepad.wButtons & ((unsigned long const *)0x166AAE8)[i]) > 0;
		update_button(&out_gamepad_data->button_frames[i + 2], &out_gamepad_data->button_milliseconds[i + 2], button_pressed, delta_milliseconds);
	}
	out_gamepad_data->left_thumb = { xinput_data->Gamepad.sThumbLX, xinput_data->Gamepad.sThumbLY };
	out_gamepad_data->right_thumb = { xinput_data->Gamepad.sThumbRX, xinput_data->Gamepad.sThumbRY };
	float left_axial_deadzone = 0.24f;
	float left_radial_deadzone = 0.0f;
	float right_axial_deadzone = 0.2f;
	float right_radial_deadzone = 0.0f;
	Modules::ModuleInput const &module_input = Modules::ModuleInput::Instance();
	if (module_input.VarControllerAimControl->ValueInt == 1)
	{
		long stick_layout = input_abstraction_globals.preferences[0].stick_layout;
		float preferred_axial_deadzone = (float)module_input.VarControllerAxialDeadzone->ValueInt / 100.0f;
		float preferred_radial_deadzone = (float)module_input.VarControllerRadialDeadzone->ValueInt / 100.0f;
		if (stick_layout == 1)
		{
			left_axial_deadzone = preferred_axial_deadzone;
			left_radial_deadzone = preferred_radial_deadzone;
		}
		else
		{
			if (stick_layout <= 3)
			{
				left_axial_deadzone = preferred_axial_deadzone;
				left_radial_deadzone = preferred_radial_deadzone;
			}
			right_axial_deadzone = preferred_axial_deadzone;
			right_radial_deadzone = preferred_radial_deadzone;
		}
	}
	apply_deadzone(&out_gamepad_data->left_thumb, xinput_data->Gamepad.sThumbLX, xinput_data->Gamepad.sThumbLY, left_axial_deadzone, left_radial_deadzone);
	apply_deadzone(&out_gamepad_data->right_thumb, xinput_data->Gamepad.sThumbRX, xinput_data->Gamepad.sThumbRY, right_axial_deadzone, right_radial_deadzone);
	if (Modules::ModuleInput::Instance().VarControllerInvertY->ValueInt)
	{
		if (out_gamepad_data->right_thumb.y == -32768)
			out_gamepad_data->right_thumb.y++;
		out_gamepad_data->right_thumb.y = -out_gamepad_data->right_thumb.y;
	}
}

bool input_xinput_update_gamepad(long controller_index, long delta_milliseconds, s_gamepad_state *out_gamepad_data, s_debug_gamepad_data *out_debug_gamepad_data, bool *out_input_detected) // 0x10A80040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_xinput_update_gamepad@@YA_NJJPAUs_gamepad_state@@PAUs_debug_gamepad_data@@PA_N@Z");
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

	HINSTANCE__ *hModule = *(HINSTANCE__ **)0x2497CEC;
	unsigned long (__stdcall *XInputGetStateFn)(unsigned long, _XINPUT_STATE *) = *(unsigned long (__stdcall **)(unsigned long, _XINPUT_STATE *))0x2497CE4;
	unsigned long (__stdcall *XInputSetStateFn)(unsigned long, _XINPUT_STATE *) = *(unsigned long (__stdcall **)(unsigned long, _XINPUT_STATE *))0x2497CE8;
	_XINPUT_STATE xinput_state;
	if (!hModule || !XInputGetStateFn || !XInputSetStateFn)
		return false;

	if (XInputGetStateFn(controller_index, &xinput_state))
	{
		memset(out_gamepad_data, 0, sizeof(out_gamepad_data));
		return false;
	}
	else
	{
		input_xinput_update_gamepad_core(controller_index, delta_milliseconds, &xinput_state, out_gamepad_data, out_debug_gamepad_data, out_input_detected);
		return true;
	}
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

void input_update_gamepads_rumble() // 0x10A7F710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_update_gamepads_rumble@@YAXXZ");
	// `anonymous-namespace'::input_update_gamepads_rumble
	// procedure flags: nofpo
	// void (*const input_xinput_update_rumble_state)(long, s_rumble_state *, bool);
	// bool disabled;
		// long i;
			// bool disable_index;
	// function call : bool (*const)()
	// function call : void (*const)(long, s_rumble_state *, bool)

	void (*const input_xinput_update_rumble_state)(long, s_rumble_state *, bool) = reinterpret_cast<void (*)(long, s_rumble_state *, bool)>(0x65F220);
	bool disabled = input_globals.feedback_supressed || input_globals.supressed;
	if (((bool (*)())0x531E90)())
		disabled = true;
	for (long i = 0; i < 4; i++)
	{
		bool disable_index = disabled || c_gui_screen_manager::get()->any_active_screens(i);
		input_xinput_update_rumble_state(i, &input_globals.rumble_states[i], disable_index);
	}
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

void input_update_hook() // 0x10A7F880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_update_hook@@YAXXZ");
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

	bool (*const game_in_editor)() = reinterpret_cast<bool (*)()>(0x42E130);
	bool (*const sub_42E000)() = reinterpret_cast<bool (*)()>(0x42E000);
	if (!input_globals.initialized || !input_globals.field_1 && (!game_in_editor() || !sub_42E000()))
		return;
	unsigned long milliseconds = system_milliseconds();
	long delta_milliseconds = milliseconds - input_globals.last_update_milliseconds;
	if (delta_milliseconds < 0)
		delta_milliseconds = 0;
	else if (delta_milliseconds >= 100)
		delta_milliseconds = 100;
	input_globals.supressed = false;
	input_globals.last_update_milliseconds = milliseconds;
	bool mkb_input_enabled = game_in_editor() || *(HWND *)0x199C014 == GetForegroundWindow();
	bool mkb_input_detected = false;
	bool gamepad_input_detected = false;
	input_update_keyboard(delta_milliseconds, mkb_input_enabled, &mkb_input_detected);
	input_update_mouse(milliseconds, delta_milliseconds, mkb_input_enabled, &mkb_input_detected);
	input_update_gamepads(delta_milliseconds, &gamepad_input_detected);
	input_update_gamepads_rumble();
	if (input_abstraction_globals.control_method == 1 && mkb_input_detected)
		set_control_method(0);
	else if (input_abstraction_globals.control_method == 0 && gamepad_input_detected)
		set_control_method(1);
	UpdateInputHook();
}

void normalize_thumbstick_classic(short thumb_x, short thumb_y, float *out_normalized_x, float *out_normalized_y, bool legacy, float legacy_threshold) // 0x10A80840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?normalize_thumbstick_classic@@YAXFFPAM0_NM@Z");
	// `anonymous-namespace'::normalize_thumbstick_classic
	// float legacy_threshold;
	// float const real_thumb_y;
	// float yaw;
	// float const angle;
	// float const real_thumb_x;
	// float const scale;
	// float const max_component;
	// float pitch;
		// float adjusted_angle;
		// float abs_adjusted_angle;
		// float magnitude;
			// float v30;
			// float v29;
			// float abs_angle;

	float const scale = 1.0f / 32767.0f;
	float const real_thumb_x = thumb_x;
	float const real_thumb_y = thumb_y;
	float const angle = atan2f(real_thumb_y, real_thumb_x);
	float const max_component = fmaxf(fabs(sinf(angle)), fabs(cosf(angle)));
	float yaw = real_pin(real_thumb_x * scale / max_component, -1.0f, 1.0f);
	float pitch = real_pin(real_thumb_y * scale / max_component, -1.0f, 1.0f);
	if (legacy)
	{
		if (!(input_abstraction_globals.legacy_flags & 1))
		{
			input_abstraction_globals.legacy_flags |= 1;
			input_abstraction_globals.legacy_function[0] = 0.78539819f;
			input_abstraction_globals.legacy_function[1] = 2.3561945f;
			input_abstraction_globals.legacy_function[2] = -0.78539819f;
			input_abstraction_globals.legacy_function[3] = -2.3561945f;
		}
		float adjusted_angle = angle - input_abstraction_globals.legacy_function[(yaw < 0.0f ? 1 : 0) | (pitch < 0.0f ? 2 : 0)];
		float magnitude = sqrtf(pitch * pitch + yaw * yaw);
		float abs_adjusted_angle = fabs(adjusted_angle);
		if (abs_adjusted_angle >= legacy_threshold)
		{
			float v29 = fabs(yaw);
			float v30 = fabs(pitch);
			if (v29 > v30)
			{
				pitch = 0.0f;
				yaw = (2 * (yaw >= 0.0f) - 1) * magnitude;
			}
			else
			{
				yaw = 0.0f;
				pitch = (2 * (pitch >= 0.0f) - 1) * magnitude;
			}
		}
		else
		{
			float abs_angle = fabs(angle);
			if (abs_angle >= 0.78539819f && abs_angle <= 2.3561945f)
			{
				pitch = (2 * (pitch >= 0.0f) - 1) * magnitude;
				yaw = (1.0f - abs_adjusted_angle / 0.61086524f) * ((2 * (yaw >= 0.0f) - 1) * magnitude);
			}
			else
			{
				pitch = (2 * (pitch >= 0.0f) - 1) * magnitude * (1.0f - abs_adjusted_angle / 0.61086524f);
				yaw = (2 * (yaw >= 0.0f) - 1) * magnitude;
			}
		}
		pitch = real_pin(pitch, -1.0f, 1.0f);
		yaw = real_pin(yaw, -1.0f, 1.0f);
	}
	*out_normalized_x = yaw;
	*out_normalized_y = pitch;
}

void normalize_thumbstick_modern(short thumb_x, short thumb_y, float *out_normalized_x, float *out_normalized_y) // 0x10A80F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?normalize_thumbstick_modern@@YAXFFPAM0@Z");
	// `anonymous-namespace'::normalize_thumbstick_modern
	// float *out_normalized_y;

	*out_normalized_x = real_pin((float)thumb_x * 1.0f / 32767.0f, -1.0f, 1.0f);
	*out_normalized_y = real_pin((float)thumb_y * 1.0f / 32767.0f, -1.0f, 1.0f);
}

void input_abstraction_update_gamepad(s_gamepad_state const *gamepad_state, s_game_input_preferences const *preferences, s_game_input_state *input_state, long controller_index) // 0x10A7EB40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_abstraction_update_gamepad@@YAXPBUs_gamepad_state@@PBUs_game_input_preferences@@PAUs_game_input_state@@J@Z");
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
		// bool legacy;
		// long i;
			// unsigned short down_msec;
			// unsigned char down_frames;
			// c_abstract_button *abstract_button;
			// long button_index;
			// unsigned char down_amount;
	// function call : bool (*const)(long)
	// function call : bool (*const)(long)

	bool (*const input_blocked)(long) = reinterpret_cast<bool (*)(long)>(0x511B50);
	input_state->left_thumb_x = gamepad_state->left_thumb.x;
	input_state->left_thumb_y = gamepad_state->left_thumb.y;
	input_state->right_thumb_x = gamepad_state->right_thumb.x;
	input_state->right_thumb_y = gamepad_state->right_thumb.y;
	input_state->field_324 = 0.0f;
	float left_thumb_x = 0.0f;
	float left_thumb_y = 0.0f;
	float right_thumb_x = 0.0f;
	float right_thumb_y = 0.0f;
	if (!input_blocked(1))
	{
		if (Modules::ModuleInput::Instance().VarControllerAimControl->ValueInt == 1)
		{
			normalize_thumbstick_modern(gamepad_state->left_thumb.x, gamepad_state->left_thumb.y, &left_thumb_x, &left_thumb_y);
			normalize_thumbstick_modern(gamepad_state->right_thumb.x, gamepad_state->right_thumb.y, &right_thumb_x, &right_thumb_y);
		}
		else
		{
			bool legacy = preferences->stick_layout == 2 || preferences->stick_layout == 3;
			normalize_thumbstick_classic(gamepad_state->left_thumb.x, gamepad_state->left_thumb.y, &left_thumb_x, &left_thumb_y, legacy, 0.61086518f);
			normalize_thumbstick_classic(gamepad_state->right_thumb.x, gamepad_state->right_thumb.y, &right_thumb_x, &right_thumb_y, legacy, 0.17453292f);
		}
	}
	for (long i = 0; i < 59; i++)
	{
		long button_index = preferences->button_remap[i];
		if (input_blocked(1) && i >= 16)
			break;
		if (button_index >= 16)
			continue;
		c_abstract_button *abstract_button = &input_state->buttons[i];
		unsigned short down_msec = gamepad_state->button_milliseconds[button_index];
		unsigned char down_frames = gamepad_state->button_frames[button_index];
		unsigned char down_amount = button_index < 2 ? gamepad_state->trigger_values[button_index] : (down_frames ? 0xFF : 0);
		if (preferences->hold_buttons[i] && down_msec <= 233)
			abstract_button->unlatch();
		else
			abstract_button->update(down_msec, down_frames, down_amount);
	}
	switch (preferences->stick_layout)
	{
	case 1:
		input_state->forward = right_thumb_y;
		input_state->strafe = -right_thumb_x;
		input_state->yaw = -left_thumb_x;
		input_state->pitch = left_thumb_y;
		input_state->field_31C = left_thumb_y;
		break;
	case 2:
		input_state->forward = left_thumb_y;
		input_state->strafe = -right_thumb_x;
		input_state->yaw = -left_thumb_x;
		input_state->pitch = right_thumb_y;
		input_state->field_31C = right_thumb_y;
		break;
	case 3:
		input_state->forward = right_thumb_y;
		input_state->strafe = -left_thumb_x;
		input_state->yaw = -right_thumb_x;
		input_state->pitch = left_thumb_y;
		input_state->field_31C = left_thumb_y;
		break;
	default:
		input_state->forward = left_thumb_y;
		input_state->strafe = -left_thumb_x;
		input_state->yaw = -right_thumb_x;
		input_state->pitch = right_thumb_y;
		input_state->field_31C = right_thumb_y;
		break;
	}
	input_state->vehicle_forward = input_state->forward;
	input_state->vehicle_yaw = input_state->yaw;
	input_state->vehicle_ground_pitch = input_state->pitch;
	input_state->field_320 = input_state->field_31C;
	if (preferences->pitch_inverted)
		input_state->pitch = input_state->pitch * -1.0f;
	input_state->vehicle_aircraft_pitch = input_state->pitch;
	if (!preferences->pitch_inverted && preferences->vehicle_pitch_inverted)
		input_state->vehicle_aircraft_pitch = input_state->vehicle_aircraft_pitch * -1.0f;
	if (!input_abstraction_globals.active_gamepads[controller_index])
		input_abstraction_globals.active_gamepads[controller_index] = true;
}

void input_abstraction_update_hook() // 0x10A7F2A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?input_abstraction_update_hook@@YAXXZ");
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
		// long i;
	// function call : s_gamepad_state *(*const)(long)
	// function call : bool (*const)()
	// function call : s_mouse_state *(*const)(long)
	// function call : void (*const)(s_mouse_state *, s_game_input_state *, long)
	// function call : void (*const)(s_game_input_preferences *, s_game_input_state *)

	s_gamepad_state *(*const input_get_gamepad_state)(long) = reinterpret_cast<s_gamepad_state *(*)(long)>(0x511840);
	void (*const input_abstraction_set_control_method)(long) = reinterpret_cast<void (*)(long)>(0x60D7B0);
	s_mouse_state *(*const input_get_mouse_state)(long) = reinterpret_cast<s_mouse_state *(*)(long)>(0x5119F0);
	void (*const input_abstraction_update_keyboard)(s_game_input_preferences *, s_game_input_state *) = reinterpret_cast<void (*)(s_game_input_preferences *, s_game_input_state *)>(0x60C4A0);
	void (*const input_abstraction_process_mouse)(s_mouse_state *, s_game_input_state *, long) = reinterpret_cast<void (*)(s_mouse_state *, s_game_input_state *, long)>(0x60D160);
	void (*const input_abstraction_process_keyboard)(s_game_input_preferences *, s_game_input_state *) = reinterpret_cast<void (*)(s_game_input_preferences *, s_game_input_state *)>(0x60D620);
	char (*const input_abstraction_update_mouse)(s_game_input_preferences *, s_game_input_state *) = reinterpret_cast<char (*)(s_game_input_preferences *, s_game_input_state *)>(0x60CE70);
	bool (*const user_interface_is_active)() = reinterpret_cast<bool (*)()>(0xA84840);
	unsigned long milliseconds = system_milliseconds();
	long delta_milliseconds = milliseconds - input_abstraction_globals.last_update_milliseconds;
	input_abstraction_globals.last_update_milliseconds = milliseconds;
	if (delta_milliseconds < 0)
		delta_milliseconds = 0;
	if (delta_milliseconds > 100)
		delta_milliseconds = 100;
	s_gamepad_state *gamepad_data = nullptr;
	for (long i = 0; i < 4; i++)
	{
		gamepad_data = input_get_gamepad_state(i);
		if (gamepad_data)
			break;
	}
	for (long i = 0; i < k_abstract_button_count; i++)
	{
		input_abstraction_globals.input_states[0].buttons[i].down_frames = 0;
		input_abstraction_globals.input_states[0].buttons[i].down_amount = 0.0f;
		input_abstraction_globals.input_states[0].buttons[i].down_msec = 0;
	}
	long control_method = input_abstraction_globals.control_method;
	if (gamepad_data && control_method == 1)
	{
		input_abstraction_update_gamepad(gamepad_data, input_abstraction_globals.preferences, input_abstraction_globals.input_states, 0);
	}
	else
	{
		ProcessKeyBindingsHook(*reinterpret_cast<BindingsTable *>(input_abstraction_globals.preferences), reinterpret_cast<ActionState *>(input_abstraction_globals.input_states));
		if (!user_interface_is_active())
			ProcessMouseBindingsHook(*reinterpret_cast<BindingsTable *>(input_abstraction_globals.preferences), reinterpret_cast<ActionState *>(input_abstraction_globals.input_states));
		input_abstraction_process_mouse(input_get_mouse_state(0), input_abstraction_globals.input_states, delta_milliseconds);
		input_abstraction_process_keyboard(input_abstraction_globals.preferences, input_abstraction_globals.input_states);
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::Write<Blam::Input::ConfigurableAction *>(Blam::Input::ConfigurableAction *const) const;

/* ---------- explicit instantiations */
template unsigned short & Pointer::Read<unsigned short>() const;
