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

namespace Forge
{
	namespace RotationSnap
	{
		extern void Update(unsigned __int32 playerIndex, unsigned __int32 heldObjectIndex);
		extern void RotateSnapped(real_vector3d const &axis);
		extern void RotateToScripted(unsigned __int32 objectIndex, real_quaternion const &rotation);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern float const SNAP_ANGLES[7]; // 0x1119ABF8
}
/* ---------- public code */

namespace Forge
{
	namespace RotationSnap
	{
		_extern void _sub_10971C90(unsigned __int32, unsigned __int32);
		void Update(unsigned __int32 playerIndex, unsigned __int32 heldObjectIndex) // 0x10971C90
		{
			mangled_x86(MANGLED_TODO, "?Update@RotationSnap@Forge@@YAXII@Z");
			// static ...; // 0x1097205C
			// static ...; // 0x10972047
			// static ...; // 0x10972040
			// static ...; // 0x10972010
			// static ...; // 0x10972008
			// unsigned __int32 playerIndex;
			// unsigned __int32 heldObjectIndex;
			// static Modules::ModuleForge &moduleForge; // 0x1244FA40
			// real_quaternion interpolatedRotation;
			// unsigned long currentSnapIndex;
			// real_matrix3x3 matrix;
			// static __int32 $TSS0; // 0x1244FA44
			// float const snapAngleDegrees;
			{
				// real_matrix4x3 objectTransform;
				// real_quaternion startRotation;
			}
			// function call : long (*const)()
			// function call : float (*const)()
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
			// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
			todo("implement");
			_sub_10971C90(playerIndex, heldObjectIndex);
		}

		_extern void _sub_10971520(real_vector3d const &);
		void RotateSnapped(real_vector3d const &axis) // 0x10971520
		{
			mangled_x86(MANGLED_TODO, "?RotateSnapped@RotationSnap@Forge@@YAXABUreal_vector3d@@@Z");
			// static ...; // 0x1097179B
			// static ...; // 0x1097178D
			// static ...; // 0x10971781
			// static ...; // 0x10971774
			// static ...; // 0x10971744
			// static ...; // 0x1097173C
			// real_vector3d const &axis;
			// float const snapAngleRadians;
			// unsigned long currentSnap;
			// static Modules::ModuleForge &moduleForge; // 0x1244FA48
			// real_quaternion axisRotation;
			// real_matrix4x3 objectTransform;
			// real_quaternion startRotation;
			// static __int32 $TSS0; // 0x1244FA4C
			// float const snapAngleDegrees;
			// real_quaternion endRotation;
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
			// function call : long (*const)()
			todo("implement");
			_sub_10971520(axis);
		}

		_extern void _sub_10971850(unsigned __int32, real_quaternion const &);
		void RotateToScripted(unsigned __int32 objectIndex, real_quaternion const &rotation) // 0x10971850
		{
			mangled_x86(MANGLED_TODO, "?RotateToScripted@RotationSnap@Forge@@YAXIABUreal_quaternion@@@Z");
			// static ...; // 0x10971968
			// static ...; // 0x10971950
			// static ...; // 0x10971948
			// unsigned __int32 objectIndex;
			// real_quaternion const &rotation;
			// real_matrix4x3 objectTransform;
			// real_quaternion startRotation;
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
			// function call : long (*const)()
			todo("implement");
			_sub_10971850(objectIndex, rotation);
		}
	}
}

/* ---------- private code */
