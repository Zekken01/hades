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
struct real_matrix3x3;
struct real_matrix4x3;
struct real_plane3d;
struct real_point3d;
struct real_quaternion;
struct real_vector3d;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern float square_root(float value);  // hades: added for 0x10EFD4D0

real_vector3d *scale_vector3d(real_vector3d const *vector, float scale, real_vector3d *result);  // hades: added for 0x10EFE320
real_vector3d *vector_from_points3d(real_point3d const *a, real_point3d const *b, real_vector3d *result);  // hades: added for 0x10EFE320

extern float sine(float x);  // hades: added for 0x10EFC740

extern float dot_product3d(real_vector3d const *v1, real_vector3d const *v2);  // hades: added for 0x10EFF6A0

real_vector3d *cross_product3d(real_vector3d const *a, real_vector3d const *b, real_vector3d *out);  // hades: added for 0X10EFCBF0

extern void matrix4x3_multiply(real_matrix4x3 const *m1, real_matrix4x3 const *m2, real_matrix4x3 *result);
extern void matrix4x3_identity(real_matrix4x3 *matrix);
extern void matrix4x3_translation(real_matrix4x3 *matrix, real_point3d const *point);
extern void matrix4x3_inverse(real_matrix4x3 const *matrix, real_matrix4x3 *result);
extern real_vector3d *matrix4x3_transform_vector(real_matrix4x3 const *matrix, real_vector3d const *vector, real_vector3d *result);
extern real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);
extern real_vector3d *matrix4x3_inverse_transform_vector(real_matrix4x3 const *matrix, real_vector3d const *vector, real_vector3d *result);
extern real_point3d *matrix4x3_inverse_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);
extern void matrix4x3_transform_points(real_matrix4x3 const *matrix, long point_count, real_point3d const *points, real_point3d *out_points);
extern real_vector3d *matrix4x3_transform_normal(real_matrix4x3 const *matrix, real_vector3d const *normal, real_vector3d *result);
extern real_vector3d *matrix4x3_inverse_transform_normal(real_matrix4x3 const *matrix, real_vector3d const *normal, real_vector3d *result);
extern real_plane3d *matrix4x3_inverse_transform_plane(real_matrix4x3 const *matrix, real_plane3d const *plane, real_plane3d *result);
extern real_plane3d *matrix4x3_transform_plane(real_matrix4x3 const *matrix, real_plane3d const *plane, real_plane3d *result);
extern void matrix4x3_to_point_and_vectors(real_matrix4x3 *matrix, real_point3d *point, real_vector3d *forward, real_vector3d *up);
extern void matrix4x3_rotation_from_vectors(real_matrix4x3 *matrix, real_vector3d const *forward, real_vector3d const *up);
extern void matrix4x3_from_point_and_vectors(real_matrix4x3 *matrix, real_point3d const *point, real_vector3d const *forward, real_vector3d const *up);
extern void matrix4x3_rotation_to_angles(real_matrix4x3 const *matrix, real_euler_angles3d *angles);
extern void matrix4x3_rotation_from_angles(real_matrix4x3 *matrix, float yaw, float pitch, float roll);
extern void matrix4x3_rotation_from_axis_and_angle(real_matrix4x3 *matrix, real_vector3d const *axis, float sin_theta, float cos_theta);
extern real_vector3d *matrix3x3_transform_vector(real_matrix3x3 const *matrix, real_vector3d const *vector, real_vector3d *result);
extern real_vector3d *matrix3x3_inverse_transform_vector(real_matrix3x3 const *matrix, real_vector3d const *vector, real_vector3d *result);
extern real_matrix3x3 *matrix3x3_multiply(real_matrix3x3 *m1, real_matrix3x3 *m2, real_matrix3x3 *result);
extern void matrix3x3_from_angles(real_matrix3x3 *matrix, float yaw, float pitch, float roll);
extern void matrix3x3_from_axis_and_angle(real_matrix3x3 *matrix, real_vector3d const *axis, float sin_theta, float cos_theta);
extern real_quaternion *matrix3x3_rotation_to_quaternion(real_matrix3x3 const *matrix, real_quaternion *quaternion);
extern real_matrix3x3 *matrix3x3_rotation_from_quaternion(real_matrix3x3 *matrix, real_quaternion const *quaternion);
extern real_matrix3x3 *matrix3x3_from_forward_and_up(real_matrix3x3 *matrix, real_vector3d const *forward, real_vector3d const *up);

/* ---------- globals */

extern float cosine(float x);  // hades: added for 0x10EFF300
extern float arcsine(float x);  // hades: added for 0x10EFF300
extern float arctangent(float y, float x);  // hades: added for 0x10EFF300

/* ---------- private variables */

/* ---------- public code */

void matrix4x3_multiply(real_matrix4x3 const *m1, real_matrix4x3 const *m2, real_matrix4x3 *result) // 0x10EFE7D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_multiply@@YAXPBUreal_matrix4x3@@0PAU1@@Z");
	// static ...; // 0x10EFEBD5
	// static ...; // 0x10EFEBCC
	// static ...; // 0x10EFEB9C
	// static ...; // 0x10EFEB94
	// real_matrix4x3 const *m1;
	// real_matrix4x3 const *m2;
	// real_matrix4x3 *result;
	// real_vector3d forward;
	// real_point3d position;
	// real_vector3d left;
	// real_vector3d up;

	real_vector3d forward;
	real_vector3d left;
	real_vector3d up;
	forward.i = m1->forward.i * m2->forward.i + m1->left.i * m2->forward.j + m1->up.i * m2->forward.k;
	forward.j = m1->forward.j * m2->forward.i + m1->left.j * m2->forward.j + m1->up.j * m2->forward.k;
	forward.k = m1->forward.k * m2->forward.i + m1->left.k * m2->forward.j + m1->up.k * m2->forward.k;
	left.i = m1->forward.i * m2->left.i + m1->left.i * m2->left.j + m1->up.i * m2->left.k;
	left.j = m1->forward.j * m2->left.i + m1->left.j * m2->left.j + m1->up.j * m2->left.k;
	left.k = m1->forward.k * m2->left.i + m1->left.k * m2->left.j + m1->up.k * m2->left.k;
	up.i = m1->forward.i * m2->up.i + m1->left.i * m2->up.j + m1->up.i * m2->up.k;
	up.j = m1->forward.j * m2->up.i + m1->left.j * m2->up.j + m1->up.j * m2->up.k;
	up.k = m1->forward.k * m2->up.i + m1->left.k * m2->up.j + m1->up.k * m2->up.k;
	real_point3d position;
	position.x = (m1->forward.i * m2->position.x + m1->left.i * m2->position.y + m1->up.i * m2->position.z) * m1->scale + m1->position.x;
	position.y = (m1->forward.j * m2->position.x + m1->left.j * m2->position.y + m1->up.j * m2->position.z) * m1->scale + m1->position.y;
	position.z = (m1->forward.k * m2->position.x + m1->left.k * m2->position.y + m1->up.k * m2->position.z) * m1->scale + m1->position.z;
	result->scale = m1->scale * m2->scale;
	result->forward = forward;
	result->left = left;
	result->up = up;
	result->position = position;
}

void matrix4x3_identity(real_matrix4x3 *matrix) // 0x10EFDBE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_identity@@YAXPAUreal_matrix4x3@@@Z");
	// real_matrix4x3 *matrix;

	matrix->scale = 1.0f;
	matrix->forward = global_forward3d;
	matrix->left = global_left3d;
	matrix->up = global_up3d;
	matrix->position = global_origin3d;
}

void matrix4x3_translation(real_matrix4x3 *matrix, real_point3d const *point) // 0x10EFFB10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_translation@@YAXPAUreal_matrix4x3@@PBUreal_point3d@@@Z");
	// real_point3d const *point;

	matrix->scale = 1.0f;
	matrix->forward = global_forward3d;
	matrix->left = global_left3d;
	matrix->up = global_up3d;
	matrix->position = *point;
}

void matrix4x3_inverse(real_matrix4x3 const *matrix, real_matrix4x3 *result) // 0x10EFDCE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_inverse@@YAXPBUreal_matrix4x3@@PAU1@@Z");
	// static ...; // 0x10EFDF8C
	// static ...; // 0x10EFDF84
	// real_matrix4x3 const *matrix;
	// real_matrix4x3 *result;
	// real_vector3d vector;
	// float up_j;
	// float inv_scale;
	// float left_i;
	// float up_i;
		// float scale;

	real_vector3d vector = { -matrix->position.x, -matrix->position.y, -matrix->position.z };
	float inv_scale = 1.0f;
	if (matrix->scale != 1.0f)
	{
		float scale = matrix->scale;
		if (fabsf(scale) < 0.00001f)
			scale = scale < 0.0f ? -0.00001f : 0.00001f;
		inv_scale = 1.0f / scale;
		scale_vector3d(&vector, inv_scale, &vector);
	}
	result->scale = inv_scale;
	result->forward.i = matrix->forward.i;
	result->left.j = matrix->left.j;
	result->up.k = matrix->up.k;
	float left_i = matrix->left.i;
	result->left.i = matrix->forward.j;
	result->forward.j = left_i;
	float up_i = matrix->up.i;
	result->up.i = matrix->forward.k;
	result->forward.k = up_i;
	float up_j = matrix->up.j;
	result->up.j = matrix->left.k;
	result->left.k = up_j;
	result->position.x = vector.i * result->forward.i + vector.j * result->left.i + vector.k * result->up.i;
	result->position.y = vector.i * result->forward.j + vector.j * result->left.j + vector.k * result->up.j;
	result->position.z = vector.i * result->forward.k + vector.j * result->left.k + vector.k * result->up.k;
}

__declspec(safebuffers) real_vector3d *matrix4x3_transform_vector(real_matrix4x3 const *matrix, real_vector3d const *vector, real_vector3d *result) // 0x10EFF990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_transform_vector@@YAPAUreal_vector3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
	// static ...; // 0x10EFFAAC
	// real_matrix4x3 const *matrix;
	// real_vector3d const *vector;
	// real_vector3d *result;
	// real_vector3d v;

	real_vector3d const v = *vector;

	result->i = (matrix->forward.i * v.i + matrix->left.i * v.j + matrix->up.i * v.k) * matrix->scale;
	result->j = (matrix->forward.j * v.i + matrix->left.j * v.j + matrix->up.j * v.k) * matrix->scale;
	result->k = (matrix->forward.k * v.i + matrix->left.k * v.j + matrix->up.k * v.k) * matrix->scale;
	return result;
}

__declspec(safebuffers) real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result) // 0x10EFF760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_transform_point@@YAPAUreal_point3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
	// static ...; // 0x10EFF894
	// real_matrix4x3 const *matrix;
	// real_point3d const *point;
	// real_point3d *result;
	// real_point3d p;

	real_point3d const p = *point;

	result->x = (matrix->forward.i * p.x + matrix->left.i * p.y + matrix->up.i * p.z) * matrix->scale + matrix->position.x;
	result->y = (matrix->forward.j * p.x + matrix->left.j * p.y + matrix->up.j * p.z) * matrix->scale + matrix->position.y;
	result->z = (matrix->forward.k * p.x + matrix->left.k * p.y + matrix->up.k * p.z) * matrix->scale + matrix->position.z;
	return result;
}

real_vector3d *matrix4x3_inverse_transform_vector(real_matrix4x3 const *matrix, real_vector3d const *vector, real_vector3d *result) // 0x10EFE580
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_inverse_transform_vector@@YAPAUreal_vector3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
	// static ...; // 0x10EFE744
	// real_matrix4x3 const *matrix;
	// real_vector3d const *vector;
	// real_vector3d *result;
	// real_vector3d v;
		// float scale;

	real_vector3d v = *vector;
	if (matrix->scale != 1.0f)
	{
		float scale = matrix->scale;
		if (fabsf(scale) < 0.00001f)
			scale = scale < 0.0f ? -0.00001f : 0.00001f;
		scale_vector3d(&v, 1.0f / scale, &v);
	}
	result->i = v.i * matrix->forward.i + v.j * matrix->forward.j + v.k * matrix->forward.k;
	result->j = v.i * matrix->left.i + v.j * matrix->left.j + v.k * matrix->left.k;
	result->k = v.i * matrix->up.i + v.j * matrix->up.j + v.k * matrix->up.k;
	return result;
}

real_point3d *matrix4x3_inverse_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result) // 0x10EFE320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_inverse_transform_point@@YAPAUreal_point3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
	// static ...; // 0x10EFE4E8
	// real_matrix4x3 const *matrix;
	// real_point3d const *point;
	// real_point3d *result;
	// real_vector3d v;
		// float scale;

	real_vector3d v;
	vector_from_points3d(&matrix->position, point, &v);
	if (matrix->scale != 1.0f)
	{
		float scale = matrix->scale;
		if (fabsf(scale) < 0.00001f)
			scale = scale < 0.0f ? -0.00001f : 0.00001f;
		scale_vector3d(&v, 1.0f / scale, &v);
	}
	result->x = v.i * matrix->forward.i + v.j * matrix->forward.j + v.k * matrix->forward.k;
	result->y = v.i * matrix->left.i + v.j * matrix->left.j + v.k * matrix->left.k;
	result->z = v.i * matrix->up.i + v.j * matrix->up.j + v.k * matrix->up.k;
	return result;
}

void matrix4x3_transform_points(real_matrix4x3 const *matrix, long point_count, real_point3d const *points, real_point3d *out_points) // 0x10EFF900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_transform_points@@YAXPBUreal_matrix4x3@@JPBUreal_point3d@@PAU2@@Z");
	// real_point3d *out_points;
		// long i;

	long i;

	for (i = 0; i < point_count; i++)
	{
		matrix4x3_transform_point(matrix, &points[i], &out_points[i]);
	}
}


// hades: the original has no /GS cookie here although /GS is on and the
// function has a 12-byte struct local; safebuffers reproduces it. Cause
// not established - see the matrix-math note in memory.
__declspec(safebuffers) real_vector3d *matrix4x3_transform_normal(real_matrix4x3 const *matrix, real_vector3d const *normal, real_vector3d *result) // 0x10EFF530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_transform_normal@@YAPAUreal_vector3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
	// static ...; // 0x10EFF638
	// real_matrix4x3 const *matrix;
	// real_vector3d const *normal;
	// real_vector3d *result;
	// real_vector3d v;

	real_vector3d const v = *normal;

	result->i = v.i * matrix->forward.i + v.j * matrix->left.i + v.k * matrix->up.i;
	result->j = v.i * matrix->forward.j + v.j * matrix->left.j + v.k * matrix->up.j;
	result->k = v.i * matrix->forward.k + v.j * matrix->left.k + v.k * matrix->up.k;
	return result;
}


// hades: the original has no /GS cookie here although /GS is on and the
// function has a 12-byte struct local; safebuffers reproduces it. Cause
// not established - see the matrix-math note in memory.
__declspec(safebuffers) real_vector3d *matrix4x3_inverse_transform_normal(real_matrix4x3 const *matrix, real_vector3d const *normal, real_vector3d *result) // 0x10EFE050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_inverse_transform_normal@@YAPAUreal_vector3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
	// static ...; // 0x10EFE158
	// real_matrix4x3 const *matrix;
	// real_vector3d const *normal;
	// real_vector3d *result;
	// real_vector3d v;

	real_vector3d const v = *normal;

	result->i = v.i * matrix->forward.i + v.j * matrix->forward.j + v.k * matrix->forward.k;
	result->j = v.i * matrix->left.i + v.j * matrix->left.j + v.k * matrix->left.k;
	result->k = v.i * matrix->up.i + v.j * matrix->up.j + v.k * matrix->up.k;
	return result;
}

real_plane3d *matrix4x3_inverse_transform_plane(real_matrix4x3 const *matrix, real_plane3d const *plane, real_plane3d *result) // 0x10EFE1C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_inverse_transform_plane@@YAPAUreal_plane3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
	// real_plane3d *result;
	// float scale;

	result->d = plane->d - dot_product3d((real_vector3d const *)&matrix->position, &plane->normal);
	float scale = matrix->scale;
	if (scale != 1.0f)
	{
		if (fabsf(scale) < 0.00001f)
		{
			scale = scale < 0.0f ? -0.00001f : 0.00001f;
		}

		result->d = result->d / scale;
	}

	matrix4x3_inverse_transform_normal(matrix, &plane->normal, &result->normal);
	return result;
}

real_plane3d *matrix4x3_transform_plane(real_matrix4x3 const *matrix, real_plane3d const *plane, real_plane3d *result) // 0x10EFF6A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_transform_plane@@YAPAUreal_plane3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
	// real_plane3d *result;

	matrix4x3_transform_normal(matrix, &plane->normal, &result->normal);
	result->d = plane->d * matrix->scale + dot_product3d((real_vector3d const *)&matrix->position, &result->normal);
	return result;
}

void matrix4x3_to_point_and_vectors(real_matrix4x3 *matrix, real_point3d *point, real_vector3d *forward, real_vector3d *up) // 0x10EFF490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_to_point_and_vectors@@YAXPAUreal_matrix4x3@@PAUreal_point3d@@PAUreal_vector3d@@2@Z");
	// real_vector3d *up;

	*forward = matrix->forward;
	*up = matrix->up;
	*point = matrix->position;
}

void matrix4x3_rotation_from_vectors(real_matrix4x3 *matrix, real_vector3d const *forward, real_vector3d const *up) // 0x10EFF220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_rotation_from_vectors@@YAXPAUreal_matrix4x3@@PBUreal_vector3d@@1@Z");
	// real_vector3d const *up;

	matrix->scale = 1.0f;
	matrix->forward = *forward;
	cross_product3d(up, forward, &matrix->left);
	matrix->up = *up;
	matrix->position = global_origin3d;
}

void matrix4x3_from_point_and_vectors(real_matrix4x3 *matrix, real_point3d const *point, real_vector3d const *forward, real_vector3d const *up) // 0x10EFDB30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_from_point_and_vectors@@YAXPAUreal_matrix4x3@@PBUreal_point3d@@PBUreal_vector3d@@2@Z");
	// real_vector3d const *up;

	#line 383 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\math\\matrix_math.cpp"
		assert(point);
		#line 389 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\matrix_math.cpp"
	matrix4x3_rotation_from_vectors(matrix, forward, up);
	matrix->position = *point;
}

void matrix4x3_rotation_to_angles(real_matrix4x3 const *matrix, real_euler_angles3d *angles) // 0x10EFF300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_rotation_to_angles@@YAXPBUreal_matrix4x3@@PAUreal_euler_angles3d@@@Z");
	// real_euler_angles3d *angles;
	// float cos_pitch;

	angles->pitch = -arcsine(matrix->up.i);

	float cos_pitch = cosine(angles->pitch);
	if (cos_pitch <= 0.0001f)
	{
		angles->roll = 0.0f;
		angles->yaw = arctangent(matrix->forward.j, matrix->left.j);
	}
	else
	{
		angles->roll = arctangent(-matrix->up.j / cos_pitch, matrix->up.k / cos_pitch);
		angles->yaw = arctangent(-matrix->left.i / cos_pitch, matrix->forward.i / cos_pitch);
	}
}

void matrix4x3_rotation_from_angles(real_matrix4x3 *matrix, float yaw, float pitch, float roll) // 0x10EFECF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_rotation_from_angles@@YAXPAUreal_matrix4x3@@MMM@Z");
	// float roll;
	// float cos_roll_sin_pitch;
	// float sin_yaw;
	// float sin_roll_sin_pitch;
	// float sin_roll;
	// float cos_yaw;
	// float cos_roll;
	// float sin_pitch;
	// float cos_pitch;

	float cos_roll = cosine(roll);
	float sin_roll = sine(roll);
	float cos_pitch = cosine(pitch);
	float sin_pitch = sine(pitch);
	float cos_yaw = cosine(yaw);
	float sin_yaw = sine(yaw);
	float cos_roll_sin_pitch = cos_roll * sin_pitch;
	float sin_roll_sin_pitch = sin_roll * sin_pitch;
	matrix->scale = 1.0f;
	matrix->forward.i = cos_pitch * cos_yaw;
	matrix->forward.j = -sin_roll_sin_pitch * cos_yaw + cos_roll * sin_yaw;
	matrix->forward.k = cos_roll_sin_pitch * cos_yaw + sin_roll * sin_yaw;
	matrix->left.i = -cos_pitch * sin_yaw;
	matrix->left.j = sin_roll_sin_pitch * sin_yaw + cos_roll * cos_yaw;
	matrix->left.k = -cos_roll_sin_pitch * sin_yaw + sin_roll * cos_yaw;
	matrix->up.i = -sin_pitch;
	matrix->up.j = -sin_roll * cos_pitch;
	matrix->up.k = cos_roll * cos_pitch;
	matrix->position = global_origin3d;
}

void matrix4x3_rotation_from_axis_and_angle(real_matrix4x3 *matrix, real_vector3d const *axis, float sin_theta, float cos_theta) // 0x10EFEF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix4x3_rotation_from_axis_and_angle@@YAXPAUreal_matrix4x3@@PBUreal_vector3d@@MM@Z");
	// float cos_theta;
	// float zz;
	// float one_minus_cos;
	// float sin_y;
	// float sin_z;
	// float x;
	// float xx;
	// float y;
	// float yy;
	// float sin_x;
	// float cxy;
	// float cyz;
	// float cxz;
	// float z;

	float x = axis->i;
	float y = axis->j;
	float z = axis->k;
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float sin_x = sin_theta * x;
	float sin_y = sin_theta * y;
	float sin_z = sin_theta * z;
	float one_minus_cos = 1.0f - cos_theta;
	float cxy = x * y * one_minus_cos;
	float cxz = x * z * one_minus_cos;
	float cyz = y * z * one_minus_cos;
	matrix->scale = 1.0f;
	matrix->forward.i = (1.0f - xx) * cos_theta + xx;
	matrix->forward.j = cxy + sin_z;
	matrix->forward.k = cxz - sin_y;
	matrix->left.i = cxy - sin_z;
	matrix->left.j = (1.0f - yy) * cos_theta + yy;
	matrix->left.k = cyz + sin_x;
	matrix->up.i = cxz + sin_y;
	matrix->up.j = cyz - sin_x;
	matrix->up.k = (1.0f - zz) * cos_theta + zz;
	matrix->position = global_origin3d;
}


// hades: the original has no /GS cookie here although /GS is on and the
// function has a 12-byte struct local; safebuffers reproduces it. Cause
// not established - see the matrix-math note in memory.
__declspec(safebuffers) real_vector3d *matrix3x3_transform_vector(real_matrix3x3 const *matrix, real_vector3d const *vector, real_vector3d *result) // 0x10EFD9D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix3x3_transform_vector@@YAPAUreal_vector3d@@PBUreal_matrix3x3@@PBU1@PAU1@@Z");
	// static ...; // 0x10EFDAD4
	// real_matrix3x3 const *matrix;
	// real_vector3d const *vector;
	// real_vector3d *result;
	// real_vector3d v;

	real_vector3d const v = *vector;

	result->i = v.i * matrix->forward.i + v.j * matrix->left.i + v.k * matrix->up.i;
	result->j = v.i * matrix->forward.j + v.j * matrix->left.j + v.k * matrix->up.j;
	result->k = v.i * matrix->forward.k + v.j * matrix->left.k + v.k * matrix->up.k;
	return result;
}

__declspec(safebuffers) real_vector3d *matrix3x3_inverse_transform_vector(real_matrix3x3 const *matrix, real_vector3d const *vector, real_vector3d *result) // 0x10EFCC90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix3x3_inverse_transform_vector@@YAPAUreal_vector3d@@PBUreal_matrix3x3@@PBU1@PAU1@@Z");
	// static ...; // 0x10EFCD94
	// real_matrix3x3 const *matrix;
	// real_vector3d const *vector;
	// real_vector3d *result;
	// real_vector3d v;

	real_vector3d const v = *vector;

	result->i = v.i * matrix->forward.i + v.j * matrix->forward.j + v.k * matrix->forward.k;
	result->j = v.i * matrix->left.i + v.j * matrix->left.j + v.k * matrix->left.k;
	result->k = v.i * matrix->up.i + v.j * matrix->up.j + v.k * matrix->up.k;
	return result;
}

real_matrix3x3 *matrix3x3_multiply(real_matrix3x3 *m1, real_matrix3x3 *m2, real_matrix3x3 *result) // 0x10EFCDF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix3x3_multiply@@YAPAUreal_matrix3x3@@PAU1@00@Z");
	// static ...; // 0x10EFD0CC
	// static ...; // 0x10EFD0A8
	// static ...; // 0x10EFD0A0
	// real_matrix3x3 *m1;
	// real_matrix3x3 *m2;
	// real_matrix3x3 *result;
	// real_vector3d forward;
	// real_vector3d left;
	// real_vector3d up;

	real_vector3d forward;
	real_vector3d left;
	real_vector3d up;
	forward.i = m1->forward.i * m2->forward.i + m1->left.i * m2->forward.j + m1->up.i * m2->forward.k;
	forward.j = m1->forward.j * m2->forward.i + m1->left.j * m2->forward.j + m1->up.j * m2->forward.k;
	forward.k = m1->forward.k * m2->forward.i + m1->left.k * m2->forward.j + m1->up.k * m2->forward.k;
	left.i = m1->forward.i * m2->left.i + m1->left.i * m2->left.j + m1->up.i * m2->left.k;
	left.j = m1->forward.j * m2->left.i + m1->left.j * m2->left.j + m1->up.j * m2->left.k;
	left.k = m1->forward.k * m2->left.i + m1->left.k * m2->left.j + m1->up.k * m2->left.k;
	up.i = m1->forward.i * m2->up.i + m1->left.i * m2->up.j + m1->up.i * m2->up.k;
	up.j = m1->forward.j * m2->up.i + m1->left.j * m2->up.j + m1->up.j * m2->up.k;
	up.k = m1->forward.k * m2->up.i + m1->left.k * m2->up.j + m1->up.k * m2->up.k;
	result->forward = forward;
	result->left = left;
	result->up = up;
	return result;
}

void matrix3x3_from_angles(real_matrix3x3 *matrix, float yaw, float pitch, float roll) // 0x10EFC740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix3x3_from_angles@@YAXPAUreal_matrix3x3@@MMM@Z");
	// float roll;
	// float cos_roll_sin_pitch;
	// float sin_yaw;
	// float sin_roll_sin_pitch;
	// float sin_roll;
	// float cos_yaw;
	// float cos_roll;
	// float sin_pitch;
	// float cos_pitch;

	float cos_roll = cosine(roll);
	float sin_roll = sine(roll);
	float cos_pitch = cosine(pitch);
	float sin_pitch = sine(pitch);
	float cos_yaw = cosine(yaw);
	float sin_yaw = sine(yaw);
	float cos_roll_sin_pitch = cos_roll * sin_pitch;
	float sin_roll_sin_pitch = sin_roll * sin_pitch;
	matrix->forward.i = cos_pitch * cos_yaw;
	matrix->forward.j = -sin_roll_sin_pitch * cos_yaw + cos_roll * sin_yaw;
	matrix->forward.k = cos_roll_sin_pitch * cos_yaw + sin_roll * sin_yaw;
	matrix->left.i = -cos_pitch * sin_yaw;
	matrix->left.j = sin_roll_sin_pitch * sin_yaw + cos_roll * cos_yaw;
	matrix->left.k = -cos_roll_sin_pitch * sin_yaw + sin_roll * cos_yaw;
	matrix->up.i = -sin_pitch;
	matrix->up.j = -sin_roll * cos_pitch;
	matrix->up.k = cos_roll * cos_pitch;
}

void matrix3x3_from_axis_and_angle(real_matrix3x3 *matrix, real_vector3d const *axis, float sin_theta, float cos_theta) // 0x10EFC990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix3x3_from_axis_and_angle@@YAXPAUreal_matrix3x3@@PBUreal_vector3d@@MM@Z");
	// float cos_theta;
	// float zz;
	// float one_minus_cos;
	// float sin_y;
	// float sin_z;
	// float x;
	// float xx;
	// float y;
	// float yy;
	// float sin_x;
	// float cxy;
	// float cyz;
	// float cxz;
	// float z;

	float x = axis->i;
	float y = axis->j;
	float z = axis->k;
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float sin_x = sin_theta * x;
	float sin_y = sin_theta * y;
	float sin_z = sin_theta * z;
	float one_minus_cos = 1.0f - cos_theta;
	float cxy = x * y * one_minus_cos;
	float cxz = x * z * one_minus_cos;
	float cyz = y * z * one_minus_cos;
	matrix->forward.i = (1.0f - xx) * cos_theta + xx;
	matrix->forward.j = cxy + sin_z;
	matrix->forward.k = cxz - sin_y;
	matrix->left.i = cxy - sin_z;
	matrix->left.j = (1.0f - yy) * cos_theta + yy;
	matrix->left.k = cyz + sin_x;
	matrix->up.i = cxz + sin_y;
	matrix->up.j = cyz - sin_x;
	matrix->up.k = (1.0f - zz) * cos_theta + zz;
}

real_quaternion *matrix3x3_rotation_to_quaternion(real_matrix3x3 const *matrix, real_quaternion *quaternion) // 0x10EFD4D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix3x3_rotation_to_quaternion@@YAPAUreal_quaternion@@PBUreal_matrix3x3@@PAU1@@Z");
	// real_quaternion *quaternion;
	// float trace;
		// float t;
		// float s;

	float trace = matrix->forward.i + matrix->left.j + matrix->up.k;
	if (trace > 0.0f)
	{
		float s = square_root(trace + 1.0f) * 0.5f;
		float t = 0.25f / s;
		quaternion->w = s;
		quaternion->i = (matrix->left.k - matrix->up.j) * t;
		quaternion->j = (matrix->up.i - matrix->forward.k) * t;
		quaternion->k = (matrix->forward.j - matrix->left.i) * t;
	}
	else if (matrix->forward.i >= matrix->left.j && matrix->forward.i >= matrix->up.k)
	{
		float s = square_root(1.0f + matrix->forward.i - matrix->left.j - matrix->up.k) * 0.5f;
		float t = 0.25f / s;
		quaternion->i = s;
		quaternion->j = (matrix->forward.j + matrix->left.i) * t;
		quaternion->k = (matrix->forward.k + matrix->up.i) * t;
		quaternion->w = (matrix->left.k - matrix->up.j) * t;
	}
	else if (matrix->left.j > matrix->up.k)
	{
		float s = square_root(1.0f + matrix->left.j - matrix->forward.i - matrix->up.k) * 0.5f;
		float t = 0.25f / s;
		quaternion->i = (matrix->left.i + matrix->forward.j) * t;
		quaternion->j = s;
		quaternion->k = (matrix->up.j + matrix->left.k) * t;
		quaternion->w = (matrix->up.i - matrix->forward.k) * t;
	}
	else
	{
		float s = square_root(1.0f + matrix->up.k - matrix->forward.i - matrix->left.j) * 0.5f;
		float t = 0.25f / s;
		quaternion->i = (matrix->up.i + matrix->forward.k) * t;
		quaternion->j = (matrix->up.j + matrix->left.k) * t;
		quaternion->k = s;
		quaternion->w = (matrix->forward.j - matrix->left.i) * t;
	}
	if (quaternion->w < 0.0f)
	{
		quaternion->w = -quaternion->w;
		quaternion->i = -quaternion->i;
		quaternion->j = -quaternion->j;
		quaternion->k = -quaternion->k;
	}
	return quaternion;
}

real_matrix3x3 *matrix3x3_rotation_from_quaternion(real_matrix3x3 *matrix, real_quaternion const *quaternion) // 0x10EFD1A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix3x3_rotation_from_quaternion@@YAPAUreal_matrix3x3@@PAU1@PBUreal_quaternion@@@Z");
	// real_quaternion const *quaternion;
	// float zz;
	// float yz;
	// float xz;
	// float w;
	// float x;
	// float s;
	// float wy;
	// float norm_sq;
	// float xx;
	// float y;
	// float yy;
	// float wx;
	// float wz;
	// float z;
	// float xy;

	float x = quaternion->i;
	float y = quaternion->j;
	float z = quaternion->k;
	float w = quaternion->w;
	float norm_sq = x * x + y * y + z * z + w * w;
	float s = norm_sq <= 0.00001f ? 0.0f : 2.0f / norm_sq;
	float xx = x * x * s;
	float yy = y * y * s;
	float zz = z * z * s;
	float xy = x * y * s;
	float xz = x * z * s;
	float yz = y * z * s;
	float wx = w * x * s;
	float wy = w * y * s;
	float wz = w * z * s;
	matrix->forward.i = 1.0f - (yy + zz);
	matrix->forward.j = xy + wz;
	matrix->forward.k = xz - wy;
	matrix->left.i = xy - wz;
	matrix->left.j = 1.0f - (xx + zz);
	matrix->left.k = yz + wx;
	matrix->up.i = xz + wy;
	matrix->up.j = yz - wx;
	matrix->up.k = 1.0f - (xx + yy);
	return matrix;
}

real_matrix3x3 *matrix3x3_from_forward_and_up(real_matrix3x3 *matrix, real_vector3d const *forward, real_vector3d const *up) // 0x10EFCBF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?matrix3x3_from_forward_and_up@@YAPAUreal_matrix3x3@@PAU1@PBUreal_vector3d@@1@Z");
	// real_vector3d const *up;

	matrix->forward = *forward;
	cross_product3d(up, forward, &matrix->left);
	matrix->up = *up;
	return matrix;
}

/* ---------- private code */
