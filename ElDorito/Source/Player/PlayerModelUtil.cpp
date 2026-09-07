/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_euler_angles3d;
struct real_matrix4x3;
struct real_point3d;

namespace Player {}
using namespace ::Player;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Player
{
	extern real_point3d CalculateBipedPosition(real_point3d const *point, real_euler_angles3d const *euler, float distance, float right_distance);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern real_point3d _sub_106805F0(real_point3d const *, real_euler_angles3d const *, float, float);
namespace Player
{
	real_point3d CalculateBipedPosition(real_point3d const *point, real_euler_angles3d const *euler, float distance, float right_distance) // 0x106805F0
	{
		mangled_x86(MANGLED_TODO, "?CalculateBipedPosition@Player@@YA?AUreal_point3d@@PBU2@PBUreal_euler_angles3d@@MM@Z");
		// real_point3d const *point;
		// real_euler_angles3d const *euler;
		// float distance;
		// float right_distance;
		// real_matrix4x3 matrix;
		todo("implement");
		real_point3d __result = _sub_106805F0(point, euler, distance, right_distance);
		return __result;
	}
}

/* ---------- private code */
