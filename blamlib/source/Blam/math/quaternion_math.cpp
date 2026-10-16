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

extern float arccosine(float x); extern float sine(float x); /* hades: added for 0x10F1A430 */ extern float arcsine(float x);  // hades: added for 0x10F198C0

extern float dot_product3d(real_vector3d const *a, real_vector3d const *b);  // hades: added for 0x10F195A0
extern float reciprocal_square_root(float value);  // hades: added for 0x10F195A0

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

	return fabsf(q->w - 1.0f) < 0.00001f;
}

void quaternion_inverse(real_quaternion *q) // 0x10F19490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_inverse@@YAXPAUreal_quaternion@@@Z");

	q->w = q->w * -1.0f;
}

void quaternion_normalize(real_quaternion *q) // 0x10F195A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_normalize@@YAXPAUreal_quaternion@@@Z");

	float dot = dot_product3d(&q->v, &q->v) + q->w * q->w;
	if (dot <= 0.0)
	{
		q->v = real_vector3d{ 0.0f, 0.0f, 0.0f };
		q->w = 1.0f;
	}
	else
	{
		float rs = reciprocal_square_root(dot);
		q->i *= rs;
		q->j *= rs;
		q->k *= rs;
		q->w *= rs;
	}
}

void quaternion_to_angle_and_vector(real_quaternion *q, float *angle, real_vector3d *vector) // 0x10F19730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_to_angle_and_vector@@YAXPAUreal_quaternion@@PAMPAUreal_vector3d@@@Z");

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

	quaternion_to_euler_angles_internal(q, euler, 0.00001f);
}

void quaternion_from_axis_and_angle(real_vector3d const *axis, float angle, real_quaternion *quaternion) // 0x10F19360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_from_axis_and_angle@@YAXPBUreal_vector3d@@MPAUreal_quaternion@@@Z");

	float half_angle = angle * 0.5f;
	float sin_theta = sinf(half_angle);
	float cos_theta = cosf(half_angle);

	*quaternion = real_quaternion{ { { axis->i * sin_theta, axis->j * sin_theta, axis->k * sin_theta } }, cos_theta };
}

#line 147
void quaternion_transform_point(real_quaternion const *q, real_point3d const *point, real_point3d *result) // 0x10F19C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternion_transform_point@@YAXPBUreal_quaternion@@PBUreal_point3d@@PAU2@@Z");
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

	#line 149 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\math\\quaternion_math.cpp"
		assert(q);
		#line 171 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
	#line 150 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\math\\quaternion_math.cpp"
		assert(point);
		#line 174 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
	#line 151 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\math\\quaternion_math.cpp"
		assert(result);
		#line 177 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
	float const w = q->w;
	float const x = q->i;
	float const y = q->j;
	float const z = q->k;
	float const px = point->x;
	float const py = point->y;
	float const pz = point->z;
	float const xx = x * x;
	float const yy = y * y;
	float const zz = z * z;
	float const xy = x * y;
	float const xz = x * z;
	float const yz = y * z;
	float const wx = w * x;
	float const wy = w * y;
	float const wz = w * z;
	result->x = (1.0f - (yy + zz) * 2.0f) * px + (xy - wz) * 2.0f * py + (xz + wy) * 2.0f * pz;
	result->y = (xy + wz) * 2.0f * px + (1.0f - (xx + zz) * 2.0f) * py + (yz - wx) * 2.0f * pz;
	result->z = (xz - wy) * 2.0f * px + (yz + wx) * 2.0f * py + (1.0f - (xx + yy) * 2.0f) * pz;
}

float quaternions_dot(real_quaternion const *q1, real_quaternion const *q2) // 0x10F19FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternions_dot@@YAMPBUreal_quaternion@@0@Z");

	return q1->i * q2->i + q1->j * q2->j + q1->k * q2->k + q1->w * q2->w;
}

void quaternions_interpolate(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result) // 0x10F1A060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternions_interpolate@@YAXPBUreal_quaternion@@0MPAU1@@Z");

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

#line 225
void quaternions_slerp_interpolate(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result) // 0x10F1A430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternions_slerp_interpolate@@YAXPBUreal_quaternion@@0MPAU1@@Z");
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
		// float sin_theta;
		// float sign;
		// float theta;
			// float b;
			// float a;

	#line 227 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\math\\quaternion_math.cpp"
		assert(q1);
		assert(q2);
		assert(result);
		#line 249 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
	float w1 = q1->w;
	float x1 = q1->i;
	float y1 = q1->j;
	float z1 = q1->k;
	float w2 = q2->w;
	float x2 = q2->i;
	float y2 = q2->j;
	float z2 = q2->k;
	float dot = w1 * w2 + x1 * x2 + y1 * y2 + z1 * z2;
	if (fabsf(dot) > 0.99999f)
	{
		result->i = (x2 - x1) * t + x1;
		result->j = (y2 - y1) * t + y1;
		result->k = (z2 - z1) * t + z1;
		result->w = (w2 - w1) * t + w1;
	}
	else
	{
		if (dot > 1.0f)
			dot = 1.0f;
		if (dot < -1.0f)
			dot = -1.0f;
		float sign = dot < 0.0f ? -1.0f : 1.0f;
		w2 *= sign;
		x2 *= sign;
		y2 *= sign;
		z2 *= sign;
		dot = fabsf(dot);
		float theta = arccosine(dot);
		float sin_theta = sine(theta);
		if (sin_theta < 0.00001f)
		{
			result->w = (w2 - w1) * t + w1;
			result->i = (x2 - x1) * t + x1;
			result->j = (y2 - y1) * t + y1;
			result->k = (z2 - z1) * t + z1;
		}
		else
		{
			float a = sine((1.0f - t) * theta) / sin_theta;
			float b = sine(t * theta) / sin_theta;
			result->w = a * w1 + b * w2;
			result->i = a * x1 + b * x2;
			result->j = a * y1 + b * y2;
			result->k = a * z1 + b * z2;
		}
	}
}

void quaternions_slerp_interpolate_and_normalize(real_quaternion const *q1, real_quaternion const *q2, float t, real_quaternion *result) // 0x10F1A9B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternions_slerp_interpolate_and_normalize@@YAXPBUreal_quaternion@@0MPAU1@@Z");

	quaternions_slerp_interpolate(q1, q2, t, result);
	quaternion_normalize(result);
}

#line 307
void quaternions_multiply(real_quaternion const *q1, real_quaternion const *q2, real_quaternion *result) // 0x10F1A1C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?quaternions_multiply@@YAXPBUreal_quaternion@@0PAU1@@Z");
	// real_quaternion *result;
	// float const w2;
	// float const z1;
	// float const x2;
	// float const z2;
	// float const w1;
	// float const x1;
	// float const y1;
	// float const y2;

	#line 309 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\math\\quaternion_math.cpp"
		assert(q1);
		assert(q2);
		assert(result);
		#line 325 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
	float const w1 = q1->w;
	float const x1 = q1->i;
	float const y1 = q1->j;
	float const z1 = q1->k;
	float const w2 = q2->w;
	float const x2 = q2->i;
	float const y2 = q2->j;
	float const z2 = q2->k;
	result->w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
	result->i = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
	result->j = w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2;
	result->k = w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2;
}

/* ---------- private code */

extern "C" void quaternion_to_euler_angles_internal(real_quaternion const *q, real_euler_angles3d *euler, float epsilon) // 0x10F198C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_quaternion_to_euler_angles_internal");
	// quaternion_to_euler_angles_internal
	// float epsilon;
	// float const w;
	// float const x;
	// float const y;
	// float sinp;
	// float const z;

	#line 343 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
		assert(q);
		#line 355 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
	#line 344 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
		assert(euler);
		#line 358 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\quaternion_math.cpp"
	float const w = q->w;
	float const x = q->i;
	float const y = q->j;
	float const z = q->k;
	float sinp = (w * y - z * x) * 2.0f;
	if (fabsf(sinp) >= 1.0f - epsilon)
	{
		euler->pitch = copysignf(6.2831855f, sinp);
		euler->yaw = arctangent((x * y + w * z) * 2.0f, w * w + x * x - y * y - z * z);
		euler->roll = 0.0f;
	}
	else
	{
		euler->pitch = arcsine(sinp);
		euler->yaw = arctangent((w * z + x * y) * 2.0f, w * w + x * x - y * y - z * z);
		euler->roll = arctangent((w * x + y * z) * 2.0f, w * w - x * x - y * y + z * z);
	}
}
