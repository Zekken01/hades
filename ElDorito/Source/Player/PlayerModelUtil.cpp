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

extern void matrix4x3_rotation_from_angles(real_matrix4x3 *matrix, float yaw, float pitch, float roll);  // hades: added for 0x106805F0

namespace Player
{
	extern real_point3d CalculateBipedPosition(real_point3d const *point, real_euler_angles3d const *euler, float distance, float right_distance);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */


namespace Player
{
	real_point3d CalculateBipedPosition(real_point3d const *point, real_euler_angles3d const *euler, float distance, float right_distance) // 0x106805F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CalculateBipedPosition@Player@@YA?AUreal_point3d@@PBU2@PBUreal_euler_angles3d@@MM@Z");

		real_matrix4x3 matrix;
		matrix4x3_rotation_from_angles(&matrix, euler->yaw, euler->pitch, euler->roll);
		return {
			point->x + distance * matrix.forward.i - right_distance * matrix.left.i,
			point->y + distance * matrix.forward.j - right_distance * matrix.left.j,
			point->z + distance * matrix.forward.k - right_distance * matrix.left.k };
	}
}

/* ---------- private code */
