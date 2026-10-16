/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/physics/havok_utilities.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Blam/rasterizer/rasterizer_primitives.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizer_vertex_types.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeUndo.hpp"

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

struct c_font_cache_mt_safe;
struct c_player_view;
struct c_rasterizer_draw_string;
struct hkShapeContainer;
struct hkTransform;
struct hkVector4;
struct hkpBoxShape;
struct hkpBvShape;
struct hkpCapsuleShape;
struct hkpConvexTransformShape;
struct hkpConvexTranslateShape;
struct hkpConvexVerticesShape;
struct hkpListShape;
struct hkpShape;
struct hkpTriangleShape;
struct real_argb_color;
struct real_matrix4x3;
struct real_plane3d;
struct real_point2d;
struct real_point3d;
struct real_rectangle3d;
struct real_vector3d;
struct s_debug_vertex;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const real_argb_color_to_pixel32 = reinterpret_cast<unsigned long (*)(real_argb_color const &)>(0x521810);
}

real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x10F08A60

bool render_camera_world_to_window(s_render_camera const *camera, s_render_projection const *projection, short_rectangle2d const *window_display_bounds, real_point3d const *world_point, real_point2d *screen_point);  // hades: added for 0x10F0B960
#include "Blam/render/views/render_view.hpp"  // hades: added for 0x10F0B960

__declspec(safebuffers) void render_debug_vector(real_point3d const &point, real_vector3d const &vector, real_argb_color const &color);  // hades: added for 0X10F0BDD0

extern void rectangle3d_build_faces(real_rectangle3d const &bounds, real_point3d (*const faces)[4]);  // hades: added for 0x10F086C0
extern long rectangle3d_build_edges(real_rectangle3d const &bounds, long maximum_edge_count, real_point3d (*const edges)[2]);  // hades: added for 0x10F086C0

float dot_product3d(real_vector3d const *a, real_vector3d const *b);  // hades: added for 0X10F0BEC0
float plane3d_distance_to_point(real_plane3d const *plane, real_point3d const *point);  // hades: added for 0X10F0BEC0

void render_debug_triangle(real_point3d const &point0, real_point3d const &point1, real_point3d const &point2, real_argb_color const &color);  // hades: added for 0X10F0B1B0

extern void render_debug_enable_depth_test(bool enable);
extern void render_debug_build_circle_points(float radius, real_point2d *points, long total_point_count);
extern float build_height_matrix(real_point3d const *base, real_vector3d const *height, real_matrix4x3 *matrix);
extern void render_debug_build_pill_points(real_point3d const *base, real_vector3d const *height, float radius, real_point3d *p1, real_point3d *p2, real_point3d *p3, real_point3d *p4, real_point3d *p5, real_point3d *p6);
extern void render_debug_sphere(real_point3d const &center, float radius, real_argb_color const &color);
extern void render_debug_triangle(real_point3d const &point1, real_point3d const &point2, real_point3d const &point3, real_argb_color const &color);
extern void render_debug_line(real_point3d const &point0, real_point3d const &point1, real_argb_color const &color);
extern void render_debug_quadrilateral(real_point3d const &point0, real_point3d const &point1, real_point3d const &point2, real_point3d const &point3, real_argb_color const &color);
extern void render_debug_box(real_rectangle3d const &bounds, real_argb_color const &color);
extern void render_debug_box_outline(real_rectangle3d const &bounds, real_argb_color const &color);
extern void render_debug_box_oriented(real_rectangle3d const &bounds, real_matrix4x3 const &matrix, real_argb_color const &color);
extern void render_debug_point(real_point3d const &point, float size, real_argb_color const &color);
extern void render_debug_vector(real_point3d const &point, real_vector3d const &vector, real_argb_color const &color);
extern void render_debug_pill(real_point3d const &base, real_vector3d const &height, float radius, real_argb_color const &color);
extern void render_debug_cylinder(real_point3d const &base, real_vector3d const &height, float radius, real_argb_color const &color);
extern void render_debug_cone_outline(real_point3d const &base, real_vector3d const &up, float theta, float height, real_argb_color const &color);
extern void render_debug_string_at_point(real_point3d const &point, char const *string, real_argb_color const &color, long font_id, float scale);
extern float point3d_distance(real_point3d const *pA, real_point3d const *pB);
extern bool vector_plane_intersection(real_point3d const *point, real_vector3d const *vector, real_plane3d const *plane, float *out_t);
extern void render_debug_convex_vertices_shape(hkpConvexVerticesShape const *shape, real_matrix4x3 const *matrix, real_argb_color const *color);
extern void render_debug_physics_shape(hkpShape const *shape, real_matrix4x3 const *matrix, real_argb_color const *color);

/* ---------- globals */

extern float normalize3d(real_vector3d *v);  // hades: added for 0X10F08000
extern float magnitude3d(real_vector3d const *v);  // hades: added for 0X10F08000
extern real_vector3d *cross_product3d(real_vector3d const *v1, real_vector3d const *v2, real_vector3d *result);  // hades: added for 0X10F08000
extern real_vector3d *perpendicular3d(real_vector3d const *v, real_vector3d *result);  // hades: added for 0X10F08000
extern void matrix4x3_transform_points(real_matrix4x3 const *matrix, long point_count, real_point3d const *points, real_point3d *out_points);  // hades: added for 0X10F08540
extern void matrix4x3_multiply(real_matrix4x3 const *m1, real_matrix4x3 const *m2, real_matrix4x3 *result);  // hades: added for 0x10F0A2E0
extern float magnitude_squared3d(real_vector3d const *v);  // hades: added for 0x10F0A2E0
extern float dot_product3d(real_vector3d const *v1, real_vector3d const *v2);  // hades: added for 0x10F09390
extern real_vector3d *vector_from_points3d(real_point3d const *p1, real_point3d const *p2, real_vector3d *result);  // hades: added for 0x10F09390
extern float plane3d_distance_to_point(real_plane3d const *plane, real_point3d const *point);  // hades: added for 0x10F09390

/* ---------- private variables */

/* ---------- public code */

void render_debug_enable_depth_test(bool enable) // 0x10F0A190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_enable_depth_test@@YAX_N@Z");
	// bool enable;


	*(unsigned char *)0xa4587c = enable ? 1 : 2;
	*(unsigned char *)0xa45baf = enable ? 1 : 2;
}

void render_debug_build_circle_points(float radius, real_point2d *points, long total_point_count) // 0x10F08820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_build_circle_points@@YAXMPAUreal_point2d@@J@Z");
	// long total_point_count;
		// __int32 i;
			// float x0;
			// float t1;
			// float y0;
			// float t0;
			// float x1;
			// float y1;

	for (__int32 i = 0; i < total_point_count - 1; i++)
	{
		float t0 = (float)i / (total_point_count - 1) * 3.14159265f * 2.0f;
		float t1 = (float)(i + 1) / (total_point_count - 1) * 3.14159265f * 2.0f;
		float x0 = cos(t0) * radius;
		float y0 = sin(t0) * radius;
		float x1 = cos(t1) * radius;
		float y1 = sin(t1) * radius;
		points[i] = real_point2d{ x0, y0 };
		points[i + 1] = real_point2d{ x1, y1 };
	}
}

float build_height_matrix(real_point3d const *base, real_vector3d const *height, real_matrix4x3 *matrix) // 0x10F08000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_height_matrix@@YAMPBUreal_point3d@@PBUreal_vector3d@@PAUreal_matrix4x3@@@Z");
	// real_matrix4x3 *matrix;

	matrix->scale = 1.0f;
	matrix->up = *height;
	perpendicular3d(&matrix->up, &matrix->left);
	normalize3d(&matrix->up);
	normalize3d(&matrix->left);
	cross_product3d(&matrix->left, &matrix->up, &matrix->forward);
	matrix->position = *base;
	return magnitude3d(height);
}

void render_debug_build_pill_points(real_point3d const *base, real_vector3d const *height, float radius, real_point3d *p1, real_point3d *p2, real_point3d *p3, real_point3d *p4, real_point3d *p5, real_point3d *p6) // 0x10F08A60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_build_pill_points@@YAXPBUreal_point3d@@PBUreal_vector3d@@MPAU1@22222@Z");
	// real_point3d *p2;
	// real_point3d *p3;
	// real_point3d *p4;
	// real_point3d *p5;
	// real_point3d *p6;
	// float h;
	// real_point2d circle_points[17];
	// real_matrix4x3 height_matrix;
		// __int32 i;
		// __int32 j;
			// real_point2d &v17;
			// real_point2d &v18;

	real_matrix4x3 height_matrix;
	float h = build_height_matrix(base, height, &height_matrix);
	real_point2d circle_points[17];
	render_debug_build_circle_points(radius, circle_points, 17);
	if (p1 && p2)
	{
		for (__int32 i = 0; i < 17; i++)
		{
			p1[i] = real_point3d{ circle_points[i].x, circle_points[i].y, h };
			p2[i] = real_point3d{ circle_points[i].x, circle_points[i].y, 0.0f };
			matrix4x3_transform_point(&height_matrix, &p1[i], &p1[i]);
			matrix4x3_transform_point(&height_matrix, &p2[i], &p2[i]);
		}
	}
	if (p3 && p4 && p5 && p6)
	{
		for (__int32 j = 0; j < 9; j++)
		{
			real_point2d &v17 = circle_points[j];
			real_point2d &v18 = circle_points[j + 8];
			p3[j] = real_point3d{ 0.0f, v17.x, v17.y + h };
			p4[j] = real_point3d{ 0.0f, v18.x, v18.y };
			p5[j] = real_point3d{ v17.x, 0.0f, v17.y + h };
			p6[j] = real_point3d{ v18.x, 0.0f, v18.y };
			matrix4x3_transform_point(&height_matrix, &p3[j], &p3[j]);
			matrix4x3_transform_point(&height_matrix, &p4[j], &p4[j]);
			matrix4x3_transform_point(&height_matrix, &p5[j], &p5[j]);
			matrix4x3_transform_point(&height_matrix, &p6[j], &p6[j]);
		}
	}
}

void render_debug_sphere(real_point3d const &center, float radius, real_argb_color const &color) // 0x10F0B230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_sphere@@YAXABUreal_point3d@@MABUreal_argb_color@@@Z");
	// static ...; // 0x10F0B7CB
	// static ...; // 0x10F0B7C8
	// static ...; // 0x10F0B798
	// static ...; // 0x10F0B790
	// real_point3d const &center;
	// float radius;
	// real_argb_color const &color;
	// s_debug_vertex vertices[162];
	// real_point2d circle_points[27];
	// unsigned long pixel_color;
	// __int32 j;
		// __int32 i;
			// real_point2d p2;
			// real_point2d p1;
	// function call : unsigned long (*const)(real_argb_color const &)
	// function call : void (*const)(s_debug_vertex const *, long)

	real_point2d circle_points[27];
	render_debug_build_circle_points(radius, circle_points, 27);
	s_debug_vertex vertices[162];
	unsigned long pixel_color = ((unsigned long (__cdecl *)(real_argb_color const &))0x521810)(color);
	__int32 j = 0;
	for (__int32 i = 0; i < sizeof(circle_points) / sizeof(circle_points[0]) - 1; i++)
	{
		real_point2d p1 = circle_points[i];
		real_point2d p2 = circle_points[i + 1];
		if (j >= sizeof(vertices) / sizeof(vertices[0]))
			break;
		vertices[j].color = pixel_color;
		vertices[j++].position = center + real_point3d{ p1.x, p1.y, 0.0f };
		vertices[j].color = pixel_color;
		vertices[j++].position = center + real_point3d{ p1.x, p1.y, 0.0f };
		vertices[j].color = pixel_color;
		vertices[j++].position = center + real_point3d{ p1.y, 0.0f, p1.x };
		vertices[j].color = pixel_color;
		vertices[j++].position = center + real_point3d{ p2.y, 0.0f, p2.x };
		vertices[j].color = pixel_color;
		vertices[j++].position = center + real_point3d{ 0.0f, p1.x, p1.y };
		vertices[j].color = pixel_color;
		vertices[j++].position = center + real_point3d{ 0.0f, p2.x, p2.y };
	}
	((void (__cdecl *)(s_debug_vertex const *, long))0xA45920)(vertices, j / 2);
}

void render_debug_triangle(real_point3d const &point1, real_point3d const &point2, real_point3d const &point3, real_argb_color const &color) // 0x10F0BC40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_triangle@@YAXABUreal_point3d@@00ABUreal_argb_color@@@Z");
	// real_point3d const &point1;
	// real_point3d const &point2;
	// real_point3d const &point3;
	// real_argb_color const &color;
	// s_debug_vertex vertices[3];
	// unsigned long pixel_color;
	// function call : unsigned long (*const)(real_argb_color const &)
	// function call : void (*const)(s_debug_vertex const *, long, e_primitive_type)

	s_debug_vertex vertices[3];

	unsigned long pixel_color = ((unsigned long (__cdecl *)(real_argb_color const &))0x521810)(color);
	vertices[0].color = pixel_color;
	vertices[0].position = point1;
	vertices[1].color = pixel_color;
	vertices[1].position = point2;
	vertices[2].color = pixel_color;
	vertices[2].position = point3;
	((void (__cdecl *)(s_debug_vertex const *, long, e_primitive_type))0xa45b90)(vertices, 1, _primitive_type_triangle_list);
}

void render_debug_line(real_point3d const &point0, real_point3d const &point1, real_argb_color const &color) // 0x10F0A240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_line@@YAXABUreal_point3d@@0ABUreal_argb_color@@@Z");
	// real_argb_color const &color;
	// unsigned long pixel_color;
	// function call : unsigned long (*const)(real_argb_color const &)
	// function call : void (*const)(real_point3d const *, real_point3d const *, unsigned long, unsigned long)

	unsigned int pixel_color = ((unsigned int (__cdecl *)(real_argb_color const &))0x521810)(color);
	((void (__cdecl *)(real_point3d const &, real_point3d const &, unsigned int, unsigned int))0xa45830)(point0, point1, pixel_color, pixel_color);
}

void render_debug_quadrilateral(real_point3d const &point0, real_point3d const &point1, real_point3d const &point2, real_point3d const &point3, real_argb_color const &color) // 0x10F0B1B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_quadrilateral@@YAXABUreal_point3d@@000ABUreal_argb_color@@@Z");
	// real_argb_color const &color;

	render_debug_triangle(point0, point1, point2, color);
	render_debug_triangle(point0, point2, point3, color);
}

void render_debug_box(real_rectangle3d const &bounds, real_argb_color const &color) // 0x10F083A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_box@@YAXABUreal_rectangle3d@@ABUreal_argb_color@@@Z");
	// static ...; // 0x10F084D4
	// static ...; // 0x10F084CC
	// real_rectangle3d const &bounds;
	// real_argb_color const &color;
	// unsigned long pixel_color;
	// real_point3d faces[6][4];
		// long i;
	// function call : unsigned long (*const)(real_argb_color const &)

	real_point3d faces[6][4];
	rectangle3d_build_faces(bounds, faces);
	unsigned long pixel_color = eldorado::real_argb_color_to_pixel32(color);
	for (long i = 0; i < 6; i++)
	{
		render_debug_quadrilateral(faces[i][0], faces[i][1], faces[i][2], faces[i][3], color);
	}
}

void render_debug_box_outline(real_rectangle3d const &bounds, real_argb_color const &color) // 0x10F086C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_box_outline@@YAXABUreal_rectangle3d@@ABUreal_argb_color@@@Z");
	// static ...; // 0x10F087C0
	// static ...; // 0x10F087B8
	// real_rectangle3d const &bounds;
	// real_argb_color const &color;
	// real_point3d edges[12][2];
	// unsigned long pixel_color;
		// long edge_index;
	// function call : unsigned long (*const)(real_argb_color const &)

	real_point3d edges[12][2];
	rectangle3d_build_edges(bounds, 12, edges);
	unsigned long pixel_color = eldorado::real_argb_color_to_pixel32(color);
	for (long edge_index = 0; edge_index < 12; edge_index++)
	{
		render_debug_line(edges[edge_index][0], edges[edge_index][1], color);
	}
}

void render_debug_box_oriented(real_rectangle3d const &bounds, real_matrix4x3 const &matrix, real_argb_color const &color) // 0x10F08540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_box_oriented@@YAXABUreal_rectangle3d@@ABUreal_matrix4x3@@ABUreal_argb_color@@@Z");
	// static ...; // 0x10F08654
	// real_rectangle3d const &bounds;
	// real_matrix4x3 const &matrix;
	// real_argb_color const &color;
	// real_point3d edges[12][2];
	// unsigned long pixel_color;
		// long edge_index;
	// function call : unsigned long (*const)(real_argb_color const &)

	real_point3d edges[12][2];

	rectangle3d_build_edges(bounds, 12, edges);
	matrix4x3_transform_points(&matrix, 24, (real_point3d *)edges, (real_point3d *)edges);
	unsigned long pixel_color = ((unsigned long (__cdecl *)(real_argb_color const &))0x521810)(color);
	for (long edge_index = 0; edge_index < 12; edge_index++)
	{
		render_debug_line(edges[edge_index][0], edges[edge_index][1], color);
	}
}

void render_debug_point(real_point3d const &point, float size, real_argb_color const &color) // 0x10F0AF70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_point@@YAXABUreal_point3d@@MABUreal_argb_color@@@Z");
	// static ...; // 0x10F0B120
	// real_point3d const &point;
	// float size;
	// real_argb_color const &color;
	// real_point3d vertices[6];
		// long i;

	size *= 0.5f;
	real_point3d vertices[6] =
	{
		{ point.x - size, point.y, point.z },
		{ point.x + size, point.y, point.z },
		{ point.x, point.y - size, point.z },
		{ point.x, point.y + size, point.z },
		{ point.x, point.y, point.z - size },
		{ point.x, point.y, point.z + size },
	};
	for (long i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i += 2)
		render_debug_line(vertices[i], vertices[i + 1], color);
}

void render_debug_vector(real_point3d const &point, real_vector3d const &vector, real_argb_color const &color) // 0x10F0BDD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_vector@@YAXABUreal_point3d@@ABUreal_vector3d@@ABUreal_argb_color@@@Z");
	// real_argb_color const &color;

	render_debug_point(point, 0.0025f, color);
	render_debug_line(point, real_point3d{ point.x + vector.i, point.y + vector.j, point.z + vector.k }, color);
}

void render_debug_pill(real_point3d const &base, real_vector3d const &height, float radius, real_argb_color const &color) // 0x10F0ABF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_pill@@YAXABUreal_point3d@@ABUreal_vector3d@@MABUreal_argb_color@@@Z");
	// static ...; // 0x10F0AEAA
	// static ...; // 0x10F0AEA7
	// static ...; // 0x10F0AEA4
	// static ...; // 0x10F0AE5C
	// static ...; // 0x10F0AE54
	// real_point3d const &base;
	// real_vector3d const &height;
	// float radius;
	// real_argb_color const &color;
	// real_point3d p6[17];
	// real_point3d p2[17];
	// real_point3d p4[17];
	// real_point3d p1[17];
	// real_point3d p3[17];
	// real_point3d p5[17];
		// long i;
		// long j;
		// long k;

	real_point3d p1[17];
	real_point3d p2[17];
	real_point3d p3[17];
	real_point3d p4[17];
	real_point3d p5[17];
	real_point3d p6[17];
	render_debug_build_pill_points(&base, &height, radius, p1, p2, p3, p4, p5, p6);
	for (long i = 0; i < 16; i++)
	{
		render_debug_line(p1[i], p1[i + 1], color);
		render_debug_line(p2[i], p2[i + 1], color);
	}
	for (long j = 0; j < 16; j += 4)
		render_debug_line(p1[j], p2[j], color);
	for (long k = 0; k < 8; k++)
	{
		render_debug_line(p3[k], p3[k + 1], color);
		render_debug_line(p4[k], p4[k + 1], color);
		render_debug_line(p5[k], p5[k + 1], color);
		render_debug_line(p6[k], p6[k + 1], color);
	}
}

void render_debug_cylinder(real_point3d const &base, real_vector3d const &height, float radius, real_argb_color const &color) // 0x10F09EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_cylinder@@YAXABUreal_point3d@@ABUreal_vector3d@@MABUreal_argb_color@@@Z");
	// static ...; // 0x10F0A0DC
	// real_point3d const &base;
	// real_vector3d const &height;
	// float radius;
	// real_argb_color const &color;
	// real_point3d p2[17];
	// real_point3d p1[17];
		// long i;
		// long j;
		// long k;

	real_point3d p1[17];
	real_point3d p2[17];
	render_debug_build_pill_points(&base, &height, radius, p1, p2, nullptr, nullptr, nullptr, nullptr);
	for (long i = 0; i < 16; i++)
	{
		render_debug_line(p2[i], p2[i + 1], color);
		render_debug_line(p1[i], p1[i + 1], color);
	}
	for (long j = 0; j < 16; j += 4)
		render_debug_line(p2[j], p1[j], color);
	for (long k = 0; k < 8; k += 4)
	{
		render_debug_line(p2[k], p2[k + 8], color);
		render_debug_line(p1[k], p1[k + 8], color);
	}
}

void render_debug_cone_outline(real_point3d const &base, real_vector3d const &up, float theta, float height, real_argb_color const &color) // 0x10F08FF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_cone_outline@@YAXABUreal_point3d@@ABUreal_vector3d@@MMABUreal_argb_color@@@Z");
	// static ...; // 0x10F09278
	// static ...; // 0x10F09270
	// real_point3d const &base;
	// real_vector3d const &up;
	// float theta;
	// float height;
	// real_argb_color const &color;
	// __int32 const points_count;
	// real_point3d points[17];
	// real_point2d circle_points[17];
	// real_point3d apex;
	// real_matrix4x3 height_matrix;
	// float radius;
		// long i;

	float radius = tan(theta) * height;
	real_point3d apex = base + height * up;
	__int32 const points_count = 17;
	real_point2d circle_points[points_count];
	render_debug_build_circle_points(radius, circle_points, points_count);
	real_matrix4x3 height_matrix;
	build_height_matrix(&base, &up, &height_matrix);
	real_point3d points[points_count];
	for (long i = 0; i < points_count; i++)
	{
		points[i] = real_point3d{ circle_points[i].x, circle_points[i].y, 0.0f };
		matrix4x3_transform_point(&height_matrix, &points[i], &points[i]);
	}
	for (long i = 0; i < points_count - 1; i++)
	{
		render_debug_line(points[i], apex, color);
		render_debug_line(points[i], points[i + 1], color);
	}
}

void render_debug_string_at_point(real_point3d const &point, char const *string, real_argb_color const &color, long font_id, float scale) // 0x10F0B960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_string_at_point@@YAXABUreal_point3d@@PBDABUreal_argb_color@@JM@Z");
	// static ...; // 0x10F0BB54
	// static ...; // 0x10F0BB4C
	// real_point3d const &point;
	// char const *string;
	// real_argb_color const &color;
	// long font_id;
	// float scale;
	// real_point2d screen_point;
	// c_player_view *player_view;
		// short_rectangle2d bounds;
		// c_rasterizer_draw_string draw_str;
		// c_font_cache_mt_safe font_cache;

	real_point2d screen_point;
	c_player_view *player_view = (c_player_view *)0x50DEE10;
	if (render_camera_world_to_window(&player_view->rasterizer_camera, &player_view->rasterizer_projection, &player_view->rasterizer_camera.display_pixel_bounds, &point, &screen_point))
	{
		c_font_cache_mt_safe font_cache;
		c_rasterizer_draw_string draw_str;
		draw_str.set_font(font_id);
		draw_str.set_scale(scale);
		draw_str.set_style(-1);
		draw_str.set_justification(0);
		draw_str.set_color(color);
		draw_str.set_shadow_color(real_argb_color{ 1.0f, 0.0f, 0.0f, 0.0f });
		draw_str.set_drop_shadow_style(2);
		short_rectangle2d bounds;
		bounds.x0 = (short)screen_point.x;
		bounds.y0 = (short)screen_point.y;
		bounds.x1 = 0x7FFF;
		bounds.y1 = 0x7FFF;
		draw_str.set_bounds(bounds);
		draw_str.draw(&font_cache, string);
	}
}

float point3d_distance(real_point3d const *pA, real_point3d const *pB) // 0x10F082A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?point3d_distance@@YAMPBUreal_point3d@@0@Z");
	// real_point3d const *pB;
	// double x;
	// double y;
	// double z;

	double x = pow(pA->x - pB->x, 2);
	double y = pow(pA->y - pB->y, 2);
	double z = pow(pA->z - pB->z, 2);
	return sqrt(x + y + z);
}

bool vector_plane_intersection(real_point3d const *point, real_vector3d const *vector, real_plane3d const *plane, float *out_t) // 0x10F0BEC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?vector_plane_intersection@@YA_NPBUreal_point3d@@PBUreal_vector3d@@PBUreal_plane3d@@PAM@Z");
	// float *out_t;
	// float d;
	// float n;

	float n = dot_product3d(&plane->normal, vector);
	float d = plane3d_distance_to_point(plane, point);
	if (fabsf(n) < 0.00001f)
	{
		*out_t = 0.0f;
		return false;
	}
	*out_t = -d / n;
	return true;
}

void render_debug_convex_vertices_shape(hkpConvexVerticesShape const *shape, real_matrix4x3 const *matrix, real_argb_color const *color) // 0x10F09390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_convex_vertices_shape@@YAXPBUhkpConvexVerticesShape@@PBUreal_matrix4x3@@PBUreal_argb_color@@@Z");
	// static ...; // 0x10F09C94
	// static ...; // 0x10F09C89
	// static ...; // 0x10F09C80
	// static ...; // 0x10F09C79
	// static ...; // 0x10F09C77
	// static ...; // 0x10F09C74
	// static ...; // 0x10F09C71
	// static ...; // 0x10F09C6E
	// static ...; // 0x10F09C6B
	// static ...; // 0x10F09C68
	// static ...; // 0x10F09BD8
	// static ...; // 0x10F09BD0
	// hkpConvexVerticesShape const *shape;
	// real_matrix4x3 const *matrix;
	// real_argb_color const *color;
	// hkVector4 *plane_equations;
	// bool (*const line_from_planes3d)(real_plane3d *, real_plane3d *, real_point3d *, real_vector3d *);
	// hkpConvexVerticesShape::FourVectors *four_vector_vertices;
		// long i;
			// hkpConvexVerticesShape::FourVectors *const v1;
				// long j;
					// real_point3d p1;
		// __int32 i;
			// real_plane3d plane1;
				// __int32 j;
					// float min_dist;
					// real_plane3d plane2;
					// bool skip;
					// real_point3d line_start;
					// real_vector3d line_vec;
					// float max_dist;
						// __int32 k;
							// float t;
							// real_plane3d plane3;
						// real_point3d p2;
						// hkpConvexVerticesShape::FourVectors *four_vector_vertices;
						// real_point3d p1;
						// __int32 found;
							// long i;
								// hkpConvexVerticesShape::FourVectors *const v1;
									// long l;
										// real_vector3d v1;
										// real_point3d p3;
										// real_vector3d v2;
	// function call : bool (*const)(real_plane3d *, real_plane3d *, real_point3d *, real_vector3d *)

	bool (*const line_from_planes3d)(real_plane3d *, real_plane3d *, real_point3d *, real_vector3d *) = (bool (*)(real_plane3d *, real_plane3d *, real_point3d *, real_vector3d *))0x4F2550;
	hkpConvexVerticesShape::FourVectors *four_vector_vertices = (hkpConvexVerticesShape::FourVectors *)shape->m_rotatedVertices.m_data;
	for (long i = 0; i < shape->m_rotatedVertices.m_size; i++)
	{
		hkpConvexVerticesShape::FourVectors *const v1 = &four_vector_vertices[i];
		for (long j = 0; j < 4; j++)
		{
			real_point3d p1 = { v1->m_x(j), v1->m_y(j), v1->m_z(j) };
			matrix4x3_transform_point(matrix, &p1, &p1);
			render_debug_point(p1, 0.025f, *color);
		}
	}
	if (shape->m_rotatedVertices.m_size < 2 || shape->m_planeEquation.m_size < 4 || shape->m_planeEquation.m_size > 64)
		return;
	hkVector4 *plane_equations = (hkVector4 *)shape->m_planeEquation.m_data;
	for (__int32 i = 0; i < shape->m_planeEquation.m_size; i++)
	{
		real_plane3d plane1 = { plane_equations[i].x, plane_equations[i].y, plane_equations[i].z, -plane_equations[i].w };
		for (__int32 j = i + 1; j < shape->m_planeEquation.m_size; j++)
		{
			real_plane3d plane2 = { plane_equations[j].x, plane_equations[j].y, plane_equations[j].z, -plane_equations[j].w };
			real_point3d line_start;
			real_vector3d line_vec;
			if (!line_from_planes3d(&plane1, &plane2, &line_start, &line_vec))
				continue;
			float min_dist = -1000.0f;
			float max_dist = 1000.0f;
			bool skip = false;
			for (__int32 k = 0; k < shape->m_planeEquation.m_size && !skip; k++)
			{
				if (k == i && k == j)
					continue;
				real_plane3d plane3 = { plane_equations[k].x, plane_equations[k].y, plane_equations[k].z, -plane_equations[k].w };
				float t;
				if (!vector_plane_intersection(&line_start, &line_vec, &plane3, &t))
					continue;
				normalize3d(&line_vec);
				if (t == 0.0f)
				{
					if (plane3d_distance_to_point(&plane3, &line_start) > 0.0f)
						skip = true;
				}
				else if (dot_product3d(&plane3.normal, &line_vec) > 0.0f)
				{
					max_dist = fminf(max_dist, t);
				}
				else
				{
					min_dist = fmaxf(min_dist, t);
				}
				if (min_dist >= max_dist)
					skip = true;
			}
			if (!skip)
			{
				real_point3d p1;
				p1 = line_start + max_dist * line_vec;
				real_point3d p2;
				p2 = line_start + min_dist * line_vec;
				hkpConvexVerticesShape::FourVectors *four_vector_vertices = (hkpConvexVerticesShape::FourVectors *)shape->m_rotatedVertices.m_data;
				__int32 found = 0;
				for (long i = 0; i < shape->m_rotatedVertices.m_size; i++)
				{
					hkpConvexVerticesShape::FourVectors *const v1 = &four_vector_vertices[i];
					for (long l = 0; l < 4; l++)
					{
						real_point3d p3 = { v1->m_x(l), v1->m_y(l), v1->m_z(l) };
						real_vector3d v1;
						real_vector3d v2;
						vector_from_points3d(&p1, &p3, &v1);
						vector_from_points3d(&p2, &p3, &v2);
						if (magnitude_squared3d(&v1) < 0.00001f)
							found++;
						if (magnitude_squared3d(&v2) < 0.00001f)
							found++;
					}
				}
				if (found == 2)
				{
					matrix4x3_transform_point(matrix, &p1, &p1);
					matrix4x3_transform_point(matrix, &p2, &p2);
					render_debug_line(p1, p2, *color);
				}
			}
		}
	}
}

void render_debug_physics_shape(hkpShape const *shape, real_matrix4x3 const *matrix, real_argb_color const *color) // 0x10F0A2E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_physics_shape@@YAXPBUhkpShape@@PBUreal_matrix4x3@@PBUreal_argb_color@@@Z");
	// static ...; // 0x10F0A9D9
	// static ...; // 0x10F0A9D6
	// static ...; // 0x10F0A9D3
	// static ...; // 0x10F0A9CE
	// static ...; // 0x10F0A9C5
	// static ...; // 0x10F0A9BC
	// static ...; // 0x10F0A9AE
	// static ...; // 0x10F0A9A4
	// static ...; // 0x10F0A99A
	// static ...; // 0x10F0A990
	// static ...; // 0x10F0A918
	// static ...; // 0x10F0A910
// $LN22:
// $LN21:
// $LN20:
// $LN19:
// $LN14:
// $LN13:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
	// hkpShape const *shape;
	// real_matrix4x3 const *matrix;
	// real_argb_color const *color;
		// real_point3d p2;
		// real_point3d p1;
		// hkpTriangleShape *triangle;
		// real_point3d p3;
		// hkpBoxShape *box;
		// real_rectangle3d aabb;
		// real_vector3d height_vector;
		// real_point3d vertex_b;
		// float height_squared;
		// hkpCapsuleShape *pill;
		// real_point3d vertex_a;
		// char shapebuff[512];
		// hkShapeContainer const *shape_container;
			// hkpListShape *list;
			// unsigned __int32 k;
				// hkpShape *child_shape;
		// hkpBvShape *bv;
		// real_matrix4x3 transform;
		// hkpShape *child_shape;
		// hkpConvexTransformShape *convex_transform;
		// hkpConvexTranslateShape *convex_translate;
	// function call : void (*const)(real_matrix4x3 *, hkTransform *)

	switch (shape->m_type)
	{
	case HK_SHAPE_SPHERE:
		render_debug_sphere(matrix->position, ((hkpConvexShape const *)shape)->m_radius, *color);
		break;
	case HK_SHAPE_TRIANGLE:
	{
		hkpTriangleShape *triangle = (hkpTriangleShape *)shape;
		real_point3d p1 = { triangle->m_vertexA.x, triangle->m_vertexA.y, triangle->m_vertexA.z };
		real_point3d p2 = { triangle->m_vertexB.x, triangle->m_vertexB.y, triangle->m_vertexB.z };
		real_point3d p3 = { triangle->m_vertexC.x, triangle->m_vertexC.y, triangle->m_vertexC.z };
		matrix4x3_transform_point(matrix, &p1, &p1);
		matrix4x3_transform_point(matrix, &p2, &p2);
		matrix4x3_transform_point(matrix, &p3, &p3);
		render_debug_triangle(p1, p2, p3, *color);
		break;
	}
	case HK_SHAPE_BOX:
	{
		hkpBoxShape *box = (hkpBoxShape *)shape;
		real_rectangle3d aabb;
		aabb.x0 = -box->m_halfExtents.x;
		aabb.x1 = box->m_halfExtents.x;
		aabb.y0 = -box->m_halfExtents.y;
		aabb.y1 = box->m_halfExtents.y;
		aabb.z0 = -box->m_halfExtents.z;
		aabb.z1 = box->m_halfExtents.z;
		render_debug_box_oriented(aabb, *matrix, *color);
		break;
	}
	case HK_SHAPE_CAPSULE:
	{
		hkpCapsuleShape *pill = (hkpCapsuleShape *)shape;
		real_point3d vertex_a = { pill->m_vertexA.x, pill->m_vertexA.y, pill->m_vertexA.z };
		real_point3d vertex_b = { pill->m_vertexB.x, pill->m_vertexB.y, pill->m_vertexB.z };
		matrix4x3_transform_point(matrix, &vertex_a, &vertex_a);
		matrix4x3_transform_point(matrix, &vertex_b, &vertex_b);
		real_vector3d height_vector;
		height_vector = vertex_b - vertex_a;
		float height_squared = magnitude_squared3d(&height_vector);
		if (height_squared >= 0.00001f)
			render_debug_pill(vertex_a, height_vector, pill->m_radius, *color);
		else
			render_debug_sphere(vertex_a, pill->m_radius, *color);
		break;
	}
	case HK_SHAPE_CONVEX_VERTICES:
		render_debug_convex_vertices_shape((hkpConvexVerticesShape const *)shape, matrix, color);
		break;
	case HK_SHAPE_LIST:
	case HK_SHAPE_BV_TREE:
	case HK_SHAPE_MOPP:
	{
		hkShapeContainer const *shape_container = nullptr;
		if (shape->m_type == HK_SHAPE_LIST)
		{
			hkpListShape *list = (hkpListShape *)shape;
			shape_container = list;
		}
		else
		{
			shape_container = shape->getContainer();
		}
		alignas(16) char shapebuff[512];
		for (unsigned __int32 k = shape_container->getFirstKey(); k != -1; k = shape_container->getNextKey(k))
		{
			hkpShape *child_shape = shape_container->getChildShape(k, shapebuff);
			render_debug_physics_shape(child_shape, matrix, color);
		}
		break;
	}
	case HK_SHAPE_BV:
	{
		hkpBvShape *bv = (hkpBvShape *)shape;
		render_debug_physics_shape(bv->m_child_shape.m_childShape, matrix, color);
		break;
	}
	case HK_SHAPE_CONVEX_TRANSFORM:
	{
		hkpConvexTransformShape *convex_transform = (hkpConvexTransformShape *)shape;
		real_matrix4x3 transform;
		((void (*const)(real_matrix4x3 *, hkTransform *))0x717B70)(&transform, &convex_transform->m_transform);
		matrix4x3_multiply(matrix, &transform, &transform);
		hkpShape *child_shape = convex_transform->m_childShape.m_childShape;
		render_debug_physics_shape(child_shape, &transform, color);
		break;
	}
	case HK_SHAPE_CONVEX_TRANSLATE:
	{
		hkpConvexTranslateShape *convex_translate = (hkpConvexTranslateShape *)shape;
		real_matrix4x3 transform;
		transform.scale = 1.0f;
		transform.forward = global_forward3d;
		transform.up = global_up3d;
		transform.left = global_left3d;
		transform.position = { convex_translate->m_translation.x, convex_translate->m_translation.y, convex_translate->m_translation.z };
		matrix4x3_multiply(matrix, &transform, &transform);
		hkpShape *child_shape = convex_translate->m_childShape.m_childShape;
		render_debug_physics_shape(child_shape, &transform, color);
		break;
	}
	}
}

/* ---------- private code */
