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

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F0A190(bool);
void render_debug_enable_depth_test(bool enable) // 0x10F0A190
{
	mangled_x86(MANGLED_TODO, "?render_debug_enable_depth_test@@YAX_N@Z");
	// bool enable;
	todo("implement");
	_sub_10F0A190(enable);
}

_extern void _sub_10F08820(float, real_point2d *, long);
void render_debug_build_circle_points(float radius, real_point2d *points, long total_point_count) // 0x10F08820
{
	mangled_x86(MANGLED_TODO, "?render_debug_build_circle_points@@YAXMPAUreal_point2d@@J@Z");
	// long total_point_count;
	{
		// __int32 i;
		{
			// float x0;
			// float t1;
			// float y0;
			// float t0;
			// float x1;
			// float y1;
		}
	}
	todo("implement");
	_sub_10F08820(radius, points, total_point_count);
}

_extern float _sub_10F08000(real_point3d const *, real_vector3d const *, real_matrix4x3 *);
float build_height_matrix(real_point3d const *base, real_vector3d const *height, real_matrix4x3 *matrix) // 0x10F08000
{
	mangled_x86(MANGLED_TODO, "?build_height_matrix@@YAMPBUreal_point3d@@PBUreal_vector3d@@PAUreal_matrix4x3@@@Z");
	// real_matrix4x3 *matrix;
	todo("implement");
	float __result = _sub_10F08000(base, height, matrix);
	return __result;
}

_extern void _sub_10F08A60(real_point3d const *, real_vector3d const *, float, real_point3d *, real_point3d *, real_point3d *, real_point3d *, real_point3d *, real_point3d *);
void render_debug_build_pill_points(real_point3d const *base, real_vector3d const *height, float radius, real_point3d *p1, real_point3d *p2, real_point3d *p3, real_point3d *p4, real_point3d *p5, real_point3d *p6) // 0x10F08A60
{
	mangled_x86(MANGLED_TODO, "?render_debug_build_pill_points@@YAXPBUreal_point3d@@PBUreal_vector3d@@MPAU1@22222@Z");
	// real_point3d *p2;
	// real_point3d *p3;
	// real_point3d *p4;
	// real_point3d *p5;
	// real_point3d *p6;
	// float h;
	// real_point2d circle_points[17];
	// real_matrix4x3 height_matrix;
	{
		// __int32 i;
	}
	{
		// __int32 j;
		{
			// real_point2d &v17;
			// real_point2d &v18;
		}
	}
	todo("implement");
	_sub_10F08A60(base, height, radius, p1, p2, p3, p4, p5, p6);
}

_extern void _sub_10F0B230(real_point3d const &, float, real_argb_color const &);
void render_debug_sphere(real_point3d const &center, float radius, real_argb_color const &color) // 0x10F0B230
{
	mangled_x86(MANGLED_TODO, "?render_debug_sphere@@YAXABUreal_point3d@@MABUreal_argb_color@@@Z");
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
	{
		// __int32 i;
		{
			// real_point2d p2;
			// real_point2d p1;
		}
	}
	// function call : unsigned long (*const)(real_argb_color const &)
	// function call : void (*const)(s_debug_vertex const *, long)
	todo("implement");
	_sub_10F0B230(center, radius, color);
}

_extern void _sub_10F0BC40(real_point3d const &, real_point3d const &, real_point3d const &, real_argb_color const &);
void render_debug_triangle(real_point3d const &point1, real_point3d const &point2, real_point3d const &point3, real_argb_color const &color) // 0x10F0BC40
{
	mangled_x86(MANGLED_TODO, "?render_debug_triangle@@YAXABUreal_point3d@@00ABUreal_argb_color@@@Z");
	// real_point3d const &point1;
	// real_point3d const &point2;
	// real_point3d const &point3;
	// real_argb_color const &color;
	// s_debug_vertex vertices[3];
	// unsigned long pixel_color;
	// function call : unsigned long (*const)(real_argb_color const &)
	// function call : void (*const)(s_debug_vertex const *, long, e_primitive_type)
	todo("implement");
	_sub_10F0BC40(point1, point2, point3, color);
}

_extern void _sub_10F0A240(real_point3d const &, real_point3d const &, real_argb_color const &);
void render_debug_line(real_point3d const &point0, real_point3d const &point1, real_argb_color const &color) // 0x10F0A240
{
	mangled_x86(MANGLED_TODO, "?render_debug_line@@YAXABUreal_point3d@@0ABUreal_argb_color@@@Z");
	// real_argb_color const &color;
	// unsigned long pixel_color;
	// function call : unsigned long (*const)(real_argb_color const &)
	// function call : void (*const)(real_point3d const *, real_point3d const *, unsigned long, unsigned long)
	todo("implement");
	_sub_10F0A240(point0, point1, color);
}

_extern void _sub_10F0B1B0(real_point3d const &, real_point3d const &, real_point3d const &, real_point3d const &, real_argb_color const &);
void render_debug_quadrilateral(real_point3d const &point0, real_point3d const &point1, real_point3d const &point2, real_point3d const &point3, real_argb_color const &color) // 0x10F0B1B0
{
	mangled_x86(MANGLED_TODO, "?render_debug_quadrilateral@@YAXABUreal_point3d@@000ABUreal_argb_color@@@Z");
	// real_argb_color const &color;
	todo("implement");
	_sub_10F0B1B0(point0, point1, point2, point3, color);
}

_extern void _sub_10F083A0(real_rectangle3d const &, real_argb_color const &);
void render_debug_box(real_rectangle3d const &bounds, real_argb_color const &color) // 0x10F083A0
{
	mangled_x86(MANGLED_TODO, "?render_debug_box@@YAXABUreal_rectangle3d@@ABUreal_argb_color@@@Z");
	// static ...; // 0x10F084D4
	// static ...; // 0x10F084CC
	// real_rectangle3d const &bounds;
	// real_argb_color const &color;
	// unsigned long pixel_color;
	// real_point3d faces[6][4];
	{
		// long i;
	}
	// function call : unsigned long (*const)(real_argb_color const &)
	todo("implement");
	_sub_10F083A0(bounds, color);
}

_extern void _sub_10F086C0(real_rectangle3d const &, real_argb_color const &);
void render_debug_box_outline(real_rectangle3d const &bounds, real_argb_color const &color) // 0x10F086C0
{
	mangled_x86(MANGLED_TODO, "?render_debug_box_outline@@YAXABUreal_rectangle3d@@ABUreal_argb_color@@@Z");
	// static ...; // 0x10F087C0
	// static ...; // 0x10F087B8
	// real_rectangle3d const &bounds;
	// real_argb_color const &color;
	// real_point3d edges[12][2];
	// unsigned long pixel_color;
	{
		// long edge_index;
	}
	// function call : unsigned long (*const)(real_argb_color const &)
	todo("implement");
	_sub_10F086C0(bounds, color);
}

_extern void _sub_10F08540(real_rectangle3d const &, real_matrix4x3 const &, real_argb_color const &);
void render_debug_box_oriented(real_rectangle3d const &bounds, real_matrix4x3 const &matrix, real_argb_color const &color) // 0x10F08540
{
	mangled_x86(MANGLED_TODO, "?render_debug_box_oriented@@YAXABUreal_rectangle3d@@ABUreal_matrix4x3@@ABUreal_argb_color@@@Z");
	// static ...; // 0x10F08654
	// real_rectangle3d const &bounds;
	// real_matrix4x3 const &matrix;
	// real_argb_color const &color;
	// real_point3d edges[12][2];
	// unsigned long pixel_color;
	{
		// long edge_index;
	}
	// function call : unsigned long (*const)(real_argb_color const &)
	todo("implement");
	_sub_10F08540(bounds, matrix, color);
}

_extern void _sub_10F0AF70(real_point3d const &, float, real_argb_color const &);
void render_debug_point(real_point3d const &point, float size, real_argb_color const &color) // 0x10F0AF70
{
	mangled_x86(MANGLED_TODO, "?render_debug_point@@YAXABUreal_point3d@@MABUreal_argb_color@@@Z");
	// static ...; // 0x10F0B120
	// real_point3d const &point;
	// float size;
	// real_argb_color const &color;
	// real_point3d vertices[6];
	{
		// long i;
	}
	todo("implement");
	_sub_10F0AF70(point, size, color);
}

_extern void _sub_10F0BDD0(real_point3d const &, real_vector3d const &, real_argb_color const &);
void render_debug_vector(real_point3d const &point, real_vector3d const &vector, real_argb_color const &color) // 0x10F0BDD0
{
	mangled_x86(MANGLED_TODO, "?render_debug_vector@@YAXABUreal_point3d@@ABUreal_vector3d@@ABUreal_argb_color@@@Z");
	// real_argb_color const &color;
	todo("implement");
	_sub_10F0BDD0(point, vector, color);
}

_extern void _sub_10F0ABF0(real_point3d const &, real_vector3d const &, float, real_argb_color const &);
void render_debug_pill(real_point3d const &base, real_vector3d const &height, float radius, real_argb_color const &color) // 0x10F0ABF0
{
	mangled_x86(MANGLED_TODO, "?render_debug_pill@@YAXABUreal_point3d@@ABUreal_vector3d@@MABUreal_argb_color@@@Z");
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
	{
		// long i;
	}
	{
		// long j;
	}
	{
		// long k;
	}
	todo("implement");
	_sub_10F0ABF0(base, height, radius, color);
}

_extern void _sub_10F09EF0(real_point3d const &, real_vector3d const &, float, real_argb_color const &);
void render_debug_cylinder(real_point3d const &base, real_vector3d const &height, float radius, real_argb_color const &color) // 0x10F09EF0
{
	mangled_x86(MANGLED_TODO, "?render_debug_cylinder@@YAXABUreal_point3d@@ABUreal_vector3d@@MABUreal_argb_color@@@Z");
	// static ...; // 0x10F0A0DC
	// real_point3d const &base;
	// real_vector3d const &height;
	// float radius;
	// real_argb_color const &color;
	// real_point3d p2[17];
	// real_point3d p1[17];
	{
		// long i;
	}
	{
		// long j;
	}
	{
		// long k;
	}
	todo("implement");
	_sub_10F09EF0(base, height, radius, color);
}

_extern void _sub_10F08FF0(real_point3d const &, real_vector3d const &, float, float, real_argb_color const &);
void render_debug_cone_outline(real_point3d const &base, real_vector3d const &up, float theta, float height, real_argb_color const &color) // 0x10F08FF0
{
	mangled_x86(MANGLED_TODO, "?render_debug_cone_outline@@YAXABUreal_point3d@@ABUreal_vector3d@@MMABUreal_argb_color@@@Z");
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
	{
		// long i;
	}
	{
	}
	todo("implement");
	_sub_10F08FF0(base, up, theta, height, color);
}

_extern void _sub_10F0B960(real_point3d const &, char const *, real_argb_color const &, long, float);
void render_debug_string_at_point(real_point3d const &point, char const *string, real_argb_color const &color, long font_id, float scale) // 0x10F0B960
{
	mangled_x86(MANGLED_TODO, "?render_debug_string_at_point@@YAXABUreal_point3d@@PBDABUreal_argb_color@@JM@Z");
	// static ...; // 0x10F0BB54
	// static ...; // 0x10F0BB4C
	// real_point3d const &point;
	// char const *string;
	// real_argb_color const &color;
	// long font_id;
	// float scale;
	// real_point2d screen_point;
	// c_player_view *player_view;
	{
		// short_rectangle2d bounds;
		// c_rasterizer_draw_string draw_str;
		// c_font_cache_mt_safe font_cache;
	}
	todo("implement");
	_sub_10F0B960(point, string, color, font_id, scale);
}

_extern float _sub_10F082A0(real_point3d const *, real_point3d const *);
float point3d_distance(real_point3d const *pA, real_point3d const *pB) // 0x10F082A0
{
	mangled_x86(MANGLED_TODO, "?point3d_distance@@YAMPBUreal_point3d@@0@Z");
	// real_point3d const *pB;
	// double x;
	// double y;
	// double z;
	todo("implement");
	float __result = _sub_10F082A0(pA, pB);
	return __result;
}

_extern bool _sub_10F0BEC0(real_point3d const *, real_vector3d const *, real_plane3d const *, float *);
bool vector_plane_intersection(real_point3d const *point, real_vector3d const *vector, real_plane3d const *plane, float *out_t) // 0x10F0BEC0
{
	mangled_x86(MANGLED_TODO, "?vector_plane_intersection@@YA_NPBUreal_point3d@@PBUreal_vector3d@@PBUreal_plane3d@@PAM@Z");
	// float *out_t;
	// float d;
	// float n;
	todo("implement");
	bool __result = _sub_10F0BEC0(point, vector, plane, out_t);
	return __result;
}

_extern void _sub_10F09390(hkpConvexVerticesShape const *, real_matrix4x3 const *, real_argb_color const *);
void render_debug_convex_vertices_shape(hkpConvexVerticesShape const *shape, real_matrix4x3 const *matrix, real_argb_color const *color) // 0x10F09390
{
	mangled_x86(MANGLED_TODO, "?render_debug_convex_vertices_shape@@YAXPBUhkpConvexVerticesShape@@PBUreal_matrix4x3@@PBUreal_argb_color@@@Z");
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
	{
		// long i;
		{
			// hkpConvexVerticesShape::FourVectors *const v1;
			{
				// long j;
				{
					// real_point3d p1;
				}
			}
		}
	}
	{
		// __int32 i;
		{
			// real_plane3d plane1;
			{
				// __int32 j;
				{
					// float min_dist;
					// real_plane3d plane2;
					// bool skip;
					// real_point3d line_start;
					// real_vector3d line_vec;
					// float max_dist;
					{
						// __int32 k;
						{
							// float t;
							// real_plane3d plane3;
						}
					}
					{
						// real_point3d p2;
						// hkpConvexVerticesShape::FourVectors *four_vector_vertices;
						// real_point3d p1;
						// __int32 found;
						{
							// long i;
							{
								// hkpConvexVerticesShape::FourVectors *const v1;
								{
									// long l;
									{
										// real_vector3d v1;
										// real_point3d p3;
										// real_vector3d v2;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// function call : bool (*const)(real_plane3d *, real_plane3d *, real_point3d *, real_vector3d *)
	todo("implement");
	_sub_10F09390(shape, matrix, color);
}

_extern void _sub_10F0A2E0(hkpShape const *, real_matrix4x3 const *, real_argb_color const *);
void render_debug_physics_shape(hkpShape const *shape, real_matrix4x3 const *matrix, real_argb_color const *color) // 0x10F0A2E0
{
	mangled_x86(MANGLED_TODO, "?render_debug_physics_shape@@YAXPBUhkpShape@@PBUreal_matrix4x3@@PBUreal_argb_color@@@Z");
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
	{
		// real_point3d p2;
		// real_point3d p1;
		// hkpTriangleShape *triangle;
		// real_point3d p3;
	}
	{
		// hkpBoxShape *box;
		// real_rectangle3d aabb;
	}
	{
		// real_vector3d height_vector;
		// real_point3d vertex_b;
		// float height_squared;
		// hkpCapsuleShape *pill;
		// real_point3d vertex_a;
	}
	{
		// char shapebuff[512];
		// hkShapeContainer const *shape_container;
		{
			// hkpListShape *list;
		}
		{
			// unsigned __int32 k;
			{
				// hkpShape *child_shape;
			}
		}
	}
	{
		// hkpBvShape *bv;
	}
	{
		// real_matrix4x3 transform;
		// hkpShape *child_shape;
		// hkpConvexTransformShape *convex_transform;
	}
	{
		// hkpConvexTranslateShape *convex_translate;
	}
	// function call : void (*const)(real_matrix4x3 *, hkTransform *)
	todo("implement");
	_sub_10F0A2E0(shape, matrix, color);
}

/* ---------- private code */
