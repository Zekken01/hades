/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/player_control.hpp"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/main/game_preferences.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_global_preferences;
struct s_global_preferences_settings;
struct s_player_control_input_state;
struct s_player_datum;
namespace hades_file_local
{
	struct RawMouseState;
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
namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace RawInput {}
	using namespace Patches::RawInput;
	namespace Camera {}
	using namespace Patches::Camera;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct RawMouseState
	{
	    enum
		{
			eButtonLeft = (1 << 0),
			eButtonMiddle = (1 << 1),
			eButtonRight = (1 << 2),
			eButton4 = (1 << 3),
			eButton5 = (1 << 4),
		};
		unsigned char buttons; // 0x0
		unsigned char __pad0[3]; // 0x1
		__int32 deltaX; // 0x4
		__int32 deltaY; // 0x8
		__int32 wheelDelta; // 0xC
	};
	static_assert(sizeof(RawMouseState) == 16, "Invalid RawMouseState size");
}
using namespace hades_file_local;
/* ---------- prototypes */

#include "Modules/ModuleInput.hpp"  // hades: added for 0x10ABF380
#include "Blam/camera/camera.hpp"  // hades: added for 0x10ABF380
namespace Patches { namespace Camera { extern e_camera_mode GetForcedCameraMode(); } }  // hades: added for 0x10ABF380

namespace Patches
{
	namespace RawInput
	{
		extern void ApplyAll();
		extern void UpdateCameraYawPitch(float deltaX, float deltaY, float &yaw, float &pitch);
	}
}

bool ShouldDisableRawInput();
bool RawInputHookImpl(tagRAWINPUT *rwInput);
void RawInputHook(__int32 unused, unsigned __int32 wParam, HRAWINPUT__ *hRawInput);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace RawInput
	{
		void ApplyAll() // 0x10ABEF90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@RawInput@Patches@@YAXXZ");
			// procedure flags: nofpo
			// Hook the input handling routine to fix mouse acceleration

			Hook(0x2E7A9, RawInputHook, 1).Apply();
		}

		void UpdateCameraYawPitch(float deltaX, float deltaY, float &yaw, float &pitch) // 0x10ABF8E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateCameraYawPitch@RawInput@Patches@@YAXMMAAM0@Z");
			// float &pitch;
			// s_global_preferences_settings::s_input_settings *const input_settings;
			// float weaponSensitivity;
			// long player_index;
			// float maxVertAngle;
			// float yaxisSens;
			// s_global_preferences *prefs;
			// float xaxisSens;
			// function call : unsigned long (*const)(long)
			// function call : bool (*const)(long)

			float weaponSensitivity = Pointer::Base(0x4CDEF14).Read<float>();
			float maxVertAngle = Pointer::Base(0x14B49E4).Read<float>();
			if (weaponSensitivity <= 0.0001f)
				return;

			s_global_preferences *prefs = tls_getd().preferences;
			if (!prefs)
				prefs = (s_global_preferences *)0x22C0128;
			s_global_preferences_settings::s_input_settings *const input_settings = &prefs->current.settings.input_settings;
			float yaxisSens = input_settings->mouse_sensitivity_vertical / 25.0f;
			float xaxisSens = input_settings->mouse_sensitivity_horizontal / 25.0f;
			long player_index = ((unsigned long (__cdecl *)(long))0x589C30)(0);
			if (player_index != -1 && ((bool (__cdecl *)(long))0x58DE40)(player_index))
			{
				yaxisSens = input_settings->mouse_sensitivity_vehicle_vertical / 25.0f;
				xaxisSens = input_settings->mouse_sensitivity_vehicle_horizontal / 25.0f;
			}

			if (input_settings->invert_mouse)
				pitch += deltaY * yaxisSens / 1000.0f / weaponSensitivity;
			else
				pitch -= deltaY * yaxisSens / 1000.0f / weaponSensitivity;

			if (pitch > maxVertAngle)
				pitch = maxVertAngle;
			else if (0.0f - maxVertAngle > pitch)
				pitch = 0.0f - maxVertAngle;

			yaw -= deltaX * xaxisSens / 1000.0f / weaponSensitivity;
		}
	}
}

/* ---------- private code */

bool ShouldDisableRawInput() // 0x10ABF5C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShouldDisableRawInput@@YA_NXZ");
	// `anonymous-namespace'::ShouldDisableRawInput
	// procedure flags: nofpo
	// static ...; // 0x10ABF82C
	// static ...; // 0x10ABF820
	// static ...; // 0x10ABF818
	// bool (*const game_engine_round_in_progress)();
		// s_player_datum *player;
		// long heldObjectIndex;
		// bool leftMouseDown;
		// unsigned long playerIndex;
		// short activeScreenCount;
	// function call : bool (*const)()
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)

	bool (*const game_engine_round_in_progress)() = reinterpret_cast<bool (*)()>(0x550F90);
	if (game_engine_round_in_progress())
	{
		unsigned long playerIndex = ((unsigned long (*const)(long))0x589C30)(0);
		s_player_datum *player = nullptr;
		if (playerIndex == -1 || !(player = players_get()->try_and_get(playerIndex)))
			return false;
		short activeScreenCount = Pointer(0x5260F34)[0](0x3C, 1).Read<short>();
		if (activeScreenCount > 0)
			return true;
		bool leftMouseDown = *(unsigned char *)0x238E6AC > 0;
		long heldObjectIndex;
		if (((bool (*const)(long, long *, long *))0x59A6F0)(playerIndex, &heldObjectIndex, nullptr) && heldObjectIndex != -1 && leftMouseDown)
			return true;
		return player && player->unit_index == -1;
	}
	return false;
}

bool RawInputHookImpl(tagRAWINPUT *rwInput) // 0x10ABF380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RawInputHookImpl@@YA_NPAUtagRAWINPUT@@@Z");
	// `anonymous-namespace'::RawInputHookImpl
	// tagRAWINPUT *rwInput;
	// bool (*const game_is_mainmenu)();
	// bool inhibit_movement;
	// bool controllerEnabled;
	// s_player_control_input_state *player_control;
	// bool isFlying;
	// function call : bool (*const)()
	// function call : bool (*const)(__int32)

	bool (*const game_is_mainmenu)() = reinterpret_cast<bool (*)()>(0x531E90);
	bool isFlying = Patches::Camera::GetForcedCameraMode() == _camera_mode_flying;
	if (isFlying)
		return false;
	bool controllerEnabled = Pointer::Base(0x204DE98, 1).Read<bool>();
	if (controllerEnabled && !isFlying)
		return true;
	if (!Utils::Singleton<Modules::ModuleInput>::Instance().VarInputRawInput->ValueInt)
		return false;
	if (rwInput->header.dwType != RIM_TYPEMOUSE)
		return true;
	if (ShouldDisableRawInput())
		return false;
	bool inhibit_movement = !game_is_mainmenu() && reinterpret_cast<bool (*)(long)>(0x725AA0)(0);
	s_player_control_input_state *player_control = player_control_input_get(0);
	Patches::RawInput::UpdateCameraYawPitch((float)rwInput->data.mouse.lLastX, (float)rwInput->data.mouse.lLastY, player_control->state.desired_angles.yaw, player_control->state.desired_angles.pitch);
	return true;
}

void RawInputHook(__int32 unused, unsigned __int32 wParam, HRAWINPUT__ *hRawInput) // 0x10ABF0F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RawInputHook@@YAXHIPAUHRAWINPUT__@@@Z");
	// `anonymous-namespace'::RawInputHook
	// static ...; // 0x10ABF2D8
	// static ...; // 0x10ABF2D0
	// __int32 unused;
	// unsigned __int32 wParam;
	// HRAWINPUT__ *hRawInput;
	// RawMouseState *mouseState;
	// bool const mouseEnabled;
	// unsigned __int32 cbSize;
	// tagRAWINPUT input;
	// function call : unsigned __int32 (HRAWINPUT__ *, unsigned __int32, void *, unsigned __int32 *, unsigned __int32)

	bool const mouseEnabled = *(bool *)0x512356;
	RawMouseState *mouseState = (RawMouseState *)0x238E6BC;
	if (!mouseEnabled)
		return;
	tagRAWINPUT input;
	unsigned __int32 cbSize = sizeof(tagRAWINPUT);
	if (GetRawInputData(hRawInput, RID_INPUT, &input, &cbSize, sizeof(tagRAWINPUTHEADER)) != sizeof(tagRAWINPUT))
		return;
	if (input.header.dwType != RIM_TYPEMOUSE)
		return;
	if (!RawInputHookImpl(&input))
	{
		mouseState->deltaX += input.data.mouse.lLastX;
		mouseState->deltaY += input.data.mouse.lLastY;
	}
	if (input.data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
		mouseState->wheelDelta += (short)input.data.mouse.usButtonData;
	if (input.data.mouse.ulButtons & RI_MOUSE_LEFT_BUTTON_DOWN)
		mouseState->buttons |= RawMouseState::eButtonLeft;
	if (input.data.mouse.ulButtons & RI_MOUSE_LEFT_BUTTON_UP)
		mouseState->buttons &= ~RawMouseState::eButtonLeft;
	if (input.data.mouse.ulButtons & RI_MOUSE_MIDDLE_BUTTON_DOWN)
		mouseState->buttons |= RawMouseState::eButtonMiddle;
	if (input.data.mouse.ulButtons & RI_MOUSE_MIDDLE_BUTTON_UP)
		mouseState->buttons &= ~RawMouseState::eButtonMiddle;
	if (input.data.mouse.ulButtons & RI_MOUSE_RIGHT_BUTTON_DOWN)
		mouseState->buttons |= RawMouseState::eButtonRight;
	if (input.data.mouse.ulButtons & RI_MOUSE_RIGHT_BUTTON_UP)
		mouseState->buttons &= ~RawMouseState::eButtonRight;
	if (input.data.mouse.ulButtons & RI_MOUSE_BUTTON_4_DOWN)
		mouseState->buttons |= RawMouseState::eButton4;
	if (input.data.mouse.ulButtons & RI_MOUSE_BUTTON_4_UP)
		mouseState->buttons &= ~RawMouseState::eButton4;
	if (input.data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN)
		mouseState->buttons |= RawMouseState::eButton5;
	if (input.data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_UP)
		mouseState->buttons &= ~RawMouseState::eButton5;
}

/* ---------- explicit instantiations */
template float & Pointer::Read<float>() const;
