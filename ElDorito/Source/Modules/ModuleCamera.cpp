/* ---------- headers */

#include "Modules/ModuleCamera.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/camera/camera.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/camera/observer.hpp"
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
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_camera;
class c_director;
struct real_euler_angles2d;
struct real_euler_angles3d;
struct real_point3d;
struct real_vector3d;
struct s_observer_result;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleCamera;
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
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Camera {}
	using namespace Patches::Camera;
}

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

extern real_euler_angles3d *euler_angles3d_from_vectors3d(real_euler_angles3d *angles, real_vector3d const *forward, real_vector3d const *up);  // hades: added for 0x1097A670
extern real_vector3d *vector3d_from_euler_angles2d(real_vector3d *result, real_euler_angles2d const *angles);  // hades: added for 0x1097A670

namespace Patches { namespace Camera { extern bool SetForcedCameraMode(std::string const mode); } }  // hades: added for 0x1097A4A0

bool VariableCameraFovUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableCameraHideHudUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableCameraHideKillFeedUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableCameraSpeedUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableCameraPositionUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableCameraModeUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableCameraShowCoordinatesUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableOldViewOffsetScaleUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern float &k_camera_field_of_view_default; // 0x11353EC0
	extern real_euler_angles2d inputAngularVelocity; // 0x12454D54
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	ModuleCamera::ModuleCamera() : ModuleBase("Camera"), HideHudPatch(0x151CC64, 0, 1), HideKillFeedPatch(0x695929, { 0xEB }) /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x10978AE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleCamera@Modules@@QAE@XZ");
		// Modules::ModuleCamera *const this;

		VarCameraCenteredCrosshairFirst = AddVariableInt("CenteredCrosshairFirst", "crosshair1p", "Controls whether the crosshair should be centered in first person", eCommandFlagsArchived, 0);
		VarCameraCenteredCrosshairFirst->ValueIntMin = 0;
		VarCameraCenteredCrosshairFirst->ValueIntMax = 1;
		VarCameraCenteredCrosshairThird = AddVariableInt("CenteredCrosshairThird", "crosshair3p", "Controls whether the crosshair should be centered in third person", eCommandFlagsArchived, 1);
		VarCameraCenteredCrosshairThird->ValueIntMin = 0;
		VarCameraCenteredCrosshairThird->ValueIntMax = 1;
		VarCameraFocusDistance = AddVariableFloat("FocusDistance", "camFocusDist", "The camera focus distance. Only applies to the third person. 0 = unchanged", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsCheat), 0.0f);
		VarCameraFocusDistance->ValueIntMin = 0;
		VarVehicleCameraFov = AddVariableFloat("VehicleFOV", "vehiclefov", "The vehicle cameras field of view", eCommandFlagsArchived, 90.0f);
		VarVehicleCameraFov->ValueFloatMin = 55.0f;
		VarVehicleCameraFov->ValueFloatMax = 120.0f;
		VarCameraFov = AddVariableFloat("FOV", "fov", "The cameras field of view", eCommandFlagsArchived, 90.0f, VariableCameraFovUpdate);
		VarCameraFov->ValueFloatMin = 55.0f;
		VarCameraFov->ValueFloatMax = 120.0f;
		VarCameraVertSpeed = AddVariableFloat("VertSpeed", "camSpeedVert", "The camera's vertical speed", eCommandFlagsArchived, 2.0f);
		VarCameraVertSpeed->ValueFloatMin = 0.0099999998f;
		VarCameraVertSpeed->ValueFloatMax = 1000.0f;
		VarCameraHideHud = AddVariableInt("HideHUD", "hud", "Toggles the HUD", eCommandFlagsRunOnMainMenu, 0, VariableCameraHideHudUpdate);
		VarCameraHideHud->ValueIntMin = 0;
		VarCameraHideHud->ValueIntMax = 1;
		VarCameraHideKillFeed = AddVariableInt("HideKillFeed", "killfeed", "Toggles the Kill Feed", eCommandFlagsArchived, 0, VariableCameraHideKillFeedUpdate);
		VarCameraHideKillFeed->ValueIntMin = 0;
		VarCameraHideKillFeed->ValueIntMax = 1;
		VarCameraSpeed = AddVariableFloat("Speed", "camSpeed", "The camera speed", CommandFlags(eCommandFlagsRunOnMainMenu | eCommandFlagsArchived), 3.0f, VariableCameraSpeedUpdate);
		VarCameraSpeed->ValueFloatMin = 0.0099999998f;
		VarCameraSpeed->ValueFloatMax = 1000.0f;
		VarCameraSmoothing = AddVariableFloat("Smoothing", "camSmooth", "The flying camera smoothing factor", CommandFlags(eCommandFlagsRunOnMainMenu | eCommandFlagsArchived), 0.1f);
		VarCameraSmoothing->ValueFloatMin = 0.0f;
		VarCameraSmoothing->ValueFloatMax = 5.0f;
		VarOldViewOffsetScale = AddVariableInt("OldViewOffsetScale", "oldViewOffsets", "use the old view model offset system", CommandFlags(eCommandFlagsHidden | eCommandFlagsArchived), 0, VariableOldViewOffsetScaleUpdate);
		VarOldViewOffsetScale->ValueIntMin = 0;
		VarOldViewOffsetScale->ValueIntMax = 1;
		VarCameraPosition = AddCommand("Position", "camPos", "The cameras position, Doesn't work when camera mode is set to default", eCommandFlagsNone, VariableCameraPositionUpdate, { "X Coordinate", "Y Coordinate", "Z Coordinate", "H Angle", "V Angle" });
		VarCameraMode = AddVariableString("Mode", "cam", "Camera mode, valid modes: default, first, third, flying, static", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsRunOnMainMenu | eCommandFlagsDontUpdateInitial | eCommandFlagsCheat), "default", VariableCameraModeUpdate);
		VarCameraShowCoordinates = AddVariableInt("ShowCoordinates", "coords", "The cameras field of view", CommandFlags(eCommandFlagsRunOnMainMenu | eCommandFlagsArchived), 0, VariableCameraShowCoordinatesUpdate);
		VarCameraShowCoordinates->ValueIntMin = 0;
		VarCameraShowCoordinates->ValueIntMax = 1;
	}

	void ModuleCamera::SetInputAngularVelocity(real_euler_angles2d const *velocity) // 0x10979E30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetInputAngularVelocity@ModuleCamera@Modules@@QAEXPBUreal_euler_angles2d@@@Z");
		// real_euler_angles2d const *velocity;

		inputAngularVelocity = *velocity;
	}

	void ModuleCamera::GetInputAngularVelocity(real_euler_angles2d *velocity) const // 0x10979DF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetInputAngularVelocity@ModuleCamera@Modules@@QBEXPAUreal_euler_angles2d@@@Z");
		// real_euler_angles2d *velocity;

		*velocity = inputAngularVelocity;
	}
}

/* ---------- private code */

bool VariableCameraFovUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10979E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCameraFovUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableCameraFovUpdate
	// std::string &returnInfo;
	// Modules::ModuleCamera &moduleCamera;
	// float value;

	auto &moduleCamera = Modules::ModuleCamera::Instance();
	float value = moduleCamera.VarCameraFov->ValueFloat;
	Pointer::Base(0x1F01D98).Write(value);
	Pointer::Base(0x149D42C).Write(value);
	return true;
}

bool VariableCameraHideHudUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097A000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCameraHideHudUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableCameraHideHudUpdate
	// static ...; // 0x1097A1C4
	// static ...; // 0x1097A1BC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool statusBool;
	// std::string status;
	// unsigned long value;

	unsigned long value = Modules::ModuleCamera::Instance().VarCameraHideHud->ValueInt;
	std::string status = "shown.";
	bool statusBool = value != 0;
	if (statusBool)
		status = "hidden.";

	Modules::ModuleCamera::Instance().HideHudPatch.Apply(!statusBool);
	returnInfo = "HUD " + status;
	return true;
}

bool VariableCameraHideKillFeedUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097A250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCameraHideKillFeedUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableCameraHideKillFeedUpdate
	// static ...; // 0x1097A414
	// static ...; // 0x1097A40C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool statusBool;
	// std::string status;
	// unsigned long value;

	unsigned long value = Modules::ModuleCamera::Instance().VarCameraHideKillFeed->ValueInt;
	std::string status = "shown.";
	bool statusBool = value != 0;
	if (statusBool)
		status = "hidden.";

	Modules::ModuleCamera::Instance().HideKillFeedPatch.Apply(!statusBool);
	returnInfo = "Kill Feed " + status;
	return true;
}

bool VariableCameraSpeedUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097AD40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCameraSpeedUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableCameraSpeedUpdate
	// static ...; // 0x1097AE6C
	// static ...; // 0x1097AE64
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// float speed;
	// std::stringstream ss;

	float speed = Modules::ModuleCamera::Instance().VarCameraSpeed->ValueFloat;

	std::stringstream ss;
	ss << "Camera speed set to " << speed;
	returnInfo = ss.str();

	return true;
}

bool VariableCameraPositionUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097A670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCameraPositionUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableCameraPositionUpdate
	// static ...; // 0x1097AA77
	// static ...; // 0x1097AA73
	// static ...; // 0x1097AA6C
	// static ...; // 0x1097AA64
	// static ...; // 0x1097AA28
	// static ...; // 0x1097AA20
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// c_director *director;
	// c_camera *camera;
	// real_point3d pos;
		// s_observer_result const *observer_camera;
		// std::stringstream ss;
		// real_euler_angles3d euler;
		// real_euler_angles2d angles;
		// real_vector3d forward;
	// function call : c_director *(*const)(long)
	// function call : bool (*const)()
	// function call : s_observer_result *(*const)(long)
	// function call : void (real_point3d const *)
	// function call : void (real_vector3d const *)

	c_director *director = ((c_director *(__cdecl *)(long))0x591990)(0);
	c_camera *camera = director->get_camera();
	if (!((bool(__cdecl *)())0x5314B0)())
	{
		returnInfo = "Not available at this time";
		return false;
	}
	if (Arguments.size() != 3 && Arguments.size() != 5)
	{
		s_observer_result const *observer_camera = ((s_observer_result const *(__cdecl *)(long))0x6127C0)(0);
		real_euler_angles3d euler;
		euler_angles3d_from_vectors3d(&euler, &observer_camera->forward, &observer_camera->up);
		std::stringstream ss;
		ss << "X: " << observer_camera->position.x << ", Y: " << observer_camera->position.y << ", Z: " << observer_camera->position.z << ", H: " << euler.yaw * 180.0f / 3.14159265f << ", V: " << euler.pitch * 180.0f / 3.14159265f;
		returnInfo = ss.str();
		return true;
	}
	real_point3d pos = { std::stof(Arguments[0]), std::stof(Arguments[1]), std::stof(Arguments[2]) };
	camera->set_position(&pos);
	if (Arguments.size() == 5)
	{
		real_euler_angles2d angles = { std::stof(Arguments[3]), std::stof(Arguments[4]) };
		real_vector3d forward;
		vector3d_from_euler_angles2d(&forward, &angles);
		camera->set_forward(&forward);
	}
	return true;
}

bool VariableCameraModeUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097A4A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCameraModeUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableCameraModeUpdate
	// static ...; // 0x1097A5FC
	// static ...; // 0x1097A5F4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// constexpr bool (*const `VariableCameraModeUpdate'::`2'::player_terminal_chud_set)(bool); // constant == 11050832
	// bool result;
	// std::string mode;
	// function call : bool (*const)()

	std::string mode = Utils::String::ToLower(Modules::ModuleCamera::Instance().VarCameraMode->ValueString);
	if (!((bool(__cdecl *)())0x5314B0)())
	{
		returnInfo = "Unable to set camera mode.";
		return false;
	}
	bool result = Patches::Camera::SetForcedCameraMode(mode);
	if (!result)
	{
		returnInfo = "valid modes: default, first, third, flying, static";
		return false;
	}
	return true;
}

bool VariableCameraShowCoordinatesUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097AB90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCameraShowCoordinatesUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableCameraShowCoordinatesUpdate
	// static ...; // 0x1097ACD0
	// static ...; // 0x1097ACC8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::Session *session;
	// std::string status;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || Arguments.size() != 1)
	{
		returnInfo = "Unable to enable debug coordinates!";
		return false;
	}

	std::string status = "disabled.";
	if (Modules::ModuleCamera::Instance().VarCameraShowCoordinates->ValueInt)
		status = "enabled.";
	else
		status = "disabled.";

	returnInfo = "Debug coordinates " + status;
	return true;
}

bool VariableOldViewOffsetScaleUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097AED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableOldViewOffsetScaleUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableOldViewOffsetScaleUpdate
	// std::string &returnInfo;

	if (!Modules::ModuleCamera::Instance().VarOldViewOffsetScale->ValueInt)
	{
		k_camera_field_of_view_default = 1.22173047f;
		returnInfo = "view offset scaling enabled";
	}
	else
	{
		k_camera_field_of_view_default = 1.39626336f;
		returnInfo = "view offset scaling disabled";
	}

	return true;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { real_euler_angles2d inputAngularVelocity; }
