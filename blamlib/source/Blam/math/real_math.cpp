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

struct real_euler_angles2d;
struct real_euler_angles3d;
struct real_matrix4x3;
struct real_plane3d;
struct real_point2d;
struct real_point3d;
struct real_rectangle3d;
struct real_vector2d;
struct real_vector3d;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void matrix4x3_from_point_and_vectors(real_matrix4x3 *matrix, real_point3d const *point, real_vector3d const *forward, real_vector3d const *up);  // hades: added for 0x10EF9C90
extern void matrix4x3_rotation_to_angles(real_matrix4x3 const *matrix, real_euler_angles3d *angles);  // hades: added for 0x10EF9C90

extern void matrix4x3_rotation_from_angles(real_matrix4x3 *matrix, float yaw, float pitch, float roll);  // hades: added for 0x10EFBF40
extern void matrix4x3_to_point_and_vectors(real_matrix4x3 *matrix, real_point3d *point, real_vector3d *forward, real_vector3d *up);  // hades: added for 0x10EFBF40

extern "C" float __cdecl atan2f(float _Y, float _X);  // hades: added for 0X10EF97E0

extern float real_pin(float x, float min, float max);
extern float real_pin_0_1(float x);
extern float square_root(float x);
extern float reciprocal_square_root(float x);
extern float cosine(float x);
extern float sine(float x);
extern float tangent(float x);
extern float arcsine(float x);
extern float arccosine(float x);
extern float arctangent(float y, float x);
extern float normalize3d(real_vector3d *v);
extern float magnitude_squared3d(real_vector3d const *v);
extern float magnitude3d(real_vector3d const *v);
extern float distance_squared3d(real_point3d const *p1, real_point3d const *p2);
extern float distance3d(real_point3d const *p1, real_point3d const *p2);
extern float dot_product3d(real_vector3d const *v1, real_vector3d const *v2);
extern real_vector3d *cross_product3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result);
extern real_vector3d *perpendicular3d(real_vector3d const *v, real_vector3d *result);
extern real_vector3d *set_real_vector3d(real_vector3d *result, float i, float j, float k);
extern real_vector3d *add_vectors3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result);
extern real_vector3d *subtract_vectors3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result);
extern real_vector3d *scale_vector3d(real_vector3d const *v1, float scale, real_vector3d *result);
extern real_vector3d *negate_vector3d(real_vector3d const *v, real_vector3d *result);
extern real_vector3d *vector_from_points3d(real_point3d const *p1, real_point3d const *p2, real_vector3d *result);
extern real_vector3d *generate_up_vector3d(real_vector3d const *forward, real_vector3d *up);
extern real_vector3d *vector3d_from_euler_angles2d(real_vector3d *result, real_euler_angles2d const *angles);
extern real_euler_angles3d *euler_angles3d_from_vectors3d(real_euler_angles3d *angles, real_vector3d const *forward, real_vector3d const *up);
extern real_vector3d *vector_from_yaw_and_pitch(float yaw, float pitch, real_vector3d *result);
extern real_point3d *point_from_line3d(real_point3d const *origin, real_vector3d const *vector, float t, real_point3d *result);
extern real_point3d *set_real_point3d(real_point3d *point, float x, float y, float z);
extern real_vector3d *vectors_interpolate(real_vector3d const *v1, real_vector3d const *v2, float t, real_vector3d *result);
extern float angle_between_normalized_vectors3d(real_vector3d const *v1, real_vector3d const *v2);
extern float angle_between_vectors3d(real_vector3d const *v1, real_vector3d const *v2);
extern real_vector3d *rotate_vector_about_axis(real_vector3d *vector, real_vector3d const *axis, float sin_theta, float cos_theta);
extern real_plane3d *plane3d_from_point_and_normal(real_plane3d *plane, real_point3d const *point, real_vector3d const *normal);
extern real_plane3d *plane3d_negate(real_plane3d const *plane, real_plane3d *result);
extern float plane3d_distance_to_point(real_plane3d const *plane, real_point3d const *point);
extern void vectors3d_from_euler_angles3d(real_vector3d *forward, real_vector3d *up, real_euler_angles3d const *angles);
extern real_vector2d *scale_vector2d(real_vector2d const *v, float scale, real_vector2d *result);
extern real_vector2d *negate_vector2d(real_vector2d const *v, real_vector2d *result);
extern real_vector2d *add_vectors2d(real_vector2d const *v1, real_vector2d const *v2, real_vector2d *result);
extern real_vector2d *set_real_vector2d(real_vector2d *result, float i, float j);
extern real_vector2d *subract_vectors2d(real_vector2d const *v1, real_vector2d const *v2, real_vector2d *result);
extern real_vector2d *rotate_vector2d(real_vector2d const *v, float sin_y, float cos_x, real_vector2d *result);
extern real_vector2d *vector_from_points2d(real_point2d const *p1, real_point2d const *p2, real_vector2d *result);
extern float angle_between_vectors2d(real_vector2d const *v1, real_vector2d const *v2);
extern float signed_angle_between_vectors2d(real_vector2d const *v1, real_vector2d const *v2);
extern real_point2d *point_from_line2d(real_point2d const *origin, real_vector2d const *vector, float t, real_point2d *result);
extern real_point2d *set_real_point2d(real_point2d *point, float x, float y);
extern float magnitude2d_squared(real_vector2d const *v);
extern float magnitude2d(real_vector2d const *v);
extern float normalize2d(real_vector2d *v);
extern float dot_product2d(real_vector2d const *v1, real_vector2d const *v2);
extern float cross_product2d(real_vector2d const *v1, real_vector2d const *v2);
extern long rectangle3d_build_vertices(real_rectangle3d const &bounds, long maximum_vertex_count, real_point3d (&vertices)[8]);
extern long rectangle3d_build_edges(real_rectangle3d const &bounds, long maximum_edge_count, real_point3d (*const edges)[2]);
extern void rectangle3d_build_faces(real_rectangle3d const &bounds, real_point3d (*const faces)[4]);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

float real_pin(float x, float min, float max) // 0x10EFA880
{
	return min > x ? min : (x > max ? max : x);
}

float real_pin_0_1(float x) // 0x10EFA940
{
	return real_pin(x, 0.0f, 1.0f);
}

float square_root(float x) // 0x10EFB9E0
{
	return sqrtf(x);
}

float reciprocal_square_root(float x) // 0x10EFA9C0
{
	return 1.0f / square_root(x);
}

float cosine(float x) // 0x10EF9850
{
	return cosf(x);
}

float sine(float x) // 0x10EFB980
{
	return sinf(x);
}

float tangent(float x) // 0x10EFBB60
{
	return tanf(x);
}

float arcsine(float x) // 0x10EF9780
{
	return asinf(x);
}

float arccosine(float x) // 0x10EF9720
{
	return acosf(x);
}

float arctangent(float y, float x) // 0x10EF97E0
{
	return atan2f(y, x);
}

float normalize3d(real_vector3d *v) // 0x10EFA2E0
{
	float m = magnitude3d(v);

	if (m < 0.00001f)
	{
		return 0.0f;
	}
	else
	{
		scale_vector3d(v, 1.0f / m, v);
	}

	return m;
}

float magnitude_squared3d(real_vector3d const *v) // 0x10EFA070
{
	return v->i * v->i + v->j * v->j + v->k * v->k;
}

float magnitude3d(real_vector3d const *v) // 0x10EFA010
{
	return square_root(magnitude_squared3d(v));
}

float distance_squared3d(real_point3d const *p1, real_point3d const *p2) // 0x10EF9AA0
{
	real_vector3d v;

	vector_from_points3d(p1, p2, &v);
	return magnitude_squared3d(&v);
}

float distance3d(real_point3d const *p1, real_point3d const *p2) // 0x10EF9A30
{
	return square_root(distance_squared3d(p1, p2));
}

float dot_product3d(real_vector3d const *v1, real_vector3d const *v2) // 0x10EF9BF0
{
	return v1->i * v2->i + v1->j * v2->j + v1->k * v2->k;
}

real_vector3d *cross_product3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result) // 0x10EF9940
{
	result->i = v1->j * v2->k - v1->k * v2->j;
	result->j = v1->k * v2->i - v1->i * v2->k;
	result->k = v1->i * v2->j - v1->j * v2->i;

	return result;
}

real_vector3d *perpendicular3d(real_vector3d const *v, real_vector3d *result) // 0x10EFA390
{
	float abs_i = fabs(v->i);
	float abs_j = fabs(v->j);
	float abs_k = fabs(v->k);
	if (abs_i > abs_j || abs_i > abs_k)
	{
		if (abs_j > abs_k)
		{
			*result = real_vector3d{ v->j, -v->i, 0.0f };
		}
		else
		{
			*result = real_vector3d{ -v->k, 0.0f, v->i };
		}
	}
	else
	{
		*result = real_vector3d{ 0.0f, v->k, -v->j };
	}

	return result;
}

real_vector3d *set_real_vector3d(real_vector3d *result, float i, float j, float k) // 0x10EFB810
{
	result->i = i;
	result->j = j;
	result->k = k;
	return result;
}

real_vector3d *add_vectors3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result) // 0x10EF9280
{
	result->i = v1->i + v2->i;
	result->j = v1->j + v2->j;
	result->k = v1->k + v2->k;

	return result;
}

real_vector3d *subtract_vectors3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result) // 0x10EFBAC0
{
	result->i = v1->i - v2->i;
	result->j = v1->j - v2->j;
	result->k = v1->k - v2->k;
	return result;
}

real_vector3d *scale_vector3d(real_vector3d const *v1, float scale, real_vector3d *result) // 0x10EFB610
{
	result->i = scale * v1->i;
	result->j = scale * v1->j;
	result->k = scale * v1->k;

	return result;
}

real_vector3d *negate_vector3d(real_vector3d const *v, real_vector3d *result) // 0x10EFA190
{
	result->i = -v->i;
	result->j = -v->j;
	result->k = -v->k;

	return result;
}

real_vector3d *vector_from_points3d(real_point3d const *p1, real_point3d const *p2, real_vector3d *result) // 0x10EFBD50
{
	result->i = p2->x - p1->x;
	result->j = p2->y - p1->y;
	result->k = p2->z - p1->z;

	return result;
}

real_vector3d *generate_up_vector3d(real_vector3d const *forward, real_vector3d *up) // 0x10EF9DE0
{
	real_vector3d orth;

	orth.i = forward->j;
	orth.j = -forward->i;
	orth.k = 0.0f;
	if (normalize3d(&orth) < 0.0000099999997f)
	{
		orth = global_forward3d;
	}

	cross_product3d(&orth, forward, up);
	return up;
}

real_vector3d *vector3d_from_euler_angles2d(real_vector3d *result, real_euler_angles2d const *angles) // 0x10EFBBC0
{
	float cos_pitch = cosine(angles->pitch);
	result->i = cosine(angles->yaw) * cos_pitch;
	result->j = sine(angles->yaw) * cos_pitch;
	result->k = sine(angles->pitch);
	return result;
}

#line 404
real_euler_angles3d *euler_angles3d_from_vectors3d(real_euler_angles3d *angles, real_vector3d const *forward, real_vector3d const *up) // 0x10EF9C90
{
#line 412

	#line 406 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\math\\real_math.cpp"
		assert(forward);
		assert(up);
		assert(angles);
		#line 418 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\math\\real_math.cpp"
	real_matrix4x3 matrix;
	matrix4x3_from_point_and_vectors(&matrix, &global_origin3d, forward, up);
	matrix4x3_rotation_to_angles(&matrix, angles);
	return angles;
}

real_vector3d *vector_from_yaw_and_pitch(float yaw, float pitch, real_vector3d *result) // 0x10EFBDF0
{
	result->i = cosine(yaw) * cosine(pitch);
	result->j = sine(yaw) * cosine(pitch);
	result->k = sine(pitch);

	return result;
}

real_point3d *point_from_line3d(real_point3d const *origin, real_vector3d const *vector, float t, real_point3d *result) // 0x10EFA7D0
{
	result->x = vector->i * t + origin->x;
	result->y = vector->j * t + origin->y;
	result->z = vector->k * t + origin->z;

	return result;
}

real_point3d *set_real_point3d(real_point3d *point, float x, float y, float z) // 0x10EFB720
{
	point->x = x;
	point->y = y;
	point->z = z;
	return point;
}

real_vector3d *vectors_interpolate(real_vector3d const *v1, real_vector3d const *v2, float t, real_vector3d *result) // 0x10EFC050
{
	result->i = (1.0f - t) * v1->i + t * v2->i;
	result->j = (1.0f - t) * v1->j + t * v2->j;
	result->k = (1.0f - t) * v1->k + t * v2->k;
	return result;
}

float angle_between_normalized_vectors3d(real_vector3d const *v1, real_vector3d const *v2) // 0x10EF9320
{
	return arccosine(real_pin(dot_product3d(v1, v2), -1.0f, 1.0f));
}

float angle_between_vectors3d(real_vector3d const *v1, real_vector3d const *v2) // 0x10EF9570
{
	float angle_radians = 0.0f;
	float magnitude_product = magnitude3d(v1) * magnitude3d(v2);
	if (magnitude_product != 0.0f)
	{
		float dot = dot_product3d(v1, v2);
		float cos_angle = real_pin(2.0f * dot * dot / magnitude_product - 1.0f, -1.0f, 1.0f);
		angle_radians = arccosine(cos_angle) * 0.5f;
		if (dot < 0.0f)
			return 3.14159265f - angle_radians;
	}
	return angle_radians;
}

real_vector3d *rotate_vector_about_axis(real_vector3d *vector, real_vector3d const *axis, float sin_theta, float cos_theta) // 0x10EFB3C0
{
	float one_minus_cos = (1.0f - cos_theta) * dot_product3d(vector, axis);

	vector->i = cos_theta * vector->i + one_minus_cos * axis->i - (vector->j * axis->k - vector->k * axis->j) * sin_theta;
	vector->j = cos_theta * vector->j + one_minus_cos * axis->j - (vector->k * axis->i - vector->i * axis->k) * sin_theta;
	vector->k = cos_theta * vector->k + one_minus_cos * axis->k - (vector->i * axis->j - vector->j * axis->i) * sin_theta;

	return vector;
}

real_plane3d *plane3d_from_point_and_normal(real_plane3d *plane, real_point3d const *point, real_vector3d const *normal) // 0x10EFA640
{
	plane->normal = *normal;
	plane->d = dot_product3d((real_vector3d const *)point, normal);

	return plane;
}

real_plane3d *plane3d_negate(real_plane3d const *plane, real_plane3d *result) // 0x10EFA6C0
{
	negate_vector3d(&plane->normal, &result->normal);
	result->d = -plane->d;
	return result;
}

float plane3d_distance_to_point(real_plane3d const *plane, real_point3d const *point) // 0x10EFA590
{
	return point->x * plane->normal.i + point->y * plane->normal.j + point->z * plane->normal.k - plane->d;
}

void vectors3d_from_euler_angles3d(real_vector3d *forward, real_vector3d *up, real_euler_angles3d const *angles) // 0x10EFBF40
{
	real_matrix4x3 matrix;
	real_point3d point;

	matrix4x3_rotation_from_angles(&matrix, angles->yaw, angles->pitch, angles->roll);
	matrix4x3_to_point_and_vectors(&matrix, &point, forward, up);
}

real_vector2d *scale_vector2d(real_vector2d const *v, float scale, real_vector2d *result) // 0x10EFB590
{
	result->i = scale * v->i;
	result->j = scale * v->j;

	return result;
}

real_vector2d *negate_vector2d(real_vector2d const *v, real_vector2d *result) // 0x10EFA110
{
	result->i = -v->i;
	result->j = -v->j;

	return result;
}

real_vector2d *add_vectors2d(real_vector2d const *v1, real_vector2d const *v2, real_vector2d *result) // 0x10EF9200
{
	result->i = v1->i + v2->i;
	result->j = v1->j + v2->j;
	return result;
}

real_vector2d *set_real_vector2d(real_vector2d *result, float i, float j) // 0x10EFB7A0
{
	result->i = i;
	result->j = j;

	return result;
}

real_vector2d *subract_vectors2d(real_vector2d const *v1, real_vector2d const *v2, real_vector2d *result) // 0x10EFBA40
{
	result->i = v1->i - v2->i;
	result->j = v1->j - v2->j;
	return result;
}

real_vector2d *rotate_vector2d(real_vector2d const *v, float sin_y, float cos_x, real_vector2d *result) // 0x10EFB310
{
	result->i = cos_x * v->i - sin_y * v->j;
	result->j = sin_y * v->i + cos_x * v->j;
	return result;
}

real_vector2d *vector_from_points2d(real_point2d const *p1, real_point2d const *p2, real_vector2d *result) // 0x10EFBCD0
{
	result->i = p2->x - p1->x;
	result->j = p2->y - p1->y;
	return result;
}

float angle_between_vectors2d(real_vector2d const *v1, real_vector2d const *v2) // 0x10EF93C0
{
	float angle_radians = 0.0f;
	float magnitude_product = magnitude2d(v1) * magnitude2d(v2);
	if (magnitude_product != 0.0f)
	{
		float dot = dot_product2d(v1, v2);
		float cos_angle = real_pin(2.0f * dot * dot / magnitude_product - 1.0f, -1.0f, 1.0f);
		angle_radians = arccosine(cos_angle) * 0.5f;
		if (dot < 0.0f)
			return 3.14159265f - angle_radians;
	}
	return angle_radians;
}

float signed_angle_between_vectors2d(real_vector2d const *v1, real_vector2d const *v2) // 0x10EFB890
{
	float angle_radians = arccosine(real_pin(dot_product2d(v1, v2), -1.0f, 1.0f));

	if (cross_product2d(v1, v2) < 0.0f)
	{
		return -angle_radians;
	}

	return angle_radians;
}

real_point2d *point_from_line2d(real_point2d const *origin, real_vector2d const *vector, float t, real_point2d *result) // 0x10EFA740
{
	result->x = vector->i * t + origin->x;
	result->y = vector->j * t + origin->y;

	return result;
}

real_point2d *set_real_point2d(real_point2d *point, float x, float y) // 0x10EFB6B0
{
	point->x = x;
	point->y = y;

	return point;
}

float magnitude2d_squared(real_vector2d const *v) // 0x10EF9F80
{
	return v->i * v->i + v->j * v->j;
}

float magnitude2d(real_vector2d const *v) // 0x10EF9F20
{
	return square_root(magnitude2d_squared(v));
}

float normalize2d(real_vector2d *v) // 0x10EFA230
{
	float m = magnitude2d(v);
	if (m < 0.0000099999997f)
	{
		return 0.0f;
	}
	else
	{
		scale_vector2d(v, 1.0f / m, v);
	}

	return m;
}

float dot_product2d(real_vector2d const *v1, real_vector2d const *v2) // 0x10EF9B60
{
	return v1->i * v2->i + v1->j * v2->j;
}

float cross_product2d(real_vector2d const *v1, real_vector2d const *v2) // 0x10EF98B0
{
	return v1->i * v2->j - v1->j * v2->i;
}

long rectangle3d_build_vertices(real_rectangle3d const &bounds, long maximum_vertex_count, real_point3d (&vertices)[8]) // 0x10EFB080
{
	vertices->x = bounds.x0;
	vertices->y = bounds.y0;
	vertices->z = bounds.z0;
	vertices[1].x = bounds.x1;
	vertices[1].y = bounds.y0;
	vertices[1].z = bounds.z0;
	vertices[2].x = bounds.x0;
	vertices[2].y = bounds.y1;
	vertices[2].z = bounds.z0;
	vertices[3].x = bounds.x1;
	vertices[3].y = bounds.y1;
	vertices[3].z = bounds.z0;
	vertices[4].x = bounds.x0;
	vertices[4].y = bounds.y0;
	vertices[4].z = bounds.z1;
	vertices[5].x = bounds.x1;
	vertices[5].y = bounds.y0;
	vertices[5].z = bounds.z1;
	vertices[6].x = bounds.x0;
	vertices[6].y = bounds.y1;
	vertices[6].z = bounds.z1;
	vertices[7].x = bounds.x1;
	vertices[7].y = bounds.y1;
	vertices[7].z = bounds.z1;
	return 8;
}

long rectangle3d_build_edges(real_rectangle3d const &bounds, long maximum_edge_count, real_point3d (*const edges)[2]) // 0x10EFAA50
{
	real_point3d vertices[8];
	rectangle3d_build_vertices(bounds, 8, vertices);
	long const line_vertex_indices[12][2] = { { 0, 2 }, { 2, 3 }, { 3, 1 }, { 1, 0 }, { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }, { 4, 5 }, { 5, 7 }, { 7, 6 }, { 6, 4 } };
	for (long edge_index = 0; edge_index < 12; edge_index++)
	{
		edges[edge_index][0] = vertices[line_vertex_indices[edge_index][0]];
		edges[edge_index][1] = vertices[line_vertex_indices[edge_index][1]];
	}
	return 12;
}

void rectangle3d_build_faces(real_rectangle3d const &bounds, real_point3d (*const faces)[4]) // 0x10EFAD30
{
	long const face_vertex_indices[6][4] = { { 0, 2, 3, 1 }, { 0, 1, 5, 4 }, { 1, 3, 7, 5 }, { 2, 6, 7, 3 }, { 0, 4, 6, 2 }, { 4, 5, 7, 6 } };
	real_point3d vertices[8];
	rectangle3d_build_vertices(bounds, 8, vertices);
	for (long i = 0, j = 0; i < 6; i++)
	{
		faces[i][0] = vertices[face_vertex_indices[i][0]];
		faces[i][1] = vertices[face_vertex_indices[i][1]];
		faces[i][2] = vertices[face_vertex_indices[i][2]];
		faces[i][3] = vertices[face_vertex_indices[i][3]];
	}
}

/* ---------- private code */
