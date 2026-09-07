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

extern real_vector3d &_sub_10910120(real_vector3d &, float const);
_inline real_vector3d &operator*=(real_vector3d &v, float const c) // 0x10910120
{
	mangled_x86(MANGLED_TODO, "??X@YAAAUreal_vector3d@@AAU0@M@Z");
	// float const c;
	todo("implement");
	real_vector3d & __result = _sub_10910120(v, c);
	return __result;
}

extern real_vector3d _sub_1079B280(float const, real_vector3d const &);
_inline real_vector3d operator*(float const c, real_vector3d const &v) // 0x1079B280
{
	mangled_x86(MANGLED_TODO, "??D@YA?AUreal_vector3d@@MABU0@@Z");
	// real_vector3d const &v;
	todo("implement");
	real_vector3d __result = _sub_1079B280(c, v);
	return __result;
}

extern real_vector3d _sub_10968860(real_vector3d const &, float);
_inline real_vector3d operator*(real_vector3d const &v, float c) // 0x10968860
{
	mangled_x86(MANGLED_TODO, "??D@YA?AUreal_vector3d@@ABU0@M@Z");
	// float c;
	todo("implement");
	real_vector3d __result = _sub_10968860(v, c);
	return __result;
}

extern real_vector3d _sub_1079B3E0(real_vector3d const &, real_vector3d const &);
_inline real_vector3d operator+(real_vector3d const &v1, real_vector3d const &v2) // 0x1079B3E0
{
	mangled_x86(MANGLED_TODO, "??H@YA?AUreal_vector3d@@ABU0@0@Z");
	// real_vector3d const &v2;
	todo("implement");
	real_vector3d __result = _sub_1079B3E0(v1, v2);
	return __result;
}

extern real_vector3d _sub_1079B330(real_vector3d const &, real_vector3d const &);
_inline real_vector3d operator-(real_vector3d const &v1, real_vector3d const &v2) // 0x1079B330
{
	mangled_x86(MANGLED_TODO, "??G@YA?AUreal_vector3d@@ABU0@0@Z");
	// real_vector3d const &v2;
	todo("implement");
	real_vector3d __result = _sub_1079B330(v1, v2);
	return __result;
}

extern real_vector3d _sub_10956EA0(real_vector3d const &);
_inline real_vector3d operator-(real_vector3d const &v) // 0x10956EA0
{
	mangled_x86(MANGLED_TODO, "??G@YA?AUreal_vector3d@@ABU0@@Z");
	// real_vector3d const &v;
	todo("implement");
	real_vector3d __result = _sub_10956EA0(v);
	return __result;
}

extern real_vector3d _sub_1069ED00(real_point3d const &, real_point3d const &);
_inline real_vector3d operator-(real_point3d const &p1, real_point3d const &p2) // 0x1069ED00
{
	mangled_x86(MANGLED_TODO, "??G@YA?AUreal_vector3d@@ABUreal_point3d@@0@Z");
	// real_point3d const &p2;
	todo("implement");
	real_vector3d __result = _sub_1069ED00(p1, p2);
	return __result;
}

extern real_point3d _sub_108C7630(real_point3d const &, real_vector3d const &);
_inline real_point3d operator+(real_point3d const &p, real_vector3d const &v) // 0x108C7630
{
	mangled_x86(MANGLED_TODO, "??H@YA?AUreal_point3d@@ABU0@ABUreal_vector3d@@@Z");
	// real_vector3d const &v;
	todo("implement");
	real_point3d __result = _sub_108C7630(p, v);
	return __result;
}

extern real_point3d _sub_1096F940(real_point3d const &, real_point3d const &);
_inline real_point3d operator+(real_point3d const &p1, real_point3d const &p2) // 0x1096F940
{
	mangled_x86(MANGLED_TODO, "??H@YA?AUreal_point3d@@ABU0@0@Z");
	// real_point3d const &p2;
	todo("implement");
	real_point3d __result = _sub_1096F940(p1, p2);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_MATH_REAL_MATH_INL__
