#ifndef __BLAM_MATH_REAL_MATH_DEFINITIONS_HPP__
#define __BLAM_MATH_REAL_MATH_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct real_bounds;
struct real_euler_angles2d;
struct real_euler_angles3d;
struct real_matrix3x3;
struct real_matrix4x3;
struct real_matrix4x4;
struct real_plane2d;
struct real_plane3d;
struct real_point2d;
struct real_quaternion;
struct real_rectangle2d;
struct real_rectangle3d;
struct real_vector2d;
struct real_vector3d;
struct real_vector4d;

/* ---------- constants */

/* ---------- definitions */

struct real_vector3d
{
	float i; // 0x0
	float j; // 0x4
	float k; // 0x8
};
static_assert(sizeof(real_vector3d) == 12, "Invalid real_vector3d size");

struct real_vector4d
{
	float i; // 0x0
	float j; // 0x4
	float k; // 0x8
	float w; // 0xC
	float operator[](long) const;
	_inline float &operator[](long index);
};
static_assert(sizeof(real_vector4d) == 16, "Invalid real_vector4d size");

struct real_point2d
{
	float x; // 0x0
	float y; // 0x4
};
static_assert(sizeof(real_point2d) == 8, "Invalid real_point2d size");

struct real_vector2d
{
	float i; // 0x0
	float j; // 0x4
};
static_assert(sizeof(real_vector2d) == 8, "Invalid real_vector2d size");

#pragma pack(push, 4)
struct real_matrix4x3
{
	float scale; // 0x0
	real_vector3d forward; // 0x4
	real_vector3d left; // 0x10
	real_vector3d up; // 0x1C
	real_point3d position; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(real_matrix4x3) == 52, "Invalid real_matrix4x3 size");

struct real_matrix4x4
{
	real_vector4d forward; // 0x0
	real_vector4d left; // 0x10
	real_vector4d up; // 0x20
	real_vector4d position; // 0x30
	real_matrix4x4 transpose();
	static void mul(real_vector4d *, real_matrix4x4 *);
};
static_assert(sizeof(real_matrix4x4) == 64, "Invalid real_matrix4x4 size");

#pragma pack(push, 4)
struct real_matrix3x3
{
	real_vector3d forward; // 0x0
	real_vector3d left; // 0xC
	real_vector3d up; // 0x18
};
#pragma pack(pop)
static_assert(sizeof(real_matrix3x3) == 36, "Invalid real_matrix3x3 size");

struct real_plane2d
{
	float i; // 0x0
	float j; // 0x4
	float d; // 0x8
};
static_assert(sizeof(real_plane2d) == 12, "Invalid real_plane2d size");

struct real_plane3d
{
	real_vector3d normal; // 0x0
	float d; // 0xC
};
static_assert(sizeof(real_plane3d) == 16, "Invalid real_plane3d size");

struct real_euler_angles2d
{
	float yaw; // 0x0
	float pitch; // 0x4
};
static_assert(sizeof(real_euler_angles2d) == 8, "Invalid real_euler_angles2d size");

struct real_euler_angles3d
{
	float yaw; // 0x0
	float pitch; // 0x4
	float roll; // 0x8
};
static_assert(sizeof(real_euler_angles3d) == 12, "Invalid real_euler_angles3d size");

struct real_quaternion
{
	union
	{
		struct
		{
			float i; // 0x0
			float j; // 0x4
			float k; // 0x8
		};
		real_vector3d v; // 0x0
	};
	float w; // 0xC
};
static_assert(sizeof(real_quaternion) == 16, "Invalid real_quaternion size");

struct real_bounds
{
	float lower; // 0x0
	float upper; // 0x4
};
static_assert(sizeof(real_bounds) == 8, "Invalid real_bounds size");

struct real_rectangle3d
{
	float x0; // 0x0
	float x1; // 0x4
	float y0; // 0x8
	float y1; // 0xC
	float z0; // 0x10
	float z1; // 0x14
};
static_assert(sizeof(real_rectangle3d) == 24, "Invalid real_rectangle3d size");

struct real_rectangle2d
{
	float x0; // 0x0
	float x1; // 0x4
	float y0; // 0x8
	float y1; // 0xC
};
static_assert(sizeof(real_rectangle2d) == 16, "Invalid real_rectangle2d size");

/* ---------- prototypes */

/* ---------- globals */

// Namespace-scope constants, so each translation unit gets its own copy - which
// is what the PDB shows: 254 distinct addresses for global_origin3d, one per file
// that includes this header. Values read from .rdata.
real_point3d const global_origin3d = { 0.0f, 0.0f, 0.0f };
real_vector3d const global_forward3d = { 1.0f, 0.0f, 0.0f };
real_vector3d const global_left3d = { 0.0f, 1.0f, 0.0f };
real_vector3d const global_up3d = { 0.0f, 0.0f, 1.0f };

// Lives in .data and is filled by a dynamic initialiser, so the binary holds no
// usable value for it.
extern real_matrix4x3 const global_identity4x3;

/* ---------- public code */

_extern float &_sub_108E3DF0(real_vector4d *const, long);
_inline float &real_vector4d::operator[](long index) // 0x108E3DF0
{
	mangled_x86(MANGLED_TODO, "??Areal_vector4d@@QAEAAMJ@Z");
	// long index;
	todo("implement");
	float & __result = _sub_108E3DF0(this, index);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_MATH_REAL_MATH_DEFINITIONS_HPP__
