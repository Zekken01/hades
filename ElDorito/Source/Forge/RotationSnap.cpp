/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Forge/ForgeUtil.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Modules/ModuleForge.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct real_matrix3x3;
struct real_matrix4x3;
struct real_point3d;
struct real_quaternion;
struct real_vector3d;
struct s_RotationSnapState;
namespace Blam
{
	namespace Input
	{
		struct ActionState;
	}
}
namespace Modules
{
	class ModuleForge;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

/* ---------- constants */

/* ---------- definitions */

struct s_RotationSnapState
{
	unsigned __int32 ObjectIndex; // 0x0
	unsigned __int32 StartTime; // 0x4
	float Current; // 0x8
	real_quaternion StartRotation; // 0xC
	real_quaternion EndRotation; // 0x1C
	bool IsScripted; // 0x2C
};
// static_assert(sizeof(s_RotationSnapState) == 48, "Invalid s_RotationSnapState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const sandbox_update_object_position = reinterpret_cast<void (*)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)>(0x59E340);
}

extern float (*const game_tick_length)();  // hades: added for 0x10971C90
extern void quaternions_slerp_interpolate_and_normalize(real_quaternion const *q0, real_quaternion const *q1, float fraction, real_quaternion *result);  // hades: added for 0x10971C90
extern real_matrix3x3 *matrix3x3_rotation_from_quaternion(real_matrix3x3 *matrix, real_quaternion const *quaternion);  // hades: added for 0x10971C90

extern void quaternion_normalize(real_quaternion *q);  // hades: added for 0x10971520
extern void quaternion_from_axis_and_angle(real_vector3d const *axis, float angle, real_quaternion *quaternion);  // hades: added for 0x10971520
extern void quaternions_multiply(real_quaternion const *q1, real_quaternion const *q2, real_quaternion *result);  // hades: added for 0x10971520

extern real_quaternion *matrix3x3_rotation_to_quaternion(real_matrix3x3 const *matrix, real_quaternion *quaternion);  // hades: added for 0x10971850
extern long (*const game_time_get)();  // hades: added for 0x10971850

namespace Forge
{
	namespace RotationSnap
	{
		extern void Update(unsigned __int32 playerIndex, unsigned __int32 heldObjectIndex);
		extern void RotateSnapped(real_vector3d const &axis);
		extern void RotateToScripted(unsigned __int32 objectIndex, real_quaternion const &rotation);
	}
}

void SetSnap(__int32 value);
void HandleInput();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern float const SNAP_ANGLES[7]; // 0x1119ABF8
	extern s_RotationSnapState s_RotationSnapState; // 0x1244FA10
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	namespace RotationSnap
	{
		void Update(unsigned __int32 playerIndex, unsigned __int32 heldObjectIndex) // 0x10971C90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Update@RotationSnap@Forge@@YAXII@Z");

			if (heldObjectIndex == -1)
				return;
			HandleInput();
			static Modules::ModuleForge &moduleForge = Modules::ModuleForge::Instance();
			unsigned long currentSnapIndex = moduleForge.VarRotationSnap->ValueInt;
			if (currentSnapIndex < 0 || currentSnapIndex > 6)
				currentSnapIndex = 0;
			float const snapAngleDegrees = SNAP_ANGLES[currentSnapIndex];
			if (snapAngleDegrees < 1 && !hades_file_local::s_RotationSnapState.IsScripted)
				return;
			if (heldObjectIndex == -1)
			{
				hades_file_local::s_RotationSnapState.StartTime = game_time_get();
				hades_file_local::s_RotationSnapState.StartRotation = real_quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
				hades_file_local::s_RotationSnapState.EndRotation = hades_file_local::s_RotationSnapState.StartRotation;
				hades_file_local::s_RotationSnapState.Current = 1.0f;
				hades_file_local::s_RotationSnapState.ObjectIndex = -1;
			}
			hades_file_local::s_RotationSnapState.Current += game_tick_length() / 0.3f;
			if (hades_file_local::s_RotationSnapState.Current >= 1)
			{
				hades_file_local::s_RotationSnapState.IsScripted = false;
				hades_file_local::s_RotationSnapState.Current = 1;
			}
			if (hades_file_local::s_RotationSnapState.ObjectIndex != heldObjectIndex)
			{
				real_matrix4x3 objectTransform;
				real_quaternion startRotation;
				((real_matrix4x3 *(__cdecl *)(long, real_matrix4x3 *))0xB2EC60)(heldObjectIndex, &objectTransform);
				matrix3x3_rotation_to_quaternion((real_matrix3x3 const *)&objectTransform.forward, &startRotation);
				hades_file_local::s_RotationSnapState.StartRotation = startRotation;
				hades_file_local::s_RotationSnapState.EndRotation = hades_file_local::s_RotationSnapState.StartRotation;
				hades_file_local::s_RotationSnapState.Current = 1.0f;
			}
			real_quaternion interpolatedRotation;
			quaternions_slerp_interpolate_and_normalize(&hades_file_local::s_RotationSnapState.StartRotation, &hades_file_local::s_RotationSnapState.EndRotation, hades_file_local::s_RotationSnapState.Current, &interpolatedRotation);
			real_matrix3x3 matrix;
			matrix3x3_rotation_from_quaternion(&matrix, &interpolatedRotation);
			eldorado::sandbox_update_object_position(false, heldObjectIndex, nullptr, &matrix.forward, &matrix.up);
			hades_file_local::s_RotationSnapState.ObjectIndex = heldObjectIndex;
		}

		void RotateSnapped(real_vector3d const &axis) // 0x10971520
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RotateSnapped@RotationSnap@Forge@@YAXABUreal_vector3d@@@Z");

			static Modules::ModuleForge &moduleForge = Modules::ModuleForge::Instance();
			unsigned long currentSnap = moduleForge.VarRotationSnap->ValueInt;
			float const snapAngleDegrees = SNAP_ANGLES[currentSnap];
			float const snapAngleRadians = snapAngleDegrees / 180.0f * 3.14159265f;
			if (hades_file_local::s_RotationSnapState.Current < 1)
				return;
			real_matrix4x3 objectTransform;
			real_quaternion startRotation;
			real_quaternion endRotation;
			real_quaternion axisRotation;
			((real_matrix4x3 *(__cdecl *)(long, real_matrix4x3 *))0xB2EC60)(hades_file_local::s_RotationSnapState.ObjectIndex, &objectTransform);
			matrix3x3_rotation_to_quaternion((real_matrix3x3 const *)&objectTransform.forward, &startRotation);
			quaternion_from_axis_and_angle(&axis, snapAngleRadians, &axisRotation);
			quaternions_multiply(&axisRotation, &startRotation, &endRotation);
			quaternion_normalize(&startRotation);
			quaternion_normalize(&endRotation);
			hades_file_local::s_RotationSnapState.StartTime = game_time_get();
			hades_file_local::s_RotationSnapState.StartRotation = startRotation;
			hades_file_local::s_RotationSnapState.EndRotation = endRotation;
			hades_file_local::s_RotationSnapState.Current = 0;
		}

		void RotateToScripted(unsigned __int32 objectIndex, real_quaternion const &rotation) // 0x10971850
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RotateToScripted@RotationSnap@Forge@@YAXIABUreal_quaternion@@@Z");

			real_matrix4x3 objectTransform;
			real_quaternion startRotation;
			((real_matrix4x3 *(__cdecl *)(long, real_matrix4x3 *))0xB2EC60)(hades_file_local::s_RotationSnapState.ObjectIndex, &objectTransform);
			matrix3x3_rotation_to_quaternion((real_matrix3x3 const *)&objectTransform.forward, &startRotation);
			hades_file_local::s_RotationSnapState.ObjectIndex = objectIndex;
			hades_file_local::s_RotationSnapState.IsScripted = true;
			hades_file_local::s_RotationSnapState.StartTime = game_time_get();
			hades_file_local::s_RotationSnapState.StartRotation = startRotation;
			hades_file_local::s_RotationSnapState.EndRotation = rotation;
			hades_file_local::s_RotationSnapState.Current = 0;
		}
	}
}

/* ---------- private code */

void SetSnap(__int32 value) // 0x109719E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetSnap@@YAXH@Z");

	static void (*PrintKillFeedText)(unsigned __int32, wchar_t *, __int32) = (void (*)(unsigned __int32, wchar_t *, __int32))0xA95920;
	static Modules::ModuleForge &moduleForge = Utils::Singleton<Modules::ModuleForge>::Instance();
	if (value < 0)
		value = 0;
	if (value > 6)
		value = 6;
	std::string prev;
	Utils::Singleton<Modules::CommandMap>::Instance().SetVariable(moduleForge.VarRotationSnap, std::to_string(value), prev, true);
	wchar_t buff[256];
	if (value > 0)
		swprintf_s(buff, 256, L"Rotation Snap: %.2f\n", SNAP_ANGLES[value]);
	else
		swprintf_s(buff, 256, L"Rotation Snap: OFF");
	PrintKillFeedText(0, buff, 0);
}

void HandleInput() // 0x10971350
{

	using namespace Blam::Input;

	static auto& moduleForge = Modules::ModuleForge::Instance();

	auto uiLeftAction = GetActionState(eGameActionUiLeft);
	auto uiRightAction = GetActionState(eGameActionUiRight);

	int snapAngleCount = sizeof(SNAP_ANGLES) / sizeof(SNAP_ANGLES[0]);
	auto currentSnap = static_cast<int>(moduleForge.VarRotationSnap->ValueInt);

	if (!(uiLeftAction->Flags & eActionStateFlagsHandled) && uiLeftAction->Ticks == 1)
	{
		if (--currentSnap < 0)
			currentSnap = snapAngleCount - 1;

		uiLeftAction->Flags |= eActionStateFlagsHandled;
		SetSnap(currentSnap);
	}
	if (!(uiRightAction->Flags & eActionStateFlagsHandled) &&  uiRightAction->Ticks == 1)
	{
		if (++currentSnap >= snapAngleCount)
			currentSnap = 0;

		uiRightAction->Flags |= eActionStateFlagsHandled;
		SetSnap(currentSnap);
	}
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { float const SNAP_ANGLES[7] = { 0.0f, 3.0f, 5.0f, 15.0f, 30.0f, 45.0f, 90.0f }; }
namespace hades_file_local { struct s_RotationSnapState s_RotationSnapState; }
