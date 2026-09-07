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

_extern float _sub_10EFA880(float, float, float);
float real_pin(float x, float min, float max) // 0x10EFA880
{
	mangled_x86(MANGLED_TODO, "?real_pin@@YAMMMM@Z");
	// float max;
	todo("implement");
	float __result = _sub_10EFA880(x, min, max);
	return __result;
}

_extern float _sub_10EFA940(float);
float real_pin_0_1(float x) // 0x10EFA940
{
	mangled_x86(MANGLED_TODO, "?real_pin_0_1@@YAMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EFA940(x);
	return __result;
}

_extern float _sub_10EFB9E0(float);
float square_root(float x) // 0x10EFB9E0
{
	mangled_x86(MANGLED_TODO, "?square_root@@YAMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EFB9E0(x);
	return __result;
}

_extern float _sub_10EFA9C0(float);
float reciprocal_square_root(float x) // 0x10EFA9C0
{
	mangled_x86(MANGLED_TODO, "?reciprocal_square_root@@YAMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EFA9C0(x);
	return __result;
}

_extern float _sub_10EF9850(float);
float cosine(float x) // 0x10EF9850
{
	mangled_x86(MANGLED_TODO, "?cosine@@YAMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EF9850(x);
	return __result;
}

_extern float _sub_10EFB980(float);
float sine(float x) // 0x10EFB980
{
	mangled_x86(MANGLED_TODO, "?sine@@YAMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EFB980(x);
	return __result;
}

_extern float _sub_10EFBB60(float);
float tangent(float x) // 0x10EFBB60
{
	mangled_x86(MANGLED_TODO, "?tangent@@YAMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EFBB60(x);
	return __result;
}

_extern float _sub_10EF9780(float);
float arcsine(float x) // 0x10EF9780
{
	mangled_x86(MANGLED_TODO, "?arcsine@@YAMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EF9780(x);
	return __result;
}

_extern float _sub_10EF9720(float);
float arccosine(float x) // 0x10EF9720
{
	mangled_x86(MANGLED_TODO, "?arccosine@@YAMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EF9720(x);
	return __result;
}

_extern float _sub_10EF97E0(float, float);
float arctangent(float y, float x) // 0x10EF97E0
{
	mangled_x86(MANGLED_TODO, "?arctangent@@YAMMM@Z");
	// float x;
	todo("implement");
	float __result = _sub_10EF97E0(y, x);
	return __result;
}

_extern float _sub_10EFA2E0(real_vector3d *);
float normalize3d(real_vector3d *v) // 0x10EFA2E0
{
	mangled_x86(MANGLED_TODO, "?normalize3d@@YAMPAUreal_vector3d@@@Z");
	// real_vector3d *v;
	// float m;
	todo("implement");
	float __result = _sub_10EFA2E0(v);
	return __result;
}

_extern float _sub_10EFA070(real_vector3d const *);
float magnitude_squared3d(real_vector3d const *v) // 0x10EFA070
{
	mangled_x86(MANGLED_TODO, "?magnitude_squared3d@@YAMPBUreal_vector3d@@@Z");
	// real_vector3d const *v;
	todo("implement");
	float __result = _sub_10EFA070(v);
	return __result;
}

_extern float _sub_10EFA010(real_vector3d const *);
float magnitude3d(real_vector3d const *v) // 0x10EFA010
{
	mangled_x86(MANGLED_TODO, "?magnitude3d@@YAMPBUreal_vector3d@@@Z");
	// real_vector3d const *v;
	todo("implement");
	float __result = _sub_10EFA010(v);
	return __result;
}

_extern float _sub_10EF9AA0(real_point3d const *, real_point3d const *);
float distance_squared3d(real_point3d const *p1, real_point3d const *p2) // 0x10EF9AA0
{
	mangled_x86(MANGLED_TODO, "?distance_squared3d@@YAMPBUreal_point3d@@0@Z");
	// static ...; // 0x10EF9B28
	// static ...; // 0x10EF9B20
	// real_point3d const *p1;
	// real_point3d const *p2;
	// real_vector3d v;
	todo("implement");
	float __result = _sub_10EF9AA0(p1, p2);
	return __result;
}

_extern float _sub_10EF9A30(real_point3d const *, real_point3d const *);
float distance3d(real_point3d const *p1, real_point3d const *p2) // 0x10EF9A30
{
	mangled_x86(MANGLED_TODO, "?distance3d@@YAMPBUreal_point3d@@0@Z");
	// real_point3d const *p2;
	todo("implement");
	float __result = _sub_10EF9A30(p1, p2);
	return __result;
}

_extern float _sub_10EF9BF0(real_vector3d const *, real_vector3d const *);
float dot_product3d(real_vector3d const *v1, real_vector3d const *v2) // 0x10EF9BF0
{
	mangled_x86(MANGLED_TODO, "?dot_product3d@@YAMPBUreal_vector3d@@0@Z");
	// real_vector3d const *v2;
	todo("implement");
	float __result = _sub_10EF9BF0(v1, v2);
	return __result;
}

extern real_vector3d *_sub_10EF9940(real_vector3d const *, real_vector3d const *, real_vector3d *);
real_vector3d *cross_product3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result) // 0x10EF9940
{
	mangled_x86(MANGLED_TODO, "?cross_product3d@@YAPAUreal_vector3d@@PBU1@0PAU1@@Z");
	// real_vector3d *result;
	todo("implement");
	real_vector3d * __result = _sub_10EF9940(v1, v2, result);
	return __result;
}

extern real_vector3d *_sub_10EFA390(real_vector3d const *, real_vector3d *);
real_vector3d *perpendicular3d(real_vector3d const *v, real_vector3d *result) // 0x10EFA390
{
	mangled_x86(MANGLED_TODO, "?perpendicular3d@@YAPAUreal_vector3d@@PBU1@PAU1@@Z");
	// real_vector3d *result;
	// float abs_i;
	// float abs_k;
	// float abs_j;
	todo("implement");
	real_vector3d * __result = _sub_10EFA390(v, result);
	return __result;
}

extern real_vector3d *_sub_10EFB810(real_vector3d *, float, float, float);
real_vector3d *set_real_vector3d(real_vector3d *result, float i, float j, float k) // 0x10EFB810
{
	mangled_x86(MANGLED_TODO, "?set_real_vector3d@@YAPAUreal_vector3d@@PAU1@MMM@Z");
	// float k;
	todo("implement");
	real_vector3d * __result = _sub_10EFB810(result, i, j, k);
	return __result;
}

extern real_vector3d *_sub_10EF9280(real_vector3d const *, real_vector3d const *, real_vector3d *);
real_vector3d *add_vectors3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result) // 0x10EF9280
{
	mangled_x86(MANGLED_TODO, "?add_vectors3d@@YAPAUreal_vector3d@@PBU1@0PAU1@@Z");
	// real_vector3d *result;
	todo("implement");
	real_vector3d * __result = _sub_10EF9280(v1, v2, result);
	return __result;
}

extern real_vector3d *_sub_10EFBAC0(real_vector3d const *, real_vector3d const *, real_vector3d *);
real_vector3d *subtract_vectors3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result) // 0x10EFBAC0
{
	mangled_x86(MANGLED_TODO, "?subtract_vectors3d@@YAPAUreal_vector3d@@PBU1@0PAU1@@Z");
	// real_vector3d *result;
	todo("implement");
	real_vector3d * __result = _sub_10EFBAC0(v1, v2, result);
	return __result;
}

extern real_vector3d *_sub_10EFB610(real_vector3d const *, float, real_vector3d *);
real_vector3d *scale_vector3d(real_vector3d const *v1, float scale, real_vector3d *result) // 0x10EFB610
{
	mangled_x86(MANGLED_TODO, "?scale_vector3d@@YAPAUreal_vector3d@@PBU1@MPAU1@@Z");
	// real_vector3d *result;
	todo("implement");
	real_vector3d * __result = _sub_10EFB610(v1, scale, result);
	return __result;
}

extern real_vector3d *_sub_10EFA190(real_vector3d const *, real_vector3d *);
real_vector3d *negate_vector3d(real_vector3d const *v, real_vector3d *result) // 0x10EFA190
{
	mangled_x86(MANGLED_TODO, "?negate_vector3d@@YAPAUreal_vector3d@@PBU1@PAU1@@Z");
	// real_vector3d *result;
	todo("implement");
	real_vector3d * __result = _sub_10EFA190(v, result);
	return __result;
}

extern real_vector3d *_sub_10EFBD50(real_point3d const *, real_point3d const *, real_vector3d *);
real_vector3d *vector_from_points3d(real_point3d const *p1, real_point3d const *p2, real_vector3d *result) // 0x10EFBD50
{
	mangled_x86(MANGLED_TODO, "?vector_from_points3d@@YAPAUreal_vector3d@@PBUreal_point3d@@0PAU1@@Z");
	// real_vector3d *result;
	todo("implement");
	real_vector3d * __result = _sub_10EFBD50(p1, p2, result);
	return __result;
}

extern real_vector3d *_sub_10EF9DE0(real_vector3d const *, real_vector3d *);
real_vector3d *generate_up_vector3d(real_vector3d const *forward, real_vector3d *up) // 0x10EF9DE0
{
	mangled_x86(MANGLED_TODO, "?generate_up_vector3d@@YAPAUreal_vector3d@@PBU1@PAU1@@Z");
	// static ...; // 0x10EF9EC4
	// static ...; // 0x10EF9EBC
	// real_vector3d const *forward;
	// real_vector3d *up;
	// real_vector3d orth;
	todo("implement");
	real_vector3d * __result = _sub_10EF9DE0(forward, up);
	return __result;
}

extern real_vector3d *_sub_10EFBBC0(real_vector3d *, real_euler_angles2d const *);
real_vector3d *vector3d_from_euler_angles2d(real_vector3d *result, real_euler_angles2d const *angles) // 0x10EFBBC0
{
	mangled_x86(MANGLED_TODO, "?vector3d_from_euler_angles2d@@YAPAUreal_vector3d@@PAU1@PBUreal_euler_angles2d@@@Z");
	// real_euler_angles2d const *angles;
	// float cos_pitch;
	todo("implement");
	real_vector3d * __result = _sub_10EFBBC0(result, angles);
	return __result;
}

extern real_euler_angles3d *_sub_10EF9C90(real_euler_angles3d *, real_vector3d const *, real_vector3d const *);
real_euler_angles3d *euler_angles3d_from_vectors3d(real_euler_angles3d *angles, real_vector3d const *forward, real_vector3d const *up) // 0x10EF9C90
{
	mangled_x86(MANGLED_TODO, "?euler_angles3d_from_vectors3d@@YAPAUreal_euler_angles3d@@PAU1@PBUreal_vector3d@@1@Z");
	// static ...; // 0x10EF9D80
	// real_euler_angles3d *angles;
	// real_vector3d const *forward;
	// real_vector3d const *up;
	// real_matrix4x3 matrix;
	todo("implement");
	real_euler_angles3d * __result = _sub_10EF9C90(angles, forward, up);
	return __result;
}

extern real_vector3d *_sub_10EFBDF0(float, float, real_vector3d *);
real_vector3d *vector_from_yaw_and_pitch(float yaw, float pitch, real_vector3d *result) // 0x10EFBDF0
{
	mangled_x86(MANGLED_TODO, "?vector_from_yaw_and_pitch@@YAPAUreal_vector3d@@MMPAU1@@Z");
	// real_vector3d *result;
	todo("implement");
	real_vector3d * __result = _sub_10EFBDF0(yaw, pitch, result);
	return __result;
}

extern real_point3d *_sub_10EFA7D0(real_point3d const *, real_vector3d const *, float, real_point3d *);
real_point3d *point_from_line3d(real_point3d const *origin, real_vector3d const *vector, float t, real_point3d *result) // 0x10EFA7D0
{
	mangled_x86(MANGLED_TODO, "?point_from_line3d@@YAPAUreal_point3d@@PBU1@PBUreal_vector3d@@MPAU1@@Z");
	// real_point3d *result;
	todo("implement");
	real_point3d * __result = _sub_10EFA7D0(origin, vector, t, result);
	return __result;
}

extern real_point3d *_sub_10EFB720(real_point3d *, float, float, float);
real_point3d *set_real_point3d(real_point3d *point, float x, float y, float z) // 0x10EFB720
{
	mangled_x86(MANGLED_TODO, "?set_real_point3d@@YAPAUreal_point3d@@PAU1@MMM@Z");
	// float z;
	todo("implement");
	real_point3d * __result = _sub_10EFB720(point, x, y, z);
	return __result;
}

extern real_vector3d *_sub_10EFC050(real_vector3d const *, real_vector3d const *, float, real_vector3d *);
real_vector3d *vectors_interpolate(real_vector3d const *v1, real_vector3d const *v2, float t, real_vector3d *result) // 0x10EFC050
{
	mangled_x86(MANGLED_TODO, "?vectors_interpolate@@YAPAUreal_vector3d@@PBU1@0MPAU1@@Z");
	// real_vector3d *result;
	todo("implement");
	real_vector3d * __result = _sub_10EFC050(v1, v2, t, result);
	return __result;
}

_extern float _sub_10EF9320(real_vector3d const *, real_vector3d const *);
float angle_between_normalized_vectors3d(real_vector3d const *v1, real_vector3d const *v2) // 0x10EF9320
{
	mangled_x86(MANGLED_TODO, "?angle_between_normalized_vectors3d@@YAMPBUreal_vector3d@@0@Z");
	// real_vector3d const *v2;
	todo("implement");
	float __result = _sub_10EF9320(v1, v2);
	return __result;
}

_extern float _sub_10EF9570(real_vector3d const *, real_vector3d const *);
float angle_between_vectors3d(real_vector3d const *v1, real_vector3d const *v2) // 0x10EF9570
{
	mangled_x86(MANGLED_TODO, "?angle_between_vectors3d@@YAMPBUreal_vector3d@@0@Z");
	// real_vector3d const *v2;
	// float magnitude_product;
	// float angle_radians;
	{
		// float dot;
		// float cos_angle;
	}
	todo("implement");
	float __result = _sub_10EF9570(v1, v2);
	return __result;
}

extern real_vector3d *_sub_10EFB3C0(real_vector3d *, real_vector3d const *, float, float);
real_vector3d *rotate_vector_about_axis(real_vector3d *vector, real_vector3d const *axis, float sin_theta, float cos_theta) // 0x10EFB3C0
{
	mangled_x86(MANGLED_TODO, "?rotate_vector_about_axis@@YAPAUreal_vector3d@@PAU1@PBU1@MM@Z");
	// float cos_theta;
	// float one_minus_cos;
	todo("implement");
	real_vector3d * __result = _sub_10EFB3C0(vector, axis, sin_theta, cos_theta);
	return __result;
}

extern real_plane3d *_sub_10EFA640(real_plane3d *, real_point3d const *, real_vector3d const *);
real_plane3d *plane3d_from_point_and_normal(real_plane3d *plane, real_point3d const *point, real_vector3d const *normal) // 0x10EFA640
{
	mangled_x86(MANGLED_TODO, "?plane3d_from_point_and_normal@@YAPAUreal_plane3d@@PAU1@PBUreal_point3d@@PBUreal_vector3d@@@Z");
	// real_vector3d const *normal;
	todo("implement");
	real_plane3d * __result = _sub_10EFA640(plane, point, normal);
	return __result;
}

extern real_plane3d *_sub_10EFA6C0(real_plane3d const *, real_plane3d *);
real_plane3d *plane3d_negate(real_plane3d const *plane, real_plane3d *result) // 0x10EFA6C0
{
	mangled_x86(MANGLED_TODO, "?plane3d_negate@@YAPAUreal_plane3d@@PBU1@PAU1@@Z");
	// real_plane3d *result;
	todo("implement");
	real_plane3d * __result = _sub_10EFA6C0(plane, result);
	return __result;
}

_extern float _sub_10EFA590(real_plane3d const *, real_point3d const *);
float plane3d_distance_to_point(real_plane3d const *plane, real_point3d const *point) // 0x10EFA590
{
	mangled_x86(MANGLED_TODO, "?plane3d_distance_to_point@@YAMPBUreal_plane3d@@PBUreal_point3d@@@Z");
	// real_point3d const *point;
	todo("implement");
	float __result = _sub_10EFA590(plane, point);
	return __result;
}

_extern void _sub_10EFBF40(real_vector3d *, real_vector3d *, real_euler_angles3d const *);
void vectors3d_from_euler_angles3d(real_vector3d *forward, real_vector3d *up, real_euler_angles3d const *angles) // 0x10EFBF40
{
	mangled_x86(MANGLED_TODO, "?vectors3d_from_euler_angles3d@@YAXPAUreal_vector3d@@0PBUreal_euler_angles3d@@@Z");
	// static ...; // 0x10EFBFF4
	// static ...; // 0x10EFBFEC
	// real_vector3d *forward;
	// real_vector3d *up;
	// real_euler_angles3d const *angles;
	// real_matrix4x3 matrix;
	// real_point3d point;
	todo("implement");
	_sub_10EFBF40(forward, up, angles);
}

extern real_vector2d *_sub_10EFB590(real_vector2d const *, float, real_vector2d *);
real_vector2d *scale_vector2d(real_vector2d const *v, float scale, real_vector2d *result) // 0x10EFB590
{
	mangled_x86(MANGLED_TODO, "?scale_vector2d@@YAPAUreal_vector2d@@PBU1@MPAU1@@Z");
	// real_vector2d *result;
	todo("implement");
	real_vector2d * __result = _sub_10EFB590(v, scale, result);
	return __result;
}

extern real_vector2d *_sub_10EFA110(real_vector2d const *, real_vector2d *);
real_vector2d *negate_vector2d(real_vector2d const *v, real_vector2d *result) // 0x10EFA110
{
	mangled_x86(MANGLED_TODO, "?negate_vector2d@@YAPAUreal_vector2d@@PBU1@PAU1@@Z");
	// real_vector2d *result;
	todo("implement");
	real_vector2d * __result = _sub_10EFA110(v, result);
	return __result;
}

extern real_vector2d *_sub_10EF9200(real_vector2d const *, real_vector2d const *, real_vector2d *);
real_vector2d *add_vectors2d(real_vector2d const *v1, real_vector2d const *v2, real_vector2d *result) // 0x10EF9200
{
	mangled_x86(MANGLED_TODO, "?add_vectors2d@@YAPAUreal_vector2d@@PBU1@0PAU1@@Z");
	// real_vector2d *result;
	todo("implement");
	real_vector2d * __result = _sub_10EF9200(v1, v2, result);
	return __result;
}

extern real_vector2d *_sub_10EFB7A0(real_vector2d *, float, float);
real_vector2d *set_real_vector2d(real_vector2d *result, float i, float j) // 0x10EFB7A0
{
	mangled_x86(MANGLED_TODO, "?set_real_vector2d@@YAPAUreal_vector2d@@PAU1@MM@Z");
	// float j;
	todo("implement");
	real_vector2d * __result = _sub_10EFB7A0(result, i, j);
	return __result;
}

extern real_vector2d *_sub_10EFBA40(real_vector2d const *, real_vector2d const *, real_vector2d *);
real_vector2d *subract_vectors2d(real_vector2d const *v1, real_vector2d const *v2, real_vector2d *result) // 0x10EFBA40
{
	mangled_x86(MANGLED_TODO, "?subract_vectors2d@@YAPAUreal_vector2d@@PBU1@0PAU1@@Z");
	// real_vector2d *result;
	todo("implement");
	real_vector2d * __result = _sub_10EFBA40(v1, v2, result);
	return __result;
}

extern real_vector2d *_sub_10EFB310(real_vector2d const *, float, float, real_vector2d *);
real_vector2d *rotate_vector2d(real_vector2d const *v, float sin_y, float cos_x, real_vector2d *result) // 0x10EFB310
{
	mangled_x86(MANGLED_TODO, "?rotate_vector2d@@YAPAUreal_vector2d@@PBU1@MMPAU1@@Z");
	// real_vector2d *result;
	todo("implement");
	real_vector2d * __result = _sub_10EFB310(v, sin_y, cos_x, result);
	return __result;
}

extern real_vector2d *_sub_10EFBCD0(real_point2d const *, real_point2d const *, real_vector2d *);
real_vector2d *vector_from_points2d(real_point2d const *p1, real_point2d const *p2, real_vector2d *result) // 0x10EFBCD0
{
	mangled_x86(MANGLED_TODO, "?vector_from_points2d@@YAPAUreal_vector2d@@PBUreal_point2d@@0PAU1@@Z");
	// real_vector2d *result;
	todo("implement");
	real_vector2d * __result = _sub_10EFBCD0(p1, p2, result);
	return __result;
}

_extern float _sub_10EF93C0(real_vector2d const *, real_vector2d const *);
float angle_between_vectors2d(real_vector2d const *v1, real_vector2d const *v2) // 0x10EF93C0
{
	mangled_x86(MANGLED_TODO, "?angle_between_vectors2d@@YAMPBUreal_vector2d@@0@Z");
	// real_vector2d const *v2;
	// float magnitude_product;
	// float angle_radians;
	{
		// float dot;
		// float cos_angle;
	}
	todo("implement");
	float __result = _sub_10EF93C0(v1, v2);
	return __result;
}

_extern float _sub_10EFB890(real_vector2d const *, real_vector2d const *);
float signed_angle_between_vectors2d(real_vector2d const *v1, real_vector2d const *v2) // 0x10EFB890
{
	mangled_x86(MANGLED_TODO, "?signed_angle_between_vectors2d@@YAMPBUreal_vector2d@@0@Z");
	// real_vector2d const *v2;
	// float angle_radians;
	todo("implement");
	float __result = _sub_10EFB890(v1, v2);
	return __result;
}

extern real_point2d *_sub_10EFA740(real_point2d const *, real_vector2d const *, float, real_point2d *);
real_point2d *point_from_line2d(real_point2d const *origin, real_vector2d const *vector, float t, real_point2d *result) // 0x10EFA740
{
	mangled_x86(MANGLED_TODO, "?point_from_line2d@@YAPAUreal_point2d@@PBU1@PBUreal_vector2d@@MPAU1@@Z");
	// real_point2d *result;
	todo("implement");
	real_point2d * __result = _sub_10EFA740(origin, vector, t, result);
	return __result;
}

extern real_point2d *_sub_10EFB6B0(real_point2d *, float, float);
real_point2d *set_real_point2d(real_point2d *point, float x, float y) // 0x10EFB6B0
{
	mangled_x86(MANGLED_TODO, "?set_real_point2d@@YAPAUreal_point2d@@PAU1@MM@Z");
	// float y;
	todo("implement");
	real_point2d * __result = _sub_10EFB6B0(point, x, y);
	return __result;
}

_extern float _sub_10EF9F80(real_vector2d const *);
float magnitude2d_squared(real_vector2d const *v) // 0x10EF9F80
{
	mangled_x86(MANGLED_TODO, "?magnitude2d_squared@@YAMPBUreal_vector2d@@@Z");
	// real_vector2d const *v;
	todo("implement");
	float __result = _sub_10EF9F80(v);
	return __result;
}

_extern float _sub_10EF9F20(real_vector2d const *);
float magnitude2d(real_vector2d const *v) // 0x10EF9F20
{
	mangled_x86(MANGLED_TODO, "?magnitude2d@@YAMPBUreal_vector2d@@@Z");
	// real_vector2d const *v;
	todo("implement");
	float __result = _sub_10EF9F20(v);
	return __result;
}

_extern float _sub_10EFA230(real_vector2d *);
float normalize2d(real_vector2d *v) // 0x10EFA230
{
	mangled_x86(MANGLED_TODO, "?normalize2d@@YAMPAUreal_vector2d@@@Z");
	// real_vector2d *v;
	// float m;
	todo("implement");
	float __result = _sub_10EFA230(v);
	return __result;
}

_extern float _sub_10EF9B60(real_vector2d const *, real_vector2d const *);
float dot_product2d(real_vector2d const *v1, real_vector2d const *v2) // 0x10EF9B60
{
	mangled_x86(MANGLED_TODO, "?dot_product2d@@YAMPBUreal_vector2d@@0@Z");
	// real_vector2d const *v2;
	todo("implement");
	float __result = _sub_10EF9B60(v1, v2);
	return __result;
}

_extern float _sub_10EF98B0(real_vector2d const *, real_vector2d const *);
float cross_product2d(real_vector2d const *v1, real_vector2d const *v2) // 0x10EF98B0
{
	mangled_x86(MANGLED_TODO, "?cross_product2d@@YAMPBUreal_vector2d@@0@Z");
	// real_vector2d const *v2;
	todo("implement");
	float __result = _sub_10EF98B0(v1, v2);
	return __result;
}

_extern long _sub_10EFB080(real_rectangle3d const &, long, real_point3d (&)[8]);
long rectangle3d_build_vertices(real_rectangle3d const &bounds, long maximum_vertex_count, real_point3d (&vertices)[8]) // 0x10EFB080
{
	mangled_x86(MANGLED_TODO, "?rectangle3d_build_vertices@@YAJABUreal_rectangle3d@@JAAY07Ureal_point3d@@@Z");
	// real_point3d (&vertices)[8];
	todo("implement");
	long __result = _sub_10EFB080(bounds, maximum_vertex_count, vertices);
	return __result;
}

_extern long _sub_10EFAA50(real_rectangle3d const &,  long, real_point3d (*const edges)[2]);
long rectangle3d_build_edges(real_rectangle3d const &bounds, long maximum_edge_count, real_point3d (*const edges)[2]) // 0x10EFAA50
{
	mangled_x86(MANGLED_TODO, "?rectangle3d_build_edges@@YAJABUreal_rectangle3d@@JQAY01Ureal_point3d@@@Z");
	// static ...; // 0x10EFAC64
	// static ...; // 0x10EFAC5C
	// real_rectangle3d const &bounds;
	// long maximum_edge_count;
	// real_point3d *const edges[2];
	// real_point3d vertices[8];
	// long const line_vertex_indices[12][2];
	{
		// long edge_index;
	}
	todo("implement");
	long __result = _sub_10EFAA50(bounds, maximum_edge_count, edges);
	return __result;
}

_extern void _sub_10EFAD30(real_rectangle3d const &, real_point3d (*const faces)[4]);
void rectangle3d_build_faces(real_rectangle3d const &bounds, real_point3d (*const faces)[4]) // 0x10EFAD30
{
	mangled_x86(MANGLED_TODO, "?rectangle3d_build_faces@@YAXABUreal_rectangle3d@@QAY03Ureal_point3d@@@Z");
	// static ...; // 0x10EFAFB4
	// static ...; // 0x10EFAF9C
	// static ...; // 0x10EFAF94
	// real_rectangle3d const &bounds;
	// real_point3d *const faces[4];
	// real_point3d vertices[8];
	// long const face_vertex_indices[6][4];
	{
		// long i;
		// long j;
	}
	todo("implement");
	_sub_10EFAD30(bounds, faces);
}

/* ---------- private code */
