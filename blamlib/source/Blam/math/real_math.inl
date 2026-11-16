#ifndef __BLAM_MATH_REAL_MATH_INL__
#define __BLAM_MATH_REAL_MATH_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_point3d;
struct real_vector3d;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern _inline real_vector3d &operator*=(real_vector3d &v, float const c);
extern _inline real_vector3d operator*(float const c, real_vector3d const &v);
extern _inline real_vector3d operator*(real_vector3d const &v, float c);
extern _inline real_vector3d operator+(real_vector3d const &v1, real_vector3d const &v2);
extern _inline real_vector3d operator-(real_vector3d const &v1, real_vector3d const &v2);
extern _inline real_vector3d operator-(real_vector3d const &v);
extern _inline real_vector3d operator-(real_point3d const &p1, real_point3d const &p2);
extern _inline real_point3d operator+(real_point3d const &p, real_vector3d const &v);
extern _inline real_point3d operator+(real_point3d const &p1, real_point3d const &p2);

/* ---------- globals */

/* ---------- public code */

inline real_vector3d &operator*=(real_vector3d &v, float const c) // 0x10910120
{
	v.i = v.i * c;
	v.j = v.j * c;
	v.k = v.k * c;
	return v;
}

inline real_vector3d operator*(float const c, real_vector3d const &v) // 0x1079B280
{
	return { c * v.i, c * v.j, c * v.k };
}

inline real_vector3d operator*(real_vector3d const &v, float c) // 0x10968860
{
	return { c * v.i, c * v.j, c * v.k };
}

inline real_vector3d operator+(real_vector3d const &v1, real_vector3d const &v2) // 0x1079B3E0
{
	return real_vector3d{ v1.i + v2.i, v1.j + v2.j, v1.k + v2.k };
}

inline real_vector3d operator-(real_vector3d const &v1, real_vector3d const &v2) // 0x1079B330
{
	return real_vector3d{ v1.i - v2.i, v1.j - v2.j, v1.k - v2.k };
}

inline real_vector3d operator-(real_vector3d const &v) // 0x10956EA0
{
	return { -v.i, -v.j, -v.k };
}

inline real_vector3d operator-(real_point3d const &p1, real_point3d const &p2) // 0x1069ED00
{
	return { p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
}

inline real_point3d operator+(real_point3d const &p, real_vector3d const &v) // 0x108C7630
{
	return real_point3d{ p.x + v.i, p.y + v.j, p.z + v.k };
}

inline real_point3d operator+(real_point3d const &p1, real_point3d const &p2) // 0x1096F940
{
	return { p1.x + p2.x, p1.y + p2.y, p1.z + p2.z };
}

/* ---------- private code */

#endif // __BLAM_MATH_REAL_MATH_INL__
