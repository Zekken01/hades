/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Common/Http/HttpHeaders.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>

/* ---------- forward declarations */

struct real_euler_angles3d;
struct real_point3d;
struct real_quaternion;
struct real_vector3d;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void quaternions_slerp_interpolate(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result);  // hades: added for 0X10F1A9B0
void quaternion_normalize(real_quaternion *q);  // hades: added for 0X10F1A9B0

extern bool quaternion_is_identity(real_quaternion const *q);
extern void quaternion_inverse(real_quaternion *q);
extern void quaternion_normalize(real_quaternion *q);
extern void quaternion_to_angle_and_vector(real_quaternion *q, float *angle, real_vector3d *vector);
extern void quaternion_to_euler_angles(real_quaternion const *q, real_euler_angles3d *euler);
extern void quaternion_from_axis_and_angle(real_vector3d const *axis, float angle, real_quaternion *quaternion);
extern void quaternion_transform_point(real_quaternion const *q, real_point3d const *point, real_point3d *result);
extern float quaternions_dot(real_quaternion const *q1, real_quaternion const *q2);
extern void quaternions_interpolate(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result);
extern void quaternions_slerp_interpolate(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result);
extern void quaternions_slerp_interpolate_and_normalize(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result);
extern void quaternions_multiply(real_quaternion const *q1, real_quaternion const *q2, real_quaternion *result);

extern "C" void quaternion_to_euler_angles_internal(real_quaternion const *q, real_euler_angles3d *euler, float epsilon);

/* ---------- globals */

extern float arctangent(float y, float x);
extern float normalize3d(real_vector3d *v);
extern real_vector3d *negate_vector3d(real_vector3d const *v, real_vector3d *result);

/* ---------- private variables */

/* ---------- public code */

bool quaternion_is_identity(real_quaternion const *q) // 0x10F194F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_is_identity@@YA_NPBUreal_quaternion@@@Z");
	// real_quaternion const *q;

	return fabsf(q->w - 1.0f) < 0.00001f;
}

void quaternion_inverse(real_quaternion *q) // 0x10F19490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_inverse@@YAXPAUreal_quaternion@@@Z");
	// real_quaternion *q;

	q->w = q->w * -1.0f;
}

_extern void _sub_10F195A0(real_quaternion *);
void quaternion_normalize(real_quaternion *q) // 0x10F195A0
{
	mangled_x86(MANGLED_TODO, "?quaternion_normalize@@YAXPAUreal_quaternion@@@Z");
	// real_quaternion *q;
	// float dot;
	{
		// float rs;
	}
	todo("implement");
	_sub_10F195A0(q);
}

void quaternion_to_angle_and_vector(real_quaternion *q, float *angle, real_vector3d *vector) // 0x10F19730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_to_angle_and_vector@@YAXPAUreal_quaternion@@PAMPAUreal_vector3d@@@Z");
	// real_vector3d *vector;
	// float length;

	vector->i = q->i;
	vector->j = q->j;
	vector->k = q->k;

	float length = normalize3d(vector);

	*angle = arctangent(length, q->w) * 2.0f;
	if (*angle > 3.1415927f)
	{
		negate_vector3d(vector, vector);
		*angle = 6.2831855f - *angle;
	}
}

void quaternion_to_euler_angles(real_quaternion const *q, real_euler_angles3d *euler) // 0x10F19850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_to_euler_angles@@YAXPBUreal_quaternion@@PAUreal_euler_angles3d@@@Z");
	// real_euler_angles3d *euler;

	quaternion_to_euler_angles_internal(q, euler, 0.00001f);
}

void quaternion_from_axis_and_angle(real_vector3d const *axis, float angle, real_quaternion *quaternion) // 0x10F19360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_from_axis_and_angle@@YAXPBUreal_vector3d@@MPAUreal_quaternion@@@Z");
	// real_quaternion *quaternion;
	// float cos_theta;
	// float sin_theta;
	// float half_angle;

	float half_angle = angle * 0.5f;
	float sin_theta = sinf(half_angle);
	float cos_theta = cosf(half_angle);

	*quaternion = real_quaternion{ { { axis->i * sin_theta, axis->j * sin_theta, axis->k * sin_theta } }, cos_theta };
}

_extern void _sub_10F19C10(real_quaternion const *, real_point3d const *, real_point3d *);
void quaternion_transform_point(real_quaternion const *q, real_point3d const *point, real_point3d *result) // 0x10F19C10
{
	mangled_x86(MANGLED_TODO, "?quaternion_transform_point@@YAXPBUreal_quaternion@@PBUreal_point3d@@PAU2@@Z");
	// real_point3d *result;
	// float const zz;
	// float const yz;
	// float const xz;
	// float const w;
	// float const px;
	// float const x;
	// float const wy;
	// float const xx;
	// float const y;
	// float const pz;
	// float const yy;
	// float const py;
	// float const wx;
	// float const wz;
	// float const z;
	// float const xy;
	todo("implement");
	_sub_10F19C10(q, point, result);
}

float quaternions_dot(real_quaternion const *q1, real_quaternion const *q2) // 0x10F19FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternions_dot@@YAMPBUreal_quaternion@@0@Z");
	// real_quaternion const *q2;

	return q1->i * q2->i + q1->j * q2->j + q1->k * q2->k + q1->w * q2->w;
}

void quaternions_interpolate(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result) // 0x10F1A060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternions_interpolate@@YAXPBUreal_quaternion@@0MPAU1@@Z");
	// real_quaternion *result;
	// float const one_minus_t;

	float const one_minus_t = 1.0f - t;

	if (quaternions_dot(q1, q2) < 0.0f)
	{
		t = -t;
	}

	result->i = one_minus_t * q1->i + t * q2->i;
	result->j = one_minus_t * q1->j + t * q2->j;
	result->k = one_minus_t * q1->k + t * q2->k;
	result->w = one_minus_t * q1->w + t * q2->w;
}

_extern void _sub_10F1A430(real_quaternion const *, real_quaternion const *, float, real_quaternion *);
void quaternions_slerp_interpolate(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result) // 0x10F1A430
{
	mangled_x86(MANGLED_TODO, "?quaternions_slerp_interpolate@@YAXPBUreal_quaternion@@0MPAU1@@Z");
	// real_quaternion *result;
	// float w2;
	// float z1;
	// float x2;
	// float dot;
	// float z2;
	// float w1;
	// float x1;
	// float y1;
	// float y2;
	{
		// float sin_theta;
		// float sign;
		// float theta;
		{
			// float b;
			// float a;
		}
	}
	todo("implement");
	_sub_10F1A430(q1, q2, t, result);
}

void quaternions_slerp_interpolate_and_normalize(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result) // 0x10F1A9B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternions_slerp_interpolate_and_normalize@@YAXPBUreal_quaternion@@0MPAU1@@Z");
	// real_quaternion *result;

	quaternions_slerp_interpolate(q1, q2, t, result);
	quaternion_normalize(result);
}

_extern void _sub_10F1A1C0(real_quaternion const *, real_quaternion const *, real_quaternion *);
void quaternions_multiply(real_quaternion const *q1, real_quaternion const *q2, real_quaternion *result) // 0x10F1A1C0
{
	mangled_x86(MANGLED_TODO, "?quaternions_multiply@@YAXPBUreal_quaternion@@0PAU1@@Z");
	// real_quaternion *result;
	// float const w2;
	// float const z1;
	// float const x2;
	// float const z2;
	// float const w1;
	// float const x1;
	// float const y1;
	// float const y2;
	todo("implement");
	_sub_10F1A1C0(q1, q2, result);
}

/* ---------- private code */

_extern void _sub_10F198C0(real_quaternion const *, real_euler_angles3d *, float);
extern "C" void quaternion_to_euler_angles_internal(real_quaternion const *q, real_euler_angles3d *euler, float epsilon) // 0x10F198C0
{
	// quaternion_to_euler_angles_internal
	// float epsilon;
	// float const w;
	// float const x;
	// float const y;
	// float sinp;
	// float const z;
	todo("implement");
	_sub_10F198C0(q, euler, epsilon);
}
