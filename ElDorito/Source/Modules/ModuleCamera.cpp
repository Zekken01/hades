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
	extern ModuleCamera* _sub_10978AE0(Modules::ModuleCamera *const);
	ModuleCamera::ModuleCamera() : ModuleBase(todo_result<std::string>()) // 0x10978AE0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleCamera@Modules@@QAE@XZ");
		// Modules::ModuleCamera *const this;
		todo("implement");
		_sub_10978AE0(this);
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

_extern bool _sub_1097A000(std::vector<std::string> const &, std::string &);
bool VariableCameraHideHudUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097A000
{
	// `anonymous-namespace'::VariableCameraHideHudUpdate
	// static ...; // 0x1097A1C4
	// static ...; // 0x1097A1BC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool statusBool;
	// std::string status;
	// unsigned long value;
	todo("implement");
	bool __result = _sub_1097A000(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1097A250(std::vector<std::string> const &, std::string &);
bool VariableCameraHideKillFeedUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097A250
{
	// `anonymous-namespace'::VariableCameraHideKillFeedUpdate
	// static ...; // 0x1097A414
	// static ...; // 0x1097A40C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool statusBool;
	// std::string status;
	// unsigned long value;
	todo("implement");
	bool __result = _sub_1097A250(Arguments, returnInfo);
	return __result;
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

_extern bool _sub_1097A670(std::vector<std::string> const &, std::string &);
bool VariableCameraPositionUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097A670
{
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
	{
		// s_observer_result const *observer_camera;
		// std::stringstream ss;
		// real_euler_angles3d euler;
	}
	{
		// real_euler_angles2d angles;
		// real_vector3d forward;
	}
	// function call : c_director *(*const)(long)
	// function call : bool (*const)()
	// function call : s_observer_result *(*const)(long)
	// function call : void (real_point3d const *)
	// function call : void (real_vector3d const *)
	todo("implement");
	bool __result = _sub_1097A670(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1097A4A0(std::vector<std::string> const &, std::string &);
bool VariableCameraModeUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097A4A0
{
	// `anonymous-namespace'::VariableCameraModeUpdate
	// static ...; // 0x1097A5FC
	// static ...; // 0x1097A5F4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// constexpr bool (*const `VariableCameraModeUpdate'::`2'::player_terminal_chud_set)(bool); // constant == 11050832
	// bool result;
	// std::string mode;
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1097A4A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_1097AB90(std::vector<std::string> const &, std::string &);
bool VariableCameraShowCoordinatesUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097AB90
{
	// `anonymous-namespace'::VariableCameraShowCoordinatesUpdate
	// static ...; // 0x1097ACD0
	// static ...; // 0x1097ACC8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Blam::Network::Session *session;
	// std::string status;
	todo("implement");
	bool __result = _sub_1097AB90(Arguments, returnInfo);
	return __result;
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
