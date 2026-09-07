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

namespace Patches
{
	namespace Input
	{
		extern void ApplyAll();
		extern void PushContext(std::shared_ptr<Patches::Input::InputContext> context);
		extern void RegisterDefaultInputHandler(void (*func)());
		extern void RegisterMenuUIInputHandler(void (*func)());
		extern void SetKeyboardSettingsMenu(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &infantrySettings, std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &vehicleSettings);
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
namespace Blam
{
	namespace Input
	{
		BindingsPreferences *PreferencesGetKeyBindingsHook(Blam::Input::BindingsPreferences *result);
	}
}

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

c_gui_screen_widget *(*c_gui_location_manager::get_location_gui_screen)(); // 0x1135459C

/* ---------- private variables */

namespace hades_file_local
{
	extern std::stack<std::shared_ptr<Patches::Input::InputContext>,std::deque<std::shared_ptr<Patches::Input::InputContext>,std::allocator<std::shared_ptr<Patches::Input::InputContext> > > > contextStack; // 0x12458880
	extern std::vector<void (__cdecl*)(void),std::allocator<void (__cdecl*)(void)> > defaultHandlers; // 0x12458850
	extern std::vector<void (__cdecl*)(void),std::allocator<void (__cdecl*)(void)> > uiHandlers; // 0x12458870
	extern bool contextDone; // 0x12458894
	extern bool blockStates[3]; // 0x124588A0
	extern std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > settings; // 0x12458860
	extern Blam::Input::InputType actionInputTypes[63]; // 0x11354458
	extern Blam::Input::BindingsTable s_ForgeMonitorModeBindings; // 0x124588A8
	extern unsigned __int32 s_ControllerVibrationTestTicks; // 0x124588A4
	extern unsigned __int32 bindingsNextUpdateTicks; // 0x11354454
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

		_extern void _sub_10A7AD30(void (*)());
		void RegisterDefaultInputHandler(void (*func)()) // 0x10A7AD30
		{
			mangled_x86(MANGLED_TODO, "?RegisterDefaultInputHandler@Input@Patches@@YAXP6AXXZ@Z");
			// void (*func)();
			todo("implement");
			_sub_10A7AD30(func);
		}

		_extern void _sub_10A7AD80(void (*)());
		void RegisterMenuUIInputHandler(void (*func)()) // 0x10A7AD80
		{
			mangled_x86(MANGLED_TODO, "?RegisterMenuUIInputHandler@Input@Patches@@YAXP6AXXZ@Z");
			// void (*func)();
			todo("implement");
			_sub_10A7AD80(func);
		}

		_extern void _sub_10A7AEB0(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &, std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &);
		void SetKeyboardSettingsMenu(std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &infantrySettings, std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &vehicleSettings) // 0x10A7AEB0
		{
			mangled_x86(MANGLED_TODO, "?SetKeyboardSettingsMenu@Input@Patches@@YAXABV?$vector@UConfigurableAction@Input@Blam@@V?$allocator@UConfigurableAction@Input@Blam@@@std@@@std@@0@Z");
			// static ...; // 0x10A7B567
			// static ...; // 0x10A7B55B
			// static ...; // 0x10A7B545
			// static ...; // 0x10A7B530
			// static ...; // 0x10A7B4F4
			// static ...; // 0x10A7B4EC
			// std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &infantrySettings;
			// std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > const &vehicleSettings;
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

		_extern void _sub_10A7B740(float);
		void TestControllerVibration(float durationSeconds) // 0x10A7B740
		{
			mangled_x86(MANGLED_TODO, "?TestControllerVibration@Input@Patches@@YAXM@Z");
			// float durationSeconds;
			// function call : long (*const)(float)
			todo("implement");
			_sub_10A7B740(durationSeconds);
		}

		_extern void _sub_10A79CA0();
		void InvalidateBindings() // 0x10A79CA0
		{
			mangled_x86(MANGLED_TODO, "?InvalidateBindings@Input@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A79CA0();
		}
	}
}

/* ---------- private code */

_extern void _sub_10A81040();
void null_stub() // 0x10A81040
{
	// `anonymous-namespace'::null_stub
	// procedure flags: nofpo
	todo("implement");
	_sub_10A81040();
}

_extern void _sub_10A7A430();
void PopContext() // 0x10A7A430
{
	// `anonymous-namespace'::PopContext
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	// function call : void ()
	// function call : void ()
	todo("implement");
	_sub_10A7A430();
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
		// std::vector<void (__cdecl*)(void),std::allocator<void (__cdecl*)(void)> > &<range>$L0;
		// void (**<begin>$L0)();
		// void (**<end>$L0)();
		{
			// void (*&handler)();
		}
	}
	{
		// void (**<end>$L1)();
		// void (**<begin>$L1)();
		// std::vector<void (__cdecl*)(void),std::allocator<void (__cdecl*)(void)> > &<range>$L1;
		{
		}
	}
	{
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
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

_extern void _sub_10A7B7C0();
void UiInputTick() // 0x10A7B7C0
{
	// `anonymous-namespace'::UiInputTick
	// procedure flags: nofpo
	// function call : void ()
	// function call : bool ()
	// function call : void ()
	todo("implement");
	_sub_10A7B7C0();
}

_extern void _sub_10A7AB30();
void ProcessUiInputHook() // 0x10A7AB30
{
	// `anonymous-namespace'::ProcessUiInputHook
	// procedure flags: nofpo
	todo("implement");
	_sub_10A7AB30();
}

_extern void _sub_10A7ACD0();
void QuickUpdateUiInputHook() // 0x10A7ACD0
{
	// `anonymous-namespace'::QuickUpdateUiInputHook
	// procedure flags: nofpo
	// void (*QuickPumpMessages)();
	// function call : void (*)()
	todo("implement");
	_sub_10A7ACD0();
}

_extern void _sub_10A79380(Blam::Input::InputType, bool);
void BlockInputHook(Blam::Input::InputType type, bool blocked) // 0x10A79380
{
	// `anonymous-namespace'::BlockInputHook
	// bool blocked;
	todo("implement");
	_sub_10A79380(type, blocked);
}

_extern void _sub_10A7B8F0();
void UpdateForgeMonitorBindings() // 0x10A7B8F0
{
	// `anonymous-namespace'::UpdateForgeMonitorBindings
	// procedure flags: nofpo
	todo("implement");
	_sub_10A7B8F0();
}

_extern void _sub_10A79A80(Blam::Input::BindingsTable *);
void InitBindingsHook(Blam::Input::BindingsTable *bindings) // 0x10A79A80
{
	// `anonymous-namespace'::InitBindingsHook
	// Blam::Input::BindingsTable *bindings;
	todo("implement");
	_sub_10A79A80(bindings);
}

namespace Blam
{
	namespace Input
	{
		extern BindingsPreferences *_sub_10A7A550(Blam::Input::BindingsPreferences *);
		BindingsPreferences *PreferencesGetKeyBindingsHook(Blam::Input::BindingsPreferences *result) // 0x10A7A550
		{
			// `anonymous-namespace'::PreferencesGetKeyBindingsHook
			// Blam::Input::BindingsPreferences *result;
			// Blam::Input::BindingsTable *bindings;
			todo("implement");
			Blam::Input::BindingsPreferences * __result = _sub_10A7A550(result);
			return __result;
		}
	}
}

_extern void _sub_10A7A620(Blam::Input::BindingsPreferences);
void PreferencesSetKeyBindingsHook(Blam::Input::BindingsPreferences newBindings) // 0x10A7A620
{
	// `anonymous-namespace'::PreferencesSetKeyBindingsHook
	// Blam::Input::BindingsPreferences newBindings;
	// Blam::Input::BindingsTable *bindings;
	todo("implement");
	_sub_10A7A620(newBindings);
}

_extern void _sub_10A793F0(__int32, Blam::Input::BindingsTable *);
void GetDefaultBindingsHook(__int32 type, Blam::Input::BindingsTable *result) // 0x10A793F0
{
	// `anonymous-namespace'::GetDefaultBindingsHook
	// Blam::Input::BindingsTable *result;
	todo("implement");
	_sub_10A793F0(type, result);
}

extern void _sub_10A794B0();
__declspec(naked) void GetKeyboardActionTypeHook() // 0x10A794B0
{
	// `anonymous-namespace'::GetKeyboardActionTypeHook
	// procedure flags: nofpo
	todo("implement");
	_sub_10A794B0();
}

_extern bool _sub_10A79A00();
bool InMonitorMode() // 0x10A79A00
{
	// `anonymous-namespace'::InMonitorMode
	// procedure flags: nofpo
	// static bool (*`InMonitorMode'::`2'::Forge_GetEditorModeState)(unsigned __int32, unsigned __int32 *, unsigned __int32 *); // 0x11354554
	// function call : unsigned long (*const)(long)
	// function call : bool (*)(unsigned __int32, unsigned __int32 *, unsigned __int32 *)
	todo("implement");
	bool __result = _sub_10A79A00();
	return __result;
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

_extern void _sub_10A7AA80(Blam::Input::BindingsTable const &, Blam::Input::ActionState *);
void ProcessMouseBindingsHook(Blam::Input::BindingsTable const &bindings, Blam::Input::ActionState *actions) // 0x10A7AA80
{
	// `anonymous-namespace'::ProcessMouseBindingsHook
	// Blam::Input::ActionState *actions;
	// static void (*`ProcessMouseBindingsHook'::`2'::ProcessMouseBindings)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *); // 0x11354558
	// function call : void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)
	// function call : void (*)(Blam::Input::BindingsTable const &, Blam::Input::ActionState *)
	todo("implement");
	_sub_10A7AA80(bindings, actions);
}

_extern void _sub_10A7BE10(__int32);
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
	{
		// std::chrono::duration<double,std::ratio<1,1> > elapsedTime;
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
		{
			// float angle;
		}
	}
	{
		// std::vector<void (__cdecl*)(void),std::allocator<void (__cdecl*)(void)> > &<range>$L0;
		// void (**<begin>$L0)();
		// void (**<end>$L0)();
		{
			// void (*&handler)();
		}
	}
	// function call : c_gui_screen_widget *(*)()
	// function call : void (*)(__int32)
	// function call : bool (*const)()
	// function call : long ()
	// function call : long ()
	// function call : void (*)()
	// function call : void (*)()
	todo("implement");
	_sub_10A7BE10(a0);
}

_extern void _sub_10A7ADD0(__int32, unsigned short, unsigned short);
void SetControllerVibrationHook(__int32 controllerIndex, unsigned short leftMotorSpeed, unsigned short rightMotorSpeed) // 0x10A7ADD0
{
	// `anonymous-namespace'::SetControllerVibrationHook
	// unsigned short rightMotorSpeed;
	// Modules::ModuleInput const &moduleInput;
	// SetControllerVibrationHook::__l2::CONTROLLER_VIBRATION &vibration;
	// float intensity;
	todo("implement");
	_sub_10A7ADD0(controllerIndex, leftMotorSpeed, rightMotorSpeed);
}

_extern bool _sub_10A79CD0();
bool IsDualWielding() // 0x10A79CD0
{
	// `anonymous-namespace'::IsDualWielding
	// procedure flags: nofpo
	// s_unit_data *unit;
	// long unit_index;
	todo("implement");
	bool __result = _sub_10A79CD0();
	return __result;
}

_extern bool _sub_10A794D0(Blam::Input::GameAction, Blam::Input::GameAction, Blam::Input::InputType);
bool HasEqualBindingsDown(Blam::Input::GameAction action1, Blam::Input::GameAction action2, Blam::Input::InputType inputType) // 0x10A794D0
{
	// `anonymous-namespace'::HasEqualBindingsDown
	// Blam::Input::InputType inputType;
	// bool isUsingController;
	// Blam::Input::BindingsTable *bindings;
	// Modules::ModuleInput &moduleInput;
	{
		// Blam::Input::ActionState *action2State;
		// Blam::Input::ActionState *action1State;
	}
	{
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
	}
	todo("implement");
	bool __result = _sub_10A794D0(action1, action2, inputType);
	return __result;
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

_extern void _sub_10A81A40(Blam::Input::KeyState *, bool, long);
void update_key_state(Blam::Input::KeyState *key, bool is_down, long delta_msec) // 0x10A81A40
{
	// `anonymous-namespace'::update_key_state
	// long delta_msec;
	todo("implement");
	_sub_10A81A40(key, is_down, delta_msec);
}

_extern void _sub_10A81B00(long, bool, bool *);
void update_keyboard_input_di(long delta_msec, bool enabled, bool *input_detected) // 0x10A81B00
{
	// `anonymous-namespace'::update_keyboard_input_di
	// static ...; // 0x10A81C5C
	// long delta_msec;
	// bool enabled;
	// bool *input_detected;
	// unsigned char diKeys[256];
	{
		// long i;
		{
			// Blam::Input::KeyState *key;
			// bool is_down;
		}
	}
	// function call : HRESULT (unsigned long, void *)
	todo("implement");
	_sub_10A81B00(delta_msec, enabled, input_detected);
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

_extern void _sub_10A7FB10(long, bool, bool *);
void input_update_keyboard(long delta_milliseconds, bool enabled, bool *out_input_detected) // 0x10A7FB10
{
	// `anonymous-namespace'::input_update_keyboard
	// bool *out_input_detected;
	todo("implement");
	_sub_10A7FB10(delta_milliseconds, enabled, out_input_detected);
}

_extern void _sub_10A81970(unsigned char *, unsigned short *, bool, unsigned long);
void update_button(unsigned char *frames, unsigned short *milliseconds, bool is_pressed, unsigned long delta_milliseconds) // 0x10A81970
{
	// `anonymous-namespace'::update_button
	// unsigned long delta_milliseconds;
	todo("implement");
	_sub_10A81970(frames, milliseconds, is_pressed, delta_milliseconds);
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

_extern float _sub_10A7E120(float, float);
float apply_axial_deadzone(float x, float deadzone) // 0x10A7E120
{
	// `anonymous-namespace'::apply_axial_deadzone
	// float deadzone;
	todo("implement");
	float __result = _sub_10A7E120(x, deadzone);
	return __result;
}

_extern void _sub_10A7E1D0(short_point_2d *, short, short, float, float);
void apply_deadzone(short_point_2d *output, short thumb_x, short thumb_y, float axial_deadzone, float radial_deadzone) // 0x10A7E1D0
{
	// `anonymous-namespace'::apply_deadzone
	// short_point_2d *output;
	// short thumb_x;
	// short thumb_y;
	// float axial_deadzone;
	// float radial_deadzone;
	// float x;
	// float y;
	todo("implement");
	_sub_10A7E1D0(output, thumb_x, thumb_y, axial_deadzone, radial_deadzone);
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

_extern void _sub_10A7F5E0(long, bool *);
void input_update_gamepads(long delta_milliseconds, bool *out_input_detected) // 0x10A7F5E0
{
	// `anonymous-namespace'::input_update_gamepads
	// bool *out_input_detected;
	// long port;
	{
		// long i;
		{
			// s_gamepad_state *gamepad_state;
		}
	}
	todo("implement");
	_sub_10A7F5E0(delta_milliseconds, out_input_detected);
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

_extern void _sub_10A815F0(long);
void set_control_method(long method) // 0x10A815F0
{
	// `anonymous-namespace'::set_control_method
	// long method;
	// function call : void (*const)(long)
	todo("implement");
	_sub_10A815F0(method);
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

_extern void _sub_10A80F50(short, short, float *, float *);
void normalize_thumbstick_modern(short thumb_x, short thumb_y, float *out_normalized_x, float *out_normalized_y) // 0x10A80F50
{
	// `anonymous-namespace'::normalize_thumbstick_modern
	// float *out_normalized_y;
	todo("implement");
	_sub_10A80F50(thumb_x, thumb_y, out_normalized_x, out_normalized_y);
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
